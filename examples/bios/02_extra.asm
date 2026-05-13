format bin;
entry start;
start:
    cli;
    mov dx, 96;
    mov al, 85;
    out dx, al;
    in al, dx;
    sti;
    ret;