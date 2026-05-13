arch arm64;
format elf64;
declare steps dq = 4;
entry main;
main:
    mov x0, steps;
    mov x1, 0;
loop:
    adds x1, x1, x0;
    subs x0, x0, 1;
    bne loop;
    ret;