format bin;
entry start;
start:
    smsw ax;
    lmsw ax;
    invlpg page;
    wbinvd;
    ret;