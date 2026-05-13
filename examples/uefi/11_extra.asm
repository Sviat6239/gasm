format efi_64;
declare iface dq = 0;
entry main;
main:
    install_protocol_interface iface;
    reinstall_protocol_interface iface;
    uninstall_protocol_interface iface;
    ret;