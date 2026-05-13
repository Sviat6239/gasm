arch rv64;
format elf64;
entry main;
main:
    addi a0, zero, 10;
    addi a1, zero, 20;
    bltu a0, a1, smaller;
    bgeu a0, a1, bigger;
smaller:
    addi a2, zero, 1;
    ret;
bigger:
    addi a2, zero, 2;
    ret;