arch aarch64;
declare buffer db[64];
entry _start;
_start:
    str x0, [sp, 16];
    ldr x1, [sp, 16];
