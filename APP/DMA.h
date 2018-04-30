#ifndef __DMA_H
#define __DMA_H


//#include "stm32f10x.h"
#include "system_conf.h"

#define RECEBUFF_SIZE 1035  //���ջ����С����Ϊ1KByte+11Byte

typedef struct {
uint8_t  DMA_USART1_RxBuffer[RECEBUFF_SIZE];     //�������ݻ�������
uint8_t  DMA_USART2_RxBuffer[RECEBUFF_SIZE];     //�������ݻ�������
uint8_t  DMA_USART3_RxBuffer[RECEBUFF_SIZE];     //�������ݻ�������
}DMA_USARTy_RxBuffer;

typedef struct {
   uint8_t  DMA_USART1_RxBufferTemp;   //��������һ�ֽڻ������
   uint16_t DMA_USART1_RxByteSize;     //����RxByteΪ�������ֽ���
   uint8_t  DMA_USART2_RxBufferTemp;   //��������һ�ֽڻ������
   uint16_t DMA_USART2_RxByteSize;     //����RxByteΪ�������ֽ���
   uint8_t  DMA_USART3_RxBufferTemp;   //��������һ�ֽڻ������
   uint16_t DMA_USART3_RxByteSize;     //����RxByteΪ�������ֽ���
}DMA_USARTy_RxBuffer_param;
typedef struct {
   FlagStatus DMA_USART1_RECE_FLAG_TC; 
   FlagStatus DMA_USART2_RECE_FLAG_TC;  
   FlagStatus DMA_USART3_RECE_FLAG_TC;   	
}DMA_USARTy_RECE_Flag;

void NVIC_Config(void);
void DMA_USART1_DataSand(void* SendBuff,u16 SendBuff_size);//USART1����
void DMA_USART1_DataRece(void* SendBuff,u16 SendBuff_size);//USART1����
void DMA_USART2_DataSand(void* SendBuff,u16 SendBuff_size);//USART2����
void DMA_USART2_DataRece(void* SendBuff,u16 SendBuff_size);//USART2����
void DMA_USART3_DataSand(void* SendBuff,u16 SendBuff_size);//USART3����
void DMA_UART4_DataSand(void* SendBuff,u16 SendBuff_size);//UART4����

#endif
