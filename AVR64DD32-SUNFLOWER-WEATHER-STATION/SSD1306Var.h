/*
 * SSD1306Var.h
 *
 * Created: 2025-01-22 21:32:06
 *  Author: Saulius
 */ 


#ifndef SSD1306VAR_H_
#define SSD1306VAR_H_

uint8_t ssd1306Commands[26]={
	0x00,
	0xAE,  // Display OFF (sleep mode)
	0xA8,  // Set multiplex ratio(1 to 64)
	0x3F,  // 1/64 duty
	0xD3,  // Set display offset
	0x00,  // No offset
	0x40,  // Set start line address
	0x20,  // Set Memory Addressing Mode
	0x00,  // Horizontal addressing mode
	0xD9,  // Set pre-charge period
	0xF1,  // Pre-charge period
	0xDB,  // Set VCOMH deselect level
	0x40,  // VCOMH deselect level
	0xA1,  // Set segment re-map
	0xC8,  // Set COM Output Scan Direction
	0xDA,  // Set COM pins hardware configuration
	0x12,  // Alternative COM pin config
	0x81,  // Set contrast control
	0xff,  // Contrast value
	0xA4,  // Entire display ON, resume to RAM content display
	0xA6,  // Set normal display (not inverted)
	0xD5,  // Set display clock divide ratio/oscillator frequency
	0xf0,  // Set divide ratio
	0x8D,  // Charge Pump
	0x14,  // Enable charge pump
	0xAF  // Display ON in normal mode
};

#endif /* SSD1306VAR_H_ */