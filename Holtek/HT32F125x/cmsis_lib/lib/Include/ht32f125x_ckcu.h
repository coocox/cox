/*********************************************************************************************************//**
 * @file    ht32f125x_ckcu.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of Clock Control library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125x_CKCU_H
#define __HT32F125x_CKCU_H

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup CKCU
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Exported_Types CKCU exported types
  * @{
  */

/**
 * @brief Enumeration of USART clock prescaler.
 */
typedef enum
{
  CKCU_URPRE_DIV1 = 0,
  CKCU_URPRE_DIV2
} CKCU_URPRE_TypeDef;

/**
 * @brief Enumeration of WDT clock source.
 */
typedef enum
{
  CKCU_WDTSRC_LSI = 0,
  CKCU_WDTSRC_LSE
} CKCU_WDTSRC_TypeDef;

/**
 * @brief Enumeration of PLL clock source.
 */
typedef enum
{
  CKCU_PLLSRC_HSE = 0,
  CKCU_PLLSRC_HSI
} CKCU_PLLSRC_TypeDef;

/**
 * @brief Enumeration of AHB prescaler.
 */
typedef enum
{
  CKCU_SYSCLK_DIV1 = 0,
  CKCU_SYSCLK_DIV2,
  CKCU_SYSCLK_DIV4,
  CKCU_SYSCLK_DIV8
} CKCU_SYSCLKDIV_TypeDef;

/**
 * @brief Enumeration of ADC clock divide.
 */
typedef enum
{
  CKCU_PCLK_DIV1 = 0,
  CKCU_PCLK_DIV2,
  CKCU_PCLK_DIV4,
  CKCU_PCLK_DIV8,
  CKCU_PCLK_DIV16,
  CKCU_PCLK_DIV32,
  CKCU_PCLK_DIV64,
  CKCU_PCLK_DIV6
} CKCU_PCLKDIV_TypeDef;

/**
 * @brief Enumeration of System clock source.
 */
typedef enum
{
  CKCU_SW_REV0 = 0,
  CKCU_SW_PLL,
  CKCU_SW_HSE,
  CKCU_SW_HSI
} CKCU_SW_TypeDef;

/**
 * @brief Enumeration of CKOUT output clock source.
 */
typedef enum
{
  CKCU_CKOUTSRC_PLL_DIV16 = 0,
  CKCU_CKOUTSRC_HCLK_DIV16,
  CKCU_CKOUTSRC_SYSCK_DIV16,
  CKCU_CKOUTSRC_HSECK_DIV16,
  CKCU_CKOUTSRC_HSICK_DIV16,
  CKCU_CKOUTSRC_LSECK,
  CKCU_CKOUTSRC_LSICK
} CKCU_CKOUTSRC_TypeDef;

/**
 * @brief Enumeration of PLL clock source status.
 */
typedef enum
{
  CKCU_PLLST_SYSCK  = 0x01
} CKCU_PLLST_TypeDef;

/**
 * @brief Enumeration of HSI clock source status.
 */
typedef enum
{
  CKCU_HSIST_SYSCK  = 0x1,
  CKCU_HSIST_PLL    = 0x2,
  CKCU_HSIST_CKM    = 0x4
} CKCU_HSIST_TypeDef;

/**
 * @brief Enumeration of HSE clock source status.
 */
typedef enum
{
  CKCU_HSEST_SYSCK  = 0x1,
  CKCU_HSEST_PLL    = 0x2
} CKCU_HSEST_TypeDef;

/**
 * @brief Definition of initial structure for CKOUT function.
 */
typedef struct
{
  CKCU_CKOUTSRC_TypeDef CKOUTSRC;
} CKCU_CKOUTInitTypeDef;

/**
 * @brief Definition of initial structure of PLL frequency.
 */
typedef struct
{
  u16 CFG;
  CKCU_PLLSRC_TypeDef ClockSource;
  EventStatus BYPASSCmd;
} CKCU_PLLInitTypeDef;

/**
 * @brief Definition of structure for clock frequency.
 */
typedef struct
{
  u32 PLL_Freq;
  u32 SYSCK_Freq;
  u32 HCLK_Freq;
  u32 USART_Freq;
  u32 ADC_Freq;
} CKCU_ClocksTypeDef;

