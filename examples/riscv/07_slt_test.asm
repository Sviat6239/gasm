arch rv64;
entry main;
main:
    addi a0, zero, 10;
    addi a1, zero, 20;
    slt a2, a0, a1;
    slti a3, a0, 5;
    print a2;
