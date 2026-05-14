format efi_64;
declare pool dq = 0;
entry main;
main:
    allocate_pool pool;
    free_pool pool;
    ret;