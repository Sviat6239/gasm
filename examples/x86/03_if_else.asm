arch x86;
format elf64;
entry _start;
_start:
    mov rax, 100;
    if(rax > 50) {
        print "Greater than 50";
    } else {
        print "50 or less";
    }
