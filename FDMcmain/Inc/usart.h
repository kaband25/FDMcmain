/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  */

#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "main.h"
#include <stdint.h>
#include <stddef.h>


#define StartBlock()	(code_ptr = dst++, code = 1)
#define FinishBlock()	(*code_ptr = code)

extern void _Error_Handler(char *, int);

void USART1_UART_Init(void);
size_t UnStuffData(const uint8_t *ptr, size_t length, uint8_t *dst);

#ifdef __cplusplus
}
#endif
#endif
