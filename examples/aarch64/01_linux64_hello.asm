arch aarch64;
format elf64;
declare msg char[] = "AArch64 Linux is here!#";
entry _start;
_start:
    mov x8, 64;         # sys_write (aarch64)
    mov x0, 1;          # fd = stdout
    adr x1, msg;        # buf
    mov x2, 23;         # count
    svc 0;
    mov x8, 93;         # sys_exit (aarch64)
    mov x0, 0;          # status = 0
    svc 0;
