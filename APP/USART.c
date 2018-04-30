/**
	***************************************************************************************************************
	*文件：USART.c
	*作者：裴朝峰
	*日期：——
	*简介：提供STM32F103ZE的USART接口函数，支持DMA功能
	***************************************************************************************************************
	*注意：文件在2018/03/12修改。
	*删除了原来用于配置USART1和USART2的函数，使用新的函数替代，支持所有USARTx，在usart.h中设置需要打开的USARTx。
	*
	***************************************************************************************************************
*/

#include "usart.h"
uint32_t USART_DefaultBaudRate = 0;
extern DMA_USARTy_RxBuffer DMA_USARTy_RxBufferStruct;
extern DMA_USARTy_RxBuffer_param DMA_USARTy_RxBuffer_paramStruct;
extern DMA_USARTy_RECE_Flag DMA_USARTy_RECE_FlagStatus;

/*
 *函数名：	GPIO_USARTx_Config(USART_TypeDef* USARTx)
 *描述： 	USARTx端口配置
 *输入：		USART_TypeDef* USARTx
 *输出： 	无 
 */
void GPIO_USARTx_Config(USART_TypeDef* USARTx)
{
	if (USARTx == USART1)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		//USART1 TX->(PA.09) 	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);	
		//USART1 Rx->(PA.10)
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	}
	else if (USARTx == USART2)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		//USART1 TX->(PA-02) 	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);	
		//USART1 Rx->(PA-02)
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	}
	else if (USARTx == USART3)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		//USART1 TX->(PB-10) 	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);	
		//USART1 Rx->(PB-11)
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	}
	else if (USARTx == UART4)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		//USART1 TX->(PC-10) 	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOC,&GPIO_InitStructure);	
		//USART1 Rx->(PC-11)
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	}
	else if (USARTx == UART5)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		//USART1 TX->(PC-12) 	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOC,&GPIO_InitStructure);	
		//USART1 Rx->(PD-2)
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOD,&GPIO_InitStructure);
	}
}

/*
 *函数名：	Init_USARTx_Config(USART_TypeDef* USARTx,u32 BaudRate)
 *描述：		USARTx配置工作模式
 *输入：		USART_TypeDef* USARTx
 *输入：		BaudRate：波特率配置
 *输出：		无
 */
void Init_USARTx_Config(USART_TypeDef* USARTx,u32 BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate=BaudRate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USARTx,&USART_InitStructure);
  USART_Cmd(USARTx,ENABLE);	
}

/*
 *函数名：	void USART_Config(void)
 *描述：		USARTx的初始化程序，在usart.h中#define需要开启的USARTx，以及#define对应的波特率USARTx_BaudRate
 *输入：		无
 *输出：		无
 */
void USARTx_Init(void)
{
	/*使能DMA时钟	*/
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	#ifdef USART1_ENABLE
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);													//使能时钟， TX-PA9， RX-PA10
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
  	USART_DeInit(USART1);
	  GPIO_USARTx_Config(USART1);
	  Init_USARTx_Config(USART1,USART1_BaudRate);
	#endif
	
	#ifdef USART2_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE);													//使能时钟， TX-PA2， RX-PA3
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  	USART_DeInit(USART2);
	  GPIO_USARTx_Config(USART2);
	  Init_USARTx_Config(USART2,USART2_BaudRate);
	#endif
	
	#ifdef USART3_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 ,ENABLE);													//使能时钟， TX-PB10，RX-PB11
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  	USART_DeInit(USART3);
	  GPIO_USARTx_Config(USART3);
	  Init_USARTx_Config(USART3,USART3_BaudRate);
	#endif
	
	#ifdef UART4_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 ,ENABLE);													//使能时钟， TX-PC10，RX-PC11
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	 	USART_DeInit(UART4);
	  GPIO_USARTx_Config(UART4);
	  Init_USARTx_Config(UART4,UART4_BaudRate);
	#endif
	
	#ifdef UART5_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 ,ENABLE);		//使能时钟， TX-PC12，RX-PD2
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  	USART_DeInit(UART5);
	  GPIO_USARTx_Config(UART5);
	  Init_USARTx_Config(UART5,UART5_BaudRate);
	#endif
}

/*
 *函数名：	USART_SendByte(USART_TypeDef* USARTx, uint8_t Data)
 *描述：		发送单个字符
 *输入：		USARTx：串口号；Data：单个字符数据
 *输出：		无
 */
void USART_SendByte(USART_TypeDef* USARTx, uint8_t Data)
{
	//操作USART_DR寄存器发送单个数据
	USART_SendData(USARTx,Data);
	//等待发送寄存器TDR为空
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}

/*
 *函数名：	USART_SendStr(USART_TypeDef* USARTx,char *str)
 *描述：		发送字符串
 *输入：		USARTx：串口号；str：字符串数据
 *输出：		无
 */
void USART_SendStr(USART_TypeDef* USARTx,char *str)
{
	uint8_t i=0;
	do
	{
		USART_SendByte(USARTx,*(str+i));
		i++;
	}while(*(str+i)!='\0');
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}

