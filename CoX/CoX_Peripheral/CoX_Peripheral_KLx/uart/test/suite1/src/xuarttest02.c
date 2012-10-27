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

//
// UART Port select
// first, you can set UART_BASE to UART1_BASE
// then set to UART2_BASE, so you can test UART1 and UART2
// However , UART1 is identical with UART2, so test one of them is OK.
//
#define UART_BASE UART2_BASE

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
//! Get the Test description of xuart0201  test.
//!
//! \return the desccription of the xuart0201 test.
//
//*****************************************************************************
static char* xuart0201GetTest(void)
{
    return "UART 0201 : UARTConfigSet test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0201 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0201Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART2_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0201 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0201TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART2_EN);
}


//*****************************************************************************
//
//! xuart0201 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0201Execute(void)
{
    unsigned char ucTmpReg = 0;

    //
    // Test UARTConfigSet function for set chars length/parity/stop_bit
    //


    //
    // Length test.
    //
    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_WLEN_8);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);
    TestAssert((0 == ucTmpReg),
            "UART 0201: set wlen8 failed!\r\n");

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_WLEN_9);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);
    TestAssert((0 != ucTmpReg),
            "UART 0201: set wlen9 failed!\r\n");

    //
    // Parity test.
    //
    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_PAR_ODD );
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<0);
    TestAssert((0 != ucTmpReg),
            "UART 0201: set parity odd failed!\r\n");
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<1);
    TestAssert((0 != ucTmpReg),
            "UART 0201: set parity odd failed!\r\n");  

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_PAR_EVEN);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<0);
    TestAssert((0 == ucTmpReg),
            "UART 0201: set parity even failed!\r\n");
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<1);
    TestAssert((0 != ucTmpReg),
            "UART 0201: set parity even failed!\r\n");  

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_PAR_NONE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<1);
    TestAssert((0 == ucTmpReg),
            "UART 0201: set parity none failed!\r\n");  
    //
    // Stop bit test.
    //
    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_STOP_1);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);
    TestAssert((0 == ucTmpReg),
            "UART 0201: set one stop bit failed!\r\n");  

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_STOP_2);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);
    TestAssert((0 != ucTmpReg),
            "UART 0201: set two stop bit failed!\r\n");  
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0201 = {
    xuart0201GetTest,
    xuart0201Setup,
    xuart0201TearDown,
    xuart0201Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart0202  test.
//!
//! \return the desccription of the xuart0202 test.
//
//*****************************************************************************
static char* xuart0202GetTest(void)
{
    return "UART 0202 : UARTIntEnable/Disable test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0202 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0202Setup(void)
{
    //Null
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART2_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0202 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0202TearDown(void)
{
    //Null
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART2_EN);
}


//*****************************************************************************
//
//! xuart0202 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0202Execute(void)
{
    unsigned char ucTmpReg = 0;

    //
    // =======BDH========
    // LBKDIE  7
    // RXEDGIE 6
    //
    UARTIntEnable(UART_BASE, UART_INT_LBKD);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<7);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable LBKD failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_LBKD);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<7);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable LBKD failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_RXEDG);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<6);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable RXEDG failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_RXEDG);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<6);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable RXEDG failed!\r\n");

    //
    // =======C2=========
    // TIE  7
    // TCIE 6
    // RIE  5
    // ILIE 4
    //
    UARTIntEnable(UART_BASE, UART_INT_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<7);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable T failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<7);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable T failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_TC);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<6);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable TC failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_TC);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<6);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable TC failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<5);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable R failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<5);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable R failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_IL);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<4);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable IL failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_IL);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C2) & (1<<4);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable IL failed!\r\n");

    //
    // ========C3========
    // ORIE  3
    // NEIE  2
    // FEIE  1
    // PEIE  0
    //
    UARTIntEnable(UART_BASE, UART_INT_OR);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<3);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable OR failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_OR);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<3);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable OR failed!\r\n"); 

    UARTIntEnable(UART_BASE, UART_INT_NE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<2);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable NE failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_NE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<2);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable NE failed!\r\n"); 

    UARTIntEnable(UART_BASE, UART_INT_FE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<1);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable FE failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_FE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<1);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable FE failed!\r\n"); 

    UARTIntEnable(UART_BASE, UART_INT_PE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<0);
    TestAssert((0 != ucTmpReg),
            "UART 0202: Int Enable PE failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_PE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1<<0);
    TestAssert((0 == ucTmpReg),
            "UART 0202: Int Disable PE failed!\r\n"); 
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0202 = {
    xuart0202GetTest,
    xuart0202Setup,
    xuart0202TearDown,
    xuart0202Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0203  test.
//!
//! \return the desccription of the xuart0203 test.
//
//*****************************************************************************
static char* xuart0203GetTest(void)
{
    return "UART 0203 : LIN function test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0203 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0203Setup(void)
{
    //Null
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART2_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0203 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0203TearDown(void)
{
    //Null
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART2_EN);
}

//*****************************************************************************
//
//!  Test for function: UARTLINConfig
//
//! \return None.
//
//*****************************************************************************
static void Test_UARTLINConfig(void)
{
    unsigned char ucTmpReg = 0;

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_10);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1<<2);   //BRK13
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);  //SBNS
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_11);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1<<2);   //BRK13
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_12);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1<<2);   //BRK13
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);   //M
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_13);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1<<2);   //BRK13
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);  //SBNS
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_14);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1<<2);   //BRK13
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_15);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1<<2);   //BRK13
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1<<4);   //M
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_12_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Config 10 failed!\r\n"); 

}

