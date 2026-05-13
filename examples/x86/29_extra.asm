arch x86_64;
format win_64;
entry main;
main:
    mov rax, 5;
    mov rbx, 0;
top:
    add rbx, rax;
    dec rax;
    cmp rax, 0;
    jne top;
    ret;