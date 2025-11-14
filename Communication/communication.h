#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "config.h"

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


extern DHT11_Data_t DHT11_Data;
extern US_Data_t US_Data;

void Comm_StartParse(u8 DatBuf[64], u8 len);
void Comm_ParseTask(void);

void Comm_SendTask(void);

#endif // !__COMMUNICATION_H
