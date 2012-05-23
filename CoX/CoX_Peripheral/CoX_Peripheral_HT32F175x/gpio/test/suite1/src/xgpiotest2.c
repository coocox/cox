//*****************************************************************************
//
//! @page xgpio_testcase xgpio EXTI interrupt test
//!
//! File: @ref xgpiotest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xgpio sub component.<br><br>
//! - \p Board: HT32F125x Development Board <br><br>
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
//! - \subpage test_xgpio_EXTI_interrupt
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

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback0(void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData)                                        
{
    TestEmitToken('a');
    xIntDisable(xINT_GPIOA);
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
    static const char * const pcName = "xgpio, 002, xgpio EXTI line interrupt test";
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
    xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_EXTI);
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
    xSysCtlPeripheralReset(SYSCTL_PERIPH_EXTI);  
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
	// Set as gpio function
	//
	GPIOPinFunctionSet(GPIO_FUNCTION_GPIO, GPIO_PORTA_BASE, xGPIO_PIN_10);    

	//
    // Set PA.0 as mode in
    //
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_IN);
    
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(xGPIO_PORTA_BASE, xGPIO_PIN_10, user_Callback0);
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable(xGPIO_PORTA_BASE, xGPIO_PIN_10, GPIO_FALLING_EDGE);
    
    xIntEnable(xINT_GPIOA);
    TestAssertQBreak("a", "gpio interrupt test fail", 0xffffffff);    
 
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
