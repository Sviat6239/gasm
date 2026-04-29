arch x86;
entry main;
main:
    # mock stack ops using supported regs
    mov rsp, 0x1000;
    mov rbp, rsp;
    print rsp;
