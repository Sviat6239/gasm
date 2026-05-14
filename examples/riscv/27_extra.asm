arch rv64;
format elf64;
entry main;
main:
    c.add x1, x2;
    c.li x3, 7;
    c.mv x4, x5;
    c.addi x6, 1;
    ebreak;