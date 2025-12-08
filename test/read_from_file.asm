format ELF64

public read_from_file

section '.text' executable

read_from_file:
    push rbp
    mov rbp, rsp
    push rbx
    push r12

    mov rbx, rsi   
    mov rcx, rdx  


    mov rax, 2          
    mov rdi, rdi        
    mov rsi, 0          
    mov rdx, 0         
    syscall
    mov r12, rax        

    test r12, r12
    js .done


    mov rax, 0          
    mov rdi, r12       
    mov rsi, rbx        
    mov rdx, rcx       
    syscall

    mov rbx, rax        


    mov rax, 3          
    mov rdi, r12
    syscall

    mov rax, rbx        
    pop r12
    pop rbx
    pop rbp
    ret

.done:
    mov rax, -1
    pop r12
    pop rbx
    pop rbp
    ret

section '.note.GNU-stack'
