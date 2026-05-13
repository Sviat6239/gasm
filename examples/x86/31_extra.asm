arch x86_64;
format win_64;
entry main;
main:
    mov rax, 6;
    mul rax, 7;
    div rax, 2;
    ret;