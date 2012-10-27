//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: FREEDOM-KL25Z <br><br>
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
#include "xhw_adc.h"
//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************

//unsigned long ulxWDT0ClkSource[] = {xSYSCTL_WDT0_INTSL, xSYSCTL_WDT0_HCLK_2};


unsigned long ulxADC0ClkSource[] = {xSYSCTL_ADC0_MAIN};

unsigned long ulxPWMAClkSource[] = {xSYSCTL_PWMA_HCLK, xSYSCTL_PWMA_MAIN,
                                    xSYSCTL_PWMA_INT};
unsigned long ulxTIMER0ClkSource[] = {xSYSCTL_TIMER0_HCLK, xSYSCTL_TIMER0_MAIN,
                                      xSYSCTL_TIMER0_INT};

unsigned long ulxUART0ClkSource[] = {xSYSCTL_UART0_PLL, xSYSCTL_UART0_MAIN,
                                     xSYSCTL_UART0_INT};
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
//! \brief xsysctl 001 test of set and get HCLK test .
//!
//! \return None.
//
//*****************************************************************************

static void xsysctl_SetHCLK_test(void)
{
	unsigned long ulTemp;

    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 48000000), "xsysctl API error!");

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

    xSysCtlClockSet(2000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 2000000), "xsysctl API error!");
/*
    xSysCtlClockSet(32768, xSYSCTL_OSC_INTSL);
    ulTemp = xSysCtlClockGet();
    TestAssert((ulTemp == 32768), "xsysctl API error!");
*/
}

//*****************************************************************************
//
//! \brief xsysctl 004 test of Set a peripheral clock source and peripheral 
//! divide test .
//!
//! \return None.
//
//*****************************************************************************


static void xsysctl_xSysCtlPeripheralClockSourceSet_test(void)
{
    unsigned long ulTemp,i,ulTempValue,j;
/*
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxWDT0ClkSource[i], 1);
        ulTemp = (xHWREG(SIM_COPC) & SIM_COPC_COPCLKS)>>1;
        TestAssert((i == ulTemp), "xsysctl API error!");
    }
*/   
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
    for(i = 0; i < 1; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxADC0ClkSource[i], 1);
        ulTemp = xHWREG(ADC_BASE + ADC0_CFG1);
        TestAssert((i == (ulTemp & ADC0_CFG1_ADICLK_M)>>ADC0_CFG1_ADICLK_S),
                                                          "xsysctl API error!");
    }

    for(i = 0; i < 3; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxTIMER0ClkSource[i], 1);
        ulTemp = xHWREG(SIM_SOPT2);
        TestAssert(((i+1) == (ulTemp & SIM_SOPT2_TPMSRC_M)>>SIM_SOPT2_TPMSRC_S),
                                                          "xsysctl API error!");
    }
    
    for(i = 0; i < 3; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxPWMAClkSource[i], 1);
        ulTemp = xHWREG(SIM_SOPT2);
        TestAssert(((i+1) == (ulTemp & SIM_SOPT2_TPMSRC_M)>>SIM_SOPT2_TPMSRC_S),
                                                          "xsysctl API error!");
    }
    
    for(i = 0; i < 3; i++)
    {
        xSysCtlPeripheralClockSourceSet(ulxUART0ClkSource[i], 1);
        ulTemp = xHWREG(SIM_SOPT2);
        TestAssert(((i+1) == (ulTemp & SIM_SOPT2_UART0SRC_M)>>SIM_SOPT2_UART0SRC_S),
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

    xsysctl_SetHCLK_test();
    xsysctl_xSysCtlPeripheralClockSourceSet_test();
   
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
const tTestCase * const psPatternXsysctl01[] =
{
    &sTestXSysctl002Register,
    0
};