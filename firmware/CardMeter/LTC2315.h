#ifndef LTC2315_H_
#define LTC2315_H_

#include "setup.h"
#include <avr/io.h>
#include "utils.h"

#define LTC2315_STEP 0.0005

uint16_t LTC2315_readAll(pin_t cs);

#endif /* LTC2315_H_ */