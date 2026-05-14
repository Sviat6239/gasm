arch arm64;
format elf64;
declare source dq = 8;
declare sink dq = 0;
entry main;
main:
    ldr x0, source;
    str x0, sink;
    ret;