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

#define UART_BASE UART0_BASE

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
//! Get the Test description of xuart0101  test.
//!
//! \return the desccription of the xuart0101 test.
//
//*****************************************************************************
static char* xuart0101GetTest(void)
{
    return "UART 0101 : UARTConfigSet test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0101 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0101Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART0_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0101 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0101TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
}


//*****************************************************************************
//
//! xuart0101 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0101Execute(void)
{
    unsigned char ucTmpReg = 0;

    //
    // Test UARTConfigSet function for set chars length/parity/stop_bit
    //

    //
    // Length test.
    //
    UARTConfigSet(UART0_BASE, UART_BAUD, UART_CONFIG_WLEN_8);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);
    TestAssert((0 == ucTmpReg),
            "UART 0101: set wlen8 failed!\r\n");
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);
    TestAssert((0 == ucTmpReg),
            "UART 0101: set wlen8 failed!%x\r\n", xHWREGB(UART_BASE + UART_0_C4));

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_WLEN_9  );
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);
    TestAssert((0 != ucTmpReg),
            "UART 0101: set wlen9 failed!\r\n");
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);
    TestAssert((0 == ucTmpReg),
            "UART 0101: set wlen9 failed!\r\n");

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_WLEN_10 );
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);
    TestAssert((0 != ucTmpReg),
            "UART 0101: set wlen10 failed!\r\n");

    //
    // Parity test.
    //
    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_PAR_ODD );
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<0);
    TestAssert((0 != ucTmpReg),
            "UART 0101: set parity odd failed!\r\n");
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<1);
    TestAssert((0 != ucTmpReg),
            "UART 0101: set parity odd failed!\r\n");  

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_PAR_EVEN);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<0);
    TestAssert((0 == ucTmpReg),
            "UART 0101: set parity even failed!\r\n");
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<1);
    TestAssert((0 != ucTmpReg),
            "UART 0101: set parity even failed!\r\n");  

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_PAR_NONE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<1);
    TestAssert((0 == ucTmpReg),
            "UART 0101: set parity none failed!\r\n");  
    //
    // Stop bit test.
    //
    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_STOP_1  );
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);
    TestAssert((0 == ucTmpReg),
            "UART 0101: set one stop bit failed!\r\n");  

    UARTConfigSet(UART_BASE, UART_BAUD, UART_CONFIG_STOP_2  );
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);
    TestAssert((0 != ucTmpReg),
            "UART 0101: set two stop bit failed!   BDH->%x\r\n",
            xHWREGB(UART_BASE + UART_0_BDH));  
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0101 = {
    xuart0101GetTest,
    xuart0101Setup,
    xuart0101TearDown,
    xuart0101Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart0102  test.
//!
//! \return the desccription of the xuart0102 test.
//
//*****************************************************************************
static char* xuart0102GetTest(void)
{
    return "UART 0102 : UARTIntEnable/Disable test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0102 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0102Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART0_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0102 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0102TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
}


//*****************************************************************************
//
//! xuart0102 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0102Execute(void)
{
    unsigned char ucTmpReg = 0;

    //
    // =======BDH========
    // LBKDIE  7
    // RXEDGIE 6
    //
    UARTIntEnable(UART_BASE, UART_INT_LBKD);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<7);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable LBKD failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_LBKD );
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<7);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable LBKD failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_RXEDG);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<6);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable RXEDG failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_RXEDG);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<6);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable RXEDG failed!\r\n");

    //
    // =======C2=========
    // TIE  7
    // TCIE 6
    // RIE  5
    // ILIE 4
    //
    UARTIntEnable(UART_BASE, UART_INT_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<7);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable T failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<7);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable T failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_TC);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<6);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable TC failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_TC);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<6);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable TC failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<5);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable R failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<5);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable R failed!\r\n");

    UARTIntEnable(UART_BASE, UART_INT_IL);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<4);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable IL failed!\r\n");
    UARTIntDisable(UART_BASE, UART_INT_IL);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C2) & (1<<4);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable IL failed!\r\n");

    //
    // ========C3========
    // ORIE  3
    // NEIE  2
    // FEIE  1
    // PEIE  0
    //
    UARTIntEnable(UART_BASE, UART_INT_OR);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<3);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable OR failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_OR);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<3);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable OR failed!\r\n"); 

    UARTIntEnable(UART_BASE, UART_INT_NE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<2);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable NE failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_NE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<2);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable NE failed!\r\n"); 

    UARTIntEnable(UART_BASE, UART_INT_FE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<1);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable FE failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_FE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<1);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable FE failed!\r\n"); 

    UARTIntEnable(UART_BASE, UART_INT_PE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<0);
    TestAssert((0 != ucTmpReg),
            "UART 0102: Int Enable PE failed!\r\n"); 
    UARTIntDisable(UART_BASE, UART_INT_PE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1<<0);
    TestAssert((0 == ucTmpReg),
            "UART 0102: Int Disable PE failed!\r\n"); 
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0102 = {
    xuart0102GetTest,
    xuart0102Setup,
    xuart0102TearDown,
    xuart0102Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0103  test.
//!
//! \return the desccription of the xuart0103 test.
//
//*****************************************************************************
static char* xuart0103GetTest(void)
{
    return "UART 0103 : LIN function test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0103 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0103Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART0_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0103 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0103TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
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
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1<<2);   //BRK13
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 10 failed! S2->%x\r\n", 
            xHWREGB(UART_BASE + UART_0_S2)); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 10 failed! C1->%x\r\n",
            xHWREGB(UART_BASE + UART_0_C1));   
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);   //M10
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 10 failed! C4->%x\r\n",
            xHWREGB(UART_BASE + UART_0_C4)); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);  //SBNS
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 10 failed! BDH->%x\r\n",
            xHWREGB(UART_BASE + UART_0_BDH)); 
  
    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_11);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1<<2);   //BRK13
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 11 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 11 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);   //M10
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 11 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 11 failed! BDH->%x\r\n",
            xHWREGB(UART_BASE + UART_0_BDH)); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_12);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1<<2);   //BRK13
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 12 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);   //M
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 12 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);   //M10
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 12 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 12 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_13);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1<<2);   //BRK13
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 13 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 13 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);   //M10
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 13 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);  //SBNS
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 13 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_14);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1<<2);   //BRK13
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 14 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 14 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);   //M10
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 14 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 14 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_15);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1<<2);   //BRK13
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 15 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);   //M
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 15 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);   //M10
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 15 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 15 failed!\r\n"); 

    UARTLINConfig(UART_BASE, UART_BAUD, UART_LIN_SYNC_BREAK_LEN_16);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1<<2);   //BRK13
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 16 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1<<4);   //M
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Config 16 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1<<5);   //M10
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 16 failed!\r\n"); 
    ucTmpReg = xHWREGB(UART_BASE + UART_0_BDH) & (1<<5);  //SBNS
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Config 16 failed!\r\n"); 

}

