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

double calculate_refraction() {
	// 1. Geometrinë korekcija dël aukðèio
    double elevationRad = SUN.elevation * M_PI / 180.0; // Elevacija radianais
    double elevationCorrection = atan(Altitude.UNCOMP / R_EARTH); // Kampas dël aukðèio
    elevationRad += elevationCorrection; // Koreguojame elevacijà

    // 2. Atmosferinës refrakcijos korekcija su drëgme
    double elevationDegree = elevationRad * 180.0 / M_PI; // Paverèiame atgal á laipsnius

    if (elevationDegree > 0) { // Refrakcija taikoma tik teigiamai elevacijai
        double refrakcija = (BMP280.Pressure / 1010.0) * (283.0 / (273.0 + SHT21.T)) *
                            (1.02 * (1 + 0.0037 * SHT21.RH)) / 
                            tan(elevationDegree + 10.3 / (elevationDegree + 5.11));
        elevationDegree += refrakcija; // Pridedame refrakcijà prie elevacijos
    }

    return elevationDegree;
}


void correct_solar_angles() {
    if(SUN.elevation > 0){
        // Adjust the elevation by the refraction and keep the azimuth unchanged
        SUN.adjelevation = calculate_refraction();  
        SUN.adjazimuth = SUN.azimuth;
    }
    // If the elevation is below the horizon, retain the last azimuth and elevation values
}


void SunLevel(){
    ADC0_SetupSLS();  // Set up the ADC for reading the sun level
    SUN.sunlevel = round(ADC0_read()/4);  // Read ADC value, scale it, and round the result
}
