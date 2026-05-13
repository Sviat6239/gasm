format bin;
entry start;
start:
    cpuid;
    rdmsr;
    wrmsr;
    rdtsr;
    ret;