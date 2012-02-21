//*****************************************************************************
//
//! @page xpwm_testcase xpwm PWMode test
//!
//! File: @ref xpwmtest2.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: Mini51 <br><br>
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
#include "xhw_pwm.h"

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
static unsigned long PWMCallback( void *pvCBData, unsigned long ulEvent, \
                                     unsigned long ulMsgParam, void *pvMsgData )                                        
{ 
    TestEmitToken('a');
    return 0;
}

//
// pwm base value
//
static unsigned long PWMBase[1] = {xPWMA_BASE};

//
// pwm channel value
//
static unsigned long PWMChannel[6] = {xPWM_CHANNEL0, xPWM_CHANNEL1,
                                      xPWM_CHANNEL2, xPWM_CHANNEL3,
                                      xPWM_CHANNEL4, xPWM_CHANNEL5};

//
// pwm Inttertupt ID
//
static unsigned long IntID[1] = {xINT_PWMA};

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
    for(i = 0; i < 1; i++)
    {   
        for(j = 0; j < 6; j++)
        {
            ulBase = PWMBase[i];
                                                     
            //
            // Set invert, dead zone and mode
            //
            xPWMInitConfigure(ulBase, PWMChannel[j], xPWM_TOGGLE_MODE | 
                                      xPWM_OUTPUT_INVERTER_DIS | xPWM_DEAD_ZONE_DIS);
                        
            //    
            // Set CMR
            //
            xPWMDutySet(ulBase, PWMChannel[j], 40);    
            
            //
            // Set CNR, Prescale and Divider
            //
            xPWMFrequencyConfig(ulBase, PWMChannel[j], 0x3FF0100);
                
            //    
            // Set output enable
            //
            xPWMOutputEnable(ulBase, PWMChannel[j]);   
            
            //
            // Set interrupt call back 
            //
            xPWMIntCallbackInit(ulBase, PWMCallback);
                
            //
            // PWM output interrupt enable
            //
            xPWMIntEnable(ulBase, PWMChannel[j], xPWM_INT_PWM);
                
            //
            // NVIC interrupt enable
            //
            xIntEnable(IntID[i]);
                
            //    
            // start pwm
            //
            xPWMStart(ulBase, PWMChannel[j]);
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
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
   
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMA);
    
    //
    // GPIO pin function set as pwm output
    //
    xSPinTypePWM(PWM0, PC2);    
    xSPinTypePWM(PWM1, PC3); 
    xSPinTypePWM(PWM2, PC4); 
    xSPinTypePWM(PWM3, PC5); 
    xSPinTypePWM(PWM4, PC6); 
    xSPinTypePWM(PWM5, PA4);  
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

