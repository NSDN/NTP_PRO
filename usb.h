#ifndef __USB_H
#define __USB_H

#include <stdint.h>

#define HID_BUF_SIZE 42

void usbDevInit();

void setKeycode(uint8_t i, uint8_t key);
void releaseAllKey();
void pushKeyData();
uint8_t* fetchKeyData();

#define LED_NUMS    0x01
#define LED_CAPS    0x02
#define LED_SCOL    0x04
uint8_t fetchLED();

uint8_t getHIDData(uint8_t index);
void setHIDData(uint8_t index, uint8_t data);
__bit hasHIDData();
void requestHIDData();
void pushHIDData();
uint8_t* fetchHIDData();

void hidPrint(const char* str);

#endif
