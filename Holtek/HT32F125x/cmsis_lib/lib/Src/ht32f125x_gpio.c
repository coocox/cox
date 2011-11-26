/*********************************************************************************************************//**
 * @file    ht32f125x_gpio.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the firmware functions about GPIO and AFIO.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_gpio.h"
#include "ht32f125x_rstcu.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO driver modules
  * @{
  */

/** @defgroup GPIO_Private_TypesDefinitions GPIO private types definitions
  * @{
  */
/**
  * @}
  *//* End of GPIO_Private_TypesDefinitions group */

/** @defgroup GPIO_Private_Define GPIO private definitions
  * @{
  */
/**
  * @}
  *//* End of GPIO_Private_Define group */

/** @defgroup GPIO_Private_Macro GPIO private macros
  * @{
  */
/**
  * @}
  *//* End of GPIO_Private_Macro group */

/** @defgroup GPIO_Private_Variable GPIO private variables
  * @{
  */
/**
  * @}
  */

/** @defgroup GPIO_Private_Function GPIO private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitialize the GPIOx peripheral registers to their default reset values.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @retval None
 ************************************************************************************************************/
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  if(GPIOx == GPIOA)
  {
    RSTCU_APBPerip0Reset(RSTCU_APBRST0_PA, ENABLE);
  }
  else if(GPIOx == GPIOB)
  {
    RSTCU_APBPerip0Reset(RSTCU_APBRST0_PB, ENABLE);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the direction of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Direction: This parameter can be one of below:
 *        @arg GPIO_DIR_IN  : The pins are input mode.
 *        @arg GPIO_DIR_OUT : The pins are output mode.
 * @retval None
 ************************************************************************************************************/
void GPIO_DirectionConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DIR_Enum Direction)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  Assert_Param(IS_GPIO_DIR(Direction)) ;

  if(Direction != GPIO_DIR_IN)
    GPIOx->DIRCR |= GPIO_PIN ;
  else
    GPIOx->DIRCR &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Configure the pull resistor of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param PR: Selection of Pull resistor. This parameter can be one of below:
 *        @arg GPIO_PR_UP      : The pins with internal pull-up resistor
 *        @arg GPIO_PR_DOWN    : The pins with internal pull-down resistor
 *        @arg GPIO_PR_DISABLE : The pins without pull resistor
 * @retval None
 ************************************************************************************************************/
void GPIO_PullResistorConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_PR_Enum PR)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  Assert_Param(IS_GPIO_PR(PR)) ;

  if(PR == GPIO_PR_UP)
  {
    GPIOx->PUR |= GPIO_PIN ;
    GPIOx->PDR &= ~GPIO_PIN ;
  }
  else if(PR == GPIO_PR_DOWN)
  {
    GPIOx->PDR |= GPIO_PIN ;
    GPIOx->PUR &= ~GPIO_PIN ;
  }
  else
  {
    GPIOx->PUR &= ~GPIO_PIN ;
    GPIOx->PDR &= ~GPIO_PIN ;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the input control of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPIO_InputConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  Assert_Param(IS_CONTROL_STATUS(Cmd)) ;

  if(Cmd != DISABLE)
    GPIOx->INER |= GPIO_PIN ;
  else
    GPIOx->INER &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Select the driving current of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Drive: This parameter can be one of below:
 *        @arg GPIO_DV_4MA  : Selects output driving current as 4 mA
 *        @arg GPIO_DV_8MA  : Selects output driving current as 8 mA
 * @retval None
 ************************************************************************************************************/
void GPIO_DriveConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DV_Enum Drive)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  Assert_Param(IS_GPIO_DV(Drive)) ;

  if(Drive != GPIO_DV_4MA)
    GPIOx->DRVR |= GPIO_PIN ;
  else
    GPIOx->DRVR &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the open drain function of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPIO_OpenDrainConfig(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  Assert_Param(IS_CONTROL_STATUS(Cmd)) ;

  if(Cmd != DISABLE)
    GPIOx->ODR |= GPIO_PIN ;
  else
    GPIOx->ODR &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Get the input data of specified port pin.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: This parameter can be GPIO_PIN_x where x can be 0 ~ 15.
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus GPIO_ReadInBit(GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  if ((GPIOx->DINR & GPIO_PIN) != RESET)
    return SET;
  else
    return RESET;
}

/*********************************************************************************************************//**
 * @brief Get the input data of specified GPIO port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @return The value of input data register.
 ************************************************************************************************************/
u16 GPIO_ReadInData(GPIO_TypeDef* GPIOx)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  return ((u16)GPIOx->DINR);
}

/*********************************************************************************************************//**
 * @brief Get the output data of specified port pin.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: This parameter can be GPIO_PIN_x where x can be 0 ~ 15.
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus GPIO_ReadOutBit(GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  if ((GPIOx->DOTR & GPIO_PIN) != RESET)
    return SET;
  else
    return RESET;
}

/*********************************************************************************************************//**
 * @brief Get the output data of specified GPIO port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @return The value of output data register.
 ************************************************************************************************************/
u16 GPIO_ReadOutData(GPIO_TypeDef* GPIOx)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  return ((u16)GPIOx->DOTR);
}

/*********************************************************************************************************//**
 * @brief Set the selected port bits of output data.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: Specify the port bit to be set.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @retval None
 ************************************************************************************************************/
void GPIO_SetOutBits(GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  Assert_Param(IS_GPIO(GPIOx)) ;
  GPIOx->SRR = GPIO_PIN;
}

