/*********************************************************************************************************//**
 * @file    ht32f125x_rstcu.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This library provides all the firmware functions about Reset Control Unit.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_rstcu.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup RSTCU RSTCU
  * @brief RSTCU driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Private_TypesDefinitions RSTCU private types definitions
  * @{
  */

/**
  * @}
  */  /* End of RSTCU_Private_TypesDefinitions group */

/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Private_Define RSTCU private defines
  * @{
  */

/**
  * @}
  */  /* End of RSTCU_Private_Define group */

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Private_Macro RSTCU private macros
  * @{
  */

/**
  * @}
  */  /* End of RSTCU_Private_Macro group */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Private_Variable RSTCU private variables
  * @{
  */

/**
  * @}
  */  /* End of RSTCU_Private_Variable group */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup RSTCU_Private_Function_Prototype RSTCU private function prototypes
  * @{
  */

/**
  * @}
  */  /* End of RSTCU_Private_Function_Prototype group */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup RSTCU_Private_Function RSTCU private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Check if the specified global reset flag has been set.
 * @param RSTCU_RSTF: Specify the reset flag.
 *        This parameter can be:
 *        @arg RSTCU_FLAG_SYSRST: Get system reset flag
 *        @arg RSTCU_FLAG_EXTRST: Get external pin reset flag
 *        @arg RSTCU_FLAG_WDTRST: Get WDT reset flag
 *        @arg RSTCU_FLAG_PORST : Get power on reset flag
 * @retval The status of RSTCU_RSTF, SET or RESET.
 ************************************************************************************************************/
FlagStatus RSTCU_GetResetFlagStatus(RSTCU_RSTF_TypeDef RSTCU_RSTF)
{
  u32 tmp;
  
  /* Check the parameters */
  Assert_Param(IS_RSTCU_FLAG(RSTCU_RSTF));

  tmp = (RSTCU->GRSR & ((u32)0x1<<RSTCU_RSTF));
  if (tmp != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the specified global reset flag.
 * @param RSTCU_RSTF: Specify the reset flag.
 *        This parameter can be:
 *        @arg RSTCU_FLAG_SYSRST: Clear system reset flag
 *        @arg RSTCU_FLAG_EXTRST: Clear external pin reset flag
 *        @arg RSTCU_FLAG_WDTRST: Clear WDT reset flag
 *        @arg RSTCU_FLAG_PORST : Clear power on reset flag  
 * @retval None
 ************************************************************************************************************/
void RSTCU_ClearResetFlag(RSTCU_RSTF_TypeDef RSTCU_RSTF)
{
  /* Check the parameters */
  Assert_Param(IS_RSTCU_FLAG(RSTCU_RSTF));
  
  RSTCU->GRSR = (u32)0x1 << RSTCU_RSTF;  /* Write 1 to clear */
} 

/*********************************************************************************************************//**
 * @brief Enable APB peripheral 0 reset function.
 * @param RSTCU_APBP: Specify the APB peripheral 0.
 *        This parameter can be:
 *        @arg RSTCU_APBRST0_I2C,  RSTCU_APBRST0_SPI, RSTCU_APBRST0_USART, RSTCU_APBRST0_AFIO,
 *             RSTCU_APBRST0_EXTI, RSTCU_APBRST0_PA,  RSTCU_APBRST0_PB
 * @param Cmd: new status of the peripheral reset.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void RSTCU_APBPerip0Reset(u32 RSTCU_APBP, ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_RSTCU_APBRST0(RSTCU_APBP));
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  if (Cmd == ENABLE)
  {
    RSTCU->APBPRST0 |= RSTCU_APBP;
  }
  else
  {
    RSTCU->APBPRST0 &= ~RSTCU_APBP;
  }
}

/*********************************************************************************************************//**
 * @brief Enable APB peripheral 1 reset function.
 * @param RSTCU_APBP: Specify the APB peripheral 1.
 *        This parameter can be:
 *        @arg RSTCU_APBRST1_WDT,  RSTCU_APBRST1_GPTM0, RSTCU_APBRST1_GPTM1, RSTCU_APBRST1_OPA0,
 *             RSTCU_APBRST1_OPA1, RSTCU_APBRST1_ADC
 * @param Cmd: new status of the peripheral reset.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void RSTCU_APBPerip1Reset(u32 RSTCU_APBP, ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_RSTCU_APBRST1(RSTCU_APBP));
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  if (Cmd == ENABLE)
  {
    RSTCU->APBPRST1 |= RSTCU_APBP;
  }
  else
  {
    RSTCU->APBPRST1 &= ~RSTCU_APBP;
  }
}

/*********************************************************************************************************//**
 * @brief Check APB peripheral 0 reset state.
 * @param RSTCU_APBP: Specify the APB peripheral 0.
 *        This parameter can be:
 *        @arg RSTCU_APBRST0_I2C,  RSTCU_APBRST0_SPI, RSTCU_APBRST0_USART, RSTCU_APBRST0_AFIO,
 *             RSTCU_APBRST0_EXTI, RSTCU_APBRST0_PA,  RSTCU_APBRST0_PB
 * @retval The status of RSTCU_APBP, TRUE or FALSE.
 ************************************************************************************************************/
bool RSTCU_IS_APBPerip0ResetEnd(u32 RSTCU_APBP)
{
  bool tmp = FALSE;
  
  /* Check the parameters */
  Assert_Param(IS_RSTCU_APBRST0(RSTCU_APBP));

  if ((RSTCU->APBPRST0 & RSTCU_APBP) == 0)  /* Hardware clear automatically */
    tmp = TRUE;

  return tmp;
}

/*********************************************************************************************************//**
 * @brief Check APB peripheral 1 reset state.
 * @param RSTCU_APBP: Specify the APB peripheral 1.
 *        This parameter can be:
 *        @arg RSTCU_APBRST1_WDT,  RSTCU_APBRST1_GPTM0, RSTCU_APBRST1_GPTM1, RSTCU_APBRST1_OPA0,
 *             RSTCU_APBRST1_OPA1, RSTCU_APBRST1_ADC
 * @retval The status of RSTCU_APBP, TRUE or FALSE.
 ************************************************************************************************************/
bool RSTCU_IS_APBPerip1ResetEnd(u32 RSTCU_APBP)
{
  bool tmp = FALSE;
  
  /* Check the parameters */
  Assert_Param(IS_RSTCU_APBRST1(RSTCU_APBP));

  if ((RSTCU->APBPRST1 & RSTCU_APBP) == 0)  /* Hardware clear automatically */
    tmp = TRUE;

  return tmp;
}

/**
  * @}
  */  /* End of RSTCU_Private_Function group */

/**
  * @}
  */  /* End of RSTCU peripheral group */

/**
  * @}
  */  /* End of HT32F125x_Peripheral_Driver group */
