arch arm64;
format elf64;
entry main;
main:
    bl worker;
    ret;
worker:
    mov x0, 1;
    adds x0, x0, 2;
    ret;