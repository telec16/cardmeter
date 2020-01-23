#include "setup.h"
#include <stdlib.h>
#include <avr/io.h>
#include "utils.h"
#include "NOKIA3310.h"
#include "LTC6911.h"
#include "LTC2402.h"


int main(void)
{
	uint32_t ch, data;
	uint16_t ch0=0, ch1=0;
	ADC_CHN_t chn;
	ADC_STATUS_t status;
	
	uint8_t bias=T_BIAS, vop=T_VOP;
	char buf[16];
	
	clockSetup();
	pinSetup();
	screenSetup();
	_delay_ms(100);
	changeGain(G100);

	putString("Hey !", 5*LCD_CW, 0);
	_delay_ms(1000);
	
	VPORTA.DIR |= 1<<7;
	VPORTB.DIR |= 1<<4;
	testLCD();

    while (1) 
    {
		//*
		for (int i=0; i<4; i++){
			if(ready()){
				putString("OK ", i*3*LCD_CW, 1);
			}else{
				putString("NOK", i*3*LCD_CW, 1);
			}
			_delay_ms(1);
		}//*/
		
		data = readAll();
		parse(data, &chn, &status, &ch);
		
		putString("              ", 0, 2);
		
		itoa(data, buf, 16);
		putString(buf, 0, 2);
		itoa(ch, buf, 16);
		putString(buf, 5*LCD_CW, 2);
		itoa(status.subLSBs, buf, 2);
		putString(buf, 10*LCD_CW, 2);
		
		itoa(chn == CH1, buf, 2);
		putString("CH", 0, 3);
		putString(buf, 2*LCD_CW, 3);
		itoa(status.EXR, buf, 2);
		putString("E", 4*LCD_CW, 3);
		putString(buf, 5*LCD_CW, 3);
		itoa(status.SIG, buf, 2);
		putString("S", 7*LCD_CW, 3);
		putString(buf, 8*LCD_CW, 3);
		itoa(status.EOC, buf, 2);
		putString("OK", 10*LCD_CW, 3);
		putString(buf, 12*LCD_CW, 3);
		
		if(chn == CH1)
			ch1 = (uint16_t)(((float)ch)*ADC_STEP*1000.0);
		else
			ch0 = (uint16_t)(((float)ch)*ADC_STEP*1000.0);
			
		itoa(ch0, buf, 10);
		putString(buf, 0, 4);
		itoa(ch1, buf, 10);
		putString(buf, LCD_W/2, 4);
		
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
		getData(&ch0, &ch1);
		PORTA.OUTTGL = 1<<7;*/
		
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

