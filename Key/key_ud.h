#ifndef __KEY_UD_H
#define __KEY_UD_H

#include "config.h"

#define Key_UD1_PinIn           P00
#define Key_UD2_PinIn           P00

extern bit Key_UD_Left, Key_UD_Right;

#define KeyUD_Is_Pressed(key)     ((key) == Bit_RESET)
#define KeyUD_Is_Released(key)    ((key) == Bit_SET)


void Key_UD_Task(void);

#endif // !__KEY_UD_H
