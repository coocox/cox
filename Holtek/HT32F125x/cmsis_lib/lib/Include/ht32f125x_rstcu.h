/*********************************************************************************************************//**
 * @file    ht32f125x_rstcu.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of the Reset Control Unit library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125x_RSTCU_H
#define __HT32F125x_RSTCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup RSTCU
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Exported_Types RSTCU exported types
  * @{
  */

/**
 * @brief Enumeration of Global reset status.
 */
typedef enum
{
  RSTCU_FLAG_SYSRST = 0,
  RSTCU_FLAG_EXTRST,
  RSTCU_FLAG_WDTRST,
  RSTCU_FLAG_PORST
} RSTCU_RSTF_TypeDef;

/**
  * @}
  */  /* End of RSTCU_Exported_Types group */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Exported_Constants RSTCU exported constants
  * @{
  */

/*  Definitions of APB peripheral 0 reset */
#define RSTCU_APBRST0_I2C         ((u32)0x1 << 0)
#define RSTCU_APBRST0_SPI         ((u32)0x1 << 4)
#define RSTCU_APBRST0_USART       ((u32)0x1 << 8)
#define RSTCU_APBRST0_AFIO        ((u32)0x1 << 14)
#define RSTCU_APBRST0_EXTI        ((u32)0x1 << 15)
#define RSTCU_APBRST0_PA          ((u32)0x1 << 16)
#define RSTCU_APBRST0_PB          ((u32)0x1 << 17)

#define IS_RSTCU_APBRST0(PERIPH)  ((PERIPH == RSTCU_APBRST0_I2C) || \
                                   (PERIPH == RSTCU_APBRST0_SPI) || \
                                   (PERIPH == RSTCU_APBRST0_USART) || \
                                   (PERIPH == RSTCU_APBRST0_AFIO) || \
                                   (PERIPH == RSTCU_APBRST0_EXTI) || \
                                   (PERIPH == RSTCU_APBRST0_PA) || \
                                   (PERIPH == RSTCU_APBRST0_PB))

/* Definitions of APB peripheral 1 reset */
#define RSTCU_APBRST1_WDT         ((u32)0x1 << 4)
#define RSTCU_APBRST1_GPTM0       ((u32)0x1 << 8)
#define RSTCU_APBRST1_GPTM1       ((u32)0x1 << 9)
#define RSTCU_APBRST1_OPA0        ((u32)0x1 << 22)
#define RSTCU_APBRST1_OPA1        ((u32)0x1 << 23)
#define RSTCU_APBRST1_ADC         ((u32)0x1 << 24)

#define IS_RSTCU_APBRST1(PERIPH)  ((PERIPH == RSTCU_APBRST1_WDT) || \
                                   (PERIPH == RSTCU_APBRST1_GPTM0) || \
                                   (PERIPH == RSTCU_APBRST1_GPTM1) || \
                                   (PERIPH == RSTCU_APBRST1_OPA0) || \
                                   (PERIPH == RSTCU_APBRST1_OPA1) || \
                                   (PERIPH == RSTCU_APBRST1_ADC))
                                   
/* Other definitions */                                   
#define IS_RSTCU_FLAG(FLAG)       ((FLAG == RSTCU_FLAG_SYSRST) || \
                                   (FLAG == RSTCU_FLAG_EXTRST) || \
                                   (FLAG == RSTCU_FLAG_WDTRST) || \
                                   (FLAG == RSTCU_FLAG_PORST))

/**
  * @}
  */  /* End of RSTCU_Exported_Constants group */


/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Exported_Macro RSTCU exported macro
  * @{
  */

/**
  * @}
  */  /* End of RSTCU_Exported_Macro group */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Exported_Functions RSTCU exported functions
  * @{
  */
FlagStatus RSTCU_GetResetFlagStatus(RSTCU_RSTF_TypeDef RSTCU_RSTF);
void RSTCU_ClearResetFlag(RSTCU_RSTF_TypeDef RSTCU_RSTF);
void RSTCU_APBPerip0Reset(u32 RSTCU_APBP, ControlStatus Cmd);
void RSTCU_APBPerip1Reset(u32 RSTCU_APBP, ControlStatus Cmd);
bool RSTCU_IS_APBPerip0ResetEnd(u32 RSTCU_APBP);
bool RSTCU_IS_APBPerip1ResetEnd(u32 RSTCU_APBP);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */  /* End of RSTCU_Exported_Functions group */

/**
  * @}
  */  /* End of RSTCU group */

/**
  * @}
  */  /* End of HT32F125x_Peripheral_Driver group */

#endif /* __HT32F125x_RSTCU_H ------------------------------------------------------------------------------*/
