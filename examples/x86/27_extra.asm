arch x86_64;
format win_64;
entry main;
main:
    mov rax, 1;
    mov rbx, 1;
    cmp rax, rbx;
    je equal;
    mov rcx, 0;
    jmp done;
equal:
    mov rcx, 1;
done:
    ret;