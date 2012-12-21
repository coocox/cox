//*****************************************************************************
//
//! \file xuart.c
//! \brief Driver for the UART
//! \version V2.2.1.0
//! \date 4/27/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     * Neither the name of the <ORGANIZATION> nor the names of its
//! contributors may be used to endorse or promote products derived
//! from this software without specific prior written permission.
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_uart.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xuart.h"

//*****************************************************************************
//
// An array is UART callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnUARTHandlerCallbacks[2]={0};

//*****************************************************************************
//
//! \internal
//! \brief Checks a UART base address.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function determines if a UART port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
UARTBaseValid(unsigned long ulBase)
{
    return((ulBase == UART0_BASE) || (ulBase == UART1_BASE));
}
#endif

//*****************************************************************************
//
//! \brief The function is the UART0 interrupt service.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
UART0IntHandler(void)
{
    unsigned long ulUART0IntStatus;

    ulUART0IntStatus = xHWREG(UART0_BASE + USART_IIR);

    if(g_pfnUARTHandlerCallbacks[0] != 0)
    {
        g_pfnUARTHandlerCallbacks[0](0, 0, ulUART0IntStatus, 0);
    }
}

//*****************************************************************************
//
//! \brief The function is the UART1 interrupt service.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
UART1IntHandler(void)
{
    unsigned long ulUART1IntStatus;

    ulUART1IntStatus = xHWREG(UART1_BASE + USART_IIR);

    if(g_pfnUARTHandlerCallbacks[1] != 0)
    {
        g_pfnUARTHandlerCallbacks[1](0, 0, ulUART1IntStatus, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is used to get Uart clock.
//!
//! \param ulBase is the base address of the UART port.
//!
//! \return Returns the Current Uart Clock.
//
//*****************************************************************************
static unsigned long UARTCLkGet(void)
{
    unsigned long ulSysClk = 0;
    unsigned long ulUartDiv;

    //
    // Get system clock.
    //
    ulSysClk = xSysCtlClockGet();
    
    //
    // Get UART divder value.
    //
    ulUartDiv = xHWREG(SYSCLK_GCFGR) & SYSCLK_GCFGR_URPRE_M;

    if(ulUartDiv == SYSCLK_GCFGR_URPRE_2)
    {
        ulUartDiv = 2;
    }
    else
    {
        ulUartDiv = 1;
    }
    
    return ulSysClk/ulUartDiv;
}


//*****************************************************************************
//
//! \brief Sets the type of parity.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulParity specifies the type of parity to use.
//! 
//! Sets the type of parity to use for transmitting and expect when receiving.
//! The \e ulParity parameter must be one of \b UART_CONFIG_PAR_NONE,
//! \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE,
//! or \b UART_CONFIG_PAR_ZERO.  The last two allow direct control of the
//! parity bit; it is always either one or zero based on the mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTParityModeSet(unsigned long ulBase, unsigned long ulParity)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulParity == UART_CONFIG_PAR_NONE) ||
            (ulParity == UART_CONFIG_PAR_EVEN) ||
            (ulParity == UART_CONFIG_PAR_ZERO) ||
            (ulParity == UART_CONFIG_PAR_ODD) ||
            (ulParity == UART_CONFIG_PAR_ONE)
           );

    //
    // Set the parity mode.
    //
    xHWREG(ulBase + USART_LCR) = ((xHWREG(ulBase + USART_LCR) &
                                    ~(USART_LCR_PBE | USART_LCR_EPE |
                                      USART_LCR_SPE)) | ulParity);
}

//*****************************************************************************
//
//! \brief Get the type of parity mode currently being used.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function gets the type of parity used for transmitting data and
//! expected when receiving data.
//!
//! \return Returns the current parity settings, specified as one of
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD,
//! \b UART_CONFIG_PAR_ONE, or \b UART_CONFIG_PAR_ZERO.
//
//*****************************************************************************
unsigned long
UARTParityModeGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the current parity setting.
    //
    return(xHWREG(ulBase + USART_LCR) &
           (USART_LCR_PBE | USART_LCR_EPE | USART_LCR_SPE));
}

