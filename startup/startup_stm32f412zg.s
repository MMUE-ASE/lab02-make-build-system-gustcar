/* startup_stm32f412zg.s — Vector table and Reset_Handler
 *
 * This file is part of the template and is already complete.
 * No modifications are required for this lab.
 *
 * STM32F412ZG: Cortex-M4, Flash 0x08000000, RAM 0x20000000
 */

    .syntax unified
    .cpu cortex-m4
    .thumb

/* Symbols defined by the linker script */
    .global _estack
    .global _sdata
    .global _edata
    .global _sidata
    .global _sbss
    .global _ebss

/* Entry point visible to the linker */
    .global Reset_Handler

/* -----------------------------------------------------------------------
 * Interrupt vector table
 * Must be placed in .isr_vector at the start of Flash
 * ----------------------------------------------------------------------- */
    .section .isr_vector, "a", %progbits
    .type g_vectors, %object
g_vectors:
    .word   _estack             /* 0:  initial stack pointer (top of RAM) */
    .word   Reset_Handler       /* 1:  Reset */
    .word   Default_Handler     /* 2:  NMI */
    .word   HardFault_Handler   /* 3:  HardFault */
    .word   Default_Handler     /* 4:  MemManage */
    .word   Default_Handler     /* 5:  BusFault */
    .word   Default_Handler     /* 6:  UsageFault */
    .word   0                   /* 7-10: reserved */
    .word   0
    .word   0
    .word   0
    .word   Default_Handler     /* 11: SVCall */
    .word   Default_Handler     /* 12: Debug Monitor */
    .word   0                   /* 13: reserved */
    .word   Default_Handler     /* 14: PendSV */
    .word   Default_Handler     /* 15: SysTick */
    /* External IRQs: add entries as needed */

/* -----------------------------------------------------------------------
 * Reset_Handler — first code executed by the MCU after reset
 *
 * Required sequence before calling main():
 *   1. Copy the .data section from Flash (LMA) to RAM (VMA).
 *   2. Zero-fill the .bss section.
 *   3. Call main().
 * ----------------------------------------------------------------------- */
    .section .text.Reset_Handler, "ax", %progbits
    .type Reset_Handler, %function
Reset_Handler:

    /* 1. Copy .data from Flash (LMA) to RAM (VMA) */
    ldr     r0, =_sdata         /* destination: start of .data in RAM */
    ldr     r1, =_edata         /* end of .data in RAM */
    ldr     r2, =_sidata        /* source: .data image in Flash */
    b       .Lcopy_check
.Lcopy_loop:
    ldr     r3, [r2], #4
    str     r3, [r0], #4
.Lcopy_check:
    cmp     r0, r1
    bcc     .Lcopy_loop

    /* 2. Zero-fill .bss */
    ldr     r0, =_sbss
    ldr     r1, =_ebss
    mov     r2, #0
    b       .Lzero_check
.Lzero_loop:
    str     r2, [r0], #4
.Lzero_check:
    cmp     r0, r1
    bcc     .Lzero_loop

    /* 3. Call main */
    bl      main

    /* Hang if main returns (should never happen) */
.Lhang:
    b       .Lhang

    .size Reset_Handler, . - Reset_Handler

/* -----------------------------------------------------------------------
 * Default handlers — infinite loop
 * Can be overridden by defining a C function with the same name
 * ----------------------------------------------------------------------- */
    .section .text, "ax", %progbits

    .type HardFault_Handler, %function
HardFault_Handler:
    b       HardFault_Handler
    .size HardFault_Handler, . - HardFault_Handler

    .type Default_Handler, %function
Default_Handler:
    b       Default_Handler
    .size Default_Handler, . - Default_Handler

    .end
