/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "DMA.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */
	extern DMA_USARTy_RxBuffer DMA_USARTy_RxBufferStruct;
	extern DMA_USARTy_RxBuffer_param DMA_USARTy_RxBuffer_paramStruct;
	extern DMA_USARTy_RECE_Flag DMA_USARTy_RECE_FlagStatus;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
		TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
/*以下为测试参考程序，可以按照意愿更改*/
void DMA1_Channel5_IRQHandler(void)
{
	//判断DMA是否接收完成一帧数据
	static u16 RxCount = 0;           //定义RxCount为接收计数变量	

	if(DMA_GetFlagStatus(DMA1_FLAG_TC5)==SET)
	{
		DMA_Cmd(DMA1_Channel5,DISABLE);//禁止DMA通道5*/
		/*----------判断帧头----------*/
		for(;;)
		{
				DMA_USARTy_RxBufferStruct.DMA_USART1_RxBuffer[RxCount] = DMA_USARTy_RxBuffer_paramStruct.DMA_USART1_RxBufferTemp;//转存数据
				//USART_SendData(USART1,RxCount);//测试用-用于发送当前的RxCount值
				if(DMA_USARTy_RxBufferStruct.DMA_USART1_RxBuffer[RxCount] == '\0')  
				{
					DMA_USARTy_RECE_FlagStatus.DMA_USART1_RECE_FLAG_TC = SET;
					DMA_USARTy_RxBuffer_paramStruct.DMA_USART1_RxByteSize = RxCount;//记录结束接收次数值
					RxCount = 0;//清零接收计数值
					return;//退出中断程序
				}
				RxCount++;//计数值自增
				DMA_ClearFlag(DMA1_FLAG_TC5);//清除中断标志
		    DMA_USART1_DataRece(&DMA_USARTy_RxBuffer_paramStruct.DMA_USART1_RxBufferTemp,1);//继续接收下一帧数据
		}
			//接下来清除中断标志，继续接收下一帧数据
		
	}
}

/*以下为测试参考程序，可以按照意愿更改*/
void DMA1_Channel6_IRQHandler(void)
{
	//判断DMA是否接收完成一帧数据
	static u16 RxCount = 0;           //定义RxCount为接收计数变量	

	if(DMA_GetFlagStatus(DMA1_FLAG_TC6)==SET)
	{
		DMA_Cmd(DMA1_Channel6,DISABLE);//禁止DMA通道5*/
		/*----------判断帧头----------*/
		for(;;)
		{
				DMA_USARTy_RxBufferStruct.DMA_USART2_RxBuffer[RxCount] = DMA_USARTy_RxBuffer_paramStruct.DMA_USART2_RxBufferTemp;//转存数据
				//USART_SendData(USART1,RxCount);//测试用-用于发送当前的RxCount值
				if(DMA_USARTy_RxBufferStruct.DMA_USART2_RxBuffer[RxCount] == '\0')  
				{
					DMA_USARTy_RECE_FlagStatus.DMA_USART2_RECE_FLAG_TC = SET;
					DMA_USARTy_RxBuffer_paramStruct.DMA_USART2_RxByteSize = RxCount;//记录结束接收次数值
					RxCount = 0;//清零接收计数值
					return;//退出中断程序
				}
				RxCount++;//计数值自增
				DMA_ClearFlag(DMA1_FLAG_TC6);//清除中断标志
		    DMA_USART2_DataRece(&DMA_USARTy_RxBuffer_paramStruct.DMA_USART2_RxBufferTemp,1);//继续接收下一帧数据
		}
			//接下来清除中断标志，继续接收下一帧数据
		
	}
 
}


/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