static void Test_UARTLINEnable_Disable(void)
{
    unsigned char ucTmpReg = 0;

    //
    // LIN Enable Test
    //
    UARTLINEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1 << 1);
    TestAssert((0 != ucTmpReg),
            "UART 0203: LIN Enable failed!\r\n"); 

    //
    // LIN Disable Test
    //
    UARTLINDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1 << 1);
    TestAssert((0 == ucTmpReg),
            "UART 0203: LIN Enable failed!\r\n"); 

}

//*****************************************************************************
//
//! xuart0203 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0203Execute(void)
{
    Test_UARTLINConfig();
    Test_UARTLINEnable_Disable();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0203 = {
    xuart0203GetTest,
    xuart0203Setup,
    xuart0203TearDown,
    xuart0203Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0204  test.
//!
//! \return the desccription of the xuart0204 test.
//
//*****************************************************************************
static char* xuart0204GetTest(void)
{
    return "UART 0204 : DMA Enable/Disable test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0204 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0204Setup(void)
{
    //Null
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART2_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0204 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0204TearDown(void)
{
    //Null
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART2_EN);
}


//*****************************************************************************
//
//! xuart0204 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0204Execute(void)
{
    unsigned char ucTmpReg = 0;
    
    //
    // Test for DMA Transmit register empty
    //
    UARTDMAEnable(UART_BASE, UART_DMA_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 7);
    TestAssert((0 != ucTmpReg),
            "UART 0204: DMA Enable failed!\r\n"); 
    UARTDMADisable(UART_BASE, UART_DMA_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 7);
    TestAssert((0 == ucTmpReg),
            "UART 0204: DMA Disable failed!\r\n"); 

    //
    // Test for DMA Transmit complete
    //
    UARTDMAEnable(UART_BASE, UART_DMA_TC);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 6);
    TestAssert((0 != ucTmpReg),
            "UART 0204: DMA Enable failed!\r\n"); 
    UARTDMADisable(UART_BASE, UART_DMA_TC);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 6);
    TestAssert((0 == ucTmpReg),
            "UART 0204: DMA Disable failed!\r\n"); 

    //
    // Test for DMA Receive register full
    //
    UARTDMAEnable(UART_BASE, UART_DMA_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 5);
    TestAssert((0 != ucTmpReg),
            "UART 0204: DMA Enable failed!\r\n"); 
    UARTDMADisable(UART_BASE, UART_DMA_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 5);
    TestAssert((0 == ucTmpReg),
            "UART 0204: DMA Disable failed!\r\n"); 

    //
    // Test for DMA Idle Line detect
    //
    UARTDMAEnable(UART_BASE, UART_DMA_IDLE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 4);
    TestAssert((0 != ucTmpReg),
            "UART 0204: DMA Enable failed!\r\n"); 
    UARTDMADisable(UART_BASE, UART_DMA_IDLE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 4);
    TestAssert((0 == ucTmpReg),
            "UART 0204: DMA Disable failed!\r\n"); 

    //
    // Test for DMA LIN Break
    //
    UARTDMAEnable(UART_BASE, UART_DMA_LBKD);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 3);
    TestAssert((0 != ucTmpReg),
            "UART 0204: DMA Enable failed!\r\n"); 
    UARTDMADisable(UART_BASE, UART_DMA_LBKD);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C4) & (1 << 3);
    TestAssert((0 == ucTmpReg),
            "UART 0204: DMA Disable failed!\r\n"); 

}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0204 = {
    xuart0204GetTest,
    xuart0204Setup,
    xuart0204TearDown,
    xuart0204Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0205  test.
//!
//! \return the desccription of the xuart0205 test.
//
//*****************************************************************************
static char* xuart0205GetTest(void)
{
    return "UART 0205 : Invert Enable/Disable test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0205 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0205Setup(void)
{
    //Null
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART2_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0205 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0205TearDown(void)
{
    //Null
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART2_EN);
}


//*****************************************************************************
//
//! xuart0205 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0205Execute(void)
{
    unsigned char ucTmpReg = 0;
    
    //
    // Test for Tx Invert Enable/Diable
    //
    UARTTxInvertEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1 << 4);
    TestAssert((0 != ucTmpReg),
            "UART 0205: Tx Invert Enable failed!\r\n"); 
    UARTTxInvertDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C3) & (1 << 4);
    TestAssert((0 == ucTmpReg),
            "UART 0205: Tx Invert Disable failed!\r\n"); 

    //
    // Test for Rx Invert Enable/Diable
    //
    UARTRxInvertEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1 << 4);
    TestAssert((0 != ucTmpReg),
            "UART 0205: Rx Invert Enable failed!\r\n"); 
    UARTRxInvertDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_S2) & (1 << 4);
    TestAssert((0 == ucTmpReg),
            "UART 0205: Rx Invert Disable failed!\r\n"); 
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0205 = {
    xuart0205GetTest,
    xuart0205Setup,
    xuart0205TearDown,
    xuart0205Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0206  test.
//!
//! \return the desccription of the xuart0206 test.
//
//*****************************************************************************
static char* xuart0206GetTest(void)
{
    return "UART 0206 : OutMode test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0206 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0206Setup(void)
{
    //Null
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART2_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0206 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0206TearDown(void)
{
    //Null
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART2_EN);
}


//*****************************************************************************
//
//! Test for function: OuntModeConfig
//
//! \return None.
//
//*****************************************************************************
static void Test_OutModeConfig(void)
{
    //
    // Test for UART Mode
    // C1                 LOOPS(7)     RSRC(5)
    // 1: Normal            0            x
    // 2: Single-line       1            1
    // 3: Loops             1            0
    //
    unsigned char Mask     = 0xA0;
    unsigned char ucTmpReg = 0;

    //
    // Normal
    //
    UARTOutModeConfig(UART_BASE, UART_MODE_NORMAL);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & Mask;
    TestAssert((0x00 == ucTmpReg),
            "UART 0206: OutMode Normal failed!\r\n"); 

    //
    // Single line
    //
    UARTOutModeConfig(UART_BASE, UART_MODE_SINGLE_LINE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & Mask;
    TestAssert((0xA0 == ucTmpReg),
            "UART 0206: OutMode Single line failed!\r\n"); 

    //
    // Loops
    //
    UARTOutModeConfig(UART_BASE, UART_MODE_LOOP);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & Mask;
    TestAssert((0x80 == ucTmpReg),
            "UART 0206: OutMode Loops failed!\r\n"); 
}


//*****************************************************************************
//
//! Test for function: UARTWaitModeRun/Stop and wakeup method
//
//! \return None.
//
//*****************************************************************************
static void Test_WaitMode(void)
{
    unsigned char ucTmpReg = 0;
    //
    // UART run in wait mode.
    //
    UARTWaitModeRun(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1 << 6);
    TestAssert((0 == ucTmpReg),
            "UART 0206: Mode run failed!\r\n"); 

    //
    // UART stop in wait mode.
    //
    UARTWaitModeStop(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1 << 6);
    TestAssert((0 != ucTmpReg),
            "UART 0206: Mode stop failed!\r\n"); 

    //
    // Wakeup method test.
    //
    UARTWakeupMethodConfig(UART_BASE, UART_WAKEUP_IDLE_LINE);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1 << 3);
    TestAssert((0 == ucTmpReg),
            "UART 0206: Wakeup Mode idle line failed!\r\n"); 

    UARTWakeupMethodConfig(UART_BASE, UART_WAKEUP_ADDRESS_MARK);
    ucTmpReg = xHWREGB(UART_BASE + UART_12_C1) & (1 << 3);
    TestAssert((0 != ucTmpReg),
            "UART 0206: Wakeup Mode address mark failed!\r\n"); 

}

//*****************************************************************************
//
//! xuart0206 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0206Execute(void)
{
    Test_OutModeConfig();
    Test_WaitMode();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0206 = {
    xuart0206GetTest,
    xuart0206Setup,
    xuart0206TearDown,
    xuart0206Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0207  test.
//!
//! \return the desccription of the xuart0207 test.
//
//*****************************************************************************
static char* xuart0207GetTest(void)
{
    return "UART 0207 : UARTConfigSet test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0207 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0207Setup(void)
{
    //Null
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART2_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0207 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0207TearDown(void)
{
    //Null
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART2_EN);
}

//*****************************************************************************
//
//! xuart0207 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0207Execute(void)
{

}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0207 = {
    xuart0207GetTest,
    xuart0207Setup,
    xuart0207TearDown,
    xuart0207Execute
};    

//
// xuart test suits.
//
const tTestCase * const psPatternxUART02[] =
{
    &sTestxuart0201,
    &sTestxuart0202,
    &sTestxuart0203,
    &sTestxuart0204,
    &sTestxuart0205,
    &sTestxuart0206,
    &sTestxuart0207,
    0
};

