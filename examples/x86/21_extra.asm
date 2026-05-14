arch x86_64;
format win_64;
declare steps dq = 4;
declare total dq = 0;
entry main;
main:
    mov rax, steps;
    xor rbx, rbx;
spin:
    add rbx, rax;
    sub rax, 1;
    cmp rax, 0;
    jne spin;
    mov rcx, total;
    add rcx, rbx;
    ret;