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

typedef enum{CH0, CH1} ADC_CHN_t;
typedef struct{
	boolean SIG;
	boolean EXR;
	uint8_t subLSBs;
}ADC_STATUS_t;

void getData(uint32_t *ch0, uint32_t *ch1);
boolean parse(uint32_t data, ADC_CHN_t *chn, ADC_STATUS_t *status, uint32_t *value);
boolean ready();
uint32_t readAll();

#endif /* LTC2402_H_ */