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


uint16_t meArr[10000];
uint8_t cobsArr[500];
uint8_t order[8];
uint8_t order_[6];
uint8_t *pOrder = order;
uint16_t ArrI=0;
uint16_t frequency=0;
uint16_t numberOfMeasurements=0;
uint16_t numberOfRepeats=0;

void TIM3_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_CC1(TIM3))
	{
		meArr[ArrI]=ReceiveData();
		if(ArrI<numberOfMeasurements)
		{
			ArrI++;
		}
		else
		{
			LL_TIM_DisableCounter(TIM3);
			LL_TIM_CC_DisableChannel(TIM3,1|4);
			LL_TIM_DisableIT_CC1(TIM3);
			LL_SPI_Disable(SPI1);

			StuffData(&meArr,(2*numberOfMeasurements)+1,&cobsArr);

			DMA2->HIFCR = DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CFEIF7| DMA_HIFCR_CHTIF7|DMA_HIFCR_CTCIF7|DMA_HIFCR_CTEIF7;
			DMA2_Stream7->PAR = (uint32_t)&USART1->DR;
			DMA2_Stream7->M0AR = (uint32_t)&cobsArr[0];
			DMA2_Stream7->NDTR = (numberOfMeasurements*2)+3;
			DMA2_Stream7->CR |= DMA_SxCR_EN;
			USART1->CR3 |= USART_CR3_DMAT;

			ArrI=0;
		}
		LL_TIM_ClearFlag_CC1(TIM3);
	}
}

void USART1_IRQHandler(void)
{
    if(LL_USART_IsActiveFlag_RXNE(USART1))
	{
		if(USART1->DR == 0x00)
		{
			*pOrder++=USART1->DR;
			UnStuffData(&order,6,&order_);

			frequency =((uint16_t)order_[0]<<8)|order_[1];
			numberOfMeasurements=((uint16_t)order_[2]<<8)|order_[3];
			numberOfRepeats=((uint16_t)order_[4]<<8)|order_[4];

			LL_SPI_Enable(SPI1);
			LL_TIM_CC_EnableChannel(TIM3,1|4);
			LL_TIM_EnableIT_CC1(TIM3);
			LL_TIM_EnableCounter(TIM3);
		}
		else
		{
			*pOrder++=USART1->DR;
		}
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
