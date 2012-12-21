//*****************************************************************************
//
//! @page xcore_testcase xcore Intterrupt corresponding API test
//!
//! File: @ref xcoretest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xcore sub component.<br><br>
//! - \p Board: HT32F125x Development Board<br><br>
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
//! - \subpage test_xcore_register
//! .
//! \file xcoretest1.c
//! \brief xcore test source file
//! \brief xcore test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xcore_register test_xcore_register
//!
//!<h2>Description</h2>
//!Test xcore register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of xcore001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xcore001GetTest(void)
{
    return "xcore, 001, xcore interrupt corresponding APIS test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xcore001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xcore001Setup(void)
{
    xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xcore001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xcore001TearDown(void)
{
}

//*****************************************************************************
//
//! \brief xcore001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xcore001Execute(void)
{
    unsigned long ulTemp;

	//
	// Priority set and get test
	//
//	xIntPriorityGroupingSet(0);
    xIntPrioritySet(20, 2);
//    xHWREG(NVIC_PRI1) = 0xff;
	ulTemp = xIntPriorityGet(20);
//	ulTemp = xHWREG(NVIC_PRI1) & 0xff;
	TestAssert(2 == ulTemp, "Priority Set Test fail");
	
		
	xIntPrioritySet(xINT_GPIOA, 2);
	ulTemp = xIntPriorityGet(xINT_GPIOA);
	TestAssert(2 == ulTemp, "Priority Set Test fail");

	xIntPrioritySet(xINT_GPIOA, 1);
	ulTemp = xIntPriorityGet(xINT_GPIOA);
	TestAssert(1 == ulTemp, "Priority Set Test fail");

    //
	// Int Enable and Disable test
	//
	xIntEnable(20);
	ulTemp = xHWREG(NVIC_EN0) & 0x10;
    TestAssert(0x10 == ulTemp, "Int Enable Test fail");

	xIntEnable(63);
	xIntDisable(63);
	 xHWREG(NVIC_EN1) = 0x00008000;
	 xIntDisable(63);
	/*
	ulTemp = xHWREG(NVIC_EN1) & 0x10;
    TestAssert(0x10 == ulTemp, "Int Enable Test fail");
	*/

	xIntDisable(20);
	ulTemp = xHWREG(NVIC_EN0) & 0x10;
    TestAssert(0 == ulTemp, "Int Disable Test fail");

	//
	// Pend set and clear test
	//
	xIntPendSet(20);
	ulTemp = xHWREG(NVIC_PEND0) & 0x10;
    TestAssert(0x10 == ulTemp, "Int Pend Set Test fail");

	xIntPendClear(20);
	ulTemp = xHWREG(NVIC_PEND0) & 0x10;
    TestAssert(0 == ulTemp, "Int Pend Clear Test fail");

}   

//
// xcore001 register test case struct.
//
const tTestCase sTestxcore001Register = {
    xcore001GetTest,
    xcore001Setup,
    xcore001TearDown,
    xcore001Execute
};

//
// xcore test suits.
//
const tTestCase * const psPatternxcore1[] =
{
    &sTestxcore001Register,
    0
};
