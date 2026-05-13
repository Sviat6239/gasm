arch arm64;
format elf64;
entry main;
main:
    mov x0, 3;
    mov x1, 7;
    cmp x0, x1;
    bge ge;
    mov x2, 0;
    b done;
ge:
    mov x2, 1;
done:
    ret;