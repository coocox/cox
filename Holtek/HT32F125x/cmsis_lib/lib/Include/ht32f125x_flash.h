/*********************************************************************************************************//**
 * @file    ht32f125x_flash.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of the Flash Control library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125x_FLASH_H
#define __HT32F125x_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Exported_Types FLASH exported types
  * @{
  */

/**
 * @brief  Enumeration of FLASH return status.
 */
typedef enum
{
  FLASH_COMPLETE              = 0,
  FLASH_BUSY                  = 1,
  FLASH_ERR_ADDR_OUT_OF_RANGE = 2,
  FLASH_ERR_COMMAND           = 3,
  FLASH_ERR_WRITE_PROTECTED   = 4,
  FLASH_ERR_PROGRAM           = 5,
  FLASH_ERR_ERASE             = 6,
  FLASH_ERR_ERROR             = 7,
  FLASH_TIME_OUT              = 8
}FLASH_State;

/**
 * @brief  Enumeration of FLASH security status.
 */
typedef enum
{
  FLASH_SEC_DISABLE = 0x00000000,
  FLASH_SEC_MAIN    = 0x00000001,
  FLASH_SEC_OB      = 0x00000002,
  FLASH_SEC_BOTH    = 0x00000003
}FLASH_Security;

/**
 * @brief  Enumeration of FLASH boot mode.
 */
typedef enum
{
  FLASH_BOOT_LOADER = 0x00000000,
  FLASH_BOOT_SRAM   = 0x00000001,
  FLASH_BOOT_MAIN   = 0x00000002
}FLASH_Vector;

