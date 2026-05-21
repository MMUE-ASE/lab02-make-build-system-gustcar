#ifndef GPIO_H
#define GPIO_H

/*
 * gpio.h — GPIO register access for the STM32F412
 *
 * Source: RM0402, section 8 "General-purpose I/Os (GPIO)"
 */

#include <stdint.h>

/* -----------------------------------------------------------------------
 * GPIO port base addresses
 * RM0402 — Memory map, AHB1 peripherals
 * ----------------------------------------------------------------------- */
#define GPIOA_BASE 0x40020000UL
#define GPIOB_BASE 0x40020400UL
#define GPIOC_BASE 0x40020800UL
#define GPIOD_BASE 0x40020C00UL
#define GPIOE_BASE 0x40021000UL
#define GPIOF_BASE 0x40021400UL
#define GPIOG_BASE 0x40021800UL
#define GPIOH_BASE 0x40021C00UL

/* -----------------------------------------------------------------------
 * GPIO register access macros (volatile read/write)
 * Offsets from RM0402, GPIO register map
 * ----------------------------------------------------------------------- */
#define GPIOx_MODER(base)   (*(volatile uint32_t *)((base) + 0x00U))
#define GPIOx_OTYPER(base)  (*(volatile uint32_t *)((base) + 0x04U))
#define GPIOx_OSPEEDR(base) (*(volatile uint32_t *)((base) + 0x08U))
#define GPIOx_PUPDR(base)   (*(volatile uint32_t *)((base) + 0x0CU))
#define GPIOx_IDR(base)     (*(volatile uint32_t *)((base) + 0x10U))
#define GPIOx_ODR(base)     (*(volatile uint32_t *)((base) + 0x14U))
#define GPIOx_BSRR(base)    (*(volatile uint32_t *)((base) + 0x18U))

/* -----------------------------------------------------------------------
 * MODERy field values — RM0402, GPIOx_MODER
 * Each pin occupies 2 bits: bits [2y+1 : 2y]
 * ----------------------------------------------------------------------- */
#define GPIO_MODER_INPUT  0U /* 00 — input (reset state) */
#define GPIO_MODER_OUTPUT 1U /* 01 — general-purpose output */
#define GPIO_MODER_AF     2U /* 10 — alternate function */
#define GPIO_MODER_ANALOG 3U /* 11 — analog mode */

/* -----------------------------------------------------------------------
 * Minimal GPIO driver — declarations
 * Implementation in src/gpio.c
 * ----------------------------------------------------------------------- */

/* Enable the AHB1 clock for the port identified by its base address. */
void gpio_enable_clock(uint32_t port_base);

/* Configure the pin as a general-purpose input. */
void gpio_config_input(uint32_t port_base, uint8_t pin);

/* Configure the pin as a general-purpose push-pull output. */
void gpio_config_output(uint32_t port_base, uint8_t pin);

/* Read the logic level of the pin from IDR. Returns 0 or 1. */
int gpio_read(uint32_t port_base, uint8_t pin);

/* Write the logic level of the pin using BSRR. */
void gpio_write(uint32_t port_base, uint8_t pin, int value);

#endif /* GPIO_H */
