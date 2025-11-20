#ifndef __USER_SOFT_IIC_H
#define __USER_SOFT_IIC_H

#include "config.h"

#define SCL_Pin             OLED_SCL
#define SDA_Pin             OLED_SDA

void Soft_IIC_MemWrite(u8 DevAddr, u8 MemAddr, const u8 *pData, u16 Len);

#endif // !__USER_SOFT_IIC_H
