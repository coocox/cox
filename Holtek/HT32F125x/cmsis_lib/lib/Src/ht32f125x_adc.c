/*********************************************************************************************************//**
 * @file    ht32f125x_adc.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the firmware functions about ADC.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_adc.h"
#include "ht32f125x_rstcu.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup  ADC ADC
  * @brief ADC driver modules
  * @{
  */

/** @defgroup ADC_Private_TypesDefinitions ADC private types definitions
  * @{
  */

/**
  * @}
  *//* End of ADC_Private_TypesDefinitions group */

/** @defgroup ADC_Private_Define ADC private definitions
  * @{
  */
#define ADC_SOFTWARE_RESET   (u32)0x00000001
#define LST_SEQ_SET          (u32)0x0000001F
#define RST_SET              (u32)0x00000001
#define TCR_SC_SET           (u32)0x00000001
#define HTCR_HSC_SET         (u32)0x00000001
/* ADC ADON mask */
#define ADC1_ON              ((u32)0x1 << 19 )

/**
  * @}
  *//* End of GPIO_Private_Define group */

/** @defgroup ADC_Private_Macro ADC private macros
  * @{
  */

/**
  * @}
  *//* End of GPIO_Private_Macro group */

/** @defgroup ADC_Private_Variable ADC private variables
  * @{
  */

/**
  * @}
  */


/** @defgroup ADC_Private_Function_Prototype ADC private function prototypes
  * @{
  */

/**
  * @}
  */


/** @defgroup ADC_Private_Function ADC private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitialize the ADCx peripheral registers to their default reset values.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @retval None
 ************************************************************************************************************/
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));

  RSTCU_APBPerip1Reset(RSTCU_APBRST1_ADC, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the ADC peripheral according to the specified parameters in the ADC_InitStruct.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_InitStructure: pointer to a ADC_InitTypeDef structure that contains the configuration information
 *        for the specified ADC peripheral.
 * @retval None
 ************************************************************************************************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure)
{ 
  u32 tmpreg = 0x00;
  /* Check the parameters */  
  Assert_Param(IS_ADC(ADCx));

  /*---------------------------- ADC Regular CONF Configuration --------------------------------------------*/
  tmpreg &= 0x00;

  tmpreg |= (u32)ADC_InitStructure->ADC_ConversionMode;

  ADCx->CONV = tmpreg;

  /*---------------------------- ADC High-priority CONF Configuration --------------------------------------*/
  tmpreg &= 0x00;

  tmpreg |= (u32)ADC_InitStructure->ADC_HPCCMode;

  ADCx->HCONV = tmpreg;

  /*---------------------------- ADC Trigger Control TCR Configuration -------------------------------------*/
  tmpreg &= 0x00;

  tmpreg |= (u32)ADC_InitStructure->ADC_TriggerMode;

  ADCx->TCR = tmpreg;
  /*---------------------------- ADC Trigger Control TSR Configuration -------------------------------------*/
  tmpreg &= 0x00;

  tmpreg |= (u32)ADC_InitStructure->ADC_ExtiTriggerSource;
  tmpreg |= (u32)ADC_InitStructure->ADC_ETPUTriggerChannel;
  tmpreg |= (u32)ADC_InitStructure->ADC_TPTriggerChannel;
  ADCx->TSR = tmpreg;

  /*---------------------------- ADC Trigger Control TCR Configuration -------------------------------------*/
  tmpreg &= 0x00;
  tmpreg |= (u32)ADC_InitStructure->ADC_HPTriggerMode;

  ADCx->HTCR = tmpreg;
  /*---------------------------- ADC Trigger Control TSR Configuration -------------------------------------*/
  tmpreg &= 0x00;
  tmpreg |= (u32)ADC_InitStructure->ADC_HPExtiTriggerSource;
  tmpreg |= (u32)ADC_InitStructure->ADC_HPETPUTriggerChannel;
  tmpreg |= (u32)ADC_InitStructure->ADC_HPTPTriggerChannel;
  ADCx->HTSR = tmpreg;
}

/*********************************************************************************************************//**
 * @brief Reset ADC.
 * @param ADCx: is the selected ADC from the ADC peripherals.
 * @retval None
 ************************************************************************************************************/
