arch x86_64;
format win_64;
entry main;
main:
    mov rax, 1;
    shl rax, 4;
    shr rax, 1;
    sar rax, 1;
    ret;