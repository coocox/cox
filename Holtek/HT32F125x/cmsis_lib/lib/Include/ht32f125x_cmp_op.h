/*********************************************************************************************************//**
 * @file    ht32f125x_cmp_op.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of the CMP_OP library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __ht32f125x_CMP_OP_H
#define __ht32f125x_CMP_OP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup CMP_OP
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Exported_Types CMP_OP exported types
  * @{
  */

/* Definitions of Control Registers */
typedef struct
{
  u32 CMP_OP_Enable;
  u32 CMP_OP_CMPOPMode;
  u32 CMP_OP_CancellOPAMode;
  u32 CMP_OP_RefSelect;
  u32 CMP_OP_Cancellation;
  u32 CMP_OP_RisingInterruptMask;
  u32 CMP_OP_FallingInterruptMask;
}CMP_OP_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Exported_Constants CMP_OP exported constants
  * @{
  */


/* CMP_OP Control */
/** @defgroup CMP_OP_Control Definitions of CMP_OP control
  * @{
  */
#define CMP_OP_DISABLE                ((u32)0x00000000)
#define CMP_OP_ENABLE                 ((u32)0x00000001)
#define OP_MODE                       ((u32)0x00000000)
#define CMP_MODE                      ((u32)0x00000002)
#define NORMAL_MODE                   ((u32)0x00000000)
#define CANCELLATION_MODE             ((u32)0x00000004)
#define NEGATIVE_INPUT                ((u32)0x00000000)
#define POSITIVE_INPUT                ((u32)0x00000008)
  
#define IS_CMP_OP_MODE(MODE) ((MODE == CMP_OP_DISABLE) || (MODE == CMP_OP_ENABLE) || \
                              (MODE == OP_MODE) || (MODE == CMP_MODE) || \
                              (MODE == NORMAL_MODE) || (MODE == CANCELLATION_MODE) || \
                              (MODE == NEGATIVE_INPUT ) || (MODE == POSITIVE_INPUT))
                              
#define IS_CMP_OP_REF(REF) ((REF == NEGATIVE_INPUT ) || (REF == POSITIVE_INPUT))
                              
/**
  * @}
  */
  
/* CMP_OP Input Offset Voltage Cancellation */
/** @defgroup CMP_OP_Input_Offset Definitions of CMP_OP input offset
  * @{
  */  
#define MIN                           ((u32)0x00000000)
#define CENTER                        ((u32)0x00000020)
#define MAX                           ((u32)0x0000003F)

#define IS_CMP_OP_OFFSET(OFFSET)      (OFFSET <= 63 )

/**
  * @}
  */
  
/* CMP_OP Interrupt Mask */
/** @defgroup CMP_OP_Interrupt_Mask Definitions of CMP_OP interrupts mask
  * @{
  */
#define FALL_INTERRUPT_NONMASK        (~(u32)0x00000001)
#define FALL_INTERRUPT_MASK           ((u32)0x00000001)
#define RISING_INTERRUPT_NONMASK      (~(u32)0x00000002)
#define RISING_INTERRUPT_MASK         ((u32)0x00000002)

#define IS_CMP_OP_MASK(MASK) ((MASK == FALL_INTERRUPT_NONMASK) || \
                              (MASK == FALL_INTERRUPT_MASK) || \
                              (MASK == RISING_INTERRUPT_NONMASK) || \
                              (MASK == RISING_INTERRUPT_MASK ))  
/**
  * @}
  */

/* CMP_OP Interrupt */
/** @defgroup CMP_OP_Interrupt Definitions of CMP_OP interrupts
  * @{
  */  
#define CMP_OP_INT_FALLING            ((u32)0x00000001)
#define CMP_OP_INT_RISING             ((u32)0x00000002)

#define IS_CMP_OP_INT(INT) ((INT == CMP_OP_INT_FALLING) || \
                            (INT == CMP_OP_INT_RISING))
/**
  * @}
  */

/* CMP_OP Interrupt Flag */
/** @defgroup CMP_OP_Interrupt_Flag Definitions of CMP_OP interrupt flags
  * @{
  */
#define CMP_OP_FLAG_FALLING          ((u32)0x00000001)
#define CMP_OP_FLAG_RISING           ((u32)0x00000002)

#define IS_CMP_OP_FLAG(FLAG) ((FLAG == CMP_OP_FLAG_FALLING) || \
                              (FLAG == CMP_OP_FLAG_RISING))
/**
  * @}
  */

/* CMP_OP BASE */
/**
 * @brief Used to check parameter of the CMP_OPx.
 */
#define IS_CMP_OP_ALL_PERIPH(PERIPH) ((PERIPH == CMP_OP0) || (PERIPH == CMP_OP1))

/**
  * @}
  *//* End of CMP_OP_Exported_Constants group */

/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Exported_Macro CMP_OP exported macro
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Exported_Functions CMP_OP exported functions
  * @{
  */
  
void CMP_OP_Init(CMP_OP_TypeDef* CMP_OPx, CMP_OP_InitTypeDef* CMP_OP_InitStructure);
u16 CMP_OP_Cancellation(CMP_OP_TypeDef* CMP_OPx, u16 CMP_OP_REF_INPUT);
void CMP_OP_IntConfig(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT, ControlStatus NewState);
FlagStatus CMP_OP_GetIntStatus(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT);
FlagStatus CMP_OP_GetFlagStatus(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_FLAG);
void CMP_OP_ClearIntPendingBit(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT);

#ifdef __cplusplus
}
#endif

#endif /* __HT32F125x_CMP_OP_H -------------------------------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
