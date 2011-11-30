//*****************************************************************************
//
//! \file DrvFMC.h
//! \brief Defines and Macros for FMC API.
//! \version v1.02.002
//! \date 09/05/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//*****************************************************************************
#ifndef _NANO100_FMC_H_
#define _NANO100_FMC_H_

//*****************************************************************************
//
//! Include related headers
//
//*****************************************************************************
#include "mini51.h"

//*****************************************************************************
//
//!  Define Version number
//
//*****************************************************************************
#define FMC_MAJOR_NUM		1
#define FMC_MINOR_NUM		00
#define FMC_BUILD_NUM		1

//*****************************************************************************
//
//!  Version define with SysInfra
//
//*****************************************************************************
#define DRVFMC_VERSION_NUM     _SYSINFRA_VERSION(FMC_MAJOR_NUM, FMC_MINOR_NUM, FMC_BUILD_NUM)

//*****************************************************************************
//
//!  Define Error Code
//
//*****************************************************************************
#define E_DRVFMC_ERR_ISP_FAIL   0xFFFF0010

//*****************************************************************************
//
//!  Define parameter
//
//*****************************************************************************
#define CONFIG0         0x00300000
#define CONFIG1         0x00300004 

//*****************************************************************************
//
//!  Flash Boot Selector 
//
//*****************************************************************************
typedef enum { E_FMC_APROM = 0, E_FMC_LDROM = 1} E_FMC_BOOTSELECT;

//*****************************************************************************
//
//!  Define FMC functions prototype
//
//*****************************************************************************
void 	 DrvFMC_EnableISP(void);
void     DrvFMC_DisableISP(void);
void 	 DrvFMC_BootSelect(E_FMC_BOOTSELECT boot);
E_FMC_BOOTSELECT DrvFMC_GetBootSelect(void);
void 	 DrvFMC_EnableLDUpdate(void);
void 	 DrvFMC_DisableLDUpdate(void);
void 	 DrvFMC_EnableConfigUpdate(void);
void     DrvFMC_DisableConfigUpdate(void);
void 	 DrvFMC_EnablePowerSaving(void);
void     DrvFMC_DisablePowerSaving(void);
void     DrvFMC_EnableLowSpeedMode(void);
void     DrvFMC_DisableLowSpeedMode(void);
int32_t  DrvFMC_ReadCID(uint32_t * u32data);
int32_t  DrvFMC_ReadDID(uint32_t * u32data);
int32_t  DrvFMC_ReadPID(uint32_t * u32data);
int32_t  DrvFMC_ReadUID(int index, uint32_t * u32data);
int32_t  DrvFMC_Write(uint32_t u32addr, uint32_t u32data);
int32_t  DrvFMC_Read(uint32_t u32addr, uint32_t * u32data);
int32_t  DrvFMC_Erase(uint32_t u32addr);
int32_t  DrvFMC_WriteConfig(uint32_t u32data0, uint32_t u32data1);
uint32_t DrvFMC_ReadDataFlashBaseAddr(void);

#endif

