#ifndef BOARD_H
#define BOARD_H

/*
 * board.h — Signal assignments for the NUCLEO-F412ZG board
 *
 * Fill in the TODOs with the values you found in UM1974
 * and recorded in answers.env.
 *
 * Source: UM1974 — STM32 Nucleo-144 boards (MB1137)
 */

#include "gpio.h"

#include <stdint.h>

/* -----------------------------------------------------------------------
 * User button B1
 * ----------------------------------------------------------------------- */

/* TODO P1.1 — pin number of B1 within its GPIO port (0-15)
 *             Source: UM1974, section "Push-button"                  */
#define B1_PIN 0U

/* TODO P1.2 — base address of the GPIO port for B1
 *             Use the constants from gpio.h: GPIOA_BASE, GPIOB_BASE...
 *             Source: UM1974, section "Push-button"                  */
#define B1_PORT GPIOA_BASE

/* -----------------------------------------------------------------------
 * User LED LD2 (blue)
 * ----------------------------------------------------------------------- */

/* TODO P1.4 — pin number of LD2 within its GPIO port (0-15)
 *             Source: UM1974, section "LEDs"                         */
#define LD2_PIN 1U

/* TODO P1.5 — base address of the GPIO port for LD2
 *             Use the constants from gpio.h: GPIOA_BASE, GPIOB_BASE...
 *             Source: UM1974, section "LEDs"                         */
#define LD2_PORT GPIOD_BASE

#endif /* BOARD_H */
