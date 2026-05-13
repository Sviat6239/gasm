format efi_64;
entry main;
main:
    register_protocol_notify notify;
    ret;