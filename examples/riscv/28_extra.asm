arch rv64;
format elf64;
entry main;
main:
    c.j target;
    c.beqz a0, target;
    c.bnez a1, target;
target:
    ret;