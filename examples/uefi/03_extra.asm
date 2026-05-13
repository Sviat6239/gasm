format efi_64;
entry main;
main:
    allocate_pages pages;
    free_pages pages;
    ret;