#ifndef LTC2315_H_
#define LTC2315_H_

#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include "utils.h"

#define LTC2315_REF 2.048
#define LTC2315_FULL 2048
#define LTC2315_STEP (LTC2315_REF / LTC2315_FULL)

uint16_t LTC2315_readAll(pin_t cs);

#endif /* LTC2315_H_ */