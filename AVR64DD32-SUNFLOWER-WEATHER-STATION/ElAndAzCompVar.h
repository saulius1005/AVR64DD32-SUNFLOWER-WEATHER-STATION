/*
 * ElAndAzCompVar.h
 *
 * Created: 2024-12-10 18:45:05
 * Author: Saulius
 *
 * This header file contains the definition and initialization of the external `SUN`
 * variable, which is an instance of the `SunAngles` structure.
 * The `SUN` variable holds the solar elevation, azimuth, adjusted angles, and sun level.
 */

#ifndef ELANDAZCOMPVAR_H_
#define ELANDAZCOMPVAR_H_

SunAngles SUN = {
    .adjazimuth = Default_AZ,
    .adjelevation = Default_EL,
    .sunlevel = 0 
};

Alt Altitude = {
 .UNCOMP = 86
};

#endif /* ELANDAZCOMPVAR_H_ */
