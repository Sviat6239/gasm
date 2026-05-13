format efi_64;
entry main;
main:
    allocate_pool pool;
    free_pool pool;
    ret;