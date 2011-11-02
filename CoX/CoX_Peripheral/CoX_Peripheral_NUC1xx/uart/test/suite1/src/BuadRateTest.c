#include "test.h"

#define BAUDRATE  115200
char send[] = "This is buadrate test for cox lib of NUC1xx.";
#define SENDNUM  sizeof(send)
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

//*****************************************************************************
//
//! brief callback function of uart1 interrupt handler.
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

void BuadRateTest()
{
    int i;
    recNum = 0;

    //
    // Initialize recData[] to '0'
    //
    InitRecData();

    //
    // Config the pins to uart function
    //
    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);
    xSPinTypeUART(UART1RX,PB4);
    xSPinTypeUART(UART1TX,PB5);

    //           
    // Reset and Enable uart0, and set uart clock to 12M
    //
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    //
    // Config the baudrate 115200, 8 bit word length, 1 stop bit, 
    // and none parity bit, receive FIFO 1 byte.
    //
    UARTConfigSetExpClk(UART0_BASE, 115200, 
                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTFIFOTriggerLevelSet(UART0_BASE, UART_FIFO_1BYTES);

    UARTConfigSetExpClk(UART1_BASE, 115200, 
                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTFIFOTriggerLevelSet(UART1_BASE, UART_FIFO_1BYTES);

    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    UARTEnable(UART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    
    //
    // Register the uart0 interrupt handler, Enable uart0 receive interrupt.
    //
    UARTIntCallbackInit(UART0_BASE, uart0CallbackFunc);
    UARTIntEnable(UART0_BASE, UART_INT_RDA);
    xIntEnable(INT_UART02);
    xIntMasterEnable();

    //for(i=0; i<dataNum; i++)
    {
        UARTBufferWrite(UART1_BASE, sendData, dataNum);      
    }  

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