static void Test_UARTLINEnable_Disable(void)
{
    unsigned char ucTmpReg = 0;

    //
    // LIN Enable Test
    //
    UARTLINEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1 << 1);
    TestAssert((0 != ucTmpReg),
            "UART 0103: LIN Enable failed!\r\n"); 

    //
    // LIN Disable Test
    //
    UARTLINDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1 << 1);
    TestAssert((0 == ucTmpReg),
            "UART 0103: LIN Enable failed!\r\n"); 

}

//*****************************************************************************
//
//! xuart0103 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0103Execute(void)
{
    Test_UARTLINConfig();
    Test_UARTLINEnable_Disable();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0103 = {
    xuart0103GetTest,
    xuart0103Setup,
    xuart0103TearDown,
    xuart0103Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0104  test.
//!
//! \return the desccription of the xuart0104 test.
//
//*****************************************************************************
static char* xuart0104GetTest(void)
{
    return "UART 0104 : DMA Enable/Disable test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0104 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0104Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART0_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0104 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0104TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
}


//*****************************************************************************
//
//! xuart0104 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0104Execute(void)
{
    unsigned char ucTmpReg = 0;
    //
    // Test for DMA Transmit register empty
    //
    UARTDMAEnable(UART_BASE, UART_DMA_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 7);
    TestAssert((0 != ucTmpReg),
            "UART 0104: DMA Enable failed!\r\n"); 

    UARTDMADisable(UART_BASE, UART_DMA_T);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 7);
    TestAssert((0 == ucTmpReg),
            "UART 0104: DMA Disable failed!\r\n"); 

    //
    // Test for DMA Receive register full
    //
    UARTDMAEnable(UART_BASE, UART_DMA_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 5);
    TestAssert((0 != ucTmpReg),
            "UART 0104: DMA Enable failed!\r\n"); 

    UARTDMADisable(UART_BASE, UART_DMA_R);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 5);
    TestAssert((0 == ucTmpReg),
            "UART 0104: DMA Disable failed!\r\n"); 
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0104 = {
    xuart0104GetTest,
    xuart0104Setup,
    xuart0104TearDown,
    xuart0104Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0105  test.
//!
//! \return the desccription of the xuart0105 test.
//
//*****************************************************************************
static char* xuart0105GetTest(void)
{
    return "UART 0105 : Invert Enable/Disable test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0105 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0105Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART0_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0105 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0105TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
}


//*****************************************************************************
//
//! xuart0105 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0105Execute(void)
{
    unsigned char ucTmpReg = 0;
    //
    // Test for Tx Invert Enable/Diable
    //
    UARTTxInvertEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1 << 4);
    TestAssert((0 != ucTmpReg),
            "UART 0105: Tx Invert Enable failed!\r\n"); 
    UARTTxInvertDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C3) & (1 << 4);
    TestAssert((0 == ucTmpReg),
            "UART 0105: Tx Invert Disable failed!\r\n"); 

    //
    // Test for Rx Invert Enable/Diable
    //
    UARTRxInvertEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1 << 4);
    TestAssert((0 != ucTmpReg),
            "UART 0105: Rx Invert Enable failed!\r\n"); 
    UARTRxInvertDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1 << 4);
    TestAssert((0 == ucTmpReg),
            "UART 0105: Rx Invert Disable failed!\r\n"); 
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0105 = {
    xuart0105GetTest,
    xuart0105Setup,
    xuart0105TearDown,
    xuart0105Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0106  test.
//!
//! \return the desccription of the xuart0106 test.
//
//*****************************************************************************
static char* xuart0106GetTest(void)
{
    return "UART 0106 : OutMode test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0106 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0106Setup(void)
{
    xHWREG(SIM_SCGC4) |= SIM_SCGC4_UART0_EN;
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0106 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0106TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
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
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & Mask;
    TestAssert((0x00 == ucTmpReg),
            "UART 0106: OutMode Normal failed!\r\n"); 

    //
    // Single line
    //
    UARTOutModeConfig(UART_BASE, UART_MODE_SINGLE_LINE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & Mask;
    TestAssert((0xA0 == ucTmpReg),
            "UART 0106: OutMode Single line failed!\r\n"); 

    //
    // Loops
    //
    UARTOutModeConfig(UART_BASE, UART_MODE_LOOP);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & Mask;
    TestAssert((0x80 == ucTmpReg),
            "UART 0106: OutMode Loops failed!\r\n"); 
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
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1 << 6);
    TestAssert((0 == ucTmpReg),
            "UART 0106: Mode run failed!\r\n"); 

    //
    // UART stop in wait mode.
    //
    UARTWaitModeStop(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1 << 6);
    TestAssert((0 != ucTmpReg),
            "UART 0106: Mode stop failed!\r\n"); 

    //
    // Wakeup method test.
    //
    UARTWakeupMethodConfig(UART_BASE, UART_WAKEUP_IDLE_LINE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1 << 3);
    TestAssert((0 == ucTmpReg),
            "UART 0106: Wakeup Mode idle line failed!\r\n"); 

    UARTWakeupMethodConfig(UART_BASE, UART_WAKEUP_ADDRESS_MARK);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C1) & (1 << 3);
    TestAssert((0 != ucTmpReg),
            "UART 0106: Wakeup Mode address mark failed!\r\n"); 

}

//*****************************************************************************
//
//! xuart0106 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0106Execute(void)
{
    Test_OutModeConfig();
    Test_WaitMode();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0106 = {
    xuart0106GetTest,
    xuart0106Setup,
    xuart0106TearDown,
    xuart0106Execute
};    

//*****************************************************************************
//
//! Get the Test description of xuart0107  test.
//!
//! \return the desccription of the xuart0107 test.
//
//*****************************************************************************
static char* xuart0107GetTest(void)
{
    return "UART 0107 : UARTConfigSet test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart0107 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0107Setup(void)
{
    xHWREG(SIM_SCGC4) |= (SIM_SCGC4_UART0_EN);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart0107 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart0107TearDown(void)
{
    xHWREG(SIM_SCGC4) &= (~SIM_SCGC4_UART0_EN);
}

//*****************************************************************************
//
//! Test for UART MSB/LSB First.
//
//! \return None.
//
//*****************************************************************************
static void Test_Msb_LsbFirst(void)
{
    unsigned char ucTmpReg = 0;

    UARTMsbFirst(UART_BASE);  
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1 << 5);
    TestAssert((0 != ucTmpReg),
            "UART 0107: Set MSB first failed!\r\n"); 

    UARTLsbFirst(UART_BASE);  
    ucTmpReg = xHWREGB(UART_BASE + UART_0_S2) & (1 << 5);
    TestAssert((0 == ucTmpReg),
            "UART 0107: Set LSB first failed!\r\n"); 

}

//*****************************************************************************
//
//! Test for UART Match about function.
//
//! \return None.
//
//*****************************************************************************
static void Test_MatchAddress(void)
{
    unsigned char ucTmpReg = 0;
    unsigned char i        = 0;
    unsigned char ucTestData[3] = 
    {
        0x00,
        0x1F,
        0xFF,
    };
    
    //
    // Match Address Set test
    //
    for(i = 0; i < 3; i++)
    {
        UARTMatchAddressSet(UART_BASE, UART_ADDRESS_CHL_1, ucTestData[i]);
        ucTmpReg = xHWREGB(UART_BASE + UART_0_MA1);
        TestAssert((ucTestData[i] == ucTmpReg),
                "UART 0107: Match Address Set failed!\r\n");

        UARTMatchAddressSet(UART_BASE, UART_ADDRESS_CHL_2, ucTestData[i]);
        ucTmpReg = xHWREGB(UART_BASE + UART_0_MA2);
        TestAssert((ucTestData[i] == ucTmpReg),
                "UART 0107: Match Address Set failed!\r\n");
    }

    //
    // Match Address Enable
    //
    UARTMatchAddrModeEnable(UART_BASE, UART_ADDRESS_CHL_1);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1 << 7);
    TestAssert((0 != ucTmpReg),
            "UART 0107: Address Mode 1 Enable failed!\r\n"); 

    UARTMatchAddrModeEnable(UART_BASE, UART_ADDRESS_CHL_2);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1 << 6);
    TestAssert((0 != ucTmpReg),
            "UART 0107: Address Mode 2 Enable failed!\r\n"); 

    //
    // Match Address Disable
    //
    UARTMatchAddrModeDisable(UART_BASE, UART_ADDRESS_CHL_1);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1 << 7);
    TestAssert((0 == ucTmpReg),
            "UART 0107: Address Mode 1 Disable failed!\r\n"); 

    UARTMatchAddrModeDisable(UART_BASE, UART_ADDRESS_CHL_2);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C4) & (1 << 6);
    TestAssert((0 == ucTmpReg),
            "UART 0107: Address Mode 2 Disable failed!\r\n"); 

}


