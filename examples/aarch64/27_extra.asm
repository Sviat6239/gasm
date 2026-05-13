arch arm64;
format elf64;
entry main;
main:
    mov x0, 0;
    cbz x0, zero;
    mov x1, 1;
    b done;
zero:
    mov x1, 0;
done:
    ret;