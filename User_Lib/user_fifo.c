
#include "User_FIFO.h"

static void User_FIFO_AddHeadIndex(User_FIFO_TypeDef *fifo, u16 len);
static void User_FIFO_AddTailIndex(User_FIFO_TypeDef *fifo, u16 len);


/**
 * @brief FIFO 结构体初始化。
 * @note  FIFO 实际能使用的长度是其管理的内存数组长度 -1。
 * 
 * @param fifo      FIFO 结构体
 * @param buf       结构体管理的内存数组
 * @param maxSize   上述数组的长度
 */
void User_FIFO_Init(User_FIFO_TypeDef *fifo, u8 *buf, u16 maxSize)
{
    if (fifo == NULL || buf == NULL || maxSize == 0) return;

    fifo->Buff = buf;
    fifo->Head = 0;
    fifo->Tail = 0;
    fifo->MaxSize = maxSize;
    fifo->Lock = USER_FIFO_UNLOCK;
}

/**
 * @brief 向 FIFO 中写入一字节数据
 * 
 * @param fifo FIFO 结构体
 * @param byt  一字节数据
 */
void User_FIFO_WriteByte(User_FIFO_TypeDef *fifo, u8 byt)
{
    if (fifo == NULL) return;
    if (fifo->Lock == USER_FIFO_LOCK) return;

    fifo->Lock = USER_FIFO_LOCK;

    if (User_FIFO_GetUsedLength(fifo) + 1 < fifo->MaxSize)
    {
        fifo->Buff[fifo->Tail] = byt;
        User_FIFO_AddTailIndex(fifo, 1);
    }

    fifo->Lock = USER_FIFO_UNLOCK;
}

/**
 * @brief 从 FIFO 中读取一定长度数据。
 * 
 * @param fifo  FIFO 结构体
 * @param pData 数据目的地
 * @param len   要读取的长度
 * @param opt   读取选项
 */
void User_FIFO_Read(User_FIFO_TypeDef *fifo, u8 *pData, u16 len, User_FIFO_ReadOperation_TypeDef opt)
{
    u16 lenToEnd;

    if (fifo == NULL || pData == NULL || len == 0) return;  // 参数合法
    if (fifo->Lock == USER_FIFO_LOCK) return;                    // 没锁
    if (len > User_FIFO_GetUsedLength(fifo)) return;             // 长度合法

    fifo->Lock = USER_FIFO_LOCK;     // 锁上

    lenToEnd = fifo->MaxSize - fifo->Head;  // 计算尾指针后面有多少空间
    if (len <= lenToEnd)                    // 长度小于等于尾指针后面的空间
    {
        memcpy(pData, fifo->Buff + fifo->Head, len);
    }
    else                                    // 长度大于尾指针后面的空间
    {
        memcpy(pData, fifo->Buff + fifo->Head, lenToEnd);
        memcpy(pData + lenToEnd, fifo->Buff, len - lenToEnd);
    }

    if (opt == USER_FIFO_READ_AND_CLEAN)
    {
        User_FIFO_AddHeadIndex(fifo, len);       // 移动头指针
    }

    fifo->Lock = USER_FIFO_UNLOCK;               // 解锁
}

/**
 * @brief 计算已使用多少空间。
 * 
 * @param fifo FIFO 结构体
 * @return u16 使用了多少空间（字节）
 */
u16 User_FIFO_GetUsedLength(const User_FIFO_TypeDef *fifo)
{
    return (fifo->Tail + fifo->MaxSize - fifo->Head) % fifo->MaxSize;
}

/**
 * @brief 清空 FIFO 索引小于 range 的数据。
 * @note  当 range > 已使用长度时，FIFO 会被全部清空，
 *        这种情况和 range 给<User_FIFO_GetUsedLength(fifo)>是一样的。
 * 
 * @param fifo  FIFO 结构体。
 * @param range 索引
 */
void User_FIFO_Clear(User_FIFO_TypeDef *fifo, u16 range)
{
    if (fifo == NULL) return;
    if (fifo->Lock == USER_FIFO_LOCK) return;

    fifo->Lock = USER_FIFO_LOCK;
    range > User_FIFO_GetUsedLength(fifo) ? (range = User_FIFO_GetUsedLength(fifo)) : (void)0;
    User_FIFO_AddHeadIndex(fifo, range);
    fifo->Lock = USER_FIFO_UNLOCK;
}


/**
 * @brief 在 FIFO 已使用的区间上找某个字节第一次出现的位置，返回位置索引（0 ~ MaxSize - 2)。
 * 
 * @param fifo FIFO 实例
 * @param byte 想找的字节数据
 * @return u16 该字节第一次出现位置的索引。注意 0 也是索引，相当于数组的 0 号元素。
 *         而返回 65535 表示没有找到，其宏定义是 User_FIFO_BYTENOTFOUND。
 */
u16 User_FIFO_FindByte(User_FIFO_TypeDef *fifo, u8 byte)
{
    u16 index = User_FIFO_BYTENOTFOUND;
    if (fifo == NULL) return User_FIFO_BYTENOTFOUND;
    if (fifo->Lock == USER_FIFO_LOCK) return User_FIFO_BYTENOTFOUND;

    fifo->Lock = USER_FIFO_LOCK;

    if (fifo->Tail > fifo->Head)
    {
        u8 *p_res = memchr(fifo->Buff + fifo->Head, byte, fifo->Tail - fifo->Head);
        if (p_res != NULL) index = p_res - (fifo->Buff + fifo->Head);
    }
    else if (fifo->Tail < fifo->Head)
    {
        u8 *p_res = memchr(fifo->Buff, byte, fifo->Tail);
        if (p_res == NULL)
        {
            p_res = memchr(fifo->Buff + fifo->Head, byte, fifo->MaxSize - fifo->Head);
            if (p_res != NULL) index = p_res - (fifo->Buff + fifo->Head);
        }
        else index = (p_res - fifo->Buff) + (fifo->MaxSize - fifo->Head);
    }
    // else if (fifo->Tail == fifo->Head);      // 这种情况 FIFO 使用长度为 0

    fifo->Lock = USER_FIFO_UNLOCK;
    return index;
}


/**
 * @brief 根据索引获得 FIFO 数组元素的值
 * @note  FIFO 随时可以看作是一个长度为 MaxSize - 1 的数组，其 0 号元素就是最早进入队列的元素。
 * 
 * @param fifo  FIFO 实例
 * @param index FIFO 数组索引（0 ~ MaxSize - 2）
 * @param byte  数组元素（地址）
 * @return BOOL 操作是否成功
 */
BOOL User_FIFO_GetByte(User_FIFO_TypeDef *fifo, u16 index, u8 *byte)
{
    if (fifo == NULL || byte == NULL) return FALSE;
    if (index >= User_FIFO_GetUsedLength(fifo)) return FALSE;
    fifo->Lock = USER_FIFO_LOCK;

    if (index >= fifo->MaxSize - fifo->Head) *byte = fifo->Buff[index - (fifo->MaxSize - fifo->Head)];
    else *byte = fifo->Buff[fifo->Head + index];

    fifo->Lock = USER_FIFO_UNLOCK;
    return TRUE;
}


static void User_FIFO_AddHeadIndex(User_FIFO_TypeDef *fifo, u16 len)
{
    fifo->Head += len;
    fifo->Head %= fifo->MaxSize;
}

static void User_FIFO_AddTailIndex(User_FIFO_TypeDef *fifo, u16 len)
{
    fifo->Tail += len;
    fifo->Tail %= fifo->MaxSize;
}