//*****************************************************************************
//
//! \brief Set the RX FIFO level.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulRxLevel is the transmit FIFO interrupt level, specified as one of
//! \b UART_FIFO_1BYTES, \b UART_FIFO_4BYTES, \b UART_FIFO_8BYTES,
//! \b UART_FIFO_14BYTES
//!
//! This function sets the FIFO level at which  receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOTriggerLevelSet(unsigned long ulBase, unsigned long ulRxLevel)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Sets the RX FIFO level.
    //
    xHWREG(ulBase + USART_FCR) &= (~(USART_FCR_RFTL_M));
    xHWREG(ulBase + USART_FCR) |= ((ulRxLevel));
}

//*****************************************************************************
//
//! \brief Gets the Rx FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulRxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of 
//! \b UART_FIFO_1BYTES, \b UART_FIFO_4BYTES, \b UART_FIFO_8BYTES,
//! \b UART_FIFO_14BYTES
//!
//! This function gets the Rx FIFO level at which receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************

unsigned long
UARTFIFOTriggerLevelGet(unsigned long ulBase)
{
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Read the FIFO level register.
    //
    ulTemp = xHWREG(ulBase + USART_FCR);

    //
    // Extract the transmit and receive FIFO levels.
    //
    ulTemp = ulTemp & USART_FCR_RFTL_M;

    return ulTemp;
}

//*****************************************************************************
//
//! \brief Set the configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//!
//! This function configures the UART for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter and the data
//! format in the \e ulConfig parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_9,select from eight to five data
//! bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE, and \b UART_CONFIG_PAR_ZERO
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigSetExpClk(unsigned long ulBase, 
                    unsigned long ulBaud, unsigned long ulConfig)
{
    unsigned long ulExtClk, ulDiv;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    xASSERT(ulBaud != 0);

    //
    // Reset UART.
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_UART0);

    //
    // Tx FIFO Reset & Rx FIFO Reset & FIFO Mode Enable .
    //    
    xHWREG(ulBase + USART_FCR) |= USART_FCR_RX_RST | USART_FCR_TX_RST;

    //
    // Set Parity & Data bits & Stop bits .
    //  
    xHWREG(ulBase + USART_LCR) = ulConfig;

    ulExtClk = UARTCLkGet();

    //
    // Get baud-rate divisor.
    //
    ulDiv = ulExtClk / ulBaud;

    xHWREG(ulBase + USART_BAUD) &= ~USART_BAUD_BRD_M;
    xHWREG(ulBase + USART_BAUD) |= (ulDiv & USART_BAUD_BRD_M);
}

//*****************************************************************************
//
//! \brief Get the current configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulBaud is a pointer to storage for the baud rate.
//! \param pulConfig is a pointer to storage for the data format.
//!
//! The baud rate and data format for the UART is determined, given an
//! explicitly provided peripheral clock (hence the ExpClk suffix).  The
//! returned baud rate is the actual baud rate; it may not be the exact baud
//! rate requested or an "official" baud rate.  The data format returned in
//! \e pulConfig is enumerated the same as the \e ulConfig parameter of
//! UARTConfigSetExpClk().
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigGetExpClk(unsigned long ulBase, 
                    unsigned long *pulBaud, unsigned long *pulConfig)
{
    unsigned long ulBaud,ulExtClk;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Compute the baud rate.
    //
    ulBaud = xHWREG(ulBase + USART_BAUD);
    ulExtClk = UARTCLkGet();

    *pulBaud = ulExtClk/(ulBaud & USART_BAUD_BRD_M);

    //
    // Get the parity, data length, and number of stop bits.
    //
    *pulConfig = (xHWREG(ulBase + USART_LCR) &
                  (USART_LCR_SPE | USART_LCR_WLS_M | USART_LCR_NSB |
                   USART_LCR_EPE | USART_LCR_PBE));
}

