//*****************************************************************************
//
//! @page xgpio_testcase xgpio interrupt test
//!
//! File: @ref xgpiotest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xgpio sub component.<br><br>
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
//! - \subpage test_xgpio_interrupt
//! .
//! \file xgpiotest3.c
//! \brief xgpio test source file
//! \brief xgpio test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xgpio_interrupt test_xgpio_interrupt
//!
//!<h2>Description</h2>
//!Test xgpio interrupt. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
static unsigned long user_Callback0(void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData)                                        
{
    TestEmitToken('a');
    xIntDisable(xINT_EINT0);
    return 0;
}

static unsigned long user_Callback1(void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData)                                        
{
    TestEmitToken('a');
    xIntDisable(xINT_EINT1);    
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xgpio002 interrupt test.
//!
//! \return the desccription of the xgpio002 test.
//
//*****************************************************************************
static char* xgpio002GetTest(void)
{
    return "xgpio, 002, EINT interrupt test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio002Setup(void)
{
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio002TearDown(void)
{
    xSysCtlPeripheralReset(SYSCTL_PERIPH_GPIO);
}

//*****************************************************************************
//
//! \brief xgpio002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio002Execute(void)
{          
    //
    // Set PD.3 mode in.
    //  
    xSPinTypeEXTINT(NINT0, PD2);
    
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(xGPIO_PORTD_BASE, xGPIO_PIN_2, user_Callback0);
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable(xGPIO_PORTD_BASE, xGPIO_PIN_2, xGPIO_FALLING_EDGE);
    
    xIntEnable(xINT_EINT0);
    TestAssertQBreak("a", "gpio interrupt test fail", 0xffffffff);  
    //--------------------------------------------------------------------
    
    //
    // Set PD.3 mode in.
    //  
    xSPinTypeEXTINT(NINT1, PF2);
    
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(xGPIO_PORTF_BASE, xGPIO_PIN_2, user_Callback1);
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable(xGPIO_PORTF_BASE, xGPIO_PIN_2, xGPIO_FALLING_EDGE);
    
    xIntEnable(xINT_EINT1);
    TestAssertQBreak("a", "gpio interrupt test fail", 0xffffffff);  
    //--------------------------------------------------------------------    
        
}   

//
// xgpio002 interrupt test case struct.
//
const tTestCase sTestxGpio002EINT = {
    xgpio002GetTest,
    xgpio002Setup,
    xgpio002TearDown,
    xgpio002Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternxgpio3[] =
{
    &sTestxGpio002EINT,
    0
};
