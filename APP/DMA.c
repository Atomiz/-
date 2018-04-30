#include "DMA.h"

  DMA_USARTy_RxBuffer DMA_USARTy_RxBufferStruct;
  DMA_USARTy_RxBuffer_param DMA_USARTy_RxBuffer_paramStruct;
	DMA_USARTy_RECE_Flag DMA_USARTy_RECE_FlagStatus;
	
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructrue;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//NVIC中断优先级分组设置为第1组
	/*--------------NVIC_DMA_USART1-------------------*/
	//配置DMA中断向量
	NVIC_InitStructrue.NVIC_IRQChannel = DMA1_Channel5_IRQn;//DMA1_5通道
	NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructrue.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructrue);//初始化中断配置
	/*--------------NVIC_DMA_USART2-------------------*/
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//NVIC中断优先级分组设置为第1组
	//配置DMA中断向量
	NVIC_InitStructrue.NVIC_IRQChannel = DMA1_Channel6_IRQn;//DMA1_6通道
	NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructrue.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructrue);//初始化中断配置
	
}
//发送
void DMA_USART1_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	/*关闭DMA通道*/
	DMA_Cmd(DMA1_Channel4,ENABLE);
	/*恢复缺省值*/
  DMA_DeInit(DMA1_Channel4);
	//NVIC_Config(); //配置DMA中断
	/*设置DMA源：内存地址 & 串口数据寄存器地址*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	/*内存地址（要传输的变量的指针）*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*方向：从内存带外设*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*传输大小：DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*外设地址不增*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*内存地址自增*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*外设数据单位*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMA模式：一次传输，循环=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*优先级：中*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*禁止内存到内存传输*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*初始化默认值DMA1_Channel4*/
	DMA_DeInit(DMA1_Channel4); 
	/*配置DMA1的4通道*/
	DMA_Init(DMA1_Channel4,&DMA_InitStructrue);
	//串口向DMA发出请求
  USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA1_Channel4,ENABLE);//使能DMA
	//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);//配置DMA发送完成后产生中断
}

void DMA_USART2_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	//NVIC_Config(); //配置DMA中断
	/*设置DMA源：内存地址 & 串口数据寄存器地址*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
	/*内存地址（要传输的变量的指针）*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*方向：从内存带外设*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*传输大小：DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*外设地址不增*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*内存地址自增*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*外设数据单位*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMA模式：一次传输，循环=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*优先级：中*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*禁止内存到内存传输*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*初始化默认值DMA1_Channel7*/
	DMA_DeInit(DMA1_Channel7); 
	/*配置DMA1的7通道*/
	DMA_Init(DMA1_Channel7,&DMA_InitStructrue);
	//串口向DMA发出请求
  USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA1_Channel7,ENABLE);//使能DMA
	//DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);//配置DMA发送完成后产生中断
}

void DMA_USART3_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	//NVIC_Config(); //配置DMA中断
	/*设置DMA源：内存地址 & 串口数据寄存器地址*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART3->DR);
	/*内存地址（要传输的变量的指针）*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*方向：从内存带外设*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*传输大小：DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*外设地址不增*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*内存地址自增*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*外设数据单位*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMA模式：一次传输，循环=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*优先级：中*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*禁止内存到内存传输*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*初始化默认值DMA1_Channel2*/
	DMA_DeInit(DMA1_Channel2); 
	/*配置DMA1的2通道*/
	DMA_Init(DMA1_Channel2,&DMA_InitStructrue);
	//串口向DMA发出请求
  USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA1_Channel2,ENABLE);//使能DMA
	//DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);//配置DMA发送完成后产生中断
}

void DMA_UART4_DataSand(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	//NVIC_Config(); //配置DMA中断
	/*设置DMA源：内存地址 & 串口数据寄存器地址*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&UART4->DR);
	/*内存地址（要传输的变量的指针）*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*方向：从内存带外设*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
	/*传输大小：DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*外设地址不增*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*内存地址自增*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*外设数据单位*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMA模式：一次传输，循环=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*优先级：中*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*禁止内存到内存传输*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*初始化默认值DMA2_Channel5*/
	DMA_DeInit(DMA2_Channel5); 
	/*配置DMA2的5通道*/
	DMA_Init(DMA2_Channel5,&DMA_InitStructrue);
	//串口向DMA发出请求
  USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
  
	DMA_Cmd(DMA2_Channel5,ENABLE);//使能DMA
	//DMA_ITConfig(DMA2_Channel5,DMA_IT_TC,ENABLE);//配置DMA发送完成后产生中断
}

