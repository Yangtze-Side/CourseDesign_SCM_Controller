
#include "communication.h"
#include "user_uart_fifo.h"
#include "system.h"
#include "Control/control.h"

#define COMM_SendReq_NONE           0
#define COMM_SendReq_MUSICSTART     1
#define COMM_SendReq_MUSICPAUSE     2
#define COMM_SendReq_MUSICSTOP      3

US_Data_t US_Data = { 0 };
DHT11_Data_t DHT11_Data = { 0 };
static BOOL Comm_Linked = FALSE;
static u8 Comm_SendRequest = COMM_SendReq_NONE;
static u8 comm_music_num = 1;


void Comm_Init(void)
{
    Comm_Linked = Comm_GetLinkStatusPinLevel();
}


/**
 * @brief Data parse program.
 * 
 * @param dat Data of a frame.
 */
void Comm_Parse(u8 *dat)
{
    if (COMM_IsFrameHeadCorrect(dat) && COMM_IsFrameTailCorrect(dat + COMM_CMD_DHT11Data_LEN - 2))
    {
        switch (dat[2])
        {
            case COMM_CMD_DHT11Data:
            {
                DHT11_Data.temp_int = dat[3];
                DHT11_Data.temp_deci = dat[4];
                DHT11_Data.humi_int = dat[5];
                DHT11_Data.humi_deci = dat[6];
                US_Data.F = *(float*)(dat + 7);
                US_Data.B = *(float*)(dat + 11);
                US_Data.L = *(float*)(dat + 15);
                US_Data.R = *(float*)(dat + 19);
            } break;
            
            default:
                break;
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
    if (Comm_Linked == FALSE) return;

    Control_Update();

    switch (Comm_SendRequest)
    {
        case COMM_SendReq_NONE:
        {
            switch (ctrl_car.mode)
            {
                case Ctrl_Mode_JoyStick:
                {
                    u8 dat[15];
                    // 前三个字节是帧头和命令
                    dat[0] = COMM_HEAD_BYTE0;
                    dat[1] = COMM_HEAD_BYTE1;
                    dat[2] = COMM_CMD_JoysMode;

                    *(float*)(dat + 3) = ctrl_car.joystick->vx;       // dat[3 ~ 6] 存放 vx
                    *(float*)(dat + 7) = ctrl_car.joystick->vy;       // dat[7 ~ 10] 存放 vy
                    *(float*)(dat + 11) = ctrl_car.joystick->vw;      // dat[11 ~ 14] 存放 vw

                    UART_Send_Start(&uart1_tx, dat, sizeof(dat));
                } break;
                
                case Ctrl_Mode_Gravity:
                {
                    u8 dat[15];
                    // 前三个字节是帧头和命令
                    dat[0] = COMM_HEAD_BYTE0;
                    dat[1] = COMM_HEAD_BYTE1;
                    dat[2] = COMM_CMD_GravMode;

                    *(float*)(dat + 3) = ctrl_car.gravity->vx;       // dat[3 ~ 6] 存放 vx
                    *(float*)(dat + 7) = ctrl_car.gravity->vy;       // dat[7 ~ 10] 存放 vy
                    *(float*)(dat + 11) = ctrl_car.gravity->target_yaw;      // dat[11 ~ 14] 存放 target_angle

                    UART_Send_Start(&uart1_tx, dat, sizeof(dat));
                } break;

                case Ctrl_Mode_AutoCruise:
                {
                    u8 dat[3];

                    // 前三个字节是帧头和命令
                    dat[0] = COMM_HEAD_BYTE0;
                    dat[1] = COMM_HEAD_BYTE1;
                    dat[2] = COMM_CMD_ACMode;
                    UART_Send_Start(&uart1_tx, dat, sizeof(dat));
                } break;

                case Ctrl_Mode_AutoFollow:
                {
                    u8 dat[3];

                    // 前三个字节是帧头和命令
                    dat[0] = COMM_HEAD_BYTE0;
                    dat[1] = COMM_HEAD_BYTE1;
                    dat[2] = COMM_CMD_AFMode;
                    UART_Send_Start(&uart1_tx, dat, sizeof(dat));
                } break;

                default: break;
            }
        } break;

        case COMM_SendReq_MUSICSTART:
        {
            u8 dat[4] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_MusicStart };
            dat[3] = comm_music_num;
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendRequest = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_MUSICPAUSE:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_MusicStart };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendRequest = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_MUSICSTOP:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_MusicStart };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendRequest = COMM_SendReq_NONE;
        } break;
    }
}


/**
 * @brief Change BT link status when the LINKED pin level changes.
 * 
 * @param status new satus (TRUE/FALSE)
 */
void Comm_SetLinkStatus(BOOL status)
{
    Comm_Linked = status;
}


/**
 * @brief Get BT link status.
 * 
 * @return BOOL status (TRUE for linked and FALSE vice versa).
 */
BOOL Comm_GetLinkStatus(void)
{
    return Comm_Linked;
}


/**
 * @brief 发送信息让小车播放音乐。
 * 
 * @param num 音乐序号。
 */
void Comm_MusicStart(u8 num)
{
    Comm_SendRequest = COMM_SendReq_MUSICSTART;
    comm_music_num = num;
}

void Comm_MusicPause(void)
{
    Comm_SendRequest = COMM_SendReq_MUSICPAUSE;
}

void Comm_MusicStop(void)
{
    Comm_SendRequest = COMM_SendReq_MUSICSTOP;
}
