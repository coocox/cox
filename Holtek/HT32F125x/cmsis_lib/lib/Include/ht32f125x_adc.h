/*********************************************************************************************************//**
 * @file    ht32f125x_adc.h
 * @version V1.0
 * @date    04/11/2011
 * @brief   The header file of ADC library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __ht32f125x_ADC_H
#define __ht32f125x_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x.h"

/** @addtogroup HT32F125x_Peripheral_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup ADC_Exported_Types ADC exported types
  * @{
  */

/* Definition of ADC Init Structure                                                                          */
typedef struct
{
  u32 ADC_ConversionMode;
  u32 ADC_LengthListQueue;
  u32 ADC_LengthSubgrup;
  u32 ADC_HPCCMode;
  u32 ADC_HPLengthListQueue;
  u32 ADC_HPLengthSubgrup;

  u32 ADC_TriggerMode;
  u32 ADC_ExtiTriggerSource;
  u32 ADC_ETPUTriggerChannel;
  u32 ADC_TPTriggerChannel;

  u32 ADC_HPTriggerMode;
  u32 ADC_HPExtiTriggerSource;
  u32 ADC_HPETPUTriggerChannel;
  u32 ADC_HPTPTriggerChannel;

  u32 ADC_WatchdogLowerFunc;
  u32 ADC_WatchdogUpperFunc;
  u32 ADC_WatchdogAllChannel;
  u32 ADC_WatchdogChannel;
}ADC_InitTypeDef;


/**
  * @}
  *//* End of ADC_Exported_Types group */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC exported constants
  * @{
  */

/* ADC BASE ------------------------------------------------------------------------------------------------*/
#define IS_ADC(x) (x == ADC)



/* ADC Cyclic Conversion Mode for ADC high-priority & regular group --------------------------------------------*/
/** @defgroup ADC_Conversion_Mode Definitions of ADC conversion mode
  * @{
  */
#define ONE_SHOT_MODE                           ((u32)0x0000)
#define CONTINUOUS_MODE                         ((u32)0x0002)
#define DISCONTINUOUS_MODE                      ((u32)0x0003)
#define IS_ADC_CYCLIC_CONVERSION_MODE(ADC_MODE) (((ADC_MODE) == ONE_SHOT_MODE) || \
                                                 ((ADC_MODE) == CONTINUOUS_MODE) || \
                                                 ((ADC_MODE) == DISCONTINUOUS_MODE))
/**
  * @}
  */

/* ADC High-Priority Cyclic Conversion Mode ----------------------------------------------------------------*/
/** @defgroup ADC_High_Priority_Conversion_Mode Definitions of ADC high-priority conversion mode
  * @{
  */
#define HP_ONE_SHOT_MODE                        ((u32)0x0000)
#define HP_CONTINUOUS_MODE                      ((u32)0x0002)
#define HP_DISCONTIOUS_MODE                     ((u32)0x0003)
#define IS_ADC_HPCYCLIC_CONVERSION_MODE(HPMODE) ((HPMODE == HP_ONE_SHOT_MODE) || \
                                                 (HPMODE == HP_CONTINUOUS_MODE) || \
                                                 (HPMODE == HP_DISCONTIOUS_MODE))
/**
  * @}
  */

/* ADC Trigger Control Register ----------------------------------------------------------------------------*/
/** @defgroup ADC_Trigger_Control Definitions of ADC trigger
  * @{
  */
#define SOFTWARE_TRIGGER                      ((u32)0x0001)
#define EXTI_TRIGGER                          ((u32)0x0002)
#define ETM_TRIGGER                           ((u32)0x0004)
#define IS_ADC_TRIGGER_CONTROL(TRCONTROL)     ((TRCONTROL == SOFTWAER_TRIGGER) || \
                                               (TRCONTROL == EXTI_TRIGGER) || \
                                               (TRCONTROL == ETPU_TRIGGER))
/**
  * @}
  */

/* ADC Trigger Source Register -----------------------------------------------------------------------------*/
/** @defgroup ADC_Trigger_Source Definitions of ADC trigger source
  * @{
  */
