/**
 * @file oled.c
 * @author Zach (zachary-yue@qq.com)
 * 
 * @brief STM32 OLED 应用例程。使用 IIC DMA 驱动。
 *        配置详见 Display.c/.h。
 * 
 * @version 0.1
 * @date 2025-07-15
 * 
 */
#include "OLED.h"


/*---------------------------------------- Constants And Declarations -------------------------------------*/

#define OLED_CONTROLBYTE_CMD_STREAM     (0x00) // 多字节命令 0000 0000b
#define OLED_CONTROLBYTE_CMD_SINGLE     (0x80) // 单字节命令 1000 0000b
#define OLED_CONTROLBYTE_DATA           (0x40) // 传输数据   0100 0000b

#define OLED_DISPLAY_ON                 (0xAF)
#define OLED_DISPLAY_OFF                (0xAE)

#define OLED_DISPGRAPH_SIZE             ((u16)(8*128))

static u8 OLED_DispGraph[OLED_DISPGRAPH_SIZE];

BOOL OLED_IsInit = FALSE;

void OLED_Clear(void);


/*-------------------------------------------------- Library -----------------------------------------------*/

/**
 * @brief 初始化 OLED 显示屏。
 * 
 */
void OLED_Init(void)
{
    u8 init[] =
    {
        OLED_DISPLAY_OFF, // 关闭显示

        0xC8, // 设置COM扫描方向
        0x40, // 设置显示开始行
        0x81, // 设置对比度
        0xFF, // 对比度值
        0xA1, // 设置段重映射
        0xA6, // 设置正显
        0xA8, // 设置多路复用比
        0x3F, // 多路复用比值
        0xA4, // 全局显示开启

        0xD5, // 设置显示时钟分频
        0x80, // 分频值
        0xD9, // 设置预充电周期
        0x22, // 预充电周期值
        0xDA, // 设置COM硬件配置
        0x12, // COM硬件配置值
        0xDB, // 设置VCOMH
        0x30, // VCOMH值
        0x8D, // 设置电荷泵
        0x14, // 电荷泵值

        0xD3, // 设置显示偏移
        // 0x38, // 偏移值
        0x00, // 偏移值

        0xB0, // 给指针指回去（这里写几都不管用，画面都向上偏移了一页，即 8 px）
        0x00, // 给指针指回去
        0x10, // 给指针指回去（不知道为什么需要将偏移值设置为 56，也就是画面整体向下移一页才是正确的）

        // 0x20, // 设置内存地址模式
        // 0x00, // 设置水平寻址模式

        OLED_DISPLAY_ON,    // 显示开启
    };

    OLED_Clear();
    OLED_I2C_Write(OLED_CONTROLBYTE_CMD_STREAM, init, sizeof(init));
}


/**
 * @brief Set cursor.
 * 
 * @param y Vertical cursor, (0 ~ 7)
 * @param x Horizonal cursor, (0 ~ 127)
 */
static void OLED_SetCursor(u8 y, u8 x)
{
    u8 pdat[3];
    if (y > 7 || x > 127) return;
    pdat[0] = 0xB0 | y;
    pdat[1] = 0x10 | (x >> 4);
    pdat[2] = 0x00 | (x & 0x0f);
    OLED_I2C_Write(OLED_CONTROLBYTE_CMD_STREAM, pdat, 3);
}


/**
 * @brief 清屏
 * 
 */
void OLED_Clear(void)
{
	// memset(OLED_DispGraph, 0x00, OLED_DISPGRAPH_SIZE);
    u8 i = 0;
    u8 dat[128] = { 0 };
    // memset(dat, 0x00, 128);
    for (; i <= 7; i++)
    {
        OLED_SetCursor(0, i);
        OLED_I2C_Write(OLED_CONTROLBYTE_DATA, dat, 128);
    }
}

/**
 * @brief 显示字符
 * 
 * @param row 字符所在行(1 ~ 4)
 * @param col 字符所在列(1 ~ 16)
 * @param ch 待显示的字符('\32' ~ '\127')
 */
void OLED_ShowChar(u8 row, u8 col, char ch)
{
    if (--row > 3 || --col > 15 || ch < 32 || ch > 127) return;
    ch -= 32;

    OLED_SetCursor(2 * row, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, ascii_1608[(u8)ch] + 0, 8);
    OLED_SetCursor(2 * row + 1, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, ascii_1608[(u8)ch] + 8, 8);
}

/**
 * @brief 显示英文字符串
 * 
 * @param row 字符串所在行
 * @param col 字符串所在列
 * @param str 待显示的字符串
 */
void OLED_ShowString(u8 row, u8 col, const char* str)
{
    char *str1 = (char*)str;
	if (--row > 3 || --col > 15 || !str1) return;
	++row, ++col;
	
    do {
        OLED_ShowChar(row, col, *str1++);
        if (++col > 16)
        {
            col = 1;
            if (++row > 4) break;
        }
    } while (*str1);
}

