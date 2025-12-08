format ELF64

public write_to_file

section '.text' executable

write_to_file:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13

    mov r12, rdi      ; filename
    mov rbx, rsi      ; data pointer
    mov r13, rdx      ; data length

    ; open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644)
    mov rax, 2
    mov rdi, r12
    mov rsi, 0x241
    mov rdx, 0644o
    syscall
    mov r12, rax      ; fd
    test r12, r12
    js .exit

    ; write(fd, data, len)
    mov rax, 1
    mov rdi, r12
    mov rsi, rbx
    mov rdx, r13
    syscall

    ; close(fd)
    mov rax, 3
    mov rdi, r12
    syscall

.exit:
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret

section '.note.GNU-stack'

