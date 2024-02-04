#include "dac.h"

#include "iic.h"

#define DAC5571_ADDR            0x98
#define DAC5571_MODE_NORMAL     0x0
#define DAC5571_MODE_PWD_1K     0x1
#define DAC5571_MODE_PWD_100K   0x2
#define DAC5571_MODE_PWD_HI     0x3

void DAC5571_Set(uint8_t cfg, uint8_t val) {
    iicStart();
    iicWrite(DAC5571_ADDR);
    iicAck();
    iicWrite(((cfg & 0x3) << 4) | (val >> 4));
    iicAck();
    iicWrite(val << 4);
    iicNak();
    iicStop();
}

void dacInit() {
    iicInit();
    DAC5571_Set(DAC5571_MODE_NORMAL, 0x00);
}

void dacSet(uint8_t value) {
    DAC5571_Set(DAC5571_MODE_NORMAL, value);
}

void voltSet(uint16_t mV) {
    if (mV < 1050)
        mV = 1050;
    uint32_t v32 = mV;
    v32 = (v32 - 1050) * 21795;
    v32 = v32 / 1000000;
    if (v32 > 255)
        v32 = 255;
    dacSet((uint8_t) v32);
}
