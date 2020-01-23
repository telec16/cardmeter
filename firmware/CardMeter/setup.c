/*		____u___
 * VDD-|	A	|-GND
 * PA4-|	T	|-PA3
 * PA5-|	t	|-PA2
 * PA6-|	i	|-PA1
 * PA7-|	n	|-PA0
 * PB5-|	y	|-PC3
 * PB4-|	1	|-PC2
 * PB3-|	6	|-PC1
 * PB2-|	1	|-PC0
 * PB1-|____6___|-PB0
 */

#include "setup.h"

void clockSetup()
{
	CCP = IOREG;
	CLKCTRL.MCLKCTRLA = OSC20M;
	
	CCP = IOREG;
	CLKCTRL.MCLKCTRLB = PDIV2 | PEN;
	
	CCP = IOREG;
	CLKCTRL.MCLKLOCK = 1;
}

/*
 * PA4/5/6 -> G0/1/2
 * PA3 -> CLK
 * PA2 -> MISO
 * PA1 -> MOSI
 *
 * PB0/1/2/3 -> SW1/2/3/4
 *
 * PC3 -> D/C
 * PC2 -> RST
 * PC1 -> _CS_SCR
 * PC0 -> _CS_ADC
 *
 * PA7 PB4/5 -> Free
 */ 
void pinSetup()
{
	VPORTA.DIR = 0b00111010;
	VPORTB.DIR = 0b00000000;
	VPORTC.DIR = 0b00001111;
	
	PORTB.PIN0CTRL = PULLUPEN | INVEN;
	PORTB.PIN1CTRL = PULLUPEN | INVEN;
	PORTB.PIN2CTRL = PULLUPEN | INVEN;
	PORTB.PIN3CTRL = PULLUPEN | INVEN;
}