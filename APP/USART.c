/**
	***************************************************************************************************************
	*�ļ���USART.c
	*���ߣ��ᳯ��
	*���ڣ�����
	*��飺�ṩSTM32F103ZE��USART�ӿں�����֧��DMA����
	***************************************************************************************************************
	*ע�⣺�ļ���2018/03/12�޸ġ�
	*ɾ����ԭ����������USART1��USART2�ĺ�����ʹ���µĺ��������֧������USARTx����usart.h��������Ҫ�򿪵�USARTx��
	*
	***************************************************************************************************************
*/

#include "usart.h"
uint32_t USART_DefaultBaudRate = 0;
extern DMA_USARTy_RxBuffer DMA_USARTy_RxBufferStruct;
extern DMA_USARTy_RxBuffer_param DMA_USARTy_RxBuffer_paramStruct;
extern DMA_USARTy_RECE_Flag DMA_USARTy_RECE_FlagStatus;

/*
 *��������	GPIO_USARTx_Config(USART_TypeDef* USARTx)
 *������ 	USARTx�˿�����
 *���룺		USART_TypeDef* USARTx
 *����� 	�� 
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
 *��������	Init_USARTx_Config(USART_TypeDef* USARTx,u32 BaudRate)
 *������		USARTx���ù���ģʽ
 *���룺		USART_TypeDef* USARTx
 *���룺		BaudRate������������
 *�����		��
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
 *��������	void USART_Config(void)
 *������		USARTx�ĳ�ʼ��������usart.h��#define��Ҫ������USARTx���Լ�#define��Ӧ�Ĳ�����USARTx_BaudRate
 *���룺		��
 *�����		��
 */
void USARTx_Init(void)
{
	/*ʹ��DMAʱ��	*/
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	#ifdef USART1_ENABLE
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);													//ʹ��ʱ�ӣ� TX-PA9�� RX-PA10
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
  	USART_DeInit(USART1);
	  GPIO_USARTx_Config(USART1);
	  Init_USARTx_Config(USART1,USART1_BaudRate);
	#endif
	
	#ifdef USART2_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE);													//ʹ��ʱ�ӣ� TX-PA2�� RX-PA3
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  	USART_DeInit(USART2);
	  GPIO_USARTx_Config(USART2);
	  Init_USARTx_Config(USART2,USART2_BaudRate);
	#endif
	
	#ifdef USART3_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 ,ENABLE);													//ʹ��ʱ�ӣ� TX-PB10��RX-PB11
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  	USART_DeInit(USART3);
	  GPIO_USARTx_Config(USART3);
	  Init_USARTx_Config(USART3,USART3_BaudRate);
	#endif
	
	#ifdef UART4_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 ,ENABLE);													//ʹ��ʱ�ӣ� TX-PC10��RX-PC11
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	 	USART_DeInit(UART4);
	  GPIO_USARTx_Config(UART4);
	  Init_USARTx_Config(UART4,UART4_BaudRate);
	#endif
	
	#ifdef UART5_ENABLE
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 ,ENABLE);		//ʹ��ʱ�ӣ� TX-PC12��RX-PD2
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  	USART_DeInit(UART5);
	  GPIO_USARTx_Config(UART5);
	  Init_USARTx_Config(UART5,UART5_BaudRate);
	#endif
}

/*
 *��������	USART_SendByte(USART_TypeDef* USARTx, uint8_t Data)
 *������		���͵����ַ�
 *���룺		USARTx�����ںţ�Data�������ַ�����
 *�����		��
 */
void USART_SendByte(USART_TypeDef* USARTx, uint8_t Data)
{
	//����USART_DR�Ĵ������͵�������
	USART_SendData(USARTx,Data);
	//�ȴ����ͼĴ���TDRΪ��
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}

/*
 *��������	USART_SendStr(USART_TypeDef* USARTx,char *str)
 *������		�����ַ���
 *���룺		USARTx�����ںţ�str���ַ�������
 *�����		��
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

/*print�ض���*/
int fputc(int ch,FILE *f)
{
	USART_SendData(USART2,(unsigned char) ch);//��USART2����printf����
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	return(ch);
}

/*
 * ��������	USART_Data_Send(uint8_t *data,u16 LenghtSize)
 * ����  �� ���ݷ��ͳ���
 * ����  �� *data��ָ��Ҫ�������ݵ�����
 *          LenghtSize�����ݳ���
 *          USARTz��ѡ�񴮿�ͨ��ͨ��
 * ���  �� ���ͳɹ���λDataSendYesFla
 */
