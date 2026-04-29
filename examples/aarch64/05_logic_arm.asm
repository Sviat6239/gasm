arch aarch64;
entry _start;
_start:
    orr x0, xzr, 0x1;
    eor x1, x0, 0x1;
    bic x2, x0, 0x1;
    print x1;
