#include "LTC2315.h"

uint16_t LTC2315_readAll(pin_t cs)
{
	uint8_t i;
	uint16_t data=0;

	_CLR_PIN(SCK);
	_delay_us(1);
	_CLR_PIN(cs);

	for(i=0; i<14; i++)
	{
		_CLR_PIN(SCK);
		_delay_us(1);
		_SET_PIN(SCK);
		_delay_us(1);
		if((1 <= i) && (i <= 12))
			data = (data<<1) | _GET_PIN(SDI);
	}

	_SET_PIN(cs);

	return data;
}



