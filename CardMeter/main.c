/*
 * PB0/1/2/3 -> SW1/2/3/4
 * PA4/5/6 -> G0/1/2
 * PA3 -> CLK
 * PA2 -> MISO
 * PA1 -> MOSI
 * PC3 -> D/C
 * PC2 -> RST
 * PC1 -> _CS_SCR
 * PC0 -> _CS_ADC
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include "setup.h"
#include "utils.h"
#include "NOKIA3310.h"
#include "LTC6911.h"
#include "LTC2402.h"


int main(void)
{
	uint32_t ch0, ch1;
	char buf[16];
	
	pinSetup();
	screenSetup();
	changeGain(OPEN);

	putString("Hey !", 4, 2);

    while (1) 
    {
		getData(&ch0, &ch1);
		
		putString("       ", 0, 3);
		putString("       ", 0, 4);
		
		itoa(ch0, buf, 16);
		putString(buf, 0, 3);
		itoa(ch1, buf, 16);
		putString(buf, 0, 4);
    }
}

