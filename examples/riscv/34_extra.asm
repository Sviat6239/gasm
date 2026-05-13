arch rv64;
format elf64;
entry main;
main:
    xor a0, a1;
    or a0, a2;
    and a0, a3;
    xori a0, a0, 1;
    ori a0, a0, 2;
    andi a0, a0, 3;
    ret;