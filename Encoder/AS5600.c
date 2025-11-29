#include "AS5600.h"
#include "Encoder_iic.h"

float encoder_degree = 0.0f;  // 存储转换后的角度值(度)
u16 raw_angle;

/**
 * @brief 读取AS5600的原始角度值
 * @return 12位原始角度值(0-4095), 0xFFFF表示读取失败
 */
void AS5600_ReadRawAngle(void)
{
    u8 encoder_data[2];
    
    // 读取原始角度寄存器(连续读取2个字节)
    ENC_IIC_ReadBytes(AS5600_ADDR, AS5600_RAW_ANGLE_H, encoder_data, 2);
    
    // 合成12位角度值(高4位 + 低8位)
    raw_angle = MAKEWORD(encoder_data[1], encoder_data[0]);
}

/** 
 * @brief 将原始角度值转换为角度(度)
 * @param raw_angle 12位原始角度值(0-4095)
 * @return 角度值(0-360度)
 */
float AS5600_RawAngleToDegree(u16 raw_angle)
{
    // 4096对应360度
    return (float)raw_angle * 360.0f / 4096.0f;
}

void AS5600_Update(void)
{
    AS5600_ReadRawAngle();
    if(raw_angle != 0xFFFF)
    {
        encoder_degree = AS5600_RawAngleToDegree(raw_angle);
        // 在此处处理angle_degree，例如存储或显示
    }
}