//*****************************************************************************
//
//! \brief Set the Mode of UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulUartMode is the mode value.
//!
//! The \e ulUartMode parameter must be only one of the following values:
//! \b USART_FUN_SEL_USART_EN, \b USART_FUN_SEL_IRDA_EN, \b USART_FUN_SEL_SYN_EN,
//! \b USART_FUN_SEL_RS485_EN.
//! \return None.
//
//*****************************************************************************
void
UARTModeSet(unsigned long ulBase, unsigned long ulUartMode)
{

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    //
    // Check the arguments.
    //
    xASSERT((ulUartMode == USART_FUN_SEL_USART_EN)||
            (ulUartMode == USART_FUN_SEL_RS485_EN)||
            (ulUartMode == USART_FUN_SEL_IRDA_EN)||
            (ulUartMode == USART_FUN_SEL_SYN_EN)
            );
    //
    // Select the mode of UART.
    //
    xHWREG(ulBase + USART_MDR) &= ~USART_FUN_SEL_M;
    xHWREG(ulBase + USART_MDR) |= ulUartMode;
}

//*****************************************************************************
//
//! \brief Set the Transfer Mode of UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulUartTransferMode is the transfer mode value.
//!
//! The \e ulUartTransferMode parameter must be only one of the following values:
//! \b USART_MDR_MSB, \b USART_MDR_LSB.
//! \return None.
//
//*****************************************************************************
void
UARTTransferModeSet(unsigned long ulBase, unsigned long ulUartTransferMode)
{

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    //
    // Check the arguments.
    //
    xASSERT((ulUartTransferMode == USART_MDR_MSB)||
            (ulUartTransferMode == USART_MDR_LSB)
            );
    //
    // Select the transfer mode of UART.
    //
    xHWREG(ulBase + USART_MDR) &= ~USART_MDR_MSB;
    xHWREG(ulBase + USART_MDR) |= ulUartTransferMode;
}
//*****************************************************************************
//
//! \brief Enable SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param bEnable is a boolean that is \b true if Enable IrDA and 
//! \b false if not.
//!
//! Enables the SIREN control bit for IrDA mode on the UART. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnableIrDA(unsigned long ulBase, xtBoolean bEnable)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
	if(bEnable)
	{
        //
        // Enable SIR.
        //
        xHWREG(ulBase + USART_IRCR) |= USART_IRCR_IRDA_EN;
    }
	else
	{
        //
        // Disable SIR .
        //
        xHWREG(ulBase + USART_IRCR) &= ~(USART_IRCR_IRDA_EN);
	}
}

//*****************************************************************************
//
//! \brief Open SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulConfig is the Config of the UART port in IrDA mode.Please refer to 
//!  HT32F1755_UART_IrDA_Config in xuart.h
//!
//! Open the SIREN control bit for IrDA mode on the UART. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTIrDAConfig(unsigned long ulBase, unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Set the Mode of IrDA.
    //
    UARTModeSet(ulBase, USART_FUN_SEL_IRDA_EN);
    xHWREG(ulBase + USART_IRCR) &= 0xFFFF00C0;
    xHWREG(ulBase + USART_IRCR) |= ulConfig;
}

