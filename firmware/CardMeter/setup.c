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

#define PULLUPEN (1<<3)
#define INVEN (1<<7)
#define PEN (1<<0)

#define OSC20M (0b00<<0)
#define PDIV2 (0b0000<<1)

#define IOREG 0xD8


// Serial
const pin_t SCK = {.pin=3, .port=&VPORTA}; //PA3
const pin_t SDI = {.pin=2, .port=&VPORTA}; //PA2
const pin_t SDO = {.pin=1, .port=&VPORTA}; //PA1
const pin_t CS_SCR = {.pin=1, .port=&VPORTC}; //PC1
const pin_t CS_ADC = {.pin=0, .port=&VPORTC}; //PC0

// Gain
const pin_t CS_GAIN = {.pin=4, .port=&VPORTB}; //PB4

// Screen
const pin_t DC = {.pin=3, .port=&VPORTC}; //PC3
const pin_t RST = {.pin=2, .port=&VPORTC}; //PC2
	

void clockSetup()
{
	CCP = IOREG;
	CLKCTRL.MCLKCTRLA = OSC20M;
	
	CCP = IOREG;
	CLKCTRL.MCLKCTRLB = PDIV2 | PEN;
	
	CCP = IOREG;
	CLKCTRL.MCLKLOCK = 1;
}
 
void pinSetup()
{
#if defined (V1)
	VPORTA.DIR = 0b01111010;
	VPORTB.DIR = 0b00000000;
	VPORTC.DIR = 0b00001111;
#elif defined (V2)
	VPORTA.DIR = 0b01111010;
	VPORTB.DIR = 0b00110000;
	VPORTC.DIR = 0b00001111;
#elif defined (V4)
	VPORTA.DIR = 0b10111100;
	VPORTB.DIR = 0b00100000;
	VPORTC.DIR = 0b00001110;
#elif defined (V5_F)
	VPORTA.DIR = 0b01111010;
	VPORTB.DIR = 0b00010000;
	VPORTC.DIR = 0b00001111;
	PORTA.PIN2CTRL = PULLUPEN;
	VPORTC.OUT = 0x3;
#endif
	
	PORTB.PIN0CTRL = PULLUPEN | INVEN;
	PORTB.PIN1CTRL = PULLUPEN | INVEN;
	PORTB.PIN2CTRL = PULLUPEN | INVEN;
	PORTB.PIN3CTRL = PULLUPEN | INVEN;
}
