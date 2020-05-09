#ifndef SETUP_H_
#define SETUP_H_

#define F_CPU 8000000LL
#include <avr/io.h>
#include <util/delay.h>

#define V5_F

#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3

typedef enum{FALSE=0, TRUE} boolean;

void pinSetup();
void clockSetup();

#endif /* SETUP_H_ */