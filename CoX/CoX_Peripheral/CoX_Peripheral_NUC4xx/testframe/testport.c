#include "test.h"
#include "xhw_sysctl.h"

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
    xSysCtlClockSet(84000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlDelay(10000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
	
    xHWREG(GCR_GPGMFPL) |= ((1<<4) | (1 << 8)); //PG1:RXD PG2: TXD
    xUARTConfigSet(xUART0_BASE, 115200, (xUART_CONFIG_WLEN_8   | \
                                         xUART_CONFIG_STOP_1   | \
                                         xUART_CONFIG_PAR_NONE));

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
	xUARTCharPut(xUART0_BASE, ch);
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
