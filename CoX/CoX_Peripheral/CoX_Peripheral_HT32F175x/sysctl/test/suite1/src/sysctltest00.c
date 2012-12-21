//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: HT32F175x <br><br>
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
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"

//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl001GetTest(void)
{
    return "xsysctl, 001, xsysctl Clock Set and Get Test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001Setup(void)
{
 
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001TearDown(void)
{   

}


//*****************************************************************************
//
//! \brief xsysctl 001 test of set and get HCLK test .
//!
//! \return None.
//
//*****************************************************************************

static void xsysctl_SetHCLK_test(void)
{
	unsigned long ulTemp;

    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 72000000), "xsysctl API error!");
/*
    xSysCtlClockSet(32000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 32000000), "xsysctl API error!");

    xSysCtlClockSet(24000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 24000000), "xsysctl API error!");

    xSysCtlClockSet(16000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 16000000), "xsysctl API error!");

    xSysCtlClockSet(8000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 8000000), "xsysctl API error!");

    xSysCtlClockSet(4000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 4000000), "xsysctl API error!");

    xSysCtlClockSet(2000000, xSYSCTL_OSC_INT | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 2000000), "xsysctl API error!");

    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 72000000), "xsysctl API error!");
*/
}

//*****************************************************************************
//
//! \brief xsysctl 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001Execute(void)
{
    xsysctl_SetHCLK_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl001Register = {
		xSysctl001GetTest,
		xSysctl001Setup,
		xSysctl001TearDown,
		xSysctl001Execute
};

//
// xsysctl test suits.
//
const tTestCase * const psPatternXsysctl00[] =
{
    &sTestXSysctl001Register,
    0
};
