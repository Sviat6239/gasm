format bin;
entry start;
start:
    lidt idt;
    lgdt gdt;
    ret;