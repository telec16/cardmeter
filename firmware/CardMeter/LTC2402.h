#ifndef LTC2402_H_
#define LTC2402_H_

#include "setup.h"
#include <avr/io.h>
#include "utils.h"

#define ADC_EOC 31
#define ADC_CHN 30
#define ADC_SIG 29
#define ADC_EXR 28
#define ADC_VALUE 4

#define ADC_STEP 0.000000178813934326171875

typedef enum{CH0, CH1} LTC2402_channel_t;
typedef struct {
	boolean EOC;
	boolean SIG; /*Sign bit. 1>+*/
	boolean EXR; /*Out of range*/
	uint8_t subLSBs;
} LTC2402_status_t;

void LTC2402_getData(uint32_t *ch0, uint32_t *ch1);
boolean LTC2402_parse(uint32_t data, LTC2402_channel_t *chn, LTC2402_status_t *status, uint32_t *value);
boolean LTC2402_ready();
uint32_t LTC2402_readAll();

#endif /* LTC2402_H_ */