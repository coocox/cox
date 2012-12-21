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


void xuart006Execute_ModemConfig(void);

#define countof(x) sizeof(x)/sizeof(*x)

//
// Modem test value
//
unsigned long ulModemCfg[] = {USART_MCR_DTR_L, USART_MCR_DTR_H, USART_MCR_RTS_L,USART_MCR_RTS_H,
                              (USART_MCR_DTR_L | USART_MCR_RTS_L), 
                              (USART_MCR_RTS_L | USART_MCR_DTR_H)};

#define  modemCfgNum      countof(ulModemCfg)

unsigned long ulModemSt[] = {USART_MCR_DTR_L, USART_MCR_RTS_H};

#define  modemStNum      countof(ulModemSt)

#define  DMACfgNum       countof(ulDMACfg)


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
//! Get the Test description of xuart006  test.
//!
//! \return the desccription of the xuart006 test.
//
//*****************************************************************************
static char* xuart004GetTest(void)
{
    return "xuart [004]: xuart Modem test";
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
    
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    
    //
    // Set RTS Trigger Level
    //
    for(i=0; i<modemCfgNum; i++)
    {
        UARTModemControlSet(UART0_BASE, ulModemCfg[i]);
        ulTemp1 = UARTModemControlGet(UART0_BASE); 
        TestAssert(ulTemp1 == (ulModemCfg[i] | 0x02), "xuart API error!");   
    }

    UARTDMAModeEnable(UART0_BASE, USART_DMA_RX);
    ulTemp1 = xHWREG(UART0_BASE + USART_MDR);
    TestAssert(USART_DMA_RX == (ulTemp1 & USART_DMA_RX), "xuart API error!");
	
    UARTDMAModeEnable(UART0_BASE, USART_DMA_TX);
    ulTemp1 = xHWREG(UART0_BASE + USART_MDR);
    TestAssert(USART_DMA_TX == (ulTemp1 & USART_DMA_TX), "xuart API error!");
	
    UARTDMAModeDisable(UART0_BASE, USART_DMA_RX);
    ulTemp1 = xHWREG(UART0_BASE + USART_MDR);
    TestAssert(0 == (ulTemp1 & USART_DMA_RX), "xuart API error!");
	
    UARTDMAModeDisable(UART0_BASE, USART_DMA_TX);
    ulTemp1 = xHWREG(UART0_BASE + USART_MDR);
    TestAssert(0 == (ulTemp1 & USART_DMA_TX), "xuart API error!");
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
