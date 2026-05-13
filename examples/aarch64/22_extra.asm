arch arm64;
format elf64;
entry main;
main:
    mov x0, 3;
    cmp x0, 3;
    bne miss;
    mov x1, 1;
    b done;
miss:
    mov x1, 0;
done:
    ret;