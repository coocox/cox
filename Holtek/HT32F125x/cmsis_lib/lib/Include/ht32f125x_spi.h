/*****************************************************************************//**
 * @file    ht32f125x_spi.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of the SPI library.
 **********************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 *********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125x_SPI_H
#define __HT32F125x_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup SPI_Exported_Types SPI exported types
  * @{
  */

typedef struct
{
  u32 SPI_Mode;
  u32 SPI_FIFO;
  u32 SPI_DataLength;
  u32 SPI_SSMode;
  u32 SPI_SSPolarity;
  u32 SPI_CPOL;
  u32 SPI_CPHA;
  u32 SPI_FirstBit;
  u32 SPI_RxFIFOTriggerLevel;
  u32 SPI_TxFIFOTriggerLevel;
  u32 SPI_ClockPrescaler;
}SPI_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants SPI exported constants
  * @{
  */

#define SPI_FIFO_ENABLE                             ((u32)0x00000400)
#define SPI_FIFO_DISABLE                            ((u32)0x00000000)

#define IS_SPI_FIFO_SET(FIFO)                       ((FIFO == SPI_FIFO_ENABLE) || \
                                                     (FIFO == SPI_FIFO_DISABLE))


#define SPI_DATALENGTH_1                            ((u32)0x00000001)
#define SPI_DATALENGTH_2                            ((u32)0x00000002)
#define SPI_DATALENGTH_3                            ((u32)0x00000003)
#define SPI_DATALENGTH_4                            ((u32)0x00000004)
#define SPI_DATALENGTH_5                            ((u32)0x00000005)
#define SPI_DATALENGTH_6                            ((u32)0x00000006)
#define SPI_DATALENGTH_7                            ((u32)0x00000007)
#define SPI_DATALENGTH_8                            ((u32)0x00000008)
#define SPI_DATALENGTH_9                            ((u32)0x00000009)
#define SPI_DATALENGTH_10                           ((u32)0x0000000A)
#define SPI_DATALENGTH_11                           ((u32)0x0000000B)
#define SPI_DATALENGTH_12                           ((u32)0x0000000C)
#define SPI_DATALENGTH_13                           ((u32)0x0000000D)
#define SPI_DATALENGTH_14                           ((u32)0x0000000E)
#define SPI_DATALENGTH_15                           ((u32)0x0000000F)
#define SPI_DATALENGTH_16                           ((u32)0x00000000)

#define IS_SPI_DATALENGTH(DATALENGTH)               ((DATALENGTH <= 0xF))


#define SPI_MASTER                                  ((u32)0x00004000)
#define SPI_SLAVE                                   ((u32)0x00000000)

#define IS_SPI_MODE(MODE)                           ((MODE == SPI_MASTER) || \
                                                     (MODE == SPI_SLAVE))


#define SPI_SS_HARDWARE                             ((u32)0x00002000)
#define SPI_SS_SOFTWARE                             ((u32)0x00000000)

#define IS_SPI_SS_MODE(SSMODE)                      ((SSMODE == SPI_SS_HARDWARE) || \
                                                     (SSMODE == SPI_SS_SOFTWARE))


#define SPI_SS_ACTIVE                               ((u32)0x00000010)
#define SPI_SS_INACTIVE                             ((u32)0xFFFFFFEF)

#define IS_SPI_SOFTWARE_SS(SS)                      ((SS == SPI_SS_ACTIVE) || \
                                                     (SS == SPI_SS_INACTIVE))


#define SPI_SSPOLARITY_HIGH                         ((u32)0x00000800)
#define SPI_SSPOLARITY_LOW                          ((u32)0x00000000)

#define IS_SPI_SS_POLARITY(POLARITY)                ((POLARITY == SPI_SSPOLARITY_HIGH) || \
                                                     (POLARITY == SPI_SSPOLARITY_LOW))


#define SPI_CPOL_HIGH                               ((u32)0x00000400)
#define SPI_CPOL_LOW                                ((u32)0x00000000)

#define IS_SPI_CPOL(CPOL)                           ((CPOL == SPI_CPOL_HIGH) || \
                                                     (CPOL == SPI_CPOL_LOW))


#define SPI_CPHA_FIRST                              ((u32)0x00000000)
#define SPI_CPHA_SECOND                             ((u32)0x00000001)

#define IS_SPI_CPHA(CPHA)                           ((CPHA == SPI_CPHA_FIRST) || \
                                                     (CPHA == SPI_CPHA_SECOND))


#define SPI_FIRSTBIT_LSB                            ((u32)0x00001000)
#define SPI_FIRSTBIT_MSB                            ((u32)0x00000000)

