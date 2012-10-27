//*****************************************************************************
//
//! @page xuart_testcase xuart  test
//!  
//! File: @ref xuart_testcase.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the xuart sub component.<br><br>
//! - \p Board: KLxx <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the VCOM UART.
//!   <br><br>
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

#define UART_BASE UART1_BASE

#define UART_BAUD 9600UL


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
//! Get the Test description of xuart0301  test.
//!
//! \return the desccription of the xuart0301 test.
//
//*****************************************************************************
static char* xuart0301GetTest(void)
{
    return "UART 0301 : UART Send/Receive test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0301 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0301Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART0_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0301 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0301TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
}


//*****************************************************************************
//
//! xuart0301 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0301Execute(void)
{
    unsigned char UartData = 0;
    unsigned char i = 0;
    xtBoolean bTmpBoolean = xfalse;

    UART_Print("\r\nPlease wait 1 s then type the follow string\r\n");
    UART_Print("123456789ABCDE\r\n");

    bTmpBoolean = UARTCharsAvail(UART_BASE);
    TestAssert((xfalse == bTmpBoolean),
            "UART 0301: Function UARTCharsAvail failed!\r\n");
    
    while((UartData = UARTCharGet(UART_BASE)) != '\n')
    {
        UARTCharPut(UART_BASE, UartData);
        if(++i >= 15)
        {
            break;
        }
    }
    UARTCharPut(UART_BASE, '\r');
    UARTCharPut(UART_BASE, '\n');

}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0301 = {
    xuart0301GetTest,
    xuart0301Setup,
    xuart0301TearDown,
    xuart0301Execute
};

//
// xuart test suits.
//
const tTestCase * const psPatternxUART03[] =
{
    &sTestxuart0301,
    0
};








