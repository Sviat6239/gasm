format efi_64;
entry main;
main:
    locate_handle handle;
    locate_handle_buffer buffer;
    ret;