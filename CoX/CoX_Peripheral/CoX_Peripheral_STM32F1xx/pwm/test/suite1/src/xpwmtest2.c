//*****************************************************************************
//
//! @page xpwm_testcase xpwm PWMMode test
//!
//! File: @ref xpwmtest2.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: STM32F1xx <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xpwm_PWMode
//! .
//! \file xpwmtest.c
//! \brief xpwm test source file
//! \brief xpwm test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xpwm.h"
#include "xhw_timer.h"

//*****************************************************************************
//
//!\page test_xpwm_PWMode test_xpwm_PWMode
//!
//!<h2>Description</h2>
//!Test xpwm PWMode. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//! \breif PWM interrupt handler.
//!
//! \return None
//
//*****************************************************************************
static unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, \
                                     unsigned long ulMsgParam, void *pvMsgData )                                        
{
    xPWMIntDisable(xPWMA_BASE, 0, xPWM_INT_PWM);
    xPWMIntDisable(xPWMA_BASE, 1, xPWM_INT_PWM);
    xPWMIntDisable(xPWMA_BASE, 2, xPWM_INT_PWM);
    xPWMIntDisable(xPWMA_BASE, 3, xPWM_INT_PWM);
    
    xPWMIntDisable(xPWMA_BASE, 0, PWM_INT_UEV1);
    xPWMIntDisable(xPWMA_BASE, 1, PWM_INT_UEV1);
    xPWMIntDisable(xPWMA_BASE, 2, PWM_INT_UEV1);
    xPWMIntDisable(xPWMA_BASE, 3, PWM_INT_UEV1);
    
    xPWMIntDisable(xPWMC_BASE, 0, xPWM_INT_PWM);
    xPWMIntDisable(xPWMC_BASE, 1, xPWM_INT_PWM);
    xPWMIntDisable(xPWMC_BASE, 2, xPWM_INT_PWM);
    xPWMIntDisable(xPWMC_BASE, 3, xPWM_INT_PWM);

    xPWMIntDisable(xPWMC_BASE, 0, PWM_INT_UEV1);
    xPWMIntDisable(xPWMC_BASE, 1, PWM_INT_UEV1);
    xPWMIntDisable(xPWMC_BASE, 2, PWM_INT_UEV1);
    xPWMIntDisable(xPWMC_BASE, 3, PWM_INT_UEV1);

    xPWMIntDisable(xPWMD_BASE, 0, xPWM_INT_PWM);
    xPWMIntDisable(xPWMD_BASE, 1, xPWM_INT_PWM);
    xPWMIntDisable(xPWMD_BASE, 2, xPWM_INT_PWM);
    xPWMIntDisable(xPWMD_BASE, 3, xPWM_INT_PWM);
    
    xPWMIntDisable(xPWMD_BASE, 0, PWM_INT_UEV1);
    xPWMIntDisable(xPWMD_BASE, 1, PWM_INT_UEV1);
    xPWMIntDisable(xPWMD_BASE, 2, PWM_INT_UEV1);
    xPWMIntDisable(xPWMD_BASE, 3, PWM_INT_UEV1);

    xPWMIntDisable(xPWME_BASE, 0, xPWM_INT_PWM);
    xPWMIntDisable(xPWME_BASE, 1, xPWM_INT_PWM);
    xPWMIntDisable(xPWME_BASE, 2, xPWM_INT_PWM);
    xPWMIntDisable(xPWME_BASE, 3, xPWM_INT_PWM);
    
    xPWMIntDisable(xPWME_BASE, 0, PWM_INT_UEV1);
    xPWMIntDisable(xPWME_BASE, 1, PWM_INT_UEV1);
    xPWMIntDisable(xPWME_BASE, 2, PWM_INT_UEV1);
    xPWMIntDisable(xPWME_BASE, 3, PWM_INT_UEV1);
    TestEmitToken('a');
    return 0;
}

