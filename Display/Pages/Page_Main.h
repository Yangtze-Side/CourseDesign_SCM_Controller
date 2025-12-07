#ifndef __PAGE_MAIN_H
#define __PAGE_MAIN_H

#include "Display.h"

#define PageMain_Ptr_MAX     ((u8)(PAGE_TOTAL - 1))   // 主页面的页面指针最大值


/*------------------------------- Exported Vars & Funcs -----------------------------*/

extern u8 Page_Main_Ptr;
extern BOOL Do_Init;

void Page_Main_Subtrate(void);
void Page_Main_Task(void);


/*---------------------------------------------- User Determine -------------------------------------------*/

void Page_Main_Key_Left(void);
void Page_Main_Key_Right(void);
void Page_Main_Key_Mode_ShortPress(void);
void Page_Main_Key_Mode_LongPress(void);

#endif // !__PAGE_MAIN_H
