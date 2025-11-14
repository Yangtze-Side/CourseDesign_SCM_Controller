
#include "communication.h"
#include "contract.h"
#include "user_uart.h"
#include "system.h"
#include "Control/control.h"

#define COMM_DATBUF_SIZE        64

static bit Comm_ParseFlag = FALSE;
static u8  Comm_DatBuf[64];

DHT11_Data_t DHT11_Data;
US_Data_t US_Data;

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
                    DHT11_Data.temp_int = Comm_DatBuf[3];
                    DHT11_Data.temp_deci = Comm_DatBuf[4];
                    DHT11_Data.humi_int = Comm_DatBuf[5];
                    DHT11_Data.humi_deci = Comm_DatBuf[6];
                    US_Data.F = *(float*)(Comm_DatBuf + 7);
                    US_Data.B = *(float*)(Comm_DatBuf + 11);
                    US_Data.L = *(float*)(Comm_DatBuf + 15);
                    US_Data.R = *(float*)(Comm_DatBuf + 19);
                } break;
                
                default:
                    break;
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
    Control_Update();

    switch (ctrl_car.mode)
    {
        case Ctrl_Mode_JoyStick:
        {
            u8 dat[14];
            // 前三个字节是帧头和命令
            dat[0] = COMM_BYTE0;
            dat[1] = COMM_BYTE1;
            dat[2] = COMM_CMD_JoysMode;

            *(float*)(dat + 3) = ctrl_car.joystick.vx;       // dat[3 ~ 6] 存放 vx
            *(float*)(dat + 7) = ctrl_car.joystick.vy;       // dat[7 ~ 10] 存放 vy
            *(float*)(dat + 11) = ctrl_car.joystick.vw;      // dat[11 ~ 13] 存放 vw

            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
        } break;
        
        case Ctrl_Mode_Gravity:
        {
            u8 dat[14];
            // 前三个字节是帧头和命令
            dat[0] = COMM_BYTE0;
            dat[1] = COMM_BYTE1;
            dat[2] = COMM_CMD_GravMode;

            *(float*)(dat + 3) = ctrl_car.gravity.vx;       // dat[3 ~ 6] 存放 vx
            *(float*)(dat + 7) = ctrl_car.gravity.vy;       // dat[7 ~ 10] 存放 vy
            *(float*)(dat + 11) = ctrl_car.gravity.target_yaw;      // dat[11 ~ 13] 存放 target_angle

            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
        } break;

        case Ctrl_Mode_AutoCruise:
        {
            u8 dat[3];

            // 前三个字节是帧头和命令
            dat[0] = COMM_BYTE0;
            dat[1] = COMM_BYTE1;
            dat[2] = COMM_CMD_ACMode;
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
        } break;

        case Ctrl_Mode_AutoFollow:
        {
            u8 dat[3];

            // 前三个字节是帧头和命令
            dat[0] = COMM_BYTE0;
            dat[1] = COMM_BYTE1;
            dat[2] = COMM_CMD_AFMode;
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
        } break;

        default: break;
    }

}
