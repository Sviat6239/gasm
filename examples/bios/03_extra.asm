format bin;
entry start;
start:
    pushfd;
    lahf;
    sahf;
    popfd;
    ret;