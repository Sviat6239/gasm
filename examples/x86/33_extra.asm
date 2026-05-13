arch x86_64;
format win_64;
entry main;
main:
    push rax;
    mov rax, 42;
    pop rbx;
    ret;