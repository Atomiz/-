/**
	***************************************************************************************************************
	*文件：USART.c
	*作者：裴朝峰
	*日期：——
	*简介：无
	***************************************************************************************************************
	*注意：修改于2018/03/12
	***************************************************************************************************************
*/
#ifndef  __USART_H
#define  __USART_H

//#include "stm32f10x.h"
#include "stdio.h"
#include "system_conf.h"

typedef enum {
	DMA_USART1 = 1,
	DMA_USART2 = 2,
	DMA_USART3 = 3,
	DMA_UART4 = 4,
	DMA_UART5 = 5			//UART5没有DMA通道
}DMA_USARTy;

void Init_USARTx_Config(USART_TypeDef* USARTx,u32 BaudRate);
void GPIO_USARTx_Config(USART_TypeDef* USARTx);
void USART_SendByte(USART_TypeDef* USARTx, uint8_t Data);
void USART_SendStr(USART_TypeDef* USARTx, char *str);
void USARTx_Init(void);
void USART_Data_Send(uint8_t *data,u16 LenghtSize,DMA_USARTy USARTz);
FlagStatus DataRece(DMA_USARTy USARTz);
int fputc(int ch,FILE *f);
#endif

/*USARTx初始化，以及默认的波特率*/
#define USART1_ENABLE
#define USART1_BaudRate 9600

#define USART2_ENABLE
#define USART2_BaudRate 9600

#define USART3_ENABLE
#define USART3_BaudRate 9600

#define UART4_ENABLE
#define UART4_BaudRate 9600

#define UART5_ENABLE
#define UART5_BaudRate 9600
