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
    //Aukðèio korekcija
    float elevationRad = SUN.elevation * DegToRad; // Elevacija radianais
    float altitudeCorrection = atan(Altitude.UNCOMP / R_EARTH); // Aukðèio korekcija
    elevationRad += altitudeCorrection;

    float refraction = 0.0;
	if(SUN.elevation > 0){//Atmosferinës refrakcijos pataisa
		// Atmosferos parametrai
		float P = BMP280.Pressure / 1010.0; // Normalizuotas slëgis
		float T = 283.0 / (273.0 + SHT21.T); // Normalizuota temperatûra
		float RH = SHT21.RH / 100.0; // Santykinë drëgmë
		// Refrakcijos formulë
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
    ADC0_SetupSLS();  // Set up the ADC for reading the sun level
    SUN.sunlevel = round(ADC0_read()/4);  // Read ADC value, scale it, and round the result
}
