arch x86_64;
format win_64;
declare value dq = 7;
entry main;
main:
    lea rax, value;
    ret;