void USART_Data_Send(uint8_t *data,u16 LenghtSize,DMA_USARTy USARTz)
{
		if(USARTz == DMA_USART1) //����DMA��������
		{
			while(DMA_GetCurrDataCounter(DMA1_Channel4)!=0);//�ȴ���ǰ DMA ͨ�� 1 ʣ��Ĵ�����������ĿΪ0
			DMA_USART1_DataSand(data,LenghtSize);//����DMA_USART1��������
		}
		else if(USARTz == DMA_USART2)
		{
			while(DMA_GetCurrDataCounter(DMA1_Channel7)!=0);//�ȴ���ǰ DMA ͨ�� 2 ʣ��Ĵ�����������ĿΪ0
			DMA_USART2_DataSand(data,LenghtSize);//����DMA_USART2��������
		}
		else if(USARTz == DMA_USART3)
		{
			while(DMA_GetCurrDataCounter(DMA1_Channel2)!=0);//�ȴ���ǰ DMA ͨ�� 3 ʣ��Ĵ�����������ĿΪ0
			DMA_USART3_DataSand(data,LenghtSize);//����DMA_USART3��������
		}		
		else if(USARTz == DMA_UART4)
		{
			while(DMA_GetCurrDataCounter(DMA2_Channel5)!=0);//�ȴ���ǰ DMA ͨ�� 4 ʣ��Ĵ�����������ĿΪ0
			DMA_UART4_DataSand(data,LenghtSize);//����DMA_UART4��������
		}		
}

/*
 * ��������	DataRece(USART_TypeDef* USARTx)
 * ����  �� 	���ݽ��ճ���
 * ����  �� 	USARTx��Ҫ�������ݵĴ���
 *          USARTz��ѡ�񴮿�ͨ��
 * ���  �� ���ͳɹ���λDataReceYesFlag
 */
FlagStatus DataRece(DMA_USARTy USARTz) //���ݽ���
{
	FlagStatus bitstatus = RESET;
	extern __IO u32 TimingDelay2;
	/*��������*/
	if(USARTz == DMA_USART1)//���ڽ��յ�ģʽ
	{
		SysTick->CTRL |= SysTick_CTRL_ENABLE;//�����δ�ʱ��
		DMA_USART1_DataRece(&DMA_USARTy_RxBuffer_paramStruct.DMA_USART1_RxBufferTemp,1);//��DMA�������ݽ���,���ݴ����DMA.h�ļ���RxBuffer�������RxBufferTempΪ������ʱ����
	  while(1) 
	  {
			 if(TimingDelay2 >= 2000)  //��ʱ2000ms��Ӧ,���˳�
		   {
				  bitstatus = RESET;
				  break;
			 }
		   if(DMA_USARTy_RECE_FlagStatus.DMA_USART1_RECE_FLAG_TC == SET) //�жϽ������������ݱ�־����RECE_FLAG_TCΪ 1������λbitstatus��������0
	     {
			    //DMA_USART2_DataSand(DMA_USARTy_RxBufferStruct.DMA_USART1_RxBuffer,DMA_USARTy_RxBuffer_paramStruct.DMA_USART1_RxByteSize);//������
				  DMA_USARTy_RECE_FlagStatus.DMA_USART1_RECE_FLAG_TC = RESET;				   //����������������ݱ�־ 
		      bitstatus = SET;
				  break ;
	      }          
	   }
		 SysTick->CTRL &=~ SysTick_CTRL_ENABLE;//���õδ�ʱ��
		 TimingDelay2 = 0;
	 }
	else if(USARTz == DMA_USART2)
	{
		DMA_USART2_DataRece(&DMA_USARTy_RxBuffer_paramStruct.DMA_USART2_RxBufferTemp,1);//��DMA�������ݽ���,���ݴ����DMA.h�ļ���RxBuffer�������RxBufferTempΪ������ʱ����
    while(1) 
	  {
		   if(DMA_USARTy_RECE_FlagStatus.DMA_USART2_RECE_FLAG_TC == SET) //�жϽ������������ݱ�־����RECE_FLAG_TCΪ 1������λbitstatus��������0
	     {
			    //DMA_USART2_DataSand(DMA_USARTy_RxBufferStruct.DMA_USART2_RxBuffer,DMA_USARTy_RxBuffer_paramStruct.DMA_USART2_RxByteSize);//������
				  DMA_USARTy_RECE_FlagStatus.DMA_USART2_RECE_FLAG_TC = RESET;				   //����������������ݱ�־ 
		      bitstatus = SET;
				  break ;
	      }
	   }			
	}
	return bitstatus;
}