void ADC_Reset(ADC_TypeDef* ADCx)
{
  /* Check the parameters */ 
  Assert_Param(IS_ADC(ADCx));

  /*---------------------------- Reset ADC -----------------------------------------------------------------*/                                                                                       
  ADCx->RST |= ADC_SOFTWARE_RESET;
}


/*********************************************************************************************************//**
 * @brief Enable or Disable the specified ADC interrupts.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_INT: Specify the ADC interrupt sources that is to be enabled or disabled.
          this parameter can be any combination of the following values:
             @arg ADC_INT_SINGLE_EOC:
             @arg ADC_INT_SUB_GROUP_EOC:
             @arg ADC_INT_CYCLE_EOC:
             @arg ADC_INT_DATA_OVERWRITE:
             @arg ADC_INT_HP_SINGLE_EOC:
             @arg ADC_INT_HP_SUB_GROUP_EOC:
             @arg ADC_INT_HP_CYCLE_EOC:
             @arg ADC_INT_HP_DATA_OVERWRITE:
             @arg ADC_INT_AWD_LOWER:
             @arg ADC_INT_AWD_UPPER:
 * @param NewState new state of the specified ADC interrupts.
          This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_IntConfig(ADC_TypeDef* ADCx, u32 ADC_INT, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_INT(ADC_INT));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if(NewState != DISABLE)
  {
    ADCx->IM |= ADC_INT ;
  }
  else
  {
    ADCx->IM &= ~ADC_INT ;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified ADC interrupt has occurred.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_INT: Specify the interrupt status to check.
                     This parameter can be any combination of the following values:
                     @arg ADC_INT_SINGLE_EOC:
                     @arg ADC_INT_SUB_GROUP_EOC:
                     @arg ADC_INT_CYCLE_EOC:
                     @arg ADC_INT_DATA_OVERWRITE:
                     @arg ADC_INT_HP_SINGLE_EOC:
                     @arg ADC_INT_HP_SUB_GROUP_EOC:
                     @arg ADC_INT_HP_CYCLE_EOC:
                     @arg ADC_INT_HP_DATA_OVERWRITE:
                     @arg ADC_INT_AWD_LOWER:
                     @arg ADC_INT_AWD_UPPER:
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus ADC_GetIntStatus(ADC_TypeDef* ADCx, u32 ADC_INT)
{
  FlagStatus Status;

  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_INT(ADC_INT));

  if((ADCx->IMASK & ADC_INT) != 0x0)
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
 * @brief Check whether the specified ADC flag has been set.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_FLAG: Specify the flag to check.
          This parameter can be any combination of the following values:
             @arg ADC_FLAG_SINGLE_EOC:
             @arg ADC_FLAG_SUB_GROUP_EOC:
             @arg ADC_FLAG_CYCLE_EOC:
             @arg ADC_FLAG_DATA_OVERWRITE:
             @arg ADC_FLAG_HP_SINGLE_EOC:
             @arg ADC_FLAG_HP_SUB_GROUP_EOC:
             @arg ADC_FLAG_HP_CYCLE_EOC:
             @arg ADC_FLAG_HP_DATA_OVERWRITE:
             @arg ADC_FLAG_AWD_LOWER:
             @arg ADC_FLAG_AWD_UPPER:
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, u32 ADC_FLAG)
{
  FlagStatus Status;

  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_FLAG(ADC_FLAG));

  if((ADCx->IRAW & ADC_FLAG) != 0x0)
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
 * @brief Clear the ADCx interrupt pending bits.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_INT: Specify the interrupt pending bits to be cleared.
          This parameter can be any combination of the following values:
             @arg ADC_INT_SINGLE_EOC:
             @arg ADC_INT_SUB_GROUP_EOC:
             @arg ADC_INT_CYCLE_EOC:
             @arg ADC_INT_DATA_OVERWRITE:
             @arg ADC_INT_HP_SINGLE_EOC:
             @arg ADC_INT_HP_SUB_GROUP_EOC:
             @arg ADC_INT_HP_CYCLE_EOC:
             @arg ADC_INT_HP_DATA_OVERWRITE:
             @arg ADC_INT_AWD_LOWER:
             @arg ADC_INT_AWD_UPPER:
 * @retval None
 ************************************************************************************************************/
void ADC_ClearIntPendingBit(ADC_TypeDef* ADCx, u32 ADC_INT)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_INT(ADC_INT));

  ADCx->ICLR = ADC_INT ;
}