/**
 * @brief Show 16*16 Icon.
 * 
 * @param row       certain row (1 ~ 4)
 * @param col       certain column (1 ~ 15)
 * @param icon16    display data of the icon
 */
void OLED_ShowIcon16(u8 row, u8 col, const u8 icon16[32])
{
	if (--row > 3 || --col > 14 || !icon16) return;
    OLED_SetCursor(2 * row, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, icon16 + 0, 16);
    OLED_SetCursor(2 * row + 1, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, icon16 + 16, 16);
}

#if Enable_Cn16Char
/**
 * @brief 显示 16*16 中文字符串，超过屏幕宽度自动换行，超过屏幕长度不显示超过的部分。
 * 
 * @param row 字符串第一个字所在行
 * @param col 字符串第一个字所在列
 * @param CnString 待显示的中文字符（如果显示出错就在 UTF-8 编码下重新输入中文字符串）
 */
void OLED_ShowCnString16(u8 row, u8 col, char* CnString)
{   
    u8 i;
    if (!CnString) return;

    while(*CnString != '\0')
    {
        for(i = 0; i < Cn16Char_SUMMARY; i++)
        {
			if(*CnString == Cn16Char[i].Index[0] && \
                *(CnString + 1) == Cn16Char[i].Index[1] && \
                *(CnString + 2) == Cn16Char[i].Index[2])
            {
                OLED_ShowIcon16(row, col, Cn16Char[i].ImageData);
				break;
			}
		}
        CnString += 3;
        if ((col += 2) > 15)
        {
            col = 0;    // 超过屏幕宽度自动换行
            row++;
            if (row > 4) break;   // 超过屏幕长度不显示超过的部分
        }
	}
}
#endif // Enable_Cn16Char

/**
 * @brief Show 32*32 Icon.
 * 
 * @param row       certain row (1 ~ 3)
 * @param col       certain column (1 ~ 13)
 * @param icon32    display data of the icon
 */
void OLED_ShowIcon32(u8 row, u8 col, const u8 icon32[128])
{
	if (--row > 2 || --col > 12 || !icon32) return;
    OLED_SetCursor(2 * row, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, icon32 + 0, 32);
    OLED_SetCursor(2 * row + 1, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, icon32 + 32, 32);
    OLED_SetCursor(2 * row + 2, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, icon32 + 64, 32);
    OLED_SetCursor(2 * row + 3, col * 8);
    OLED_I2C_Write(OLED_CONTROLBYTE_DATA, icon32 + 96, 32);
}

#if Enable_Cn32Char
/**
 * @brief 显示 32*32 中文字符串，超过屏幕宽度自动换行，超过屏幕长度不显示超过的部分。
 * 
 * @param row 字符串第一个字左上角所在行
 * @param col 字符串第一个字左上角所在列
 * @param CnString 待显示的中文字符（UTF-8 编码）
 */
void OLED_ShowCnString32(u8 row, u8 col, char* CnString)
{
    u8 i;
	if (!CnString) return;

    while(*CnString != '\0')
    {
        for(i = 0; i < Cn32Char_SUMMARY; i++)
        {
			if( *CnString == Cn32Char[i].Index[0] && \
                *(CnString + 1) == Cn32Char[i].Index[1] && \
                *(CnString + 2) == Cn32Char[i].Index[2])
            {
                OLED_ShowIcon32(row, col, Cn32Char[i].ImageData);
				break;
			}
		}
        CnString += 3;
        if ((col += 4) > 13)
        {
            col = 0;                // 超过屏幕宽度自动换行
            if (++row > 3) break;   // 超过屏幕长度则不显示
        }
	}
}
#endif // Enable_Cn32Char

/**
 * @brief 显示整数
 * 
 * @param row 数字所在行
 * @param col 数字所在列
 * @param num 待显示的数字
 * @param len 数字长度
 * @param fill 填充方式
 *   @arg FILL_BY_0 用 0 填充
 *   @arg FILL_BY_SPACE 用空格填填充
 */
void OLED_ShowNum(u8 row, u8 col, s32 num, u8 len, fill_t fill)
{
	if (--row > 3 || --col > 15 || len > 16) return;
	++row, ++col;
	
    if (num < 0)
    {
        OLED_ShowChar(row, col, '-');
        num = -num;
        col++;
        len--;
    }

    while (len--)
    {
        OLED_ShowChar(row, (u8)(col + len), (char)(num % 10 + '0'));
        num /= 10;
        if (num == 0) break;
    }

    while (len--)
    {
        OLED_ShowChar(row, (u8)(col + len), (char)fill);
    }
}
