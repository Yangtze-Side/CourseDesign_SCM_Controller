/**
 * @file user_iap.c
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
#include "user_iap.h"

/**
 * @brief IAP初始化函数
 * 
 */
void IAP_Init(void)
{
    IAP_SetTimeBase();                  //设置IAP等待参数
    IAP_Enable();                       //使能EEPROM操作
    IAP_Idle();                         //设置EEPROM为空闲模式
}

/**
 * @brief EEPROM扇区擦除函数
 * 
 * @param dwAddress 
 */
void IAP_EraseSector(u32 dwAddress)
{
    IAP_SetAddress(dwAddress);          //设置EEPROM目标地址
    IAP_TriggerErase();                 //触发EEPROM扇区擦除
    IAP_Idle();                         //恢复EEPROM空闲模式
}

/**
 * @brief EEPROM字节编程函数
 * 
 * @param dwAddress EEPROM目标字节地址
 * @param bData 待写入的字节数据
 */
static void IAP_ProgramByte(u32 dwAddress, uint8_t bData)
{
    IAP_SetAddress(dwAddress);          //设置EEPROM目标地址
    IAP_SetData(bData);                 //设置EEPROM数据
    IAP_TriggerProgram();               //触发EEPROM字节编程
    IAP_Idle();                         //恢复EEPROM空闲模式
}

/**
 * @brief EEPROM字节读取函数
 * 
 * @param dwAddress EEPROM目标字节地址
 * @return uint8_t 读取的字节数据
 */
static uint8_t IAP_ReadByte(u32 dwAddress)
{
    uint8_t dat;

    IAP_SetAddress(dwAddress);          //设置EEPROM目标地址
    IAP_TriggerRead();                  //触发EEPROM字节读取
    dat = IAP_ReadData();               //保存EEPROM数据
    IAP_Idle();                         //恢复EEPROM空闲模式

    return dat;                         //返回读取的数据
}

/**
 * @brief EEPROM数据编程函数
 * 
 * @param dwAddress EEPROM目标地址
 * @param pData 待写入的数据指针
 * @param size 数据大小（字节数）
 */
void IAP_ProgramBytes(u32 dwAddress, void* pData, u32 size)
{
    u32 i = 0;
    uint8_t* pByteData = (uint8_t*)pData;
    for (; i < size; i++)
    {
        IAP_ProgramByte(dwAddress + i, pByteData[i]);
    }
}

/**
 * @brief EEPROM数据读取函数
 * 
 * @param dwAddress EEPROM目标地址
 * @param pData 读取数据存放指针
 * @param size 数据大小（字节数）
 */
void IAP_ReadBytes(u32 dwAddress, void* pData, u32 size)
{
    u32 i = 0;
    uint8_t* pByteData = (uint8_t*)pData;
    for (; i < size; i++)
    {
        pByteData[i] = IAP_ReadByte(dwAddress + i);
    }
}
