#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "config.h"
#include "contract.h"

#define Comm_LinkStatus_PIN             P32
#define Comm_GetLinkStatusPinLevel()    (Comm_LinkStatus_PIN)

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
    float gpi_kp;
    float gpi_ki;
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

void Comm_MusicStart(u8 num);
void Comm_MusicPause(void);
void Comm_MusicStop(void);
void Comm_MusicResume(void);

#endif // !__COMMUNICATION_H
