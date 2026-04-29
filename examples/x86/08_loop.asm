arch x86;
entry _start;
_start:
    mov rcx, 10;
loop:
    print rcx;
    dec rcx;
    cmp rcx, 0;
    jnz loop;
