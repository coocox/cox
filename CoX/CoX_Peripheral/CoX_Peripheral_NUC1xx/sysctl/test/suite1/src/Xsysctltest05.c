//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest05.c
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
//! \file xsysctltest05.c
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
unsigned long ulPeriprerAddr[] = { 
xWDT_BASE, xUART0_BASE, xUART1_BASE, xUART2_BASE, xTIMER0_BASE, xTIMER1_BASE, 
xTIMER2_BASE, xTIMER3_BASE, xSPI0_BASE, xSPI1_BASE, xSPI2_BASE, xSPI3_BASE,
xI2C0_BASE, xI2C1_BASE, xADC0_BASE, xACMP0_BASE};

unsigned long ulxPeriphEnableMask[] = {
SYSCLK_APBCLK_WDCLK_EN, SYSCLK_APBCLK_UART0_EN, SYSCLK_APBCLK_UART1_EN,
SYSCLK_APBCLK_UART2_EN,SYSCLK_APBCLK_TMR0_EN, SYSCLK_APBCLK_TMR1_EN,
SYSCLK_APBCLK_TMR2_EN, SYSCLK_APBCLK_TMR3_EN, SYSCLK_APBCLK_SPI0_EN,
SYSCLK_APBCLK_SPI1_EN, SYSCLK_APBCLK_SPI2_EN, SYSCLK_APBCLK_SPI3_EN,
SYSCLK_APBCLK_I2C0_EN, SYSCLK_APBCLK_I2C1_EN, SYSCLK_APBCLK_ADC_EN,
SYSCLK_APBCLK_ACMP_EN};

unsigned long ulGPIOBaseAddr[] = {xGPIO_PORTA_BASE, xGPIO_PORTB_BASE, 
xGPIO_PORTC_BASE, xGPIO_PORTD_BASE, xGPIO_PORTE_BASE};
//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl006GetTest(void)
{
    return "xsysctl, 006, xsysctl register and test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006Setup(void)
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
static void xSysctl006TearDown(void)
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
//! \brief xsysctl 002 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralDisable2_test(void)
{
    unsigned long ulTemp,ulRegVal,i;
    
    for(i = 0; i < 16; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCLK);
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK);
        TestAssert((0 == (ulRegVal & ulxPeriphEnableMask[i]) && 
        ((ulTemp & (~ulxPeriphEnableMask[i]))==ulRegVal)), "xsysctl API error!");        
    }
    
    for(i = 0; i < 5; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCLK);
        xSysCtlPeripheralDisable2(ulGPIOBaseAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK);
        TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)),
                                                          "xsysctl API error!");        
    }

    ulTemp = xHWREG(SYSCLK_APBCLK);
    xSysCtlPeripheralDisable2(PWMA_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK);
    TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_PWM01_EN & SYSCLK_APBCLK_PWM23_EN)
    &&((ulTemp & (~SYSCLK_APBCLK_PWM01_EN) & (~SYSCLK_APBCLK_PWM23_EN)) == ulRegVal)),
                                                          "xsysctl API error!");
 
    ulTemp = xHWREG(SYSCLK_APBCLK);
    xSysCtlPeripheralDisable2(PWMB_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK);
    TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_PWM45_EN & SYSCLK_APBCLK_PWM67_EN)
    &&((ulTemp & (~SYSCLK_APBCLK_PWM45_EN) & (~SYSCLK_APBCLK_PWM67_EN)) == ulRegVal)),
                                                          "xsysctl API error!");

}
//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralReset2_test(void)
{
    unsigned long i;
    
    for(i = 0; i <= 15; i++)
    {
        xSysCtlPeripheralReset2(ulPeriprerAddr[i]);
        TestAssert( (0 == xHWREG(GCR_IPRSTC1))&&(0 == xHWREG(GCR_IPRSTC2)), 
                                                          "xsysctl API error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralEnable2_test(void)
{
    unsigned long ulTemp,ulRegVal,i;


    for(i = 0; i < 16; i++)
    {
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK);
        TestAssert((ulxPeriphEnableMask[i] == (ulRegVal & ulxPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }

	
    xSysCtlPeripheralEnable2(GPIO_PORTA_BASE);
    ulTemp = xHWREG(SYSCLK_APBCLK);
    TestAssert((ulTemp == (xHWREG(SYSCLK_APBCLK))), "xsysctl API error!");
	
    xSysCtlPeripheralEnable2(PWMA_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK);
    TestAssert((SYSCLK_APBCLK_PWM01_EN == (ulRegVal & SYSCLK_APBCLK_PWM01_EN)),
                                                          "xsysctl API error!");
	
    xSysCtlPeripheralEnable2(PWMB_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK);
    TestAssert((SYSCLK_APBCLK_PWM23_EN == (ulRegVal & SYSCLK_APBCLK_PWM23_EN)),
                                                          "xsysctl API error!");
}

//*****************************************************************************
//
//! \brief xsysctl 006 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006Execute(void)
{
    xsysctl_xSysCtlPeripheralEnable2_test();
    xsysctl_xSysCtlPeripheralDisable2_test();   
    xsysctl_xSysCtlPeripheralReset2_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl006Register = {
    xSysctl006GetTest,
    xSysctl006Setup,
    xSysctl006TearDown,
    xSysctl006Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl05[] =
{
    &sTestXSysctl006Register,
    0
};