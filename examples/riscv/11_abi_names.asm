arch rv64;
entry main;
main:
    addi sp, sp, -16;
    sd ra, 8(sp);
    # uses ra, sp, gp, tp aliases
    ld ra, 8(sp);
    addi sp, sp, 16;
    ret;
