/**
 * @file CLK.c
 * @brief Clock configuration functions for the system.
 *
 * This file contains functions to initialize and configure the external high-frequency
 * crystal oscillator and external clock input for the system.
 * 
 * @author Saulius
 * @date 2024-12-05
 */

#include "Settings.h"

void CLOCK_XOSCHF_clock_init()
{
	/* Enable external (32 MHz) clock input */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_SELHF_EXTCLOCK_gc | CLKCTRL_FRQRANGE_24M_gc | CLKCTRL_ENABLE_bm);

	/* Set the main clock to use external clock as source */
	ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_EXTCLK_gc);

	/* Wait for system oscillator change to complete */
	while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
	{};
	/* Configuration complete;*/
}