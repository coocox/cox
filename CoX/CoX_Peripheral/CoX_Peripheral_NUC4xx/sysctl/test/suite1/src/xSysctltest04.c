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
#include "xhw_sysctl.h"

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
xWDT_BASE, xUART1_BASE, xUART2_BASE, xUART3_BASE, xUART4_BASE, xUART5_BASE,
xTIMER0_BASE, xTIMER1_BASE,xTIMER2_BASE, xTIMER3_BASE, xSPI0_BASE, xSPI1_BASE, xSPI2_BASE,
xSPI3_BASE, xI2C0_BASE, xI2C1_BASE, xI2C2_BASE, xI2C3_BASE, xADC0_BASE, xACMP_BASE};

unsigned long ulxPeriphEnableMask[] = {
SYSCLK_APBCLK0_WDCLK_EN, SYSCLK_APBCLK0_UART1_EN, SYSCLK_APBCLK0_UART2_EN,
SYSCLK_APBCLK0_UART3_EN, SYSCLK_APBCLK0_UART4_EN, SYSCLK_APBCLK0_UART5_EN, SYSCLK_APBCLK0_TMR0_EN,
SYSCLK_APBCLK0_TMR1_EN, SYSCLK_APBCLK0_TMR2_EN, SYSCLK_APBCLK0_TMR3_EN, SYSCLK_APBCLK0_SPI0_EN,
SYSCLK_APBCLK0_SPI1_EN, SYSCLK_APBCLK0_SPI2_EN, SYSCLK_APBCLK0_SPI3_EN, SYSCLK_APBCLK0_I2C0_EN,
SYSCLK_APBCLK0_I2C1_EN, SYSCLK_APBCLK0_I2C2_EN, SYSCLK_APBCLK0_I2C3_EN, SYSCLK_APBCLK0_ADC_EN,
SYSCLK_APBCLK0_ACMP_EN};

unsigned long ulGPIOBaseAddr[] = {xGPIO_PORTA_BASE, xGPIO_PORTB_BASE, xGPIO_PORTC_BASE, xGPIO_PORTD_BASE,
xGPIO_PORTE_BASE, xGPIO_PORTF_BASE, xGPIO_PORTG_BASE, xGPIO_PORTH_BASE, xGPIO_PORTI_BASE};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the description of the xcore004 test.
//
//*****************************************************************************
static char* xSysctl005GetTest(void)
{
    return "xsysctl, 005, xsysctl Enable2 or Disable2 peripheral test";
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
        ulTemp = xHWREG(SYSCLK_APBCLK0);
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK0);
        TestAssert((0 == (ulRegVal & ulxPeriphEnableMask[i]) &&
        ((ulTemp & (~ulxPeriphEnableMask[i]))==ulRegVal)), "xsysctl API error!");
    }

    for(i = 0; i < 5; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCLK0);
        xSysCtlPeripheralDisable2(ulGPIOBaseAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK0);
        TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)),
                                                          "xsysctl API error!");
    }

    ulTemp = xHWREG(SYSCLK_APBCLK1);
    xSysCtlPeripheralDisable2(PWMA_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK1);
    TestAssert((0 == (ulRegVal & SYSCLK_APBCLK1_PWMA01_EN & SYSCLK_APBCLK1_PWMA23_EN & SYSCLK_APBCLK1_PWMA45_EN)),
                                                          "xsysctl API error!");

    ulTemp = xHWREG(SYSCLK_APBCLK1);
    xSysCtlPeripheralDisable2(PWMB_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK1);
    TestAssert((0 == (ulRegVal & SYSCLK_APBCLK1_PWMB01_EN & SYSCLK_APBCLK1_PWMB23_EN & SYSCLK_APBCLK1_PWMB45_EN)),
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
    unsigned long ulRegVal,i;

    for(i = 0; i < 16; i++)
    {
        xSysCtlPeripheralEnable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK0);
        TestAssert((ulxPeriphEnableMask[i] == (ulRegVal & ulxPeriphEnableMask[i])), "xsysctl API error!");
    }

    xSysCtlPeripheralEnable2(PWMA_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK1);
    TestAssert((SYSCLK_APBCLK1_PWMA01_EN == (ulRegVal & SYSCLK_APBCLK1_PWMA01_EN)), "xsysctl API error!");

    xSysCtlPeripheralEnable2(PWMB_BASE);
    ulRegVal = xHWREG(SYSCLK_APBCLK1);
    TestAssert((SYSCLK_APBCLK1_PWMB23_EN == (ulRegVal & SYSCLK_APBCLK1_PWMB23_EN)), "xsysctl API error!");
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
	xsysctl_xSysCtlPeripheralEnable2_test();
    xsysctl_xSysCtlPeripheralDisable2_test();
    xsysctl_xSysCtlPeripheralReset2_test();
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
