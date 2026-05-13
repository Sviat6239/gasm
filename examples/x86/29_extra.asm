arch x86_64;
format win_64;
entry main;
main:
    mov rax, 3;
    mov rbx, 0;
top:
    add rbx, rax;
    sub rax, 1;
    cmp rax, 0;
    jne top;
    ret;