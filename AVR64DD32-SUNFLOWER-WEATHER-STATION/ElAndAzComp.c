/*
 * ElAndAzComp.c
 *
 * Created: 2024-12-10 18:43:10
 * Author: Saulius
 *
 * This file contains functions for calculating the refraction angle for solar elevation,
 * correcting solar angles, and reading the sun level from an ADC.
 */

#include "Settings.h"
#include "ElAndAzCompVar.h"

float calculate_refraction() {
	// Konvertuojam á tikrus laipsnius
	float elevationDeg = SUN.elevation / 100.0f;
	float elevationRad = elevationDeg * DegToRad;
	float altitudeCorrection = atan(Altitude.UNCOMP / R_EARTH);
	elevationRad += altitudeCorrection;

	float refraction = 0.0f;
	if (elevationDeg > 0.0f) {
		float P = BMP280.Pressure / 1010.0f;
		float T = 283.0f / (273.0f + SHT21.T);
		float RH = SHT21.RH / 100.0f;

		double denominator = tan(elevationRad + (10.3 / (elevationDeg + 5.11)) * DegToRad);
		refraction = (P / T) * (0.0167f * (1 + 0.0037f * RH)) / denominator;
	}

	// Gràþinam pataisà ×100
	return refraction * 100.0f;
}

void correct_solar_angles() {
    if(SUN.elevation > 0){
        // Adjust the elevation by the refraction and keep the azimuth unchanged
        SUN.adjelevation = SUN.elevation + (int16_t)calculate_refraction(); 
        SUN.adjazimuth = SUN.azimuth; //leave last azimuth value after sunset
    }
    // If the elevation is below the horizon, retain the last azimuth and elevation values
}

void SunLevel(){
    ADC0_SetupSLS(0);  // 1.023V
	if(ADC0_read()== 4095){
		ADC0_SetupSLS(1); //2.048V
		if (ADC0_read()== 4095){
			ADC0_SetupSLS(2); //4.096V
			if(ADC0_read()== 4095){ //this is more less actual limit of SLS but still
				ADC0_SetupSLS(5); //Vdd
				SUN.sunlevel = 1.220703125* ADC0_read(); //Assume Vdd is 5.0V 
			}
			else
			SUN.sunlevel = ADC0_read();
		}
		else
			SUN.sunlevel = (ADC0_read()/2)+0.5;
	}
	else
	 SUN.sunlevel = (ADC0_read()/4)+0.5;  // Read ADC value, scale it, and round the result
}
