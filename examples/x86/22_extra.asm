arch x86_64;
format win_64;
declare left dq = 12;
declare right dq = 30;
entry main;
main:
    mov rax, left;
    mov rbx, right;
    cmp rax, rbx;
    cmovl rax, rbx;
    add rax, 5;
    ret;