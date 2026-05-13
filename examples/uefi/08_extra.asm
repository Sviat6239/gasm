format efi_64;
declare protocol dq = 0;
entry main;
main:
    open_protocol protocol;
    handle_protocol protocol;
    ret;