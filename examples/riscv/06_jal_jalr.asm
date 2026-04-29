arch rv64;
entry main;
main:
    jal ra, func;
    ret;
func:
    print "Inside function";
    jalr zero, 0(ra);
