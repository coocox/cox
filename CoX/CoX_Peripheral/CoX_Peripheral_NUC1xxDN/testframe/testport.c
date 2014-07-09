#include "test.h"
#include "xhw_uart.h"

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
    //SysCtlKeyAddrUnlock();
    //xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
	xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlDelay(10000);

    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    xUARTConfigSet(xUART0_BASE, 115200, (xUART_CONFIG_WLEN_8 | xUART_CONFIG_STOP_1 | xUART_CONFIG_PAR_NONE));

    xUARTEnable(xUART0_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
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
    while((xHWREG(UART0_BASE + UART_FSR) & (0x800000))==0x800000);
    //
    // Write this character to the transmit FIFO.
    //
    xHWREG(UART0_BASE + UART_THR) = c;
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

