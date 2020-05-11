#ifndef MAIN_H_
#define MAIN_H_

#include "setup.h"
#include <stdlib.h>
#include <avr/io.h>
#include "utils.h"
#include "NOKIA3310.h"
#include "AD8231.h"
#include "LTC2315.h"
#include "ui.h"
#include "user_input.h"

typedef enum {
	UI_ROOT,
	UI_GAIN,
	UI_TIMEBASE
} menu_t;

typedef enum {
	ACT_NONE,
	ACT_OFFSET
} action_t;

typedef struct {
	menu_t menu;
	action_t action;
	AD8231_gain_t gain;
	uint8_t timebase;
	uint16_t offset;
} config_t;

typedef struct {
	uint16_t raw0;
	float ch0;
} data_t;

extern volatile config_t config;
extern volatile data_t data;
extern const float range_table[8];

#endif /* MAIN_H_ */