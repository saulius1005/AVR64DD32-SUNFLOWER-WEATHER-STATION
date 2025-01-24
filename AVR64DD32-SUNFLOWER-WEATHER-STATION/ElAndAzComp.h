/*
 * ElAndAzComp.h
 *
 * Created: 2024-12-10 18:44:47
 * Author: Saulius
 *
 * This header file contains the declaration of the `SunAngles` structure and the external
 * `SUN` variable used to store and manipulate solar angle data and sun level information.
 */

#ifndef ELANDAZCOMP_H_
#define ELANDAZCOMP_H_

#define R_EARTH 6371000.0
#define Default_AZ 171.4
#define Default_EL 37.3

typedef struct {
    float elevation;       
	float elevationTop;
    float azimuth;        
    float adjelevation;    
    float adjazimuth;     
    uint16_t sunlevel;    
} SunAngles;

typedef struct { 
    int16_t UNCOMP;
} Alt;

extern SunAngles SUN;  
extern Alt Altitude;

#endif /* ELANDAZCOMP_H_ */
