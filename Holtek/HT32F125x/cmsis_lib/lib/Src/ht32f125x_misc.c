/******************************************************************************//**
 * @file    ht32f125x_misc.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the miscellaneous firmware functions.
 **********************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 *********************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_misc.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup  MISC MISC
  * @brief MISC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup MISC_Private_TypesDefinitions MISC private types definitions
  * @{
  */

/**
  * @}
  */

/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup MISC_Private_Define MISC private definitions
  * @{
  */
#define AIRCR_VECTKEY_MASK    ((u32)0x05FA0000)

#define CTRL_TICKINT_SET      ((u32)0x00000002)
#define CTRL_TICKINT_RESET    ((u32)0xFFFFFFFD)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup MISC_Private_Macro MISC private macros
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup MISC_Private_Variable MISC private variables
  * @{
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup MISC_Private_Function_Prototype MISC private function prototypes
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup MISC_Private_Function MISC private functions
  * @{
  */

/*********************************************************************************************************//**
  * @brief  Set the vector table location and Offset.
  * @param  NVIC_VectTable: Specify if the vector table is in FLASH or RAM.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VECTTABLE_RAM
  *     @arg NVIC_VECTTABLE_FLASH
  * @param  NVIC_Offset: Vector Table base offset field.
  *   This value must be a multiple of 0x100.
  * @retval None
  ***********************************************************************************************************/
void NVIC_SetVectorTable(u32 NVIC_VectTable, u32 NVIC_Offset)
{
  /* Check the parameters */
  Assert_Param(IS_NVIC_VECTTABLE(NVIC_VectTable));
  Assert_Param(IS_NVIC_OFFSET(NVIC_Offset));

  SCB->VTOR = NVIC_VectTable | (NVIC_Offset & (u32)0x1FFFFF80);
}

/*********************************************************************************************************//**
  * @brief  Select the condition for the system to enter low power mode.
  * @param  NVIC_LowPowerMode:  Specify the new mode for the system to enter low power mode.
  *   This parameter can be one of the following values:
  *     @arg NVIC_LOWPOWER_SEVONPEND
  *     @arg NVIC_LOWPOWER_SLEEPDEEP
  *     @arg NVIC_LOWPOWER_SLEEPONEXIT
  * @param  NewState: new state of low power condition.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void NVIC_LowPowerConfig(u8 NVIC_LowPowerMode,  ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_NVIC_LOWPOWER(NVIC_LowPowerMode));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SCB->SCR |= NVIC_LowPowerMode;
  }
  else
  {
    SCB->SCR &= (u32)(~(u32)NVIC_LowPowerMode);
  }
}
/*********************************************************************************************************//**
  * @brief  Generate a Core (Core + NVIC) reset.
  * @retval None
  ***********************************************************************************************************/
void NVIC_CoreReset(void)
{
  SCB->AIRCR = AIRCR_VECTKEY_MASK | (u32)0x01;
}
/*********************************************************************************************************//**
  * @brief  Set the pending bit for an system handler.
  * @param  SystemHandler: Specify the system handler pending bit to be set.
  *   This parameter can be one of the following values:
  *     @arg SYSTEMHANDLER_NMI
  *     @arg SYSTEMHANDLER_PSV
  *     @arg SYSTEMHANDLER_SYSTICK
  * @retval None
  ***********************************************************************************************************/
void NVIC_SetPendingSystemHandler(u32 SystemHandler)
{
  /* Check the parameters */
  Assert_Param(IS_NVIC_SYSTEMHANDLER(SystemHandler));

  /* Set the corresponding System Handler pending bit */
  SCB->ICSR |= SystemHandler;
}

/*********************************************************************************************************//**
  * @brief  Configure the SysTick clock source.
  * @param  SysTick_ClockSource: Specify the SysTick clock source.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_SRC_STCLK  : External reference clock selected as SysTick clock source.
  *     @arg SYSTICK_SRC_FCLK   : AHB clock selected as SysTick clock source.
  * @retval  None
  ***********************************************************************************************************/
void SYSTICK_ClockSourceConfig(u32 SysTick_ClockSource)
{
  /* Check the parameters */
  Assert_Param(IS_SYSTICK_CLOCK_SOURCE(SysTick_ClockSource));

  if (SysTick_ClockSource == SYSTICK_SRC_FCLK)
  {
    SysTick->CTRL |= SYSTICK_SRC_FCLK;
  }
  else
  {
    SysTick->CTRL &= SYSTICK_SRC_STCLK;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick counter.
  * @param  SysTick_Counter: new state of the SysTick counter.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_COUNTER_DISABLE  : Disable counter
  *     @arg SYSTICK_COUNTER_ENABLE   : Enable counter
  *     @arg SYSTICK_COUNTER_CLEAR    : Clear counter value to 0
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_CounterCmd(u32 SysTick_Counter)
{
  /* Check the parameters */
  Assert_Param(IS_SYSTICK_COUNTER(SysTick_Counter));

  if (SysTick_Counter == SYSTICK_COUNTER_CLEAR)
  {
    SysTick->VAL = SYSTICK_COUNTER_CLEAR;
  }
  else
  {
    if (SysTick_Counter == SYSTICK_COUNTER_ENABLE)
    {
      SysTick->CTRL |= SYSTICK_COUNTER_ENABLE;
    }
    else
    {
      SysTick->CTRL &= SYSTICK_COUNTER_DISABLE;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick Interrupt.
  * @param  NewState: new state of the SysTick Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_IntConfig(ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SysTick->CTRL |= CTRL_TICKINT_SET;
  }
  else
  {
    SysTick->CTRL &= CTRL_TICKINT_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Set SysTick counter reload value.
  * @param  SysTick_Reload: SysTick reload new value.
  *   This parameter must be a number between 1 and 0xFFFFFF.
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_SetReloadValue(u32 SysTick_Reload)
{
  /* Check the parameters                                                                                 */
  Assert_Param(IS_SYSTICK_RELOAD(SysTick_Reload));

  SysTick->LOAD = SysTick_Reload;
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
