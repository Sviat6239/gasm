format efi_64;
entry main;
main:
    install_protocol_interface iface;
    reinstall_protocol_interface iface;
    uninstall_protocol_interface iface;
    ret;