//*****************************************************************************
//
//! \brief Enables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//! \param ulMode is the IrDA mode. 
//!
//! This function configures the UART IrDA for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter,  the data
//! format in the \e ulConfig parameter, and the ulMode is provided in the
//! \e ulMode parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b xUART_CONFIG_WLEN_8,
//! \b xUART_CONFIG_WLEN_7, select from 7 to 8 bits per byte(respectively).
//! \bX UART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE,  and
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit, 
//! even parity bit, odd parity bit, parity bit always one, and 
//! parity bit always zero, respectively).
//!
//! The \e ulMode parameter can be values:
//! - \b xUART_IRDA_MODE_NORMAL     - IrDA normal mode
//! - \b xUART_IRDA_MODE_LOW_POWER  - IrDA low pwer mode
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
void 
xUARTIrDAConfig(unsigned long ulBase, unsigned long ulBaud, 
                unsigned long ulConfig, unsigned long ulMode)
{
    unsigned long ulExtClk, ulDiv;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    xASSERT((ulMode == xUART_IRDA_MODE_NORMAL)||
            (ulMode == xUART_IRDA_MODE_LOW_POWER)
           );

    //
    // Reset UART.
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_UART0);

    //
    // Tx FIFO Reset & Rx FIFO Reset & FIFO Mode Enable .
    //    
    xHWREG(ulBase + USART_FCR) |= USART_FCR_RX_RST | USART_FCR_TX_RST;

    //
    // Set Parity & Data bits & Stop bits.
    //  
    xHWREG(ulBase + USART_LCR) = ulConfig;

    ulExtClk = UARTCLkGet();
    //
    // Get baud-rate divisor.
    //
    ulDiv = ulExtClk / ulBaud;

    xHWREG(ulBase + USART_BAUD) &= ~USART_BAUD_BRD_M;
    xHWREG(ulBase + USART_BAUD) |= (ulDiv & USART_BAUD_BRD_M);

    //
    // Set the Mode of IrDA.
    //
    UARTModeSet(ulBase, USART_FUN_SEL_IRDA_EN);
    //
    // Set IrDA Mode
    //
    xHWREG(ulBase + USART_IRCR) |= ulMode;
}

//*****************************************************************************
//
//! \brief Get to know the Tx FIFO is Empty or not from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get to know the Tx FIFO is Empty or not from the specified port.
//!
//! \return Returns the xtrue if Tx FIFO is Empty or returns xfalse
//! \e xtBoolean.
//
//*****************************************************************************
xtBoolean
UARTFIFOTxIsEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the Tx FIFO is empty or not.
    //
    return((xHWREG(ulBase + USART_LSR) & USART_LSR_TX_FIFO_EMPTY) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get to know the Rx FIFO is Empty or not from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get to know the Rx FIFO is Empty or not from the specified port.
//!
//! \return Returns the xtrue if Rx FIFO is Empty or returns xfalse
//! \e xtBoolean.
//
//*****************************************************************************
xtBoolean
UARTFIFORxIsEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the Rx FIFO is empty or not.
    //
    return((xHWREG(ulBase + USART_LSR) & USART_LSR_RXFIFO_READY) ? xfalse : xtrue);
}

//*****************************************************************************
//
//! \brief Receive a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get a character from the receive FIFO for the specified port.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.  A \b -1 is returned if there are no characters present in the
//! receive FIFO.  The UARTCharsAvail() function should be called before
//! attempting to call this function.
//
//*****************************************************************************
long
UARTCharGetNonBlocking(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // See if there are any characters in the receive FIFO.
    //
    if(xHWREG(ulBase + USART_LSR) & USART_LSR_RXFIFO_READY)
    {
        //
        // Read and return the next character.
        //
        return(xHWREG(ulBase + USART_RBR));
    }
    else
    {
        //
        // There are no characters, so return a failure.
        //
        return(-1);
    }
}

//*****************************************************************************
//
//! \brief Wait for a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.  If there
//! are no characters available, this function waits until a character is
//! received before returning.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.
//
//*****************************************************************************
long
UARTCharGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until a char is available.
    //
    while(!(xHWREG(ulBase + USART_LSR) & USART_LSR_RXFIFO_READY))
    {
    }

    //
    // Now get the char.
    //
    return(xHWREG(ulBase + USART_RBR));
}

