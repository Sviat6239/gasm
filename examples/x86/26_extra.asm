arch x86_64;
format win_64;
declare one db = 1;
declare two db = 2;
entry main;
main:
    mov rax, one;
    mov rbx, two;
    add rax, rbx;
    xor rbx, rbx;
    ret;