//*****************************************************************************
//
//! xuart0107 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void Test_Misc(void)
{
    unsigned char ucTmpReg = 0;

    //
    // Both Edge Sample Enable/Disable
    //
    UARTBothEdgeSampleEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 1);
    TestAssert((0 != ucTmpReg),
            "UART 0107: BothEdgeSample Enable failed!\r\n"); 

    UARTBothEdgeSampleDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 1);
    TestAssert((0 == ucTmpReg),
            "UART 0107: BothEdgeSample Disable failed!\r\n"); 

    //
    // Resynchronization Enable/Disable
    //
    UARTReSyncEnable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 0);
    TestAssert((0 == ucTmpReg),
            "UART 0107: Resynchronization Enable failed!\r\n"); 

    UARTReSyncDisable(UART_BASE);
    ucTmpReg = xHWREGB(UART_BASE + UART_0_C5) & (1 << 0);
    TestAssert((0 != ucTmpReg),
            "UART 0107: Resynchronization Disable failed!\r\n"); 
}



//*****************************************************************************
//
//! xuart0107 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart0107Execute(void)
{
    Test_Msb_LsbFirst();
    Test_MatchAddress();
    Test_Misc();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart0107 = {
    xuart0107GetTest,
    xuart0107Setup,
    xuart0107TearDown,
    xuart0107Execute
};    

//
// xuart test suits.
//
const tTestCase * const psPatternxUART01[] =
{
    //&sTestxuart0101,
    //&sTestxuart0102,
    //&sTestxuart0103,
    //&sTestxuart0104,
    &sTestxuart0105,
    &sTestxuart0106,
    &sTestxuart0107,
    0
};

