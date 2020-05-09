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

//H=0
#define FUN_SET 0b00100000
#define DIS_CON 0b00001000
#define SET_Y	0b01000000
#define SET_X	0b10000000
//H=1
#define TMP_CON 0b00000100
#define BIAS	0b00010000
#define VOP		0b10000000

#define H	(1<<0)
#define V	(1<<1) //Addressing
#define PD	(1<<2) //_Active
#define E	(1<<0) //Invert
#define D	(1<<2) //_Blanking

typedef enum{CMD, DAT} DC_t;

//char ecran[LCD_W][LCD_L];

void writebyte(uint8_t in, DC_t dc, boolean hold);

void screenSetup()
{
	_SET_PIN(CS_SCR);

	_delay_ms(1);
	_CLR_PIN(RST);
	_delay_ms(1);
	_SET_PIN(RST);

	writebyte(FUN_SET	| H		, CMD, TRUE);//PD=0 V=0 H=1
	writebyte(VOP		| T_VOP	, CMD, TRUE);//Vop=0010011
	writebyte(TMP_CON	| 0b10	, CMD, TRUE);//TC=01
	writebyte(BIAS		| T_BIAS, CMD, TRUE);//BS=101
	writebyte(FUN_SET	| 0		, CMD, TRUE);//PD=0 V=0 H=0
	writebyte(DIS_CON	| D		, CMD, FALSE);//D=1 E=0
	
	writebyte(SET_X		| 0, CMD, TRUE);//x=0
	writebyte(SET_Y		| 0, CMD, FALSE);//y=0
	
	clearLCD();
}


void changeVop(uint8_t vop)
{
	vop = _CLIP(0, vop, 0x40);
	writebyte(FUN_SET | H, CMD, TRUE);
	writebyte(VOP  |  vop, CMD, TRUE);
	writebyte(FUN_SET | 0, CMD, FALSE);
}

void changeBias(uint8_t bias)
{
	bias = _CLIP(0, bias, 7);
	writebyte(FUN_SET | H, CMD, TRUE);
	writebyte(BIAS | bias, CMD, TRUE);
	writebyte(FUN_SET | 0, CMD, FALSE);
}

void testLCD()
{
	uint8_t i;
	
	for(i = 0; i<2; i++)
	{
		writebyte(DIS_CON | E, CMD, FALSE);
		_delay_ms(250);
		writebyte(DIS_CON | 0, CMD, FALSE);
		_delay_ms(250);
	}
	writebyte(DIS_CON | D, CMD, FALSE);
	writebyte(SET_X	| 10, CMD, TRUE);
	writebyte(SET_Y	| 1, CMD, FALSE);
	
	for(i = 0; i<5; i++)
	{
		writebyte(0xAA, DAT, TRUE);
		writebyte(0x55, DAT, FALSE);
	}
	
	for(i = 0; i<2; i++)
	{
		writebyte(DIS_CON | E | D, CMD, FALSE);
		_delay_ms(250);
		writebyte(DIS_CON | D, CMD, FALSE);
		_delay_ms(250);
	}
}

void clearLCD()
{
	uint16_t i;

	setCoord(0,0);

	for (i = 0 ; i < (102 * ((LCD_H/8)+1)) ; i++)
		writebyte(0, DAT, TRUE);
	_SET_PIN(CS_SCR);
}

void setCoord(uint8_t x, uint8_t y)
{
	writebyte(SET_X | _CLIP(0, x, LCD_W), CMD, TRUE);
	writebyte(SET_Y | _CLIP(0, y, LCD_H/8), CMD, FALSE);
}

void putPicture(uint8_t picture[], uint8_t posX, uint8_t posY, uint8_t sizeX, uint8_t sizeY)
{
	uint16_t i;

	posX = _CLIP(0, posX, LCD_W);
	posY = _CLIP(0, posY, LCD_H);
	setCoord(posX, posY);
	
	for (i = 0 ; i < (sizeX * sizeY / 8) ; i++)
	{
		if(i%sizeX == 0)
			setCoord(posX, (i/sizeX)+posY);
		writebyte(picture[i], DAT, TRUE);
	}
	_SET_PIN(CS_SCR);
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
	uint8_t i;
	for(i = 0; i<5; i++)
		writebyte(asciiTable[(chr-32)*5+i], DAT, TRUE);
	
	if(space)
		writebyte(0, DAT, FALSE);
	
	_SET_PIN(CS_SCR);
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
	uint8_t i;
  
	_CLR_PIN(SCK);
	_CLR_PIN(CS_SCR);
	_CHG_PIN(DC, (dc == DAT));

	for(i = 0; i<8; i++)
	{
		_CLR_PIN(SCK);
		_delay_us(1);
		_CHG_PIN(SDI, (in >> (7-i)) & 1);
		_delay_us(1);
		_SET_PIN(SCK);
		_delay_us(1);
	}

	if(hold == FALSE)
		_SET_PIN(CS_SCR);
}

