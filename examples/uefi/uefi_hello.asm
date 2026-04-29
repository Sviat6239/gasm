arch x86;
format efi;

entry efi_main;

efi_main:
    # EFI Boot Services demonstration
    allocate_pool 2, 1024, [buffer];
    locate_handle 2, [protocol_guid], 0, [handle_buffer];
    open_protocol [handle], [protocol_guid], [interface], [agent], [controller], 1;

    stall 1000000;      # Wait 1 second

    get_memory_map [size], [map], [key], [descr_size], [version];

    set_watchdog_timer 0, 0, 0, 0;

    free_pool [buffer];
    reset 0;            # Cold Reset

