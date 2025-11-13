#ifndef __USER_UART_H
#define __USER_UART_H

#include "config.h"

#define UART1					1
#define UART2					2
#define UART3					3
#define UART4					4

#define UART_RecvTimeout		6

typedef struct UART_Send_t
{
	u8 Index;
	u8 Busy;
	u8 *Buf;
	u8 Size;
	u8 Cnt;
} UART_Send_t;

typedef struct UART_Recv_t
{
	u8 Index;
	u8 Start;
	u8 *Buf;
	const u8 Size;
	u8 Cnt;
	u8 Timeout;
} UART_Recv_t;

typedef void (*UART_RecvCB_t)(UART_Recv_t *recv);

void UART_Send_Start(UART_Send_t *huart, u8 txSize);
void UART_Send_ITHandler(UART_Send_t *huart);

void UART_Recv_ITHandler(UART_Recv_t *recv);
void UART_Recv_Task_5ms(UART_Recv_t *recv);
void UART_Recv_SetCB(UART_RecvCB_t cb);

#endif
