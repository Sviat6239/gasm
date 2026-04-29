arch x86;
format elf64;
entry _start;
_start:
    mov rax, 10;
    add rax, 20;
    sub rax, 5;
    mul rax, 2;
    div rax, 3;
    print rax;
    ret;
