arch rv64;
format elf64;
entry main;
main:
    addi a0, zero, 1;
    addi a0, a0, 2;
    addi a0, a0, 3;
    ret;