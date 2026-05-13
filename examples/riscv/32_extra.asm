arch rv64;
format elf64;
entry main;
main:
    bltu a0, a1, less;
    bgeu a0, a1, ge;
less:
    ret;
ge:
    ret;