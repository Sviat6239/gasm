arch x86_64;
format win_64;
entry main;
main:
    mov rax, 15;
    xor rax, 3;
    and rax, 7;
    or rax, 1;
    ret;