//*****************************************************************************
//
//! \brief Read ulLength characters from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucBuffer is the point of read buffer.
//! \param ulBase is the length of read buffer.
//!
//! Read some character from the receive FIFO for the specified port.  If there
//! are no characters available, this function waits until a character is
//! received before returning.
//!
//! \return xtrue
//
//*****************************************************************************
void
UARTBufferRead(unsigned long ulBase, unsigned char *ucBuffer,
               unsigned long ulLength)
{
    unsigned long ulCount;
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until a char is available.
    //
    for (ulCount=0; ulCount<ulLength; ulCount++)
    {
        while(!(xHWREG(ulBase + USART_LSR) & USART_LSR_RXFIFO_READY))
        {
        }
        ucBuffer[ulCount] = xHWREG(ulBase + USART_RBR);
    }
}

//*****************************************************************************
//
//! \brief Send a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit FIFO for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b false is returned, and the application must retry the function later.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit FIFO or \b false if there was no space available in the transmit
//! FIFO.
//
//*****************************************************************************
xtBoolean
UARTCharPutNonBlocking(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // See if there is space in the transmit FIFO.
    //
    if(xHWREG(ulBase + USART_LSR) & USART_LSR_TX_FIFO_EMPTY)
    {
        //
        // Write this character to the transmit FIFO.
        //
        xHWREG(ulBase + USART_THR) = ucData;

        //
        // Success.
        //
        return(xtrue);
    }
    else
    {
        //
        // There is no space in the transmit FIFO, so return a failure.
        //
        return(xfalse);
    }
}

//*****************************************************************************
//
//! \brief Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Sends the character \e ucData to the transmit FIFO for the specified port.
//! If there is no space available in the transmit FIFO, this function waits
//! until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
void
UARTCharPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until space is available.
    //
    while(!(xHWREG(ulBase + USART_LSR) & USART_LSR_TX_FIFO_EMPTY))
    {
    }

    //
    // Send the char.
    //
    xHWREG(ulBase + USART_THR) = ucData;
}

//*****************************************************************************
//
//! \brief Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Sends the character \e ucData to the transmit FIFO for the specified port.
//! If there is no space available in the transmit FIFO, this function waits
//! until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
void
UARTBufferWrite(unsigned long ulBase, unsigned char *ucBuffer,
                unsigned long ulLength)
{
    
    unsigned long ulCount;
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until a char is available.
    //
    for (ulCount=0; ulCount<ulLength; ulCount++)
    {
        while(!(xHWREG(ulBase + USART_LSR) & USART_LSR_TX_FIFO_EMPTY))
        {
        }
        xHWREG(ulBase + USART_THR) = ucBuffer[ulCount];
    }
}

//*****************************************************************************
//
//! \brief Causes a BREAK to be sent.
//!
//! \param ulBase is the base address of the UART port.
//! \param bBreakState controls the output level.
//!
//! Calling this function with \e bBreakState set to \b true asserts a break
//! condition on the UART.  Calling this function with \e bBreakState set to
//! \b false removes the break condition.  For proper transmission of a break
//! command, the break must be asserted for at least two complete frames.
//!
//! \return None.
//
//*****************************************************************************
void
UARTBreakCtl(unsigned long ulBase, xtBoolean bBreakState)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Set the break condition as requested.
    //
    xHWREG(ulBase + USART_LCR) = (bBreakState ?
                                 (xHWREG(ulBase + USART_LCR) | USART_LCR_BCB) :
                                 (xHWREG(ulBase + USART_LCR) & ~(USART_LCR_BCB)));
}

//*****************************************************************************
//
//! \brief Enable individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//! - \b UART_INT_RTO    - Rx Time out Interrupt
//! - \b UART_INT_MOS    - RModem Status Interrupt
//! - \b UART_INT_RLS    - Receive Line Status Interrupt
//! - \b UART_INT_THRE   - Transmit Holding Register Empty
//! - \b UART_INT_RHRE   - Receive Holding Register Empty
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable the specified interrupts.
    //
    xHWREG(ulBase + USART_IER) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified UART Port.
