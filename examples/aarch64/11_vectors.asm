arch aarch64;
entry _start;
_start:
    # uses v registers supported in main.cpp
    # note: main.cpp only tokenizes them
    print v0;
    print v31;
