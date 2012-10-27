//*****************************************************************************
//
//! @page xwdt_testcase xwdt register test
//!
//! File: @ref wdttest00.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xwdt sub component.<br><br>
//! - \p Board: Freescale Freedom <br><br>
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
    //Here is Nothing to do 
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
   WDTimerInit(WDT_MODE_NORMAL | WDT_INTERVAL_BUS_2_13T);
   WDTimerEnable(); 
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
    //Here is Nothing to do 
}

//
// wdt001 register test case struct.
//
const tTestCase sTestXWdt001Register =
{
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
