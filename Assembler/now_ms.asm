format ELF64

public now_ms

section '.data' writeable
time dq 2 dup (?)  

section '.text' executable


now_ms:
    mov rax, 228            
    mov rdi, 1           
    lea rsi, [time]            
    syscall

    mov rax, [time]         

    imul rax, rax, 1000 

    ret
section '.note.GNU-stack'
