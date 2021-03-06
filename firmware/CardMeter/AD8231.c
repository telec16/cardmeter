#include "AD8231.h"

#define GAIN_PIN 4
#define GAIN_P VPORTA.OUT
#define GAIN_MASK (0b111<<GAIN_PIN)

void setValue(uint8_t val);

void setValue(uint8_t val)
{
	GAIN_P = (GAIN_P & ~GAIN_MASK) | ((val << GAIN_PIN) & GAIN_MASK);
}

void AD8231_gain(AD8231_gain_t gain, pin_t csPin)
{
	_CLR_PIN(csPin);
	
	switch(gain){
		case AD8231_G1:
		setValue(0b000);
		break;
		case AD8231_G2:
		setValue(0b001);
		break;
		case AD8231_G4:
		setValue(0b010);
		break;
		case AD8231_G8:
		setValue(0b011);
		break;
		case AD8231_G16:
		setValue(0b100);
		break;
		case AD8231_G32:
		setValue(0b101);
		break;
		case AD8231_G64:
		setValue(0b110);
		break;
		case AD8231_G128:
		setValue(0b111);
		break;
		default:
		break;	
	}
	
	_SET_PIN(csPin);
}

