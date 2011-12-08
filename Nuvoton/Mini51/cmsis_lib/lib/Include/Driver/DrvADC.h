//*****************************************************************************
//
//! \file DrvADC.h
//! \brief Defines and Macros for ADC API.
//! \version v1.03.002
//! \date 09/05/2011
//! \author Nuvoton
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************
#ifndef __DRVADC_H__
#define __DRVADC_H__

//*****************************************************************************
//
//! Includes of local headers
//
//*****************************************************************************
#include "MINI51.h"
#include "SysInfra.h"

/* Address definition */
#define ADC_ADSR             (ADC_BASE       + 0x30)
#define ADC_CHANNEL_NUM		  8

//*****************************************************************************
//
//! Macro, type and constant definitions
//
//*****************************************************************************
/* version definition with SysInfra */
#define DRVADC_MAJOR_NUM 1
#define DRVADC_MINOR_NUM 01
#define DRVADC_BUILD_NUM 001
#define DRVADC_VERSION_NUM    _SYSINFRA_VERSION(DRVADC_MAJOR_NUM, DRVADC_MINOR_NUM, DRVADC_BUILD_NUM)

/* error code definition */
//#define E_DRVADC_ARGUMENT     _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVADC, 1)

typedef enum {EXTERNAL_CLOCK=0, HCLK = 2, INTERNAL_RC22MHZ=3} E_ADC_CLK_SRC;
typedef enum {FALLING_EDGE=0x00, RISING_EDGE=0x40} E_ADC_EXT_TRI_COND;
typedef enum {EXTERNAL_INPUT_SIGNAL = 0, INTERNAL_BANDGAP = 1} E_ADC_CH7_SRC;
typedef enum {LESS_THAN = 0, GREATER_OR_EQUAL = 0x4} E_ADC_CMP_CONDITION;

typedef void (DRVADC_ADC_CALLBACK)(uint32_t u32UserData);
typedef void (DRVADC_ADCMP0_CALLBACK)(uint32_t u32UserData);
typedef void (DRVADC_ADCMP1_CALLBACK)(uint32_t u32UserData);

#define _DRVADC_CONV() (ADC->ADCR.ADST=1)
#define _DRVADC_GET_ADC_INT_FLAG() ADC->ADSR.ADF
#define _DRVADC_GET_CMP0_INT_FLAG() ADC->ADSR.CMPF0
#define _DRVADC_GET_CMP1_INT_FLAG() ADC->ADSR.CMPF1
#define _DRVADC_CLEAR_ADC_INT_FLAG() (outpw(ADC_ADSR, (inpw(ADC_ADSR)&(~0x7))|0x1))
#define _DRVADC_CLEAR_CMP0_INT_FLAG() (outpw(ADC_ADSR, (inpw(ADC_ADSR)&(~0x7))|0x2))
#define _DRVADC_CLEAR_CMP1_INT_FLAG() (outpw(ADC_ADSR, (inpw(ADC_ADSR)&(~0x7))|0x4))

//*****************************************************************************
//
//! Define Function Prototypes
//
//*****************************************************************************
void DrvADC_Open(uint8_t u8Channel, E_ADC_CLK_SRC ClockSrc, uint8_t u8AdcDivisor);
void DrvADC_Close(void);
void DrvADC_SetADCChannel(uint8_t u8ChannelSelBitwise);
void DrvADC_ConfigADCChannel7(E_ADC_CH7_SRC Ch7Src);
void DrvADC_SetADCClkSrc(E_ADC_CLK_SRC ClockSrc);
void DrvADC_SetADCDivisor(uint8_t u8AdcDivisor);
void DrvADC_EnableADCInt(DRVADC_ADC_CALLBACK callback, uint32_t u32UserData);
void DrvADC_DisableADCInt(void);
void DrvADC_EnableADCCmp0Int(DRVADC_ADCMP0_CALLBACK callback, uint32_t u32UserData);
void DrvADC_DisableADCCmp0Int(void);
void DrvADC_EnableADCCmp1Int(DRVADC_ADCMP1_CALLBACK callback, uint32_t u32UserData);
void DrvADC_DisableADCCmp1Int(void);
uint32_t DrvADC_GetConversionRate(void);
void DrvADC_EnableExtTrigger(E_ADC_EXT_TRI_COND TriggerCondition);
void DrvADC_DisableExtTrigger(void);
void DrvADC_StartConvert(void);
uint32_t DrvADC_IsConversionDone(void);
int32_t DrvADC_GetConversionData(void);
uint32_t DrvADC_IsDataValid(void);
uint32_t DrvADC_IsDataOverrun(void);
int32_t DrvADC_EnableADCCmp0(uint8_t u8CmpChannelNum, E_ADC_CMP_CONDITION CmpCondition, uint16_t u16CmpData, uint8_t CmpMatchCount);
int32_t DrvADC_EnableADCCmp1(uint8_t u8CmpChannelNum, E_ADC_CMP_CONDITION CmpCondition, uint16_t u16CmpData, uint8_t CmpMatchCount);
void DrvADC_DisableADCCmp0(void);
void DrvADC_DisableADCCmp1(void);
uint32_t DrvADC_GetVersion (void);

#endif
