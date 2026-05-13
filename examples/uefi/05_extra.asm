format efi_64;
entry main;
main:
    get_memory_map map;
    ret;