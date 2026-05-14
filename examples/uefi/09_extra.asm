format efi_64;
declare handle dq = 0;
declare buffer dq = 0;
entry main;
main:
    locate_handle handle;
    locate_handle_buffer buffer;
    ret;