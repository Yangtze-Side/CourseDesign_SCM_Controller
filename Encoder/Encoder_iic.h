#ifndef __USER_SOFT_IIC_H
#define __USER_SOFT_IIC_H

#include "config.h"

#define ENC_SCL_Pin             ENC_SCL
#define ENC_SDA_Pin             ENC_SDA

void ENC_IIC_MemWrite(u8 DevAddr, u8 MemAddr, const u8 *pData, u16 Len);
BOOL ENC_IIC_ReadBytes(u8 device_addr, u8 reg_addr, u8 *buffer, u8 len);

#endif // !__USER_SOFT_IIC_H
