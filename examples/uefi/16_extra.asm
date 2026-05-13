format efi_64;
entry main;
main:
    print hello;
    stall 5;
    allocate_pool memory;
    free_pool memory;
    ret;