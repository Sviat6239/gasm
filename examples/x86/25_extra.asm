arch x86_64;
format win_64;
entry main;
main:
    push rax;
    mov rax, 9;
    call adjust;
    pop rbx;
    ret;
adjust:
    add rax, 5;
    ret;