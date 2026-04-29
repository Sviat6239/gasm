arch rv64;
format elf64;
declare hello char[] = "RISC-V 64!";
entry main;
main:
    print hello;
    ret;
