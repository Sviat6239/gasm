format efi_64;
declare path dq = 0;
entry main;
main:
    locate_device_path path;
    ret;