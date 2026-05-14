arch x86_64;
format win_64;
declare value dq = 7;
entry main;
main:
    mov rax, value;
    shl rax, 2;
    add rax, 3;
    shr rax, 1;
    ret;