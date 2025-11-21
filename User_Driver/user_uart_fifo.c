
#include "user_uart_fifo.h"
#include "system.h"


#define RecvDataProc(recv)				uart_recv_dataproc(recv)


/**
 * @brief Init uart send handle.
 * 
 * @param UARTx Index of uart (for C51 only)
 * @param send  The uart send handle
 * @param buf 	The data buffer
 * @param bufSize Size of the data buffer
 */
void UART_Send_Init(u8 UARTx, UART_Send_t *send, u8 *buf, u8 bufSize)
{
	send->Index = UARTx;
	send->Buf = buf;
	send->BufSize = bufSize;
	send->TxSize = 0;
	send->Busy = FALSE;
	send->Cnt = 0;
}


/**
 * @brief Starts the uart sending process.
 * @note  串口发送完一个数组需要一定时间，但是这个函数是非阻塞的，发送过程会在中断里自动完成；
 * 		  但是如果需要紧接着调用两次这个函数，需要在第二次以上调用时保证第一次已发送完成。请
 * 		  这么写：
 * 			  UART_Send_Start(tx, pdat1, size1);
 * 			  while (UART_Send_Start(tx, pdat2, size2) == FALSE);
 * 			  while (UART_Send_Start(tx, pdat3, size3) == FALSE);
 * 
 * @param send 		The uart handle
 * @param pDat 		Data array address or NULL.
 * 					Giving NULL is indicates that data is already at send->Buf.
 * @param txSize 	size in byte to be sent
 * @return BOOL 	If sending requiement is approved
 */
BOOL UART_Send_Start(UART_Send_t *send, u8 *pDat, u8 txSize)
{
	u8 actual_send_length;
	if (send->Busy == TRUE) return FALSE;
	if (txSize == 0) return TRUE;
	send->Busy = TRUE;
	actual_send_length = min(txSize, send->BufSize);
	if (pDat != NULL) memcpy(send->Buf, pDat, actual_send_length);
	switch (send->Index)
	{
		case UART1: SBUF  = *(send->Buf); break;
		case UART2: S2BUF = *(send->Buf); break;
		case UART3: S3BUF = *(send->Buf); break;
		case UART4: S4BUF = *(send->Buf); break;
		default: break;
	}
	send->Cnt = 0;
	send->TxSize = actual_send_length;
	return TRUE;
}


/**
 * @brief UART sending interrupt handler.
 * 
 * @param send  The uart handle.
 */
void UART_Send_ITHandler(UART_Send_t *send)
{
	++send->Cnt;
	if (send->Cnt >= send->TxSize)
	{
		send->Busy = FALSE;
		// Sending completes.
	}
	else
	{
		switch (send->Index)
		{
			case UART1: SBUF  = send->Buf[send->Cnt]; break;
			case UART2: S2BUF = send->Buf[send->Cnt]; break;
			case UART3: S3BUF = send->Buf[send->Cnt]; break;
			case UART4: S4BUF = send->Buf[send->Cnt]; break;
			default: break;
		}
	}
}


/**
 * @brief Init uart receive handle.
 * 
 * @param UARTx Index of uart (for C51 only)
 * @param recv  The uart receive handle
 * @param fifo  The fifo instance
 * @param buf 	Buffer for fifo
 * @param maxSize Max size of the buffer
 * @param sizeOfProc When data bytes length is more than this value, process program will start
 */
void UART_Recv_Init (
	u8 UARTx,
	UART_Recv_t *recv,
	User_FIFO_TypeDef *fifo,
	u8 *buf,
	u16 maxSize,
	u16 sizeOfProc
)
{
	recv->Index = UARTx;
	recv->Cnt = 0;
	recv->FIFO = fifo;
	recv->SizeOfProc = sizeOfProc;
	User_FIFO_Init(fifo, buf, maxSize);
}


/**
 * @brief UART receiving it handler.
 * 
 * @param recv The handle
 */
void UART_Recv_ITHandler(UART_Recv_t *recv)
{
	u8 datatmp;
	switch (recv->Index)
	{
		case UART1: datatmp = SBUF;  break;
		case UART2: datatmp = S2BUF; break;
		case UART3: datatmp = S3BUF; break;
		case UART4: datatmp = S4BUF; break;
		default: break;
	}
	User_FIFO_WriteByte(recv->FIFO, datatmp);
	if (++recv->Cnt >= recv->SizeOfProc)
	{
		recv->Cnt = 0;
		RecvDataProc(recv);
	}
}