/**
  * @}
  */  /* End of CKCU_Exported_Types group */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Exported_Constants CKCU exported constants
  * @{
  */

/* Definitions of clock ready flag */
#define CKCU_FLAG_PLLRDY        ((u8)0x1 << 1)
#define CKCU_FLAG_HSERDY        ((u8)0x1 << 2)
#define CKCU_FLAG_HSIRDY        ((u8)0x1 << 3)
#define CKCU_FLAG_LSERDY        ((u8)0x1 << 4)
#define CKCU_FLAG_LSIRDY        ((u8)0x1 << 5)

#define IS_CKCU_FLAG(FLAG)      (((FLAG & 0xFFFFFFC1) == 0x0) && (FLAG != 0x0))

/* Definitions of clock interrupt & flag */
#define CKCU_INT_CKS            ((u8)0x1)
#define CKCU_INT_PLLRDY         ((u8)0x1 << 2)
#define CKCU_INT_HSERDY         ((u8)0x1 << 3)
#define CKCU_INT_HSIRDY         ((u8)0x1 << 4)
#define CKCU_INT_LSERDY         ((u8)0x1 << 5)
#define CKCU_INT_LSIRDY         ((u8)0x1 << 6)

#define IS_CKCU_INT_FLAG(FLAG)  (((FLAG & 0xFFFFFF82) == 0x0) && (FLAG != 0x0))

#define CKCU_INT_CKSIE          ((u32)0x1 << 16)
#define CKCU_INT_PLLRDYIE       ((u32)0x1 << 18)
#define CKCU_INT_HSERDYIE       ((u32)0x1 << 19)
#define CKCU_INT_HSIRDYIE       ((u32)0x1 << 20)
#define CKCU_INT_LSERDYIE       ((u32)0x1 << 21)
#define CKCU_INT_LSIRDYIE       ((u32)0x1 << 22)

#define IS_CKCU_INT(IT)         (((IT & 0xFF82FFFF) == 0x0) && (IT != 0x0))

/* Definitions of PLL frequency */
#define CKCU_PLL_4M_144M        ((u32)0x1200)
#define CKCU_PLL_4M_96M         ((u32)0x0C00)
#define CKCU_PLL_8M_144M        ((u32)0x0900)
#define CKCU_PLL_8M_96M         ((u32)0x0600)
#define CKCU_PLL_8M_72M         ((u32)0x0480)
#define CKCU_PLL_12M_144M       ((u32)0x0600)
#define CKCU_PLL_12M_96M        ((u32)0x0400)
#define CKCU_PLL_16M_144M       ((u32)0x0480)
#define CKCU_PLL_16M_96M        ((u32)0x0300)

/* Definitions of APB peripheral enable control value */
#define CKCU_APBEN0_I2C         ((u32)0x1)
#define CKCU_APBEN0_SPI         ((u32)0x1 << 4)
#define CKCU_APBEN0_USART       ((u32)0x1 << 8)
#define CKCU_APBEN0_AFIO        ((u32)0x1 << 14)
#define CKCU_APBEN0_EXTI        ((u32)0x1 << 15)
#define CKCU_APBEN0_PA          ((u32)0x1 << 16)
#define CKCU_APBEN0_PB          ((u32)0x1 << 17)

#define IS_CKCU_APBEN0(PERIPH)  (((PERIPH & 0xFFFC3EEE) == 0x0) && (PERIPH != 0x0))

#define CKCU_APBEN1_WDT         ((u32)0x1 << 4)
#define CKCU_APBEN1_RTC         ((u32)0x1 << 6)
#define CKCU_APBEN1_GPTM0       ((u32)0x1 << 8)
#define CKCU_APBEN1_GPTM1       ((u32)0x1 << 9)
#define CKCU_APBEN1_OPA0        ((u32)0x1 << 22)
#define CKCU_APBEN1_OPA1        ((u32)0x1 << 23)
#define CKCU_APBEN1_ADC         ((u32)0x1 << 24)

#define IS_CKCU_APBEN1(PERIPH)  (((PERIPH & 0xFE3FFCAF) == 0x0) && (PERIPH != 0x0))

#define CKCU_APBEN0_ALL (CKCU_APBEN0_I2C | CKCU_APBEN0_SPI | CKCU_APBEN0_USART | \
                         CKCU_APBEN0_AFIO | CKCU_APBEN0_EXTI | CKCU_APBEN0_PA |  \
                         CKCU_APBEN0_PB)

#define CKCU_APBEN1_ALL (CKCU_APBEN1_WDT | CKCU_APBEN1_RTC | CKCU_APBEN1_GPTM0 |   \
                         CKCU_APBEN1_GPTM1 | CKCU_APBEN1_OPA0 | CKCU_APBEN1_OPA1 | \
                         CKCU_APBEN1_ADC)

