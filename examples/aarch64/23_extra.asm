arch arm64;
format elf64;
entry main;
main:
    mov x0, 15;
    ands x0, x0, 7;
    orr x0, x0, 1;
    eor x0, x0, 2;
    bic x0, x0, 1;
    ret;