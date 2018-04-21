#include "LTC2402.h"

#define SCK 3//PA3
#define SDO 2//PA2
#define CS 0//PC0

void getData(uint32_t *ch0, uint32_t *ch1)
{
	uint32_t dat, val;
	ADC_CHN_t chn;
	ADC_STATUS_t stat;
	uint8_t i;
	
	for(i=0; i<2; i++)
	{
		while(!ready());
		
		dat = readAll();
		
		parse(dat, &chn, &stat, &val);
		if(chn == CH0)
			*ch0 = val;
		else
			*ch1 = val;
	}
}

boolean parse(uint32_t data, ADC_CHN_t *chn, ADC_STATUS_t *status, uint32_t *value)
{
	*chn = ((data>>ADC_CHN)&1) ? CH1:CH0;
	
	status->SIG = (data>>ADC_SIG) & 1;
	status->EXR = (data>>ADC_EXR) & 1;
	status->subLSBs = data & 0b1111;
	
	*value = (data>>ADC_VALUE) & 0xFFFFFF;
	
	return !((data>>ADC_EOC) & 1);
}

boolean ready()
{
	boolean r = FALSE;

	_CLR(VPORTC.OUT, CS);
	r = _GET(VPORTA.IN, SDO);
	_SET(VPORTC.OUT, CS);

	return r;
}

uint32_t readAll()
{
	uint8_t i;
	uint32_t data=0;

	_CLR(VPORTA.OUT, SCK);
	_CLR(VPORTC.OUT, CS);

	for(i=0; i<32; i++)
	{
		_SET(VPORTA.OUT, SCK);
		_CLR(VPORTA.OUT, SCK);
		data = (data<<1) | _GET(VPORTA.IN, SDO);
	}

	_SET(VPORTC.OUT, CS);

	return data;
}



