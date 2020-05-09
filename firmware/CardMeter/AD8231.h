#ifndef AD8231_H_
#define AD8231_H_

#include <avr/io.h>
#include "utils.h"

typedef enum{
	AD8231_G1,
	AD8231_G2,
	AD8231_G4,
	AD8231_G8,
	AD8231_G16,
	AD8231_G32,
	AD8231_G64,
	AD8231_G128
} AD8231_gain_t;


void AD8231_changeGain(AD8231_gain_t gain, unsigned char csPin);


#endif /* AD8231_H_ */