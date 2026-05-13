format bin;
entry start;
start:
    pushfd;
    popfd;
    lahf;
    sahf;
    ret;