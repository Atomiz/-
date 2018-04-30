/**
	***************************************************************************************************************
	*文件：main.c
	*作者：裴朝峰
	*日期：——
	*简介：程序入口和初始化
	***************************************************************************************************************
	*注意：
	***************************************************************************************************************
*/

#include "system_conf.h"

long int i;
u16 n;
extern FlagStatus Img2Tz_Cmd(uint8_t BufferID);

void Delay(__IO u32 nCount)
{
  for(nCount=nCount; nCount != 0; nCount--);
} 

int main(void)
{
	unsigned char i;
	SysTick_Init();
	USARTx_Init();
	
	while(1)//一直发送指令
	{
		for (i=0;i<255;i++)
		{
			USART_SendStr(USART1,"USART1串口");	//TX：A9
			USART_SendStr(USART2,"USART2串口");	//TX：A2
			USART_SendStr(USART3,"USART3串口");	//TX：B10
			USART_SendStr(UART4,"UART4串口");		//TX：C10
			USART_SendStr(UART5,"UART5串口");		//TX：C12
			
			USART_Data_Send("通道一",6,DMA_USART1);
			Delay(1000000);
			USART_Data_Send("通道二",6,DMA_USART2);
			Delay(1000000);
			USART_Data_Send("通道三",6,DMA_USART3);
			Delay(1000000);
			USART_Data_Send("通道四",6,DMA_UART4);
			Delay(1000000);
		}
  }
}
