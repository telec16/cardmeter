/*
00100001-PD=0 V=0 H=1
00000101-TC=01
00010101-BS=101
10010011-Vop=0010011
00001010-S=10
00100000-PD=0 V=0 H=0
00001100-D=1 E=0
00010001-PRS=1
*/

#include "NOKIA3310.h"

#define CLK 3//PA3
#define DIN 1//PA1
#define DC 3//PC3
#define RST 2//PC2
#define CS 1//PC1

typedef enum{CMD, DAT} DC_t;

//char ecran[LCD_W][LCD_L];

void writebyte(uint8_t in, DC_t dc, boolean hold);

void screenSetup()
{
	_SET(VPORTC.OUT, CS);

	_CLR(VPORTC.OUT, RST);
	_delay_ms(1);
	_SET(VPORTC.OUT, RST);

	writebyte(0b00100001, CMD, TRUE);//PD=0 V=0 H=1
	writebyte(0b00000101, CMD, TRUE);//TC=01
	writebyte(0b00010101, CMD, TRUE);//BS=101
	writebyte(0b10010011, CMD, TRUE);//Vop=0010011
	writebyte(0b00001010, CMD, TRUE);//S=10
	writebyte(0b00100000, CMD, TRUE);//PD=0 V=0 H=0
	writebyte(0b00001100, CMD, TRUE);//D=1 E=0
	writebyte(0b00010001, CMD, FALSE);//PRS=1
	writebyte(0b10000000 | 0, CMD, TRUE);//x=0
	writebyte(0b01000000 | 0, CMD, FALSE);//y=0
	
	clearLCD();
}

void clearLCD()
{
	uint8_t i;

	setCoord(0,0);

	for (i = 0 ; i < (102 * ((LCD_H/8)+1)) ; i++)
		writebyte(0, DAT, TRUE);
	_SET(VPORTC.OUT, CS);
}

void setCoord(uint8_t x, uint8_t y)
{
	writebyte(0b10000000 | _CLIP(0, x, LCD_W), CMD, TRUE);
	writebyte(0b01000000 | _CLIP(0, y, LCD_H>>3), CMD, FALSE);
}

void putPicture(uint8_t picture[], uint8_t posX, uint8_t posY, uint8_t sizeX, uint8_t sizeY)
{
	uint8_t i;

	posX = _CLIP(0, posX, LCD_W);
	posY = _CLIP(0, posY, LCD_H);
	setCoord(posX, posY);
	
	for (i = 0 ; i < (sizeX * sizeY / 8) ; i++)
	{
		if(i%sizeX == 0)
			setCoord(posX, (i/sizeX)+posY);
		writebyte(picture[i], DAT, TRUE);
	}
	_SET(VPORTC.OUT, CS);
}

void putString(char *str, uint8_t posX, uint8_t posY)
{
  posX = _CLIP(0, posX, LCD_W);
  posY = _CLIP(0, posY, LCD_H);
  setCoord(posX, posY);
  
  while(*str)
    putChar(*str++, TRUE);
}
void putChar(char chr, boolean space)
{
  for(uint8_t i = 0; i<5; i++)
    writebyte(asciiTable[(chr-32)*5+i], DAT, TRUE);
    
  if(space)
    writebyte(0, DAT, FALSE);
    
  _SET(VPORTC.OUT, CS);
  _delay_us(1);
}

/*
void LCD_refresh();
{
  uint8_t i,x,y;
  PORTB = PORTB|0b00000100;
  PORTB = PORTB&0b11110111;
  for(y = 0; y<8; y+=1)
    for(x = 0; x<96; x+=1)
      for(i = 7; i>=0; i-=1)
      {
        PORTB = PORTB&0b11111100;
        PORTB = PORTB|(((ecran[x][y]&(1<<i))>>i)<<1);
        PORTB = PORTB|0b00000001;
      }
  PORTB = PORTB|0b00001000;
}
*/

//MSB first
void writebyte(uint8_t in, DC_t dc, boolean hold)
{
	int8_t i;
  
	_CLR(VPORTA.OUT, CLK);
	_CLR(VPORTC.OUT, CS);
	_CHG(VPORTC.OUT, DC, (dc == DAT));

	for(i = 0; i<8; i++)
	{
		_CLR(VPORTA.OUT, CLK);
		_CHG(VPORTA.OUT, DIN, (in >> (7-i)) & 1);
		_SET(VPORTA.OUT, CLK);
	}

	if(hold == FALSE)
		_SET(VPORTC.OUT, CS);
}

