/**
  ******************************************************************************
  * File Name          : CRC.h
  * Description        : This file provides code for the configuration
  *                      of the CRC instances.
  ******************************************************************************
  */

#ifndef __crc_H
#define __crc_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f4xx_ll_crc.h"
#include "main.h"

extern void _Error_Handler(char *, int);

void CRC_Init(void);

#ifdef __cplusplus
}
#endif
#endif
