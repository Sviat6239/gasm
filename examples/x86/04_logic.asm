arch x86;
entry main;
main:
    xor rax, rax;
    and rax, 0xFF;
    or rax, 0x01;
    not rax;
    print rax;
