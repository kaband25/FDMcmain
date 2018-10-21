/**
  ******************************************************************************
  * File Name          : dma.c
  * Description        : This file provides code for the configuration
  *                      of all the requested memory to memory DMA transfers.
  ******************************************************************************
  */

#include "dma.h"

void DMA_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

  NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA2_Stream7_IRQn);

  LL_DMA_InitTypeDef DMA_InitStruct;
  DMA_InitStruct.Channel = LL_DMA_CHANNEL_4;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  DMA_InitStruct.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
  DMA_InitStruct.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_FULL;
  DMA_InitStruct.MemBurst = LL_DMA_MBURST_SINGLE;
  DMA_InitStruct.PeriphBurst = LL_DMA_PBURST_SINGLE;
  LL_DMA_Init(DMA2,LL_DMA_STREAM_7,&DMA_InitStruct);
}
