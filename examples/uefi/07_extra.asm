format efi_64;
declare controller dq = 0;
entry main;
main:
    connect_controller controller;
    disconnect_controller controller;
    ret;