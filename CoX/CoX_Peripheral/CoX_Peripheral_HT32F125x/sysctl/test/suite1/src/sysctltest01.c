//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
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

unsigned long ulxWDT0ClkSrc[] = {xSYSCTL_WDT0_INTSL, xSYSCTL_WDT0_EXTSL};


unsigned long ulxUART0ClkSrc[] = {xSYSCTL_UART0_HCLK, xSYSCTL_UART0_HCLK_2};


unsigned long ulxADC0ClkSrc[] = {xSYSCTL_ADC0_HCLK, xSYSCTL_ADC0_HCLK_2, 
                                 xSYSCTL_ADC0_HCLK_4, xSYSCTL_ADC0_HCLK_8,
								 xSYSCTL_ADC0_HCLK_16, xSYSCTL_ADC0_HCLK_32,
								 xSYSCTL_ADC0_HCLK_64, xSYSCTL_ADC0_HCLK_6};

unsigned long ulWDT0ClkSrc[] = {SYSCTL_PERIPH_WDG_S_INTER, SYSCTL_PERIPH_WDG_S_EXTSL};


unsigned long ulUART0ClkSrc[] = {SYSCTL_PERIPH_UART_S_HCLK, 
                                 SYSCTL_PERIPH_UART_S_HCLK_2};


unsigned long ulADC0ClkSrc[] = {SYSCTL_PERIPH_ADC_S_HCLK, 
                                SYSCTL_PERIPH_ADC_S_HCLK_2,
								SYSCTL_PERIPH_ADC_S_HCLK_4,
								SYSCTL_PERIPH_ADC_S_HCLK_8,
								SYSCTL_PERIPH_ADC_S_HCLK_16,
								SYSCTL_PERIPH_ADC_S_HCLK_32,
								SYSCTL_PERIPH_ADC_S_HCLK_64,
								SYSCTL_PERIPH_ADC_S_HCLK_6};
//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl002GetTest(void)
{
    return "xsysctl, 002, SysCtl Peripheral Clock Source Set test";
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
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
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_HCLK);
}


//*****************************************************************************
//
//! \brief xsysctl 004 test of Set a peripheral clock source and peripheral 
//£¡ divide test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralClockSourceSet_test(void)
{
    unsigned long ulTemp,i;

    //
	// Test watchdog clock source
	//
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxWDT0ClkSrc[i], 4);
        ulTemp = xHWREG(SYSCLK_GCFGR);
        TestAssert((i == ((ulTemp & xSYSCTL_WDT0_EXTSL)>>3)), "xsysctl API error!");
    }

    //
	// Test Uart clock source
	//
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxUART0ClkSrc[i], 1);
        ulTemp = xHWREG(SYSCLK_GCFGR);
        TestAssert(((i*2) == ((ulTemp & SYSCLK_GCFGR_URPRE_M)>>SYSCLK_GCFGR_URPRE_S)), 
		                                                    "xsysctl API error!");
    }

    //
	// Test ADC clock source
	//
    for(i = 0; i < 8; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxADC0ClkSrc[i], 16);
        ulTemp = xHWREG(SYSCLK_APBCFGR);
        TestAssert((i == ((ulTemp & SYSCLK_APBCFGR_ADCDIV_M)>>SYSCLK_APBCFGR_ADCDIV_S)),
		                                                          "xsysctl API error!");
    }

    //
	// Test watchdog clock source
	//
    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralClockSourceSet(ulWDT0ClkSrc[i]);
        ulTemp = xHWREG(SYSCLK_GCFGR);
        TestAssert((i == ((ulTemp & SYSCLK_GCFGR_WDTSRC_LSE)>>3)), "xsysctl API error!");
    }

    //
	// Test Uart clock source
	//
    for(i = 0; i < 1; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulUART0ClkSrc[i], 2);
        ulTemp = xHWREG(SYSCLK_GCFGR);
        TestAssert(((i*2) == ((ulTemp & SYSCLK_GCFGR_URPRE_M)>>SYSCLK_GCFGR_URPRE_S)), 
		                                                    "xsysctl API error!");
    }

    //
	// Test ADC clock source
	//
    for(i = 0; i < 8; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulADC0ClkSrc[i], 2);
        ulTemp = xHWREG(SYSCLK_APBCFGR);
        TestAssert((i == ((ulTemp & SYSCLK_APBCFGR_ADCDIV_M)>>SYSCLK_APBCFGR_ADCDIV_S)),
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
//    xsysctl_xSysCtlPeripheralClockSourceSet_test();
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
// xsysctl test suits.
//
const tTestCase * const psPatternXsysctl01[] =
{
    &sTestXSysctl002Register,
    0
};
