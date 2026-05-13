arch x86_64;
format win_64;
declare counter dq = 3;
entry main;
main:
    mov rax, counter;
loop:
    sub rax, 1;
    cmp rax, 0;
    jnz loop;
    ret;