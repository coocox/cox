/*****************************************************************************//**
 * @file    ht32f125x_i2c.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the firmware functions about I2C.
 **********************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 *********************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_i2c.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_rstcu.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup  I2C I2C
  * @brief I2C driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup I2C_Private_TypesDefinitions I2C private types definitions
  * @{
  */

/**
  * @}
  */

/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup I2C_Private_Define I2C private definitions
  * @{
  */

/* I2C ENI2C mask */
#define CR_ENI2C_SET             ((u32)0x00000008)
#define CR_ENI2C_RESET           ((u32)0xFFFFFFF7)

/* I2C ENGC mask */
#define CR_ENGC_SET              ((u32)0x00000004)
#define CR_ENGC_RESET            ((u32)0xFFFFFFFB)

/* I2C AA mask */
#define CR_ACK_SET               ((u32)0x00000001)
#define CR_ACK_RESET             ((u32)0xFFFFFFFE)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup I2C_Private_Macro I2C private macros
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup I2C_Private_Variable I2C private variables
  * @{
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup I2C_Private_Function_Prototype I2C private function prototypes
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup I2C_Private_Function I2C private functions
  * @{
  */

/*********************************************************************************************************//**
  * @brief  Deinitialize the I2C peripheral registers to their default reset values.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @retval None
  ***********************************************************************************************************/
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));

  RSTCU_APBPerip0Reset(RSTCU_APBRST0_I2C, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Initialize the I2Cx peripheral according to the specified parameters in the I2C_InitStruct.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that contains the configuration
  *   information for the specified I2C peripheral.
  * @retval None
  ***********************************************************************************************************/
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  u32 tmpreg;
  CKCU_ClocksTypeDef CKCU_ClockFreq;

  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_GENERAL_CALL(I2C_InitStruct->I2C_GeneralCall));
  Assert_Param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AddressingMode));
  Assert_Param(IS_I2C_ACKNOWLEDGE(I2C_InitStruct->I2C_Acknowledge));
  Assert_Param(IS_I2C_ADDRESS(I2C_InitStruct->I2C_OwnAddress));
  Assert_Param(IS_I2C_SPEED(I2C_InitStruct->I2C_Speed));

  /* Enable I2Cx peripheral */
  I2C_Cmd(I2Cx, ENABLE);

  /*------------------------ I2Cx Control Register Configuration --------------------------------------------*/
  tmpreg = I2Cx->CR;
  tmpreg &= 0xFFFFFF7A;
  tmpreg |= I2C_InitStruct->I2C_GeneralCall | I2C_InitStruct->I2C_AddressingMode | I2C_InitStruct->I2C_Acknowledge;
  I2Cx->CR = tmpreg;

  /*------------------------ I2Cx Slave Address Register Configuration --------------------------------------*/
  I2Cx->ADDR = I2C_InitStruct->I2C_OwnAddress;

  /*------------------------ I2Cx SCL High & Low Period Generation Register Configuration -------------------*/
  CKCU_GetClocksFrequency(&CKCU_ClockFreq);
  I2Cx->SHPGR = (CKCU_ClockFreq.HCLK_Freq*2)/(I2C_InitStruct->I2C_Speed*5) -7;
  I2Cx->SLPGR = (CKCU_ClockFreq.HCLK_Freq*3)/(I2C_InitStruct->I2C_Speed*5) -7;
}

