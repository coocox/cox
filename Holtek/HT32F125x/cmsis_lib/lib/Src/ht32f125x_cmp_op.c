/*********************************************************************************************************//**
 * @file    ht32f125x_cmp_op.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the firmware functions about CMP_OP.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_cmp_op.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_misc.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup  CMP_OP CMP_OP
  * @brief CMP_OP driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Private_TypesDefinitions CMP_OP private types definitions
  * @{
  */

/**
  * @}
  */


/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Private_Define CMP_OP private definitions
  * @{
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Private_Macro CMP_OP private macros
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Private_Variable CMP_OP private variables
  * @{
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Private_Function_Prototype CMP_OP private function prototypes
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup CMP_OP_Private_Function CMP_OP private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitialize the CMP_OP peripheral registers to their default reset values.
 * @param CMP_OPx: where x can be 0 or 1 to select the CMP_OP peripheral.
 * @retval None
 ************************************************************************************************************/
void CMP_OP_DeInit(CMP_OP_TypeDef* CMP_OPx)
{
  /* Check the parameters */   
 Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));

  if(CMP_OPx == CMP_OP0)
  {
    RSTCU_APBPerip1Reset(RSTCU_APBRST1_OPA0, ENABLE);
  }
  else
  {
    RSTCU_APBPerip1Reset(RSTCU_APBRST1_OPA1, ENABLE);
  }  
}

/*********************************************************************************************************//**
 * @brief Initialize the CMP_OPx peripheral according to the specified parameters in the CMP_OP_InitStruct.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_InitStruct pointer to a CMP_OP_InitTypeDef structure that contains the configuration information
 *        for the specified CMP_OP peripheral.
 * @retval None
************************************************************************************************************/
void CMP_OP_Init(CMP_OP_TypeDef* CMP_OPx, CMP_OP_InitTypeDef* CMP_OP_InitStruct)
{
 u16 delayc=0;

 /* Check the parameters */   
 Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));

 CMP_OPx->OPAC =(CMP_OP_InitStruct->CMP_OP_Enable|CMP_OP_InitStruct->CMP_OP_CMPOPMode|CMP_OP_InitStruct->CMP_OP_CancellOPAMode|CMP_OP_InitStruct->CMP_OP_RefSelect);
 CMP_OPx->OFVC =(CMP_OP_InitStruct->CMP_OP_Cancellation);
 for(delayc=0 ;delayc<500 ;delayc++)
 {
 }
 CMP_OPx->CMPICLR = 0x03;
 CMP_OPx->CMPIM = 0x00;
 CMP_OPx->CMPIM =(CMP_OP_InitStruct->CMP_OP_RisingInterruptMask |CMP_OP_InitStruct->CMP_OP_FallingInterruptMask);
}

/*********************************************************************************************************//**
 * @brief Cancellation of CMP_OPx peripheral that will decrease the offset between CP and CN.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_REF_INPUT: Specify the CMP_OP reference input for cancellation.
 *        This parameter can be any combination of the following values:
 *        - NEGATIVE_INPUT:
 *        - POSITIVE_INPUT:
 * @retval None
************************************************************************************************************/
u16 CMP_OP_Cancellation(CMP_OP_TypeDef* CMP_OPx, u16 CMP_OP_REF_INPUT)
{
  CKCU_ClocksTypeDef Clocks;
  u16 i=0,temp=0,temp1=0;

  /* Check the parameters */   
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));
  Assert_Param(IS_CMP_OP_REF(CMP_OP_REF_INPUT));  
    
  CKCU_GetClocksFrequency(&Clocks);
  SYSTICK_ClockSourceConfig(SYSTICK_SRC_FCLK);
  SYSTICK_SetReloadValue(Clocks.HCLK_Freq/1000);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);

  temp1=CMP_OPx->OPAC;
  CMP_OPx->CMPIM =0x00;
  CMP_OPx->CMPICLR = 0x03;
  CMP_OPx->OPAC =(CMP_OPx->OPAC&0x01)|(CMP_OP_ENABLE|OP_MODE|CANCELLATION_MODE|CMP_OP_REF_INPUT);
  CMP_OPx->OFVC =0x00;
  while (temp ==0)
  {
    CMP_OPx->OFVC = i;
    while(!(SysTick->CTRL&0x00010000));
    temp =(CMP_OPx->OPAC&0x0100);
    i++;
    if(i >64){temp = 1;} 
  }
  SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);
  CMP_OPx->OPAC=temp1;

  return ((u16)i-1) ;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified CMP_OP interrupts.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_INT: Specify the CMP_OP interrupt sources that is to be enabled or disabled.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_INT_FALLING:
 *        - CMP_OP_INT_RISING:
 * @param NewState new state of the specified ADC interrupts.
 *        This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void CMP_OP_IntConfig(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT, ControlStatus NewState)
{
  /* Check the parameters */   
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx)); 
  Assert_Param(IS_CMP_OP_INT(CMP_OP_INT));  
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if(NewState != DISABLE)
  {
    CMP_OPx->CMPIM |= CMP_OP_INT ;
  }
  else
  {
    CMP_OPx->CMPIM &= ~CMP_OP_INT ;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified ADC interrupt has occurred.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_INT: Specify the interrupt status to check.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_INT_FALLING:
 *        - CMP_OP_INT_RISING:
 * @retval SET or RESET
************************************************************************************************************/
FlagStatus CMP_OP_GetIntStatus(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT)
{
  FlagStatus Status;

  /* Check the parameters */   
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));  
  Assert_Param(IS_CMP_OP_INT(CMP_OP_INT)); 

  if((CMP_OPx->CMPIMASK & CMP_OP_INT) != 0x0)
  {
    Status = SET ;
  }
  else
  {
    Status = RESET ;
  }

  return Status ;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified CMP_OP flag has been set.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_FLAG: Specify the flag to check.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_FLAG_FALLING:
 *        - CMP_OP_FLAG_RISING:
 * @retval SET or RESET
************************************************************************************************************/
FlagStatus CMP_OP_GetFlagStatus(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_FLAG)
{
  FlagStatus Status;

  /* Check the parameters */   
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx)); 
  Assert_Param(IS_CMP_OP_FLAG(CMP_OP_FLAG)); 
     
  if((CMP_OPx->CMPIRAW & CMP_OP_FLAG) != 0x0)
  {
    Status = SET ;
  }
  else
  {
    Status = RESET ;
  }

  return Status ;
}


/*********************************************************************************************************//**
 * @brief Clear the CMP_OPx interrupt pending bits.
 * @param CMP_OPx: where CMP_OPx is the selected CMP_OP from the CMP_OP peripherals, x can be 0 or 1.
 * @param CMP_OP_INT: specifies the interrupt pending bits to be cleared.
 *        This parameter can be any combination of the following values:
 *        - CMP_OP_INT_FALLING:
 *        - CMP_OP_INT_RISING:
 * @retval None
************************************************************************************************************/
void CMP_OP_ClearIntPendingBit(CMP_OP_TypeDef* CMP_OPx, u32 CMP_OP_INT)
{
  /* Check the parameters */   
  Assert_Param(IS_CMP_OP_ALL_PERIPH(CMP_OPx));  
  Assert_Param(IS_CMP_OP_INT(CMP_OP_INT));  

  CMP_OPx->CMPICLR = CMP_OP_INT ;
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
