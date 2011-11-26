/*********************************************************************************************************//**
 * @file    ht32f125x_gpio.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of the GPIO and AFIO library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F125X_GPIO_H
#define __HT32F125X_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types GPIO exported types
  * @{
  */

/**
 * @brief  Enumeration of GPIO pull resistor.
 */
typedef enum
{
  GPIO_PR_UP = 0,   /*!< weak pull-up resistor */
  GPIO_PR_DOWN,     /*!< weak pull-down resistor */
  GPIO_PR_DISABLE   /*!< Tri-state */
}GPIO_PR_Enum ;
/**
 * @brief  Enumeration of GPIO output drive current.
 */
typedef enum
{
  GPIO_DV_4MA = 0,   /*!< 4mA source/sink current */
  GPIO_DV_8MA        /*!< 8mA source/sink current */
}GPIO_DV_Enum ;
/**
 * @brief  Enumeration of GPIO direction.
 */
typedef enum
{
  GPIO_DIR_IN = 0,    /*!< input mode */
  GPIO_DIR_OUT        /*!< output mode */
}GPIO_DIR_Enum ;
/**
 * @brief  Enumeration of GPIO port source for EXTI channel.
 */
typedef enum
{
  AFIO_ESS_PA = 0,  /*!< EXTI channel x source come from GPIO Port A */
  AFIO_ESS_PB       /*!< EXTI channel x source come from GPIO Port B */
}AFIO_ESS_Enum ;
/**
 * @brief  Enumeration of AFIO for EXTI channel.
 */
typedef enum
{
  AFIO_EXTI_CH_0 = 0x00,     /*!< EXTI channel 0 */
  AFIO_EXTI_CH_1 = 0x04,     /*!< EXTI channel 1 */
  AFIO_EXTI_CH_2 = 0x08,     /*!< EXTI channel 2 */
  AFIO_EXTI_CH_3 = 0x0C,     /*!< EXTI channel 3 */
  AFIO_EXTI_CH_4 = 0x10,     /*!< EXTI channel 4 */
  AFIO_EXTI_CH_5 = 0x14,     /*!< EXTI channel 5 */
  AFIO_EXTI_CH_6 = 0x18,     /*!< EXTI channel 6 */
  AFIO_EXTI_CH_7 = 0x1C,     /*!< EXTI channel 7 */
  AFIO_EXTI_CH_8 = 0x20,     /*!< EXTI channel 8 */
  AFIO_EXTI_CH_9 = 0x24,     /*!< EXTI channel 9 */
  AFIO_EXTI_CH_10 = 0x28,    /*!< EXTI channel 10 */
  AFIO_EXTI_CH_11 = 0x2C,    /*!< EXTI channel 11 */
  AFIO_EXTI_CH_12 = 0x30,    /*!< EXTI channel 12 */
  AFIO_EXTI_CH_13 = 0x34,    /*!< EXTI channel 13 */
  AFIO_EXTI_CH_14 = 0x38,    /*!< EXTI channel 14 */
  AFIO_EXTI_CH_15 = 0x3C     /*!< EXTI channel 15 */
}AFIO_EXTI_CH_Enum ;

/**
  * @}
  *//* End of GPIO_Exported_Types group */

/** @defgroup GPIO_Exported_Constants GPIO exported constants
  * @{
  */

/** @defgroup GPIO_PIN Definitions of GPIO_PIN
  * @{
  */
