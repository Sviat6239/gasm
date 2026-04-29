arch aarch64;
entry _start;
_start:
    bl my_procedure;
    ret;
my_procedure:
    print "ARM procedure";
    ret;
