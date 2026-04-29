arch rv64;
entry main;
main:
    lui a0, 0x12345;
    auipc a1, 0;
    print a1;
