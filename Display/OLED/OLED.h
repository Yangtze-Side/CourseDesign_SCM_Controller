/**
 * @file oled.h
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief STM32 OLED 应用例程。使用 IIC DMA 驱动。
 *        配置详见 Display.c/.h。
 * 
 * @version 0.1
 * @date 2025-07-15
 * 
 */
#ifndef __OLED_H
#define __OLED_H

#include "config.h"
#include "user_soft_iic.h"
#include "system.h"
#include "Font_EN.h"
#include "Font_CN.h"

/*---------------------------------------------- User Determine -------------------------------------------*/

#define OLED_ADDR                               ((u8)0x78)

// OLED I2C sending operation.
#define OLED_I2C_Write(cmd, pdat, size)         User_IIC_MemWrite(OLED_ADDR, cmd, pdat, size)

// Delay Operation
#define OLED_msDelay(_ms)                       Sys_Delay(_ms)


/*-------------------------------------------------- Library -----------------------------------------------*/

#define OLED_WIDTH      (128)
#define OLED_HEIGHT     (64)

#define ROW_STEP        (OLED_WIDTH * 2)
#define COL_STEP        (8)

typedef enum {
    FILL_BY_0 = (char)'0',
    FILL_BY_SPACE = (char)' ',
} fill_t;

void OLED_Init(void);

void OLED_Clear(void);
void OLED_ShowChar(u8 row, u8 col, char ch);
void OLED_ShowString(u8 row, u8 col, const char* str);

void OLED_ShowIcon16(u8 row, u8 col, const u8 icon16[32]);
void OLED_ShowIcon32(u8 row, u8 col, const u8 icon32[128]);
void OLED_ShowNum(u8 row, u8 col, s32 num, u8 len, fill_t fill);

#if Enable_Cn16Char
void OLED_ShowCnString16(u8 row, u8 col, char* CnString);
#endif
#if Enable_Cn32Char
void OLED_ShowCnString32(u8 row, u8 col, char* CnString);
#endif

#endif // !__OLED_H
