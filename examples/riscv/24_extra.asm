arch rv64;
format elf64;
declare value dq = 9;
declare backup dq = 0;
entry main;
main:
    ld a0, value;
    sd a0, backup;
    addi a0, a0, 1;
    sd a0, value;
    ret;