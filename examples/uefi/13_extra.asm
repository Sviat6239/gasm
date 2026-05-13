format efi_64;
entry main;
main:
    print message;
    call callback;
    ret;