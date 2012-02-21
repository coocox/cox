//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: M051 <br><br>
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

//
// The value of clock which will be set in the test of "xSysCtlClockSet()"
//
unsigned long ulSYSCTL_CLKSET[] = {1,2,3,4,6,12};


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl001GetTest(void)
{
    return "xsysctl, 001, xsysctl Clock set and get test";
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
    SysCtlKeyAddrUnlock();
    
    //
    // Enable external 12 MHz high speed crystal
    //
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
    
    //
    // Enable internal 22.1184 MHz high speed oscillator
    //
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
    
    //
    // Enable internal 10 kHz low speed oscillator
    //
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC10K_EN;
    
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
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN|SYSCTL_INT_OSC_DIS;
    SysCtlHClockSet(ulTemp);

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|1);
}


//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral Divider test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_Divider_test(void)
{
    unsigned long ulTemp,i;

    SysCtlIPClockDividerSet(SYSCTL_PERIPH_ADC_D | 3);
    ulTemp = xHWREG(SYSCLK_CLKDIV);
    TestAssert((2 == ((ulTemp & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S)),
                                                         "xsysctl API error!");
    
    for(i = 1; i<=16; i++)
    {
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D | i);
        ulTemp = xHWREG(SYSCLK_CLKDIV);
        TestAssert(((i-1) == (ulTemp & SYSCLK_CLKDIV_HCLK_M)>>SYSCLK_CLKDIV_HCLK_S),
                                                          "xsysctl API error!"); 
    }
 /*    
    for(i = 1; i<=16; i++)
    {
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|i);
        ulTemp = xHWREG(SYSCLK_CLKDIV);
        TestAssert(((i-1) == (ulTemp & SYSCLK_CLKDIV_UART_M)>>SYSCLK_CLKDIV_UART_S),
                                                          "xsysctl API error!");
    }  
    */
 
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of set and get HCLK test.
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SetHCLK_test(void)
{
    unsigned long ulTemp,i;
    for(i=0;i<16;i++)
    {
        SysCtlHClockSet(SYSCTL_XTAL_12MHZ|
                           SYSCTL_OSC_MAIN|SYSCTL_INT_OSC_DIS);
        ulTemp = SysCtlHClockGet();
        TestAssert(ulTemp == 12000000, "xsysctl API error!");
    }
    
    for (i=0;i<16;i++)
    {
        SysCtlHClockSet(SYSCTL_OSC_INT);
        ulTemp = SysCtlHClockGet();
        TestAssert(ulTemp == 22000000, "xsysctl API error!");
    }

    //
    // Clock Set Test Source from Extern_12MHz
    //
    for(i=0;i<6;i++)
    {   
        unsigned long ulTempClk;
        ulTempClk = 1000000*ulSYSCTL_CLKSET[i];
        xSysCtlClockSet(ulTempClk, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
        ulTemp = xSysCtlClockGet();
        TestAssert(ulTemp == ulTempClk,"xsysctl API error!");
    }

    //
    // Clock Set Test Source from Inter_10KHz
    //

    xSysCtlClockSet(10000, xSYSCTL_OSC_INTSL);
    ulTemp = xSysCtlClockGet();
    TestAssert(ulTemp == 10000, "xsysctl API error!");
   
    
    //
    // Clock Set Test Source from Inter_22MHz
    //
    xSysCtlClockSet(22000000, xSYSCTL_OSC_INT);
    ulTemp = xSysCtlClockGet();
    TestAssert(ulTemp == 22000000,"xsysctl API error!");
 
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
  
    xsysctl_Divider_test();
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
