#ifndef LTC6911_H_
#define LTC6911_H_

#include <avr/io.h>

typedef enum{
	OPEN,
	G1,
	G2,
	G5,
	G10,
	G20,
	G50,
	G100
} Gain;


void changeGain(Gain gain);


#endif /* LTC6911_H_ */