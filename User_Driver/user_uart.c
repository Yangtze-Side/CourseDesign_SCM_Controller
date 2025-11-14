
#include "user_uart.h"

static UART_RecvCB_t uart_recv_cb = NULL;

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
 * @brief UART receiving it handler.
 * 
 * @param recv The handle
 */
void UART_Recv_ITHandler(UART_Recv_t *recv)
{
	if (recv->Start == FALSE)
	{
		recv->Start = TRUE;
		recv->Cnt = 0;
	}
	++recv->Cnt;
	recv->Timeout = 0;
	if (recv->Cnt <= recv->BufSize)
	{
		switch (recv->Index)
		{
			case UART1: recv->Buf[recv->Cnt - 1] = SBUF; break;
			case UART2: recv->Buf[recv->Cnt - 1] = S2BUF; break;
			case UART3: recv->Buf[recv->Cnt - 1] = S3BUF; break;
			case UART4: recv->Buf[recv->Cnt - 1] = S4BUF; break;
			default: break;
		}
	}
	else
	{
		recv->Start = FALSE;
		// Receiving completes for the buffer is full.
		if (uart_recv_cb) uart_recv_cb(recv);
	}
}

/**
 * @brief Periodicly executed function that is used to check receiving timeout.
 * 
 * @param recv The handle
 */
void UART_Recv_Task_5ms(UART_Recv_t *recv)
{
	if (recv->Start == TRUE)
	{
		if (++recv->Timeout >= UART_RecvTimeout)
		{
			recv->Start = FALSE;
			recv->Timeout = 0;
			// Receiving completes for time's up.
			if (uart_recv_cb) uart_recv_cb(recv);
		}
	}
}

/**
 * @brief Set UART receiving call back function.
 * 
 * @param cb the call back function name
 */
void UART_Recv_SetCB(UART_RecvCB_t cb)
{
	uart_recv_cb = cb;
}
