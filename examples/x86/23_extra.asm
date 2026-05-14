arch x86_64;
format win_64;
entry main;
main:
    mov rax, 255;
    test rax, 1;
    jz even;
    mov rbx, 1;
    jmp done;
even:
    mov rbx, 0;
done:
    ret;