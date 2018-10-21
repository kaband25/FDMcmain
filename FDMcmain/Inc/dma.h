/**
  ******************************************************************************
  * File Name          : dma.h
  * Description        : This file contains all the function prototypes for
  *                      the dma.c file
  ******************************************************************************
*/
#ifndef __dma_H
#define __dma_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_ll_dma.h"
#include "main.h"

extern void _Error_Handler(char*, int);
void DMA_Init(void);
#ifdef __cplusplus
}
#endif

#endif
