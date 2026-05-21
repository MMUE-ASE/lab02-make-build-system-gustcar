#include "board.h"
#include "gpio.h"
#include "rcc.h"

/*
 * main — application entry point: button controls LED by polling.
 *
 * Goal: read the state of B1 (PC13) and drive LD2 (PB7) accordingly.
 *
 * Button logic:
 *   B1 not pressed → pin low
 *   B1 pressed     → pin high
 */
int main(void)
{
    /* ------------------------------------------------------------------
     * TODO 1 — Enable the GPIO port clocks.
     *
     * Without this step GPIO registers do not respond.
     * Call gpio_enable_clock() for both B1_PORT and LD2_PORT.
     * ------------------------------------------------------------------ */


    /* ------------------------------------------------------------------
     * TODO 2 — Configure LD2 as an output.
     *
     * Call gpio_config_output() with LD2_PORT and LD2_PIN.
     * ------------------------------------------------------------------ */


    /* ------------------------------------------------------------------
     * TODO 3 — Configure B1 as an input.
     *
     * Call gpio_config_input() with B1_PORT and B1_PIN.
     * The MODER reset value is already input (00), but do it explicitly
     * so the code is self-documenting.
     * ------------------------------------------------------------------ */


    /* ------------------------------------------------------------------
     * Main polling loop
     * ------------------------------------------------------------------ */
    while (1) {
        /* TODO 4 — Read B1 and control LD2.
         *
         * Steps:
         *   a) Read gpio_read(B1_PORT, B1_PIN).
         *   b) Write the result with gpio_write(LD2_PORT, LD2_PIN, ...).
         */

    }
}
