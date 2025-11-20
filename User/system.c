
#include "system.h"
#include <stdarg.h>
#include "imu_app.h"
#include "communication.h"
#include "Display.h"

/*---------------------------------------- System Variables --------------------------------------*/

static volatile u32 sys_tick;          	// System tick variable, increases in SysTick interrupt.
                                    	// And the increase frequency is 1 KHz.

u8 xdata UART1_SendBuf[UART1_SendBuf_SIZE];
u8 xdata UART1_RecvBuf[UART1_RecvBuf_SIZE];

UART_Send_t uart1_tx = { UART1, FALSE, UART1_SendBuf, UART1_SendBuf_SIZE, 0, 0 };
UART_Recv_t uart1_rx = { UART1, FALSE, UART1_RecvBuf, UART1_RecvBuf_SIZE, 0, 0 };

/*---------------------------------------- User Determine --------------------------------------*/

/**
 * @brief Project init.
 * 
 */
void proj_init(void)
{
	Display_Init();
	IMU_Init();
}

/**
 * @brief UART receive handler, when a frame of data has received.
 * 
 * @param recv the handle
 */
void uart_recv_handler(UART_Recv_t *recv)
{
	if (recv->Index == UART1)
	{
		Comm_StartParse(UART1_RecvBuf, recv->Cnt);
	}
}

void sys_uart_recv_task_5ms(void)
{
	UART_Recv_Task_5ms(&uart1_rx);
}

/*---------------------------------------- System Functions --------------------------------------*/

/*---------------------- User Printf ---------------------*/

#define PRINTF_BUF                      UART1_SendBuf
#define PRINTF_HANDLE                   uart1_tx

/**
 * @brief User-defined printf function, whose usage is the same as printf.
 * 
 * @param f 	format stirng
 * @param ... 	args
 */
void user_printf(const char *f, ...)
{
	va_list args;
	if (PRINTF_HANDLE.Busy == TRUE) return;
	
	va_start(args, f);
	vsprintf((char*)PRINTF_BUF, f, args);
	va_end(args);
	UART_Send_Start(&PRINTF_HANDLE, NULL, strlen((char*)PRINTF_BUF));
}


/*---------------------- SysTick ---------------------*/

/**
 * @brief System delay function.
 * 
 * @param ms time in millisecond
 */
void Sys_Delay(u32 ms)
{
    u32 tick_start = Sys_GetTick();
    if (ms < Sys_MAX_DELAY) ms++;
    while (Sys_GetTick() - tick_start < ms);
}

/**
 * @brief Increase sys_tick by 1.
 * 
 */
void Sys_IncTick(void)
{
    ++sys_tick;
}

/**
 * @brief Get sys_tick.
 * 
 * @return u32 sys_tick
 */
u32 Sys_GetTick(void)
{
    return sys_tick;
}
