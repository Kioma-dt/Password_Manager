format ELF64

public my_rand
public my_rand_set_seed

section '.data' writeable
seed dq 1  

section '.text' executable

my_rand_set_seed:
    mov rax, 201
    xor rdi, rdi
    syscall

    mov [seed], rax

my_rand:

    mov rax, [seed]

    mov rcx, 1103515245
    imul rax, rcx
    add rax, 12345
    mov [seed], rax

    shr rax, 16
    and rax, 0xFF

    ret



section '.note.GNU-stack'
