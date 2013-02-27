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

const unsigned char Begin[] = {"Welcome, here is Freescale uart example\r\n"
                               "Now you can input your word,end with 'Enter'\r\n"};
const unsigned char End[] = {"\r\nOk, Example is over, bye\r\n"};

void UART_example(void)
{
    unsigned int i = 0;
    unsigned char Rec = 0;

    //Close watchdog
    (*((volatile unsigned long *)(0x40048100))) = 0x00;

    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(1000000);

    // Note: Defore call UART0 Function, you must call SysCtlPeripheralClockSourceSet Function.
    // SYSCTL_PERIPH_UART0_S_MCGFLLCLK, SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2,
    // SYSCTL_PERIPH_UART0_S_OSCERCLK, SYSCTL_PERIPH_UART0_S_MCGIRCLK, 
    // For UART1/2, just comment it
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2);

    //
    // Enable GPIO/UART Clock
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Remap UART pin to GPIO Port UART0_RX --> PA1 UART0_TX --> PA2
    xSPinTypeUART(UART0RX, PA1);
    xSPinTypeUART(UART0TX, PA2);

    //
    // Disable UART Receive/Transmit
    //
    UARTDisable(UART0_BASE, UART_TX | UART_RX);

    //
    // Configure UART Baud 115200 8-N-1
    //
    UARTConfigSet(UART0_BASE, 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE |
            UART_CONFIG_STOP_1);

    //
    // Enable UART Receive/Transmit
    //
    UARTEnable(UART0_BASE, UART_TX | UART_RX);
    SysCtlDelay(0xFFFFFF);
    
    //
    // print out welcome information
    //

    i = 0;
    while(Begin[i] != '\0')
    {
        UARTCharPut(UART0_BASE, Begin[i++]);
    }

    //
    // Echo user's input information
    //
    while((Rec = UARTCharGet(UART0_BASE)) != 0x0D)
    {
        UARTCharPut(UART0_BASE, Rec);
    }

    //
    // print out run over information
    //
    i = 0;
    while(End[i] != '\0')
    {
        UARTCharPut(UART0_BASE, End[i++]);
    }

    while(1);                  
}
