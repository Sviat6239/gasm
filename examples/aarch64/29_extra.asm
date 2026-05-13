arch arm64;
format elf64;
entry main;
main:
    mov x0, 2;
    madd x1, x0, x0;
    msub x2, x1, x0;
    smull x3, x1, x2;
    umaddl x4, x1, x2;
    ret;