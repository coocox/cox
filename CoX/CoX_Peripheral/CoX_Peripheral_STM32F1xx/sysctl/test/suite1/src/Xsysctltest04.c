//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: MCBSTM32<br><br>
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

unsigned long ulSysClockPara[] = 
{   
    16000000,
    24000000,
    32000000,
    40000000,
    48000000,
    56000000,
    64000000,
    72000000,
};



//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0401 register test.
//!
//! \return the desccription of the xcore0401 test.
//
//*****************************************************************************
static char* xSysctl0401GetTest(void)
{
    return "xsysctl, 0401, SysCtlClockGet Test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0401 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0401Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0401 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0401TearDown(void)
{  
    SysCtlDelay(200);
    //xSysCtlPeripheralEnable(SYSCTL_PERIPH_FLITF);
    //xSysCtlPeripheralEnable(SYSCTL_PERIPH_SRAM);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    //xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    xSPinTypeUART(UART1RX,PA10);
    xSPinTypeUART(UART1TX,PA9);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    //SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    xUARTConfigSet(USART1_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                        UART_CONFIG_STOP_ONE | 
                                        UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    TestIOPut('\r');
    TestIOPut('\n');
}


//*****************************************************************************
//
//! \brief xsysctl 0401 test of SysCtl Power Down Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlClockGet_test(void)
{     
    unsigned long ulSize = sizeof(ulSysClockPara)/sizeof(ulSysClockPara[0]);
    unsigned long i = 0;
    
    
    //
    // Wait for UART Send Data over , otherwise terimal will receive messy code
    //
    SysCtlDelay(20000);

    for(i = 0; i < ulSize; i++) 
    {
        //
        // Disable HSI
        //
        xHWREG(RCC_CR) |= RCC_CR_HSION;
        while((xHWREG(RCC_CR) & RCC_CR_HSIRDY) == 0);

        xHWREG(RCC_CFGR) &= ~RCC_CFGR_SW_M;
        while((xHWREG(RCC_CFGR) & RCC_CFGR_SWS_M) != 0);

        //
        // for configure PLL Parameter,you must disable PLL
        //
        xHWREG(RCC_CR) &= ~RCC_CR_PLLON;
        while((xHWREG(RCC_CR) & RCC_CR_PLLRDY) != 0);

        //
        // configure PLL MUL 2->9 max speed is 72MHz
        //
        xHWREG(RCC_CFGR) &= ~RCC_CFGR_PLLMUL_M;
        xHWREG(RCC_CFGR) |= i<<RCC_CFGR_PLLMUL_S;

        xHWREG(RCC_CFGR) &= ~RCC_CFGR_PLLXTPRE;
        xHWREG(RCC_CFGR) |=  RCC_CFGR_PLLSRC;

        xHWREG(RCC_CR) |= RCC_CR_PLLON;
        while((xHWREG(RCC_CR) & RCC_CR_PLLRDY) == 0);

        xHWREG(RCC_CFGR) &= ~RCC_CFGR_SW_M;
        xHWREG(RCC_CFGR) |=  RCC_CFGR_SW_PLL; 
        while((xHWREG(RCC_CFGR) & RCC_CFGR_SWS_M) != 0x08);

        xHWREG(RCC_CR) &= ~RCC_CR_HSION;
        while((xHWREG(RCC_CR) & RCC_CR_HSIRDY) != 0);


        TestAssert((ulSysClockPara[i] == SysCtlHClockGet()),
                "xSysCtl API SysCtlHClockGet Error");
        TestAssert((ulSysClockPara[i] == xSysCtlClockGet()),
                "xSysCtl API xSysCtlClockGet Error");
        TestAssert(((ulSysClockPara[i]/2) == SysCtlAPB1ClockGet()),
                "xSysCtl API SysCtlAPB1ClockGet Error");
        TestAssert((ulSysClockPara[i] == SysCtlAPB2ClockGet()),
                "xSysCtl API SysCtlAPB2ClockGet Error");
    }

}




//*****************************************************************************
//
//! \brief xsysctl 0401 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0401Execute(void)
{
    xsysctl_SysCtlClockGet_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0401Register = {
    xSysctl0401GetTest,
    xSysctl0401Setup,
    xSysctl0401TearDown,
    xSysctl0401Execute,
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl04[] =
{
    &sTestXSysctl0401Register,
    0
};