//!
//! \param ulPort is the base address of the UART port.
//! \param xtI2CCallback is callback for the specified UART Port.
//!
//! Init interrupts callback for the specified UART Port.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntCallbackInit(unsigned long ulBase, 
                    xtEventCallback xtUARTCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    if (ulBase == UART0_BASE)
    {
        g_pfnUARTHandlerCallbacks[0] = xtUARTCallback;
    }
    else
    {
        g_pfnUARTHandlerCallbacks[1] = xtUARTCallback;    
    }
}

//*****************************************************************************
//
//! \brief Get individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! If the indicated UART interrupt sources, return xtrue, otherwise return 
//! xfalse.
//!
//! The \e ulIntFlags parameter is the one of any of the following:
//!
//! - \b UART_INT_RTO    - Rx Time out Interrupt
//! - \b UART_INT_MOS    - RModem Status Interrupt
//! - \b UART_INT_RLS    - Receive Line Status Interrupt
//! - \b UART_INT_THRE   - Transmit Holding Register Empty
//! - \b UART_INT_RHRE   - Receive Holding Register Empty
//!
//! \return If the indicated UART interrupt sources, return xtrue, otherwise return 
//! xfalse.
//
//*****************************************************************************
xtBoolean
UARTIntEnableGet(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Get enable the specified interrupts.
    //
    return (xHWREG(ulBase + USART_IER) & (ulIntFlags & 0xF)) ? xtrue : xfalse;
}

//*****************************************************************************
//
//! \brief Disables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to UARTIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable the specified interrupts.
    //
    xHWREG(ulBase + USART_IER) &= ~(ulIntFlags);
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! \param ulBase is the base address of the UART port.
//! \param bMasked is \b false if the raw interrupt status is required and
//! \b true if the masked interrupt status is required.
//!
//! This returns the interrupt status for the specified UART.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in UARTIntEnable().
//
//*****************************************************************************
unsigned long
UARTIntStatusGet(unsigned long ulBase, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(xHWREG(ulBase + USART_IIR));
    }
    else
    {
        return(xHWREG(ulBase + USART_IIR));
    }
}

//*****************************************************************************
//
//! \brief Clear UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified UART interrupt sources are cleared, so that they no longer
//! assert.  This function must be called in the interrupt handler to keep the
//! interrupt from being recognized again immediately upon exit.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to UARTIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags)
{

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Clear the requested interrupt sources.
    //
    if ((ulIntFlags & UART_INT_RLS) == UART_INT_RLS)
    {
        xHWREG(ulBase + USART_LSR);
    }
    if ((ulIntFlags & UART_INT_THRE) == UART_INT_THRE)
    {
        xHWREG(ulBase + USART_THR) = 0x55;
    }
    if ((ulIntFlags & UART_INT_RHRE) == UART_INT_RHRE)
    {
        xHWREG(ulBase + USART_RBR);
    }
    if ((ulIntFlags & UART_INT_MOS) == UART_INT_MOS)
    {
        xHWREG(ulBase + USART_MSR);
    }
    if ((ulIntFlags & UART_INT_RTO) == UART_INT_RTO)
    {
        xHWREG(ulBase + USART_RBR);
    }
}

//*****************************************************************************
//
//! \brief Sets the states of the RTS modem control signals and trigger level.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulControl is a bit-mapped flag indicating how the modem control bits
//! should be set.
//!
//! Sets the states of the RTS modem handshake outputs from the UART.
//!
//! The \e ulControl parameter is the logical OR of any of the following:
//!
//! - \b USART_MCR_DTR_L - The Modem Control DTR signal on low level triggered
//! - \b USART_MCR_RTS_L - The Modem Control RTS signal on low level triggered
//! - \b USART_MCR_DTR_H - The Modem Control DTR signal on high level triggered
//! - \b USART_MCR_RTS_H - The Modem Control RTS signal on high level triggered
//!
//! \return None.
//
//*****************************************************************************
void
UARTModemControlSet(unsigned long ulBase, unsigned long ulControl)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    //
    // Enable hardware flow control
    //
    xHWREG(ulBase + USART_MCR) |= USART_MCR_HFC_EN; 
    //
    // Set the appropriate modem control output bits.
    //
    xHWREG(ulBase + USART_MCR) &= 0xFFFFFFFC;
    xHWREG(ulBase + USART_MCR) |= ulControl;
}

