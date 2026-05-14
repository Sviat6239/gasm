format bin;
declare port dw = 96;
entry start;
start:
    mov dx, port;
    mov al, 255;
    out dx, al;
    ret;