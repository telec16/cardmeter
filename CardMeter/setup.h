#ifndef SETUP_H_
#define SETUP_H_

#define F_CPU 16000000LL
#include <avr/io.h>
#include <util/delay.h>

typedef enum{FALSE=0, TRUE} boolean;


void pinSetup();

#endif /* SETUP_H_ */