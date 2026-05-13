arch rv64;
format elf64;
declare msg char[] = "RISC-V demo";
entry main;
main:
    li a7, 64;
    li a0, 1;
    la a1, msg;
    ecall;
    ret;