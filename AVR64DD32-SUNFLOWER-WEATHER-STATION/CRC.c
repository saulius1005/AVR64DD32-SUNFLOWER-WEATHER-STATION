/*
 * CRC.c
 *
 * Created: 2024-12-04 18:26:29
 * Author: Saulius
 *
 * This file implements a CRC-8 MAXIM calculation using a precomputed lookup table.
 * The function `CRC8MAXIM` verifies the CRC for a 32-bit data input and extracts the 
 * data value without the CRC if the CRC is correct.
 */

#include "Settings.h"
#include "CRCVar.h"

/**
 * @brief Calculates and validates the CRC-8 MAXIM for a 32-bit data input.
 *
 * This function extracts the first 16 bits of the provided 32-bit data, calculates
 * the CRC-8 MAXIM value for the data, and compares it with the last 8 bits (the received CRC).
 * If the calculated CRC matches the received CRC, the function returns the first 16 bits of 
 * the data (without the CRC). Otherwise, it returns 0 to indicate an error in the CRC.
 *
 * @param data 32-bit input data, where the last 8 bits represent the CRC value.
 * @return uint16_t Returns the 16-bit data if CRC is valid, 0 if the CRC is incorrect.
 */
uint16_t CRC8MAXIM(uint32_t data) {
    // Extract the data and CRC
    uint32_t data_value = (data >> 8) & 0xFFFF; // First 16 bits
    uint32_t received_crc = data & 0xFF;        // Last 8 bits (CRC)

    // Calculate CRC
    uint32_t crc_calculated = 0x00;
    crc_calculated = crc8_table[crc_calculated ^ (data_value >> 8)];  // High 8 bits
    crc_calculated = crc8_table[crc_calculated ^ (data_value & 0xFF)]; // Low 8 bits

    // Validate CRC
    if (crc_calculated != received_crc) {
        return 0; // CRC is incorrect
    }

    // Return the 16-bit data without CRC
    return data_value; // CRC is correct
}

/**
 * @brief CRC-8 calculation for CDMA2000 using a precomputed lookup table.
 * 
 * This function calculates the CRC-8 checksum for the input data using the CDMA2000
 * CRC polynomial. It uses a lookup table to quickly compute the CRC for each byte
 * of the input data. The result is returned as a single byte (CRC value).
 * 
 * @param data The input data to calculate the CRC for.
 * @return The CRC-8 checksum value for the data.
 */
uint8_t crc8_cdma2000_for_tower(){
	uint8_t buf[9];
	// MSB-first
	buf[0] = (uint8_t)(SUN.adjazimuth >> 8); //azimuth (FFFF)
	buf[1] = (uint8_t)(SUN.adjazimuth & 0xFF);
	buf[2] = (uint8_t)(SUN.adjelevation >> 8);
	buf[3] = (uint8_t)(SUN.adjelevation & 0xFF); //elevation (FFFF)
	buf[4] = (uint8_t)(SUN.elevationTop >> 8);
	buf[5] = (uint8_t)(SUN.elevationTop & 0xFF); //Topelevation (FFFF)
	buf[6] = (uint8_t)readwindspeed.Result; // wind speed (FF)
	uint16_t saveOneBit = ((readwinddirection.Result & 0x07) << 12) | (SUN.sunlevel & 0x0FFF); //wind direction (F)(values only 0- 7) + light level(FFF)(values only 0-4095) = (F+FFF)
	buf[7] = (uint8_t)(saveOneBit >> 8); //split wind direction and part of light level data
	buf[8] = (uint8_t)(saveOneBit & 0xFF); // left part of light level

	uint8_t crc = 0xFF;
	for (size_t i = 0; i < 9; i++) { // length = 9 bites
		crc = crc8_table2[crc ^ buf[i]];
	}
	return crc;
}