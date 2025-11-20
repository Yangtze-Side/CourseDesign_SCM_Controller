#ifndef __KEY_UD_H
#define __KEY_UD_H

#include "config.h"

#define Key_UD1_PinIn           P00
#define Key_UD2_PinIn           P03

// 每 20 ms 刷新，表示当前按键是否被按下，可以用下面的宏函数来判断。
// 用途：在 control.c 中需要将按键信息转化为 vw 信息。
extern BOOL Key_UD_Left, Key_UD_Right;

#define KeyUD_Is_Pressed(key)     ((key) == Bit_RESET)
#define KeyUD_Is_Released(key)    ((key) == Bit_SET)


void Key_UD_Task(void);

#endif // !__KEY_UD_H
