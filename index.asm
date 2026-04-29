arch x86;
format elf64;

declare number dw = 84;
declare msg1 char[] = "Grether than 150";
declare msg2 char[] = "Less than 150";

entry _start;
# simple comment

_start:
    mov rax, 84;
    add rax, number;
    if(rax >= 150){
        print msg1;
    } else {
        print msg2;
    }
    print rax;