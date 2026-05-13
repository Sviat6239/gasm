arch arm64;
format elf64;
entry main;
main:
    mov f0, f1;
    fadd f0, f0, f1;
    fmul f0, f0, f1;
    fcmp f0, f1;
    ret;