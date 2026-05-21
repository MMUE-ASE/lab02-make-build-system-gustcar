#include "gpio.h"
#include "rcc.h"

/*
 * gpio_enable_clock — enable the AHB1 clock for the given GPIO port.
 *
 * TODO P3.3:
 *   Set the corresponding bit in RCC_AHB1ENR.
 *   Use an if/else comparing port_base against GPIOB_BASE and GPIOC_BASE,
 *   then OR-in the correct mask with |=.
 *
 *   Accessing a GPIO peripheral before enabling its clock returns 0
 *   on reads and silently discards writes.
 */
void gpio_enable_clock(uint32_t port_base)
{
    if (port_base == GPIOB_BASE) {
        /* TODO: set RCC_AHB1ENR_GPIOBEN */

    } else if (port_base == GPIOC_BASE) {
        /* TODO: set RCC_AHB1ENR_GPIOCEN */

    }
}

/*
 * gpio_config_input — configure the pin as an input (MODER = 00).
 *
 * TODO P4.2 / P4.4:
 *   GPIOx_MODER allocates 2 bits per pin.
 *   The field for pin N starts at bit position (N * 2).
 *
 *   Steps:
 *     1. Clear the 2-bit field: use &= with the negated mask.
 *        Clear mask: (3U << (pin * 2))
 *     2. Write GPIO_MODER_INPUT (0) into those bits.
 *        The OR is a no-op for INPUT=0, but keep it for consistency.
 */
void gpio_config_input(uint32_t port_base, uint8_t pin)
{
    /* TODO: clear the MODER field for this pin */

    /* TODO: write GPIO_MODER_INPUT into those bits */
}

/*
 * gpio_config_output — configure the pin as a push-pull output (MODER = 01).
 *
 * TODO P4.3 / P4.4:
 *   Same logic as gpio_config_input but writing GPIO_MODER_OUTPUT (1).
 *
 *   Steps:
 *     1. Clear the 2-bit field.
 *     2. Write (GPIO_MODER_OUTPUT << (pin * 2)) with |=.
 */
void gpio_config_output(uint32_t port_base, uint8_t pin)
{
    /* TODO: clear the MODER field for this pin */

    /* TODO: write GPIO_MODER_OUTPUT into those bits */
}

/*
 * gpio_read — read the logic level of the pin from IDR.
 *
 * TODO P5.3:
 *   GPIOx_IDR has one bit per pin.
 *   Read bit N from IDR and return 1 if set, 0 if clear.
 *
 *   Expression: (GPIOx_IDR(port_base) >> pin) & 1U
 */
int gpio_read(uint32_t port_base, uint8_t pin)
{
    /* TODO: return the value of bit 'pin' from IDR */
    return 0;
}

/*
 * gpio_write — write the logic level of the pin using BSRR.
 *
 * TODO P5.4:
 *   BSRR is write-only and performs atomic bit manipulation:
 *     bits [15: 0] — set   (drive pin high)
 *     bits [31:16] — reset (drive pin low)
 *
 *   value != 0 → write (1U << pin)        to BSRR (set)
 *   value == 0 → write (1U << (pin + 16)) to BSRR (reset)
 */
void gpio_write(uint32_t port_base, uint8_t pin, int value)
{
    if (value) {
        /* TODO: set — write to BSRR to drive the pin high */

    } else {
        /* TODO: reset — write to BSRR to drive the pin low */
    }
}
