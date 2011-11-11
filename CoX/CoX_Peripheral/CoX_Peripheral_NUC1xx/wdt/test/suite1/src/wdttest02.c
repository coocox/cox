//*****************************************************************************
//
//! @page xwdt_testcase xwdt register test
//!
//! File: @ref wdttest02.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xwdt sub component.<br><br>
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
//! - \subpage test_xgpio_register
//! .
//! \file wdttest02.c
//! \brief xwdt test source file
//! \brief xwdt test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_wdt.h"
#include "xwdt.h"

//*****************************************************************************
//
//!\page test_xwdt_register test_xwdt_register
//!
//!<h2>Description</h2>
//!Test xwdt register. <br>
//!
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Get the Test description of xwdt004 register test.
//!
//! \return the desccription of the xwdt004 test.
//
//*****************************************************************************
static char* xwdt003GetTest(void)
{
    return "xwdt, 003, wdt wake up function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xwdt004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt003Setup(void)
{
//
// Set WDT clock source
//
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_WDG_S_INT10K);
    
//
// Enable WDT
//
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDT);
}

//*****************************************************************************
//
//! \breif Wdt interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long WDTCallbackSW(void *pvCBData, unsigned long ulEvent, 
                                      unsigned long ulMsgParam, void *pvMsgData)                                        
{

    GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 
                                                             | GPIO_PIN_15, 1 ); 

//
// clear WDT counter
//
    WDTimerRestart();
        
    return 0;
}


//*****************************************************************************
//
//! \brief  Wdt api wdt wakeup test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WakeUp_test(void)
{
//
// Set WatchDog Timer(WDT)'s Timer Interval.
//  
    WDTimerInit(WDT_INTERVAL_2_10T);
    
//
// Enter WDT function of wake up
//    
    WDTimerFunctionEnable(WDT_WAKEUP_FUNCTION | WDT_INT_FUNCTION);
    
    xIntEnable(INT_WDT);
    
//
// Install WDT callback function
//
    WDTimerIntCallbackInit(WDTCallbackSW);
    
//
// Start the WDT
//
    WDTimerEnable();
   
//
// Enter power down mode
//
    SysCtlPWRWUIntEnable(xtrue, xtrue);
    SysCtlPowerDownEnable(xtrue);
    SysCtlPowerDownWaitCPUSet(xtrue);
    xCPUwfi();
}

//*****************************************************************************
//
//! \brief xwdt004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt003Execute(void)
{
    wdt_WakeUp_test();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xwdt003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt003TearDown(void)
{
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDT);
}


//
// wdt003 register test case struct.
//
const tTestCase sTestXWdt003Register = {
    xwdt003GetTest,		
    xwdt003Setup,
    xwdt003TearDown,
    xwdt003Execute
};


//
// wdt test suits.
//
const tTestCase * const psPatternXwdt02[] =
{
    &sTestXWdt003Register,
    0
};