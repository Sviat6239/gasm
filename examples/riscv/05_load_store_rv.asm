arch rv64;
declare data_val dq 0xFF;
entry main;
main:
    ld a0, data_val;
    addi a0, a0, 1;
    sd a0, data_val;
    print a0;
