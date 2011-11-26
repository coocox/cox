/*****************************************************************************//**
 * @file    ht32f125x_wdt.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of the WDT library.
 **********************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 *********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125x_WDT_H
#define __HT32F125x_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup WDT
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup WDT_Exported_Types WDT exported types
  * @{
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup WDT_Exported_Constants WDT exported constants
  * @{
  */

/* WDT prescaler */
#define WDT_PRESCALER_1                           ((u16)0x0000)
#define WDT_PRESCALER_2                           ((u16)0x1000)
#define WDT_PRESCALER_4                           ((u16)0x2000)
#define WDT_PRESCALER_8                           ((u16)0x3000)
#define WDT_PRESCALER_16                          ((u16)0x4000)
#define WDT_PRESCALER_32                          ((u16)0x5000)
#define WDT_PRESCALER_64                          ((u16)0x6000)
#define WDT_PRESCALER_128                         ((u16)0x7000)

#define IS_WDT_PRESCALER(PRESCALER)               ((PRESCALER == WDT_PRESCALER_1) || \
                                                   (PRESCALER == WDT_PRESCALER_2) || \
                                                   (PRESCALER == WDT_PRESCALER_4) || \
                                                   (PRESCALER == WDT_PRESCALER_8) || \
                                                   (PRESCALER == WDT_PRESCALER_16) || \
                                                   (PRESCALER == WDT_PRESCALER_32) || \
                                                   (PRESCALER == WDT_PRESCALER_64) || \
                                                   (PRESCALER == WDT_PRESCALER_128))


/* WDT Flag */
#define WDT_FLAG_UNDERFLOW                        ((u32)0x00000001)
#define WDT_FLAG_ERROR                            ((u32)0x00000002)

#define IS_WDT_FLAG(WDT_FLAG)                     ((WDT_FLAG == WDT_FLAG_UNDERFLOW) || \
                                                   (WDT_FLAG == WDT_FLAG_ERROR))


#define IS_WDT_RELOAD(WDTV)                       ((WDTV <= 0xFFF))

#define IS_WDT_DELTA(WDTD)                        ((WDTD <= 0xFFF))

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup WDT_Exported_Macro WDT exported macro
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup WDT_Exported_Functions WDT exported functions
  * @{
  */

void WDT_DeInit(void);
void WDT_IntConfig(ControlStatus NewState);
void WDT_ResetCmd(ControlStatus NewState);
void WDT_ProtectCmd(ControlStatus NewState);
void WDT_SetReloadValue(u16 WDTV);
u16 WDT_GetReloadValue(void);
void WDT_SetDeltaValue(u16 WDTD);
u16 WDT_GetDeltaValue(void);
void WDT_SetPrescaler(u16 WDT_PRESCALER);
u8 WDT_GetPrescaler(void);
void WDT_Restart(void);
FlagStatus WDT_GetFlagStatus (u32 WDT_FLAG);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

#endif /* __HT32F125x_WDT_H -------------------------------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */
