
#include "user_spi.h"
#include "system.h"


/**
 * @brief SPI send a reg addr and a data byte.
 * 
 * @param Byte      data byte
 * @param Timeout   timeout of sending one byte, in ms
 * @return u8       User_SPI_Status (in user_spi.h)
 */
u8 User_SPI_Write(u8 Byte, u32 Timeout)
{
    u32 tick_start;
    u8  timeoutFlag = FALSE;

    SPI_SendData(Byte);                 // Send data byte
    tick_start = Sys_GetTick();         // Record start timestamp
    while (!SPI_CheckFlag())            // Wait until sending process is over
    {
        if (Sys_GetTick() - tick_start > Timeout)
        {
            timeoutFlag = TRUE;
            break;
        }
    }
    SPI_ClearFlag();                    // Clear IT flag
    return timeoutFlag;
}


/**
 * @brief SPI read an amount of data byte.
 * 
 * @param Buf       data buffer
 * @param Len       length to read
 * @param Timeout   timeout of the whole receiving process, in ms
 * @return u8       User_SPI_Status (in user_spi.h)
 */
u8 User_SPI_Read(u8 *Buf, u16 Len, u32 Timeout)
{
    u32 tick_start;
    u16 read_index = 0;
    u8  timeoutFlag = FALSE;

    tick_start = Sys_GetTick();             // Record start timestamp
    for (; read_index < Len; read_index++)
    {
        SPI_SendData(0xff);                 // Send dummy data byte
        while (!SPI_CheckFlag())            // Wait until sending process is over
        {
            if (Sys_GetTick() - tick_start > Timeout)
            {
                timeoutFlag = TRUE;
                break;
            }
        }
        SPI_ClearFlag();                    // Clear IT flag
        if (timeoutFlag) break;             // Exit reading process if the bus is stucked
        Buf[read_index] = SPI_ReadData();   // Copy data into Buffer
    }

    return timeoutFlag;
}
