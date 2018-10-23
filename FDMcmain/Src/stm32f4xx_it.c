/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "main.h"
#include "dma.h"


void TIM3_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_CC1(TIM3))
	{
		MakeMeasurements();
		LL_TIM_ClearFlag_CC1(TIM3);
	}
}

void USART1_IRQHandler(void)
{
    if(LL_USART_IsActiveFlag_RXNE(USART1))
	{
		GetParams(USART1->DR);
		LL_USART_ClearFlag_RXNE(USART1);
	}
}

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  while (1)
  {
  }
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  while (1)
  {
  }
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{

}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
}
