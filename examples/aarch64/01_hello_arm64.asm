arch aarch64;
format elf64;
declare msg char[] = "Hello AArch64!";
entry _start;
_start:
    print msg;
    ret;
