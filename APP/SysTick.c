#include "systick.h"

__IO u32 TimingDelay ;
__IO u32 TimingDelay2 = 0;

void SysTick_Init(void)
{
	
	//SystemCoreClock / 1000    1ms�ж�һ��
	//SystemCoreClock / 100000  10u�ж�һ��
	//SystemCoreClock / 1000000 1us�ж�һ��
	if(SysTick_Config(SystemCoreClock / 1000))
	{
		//LED_1(ON);
		while(1);
	}
	/*�رյδ�ʱ��*/
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

void Delay_us(__IO u32 nTime)
{
	 TimingDelay = nTime;
	 /*ʹ�ܵδ�ʱ��*/
	 SysTick->CTRL |= SysTick_CTRL_ENABLE;
	 while(TimingDelay !=0);
}
void Delay_ms(__IO u32 nTime)
{
	 TimingDelay = nTime;
	 /*ʹ�ܵδ�ʱ��*/
	 SysTick->CTRL |= SysTick_CTRL_ENABLE;
	 while(TimingDelay !=0);
}
void TimingDelay_Decrement(void)
{
	 if(TimingDelay != 0x00)
	 {
		 TimingDelay--;
	 }
   if(TimingDelay2 <= 5000)	 
	 {
		 TimingDelay2++;
	 }
	 else
	 {
		 TimingDelay2 = 0;
	 }
}
