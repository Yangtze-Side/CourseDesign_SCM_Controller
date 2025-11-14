
#include "communication.h"
#include "contract.h"
#include "user_uart.h"
#include "system.h"
#include "control.h"

#define COMM_DATBUF_SIZE        64

static bit Comm_ParseFlag = FALSE;
static u8  Comm_DatBuf[64];

/**
 * @brief Start parse uart data
 * 
 * @param DatBuf uart receive buffer
 * @param len    length of data received
 */
void Comm_StartParse(u8 DatBuf[64], u8 len)
{
    memcpy(Comm_DatBuf, DatBuf, len);
    Comm_ParseFlag = 1;
}


/**
 * @brief Data parse task. Executed in the infinite loop in main().
 * 
 */
void Comm_ParseTask(void)
{
    if (Comm_ParseFlag)
    {
        Comm_ParseFlag = 0;
        if (COMM_IsFrameHeadCorrect(Comm_DatBuf))
        {
            switch (Comm_DatBuf[2])
            {
                case COMM_CMD_DHT11Data:
                {
                    // 这是小车回传的温湿度数据，创建一个结构体变量来接收它们，并在头文件里 extern 这个结构体变量
                } break;
                
                case COMM_CMD_Distance:
                {
                    // 这是小车回传的距离数据，也是创建一个结构体变量来接收它们，并在头文件里 extern 这个结构体变量
                } break;
            }
        }
    }
}


/**
 * @brief This function handles data sending task.
 * @note  It's executed every 60ms.
 * 
 */
void Comm_SendTask(void)
{
    // 示例：发送摇杆模式的控制信息
    float joys_vx, joys_vy, joys_vw;        // 这些变量应该是从其他文件拿来的，比如 control.h
    u8 dat[14] = { COMM_BYTE0, COMM_BYTE1, COMM_CMD_JoysMode }; // 前三个字节是帧头和命令
    *(float*)(dat + 3) = joys_vx;       // dat[3 ~ 6] 存放 vx
    *(float*)(dat + 7) = joys_vy;       // dat[7 ~ 10] 存放 vy
    *(float*)(dat + 11) = joys_vw;      // dat[11 ~ 13] 存放 vw
    UART_Send_Start(&uart1_tx, dat, 14);

    // 这个函数根据当前的遥控模式来发送对应的控制信息
    // 可以用 switch - case 语句实现

    
}
