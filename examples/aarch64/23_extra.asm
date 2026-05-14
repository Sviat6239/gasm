arch arm64;
format elf64;
entry main;
main:
    mov x0, 15;
    ands x0, x0, 7;
    orr x0, x0, 8;
    eor x1, x0, 3;
    bic x2, x1, 1;
    ret;