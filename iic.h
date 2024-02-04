#ifndef __IIC_H
#define __IIC_H

#include <stdint.h>

void iicStart();
void iicStop();
void iicAck();
void iicNak();
void iicWrite(uint8_t data);
uint8_t iicRead();
void iicInit();

#endif
