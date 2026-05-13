format bin;
entry start;
start:
    mov ax, 1;
    cmp ax, 2;
    jnz next;
    ret;
next:
    ret;