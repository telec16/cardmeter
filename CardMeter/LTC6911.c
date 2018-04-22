#include "LTC6911.h"

#define GAIN_PIN 4
#define GAIN_MASK (0b111<<GAIN_PIN)

void setValue(uint8_t val)
{
	VPORTA.OUT = (VPORTA.OUT & ~GAIN_MASK) | ((val << GAIN_PIN) & GAIN_MASK);
}

void changeGain(Gain gain)
{
	switch(gain){
		case OPEN:
			setValue(0b000);
		break;
		case G1:
			setValue(0b001);
		break;
		case G2:
			setValue(0b010);
		break;
		case G5:
			setValue(0b011);
		break;
		case G10:
			setValue(0b100);
		break;
		case G20:
			setValue(0b101);
		break;
		case G50:
			setValue(0b110);
		break;
		case G100:
			setValue(0b111);
		break;
		default:
		break;
		 
	}
}

