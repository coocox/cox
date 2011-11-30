//*****************************************************************************
//
//! \file DrvPWM.h
//! \brief Defines and Macros for PWM API.
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//
//*****************************************************************************
#ifndef _DRVPWM_H
#define _DRVPWM_H

//*****************************************************************************
//
//! Includes of system headers
//
//*****************************************************************************
#include "MINI51.h"

#ifdef  __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! Define Version number
//
//*****************************************************************************
#define DRVPWM_MAJOR_NUM    1
#define DRVPWM_MINOR_NUM    00
#define DRVPWM_BUILD_NUM    001


//*****************************************************************************
//
//! Version define with SysInfra
//
//*****************************************************************************
#define DRVPWM_VERSION_NUM     _SYSINFRA_VERSION(DRVPWM_MAJOR_NUM, DRVPWM_MINOR_NUM, DRVPWM_BUILD_NUM)

//*****************************************************************************
//
//! Define Error Code
//
//*****************************************************************************
// E_DRVPWM_ERR_ARGUMENT        Incorrect Argument
// E_DRVPWM_ERR_NO_SUPPORT      Does not support this function
//#define E_DRVPWM_ERR_ARGUMENT   _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVPWM, 1)
#define E_DRVPWM_ERR_NO_SUPPORT _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVPWM, 2)

//*****************************************************************************
//
//! PWM Timer
//
//*****************************************************************************
#define DRVPWM_TIMER0   0x00
#define DRVPWM_TIMER1   0x01
#define DRVPWM_TIMER2   0x02
#define DRVPWM_TIMER3   0x03
#define DRVPWM_TIMER4   0x04
#define DRVPWM_TIMER5   0x05
#define DRVPWM_FB0		  0x10
#define DRVPWM_FB1		  0x11

#define DRVPWM_CHANNEL_NUM	6

//*****************************************************************************
//
//! PWM Clcok Selector
//
//*****************************************************************************
#define DRVPWM_CLOCK_DIV_1    4
#define DRVPWM_CLOCK_DIV_2    0
#define DRVPWM_CLOCK_DIV_4    1
#define DRVPWM_CLOCK_DIV_8    2
#define DRVPWM_CLOCK_DIV_16   3

//*****************************************************************************
//
//! PWM Mode Selector
//
//*****************************************************************************
#define DRVPWM_AUTO_RELOAD_MODE 1
#define DRVPWM_ONE_SHOT_MODE    0

//*****************************************************************************
//
//! Define PWM Time Data Struct
//
//*****************************************************************************

typedef struct
{
    uint8_t   u8Mode;
    uint8_t   u8HighPulseRatio;
    uint8_t   u8ClockSelector;
    uint8_t   u8PreScale;
    uint32_t  u32Frequency; 
    uint32_t  u32Duty;
    int32_t   i32Inverter;
}S_DRVPWM_TIME_DATA_T;


//*****************************************************************************
//
//! Indicates PWM interrupt type
//
//*****************************************************************************
typedef enum {
    PWM_INT_DUTY = 0x100,                 ///< PWM duty interrupt
    PWM_INT_PERIOD = 0x1                ///< PWM period interrupt
}E_DRVPWM_INTERRUPT_TYPE;


//*****************************************************************************
//
//! Holds the PWM aligned type
//
//*****************************************************************************
typedef enum {	
	PWM_EDGE_ALIGNED = 0,
	PWM_CENTER_ALIGNED = 1
}E_DRVPWM_ALIGN_TYPE;

//*****************************************************************************
//
//! Indicates PWM period interrupt type
//
//*****************************************************************************
typedef enum {
    PWM_CNTR_UNDERFLOW,                 ///< PWM counter under flow
    PWM_CNTR_MATCH                      ///< PWM counter match cnr
}E_DRVPWM_PERIOD_INT_TYPE;

//*****************************************************************************
//
//! Holds PWM fault break source
//
//*****************************************************************************
typedef enum {
	PWM_FB_EINT0,
	PWM_FB_EINT1,
	PWM_FB_CPO0
}E_DRVPWM_FB_SRC;


//*****************************************************************************
//
//! Indicates PWM timer op mode
//
//*****************************************************************************
typedef enum {
    PWM_INDEPENDENT_MODE = 0,    ///< independent mode
    PWM_COMPLEMENTARY_MODE = 1,  ///< complementary mode
	PWM_SYNCHRONIZED_MODE = 2    ///< synchronized mode
}E_DRVPWM_OP_MODE;

//*****************************************************************************
//
//! Define PWM Call back funvtion Data Struct
//
//*****************************************************************************
typedef void (*PFN_DRVPWM_CALLBACK)(uint32_t);

//*****************************************************************************
//
//! Define PWM functions prototype
//
//*****************************************************************************

void     DrvPWM_ClearInt(uint8_t u8Timer, E_DRVPWM_INTERRUPT_TYPE eType);
void     DrvPWM_Close(void);

void     DrvPWM_DisableInt(uint8_t u8Timer, E_DRVPWM_INTERRUPT_TYPE eType);

void     DrvPWM_Enable(uint8_t u8Timer);
void     DrvPWM_Disable(uint8_t u8Timer);
void     DrvPWM_EnableDeadZone(uint8_t u8Timer, uint8_t u8Length);
void     DrvPWM_DisableDeadZone(uint8_t u8Timer);
void     DrvPWM_EnableInt(uint8_t u8Timer, E_DRVPWM_INTERRUPT_TYPE eType, PFN_DRVPWM_CALLBACK pfncallback, uint32_t u32Param);

int32_t  DrvPWM_GetIntFlag(uint8_t u8Timer, E_DRVPWM_INTERRUPT_TYPE eType);
uint32_t DrvPWM_GetVersion (void);

int32_t  DrvPWM_IsTimerEnabled(uint8_t u8Timer);

void     DrvPWM_Open(void);
uint32_t DrvPWM_SetTimerClk(uint8_t u8Timer, S_DRVPWM_TIME_DATA_T *sPt);
void     DrvPWM_SetTimerCounter(uint8_t u8Timer, uint16_t u16Counter);
void     DrvPWM_SetTimerComparator(uint8_t u8Timer, uint16_t u16Comparator);
void     DrvPWM_SetTimerIO(uint8_t u8Timer, int32_t i32Enable);
void     DrvPWM_SetAttribute(E_DRVPWM_OP_MODE eMode, E_DRVPWM_ALIGN_TYPE eType, uint8_t u8Group);
void     DrvPWM_ClearCounter(void);
void     DrvPWM_SetPeriodInterruptType(E_DRVPWM_PERIOD_INT_TYPE eType); 
void     DrvPWM_SetFaultBreakOutputLevel(uint8_t u8Level);
void     DrvPWM_EnableFaultBreak(E_DRVPWM_FB_SRC eSrc);
void     DrvPWM_DisableFaultBreak(E_DRVPWM_FB_SRC eSrc);
void     DrvPWM_ClearFaultBreak(void);
#ifdef  __cplusplus
}
#endif

#endif



