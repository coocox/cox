#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
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

const unsigned char Begin[] = "Welcome, here is Freescale uart example\r\n, \
                               Now you can input your word,end with 'enter'\r\n";
const unsigned char End[] = "Ok, Example is over, bye\r\n";

void UART_example(void)
{
    unsigned int i = 0;

    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(1000000);

    //
    // Enable GPIO/UART Clock
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    //
    // Remap UART pin to GPIO Port UART1_RX --> PC3 UART1_TX --> PC4
    xSPinTypeUART(UART1RX, PC3);
    xSPinTypeUART(UART1TX, PC4);

    //
    // Disable UART Receive/Transmit
    //
    UARTDisable(UART1_BASE, UART_TX | UART_RX);

    //
    // Configure UART Baud 9600 8-N-1
    //
    UARTConfigSet(UART1_BASE, 9600, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE |
            UART_CONFIG_STOP_1);

    //
    // Enable UART Receive/Transmit
    //
    UARTEnable(UART1_BASE, UART_TX | UART_RX);

    //
    // print out welcome information
    //

    i = 0;
    while(Buf[i] != '\0')
    {
        UARTCharPut(UART1_BASE, Buf[i++]);
    }

    //
    // Echo user's input information
    //
    while((Rec = UARTCharGet(UART1_BASE)) != '\n')
    {
        UARTCharPut(UART1_BASE, Rec);
    }

    //
    // print out run over information
    //
    i = 0;
    while(Buf[i] != '\0')
    {
        UARTCharPut(UART1_BASE, End[i++]);
    }

    while(1);                  
}
