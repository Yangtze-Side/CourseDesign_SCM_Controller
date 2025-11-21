#ifndef __USER_FIFO_H
#define __USER_FIFO_H

#include "config.h"

#define User_FIFO_BYTENOTFOUND          (0xffff)

typedef enum __FIFO_Lock_t {
    USER_FIFO_UNLOCK,
    USER_FIFO_LOCK
} User_FIFO_Lock_TypeDef;

typedef struct __FIFO_t {
    u8 *Buff;
    u16 MaxSize;
    u16 Head;
    u16 Tail;
    User_FIFO_Lock_TypeDef Lock;
} User_FIFO_TypeDef;

typedef enum __FIFO_ReadOperation_t {
    USER_FIFO_READ_ONLY,
    USER_FIFO_READ_AND_CLEAN
} User_FIFO_ReadOperation_TypeDef;

void User_FIFO_Init(User_FIFO_TypeDef *fifo, u8 *buf, u16 maxSize);
void User_FIFO_WriteByte(User_FIFO_TypeDef *fifo, u8 byt);
void User_FIFO_Read(User_FIFO_TypeDef *fifo, u8 *pData, u16 len, User_FIFO_ReadOperation_TypeDef opt);
u16  User_FIFO_GetUsedLength(const User_FIFO_TypeDef *fifo);
void User_FIFO_Clear(User_FIFO_TypeDef *fifo, u16 range);
u16  User_FIFO_FindByte(User_FIFO_TypeDef *fifo, u8 byte);
BOOL User_FIFO_GetByte(User_FIFO_TypeDef *fifo, u16 index, u8 *byte);

#endif // !__USER_FIFO_H
