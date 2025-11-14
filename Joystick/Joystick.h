#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "config.h"

// 你需要设计一个任务，利用你编写的 ADC 驱动，及时地更新两路 ADC 采集得来的电压数据，
// 并把结果存放在一个结构体中。这个结果暂时不需要转换成速度数据，因为你可以在 control.c
// 中转换它，这里只是编写底层转换过程。你可以每 50 ms 执行一次这个任务。

#endif // !__JOYSTICK_H
