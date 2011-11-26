/*********************************************************************************************************//**
 * @file    ht32f125x_pwrcu.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of the Power Control Unit library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125X_PWRCU_H
#define __HT32F125X_PWRCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup PWRCU
  * @{
  */

/** @defgroup PWRCU_Exported_Types PWRCU exported types
  * @{
  */

/**
 * @brief Status of Power control unit
 */
typedef enum
{
  PWRCU_OK = 0,                     /*!< Ready for access or backup domain power on reset is released */
  PWRCU_TIMEOUT,                    /*!< Time out */
  PWRCU_ERROR                       /*!< Error */
} PWRCU_Status ;
/**
 * @brief DMOS status
 */
typedef enum
{
  PWRCU_DMOS_STS_ON = 0,            /*!< DMOS on */
  PWRCU_DMOS_STS_OFF,               /*!< DMOS off */
  PWRCU_DMOS_STS_OFF_BY_BODRESET    /*!< DMOS off caused by brow out reset */
} PWRCU_DMOSStatus ;
/**
 * @brief LVD level selection
 */
typedef enum
{
  PWRCU_LVDS_2V6 = 0x00000000,      /*!< LVD level is 2.6 V */
  PWRCU_LVDS_2V7 = 0x00020000,      /*!< LVD level is 2.7 V */
  PWRCU_LVDS_2V8 = 0x00040000,      /*!< LVD level is 2.8 V */
  PWRCU_LVDS_2V9 = 0x00060000       /*!< LVD level is 2.9 V */
} PWRCU_LVDS_Enum ;
/**
 * @brief BOD reset or interrupt selection
 */
typedef enum
{
  PWRCU_BODRIS_RESET = 0,  /*!< Reset the whole chip */
  PWRCU_BODRIS_INT   = 1   /*!< Assert interrupt */
} PWRCU_BODRIS_Enum ;
/**
 * @brief Sleep entry instruction selection
 */
typedef enum
{
  PWRCU_SLEEP_ENTRY_WFE = 0,          /*!< Sleep then wait for event */
  PWRCU_SLEEP_ENTRY_WFI               /*!< Sleep then wait for interrupt */
} PWRCU_SLEEP_ENTRY_Enum;
/**
 * @brief Backup register selection
 */
typedef enum
{
  PWRCU_BAKREG_0 = 0,
  PWRCU_BAKREG_1,
  PWRCU_BAKREG_2,
  PWRCU_BAKREG_3,
  PWRCU_BAKREG_4,
  PWRCU_BAKREG_5,
  PWRCU_BAKREG_6,
  PWRCU_BAKREG_7,
  PWRCU_BAKREG_8,
  PWRCU_BAKREG_9
} PWRCU_BAKREG_Enum;
/**
 * @brief Vdd18 power good source selection
 */
typedef enum
{
  PWRCU_V18RDYSC_BKISO = 0, /*!< Vdd18 power good source come from BK_ISO bit in CKCU unit */
  PWRCU_V18RDYSC_V18POR     /*!< Vdd18 power good source come from Vdd18 power on reset */
} PWRCU_V18RDYSC_Enum;
/**
 * @brief HSI ready counter bit length selection
 */
typedef enum
{
  PWRCU_HSIRCBL_7 = 0,  /*!< 7 bits */
  PWRCU_HSIRCBL_8,      /*!< 8 bits */
  PWRCU_HSIRCBL_9,      /*!< 9 bits */
  PWRCU_HSIRCBL_10      /*!< 10 bits (Default) */
} PWRCU_HSIRCBL_Enum;
/**
  * @} End of PWRCU_Exported_Types
  */


/** @defgroup PWRCU_Exported_Constants PWRCU exported constants
  * @{
  */

/** @defgroup PWRCU_FLAG Definitions of PWRCU_FLAG
  * @{
  */
#define PWRCU_FLAG_BAKPOR   0x0001  /*!< Backup domain power on reset flag */
#define PWRCU_FLAG_PD       0x0002  /*!< Power-Down flag */
#define PWRCU_FLAG_WUP      0x0100  /*!< External WAKEUP pin flag */
/**
  * @} End of PWRCU_FLAG group
  */

