/*****************************************************************************//**
 * @file    ht32f125x_exti.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the firmware functions about EXTI.
 **********************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 *********************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_exti.h"
#include "ht32f125x_rstcu.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup  EXTI EXTI
  * @brief EXTI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Private_TypesDefinitions EXTI private types definitions
  * @{
  */

/**
  * @}
  */

/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Private_Define EXTI private definitinos
  * @{
  */

/* EXTI EVWUPIEN mask */
#define WAKUPCR_EVWUPIEN_SET      ((u32)0x80000000)
#define WAKUPCR_EVWUPIEN_RESET    ((u32)0x7FFFFFFF)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Private_Macro EXTI private macros
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Private_Variable EXTI private variables
  * @{
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup EXTI_Private_Function_Prototype EXTI private function prototypes
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Private_Function EXTI private functions
  * @{
  */

/*********************************************************************************************************//**
  * @brief  Deinitialize the EXTI peripheral registers.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @retval None
  ***********************************************************************************************************/
void EXTI_DeInit(u32 EXTI_Channel)
{
  u32 tmp;
      
  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel)); 
  
  tmp = 1 << EXTI_Channel;
  
  *((u32 *) EXTI + EXTI_Channel ) = 0x0;
  EXTI->CR &= (~tmp);
  EXTI->EDGEFLGR = tmp;
  EXTI->EDGESR = tmp;
  EXTI->SCR &= (~tmp);
  EXTI->WAKUPCR &= (~tmp);
  EXTI->WAKUPPOLR &= (~tmp);
  EXTI->WAKUPFLG = tmp;
}

/*********************************************************************************************************//**
  * @brief  Initialize the EXTI peripheral.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure.
  * @retval None
  ***********************************************************************************************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  u32 regval;

  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_InitStruct->EXTI_Channel));
  Assert_Param(IS_EXTI_DEBOUNCE_TYPE(EXTI_InitStruct->EXTI_Debounce));
  Assert_Param(IS_EXTI_DEBOUNCE_SIZE(EXTI_InitStruct->EXTI_DebounceCnt));
  Assert_Param(IS_EXTI_INT_TYPE(EXTI_InitStruct->EXTI_IntType));

  /* Set EXTI interrupt configuration */
  regval = (EXTI_InitStruct->EXTI_Debounce << 31) | (EXTI_InitStruct->EXTI_IntType << 28) | (EXTI_InitStruct->EXTI_DebounceCnt);
  *( (u32 *) EXTI + EXTI_InitStruct->EXTI_Channel ) = regval;
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the specified EXTI channelx interrupts.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @param  NewState: new state of the EXTI Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void EXTI_IntConfig(u32 EXTI_Channel, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Configure EXTI interrupt */
  if (NewState == ENABLE)
  {
    EXTI->CR |= (1 << EXTI_Channel);
  }
  else
  {
    EXTI->CR &= ~(1 << EXTI_Channel);
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the EXTI channelx event wakeup function.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @param  EXTI_WakuUpType: determines the type of signal to trigger EXTI interrupt.
  *   This parameter can be one of the following values:
  *     @arg EXTI_WAKEUP_HIGH_LEVEL
  *     @arg EXTI_WAKEUP_LOW_LEVEL
  * @param  NewState: new state of the event wakeup of EXTI.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void EXTI_WakeupEventConfig(u32 EXTI_Channel, u8 EXTI_WakuUpType, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));
  Assert_Param(IS_EXTI_WAKEUP_TYPE(EXTI_WakuUpType));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState == ENABLE)
  {
    if (EXTI_WakuUpType == EXTI_WAKEUP_HIGH_LEVEL)
    {
      EXTI->WAKUPPOLR &= ~(1 << EXTI_Channel);
    }
    else
    {
      EXTI->WAKUPPOLR |= (1 << EXTI_Channel);
    }

    EXTI->WAKUPCR |=  (1 << EXTI_Channel);
  }
  else
  {
    EXTI->WAKUPCR &= ~(1 << EXTI_Channel);
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the EXTI channelx event wakeup interrupt.
  * @param  NewState: new state of the event wakeup interrupt of the EXTI.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void EXTI_WakeupEventIntConfig(ControlStatus NewState)
{
  if (NewState == ENABLE)
  {
    /* Set EVWUPIEN bit */
    EXTI->WAKUPCR |= WAKUPCR_EVWUPIEN_SET;
  }
  else
  {
    /* Clear EVWUPIEN bit */
    EXTI->WAKUPCR &= WAKUPCR_EVWUPIEN_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Clear the specified EXTI channelx edge flag.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @retval None
  ***********************************************************************************************************/
void EXTI_ClearEdgeFlag(u32 EXTI_Channel)
{
  u32 tmp;

  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  tmp = 1 << EXTI_Channel;

  /* Write 1 to clear both edge detection flag     */
  EXTI->EDGEFLGR = tmp;
  /* Write 1 to clear positive edge detection flag */
  EXTI->EDGESR = tmp;
}

/*********************************************************************************************************//**
  * @brief  Clear the specified EXTI channelx wakeup flag.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @retval None
  ***********************************************************************************************************/
void EXTI_ClearWakeupFlag(u32 EXTI_Channel)
{
  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  /* Write 1 to clear wake up flag  */
  EXTI->WAKUPFLG = 1 << EXTI_Channel;
}

/*********************************************************************************************************//**
  * @brief  Get the specified EXTI channelx wakeup flag.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @retval None
  ***********************************************************************************************************/
FlagStatus EXTI_GetWakeupFlagStatus(u32 EXTI_Channel)
{
  FlagStatus status = RESET;

  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  if ( EXTI->WAKUPFLG & (1 << EXTI_Channel) )
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/*********************************************************************************************************//**
  * @brief  Activate or Deactivate an EXTI channelx interrupt by software.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @param  NewState: new state of EXTI channelx interrupt condition.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void EXTI_SWIntCmd(u32 EXTI_Channel, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));
  Assert_Param(IS_CONTROL_STATUS(NewState));
  
  if(NewState == ENABLE)
  {
    EXTI->SCR = 1 << EXTI_Channel;
  }
  else
  {
    EXTI->SCR &= ~(1 << EXTI_Channel);
  }  
}

/*********************************************************************************************************//**
  * @brief  Get the specified EXTI channelx software command register bit.
  * @param  EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
  *   This parameter can be one of the following values:
  *     @arg EXTI_CHANNEL_0
  *     @arg EXTI_CHANNEL_1
  *     @arg EXTI_CHANNEL_2
  *     @arg EXTI_CHANNEL_3
  *     @arg EXTI_CHANNEL_4
  *     @arg EXTI_CHANNEL_5
  *     @arg EXTI_CHANNEL_6
  *     @arg EXTI_CHANNEL_7
  *     @arg EXTI_CHANNEL_8
  *     @arg EXTI_CHANNEL_9
  *     @arg EXTI_CHANNEL_10
  *     @arg EXTI_CHANNEL_11
  *     @arg EXTI_CHANNEL_12
  *     @arg EXTI_CHANNEL_13
  *     @arg EXTI_CHANNEL_14
  *     @arg EXTI_CHANNEL_15
  * @retval None
  ***********************************************************************************************************/
u32 EXTI_GetSWCmdStatus(u32 EXTI_Channel)
{
  u32 status = RESET;

  /* Check the parameters */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  if ( EXTI->SCR & (1 << EXTI_Channel) )
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
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