/* Definitions of MCU debug control value */
#define CKCU_DBG_SLEEP          ((u16)0x1)
#define CKCU_DBG_DEEPSLEEP1     ((u16)0x1 << 1)
#define CKCU_DBG_POWERDOWN      ((u16)0x1 << 2)
#define CKCU_DBG_WDT_HALT       ((u16)0x1 << 3)
#define CKCU_DBG_GPTM0_HALT     ((u16)0x1 << 6)
#define CKCU_DBG_GPTM1_HALT     ((u16)0x1 << 7)
#define CKCU_DBG_USART_TIMEOUT  ((u16)0x1 << 8)
#define CKCU_DBG_SPI_TIMEOUT    ((u16)0x1 << 10)
#define CKCU_DBG_DEEPSLEEP2     ((u16)0x1 << 14)

#define IS_CKCU_DBG(MODE)       (((MODE & 0xFFFFBA30) == 0x0) && (MODE != 0x0))

/* Definitions of AHB clock control */
#define CKCU_AHBEN_SLEEP_FMC    ((u16)0x1)
#define CKCU_AHBEN_SLEEP_SRAM   ((u16)0x1 << 2)

#define IS_CKCU_SLEEP_AHB(PERIPH)  (((PERIPH & 0xFFFFFFFA) == 0x0) && (PERIPH != 0x0))

/**
  * @}
  */  /* End of CKCU_Exported_Constants group */

/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Exported_Macro CKCU exported macro
  * @{
  */

/**
  * @}
  */  /* End of CKCU_Exported_Macro group */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Exported_Functions CKCU exported functions
  * @{
  */
void CKCU_DeInit(void);
void CKCU_HSECmd(EventStatus Cmd);
void CKCU_HSICmd(EventStatus Cmd);
void CKCU_PLLCmd(EventStatus Cmd);
void CKCU_PLLInit(CKCU_PLLInitTypeDef *PLLInit);
ErrStatus CKCU_WaitHSEReady(void);
FlagStatus CKCU_GetClockReadyStatus(u32 CKCU_FLAG);
ErrStatus CKCU_SysClockConfig(CKCU_SW_TypeDef CLKSRC);
u8 CKCU_GetSysClockSource(void);
void CKCU_SetHCLKPrescaler(CKCU_SYSCLKDIV_TypeDef DIV);
void CKCU_SetUSARTPrescaler(CKCU_URPRE_TypeDef URPRE);
void CKCU_SetADCDivide(CKCU_PCLKDIV_TypeDef PCLK_DIVX);
void CKCU_WDTSourceConfig(CKCU_WDTSRC_TypeDef SRC);
void CKCU_GetClocksFrequency(CKCU_ClocksTypeDef* CKCU_Clk);
void CKCU_APBPerip0ClockConfig(u32 CKCU_APBP, ControlStatus Cmd);
void CKCU_APBPerip1ClockConfig(u32 CKCU_APBP, ControlStatus Cmd);
void CKCU_CKMCmd(ControlStatus Cmd);
void CKCU_PSRCWKUPCmd(ControlStatus Cmd);
void CKCU_CKOUTConfig(CKCU_CKOUTInitTypeDef *CKOUTInit);
FlagStatus CKCU_GetIntStatus(u8 CKCU_INT);
void CKCU_ClearIntFlag(u8 CKCU_INT);
void CKCU_IntConfig(u32 CKCU_INT, ControlStatus Cmd);
void CKCU_SleepClockConfig(u32 CKCU_CLK, ControlStatus Cmd);
bool CKCU_IS_PLL_USED(CKCU_PLLST_TypeDef Target);
bool CKCU_IS_HSI_USED(CKCU_HSIST_TypeDef Target);
bool CKCU_IS_HSE_USED(CKCU_HSEST_TypeDef Target);
void CKCU_MCUDBGConfig(u16 CKCU_DBGx, ControlStatus Cmd);
void CKCU_BKISOCmd(EventStatus Cmd);
void CKCU_PLLSourceConfig(CKCU_PLLSRC_TypeDef SRC);

/**
  * @}
  */  /* End of CKCU_Exported_Functions group */

/**
  * @}
  */  /* End of CKCU group */

/**
  * @}
  */  /* End of HT32F125x_Peripheral_Driver group */

#endif /* __HT32F125x_CKCU_H -------------------------------------------------------------------------------*/
