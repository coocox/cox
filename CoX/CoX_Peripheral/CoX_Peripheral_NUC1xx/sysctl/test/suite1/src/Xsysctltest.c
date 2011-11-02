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

//
// The value of clock which will be set in the test of "xSysCtlClockSet()"
//
unsigned long ulSYSCTL_CLKSET[] = {1,2,3,4,6,12,14,17,20,
    25,27,29,31,36,37,40,46,48,50};
//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* XSysctl001GetTest(void)
{
    return "xsysctl, 001, xsysctl register and test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl001Setup(void)
{
	SysCtlKeyAddrUnlock();
    //
    // Enable external 12 MHz high speed crystal
    //
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
    //
    // Enable external 32.768 kHz low speed crystal
    //
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL32K_EN;
    //
    // Enable internal 22.1184 MHz high speed oscillator
    //
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
    //
    // Enable internal 10 kHz low speed oscillator
    //
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC10K_EN;
    //
    // PLL FOUT enable
    //
	xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;
    //
    // PLL is in normal mode
    //
	xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl001TearDown(void)
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
//! \brief xsysctl 001 test of Peripheral Clock Source Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralClockSourceSet_test(void)
{
    unsigned long ulTemp;
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_WDG_S_EXT32K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_WDG_M)),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_WDG_S_EXT32K)\" error!");
    //
    // Set Watch Dog Clock HCLK/2048 Test
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_WDG_S_HCLK_2048);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_WDG_M)),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_WDG_S_HCLK_2048)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_WDG_S_INT10K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_WDG_M)),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_WDG_S_INT10K)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_ADC_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_ADC_M)>>SYSCLK_CLKSEL1_ADC_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_ADC_S_EXT12M)\" error!");
    //
    // Set ADC Clock select Test
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_ADC_S_PLL);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp &SYSCLK_CLKSEL1_ADC_M)>>SYSCLK_CLKSEL1_ADC_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_ADC_S_PLL)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_ADC_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp &0x00000008)>>SYSCLK_CLKSEL1_ADC_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_ADC_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR0_S_EXT12M)\" error!");
    //
    // Set Timer0 Clock 32.768KHz
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_EXT32K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR0_S_EXT32K)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_HCLK);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                            "(SYSCTL_PERIPH_TMR0_S_HCLK)\" error!");
   
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_EXTTRG);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_TMR0_M)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR0_S_EXTTRG)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & 0x00000400)>>SYSCLK_CLKSEL1_TMR0_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR0_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR1_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_EXT32K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR1_S_EXT32K)\" error!");

    //
    // Set Timer1 Clock HCLK
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_HCLK);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                            "(SYSCTL_PERIPH_TMR1_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_EXTTRG);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_TMR1_M)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR1_S_EXTTRG)\" error!");
   
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & 0x00004000)>>SYSCLK_CLKSEL1_TMR1_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR1_S_INT22M)\" error!");
 
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR2_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_EXT32K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR2_S_EXT32K)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_HCLK);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                            "(SYSCTL_PERIPH_TMR2_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_EXTTRG);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_TMR2_M)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR2_S_EXTTRG)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & 0x00040000)>>SYSCLK_CLKSEL1_TMR2_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR2_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR3_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_EXT32K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR3_S_EXT32K)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_HCLK);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                            "(SYSCTL_PERIPH_TMR3_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_EXTTRG);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_TMR3_M)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR3_S_EXTTRG)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((4 == (ulTemp & 0x00400000)>>SYSCLK_CLKSEL1_TMR3_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_TMR3_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_UART_M)>>SYSCLK_CLKSEL1_UART_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_UART_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_PLL);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_UART_M)>>SYSCLK_CLKSEL1_UART_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                             "(SYSCTL_PERIPH_UART_S_PLL)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & 0x02000000)>>SYSCLK_CLKSEL1_UART_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_UART_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_CAN_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_CAN_M)>>SYSCLK_CLKSEL1_CAN_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_CAN_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_CAN_S_PLL);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_CAN_M)>>SYSCLK_CLKSEL1_CAN_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_CAN_S_PLL)\" error!");
   
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_CAN_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & 0x08000000)>>SYSCLK_CLKSEL1_CAN_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_CAN_S_INT22M)\" error!");
 
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM01_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM01_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM01_S_EXT32K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM01_S_EXT32K)\" error!");
  
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM01_S_HCLK);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_PWM01_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM01_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_PWM01_M)>>SYSCLK_CLKSEL1_PWM01_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM01_S_INT22M)\" error!");
 
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM23_S_EXT12M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL1_PWM23_M)>>SYSCLK_CLKSEL1_PWM23_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM23_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM23_S_EXT32K);
    ulTemp = xHWREG(0x50000214);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL1_PWM23_M)>>SYSCLK_CLKSEL1_PWM23_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM23_S_EXT32K)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM23_S_HCLK);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL1_PWM23_M)>>SYSCLK_CLKSEL1_PWM23_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_PWM23_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM23_S_INT22M);
    ulTemp = xHWREG(0x50000214);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL1_PWM23_M)>>SYSCLK_CLKSEL1_PWM23_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM23_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_I2S_S_EXT12M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_I2S_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_I2S_S_PLL);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                              "(SYSCTL_PERIPH_I2S_S_PLL)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_I2S_S_HCLK);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                             "(SYSCTL_PERIPH_I2S_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_I2S_S_INT22M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL2_I2S_M)>>SYSCLK_CLKSEL2_I2S_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_I2S_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_FRQDIV_S_EXT12M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_FRQDIV_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_FRQDIV_S_EXT32K);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_FRQDIV_S_EXT32K)\" error!");
   
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_FRQDIV_S_HCLK);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                          "(SYSCTL_PERIPH_FRQDIV_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_FRQDIV_S_INT22M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL2_FRQDIV_M)>>SYSCLK_CLKSEL2_FRQDIV_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                        "(SYSCTL_PERIPH_FRQDIV_S_INT22M)\" error!");
 
    //
    // Set Peripheral Clock PWM45 is Extern12MHz
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM45_S_EXT12M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL2_PWM45_M)>>SYSCLK_CLKSEL2_PWM45_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM45_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM45_S_EXT32K);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL2_PWM45_M)>>SYSCLK_CLKSEL2_PWM45_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM45_S_EXT32K)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM45_S_HCLK);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL2_PWM45_M)>>SYSCLK_CLKSEL2_PWM45_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_PWM45_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM45_S_INT22M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL2_PWM45_M)>>SYSCLK_CLKSEL2_PWM45_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM45_S_INT22M)\" error!");

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM67_S_EXT12M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL2_PWM67_M)>>SYSCLK_CLKSEL2_PWM67_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM67_S_EXT12M)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM67_S_EXT32K);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL2_PWM67_M)>>SYSCLK_CLKSEL2_PWM67_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM67_S_EXT32K)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM67_S_HCLK);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL2_PWM67_M)>>SYSCLK_CLKSEL2_PWM67_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                           "(SYSCTL_PERIPH_PWM67_S_HCLK)\" error!");
    
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_PWM67_S_INT22M);
    ulTemp = xHWREG(0x5000021C);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL2_PWM67_M)>>SYSCLK_CLKSEL2_PWM67_S),
			                      "xsysctl API \"SysCtlPeripheralClockSourceSet"
			                         "(SYSCTL_PERIPH_PWM67_S_INT22M)\" error!");

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
    unsigned long ulTemp;
    //
    // Set HCLK Source of Extern 12 MHz test
    //
    SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT12M);
    ulTemp = xHWREG(0x50000210); 
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL0_HCLK_M)), 
		  "xsysctl API \"SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT12M)\" error!");
    
    SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT32K);
	TestAssert((1 == (xHWREG(0x50000210) & SYSCLK_CLKSEL0_HCLK_M)),
		  "xsysctl API \"SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT32K)\" error!");
    
    SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);
    ulTemp = xHWREG(0x50000210);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL0_HCLK_M)), 
			 "xsysctl API \"SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL)\" error!");
    
    SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT10K);
	TestAssert((3 == (xHWREG(0x50000210) & SYSCLK_CLKSEL0_HCLK_M)),
		  "xsysctl API \"SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT10K)\" error!");
    
    SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M);
    ulTemp = xHWREG(0x50000210);
	TestAssert((4 == (ulTemp & 4)), 
		  "xsysctl API \"SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M)\" error!");
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
    unsigned long ulTemp;
    SysCtlSysTickSourceSet(SYSCTL_STCLK_S_EXT12M);
    ulTemp = xHWREG(0x50000210); 
	TestAssert((0 == (ulTemp & SYSCLK_CLKSEL0_STCLK_M)>>SYSCLK_CLKSEL0_STCLK_S),
		"xsysctl API \"SysCtlSysTickSourceSet(SYSCTL_STCLK_S_EXT12M)\" error!");
    
    SysCtlSysTickSourceSet(SYSCTL_STCLK_S_EXT32K);
    ulTemp = xHWREG(0x50000210);
	TestAssert((1 == (ulTemp & SYSCLK_CLKSEL0_STCLK_M)>>SYSCLK_CLKSEL0_STCLK_S),
		"xsysctl API \"SysCtlSysTickSourceSet(SYSCTL_STCLK_S_EXT32K)\" error!");
    
    //
    // Select Ext12M/2 as the source of SysTick
    //
    SysCtlSysTickSourceSet(SYSCTL_STCLK_S_EXT12M_2);
    ulTemp = xHWREG(0x50000210);
	TestAssert((2 == (ulTemp & SYSCLK_CLKSEL0_STCLK_M)>>SYSCLK_CLKSEL0_STCLK_S),
	  "xsysctl API \"SysCtlSysTickSourceSet(SYSCTL_STCLK_S_EXT12M_2)\" error!");
    
    SysCtlSysTickSourceSet(SYSCTL_STCLK_S_HCLK_2);
    ulTemp = xHWREG(0x50000210);
	TestAssert((3 == (ulTemp & SYSCLK_CLKSEL0_STCLK_M)>>SYSCLK_CLKSEL0_STCLK_S),
		"xsysctl API \"SysCtlSysTickSourceSet(SYSCTL_STCLK_S_HCLK_2)\" error!");
    
    SysCtlSysTickSourceSet(SYSCTL_STCLK_S_INT22M_2);
    ulTemp = xHWREG(0x50000210);
	TestAssert((0 == (ulTemp & 0x4)>>SYSCLK_CLKSEL0_STCLK_S),
	  "xsysctl API \"SysCtlSysTickSourceSet(SYSCTL_STCLK_S_INT22M_2)\" error!");
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

    for(i = 1; i<=16; i++)
    {
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D|i);
        ulTemp = xHWREG(0x50000218);
        TestAssert(((i-1) == (ulTemp & SYSCLK_CLKDIV_HCLK_M)>>SYSCLK_CLKDIV_HCLK_S),
	    "xsysctl API \"SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D|i)\" error!"); 
    }
    
