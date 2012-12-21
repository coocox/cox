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


unsigned long ulBaseArray01[] = {USART1_BASE, USART2_BASE, USART3_BASE,
                                 USART4_BASE, USART5_BASE};

void xuart002Execute_LinConfig(void);
void xuart002Execute_SyncConfig(void);

#define countof(x) sizeof(x)/sizeof(*x)

//*****************************************************************************
//
//! Get the Test description of xuart002  test.
//!
//! \return the desccription of the xuart002 test.
//
//*****************************************************************************
static char* xuart002GetTest(void)
{
    return "xuart [002]: xuart Synchronous mode and LIN Mode test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart002Setup(void)
{

}

//*****************************************************************************
//
//! Something should do after the test execute of xuart002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart002TearDown(void)
{
    xUARTConfigSet(USART2_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART2_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! !brief xuart 001 test for Synchronous mode config.
//!
//! \return None.
//
//*****************************************************************************
void xuart002Execute_SyncConfig(void)
{	  
    unsigned long i,ulTemp,ulTemp1;
    
    for(i=0; i<3; i++)
    {
        ulTemp1 = (UART_SYN_CPOL | UART_SYN_CPHA | UART_SYN_LBCL);
        UARTSynModeSet(ulBaseArray01[i], ulTemp1);
        ulTemp = xHWREG(ulBaseArray01[i] + USART_CR2);
        TestAssert((ulTemp1 & ulTemp) == ulTemp1, "xuart API error!");
    }
    
    for(i=0; i<3; i++)
    {
        UARTSYNDisable(ulBaseArray01[i]);
        ulTemp = xHWREG(ulBaseArray01[i] + USART_CR2);
        TestAssert((USART_CR2_CLKEN & ulTemp) == 0, "xuart API error!");
    }

 
}

//*****************************************************************************
//
//! !brief xuart 001 test for LIN mode config.
//!
//! \return None.
//
//*****************************************************************************
void xuart002Execute_LinConfig(void)
{	  
     unsigned long i, ulReadVal;

    //
	// LIN configure test.
	//
     
    for(i=0; i<3; i++)
    {
        UARTEnableLIN(ulBaseArray01[i]);
        ulReadVal = xHWREG(ulBaseArray01[i] + USART_CR2);
        TestAssert((USART_CR2_LINEN & ulReadVal) == USART_CR2_LINEN, "xuart API error!");
    }
    
    for(i=0; i<3; i++)
    {
        UARTDisableLIN(ulBaseArray01[i]);
        ulReadVal = xHWREG(ulBaseArray01[i] + USART_CR2);
        TestAssert((USART_CR2_LINEN & ulReadVal) == 0, "xuart API error!");
    }

    for(i=0; i<3; i++)
    {
        UARTLINConfig(ulBaseArray01[i], 115200, UART_CONFIG_BKFL_10);
        ulReadVal = xHWREG(ulBaseArray01[i] + USART_CR2);
        TestAssert((UART_CONFIG_BKFL_10 & ulReadVal) == UART_CONFIG_BKFL_10, "xuart API error!");
    }
    
    for(i=0; i<3; i++)
    {
        UARTLINConfig(ulBaseArray01[i], 115200, UART_CONFIG_BKFL_11);
        ulReadVal = xHWREG(ulBaseArray01[i] + USART_CR2);
        TestAssert((UART_CONFIG_BKFL_11 & ulReadVal) == UART_CONFIG_BKFL_11, "xuart API error!");
    }

}
//*****************************************************************************
//
//! xuart002 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart002Execute(void)
{
    //
    // Synchronous mode config Test
    //
    xuart002Execute_SyncConfig();
    //
    // Lin mode config Test
    //
    xuart002Execute_LinConfig();

}

//
// xuart FIFO test case struct.
//
const tTestCase sTestxuart001UART01 = {
    xuart002GetTest,
    xuart002Setup,
    xuart002TearDown,
    xuart002Execute
};

//
// xuart test suits.
//
const tTestCase * const psPatternxUART01[] =
{
    &sTestxuart001UART01,
    0
};

