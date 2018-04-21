#ifndef NOKIA3310_H_
#define NOKIA3310_H_

#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include "utils.h"
#include "charset.h"

#define LCD_W 96
#define LCD_H 65
#define LCD_L 8


void screenSetup();

void clearLCD();
void setCoord(uint8_t x, uint8_t y);

void putChar(char chr, boolean space);
void putString(char *str, uint8_t posX, uint8_t posY);

void putPicture(uint8_t picture[], uint8_t posX, uint8_t posY, uint8_t sizeX, uint8_t sizeY);


#endif /* NOKIA3310_H_ */