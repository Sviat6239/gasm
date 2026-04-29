arch aarch64;
entry _start;
_start:
    mov x0, 10;
    if(x0 == 10) {
        print "x0 is 10";
    }
