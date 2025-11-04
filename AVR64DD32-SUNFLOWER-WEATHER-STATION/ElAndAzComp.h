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
#define DegToRad 0.01745329251994329576923690768489 //pi/180
#define RadToDeg 57.295779513082320876798154814105 //180/pi
#define Default_AZ 17140
#define Default_EL 3730

typedef struct {
    uint16_t elevation;       
	uint16_t elevationTop;
    uint16_t azimuth;        
    uint16_t adjelevation;    
    uint16_t adjazimuth;     
    uint16_t sunlevel;    
} SunAngles;

typedef struct { 
    int16_t UNCOMP;
} Alt;

extern SunAngles SUN;  
extern Alt Altitude;

#endif /* ELANDAZCOMP_H_ */
