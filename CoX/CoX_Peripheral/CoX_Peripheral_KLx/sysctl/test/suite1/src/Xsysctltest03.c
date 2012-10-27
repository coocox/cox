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
//****************************************************************************


unsigned long ulWDT0ClkSource[] = {SYSCTL_PERIPH_WDG_S_1K, SYSCTL_PERIPH_WDG_S_BUS};


unsigned long ulADC0ClkSource[] = {SYSCTL_PERIPH_ADC_S_BUSCLK, 
SYSCTL_PERIPH_ADC_S_BUSCLK_2, SYSCTL_PERIPH_ADC_S_ATCLK, SYSCTL_PERIPH_ADC_S_ADACK};



unsigned long ulUARTClkSource[] = {
SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2, SYSCTL_PERIPH_UART0_S_OSCERCLK,
SYSCTL_PERIPH_UART0_S_MCGIRCLK};


unsigned long ulTIMER0ClkSource[] = {SYSCTL_PERIPH_TPM_S_MCGPLLCLK_2, 
 SYSCTL_PERIPH_TPM_S_OSCERCLK, SYSCTL_PERIPH_TPM_S_MCGIRCLK};


unsigned long ulRTCClkSource[] = {SYSCTL_PERIPH_RTC_S_OSC32KCLK, 0,
SYSCTL_PERIPH_RTC_S_RTC_CLKIN , SYSCTL_PERIPH_RTC_S_LPO};


unsigned long ulUSBClkSource[] = {SYSCTL_PERIPH_USB_S_USB_CLKIN,
SYSCTL_PERIPH_USB_S_MCGPLLCLK_2 };


