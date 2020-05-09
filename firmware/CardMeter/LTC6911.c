#include "LTC6911.h"

#define GAIN_PIN 4
#define GAIN_P VPORTA.OUT
#define GAIN_MASK (0b111<<GAIN_PIN)

void setValue(uint8_t val);

void setValue(uint8_t val)
{
	GAIN_P = (GAIN_P & ~GAIN_MASK) | ((val << GAIN_PIN) & GAIN_MASK);
}

void LTC6911_changeGain(LTC6911_gain_t gain)
{
	switch(gain){
		case LTC6911_OPEN:
			setValue(0b000);
		break;
		case LTC6911_G1:
			setValue(0b001);
		break;
		case LTC6911_G2:
			setValue(0b010);
		break;
		case LTC6911_G5:
			setValue(0b011);
		break;
		case LTC6911_G10:
			setValue(0b100);
		break;
		case LTC6911_G20:
			setValue(0b101);
		break;
		case LTC6911_G50:
			setValue(0b110);
		break;
		case LTC6911_G100:
			setValue(0b111);
		break;
		default:
		break;
		 
	}
}