#define ADC_EXTI0                             ((u32)0x00000000)
#define ADC_EXTI1                             ((u32)0x00000100)
#define ADC_EXTI2                             ((u32)0x00000200)
#define ADC_EXTI3                             ((u32)0x00000300)
#define ADC_EXTI4                             ((u32)0x00000400)
#define ADC_EXTI5                             ((u32)0x00000500)
#define ADC_EXTI6                             ((u32)0x00000600)
#define ADC_EXTI7                             ((u32)0x00000700)
#define ADC_EXTI8                             ((u32)0x00000800)
#define ADC_EXTI9                             ((u32)0x00000900)
#define ADC_EXTI10                            ((u32)0x00000A00)
#define ADC_EXTI11                            ((u32)0x00000B00)
#define ADC_EXTI12                            ((u32)0x00000C00)
#define ADC_EXTI13                            ((u32)0x00000D00)
#define ADC_EXTI14                            ((u32)0x00000E00)
#define ADC_EXTI15                            ((u32)0x00000F00)
#define ADC_GPTM0                             ((u32)0x00020000)
#define ADC_GPTM1                             ((u32)0x00030000)
#define ADC_TRGO                              ((u32)0x00000000)
#define ADC_CH0O                              ((u32)0x01000000)
#define ADC_CH1O                              ((u32)0x02000000)
#define ADC_CH2O                              ((u32)0x03000000)
#define ADC_CH3O                              ((u32)0x04000000)

#define IS_ADC_TRIGGER_SOURCE(SOURCE) (((SOURCE) == ADC_EXTI0) || ((SOURCE) == ADC_EXTI1) || \
                                       ((SOURCE) == ADC_EXTI2) || ((SOURCE) == ADC_EXTI3) || \
                                       ((SOURCE) == ADC_EXTI4) || ((SOURCE) == ADC_EXTI5) || \
                                       ((SOURCE) == ADC_EXTI6) || ((SOURCE) == ADC_EXTI7) || \
                                       ((SOURCE) == ADC_EXTI8) || ((SOURCE) == ADC_EXTI9) || \
                                       ((SOURCE) == ADC_EXTI10) || ((SOURCE) == ADC_EXTI11) || \
                                       ((SOURCE) == ADC_EXTI12) || ((SOURCE) == ADC_EXTI13) || \
                                       ((SOURCE) == ADC_EXTI14) || ((SOURCE) == ADC_EXTI15) || \
                                       ((SOURCE) == ADC_GPTM0) || ((SOURCE) == ADC_GPTM1) || \
                                       ((SOURCE) == ADC_TRGO) || ((SOURCE) == ADC_CH0O) || \
                                       ((SOURCE) == ADC_CH1O) || ((SOURCE) == ADC_CH2O) || \
                                       ((SOURCE) == ADC_CH3O))
/**
  * @}
  */   

/* ADC channel definition ----------------------------------------------------------------------------------*/
/** @defgroup ADC_Channel_Definition Definitions of ADC channels
  * @{
  */
#define ADC_CH_0      0
#define ADC_CH_1      1
#define ADC_CH_2      2
#define ADC_CH_3      3
#define ADC_CH_4      4
#define ADC_CH_5      5
#define ADC_CH_6      6
#define ADC_CH_7      7
#define ADC_CH_GNDREF 16
#define ADC_CH_VREF   17

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CH_0) || ((CHANNEL) == ADC_CH_1) || \
                                 ((CHANNEL) == ADC_CH_2) || ((CHANNEL) == ADC_CH_3) || \
                                 ((CHANNEL) == ADC_CH_4) || ((CHANNEL) == ADC_CH_5) || \
                                 ((CHANNEL) == ADC_CH_6) || ((CHANNEL) == ADC_CH_7) || \
                                 ((CHANNEL) == ADC_CH_GNDREF) || ((CHANNEL) == ADC_CH_VREF))

#define IS_ADC_INPUT_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CH_0) || ((CHANNEL) == ADC_CH_1) || \
                                       ((CHANNEL) == ADC_CH_2) || ((CHANNEL) == ADC_CH_3) || \
                                       ((CHANNEL) == ADC_CH_4) || ((CHANNEL) == ADC_CH_5) || \
                                       ((CHANNEL) == ADC_CH_6) || ((CHANNEL) == ADC_CH_7) )
