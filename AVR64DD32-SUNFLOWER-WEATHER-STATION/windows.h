/*
 * windows.h
 *
 * Created: 2025-01-26 23:35:38
 *  Author: Saulius
 */ 


#ifndef WINDOWS_H_
#define WINDOWS_H_

typedef struct {
		int16_t tempC; //SHT21 temperature
		int16_t tempC2; //BMP280 temperature
		uint16_t tempRh;
		uint16_t tempp;
		uint8_t tempWD;
		uint8_t tempWS;
		uint16_t tempSLS;
		uint16_t tempAz;
		uint16_t tempEl;
		uint8_t tempSec;
		uint8_t tempHsec;
		uint8_t tempKey;
} ScreenUpdater;

extern ScreenUpdater Refresh;  



#endif /* WINDOWS_H_ */