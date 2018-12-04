/**
  ******************************************************************************
  * File Name          : func.h
  * Description        : This file provides code for all the functions necessary to acquire measurements
  ******************************************************************************
  */

#include "func.h"
uint16_t START_MEAS = 501;
uint16_t RESEND_MEAS = 502;

uint16_t numberOfMeasurements=0;
uint16_t meArr[10000];
uint8_t cobsArr[20000];
uint32_t meCRC[202];
uint8_t cobsCRC[802];
uint16_t ArrItr=0;

uint16_t buff1=0;

uint8_t Param[202];
uint8_t Param_[200];
uint8_t *pParam = Param;
const uint8_t *opParam =Param;
void GetParams(uint8_t _DR)
{
	        if(_DR == 0x00)
			{
	        	*pParam++=_DR;
	        	UnStuffData(&Param,7,&Param_);

	        	uint16_t whatToDo =((uint16_t)Param_[0]<<8)|Param_[1];

	        	if(whatToDo==START_MEAS)
	        	{
					uint16_t frequency =((uint16_t)Param_[2]<<8)|Param_[3];
					numberOfMeasurements=((uint16_t)Param_[4]<<8)|Param_[5];

					SetFrequency(frequency);

					ClearParams();
					StartMeasurements();
	        	}
	        	else if(whatToDo==RESEND_MEAS)
	        	{
	        		uint16_t numberOfPackets =((uint16_t)Param_[2]<<8)|Param_[3];
	        		UnStuffData(&Param,(numberOfPackets*2)+5,&Param_);


	        	    EnableDMATransfer(cobsArr,((uint16_t)Param_[4]<<8)|Param_[5],106);



	        		ClearParams();
	        	}
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
		ArrItr++;
	}
    else
	{
		StopMeasurements();

		PackData();

		EnableDMATransfer(cobsArr,0,(numberOfMeasurements*2)+(6*(numberOfMeasurements/50)));
	}
}
void PackData(void)
{
	for(int i=0;i<(numberOfMeasurements/50);i++)
	{
		if(i)StuffData(&meArr[i*50],104,&cobsArr[i*106]); // if i>0 cobsArr will be filled with 102 bytes so I have to add 2
		else StuffData(&meArr,104,&cobsArr); // if i=0 then to cobsArr to start at 0

		for(int j=i*50;j<(i*50)+50;j++)
		{
			AddToCRC(meArr[j]);
		}
		GetCRC(i);
	}
	StuffData(&meCRC,(numberOfMeasurements/50)*4,&cobsCRC);
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
	 memset(meArr,0,sizeof(meArr));
     memset(cobsArr,0,sizeof(cobsArr));

	 LL_SPI_Enable(SPI1);
	 LL_TIM_CC_EnableChannel(TIM3,1|4);
	 LL_TIM_EnableIT_CC1(TIM3);
	 LL_TIM_EnableCounter(TIM3);
}
void EnableDMATransfer(uint8_t * _array,uint32_t _which,uint32_t _howMany)
{
	while(DMA2_Stream7->NDTR); //wait until previous transfer has ended

	DMA2->HIFCR = DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CFEIF7| DMA_HIFCR_CHTIF7|DMA_HIFCR_CTCIF7|DMA_HIFCR_CTEIF7;
	DMA2_Stream7->PAR = (uint32_t)&USART1->DR;

	if (_which==0)
		{
			DMA2_Stream7->M0AR = &_array[0];
		}

	if(_which)
		{
			DMA2_Stream7->M0AR = &_array[(_which-1)*106];
		}
	DMA2_Stream7->NDTR = _howMany;
	DMA2_Stream7->CR |= DMA_SxCR_EN;
	USART1->CR3 |= USART_CR3_DMAT;
}
void AddToCRC(uint16_t _M)
{
	WRITE_REG(CRC->DR, _M);
}
void GetCRC(uint16_t _itr)
{
	uint32_t var=READ_REG(CRC->DR);
	cobsArr[(_itr*102)]=var>>24;
	WRITE_REG(CRC->CR, CRC_CR_RESET);
}
