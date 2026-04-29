arch rv64;
entry main;
main:
    addi a0, zero, 10;
    addi a1, a0, 5;
    add a2, a0, a1;
    sub a3, a2, a0;
    print a3;
