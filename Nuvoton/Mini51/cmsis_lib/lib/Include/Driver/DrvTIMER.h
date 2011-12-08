//*****************************************************************************
//
//! \file DrvTimer.h
//! \brief Defines and Macros for Timer API.
//! \version v1.04.005
//! \date 11/28/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//
//*****************************************************************************
#ifndef __DRVTIMER_H__
#define __DRVTIMER_H__

#include "MINI51.h"

//*****************************************************************************
//
//! Macro, type and constant definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! Define Version number
//
//*****************************************************************************
#define DRVTIMER_MAJOR_NUM      1
#define DRVTIMER_MINOR_NUM      00
#define DRVTIMER_BUILD_NUM      001
#define DRVTIMER_VERSION_NUM    _SYSINFRA_VERSION(DRVTIMER_MAJOR_NUM, DRVTIMER_MINOR_NUM, DRVTIMER_BUILD_NUM)

//*****************************************************************************
//
//! Define Error Code
//
//*****************************************************************************
#define E_DRVTIMER_CHANNEL          _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVTIMER, 1)  /* Invalid channel     */
#define E_DRVTIMER_CLOCK_RATE       _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVTIMER, 2)  /* Invalid clock rate  */
#define E_DRVTIMER_EIO              _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVTIMER, 3)  /* Timer IO error      */
#define E_DRVTIMER_EVENT_FULL       _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVTIMER, 4)  /* Event Full error    */
#define E_DRVTIMER_MODE          	_SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVTIMER, 5)  /* Invalid mode     */
#define E_DRVWDT_CMD                _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVTIMER, 6)  /* Invalid CMD         */

//*****************************************************************************
//
//! Define Macro to Check 
//
//*****************************************************************************
#define CHECK_TMR_PORT(ch)			((ch == E_TMR0) || (ch == E_TMR1))

//*****************************************************************************
//
//! Global interface variables declarations
//
//*****************************************************************************
typedef void (*TIMER_CALLBACK)(uint32_t data);  /* function pointer */
typedef void (*WDT_CALLBACK)(uint32_t data);    /* function pointer */

//*****************************************************************************
//
//! Define TIME EVENT STRUCT
//
//*****************************************************************************
typedef struct timeEvent_t
{
    int32_t              active;
    int32_t              initTick;
    int32_t              curTick;
    TIMER_CALLBACK       funPtr;
    uint32_t             transParam;
} TIMER_EVENT_T;

//*****************************************************************************
//
//! Define TIMER Channel 
//
//*****************************************************************************
typedef enum {
    E_TMR0  =   0 ,
    E_TMR1  =   1     
} E_TIMER_CHANNEL;

//*****************************************************************************
//
//! Define TIMER OPREATION MODE 
//
//*****************************************************************************
typedef enum{                   
    E_ONESHOT_MODE      = 0,
    E_PERIODIC_MODE     = 1,
    E_TOGGLE_MODE        = 2, 
    E_CONTINUOUS_MODE  = 3, 
} E_TIMER_OPMODE ;

//*****************************************************************************
//
//! Define Timer Counter TX Phase 
//
//*****************************************************************************
typedef enum{                   
    E_PHASE_FALLING     = 0,
    E_PHASE_RISING      = 1,
} E_TIMER_TX_PHASE ;

//*****************************************************************************
//
//! Define Timer Capture Detect Edge : For counter-reset and free-counting mode 
//
//*****************************************************************************
typedef enum{                   
    E_EDGE_FALLING      = 0,
    E_EDGE_RISING       = 1,
    E_EDGE_BOTH         = 2,
} E_TIMER_TEX_EDGE ;

//*****************************************************************************
//
//! Define Timer Capture Detect Edge : For trigger-counting mode  
//
//*****************************************************************************
typedef enum {
    E_FALLING_FALLING_EDGE = 0,
    E_RISING_RISING_EDGE = 1,
    E_FALLING_RISING_EDGE = 2,
    E_RISING_FALLING_EDGE = 3,    
}E_TIMER_TEX_TRIGGER_EDGE;

//*****************************************************************************
//
//! Define Timer Capture Mode  
//
//*****************************************************************************
typedef enum {
    E_CAP_FREE_COUNTING = 0,
	E_CAP_COUNTER_RESET = 1,
    E_CAP_TRIGGER_COUNTING = 2,   
}E_TIMER_CAP_MODE;

//*****************************************************************************
//
//! Define Timer Reset or Capture   
//
//*****************************************************************************
typedef enum{                   
    E_CAPTURE           = 0,
    E_RESET             = 1,
} E_TIMER_RSTCAP_MODE ;

