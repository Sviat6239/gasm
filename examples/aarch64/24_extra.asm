arch arm64;
format elf64;
entry main;
main:
    mov x0, 1;
    lsl x0, x0, 4;
    lsr x0, x0, 1;
    asr x0, x0, 1;
    ror x0, x0, 2;
    ret;