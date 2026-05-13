arch arm64;
format elf64;
entry main;
main:
    adc x0, x1, x2;
    adcs x3, x0, x1;
    sbc x4, x3, x2;
    sbcs x5, x4, x1;
    ret;