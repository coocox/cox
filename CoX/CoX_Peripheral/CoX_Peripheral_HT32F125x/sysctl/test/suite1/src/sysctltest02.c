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
//
// HT32F125x_SysCtl_Peripheral_ID Array
//
unsigned long ulSysCtlPeriph[] = {SYSCTL_PERIPH_FMC, SYSCTL_PERIPH_SRAM, 
                                   SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_SPI0,
								   SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_AFIO,
                                   SYSCTL_PERIPH_EXTI, SYSCTL_PERIPH_GPIOA,
                                   SYSCTL_PERIPH_GPIOB, SYSCTL_PERIPH_WDT,
                                   SYSCTL_PERIPH_RTC, SYSCTL_PERIPH_TMR0,
                                   SYSCTL_PERIPH_TMR1, SYSCTL_PERIPH_OPA0,
                                   SYSCTL_PERIPH_OPA1, SYSCTL_PERIPH_ADC
                                  };


//
// Peripheral Enable Mask
//
unsigned long ulPeriphEnableMask[] = {SYSCLK_AHBCCR_FMC_EN, SYSCLK_AHBCCR_SRAM_EN,
                                      SYSCLK_APBCCR0_I2C0_EN, SYSCLK_APBCCR0_SPI0_EN, 
                                      SYSCLK_APBCCR0_UART0_EN, SYSCLK_APBCCR0_AFIO_EN,
									  SYSCLK_APBCCR0_EXTI_EN, SYSCLK_APBCCR0_GPIOA_EN,
									  SYSCLK_APBCCR0_GPIOB_EN, SYSCLK_APBCCR1_WDT_EN,
                                      SYSCLK_APBCCR1_RTC_EN, SYSCLK_APBCCR1_TIM0_EN,
                                      SYSCLK_APBCCR1_TIM1_EN, SYSCLK_APBCCR1_OPA0_EN,
                                      SYSCLK_APBCCR1_OPA1_EN, SYSCLK_APBCCR1_ADC0_EN };

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl003GetTest(void)
{
    return "xsysctl, 003, xsysctl api test:Peripheral Control.";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl003Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl003TearDown(void)
{   
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralDisable_test(void)
{
    unsigned long ulTemp,ulRegVal,i;
    
    for(i=0; i<2; i++)
    {
        ulTemp = xHWREG(SYSCLK_AHBCCR);
        SysCtlPeripheralDisable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_AHBCCR);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
    }

    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralEnable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_AHBCCR);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");
	}
    for(i=2; i<9; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCCR0);
        SysCtlPeripheralDisable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR0);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");  
    }

    for(i = 2; i < 9; i++)
    {
        SysCtlPeripheralEnable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR0);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }

    for(i=9; i<16; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCCR1);
        SysCtlPeripheralDisable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR1);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");  
    }

    for(i = 9; i < 16; i++)
    {
        SysCtlPeripheralEnable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR1);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }
}


//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralReset_test(void)
{
    unsigned long ulTemp;
    
    for (ulTemp=2; ulTemp<9; ulTemp++)
    {
        SysCtlPeripheralReset(ulSysCtlPeriph[ulTemp]);
        TestAssert( (0 == xHWREG(RSTCU_APBPRSTR0))&&(0 == xHWREG(RSTCU_APBPRSTR1)),
                                                          "xsysctl API error!");
    }

    for (ulTemp=10; ulTemp<16; ulTemp++)
    {
        SysCtlPeripheralReset(ulSysCtlPeriph[ulTemp]);
        TestAssert((0 == xHWREG(RSTCU_APBPRSTR1)), "xsysctl API error!");
    }
}


//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralEnable_test(void)
{
    unsigned long ulRegVal,i;


    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralEnable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_AHBCCR);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");        
    }
    
    for(i = 2; i < 9; i++)
    {
        SysCtlPeripheralEnable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR0);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }

    for(i = 9; i < 16; i++)
    {
        SysCtlPeripheralEnable(ulSysCtlPeriph[i]);
        ulRegVal = xHWREG(SYSCLK_APBCCR1);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
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
static void xSysctl003Execute(void)
{
    xsysctl_SysCtlPeripheralEnable_test();
    xsysctl_SysCtlPeripheralDisable_test();
    xsysctl_SysCtlPeripheralReset_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl003Register = {
		xSysctl003GetTest,
		xSysctl003Setup,
		xSysctl003TearDown,
		xSysctl003Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl02[] =
{
    &sTestXSysctl003Register,
    0
};
