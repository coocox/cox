//*****************************************************************************
//
//! \file DrvI2C.h
//! \brief Defines and Macros for I2C API.
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.    
//
//*****************************************************************************
#ifndef _DRVI2C_H
#define _DRVI2C_H

#include "MINI51.h"

//*****************************************************************************
//
//!
//! Define Version number   
//!
//
//*****************************************************************************
#define DRVI2C_MAJOR_NUM    1
#define DRVI2C_MINOR_NUM    00
#define DRVI2C_BUILD_NUM    001

//*****************************************************************************
//
//!
//! Version define with SysInfra    
//!
//
//*****************************************************************************
#define DRVI2C_VERSION_NUM                                                     \  
         _SYSINFRA_VERSION(DRVI2C_MAJOR_NUM, DRVI2C_MINOR_NUM, DRVI2C_BUILD_NUM)

//*****************************************************************************
//
//!
//! Define Error Code     
//!
//
//*****************************************************************************
#define E_DRVI2C_ERR_ARGUMENT   _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVI2C, 1)

typedef void (*I2C_CALLBACK)(uint32_t status);

//*****************************************************************************
//
//!
//! Define I2C Call back function type   
//!
//
//*****************************************************************************
typedef enum
{
    I2CFUNC   = 0,
    ARBITLOSS = 1,
    BUSERROR  = 2,
    TIMEOUT   = 3
} E_I2C_CALLBACK_TYPE;

//*****************************************************************************
//
//!
//! Define I2C Call back function Data Struct  
//!
//
//*****************************************************************************
typedef struct
{
    I2C_CALLBACK    I2CCallBackFn;
    I2C_CALLBACK    ArbitLossCallBackFn;
    I2C_CALLBACK    BusErrCallBackFn;
    I2C_CALLBACK    TimeoutCallBackFn;

} I2C_CALLBACK_T;

//*****************************************************************************
//
//!
//! Define I2C functions prototype  
//!
//
//*****************************************************************************
void     DrvI2C_ClearIntFlag(void);
void     DrvI2C_ClearTimeoutFlag(void);
int32_t  DrvI2C_Close(void);
void     DrvI2C_Ctrl(uint8_t start, uint8_t stop, uint8_t intFlag, uint8_t ack);

int32_t  DrvI2C_DisableInt(void);

int32_t  DrvI2C_EnableInt(void);

uint32_t DrvI2C_GetClockFreq(void);
uint8_t  DrvI2C_GetIntFlag(void);
uint32_t DrvI2C_GetStatus(void);
uint32_t DrvI2C_GetVersion(void);

int32_t  DrvI2C_InstallCallback(E_I2C_CALLBACK_TYPE Type, I2C_CALLBACK callbackfn);

int32_t  DrvI2C_Open(uint32_t u32BusClock);

uint8_t  DrvI2C_ReadData(void);

int32_t  DrvI2C_SetAddress(uint8_t slaveNo, uint8_t slave_addr, uint8_t GC_Flag);
int32_t  DrvI2C_SetAddressMask(uint8_t slaveNo, uint8_t slaveAddrMask);
int32_t  DrvI2C_SetClockFreq(uint32_t u32BusClock);
int32_t  DrvI2C_SetTimeoutCounter(int32_t i32enable, uint8_t u8div4);

int32_t  DrvI2C_UninstallCallBack(E_I2C_CALLBACK_TYPE Type);

void     DrvI2C_WriteData(uint8_t u8data);

#endif

