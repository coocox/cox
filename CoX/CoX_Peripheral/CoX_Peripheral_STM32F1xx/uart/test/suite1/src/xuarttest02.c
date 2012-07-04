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


unsigned long ulBaseArray02[] = {USART1_BASE, USART2_BASE, USART3_BASE,
                                 USART4_BASE, USART5_BASE};
//
// IrDA configuration test
//
void  xuart001Execute_IrDAConfig(void);

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
    xUARTConfigSet(USART2_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART2_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
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
     unsigned long i, ulReadVal;

    //
	// IrDA configure test.
	//
     
    for(i=0; i<3; i++)
    {
        UARTEnableIrDA(ulBaseArray02[i]);
        ulReadVal = xHWREG(ulBaseArray02[i] + USART_CR3);
        TestAssert((USART_CR3_IREN & ulReadVal) == USART_CR3_IREN, "xuart API error!");
    }
    
    for(i=0; i<3; i++)
    {
        UARTDisableIrDA(ulBaseArray02[i]);
        ulReadVal = xHWREG(ulBaseArray02[i] + USART_CR3);
        TestAssert((USART_CR3_IREN & ulReadVal) == 0, "xuart API error!");
    }

    for(i=0; i<3; i++)
    {
        UARTIrDAConfig(ulBaseArray02[i], 115200, (UART_CONFIG_WLEN_8 |
                       UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE), UART_IRDA_MODE_LPM, 128);
        
        ulReadVal = xHWREG(ulBaseArray02[i] + USART_CR3);
        TestAssert((USART_CR3_IRLP & ulReadVal) == USART_CR3_IRLP, "xuart API error!");
        
        ulReadVal = xHWREG(ulBaseArray02[i] + USART_GTPR);
        TestAssert((USART_GTPR_PSC_M & ulReadVal) == 128, "xuart API error!");
    }
    
    for(i=0; i<3; i++)
    {
        UARTIrDAConfig(ulBaseArray02[i], 115200, (UART_CONFIG_WLEN_8 |
                       UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE), UART_IRDA_MODE_NORMAL, 1);
        ulReadVal = xHWREG(ulBaseArray02[i] + USART_CR3);
        TestAssert((USART_CR3_IRLP & ulReadVal) == 0, "xuart API error!");
        ulReadVal = xHWREG(ulBaseArray02[i] + USART_GTPR);
        TestAssert((USART_GTPR_PSC_M & ulReadVal) == 1, "xuart API error!");
    }
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

