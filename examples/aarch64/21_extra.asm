arch arm64;
format elf64;
declare value dq = 1;
entry main;
main:
    mov x0, value;
    adds x0, x0, 4;
    subs x0, x0, 1;
    ret;