/**
  * @}
  */

/* ADC extrenal trigger sources for channels conversion ----------------------------------------------------*/
/** @defgroup ADC_Extrenal_Trigger Definitions of ADC extrenal trigger sources
  * @{
  */
/* for ADC */
#define ADC_EXT_TRIG_NONE         (u32)0x00000000
#define ADC_EXT_TRIG_SW           (u32)0x10000000

#define ADC_EXT_TRIG_GPTM0_TRGO   (u32)0x40020000
#define ADC_EXT_TRIG_GPTM0_CH0O   (u32)0x41020000
#define ADC_EXT_TRIG_GPTM0_CH1O   (u32)0x42020000
#define ADC_EXT_TRIG_GPTM0_CH2O   (u32)0x43020000
#define ADC_EXT_TRIG_GPTM0_CH3O   (u32)0x44020000

#define ADC_EXT_TRIG_GPTM1_TRGO   (u32)0x40030000
#define ADC_EXT_TRIG_GPTM1_CH0O   (u32)0x41030000
#define ADC_EXT_TRIG_GPTM1_CH1O   (u32)0x42030000
#define ADC_EXT_TRIG_GPTM1_CH2O   (u32)0x43030000
#define ADC_EXT_TRIG_GPTM1_CH3O   (u32)0x44030000

#define ADC_EXT_TRIG_EXTI_0       (u32)0x20000000
#define ADC_EXT_TRIG_EXTI_1       (u32)0x20000100
#define ADC_EXT_TRIG_EXTI_2       (u32)0x20000200
#define ADC_EXT_TRIG_EXTI_3       (u32)0x20000300
#define ADC_EXT_TRIG_EXTI_4       (u32)0x20000400
#define ADC_EXT_TRIG_EXTI_5       (u32)0x20000500
#define ADC_EXT_TRIG_EXTI_6       (u32)0x20000600
#define ADC_EXT_TRIG_EXTI_7       (u32)0x20000700
#define ADC_EXT_TRIG_EXTI_8       (u32)0x20000800
#define ADC_EXT_TRIG_EXTI_9       (u32)0x20000900
#define ADC_EXT_TRIG_EXTI_10      (u32)0x20000A00
#define ADC_EXT_TRIG_EXTI_11      (u32)0x20000B00
#define ADC_EXT_TRIG_EXTI_12      (u32)0x20000C00
#define ADC_EXT_TRIG_EXTI_13      (u32)0x20000D00
#define ADC_EXT_TRIG_EXTI_14      (u32)0x20000E00
#define ADC_EXT_TRIG_EXTI_15      (u32)0x20000F00


#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_EXT_TRIG_GPTM0_TRGO) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM0_CH0O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM0_CH1O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM0_CH2O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM0_CH3O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM1_TRGO) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM1_CH0O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM1_CH1O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM1_CH2O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_GPTM1_CH3O) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_0) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_1) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_2) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_3) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_4) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_5) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_6) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_7) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_8) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_9) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_10) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_11) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_12) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_13) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_14) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_EXTI_15) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_SW) || \
                                  ((REGTRIG) == ADC_EXT_TRIG_NONE))
/**
  * @}
  */


/* ADC Interrupt -------------------------------------------------------------------------------------------*/
/** @defgroup ADC_Interrupt Definitions of ADC interrupts
  * @{
  */
#define ADC_INT_SINGLE_EOC         (u32)0x00000001
#define ADC_INT_SUB_GROUP_EOC      (u32)0x00000002
#define ADC_INT_CYCLE_EOC          (u32)0x00000004
#define ADC_INT_HP_SINGLE_EOC      (u32)0x00000100
#define ADC_INT_HP_SUB_GROUP_EOC   (u32)0x00000200
#define ADC_INT_HP_CYCLE_EOC       (u32)0x00000400
#define ADC_INT_AWD_LOWER          (u32)0x00010000
#define ADC_INT_AWD_UPPER          (u32)0x00020000
#define ADC_INT_DATA_OVERWRITE     (u32)0x01000000
#define ADC_INT_HP_DATA_OVERWRITE  (u32)0x02000000

