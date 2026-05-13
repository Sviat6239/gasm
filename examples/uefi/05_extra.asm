format efi_64;
declare map dq = 0;
entry main;
main:
    get_memory_map map;
    print map;
    ret;