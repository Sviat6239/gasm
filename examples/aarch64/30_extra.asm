arch arm64;
format elf64;
entry main;
main:
    msr x0, x1;
    mrs x2, x3;
    svc 0;
    ret;