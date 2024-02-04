#include "iic.h"

#include "sys.h"
#include "pin.h"

void iicStart() {
    SDA = 1;
    SCL = 1; delay_us(1);
    SDA = 0; delay_us(1);
}

void iicStop() {
    SDA = 0;
    SCL = 1; delay_us(1);
    SDA = 1; delay_us(1);
}

void iicAck() {
    SCL = 0;
    SDA = 1;
    SCL = 1; delay_us(1);
    for (uint8_t i = 0; i < 0xFF; i++) {
        if (SDA == 0)
            break;
        delay_us(1);
    }
    SCL = 0; delay_us(1);
}

void iicNak() {
    SCL = 0;
    SDA = 1;
    SCL = 1; delay_us(1);
    SCL = 0; delay_us(1);
}

void iicWrite(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        SCL = 0; delay_us(1);
        SDA = (data & (1 << (7 - i)));
        delay_us(1);
        SCL = 1; delay_us(1);
    }
    SCL = 0;
    SDA = 1;
    delay_us(1);
}

uint8_t iicRead() {
    uint8_t data = 0;
    SDA = 1;
    SCL = 0; delay_us(1);
    for (uint8_t i = 0; i < 8; i++) {
        SCL = 1; delay_us(1);
        uint8_t tmp = 0;
        if (SDA != 0)
            tmp = 1 << (7 - i);
        data |= tmp;
        delay_us(1);
        SCL = 0; delay_us(1);
    }
    return data;
}

void iicInit() {
    SCL = 1;
    SDA = 1;
    delay(10);
}
