arch rv64;
format elf64;
entry main;
main:
    lui a0, 74565;
    auipc a1, 0;
    ret;