//*****************************************************************************
//
//! Define WDT Ioctl Command 
//
//*****************************************************************************
typedef enum {
    E_WDT_IOC_START_TIMER       = 0,
    E_WDT_IOC_STOP_TIMER        = 1,
    E_WDT_IOC_ENABLE_INT        = 2,
    E_WDT_IOC_DISABLE_INT       = 3,
    E_WDT_IOC_ENABLE_WAKEUP     = 4,
    E_WDT_IOC_DISABLE_WAKEUP    = 5,
    E_WDT_IOC_RESET_TIMER       = 6,
    E_WDT_IOC_ENABLE_RESET_FUNC = 7,
    E_WDT_IOC_DISABLE_RESET_FUNC= 8,
    E_WDT_IOC_SET_INTERVAL      = 9
} E_WDT_CMD; 

//*****************************************************************************
//
//! Define WDT INTERVAL 
//
//*****************************************************************************
typedef enum{
    E_WDT_LEVEL0      = 0,         /* 2^4 WDT_CLK                                                          */
    E_WDT_LEVEL1      = 1,         /* 2^6 WDT_CLK                                                          */
    E_WDT_LEVEL2      = 2,         /* 2^8 WDT_CLK                                                          */ 
    E_WDT_LEVEL3      = 3,         /* 2^10 WDT_CLK                                                         */
    E_WDT_LEVEL4      = 4,         /* 2^12 WDT_CLK                                                         */
    E_WDT_LEVEL5      = 5,         /* 2^14 WDT_CLK                                                         */
    E_WDT_LEVEL6      = 6,         /* 2^16 WDT_CLK                                                         */
    E_WDT_LEVEL7      = 7          /* 2^18 WDT_CLK                                                         */
} E_WDT_INTERVAL;

//*****************************************************************************
//
//! Define Function Prototype 
//
//*****************************************************************************
void DrvTIMER_Init(void);
int32_t DrvTIMER_Open(E_TIMER_CHANNEL ch, uint32_t uTicksPerSecond, E_TIMER_OPMODE op_mode);
int32_t DrvTIMER_Close(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_SetTimerEvent(E_TIMER_CHANNEL ch, uint32_t uInterruptTicks, TIMER_CALLBACK pTimerCallback, uint32_t parameter);
void    DrvTIMER_ClearTimerEvent(E_TIMER_CHANNEL ch, uint32_t uTimerEventNo);
int32_t DrvTIMER_EnableInt(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_DisableInt(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_GetIntFlag(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_ClearIntFlag(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_Start(E_TIMER_CHANNEL ch);
uint32_t DrvTIMER_GetIntTicks(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_ResetIntTicks(E_TIMER_CHANNEL ch);
void    DrvTIMER_Delay(E_TIMER_CHANNEL ch, uint32_t uTicks);
void    DrvTIMER_SetEXTClockFreq(uint32_t u32ClockFreq);
int32_t DrvTIMER_OpenCounter(E_TIMER_CHANNEL ch, uint32_t uCounterBoundary, E_TIMER_OPMODE op_mode);
int32_t DrvTIMER_StartCounter(E_TIMER_CHANNEL ch);
uint32_t DrvTIMER_GetCounters(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_OpenCapture(E_TIMER_CHANNEL ch, E_TIMER_RSTCAP_MODE mode);
int32_t DrvTIMER_CloseCapture(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_SelectExternalMode(E_TIMER_CHANNEL ch, E_TIMER_CAP_MODE mode);
int32_t DrvTIMER_SelectCaptureEdge(E_TIMER_CHANNEL ch, E_TIMER_TEX_EDGE edge);
int32_t DrvTIMER_SelectTriggerCaptureEdge(E_TIMER_CHANNEL ch, E_TIMER_TEX_TRIGGER_EDGE edge);
int32_t DrvTIMER_EnableCaptureInt(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_DisableCaptureInt(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_EnableCapture(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_DisableCapture(E_TIMER_CHANNEL ch);
uint32_t DrvTIMER_GetCaptureData(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_GetCaptureIntFlag(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_ClearCaptureIntFlag(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_EnableCaptureDebounce(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_DisableCaptureDebounce(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_EnableCounterDebounce(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_DisableCounterDebounce(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_SelectCounterDetectPhase(E_TIMER_CHANNEL ch, E_TIMER_TX_PHASE phase);
int32_t DrvTIMER_EnableWakeUp(E_TIMER_CHANNEL ch);
int32_t DrvTIMER_DisableWakeUp(E_TIMER_CHANNEL ch);
uint32_t DrvTIMER_GetVersion(void);

void DrvWDT_Open(E_WDT_INTERVAL WDTlevel);
void DrvWDT_Close(void);
void DrvWDT_InstallISR(WDT_CALLBACK pvWDTISR);
int32_t DrvWDT_Ioctl(E_WDT_CMD uWDTCmd, uint32_t uArgument);

#endif  // __DRVTIMER_H__





