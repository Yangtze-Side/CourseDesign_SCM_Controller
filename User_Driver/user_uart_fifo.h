#ifndef __USER_UART_FIFO_H
#define __USER_UART_FIFO_H

#include "config.h"
#include "user_lib.h"

#define UART_RECV_USE_FIFO      0

#define UART1					1
#define UART2					2
#define UART3					3
#define UART4					4

typedef struct UART_Send_t
{
	u8 Index;					// Index of 4 uart peripherals
	u8 Busy;					// If it's in sending process
	u8 *Buf;					// Sending buffer
	u8 BufSize;			// Buffer size
	u8 TxSize;					// Length to send
	u8 Cnt;						// Counteor of sent bytes
} UART_Send_t;

#if UART_RECV_USE_FIFO
typedef struct UART_Recv_t
{
	u8                  Index;			// Index of 4 uart peripherals
    u16                 Cnt;            // Count recently received data length
    u16                 SizeOfProc;     // When data bytes length is more than this value, process program starts
    // void (*DataProcFunc)(UART_Recv_t*);  // Data process function
    User_FIFO_TypeDef  *FIFO;           // FIFO queue used to process the data received
} UART_Recv_t;
#else
typedef struct UART_Recv_t
{
	u8  Index;					// Index of 4 uart peripherals
	u8  Start;					// If it's in receiving process
	u8  *Buf;					// Receiving buffer
	u16 BufSize;			    // Buffer size
	u16 Cnt;					// Counter of received bytes
	u16 RecvLen;				// Length of received bytes
	u8  Timeout;				// Counter of timeout
} UART_Recv_t;
#endif

void UART_Send_Init(u8 UARTx, UART_Send_t *send, u8 *buf, u8 bufSize);
BOOL UART_Send_Start(UART_Send_t *send, u8 *pDat, u8 txSize);
void UART_Send_ITHandler(UART_Send_t *huart);

#if UART_RECV_USE_FIFO
void UART_Recv_Init (
    u8 UARTx,
    UART_Recv_t *recv,
    User_FIFO_TypeDef *fifo,
    u8 *buf,
    u16 maxSize,
	u16 sizeOfProc
);
void UART_Recv_ITHandler(UART_Recv_t *recv);
#else
void UART_Recv_Init( u8 UARTx, UART_Recv_t *recv, u8 *buf, u16 bufSize );
void UART_Recv_ITHandler(UART_Recv_t *recv);
void UART_Recv_Task_5ms(UART_Recv_t *recv);
#endif

#endif // !__USER_UART_FIFO_H