//*****************************************************************************
//
//! \brief Gets the states of the RTS modem control signals and trigger level.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get the states of the RTS modem handshake outputs from the UART.
//!
//! The \e ulControl parameter is the logical OR of any of the following:
//!
//!
//! \return None.
//
//*****************************************************************************
unsigned long
UARTModemControlGet(unsigned long ulBase)
{
    unsigned long ulRal = 0;
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
	ulRal = xHWREG(ulBase + USART_MCR) & (~USART_MCR_HFC_EN);

    return ulRal;
}

//*****************************************************************************
//
//! \brief Get the current status of modem.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This returns the modem.status for the specified UART.
//!
//! \return Returns the current modem status.
//! \b USART_MSR_DDTSF, \b USART_MSR_DDCTSF, \b USART_MSR_RIS, \b USART_MSR_CTSS,
//! \b USART_MSR_DCTSF, \b USART_MSR_DSRS, \b USART_MSR_DCDS, \b USART_MSR_DRISF.
//! 
//
//*****************************************************************************
unsigned long
UARTModemStatusGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return either the modem status.
    //
    return(xHWREG(ulBase + USART_MSR));
}

//*****************************************************************************
//
//! \brief Gets current receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns the current state of each of the 3 receiver error
//! sources.
//!
//! \return Returns a logical OR combination of the receiver error flags,
//! \b USART_LSR_PARITY_ERROR_FLAG, \b USART_LSR_FRAMING_ERROR_FLAG,
//! \b USART_LSR_OVERRUN_FLAG and \b USART_LSR_BREAK_INT_FLAG.
//
//*****************************************************************************
unsigned long
UARTRxErrorGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the current value of the receive status register.
    //
    return(xHWREG(ulBase + USART_LSR) & 0x0000001E);
}

//*****************************************************************************
//
//! \brief Clears all reported receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function is used to clear all receiver error conditions reported via
//! UARTRxErrorGet().  If using the overrun, framing error, parity error or
//! break interrupts, this function must be called after clearing the interrupt
//! to ensure that later errors of the same type trigger another interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
UARTRxErrorClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Any Read Error Clear Register will clear all bits which are currently set.
    //
    xHWREG(ulBase + USART_LSR);
}

//*****************************************************************************
//
//! \brief Sets the Rx Time Out Value.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulValue Time out value
//!
//! Sets the Rx Time Out Value
//!
//! \return None.
//
//*****************************************************************************
void
UARTRxTimeOutSet(unsigned long ulBase, unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulValue < 128);

    //
    // Set the flow control mode as requested.   
    //
    xHWREG(ulBase + USART_TPR) &= ~USART_TPR_RTOIC_M;
    xHWREG(ulBase + USART_TPR) |= ulValue;

    xHWREG(ulBase + USART_TPR) |= USART_TPR_RTOI_EN;
}

//*****************************************************************************
//
//! \brief Enables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to enable. it is the logical OR of 
//! these values: \b UART_BLOCK_UART, \b UART_BLOCK_TX, \b UART_BLOCK_RX.
//!
//! Sets the UARTEN, or TXE or RXE bits.
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnable(unsigned long ulBase, unsigned long ulBlock)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable RX | TX | the UART.
    //
    UARTModeSet(ulBase, USART_FUN_SEL_USART_EN);
    xHWREG(ulBase + USART_FCR) |= USART_FCR_TX_EN | USART_FCR_RX_EN;
}


