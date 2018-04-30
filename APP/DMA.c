#include "DMA.h"

  DMA_USARTy_RxBuffer DMA_USARTy_RxBufferStruct;
  DMA_USARTy_RxBuffer_param DMA_USARTy_RxBuffer_paramStruct;
	DMA_USARTy_RECE_Flag DMA_USARTy_RECE_FlagStatus;
	
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructrue;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//NVIC�ж����ȼ���������Ϊ��1��
	/*--------------NVIC_DMA_USART1-------------------*/
	//����DMA�ж�����
	NVIC_InitStructrue.NVIC_IRQChannel = DMA1_Channel5_IRQn;//DMA1_5ͨ��
	NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructrue.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructrue);//��ʼ���ж�����
	/*--------------NVIC_DMA_USART2-------------------*/
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//NVIC�ж����ȼ���������Ϊ��1��
	//����DMA�ж�����
	NVIC_InitStructrue.NVIC_IRQChannel = DMA1_Channel6_IRQn;//DMA1_6ͨ��
	NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructrue.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructrue);//��ʼ���ж�����
	
}
//����
void DMA_USART1_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	/*�ر�DMAͨ��*/
	DMA_Cmd(DMA1_Channel4,ENABLE);
	/*�ָ�ȱʡֵ*/
  DMA_DeInit(DMA1_Channel4);
	//NVIC_Config(); //����DMA�ж�
	/*����DMAԴ���ڴ��ַ & �������ݼĴ�����ַ*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	/*�ڴ��ַ��Ҫ����ı�����ָ�룩*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*���򣺴��ڴ������*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*�����С��DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*�����ַ����*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*�ڴ��ַ����*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*�������ݵ�λ*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMAģʽ��һ�δ��䣬ѭ��=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*���ȼ�����*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*��ֹ�ڴ浽�ڴ洫��*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*��ʼ��Ĭ��ֵDMA1_Channel4*/
	DMA_DeInit(DMA1_Channel4); 
	/*����DMA1��4ͨ��*/
	DMA_Init(DMA1_Channel4,&DMA_InitStructrue);
	//������DMA��������
  USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA1_Channel4,ENABLE);//ʹ��DMA
	//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);//����DMA������ɺ�����ж�
}

void DMA_USART2_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	//NVIC_Config(); //����DMA�ж�
	/*����DMAԴ���ڴ��ַ & �������ݼĴ�����ַ*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
	/*�ڴ��ַ��Ҫ����ı�����ָ�룩*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*���򣺴��ڴ������*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*�����С��DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*�����ַ����*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*�ڴ��ַ����*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*�������ݵ�λ*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMAģʽ��һ�δ��䣬ѭ��=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*���ȼ�����*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*��ֹ�ڴ浽�ڴ洫��*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*��ʼ��Ĭ��ֵDMA1_Channel7*/
	DMA_DeInit(DMA1_Channel7); 
	/*����DMA1��7ͨ��*/
	DMA_Init(DMA1_Channel7,&DMA_InitStructrue);
	//������DMA��������
  USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA1_Channel7,ENABLE);//ʹ��DMA
	//DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);//����DMA������ɺ�����ж�
}

void DMA_USART3_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	//NVIC_Config(); //����DMA�ж�
	/*����DMAԴ���ڴ��ַ & �������ݼĴ�����ַ*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART3->DR);
	/*�ڴ��ַ��Ҫ����ı�����ָ�룩*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*���򣺴��ڴ������*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*�����С��DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*�����ַ����*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*�ڴ��ַ����*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*�������ݵ�λ*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMAģʽ��һ�δ��䣬ѭ��=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*���ȼ�����*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*��ֹ�ڴ浽�ڴ洫��*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*��ʼ��Ĭ��ֵDMA1_Channel2*/
	DMA_DeInit(DMA1_Channel2); 
	/*����DMA1��2ͨ��*/
	DMA_Init(DMA1_Channel2,&DMA_InitStructrue);
	//������DMA��������
  USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA1_Channel2,ENABLE);//ʹ��DMA
	//DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);//����DMA������ɺ�����ж�
}

