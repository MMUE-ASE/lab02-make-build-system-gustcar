/*
 * stm32f412zg.ld — Linker script for the STM32F412ZG
 *
 * Device memory (datasheet STM32F412ZG):
 *   Flash : 0x08000000 — 1 MB
 *   RAM   : 0x20000000 — 256 KB
 *
 * This file is part of the template and is already complete.
 */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

/* Entry point: first code executed after reset */
ENTRY(Reset_Handler)

/* Stack top: high end of RAM */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* Vector table: must be at the start of Flash */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* Code and read-only data */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _sidata = .;        /* LMA of .data: image stored in Flash */
    } > FLASH

    /* Initialised variables: VMA in RAM, LMA (image) in Flash */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    /* Uninitialised variables: RAM only, zeroed by Reset_Handler */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > RAM

    /* Discard unneeded sections */
    /DISCARD/ :
    {
        *(.ARM.exidx*)
        *(.eh_frame*)
    }
}