/*********************************************************************************************************//**
 * @brief Clear the selected port bits of output data.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: Specify the port bit to be clear.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @retval None
 ************************************************************************************************************/
void GPIO_ClearOutBits(GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  GPIOx->RR = GPIO_PIN;
}

/*********************************************************************************************************//**
 * @brief Set or Clear the selected port bits of data.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: Specify the port bits.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Status: Specify the value to be put to the selected bits.
 *        This parameter can be one of below:
 *        @arg RESET : To clear the port pins
 *        @arg SET   : To set the port pins
 * @retval None
 ************************************************************************************************************/
void GPIO_WriteOutBits(GPIO_TypeDef* GPIOx, u16 GPIO_PIN, FlagStatus Status)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  if (Status != RESET)
    GPIOx->SRR = GPIO_PIN;
  else
    GPIOx->RR = GPIO_PIN;
}

/*********************************************************************************************************//**
 * @brief Put data to the specified GPIO data port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param Data: Specify the data to be written to the port data register.
 * @retval None
 ************************************************************************************************************/
void GPIO_WriteOutData(GPIO_TypeDef* GPIOx, u16 Data)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  GPIOx->DOTR = Data;
}

/*********************************************************************************************************//**
 * @brief Select the GPIO pin to be used as EXTI channel.
 * @param Channel: Specify the EXTI channel to be configured.
 *        This parameter can be AFIO_EXTI_CH_x where x can be 0 ~ 15.
 * @param Source: Select the GPIO port to be used for EXTI channel.
 *        This parameter can be AFIO_ESS_Px where x can be A ~ B.
 * @retval None
 ************************************************************************************************************/
void AFIO_EXTISourceConfig(AFIO_EXTI_CH_Enum Channel, AFIO_ESS_Enum Source)
{
  u8 index = 0 ;
  u32 tmp = 0 ;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_AFIO_ESS(Source));
  Assert_Param(IS_AFIO_EXTI_CH(Channel));

  if(Channel > AFIO_EXTI_CH_7)
  {
    index = 1 ;
    Channel -= AFIO_EXTI_CH_8 ;
  }

  tmp = AFIO->ESSR[index] ;
  tmp &= ~((u32)0x0F << Channel) ;
  tmp |= (u32)Source << Channel ;
  AFIO->ESSR[index] = tmp ;

}

/*********************************************************************************************************//**
 * @brief Lock configuration of GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: Specify the port bits.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @retval None
 ************************************************************************************************************/
void GPIO_PinLock(GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  GPIOx->LOCKR = (u32)0x5FA00000 | GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Get the lock state of specified GPIO port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @return TRUE or FALSE
 ************************************************************************************************************/
bool GPIO_IsPortLocked(GPIO_TypeDef* GPIOx)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  if((GPIOx->LOCKR >> 16) == 0)
    return FALSE ;
  else
    return TRUE ;
}

/*********************************************************************************************************//**
 * @brief Get the lock state of specified GPIO port pin.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A or B.
 * @param GPIO_PIN: This parameter can be GPIO_PIN_x where x can be 0 ~ 15.
 * @return TRUE or FALSE
 ************************************************************************************************************/
bool GPIO_IsPinLocked(GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  Assert_Param(IS_GPIO(GPIOx)) ;

  if((GPIOx->LOCKR & GPIO_PIN) == 0)
    return FALSE ;
  else
    return TRUE ;
}

/*********************************************************************************************************//**
 * @brief Deinitialize the AFIO peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void AFIO_DeInit(void)
{
  RSTCU_APBPerip0Reset(RSTCU_APBRST0_AFIO, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIOA with specified pins.
 * @param AFIO_PIN: This parameter can be any combination of AFIO_PIN_x where x can be 0 ~ 15.
 * @param AFIO_MODE: This parameter can be one of the following values:
          @arg AFIO_MODE_DEFAULT : The default I/O function
          @arg AFIO_MODE_1       : Alternated mode 1
          @arg AFIO_MODE_2       : Alternated mode 2
          @arg AFIO_MODE_3       : Alternated mode 3
 * @retval None
 ************************************************************************************************************/
void AFIO_GPAConfig(u32 AFIO_PIN, u32 AFIO_MODE)
{
  /* Check the parameters*/
  Assert_Param(IS_AFIO_MODE(AFIO_MODE)) ;

  AFIO->GPACFGR = (AFIO->GPACFGR & ~AFIO_PIN) | (AFIO_MODE & AFIO_PIN);
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIOB with specified pins.
 * @param AFIO_PIN: This parameter can be any combination of AFIO_PIN_x where x can be 0 ~ 15.
 * @param AFIO_MODE: This parameter can be one of the following values:
          @arg AFIO_MODE_DEFAULT : The default I/O function
          @arg AFIO_MODE_1       : Alternated mode 1
          @arg AFIO_MODE_2       : Alternated mode 2
          @arg AFIO_MODE_3       : Alternated mode 3
 * @retval None
 ************************************************************************************************************/
void AFIO_GPBConfig(u32 AFIO_PIN, u32 AFIO_MODE)
{
  /* Check the parameters*/
  Assert_Param(IS_AFIO_MODE(AFIO_MODE)) ;

  AFIO->GPBCFGR = (AFIO->GPBCFGR & ~AFIO_PIN) | (AFIO_MODE & AFIO_PIN);
}

/**
  * @}
  *//* End of GPIO_Private_Function group */

/**
  * @}
  *//* End of GPIO group */

/**
  * @}
  *//* End of HT32F125x_Peripheral_Driver group */
