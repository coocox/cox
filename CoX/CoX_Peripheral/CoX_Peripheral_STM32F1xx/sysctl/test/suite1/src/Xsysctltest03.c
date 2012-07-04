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
unsigned long ulRTCSource[] = {SYSCTL_RTC_LSE, SYSCTL_RTC_LSI,
SYSCTL_RTC_LSE_128};


unsigned long ulMCOClkSource[] = {SYSCTL_MCO_SYSCLK, SYSCTL_MCO_HSI,  
SYSCTL_MCO_HSE, SYSCTL_MCO_PLL_2, SYSCTL_MCO_XT1,SYSCTL_MCO_PLL3,
SYSCTL_MCO_PLL2, SYSCTL_MCO_PLL3_2,};


unsigned long ulI2S2ClkSource[] = {SYSCTL_I2S2_SYSCLK, 
SYSCTL_I2S2_PLL3};

unsigned long ulI2S3ClkSource[] = {SYSCTL_I2S3_SYSCLK, 
SYSCTL_I2S3_PLL3};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xsysctl002 test.
//
//*****************************************************************************
static char* xSysctl002GetTest(void)
{
    return "xsysctl, 002, xsysctl register and api test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl002Setup(void)
{
    SysCtlLSIConfig(SYSCTL_LSI_OSC_EN);
    SysCtlLSEConfig(SYSCTL_LSE_OSC_EN);
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl002TearDown(void)
{   

}

//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral Clock Source Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralClockSourceSet_test(void)
{
    unsigned long i,ulTemp;
    
    for(i = 0; i < 3; i++)
    {
        SysCtlPeripheralClockSourceSet(ulRTCSource[i]);
        ulTemp = xHWREG(RCC_BDCR);
        TestAssert(((i+1) == (ulTemp & RCC_BDCR_RTCSEL_M)) << RCC_BDCR_RTCSEL_S,
                   "xsysctl API error!");
    }
    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulMCOClkSource[i]);
        ulTemp = xHWREG(RCC_CFGR);
        TestAssert(((i+4) == (ulTemp & RCC_CFGR_MCO_M)) << RCC_CFGR_MCO_S,
                   "xsysctl API error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl002Execute(void)
{
    xsysctl_SysCtlPeripheralClockSourceSet_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl002Register = {
    xSysctl002GetTest,
    xSysctl002Setup,
    xSysctl002TearDown,
    xSysctl002Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl03[] =
{
    &sTestXSysctl002Register,
    0
};
