arch rv64;
entry main;
main:
    addi a0, zero, 0x55;
    # not, and, or logic
    not a1, a0;
    print a1;
