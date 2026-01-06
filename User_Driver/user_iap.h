/**
 * @file user_iap.h
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief IAP 用户驱动代码。
 * @note  IAP15W 系列没有专门的模拟 EEPROM 区域，模拟 EEPROM 使用片内 Flash 存储器的一部分。
 *        因此，要注意 EEPROM 的使用起始地址需要大于用户有效程序的结束地址，
 *        使用时不要与用户程序区重叠，以免擦写用户的有效程序。
 * 
 * @version 0.1
 * @date 2025-12-29
 * 
 */
#ifndef __USER_IAP_H
#define __USER_IAP_H

#include "config.h"

void IAP_Init(void);
void IAP_EraseSector(u32 dwAddress);
void IAP_ProgramBytes(u32 dwAddress, void* pData, u32 size);
void IAP_ReadBytes(u32 dwAddress, void* pData, u32 size);

#endif // !__USER_IAP_H
