#include "main.h"

volatile config_t config = {
	.menu = UI_ROOT,
	.action = ACT_NONE,
	.gain = AD8231_G1,
	.timebase = 0,
	.offset = 0
};

volatile data_t data = {
	.raw0 = 0,
	.ch0 = 0.0
};

#define RES_DIV (10.0/480.0)

const float range_table[8] = {
	LTC2315_REF / (RES_DIV *   1) / 2.0,
	LTC2315_REF / (RES_DIV *   2) / 2.0,
	LTC2315_REF / (RES_DIV *   4) / 2.0,
	LTC2315_REF / (RES_DIV *   8) / 2.0,
	LTC2315_REF / (RES_DIV *  16) / 2.0,
	LTC2315_REF / (RES_DIV *  32) / 2.0,
	LTC2315_REF / (RES_DIV *  64) / 2.0,
	LTC2315_REF / (RES_DIV * 128) / 2.0
};
const float step_table[8] = {
	LTC2315_STEP / (RES_DIV *   1) / 2.0,
	LTC2315_STEP / (RES_DIV *   2) / 2.0,
	LTC2315_STEP / (RES_DIV *   4) / 2.0,
	LTC2315_STEP / (RES_DIV *   8) / 2.0,
	LTC2315_STEP / (RES_DIV *  16) / 2.0,
	LTC2315_STEP / (RES_DIV *  32) / 2.0,
	LTC2315_STEP / (RES_DIV *  64) / 2.0,
	LTC2315_STEP / (RES_DIV * 128) / 2.0
};

int main(void)
{
	char buf[16];
	
	clockSetup();
	pinSetup();
	screenSetup();
	AD8231_gain(config.gain, CS_GAIN);

	/* LCD tests
	_delay_ms(100);
	putString("Hey !", 5*LCD_CW, 0);
	_delay_ms(100);
	testLCD();
	clearLCD();//*/

    while (1) 
    {
		data.raw0 = LTC2315_readAll(CS_ADC);
		
		data.ch0 = ((float)data.raw0 - (float)config.offset) * step_table[config.gain];
		
		scanBtn();

		if(config.action == ACT_OFFSET){
			config.offset = data.raw0;
			config.action = ACT_NONE;
		}

		drawUI();
		
		_delay_ms(100);
    }
}
