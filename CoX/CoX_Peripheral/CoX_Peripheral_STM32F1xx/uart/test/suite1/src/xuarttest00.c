//*****************************************************************************
//
//! @page xuart_testcase xuart test
//!  
//! File: @ref xuart_testcase.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the xuart sub component.<br><br>
//! - \p Board: MiniSTM32V100 <br><br>
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

void xuart001Execute_NormalConfig(void);

void xuart001Execute_FIFOConfig(void);


#define countof(x) sizeof(x)/sizeof(*x)

//
// line config test value
//
unsigned long wordLength[] = {UART_CONFIG_WLEN_9,UART_CONFIG_WLEN_8};

unsigned long ulBaseArray[] = {USART1_BASE, USART2_BASE, USART3_BASE, USART4_BASE, USART5_BASE};

unsigned long parity[] = {UART_CONFIG_PAR_NONE,UART_CONFIG_PAR_EVEN,
                          UART_CONFIG_PAR_ODD};

unsigned long stopbit[] = {UART_CONFIG_STOP_ONE, UART_CONFIG_STOP_TWO, 
                           UART_CONFIG_STOP_0P5, UART_CONFIG_STOP_1P5};

unsigned long ulBlock[] = {UART_BLOCK_TX, UART_BLOCK_RX, UART_BLOCK_UART};

unsigned long ulGuardTime[] = {0, 10, 20, 50 , 127, 255};
unsigned long ulAddr[] = {15, 1, 7, 8, 11, 0};

unsigned long ulInt[] = {UART_INT_LIN, UART_INT_ERR, UART_INT_CTS, UART_INT_PE,  
                         UART_INT_TC, UART_INT_IDLE, UART_INT_TXE, UART_INT_RXNE};

