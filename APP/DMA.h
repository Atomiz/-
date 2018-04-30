#ifndef __DMA_H
#define __DMA_H


//#include "stm32f10x.h"
#include "system_conf.h"

#define RECEBUFF_SIZE 1035  //接收缓存大小设置为1KByte+11Byte

typedef struct {
uint8_t  DMA_USART1_RxBuffer[RECEBUFF_SIZE];     //接收数据缓冲数组
uint8_t  DMA_USART2_RxBuffer[RECEBUFF_SIZE];     //接收数据缓冲数组
uint8_t  DMA_USART3_RxBuffer[RECEBUFF_SIZE];     //接收数据缓冲数组
}DMA_USARTy_RxBuffer;

typedef struct {
   uint8_t  DMA_USART1_RxBufferTemp;   //声明接收一字节缓存变量
   uint16_t DMA_USART1_RxByteSize;     //定义RxByte为接收了字节数
   uint8_t  DMA_USART2_RxBufferTemp;   //声明接收一字节缓存变量
   uint16_t DMA_USART2_RxByteSize;     //定义RxByte为接收了字节数
   uint8_t  DMA_USART3_RxBufferTemp;   //声明接收一字节缓存变量
   uint16_t DMA_USART3_RxByteSize;     //定义RxByte为接收了字节数
}DMA_USARTy_RxBuffer_param;
typedef struct {
   FlagStatus DMA_USART1_RECE_FLAG_TC; 
   FlagStatus DMA_USART2_RECE_FLAG_TC;  
   FlagStatus DMA_USART3_RECE_FLAG_TC;   	
}DMA_USARTy_RECE_Flag;

void NVIC_Config(void);
void DMA_USART1_DataSand(void* SendBuff,u16 SendBuff_size);//USART1发送
void DMA_USART1_DataRece(void* SendBuff,u16 SendBuff_size);//USART1接收
void DMA_USART2_DataSand(void* SendBuff,u16 SendBuff_size);//USART2发送
void DMA_USART2_DataRece(void* SendBuff,u16 SendBuff_size);//USART2接收
void DMA_USART3_DataSand(void* SendBuff,u16 SendBuff_size);//USART3发送
void DMA_UART4_DataSand(void* SendBuff,u16 SendBuff_size);//UART4发送

#endif
