/**
 * @file ADC.c
 * @brief Implementation of ADC initialization and setup functions.
 * @author Saulius
 * @date 2024-12-19
 */

#include "Settings.h"

/**
 * @brief Initializes the ADC0 module.
 *
 * Configures the ADC with the following settings:
 * - Accumulated sample count: 128
 * - Prescaler: Division by 4
 * - Resolution: 12-bit
 * - Enables the ADC.
 */
void ADC0_init() {
    ADC0.CTRLB = ADC_SAMPNUM_ACC128_gc; // 1 measurements
    ADC0.CTRLC = ADC_PRESC_DIV4_gc; // 24Mhz / 16 ADC speed
    ADC0.CTRLA = ADC_ENABLE_bm | ADC_RESSEL_12BIT_gc; // 12-bit resolution
}

/**
 * @brief Sets up ADC0 to read WS (PC1) input.
 *
 * Configures the ADC0 reference voltage to VDD and sets the positive input
 * channel to AIN29 (PC1).
 */
void ADC0_SetupWS() {
    VREF.ADC0REF = VREF_REFSEL_VDD_gc;
    ADC0.MUXPOS = ADC_MUXPOS_AIN29_gc; // PC1 as input for WS
}

/**
 * @brief Sets up ADC0 to read WD (PC0) input.
 *
 * Configures the ADC0 reference voltage to VDD and sets the positive input
 * channel to AIN28 (PC0).
 */
void ADC0_SetupWD() {
    VREF.ADC0REF = VREF_REFSEL_VDD_gc;
    ADC0.MUXPOS = ADC_MUXPOS_AIN28_gc; // PC0 as input for WD
}

/**
 * @brief Sets up ADC0 to read Sun Level Sensor (SLS) on PC2.
 *
 * Configures the ADC0 with a reference voltage of 1.024V and sets the positive
 * input channel to AIN30 (PC2).
 */
void ADC0_SetupSLS(uint8_t level) {
    VREF.ADC0REF = level/*VREF_REFSEL_1V024_gc*/; // 1.024V as reference voltage for SLS //0-1.024V, 1-2.048V, 2-4.096V
    ADC0.MUXPOS = ADC_MUXPOS_AIN30_gc; // PC2 as input for SLS
}

/**
 * @brief Reads a value from ADC0.
 *
 * Starts an ADC conversion and waits for the result. Clears the result-ready
 * flag after reading. If accumulation is enabled, the result is shifted
 * appropriately.
 *
 * @return The ADC conversion result as a 12-bit value.
 */
uint16_t ADC0_read() {
    ADC0.COMMAND = ADC_STCONV_bm; // Start conversion
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)); // Wait until result is ready
    ADC0.INTFLAGS = ADC_RESRDY_bm; // Clear result ready flag
    return ADC0.RES >> 4; // Shift result if accumulation is over 16
}
