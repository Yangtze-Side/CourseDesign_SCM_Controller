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
	u8 Index;					// Index of 4 uart peripherals
	u8 Busy;					// If it's in sending process
	u8 *Buf;					// Sending buffer
	const u8 BufSize;			// Buffer size
	u8 TxSize;					// Length to send
	u8 Cnt;						// Counter of sent bytes
} UART_Send_t;

typedef struct UART_Recv_t
{
	u8 Index;					// Index of 4 uart peripherals
	u8 Start;					// If it's in receiving process
	u8 *Buf;					// Receiving buffer
	const u8 BufSize;			// Buffer size
	u8 Cnt;						// Counter of received bytes
	u8 Timeout;					// Counter of timeout
} UART_Recv_t;


BOOL UART_Send_Start(UART_Send_t *send, u8 *pDat, u8 txSize);
void UART_Send_ITHandler(UART_Send_t *huart);

void UART_Recv_ITHandler(UART_Recv_t *recv);
void UART_Recv_Task_5ms(UART_Recv_t *recv);

#endif
