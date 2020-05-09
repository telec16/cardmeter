#ifndef AD7731_H_
#define AD7731_H_

#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include "utils.h"


typedef enum{
	IDLE = 0b000, //Sync (Idle) Mode
	CCM = 0b001,  //Continuous Conversion Mode
	SCM = 0b010,  //Single Conversion Mode
	PDM = 0b011,  //Power-Down (Standby) Mode
	IZSC = 0b100, //Internal Zero-Scale Calibration
	IFSC = 0b101, //Internal Full-Scale Calibration
	SZSC = 0b110, //System Zero-Scale Calibration
	SFSC = 0b111  //System Full-Scale Calibration
} AD7731_OPmode_t;

typedef enum{
	//R0020 = 0b000,
	R0020 = 0b001, //mV
	R0040 = 0b010, //mV
	R0080 = 0b011, //mV
	R0160 = 0b100, //mV
	R0320 = 0b101, //mV
	R0640 = 0b110, //mV
	R1280 = 0b111  //mV
} AD7731_inputRange_t;

typedef enum{
	CHN16 = 0b000,
	CHN26 = 0b001,
	CHN36 = 0b010,
	CHN46 = 0b011,
	CHN12 = 0b100,
	CHN34 = 0b101,
	CHN56 = 0b110,
	CHN66 = 0b111
} AD7731_channel_t;



void AD7731_setup(void);
void AD7731_calibration(void);

void AD7731_setMode(AD7731_channel_t chn, AD7731_inputRange_t rng, AD7731_OPmode_t mode);
void AD7731_setFilter(uint16_t filter_set, boolean chop, boolean skip, boolean fast);
uint8_t AD7731_readStatus(void);
uint32_t AD7731_readData(void);

uint32_t AD7731_acquire(AD7731_channel_t chn, AD7731_inputRange_t rng);



#endif /* AD7731_H_ */