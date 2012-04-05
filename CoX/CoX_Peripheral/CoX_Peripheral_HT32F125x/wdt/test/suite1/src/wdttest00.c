//*****************************************************************************
//
//! @page xwdt_testcase xwdt register test
//!
//! File: @ref wdttest00.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xwdt sub component.<br><br>
//! - \p Board: HT32F125x <br><br>
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
//! \file wdttest00.c
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
unsigned long ulWDTInterval[] = {1, 23, 456, 789, 1024, 2047, 88, 66};


//*****************************************************************************
//
//! \brief Get the Test description of xwdt001 register test.
//!
//! \return the desccription of the xwdt001 test.
//
//*****************************************************************************
static char* xwdt001GetTest(void)
{
    return "wdt, 001, wdt register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xwdt001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001Setup(void)
{
    //
    // Enable WDT
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDT);
    //
    // Set WDT clock source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_WDT0_EXTSL, 4);

}


//*****************************************************************************
//
//! \brief  Wdt api wdt's timer interval configure test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WDTimerInit_test(void)
{
    unsigned long i,ulTemp;

    //
    // Enable WDT
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDT);

    for(i=0; i<8; i++)
    {
        WDTimerInit(ulWDTInterval[i]);
        ulTemp = xHWREG(WDT_MR0) & WDT_MR0_WDTV_M;
        TestAssert((ulWDTInterval[i] == ulTemp), "WDT API error!");
    }

    for(i=0; i<8; i++)
    {
        WDTimerDeltaSet(ulWDTInterval[i]);
        ulTemp = xHWREG(WDT_MR1) & WDT_MR1_WDTD_M;
        TestAssert(( ulWDTInterval[i] == ulTemp), "WDT API error!");
    }
}

//*****************************************************************************
//
//! \brief  Wdt api wdt restart test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WDTimerRestart_test(void)
{
    unsigned long ulTemp;
    
    WDTimerRestart();
    ulTemp = xHWREG(WDT_CR);
    TestAssert((0x00 == (ulTemp & WDT_CR)), "WDT API error!");  
}


//*****************************************************************************
//
//! \brief  Wdt api wdt function enable and disable test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WDTimerFunctionEnable_test(void)
{
    unsigned long ulTemp,ulRegVal;

    ulTemp = WDT_INT_FUNCTION | WDT_RESET_FUNCTION;
    
    WDTimerFunctionEnable(ulTemp);
    
    ulRegVal = xHWREG(WDT_MR0);
    
    TestAssert(ulTemp == (ulRegVal & ulTemp), "WDT API error!");
    
    WDTimerFunctionDisable(ulTemp);
    
    ulRegVal = xHWREG(WDT_MR0);
    
    TestAssert( 0 == (ulRegVal & ulTemp),"WDT API error!");
}



//*****************************************************************************
//
//! \brief xwdt001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001Execute(void)
{
    wdt_WDTimerInit_test();
    wdt_WDTimerRestart_test();
    wdt_WDTimerFunctionEnable_test();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xwdt001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001TearDown(void)
{

    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDT);
}

//
// wdt001 register test case struct.
//
const tTestCase sTestXWdt001Register = {
    xwdt001GetTest,	
    xwdt001Setup,
    xwdt001TearDown,
    xwdt001Execute
};

//
// wdt test suits.
//
const tTestCase * const psPatternXwdt00[] =
{
    &sTestXWdt001Register,
    0
};