/*print重定义*/
int fputc(int ch,FILE *f)
{
	USART_SendData(USART2,(unsigned char) ch);//由USART2发送printf内容
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	return(ch);
}

/*
 * 函数名：	USART_Data_Send(uint8_t *data,u16 LenghtSize)
 * 描述  ： 数据发送程序
 * 输入  ： *data：指向要发送数据的内容
 *          LenghtSize：数据长度
 *          USARTz：选择串口通信通道
 * 输出  ： 发送成功置位DataSendYesFla
 */
void USART_Data_Send(uint8_t *data,u16 LenghtSize,DMA_USARTy USARTz)
{
		if(USARTz == DMA_USART1) //启用DMA发送数据
		{
			while(DMA_GetCurrDataCounter(DMA1_Channel4)!=0);//等待当前 DMA 通道 1 剩余的待传输数据数目为0
			DMA_USART1_DataSand(data,LenghtSize);//启用DMA_USART1发送数据
		}
		else if(USARTz == DMA_USART2)
		{
			while(DMA_GetCurrDataCounter(DMA1_Channel7)!=0);//等待当前 DMA 通道 2 剩余的待传输数据数目为0
			DMA_USART2_DataSand(data,LenghtSize);//启用DMA_USART2发送数据
		}
		else if(USARTz == DMA_USART3)
		{
			while(DMA_GetCurrDataCounter(DMA1_Channel2)!=0);//等待当前 DMA 通道 3 剩余的待传输数据数目为0
			DMA_USART3_DataSand(data,LenghtSize);//启用DMA_USART3发送数据
		}		
		else if(USARTz == DMA_UART4)
		{
			while(DMA_GetCurrDataCounter(DMA2_Channel5)!=0);//等待当前 DMA 通道 4 剩余的待传输数据数目为0
			DMA_UART4_DataSand(data,LenghtSize);//启用DMA_UART4发送数据
		}		
}

/*
 * 函数名：	DataRece(USART_TypeDef* USARTx)
 * 描述  ： 	数据接收程序
 * 输入  ： 	USARTx：要接收数据的串口
 *          USARTz：选择串口通信
 * 输出  ： 发送成功置位DataReceYesFlag
 */
FlagStatus DataRece(DMA_USARTy USARTz) //数据接收
{
	FlagStatus bitstatus = RESET;
	extern __IO u32 TimingDelay2;
	/*接收数据*/
	if(USARTz == DMA_USART1)//串口接收的模式
	{
		SysTick->CTRL |= SysTick_CTRL_ENABLE;//开启滴答定时器
		DMA_USART1_DataRece(&DMA_USARTy_RxBuffer_paramStruct.DMA_USART1_RxBufferTemp,1);//向DMA申请数据接收,数据存放在DMA.h文件的RxBuffer的数据里，RxBufferTemp为缓冲临时数组
	  while(1) 
	  {
			 if(TimingDelay2 >= 2000)  //超时2000ms响应,则退出
		   {
				  bitstatus = RESET;
				  break;
			 }
		   if(DMA_USARTy_RECE_FlagStatus.DMA_USART1_RECE_FLAG_TC == SET) //判断接收完所有数据标志，即RECE_FLAG_TC为 1，则置位bitstatus，否则置0
	     {
			    //DMA_USART2_DataSand(DMA_USARTy_RxBufferStruct.DMA_USART1_RxBuffer,DMA_USARTy_RxBuffer_paramStruct.DMA_USART1_RxByteSize);//测试用
				  DMA_USARTy_RECE_FlagStatus.DMA_USART1_RECE_FLAG_TC = RESET;				   //置零接收完所有数据标志 
		      bitstatus = SET;
				  break ;
	      }          
	   }
		 SysTick->CTRL &=~ SysTick_CTRL_ENABLE;//禁用滴答定时器
		 TimingDelay2 = 0;
	 }
	else if(USARTz == DMA_USART2)
	{
		DMA_USART2_DataRece(&DMA_USARTy_RxBuffer_paramStruct.DMA_USART2_RxBufferTemp,1);//向DMA申请数据接收,数据存放在DMA.h文件的RxBuffer的数据里，RxBufferTemp为缓冲临时数组
    while(1) 
	  {
		   if(DMA_USARTy_RECE_FlagStatus.DMA_USART2_RECE_FLAG_TC == SET) //判断接收完所有数据标志，即RECE_FLAG_TC为 1，则置位bitstatus，否则置0
	     {
			    //DMA_USART2_DataSand(DMA_USARTy_RxBufferStruct.DMA_USART2_RxBuffer,DMA_USARTy_RxBuffer_paramStruct.DMA_USART2_RxByteSize);//测试用
				  DMA_USARTy_RECE_FlagStatus.DMA_USART2_RECE_FLAG_TC = RESET;				   //置零接收完所有数据标志 
		      bitstatus = SET;
				  break ;
	      }
	   }			
	}
	return bitstatus;
}
