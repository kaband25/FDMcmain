/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  */

#ifndef __spi_H
#define __spi_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_ll_spi.h"
#include "main.h"

extern void _Error_Handler(char *, int);

void SPI1_Init(void);
uint16_t ReceiveData();


#ifdef __cplusplus
}
#endif
#endif
