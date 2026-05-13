arch rv64;
format elf64;
entry main;
main:
    slli a0, a0, 1;
    srli a0, a0, 1;
    srai a0, a0, 1;
    sll a1, a0, a0;
    srl a2, a1, a0;
    sra a3, a2, a0;
    ret;