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
//! NUC1xx_SysCtl_Peripheral_ID Array
//
unsigned long ulSYSCTL_PERIPH[] = { 
SYSCTL_PERIPH_PDMA, SYSCTL_PERIPH_ISP, SYSCTL_PERIPH_WDT, SYSCTL_PERIPH_RTC,  
SYSCTL_PERIPH_TMR0, SYSCTL_PERIPH_TMR1, SYSCTL_PERIPH_TMR2,SYSCTL_PERIPH_TMR3,  
SYSCTL_PERIPH_FDIV, SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_I2C1, SYSCTL_PERIPH_SPI0, 
SYSCTL_PERIPH_SPI1, SYSCTL_PERIPH_SPI2, SYSCTL_PERIPH_SPI3,SYSCTL_PERIPH_UART0,
SYSCTL_PERIPH_UART1,SYSCTL_PERIPH_UART2, SYSCTL_PERIPH_PWM01,SYSCTL_PERIPH_PWM23, 
SYSCTL_PERIPH_PWM45,SYSCTL_PERIPH_PWM67, SYSCTL_PERIPH_CAN0,SYSCTL_PERIPH_USBD,
SYSCTL_PERIPH_ADC, SYSCTL_PERIPH_I2S, SYSCTL_PERIPH_ACMP, SYSCTL_PERIPH_PS2};


//
//! Peripheral Enable Mask
//
unsigned long ulPeriphEnableMask[] = {
SYSCLK_AHBCLK_PDMA_EN, SYSCLK_AHBCLK_ISP_EN, SYSCLK_APBCLK_WDCLK_EN,
SYSCLK_APBCLK_RTC_EN, SYSCLK_APBCLK_TMR0_EN, SYSCLK_APBCLK_TMR1_EN,
SYSCLK_APBCLK_TMR2_EN, SYSCLK_APBCLK_TMR3_EN, SYSCLK_APBCLK_FDIV_EN,
SYSCLK_APBCLK_I2C0_EN, SYSCLK_APBCLK_I2C1_EN, SYSCLK_APBCLK_SPI0_EN,
SYSCLK_APBCLK_SPI1_EN, SYSCLK_APBCLK_SPI2_EN, SYSCLK_APBCLK_SPI3_EN,
SYSCLK_APBCLK_UART0_EN, SYSCLK_APBCLK_UART1_EN,SYSCLK_APBCLK_UART2_EN, 
SYSCLK_APBCLK_PWM01_EN, SYSCLK_APBCLK_PWM01_EN, SYSCLK_APBCLK_PWM45_EN,  
SYSCLK_APBCLK_PWM67_EN, SYSCLK_APBCLK_CAN0_EN, SYSCLK_APBCLK_USBD_EN,
SYSCLK_APBCLK_ADC_EN, SYSCLK_APBCLK_I2S_EN,SYSCLK_APBCLK_ACMP_EN, 
SYSCLK_APBCLK_PS2_EN};

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
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl003TearDown(void)
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
//! \brief xsysctl 001 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralDisable_test(void)
{
    unsigned long ulTemp,ulRegVal,i;
    
    for(i = 0; i < 2; i++)
    {
        ulTemp = xHWREG(SYSCLK_AHBCLK);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SYSCLK_AHBCLK);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }
    
    for(i = 2; i < 28; i++)
    {
        ulTemp = xHWREG(SYSCLK_APBCLK);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }

    ulTemp = xHWREG(0x50000208);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIO);
    ulRegVal = xHWREG(0x50000208);
    TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)), 
                                                         "xsysctl API  error!");
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of reset() test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_Reset_test(void)
{
    unsigned long ulTemp;
    xtBoolean xtTemp;

    ulTemp = SysCtlResetSrcGet();
    TestAssert(ulTemp == ulTemp, "xsysctl API error!");
    
    xtTemp = SysCtlKeyAddrUnlock();
    TestAssert(xtTemp == 1, "xsysctl API error!");
    
    xtTemp = SysCtlKeyAddrLock();
    TestAssert(xtTemp == 0, "xsysctl API error!");
    
    SysCtlResetSrcClear(SysCtlResetSrcGet());
    ulTemp = xHWREG(GCR_RSTSRC);
    TestAssert(ulTemp == 0, "xsysctl API error!");
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
    
    for (ulTemp = 0;ulTemp <= 24; ulTemp++)
    {
        SysCtlPeripheralReset(ulSYSCTL_PERIPH[ulTemp]);
        TestAssert( (0 == xHWREG(GCR_IPRSTC1))&&(0 == xHWREG(GCR_IPRSTC2)),
                                                          "xsysctl API error!");
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
    unsigned long ulTemp,ulRegVal,i;


    for(i = 0; i < 2; i++)
    {
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SYSCLK_AHBCLK);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");
        
    }
    
    for(i = 2; i < 28; i++)
    {
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SYSCLK_APBCLK);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                                                          "xsysctl API error!");  
    }
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    ulTemp = xHWREG(SYSCLK_APBCLK);
    TestAssert((ulTemp == (xHWREG(SYSCLK_APBCLK))), "xsysctl API error!");
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
    xsysctl_Reset_test();
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