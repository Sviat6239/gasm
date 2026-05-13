arch rv64;
format elf64;
entry main;
main:
    csrrw a0, 768;
    csrrs a1, 769;
    csrrc a2, 770;
    csrrwi a3, 773;
    csrrsi a4, 774;
    csrrci a5, 775;
    ret;