/*********************************************************************************************************//**
 * @brief Clear the ADC pending flags.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_FLAG: Specify the interrupt pending bits to be cleared.
          This parameter can be any combination of the following values:
             @arg ADC_FLAG_SINGLE_EOC:
             @arg ADC_FLAG_SUB_GROUP_EOC:
             @arg ADC_FLAG_CYCLE_EOC:
             @arg ADC_FLAG_DATA_OVERWRITE:
             @arg ADC_FLAG_HP_SINGLE_EOC:
             @arg ADC_FLAG_HP_SUB_GROUP_EOC:
             @arg ADC_FLAG_HP_CYCLE_EOC:
             @arg ADC_FLAG_HP_DATA_OVERWRITE:
             @arg ADC_FLAG_AWD_LOWER:
             @arg ADC_FLAG_AWD_UPPER:
 * @retval None
 ************************************************************************************************************/
void ADC_ClearFlag(ADC_TypeDef* ADCx, u32 ADC_FLAG)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_FLAG(ADC_FLAG));

  ADCx->ICLR = ADC_FLAG ;
}

/*********************************************************************************************************//**
 * @brief Configure the ADCx external trigger for regular channels conversion.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_ExtTrigRegularConv:
          This parameter can be one of the following values:
            @arg ADC_EXT_TRIG_NONE       : Trigger disable
            @arg ADC_EXT_TRIG_SW         : S/W trigger
            @arg ADC_EXT_TRIG_GPTMx_TRGO : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH1O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH2O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH3O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH4O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_EXTI_x     : where x can be 0 ~ 15
 * @retval None
 ************************************************************************************************************/
void ADC_ExtTrigRegularConvConfig(ADC_TypeDef* ADCx, u32 ADC_ExtTrigRegularConv)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_EXT_TRIG(ADC_ExtTrigRegularConv));

  /* Config external trigger conversion source of regular group */
  ADCx->TCR = ADC_ExtTrigRegularConv >> 28 ;
  ADCx->TSR = ADC_ExtTrigRegularConv ;
}

/*********************************************************************************************************//**
 * @brief Configure the ADCx external trigger for high priority channels conversion.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_ExtTrigHPConv: 
          This parameter can be one of the following values:
            @arg ADC_EXT_TRIG_NONE       : Trigger disable
            @arg ADC_EXT_TRIG_SW         : S/W trigger
            @arg ADC_EXT_TRIG_GPTMx_TRGO : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH1O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH2O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH3O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_GPTMx_CH4O : where x can be 0 ~ 1
            @arg ADC_EXT_TRIG_EXTI_x     : where x can be 0 ~ 15
 * @retval None
 ************************************************************************************************************/
void ADC_ExtTrigHPConvConfig(ADC_TypeDef* ADCx, u32 ADC_ExtTrigHPConv)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_EXT_TRIG(ADC_ExtTrigHPConv));

  /* Config external trigger conversion source of high priority group */
  ADCx->HTCR = ADC_ExtTrigHPConv >> 28 ;
  ADCx->HTSR = ADC_ExtTrigHPConv ;
}

/*********************************************************************************************************//**
 * @brief Configure cyclic conversion mode and length of list queue for regular group.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_MODE: ADC Cyclic Conversion Mode
          This parameter can be one of following.
           @arg ONE_SHOT_MODE:
           @arg CONTINUOUS_MODE:
           @arg DISCONTIOUS_MODE:
 * @param Length: must between 1 ~ 16
 * @param SubLength: must between 1 ~ 16
 * @retval None
 ************************************************************************************************************/
void ADC_RegularGroupConfig(ADC_TypeDef* ADCx, u8 ADC_MODE, u8 Length, u8 SubLength)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_CYCLIC_CONVERSION_MODE(ADC_MODE));
  Assert_Param(IS_ADC_REGULAR_LENGTH(Length));
  Assert_Param(IS_ADC_REGULAR_SUB_LENGTH(SubLength));

  /* Config cyclic conversion mode and length of list queue and sub length for regular group */
  ADCx->CONV =  ((u32)(SubLength - 1) << 16) | ((u32)(Length - 1) << 8) | ADC_MODE ;
}