#define IS_ADC_INT(INT) ((((INT) & (u32)0xFCFCF8F8) == 0x00) && ((INT) != 0x00))
/**
  * @}
  */

/* ADC Interrupt Flag -------------------------------------------------------------------------------------------*/
/** @defgroup ADC_Interrupt_Flag Definitions of ADC interrupt flags
  * @{
  */
#define ADC_FLAG_SINGLE_EOC         (u32)0x00000001
#define ADC_FLAG_SUB_GROUP_EOC      (u32)0x00000002
#define ADC_FLAG_CYCLE_EOC          (u32)0x00000004
#define ADC_FLAG_HP_SINGLE_EOC      (u32)0x00000100
#define ADC_FLAG_HP_SUB_GROUP_EOC   (u32)0x00000200
#define ADC_FLAG_HP_CYCLE_EOC       (u32)0x00000400
#define ADC_FLAG_AWD_LOWER          (u32)0x00010000
#define ADC_FLAG_AWD_UPPER          (u32)0x00020000
#define ADC_FLAG_DATA_OVERWRITE     (u32)0x01000000
#define ADC_FLAG_HP_DATA_OVERWRITE  (u32)0x02000000

#define IS_ADC_FLAG(FLAG) ((((FLAG) & (u32)0xFCFCF8F8) == 0x00) && ((FLAG) != 0x00))
/**
  * @}
  */
  
/* ADC High-Priority conversion data definition ----------------------------------------------------------------------------------*/
/** @defgroup ADC_High_Priority_Conversion_Data_Definition Definitions of ADC high-priority conversion data
  * @{
  */
#define ADC_HP_DATA0  0
#define ADC_HP_DATA1  1
#define ADC_HP_DATA2  2
#define ADC_HP_DATA3  3

#define IS_ADC_HP_DATA(DATA)  (DATA < 4 )
/**
  * @}
  */

/* ADC regular conversion data definition ----------------------------------------------------------------------------------*/
/** @defgroup ADC_Regular_Conversion_Data_Definition Definitions of ADC regular conversion data
  * @{
  */
#define ADC_REGULAR_DATA0   0
#define ADC_REGULAR_DATA1   1
#define ADC_REGULAR_DATA2   2
#define ADC_REGULAR_DATA3   3
#define ADC_REGULAR_DATA4   4
#define ADC_REGULAR_DATA5   5
#define ADC_REGULAR_DATA6   6
#define ADC_REGULAR_DATA7   7
#define ADC_REGULAR_DATA8   8
#define ADC_REGULAR_DATA9   9
#define ADC_REGULAR_DATA10  10
#define ADC_REGULAR_DATA11  11
#define ADC_REGULAR_DATA12  12
#define ADC_REGULAR_DATA13  13
#define ADC_REGULAR_DATA14  14
#define ADC_REGULAR_DATA15  15

#define IS_ADC_REGULAR_DATA(DATA)   (DATA < 16)
/**
  * @}
  */

/* Analog watch dog ----------------------------------------------------------------------------------------*/
/** @defgroup ADC_Analog_Watch_Dog Definitions of ADC analog watch dog
  * @{
  */
#define ADC_AWD_DISABLE             (u8)0x00
#define ADC_AWD_ALL_LOWER           (u8)0x05
#define ADC_AWD_ALL_UPPER           (u8)0x06
#define ADC_AWD_ALL_LOWER_UPPER     (u8)0x07
#define ADC_AWD_SINGLE_LOWER        (u8)0x01
#define ADC_AWD_SINGLE_UPPER        (u8)0x02
#define ADC_AWD_SINGLE_LOWER_UPPER  (u8)0x03
#define IS_ADC_AWD(AWD)             (((AWD) == ADC_AWD_DISABLE) || \
                                     ((AWD) == ADC_AWD_ALL_LOWER) || \
                                     ((AWD) == ADC_AWD_ALL_UPPER) || \
                                     ((AWD) == ADC_AWD_ALL_LOWER_UPPER) || \
                                     ((AWD) == ADC_AWD_SINGLE_LOWER) || \
                                     ((AWD) == ADC_AWD_SINGLE_UPPER) || \
                                     ((AWD) == ADC_AWD_SINGLE_LOWER_UPPER))