/** @defgroup PWRCU_Check_Parameter Check parameter
  * @{
  */

/**
 * @brief Used to check PWRCU_LVDS parameter
 */
#define IS_PWRCU_LVDS(x) ((x == PWRCU_LVDS_2V6) || (x == PWRCU_LVDS_2V7) || \
                          (x == PWRCU_LVDS_2V8) || (x == PWRCU_LVDS_2V9))
/**
 * @brief Used to check PWRCU_BODRIS parameter
 */
#define IS_PWRCU_BODRIS(x) ((x == PWRCU_BODRIS_RESET) || (x == PWRCU_BODRIS_INT))
/**
 * @brief Used to check PWRCU_SLEEP_ENTRY parameter
 */
#define IS_PWRCU_SLEEP_ENTRY(x) ((x == PWRCU_SLEEP_ENTRY_WFI) || (x == PWRCU_SLEEP_ENTRY_WFE))
/**
 * @brief Used to check PWRCU_BAKREG parameter
 */
#define IS_PWRCU_BAKREG(x)  (x < 10)
/**
 * @brief Used to check PWRCU_V18RDY_SRC parameter
 */
#define IS_PWRCU_V18RDYSC(x)  ((x == PWRCU_V18RDYSC_BKISO) || (x == PWRCU_V18RDYSC_V18POR))
/**
 * @brief Used to check PWRCU_HSIRCBL parameter
 */
#define IS_PWRCU_HSIRCBL(x)  (x < 4)

/**
  * @} End of PWRCU_Check_Parameter group
  */

/**
  * @} End of PWRCU_Exported_Constants
  */

/** @defgroup PWRCU_Exported_Macro PWRCU exported macro
  * @{
  */

/**
  * @} End of PWRCU_Exported_Macro
  */

/** @defgroup PWRCU_Exported_Functions PWRCU exported functions
  * @{
  */

void PWRCU_DeInit(void) ;
PWRCU_Status PWRCU_CheckReadyAccessed(void) ;
u16 PWRCU_GetFlagStatus(void) ;
u32 PWRCU_ReadBackupRegister(PWRCU_BAKREG_Enum BAKREGx) ;
void PWRCU_WriteBackupRegister(PWRCU_BAKREG_Enum BAKREGx, u32 DATA) ;
void PWRCU_Sleep(PWRCU_SLEEP_ENTRY_Enum SleepEntry) ;
void PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_Enum SleepEntry) ;
void PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_Enum SleepEntry) ;
void PWRCU_PowerDown(void) ;
void PWRCU_SetLVDS(PWRCU_LVDS_Enum Level) ;
void PWRCU_LVDCmd(ControlStatus NewState) ;
void PWRCU_BODCmd(ControlStatus NewState) ;
void PWRCU_BODRISConfig(PWRCU_BODRIS_Enum Selection) ;
FlagStatus PWRCU_GetLVDFlagStatus(void) ;
FlagStatus PWRCU_GetBODFlagStatus(void) ;
PWRCU_DMOSStatus PWRCU_GetDMOSStatus(void) ;
void PWRCU_DMOSCmd(ControlStatus NewState) ;
void PWRCU_V18RDYSourceConfig(PWRCU_V18RDYSC_Enum Sel) ;
void PWRCU_LVDWakeupIntConfig(ControlStatus NewState);
void PWRCU_WakeupPinCmd(ControlStatus NewState);
void PWRCU_WakeupPinIntConfig(ControlStatus NewState);

void PWRCU_HSIReadyCounterBitLengthConfig(PWRCU_HSIRCBL_Enum BitLength);

#ifdef __cplusplus
}
#endif

/**
  * @} End of PWRCU_Exported_Functions
  */

/**
  * @} End of PWRCU
  */

/**
  * @} End of HT32F125x_Peripheral_Driver
  */

#endif /* __HT32F125x_PWRCU_H ------------------------------------------------------------------------------*/
