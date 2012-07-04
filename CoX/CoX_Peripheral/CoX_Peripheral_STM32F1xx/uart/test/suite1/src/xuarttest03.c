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

void xuart006Execute_ModemConfig(void);

unsigned long ulModemSet[] = {UART_MODEM_RTS, UART_MODEM_CTS};
unsigned long ulBaseArray03[] = {USART1_BASE, USART2_BASE, USART3_BASE,
                                 USART4_BASE, USART5_BASE};

//*****************************************************************************
//
//! Get the Test description of xuart006  test.
//!
//! \return the desccription of the xuart006 test.
//
//*****************************************************************************
static char* xuart004GetTest(void)
{
    return "xuart [004]: xuart Modem and DMA test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart004Setup(void)
{

}

//*****************************************************************************
//
//! Something should do after the test execute of xuart006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart004TearDown(void)
{
    xUARTConfigSet(USART2_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART2_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! !brief xuart 001 test for modem config.
//!
//! \return None.
//
//*****************************************************************************
void xuart004Execute_ModemConfig(void)
{
    int i;
    unsigned long ulTemp1;
    
    //
    // Set modem mode
    //
    for(i=0; i<3; i++)
    {
        UARTModemControlSet(ulBaseArray03[i], UART_MODEM_RTS);
        ulTemp1 = xHWREG(ulBaseArray03[i] + USART_CR3);
        TestAssert((ulTemp1&UART_MODEM_RTS) == UART_MODEM_RTS, "xuart API error!");   
    }

    for(i=0; i<3; i++)
    {
        UARTModemControlSet(ulBaseArray03[i], UART_MODEM_CTS);
        ulTemp1 = xHWREG(ulBaseArray03[i] + USART_CR3);
        TestAssert((ulTemp1&UART_MODEM_CTS) == UART_MODEM_CTS, "xuart API error!");   
    }

    for(i=0; i<3; i++)
    {
        UARTModemControlSet(ulBaseArray03[i], (UART_MODEM_RTS | UART_MODEM_CTS));
        ulTemp1 = xHWREG(ulBaseArray03[i] + USART_CR3);
        TestAssert((ulTemp1&(UART_MODEM_RTS | UART_MODEM_CTS)) == (UART_MODEM_RTS | UART_MODEM_CTS),
                   "xuart API error!");   
    }
    //
    // UART DMA Test
    //
    for(i=0; i<3; i++)
    {
        UARTDMAEnable(ulBaseArray03[i], UART_DMA_RX);
        ulTemp1 = xHWREG(ulBaseArray03[i] + USART_CR3);
        TestAssert(UART_DMA_RX == (ulTemp1 & UART_DMA_RX), "xuart API error!");
        UARTDMADisable(ulBaseArray03[i], UART_DMA_RX);
        ulTemp1 = xHWREG(ulBaseArray03[i] + USART_CR3);
        TestAssert(0 == (ulTemp1 & UART_DMA_RX), "xuart API error!");

        UARTDMAEnable(ulBaseArray03[i], UART_DMA_TX);
        ulTemp1 = xHWREG(ulBaseArray03[i] + USART_CR3);
        TestAssert(UART_DMA_TX == (ulTemp1 & UART_DMA_TX), "xuart API error!");
        UARTDMADisable(ulBaseArray03[i], UART_DMA_TX);
        ulTemp1 = xHWREG(ulBaseArray03[i] + USART_CR3);
        TestAssert(0 == (ulTemp1 & UART_DMA_TX), "xuart API error!");
	}
}
//*****************************************************************************
//
//! xuart004 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart004Execute(void)
{
    //
    // test for modem config
    //
    xuart004Execute_ModemConfig();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart001UART03 = {
    xuart004GetTest,
    xuart004Setup,
    xuart004TearDown,
    xuart004Execute
};

//
// xuart test suits.
//
const tTestCase * const psPatternxUART03[] =
{
    &sTestxuart001UART03,

    0
};
