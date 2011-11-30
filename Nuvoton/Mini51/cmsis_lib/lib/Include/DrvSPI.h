//*****************************************************************************
//
//! \file DrvSPI.h
//! \brief Defines and Macros for SPI API.
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//
//*****************************************************************************
#ifndef __DRVSPI_H__
#define __DRVSPI_H__

#include "MINI51.h"
#include "SysInfra.h"

//*****************************************************************************
//
//! Macro, type and constant definitions
//
//*****************************************************************************
#define DRVSPI_MAJOR_NUM 1
#define DRVSPI_MINOR_NUM 01
#define DRVSPI_BUILD_NUM 001

#define DRVSPI_VERSION_NUM    _SYSINFRA_VERSION(DRVSPI_MAJOR_NUM,DRVSPI_MINOR_NUM,DRVSPI_BUILD_NUM)  

//*****************************************************************************
//
//! Define Error Code
//
//*****************************************************************************

// 
//!    E_DRVSPI_ERR_BUSY                      SPI is busy
//
#define E_DRVSPI_ERR_BUSY                 _SYSINFRA_ERRCODE(TRUE,  MODULE_ID_DRVSPI, 0)

#define SPI_CHECK_INUSE				g_sSpiHandler.bInUse == 0 					
#define SPI_CHECK_BIT_LENGTH		(i32BitLength >=1) && (i32BitLength <= 32) 	
#define SPI_CHECK_BURST_SUS			(i32Interval >= 2) && (i32Interval <= 17)	
#define SPI_CHECK_BRUST_CNT			(i32BurstCnt >= 1) && (i32BurstCnt <= 2)	
#define SPI_CHECK_CALLBACK_PR		pfnCallback != NULL							
#define SPI_CHECK_SET_DATAREG_NUM	u32DataCount <= 2								
#define SPI_CHECK_BYTE_REORDER_MIX	SPI->CNTRL_BITS.TX_BIT_LEN == 0
#define SPI_CHECK_BYTE_REORDER		SPI->CNTRL_BITS.TX_BIT_LEN % 8 == 0

//*****************************************************************************
//
//! SPI Setting
//
//*****************************************************************************
typedef enum {
    eDRVSPI_MASTER=0,
    eDRVSPI_SLAVE=1
} E_DRVSPI_MODE;

typedef enum {
    eDRVSPI_TYPE0=0x000,
    eDRVSPI_TYPE1=0x004,
    eDRVSPI_TYPE2=0x002,
    eDRVSPI_TYPE3=0x006,
    eDRVSPI_TYPE4=0x800,
    eDRVSPI_TYPE5=0x804,
    eDRVSPI_TYPE6=0x802,
    eDRVSPI_TYPE7=0x806
} E_DRVSPI_TRANS_TYPE;

typedef enum {
    eDRVSPI_MSB_FIRST=0,
    eDRVSPI_LSB_FIRST=1
} E_DRVSPI_ENDIAN;

typedef enum {
    eDRVSPI_BYTE_REORDER_SUSPEND_DISABLE=0,
    eDRVSPI_BYTE_REORDER_SUSPEND=1,
    eDRVSPI_BYTE_REORDER=2,
    eDRVSPI_BYTE_SUSPEND=3
} E_DRVSPI_BYTE_REORDER;

typedef enum {
    eDRVSPI_EDGE_TRIGGER,
    eDRVSPI_LEVEL_TRIGGER
} E_DRVSPI_SSLTRIG;

typedef enum {
    eDRVSPI_ACTIVE_LOW_FALLING,
    eDRVSPI_ACTIVE_HIGH_RISING
} E_DRVSPI_SS_ACT_TYPE;

typedef void (*PFN_DRVSPI_CALLBACK)(uint32_t userData);

//*****************************************************************************
//
//! Define Function Prototypes
//
//*****************************************************************************
int32_t DrvSPI_Open(E_DRVSPI_MODE eMode, E_DRVSPI_TRANS_TYPE eType, int32_t i32BitLength);
void DrvSPI_Close(void);
void DrvSPI_SetEndian(E_DRVSPI_ENDIAN eEndian);
int32_t DrvSPI_SetBitLength(int32_t i32BitLength);
int32_t DrvSPI_SetByteReorder(E_DRVSPI_BYTE_REORDER eOption);
int32_t DrvSPI_SetSuspendCycle(int32_t i32Interval);
void DrvSPI_SetTriggerMode(E_DRVSPI_SSLTRIG eSSTriggerMode);
void DrvSPI_SetSlaveSelectActiveLevel(E_DRVSPI_SS_ACT_TYPE eSSActType);
uint8_t DrvSPI_GetLevelTriggerStatus(void);
void DrvSPI_EnableAutoSS(void);
void DrvSPI_DisableAutoSS(void);
void DrvSPI_SetSS(void);
void DrvSPI_ClrSS(void);
uint8_t DrvSPI_IsBusy(void);
int32_t DrvSPI_BurstTransfer(int32_t i32BurstCnt, int32_t i32Interval);
uint32_t DrvSPI_SetClockFreq(uint32_t u32Clock1, uint32_t u32Clock2);
uint32_t DrvSPI_GetClock1Freq(void);
uint32_t DrvSPI_GetClock2Freq(void);
void DrvSPI_SetVariableClockFunction(uint8_t bEnable, uint32_t u32Pattern);
void DrvSPI_EnableInt(PFN_DRVSPI_CALLBACK pfnCallback, uint32_t u32UserData);
void DrvSPI_DisableInt(void);
uint32_t DrvSPI_GetIntFlag(void);
void DrvSPI_ClrIntFlag(void);
uint8_t DrvSPI_SingleRead(uint32_t *pu32Data);
uint8_t DrvSPI_SingleWrite(uint32_t *pu32Data);
uint8_t DrvSPI_BurstRead(uint32_t *pu32Buf);
uint8_t DrvSPI_BurstWrite(uint32_t *pu32Buf);
uint32_t DrvSPI_DumpRxRegister(uint32_t *pu32Buf, uint32_t u32DataCount);
uint32_t DrvSPI_SetTxRegister(uint32_t *pu32Buf, uint32_t u32DataCount);
void DrvSPI_SetGo(void);
void DrvSPI_ClrGo(void);
int32_t DrvSPI_SetFIFOMode(uint8_t bEnable, int32_t i32Interval);
uint8_t DrvSPI_IsRxEmpty(void);
uint8_t DrvSPI_IsRxFull(void);
uint8_t DrvSPI_IsTxEmpty(void);
uint8_t DrvSPI_IsTxFull(void);
void DrvSPI_EnableDivOne(void);
void DrvSPI_DisableDivOne(void);
void DrvSPI_Enable3Wire(void);
void DrvSPI_Disable3Wire(void);
void DrvSPI_3WireAbort(void);
void DrvSPI_Enable3WireStartInt(PFN_DRVSPI_CALLBACK pfnCallback, uint32_t u32UserData);
void DrvSPI_Disable3WireStartInt(void);
uint32_t DrvSPI_Get3WireStartIntFlag(void);
void DrvSPI_Clr3WireStartIntFlag(void);
uint32_t DrvSPI_GetVersion(void);

#endif
