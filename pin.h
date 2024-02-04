#ifndef __PIN_H
#define __PIN_H

#include "ch558.h"

// IIC
#define SCL     P27
#define SDA     P26

// Driver Ctrl
#define MOT_F   P02
#define MOT_R   P03

// KEYs
#define KEY_1   (P4_IN & 0x80)
#define KEY_2   P34
#define KEY_3   P32
#define KEY_4   (P5_IN & 0x80)

// AINs
#define AIN_0   7
#define AIN_1   6
#define AIN_2   5
#define AIN_3   4

// PORTs
#define PRT_1   P25
#define PRT_2   P12

#endif
