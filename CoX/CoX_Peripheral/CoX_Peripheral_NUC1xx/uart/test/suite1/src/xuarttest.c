//*****************************************************************************
//
//! @page xuart_testcase xuart  test
//!  
//! File: @ref xuart_testcase.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the xuart sub component.<br><br>
//! - \p Board: NUC1xx <br><br>
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


#define UART_BASE   UART1_BASE
#define xSYSCTL_PERIPH_UART  xSYSCTL_PERIPH_UART1

void xuart001Execute_NormalConfig(void);
unsigned long uart0CallbackFunc(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData);
void xuart001Execute_uartInt(void);

void xuart002Execute_FIFOConfig(void);

void xuart003Execute_IrDAConfig(void);

void xuart004Execute_LinConfig(void);

void xuart005Execute_flowControlConfig(void);

void xuart006Execute_ModemConfig(void);

void xuart007Execute_DMAConfig(void);



#define countof(x) sizeof(x)/sizeof(*x)

//
// uart rx and tx test 
//
char  sendData[] = {'0','1','2','3','4','5','6','7','8','9'};
char  recData[]  = {'0','0','0','0','0','0','0','0','0','0'};
#define dataNum  countof(sendData)
#define InitRecData()  do{ \
                            int i = dataNum - 1; \
                            while(i>=0) \
                                recData[i--] = '0'; \
                          }while(0)

volatile unsigned int sendNum=0,recNum=0;

//
// line config test
//
unsigned long wordLength[] = {UART_CONFIG_WLEN_8,UART_CONFIG_WLEN_7, 
                              UART_CONFIG_WLEN_6,UART_CONFIG_WLEN_5};

unsigned long parity[] = {UART_CONFIG_PAR_NONE,UART_CONFIG_PAR_EVEN,
                          UART_CONFIG_PAR_ODD, UART_CONFIG_PAR_ONE,
                          UART_CONFIG_PAR_ZERO};

unsigned long stopbit[] = {UART_CONFIG_STOP_ONE,UART_CONFIG_STOP_TWO};

unsigned long ulBlock[] = {UART_BLOCK_TX, UART_BLOCK_RX};

//
// FIFO test
//
unsigned long ulRxLevel[] = {UART_FIFO_1BYTES, UART_FIFO_4BYTES, 
                             UART_FIFO_8BYTES, UART_FIFO_14BYTES, 
                             UART_FIFO_30BYTES, UART_FIFO_46BYTES, 
                             UART_FIFO_62BYTES};

#define  fifoLevelNum   countof(ulRxLevel)

//
// flow control test
//
unsigned long ulFlowCtlCfg[] = {UART_FLOWCONTROL_TX, UART_FLOWCONTROL_RX, 
                                (UART_FLOWCONTROL_TX | UART_FLOWCONTROL_RX), 
                                UART_FLOWCONTROL_NONE};

#define  flowCtlNum     countof(ulFlowCtlCfg)

//
// clock test
//
unsigned long ulDiv[] = {1,4,6,8,10};
#define  divNum  countof(ulDiv)

//
//Modem test
//
unsigned long ulModemCfg[] = {UART_TRIGGER_RTS_H, UART_TRIGGER_RTS_L, 
                              (UART_TRIGGER_RTS_H | UART_OUTPUT_RTS_SET), 
                              (UART_TRIGGER_RTS_L | UART_OUTPUT_RTS_SET)};

#define  modemCfgNum      countof(ulModemCfg)

unsigned long ulModemSt[] = {UART_TRIGGER_CTS_H, UART_TRIGGER_CTS_L};

#define  modemStNum      countof(ulModemSt)

