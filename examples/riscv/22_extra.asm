arch rv64;
format elf64;
entry main;
main:
    addi a0, zero, 10;
    addi a1, zero, 20;
    beq a0, a1, fail;
    bne a0, a1, pass;
fail:
    ret;
pass:
    ret;