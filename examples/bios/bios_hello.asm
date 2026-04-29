arch x86;
format bin;

entry kernel_main;

kernel_main:
    cli;                # Disable interrupts
    lgdt [gdt_ptr];      # Load Global Descriptor Table

    mov eax, cr0;
    or eax, 1;
    mov cr0, eax;       # Switch to Protected Mode

    out 0x80, al;       # Debug port
    in al, 0x60;        # Read keyboard

    hlt;                # Halt CPU

gdt_ptr:
    dw 0x1F;
    dd 0x1000;

