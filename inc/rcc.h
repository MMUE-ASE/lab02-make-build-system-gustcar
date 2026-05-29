#ifndef RCC_H
#define RCC_H

/*
 * rcc.h — Reset and Clock Control for the STM32F412
 *
 * Source: RM0402, section 6 "Reset and clock control (RCC)"
 */

#include <stdint.h>

/* -----------------------------------------------------------------------
 * RCC base address
 * RM0402 — Memory map, AHB1 peripherals
 * ----------------------------------------------------------------------- */
#define RCC_BASE 0x40023800UL

/* -----------------------------------------------------------------------
 * RCC_AHB1ENR — AHB1 peripheral clock enable register
 * Offset 0x30 from RCC_BASE
 * RM0402, section 6.3.10
 * ----------------------------------------------------------------------- */
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30U))

/* TODO P3.1 — bit mask to enable the GPIOB clock
 *             Form: (1U << bit_number)
 *             Source: RM0402, RCC_AHB1ENR, field GPIOBEN             */
#define RCC_AHB1ENR_GPIOBEN (1U << 1U)

/* TODO P3.2 — bit mask to enable the GPIOC clock
 *             Source: RM0402, RCC_AHB1ENR, field GPIOCEN             */
#define RCC_AHB1ENR_GPIOCEN (1U << 2U)

/* Other ports — provided for reference */
#define RCC_AHB1ENR_GPIOAEN (1U << 0U)
#define RCC_AHB1ENR_GPIODEN (1U << 3U)
#define RCC_AHB1ENR_GPIOEEN (1U << 4U)

#endif /* RCC_H */
