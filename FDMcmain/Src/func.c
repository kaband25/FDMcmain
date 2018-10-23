/**
  ******************************************************************************
  * File Name          : func.h
  * Description        : This file provides code for all the functions necessary to acquire measurements
  ******************************************************************************
  */

#include "func.h"

uint16_t numberOfMeasurements=0;
uint16_t numberOfRepeats=0;

uint16_t meArr[10000];
uint8_t cobsArr[20000];
uint16_t cobsArr2[20000];
uint16_t ArrItr=0;

uint8_t Param[8];
uint8_t Param_[6];
uint8_t *pParam = Param;
const uint8_t *opParam =Param;

void GetParams(uint8_t _DR)
{
	        if(_DR == 0x00)
			{
				*pParam++=_DR;
				UnStuffData(&Param,7,&Param_);

				uint16_t frequency =((uint16_t)Param_[0]<<8)|Param_[1];
				numberOfMeasurements=((uint16_t)Param_[2]<<8)|Param_[3];
				numberOfRepeats=(((uint16_t)Param_[4]<<8)|Param_[5])-1;

				SetFrequency(frequency);

	            ClearParams();
				StartMeasurements();
			}
			else
			{
				*pParam++=_DR;
			}
}

void ClearParams(void)
{
	memset(Param_,0,sizeof(Param_));
	memset(Param,0,sizeof(Param));
	pParam=opParam;
}

void MakeMeasurements(void)
{
	if(ArrItr<numberOfMeasurements)
	{
		meArr[ArrItr]=ReceiveData();
		//AddToCRC(uint32_t)meArr[ArrItr]);
		ArrItr++;
	}
    else
	{
		StopMeasurements();
        //GetCRC();
		StuffData(&meArr,(2*numberOfMeasurements),&cobsArr);

		EnableDMATransfer();

		if(numberOfRepeats-1)
		{
			while(DMA2_Stream7->NDTR);
			StartMeasurements();
			numberOfRepeats--;
		}
	}
}

void StopMeasurements(void)
{
	LL_TIM_DisableCounter(TIM3);
	LL_TIM_CC_DisableChannel(TIM3,1|4);
	LL_TIM_DisableIT_CC1(TIM3);
	LL_SPI_Disable(SPI1);
	ArrItr=0;
}

void StartMeasurements(void)
{
	 LL_SPI_Enable(SPI1);
	 LL_TIM_CC_EnableChannel(TIM3,1|4);
	 LL_TIM_EnableIT_CC1(TIM3);
	 LL_TIM_EnableCounter(TIM3);
}

void EnableDMATransfer(void)
{
	DMA2->HIFCR = DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CFEIF7| DMA_HIFCR_CHTIF7|DMA_HIFCR_CTCIF7|DMA_HIFCR_CTEIF7;
	DMA2_Stream7->PAR = (uint32_t)&USART1->DR;
	DMA2_Stream7->M0AR = (uint32_t)&cobsArr[0];
	DMA2_Stream7->NDTR = (numberOfMeasurements*2)+2;
	DMA2_Stream7->CR |= DMA_SxCR_EN;
	USART1->CR3 |= USART_CR3_DMAT;
}

void AddToCRC(uint16_t _M)
{
	WRITE_REG(CRC->DR, _M);
}
void GetCRC(void)
{
	uint32_t Var = READ_REG(CRC->DR);
	uint8_t * pVar = Var;
	for(int i=1;i<5;i++)
	{
		meArr[(2*numberOfMeasurements)+i]=pVar++;
	}
	WRITE_REG(CRC->CR, CRC_CR_RESET);
}
