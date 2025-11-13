#ifndef __CONTRACT_H
#define __CONTRACT_H

#include "user_def.h"

// Head of a frame
#define COMM_BYTE0                  0xCC
#define COMM_BYTE1                  0x33

// Commands send to smart car
#define COMM_CMD_JoysMode           ((u8)1)
#define COMM_CMD_GravMode           ((u8)2)
#define COMM_CMD_ACMode             ((u8)3)
#define COMM_CMD_AFMode             ((u8)4)


// Helper macros
#define COMM_IsFrameHeadCorrect(p)  (p[0] == COMM_BYTE0 && p[1] == COMM_BYTE1)

#endif // !__CONTRACT_H
