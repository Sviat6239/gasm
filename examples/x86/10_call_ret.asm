arch x86;
entry _start;
_start:
    call my_func;
    ret;
my_func:
    print "In function";
    ret;
