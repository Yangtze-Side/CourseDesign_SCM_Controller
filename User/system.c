
#include "system.h"
#include <stdarg.h>
#include "imu_app.h"
#include "communication.h"
#include "contract.h"
#include "Display.h"
#include "EncoderKey.h"
#include "FOC_App.h"

/*---------------------------------------- System Variables --------------------------------------*/

static volatile u32 sys_tick;          	// System tick variable, increases in SysTick interrupt.
                                    	// And the increase frequency is 1 KHz.

u8 xdata UART1_SendBuf[UART1_SendBuf_SIZE];
UART_Send_t uart1_tx;

static u8 xdata UART1_RecvBuf[UART1_RecvBuf_SIZE];
UART_Recv_t uart1_rx;
#if UART_RECV_USE_FIFO
static User_FIFO_TypeDef UART1_FIFO;
#endif

static u8 sec_cnt = 0;

/*---------------------------------------- User Determine --------------------------------------*/

/**
 * @brief Project init.
 * 
 */
void proj_init(void)
{
	UART_Send_Init(UART1, &uart1_tx, UART1_SendBuf, UART1_SendBuf_SIZE);
#if UART_RECV_USE_FIFO
	UART_Recv_Init(UART1, &uart1_rx, &UART1_FIFO, UART1_RecvBuf, UART1_RecvBuf_SIZE, UART1_RX_SIZEOFPROC);
#else
	UART_Recv_Init(UART1, &uart1_rx, UART1_RecvBuf, UART1_RecvBuf_SIZE);
#endif
	IMU_Init();
#if !CODE_SIMULATION
	EncoderKey_Init();
#endif
	Display_Init();
	Comm_Init();
#if !CODE_SIMULATION
	User_PWM_Init();
	FOC_Init();
#endif
}

#if UART_RECV_USE_FIFO
/**
 * @brief UART receive handler, when an amount of data has been received.
 * @note  此函数在中断中调用，当某串口的 FIFO 每接收到一定数量的数据字节后会在中断中调用此函数。
 * 		  数据处理的时候注意不要调用其他地方也会调用到的函数。
 * 
 * @param recv the handle
 */
void uart_recv_dataproc(UART_Recv_t *recv)
{
	if (recv->Index == UART1)
	{
		u8 packtail_byte[2];
		if (User_FIFO_GetUsedLength(recv->FIFO) >= 2 &&
			User_FIFO_GetByte(recv->FIFO, -2, packtail_byte + 0) == COMM_TAIL_BYTE0 &&
			User_FIFO_GetByte(recv->FIFO, -1, packtail_byte + 1) == COMM_TAIL_BYTE1)
		{
			/**
			 * 从所有 FIFO 数据中找到包头，如果没找到，就删除所有数据；
			 * 如果找到了（包头的第一个字节），删除包头（第一个字节）之前（索引小于它）的数据，
			 * 如果剩余数据长度大于一帧长度，那就处理，否则不处理。
			 * 
			 */
			// 找包头的 BYTE0
			u16 index = User_FIFO_FindByte(recv->FIFO, COMM_HEAD_BYTE0);
			if (index == User_FIFO_BYTENOTFOUND)
			{
				// 没找到，删除所有数据
				User_FIFO_Clear(recv->FIFO, recv->FIFO->MaxSize);
			}
			else
			{
				// 找到了，删除 BYTE0 以前的数据
				u8 byte1 = ~COMM_HEAD_BYTE1;
				User_FIFO_Clear(recv->FIFO, index);
				// 查看下一个字节是不是包头的 BYTE1
				if (User_FIFO_GetByte(recv->FIFO, 1, &byte1))
				{
					if (byte1 == COMM_HEAD_BYTE1)
					{
						// 如果是 BYTE1
						if (User_FIFO_GetUsedLength(recv->FIFO) >= COMM_CMD_DHT11Data_LEN)
						{
							// 如果剩余数据长度大于一帧长度，那么读取并解析数据，否则无操作
							u8 dht11_dat[COMM_CMD_DHT11Data_LEN];
							User_FIFO_Read(recv->FIFO, dht11_dat, COMM_CMD_DHT11Data_LEN, USER_FIFO_READ_AND_CLEAN);
							// Process the data
							Comm_Parse(dht11_dat);
						}
					}
					else
					{
						// 把前面那个假 BYTE0 删了
						User_FIFO_Clear(recv->FIFO, 1);
					}
				}
				else
				{
					// 如果不能查，那么一定是 FIFO 长度小于 2，那就不管了
				}
			}
		}
	}
}
#else
void uart_recv_dataproc(UART_Recv_t *recv)
{
	if (recv->Index == UART1)
	{
		if (recv->RecvLen >= COMM_CMD_DHT11Data_LEN)
		{
			Comm_Parse(recv->Buf);
		}
	}
}

/**
 * @brief 如果使用 非 FIFO 模式接收数据，则需要定时调用此函数处理接收到的数据。
 * 
 */
void uart_recv_task(void)
{
#if !UART_RECV_USE_FIFO
	UART_Recv_Task_5ms(&uart1_rx);
#endif
}
#endif


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


/*---------------------- SecCnt ---------------------*/

u8 Get_SecCnt(void)
{
	return sec_cnt;
}

void SecCnt_Task(void)
{
	static u8 task_cnt = 0;
	if (++task_cnt >= 200)
	{
		task_cnt = 0;
		++sec_cnt >= 60 ? sec_cnt = 0 : (void)0;
	}
}
