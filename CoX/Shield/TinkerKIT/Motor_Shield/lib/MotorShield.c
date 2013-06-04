//*****************************************************************************
//
//! \file MotorTest.c
//! \brief Driver for the Motor controller Test
//! \version V2.1.1.0
//! \date 6/7/2012
//! \author CooCox
//! \copy
//!
//
//*****************************************************************************

#include "xhw_types.h"
#include "xcore.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xpwm.h"
#include "xhw_timer.h"
#include "xtimer.h"
#include "cookie_cfg.h"
#include "cookie.h"
#include "MotorShield.h"

//
//! Step Motor 28BYJ-48 run forward pulse data in 8 pat
//
static unsigned char g_ul28BYJ48Forward[8] = {0x3, 0x2, 0x6, 0x4, 0xc, 0x8, 0x9, 0x1};

//
//! Step motor steps delay
//
static unsigned long g_ulStepsDelay = 10;

//*****************************************************************************
//
//! \brief Init the ULN2003 connected pin 
//!
//! \note The data will parral out.
//! 
//! \return None.
//
//*****************************************************************************
void 
MSULN2003PinInit(void)
{
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ULN2003_PIN_IN1));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ULN2003_PIN_IN2));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ULN2003_PIN_IN3));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ULN2003_PIN_IN4));
    
    //
    // Set IN1 IN2 IN3 IN4 as output.
    //
    xGPIOSPinTypeGPIOOutput(ULN2003_PIN_IN1);
    xGPIOSPinTypeGPIOOutput(ULN2003_PIN_IN2);
    xGPIOSPinTypeGPIOOutput(ULN2003_PIN_IN3);
    xGPIOSPinTypeGPIOOutput(ULN2003_PIN_IN4);

    //
    // Stop the step motor.
    //
    xGPIOSPinWrite(ULN2003_PIN_IN1, 0);
    xGPIOSPinWrite(ULN2003_PIN_IN2, 0);
    xGPIOSPinWrite(ULN2003_PIN_IN3, 0);
    xGPIOSPinWrite(ULN2003_PIN_IN4, 0);
}

//*****************************************************************************
//
//! \brief Init the selected stepper number.
//!
//! \param None.
//! 
//! \return None.
//
//*****************************************************************************
void 
MSStepMotorInit(void)
{
    MSULN2003PinInit();
}

//*****************************************************************************
//
//! \brief Set the step motor steps delay
//!
//! \param ulDelay is the steps delay ms.
//! 
//! \return None.
//
//*****************************************************************************
void 
MSStepsDelaySet(unsigned long ulDelay)
{
    g_ulStepsDelay = ulDelay;
}

//*****************************************************************************
//
//! \brief Control the 42BYGH step motor roll direction and speed. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulDir is the selection of Step Motor running direction.
//! \param ulSteps is the motor rev step number.
//!
//! The \e ulDir parameter can be one of the values:
//! \b MS_RUN_FORWARD, \b MS_RUN_BACKWARD.
//! 
//! \note The 42BYGH step motor is drivered by ladyada mshield IC1. The red wire
//!       connect to 1A(red <-> 1A), and (green <-> 2A), (yellow <-> 3A), 
//!       (blue <-> 4A). 
//! 
//! \return None.
//
//*****************************************************************************
void 
MSStepMotorRun(unsigned long ulDir, unsigned long ulSteps)
{
    unsigned long i;
    //
    // Check the arguments.
    //
    xASSERT((ulDir == MS_RUN_FORWARD) ||
            (ulDir == MS_RUN_BACKWARD));

    unsigned char StepType[8] = {0};
    if(ulSteps == 4){
        for(i = 0; i < 4; i++){
            StepType[i] = g_ul28BYJ48Forward[2*i];
        }
    } else {
        for(i = 0; i < 8; i++){
            StepType[i] = g_ul28BYJ48Forward[i];
        }
    }
    
    if(ulDir == MS_RUN_FORWARD){
        for(i = 0; i < ulSteps; i++){
            xGPIOSPinWrite(ULN2003_PIN_IN1,((StepType[i%8] >> 3) & 0x1));
            xGPIOSPinWrite(ULN2003_PIN_IN2,((StepType[i%8] >> 2) & 0x1));
            xGPIOSPinWrite(ULN2003_PIN_IN3,((StepType[i%8] >> 1) & 0x1));
            xGPIOSPinWrite(ULN2003_PIN_IN4,((StepType[i%8]) & 0x1));
            MSDelay(g_ulStepsDelay);
        }
    } else {
        for(i = 0; i < ulSteps; i++){
            xGPIOSPinWrite(ULN2003_PIN_IN1,((StepType[i%8]) & 0x1));
            xGPIOSPinWrite(ULN2003_PIN_IN2,((StepType[i%8] >> 1) & 0x1));
            xGPIOSPinWrite(ULN2003_PIN_IN3,((StepType[i%8] >> 2) & 0x1));
            xGPIOSPinWrite(ULN2003_PIN_IN4,((StepType[i%8] >> 3) & 0x1));
            MSDelay(g_ulStepsDelay);
        }
    }   
}

//*****************************************************************************
//
//! \brief Stop the 28BYJ-48 step motor. 
//!
//! \param None
//! 
//! \return None.
//
//*****************************************************************************
void 
MSStepMotorStop(void)
{
    xGPIOSPinWrite(ULN2003_PIN_IN1, 0);
    xGPIOSPinWrite(ULN2003_PIN_IN2, 0);
    xGPIOSPinWrite(ULN2003_PIN_IN3, 0);
    xGPIOSPinWrite(ULN2003_PIN_IN4, 0);   
}

//*****************************************************************************
//
//! \brief Dalay some time.
//!
//! \param ulDelay is the delay number of ms. 
//!
//! \return None.
//
//*****************************************************************************
void 
MSDelay(unsigned long ulDelay)
{
    //
    // Set the timer clock
    //   
    xSysCtlPeripheralEnable2(MS_DELAY_TIMER);

    //
    // Clear the status first
    //
    TimerFlagStatusClear(MS_DELAY_TIMER, xTIMER_INT_MATCH);

    //
    // Config as periodic mode
    //
    xTimerInitConfig(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_MODE_PERIODIC, 1000);
    xTimerIntEnable(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH);
    xTimerStart(MS_DELAY_TIMER, MS_DELAY_CHANNEL);

    while(ulDelay){
        while(!xTimerStatusGet(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH));
        TimerFlagStatusClear(MS_DELAY_TIMER, xTIMER_INT_MATCH);
        ulDelay--;
    }

    xTimerStop(MS_DELAY_TIMER, MS_DELAY_CHANNEL);
    xSysCtlPeripheralDisable2(MS_DELAY_TIMER); 
}