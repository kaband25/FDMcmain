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
void PackData(void);

void EnableDMATransfer(uint8_t * _array,uint32_t _which,uint32_t _howMany);

void AddToCRC(uint16_t _M);
void GetCRC(uint16_t _itr);

#ifdef __cplusplus
}
#endif
#endif
