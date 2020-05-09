#include "AD7731.h"

#define CLK 3 //PA3
#define CLK_P VPORTA.OUT
#define MOSI 2//PA2
#define MOSI_P VPORTA.OUT
#define MISO 1//PA1
#define MISO_P VPORTA.IN
#define CS 5//PA5
#define CS_P VPORTA.OUT
#define RST 7//PA7
#define RST_P VPORTA.OUT
#define STBY 4//PA4
#define STBY_P VPORTA.OUT
#define RDY 6//PA6
#define RDY_P VPORTA.IN
#define SYNC 5//PB5
#define SYNC_P VPORTB.OUT


/*** Communication Register ***/
typedef enum{
	SINGLE_WRITE = 0b00,
	SINGLE_READ = 0b01,
	CONT_READ = 0b10,
	STOP_READ = 0b11
} RWmode_t;
#define RW_MODE_BIT 4
typedef enum{
	COMM_ADDR = 0b000,
	STATUS_ADDR = 0b000,
	DATA_ADDR = 0b001,
	MODE_ADDR = 0b010,
	FILTER_ADDR = 0b011,
	OFFSET_ADDR = 0b101,
	GAIN_ADDR = 0b110,
} addr_t;
#define COMM_SIZE 1
#define STATUS_SIZE 1
#define DATA_SIZE 3
#define MODE_SIZE 2
#define FILTER_SIZE 2
#define OFFSET_SIZE 3
#define GAIN_SIZE 3
#define ADDR_BIT 0


/*** Mode Register ***/
#define OP_MODE_BIT 13
#define _BU_BIT 12 //_Bipolar/Unipolar Bit
#define DEN_BIT 11 //Digital Output Enable Bit
#define D1_BIT 10
#define D0_BIT 9
#define WL_BIT 8 //Data Word Length Bit (0:16bits, 1:24bits)
#define HIREF_BIT 7 //High Reference Bit (0:2.5V, 1:5V)
#define IN_RANGE_BIT 4
#define BO_BIT 3 //Burnout Current Bit
#define CHN_BIT 0

//Unipolar; No digital; 24bits length; 2V5 ref; No burnout current
#define BASE_MODE (1<<_BU_BIT) | (0<<DEN_BIT) | (1<<WL_BIT) | (0<<HIREF_BIT) | (0<<BO_BIT)


/*** Filter Register ***/
#define FILTER_SEL_BIT 4 //Sinc3 Filter Selection Bit
#define CHOP_BIT 2 //Chop Enable Bit
#define SKIP_BIT 1 //FIR Filter Skip Bit
#define FAST_BIT 0 //FASTStep™ Mode Enable Bit



/*** Prototypes ***/

void writeByte(const uint8_t data);
uint8_t readByte(void);

void startComm(const RWmode_t mode, const addr_t addr);
void stopComm(void);

void writeRegister(const addr_t addr, const uint32_t data, const uint8_t datalen);
uint32_t readRegister(const addr_t addr, const uint8_t datalen);



/*** Definitions ***/

void AD7731_setup(void)
{
	//Setup datalines
	_SET(CS_P, CS);
	_SET(CLK_P, CLK);
	
	//Performs full reset
	_CLR(RST_P, RST);
	_CLR(SYNC_P, SYNC);
	_CLR(STBY_P, STBY);
	_delay_us(1);
	
	//Startup
	_SET(RST_P, RST);
	_SET(SYNC_P, SYNC);
	_SET(STBY_P, STBY);
	_delay_us(1);
	
	AD7731_setFilter(2048, FALSE, TRUE, FALSE); //DMM mode
	
	AD7731_calibration();
}

void AD7731_calibration(void)
{
	AD7731_setMode(CHN16, R1280, IFSC);
	_delay_ms(100);
	AD7731_setMode(CHN26, R1280, IFSC);
	_delay_ms(100);
	AD7731_setMode(CHN34, R1280, IFSC);
	_delay_ms(100);
	AD7731_setMode(CHN56, R1280, IFSC);
	_delay_ms(100);
	AD7731_setMode(CHN16, R1280, IZSC);
	_delay_ms(100);
	AD7731_setMode(CHN26, R1280, IZSC);
	_delay_ms(100);
	AD7731_setMode(CHN34, R1280, IZSC);
	_delay_ms(100);
	AD7731_setMode(CHN56, R1280, IZSC);
	_delay_ms(100);
}

uint32_t AD7731_acquire(AD7731_channel_t chn, AD7731_inputRange_t rng)
{
	AD7731_setMode(chn, rng, CCM);
	_delay_ms(100);
	return AD7731_readData();
}

void AD7731_setFilter(uint16_t filter_set, boolean chop, boolean skip, boolean fast)
{
	writeRegister(	FILTER_ADDR,
	(filter_set<<FILTER_SEL_BIT) | (chop<<CHOP_BIT) | (skip<<SKIP_BIT) | (fast<<FAST_BIT),
	FILTER_SIZE);
}

void AD7731_setMode(AD7731_channel_t chn, AD7731_inputRange_t rng, AD7731_OPmode_t mode)
{
	writeRegister(	MODE_ADDR,
					BASE_MODE | (chn<<CHN_BIT) | (rng<<IN_RANGE_BIT) | (mode<<OP_MODE_BIT),
					MODE_SIZE);
}

uint8_t AD7731_readStatus(void)
{
	return readRegister(STATUS_ADDR, STATUS_SIZE);
}

uint32_t AD7731_readData(void)
{
	return readRegister(DATA_ADDR, DATA_SIZE);
}

//MSB first
void writeRegister(const addr_t addr, const uint32_t data, const uint8_t datalen)
{
	uint8_t i;
	
	startComm(SINGLE_WRITE, addr);
	for(i=0; i<datalen; i++)
	writeByte((uint8_t) ((data>>( (datalen-1 - i)*8 )) & 0xFF) );
	stopComm();
}

//MSB first
uint32_t readRegister(const addr_t addr, const uint8_t datalen)
{
	uint8_t i;
	uint32_t data=0;
	
	startComm(SINGLE_READ, addr);
	for(i=0; i<datalen; i++)
	{
		data <<= 8;
		data |= readByte();
	}
	stopComm();
	
	return data;
}

void startComm(const RWmode_t mode, const addr_t addr)
{
	_SET(CLK_P, CLK);
	_CLR(CS_P, CS);
	writeByte((mode<<RW_MODE_BIT) | (addr << ADDR_BIT));
}
void stopComm(void)
{
	_SET(CLK_P, CLK);
	_SET(CS_P, CS);
}

//MSB first
void writeByte(const uint8_t data)
{
	uint8_t i;
	
	for(i = 0; i<8; i++)
	{
		_CLR(CLK_P, CLK);
		_CHG(MOSI_P, MOSI, (data >> (7-i)) & 1);
		_delay_us(1);
		_SET(CLK_P, CLK);
		_delay_us(1);
	}
}

//MSB first
uint8_t readByte(void)
{
	uint8_t i, data=0;
	
	for(i = 0; i<8; i++)
	{
		_CLR(CLK_P, CLK);
		_delay_us(1);
		data <<= 1;
		data |= _GET(MISO_P, MISO);
		_SET(CLK_P, CLK);
		_delay_us(1);
	}
	
	return data;
}