/**
  * @}
  */  /* End of FLASH_Exported_Types group */  

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Exported_Constants FLASH exported constants
  * @{
  */

/* Flash Information                                                                                        */
#define FLASH_PAGE_SIZE               ((u32)0x00000400)   /* Flash page size (1K)                           */

/* Power Saving Enable/Disable                                                                              */
#define FLASH_POWERSAVING_ENABLE      ((u32)0x00000040)   /* FLASH Power Saving Enable                      */
#define FLASH_POWERSAVING_DISABLE     ((u32)0x00000000)   /* FLASH Power Saving Disable                     */

/* Flash Prefetch Buffer Enable/Disable                                                                     */
#define FLASH_PREFETCHBUF_ENABLE      ((u32)0x00000010)   /* Flash Prefetch Buffer Enable                   */
#define FLASH_PREFETCHBUF_DISABLE     ((u32)0x00000000)   /* Flash Prefetch Buffer Disable                  */

/* Flash Wait State                                                                                         */
#define FLASH_WAITSTATE_0             ((u32)0x00000001)   /* FLASH zero latency cycle                       */
#define FLASH_WAITSTATE_1             ((u32)0x00000002)   /* FLASH one latency cycle                        */
#define FLASH_WAITSTATE_2             ((u32)0x00000003)   /* FLASH two latency cycle                        */

/* FLASH OISR Flags                                                                                         */
#define FLASH_FLAG_ORFF               ((u32)0x00000001)   /* Operation Finished Flag                        */
#define FLASH_FLAG_ITADF              ((u32)0x00000002)   /* Invalid Target Address Flag                    */
#define FLASH_FLAG_OBEF               ((u32)0x00000004)   /* Option Byte Check Sum Error Flag               */
#define FLASH_FLAG_IOCMF              ((u32)0x00000008)   /* Invalid Operation Command Flag                 */
#define FLASH_FLAG_OREF               ((u32)0x00000010)   /* Operation Error Flag                           */
#define FLASH_FLAG_RORFF              ((u32)0x00010000)   /* Raw Operation Finished Flag                    */
#define FLASH_FLAG_PPERF              ((u32)0x00020000)   /* Page Erase/Program Protected Error Flag        */

/* FLASH OIER                                                                                               */
#define FLASH_INT_ORFIE               ((u32)0x00000001)   /* Flash Operation Finished Interrupt Enable      */
#define FLASH_INT_ITADIE              ((u32)0x00000002)   /* Invalid Target Address Interrupt Enable        */
#define FLASH_INT_OBEIE               ((u32)0x00000004)   /* Option Byte Check Sum Error Interrupt Enable   */
#define FLASH_INT_IOCMIE              ((u32)0x00000008)   /* Invalid Operation Command Interrupt Enable     */
#define FLASH_INT_OREIE               ((u32)0x00000010)   /* Operation Error Interrupt Enable               */
#define FLASH_INT_ALL                 ((u32)0x0000001F)   /* Flash all Interrupt Enable                     */

/* Option Bytes Address                                                                                     */
#define OPTION_BYTE_BASE              ((u32)0x1FF00000)              /* Option Byte Base Address            */
#define OB_PP0                        ((u32)OPTION_BYTE_BASE)        /* Option Byte: Write Protection 0     */
#define OB_PP1                        ((u32)(OPTION_BYTE_BASE+0x4))  /* Option Byte: Write Protection 1     */
#define OB_PP2                        ((u32)(OPTION_BYTE_BASE+0x8))  /* Option Byte: Write Protection 2     */
#define OB_PP3                        ((u32)(OPTION_BYTE_BASE+0xC))  /* Option Byte: Write Protection 3     */
#define OB_CP                         ((u32)(OPTION_BYTE_BASE+0x10)) /* Option Byte: Secutity Protection    */
#define OB_CHECKSUM                   ((u32)(OPTION_BYTE_BASE+0x20)) /* Option Byte: Checksum               */

/* Flash Write Protection Page Mask                                                                         */
#define FLASH_WP_PAGE00               ((u32)0x00000001)
#define FLASH_WP_PAGE01               ((u32)0x00000002)
#define FLASH_WP_PAGE02               ((u32)0x00000004)
#define FLASH_WP_PAGE03               ((u32)0x00000008)
#define FLASH_WP_PAGE04               ((u32)0x00000010)
#define FLASH_WP_PAGE05               ((u32)0x00000020)
#define FLASH_WP_PAGE06               ((u32)0x00000040)
#define FLASH_WP_PAGE07               ((u32)0x00000080)
#define FLASH_WP_PAGE08               ((u32)0x00000100)
#define FLASH_WP_PAGE09               ((u32)0x00000200)
#define FLASH_WP_PAGE10               ((u32)0x00000400)
#define FLASH_WP_PAGE11               ((u32)0x00000800)
#define FLASH_WP_PAGE12               ((u32)0x00001000)
#define FLASH_WP_PAGE13               ((u32)0x00002000)
#define FLASH_WP_PAGE14               ((u32)0x00004000)
#define FLASH_WP_PAGE15               ((u32)0x00008000)
#define FLASH_WP_PAGE16               ((u32)0x00010000)
#define FLASH_WP_PAGE17               ((u32)0x00020000)
#define FLASH_WP_PAGE18               ((u32)0x00040000)
#define FLASH_WP_PAGE19               ((u32)0x00080000)
#define FLASH_WP_PAGE20               ((u32)0x00100000)
#define FLASH_WP_PAGE21               ((u32)0x00200000)
#define FLASH_WP_PAGE22               ((u32)0x00400000)
#define FLASH_WP_PAGE23               ((u32)0x00800000)
#define FLASH_WP_PAGE24               ((u32)0x01000000)
#define FLASH_WP_PAGE25               ((u32)0x02000000)
#define FLASH_WP_PAGE26               ((u32)0x04000000)
#define FLASH_WP_PAGE27               ((u32)0x08000000)
#define FLASH_WP_PAGE28               ((u32)0x10000000)
#define FLASH_WP_PAGE29               ((u32)0x20000000)
#define FLASH_WP_PAGE30               ((u32)0x40000000)
#define FLASH_WP_ALLPAGES             ((u32)0xFFFFFFFF)

/**
  * @}
  */  /* End of FLASH_Exported_Constants group */

/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Exported_Macro FLASH exported macro
  * @{
  */

/**
  * @}
  */  /* End of FLASH_Exported_Macro group */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup FLASH_Exported_Functions FLASH exported functions
  * @{
  */

void FLASH_SetWaitState(u32 FLASH_WaitState);
void FLASH_SetPowerSaving(u32 FLASH_PowerSaving);
void FLASH_SetPrefetchBuffer(u32 FLASH_PrefetchBuf);
void FLASH_SetRemappingMode(FLASH_Vector RemapMode);
FLASH_State FLASH_ErasePage(u32 PageAddress);
FLASH_State FLASH_EraseOptionByte(void);
FLASH_State FLASH_MassErase(void);
FLASH_State FLASH_ProgramWordData(u32 Address, u32 Data);
FLASH_State FLASH_EnablePageWriteProtection(u32 FLASH_Pages);
FLASH_State FLASH_EnableSecurity(FLASH_Security SecurityMode);
FLASH_State FLASH_WaitForOperationEnd(void);
u32 FLASH_GetWriteProtectionStatus(void);
u32 FLASH_GetSecurityStatus (void);
FlagStatus FLASH_GetIntStatus(u32 FLASH_FLAG);
void FLASH_IntConfig(u16 FLASH_INT, ControlStatus Cmd);
void FLASH_ClearIntFlag(u32 FLASH_FLAG);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */  /* End of FLASH_Exported_Functions group */

/**
  * @}
  */  /* End of FLASH group */

/**
  * @}
  */  /* End of HT32F125x_Peripheral_Driver group */

#endif /* __HT32F125x_FLASH_H -------------------------------------------------------------------------------*/
