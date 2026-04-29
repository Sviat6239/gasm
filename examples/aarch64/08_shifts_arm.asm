arch aarch64;
entry _start;
_start:
    mov x0, 1;
    lsl x1, x0, 10;
    lsr x2, x1, 5;
    asr x3, x2, 2;
    print x3;
