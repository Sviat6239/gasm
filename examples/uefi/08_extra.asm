format efi_64;
entry main;
main:
    open_protocol protocol;
    handle_protocol protocol;
    ret;