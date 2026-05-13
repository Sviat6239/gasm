format bin;
entry start;
start:
    cli;
    out dx, al;
    in al, dx;
    sti;
    ret;