#define IS_SPI_FIRST_BIT(BIT)                       ((BIT == SPI_FIRSTBIT_LSB) || \
                                                     (BIT == SPI_FIRSTBIT_MSB))


#define SPI_FLAG_TXBE                               ((u32)0x00000001)
#define SPI_FLAG_TXE                                ((u32)0x00000002)
#define SPI_FLAG_RXBNE                              ((u32)0x00000004)
#define SPI_FLAG_WC                                 ((u32)0x00000008)
#define SPI_FLAG_RO                                 ((u32)0x00000010)
#define SPI_FLAG_MF                                 ((u32)0x00000020)
#define SPI_FLAG_SA                                 ((u32)0x00000040)
#define SPI_FLAG_TOUT                               ((u32)0x00000080)
#define SPI_FLAG_BUSY                               ((u32)0x00000100)

#define IS_SPI_FLAG(FLAG)                           ((FLAG ==  SPI_FLAG_TXBE) || \
                                                     (FLAG ==  SPI_FLAG_TXE) || \
                                                     (FLAG ==  SPI_FLAG_RXBNE) || \
                                                     (FLAG ==  SPI_FLAG_WC) || \
                                                     (FLAG ==  SPI_FLAG_RO) || \
                                                     (FLAG ==  SPI_FLAG_MF) || \
                                                     (FLAG ==  SPI_FLAG_SA) || \
                                                     (FLAG ==  SPI_FLAG_TOUT) || \
                                                     (FLAG ==  SPI_FLAG_BUSY))

#define IS_SPI_FLAG_CLEAR(CLEAR)                    ((CLEAR ==  SPI_FLAG_WC) || \
                                                     (CLEAR ==  SPI_FLAG_RO) || \
                                                     (CLEAR ==  SPI_FLAG_MF) || \
                                                     (CLEAR ==  SPI_FLAG_SA) || \
                                                     (CLEAR ==  SPI_FLAG_TOUT))


#define SPI_INT_TXBE                                ((u32)0x00000001)
#define SPI_INT_TXE                                 ((u32)0x00000002)
#define SPI_INT_RXBNE                               ((u32)0x00000004)
#define SPI_INT_WC                                  ((u32)0x00000008)
#define SPI_INT_RO                                  ((u32)0x00000010)
#define SPI_INT_MF                                  ((u32)0x00000020)
#define SPI_INT_SA                                  ((u32)0x00000040)
#define SPI_INT_TOUT                                ((u32)0x00000080)
#define SPI_INT_ALL                                 ((u32)0x000000FF)

#define IS_SPI_INT(SPI_INT)                         (((SPI_INT & 0xFFFFFF00) == 0x0) && (SPI_INT != 0x0))


#define SPI_FIFO_TX                                 ((u32)0x00000100)
#define SPI_FIFO_RX                                 ((u32)0x00000200)

#define IS_SPI_FIFO_DIRECTION(DIRECTION)            (((DIRECTION & 0xFFFFFCFF) == 0x0) && (DIRECTION != 0x0))



#define IS_SPI(x)                                   (x == SPI)

#define IS_SPI_DATA(DATA)                           (DATA <= 0xFFFF)

#define IS_SPI_FIFO_LEVEL(LEVEL)                    (LEVEL <= 8)

#define IS_SPI_CLOCK_PRESCALER(PRESCALER)           (PRESCALER >= 2)

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup SPI_Exported_Macro SPI exported macro
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup SPI_Exported_Functions SPI exported functions
  * @{
  */

void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_FIFOCmd(SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_SetDataLength(SPI_TypeDef* SPIx, u16 SPI_DataLength);
void SPI_SSModeConfig(SPI_TypeDef* SPIx, u32 SPI_SSMode);
void SPI_SoftwareSSCmd(SPI_TypeDef* SPIx, u32 SPI_SoftwareSS);
void SPI_SendData(SPI_TypeDef* SPIx, u32 SPI_Data);
u16 SPI_ReceiveData(SPI_TypeDef* SPIx);
void SPI_SetTimeOutValue(SPI_TypeDef* SPIx, u32 SPI_Timeout);
void SPI_IntConfig(SPI_TypeDef* SPIx, u32 SPI_Int, ControlStatus NewState);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, u32 SPI_Flag);
u8 SPI_GetFIFOStatus(SPI_TypeDef* SPIx, u32 SPI_FIFODirection);
void SPI_ClearFlag(SPI_TypeDef* SPIx, u32 SPI_FlagClear);
void SPI_FIFOTriggerLevelConfig(SPI_TypeDef* SPIx, u32 SPI_FIFODirection, u8 SPI_FIFOLevel);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */



#endif /* __HT32F125x_SPI_H --------------------------------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */
