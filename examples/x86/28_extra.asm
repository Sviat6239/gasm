arch x86_64;
format win_64;
declare msg db = "Hello";
declare flag db = 1;
entry main;
main:
    mov rax, msg;
    mov rbx, flag;
    ret;