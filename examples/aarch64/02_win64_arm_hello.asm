arch aarch64;
format win64;
entry main;
main:
    # Windows ARM64 uses x0, x1, x2 for first args
    adr x0, title;
    adr x1, text;
    mov x2, 0;
    bl MessageBoxW;
    ret;
declare title char[] = "Windows on ARM";
declare text char[] = "Running natively on AArch64!";
