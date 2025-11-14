#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "config.h"

void Comm_StartParse(u8 DatBuf[64], u8 len);
void Comm_ParseTask(void);

void Comm_SendTask(void);

#endif // !__COMMUNICATION_H