//*****************************************************************************
//
//! \brief Open 485 mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ul485Config is the Config of the UART port in 485 mode.
//!
//! Open the 485 mode for the UART.
//!
//! The \e ul485Config parameter is the UR_RTS/TXE pin Polarity of values:
//! \b USART_RS485CR_TXEP, \b USART_RS485CR_TXEN, \b USART_RS485CR_NMM_EN,
//! \b USART_RS485CR_AAD_EN, and USART_RS485CR_ADDMATCH_M.
//!
//! \return None.
//
//*****************************************************************************
void
UART485Config(unsigned long ulBase, unsigned long ulBaud,
              unsigned long ul485Config, unsigned long ulUARTConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    //
    // Set baud, word length, even parity, stop bits.
    //
    UARTConfigSetExpClk(ulBase, ulBaud, ulUARTConfig);
    
    //
    // Enable 485.
    //
    UARTModeSet(ulBase, USART_FUN_SEL_RS485_EN);
    xHWREG(ulBase + USART_RS485CR) &= 0xFFFF00F0;
    xHWREG(ulBase + USART_RS485CR) |= ul485Config;

}

//*****************************************************************************
//
//! \brief Open Synchronous mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulSYNConfig is the Config of the UART port in Synchronous mode.
//!
//! Open the Synchronous mode for the UART.
//!
//! The \e ulSYNConfig parameter is the logical OR of three values: Clock Enable
//! bit, Clock Phase bit, and Clock Polarity bit.  \b USART_SYNCR_CPO_L,
//! \b USART_SYNCR_CPO_H,USART_SYNCR_CPS_F,USART_SYNCR_CPS_S,USART_SYNCR_CLK_EN.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSyncModeConfig(unsigned long ulBase, unsigned long ulBaud,
              unsigned long ulSYNConfig, unsigned long ulUARTConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    //
    // Set baud, word length, even parity, stop bits.
    //
    UARTConfigSetExpClk(ulBase, ulBaud, ulUARTConfig);
    
    //
    // Enable Synchronous mode.
    //
    UARTModeSet(ulBase, USART_FUN_SEL_SYN_EN);
    xHWREG(ulBase + USART_SYNCR) |= ulSYNConfig;

}

//*****************************************************************************
//
//! \brief Enable USART DMA mode.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulDMAMode is the mode of the UART DMA mode.
//!
//! Set DMA mode for the USART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDMAModeEnable(unsigned long ulBase, unsigned long ulDMAMode)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    xASSERT((ulDMAMode == USART_DMA_RX) || (ulDMAMode == USART_DMA_TX));

    //
    // Set DMA mode for USART
    //
    xHWREG(ulBase + USART_MDR) |= ulDMAMode;
}

//*****************************************************************************
//
//! \brief Disable USART DMA mode.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulDMAMode is the mode of the UART DMA mode.
//!
//! Disable DMA mode for the USART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDMAModeDisable(unsigned long ulBase, unsigned long ulDMAMode)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    xASSERT((ulDMAMode == USART_DMA_RX) || (ulDMAMode == USART_DMA_TX));

    //
    // Disable DMA mode for USART
    //
    xHWREG(ulBase + USART_MDR) &= ~ulDMAMode;
}

//*****************************************************************************
//
//! \brief Get USART FIFO Status.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulFIFOType is the type of the UART FIFO.
//!
//!  Get USART FIFO Status.
//!
//! \return RX FIFO Contains Status or TX FIFO Contains Status.
//
//*****************************************************************************
unsigned long
UARTFIFOStatusGet(unsigned long ulBase, unsigned long ulFIFOType)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
    xASSERT((ulFIFOType == USART_FIFO_RX) || (ulFIFOType == USART_FIFO_TX));

    //
    // Get FIFO status
    //
    if(ulFIFOType == USART_FIFO_RX)
    {
        return (xHWREG(ulBase + USART_FSR) & USART_FSR_RXFS_M);
    }
    else
    {
        return ((xHWREG(ulBase + USART_FSR) & USART_FSR_TXFS_M) >> USART_FSR_RXFS_S);
    }
}
