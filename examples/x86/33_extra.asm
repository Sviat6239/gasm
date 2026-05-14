arch x86_64;
format win_64;
entry main;
main:
    push rax;
    push rbx;
    mov rax, 1;
    mov rbx, 2;
    pop rbx;
    pop rax;
    ret;