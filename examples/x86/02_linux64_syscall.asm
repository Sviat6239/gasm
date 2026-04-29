arch x86;
format elf64;
declare msg char[] = "Hello Linux x64!#";
entry _start;
_start:
    # write(1, msg, 17)
    mov rax, 1;         # sys_write
    mov rdi, 1;         # fd = stdout
    mov rsi, msg;       # buf
    mov rdx, 17;        # count
    syscall;
    # exit(0)
    mov rax, 60;        # sys_exit
    xor rdi, rdi;       # status = 0
    syscall;
