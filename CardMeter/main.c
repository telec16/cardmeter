#include "setup.h"
#include <stdlib.h>
#include <avr/io.h>
#include "utils.h"
#include "NOKIA3310.h"
#include "LTC6911.h"
#include "LTC2402.h"


int main(void)
{
	uint32_t ch0, ch1;
	char buf[16];
	
	clockSetup();
	pinSetup();
	screenSetup();
	_delay_ms(100);
	changeGain(G1);

	putString("Hey !", 4, 2);
	_delay_ms(1000);
	
	VPORTA.DIR |= 1<<7;
	VPORTB.DIR |= 1<<4;

    while (1) 
    {
		/*
		getData(&ch0, &ch1);
		PORTA.OUTTGL = 1<<7;*/
		
		//*
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

