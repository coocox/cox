//*****************************************************************************
//
//! @page xuart_testcase xuart test
//!  
//! File: @ref xuart_testcase.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the xuart sub component.<br><br>
//! - \p Board: MiniSTM32V100  <br><br>
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

unsigned long uart0CallbackFunc(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData);
void xuart001Execute_uartInt(void);


#define countof(x) sizeof(x)/sizeof(*x)

//
// uart rx and tx test 
//
char  sendData[] = {'0','1','2','3','4','5','6','7','8','9'};

//*****************************************************************************
//
//! Get the Test description of xuart001  test.
//!
//! \return the desccription of the xuart001 test.
//
//*****************************************************************************
static char* xuart005GetTest(void)
{
    return "xuart [005]: xuart interrupt test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart005Setup(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xUARTConfigSet(USART1_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart005TearDown(void)
{
    xUARTConfigSet(USART2_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART2_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! !brief callback function of uart1 interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long uart2CallbackFunc(void *pvCBData,
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    UARTIntDisable(USART1_BASE, UART_INT_TC);
    TestEmitToken('b');
    return 0;
}

//*****************************************************************************
//
//! test RX,TX interrupt 
//!
//! \return None.
//
//*****************************************************************************
void xuart005Execute_uartInt(void)
{
    unsigned char info[] = "Hello,CooCox World!";
    //
    // Register the uart1 interrupt handler, Enable uart1 receive interrupt.
    //

    xIntEnable(INT_USART1);
    UARTIntEnable(USART1_BASE, UART_INT_TC);
    UARTIntCallbackInit(USART1_BASE, uart2CallbackFunc);
    //UARTBufferWrite(USART2_BASE, info, countof(info));
    UARTCharPut(USART1_BASE, 'a'); 
    //
    // wait until Transmitter complete
    //
    TestAssertQBreak("b","UART Tx interrupt test fail", 0xFFFFFFFF);
    UARTIntDisable(USART1_BASE, UART_INT_TC);
    
}

//*****************************************************************************
//
//! xuart004 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart005Execute(void)
{
    
    //
    // rx,tx and interrupt test
    //
    xuart005Execute_uartInt();

}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart001UART04 = {
    xuart005GetTest,
    xuart005Setup,
    xuart005TearDown,
    xuart005Execute
};


//
// xuart test suits.
//
const tTestCase * const psPatternxUART04[] =
{
    &sTestxuart001UART04,

    0
};