#define IS_ADC_THRESHOLD(THRESHOLD) (((THRESHOLD) < 0x1000))
/**
  * @}
  */

/* ADC regular rank ----------------------------------------------------------------------------------------*/

#define IS_ADC_REGULAR_RANK(RANK) (((RANK) < 0x10))

/* ADC high priority rank-----------------------------------------------------------------------------------*/

#define IS_ADC_HIGH_PRIORITY_RANK(RANK) (((RANK) < 0x4))

/* ADC input sampling time ---------------------------------------------------------------------------------*/

#define IS_ADC_INPUT_SAMPLING_TIME(TIME) (((TIME) < 0x10))

/* Length of regular list queue ----------------------------------------------------------------------------*/

#define IS_ADC_REGULAR_LENGTH(LENGTH)         (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))
#define IS_ADC_REGULAR_SUB_LENGTH(SUB_LENGTH) (((SUB_LENGTH) >= 0x1) && ((SUB_LENGTH) <= 0x10))

/* Length of high priority list queue ----------------------------------------------------------------------*/

#define IS_ADC_HP_LENGTH(LENGTH)          (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))
#define IS_ADC_HP_SUB_LENGTH(SUB_LENGTH)  (((SUB_LENGTH) >= 0x1) && ((SUB_LENGTH) <= 0x4))



/**
  * @}
  *//* End of ADC_Exported_Constants group */

/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup ADC_Exported_Macro ADC exported macro
  * @{
  */

/**
  * @}
  *//* End of ADC_Exported_Macro group */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup ADC_Exported_Functions ADC exported functions
  * @{
  */

void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure);
void ADC_Reset(ADC_TypeDef* ADCx);
void ADC_HPGroupConfig(ADC_TypeDef* ADCx, u8 ADC_MODE, u8 Length, u8 SubLength);
void ADC_RegularGroupConfig(ADC_TypeDef* ADCx, u8 ADC_MODE, u8 Length, u8 SubLength);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 SampleClock) ;
void ADC_HPChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 SampleClock) ;
void ADC_ExtTrigHPConvConfig(ADC_TypeDef* ADCx, u32 ADC_ExtTrigHPConv) ;
void ADC_ExtTrigRegularConvConfig(ADC_TypeDef* ADCx, u32 ADC_ExtTrigRegularConv) ;
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, ControlStatus NewState) ;
void ADC_SoftwareStartHPConvCmd(ADC_TypeDef* ADCx, ControlStatus NewState) ;
u16 ADC_GetHPConversionData(ADC_TypeDef* ADCx, u8 ADC_HP_CH) ;
u16 ADC_GetConversionData(ADC_TypeDef* ADCx, u8 ADC_REGULAR_CH) ;
void ADC_AWDCmd(ADC_TypeDef* ADCx, u32 ADC_AWD) ;
void ADC_AWDSingleChannelConfig(ADC_TypeDef* ADCx, u8 ADC_CH) ;
void ADC_AWDThresholdsConfig(ADC_TypeDef* ADCx, u16 UPPER, u16 LOWER) ;
void ADC_IntConfig(ADC_TypeDef* ADCx, u32 ADC_INT, ControlStatus NewState);
FlagStatus ADC_GetIntStatus(ADC_TypeDef* ADCx, u32 ADC_INT) ;
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, u32 ADC_FLAG) ;
void ADC_ClearIntPendingBit(ADC_TypeDef* ADCx, u32 ADC_INT);
void ADC_ClearFlag(ADC_TypeDef* ADCx, u32 ADC_FLAG);

#ifdef __cplusplus
}
#endif

/**
  * @}
  *//* End of ADC_Exported_Functions group */

/**
  * @}
  *//* End of ADC group */

/**
  * @}
  *//* End of HT32F125x_Peripheral_Driver group */

#endif /* __HT32F125x_ADC_H --------------------------------------------------------------------------------*/

