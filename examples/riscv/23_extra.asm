arch rv64;
format elf64;
entry main;
main:
    lui a0, 74565;
    auipc a1, 0;
    addi a0, a0, 5;
    ret;