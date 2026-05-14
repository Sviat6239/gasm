format efi_64;
entry main;
main:
    stall 1;
    reset;
    ret;