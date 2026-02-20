ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x8000, LENGTH = 128M
}

STACK_SIZE = 64K;

SECTIONS
{
    . = ORIGIN(RAM);

    .text :
    {
        KEEP(*(.text.boot))
        *(.text*)
        *(.rodata*)
    } > RAM

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > RAM

    /* Heap starts after BSS */
    __heap_start = .;
    _end = .;

    /* Stack at top of RAM */
    . = ORIGIN(RAM) + LENGTH(RAM);
    __stack_top = .;
    _estack = .;

    /* Heap must never pass this */
    __heap_end = __stack_top - STACK_SIZE;
}