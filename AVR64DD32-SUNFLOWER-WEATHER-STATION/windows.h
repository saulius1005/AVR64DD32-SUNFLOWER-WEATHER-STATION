/*
 * windows.h
 *
 * Created: 2025-01-26 23:35:38
 *  Author: Saulius
 */ 


#ifndef WINDOWS_H_
#define WINDOWS_H_

typedef struct {
		volatile int16_t tempC; //SHT21 temperature
		volatile int16_t tempC2; //BMP280 temperature
		volatile uint16_t tempRh;
		volatile uint32_t tempp;
		volatile uint8_t tempWD;
		volatile uint8_t tempWS;
		volatile uint16_t tempSLS;
		volatile uint16_t tempAz;
		volatile int16_t tempEl;
		volatile uint8_t tempSec;
		volatile uint8_t tempHsec;
		volatile uint8_t tempKey;
		volatile uint8_t tempNoRefresh;
		volatile bool firstUpdate[5]; // 5 langai: 21, 22, 23, 24, Main Menu
} ScreenUpdater;

enum WindowID {
	WINDOW_DATE_LOCATION = 21,
	WINDOW_TIME_ANGLE_VIEW = 22,
	WINDOW_LOCATION = 23,
	WINDOW_WEATHER = 24,
	WINDOW_MAIN_MENU = 0
};

extern ScreenUpdater Refresh;  



#endif /* WINDOWS_H_ */