#ifndef __FOC_H
#define __FOC_H

#include "PosPID.h"
#include "config.h"


#define DIR 1  // 方向控制，1为正向，-1为反向


// 速度开环控制函数
extern u32 velocityOpenloop_time_stamp;
extern float shaft_angle;
extern float zero_electric_angle;
void velocityOpenloop(float target_velocity);


// 角度闭环控制函数
extern PosPID_t angleControl_loop_pid;
extern LowPassFilter_t angleControl_loop_filter;
void angleControl_loop(float target_angle);
void FOC_SetAnglePID_Param(float kp, float ki, float kd, float intMax, float intDis, float DeMax, float uMax);


// 电角度初始化
void Zero_Electric_Init(void);

#endif