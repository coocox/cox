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


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* XSysctl004GetTest(void)
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
static void XSysctl004Setup(void)
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
static void XSysctl004TearDown(void)
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
//! \brief xsysctl 004 test of Set a peripheral clock source and peripheral 
//£¡ divide test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralClockSourceSet_test(void)
{
    unsigned long ulTemp,i,ulTempValue;

    xSysCtlPeripheralClockSourceSet(xSYSCTL_WDT0_EXTSL, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_WDG_M)),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_WDG_S_EXT32K)\" error!");

    //
    // Set Watch Dog Clock HCLK/2048 Test
    //

     xSysCtlPeripheralClockSourceSet(xSYSCTL_WDT0_HCLK_2048, 1);
     ulTemp = xHWREG(0x50000214);
	 TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_WDG_M)),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_WDG_S_HCLK_2048)\" error!");
    
     xSysCtlPeripheralClockSourceSet(xSYSCTL_WDT0_INTSL, 1);
     ulTemp = xHWREG(0x50000214);
	 TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_WDG_M)),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_WDG_S_INT10K)\" error!");

    for(i=1; i <= 256;i++)
    {
        xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, i);
        ulTemp = xHWREG(0x50000214);
	    TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_ADC_M)>>SYSCLK_CLKSEL1_ADC_S),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_ADC_S_EXT12M)\" error!");

        ulTempValue = xHWREG(0x50000218);
	    TestAssert(((i-1) == (ulTempValue & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S),
		"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, i)\" error!");
    }
    //
    // Set ADC Clock select Test
    //
    for(i = 1; i <= 256; i++)
    {
        xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_PLL, i);
        ulTemp = xHWREG(0x50000214);
	    TestAssert((1 == (ulTemp &SYSCLK_CLKSEL1_ADC_M)>>SYSCLK_CLKSEL1_ADC_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
        ulTempValue = xHWREG(0x50000218);
	    TestAssert(((i-1) == (ulTempValue & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S),
		"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, i)\" error!");
    }
    for(i = 1; i <= 256; i++)
    {
        xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_INT, i);
        ulTemp = xHWREG(0x50000214);
	    TestAssert((2 == (ulTemp &0x00000008)>>SYSCLK_CLKSEL1_ADC_S),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                                     "(xSYSCTL_ADC0_INT)\" error!");
        
        ulTempValue = xHWREG(0x50000218);
	    TestAssert(((i-1) == (ulTempValue & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S),
		"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, i)\" error!");
    }

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER0_MAIN , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER0_EXTSL , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER0_HCLK , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
    

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER0_EXTTRG , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");


    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER0_INT , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");


    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER1_MAIN , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER1_EXTSL , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 ==(ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER1_HCLK , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 ==(ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");


    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER1_EXTTRG , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 ==(ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER1_INT , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & 0x00000400)>>SYSCLK_CLKSEL1_TMR0_S),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                                   "(xSYSCTL_TIMER1_INT)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER2_MAIN , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 ==(ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
     
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER2_EXTSL , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 ==(ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
   
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER2_HCLK , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 ==(ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER2_EXTTRG , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 ==(ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER2_INT , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & 0x00000400)>>SYSCLK_CLKSEL1_TMR0_S),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                                   "(xSYSCTL_TIMER2_INT)\" error!");

/*    for(i = 1; i <= 16; i++)
    {
        xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, i);
        ulTemp = xHWREG(0x50000214);
	    TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_UART_M)>>SYSCLK_CLKSEL1_UART_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
        
        ulTempValue = xHWREG(0x50000218);
	    TestAssert(((i-1) == (ulTempValue & SYSCLK_CLKDIV_UART_M)>>SYSCLK_CLKDIV_UART_S),
		"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, i)\" error!");
    }

    for(i = 1; i <= 16; i++)
    {
        xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_PLL, i);
        ulTemp = xHWREG(0x50000214);
	    TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_UART_M)>>SYSCLK_CLKSEL1_UART_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
        
        ulTempValue = xHWREG(0x50000218);
	    TestAssert(((i-1) == (ulTempValue & SYSCLK_CLKDIV_UART_M)>>SYSCLK_CLKDIV_UART_S),
		"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_PLL, i)\" error!");
    }
    for(i = 1; i <= 16; i++)
    {
        xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_INT, i);
        ulTemp = xHWREG(0x50000214);
	    TestAssert((2 == (ulTemp & 0x02000000)>>SYSCLK_CLKSEL1_UART_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
        
        ulTempValue = xHWREG(0x50000218);
	    TestAssert(((i-1) == (ulTempValue & SYSCLK_CLKDIV_UART_M)>>SYSCLK_CLKDIV_UART_S),
		"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_INT, i)\" error!");
    }
*/    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER3_MAIN, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR3_S_EXT12M)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER3_EXTSL, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR3_S_EXT32K)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER3_HCLK, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                            "(SYSCTL_PERIPH_TMR3_S_HCLK)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER3_EXTTRG, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR3_S_EXTTRG)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER3_INT , 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & 0x00000400)>>SYSCLK_CLKSEL1_TMR0_S),
			                     "xsysctl API \"xSysCtlPeripheralClockSourceSet"
			                                   "(xSYSCTL_TIMER3_INT)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_I2S0_MAIN, xSYSCTL_I2S0_MAIN);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_I2S_S_EXT12M)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_I2S0_PLL, 1);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_I2S_S_PLL)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_I2S0_HCLK, 1);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                             "(SYSCTL_PERIPH_I2S_S_HCLK)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_I2S0_INT, 1);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_I2S_S_INT22M)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_FRQDIV_MAIN, 1);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_FRQDIV_S_EXT12M)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_FRQDIV_EXTSL, 1);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_FRQDIV_S_EXT32K)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_FRQDIV_HCLK, 1);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_FRQDIV_S_HCLK)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_FRQDIV_INT, 1);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_FRQDIV_S_INT22M)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_MAIN, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
	"xsysctl API \"xSysCtlPeripheralClockSourceSet""(xSYSCTL_PWMA_MAIN, 1)\" error!");
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_EXTSL, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
	"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_EXTSL, 1)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_HCLK, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
	"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_HCLK, 1)\" error!");

    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_INT, 1);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
	"xsysctl API \"xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_INT, 1)\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of Brown-Out Detector Control Register test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_Bod_test(void)
{
	xtBoolean xtTemp;
    unsigned long ulTemp; 
    SysCtlBODEnable(xtrue);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_BOD_EN == (ulTemp & GCR_BODCR_BOD_EN)),
			                   "xsysctl API \"SysCtlBODEnable(xtrue)\" error!");
    
    SysCtlBODEnable(xfalse);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_BOD_EN == (ulTemp & GCR_BODCR_BOD_EN)),
			                  "xsysctl API \"SysCtlBODEnable(xfalse)\" error!");
    //
    // Set Threshold Voltage as 2.2V test
    //
    SysCtlBODVoltSelect(SYSCTL_BOD_2_2);
    ulTemp = xHWREG(0x50000018);
	TestAssert((0 == (ulTemp & GCR_BODCR_BOD_VL_M)>>GCR_BODCR_BOD_VL_S),
			      "xsysctl API \"SysCtlBODVoltSelect(SYSCTL_BOD_2_2)\" error!");
    
    SysCtlBODVoltSelect(SYSCTL_BOD_2_6);
    ulTemp = xHWREG(0x50000018);
	TestAssert((1 == (ulTemp & GCR_BODCR_BOD_VL_M)>>GCR_BODCR_BOD_VL_S),
			      "xsysctl API \"SysCtlBODVoltSelect(SYSCTL_BOD_2_6)\" error!");
    
    SysCtlBODVoltSelect(SYSCTL_BOD_3_8);
    ulTemp = xHWREG(0x50000018);
	TestAssert((2 == (ulTemp & GCR_BODCR_BOD_VL_M)>>GCR_BODCR_BOD_VL_S),
			      "xsysctl API \"SysCtlBODVoltSelect(SYSCTL_BOD_3_8)\" error!");
    //
    // Set Threshold Voltage as 4.5V test
    //
    SysCtlBODVoltSelect(SYSCTL_BOD_4_5);
    ulTemp = xHWREG(0x50000018);
	TestAssert((3 == (ulTemp & GCR_BODCR_BOD_VL_M)>>GCR_BODCR_BOD_VL_S),
			      "xsysctl API \"SysCtlBODVoltSelect(SYSCTL_BOD_4_5)\" error!");
    
    SysCtlBODLowPowerModeEnable(xtrue);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_BOD_LPM == (ulTemp & GCR_BODCR_BOD_LPM)),
			       "xsysctl API \"SysCtlBODLowPowerModeEnable(xtrue)\" error!");
    
    SysCtlBODLowPowerModeEnable(xfalse);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_BOD_LPM == (ulTemp & GCR_BODCR_BOD_LPM)),
			       "xsysctl API \"SysCtlBODLowPowerModeEnable(xtrue)\" error!");
    
    SysCtlLowVoltRstEnable(xtrue);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_LVR_EN == (ulTemp & GCR_BODCR_LVR_EN)),
			           "xsysctl API \"SysCtlLowVoltRstEnable(xtrue))\" error!");
    
    SysCtlLowVoltRstEnable(xfalse);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_LVR_EN == (ulTemp & GCR_BODCR_LVR_EN)),
			           "xsysctl API \"SysCtlLowVoltRstEnable(xtrue))\" error!");
    
    SysCtlTempatureSensorEnable(xfalse);
    ulTemp = xHWREG(0x50000018);
	TestAssert((0 == (ulTemp & GCR_TEMPCR_VTEMP_EN)),
			       "xsysctl API \"SysCtlTempatureSensorEnable(xtrue)\" error!");
    
	xtTemp = SysCtlBODStateGet();
	TestAssert((xtTemp==0 ),"xsysctl API \"SysCtlBODStateGet()\" error!");
    
    SysCtlBODRstEnable(xtrue);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_BOD_RSTEN == (ulTemp & GCR_BODCR_BOD_RSTEN)),
			                "xsysctl API \"SysCtlBODRstEnable(xtrue)\" error!");
    
    SysCtlBODRstEnable(xfalse);
    ulTemp = xHWREG(0x50000018);
	TestAssert((GCR_BODCR_BOD_RSTEN == (ulTemp & GCR_BODCR_BOD_RSTEN)),
			                "xsysctl API \"SysCtlBODRstEnable(xtrue)\" error!");
    //
    //Set RC adjustment value 
    //
    SysCtlRCAdjValueSet(0x34);
	TestAssert((0x34 == (xHWREG(0x50000110) & GCR_RCADJ_RCADJ_M)),
			                "xsysctl API \"SysCtlRCAdjValueSet(0x34)\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl004Execute(void)
{
    xsysctl_Bod_test();
    xsysctl_xSysCtlPeripheralClockSourceSet_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl004Register = {
		XSysctl004GetTest,
		XSysctl004Setup,
		XSysctl004TearDown,
		XSysctl004Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl03[] =
{
    &sTestXSysctl004Register,
    0
};
