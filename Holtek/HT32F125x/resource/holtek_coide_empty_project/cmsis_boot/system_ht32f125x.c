/**************************************************************************//**
 * @file    HT32F125x/system_ht32f125x.c
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Source File
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

/** @addtogroup HT32F125x_System_Private_Includes
  * @{
  */

#include "ht32f125x.h"

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Private_Defines
  * @{
  */
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
//  <h> HT32F125x Clock Configuration
//    <h> High Speed Internal RC Oscillator Configuration (HSI)
//      <e0>    HSI Enable
//                <i> Default HSI = ENABLE
//      </e>
//    </h>
//
//    <h> High Speed External Crystal Oscillator Configuration (HSE)
//      <e1>    HSE Enable
//                <i> Default HSE = DISABLE
//      </e>
//    </h>
//
//    <h> PLL Configuration
//      <e2>    PLL Enable
//                <i> Default PLL = DISABLE
//        <o3>  PLL Clock Source
//                <0=> CK_HSE
//                <1=> CK_HSI
//                <i> Default PLL clock source = CK_HSI
//                <i> PLL source clock must be in range of 4 MHz to 16 MHz
//        <o4>  PLL Feedback Clock Divider (NF2): 1 ~ 64
//                <1-64:1>
//                <i> PLL feedback clock = PLL clock source x NF2
//                <i> PLL feedback clock must be in range of 64 MHz to 144 MHz
//        <o5>  PLL Output Clock Divider (NO2)
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <i> PLL output clock = PLL feedback clock / NO2
//                <i> PLL output clock must be in range of 8 MHz to 144 MHz
//      </e>
//    </h>
//
//    <h> SystemCoreClock Configuration (CK_AHB)
//      <o6>    SystemCoreClock Source
//                <0=> CK_PLL
//                <2=> CK_HSE
//                <3=> CK_HSI
//                <i> Default SystemCoreClock source = CK_HSI
//      <o7>    SystemCoreClock Source Divider
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <i> Default SystemCoreClock source divider = 1
//    </h>
//
//    <h> Backup Domain Isolation Configuration
//      <o8>    Isolation State
//                <0=> ENABLE
//                <1=> DISABLE
//                <i> Default Isolation = ENABLE
//    </h>
//  </h>
*/
#define HSI_ENABLE    (1)       /*!< 0: DISABLE, 1: ENABLE                */
#define HSE_ENABLE    (1)       /*!< 0: DISABLE, 1: ENABLE                */
#define PLL_ENABLE    (1)       /*!< 0: DISABLE, 1: ENABLE                */
#define PLL_CLK_SRC   (0)       /*!< 0: HSE,  1: HSI                      */
#define PLL_NF2_DIV   (18)      /*!< 1~64: DIV1~DIV64                     */
#define PLL_NO2_DIV   (0)       /*!< 0: DIV1, 1: DIV2, 2: DIV4, 3: DIV8   */
#define HCLK_SRC      (0)       /*!< 0: PLL,  1: PLL, 2: HSE, 3: HSI      */
#define HCLK_DIV      (1)       /*!< 0: DIV1, 1: DIV2, 2: DIV4, 3: DIV8   */
#define BAKUP_ISO     (1)       /*!< 0: ENABLE, 1: DISABLE                */

/**
 * @brief Check HSI frequency
 */
#if (HSI_VALUE != 8000000UL)
  #error "CK_HSI clock issue: must be 8 MHz!"
#endif

/**
 * @brief Check HSE frequency
 */
#if ((HSE_VALUE < 4000000UL) || (HSE_VALUE > 16000000UL))
  #error "CK_HSE clock issue: must be in range of 4 MHz to 16 MHz!"
#endif

/**
 * @brief CK_PLL definition
 */
#if (PLL_ENABLE == 1)
  /* Get CK_VCO frequency */
  #if (PLL_CLK_SRC == 1)
    #if (HSI_ENABLE == 0)
      #error "CK_PLL clock source issue: HSI is not enable"
    #else
      #define __CK_VCO    (HSI_VALUE * (PLL_NF2_DIV & 0x1F))     /*!< Select HSI as PLL source              */
    #endif
  #else
    #if (HSE_ENABLE == 0)
      #error "CK_PLL clock source issue: HSE is not enable!"
    #else
      #define __CK_VCO    (HSE_VALUE * (PLL_NF2_DIV & 0x1F))     /*!< Select HSE as PLL source              */
    #endif
  #endif

  /* Check CK_VCO frequency */
  #if ((__CK_VCO < 64000000) || (__CK_VCO > 144000000))
    #error "CK_VCO clock issue: must be in range of 64 MHz to 144 MHz!"
  #endif

  #define __CK_PLL    (__CK_VCO >> PLL_NO2_DIV)                 /*!< Get CK_PLL frequency                   */

  /* Check CK_PLL frequency */
  #if ((__CK_PLL < 8000000UL) || (__CK_PLL > 144000000UL))
    #error "CK_PLL clock issue: must be in range of 8 MHz to 144 MHz!"
  #endif
#endif

/**
 * @brief CK_SYS definition
 */
#if (HCLK_SRC == 2)
  #if (HSE_ENABLE == 1)
    #define __CK_SYS    HSE_VALUE             /*!< Select HSE as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: HSE is not enable!"
  #endif
#elif (HCLK_SRC == 3)
  #if (HSI_ENABLE == 1)
    #define __CK_SYS    HSI_VALUE             /*!< Select HSI as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: HSI is not enable!"
  #endif
#else
  #if (PLL_ENABLE == 1)
    #define __CK_SYS    __CK_PLL              /*!< Select PLL as CK_SYS source                              */
  #else
    #error "CK_SYS clock source issue: PLL is not enable!"
  #endif
#endif

/**
 * @brief CK_AHB definition
 */
#define __CK_AHB    (__CK_SYS >> HCLK_DIV)    /*!< Get CK_AHB frequency                                     */

/* Check CK_AHB frequency */
#if ((__CK_AHB < 1000000UL) || (__CK_AHB > 72000000UL))
  #error "CK_AHB clock issue: must be in range of 1 MHz to 72 MHz!"
#endif

/**
 * @brief CKCU & Flash register definition
 */
#if (HT32F_LIB_DEBUG == 0)
  #define CKCU_GCFGR    CKCU->GCFGR                       /*!< global clock configuration register          */
  #define CKCU_GCCR     CKCU->GCCR                        /*!< global clock control register                */
  #define CKCU_GCSR     CKCU->GCSR                        /*!< global clock status register                 */
  #define CKCU_PLLCFGR  CKCU->PLLCFGR                     /*!< PLL configuration register                   */
  #define CKCU_AHBCFGR  CKCU->AHBCFGR                     /*!< AHB configuration register                   */
  #define CKCU_LPCR     CKCU->LPCR                        /*!< Low Power Control Register                   */
  #define FLASH_CFCR    FLASH->CFCR                       /*!< flash pre-fetch control register             */
#else
  #define CKCU_GCFGR    (*(vu32 *)(CKCU_BASE + 0x000))    /*!< global clock configuration register          */
  #define CKCU_GCCR     (*(vu32 *)(CKCU_BASE + 0x004))    /*!< global clock control register                */
  #define CKCU_GCSR     (*(vu32 *)(CKCU_BASE + 0x008))    /*!< global clock status register                 */
  #define CKCU_PLLCFGR  (*(vu32 *)(CKCU_BASE + 0x018))    /*!< PLL configuration register                   */
  #define CKCU_AHBCFGR  (*(vu32 *)(CKCU_BASE + 0x020))    /*!< AHB configuration register                   */
  #define CKCU_LPCR     (*(vu32 *)(CKCU_BASE + 0x300))    /*!< Low Power Control Register                   */
  #define FLASH_CFCR    (*(vu32 *)(FLASH_BASE + 0x200))   /*!< flash pre-fetch control register             */
#endif

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Private_Variables
  * @{
  */
__IO uint32_t SystemCoreClock = __CK_AHB;   /*!< SystemCoreClock = CK_AHB                                   */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup HT32F125x_System_Private_Functions
  * @{
  */
            
/**
  * @brief  Setup the microcontroller system.
  *         Initializes the system clocks and the embedded Flash.
  * @note   This function should be used after reset.
  * @retval None
  */  
void SystemInit (void)
{
  CKCU_LPCR = BAKUP_ISO;                              /*!< configure Backup domain isolation                */
  
  /**
   * @brief HSE initiation
   */
#if (HSE_ENABLE == 1)
  SetBit_BB((u32)(&CKCU_GCCR), 10);                   /*!< enable HSE                                       */
  while (!GetBit_BB((u32)(&CKCU_GCSR), 2));           /*!< wait for HSE ready                               */
#endif

  /**
   * @brief CK_AHB prescaler initiation
   */
  CKCU_AHBCFGR = HCLK_DIV;

  /**
   * @brief PLL initiation
   */
#if (HCLK_SRC == 2)
  CKCU_GCCR = ((CKCU_GCCR & 0xFFFFFFFC) | 2UL);               /*!< select CK_SYS source as HSE              */
  while ((CKCU_GCCR & 3UL) != 2);                             /*!< wait for clock switch complete           */
#elif (HCLK_SRC != 3)
  #if (PLL_ENABLE == 1)
    #if (PLL_CLK_SRC == 1)
      SetBit_BB((u32)(&CKCU_GCFGR), 8);                       /*!< select PLL source as HSI                 */
    #else
      ResetBit_BB((u32)(&CKCU_GCFGR), 8);                     /*!< select PLL source as HSE                 */
    #endif

    CKCU_PLLCFGR = (PLL_NF2_DIV << 23) | (PLL_NO2_DIV << 21); /*!< set PLL divider                          */
    SetBit_BB((u32)(&CKCU_GCCR), 9);                          /*!< enable PLL                               */
    while(!GetBit_BB((u32)(&CKCU_GCSR), 1));                  /*!< wait for PLL ready                       */

    #if (__CK_AHB > 48000000)
      FLASH_CFCR = (((FLASH_CFCR) & 0xFFFFFFF0) | 3UL);       /*!< FLASH wait state = 2                     */
    #elif (__CK_AHB > 24000000)
      FLASH_CFCR = (((FLASH_CFCR) & 0xFFFFFFF0) | 2UL);       /*!< FLASH wait state = 1                     */
    #endif

    CKCU_GCCR = ((CKCU_GCCR & 0xFFFFFFFC) | 1UL);             /*!< select CK_SYS source as CK_PLL           */
    while ((CKCU_GCCR & 3UL) != 1);                           /*!< wait for clock switch complete           */
  #endif  
#endif

  /**
   * @brief HSI power down
   */
#if ((HSI_ENABLE == 0) && (HCLK_SRC != 3) && ((PLL_ENABLE == 0) || (PLL_CLK_SRC == 0)))
  ResetBit_BB((u32)(&CKCU_GCCR), 11);
#endif
}

/**
  * @brief  Update SystemCoreClock
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  u32 SystemCoreClockDiv = CKCU_AHBCFGR & 3UL;
  u32 PllFeedbackClockDiv = ((CKCU_PLLCFGR >> 23) == 0) ? (64) : (CKCU_PLLCFGR >> 23);
  u32 PllOutputClockDiv = (CKCU_PLLCFGR >> 21) & 3UL;

  /* Get system core clock according to global clock control & configuration registers */
  if ((CKCU_GCCR & 3UL) == 3)
  {
    SystemCoreClock = HSI_VALUE >> SystemCoreClockDiv;
  }
  else if ((CKCU_GCCR & 3UL) == 2)
  {
    SystemCoreClock = HSE_VALUE >> SystemCoreClockDiv;
  }
  else
  {
    if (GetBit_BB((u32)(&CKCU_GCFGR), 8))
    {
      SystemCoreClock = ((HSI_VALUE * PllFeedbackClockDiv) >> PllOutputClockDiv) >> SystemCoreClockDiv;
    }
    else
    {
      SystemCoreClock = ((HSE_VALUE * PllFeedbackClockDiv) >> PllOutputClockDiv) >> SystemCoreClockDiv;
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 Holtek Semiconductor Inc. *****END OF FILE****/
