/*********************************************************************************************************//**
 * @file    ht32f125x_rtc.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of RTC library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125X_RTC_H
#define __HT32F125X_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/** @defgroup RTC_Exported_Types RTC exported types
  * @{
  */

/**
 * @brief Selections of RTC clock source
 */
typedef enum
{
  RTC_SRC_LSI = 0,                /*!< Low speed internal clock, about 32KHz */
  RTC_SRC_LSE                     /*!< Low speed external 32768 Hz clock */
} RTC_SRC_Enum ;
/**
 * @brief Selections of RTC LSE startup mode
 */
typedef enum
{
  RTC_LSESM_NORMAL = 0,       /*!< Shorter startup time but higher power consumption. */
  RTC_LSESM_FAST              /*!< Less power consumption but longer startup time. */
} RTC_LSESM_Enum ;
/**
 * @brief Selections of RTC prescaler
 */
typedef enum
{
  RTC_RPRE_1     = 0x0000,           /*!< CK_SECOND = CK_RTC */
  RTC_RPRE_2     = 0x0100,           /*!< CK_SECOND = CK_RTC / 2 */
  RTC_RPRE_4     = 0x0200,           /*!< CK_SECOND = CK_RTC / 4 */
  RTC_RPRE_8     = 0x0300,           /*!< CK_SECOND = CK_RTC / 8 */
  RTC_RPRE_16    = 0x0400,           /*!< CK_SECOND = CK_RTC / 16 */
  RTC_RPRE_32    = 0x0500,           /*!< CK_SECOND = CK_RTC / 32 */
  RTC_RPRE_64    = 0x0600,           /*!< CK_SECOND = CK_RTC / 64 */
  RTC_RPRE_128   = 0x0700,           /*!< CK_SECOND = CK_RTC / 128 */
  RTC_RPRE_256   = 0x0800,           /*!< CK_SECOND = CK_RTC / 256 */
  RTC_RPRE_512   = 0x0900,           /*!< CK_SECOND = CK_RTC / 512 */
  RTC_RPRE_1024  = 0x0A00,           /*!< CK_SECOND = CK_RTC / 1024 */
  RTC_RPRE_2048  = 0x0B00,           /*!< CK_SECOND = CK_RTC / 2048 */
  RTC_RPRE_4096  = 0x0C00,           /*!< CK_SECOND = CK_RTC / 4096 */
  RTC_RPRE_8192  = 0x0D00,           /*!< CK_SECOND = CK_RTC / 8192 */
  RTC_RPRE_16384 = 0x0E00,           /*!< CK_SECOND = CK_RTC / 16384 */
  RTC_RPRE_32768 = 0x0F00            /*!< CK_SECOND = CK_RTC / 32768 */
} RTC_RPRE_Enum;
/**
 * @brief Active polarity of RTC output
 */
typedef enum
{
  RTC_ROAP_HIGH = 0,              /*!< Active level is high */
  RTC_ROAP_LOW                    /*!< Active level is low */
} RTC_ROAP_Enum;
/**
 * @brief Waveform mode of RTC output
 */
typedef enum
{
  RTC_ROWM_PULSE = 0,              /*!< Pulse mode. */
  RTC_ROWM_LEVEL                   /*!< Level mode. */
} RTC_ROWM_Enum;
/**
 * @brief Waveform mode of RTC output
 */
typedef enum
{
  RTC_ROES_MATCH = 0,              /*!< Selected RTC compare match. */
  RTC_ROES_SECOND                  /*!< Selected RTC second clock. */
} RTC_ROES_Enum;

/**
  * @} End of RTC_Exported_Types group
  */

/** @defgroup RTC_Exported_Constants RTC exported constants
  * @{
  */

/** @defgroup RTC_WAKEUP  Definitions of RTC wakeup source
  * @{
  */
#define RTC_WAKEUP_CSEC   0x00000100
#define RTC_WAKEUP_CM     0x00000200
#define RTC_WAKEUP_OV     0x00000400
/**
  * @}
  */

/** @defgroup RTC_IT Definitions of RTC interrupt source
  * @{
  */
#define RTC_INT_CSEC      0x00000001
#define RTC_INT_CM        0x00000002
#define RTC_INT_OV        0x00000004
/**
  * @}
  */

/** @defgroup RTC_FLAG Definitions of RTC flags
  * @{
  */
#define RTC_FLAG_CSEC     0x00000001
#define RTC_FLAG_CM       0x00000002
#define RTC_FLAG_OV       0x00000004
/**
  * @}
  */

