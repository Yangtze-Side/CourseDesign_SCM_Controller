
#include "communication.h"
#include "user_uart_fifo.h"
#include "system.h"
#include "Control/control.h"

US_Data_t US_Data = { 0 };
DHT11_Data_t DHT11_Data = { 0 };
Comm_PID_Data_t Comm_PID_Data = { 0 };
float Comm_Car_Yaw = 0.0f;
static BOOL Comm_Linked = FALSE;
static u8 Comm_SendReq = COMM_SendReq_NONE;
static u8 comm_music_num = 1;

void Comm_Init(void)
{
    Comm_Linked = Comm_GetLinkStatusPinLevel();
}

/*-------------------------------------- Library ------------------------------------*/

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
            case COMM_CMD_CarData:
            {
                DHT11_Data.temp_int = dat[3];
                DHT11_Data.temp_deci = dat[4];
                DHT11_Data.humi_int = dat[5];
                DHT11_Data.humi_deci = dat[6];
                US_Data.F = *(float*)(dat + 7);
                US_Data.B = *(float*)(dat + 11);
                US_Data.L = *(float*)(dat + 15);
                US_Data.R = *(float*)(dat + 19);
                Comm_PID_Data.gpid_kp = *(float*)(dat + 23);
                Comm_PID_Data.gpid_ki = *(float*)(dat + 27);
                Comm_PID_Data.gpid_kd = *(float*)(dat + 31);
                Comm_PID_Data.afpid_kp = *(float*)(dat + 35);
                Comm_PID_Data.afpid_ki = *(float*)(dat + 39);
                Comm_PID_Data.afpid_kd = *(float*)(dat + 43);
                Comm_Car_Yaw = - *(float*)(dat + 47) + 180.0f;
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

    switch (Comm_SendReq)
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

                case Ctrl_Mode_Encoder:
                {
                    u8 dat[15];
                    // 前三个字节是帧头和命令
                    dat[0] = COMM_HEAD_BYTE0;
                    dat[1] = COMM_HEAD_BYTE1;
                    dat[2] = COMM_CMD_EncoderMode;

                    *(float*)(dat + 3) = ctrl_car.encoder->vx;       // dat[3 ~ 6] 存放 vx
                    *(float*)(dat + 7) = ctrl_car.encoder->vy;       // dat[7 ~ 10] 存放 vy
                    *(float*)(dat + 11) = ctrl_car.encoder->target_yaw;      // dat[11 ~ 14] 存放 target_angle

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
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_MUSICPAUSE:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_MusicPause };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_MUSICSTOP:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_MusicStop };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;
        
        case COMM_SendReq_MUSICRESUME:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_MusicResume };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;


        case COMM_SendReq_GPIDkpAdd:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_GPIDkpAdd };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;
        
        case COMM_SendReq_GPIDkpDec:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_GPIDkpDec };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_GPIDkiAdd:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_GPIDkiAdd };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_GPIDkiDec:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_GPIDkiDec };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_GPIDkdAdd:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_GPIDkdAdd };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_GPIDkdDec:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_GPIDkdDec };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;


        case COMM_SendReq_AFPIDkpAdd:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_AFPIDkpAdd };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_AFPIDkpDec:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_AFPIDkpDec };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_AFPIDkiAdd:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_AFPIDkiAdd };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_AFPIDkiDec:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_AFPIDkiDec };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_AFPIDkdAdd:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_AFPIDkdAdd };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
        } break;

        case COMM_SendReq_AFPIDkdDec:
        {
            u8 dat[3] = { COMM_HEAD_BYTE0, COMM_HEAD_BYTE1, COMM_CMD_AFPIDkdDec };
            UART_Send_Start(&uart1_tx, dat, sizeof(dat));
            Comm_SendReq = COMM_SendReq_NONE;
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


/*-------------------------------------- User Determine ------------------------------------*/

/**
 * @brief 请求发送特定信号。需要参数的信号会有单独的函数。
 * 
 * @param req 信号
 */
void Comm_SendRequest(u8 req)
{
    if (req >= COMM_SendReq_TOTAL) return;
    Comm_SendReq = req;
}

/**
 * @brief 发送信息让小车播放音乐。
 * 
 * @param num 音乐序号。
 */
void Comm_MusicStart(u8 num)
{
    Comm_SendReq = COMM_SendReq_MUSICSTART;
    comm_music_num = num;
}
