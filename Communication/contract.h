#ifndef __CONTRACT_H
#define __CONTRACT_H

#include "user_def.h"

// Head of a frame
#define COMM_BYTE0                  0xCC
#define COMM_BYTE1                  0x33

// Commands send to smart car
#define COMM_CMD_JoysMode           ((u8)1)     // 帧头 + CMD + vx(float) + vy(float) + vw(float)
#define COMM_CMD_GravMode           ((u8)2)     // 帧头 + CMD + vx(float) + vy(float) + target_yaw(float)
#define COMM_CMD_ACMode             ((u8)3)     // 帧头 + CMD
#define COMM_CMD_AFMode             ((u8)4)     // 帧头 + CMD

// Commands send to controller
#define COMM_CMD_DHT11Data          ((u8)51)    // 帧头 + CMD + 温度数据(float，摄氏度) + 湿度数据(float，%) + 前置超声波测得的距离 F (float, cm) + B + L + R

// Helper macros
#define COMM_IsFrameHeadCorrect(p)  (p[0] == COMM_BYTE0 && p[1] == COMM_BYTE1)

#endif // !__CONTRACT_H
