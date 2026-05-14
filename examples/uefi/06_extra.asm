format efi_64;
declare timer dq = 1;
entry main;
main:
    set_watchdog_timer timer;
    ret;