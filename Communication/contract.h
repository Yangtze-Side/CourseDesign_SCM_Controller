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
#define COMM_CMD_EncoderMode        ((u8)21)    // 帧头 + CMD + vx(float) + vy(float) + target_yaw(float)

#define COMM_CMD_MusicStart         ((u8)5)     // 帧头 + CMD + 音乐序号(byte)
#define COMM_CMD_MusicPause         ((u8)6)     // 帧头 + CMD
#define COMM_CMD_MusicStop          ((u8)7)     // 帧头 + CMD
#define COMM_CMD_MusicResume        ((u8)8)     // 帧头 + CMD

#define COMM_CMD_GPIDkpAdd          ((u8)9)     // 帧头 + CMD
#define COMM_CMD_GPIDkpDec          ((u8)10)    // 帧头 + CMD
#define COMM_CMD_GPIDkiAdd          ((u8)11)    // 帧头 + CMD
#define COMM_CMD_GPIDkiDec          ((u8)12)    // 帧头 + CMD
#define COMM_CMD_GPIDkdAdd          ((u8)13)    // 帧头 + CMD
#define COMM_CMD_GPIDkdDec          ((u8)14)    // 帧头 + CMD
#define COMM_CMD_AFPIDkpAdd         ((u8)15)    // 帧头 + CMD
#define COMM_CMD_AFPIDkpDec         ((u8)16)    // 帧头 + CMD
#define COMM_CMD_AFPIDkiAdd         ((u8)17)    // 帧头 + CMD
#define COMM_CMD_AFPIDkiDec         ((u8)18)    // 帧头 + CMD
#define COMM_CMD_AFPIDkdAdd         ((u8)19)    // 帧头 + CMD
#define COMM_CMD_AFPIDkdDec         ((u8)20)    // 帧头 + CMD

// Commands send to controller
// 帧头 + CMD + 温度数据(float，摄氏度) + 湿度数据(float，%) +
// 前置超声波测得的距离 F (float, cm) + B + L + R +
// GPI + AFPID + 帧尾
#define COMM_CMD_CarData            ((u8)51)
#define COMM_CMD_DHT11Data_LEN      ((u8)( (3 + 2) + 4 + 4*4 + 4*6 ))    // COMM_CMD_CarData 命令 一帧的数据总长度

// Helper macros
#define COMM_IsFrameHeadCorrect(p)  ((p)[0] == COMM_HEAD_BYTE0 && (p)[1] == COMM_HEAD_BYTE1)
#define COMM_IsFrameTailCorrect(p)  ((p)[0] == COMM_TAIL_BYTE0 && (p)[1] == COMM_TAIL_BYTE1)

#endif // !__CONTRACT_H
