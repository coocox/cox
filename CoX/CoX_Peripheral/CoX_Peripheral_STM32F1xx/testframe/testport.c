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
    xSysCtlClockSet(16000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    SysCtlDelay(10000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    //xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //xSPinTypeUART(UART1RX,PA10);
    xSPinTypeUART(UART1TX,PA9);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    //SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    xUARTConfigSet(USART1_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
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
    while((xHWREG(USART1_BASE + USART_SR) & (0x80))==0x00);
    
    //
    // Write this character to the transmit data register.
    //
    xHWREG(USART1_BASE + USART_DR) = c;

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

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.(COX)
//
//*****************************************************************************
#ifdef xDEBUG
void
__xerror__(char *pcFilename, unsigned long ulLine)
{
    while(1);
}
#endif

