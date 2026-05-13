arch x86_64;
format win_64;
declare msg db = "alpha";
declare mode db = 3;
entry main;
main:
    mov rax, msg;
    mov rbx, mode;
    ret;