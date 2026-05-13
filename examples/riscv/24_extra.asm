arch rv64;
format elf64;
declare value dq = 9;
entry main;
main:
    ld a0, value;
    sd a0, value;
    ret;