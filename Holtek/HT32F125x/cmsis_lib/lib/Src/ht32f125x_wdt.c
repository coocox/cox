/*****************************************************************************//**
 * @file    ht32f125x_wdt.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the firmware functions about WDT.
 **********************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 *********************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_wdt.h"
#include "ht32f125x_rstcu.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup  WDT WDT
  * @brief WDT driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup WDT_Private_TypesDefinitions WDT private types definitions
  * @{
  */

/**
  * @}
  */

/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup WDT_Private_Define WDT private definitions
  * @{
  */

/* WDT Restart Key */
#define RESTART_KEY            ((u32)0x5FA00000)

/* WDT Protect mask */
#define PRCT_SET               ((u32)0x0000CA35)
#define PRCT_RESET             ((u32)0x000035CA)

/* WDT WDTFIEN mask */
#define MODE0_WDTFIEN_SET      ((u32)0x00001000)
#define MODE0_WDTFIEN_RESET    ((u32)0xFFFFEFFF)

/* WDT WDTRSTEN mask */
#define MODE0_WDTRETEN_SET     ((u32)0x00002000)
#define MODE0_WDTRETEN_RESET   ((u32)0xFFFFDFFF)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup WDT_Private_Macro WDT private macros
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup WDT_Private_Variable WDT private variables
  * @{
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup WDT_Private_Function_Prototype WDT private function prototypes
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup WDT_Private_Function WDT private functions
  * @{
  */

/*********************************************************************************************************//**
  * @brief  Deinitialize the WDT peripheral registers to their default reset values.
  * @retval None
  ************************************************************************************************************/
void WDT_DeInit(void)
{
  RSTCU_APBPerip1Reset(RSTCU_APBRST1_WDT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the WDT interrupt when WDT meets underflow or error.
  * @param  NewState: new state of the WDT Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_IntConfig(ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    WDT->MR0 |= MODE0_WDTFIEN_SET;
  }
  else
  {
    WDT->MR0 &= MODE0_WDTFIEN_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the WDT Reset when WDT meets underflow or error.
  * @param   NewState: new state of the WDT Reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_ResetCmd(ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    WDT->MR0 |= MODE0_WDTRETEN_SET;
  }
  else
  {
    WDT->MR0 &= MODE0_WDTRETEN_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable protection mechanism of the WDT.
  * @param  NewState: new state of the WDT Protect.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_ProtectCmd(ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    WDT->PR = PRCT_SET;
  }
  else
  {
    WDT->PR = PRCT_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Set Reload value of the WDT.
  * @param  WDT_WDTV : Specify the WDT Reload value.
  *   This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  ************************************************************************************************************/
void WDT_SetReloadValue(u16 WDT_WDTV)
{
  /* Check the parameters */
  Assert_Param(IS_WDT_RELOAD(WDT_WDTV));

  WDT->MR0 = WDT_WDTV | (WDT->MR0 & 0x0000F000);
}

/*********************************************************************************************************//**
  * @brief  Get the current reload value of the WDT.
  * @retval WDT reload value between 0 and 0x0FFF
  ************************************************************************************************************/
u16 WDT_GetReloadValue(void)
{
  return ((u16)(WDT->MR0 & 0xFFF)) ;
}

/*********************************************************************************************************//**
  * @brief  Set delta value of the WDT.
  * @param  WDT_WDTD : Specify the WDT Delta value.
  *   This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  ************************************************************************************************************/
void WDT_SetDeltaValue(u16 WDT_WDTD)
{
  /* Check the parameters */
  Assert_Param(IS_WDT_DELTA(WDT_WDTD));

  WDT->MR1 = (WDT_WDTD | (WDT->MR1 & 0x00007000));
}

/*********************************************************************************************************//**
  * @brief  Get the current delta value of the WDT.
  * @retval WDT delta value between 0 and 0x0FFF
  ************************************************************************************************************/
u16 WDT_GetDeltaValue(void)
{
  return ((u16)(WDT->MR1 & 0xFFF)) ;
}

/*********************************************************************************************************//**
  * @brief  Set Prescaler value of the WDT.
  * @param  WDT_PRESCALER: Specify the WDT Prescaler value.
  *   This parameter can be one of the following values:
  *     @arg WDT_PRESCALER_1   : WDT prescaler set to 1
  *     @arg WDT_PRESCALER_2   : WDT prescaler set to 2
  *     @arg WDT_PRESCALER_4   : WDT prescaler set to 4
  *     @arg WDT_PRESCALER_8   : WDT prescaler set to 8
  *     @arg WDT_PRESCALER_16  : WDT prescaler set to 16
  *     @arg WDT_PRESCALER_32  : WDT prescaler set to 32
  *     @arg WDT_PRESCALER_64  : WDT prescaler set to 64
  *     @arg WDT_PRESCALER_128 : WDT prescaler set to 128
  * @retval None
  ************************************************************************************************************/
void WDT_SetPrescaler(u16 WDT_PRESCALER)
{
  /* Check the parameters */
  Assert_Param(IS_WDT_PRESCALER(WDT_PRESCALER));

  WDT->MR1 = (WDT_PRESCALER | (WDT->MR1 & 0x00000FFF));
}

/*********************************************************************************************************//**
  * @brief  Get the current prescaler value of the WDT.
  * @retval WDT prescaler value
  ************************************************************************************************************/
u8 WDT_GetPrescaler(void)
{
  u32 tmp ;

  tmp = WDT->MR1 & 0x7000 ;
  tmp >>= 12 ;
  return ((u8)0x1 << tmp) ;
}

/*********************************************************************************************************//**
  * @brief  WDT Restart (Reload WDT Counter)
  * @retval None
  ************************************************************************************************************/
void WDT_Restart(void)
{
  WDT->CR = RESTART_KEY | 0x1;
}

/*********************************************************************************************************//**
  * @brief  Check whether the specified WDT flag has been set.
  * @param  WDT_FLAG: Specify the flag to be check.
  *   This parameter can be one of the following values:
  *     @arg WDT_FLAG_UNDERFLOW       : WDT underflow active
  *     @arg WDT_FLAG_ERROR           : WDT error active
  * @retval The new state of WDT_FLAG (SET or RESET).
  ************************************************************************************************************/
FlagStatus WDT_GetFlagStatus (u32 WDT_FLAG)
{
  u32 statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  Assert_Param(IS_WDT_FLAG(WDT_FLAG));

  statusreg = WDT->SR;

  if ( statusreg != WDT_FLAG )
  {
    bitstatus = RESET;
  }
  else
  {
    bitstatus = SET;
  }

  return bitstatus;
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