/*********************************************************************************************************//**
 * @brief Configure cyclic conversion mode and length of list queue for high priority group.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_MODE: ADC Cyclic Conversion Mode
          This parameter can be one of following.
           @arg ONE_SHOT_MODE:
           @arg CONTINUOUS_MODE:
           @arg DISCONTIOUS_MODE:
 * @param Length: must between 1 ~ 4
 * @param SubLength: must between 1 ~ 4
 * @retval None
 ************************************************************************************************************/
void ADC_HPGroupConfig(ADC_TypeDef* ADCx, u8 ADC_MODE, u8 Length, u8 SubLength)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_CYCLIC_CONVERSION_MODE(ADC_MODE));
  Assert_Param(IS_ADC_HP_LENGTH(Length));
  Assert_Param(IS_ADC_HP_SUB_LENGTH(SubLength));

  /* Config cyclic conversion mode and length of list queue and sub length for high priority group */
  ADCx->HCONV =  ((u32)(SubLength - 1) << 16) | ((u32)(Length - 1) << 8) | ADC_MODE ;
}

/*********************************************************************************************************//**
 * @brief Return the result of ADC high priority channel conversion.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_HP_DATAx : where x can be 0 ~ 3
 * @return The Data conversion value.
 ************************************************************************************************************/
u16 ADC_GetHPConversionData(ADC_TypeDef* ADCx, u8 ADC_HP_DATAx)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_HP_DATA(ADC_HP_DATAx));

  return ((u16)ADCx->HDR[ADC_HP_DATAx]) ;
}

/*********************************************************************************************************//**
 * @brief Return the result of ADC regular channel conversion.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_REGULAR_DATAx : where x can be 0 ~ 15
 * @return The Value of data conversion.
 ************************************************************************************************************/
u16 ADC_GetConversionData(ADC_TypeDef* ADCx, u8 ADC_REGULAR_DATAx)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_REGULAR_DATA(ADC_REGULAR_DATAx));

  return ((u16)ADCx->DR[ADC_REGULAR_DATAx]) ;
}

/*********************************************************************************************************//**
 * @brief Configure the corresponding rank in the sequencer and the sample time for the regular channel of the selected ADC.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_Channel: the ADC channel to configure
            This parameter can be one of the following values:
              @arg ADC_CH_x: ADC Channel x selected, x must between 0 ~ 7
              @arg ADC_CH_GNDREF: ADC AGNDREF selected
              @arg ADC_CH_VREF: ADC VREF selected
 * @param Rank: The rank in the regular group sequencer.
            This parameter must be between 0 to 15.
 * @param SampleClock: Number of sampling clocks.
            This parameter must be between 0x00 to 0xFF .
 * @retval None
 ************************************************************************************************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 SampleClock)
{
  u32 tmpreg1 = 0, tmpreg2 = 0 ;

  /* Check the parameters */ 
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_CHANNEL(ADC_Channel));
  Assert_Param(IS_ADC_REGULAR_RANK(Rank));
  Assert_Param(IS_ADC_INPUT_SAMPLING_TIME(SampleClock));  
  /* config sampling clock of correspond ADC input channel */
  ADCx->STR[ADC_Channel] = SampleClock ;

  /* Config ADC Rank */

  /* Get the old register value */
  tmpreg1 = ADCx->LST[Rank >> 2] ;
  /* Calculate the mask to clear */
  tmpreg2 = LST_SEQ_SET << (8 * (Rank & 0x3));
  /* Clear the old SEQx bits for the selected rank */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set */
  tmpreg2 = (u32)ADC_Channel << (8 * (Rank & 0x3));
  /* Set the SEQx bits for the selected rank */
  tmpreg1 |= tmpreg2;
  /* Store the new register value */
  ADCx->LST[Rank >> 2] = tmpreg1;
}

/*********************************************************************************************************//**
 * @brief Configure the corresponding rank in the sequencer and the sample time for the high-priority channel of the selected ADC.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_Channel: the ADC channel to configure
            This parameter can be one of the following values:
              @arg ADC_CH_x: ADC Channel x selected, x must between 0 ~ 15
              @arg ADC_CH_GNDREF: ADC AGNDREF selected
              @arg ADC_CH_VREF: ADC VREF selected
 * @param Rank: The rank in the regular group sequencer.
            This parameter must be between 0 to 3.
 * @param SampleClock: Number of sampling clocks.
            This parameter must be between 0x00 to 0xFF .
 * @retval None
 ************************************************************************************************************/
