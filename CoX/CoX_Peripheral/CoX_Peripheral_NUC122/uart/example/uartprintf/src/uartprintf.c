#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"

void uartprinntf()
{
    //
    // Initionalize system clock.
    //
    xSysCtlPeripheralClockSourceSet( 10000000,  xSYSCTL_XTAL_6MHZ );
 
    SysCtlDelay(10000);

    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    //
    // Config 8 bit word length, 1 stop bit, 
    // and none parity bit, receive FIFO 1 byte.
    //
    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                             UART_CONFIG_STOP_ONE | 
                                               UART_CONFIG_PAR_NONE));

    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));

    UARTBufferWrite(UART0_BASE, "NUC1xx.UART.BAUDRATE EXAMPLE \r\n", sizeof("NUC1xx.UART.BAUDRATE EXAMPLE \r\n")); 
}
