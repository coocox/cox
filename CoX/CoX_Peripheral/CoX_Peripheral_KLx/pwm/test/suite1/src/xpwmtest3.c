//*****************************************************************************
//
//! @page xpwm_testcase xpwm register test
//!
//! File: @ref xpwmtest3.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: KLx25Z128 Development Board <br><br>
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
//! - \subpage test_xpwm_register
//! .
//! \file xpwmtest3.c
//! \brief xpwm test source file
//! \brief xpwm test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_tpm.h"
#include "xpwm.h"
//*****************************************************************************
//
//!\page test_xpwm_register test_xpwm_register
//!
//!<h2>Description</h2>
//!Test xpwm register. <br>
//!
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Get the Test description of xpwm003 register test.
//!
//! \return the desccription of the xpwm003 test.
//
//*****************************************************************************
static char* xpwm003GetTest(void)
{
    return "xpwm, 003, xpwm register test";
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
    //
    // Select the peripheral clock source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_MAIN, 1);
    
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
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
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOE);
}

//*****************************************************************************
//
//! \brief xpwm003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm003Execute(void)
{
    xSPinTypePWM(TIM0CH2, PE29); 
    xSPinTypePWM(TIM0CH3, PE30); 
    
    unsigned long ulBase, ulPWMChannel;
    ulBase = xPWMA_BASE;
    ulPWMChannel = xPWM_CHANNEL2;
     
    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure(ulBase, ulPWMChannel, xPWM_TOGGLE_MODE);            

    //
    // Set CNR, Prescale and Divider
    //
    xPWMFrequencySet(ulBase, ulPWMChannel, 100000);

    //    
    // Set CMR
    //
    xPWMDutySet(ulBase, ulPWMChannel, 70);   
    
    //    
    // Set output enable
    //
    xPWMOutputEnable(ulBase, ulPWMChannel);   
    
    //    
    // start pwm
    //
    xPWMStart(ulBase, ulPWMChannel);
}

//
// xpwm001 register test case struct.
//
const tTestCase sTestxpwm003Register = {
    xpwm003GetTest,
    xpwm003Setup,
    xpwm003TearDown,
    xpwm003Execute
};

//
// Xpwm test suits.
//
const tTestCase * const psPatternxpwm02[] =
{
    &sTestxpwm003Register,
    0
};