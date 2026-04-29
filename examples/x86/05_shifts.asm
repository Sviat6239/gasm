arch x86;
entry main;
main:
    mov rax, 1;
    shl rax, 4;
    shr rax, 2;
    rol rax, 1;
    print rax;