#define GPIO_PIN_0    0x0001   /*!< GPIO pin 0 selected */
#define GPIO_PIN_1    0x0002   /*!< GPIO pin 1 selected */
#define GPIO_PIN_2    0x0004   /*!< GPIO pin 2 selected */
#define GPIO_PIN_3    0x0008   /*!< GPIO pin 3 selected */
#define GPIO_PIN_4    0x0010   /*!< GPIO pin 4 selected */
#define GPIO_PIN_5    0x0020   /*!< GPIO pin 5 selected */
#define GPIO_PIN_6    0x0040   /*!< GPIO pin 6 selected */
#define GPIO_PIN_7    0x0080   /*!< GPIO pin 7 selected */
#define GPIO_PIN_8    0x0100   /*!< GPIO pin 8 selected */
#define GPIO_PIN_9    0x0200   /*!< GPIO pin 9 selected */
#define GPIO_PIN_10   0x0400   /*!< GPIO pin 10 selected */
#define GPIO_PIN_11   0x0800   /*!< GPIO pin 11 selected */
#define GPIO_PIN_12   0x1000   /*!< GPIO pin 12 selected */
#define GPIO_PIN_13   0x2000   /*!< GPIO pin 13 selected */
#define GPIO_PIN_14   0x4000   /*!< GPIO pin 14 selected */
#define GPIO_PIN_15   0x8000   /*!< GPIO pin 15 selected */
#define GPIO_PIN_ALL  0xFFFF   /*!< GPIO all pins selected */
/**
  * @}
  */

/** @defgroup AFIO_PIN  Definitions of AFIO_PIN
  * @{
  */
#define AFIO_PIN_0   (u32)0x00000003 /*!< AFIO pin 0 selected */
#define AFIO_PIN_1   (u32)0x0000000C /*!< AFIO pin 1 selected */
#define AFIO_PIN_2   (u32)0x00000030 /*!< AFIO pin 2 selected */
#define AFIO_PIN_3   (u32)0x000000C0 /*!< AFIO pin 3 selected */
#define AFIO_PIN_4   (u32)0x00000300 /*!< AFIO pin 4 selected */
#define AFIO_PIN_5   (u32)0x00000C00 /*!< AFIO pin 5 selected */
#define AFIO_PIN_6   (u32)0x00003000 /*!< AFIO pin 6 selected */
#define AFIO_PIN_7   (u32)0x0000C000 /*!< AFIO pin 7 selected */
#define AFIO_PIN_8   (u32)0x00030000 /*!< AFIO pin 8 selected */
#define AFIO_PIN_9   (u32)0x000C0000 /*!< AFIO pin 9 selected */
#define AFIO_PIN_10  (u32)0x00300000 /*!< AFIO pin 10 selected */
#define AFIO_PIN_11  (u32)0x00C00000 /*!< AFIO pin 11 selected */
#define AFIO_PIN_12  (u32)0x03000000 /*!< AFIO pin 12 selected */
#define AFIO_PIN_13  (u32)0x0C000000 /*!< AFIO pin 13 selected */
#define AFIO_PIN_14  (u32)0x30000000 /*!< AFIO pin 14 selected */
#define AFIO_PIN_15  (u32)0xC0000000 /*!< AFIO pin 15 selected */
#define AFIO_PIN_ALL (u32)0xFFFFFFFF /*!< All AFIO pins selected */
/**
  * @}
  */

/** @defgroup AFIO_MODE Definitions of AFIO_MODE
  * @{
  */
#define AFIO_MODE_DEFAULT 0x00000000   /*!< Default AFIO mode */
#define AFIO_MODE_1   0x55555555    /*!< AFIO mode 1 */
#define AFIO_MODE_2   0xAAAAAAAA    /*!< AFIO mode 2 */
#define AFIO_MODE_3   0xFFFFFFFF    /*!< AFIO mode 3 */
/**
  * @}
  */

/** @defgroup GPIO_Check_Parameter Check parameter
  * @{
  */

/**
  * @brief Used to check parameter of the GPIOx.
  */
#define IS_GPIO(x)          ((x == GPIOA) || (x == GPIOB))
/**
  * @brief Used to check parameter of the GPIOx pull resistor.
  */
#define IS_GPIO_PR(x)       (((x) == GPIO_PR_UP) || ((x) == GPIO_PR_DOWN) || ((x) == GPIO_PR_DISABLE))
/**
  * @brief Used to check parameter of the GPIOx driving current.
  */
