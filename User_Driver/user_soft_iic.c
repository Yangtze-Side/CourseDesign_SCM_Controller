
#include "user_soft_iic.h"

#define SCL_High()              (SCL_Pin = 1)
#define SCL_Low()               (SCL_Pin = 0)
#define SDA_High()              (SDA_Pin = 1)
#define SDA_Low()               (SDA_Pin = 0)

#define DELAY_TIME	10

static void IIC_Delay(void)
{
    NOP(1);
}

static void IIC_Start(void)
{
    SDA_High();
    SCL_High();
	IIC_Delay();
    SDA_Low();
	IIC_Delay();
    SCL_Low();    
}

static void IIC_Stop(void)
{
    SDA_Low();
    SCL_High();
	IIC_Delay();
    SDA_High();
	IIC_Delay();
}

static void IIC_SendByte(u8 byte)
{
    u8 i = 0;
    for(; i < 8; i++)
    {
        SCL_Low();
		IIC_Delay();
        SDA_Pin = (byte & 0x80);
		IIC_Delay();
        SCL_High();
        byte <<= 1;
		IIC_Delay();
    }
    SCL_Low();
    SDA_High();
}

static u8 IIC_ReceiveByte(void)
{
	u8 byte;
	u8 i = 0;
	for(; i < 8; i++)
    {   
		SCL_High();
		IIC_Delay();
		byte <<= 1;
		if(SDA_Pin)  byte |= 0x01;
		SCL_Low();
		IIC_Delay();
	}
	return byte;    
}

static u8 IIC_WaitAck(void)
{
	u8 ackbit;
	
    SCL_High();
	IIC_Delay();
    ackbit = SDA_Pin; 
    SCL_Low();
	
	return ackbit;
}

static void IIC_SendAck(u8 ackbit)
{
    SCL_Low();
    SDA_Pin = ackbit; 
	IIC_Delay();
    SCL_High();
	IIC_Delay();
    SCL_Low(); 
	SDA_High();
}

void IIC_MemWrite(u8 DevAddr, u8 MemAddr, u8 *pData, u16 Len)
{
    u16 i = 0;

    IIC_Start();
    IIC_SendByte(DevAddr);
    IIC_WaitAck();
    IIC_SendByte(MemAddr);
    IIC_WaitAck();

    for (; i < Len; i++)
    {
        IIC_SendByte(*(pData + i));
        IIC_WaitAck();
    }

    IIC_Stop();
}