/*    for(i = 1; i<=16; i++)
    {
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_USB_D|i);
        ulTemp = xHWREG(0x50000218);
        TestAssert(((i-1) == (ulTemp & SYSCLK_CLKDIV_USB_M)>>SYSCLK_CLKDIV_USB_S),
	    "xsysctl API \"SysCtlIPClockDividerSet(SYSCTL_PERIPH_USB_D|i)\" error!"); 
    }
*/
    
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_USB_D|3);
    ulTemp = xHWREG(0x50000218);
	TestAssert((2 == (ulTemp & SYSCLK_CLKDIV_USB_M)>>SYSCLK_CLKDIV_USB_S),
		"xsysctl API \"SysCtlIPClockDividerSet(SYSCTL_PERIPH_USB_D|3)\" error!");
    
    for(i = 1; i<=16; i++)
    {
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|i);
        ulTemp = xHWREG(0x50000218);
        TestAssert(((i-1) == (ulTemp & SYSCLK_CLKDIV_UART_M)>>SYSCLK_CLKDIV_UART_S),
	    "xsysctl API \"SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|i)\" error!");
    } 
    
    for(i = 1; i<=256; i++)
    {
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_ADC_D|i);
        ulTemp = xHWREG(0x50000218);
        TestAssert(((i-1) == (ulTemp & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S),
	    "xsysctl API \"SysCtlIPClockDividerSet(SYSCTL_PERIPH_ADC_D|i)\" error!");
    }

    
    SysCtlFreqDividerOutputEnable(xtrue, 0x6);
    ulTemp = xHWREG(0x50000224);
	TestAssert((6 == (ulTemp & SYSCLK_FRQDIV_FSEL_M)>>SYSCLK_FRQDIV_FSEL_S),
			"xsysctl API \"SysCtlFreqDividerOutputEnable(xtrue, 0x6)\" error!");
	TestAssert((SYSCLK_FRQDIV_FDIV_EN == (ulTemp & SYSCLK_FRQDIV_FDIV_EN)),
			"xsysctl API \"SysCtlFreqDividerOutputEnable(xtrue, 0x6)\" error!");
     
    xSysCtlPeripheralClockSourceSet2(ADC0, INT, 3);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp &0x00000008)>>SYSCLK_CLKSEL1_ADC_S),
	   "xsysctl API \"xSysCtlPeripheralClockSourceSet2(ADC0, INT, 3)\" error!");
    ulTemp = xHWREG(0x50000218);
    TestAssert((2 == (ulTemp & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S),
	   "xsysctl API \"xSysCtlPeripheralClockSourceSet2(ADC0, INT, 3)\" error!");      

    xSysCtlPeripheralClockSourceSet2(ADC0, INT, 159);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp &0x00000008)>>SYSCLK_CLKSEL1_ADC_S),
	 "xsysctl API \"xSysCtlPeripheralClockSourceSet2(ADC0, INT, 159)\" error!");
    ulTemp = xHWREG(0x50000218);
    TestAssert((158 == (ulTemp & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S),
	 "xsysctl API \"xSysCtlPeripheralClockSourceSet2(ADC0, INT, 159)\" error!"); 
    
    xSysCtlPeripheralClockSourceSet2(ADC0, INT, 256);
    ulTemp = xHWREG(0x50000214);
	TestAssert((2 == (ulTemp &0x00000008)>>SYSCLK_CLKSEL1_ADC_S),
	 "xsysctl API \"xSysCtlPeripheralClockSourceSet2(ADC0, INT, 256)\" error!");
    ulTemp = xHWREG(0x50000218);
    TestAssert((255 == (ulTemp & SYSCLK_CLKDIV_ADC_M)>>SYSCLK_CLKDIV_ADC_S),
	 "xsysctl API \"xSysCtlPeripheralClockSourceSet2(ADC0, INT, 256)\" error!"); 
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
    unsigned long ulTemp,i;
    for(i=0;i<16;i++)
    {
		SysCtlHClockSet((i<<24)|SYSCTL_XTAL_12MHZ|
						SYSCTL_OSC_MAIN|SYSCTL_PLL_PWRDN|SYSCTL_INT_OSC_DIS);
		ulTemp = SysCtlHClockGet();
		TestAssert(ulTemp == 12000000/(i+1),
				                    "xsysctl API \"SysCtlHClockSet(xx)\" error!"
				                    "xsysctl API \"SysCtlHClockGet()\" error!");
    }
    
    for (i=0;i<16;i++)
    {
		SysCtlHClockSet((i<<24)|SYSCTL_XTAL_12MHZ|
				        SYSCTL_OSC_INT|SYSCTL_PLL_PWRDN);
		ulTemp = SysCtlHClockGet();
		TestAssert(ulTemp == 22000000/(i+1),
				                    "xsysctl API \"SysCtlHClockSet(xx)\" error!"
				                    "xsysctl API \"SysCtlHClockGet()\" error!");
    }

    for(i=0;i<16;i++)
    {
		SysCtlHClockSet((i<<24)|SYSCTL_XTAL_12MHZ|
				        SYSCTL_OSC_PLL|SYSCTL_PLL_MAIN);
		ulTemp = SysCtlHClockGet();
		TestAssert(ulTemp == 48000000/(i+1),
				                    "xsysctl API \"SysCtlHClockSet(xx)\" error!"
				                    "xsysctl API \"SysCtlHClockGet()\" error!");
    }

    for(i=0;i<16;i++)
    {
		SysCtlHClockSet((i<<24)|SYSCTL_XTAL_12MHZ|
				        SYSCTL_OSC_PLL|SYSCTL_PLL_INT);
		ulTemp = SysCtlHClockGet();
		TestAssert(ulTemp == 48000000/(i+1),
				                    "xsysctl API \"SysCtlHClockSet(xx)\" error!"
				                    "xsysctl API \"SysCtlHClockGet()\" error!");
    }

    //
    // Clock Set Test Source from Extern_12MHz
    //
   for(i=0;i<19;i++)
   {   
       unsigned long ulTempClk;
       ulTempClk = 1000000*ulSYSCTL_CLKSET[i];
	   xSysCtlClockSet(ulTempClk, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
	   ulTemp = xSysCtlClockGet();
	   TestAssert(ulTemp == ulTempClk,"xsysctl API \"xSysCtlClockSet(xx)\" error!");
    }

    //
    // Clock Set Test Source from Inter_10KHz
    //
	xSysCtlClockSet(10000, xSYSCTL_OSC_INTSL|xSYSCTL_INTSL_10KHZ);
	ulTemp = xSysCtlClockGet();
	TestAssert(ulTemp == 10000, "xsysctl API \"XSysCtlClockSet(xx)\" error!");
    //
    // Clock Set Test Source from Inter_22MHz
    //
	xSysCtlClockSet(22000000, xSYSCTL_OSC_INT|xSYSCTL_INT_22MHZ);
	ulTemp = xSysCtlClockGet();
	TestAssert(ulTemp == 22000000,"xsysctl API \"XSysCtlClockSet(xx)\" error!");
    //
    // Clock Set Test Source from Inter_32KHz
    //
	xSysCtlClockSet(32768, xSYSCTL_OSC_EXTSL|xSYSCTL_XTALSL_32768HZ);
	ulTemp = SysCtlHClockGet();
	TestAssert(ulTemp == 32000, "xsysctl API \"xSysCtlClockSet(xx)\" error!");

}

//*****************************************************************************
//
//! \brief xsysctl 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl001Execute(void)
{
	xsysctl_SysCtlPeripheralClockSourceSet_test();
	xsysctl_SysCtlHClockSourceSet_test();
    xsysctl_SysCtlSysTickSourceSet_test();
    xsysctl_Divider_test();
    xsysctl_SetHCLK_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl001Register = {
		XSysctl001GetTest,
		XSysctl001Setup,
		XSysctl001TearDown,
		XSysctl001Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl[] =
{
    &sTestXSysctl001Register,
    0
};
