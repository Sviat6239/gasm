arch arm64;
format elf64;
entry main;
main:
    mov x0, 1;
    mov x1, 2;
    tbz x0, 1, bit_zero;
    tbnz x1, 0, bit_one;
bit_zero:
bit_one:
    ret;