arch rv64;
format elf64;
declare addr dq = 0;
entry main;
main:
    lr_w a0, addr;
    sc_w a1, addr;
    amoswap_w a2, addr;
    amoadd_w a3, addr;
    ret;