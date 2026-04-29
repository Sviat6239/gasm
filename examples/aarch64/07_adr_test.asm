arch aarch64;
declare my_data dq 0xCAFEBABE;
entry _start;
_start:
    adr x0, my_data;
    ldr x1, [x0];
    print x1;
