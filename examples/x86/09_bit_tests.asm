arch x86;
entry _start;
_start:
    mov rax, 0b1010;
    tst rax, 1;
    jnz bit_set;
    print "Bit 0 is not set";
bit_set:
    ret;
