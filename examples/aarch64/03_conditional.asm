arch aarch64;
entry _start;
_start:
    mov x0, 0;
    cbz x0, is_zero;
    print "Not zero";
    b end;
is_zero:
    print "Is zero";
end:
    ret;
