#include "setup.h"
#include <stdlib.h>
#include <avr/io.h>
#include "utils.h"
#include "NOKIA3310.h"
#include "AD8231.h"
#include "LTC2315.h"


int main(void)
{
	uint8_t tempo=0;
	uint16_t data, ch;
	AD8231_gain_t gain = AD8231_G1;
	
	char buf[16];
	
	clockSetup();
	pinSetup();
	screenSetup();
	AD8231_gain(gain, CS_GAIN);

	_delay_ms(100);
	putString("Hey !", 5*LCD_CW, 0);
	_delay_ms(100);
	testLCD();

    while (1) 
    {
		putCharAt((tempo++%2)?'@':' ', 12*LCD_CW, 0);

		data = LTC2315_readAll(CS_ADC);
		
		putString("              ", 0, 2);
		
		itoa(data, buf, 16);
		putString(buf, 0, 2);
		
		ch = (uint16_t)(((float)data) * LTC2315_STEP * 1000.0);
			
		itoa(ch, buf, 10);
		putString(buf, 0, 3);
		

		if(_SW1) gain--;
		if(_SW2) gain++;
		if(_SW3) ;
		if(_SW4) ;

		gain = _CLIP(0, gain, 7);
		AD8231_gain(gain, CS_GAIN);
		
		putString("Gain:    ", 0, 1);
		itoa(gain, buf, 10);
		putString(buf, 7*LCD_CW, 1);
		
		_delay_ms(1000);
    }
}

