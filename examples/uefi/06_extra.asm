format efi_64;
entry main;
main:
    set_watchdog_timer timer;
    ret;