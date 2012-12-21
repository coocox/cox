//*****************************************************************************
//
//! @page xuart_testcase xuart test
//!  
//! File: @ref xuart_testcase.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the xuart sub component.<br><br>
//! - \p Board: HT32F175x <br><br>
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

void xuart001Execute_NormalConfig(void);

void xuart001Execute_FIFOConfig(void);


#define countof(x) sizeof(x)/sizeof(*x)

//
// line config test value
//
unsigned long wordLength[] = {UART_CONFIG_WLEN_9,UART_CONFIG_WLEN_8, 
                              UART_CONFIG_WLEN_7};

unsigned long parity[] = {UART_CONFIG_PAR_NONE,UART_CONFIG_PAR_EVEN,
                          UART_CONFIG_PAR_ODD, UART_CONFIG_PAR_ONE,
                          UART_CONFIG_PAR_ZERO};

unsigned long stopbit[] = {UART_CONFIG_STOP_ONE,UART_CONFIG_STOP_TWO};

unsigned long ulBlock[] = {UART_BLOCK_TX, UART_BLOCK_RX};

//
// FIFO test value
//
unsigned long ulRxLevel[] = {UART_FIFO_1BYTES, UART_FIFO_4BYTES, 
                             UART_FIFO_8BYTES, UART_FIFO_14BYTES};

#define  fifoLevelNum   countof(ulRxLevel)

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
static char* xuart001GetTest(void)
{
    return "xuart [001]: xuart uart Config, FIFO test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart001Setup(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart001TearDown(void)
{
    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                             UART_CONFIG_STOP_ONE | 
                                             UART_CONFIG_PAR_NONE));

    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}


//*****************************************************************************
//
//! !brief xuart 001 test for line config.
//!
//! \return None.
//
//*****************************************************************************
void xuart001Execute_NormalConfig(void)
{
    int w, p, s,w1, p1, s1;
    unsigned long ulBuad, ulConfig, ulTemp1;
    
    w1 = countof(wordLength);
    p1 = countof(parity);
    s1 = countof(stopbit);

    //
    // the combined test of word length,parity and stop bit.
    //
    for(w=0; w<w1; w++)
    {
        for(p=0; p<p1; p++)
        {   
            UARTParityModeSet(UART1_BASE, parity[p]);
            ulTemp1 = UARTParityModeGet(UART1_BASE);
            TestAssert(parity[p] == ulTemp1, "xuart API error!");

            for(s=0; s<s1; s++)
            {
                ulTemp1 = (wordLength[w] | parity[p] | stopbit[s]);
                UARTConfigSetExpClk(UART1_BASE, 115200, ulTemp1);     
                UARTConfigGetExpClk(UART1_BASE, &ulBuad, &ulConfig);
                TestAssert((ulConfig & ulTemp1) == ulTemp1, "xuart API error!");
            }
        } 
    }
    
    //
    // Break Control test
    //
    UARTBreakCtl(UART1_BASE, xtrue);
    ulTemp1 = xHWREG(UART1_BASE + USART_LCR) & USART_LCR_BCB;
    TestAssert(ulTemp1 == USART_LCR_BCB, "xuart API \"UARTBreakCtl\" error!");
    
    UARTBreakCtl(UART1_BASE, xfalse);
    ulTemp1 = xHWREG(UART1_BASE + USART_LCR_BCB) & USART_LCR_BCB;
    TestAssert(ulTemp1 == 0,  "xuart API \"UARTBreakCtl\" error!");

}
//*****************************************************************************
//
//! !brief xuart 001 test for fifo config.
//!
//! \return None.
//
//*****************************************************************************
void xuart001Execute_FIFOConfig(void)
{
    unsigned long ulTemp1;
	xtBoolean xtTemp = xfalse;
    int i;
    
    //
    // test for rx trigger level config
    //
    for(i=0; i<fifoLevelNum; i++)
    {
        UARTFIFOTriggerLevelSet(UART1_BASE, ulRxLevel[i]); 
        ulTemp1 = UARTFIFOTriggerLevelGet(UART1_BASE);
        TestAssert(ulTemp1 == ulRxLevel[i], "xuart API error!");
    }

    //
    // reset rx and tx fifo
    //
    xHWREG(UART1_BASE + USART_FCR) = USART_FCR_RX_RST | USART_FCR_TX_RST;

    SysCtlDelay(100000);
	xtTemp = UARTFIFOTxIsEmpty(UART1_BASE);

    TestAssert(xtTemp == xtrue, "xuart API error!");

	xtTemp = UARTFIFORxIsEmpty(UART1_BASE);

    TestAssert(xtTemp == xtrue, "xuart API error!");


}

//*****************************************************************************
//
//! xuart001 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart001Execute(void)
{
    //
    // Line configuration test
    //
    xuart001Execute_NormalConfig();
    //
    // FIFO configuration test
    //
    xuart001Execute_FIFOConfig();

}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart001UART00 = {
    xuart001GetTest,
    xuart001Setup,
    xuart001TearDown,
    xuart001Execute
};

//
// xuart test suits.
//
const tTestCase * const psPatternxUART00[] =
{
    &sTestxuart001UART00,
    0
};

