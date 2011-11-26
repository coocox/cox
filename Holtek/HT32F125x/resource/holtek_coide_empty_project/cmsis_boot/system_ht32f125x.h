/**************************************************************************//**
 * @file    system_ht32f125x.h
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Header File 
 *          for the Holtek HT32F125x Device Series
 * @version V1.00
 * @date    04/11/2011
 *
 * @note
 * Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup HT32F125x_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */

#ifndef __SYSTEM_HT32F125x_H
#define __SYSTEM_HT32F125x_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup HT32F125x_System_Includes
  * @{
  */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Exported_types
  * @{
  */

extern __IO uint32_t SystemCoreClock;  /*!< System Clock Frequency (Core Clock)          */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Exported_Functions
  * @{
  */

extern void SystemInit (void);
extern void SystemCoreClockUpdate(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_HT32F125x_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 Holtek Semiconductor Inc. *****END OF FILE****/
