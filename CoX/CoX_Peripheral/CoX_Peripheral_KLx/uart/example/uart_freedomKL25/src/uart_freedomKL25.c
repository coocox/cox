/**
  *****************************************************************************
  * @title   uart_freedomKL25.c
  * @author  0xc0170
  * @date    30 Nov 2012
  * @brief   Print welcome message to the terminal through UART on
  * 		     KL25 Freedom board and echo users input typed in the terminal.
  *******************************************************************************
  */
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"

const unsigned char Begin[] = "Welcome, here is Freedom KL25 UART example\r\n, \
                               Now you can input your word, end with 'enter'\r\n";
const unsigned char End[] = "\nEnd of UART Example";

//*****************************************************************************
//
//! Initialize the UART module and send characters to the terminal
//!
//! \param None
//!
//! This function initializes the UART including clock source, enables RX and TX.
//! Prints the welcome message and echos characters.
//!
//! \return none
//
//*****************************************************************************
void UART_example_freedomKL25(void)
{
    unsigned int i = 0;
    unsigned char Rec;

    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(1000000);

    //
    // Enable GPIO and UART Clock
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Remap UART pin to GPIO Port UART0_RX --> PA2 UART0_TX --> PA1
    //
    xSPinTypeUART(UART0RX, PA1);
    xSPinTypeUART(UART0TX, PA2);

    //
    // Set UART clock
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2);

    //
    // Disable UART Receive/Transmit
    //
    UARTDisable(UART0_BASE, UART_TX | UART_RX);

    //
    // Configure UART Baud 115200
    //
    UARTConfigSet(UART0_BASE, 115200, UART_CONFIG_SAMPLE_RATE_15 | UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_1);

    //
    // Enable UART Receive and Transmit
    //
    UARTEnable(UART0_BASE, UART_TX | UART_RX);

    //
    // Print out welcome information
    //
    i = 0;
    while(Begin[i] != '\0')
    {
        UARTCharPut(UART0_BASE, Begin[i++]);
    }

    //
    // Echo user's input information. End if 0xD (CR)
    //
    while((Rec = UARTCharGet(UART0_BASE)) != 0xD)
    {
        UARTCharPut(UART0_BASE, Rec);
    }

    //
    // print out last message
    //
    i = 0;
    while(End[i] != '\0')
    {
        UARTCharPut(UART0_BASE, End[i++]);
    }

    while(1);                  
}
