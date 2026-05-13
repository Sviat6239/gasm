format bin;
entry start;
start:
    mov dx, 1016;
    in al, dx;
    out dx, al;
    ret;