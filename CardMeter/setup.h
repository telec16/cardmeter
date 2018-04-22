#ifndef SETUP_H_
#define SETUP_H_

#define F_CPU 8000000LL
#include <avr/io.h>
#include <util/delay.h>

#define PULLUPEN (1<<3)
#define INVEN (1<<7)
#define OSC20M (0b00<<0)
#define PDIV2 (0b0000<<1)
#define PEN (1<<0)
#define IOREG 0xD8

#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3

typedef enum{FALSE=0, TRUE} boolean;

void pinSetup();
void clockSetup();

#endif /* SETUP_H_ */