//接收
void DMA_USART1_DataRece(void* SendBuff,u16 SendBuff_size)
{
	DMA_InitTypeDef DMA_InitStructrue;
	NVIC_Config();
	//USART_SendStr(USART1,"探针2\t");
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//开启DMA时钟	
	//NVIC_Config(); //配置DMA中断
	/*设置DMA源：内存地址 & 串口数据寄存器地址*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	/*内存地址（要传输的变量的指针）*/
	//DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*方向：从外设到内存*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralSRC;
	/*传输大小：DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*外设地址不增*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*内存地址自增*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*外设数据单位*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMA模式：一次传输，循环=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*优先级：中*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*禁止内存到内存传输*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*初始化默认值DMA1_Channel5*/
	DMA_DeInit(DMA1_Channel5); 
	/*配置DMA1的5通道*/
	DMA_Init(DMA1_Channel5,&DMA_InitStructrue);
	//串口向DMA发出请求
  USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
  
	DMA_Cmd(DMA1_Channel5,ENABLE);//使能DMA
	//DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);//配置DMA发送完成后产生中断

}

////UASRT2发送
//void DMA_USART2_DataSand(void* SendBuff,u16 SendBuff_size)
//{
//	DMA_InitTypeDef DMA_InitStructrue;
//	//NVIC_Config(); //配置DMA中断
//	/*设置DMA源：内存地址 & 串口数据寄存器地址*/
//	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
//	/*内存地址（要传输的变量的指针）*/
//	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
//	/*方向：从内存带外设*/
//	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralDST;
//	/*传输大小：DMA_BufferSize = SENDBUFF_SIZE*/
//	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
//	/*外设地址不增*/
//	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	/*内存地址自增*/
//	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	/*外设数据单位*/
//	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	/*内存数据单位 8bit*/
//	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
//	/*DMA模式：一次传输，循环=Circular*/
//	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
//	/*优先级：中*/
//	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
//	/*禁止内存到内存传输*/
//	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
//	/*初始化默认值DMA1_Channel4*/
//	DMA_DeInit(DMA1_Channel7); 
//	/*配置DMA1的4通道*/
//	DMA_Init(DMA1_Channel7,&DMA_InitStructrue);
//			 //串口向DMA发出请求
//  USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
//  
//	DMA_Cmd(DMA1_Channel7,ENABLE);//使能DMA
//	//DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);//配置DMA发送完成后产生中断

//}

//UASRT2接收
void DMA_USART2_DataRece(void* SendBuff,u16 SendBuff_size)
{
	
	DMA_InitTypeDef DMA_InitStructrue;
	NVIC_Config();//配置DMA中断
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//开启DMA时钟	
	/*设置DMA源：内存地址 & 串口数据寄存器地址*/
	DMA_InitStructrue.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
	/*内存地址（要传输的变量的指针）*/
	DMA_InitStructrue.DMA_MemoryBaseAddr = (u32)SendBuff;
	/*方向：从外设到内存*/
	DMA_InitStructrue.DMA_DIR = DMA_DIR_PeripheralSRC;
	/*传输大小：DMA_BufferSize = SENDBUFF_SIZE*/
	DMA_InitStructrue.DMA_BufferSize = SendBuff_size;
	/*外设地址不增*/
	DMA_InitStructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*内存地址自增*/
	DMA_InitStructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*外设数据单位*/
	DMA_InitStructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructrue.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	/*DMA模式：一次传输，循环=Circular*/
	DMA_InitStructrue.DMA_Mode = DMA_Mode_Normal;
	/*优先级：中*/
	DMA_InitStructrue.DMA_Priority = DMA_Priority_Medium;
	/*禁止内存到内存传输*/
	DMA_InitStructrue.DMA_M2M = DMA_M2M_Disable;
	/*初始化默认值DMA1_Channel6*/
	DMA_DeInit(DMA1_Channel6); 
	/*配置DMA1的6通道*/
	DMA_Init(DMA1_Channel6,&DMA_InitStructrue);
	//串口向DMA发出请求
  USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
  
	DMA_Cmd(DMA1_Channel6,ENABLE);//使能DMA
	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC,ENABLE);//配置DMA发送完成后产生中断

}
