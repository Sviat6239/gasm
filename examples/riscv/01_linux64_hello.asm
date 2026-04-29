arch rv64;
format elf64;
declare msg char[] = "RISC-V 64 Linux Power!#";
entry main;
main:
    li a7, 64;          # sys_write (riscv)
    li a0, 1;           # fd = stdout
    la a1, msg;         # buf
    li a2, 23;          # count
    ecall;
    li a7, 93;          # sys_exit (riscv)
    li a0, 0;           # status = 0
    ecall;
