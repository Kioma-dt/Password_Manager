format ELF64

public rc_4

section '.data' writable

section '.text' executable
rc_4:
    ; rdi - key
    ; rsi - keylen
    ; rdx - data
    ; rcx - datalen


    push rbp

    ; push callee-saved registers
    push rbx
    push r12
    push r13
    push r14
    push r15

    ; r8 - data
    mov r8, rdx

    ; enlarge stack
    mov rbp, rsp
    sub rsp, 256
    ; r12 - S[0]
    mov r12, rsp

    test rsi, rsi
    jz .done
    test rcx, rcx
    jz .done

    ; init S
    xor rax, rax
.S_init_loop:
    mov byte [r12 + rax], al
    inc rax
    cmp rax, 256
    jne .S_init_loop

    ; r13 - i
    xor r13, r13
    ; r14 - j
    xor r14, r14

.ksa_loop:
    ; j = (j + S[i] + K[i mod keylen]) mod 256
    movzx rax, byte [r12 + r13]
    add r14, rax

    mov rax, r13
    xor rdx, rdx
    xor r9, r9
    div rsi

    ; r9 = i % keylen
    mov r9, rdx

    movzx rax, byte [rdi + r9]
    add r14, rax

    ; r14 = r14 mod 256
    and r14, 0xFF

    ; swap S[i] and S[j]
    movzx rax, byte [r12 + r13]
    movzx rdx, byte [r12 + r14]
    mov byte [r12 + r13], dl
    mov byte [r12 + r14], al

    inc r13
    cmp r13, 256
    jne .ksa_loop

    xor r13, r13
    xor r14, r14        

    ; rbx - data
    mov rbx, r8
    xor rax, rax

.prga_loop:
    cmp rcx, 0
    je .done

    ; i = (i + 1) mod 256
    inc r13
    and r13, 0xFF

    ; j = (j + S[i]) mod 256
    movzx rax, byte [r12 + r13]
    add r14, rax
    and r14, 0xFF

    ; swap S[i], S[j]
    movzx rax, byte [r12 + r13]
    movzx rdx, byte [r12 + r14]
    mov byte [r12 + r13], dl
    mov byte [r12 + r14], al

    ; t = (S[i] + S[j]) mod 256
    movzx rax, byte [r12 + r13]
    movzx rdx, byte [r12 + r14]
    add rax, rdx
    and rax, 0xFF

    ; K = S[t]
    movzx rax, byte [r12 + rax]

    mov dl, [rbx]
    xor dl, al
    mov [rbx], dl

    inc rbx
    dec rcx
    jmp .prga_loop

.done:
    mov rsp, rbp
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret

section '.note.GNU-stack'