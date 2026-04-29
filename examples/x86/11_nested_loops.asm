arch x86;
entry main;
main:
    mov rcx, 5;
outer:
    mov rbx, 3;
inner:
    print rbx;
    dec rbx;
    jnz inner;
    dec rcx;
    jnz outer;
