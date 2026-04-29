arch x86;
macro exit {
    mov rax, 60;
    xor rdi, rdi;
    syscall;
} endmacro;
entry _start;
_start:
    exit;
