//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
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

unsigned long ulBodVoltage[] = {SYSCTL_BOD_2_2, SYSCTL_BOD_2_6, SYSCTL_BOD_3_8,
                                                                SYSCTL_BOD_4_5};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the desccription of the xcore004 test.
//
//*****************************************************************************
static char* xSysctl005GetTest(void)
{
    return "xsysctl, 005, xsysctl register and api test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005Setup(void)
{
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL32K_EN;
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC10K_EN;
    xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;
    xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005TearDown(void)
{   
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN|SYSCTL_PLL_PWRDN
                                                           | SYSCTL_INT_OSC_DIS;
    SysCtlHClockSet(ulTemp);

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|1);
}


//*****************************************************************************
//
//! \brief xsysctl 002 test of SysCtl Power Down Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPowerDownEnable_test(void)
{
    unsigned long ulTemp;
    SysCtlPowerDownEnable(xtrue);
    ulTemp = xHWREG(SYSCLK_PWRCON);
    TestAssert(ulTemp == 0x0000009F, "xsysctl API  error!");
}


//*****************************************************************************
//
//! \brief xsysctl 002 test of tempature sensor enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlTempatureSensorEnable_test(void)
{
    unsigned long ulTemp;
    SysCtlTempatureSensorEnable(xtrue);
    ulTemp = xHWREG(GCR_TEMPCR);
    TestAssert((ulTemp == (ulTemp & GCR_TEMPCR_VTEMP_EN)), "xsysctl API error!");
    
    SysCtlTempatureSensorEnable(xfalse);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((0 == (ulTemp & GCR_TEMPCR_VTEMP_EN)), "xsysctl API error!");
}


//*****************************************************************************
//
//! \brief xsysctl 005 test of Brown-Out Detector Control Register test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_Bod_test(void)
{
    xtBoolean xtTemp,i;
    unsigned long ulTemp; 
    
    SysCtlBODEnable(xtrue);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((GCR_BODCR_BOD_EN == (ulTemp & GCR_BODCR_BOD_EN)),
                                                          "xsysctl API error!");
    
    SysCtlBODEnable(xfalse);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((0 == (ulTemp & GCR_BODCR_BOD_EN)), "xsysctl API error!");
    //
    // Set Threshold Voltage as 2.2V test
    //
    for(i = 0; i < 4; i++)
    {
        SysCtlBODVoltSelect(ulBodVoltage[i]);
        ulTemp = xHWREG(GCR_BODCR);
        TestAssert((i == (ulTemp & GCR_BODCR_BOD_VL_M)>>GCR_BODCR_BOD_VL_S),
                                                          "xsysctl API error!");
    }
    
    SysCtlBODLowPowerModeEnable(xtrue);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((GCR_BODCR_BOD_LPM == (ulTemp & GCR_BODCR_BOD_LPM)),
                                                          "xsysctl API error!");
    
    SysCtlBODLowPowerModeEnable(xfalse);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((0 == (ulTemp & GCR_BODCR_BOD_LPM)), "xsysctl API error!");
    
    SysCtlLowVoltRstEnable(xtrue);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((GCR_BODCR_LVR_EN == (ulTemp & GCR_BODCR_LVR_EN)),
                                                          "xsysctl API error!");
    
    SysCtlLowVoltRstEnable(xfalse);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((0 == (ulTemp & GCR_BODCR_LVR_EN)), "xsysctl API error!");
    
    xtTemp = SysCtlBODStateGet();
    TestAssert((xtTemp==0 ),"xsysctl API \"SysCtlBODStateGet()\" error!");
    
    SysCtlBODRstEnable(xtrue);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((GCR_BODCR_BOD_RSTEN == (ulTemp & GCR_BODCR_BOD_RSTEN)),
                                                          "xsysctl API error!");
    
    SysCtlBODRstEnable(xfalse);
    ulTemp = xHWREG(GCR_BODCR);
    TestAssert((0 == (ulTemp & GCR_BODCR_BOD_RSTEN)),"xsysctl API error!");
    //
    //Set RC adjustment value 
    //
    SysCtlRCAdjValueSet(0x34);
    TestAssert((0x34 == (xHWREG(GCR_RCADJ) & GCR_RCADJ_RCADJ_M)),
                                                          "xsysctl API error!");
}


//*****************************************************************************
//
//! \brief xsysctl 005 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005Execute(void)
{
    xsysctl_SysCtlTempatureSensorEnable_test();
    xsysctl_SysCtlPowerDownEnable_test();
    xsysctl_Bod_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl005Register = {
    xSysctl005GetTest,
    xSysctl005Setup,
    xSysctl005TearDown,
    xSysctl005Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl04[] =
{
    &sTestXSysctl005Register,
    0
};