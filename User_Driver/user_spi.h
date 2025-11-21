#ifndef __USER_SPI_H
#define __USER_SPI_H

#include "config.h"

// User_SPI_Status
#define User_SPI_OK                 FALSE       // No timeout
#define User_SPI_TIMEOUT            TRUE        // Is timeout

u8 User_SPI_Write_1(u8 Byte, u32 Timeout);
u8 User_SPI_Write_2(u8 Byte, u32 Timeout);
u8 User_SPI_Read_1(u8 *Buf, u16 Len, u32 Timeout);
u8 User_SPI_Read_2(u8 *Buf, u16 Len, u32 Timeout);

#endif // !__USER_SPI_H
