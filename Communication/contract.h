#ifndef __CONTRACT_H
#define __CONTRACT_H

#include "user_def.h"

// Head of a frame
#define COMM_HEAD_BYTE0             0xCC
#define COMM_HEAD_BYTE1             0x33
// Tail of a frame
#define COMM_TAIL_BYTE0             0x99
#define COMM_TAIL_BYTE1             0x66

// Commands send to smart car
#define COMM_CMD_JoysMode           ((u8)1)     // 帧头 + CMD + vx(float) + vy(float) + vw(float)
#define COMM_CMD_GravMode           ((u8)2)     // 帧头 + CMD + vx(float) + vy(float) + target_yaw(float)
#define COMM_CMD_ACMode             ((u8)3)     // 帧头 + CMD
#define COMM_CMD_AFMode             ((u8)4)     // 帧头 + CMD
#define COMM_CMD_MusicStart         ((u8)5)     // 帧头 + CMD + 音乐序号(byte)
#define COMM_CMD_MusicPause         ((u8)6)     // 帧头 + CMD
#define COMM_CMD_MusicStop          ((u8)7)     // 帧头 + CMD
#define COMM_CMD_MusicResume        ((u8)8)     // 帧头 + CMD

// Commands send to controller
// 帧头 + CMD + 温度数据(float，摄氏度) + 湿度数据(float，%) +
// 前置超声波测得的距离 F (float, cm) + B + L + R +
// GPI + AFPID + 帧尾
#define COMM_CMD_CarData            ((u8)51)
#define COMM_CMD_DHT11Data_LEN      ((u8)( (3 + 2) + 4 + 4*4 + 4*5 ))    // COMM_CMD_CarData 命令 一帧的数据总长度

// Helper macros
#define COMM_IsFrameHeadCorrect(p)  ((p)[0] == COMM_HEAD_BYTE0 && (p)[1] == COMM_HEAD_BYTE1)
#define COMM_IsFrameTailCorrect(p)  ((p)[0] == COMM_TAIL_BYTE0 && (p)[1] == COMM_TAIL_BYTE1)

#endif // !__CONTRACT_H
