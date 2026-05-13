arch x86_64;
format win_64;
entry main;
main:
    call helper;
    ret;
helper:
    mov rax, 1;
    ret;