/*********************************************************************************************************//**
  * @brief  Fill each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  ***********************************************************************************************************/
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
  /* Initialize the I2C_GeneralCall member */
  I2C_InitStruct->I2C_GeneralCall = I2C_GENERALCALL_DISABLE;

  /* Initialize the I2C_AddressingMode member */
  I2C_InitStruct->I2C_AddressingMode = I2C_ADDRESSING_7BIT;

  /* Initialize the I2C_Acknowledge member */
  I2C_InitStruct->I2C_Acknowledge = I2C_ACK_DISABLE;

  /* Initialize the I2C_OwnAddress member */
  I2C_InitStruct->I2C_OwnAddress = 0;

  /* Initialize the I2C_Speed member */
  I2C_InitStruct->I2C_Speed = 1000000;
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the specified I2C peripheral.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void I2C_Cmd(I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CR |= CR_ENI2C_SET;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CR &= CR_ENI2C_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Generate STOP condition of I2C communication.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @retval None
  ***********************************************************************************************************/
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));

  I2Cx->CR |= 0x2;
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable I2C interrupts.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Int: Specify if the I2C interrupt source to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_INT_STA
  *     @arg I2C_INT_STO
  *     @arg I2C_INT_ADRS
  *     @arg I2C_INT_GCS
  *     @arg I2C_INT_ARBLOS
  *     @arg I2C_INT_RXNACK
  *     @arg I2C_INT_BUSERR
  *     @arg I2C_INT_RXDNE
  *     @arg I2C_INT_TXDE
  *     @arg I2C_INT_RXBF
  *     @arg I2C_INT_ALL
  * @param  NewState: new state of the I2C interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void I2C_IntConfig(I2C_TypeDef* I2Cx, u32 I2C_Int, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_INT(I2C_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->IER |= I2C_Int;
  }
   else
  {
    I2Cx->IER &= (u32)~I2C_Int;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable I2C General Call.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  NewState: new state of the I2C General Call.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_ENGC_SET;
  }
  else
  {
    I2Cx->CR &= CR_ENGC_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable I2C sending acknowledgment.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  NewState: new state of the I2C acknowledge.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void I2C_AckCmd(I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_ACK_SET;
  }
  else
  {
    I2Cx->CR &= CR_ACK_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Configure own address of the specified I2C.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Address: Specify own address of I2C.
  * @retval None
  ***********************************************************************************************************/
void I2C_SetOwnAddress(I2C_TypeDef* I2Cx, u16 I2C_Address)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_ADDRESS(I2C_Address));

  I2Cx->ADDR = I2C_Address;
}

/*********************************************************************************************************//**
  * @brief  Start transmitting to target slave address.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Address: Specify the slave address which will be transmitted.
  * @param  I2C_Direction: Specify whether the Master I2C device will read or write.
  * @retval None
  ***********************************************************************************************************/
void I2C_TargetAddressConfig(I2C_TypeDef* I2Cx, u16 I2C_Address, u32 I2C_Direction)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_ADDRESS(I2C_Address));
  Assert_Param(IS_I2C_DIRECTION(I2C_Direction));

  if (I2C_Direction != I2C_MASTER_WRITE)
  {
    I2Cx->TAR = I2C_Address | I2C_MASTER_READ;
  }
   else
  {
    I2Cx->TAR = I2C_Address | I2C_MASTER_WRITE;
  }
}

/*********************************************************************************************************//**
  * @brief  Send a data word through the I2Cx peripheral.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Data: Byte to be transmitted.
  * @retval None
  ***********************************************************************************************************/
void I2C_SendData(I2C_TypeDef* I2Cx, u8 I2C_Data)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));

  I2Cx->DR = I2C_Data;
}

/*********************************************************************************************************//**
  * @brief  Return the received data by the I2Cx peripheral.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @retval The value of the received data.
  ***********************************************************************************************************/
u8 I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));

  return (u8)I2Cx->DR;
}

/*********************************************************************************************************//**
  * @brief  Read the specified I2C register and returns its value.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Register: Specify the register to read.
  *   This parameter can be one of the following values:
  *     @arg I2C_REGISTER_CR              : Control Register
  *     @arg I2C_REGISTER_IER             : Interrupt Enable Register
  *     @arg I2C_REGISTER_ADDR            : Address Register
  *     @arg I2C_REGISTER_SR              : Status Register
  *     @arg I2C_REGISTER_SHPGR           : SCL High Period Generation Register
  *     @arg I2C_REGISTER_SLPGR           : SCL Low Period Generation Register
  *     @arg I2C_REGISTER_DR              : Data Register
  *     @arg I2C_REGISTER_TAR             : Target Register
  * @retval None
  ***********************************************************************************************************/
u32 I2C_ReadRegister(I2C_TypeDef* I2Cx, u8 I2C_Register)
{
  vu32 tmp = 0;
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_REGISTER(I2C_Register));

  tmp = (u32) I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(vu32 *) tmp);
}

