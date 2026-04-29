arch x86;
format win64;
declare caption char[] = "Alert";
declare text char[] = "Hello from GASM on Windows x64!";
entry main;
main:
    # Shadow space for Win64 ABI
    sub rsp, 32;
    xor rcx, rcx;       # hWnd = NULL
    mov rdx, text;      # lpText
    mov r8, caption;    # lpCaption
    mov r9, 0;          # uType = MB_OK
    call MessageBoxA;
    add rsp, 32;
    ret;