//
// pwm base value
//
static unsigned long PWMBase[2] = {xPWMA_BASE, xPWMC_BASE};

//
// pwm channel value
//
static unsigned long PWMChannel[4] = {xPWM_CHANNEL0, xPWM_CHANNEL1,
                                      xPWM_CHANNEL2, xPWM_CHANNEL3};

//
// pwm Inttertupt ID
//
//static unsigned long IntID[2] = {xINT_PWMA, xINT_PWMB};

//*****************************************************************************
//
//! \brief xpwm002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************

static void xpwm002Execute(void)
{          
  
    unsigned long ulBase;
        
    int i, j;
    for(i = 0; i < 2; i++)
    {   
        for(j = 0; j < 4; j++)
        {
            ulBase = PWMBase[i];
                                                     
            //
            // Set invert, dead zone and mode
            //
            xPWMInitConfigure(ulBase, PWMChannel[i], xPWM_TOGGLE_MODE | 
                                            xPWM_OUTPUT_INVERTER_DIS | xPWM_DEAD_ZONE_DIS);
                
            // Set CNR, Prescale and Divider
            xPWMFrequencyConfig(ulBase, PWMChannel[i], 0x0E100028);
                
            //    
            // Set CMR
            //
            xPWMDutySet(ulBase, PWMChannel[i], 40);
                
            //    
            // Set output enable
            //
            xPWMOutputEnable(ulBase, PWMChannel[i]);   
            
            //
            // Set interrupt call back 
            //
            xPWMIntCallbackInit(ulBase, user_Callback);
                
            //
            // PWM output interrupt enable
            //
            xPWMIntEnable(ulBase, PWMChannel[i], xPWM_INT_PWM);
                
            //
            // NVIC interrupt enable
            //
            xIntEnable(xINT_TIMER1);
            xIntEnable(xINT_TIMER2);
            xIntEnable(xINT_TIMER3);
            xIntEnable(xINT_TIMER4);
                
            //    
            // start pwm
            //
            xPWMStart(ulBase, PWMChannel[i]);
            TestAssertQBreak("a", " pwm intterupt test error!", 0xffffffff);
        }             
    }   
}

//*****************************************************************************
//
//! \brief Get the Test description of xpwm002 PWMode test.
//!
//! \return the desccription of the xpwm002 test.
//
//*****************************************************************************
static char* xpwm002GetTest(void)
{
    return "xpwm, 002, xpwm PWMode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xpwm002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm002Setup(void)
{
   
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMB);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMC);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMD);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWME);
    //
    // GPIO pin function set as pwm output
    //
    xSPinTypeTimer(TIM1CH1, PA8);
    xSPinTypeTimer(TIM1CH2, PE11);
    xSPinTypeTimer(TIM1CH3, PA10);
    xSPinTypeTimer(TIM1CH4, PA11);
    xSPinTypeTimer(TIM2CH1, PA0);
    xSPinTypeTimer(TIM2CH2, PA1);
    xSPinTypeTimer(TIM2CH3, PA2);
    xSPinTypeTimer(TIM2CH4, PA3);
    xSPinTypeTimer(TIM3CH1, PA6);
    xSPinTypeTimer(TIM3CH2, PA7);
    xSPinTypeTimer(TIM3CH3, PB0);
    xSPinTypeTimer(TIM3CH4, PB1);
    xSPinTypeTimer(TIM4CH1, PB6);
    xSPinTypeTimer(TIM4CH2, PB7);
    xSPinTypeTimer(TIM4CH3, PB8);
    xSPinTypeTimer(TIM4CH4, PB9);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xpwm002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm002TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_PWMB);
}

//
// xpwm002 PWMode test case struct.
//
const tTestCase sTestxpwm002PWMode = {
    xpwm002GetTest,
    xpwm002Setup,
    xpwm002TearDown,
    xpwm002Execute
};

//
// Xpwm test suits.
//
const tTestCase * const psPatternxpwm2[] =
{
    &sTestxpwm002PWMode,
    0
};