//*****************************************************************************
//
//! Get the Test description of xuart001  test.
//!
//! \return the desccription of the xuart001 test.
//
//*****************************************************************************
static char* xuart001GetTest(void)
{
    return "xuart [001]: xuart uart Config test";
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
    SysCtlPeripheralReset(SYSCTL_PERIPH_USART1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_USART2);
    SysCtlPeripheralReset(SYSCTL_PERIPH_USART3);
    SysCtlPeripheralReset(SYSCTL_PERIPH_UART4);
    SysCtlPeripheralReset(SYSCTL_PERIPH_UART5);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_USART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USART2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USART3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
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
    xUARTConfigSet(USART2_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART2_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
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
    int w, p, s,w1, p1, s1, i, j;
    unsigned long ulTemp1, ulStop;
    
    w1 = countof(wordLength);
    p1 = countof(parity);
    s1 = countof(stopbit);  

    //
    // the combined test of word length,parity and stop bit.
    //
    for(i=0; i<3; i++)
    {
        for(w=0; w<w1; w++)
        {
            for(p=0; p<p1; p++)
            {   
                UARTParityModeSet(ulBaseArray[i], parity[p]);
                ulTemp1 = UARTParityModeGet(ulBaseArray[i]);
                TestAssert(parity[p] == ulTemp1, "xuart API error!");
    
                for(s=0; s<s1; s++)
                {
                    ulTemp1 = (wordLength[w] | parity[p] | stopbit[s]);
                    UARTConfigSet(ulBaseArray[i], 115200, ulTemp1);
                    ulStop = xHWREG(ulBaseArray[i] + USART_CR2);
                    TestAssert((stopbit[s] & ulStop) == stopbit[s], "xuart API error!");
                    ulTemp1 = xHWREG(ulBaseArray[i] + USART_CR1);
                    TestAssert(((wordLength[w] | parity[p]) & ulTemp1) == (wordLength[w] | parity[p]),
                               "xuart API error!");
                }
            } 
        }
    }
    
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            UARTEnable(ulBaseArray[i], ulBlock[j]);
            ulTemp1 = xHWREG(ulBaseArray[i] + USART_CR1);
            TestAssert((ulBlock[j] & ulTemp1) == ulBlock[j], "xuart API error!");
        }
        for(j=0; j<3; j++)
        {
            UARTDisable(ulBaseArray[i], ulBlock[j]);
            ulTemp1 = xHWREG(ulBaseArray[i] + USART_CR1);
            TestAssert((ulBlock[j] & ulTemp1) == 0, "xuart API error!");
        }
    }
    
    for(i=0; i<3; i++)
    {
        UARTBreakCtl(ulBaseArray[i]);
        ulTemp1 = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((USART_CR1_SBK & ulTemp1) == USART_CR1_SBK, "xuart API error!");
    }


}
//*****************************************************************************
//
//! !brief xuart 001 test for fifo config.
//!
//! \return None.
//
//*****************************************************************************
void xuart001Execute_Config(void)
{
    int i, j, ulReadVal;
    
    //
    //Guard time set Test
    //
    for(i=0; i<3; i++)
    {
        for(j=0; j<6; j++)
        {
            UARTGuardTimeSet(ulBaseArray[i], ulGuardTime[j]);
            
            ulReadVal = xHWREG(ulBaseArray[i] + USART_GTPR);
            TestAssert(((ulReadVal&USART_GTPR_GT_M) >>8 ) == ulGuardTime[j], "xuart API error!");
        }

    }
    //
    // Smartcard mode set test
    //
    for(i=0; i<3; i++)
    {
        UARTSmartCardEnable(ulBaseArray[i], UART_SC_TX);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_SCEN) == USART_CR3_SCEN, "xuart API error!");
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR2);
        TestAssert((ulReadVal&USART_CR2_STOP_05) == USART_CR2_STOP_05, "xuart API error!");
        
        UARTSmartCardEnable(ulBaseArray[i], UART_SC_RX);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_SCEN) == USART_CR3_SCEN, "xuart API error!");
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR2);
        TestAssert((ulReadVal&USART_CR2_STOP_15) == USART_CR2_STOP_15, "xuart API error!");
        
        UARTSmartCardDisable(ulBaseArray[i]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_SCEN) == 0, "xuart API error!");
    }
    
    for(i=0; i<3; i++)
    {
        UARTHalfDuplexEnable(ulBaseArray[i]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_HDSEL) == USART_CR3_HDSEL, "xuart API error!");
        
        UARTHalfDuplexDisable(ulBaseArray[i]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_HDSEL) == 0, "xuart API error!");
    }
    
    for(i=0; i<3; i++)
    {
        UARTWakeUpConfig(ulBaseArray[i], UART_WAKEUP_IDLE);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&UART_WAKEUP_IDLE) == UART_WAKEUP_IDLE, "xuart API error!");
        
        UARTWakeUpConfig(ulBaseArray[i], UART_WAKEUP_ADDRESS);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&UART_WAKEUP_ADDRESS) == UART_WAKEUP_ADDRESS, "xuart API error!");
    }
    
    //
    // Multiprocessor Communication address set Test
    //
    for(i=0; i<3; i++)
    {
        for(j=0; j<6; j++)
        {
            UARTAddressSet(ulBaseArray[i], ulAddr[j]);
            ulReadVal = xHWREG(ulBaseArray[i] + USART_CR2);
            TestAssert((ulReadVal&USART_CR2_ADD_M) == ulAddr[j], "xuart API error!");
        }
    }
    
    //
    // Interrupt enable Test
    //
    for(i=0; i<3; i++)
    {
        //
        // LIN interrupt
        //

        UARTIntEnable(ulBaseArray[i], ulInt[0]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR2);
        TestAssert((ulReadVal&USART_CR2_LBDIE) == USART_CR2_LBDIE, "xuart API error!");

        UARTIntEnable(ulBaseArray[i], ulInt[1]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_EIE) == USART_CR3_EIE, "xuart API error!");

        UARTIntEnable(ulBaseArray[i], ulInt[2]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_CTSIE) == USART_CR3_CTSIE, "xuart API error!");

        UARTIntEnable(ulBaseArray[i], ulInt[3]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_PEIE) == USART_CR1_PEIE, "xuart API error!");
        
        UARTIntEnable(ulBaseArray[i], ulInt[4]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_TCIE) == USART_CR1_TCIE, "xuart API error!");
        
        UARTIntEnable(ulBaseArray[i], ulInt[5]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_IDLEIE) == USART_CR1_IDLEIE, "xuart API error!");
        
        UARTIntEnable(ulBaseArray[i], ulInt[6]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_TXEIE) == USART_CR1_TXEIE, "xuart API error!");
        
        UARTIntEnable(ulBaseArray[i], ulInt[7]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_RXNEIE) == USART_CR1_RXNEIE, "xuart API error!");
        

        UARTIntDisable(ulBaseArray[i], ulInt[0]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR2);
        TestAssert((ulReadVal&USART_CR2_LBDIE) == 0, "xuart API error!");

        UARTIntDisable(ulBaseArray[i], ulInt[1]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_EIE) == 0, "xuart API error!");

        UARTIntDisable(ulBaseArray[i], ulInt[2]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR3);
        TestAssert((ulReadVal&USART_CR3_CTSIE) == 0, "xuart API error!");

        UARTIntDisable(ulBaseArray[i], ulInt[3]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_PEIE) == 0, "xuart API error!");
        
        UARTIntDisable(ulBaseArray[i], ulInt[4]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_TCIE) == 0, "xuart API error!");
        
        UARTIntDisable(ulBaseArray[i], ulInt[5]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_IDLEIE) == 0, "xuart API error!");
        
        UARTIntDisable(ulBaseArray[i], ulInt[6]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_TXEIE) == 0, "xuart API error!");
        
        UARTIntDisable(ulBaseArray[i], ulInt[7]);
        ulReadVal = xHWREG(ulBaseArray[i] + USART_CR1);
        TestAssert((ulReadVal&USART_CR1_RXNEIE) == 0, "xuart API error!");

    }
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
    xuart001Execute_Config();

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

