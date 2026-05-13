format efi_64;
entry main;
main:
    connect_controller controller;
    disconnect_controller controller;
    ret;