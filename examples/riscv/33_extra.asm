arch rv64;
format elf64;
entry main;
main:
    mul a0, a1;
    mulh a1, a2;
    mulhsu a2, a3;
    mulhu a3, a4;
    divu a4, a5;
    rem a5, a6;
    remu a6, a7;
    ret;