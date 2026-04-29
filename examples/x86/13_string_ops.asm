arch x86;
declare str char[] = "Processing...";
entry main;
main:
    print str;
    mov rsi, str;
    # loop over string logi
