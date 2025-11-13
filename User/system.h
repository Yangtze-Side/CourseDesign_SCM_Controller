#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "config.h"
#include "user_driver.h"

/*---------------------------------- System Defines ---------------------------------*/

#define Sys_MAX_DELAY                       ( 0xffffffff )

#define UART1_SendBuf_SIZE		            128
#define UART1_RecvBuf_SIZE		            64


/*-------------------------------- Exported Variables -------------------------------*/

extern u8 xdata UART_RecvBuf[UART1_RecvBuf_SIZE];
extern u8 xdata UART1_RecvBuf[UART1_RecvBuf_SIZE];

extern UART_Send_t uart1_tx;
extern UART_Recv_t uart1_rx;


/*-------------------------------- Exported Functions -------------------------------*/

void proj_init(void);
void user_printf(const char *f, ...);

void sys_uart_recv_task_5ms(void);

void Sys_Delay(u32 ms);
void Sys_IncTick(void);
u32  Sys_GetTick(void);

#endif // !__SYSTEM_H
