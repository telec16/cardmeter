#ifndef LTC6911_H_
#define LTC6911_H_

#include <avr/io.h>

typedef enum{
	LTC6911_OPEN,
	LTC6911_G1,
	LTC6911_G2,
	LTC6911_G5,
	LTC6911_G10,
	LTC6911_G20,
	LTC6911_G50,
	LTC6911_G100
} LTC6911_gain_t;


void LTC6911_gain(LTC6911_gain_t gain);


#endif /* LTC6911_H_ */