#ifndef __SYSTICK_H
#define __SYSTICK_H

//#include "stm32f10x.h"
#include "system_conf.h"
//#include "led.h"
void SysTick_Init(void);
void Delay_us(__IO u32 nTime);
void Delay_ms(__IO u32 nTime);
void TimingDelay_Decrement(void);
//void TimingDelay2_Decrement(void);
#endif
