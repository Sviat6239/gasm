format bin;
entry start;
start:
    pushfd;
    cli;
    sti;
    popfd;
    iret;