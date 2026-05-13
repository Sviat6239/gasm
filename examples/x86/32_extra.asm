arch x86_64;
format win_64;
entry main;
main:
    mov rax, 8;
    mov rbx, 3;
    and rax, rbx;
    or rax, 1;
    xor rax, 2;
    ret;