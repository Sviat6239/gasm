arch rv64;
entry main;
main:
    addi a0, zero, 1;
    addi a1, zero, 2;
    beq a0, a1, fail;
    bne a0, a1, pass;
fail:
    print "Failed";
    ret;
pass:
    print "Passed";
    ret;
