#ifndef __CONTROL_H
#define __CONTROL_H

#include "config.h"

// 在 control 里定义和控制相关的变量（如当前小车的模式）和函数（如根据按键状态、 ADC 结果、
// 欧拉角等计算出小车的 vx、vy 等控制信息。建议每种控制方式都用一个不同的结构体变量来存放。
// 定义的这个控制函数在每一次发送控制信息之前调用一下即可，也就是把它放在 communication.c
// 中的 Comm_SendTask 的开始。

// 介绍一下两种控制模式。
// 1. 摇杆模式：摇杆决定 vx, vy，两个识别按下/抬起的按键决定 vw，例如按下左边按键 vw 30，
//             按下右边按键 vw = -30；
// 2. 重力遥控：俯仰角和横滚决定 vy 和 vx，偏航角决定 target_yaw。


//对重力的敏感度
#define GRAVITY_SENSITY         2.0f
#define SPEED_LIMIT           100.0f
//使用的角度范围
#define ROLL_ANGLE_USE         45.0f
#define PITCH_ANGLE_USE        45.0f
#define YAW_ANGLE_USE          30.0f
// 默认旋转速度
#define DEFAULT_VW             30.0f

#define MapAngleTo100(angle, angle_limit)   ((angle) / (angle_limit) * 100.0f)


//控制模式
typedef enum {
    Ctrl_Mode_JoyStick = 0,   // 摇杆模式
    Ctrl_Mode_Gravity,         // 重力遥控模式
    Ctrl_Mode_AutoCruise,       // 自动巡航模式
    Ctrl_Mode_AutoFollow       // 自动跟随模式
} ControlMode_t;

//摇杆数据
typedef struct {
    float vx;           // 摇杆 x → 速度 x
    float vy;           // 摇杆 y → 速度 y
    float vw;           // 旋转速度（由按键控制）
} ControlJoystick_t;

//重力遥控数据
typedef struct {
    float vx;           // 横滚角 → 速度 vx
    float vy;           // 俯仰角 → 速度 vy
    float target_yaw;   // 偏航角 → 目标偏航角 target_yaw
} ControlGravity_t;

typedef struct {
    ControlMode_t mode;                 // 当前控制模式
    float vw_set;                       // 摇杆模式下的旋转速度大小
    ControlJoystick_t joystick;         // 摇杆模式数据
    ControlGravity_t  gravity;          // 重力遥控数据
} ControlCar_t;


extern ControlCar_t ctrl_car;


void Control_Update(void);
void Control_Set_Mode(ControlMode_t mode);
void Control_SetVw(float vw);

#endif // !__CONTROL_H
