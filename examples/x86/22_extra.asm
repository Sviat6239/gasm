arch x86_64;
format win_64;
declare a dq = 4;
declare b dq = 8;
entry main;
main:
    mov rax, a;
    add rax, b;
    add rax, 16;
    ret;