//
//DMA test
//
unsigned long ulDMACfg[] = {UART_DMA_RX, UART_DMA_TX, 
                            (UART_DMA_RX | UART_DMA_TX)};

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
//! Get the Test description of xuart001  test.
//!
//! \return the desccription of the xuart001 test.
//
//*****************************************************************************
static char* xuart001GetTest(void)
{
    return "xuart [001]: xuart uart Config ,rx,tx and interrupt test";
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

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART);   

    //
    // the combined test of word length,parity and stop bit.
    //
    for(w=0; w<w1; w++)
    {
        for(p=0; p<p1; p++)
        {   
            UARTParityModeSet(UART_BASE, parity[p]);
            ulTemp1 = UARTParityModeGet(UART_BASE);
            TestAssert(parity[p] == ulTemp1, 
                  "xuart API \"UARTParityModeSet\" or " 
                  "\"UARTParityModeGet\" error!");

            for(s=0; s<s1; s++)
            {
                ulTemp1 = (wordLength[w] | parity[p] | stopbit[s]);
                UARTConfigSetExpClk(UART_BASE, 115200, ulTemp1);     
                UARTConfigGetExpClk(UART_BASE, &ulBuad, &ulConfig);
                TestAssert((ulConfig & ulTemp1) == ulTemp1, 
                   "xuart API \"UARTConfigSetExpClk\" or "
                   "\"UARTConfigGetExpClk\" error!");
            }
        } 
    }
    
    
    //
    // Break Control test
    //
    UARTBreakCtl(UART_BASE, xtrue);
    ulTemp1 = xHWREG(UART_BASE + UART_LCR);
    TestAssert(((ulTemp1>>6) & 1) == 1, 
                 "xuart API \"UARTBreakCtl\" error!");
    UARTBreakCtl(UART_BASE, xfalse);
    ulTemp1 = xHWREG(UART_BASE + UART_LCR);
    TestAssert(((ulTemp1>>6) & 1) == 0, 
                 "xuart API \"UARTBreakCtl\" error!");

}

//*****************************************************************************
//
//! !brief callback function of uart1 interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long uart0CallbackFunc(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    if((UARTIntStatus(UART0_BASE, xtrue) & 0x100) == 0x100)
    {
        while(!UARTFIFORxIsEmpty(UART0_BASE))
            recData[recNum++] = UARTCharGet(UART0_BASE);
    }  
                             
    return 0;                       
}

