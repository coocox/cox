//*****************************************************************************
//
//! @page xcore_testcase xcore Interrupt corresponding API test
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
const char* xcore001GetTest(void)
{
    const char * const pcName = "xcore, 001, xcore interrupt corresponding APIS test";
    return pcName;
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
    //xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
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
        xIntPrioritySet(20, 2);
	ulTemp = xIntPriorityGet(20);
	TestAssert(2 == ulTemp, "Priority Set Test fail");
	
	xIntPrioritySet(xINT_GPIOA, 2);
	ulTemp = xIntPriorityGet(xINT_GPIOA);
	TestAssert(2 == ulTemp, "Priority Set Test fail");

	xIntPrioritySet(xINT_GPIOA, 1);
	ulTemp = xIntPriorityGet(xINT_GPIOA);
	TestAssert(1 == ulTemp, "Priority Set Test fail");
        
	xIntPrioritySet(xFAULT_SYSTICK, 1);
	ulTemp = xIntPriorityGet(xFAULT_SYSTICK);
	TestAssert(1 == ulTemp, "Priority Set Test fail"); 
 
	xIntPrioritySet(xINT_SYSCTL, 1);
	ulTemp = xIntPriorityGet(INT_LVD);
	TestAssert(1 == ulTemp, "Priority Set Test fail");            

        //
	// Int Enable and Disable test
	//
	xIntEnable(21);
	ulTemp = xHWREG(NVIC_EN0) & 0x20;
        TestAssert(0x20 == ulTemp, "Int Enable Test fail");
	xIntDisable(21);
	ulTemp = xHWREG(NVIC_DIS0) & 0x20;
        TestAssert(0 == ulTemp, "Int Disable Test fail");
 /*       
	xIntEnable(xFAULT_SYSTICK);
	ulTemp = xHWREG(NVIC_ST_CTRL) & NVIC_ST_CTRL_INTEN;
        TestAssert(NVIC_ST_CTRL_INTEN == ulTemp, "Int Enable Test fail");
	xIntDisable(xFAULT_SYSTICK);
	ulTemp = xHWREG(NVIC_ST_CTRL) & NVIC_ST_CTRL_INTEN;
        TestAssert(0 == ulTemp, "Int Disable Test fail"); 
 */      
        xIntEnable(xINT_GPIOD);
	ulTemp = xHWREG(NVIC_EN0) & 0x80000000;
        TestAssert(0x80000000 == ulTemp, "Int Enable Test fail");
	xIntDisable(xINT_GPIOD);
	ulTemp = xHWREG(NVIC_DIS0) & 0x80000000;
        TestAssert(0 == ulTemp, "Int Disable Test fail"); 
        
        xIntEnable(xINT_SYSCTL);
	ulTemp = xHWREG(NVIC_EN0) & 0x000000C0;
        TestAssert(0x000000C0 == ulTemp, "Int Enable Test fail");
	xIntDisable(xINT_SYSCTL);
	ulTemp = xHWREG(NVIC_DIS0) & 0x000000C0;
        TestAssert(0 == ulTemp, "Int Disable Test fail");         
          
	//
	// Pend set and clear test
	//
	xIntPendSet(21);
	ulTemp = xHWREG(NVIC_PEND0) & 0x20;
        TestAssert(0x20 == ulTemp, "Int Pend Set Test fail");
	xIntPendClear(21);
	ulTemp = xHWREG(NVIC_PEND0) & 0x20;
        TestAssert(0 == ulTemp, "Int Pend Clear Test fail");

	xIntPendSet(xINT_SYSCTL);
	ulTemp = xHWREG(NVIC_PEND0) & 0xC0;
        TestAssert(0xC0 == ulTemp, "Int Pend Set Test fail");
	xIntPendClear(xINT_SYSCTL);
	ulTemp = xHWREG(NVIC_PEND0) & 0xC0;
        TestAssert(0 == ulTemp, "Int Pend Clear Test fail");        
        
	xIntPendSet(xFAULT_SYSTICK);
	ulTemp =  xHWREG(NVIC_INT_CTRL) & NVIC_INT_CTRL_PENDSTSET;
        TestAssert(NVIC_INT_CTRL_PENDSTSET == ulTemp, "Int Pend Set Test fail");
	xIntPendClear(xFAULT_SYSTICK);
	ulTemp = xHWREG(NVIC_INT_CTRL) & NVIC_INT_CTRL_PENDSTCLR;
        TestAssert(NVIC_INT_CTRL_PENDSTCLR == ulTemp, "Int Pend Clear Test fail"); 
        
    //
    // System tick Enable test
    //       
    xSysTickEnable(); 
    ulTemp = xHWREG(NVIC_ST_CTRL) & NVIC_ST_CTRL_ENABLE;
    TestAssert(NVIC_ST_CTRL_ENABLE == ulTemp, "System tick Enable test"); 
    
    xSysTickDisable();
    ulTemp = xHWREG(NVIC_ST_CTRL) & NVIC_ST_CTRL_ENABLE;
    TestAssert(0 == ulTemp, "System tick Enable test"); 
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