/*********************************************************************************************************//**
  * @brief  Check whether the specified I2C flag has been set.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Flag: Specify the flag to be check.
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_STA               : I2C start condition transmitted flag (Master mode)
  *     @arg I2C_FLAG_STO                 : I2C stop condition detected flag (Slave flag)
  *     @arg I2C_FLAG_ADRS                : I2C address flag
  *     @arg I2C_FLAG_GCS                 : I2C general call flag (Slave mode)
  *     @arg I2C_FLAG_ARBLOS              : I2C arbitration loss flag (Master mode)
  *     @arg I2C_FLAG_RXNACK              : I2C received not acknowledge flag
  *     @arg I2C_FLAG_BUSERR              : I2C bus error flag
  *     @arg I2C_FLAG_RXDNE               : I2C Rx data not empty flag
  *     @arg I2C_FLAG_TXDE                : I2C Tx data empty flag
  *     @arg I2C_FLAG_RXBF                : I2C RX buffer full flag
  *     @arg I2C_FLAG_BUSBUSY             : I2C bus busy flag
  *     @arg I2C_FLAG_MASTER              : I2C master mode flag (Master flag)
  *     @arg I2C_FLAG_TXNRX               : I2C transmitter mode flag
  * @retval The new state of I2C_Flag (SET or RESET).
  ***********************************************************************************************************/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, u32 I2C_Flag)
{
  u32 statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_FLAG(I2C_Flag));

  statusreg = I2Cx->SR;

  if ( (statusreg & I2C_Flag) != (u32)RESET )
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*********************************************************************************************************//**
  * @brief  Check whether the specified I2C status has been active .
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Status: Specify the flag that is to be check.
  *   This parameter can be one of the following values:
  *     @arg I2C_MASTER_SEND_START
  *     @arg I2C_MASTER_RECEIVER_MODE
  *     @arg I2C_MASTER_TRANSMITTER_MODE
  *     @arg I2C_MASTER_RX_NOT_EMPTY
  *     @arg I2C_MASTER_RX_NOT_EMPTY_NOBUSY
  *     @arg I2C_MASTER_TX_EMPTY
  *     @arg I2C_MASTER_RX_BUFFER_FULL
  *     @arg I2C_SLAVE_ACK_TRANSMITTER_ADDESS
  *     @arg I2C_SLAVE_ACK_RECEIVER_ADDRESS
  *     @arg I2C_SLAVE_ACK_GCALL_ADDRESS
  *     @arg I2C_SLAVE_RX_NOT_EMPTY
  *     @arg I2C_SLAVE_RX_NOT_EMPTY_STOP
  *     @arg I2C_SLAVE_TX_EMPTY
  *     @arg I2C_SLAVE_BUFFER_FULL
  *     @arg I2C_SLAVE_RECEIVED_NACK
  *     @arg I2C_SLAVE_RECEIVED_NACK_STOP
  *     @arg I2C_SLAVE_STOP_DETECED
  * @retval An ErrorStatus enumuration value:
  *   SUCCESS: Last event is equal to the I2C_Event
  *   ERROR: Last event is different from the I2C_Event
  ***********************************************************************************************************/
ErrStatus I2C_CheckStatus(I2C_TypeDef* I2Cx, u32 I2C_Status)
{
  u32 statusreg = 0;
  ErrStatus status = ERROR;

  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_STATUS(I2C_Status));

  statusreg = I2Cx->SR;

  if ( statusreg == I2C_Status )
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }

  return status;
}

/*********************************************************************************************************//**
  * @brief  Clear the specified I2C flag.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_Flag: Specify the flag that is to be cleared.
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_ARBLOS             : I2C arbitration flag
  *     @arg I2C_FLAG_RXNACK             : I2C receive not acknowledge flag
  *     @arg I2C_FLAG_BUSERR             : I2C Bus error flag
  * @retval None
  ***********************************************************************************************************/
void I2C_ClearFlag(I2C_TypeDef* I2Cx, u32 I2C_Flag)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_CLEAR_FLAG(I2C_Flag));

  I2Cx->SR = I2C_Flag;
}

/*********************************************************************************************************//**
  * @brief  Set the interval timing of the high period of the I2C clock.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_HighPeriod: Specify the high period that is to be set.
      This parameter must be a number between 0 and 0xFFFF.
  * @retval None
  ***********************************************************************************************************/
void I2C_SetSCLHighPeriod(I2C_TypeDef* I2Cx, u32 I2C_HighPeriod)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_SCL_HIGH(I2C_HighPeriod));
 
  I2Cx->SHPGR = I2C_HighPeriod;
}

/*********************************************************************************************************//**
  * @brief  Set the interval timing of low period of the I2C clock.
  * @param  I2Cx: where I2Cx is the selected I2C from the I2C peripheral.
  * @param  I2C_LowPeriod: Specify the low period that is to be set.
      This parameter must be a number between 0 and 0xFFFF.
  * @retval None
  ***********************************************************************************************************/
void I2C_SetSCLLowPeriod(I2C_TypeDef* I2Cx, u32 I2C_LowPeriod)
{
  /* Check the parameters */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_SCL_LOW(I2C_LowPeriod));
 
  I2Cx->SLPGR = I2C_LowPeriod;
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
