//*****************************************************************************
//
//! @page xpwm_testcase xpwm CaptureMode test
//!
//! File: @ref xpwmtest3.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: NUC140 <br><br>
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
//! - \subpage test_xpwm_CaptureMode
//! .
//! \file xpwmtest3.c
//! \brief xpwm test source file
//! \brief xpwm test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xpwm.h"
#include "xhw_pwm.h"

//*****************************************************************************
//
//!\page test_xpwm_CaptureMode test_xpwm_CaptureMode
//!
//!<h2>Description</h2>
//!Test xpwm CaptureMode. <br>
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
    TestEmitToken('a');
    return 0;
}

//
// pwm base value
//
static unsigned long PWNBase[2] = {xPWMA_BASE, xPWMB_BASE};

//
// pwm channel value
//
static unsigned long PWMChannel[2][4] = {
                                         {xPWM_CHANNEL0, xPWM_CHANNEL1,
                                          xPWM_CHANNEL2,xPWM_CHANNEL3},
                                         {xPWM_CHANNEL4,xPWM_CHANNEL5,
                                          xPWM_CHANNEL6,xPWM_CHANNEL7}
                                        };

//
// pwm Inttertupt ID
//
static unsigned long IntID[2] = {xINT_PWMA, xINT_PWMB};

//*****************************************************************************
//
//! \brief xpwm003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm003Execute(void)
{          
  
    unsigned long ulBase;
        
    int i, j;
    for(i = 0; i < 2; i++)
    {   
        for(j = 0; j < 4; j++)
        {
            ulBase = PWNBase[i];
                                                     
            //
            // Set invert, dead zone and mode
            //
            xPWMInitConfigure(ulBase, PWMChannel[i][j], xPWM_TOGGLE_MODE | 
                                            xPWM_OUTPUT_INVERTER_DIS | xPWM_DEAD_ZONE_DIS);
                
            // Set CNR, Prescale and Divider
            xPWMFrequencyConfig(ulBase, PWMChannel[i][j], 0x3FF0100);
                
            //    
            // Set output disable
            //
            xPWMOutputDisable(ulBase, PWMChannel[i][j]);   
            
            //
            // Enable capture in
            //
            PWMCAPInputEnable(ulBase, PWMChannel[i][j]);
            
            //
            // Set interrupt call back 
            //
            xPWMIntCallbackInit(ulBase, user_Callback);
                
            //
            // PWM output interrupt enable
            //
            xPWMIntEnable(ulBase, PWMChannel[i][j], PWM_INT_CAP_BOTH);
                
            //
            // NVIC interrupt enable
            //
            xIntEnable(IntID[i]);
                
            //    
            // start pwm
            //
            PWMCAPEnable(ulBase, PWMChannel[i][j]);
            TestAssertQBreak("a", " pwm intterupt test error!", 0xffffffff);
        }             
    }
    
}

//*****************************************************************************
//
//! \brief Get the Test description of xpwm003 CaptureMode test.
//!
//! \return the desccription of the xpwm003 test.
//
//*****************************************************************************
static char* xpwm003GetTest(void)
{
    return "xpwm, 003, xpwm CaptureMode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xpwm003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm003Setup(void)
{
    SysCtlKeyAddrUnlock();  
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
   
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMB);
    
    //
    // GPIO pin function set as pwm output
    //
    xSPinTypePWM(PWM0, PA12);    
    xSPinTypePWM(PWM1, PA13); 
    xSPinTypePWM(PWM2, PA14); 
    xSPinTypePWM(PWM3, PA15); 
    xSPinTypePWM(PWM4, PB11); 
    xSPinTypePWM(PWM5, PE5); 
    xSPinTypePWM(PWM6, PE0); 
    xSPinTypePWM(PWM7, PE1);     
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xpwm003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm003TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_PWMB);
}

//
// xpwm003 CaptureMode test case struct.
//
const tTestCase sTestxpwm003CaptureMode = {
    xpwm003GetTest,
    xpwm003Setup,
    xpwm003TearDown,
    xpwm003Execute
};

//
// Xpwm test suits.
//
const tTestCase * const psPatternxpwm3[] =
{
    &sTestxpwm003CaptureMode,
    0
};

