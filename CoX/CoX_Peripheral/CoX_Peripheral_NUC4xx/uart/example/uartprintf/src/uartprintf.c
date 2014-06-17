#include "CoX.h"

void uartprinntf()
{
    xSysCtlClockSet(84000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlDelay(10000);

    xSPinTypeUART(UART0RX,PG1);
    xSPinTypeUART(UART0TX,PG2);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);

    //
    // Config 8 bit word length, 1 stop bit, 
    // and none parity bit, receive FIFO 1 byte.
    //
    xUARTConfigSet(xUART0_BASE, 115200, (xUART_CONFIG_WLEN_8   | \
                                         xUART_CONFIG_STOP_1   | \
                                         xUART_CONFIG_PAR_NONE));

    xUARTEnable(xUART0_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));

    UARTBufferWrite(UART0_BASE, "NUC1xx.UART.BAUDRATE EXAMPLE \r\n", sizeof("NUC1xx.UART.BAUDRATE EXAMPLE \r\n")); 
}
