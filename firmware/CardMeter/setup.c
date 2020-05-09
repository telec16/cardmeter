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


void clockSetup()
{
	CCP = IOREG;
	CLKCTRL.MCLKCTRLA = OSC20M;
	
	CCP = IOREG;
	CLKCTRL.MCLKCTRLB = PDIV2 | PEN;
	
	CCP = IOREG;
	CLKCTRL.MCLKLOCK = 1;
}

/* V1
 * PA7 -> x
 * PA4/5/6 -> G0/1/2
 * PA3 -> CLK
 * PA2 <- MISO
 * PA1 -> MOSI
 * PA0 <- Prog
 *
 * PB5 -> x
 * PB4 -> x
 * PB0/1/2/3 <- SW1/2/3/4
 *
 * PC3 -> D/C
 * PC2 -> RST
 * PC1 -> _CS_SCR
 * PC0 -> _CS_ADC
 */ 

/* V2
 * PA7 -> x
 * PA4/5/6 -> G0/1/2
 * PA3 -> CLK
 * PA2 <- MISO
 * PA1 -> MOSI
 * PA0 <- Prog
 *
 * PB5 -> _CS_GAIN_A
 * PB4 -> _CS_GAIN_B
 * PB0/1/2/3 <- SW1/2/3/4
 *
 * PC3 -> D/C
 * PC2 -> RST
 * PC1 -> _CS_SCR
 * PC0 -> _CS_ADC
 */ 
 
 /* V4
  * PA7 -> _ADC_RST
  * PA6 <- _RDY
  * PA5 -> _ADC_CS
  * PA4 -> _STANDBY
  * PA3 -> CLK
  * PA2 -> MOSI
  * PA1 <- MISO
  * PA0 <- Prog
  *
  * PB5 -> _SYNC
  * PB4 -> x
  * PB0/1/2/3 <- SW1/2/3/4
  *
  * PC3 -> D/C
  * PC2 -> _SCR_RST
  * PC1 -> _SCR_CS
  * PC0 -> x					
  */ 
 
/* V5 (new frontend on V2 board)
 * PA7 -> x
 * PA4/5/6 -> G0/1/2
 * PA3 -> CLK
 * PA2 <- MISO
 * PA1 -> MOSI
 * PA0 <- Prog
 *
 * PB5 -> x
 * PB4 -> _CS_GAIN
 * PB0/1/2/3 <- SW1/2/3/4
 *
 * PC3 -> D/C
 * PC2 -> RST
 * PC1 -> _CS_SCR
 * PC0 -> _CS_ADC
 */ 
 
void pinSetup()
{
#if defined (V1)
	VPORTA.DIR = 0b00111010;
	VPORTB.DIR = 0b00000000;
	VPORTC.DIR = 0b00001111;
#elif defined (V2)
	VPORTA.DIR = 0b00111010;
	VPORTB.DIR = 0b00110000;
	VPORTC.DIR = 0b00001111;
#elif defined (V4)
	VPORTA.DIR = 0b10111100;
	VPORTB.DIR = 0b00100000;
	VPORTC.DIR = 0b00001110;
#elif defined (V5_F)
	VPORTA.DIR = 0b00111010;
	VPORTB.DIR = 0b00010000;
	VPORTC.DIR = 0b00001111;
#endif
	
	PORTB.PIN0CTRL = PULLUPEN | INVEN;
	PORTB.PIN1CTRL = PULLUPEN | INVEN;
	PORTB.PIN2CTRL = PULLUPEN | INVEN;
	PORTB.PIN3CTRL = PULLUPEN | INVEN;
}
