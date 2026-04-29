arch aarch64;
entry _start;
_start:
    bfi x0, x1, 0, 8;
    ubfx x2, x0, 0, 4;
    print x2;
