
#include "Encoder_iic.h"

#define ENC_SCL_High()              (ENC_SCL_Pin = 1)
#define ENC_SCL_Low()               (ENC_SCL_Pin = 0)
#define ENC_SDA_High()              (ENC_SDA_Pin = 1)
#define ENC_SDA_Low()               (ENC_SDA_Pin = 0)

#define ENC_IIC_Delay()             NOP(15)


static void ENC_IIC_Start(void)
{
    ENC_SDA_High();
    ENC_SCL_High();
	ENC_IIC_Delay();
    ENC_SDA_Low();
	ENC_IIC_Delay();
    ENC_SCL_Low();
}

static void ENC_IIC_Stop(void)
{
    ENC_SDA_Low();
    ENC_SCL_High();
	ENC_IIC_Delay();
    ENC_SDA_High();
	ENC_IIC_Delay();
}

static void ENC_IIC_SendByte(u8 byte)
{
    u8 i = 0;
    for(; i < 8; i++)
    {
        ENC_SCL_Low();
		ENC_IIC_Delay();
        ENC_SDA_Pin = (byte & 0x80);
		ENC_IIC_Delay();
        ENC_SCL_High();
        byte <<= 1;
		ENC_IIC_Delay();
    }
    ENC_SCL_Low();
    ENC_SDA_High();
}

static u8 ENC_IIC_ReceiveByte(void)
{
	u8 byte;
	u8 i = 0;
	for(; i < 8; i++)
    {
		ENC_SCL_High();
		ENC_IIC_Delay();
		byte <<= 1;
		if(ENC_SDA_Pin)  byte |= 0x01;
		ENC_SCL_Low();
		ENC_IIC_Delay();
	}
	return byte;
}

static BOOL ENC_IIC_WaitAck(void)
{
	BOOL ackbit;

    ENC_SCL_High();
	ENC_IIC_Delay();
    ackbit = ENC_SDA_Pin;
    ENC_SCL_Low();

	return ackbit;
}

static void ENC_IIC_SendAck(BOOL ackbit)
{
    ENC_SCL_Low();
    ENC_SDA_Pin = ackbit;
	ENC_IIC_Delay();
    ENC_SCL_High();
	ENC_IIC_Delay();
    ENC_SCL_Low();
	ENC_SDA_High();
}

void ENC_IIC_MemWrite(u8 DevAddr, u8 MemAddr, const u8 *pData, u16 Len)
{
    u16 i = 0;

    ENC_IIC_Start();
    ENC_IIC_SendByte(DevAddr);
    ENC_IIC_WaitAck();
    ENC_IIC_SendByte(MemAddr);
    ENC_IIC_WaitAck();

    for (; i < Len; i++)
    {
        ENC_IIC_SendByte(*(pData + i));
        ENC_IIC_WaitAck();
    }

    ENC_IIC_Stop();
}

/**
 * @brief IIC读取多个字节
 * @param device_addr 设备地址(7位地址)
 * @param reg_addr 寄存器地址
 * @param buffer 接收数据的缓冲区
 * @param len 读取字节数
 * @return 0:成功 1:失败
 */
BOOL ENC_IIC_ReadBytes(u8 device_addr, u8 reg_addr, u8 *buffer, u8 len)
{
    u8 i;
    
    // 发送起始信号
    ENC_IIC_Start();
    
    // 发送设备地址(写)
    ENC_IIC_SendByte(device_addr);
    ENC_IIC_WaitAck();
    // 发送寄存器地址
    ENC_IIC_SendByte(reg_addr);
    ENC_IIC_WaitAck();
    
    // 重新发送起始信号
    ENC_IIC_Start();
    
    // 发送设备地址(读)
    ENC_IIC_SendByte(device_addr | 1);
    ENC_IIC_WaitAck();
    
    // 连续读取len个字节
    for(i = 0; i < len; i++)
    {
        buffer[i] = ENC_IIC_ReceiveByte();
        
        // 最后一个字节发送NACK,其他字节发送ACK
        if(i == len - 1)
            ENC_IIC_SendAck(1);  // NACK
        else
            ENC_IIC_SendAck(0);  // ACK
    }
    
    // 发送停止信号
    ENC_IIC_Stop();
    return TRUE;
}