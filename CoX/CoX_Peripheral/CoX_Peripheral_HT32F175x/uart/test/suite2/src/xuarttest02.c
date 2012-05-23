//*****************************************************************************
//
//! @page xuart_testcase xuart test
//!  
//! File: @ref xuart_testcase.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the xuart sub component.<br><br>
//! - \p Board: HT32F125x <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the VCOM UART. <br><br>
//! .
//! 
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define: 
//! <br>(1)None.<br><br>
//! - \p Option-hardware: 
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:         
//! <br>None.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//! 
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xuart_Config
//! .
//! \file xuart_testcase.c
//! \brief xuart test source file
//! \file xuart_testcase.h
//! \brief xuart test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "testcase.h"

#define xSYSCTL_PERIPH_UART  xSYSCTL_PERIPH_UART1

    //
    // IrDA configuration test
    //
void  xuart001Execute_IrDAConfig(void);

#define countof(x) sizeof(x)/sizeof(*x)


//*****************************************************************************
//
//! \page test_xuart test_xuart
//!
//! <h2>Description</h2>
//! 
//! Test xuart . <br> 
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! Get the Test description of xuart001  test.
//!
//! \return the desccription of the xuart001 test.
//
//*****************************************************************************
static char* xuart003GetTest(void)
{
    return "xuart [003]: IrDA test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart003Setup(void)
{
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart003TearDown(void)
{

}

//*****************************************************************************
//
//! !brief xuart 003 test for IrDA config.
//!
//! \return None.
//
//*****************************************************************************
void xuart003Execute_IrDAConfig(void)
{
    unsigned long ulTemp1, ulTemp2;

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);

    UARTEnableIrDA(UART1_BASE, xtrue);
    ulTemp1 = xHWREG(UART1_BASE + USART_IRCR) & USART_IRCR_IRDA_EN;
    TestAssert(ulTemp1 == USART_IRCR_IRDA_EN, "xuart API  error!");

    UARTEnableIrDA(UART1_BASE, xfalse);
    ulTemp1 = xHWREG(UART1_BASE + USART_IRCR) & USART_IRCR_IRDA_EN;
    TestAssert(ulTemp1 == 0, "xuart API  error!");
    
    ulTemp1 = USART_IRCR_IRDA_EN | USART_IRCR_LB_EN;
    UARTIrDAConfig(UART1_BASE, ulTemp1);
    ulTemp2 = xHWREG(UART1_BASE + USART_IRCR);
    TestAssert(ulTemp1 == ulTemp2, "xuart API error!");

    ulTemp1 = (USART_IRCR_TXINV | USART_IRCR_RXINV);
    UARTIrDAConfig(UART1_BASE, ulTemp1);
    ulTemp2 = xHWREG(UART1_BASE + USART_IRCR);
    TestAssert(ulTemp1 == ulTemp2, "xuart API \"UARTIrDAConfig\" error!");

    ulTemp1 = 0x5500;
    UARTIrDAConfig(UART1_BASE, ulTemp1);
    ulTemp2 = xHWREG(UART1_BASE + USART_IRCR);
    TestAssert(ulTemp1 == ulTemp2, "xuart API \"UARTIrDAConfig\" error!");

    ulTemp1 = 0xAA00;
    UARTIrDAConfig(UART1_BASE, ulTemp1);
    ulTemp2 = xHWREG(UART1_BASE + USART_IRCR);
    TestAssert(ulTemp1 == ulTemp2, "xuart API \"UARTIrDAConfig\" error!");
}
//*****************************************************************************
//
//! xuart005 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart003Execute(void)
{
    //
    // IrDA configuration test
    //
    xuart003Execute_IrDAConfig();
    
}

//
// xuart flow control test case struct.
//
const tTestCase sTestxuart001UART02 = {
    xuart003GetTest,
    xuart003Setup,
    xuart003TearDown,
    xuart003Execute
};

//
// xuart test suits.
//
const tTestCase * const psPatternxUART02[] =
{
    &sTestxuart001UART02,
    0
};

