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
unsigned long ulSysTickClkSource[] = {SYSCTL_STCLK_S_EXT12M, SYSCTL_STCLK_S_EXT32K,
SYSCTL_STCLK_S_EXT12M_2, SYSCTL_STCLK_S_HCLK_2};


unsigned long ulWDT0ClkSource[] = {SYSCTL_PERIPH_WDG_S_EXT32K, 
SYSCTL_PERIPH_WDG_S_HCLK_2048, SYSCTL_PERIPH_WDG_S_INT10K};


unsigned long ulADC0ClkSource[] = {SYSCTL_PERIPH_ADC_S_EXT12M, 
SYSCTL_PERIPH_ADC_S_PLL};


unsigned long ulUARTClkSource[] = {SYSCTL_PERIPH_UART_S_EXT12M, 
SYSCTL_PERIPH_UART_S_PLL};

unsigned long ulFRQDIVClkSource[] = {
SYSCTL_PERIPH_FRQDIV_S_EXT12M, SYSCTL_PERIPH_FRQDIV_S_EXT32K,
SYSCTL_PERIPH_FRQDIV_S_HCLK, SYSCTL_PERIPH_FRQDIV_S_INT22M};


unsigned long ulI2SClkSource[] = {SYSCTL_PERIPH_I2S_S_EXT12M, 
SYSCTL_PERIPH_I2S_S_PLL, SYSCTL_PERIPH_I2S_S_HCLK, SYSCTL_PERIPH_I2S_S_INT22M};


unsigned long ulTIMER0ClkSource[] = {SYSCTL_PERIPH_TMR0_S_EXT12M,
SYSCTL_PERIPH_TMR0_S_EXT32K , SYSCTL_PERIPH_TMR0_S_HCLK, SYSCTL_PERIPH_TMR0_S_EXTTRG,
SYSCTL_PERIPH_TMR0_S_INT22M};


unsigned long ulTIMER1ClkSource[] = {SYSCTL_PERIPH_TMR0_S_EXT12M,
SYSCTL_PERIPH_TMR0_S_EXT32K , SYSCTL_PERIPH_TMR0_S_HCLK, SYSCTL_PERIPH_TMR0_S_EXTTRG,
SYSCTL_PERIPH_TMR0_S_INT22M};


unsigned long ulTIMER2ClkSource[] = {SYSCTL_PERIPH_TMR0_S_EXT12M,
SYSCTL_PERIPH_TMR0_S_EXT32K ,SYSCTL_PERIPH_TMR0_S_HCLK, SYSCTL_PERIPH_TMR0_S_EXTTRG,
SYSCTL_PERIPH_TMR0_S_INT22M};


unsigned long ulTIMER3ClkSource[] = {SYSCTL_PERIPH_TMR0_S_EXT12M,
SYSCTL_PERIPH_TMR0_S_EXT32K , SYSCTL_PERIPH_TMR0_S_HCLK, SYSCTL_PERIPH_TMR0_S_EXTTRG,
SYSCTL_PERIPH_TMR0_S_INT22M};

unsigned long ulPWM01ClkSource[] = {SYSCTL_PERIPH_PWM01_S_EXT12M,
SYSCTL_PERIPH_PWM01_S_EXT32K , SYSCTL_PERIPH_PWM01_S_HCLK, SYSCTL_PERIPH_PWM01_S_INT22M};


unsigned long ulPWM23ClkSource[] = {SYSCTL_PERIPH_PWM23_S_EXT12M,
SYSCTL_PERIPH_PWM23_S_EXT32K , SYSCTL_PERIPH_PWM23_S_HCLK, SYSCTL_PERIPH_PWM23_S_INT22M};


unsigned long ulPWM45ClkSource[] = {SYSCTL_PERIPH_PWM45_S_EXT12M,
SYSCTL_PERIPH_PWM45_S_EXT32K , SYSCTL_PERIPH_PWM45_S_HCLK, SYSCTL_PERIPH_PWM45_S_INT22M};


unsigned long ulPWM67ClkSource[] = {SYSCTL_PERIPH_PWM67_S_EXT12M,
SYSCTL_PERIPH_PWM67_S_EXT32K , SYSCTL_PERIPH_PWM67_S_HCLK, SYSCTL_PERIPH_PWM67_S_INT22M};


