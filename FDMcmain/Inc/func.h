/**
  ******************************************************************************
  * File Name          : func.h
  * Description        : This file provides code for all the functions necessary to acquire measurements
  ******************************************************************************
  */

#ifndef __crc_H
#define __crc_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

void GetParams(uint8_t _DR);
void ClearParams(void);

void StartMeasurements(void);
void StopMeasurements(void);
void MakeMeasurements(void);

void EnableDMATransfer(void);

void AddToCRC(uint16_t _M);
void GetCRC(void);

#ifdef __cplusplus
}
#endif
#endif
