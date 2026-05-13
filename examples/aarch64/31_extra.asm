arch arm64;
format elf64;
entry main;
main:
    stp x29, x30, 16;
    ldp x29, x30, 16;
    ret;