void xuart001Execute_uartInt(void)
{
    int i;
    unsigned char info[] = "Please input(0123456789) : ";
    recNum = 0;
    
    //
    // Initialize recData[] to '0'
    //
    InitRecData();

    //
    // Register the uart0 interrupt handler, Enable uart0 receive interrupt.
    //
    UARTIntCallbackInit(UART0_BASE, uart0CallbackFunc);
    UARTIntEnable(UART0_BASE, UART_INT_RDA);
    xIntEnable(INT_UART02);
    xIntMasterEnable();

    UARTBufferWrite(UART0_BASE, info, countof(info));

    //
    // wait the hyperterminal to transmit data "0123456789"
    //
    while(recData[dataNum-1] != '9');

    //
    // Check the data received.
    //
    for(i=0; i<dataNum; i++)
    {
        TestAssert(recData[i] == ('0' + i), 
                    "xuart API \"receive\" or \"interrupt\" error!");      
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
    
    //
    // rx,tx and interrupt test
    //
    xuart001Execute_uartInt();  
            
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart001UART = {
    xuart001GetTest,
    xuart001Setup,
    xuart001TearDown,
    xuart001Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart002  test.
//!
//! \return the desccription of the xuart002 test.
//
//*****************************************************************************
static char* xuart002GetTest(void)
{
    return "xuart [002]: xuart FIFO test";
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

}

void xuart002Execute_FIFOConfig(void)
{
    unsigned long ulTemp1;
    int i;
    
    //
    // test for rx trigger level config
    //
    for(i=0; i<fifoLevelNum; i++)
    {
        UARTFIFOTriggerLevelSet(UART_BASE, ulRxLevel[i]); 
        UARTFIFOTriggerLevelGet(UART_BASE, &ulTemp1);
        TestAssert(ulTemp1 == ulRxLevel[i], 
           "xuart API \"UARTFIFOTriggerLevelSet\" or "
           "\"UARTFIFOTriggerLevelGet\" error!");
    }

    //
    // reset rx and tx fifo
    //
    xHWREG(UART_BASE + UART_FCR) = 0x60;

    SysCtlDelay(100000);

    TestAssert(UARTFIFOTxIsEmpty(UART_BASE) == xtrue,
                  "xuart API \"UARTFIFOTxIsEmpty\" error!");

    TestAssert(UARTFIFOTxIsFull(UART_BASE) == xfalse,
                  "xuart API \"UARTFIFOTxIsFull\" error!");

    TestAssert(UARTFIFOTxLength(UART_BASE) == 0,
                  "xuart API \"UARTFIFOTxLength\" error!");

    TestAssert(UARTFIFORxIsEmpty(UART_BASE) == xtrue,
                  "xuart API \"UARTFIFORxIsEmpty\" error!");

    TestAssert(UARTFIFORxIsFull(UART_BASE) == xfalse,
                  "xuart API \"UARTFIFORxIsFull\" error!");

    TestAssert(UARTFIFORxLength(UART_BASE) == 0,
                   "xuart API \"UARTFIFORxLength\" error!");


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
    // FIFO config
    //
    xuart002Execute_FIFOConfig();

}

//
// xuart FIFO test case struct.
//
const tTestCase sTestxuart002FIFO = {
    xuart002GetTest,
    xuart002Setup,
    xuart002TearDown,
    xuart002Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart003  test.
//!
//! \return the desccription of the xuart003 test.
//
//*****************************************************************************
static char* xuart003GetTest(void)
{
    return "xuart [003]: xuart IrDA test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart003Setup(void)
{

}

void xuart003Execute_IrDAConfig(void)
{
    unsigned long ulTemp1;

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);

    UARTEnableIrDA(UART_BASE);
    ulTemp1 = xHWREG(UART_BASE + UART_FUN_SEL) & 0x02;
    TestAssert(ulTemp1 == 0x02,
                   "xuart API \"UARTEnableIrDA\" error!");
    
    ulTemp1 = (UART_CONFIG_IrDA_TX_EN | UART_CONFIG_IrDA_INV_TX | 
               UART_CONFIG_IrDA_INV_RX);
    UARTIrDAConfig(UART_BASE, ulTemp1);
    ulTemp1 = xHWREG(UART_BASE + UART_IRCR) & 0x62;
    TestAssert(ulTemp1 == 0x62,
                   "xuart API \"UARTIrDAConfig\" error!");

    ulTemp1 = ~(UART_CONFIG_IrDA_TX_EN | UART_CONFIG_IrDA_INV_TX | 
                UART_CONFIG_IrDA_INV_RX);
    UARTIrDAConfig(UART_BASE, ulTemp1);
    ulTemp1 = xHWREG(UART_BASE + UART_IRCR) & 0x62;
    TestAssert(ulTemp1 == 0x0,
                   "xuart API \"UARTIrDAConfig\" error!");
    
    UARTDisableIrDA(UART_BASE);
    ulTemp1 = xHWREG(UART_BASE + UART_FUN_SEL) & 0x02;
    TestAssert(ulTemp1 == 0,
                   "xuart API \"UARTDisableIrDA\" error!");
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart003TearDown(void)
{

}

//*****************************************************************************
//
//! xuart003 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart003Execute(void)
{
    //
    // IrDA config
    //
    xuart003Execute_IrDAConfig();
}

//
// xuart IrDA test case struct.
//
const tTestCase sTestxuart003IrDA = {
    xuart003GetTest,
    xuart003Setup,
    xuart003TearDown,
    xuart003Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart004  test.
//!
//! \return the desccription of the xuart004 test.
//
//*****************************************************************************
static char* xuart004GetTest(void)
{
    return "xuart [004]: xuart LIN test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart004Setup(void)
{

}

//*****************************************************************************
//
//! Something should do after the test execute of xuart004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart004TearDown(void)
{

}

void xuart004Execute_LinConfig(void)
{
    unsigned long ulTemp1;

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);

    UARTEnableLIN(UART_BASE);
    ulTemp1 = xHWREG(UART_BASE + UART_FUN_SEL) & 0x01;
    TestAssert(ulTemp1 == 0x01,
                   "xuart API \"UARTEnableLIN\" error!");

    //
    // Enable LIN, Set the LIN Break Field Length
    //
    ulTemp1 = (UART_CONFIG_LIN_RX_EN | UART_CONFIG_LIN_TX_EN | 0x0A);
    UARTLINConfig(UART_BASE, 115200, ulTemp1);
    ulTemp1 = xHWREG(UART_BASE + UART_LIN_BCNT) & 0xCA;
    TestAssert(ulTemp1 == 0xCA,
                   "xuart API \"UARTLINConfig\" error!");

    ulTemp1 = (UART_CONFIG_LIN_RX_EN | UART_CONFIG_LIN_TX_EN | 0x0F);
    UARTLINConfig(UART_BASE, 115200, ulTemp1);
    ulTemp1 = xHWREG(UART_BASE + UART_LIN_BCNT) & 0xCF;
    TestAssert(ulTemp1 == 0xCF,
                   "xuart API \"UARTLINConfig\" error!");

    ulTemp1 = (~(UART_CONFIG_LIN_RX_EN | UART_CONFIG_LIN_TX_EN)) | 0x0A;
    UARTLINConfig(UART_BASE, 115200, ulTemp1);
    ulTemp1 = xHWREG(UART_BASE + UART_LIN_BCNT) & 0x0A;
    TestAssert(ulTemp1 == 0x0A,
                   "xuart API \"UARTLINConfig\" error!");
    
    //
    // Disable Lin
    //
    UARTDisableLIN(UART_BASE);
    ulTemp1 = xHWREG(UART_BASE + UART_FUN_SEL) & 0x01;
    TestAssert(ulTemp1 == 0,
                   "xuart API \"UARTDisableIrDA\" error!");

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
    // Lin configuration and enable/disable.
    //
    xuart004Execute_LinConfig();
   
}

//
// xuart Lin test case struct.
//
const tTestCase sTestxuart004Lin = {
    xuart004GetTest,
    xuart004Setup,
    xuart004TearDown,
    xuart004Execute
};
//*****************************************************************************
//
//! Get the Test description of xuart005  test.
//!
//! \return the desccription of the xuart005 test.
//
//*****************************************************************************
static char* xuart005GetTest(void)
{
    return "xuart [005]: xuart flow control test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart005Setup(void)
{

}

//*****************************************************************************
//
//! Something should do after the test execute of xuart005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart005TearDown(void)
{

}

//*****************************************************************************
//
//! test for flow control config 
//!
//! \return None.
//
//*****************************************************************************
void xuart005Execute_flowControlConfig(void)
{
    int i;
    unsigned long ulTemp1;
    
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);

    //
    // Enable/Disable RTS and CTS
    //
    for(i=0; i<flowCtlNum; i++)
    {
        UARTFlowControlSet(UART_BASE, ulFlowCtlCfg[i]);
        ulTemp1 = UARTFlowControlGet(UART_BASE);
        TestAssert(ulTemp1 == ulFlowCtlCfg[i],
                   "xuart API \"UARTFlowControlSet\" or "
                   "\"UARTFlowControlGet\" error!");
    }
    
    
}
//*****************************************************************************
//
//! xuart005 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart005Execute(void)
{
    //
    // uart flow control config
    //
    xuart005Execute_flowControlConfig();
    
}

//
// xuart flow control test case struct.
//
const tTestCase sTestxuart005flowCtl = {
    xuart005GetTest,
    xuart005Setup,
    xuart005TearDown,
    xuart005Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart006  test.
//!
//! \return the desccription of the xuart006 test.
//
//*****************************************************************************
static char* xuart006GetTest(void)
{
    return "xuart [006]: xuart Modem test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart006Setup(void)
{

}

//*****************************************************************************
//
//! Something should do after the test execute of xuart006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart006TearDown(void)
{

}

void xuart006Execute_ModemConfig(void)
{
    int i;
    unsigned long ulTemp1, ulTemp2;
    
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    
    //
    // Set RTS Trigger Level
    //
    for(i=0; i<modemCfgNum; i++)
    {
        UARTModemControlSet(UART_BASE, ulModemCfg[i]);
        ulTemp1 = UARTModemControlGet(UART_BASE); 
        ulTemp2 = (((((xHWREG(UART_BASE + UART_MCR)>>1) & 0x01)^
        ((xHWREG(UART_BASE + UART_MCR)>>9) & 0x01)))^1)<<13;
        TestAssert(ulTemp1 == ulTemp2,
                   "xuart API \"UARTModemControlSet\" or "
                   "\"UARTModemControlGet\" error!");   
    }
    UARTModemControlClear(UART_BASE, UART_OUTPUT_RTS_SET);
    ulTemp1 = ((xHWREG(UART_BASE + UART_MCR)>>1) & 0x01);
    TestAssert(ulTemp1 == ulTemp2,
                   "xuart API \"UARTModemControlClear\" error!");
    //
    // Set CTS Trigger Level
    //
    for(i=0; i<modemStNum; i++)
    {
        UARTModemStatusSet(UART_BASE, ulModemSt[i]);
        ulTemp1 = xHWREG(UART_BASE + UART_MSR) & 0x100;
        TestAssert(ulTemp1 == ulModemSt[i],
                   "xuart API \"UARTModemStatusSet\" error!");
    }

    /*
    //
    // Get CTS Pin Status, 0 when high level trigger
    //
    UARTModemStatusSet(UART_BASE, UART_TRIGGER_CTS_H);
    ulTemp1 = UARTModemStatusGet(UART_BASE);
    TestAssert(ulTemp1 == 0x0,
                   "xuart API \"UARTModemStatusGet\" error!");
    //
    // Get CTS Pin Status, 1 when low level trigger
    //
    UARTModemStatusSet(UART_BASE, UART_TRIGGER_CTS_L);
    ulTemp1 = UARTModemStatusGet(UART_BASE);
    TestAssert(ulTemp1 == 0x10,
                   "xuart API \"UARTModemStatusGet\" error!");
    */
}
//*****************************************************************************
//
//! xuart006 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart006Execute(void)
{
    //
    // test for modem config
    //
    xuart006Execute_ModemConfig();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart006Modem = {
    xuart006GetTest,
    xuart006Setup,
    xuart006TearDown,
    xuart006Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart007  test.
//!
//! \return the desccription of the xuart007 test.
//
//*****************************************************************************
static char* xuart007GetTest(void)
{
    return "xuart [007]: xuart DMA test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart007 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart007Setup(void)
{

}

//*****************************************************************************
//
//! Something should do after the test execute of xuart007 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart007TearDown(void)
{

}

void xuart007Execute_DMAConfig(void)
{
    int i;
    unsigned long ulTemp1;
    
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);

    //
    // Enable Tx/Rx DMA
    //
    for(i=0; i<DMACfgNum; i++)
    {
        UARTDMAEnable(UART_BASE, ulDMACfg[i]);
        ulTemp1 = xHWREG(UART_BASE + UART_IER) & ulDMACfg[i];
        TestAssert(ulTemp1 == ulDMACfg[i],
                   "xuart API \"UARTModemStatusGet\" error!");
    }

    //
    // Disable Tx/Rx DMA
    //
    for(i=0; i<DMACfgNum; i++)
    {
        UARTDMADisable(UART_BASE, ulDMACfg[i]);
        ulTemp1 = xHWREG(UART_BASE + UART_IER) & ulDMACfg[i];
        TestAssert(ulTemp1 == 0,
                   "xuart API \"UARTModemStatusGet\" error!");
    }
}

//*****************************************************************************
//
//! xuart007 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart007Execute(void)
{
    //
    // test for DMA config
    //
    xuart007Execute_DMAConfig();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart007DMA = {
    xuart007GetTest,
    xuart007Setup,
    xuart007TearDown,
    xuart007Execute
};

//
// xuart test suits.
//
const tTestCase * const psPatternxUART[] =
{
    &sTestxuart001UART,
    &sTestxuart002FIFO,
    &sTestxuart003IrDA,    
    &sTestxuart004Lin,
    &sTestxuart005flowCtl,
    &sTestxuart006Modem,
    &sTestxuart007DMA,
    0
};

