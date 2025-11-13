#ifndef __USER_SOFT_IIC_H
#define __USER_SOFT_IIC_H

#include "config.h"

#define SCL_Pin             P00
#define SDA_Pin             P00

void IIC_MemWrite(u8 DevAddr, u8 MemAddr, u8 *pData, u16 Len);

#endif // !__USER_SOFT_IIC_H