unsigned long ulHCLKSource[] = {SYSCTL_HLCK_S_EXT12M, SYSCTL_HLCK_S_EXT32K,
SYSCTL_HLCK_S_PLL, SYSCTL_HLCK_S_INT10K};

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
//! \brief something should do after the test execute of xsysctl004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl004TearDown(void)
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
//! \brief xsysctl 001 test of SysTick Source Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlSysTickSourceSet_test(void)
{
    unsigned long ulTemp,i;
    
    for(i = 0; i < 4; i++)
    {
        SysCtlSysTickSourceSet(ulSysTickClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL0);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL0_STCLK_M)>>SYSCLK_CLKSEL0_STCLK_S),
                             "xsysctl API \"SysCtlSysTickSourceSet()\" error!");
    }
    
    SysCtlSysTickSourceSet(SYSCTL_STCLK_S_INT22M_2);
    ulTemp = xHWREG(SYSCLK_CLKSEL0);
    TestAssert((0 == (ulTemp & 0x4)>>SYSCLK_CLKSEL0_STCLK_S),
                             "xsysctl API \"SysCtlSysTickSourceSet()\" error!");
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
    
    for(i = 0; i < 3; i++)
    {
        SysCtlPeripheralClockSourceSet(ulWDT0ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert(((i+1) == (ulTemp & SYSCLK_CLKSEL1_WDG_M)),"xsysctl API error!");
    }

    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralClockSourceSet(ulADC0ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_ADC_M)>>SYSCLK_CLKSEL1_ADC_S),
                                                          "xsysctl API error!");
    }
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_ADC_S_INT22M);
    ulTemp = xHWREG(SYSCLK_CLKSEL1);
    TestAssert((2 == (ulTemp &0x00000008)>>SYSCLK_CLKSEL1_ADC_S),
                                                          "xsysctl API error!");

    for(i = 0; i < 5; i++)
    {
        SysCtlPeripheralClockSourceSet(ulTIMER0ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
                                                          "xsysctl API error!");
    }
    
    for(i = 0; i < 5; i++)
    {
        SysCtlPeripheralClockSourceSet(ulTIMER1ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
                                                          "xsysctl API error!");
    }

    for(i = 0; i < 5; i++)
    {
        SysCtlPeripheralClockSourceSet(ulTIMER2ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
                                                          "xsysctl API error!");
    }
    
    for(i = 0; i < 5; i++)
    {
        SysCtlPeripheralClockSourceSet(ulTIMER3ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
                                                          "xsysctl API error!");
    }

    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralClockSourceSet(ulUARTClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_UART_M)>>SYSCLK_CLKSEL1_UART_S),
                                                          "xsysctl API error!");
    }
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_INT22M);
    ulTemp = xHWREG(SYSCLK_CLKSEL1);
    TestAssert((2 == (ulTemp & 0x02000000)>>SYSCLK_CLKSEL1_UART_S),
                                                          "xsysctl API error!");

    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulI2SClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL2);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
                                                          "xsysctl API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulFRQDIVClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL2);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
                                                          "xsysctl API error!");
    }

    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulPWM01ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
                                                          "xsysctl API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulPWM23ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL1);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL1_PWM23_M)>>SYSCLK_CLKSEL1_PWM23_S),
                                                          "xsysctl API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulPWM45ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL2);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL2_PWM45_M)>>SYSCLK_CLKSEL2_PWM45_S),
                                                          "xsysctl API error!");
    } 

    for(i = 0; i < 4; i++)
    {
        SysCtlPeripheralClockSourceSet(ulPWM67ClkSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL2);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL2_PWM67_M)>>SYSCLK_CLKSEL2_PWM67_S),
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
    
    for(i = 0; i < 4; i++)
    {
        SysCtlHClockSourceSet(ulHCLKSource[i]);
        ulTemp = xHWREG(SYSCLK_CLKSEL0);
        TestAssert((i == (ulTemp & SYSCLK_CLKSEL0_HCLK_M)),"xsysctl API error!");
    }
    
    SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M);
    ulTemp = xHWREG(SYSCLK_CLKSEL0);
    TestAssert((4 == (ulTemp & 4)), "xsysctl API error!");
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
    xsysctl_SysCtlSysTickSourceSet_test();
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
