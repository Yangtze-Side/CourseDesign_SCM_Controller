#ifndef __CONTROL_H
#define __CONTROL_H

#include "config.h"

// 在 control 里定义和控制相关的变量（如当前小车的模式）和函数（如根据按键状态、 ADC 结果、
// 欧拉角等计算出小车的 vx、vy 等控制信息。建议没中控制方式都用一个不同的结构体变量来存放。
// 定义的这个控制函数在每一次发送控制信息之前调用一下即可，也就是把它放在 communication.c
// 中的 Comm_SendTask 的开始。

// 介绍一下两种控制模式。
// 1. 摇杆模式：摇杆决定 vx, vy，两个识别按下/抬起的按键决定 vw，例如按下左边按键 vw 30，
//             按下右边按键 vw = -30；
// 2. 重力遥控：俯仰角和横滚决定 vy 和 vx，偏航角决定 target_yaw。

#endif // !__CONTROL_H
