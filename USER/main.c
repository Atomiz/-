/**
	***************************************************************************************************************
	*�ļ���main.c
	*���ߣ��ᳯ��
	*���ڣ�����
	*��飺������ںͳ�ʼ��
	***************************************************************************************************************
	*ע�⣺
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
	
	while(1)//һֱ����ָ��
	{
		for (i=0;i<255;i++)
		{
			USART_SendStr(USART1,"USART1����");	//TX��A9
			USART_SendStr(USART2,"USART2����");	//TX��A2
			USART_SendStr(USART3,"USART3����");	//TX��B10
			USART_SendStr(UART4,"UART4����");		//TX��C10
			USART_SendStr(UART5,"UART5����");		//TX��C12
			
			USART_Data_Send("ͨ��һ",6,DMA_USART1);
			Delay(1000000);
			USART_Data_Send("ͨ����",6,DMA_USART2);
			Delay(1000000);
			USART_Data_Send("ͨ����",6,DMA_USART3);
			Delay(1000000);
			USART_Data_Send("ͨ����",6,DMA_UART4);
			Delay(1000000);
		}
  }
}
