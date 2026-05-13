format efi_64;
declare pages dq = 2;
entry main;
main:
    allocate_pages pages;
    free_pages pages;
    ret;