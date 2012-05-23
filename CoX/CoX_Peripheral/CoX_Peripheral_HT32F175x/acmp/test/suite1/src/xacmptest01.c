//*****************************************************************************
//
//! @page xacmp_testcase xcore register test
//!
//! File: @ref xacmptest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xacmp sub component.<br><br>
//! - \p Board: HT32F175x/275x <br><br>
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
//! - \subpage test_xacmp_register
//! .
//! \file xacmptest.c
//! \brief xacmp test source file
//! \brief xacmp test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"
#include "xhw_acmp.h"
#include "xacmp.h"
//*****************************************************************************
//
//!\page test_xacmp_register test_xacmp_register
//!
//!<h2>Description</h2>
//!Test xacmp register. <br>
//!
//
//*****************************************************************************

unsigned long ulBase = ACMP_BASE;

unsigned long ulTempData[] = {ACMP_POSITIVE_INPUT | ACMP_MODE_CMP,
                               ACMP_POSITIVE_INPUT | ACMP_MODE_OP,
                               ACMP_NEGATIVE_INPUT | ACMP_MODE_CMP,
                               ACMP_NEGATIVE_INPUT | ACMP_MODE_OP
                              };

//*****************************************************************************
//
//! \breif xacmp slave interrupt install function
//! 
//! \return none
//
//*****************************************************************************
unsigned long ACMPCallback(void *pvCBData, 
                           unsigned long ulEvent,
                           unsigned long ulMsgParam,
                           void *pvMsgData)
{
    TestEmitToken('a');
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xacmp001 register test.
//!
//! \return the desccription of the xacmp001 test.
//
//*****************************************************************************
static char* xACMP001GetTest(void)
{
    return "xACMP, 001, xACMP Peripheral register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xacmp001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xACMP001Setup(void)
{    
    xSysCtlPeripheralEnable2(xACMP0_BASE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_OPA1);
    xSysCtlPeripheralReset2(xACMP0_BASE);
    
    xSysCtlPeripheralEnable2(xGPIO_PORTB_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeACMP(CMP0P, PE6);
    xSPinTypeACMP(CMP0N, PE5);
    xSPinTypeACMP(CMP0O, PE7);
    xSPinTypeACMP(CMP1P, PE9);
    xSPinTypeACMP(CMP1N, PE8);
    xSPinTypeACMP(CMP1O, PE10);
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xacmp001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xACMP001TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xacmp 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xACMP001Execute(void)
{
    int i,j;
    unsigned long ulTemp;
    for(i=0; i<2; i++)
    {
        ACMPEnable(ulBase, i);
        ulTemp = xHWREG(ulBase + ACMP_OPACR + i*0x100) & ACMP_OPACR_EN;
        TestAssert(ACMP_OPACR_EN == ulTemp, 
               "xi2c API \"ACMPEnable\" error!");
        
        ACMPDisable(ulBase, i);
        ulTemp = xHWREG(ulBase + ACMP_OPACR + i*0x100) & ACMP_OPACR_EN;
        TestAssert(0 == ulTemp, 
               "xi2c API \"ACMPDisable\" error!");
        
        ACMPIntEnable(ulBase, i, ACMP_INT_RISING | ACMP_INT_FALLING);
        ulTemp = xHWREG(ulBase + ACMP_IER + i*0x100);
        TestAssert(ACMP_INT_RISING | ACMP_INT_FALLING == ulTemp, 
               "xi2c API \"ACMPIntEnable\" error!");
        
        ACMPIntDisable(ulBase, i, ACMP_INT_RISING | ACMP_INT_FALLING);
        ulTemp = xHWREG(ulBase + ACMP_IER + i*0x100);
        TestAssert(0 == ulTemp, 
               "xi2c API \"ACMPIntDisable\" error!");
        
        for(j=0; j<4; j++)
        {
            ACMPConfigure(ulBase, i, ulTempData[j]);
            ulTemp = xHWREG(ulBase + ACMP_OPACR + i*0x100) & ulTempData[0];
            TestAssert(ulTempData[j] == ulTemp, 
                       "xi2c API \"ACMPConfigure\" error!");
        }
        
    }
}

//*****************************************************************************
//
//! \brief Get the Test description of xacmp001 register test.
//!
//! \return the desccription of the xacmp001 test.
//
//*****************************************************************************
static char* xACMP002GetTest(void)
{
    return "xACMP, 002, xACMP Interrupt test";
}

//*****************************************************************************
//
//! \brief xacmp 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xACMP002Execute(void)
{
    unsigned long ulTemp;
    for(ulTemp=0;ulTemp<2;ulTemp++)
    {
        ACMPConfigure(ulBase, ulTemp, ulTempData[0]);
        ACMPCancellation(ulBase, ulTemp, ACMP_POSITIVE_INPUT);
        ACMPEnable(ulBase, ulTemp);
        ACMPIntEnable(ulBase, ulTemp, ACMP_INT_RISING | ACMP_INT_FALLING);  
        xACMPIntCallbackInit(ulBase, ulTemp, ACMPCallback);
        xIntEnable(xSysCtlPeripheralIntNumGet(ulBase));
        SysCtlDelay(20000);
        TestAssertQBreak("a", "Int error!", -1);
    }
    
}

//
// xacmp register test case struct.
//
const tTestCase sTestXacmp001Register = {
		xACMP001GetTest,
		xACMP001Setup,
		xACMP001TearDown,
		xACMP001Execute
};

//
// xacmp register test case struct.
//
const tTestCase sTestXacmp002Register = {
		xACMP002GetTest,
		xACMP001Setup,
		xACMP001TearDown,
		xACMP002Execute
};

//
// xacmp test suits.
//
const tTestCase * const psPatternXacmp01[] =
{
    &sTestXacmp001Register,
    0
};

//
// xacmp test suits.
//
const tTestCase * const psPatternXacmp02[] =
{
    &sTestXacmp002Register,
    0
};
