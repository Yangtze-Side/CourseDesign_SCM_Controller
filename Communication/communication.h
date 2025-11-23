#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "config.h"
#include "contract.h"

#define Comm_LinkStatus_PIN             P32
#define Comm_GetLinkStatusPinLevel()    (Comm_LinkStatus_PIN)

typedef enum Comm_SendReq_t
{
    COMM_SendReq_NONE = 0,

    COMM_SendReq_MUSICSTART,
    COMM_SendReq_MUSICPAUSE,
    COMM_SendReq_MUSICSTOP,
    COMM_SendReq_MUSICRESUME,

    COMM_SendReq_GPIDkpAdd,
    COMM_SendReq_GPIDkpDec,
    COMM_SendReq_GPIDkiAdd,
    COMM_SendReq_GPIDkiDec,
    COMM_SendReq_GPIDkdAdd,
    COMM_SendReq_GPIDkdDec,

    COMM_SendReq_AFPIDkpAdd,
    COMM_SendReq_AFPIDkpDec,
    COMM_SendReq_AFPIDkiAdd,
    COMM_SendReq_AFPIDkiDec,
    COMM_SendReq_AFPIDkdAdd,
    COMM_SendReq_AFPIDkdDec,

    COMM_SendReq_TOTAL
} Comm_SendReq_t;

typedef struct{
    u8 humi_int;
	u8 humi_deci;
	u8 temp_int;
	u8 temp_deci;
} DHT11_Data_t;

typedef struct US_Data_t
{
    float F;                // Front, cm
    float B;                // Back, cm
    float L;                // Left, cm
    float R;                // Right, cm
} US_Data_t;

typedef struct Comm_PID_Data_t
{
    float gpid_kp;
    float gpid_ki;
    float gpid_kd;
    float afpid_kp;
    float afpid_ki;
    float afpid_kd;
} Comm_PID_Data_t;


extern Comm_PID_Data_t Comm_PID_Data;
extern DHT11_Data_t DHT11_Data;
extern US_Data_t US_Data;

void Comm_Init(void);

void Comm_Parse(u8 *dat);

void Comm_SendTask(void);

void Comm_SetLinkStatus(BOOL status);
BOOL Comm_GetLinkStatus(void);

void Comm_SendRequest(u8 req);
void Comm_MusicStart(u8 num);

#endif // !__COMMUNICATION_H