void DMA_UART4_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	//NVIC_Config(); //����DMA�ж�
	/*����DMAԴ���ڴ��ַ & �������ݼĴ�����ַ*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&UART4->DR);
	/*�ڴ��ַ��Ҫ����ı�����ָ�룩*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*���򣺴��ڴ������*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*�����С��DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*�����ַ����*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*�ڴ��ַ����*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*�������ݵ�λ*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMAģʽ��һ�δ��䣬ѭ��=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*���ȼ�����*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*��ֹ�ڴ浽�ڴ洫��*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*��ʼ��Ĭ��ֵDMA2_Channel5*/
	DMA_DeInit(DMA2_Channel5); 
	/*����DMA2��5ͨ��*/
	DMA_Init(DMA2_Channel5,&DMA_InitStructrue);
	//������DMA��������
  USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA2_Channel5,ENABLE);//ʹ��DMA
	//DMA_ITConfig(DMA2_Channel5,DMA_IT_TC,ENABLE);//����DMA������ɺ�����ж�
}

//����
void DMA_USART1_DataRece(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	NVIC_Config();
	//USART_SendStr(USART1,"̽��2\t");
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//����DMAʱ��	
	//NVIC_Config(); //����DMA�ж�
	/*����DMAԴ���ڴ��ַ & �������ݼĴ�����ַ*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	/*�ڴ��ַ��Ҫ����ı�����ָ�룩*/
	//DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*���򣺴����赽�ڴ�*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralSRC;
	/*�����С��DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*�����ַ����*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*�ڴ��ַ����*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*�������ݵ�λ*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMAģʽ��һ�δ��䣬ѭ��=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*���ȼ�����*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*��ֹ�ڴ浽�ڴ洫��*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*��ʼ��Ĭ��ֵDMA1_Channel5*/
	DMA_DeInit(DMA1_Channel5); 
	/*����DMA1��5ͨ��*/
	DMA_Init(DMA1_Channel5,&DMA_InitStructrue);
	//������DMA��������
  USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
  
	DMA_Cmd(DMA1_Channel5,ENABLE);//ʹ��DMA
	//DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);//����DMA������ɺ�����ж�

}

////UASRT2����
//void DMA_USART2_DataSand(void* SendBuff,u16 SendBuff_size)
//{
//	DMA_InitTypeDef DMA_InitStructrue;
//	//NVIC_Config(); //����DMA�ж�
//	/*����DMAԴ���ڴ��ַ & �������ݼĴ�����ַ*/
//	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
//	/*�ڴ��ַ��Ҫ����ı�����ָ�룩*/
//	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
//	/*���򣺴��ڴ������*/
//	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
//	/*�����С��DMA_BufferSize = SENDBUFF_SIZE*/
//	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
//	/*�����ַ����*/
//	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	/*�ڴ��ַ����*/
//	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	/*�������ݵ�λ*/
//	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	/*�ڴ����ݵ�λ 8bit*/
//	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
//	/*DMAģʽ��һ�δ��䣬ѭ��=Circular*/
//	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
//	/*���ȼ�����*/
//	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
//	/*��ֹ�ڴ浽�ڴ洫��*/
//	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
//	/*��ʼ��Ĭ��ֵDMA1_Channel4*/
//	DMA_DeInit(DMA1_Channel7); 
//	/*����DMA1��4ͨ��*/
//	DMA_Init(DMA1_Channel7,&DMA_InitStructrue);
//			 //������DMA��������
//  USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
//  
//	DMA_Cmd(DMA1_Channel7,ENABLE);//ʹ��DMA
//	//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);//����DMA������ɺ�����ж�

//}

//UASRT2����
void DMA_USART2_DataRece(void* SendBuff,u16 SendBuff_size)
{
	
	DMA_InitTypeDef DMA_InitStructrue;
	NVIC_Config();//����DMA�ж�
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//����DMAʱ��	
	/*����DMAԴ���ڴ��ַ & �������ݼĴ�����ַ*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
	/*�ڴ��ַ��Ҫ����ı�����ָ�룩*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*���򣺴����赽�ڴ�*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralSRC;
	/*�����С��DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*�����ַ����*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*�ڴ��ַ����*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*�������ݵ�λ*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMAģʽ��һ�δ��䣬ѭ��=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*���ȼ�����*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*��ֹ�ڴ浽�ڴ洫��*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*��ʼ��Ĭ��ֵDMA1_Channel6*/
	DMA_DeInit(DMA1_Channel6); 
	/*����DMA1��6ͨ��*/
	DMA_Init(DMA1_Channel6,&DMA_InitStructrue);
	//������DMA��������
  USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
  
	DMA_Cmd(DMA1_Channel6,ENABLE);//ʹ��DMA
	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC,ENABLE);//����DMA������ɺ�����ж�

}
