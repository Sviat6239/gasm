format efi_64;
declare hello char[] = "UEFI hello";
declare memory dq = 0;
entry main;
main:
    print hello;
    stall 5;
    allocate_pool memory;
    free_pool memory;
    ret;