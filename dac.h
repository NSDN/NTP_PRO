#ifndef __DAC_H
#define __DAC_H

#include <stdint.h>

void dacInit();
void dacSet(uint8_t value);
void voltSet(uint16_t mV);

#endif
