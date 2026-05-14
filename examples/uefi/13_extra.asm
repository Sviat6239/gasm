format efi_64;
declare message char[] = "UEFI ready";
entry main;
main:
    print message;
    call callback;
    ret;
callback:
    print message;
    ret;