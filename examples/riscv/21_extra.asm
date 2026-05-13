arch rv64;
format elf64;
entry main;
main:
    addi t0, zero, 4;
    addi t1, zero, 0;
loop:
    add t1, t1, t0;
    addi t0, t0, -1;
    bne t0, zero, loop;
    ret;