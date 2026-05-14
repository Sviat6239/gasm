arch x86_64;
format win_64;
entry main;
main:
    nop;
    mov rax, 0;
    jmp exit;
exit:
    hlt;
    ret;