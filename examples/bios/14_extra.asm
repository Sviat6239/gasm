format bin;
entry start;
start:
    mov ax, 1;
    mov bx, 2;
    cmp ax, bx;
    jnz mismatch;
    ret;
mismatch:
    ret;