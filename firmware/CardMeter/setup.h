#ifndef SETUP_H_
#define SETUP_H_

#define F_CPU 8000000LL
#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	uint8_t pin;
	VPORT_t * port;
} pin_t;

#define V5_F

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

// Buttons
#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3

// Serial
extern const pin_t SCK; //PA3
extern const pin_t SDI; //PA2
extern const pin_t SDO; //PA1
extern const pin_t CS_SCR; //PC1
extern const pin_t CS_ADC; //PC0

// Gain
extern const pin_t CS_GAIN; //PB4

// Screen
extern const pin_t DC; //PC3
extern const pin_t RST; //PC2

void pinSetup();
void clockSetup();

#endif /* SETUP_H_ */