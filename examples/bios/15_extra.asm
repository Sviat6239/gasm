format bin;
entry start;
start:
    xchg ax, bx;
    xadd ax, bx;
    bsf cx, dx;
    bsr cx, dx;
    ret;