#include "setup.h"
#include <stdlib.h>
#include <avr/io.h>
#include "utils.h"
#include "NOKIA3310.h"
#include "AD8231.h"
#include "LTC2315.h"


int main(void)
{
	uint16_t data, ch;
	
	uint8_t bias=T_BIAS, vop=T_VOP;
	char buf[16];
	
	clockSetup();
	pinSetup();
	screenSetup();
	_delay_ms(100);
	AD8231_changeGain(AD8231_G16, CS_GAIN);

	putString("Hey !", 5*LCD_CW, 0);
	_delay_ms(1000);
	
	VPORTA.DIR |= 1<<7;
	VPORTB.DIR |= 1<<4;
	testLCD();

    while (1) 
    {
		data = LTC2315_readAll(CS_ADC);
		
		putString("              ", 0, 2);
		
		itoa(data, buf, 16);
		putString(buf, 0, 2);
		
		ch = (uint16_t)(((float)data) * LTC2315_STEP * 1000.0);
			
		itoa(ch, buf, 10);
		putString(buf, 0, 4);
		
		_delay_ms(250);
		
		bias = _CLIP(0, bias, 7);
		vop = _CLIP(0, vop, 0x40);
		
		changeBias(bias);
		changeVop(vop);
		
		if(_SW1) bias++;
		if(_SW2) bias--;
		if(_SW3) vop++;
		if(_SW4) vop--;
		
		itoa(bias, buf, 10);
		putString(buf, 0, 0);
		itoa(vop, buf, 16);
		putString(buf, 11*LCD_CW, 0);
		
		/*
		testLCD();
		PORTA.OUTTGL = 1<<7;//*/
		/*
		itoa(ch0, buf, 16);
		putString(buf, 0, 3);
		itoa(ch1, buf, 16);
		putString(buf, 0, 4);//*/
		
		
		/*
		if(_GET(VPORTB.IN, SW2)){
			_SET(VPORTA.OUT, 7);
			}else{
			_CLR(VPORTA.OUT, 7);
		}
		
		_CHG(VPORTB.OUT, 4, _GET(VPORTB.IN, SW4));//*/
    }
}