unsigned long ulOutputClkSource[] = {SYSCTL_OUTPUT_CLKSRC_BUS,
SYSCTL_OUTPUT_CLKSRC_LPO , SYSCTL_OUTPUT_CLKSRC_MCGIRCLK, 0,
SYSCTL_OUTPUT_CLKSRC_OSCERCLK};
/*
unsigned long ulPWMAClkSource[] = {SYSCTL_PERIPH_PWM01_S_EXT12M,
SYSCTL_PERIPH_PWM01_S_EXT32K , SYSCTL_PERIPH_PWM01_S_HCLK, SYSCTL_PERIPH_PWM01_S_INT22M};


unsigned long ulPWMBClkSource[] = {SYSCTL_PERIPH_PWM23_S_EXT12M,
SYSCTL_PERIPH_PWM23_S_EXT32K , SYSCTL_PERIPH_PWM23_S_HCLK, SYSCTL_PERIPH_PWM23_S_INT22M};


unsigned long ulPWMCClkSource[] = {SYSCTL_PERIPH_PWM45_S_EXT12M,
SYSCTL_PERIPH_PWM45_S_EXT32K , SYSCTL_PERIPH_PWM45_S_HCLK, SYSCTL_PERIPH_PWM45_S_INT22M};
*/
unsigned long ulHCLKSource[] = {SYSCTL_HLCK_S_PLL, SYSCTL_HLCK_S_INT, SYSCTL_HLCK_S_MAIN};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl004GetTest(void)
{
    return "xsysctl, 004, xsysctl register and api test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl004Setup(void)
{
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl004TearDown(void)
{   

}

//*****************************************************************************
//
//! \brief xsysctl 004 test of Peripheral Clock Source Set test .
//!
//! \return None.
//
//*****************************************************************************

static void xsysctl_SysCtlPeripheralClockSourceSet_test(void)
{
    unsigned long i,ulTemp;
    
/*
    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralClockSourceSet(ulWDT0ClkSource[i]);
        ulTemp = (xHWREG(SIM_COPC) & SIM_COPC_COPCLKS)>>1;
        TestAssert((i == ulTemp), "xsysctl API error!");
    }
*/   
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulADC0ClkSource[i]);
        ulTemp = xHWREG(ADC_BASE + ADC0_CFG1);
        TestAssert((i == ((ulTemp & ADC0_CFG1_ADICLK_M)>>ADC0_CFG1_ADICLK_S)),
                                                          "xsysctl API error!");
    }

    for(i = 0; i < 3; i++)
    {
        SysCtlPeripheralClockSourceSet(ulTIMER0ClkSource[i]);
        ulTemp = xHWREG(SIM_SOPT2);
        TestAssert(((i+1) == (ulTemp & SIM_SOPT2_TPMSRC_M)>>SIM_SOPT2_TPMSRC_S),
                                                          "xsysctl API error!");
    }
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TPM_S_MCGFLLCLK);
    ulTemp = xHWREG(SIM_SOPT2);
    TestAssert((1 == (ulTemp & SIM_SOPT2_TPMSRC_M)>>SIM_SOPT2_TPMSRC_S),
                                                          "xsysctl API error!");

    for(i = 0; i < 3; i++)
    {
        SysCtlPeripheralClockSourceSet(ulUARTClkSource[i]);
        ulTemp = xHWREG(SIM_SOPT2);
        TestAssert(((i+1) == (ulTemp & SIM_SOPT2_UART0SRC_M)>>SIM_SOPT2_UART0SRC_S),
                                                          "xsysctl API error!");
    }
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART0_S_MCGFLLCLK);
    ulTemp = xHWREG(SIM_SOPT2);
    TestAssert((1 == (ulTemp & SIM_SOPT2_UART0SRC_M)>>SIM_SOPT2_UART0SRC_S),
                                                          "xsysctl API error!");
    for(i = 0; i < 4; i++)
    {
        if(i==1)
        {
            continue;
        }
        SysCtlPeripheralClockSourceSet(ulRTCClkSource[i]);
        ulTemp = xHWREG(SIM_SOPT1);
        TestAssert((i == (ulTemp & SIM_SOPT1_OSC32KSEL_M)>>SIM_SOPT1_OSC32KSEL_S),
                                                          "xsysctl API error!");
    }

    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralClockSourceSet(ulUSBClkSource[i]);
        ulTemp = xHWREG(SIM_SOPT2);
        TestAssert((i == (ulTemp & SIM_SOPT2_USBSRC)>>18), "xsysctl API error!");
    }
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_USB_S_MCGFLLCLK);
    ulTemp = xHWREG(SIM_SOPT2);
    TestAssert((1 == (ulTemp & SIM_SOPT2_USBSRC)>>18), "xsysctl API error!");
    
    for(i = 0; i < 5; i++)
    {
        if(i==3)
        {
            continue;
        }
        SysCtlClkOututSrcSet(ulOutputClkSource[i]);
        ulTemp = xHWREG(SIM_SOPT2);
        TestAssert(((i+2) == (ulTemp & SIM_SOPT2_CLKOUTSEL_M)>>SIM_SOPT2_CLKOUTSEL_S),
                                                          "xsysctl API error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of HCLK Source Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlHClockSourceSet_test(void)
{
    unsigned long ulTemp,i;
/*    
    for(i = 0; i < 3; i++)
    {
        SysCtlHClockSourceSet(ulHCLKSource[i]);
        ulTemp = xHWREGB(MCG_C1);
        TestAssert((i == ((ulTemp & MCG_C1_SRC_MCGOUTCLK_M)>>MCG_C1_SRC_MCGOUTCLK_S)),
                                                          "xsysctl API error!");
    }
*/
}
//*****************************************************************************
//
//! \brief xsysctl 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl004Execute(void)
{
    xsysctl_SysCtlPeripheralClockSourceSet_test();
    xsysctl_SysCtlHClockSourceSet_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl004Register = {
		xSysctl004GetTest,
		xSysctl004Setup,
		xSysctl004TearDown,
		xSysctl004Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl03[] =
{
    &sTestXSysctl004Register,
    0
};
