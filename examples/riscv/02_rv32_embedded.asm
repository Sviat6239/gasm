arch rv32;
format elf32;
entry reset_handler;
reset_handler:
    # Initialize stack
    la sp, _stack_top;
    # Toggle some LED via memory mapped IO
    li t0, 0x40001000;  # GPIO base
    li t1, 1;
    sw t1, 0(t0);       # Turn on
    ret;
