#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"

#define BAUDRATE  115200

unsigned char send[] = "This is buadrate test for cox lib of NUC1xx.\r\n";
#define SENDNUM  sizeof(send)

void BuadRateTest()
{
    unsigned long ulTemp1, ulBuad, ulConfig;

   
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_PWRCON) |= (SYSCLK_PWRCON_XTL12M_EN | SYSCLK_PWRCON_OSC22M_EN);;
    
    //
    // Config 8 bit word length, 1 stop bit, 
    // and none parity bit, receive FIFO 1 byte.
    //
    ulTemp1 = (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    SysCtlDelay(10000);

    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, (UART_CONFIG_WLEN_8 | 
                                             UART_CONFIG_STOP_ONE | 
                                               UART_CONFIG_PAR_NONE));

    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));

    UARTBufferWrite(UART0_BASE, "NUC1xx.UART.BAUDRATE TEST \r\n", sizeof("NUC1xx.UART.BAUDRATE TEST \r\n"));      

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x00000000; //source: 12M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000100; //divide: 1+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig);
    UARTBufferWrite(UART0_BASE, "1. 12M,2div: \r\n", 15);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x00000000; //source: 12M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000000; //divide: 0+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig);  
    UARTBufferWrite(UART0_BASE, "2. 12M,1div: \r\n", 15);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);      

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);      
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x00000000; //source: 12M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000300; //divide: 3+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig); 
    UARTBufferWrite(UART0_BASE, "3. 12M,4div: \r\n", 15);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x01000000; //source: PLL
    xHWREG(0x50000220) = 0x0000C22E;  //48M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000100; //divide: 1+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig); 
    UARTBufferWrite(UART0_BASE, "4. 48M,2div: \r\n", 15);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x01000000; //source: PLL
    xHWREG(0x50000220) = 0x0000C22E;  //48M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000000; //divide: 0+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig);
    UARTBufferWrite(UART0_BASE, "5. 48M,1div: \r\n", 15); 
    UARTBufferWrite(UART0_BASE, send, SENDNUM);

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x01000000; //source: PLL
    xHWREG(0x50000220) = 0x0000C22E;  //48M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000F00; //divide: 15+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig);
    UARTBufferWrite(UART0_BASE, "6. 48M,16div: \r\n", 16);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x03000000; //source: 22M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000100; //divide: 1+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig); 
    UARTBufferWrite(UART0_BASE, "7. 22M,2div: \r\n", 15);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x03000000; //source: 22M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000000; //divide: 0+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig);
    UARTBufferWrite(UART0_BASE, "8. 22M,1div: \r\n", 15);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);

    while(!UARTFIFOTxIsEmpty(UART0_BASE));
    SysCtlDelay(10000);
    SysCtlKeyAddrUnlock();
    xHWREG(0x50000214) &= 0xF0FFFFFF;
    xHWREG(0x50000214) |= 0x03000000; //source: 22M
    xHWREG(0x50000218) &= 0xFFFFF0FF;
    xHWREG(0x50000218) |= 0x00000700; //divide: 7+1
    SysCtlKeyAddrLock();
    SysCtlDelay(10000);
    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
    UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig);
    UARTBufferWrite(UART0_BASE, "9. 22M,8div: \r\n", 15);
    UARTBufferWrite(UART0_BASE, send, SENDNUM);
}
