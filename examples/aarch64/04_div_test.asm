arch aarch64;
entry _start;
_start:
    mov x0, 100;
    mov x1, 3;
    sdiv x2, x0, x1;
    print x2;
