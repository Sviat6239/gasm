arch x86_64;
format win_64;
entry main;
main:
    mov rax, 2;
    cmp rax, 2;
    je equal;
    mov rbx, 0;
    jmp done;
equal:
    mov rbx, 1;
done:
    ret;