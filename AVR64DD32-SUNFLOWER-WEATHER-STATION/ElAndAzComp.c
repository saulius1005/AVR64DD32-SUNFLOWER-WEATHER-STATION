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
    //Auk��io korekcija
    float elevationRad = SUN.elevation * DegToRad; // Elevacija radianais
    float altitudeCorrection = atan(Altitude.UNCOMP / R_EARTH); // Auk��io korekcija
    elevationRad += altitudeCorrection;

    float refraction = 0.0;
	if(SUN.elevation > 0){//Atmosferin�s refrakcijos pataisa
		// Atmosferos parametrai
		float P = BMP280.Pressure / 1010.0; // Normalizuotas sl�gis
		float T = 283.0 / (273.0 + SHT21.T); // Normalizuota temperat�ra
		float RH = SHT21.RH / 100.0; // Santykin� dr�gm�
		// Refrakcijos formul�
		double denominator = tan(elevationRad + (10.3 / (SUN.elevation + 5.11)) * DegToRad);
			refraction = (P / T) * (0.0167 * (1 + 0.0037 * RH)) / denominator;
	}

    return SUN.elevation + refraction;
}

void correct_solar_angles() {
    if(SUN.elevation > 0){
        // Adjust the elevation by the refraction and keep the azimuth unchanged
        SUN.adjelevation = calculate_refraction();  
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
