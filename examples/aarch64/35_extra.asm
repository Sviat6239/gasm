arch arm64;
format elf64;
entry main;
main:
    smc 0;
    hvc 1;
    dmb 0;
    dsb 0;
    isb 0;
    ret;