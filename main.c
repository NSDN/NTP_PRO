#include "ch558.h"

#include <stdio.h>
char buff[16];

#include "sys.h"
#include "pin.h"
#include "usb.h"
#include "dac.h"

void __usb_interrupt() __interrupt (INT_NO_USB) __using (1);
extern __bit USB_OK;

void main() {
    MOT_F = 0; MOT_R = 0;
    sysPinConfig();
    sysClockConfig();
    delay(10);

    adcInit();
    dacInit();
    usbDevInit();
    EA = 1;

    delay(50);
    releaseAllKey();
    pushKeyData();
    requestHIDData();

    uint16_t ad_val;
    int8_t dir = 0, pwr = 0;
    int8_t pd = 127, pp = 127;
    while (1) {
        adcGet(AIN_0);
        ad_val = adcGet(AIN_0) & 0x7FF;
        dir = (int8_t) (ad_val / 700) - 1;

        adcGet(AIN_1);
        ad_val = adcGet(AIN_1) & 0x7FF;
        pwr = (int8_t) (ad_val / 350);

        if (USB_OK) {
            uint16_t code = 0;
            switch (dir) {
                case -1:
                    code |= 0x0001;
                    break;
                case 0:
                    code |= 0x0002;
                    break;
                case 1:
                    code |= 0x0004;
                    break;
                default:
                    code |= 0x0008;
                    break;
            }
            code |= ((1 << pwr) << 4);

            releaseAllKey();
            setKeycode(0, 3);
            setKeycode(1, code & 0xFF);
            setKeycode(2, code >> 8);
            setKeycode(3, 0x00);

            if (pd != dir || pp != pwr) {
                pd = dir; pp = pwr;
                pushKeyData();
            } else {
                sprintf(buff, "D%dP%d", dir, pwr);
                hidPrint(buff);
                delay(100);
            }
        } else {
            switch (dir) {
                case -1:
                    MOT_F = 0; MOT_R = 1;
                    break;
                case 0:
                    MOT_F = 0; MOT_R = 0;
                    break;
                case 1:
                    MOT_F = 1; MOT_R = 0;
                    break;
                default:
                    MOT_F = 1; MOT_R = 1;
                    break;
            }
            voltSet((uint16_t) pwr * 2400); // 12V Max
            delay(20);
        }
    }
}
