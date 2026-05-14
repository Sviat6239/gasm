format efi_64;
declare notify dq = 0;
entry main;
main:
    register_protocol_notify notify;
    ret;