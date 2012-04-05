//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest05.c
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
unsigned long ulPeriprerAddr[] = {xI2C0_BASE, xSPI0_BASE, xUART0_BASE,
                                   xGPIO_PORTA_BASE, xGPIO_PORTB_BASE, xWDT_BASE,
			                  xTIMER0_BASE, xTIMER1_BASE, xACMP0_BASE, xADC0_BASE};

//
// Peripheral Enable Mask
//
unsigned long ulxPeriphEnableMask[] = {SYSCLK_APBCCR0_I2C0_EN, SYSCLK_APBCCR0_SPI0_EN, 
                                       SYSCLK_APBCCR0_UART0_EN, SYSCLK_APBCCR0_GPIOA_EN,
									   SYSCLK_APBCCR0_GPIOB_EN, SYSCLK_APBCCR1_WDT_EN,
                                       SYSCLK_APBCCR1_TIM0_EN, SYSCLK_APBCCR1_TIM1_EN,
                                       SYSCLK_APBCCR1_OPA0_EN, SYSCLK_APBCCR1_ADC0_EN };
//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl006GetTest(void)
{
    return "xsysctl, 006, xsysctl peripheral enable and disable test";
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
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
  
    for(i=0; i<5; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCCR0);
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR0);
        TestAssert((0 == (ulRegVal & ulxPeriphEnableMask[i]) && 
        ((ulTemp & (~ulxPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");  
    }

    for(i=5; i<10; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCCR1);
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR1);
        TestAssert((0 == (ulRegVal & ulxPeriphEnableMask[i]) && 
        ((ulTemp & (~ulxPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");  
    }

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
    unsigned long ulTemp;
    
    for (ulTemp=0; ulTemp<5; ulTemp++)
    {
        xSysCtlPeripheralReset2(ulPeriprerAddr[ulTemp]);
        TestAssert( (0 == xHWREG(RSTCU_APBPRSTR0)), "xsysctl API error!");
    }

    for (ulTemp=5; ulTemp<10; ulTemp++)
    {
        xSysCtlPeripheralReset2(ulPeriprerAddr[ulTemp]);
        TestAssert((0 == xHWREG(RSTCU_APBPRSTR1)), "xsysctl API error!");
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

    
    for(i = 0; i < 5; i++)
    {
        xSysCtlPeripheralEnable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR0);
        TestAssert((ulxPeriphEnableMask[i] == (ulRegVal & ulxPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }

    for(i = 5; i < 10; i++)
    {
        xSysCtlPeripheralEnable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR1);
        TestAssert((ulxPeriphEnableMask[i] == (ulRegVal & ulxPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }
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
    xsysctl_xSysCtlPeripheralDisable2_test(); 
    xsysctl_xSysCtlPeripheralEnable2_test();  
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
