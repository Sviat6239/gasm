format efi_64;
entry main;
main:
    import entry_point;
    export entry_point;
    return;