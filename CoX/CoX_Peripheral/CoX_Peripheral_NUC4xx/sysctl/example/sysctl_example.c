#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "CoX.h"


const unsigned char Begin[] = "Welcome, here is NUC4xx uart example\r\n, \
                               Now you can input your word,end with 'enter'\r\n";
const unsigned char End[] = "Ok, Example is over, bye\r\n";

void UART_example(void)
{
    unsigned int i = 0;

    //
    // Configure System clock
    //
    xSysCtlClockSet(84000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    SysCtlDelay(10000);

    //
    // Enable GPIO/UART Clock
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOG);

    //
    // Remap UART pin to GPIO Port UART0_RX --> PG1 UART0_TX --> PG2
    xSPinTypeUART(UART0RX, PG1);
    xSPinTypeUART(UART0TX, PG2);

    //
    // Configure UART Baud 115200 8-N-1
    //
    xUARTConfigSet(xUART0_BASE, 115200, xUART_CONFIG_WLEN_8 | xUART_CONFIG_PAR_NONE | xUART_CONFIG_STOP_1);

    //
    // Enable UART Receive/Transmit
    //
    xUARTEnable(xUART0_BASE, xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX);

    //
    // print out welcome information
    //

    i = 0;
    while(Buf[i] != '\0')
    {
        xUARTCharPut(xUART0_BASE, Buf[i++]);
    }

    //
    // Echo user's input information
    //
    while((Rec = UxARTCharGet(xUART0_BASE)) != '\n')
    {
        xUARTCharPut(xUART0_BASE, Rec);
    }

    //
    // print out run over information
    //
    i = 0;
    while(Buf[i] != '\0')
    {
        xUARTCharPut(xUART0_BASE, End[i++]);
    }

    while(1);                  
}
