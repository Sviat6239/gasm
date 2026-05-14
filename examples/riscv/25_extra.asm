arch rv64;
format elf64;
entry main;
main:
    jal ra, func;
    ret;
func:
    addi a0, zero, 1;
    addi a0, a0, 2;
    jalr zero, ra;