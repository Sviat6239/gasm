arch aarch64;
declare val uint64 = 1234;
entry _start;
_start:
    ldr x0, val;
    add x0, x0, 1;
    str x0, val;
    print x0;
