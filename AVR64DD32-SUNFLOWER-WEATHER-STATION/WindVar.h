/*
 * WindVar.h
 *
 * Created: 2024-12-19 19:30:46
 *  Author: Saulius
 */ 


#ifndef WINDVAR_H_
#define WINDVAR_H_

WindParam Wind= {
.speed = 0,
.direction = 0
};

FIR_VALUES readwindspeed = {
	.Result = 0,
	.Filter = {0},
	.index = 0 
};

FIR_VALUES readwinddirection = {
	.Result = 0,
	.Filter = {0},
	.index = 0
};



#endif /* WINDVAR_H_ */