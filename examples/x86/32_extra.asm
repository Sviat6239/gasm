arch x86_64;
format win_64;
entry main;
main:
    mov rax, 5;
    test rax, 1;
    jnz set;
    ret;
set:
    mov rbx, 1;
    ret;