arch rv32;
entry main;
main:
    lui t0, 0x10000;
    auipc t1, 0x2000;
    add t2, t0, t1;
    print t2;
