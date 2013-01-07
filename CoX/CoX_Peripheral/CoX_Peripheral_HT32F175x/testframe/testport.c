#include "test.h"

//*****************************************************************************
//
//! \brief Init uart to print.
//!
//! \param None
//!
//! \details uart config as (115200, 8 data bit, 1 stop bit , no partiy)
//!
//! \return None.
//
//*****************************************************************************

void 
TestIOInit(void)
{
    //
    //Set System Clock
    //
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    xSysCtlDelay(10000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART0RX, PC10);
    xSPinTypeUART(UART0TX, PC8);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    //
    // Set UART0 clock source.
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_HCLK);

    //
    // Configure 8 bit word length, 1 stop bit,
    // and none parity bit, receive FIFO 1 byte.
    //
    xUARTConfigSet(UART0_BASE, 115200, (xUART_CONFIG_WLEN_8 |
                                        xUART_CONFIG_STOP_1 |
                                        xUART_CONFIG_PAR_NONE));

    xUARTEnable(UART0_BASE, (UART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
}

//*****************************************************************************
//
//! \brief print a char.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
TestIOPut(char ch)
{
    uint8_t c;
    c = ch;
    while(!((xHWREG(UART0_BASE + USART_LSR) & 0x40)==0x40));
    //
    // Write this character to the transmit FIFO.
    //
    xHWREG(UART0_BASE + USART_THR) = c;
}

//*****************************************************************************
//
//! \brief Enable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestEnableIRQ(void)
{
    xCPUcpsie();
}

//*****************************************************************************
//
//! \brief Disable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestDisableIRQ(void)
{
    xCPUcpsid();
}