/** @defgroup RTC_Check_Parameter Check parameter
  * @{
  */

/**
 * @brief Used to check RTC_SRC_Enum parameter
 */
#define IS_RTC_SRC(x) ((x == RTC_SRC_LSI) || (x == RTC_SRC_LSE))
/**
 * @brief Used to check RTC_LSESM_Enum parameter
 */
#define IS_RTC_LSESM(x) ((x == RTC_LSESM_NORMAL) || (x == RTC_LSESM_FAST))
/**
 * @brief Used to check RTC_RPRE_Enum parameter
 */
#define IS_RTC_PSC(x) ((x == RTC_RPRE_1) || (x == RTC_RPRE_2) || (x == RTC_RPRE_4) ||\
                       (x == RTC_RPRE_8) || (x == RTC_RPRE_16) || (x == RTC_RPRE_32) ||\
                       (x == RTC_RPRE_64) || (x == RTC_RPRE_128) || (x == RTC_RPRE_256) ||\
                       (x == RTC_RPRE_512) || (x == RTC_RPRE_1024) || (x == RTC_RPRE_2048) ||\
                       (x == RTC_RPRE_4096) || (x == RTC_RPRE_8192) || (x == RTC_RPRE_16384) ||\
                       (x == RTC_RPRE_32768))
/**
 * @brief Used to check RTC_ROAP_Enum parameter
 */
#define IS_RTC_ROAP(x) ((x == RTC_ROAP_HIGH) || (x == RTC_ROAP_LOW))
/**
 * @brief Used to check RTC_ROWM_Enum parameter
 */
#define IS_RTC_ROWM(x) ((x == RTC_ROWM_PULSE) || (x == RTC_ROWM_LEVEL))
/**
 * @brief Used to check RTC_ROES_Enum parameter
 */
#define IS_RTC_ROES(x) ((x == RTC_ROES_MATCH) || (x == RTC_ROES_SECOND))
/**
 * @brief Used to check RTC_WAKEUP parameter
 */
#define IS_RTC_WAKEUP(x) ((((x) & (u32)0xFFFFF8FF) == 0x00) && ((x) != 0x00))
/**
 * @brief Used to check RTC_INT parameter
 */
#define IS_RTC_INT(x) ((((x) & (u32)0xFFFFFFF8) == 0x00) && ((x) != 0x00))
/**
 * @brief Used to check RTC_FLAG parameter
 */
#define IS_RTC_FLAG(x) ((((x) & (u32)0xFFFFFFF8) == 0x00) && ((x) != 0x00))
/**

  * @} End of RTC_Check_Parameter group
  */

/**
  * @} End of RTC_Exported_Constants group
  */

/** @defgroup RTC_Exported_Macro RTC exported macro
  * @{
  */
/**
  * @} End of RTC_Exported_Macro group
  */

/** @defgroup RTC_Exported_Functions RTC exported functions
  * @{
  */

void RTC_DeInit(void) ;
void RTC_ClockSourceConfig(RTC_SRC_Enum Source) ;
void RTC_LSILoadTrimData(void) ;
void RTC_LSICmd(ControlStatus NewState) ;
void RTC_LSESMConfig(RTC_LSESM_Enum Mode) ;
void RTC_LSECmd(ControlStatus NewState) ;
void RTC_CMPCLRCmd(ControlStatus NewState) ;
void RTC_SetPrescaler(RTC_RPRE_Enum Psc) ;
u16 RTC_GetPrescaler(void) ;
void RTC_Cmd(ControlStatus NewState) ;
u32 RTC_GetCounter(void) ;
void RTC_SetCompare(u32 Compare) ;
u32 RTC_GetCompare(void) ;
void RTC_WakeupConfig(u32 RTC_WAKEUP, ControlStatus NewState) ;
void RTC_IntConfig(u32 RTC_INT, ControlStatus NewState) ;
u8 RTC_GetFlagStatus(void) ;
void RTC_OutConfig(RTC_ROWM_Enum WMode, RTC_ROES_Enum EventSel, RTC_ROAP_Enum Pol) ;
void RTC_OutCmd(ControlStatus NewState) ;
FlagStatus RTC_GetOutStatus(void) ;

#ifdef __cplusplus
}
#endif

/**
  * @} End of RTC_Exported_Functions group
  */

/**
  * @} End of RTC group
  */

/**
  * @} End of HT32F125x_Peripheral_Driver group
  */

#endif /* __HT32F125x_RTC_H --------------------------------------------------------------------------------*/
