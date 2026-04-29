arch rv32;
entry main;
main:
    addi t0, zero, 42;
    if(t0 == 42) {
        print "Target reached";
    }
