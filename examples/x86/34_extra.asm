arch x86_64;
format win_64;
entry main;
main:
    mov rax, 4;
    mov rbx, 9;
    cmp rax, rbx;
    cmovz rcx, rax;
    cmovnz rcx, rbx;
    ret;