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
//! \file xgpiotest2.c
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

//
// Global variable value
//
volatile char cIntCount;

//
// GPIO base value
//
static unsigned long ulGPIO[2] = {xGPIO_PORTA_BASE,xGPIO_PORTD_BASE};

//
// GPIO interrupt ID  
//
static unsigned long ulGPIOInt[2] = {xINT_GPIOA, xINT_GPIOD};

//
// 
//

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback(void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData)                                        
{
    TestEmitToken('a');
    xIntDisable(ulGPIOInt[1]);
    cIntCount++;
    return 0;
}


//*****************************************************************************
//
//! \brief Get the Test description of xgpio002 interrupt test.
//!
//! \return the desccription of the xgpio002 test.
//
//*****************************************************************************
const char* xgpio002GetTest(void)
{
    static const char * const pcName = "xgpio, 002, xgpio interrupt test";      
    return pcName;
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
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);    
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
    cIntCount = 0;
    
    //
    // Level trigger interrupt
    //
    xGPIOSPinTypeGPIOInput(PD7);
    
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(ulGPIO[1], xGPIO_PIN_7, user_Callback);
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable(ulGPIO[1], xGPIO_PIN_7, xGPIO_FALLING_EDGE);
    
    xIntEnable(ulGPIOInt[1]);
    TestAssertQBreak("a", "gpio interrupt teset fail", 0xffffffff);     

}   

//
// xgpio002 interrupt test case struct.
//
const tTestCase sTestxGpio002Interrupt = {
    xgpio002GetTest,
    xgpio002Setup,
    xgpio002TearDown,
    xgpio002Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternxgpio2[] =
{
    &sTestxGpio002Interrupt,
    0
};
