/**
  ******************************************************************************
  * File Name          : TIM.h
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  */

#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f4xx_ll_tim.h"
#include "main.h"


extern void _Error_Handler(char *, int);

void TIM3_Init(void);


#ifdef __cplusplus
}
#endif
#endif
