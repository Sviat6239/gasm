format win32;
declare number dw = 84;
entry _start;

_start:
    mov rax, 84;
    add rax, number;
    print rax;