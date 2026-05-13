arch arm64;
format elf64;
entry main;
main:
    bl helper;
    ret;
helper:
    mov x0, 1;
    ret;