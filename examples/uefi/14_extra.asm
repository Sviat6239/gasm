format efi_64;
declare entry_point dq = 0;
entry main;
main:
    import entry_point;
    export entry_point;
    return;