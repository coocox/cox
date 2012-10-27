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
//! Klx_SysCtl_Peripheral_ID Array
//
unsigned long ulSYSCTL_PERIPH[] = { 
SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_I2C1, SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1,  
SYSCTL_PERIPH_UART2, SYSCTL_PERIPH_USB, SYSCTL_PERIPH_ACMP,SYSCTL_PERIPH_SPI0,  
SYSCTL_PERIPH_SPI1, SYSCTL_PERIPH_LPTMR, SYSCTL_PERIPH_TSI, SYSCTL_PERIPH_GPIOA, 
SYSCTL_PERIPH_GPIOB, SYSCTL_PERIPH_GPIOC, SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOE,
SYSCTL_PERIPH_FLASH,SYSCTL_PERIPH_DMAMUX, SYSCTL_PERIPH_PIT,SYSCTL_PERIPH_TMR0, 
SYSCTL_PERIPH_TMR1,SYSCTL_PERIPH_TMR2, SYSCTL_PERIPH_ADC,SYSCTL_PERIPH_RTC,
SYSCTL_PERIPH_DAC, SYSCTL_PERIPH_DMA};


//
//! Peripheral Enable Mask
//
unsigned long ulPeriphEnableMask[] = {
SIM_SCGC4_I2C0_EN,  SIM_SCGC4_I2C1_EN,  SIM_SCGC4_UART0_EN,
SIM_SCGC4_UART1_EN, SIM_SCGC4_UART2_EN, SIM_SCGC4_USBOTG_EN,
SIM_SCGC4_CMP_EN,   SIM_SCGC4_SPI0_EN,  SIM_SCGC4_SPI1_EN,
SIM_SCGC5_LPTMR_EN, SIM_SCGC5_TSI_EN,   SIM_SCGC5_PORTA_EN,
SIM_SCGC5_PORTB_EN, SIM_SCGC5_PORTC_EN, SIM_SCGC5_PORTD_EN,
SIM_SCGC5_PORTE_EN, SIM_SCGC6_FTF_EN,   SIM_SCGC6_DMAMUX_EN,
SIM_SCGC6_PIT_EN,   SIM_SCGC6_TPM0_EN,  SIM_SCGC6_TPM1_EN,
SIM_SCGC6_TPM2_EN,  SIM_SCGC6_ADC0_EN,  SIM_SCGC6_RTC_EN,
SIM_SCGC6_DAC0_EN,  SIM_SCGC7_DMA_EN};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl003GetTest(void)
{
    return "xsysctl, 003, xsysctl register and api test";
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
    
    for(i = 0; i < 9; i++)
    {
        ulTemp = xHWREG(SIM_SCGC4);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC4);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }
    
    for(i = 9; i < 16; i++)
    {
        ulTemp = xHWREG(SIM_SCGC5);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC5);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }

    for(i = 16; i < 25; i++)
    {
        ulTemp = xHWREG(SIM_SCGC6);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC6);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }

    for(i = 25; i < 26; i++)
    {
        ulTemp = xHWREG(SIM_SCGC7);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC7);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
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


    for(i = 0; i < 9; i++)
    {
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC4);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");
    }

    for(i = 9; i < 16; i++)
    {
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC5);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");
    }

    for(i = 16; i < 25; i++)
    {
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC6);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }
	
    for(i = 25; i < 26; i++)
    {
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SIM_SCGC7);
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