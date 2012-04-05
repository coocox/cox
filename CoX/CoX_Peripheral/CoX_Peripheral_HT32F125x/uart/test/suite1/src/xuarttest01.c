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

#define xSYSCTL_PERIPH_UART  xSYSCTL_PERIPH_UART0

unsigned long ulUartMode[] = { USART_FUN_SEL_RS485_EN, USART_FUN_SEL_SYN_EN,
                              USART_FUN_SEL_IRDA_EN	,USART_FUN_SEL_USART_EN};

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
    return "xuart [002]: xuart Synchronous and RS485 mode test";
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
    SysCtlPeripheralEnable(xSYSCTL_PERIPH_UART);
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
    UARTModeSet(UART0_BASE, USART_FUN_SEL_USART_EN);
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
    unsigned long i,ulTemp,ulTemp1,ulTemp2;

    //
    // UART Mode Select Test
    //
    for(i=0; i<4; i++)
	{
	    UARTModeSet(UART0_BASE, ulUartMode[i]);
        ulTemp = xHWREG(UART0_BASE + USART_MDR) & USART_FUN_SEL_M;
        TestAssert(ulTemp == ulUartMode[i], "xuart API error!");
	}
    
    ulTemp1 = USART_SYNCR_CLK_EN ;
    UARTSyncModeConfig(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                            UART_CONFIG_STOP_ONE | 
                                            UART_CONFIG_PAR_NONE), ulTemp1);
    ulTemp2 = xHWREG(UART0_BASE + USART_SYNCR);
    TestAssert(ulTemp1 == ulTemp2, "xuart API error!");
/*
    ulTemp1 = USART_SYNCR_CPS_S | USART_SYNCR_CPO_H;
    UARTSyncModeConfig(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                            UART_CONFIG_STOP_ONE | 
                                            UART_CONFIG_PAR_NONE), ulTemp1);
    ulTemp2 = xHWREG(UART0_BASE + USART_SYNCR);
    TestAssert(ulTemp1 == ulTemp2, "xuart API error!");

    ulTemp1 = ~(USART_SYNCR_CLK_EN | USART_SYNCR_CPS_S | USART_SYNCR_CPO_H);
    UARTSyncModeConfig(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                            UART_CONFIG_STOP_ONE | 
                                            UART_CONFIG_PAR_NONE), ulTemp1);
    ulTemp2 = xHWREG(UART0_BASE + USART_SYNCR);
    ulTemp1 = ulTemp1 & 0x0000000D | (~ulTemp1);
    TestAssert(ulTemp1 == ulTemp2, "xuart API \"UARTIrDAConfig\" error!");
*/
}

//*****************************************************************************
//
//! !brief xuart 001 test for Synchronous mode config.
//!
//! \return None.
//
//*****************************************************************************
void xuart002Execute_RS485Config(void)
{	  
    unsigned long ulWriteVal,ulReadVal;

    //
	// RS485 configure test.
	//
	ulWriteVal =  USART_RS485CR_TXEN;
    UART485Config(UART0_BASE, 115200, ulWriteVal, (UART_CONFIG_WLEN_8 | 
                                                   UART_CONFIG_STOP_ONE | 
                                                   UART_CONFIG_PAR_NONE));
	ulReadVal = xHWREG(UART0_BASE + USART_RS485CR);
    TestAssert(ulWriteVal == ulReadVal, "xuart API error!");

	ulWriteVal =  USART_RS485CR_TXEP;
    UART485Config(UART0_BASE, 115200, ulWriteVal, (UART_CONFIG_WLEN_8 | 
                                                   UART_CONFIG_STOP_ONE | 
                                                   UART_CONFIG_PAR_NONE));
	ulReadVal = xHWREG(UART0_BASE + USART_RS485CR);
    TestAssert(ulWriteVal == ulReadVal, "xuart API error!");
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
    // Synchronous mode config
    //
    xuart002Execute_SyncConfig();

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

