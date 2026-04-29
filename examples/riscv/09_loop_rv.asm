arch rv64;
entry main;
main:
    addi t0, zero, 5;
loop:
    print t0;
    addi t0, t0, -1;
    bge t0, zero, loop;
