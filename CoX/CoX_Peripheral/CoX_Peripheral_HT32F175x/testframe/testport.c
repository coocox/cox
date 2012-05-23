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
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART0RX, PC10);
    xSPinTypeUART(UART0TX, PC8);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_HCLK);

    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                             UART_CONFIG_STOP_ONE | 
                                             UART_CONFIG_PAR_NONE));
    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
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
