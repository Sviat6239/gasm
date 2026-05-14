arch x86_64;
format win_64;
declare base dq = 64;
entry main;
main:
    lea rax, base;
    add rax, 8;
    ret;