void ADC_HPChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 SampleClock)
{
  u32 tmpreg1 = 0, tmpreg2 = 0 ;

  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_CHANNEL(ADC_Channel));
  Assert_Param(IS_ADC_HIGH_PRIORITY_RANK(Rank));
  Assert_Param(IS_ADC_INPUT_SAMPLING_TIME(SampleClock)); 
  /* config sampling clock of correspond ADC input channel */
  ADCx->STR[ADC_Channel] = SampleClock ;

  /* Config ADC Rank */

  /* Get the old register value */
  tmpreg1 = ADCx->HLST ;
  /* Calculate the mask to clear */
  tmpreg2 = LST_SEQ_SET << (8 * Rank);
  /* Clear the old SEQx bits for the selected rank */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set */
  tmpreg2 = (u32)ADC_Channel << (8 * Rank);
  /* Set the SEQx bits for the selected rank */
  tmpreg1 |= tmpreg2;
  /* Store the new register value */
  ADCx->HLST = tmpreg1;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable software start of the regular channel conversion of the selected ADC .
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param NewState: new state of the selected ADC software start regular conversion.
            This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Start Conversion */
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event and starts the selected
       ADC conversion */
    ADCx->TSR |= TCR_SC_SET;
  }
  else
  {
    /* Disable the selected ADC conversion on external event and stops the selected
       ADC conversion */
    ADCx->TSR &= ~TCR_SC_SET;

  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable software start of the high priority channel conversion of the selected ADC .
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param NewState: new state of the selected ADC software start regular conversion.
            This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_SoftwareStartHPConvCmd(ADC_TypeDef* ADCx, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Start Conversion */
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event and start the selected
       ADC conversion */
    ADCx->HTSR |= HTCR_HSC_SET;
  }
  else
  {
    /* Disable the selected ADC conversion on external event and stop the selected
       ADC conversion */
    ADCx->HTSR &= ~HTCR_HSC_SET;

  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable Lower/Upper threshold warning of the analog watchdog on single/all channels.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_AWD:
           This parameter can be any combination of the following values.
          @arg ADC_AWD_DISABLE
          @arg ADC_AWD_ALL_LOWER
          @arg ADC_AWD_ALL_UPPER
          @arg ADC_AWD_ALL_LOWER_UPPER
          @arg ADC_AWD_SINGLE_LOWER
          @arg ADC_AWD_SINGLE_UPPER
          @arg ADC_AWD_SINGLE_LOWER_UPPER
 * @retval None
 ************************************************************************************************************/
void ADC_AWDConfig(ADC_TypeDef* ADCx, u32 ADC_AWD)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_AWD(ADC_AWD));

  ADCx->WCR = (ADCx->WCR & 0xFFFFFFF8) | ADC_AWD ;
}

/*********************************************************************************************************//**
 * @brief Configure the analog watchdog that guards single channel.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_CH: ADC input channel
           This parameter can be one of following
          @arg ADC_CH_x  where x must between 0 ~ 7
 * @retval None
 ************************************************************************************************************/
void ADC_AWDSingleChannelConfig(ADC_TypeDef* ADCx, u8 ADC_CH)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_INPUT_CHANNEL(ADC_CH));

  ADCx->WCR = (ADCx->WCR & 0xFFFFF0FF) | ((u32)ADC_CH << 8) ;
}

/*********************************************************************************************************//**
 * @brief Configure the high and low thresholds of the analog watchdog.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param UPPER : must between 0x0000 ~ 0x0FFF
 * @param LOWER : must between 0x0000 ~ 0x0FFF
 * @retval None
 ************************************************************************************************************/
void ADC_AWDThresholdsConfig(ADC_TypeDef* ADCx, u16 UPPER, u16 LOWER)
{
  /* Check the parameters */
  Assert_Param(IS_ADC(ADCx));
  Assert_Param(IS_ADC_THRESHOLD(UPPER));
  Assert_Param(IS_ADC_THRESHOLD(LOWER));

  ADCx->LTR = LOWER ;
  ADCx->UTR = UPPER ;
}


/**
  * @}
  *//* End of ADC_Private_Function group */

/**
  * @}
  *//* End of ADC group */

/**
  * @}
  *//* End of HT32F125x_Peripheral_Driver group */
