arch arm64;
format elf64;
entry main;
main:
    cmn x0, x1;
    tst x0, x1;
    cbnz x0, next;
    ret;
next:
    eret;