#define IS_GPIO_DV(x)       (((x) == GPIO_DV_4MA) || ((x) == GPIO_DV_8MA) )
/**
  * @brief Used to check parameter of the GPIOx input/output direction.
  */
#define IS_GPIO_DIR(x)      (((x) == GPIO_DIR_IN) || ((x) == GPIO_DIR_OUT) )
/**
  * @brief Used to check parameter of the EXTI source port.
  */
#define IS_AFIO_ESS(x)      ((x == AFIO_ESS_PA) || (x == AFIO_ESS_PB) )
/**
  * @brief Used to check parameter of the EXTI channel.
  */
#define IS_AFIO_EXTI_CH(x)  ((x == AFIO_EXTI_CH_0) || (x == AFIO_EXTI_CH_1) || \
                             (x == AFIO_EXTI_CH_2) || (x == AFIO_EXTI_CH_3) || \
                             (x == AFIO_EXTI_CH_4) || (x == AFIO_EXTI_CH_5) || \
                             (x == AFIO_EXTI_CH_6) || (x == AFIO_EXTI_CH_7) || \
                             (x == AFIO_EXTI_CH_8) || (x == AFIO_EXTI_CH_9) || \
                             (x == AFIO_EXTI_CH_10) || (x == AFIO_EXTI_CH_11) || \
                             (x == AFIO_EXTI_CH_12) || (x == AFIO_EXTI_CH_13) || \
                             (x == AFIO_EXTI_CH_14) || (x == AFIO_EXTI_CH_15))
/**
  * @brief Used to check parameter of the AFIO mode.
  */
#define IS_AFIO_MODE(x)     ((x == AFIO_MODE_DEFAULT) || (x == AFIO_MODE_1) || \
                             (x == AFIO_MODE_2) || (x == AFIO_MODE_3))
/**
  * @}
  */

/**
  * @}
  *//* End of GPIO_Exported_Constants group */


/** @defgroup GPIO_Exported_Functions GPIO exported functions
  * @{
  */

/* Pototype of related GPIO function */
void GPIO_DeInit(GPIO_TypeDef* GPIOx) ;
void GPIO_DirectionConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DIR_Enum Direction) ;
void GPIO_PullResistorConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_PR_Enum PR) ;
void GPIO_InputConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd) ;
void GPIO_DriveConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DV_Enum Drive) ;
void GPIO_OpenDrainConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd) ;
FlagStatus GPIO_ReadInBit(GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
FlagStatus GPIO_ReadOutBit(GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
u16 GPIO_ReadInData(GPIO_TypeDef* GPIOx);
u16 GPIO_ReadOutData(GPIO_TypeDef* GPIOx);
void GPIO_SetOutBits(GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
void GPIO_ClearOutBits(GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
void GPIO_WriteOutBits(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, FlagStatus Status);
void GPIO_WriteOutData(GPIO_TypeDef* GPIOx, u16 Data);
void GPIO_PinLock(GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
bool GPIO_IsPortLocked(GPIO_TypeDef* GPIOx);
bool GPIO_IsPinLocked(GPIO_TypeDef* GPIOx, u16 GPIO_PIN);

/* Pototype of related AFIO function */
void AFIO_DeInit(void) ;
void AFIO_GPAConfig(u32 AFIO_PIN, u32 AFIO_MODE);
void AFIO_GPBConfig(u32 AFIO_PIN, u32 AFIO_MODE);
void AFIO_EXTISourceConfig(AFIO_EXTI_CH_Enum Channel, AFIO_ESS_Enum Source);

#ifdef __cplusplus
}
#endif

/**
  * @}
  *//* End of GPIO_Exported_Functions group */

/**
  * @}
  *//* End of GPIO group */

/**
  * @}
  *//* End of HT32F125x_Peripheral_Driver group */

#endif /* __HT32F125x_GPIO_H -------------------------------------------------------------------------------*/
