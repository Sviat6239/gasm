arch x86_64;
format win_64;
entry main;
main:
    mov rax, 1;
    mov rbx, 2;
    cmp rax, rbx;
    cmovz rcx, rax;
    cmovnz rcx, rbx;
    ret;