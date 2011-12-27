//*****************************************************************************
//
//! \file xuart.c
//! \brief Driver for the UART.
//! \version V2.1.1.0
//! \date 11/14/2011
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

#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xhw_types.h"
#include "xhw_uart.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xuart.h"

#if xUART_CONFIG_DMA_INT
#include "xhw_dma.h"
#include "xdma.h"
#endif

#if !xUART_CONFIG_DMA_INT
static xtEventCallback g_pfnUARTHandlerCallbacks[3] = {0};
#endif

//*****************************************************************************
//
// The system clock divider defining the maximum baud rate supported by the
// UART.
//
//*****************************************************************************
#define UART_CLK_DIVIDER        ((CLASS_IS_SANDSTORM ||                       \
                                  (CLASS_IS_FURY && REVISION_IS_A2) ||        \
                                  (CLASS_IS_DUSTDEVIL && REVISION_IS_A0)) ?   \
                                 16 : 8)

//*****************************************************************************
//
//! \internal
//! \brief Checks a UART base address.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function determines if a UART port base address is valid.
//!
//! \return Returns \b xtrue if the base address is valid and \b xfalse
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
UARTBaseValid(unsigned long ulBase)
{
    return((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));
}
#endif

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
           (ulParity == UART_CONFIG_PAR_ODD) ||
           (ulParity == UART_CONFIG_PAR_ONE) ||
           (ulParity == UART_CONFIG_PAR_ZERO));

    //
    // Set the parity mode.
    //
    xHWREG(ulBase + UART_LCRH) = ((xHWREG(ulBase + UART_LCRH) &
                                    ~(UART_LCRH_SPS | UART_LCRH_EPS |
                                      UART_LCRH_PEN)) | ulParity);
}

//*****************************************************************************
//
//! \brief Gets the type of parity currently being used.
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
    return(xHWREG(ulBase + UART_LCRH) &
           (UART_LCRH_SPS | UART_LCRH_EPS | UART_LCRH_PEN));
}

//*****************************************************************************
//
//! \brief Sets the Tx FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulTxLevel is the transmit FIFO interrupt level, specified as one of
//! \b xUART_FIFO_TX_0 (Tx FIFO is completely empty),
//! \b xUART_FIFO_TX_1, \b xUART_FIFO_TX_2, \b xUART_FIFO_TX_4,
//! \b xUART_FIFO_TX_6, or \b xUART_FIFO_TX_7.
//!
//! This function sets the FIFO level at which transmit interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
xUARTFIFOTxLevelSet(unsigned long ulBase, unsigned long ulTxLevel)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulTxLevel == xUART_FIFO_TX_0) ||
           (ulTxLevel == xUART_FIFO_TX_1) ||
           (ulTxLevel == xUART_FIFO_TX_2) ||
           (ulTxLevel == xUART_FIFO_TX_4) ||
           (ulTxLevel == xUART_FIFO_TX_6) ||
           (ulTxLevel == xUART_FIFO_TX_7));

    if (ulTxLevel == xUART_FIFO_TX_0)
    {
        //
        // Set  the EOT bit of the UART control register as appropriate.
        //
        xHWREG(ulBase + UART_CTL) = ((xHWREG(ulBase + UART_CTL) &
                                      ~(UART_TXINT_MODE_EOT |
                                        UART_TXINT_MODE_FIFO)) | 
                                      UART_TXINT_MODE_EOT);
    }
    else
    {

        //
        // Clear  the EOT bit of the UART control register as appropriate.
        //
        xHWREG(ulBase + UART_CTL) = ((xHWREG(ulBase + UART_CTL) &
                                      ~(UART_TXINT_MODE_EOT |
                                        UART_TXINT_MODE_FIFO)) | 
                                      UART_TXINT_MODE_FIFO);

        //
        // Set the FIFO interrupt levels.
        //
        xHWREG(ulBase + UART_IFLS) = ulTxLevel;
    }

}

//*****************************************************************************
//
//! \brief Sets the Rx FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulRxLevel is the receive FIFO interrupt level, specified as one of
//! \b xUART_FIFO_RX_1, \b xUART_FIFO_RX_2, \b xUART_FIFO_RX_4,
//! \b xUART_FIFO_RX_6, or \b xUART_FIFO_RX_7.
//!
//! This function sets the FIFO level at which receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
xUARTFIFORxLevelSet(unsigned long ulBase, unsigned long ulRxLevel)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulRxLevel == xUART_FIFO_RX_1) ||
           (ulRxLevel == xUART_FIFO_RX_2) ||
           (ulRxLevel == xUART_FIFO_RX_4) ||
           (ulRxLevel == xUART_FIFO_RX_6) ||
           (ulRxLevel == xUART_FIFO_RX_7));

    //
    // Set the FIFO interrupt levels.
    //
    xHWREG(ulBase + UART_IFLS) = ulRxLevel;
}

//*****************************************************************************
//
//! \brief Sets the FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulTxLevel is the transmit FIFO interrupt level, specified as one of
//! \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8, \b UART_FIFO_TX4_8,
//! \b UART_FIFO_TX6_8, or \b UART_FIFO_TX7_8.
//! \param ulRxLevel is the receive FIFO interrupt level, specified as one of
//! \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8, \b UART_FIFO_RX4_8,
//! \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function sets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOLevelSet(unsigned long ulBase, unsigned long ulTxLevel,
                 unsigned long ulRxLevel)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulTxLevel == UART_FIFO_TX1_8) ||
           (ulTxLevel == UART_FIFO_TX2_8) ||
           (ulTxLevel == UART_FIFO_TX4_8) ||
           (ulTxLevel == UART_FIFO_TX6_8) ||
           (ulTxLevel == UART_FIFO_TX7_8));
    xASSERT((ulRxLevel == UART_FIFO_RX1_8) ||
           (ulRxLevel == UART_FIFO_RX2_8) ||
           (ulRxLevel == UART_FIFO_RX4_8) ||
           (ulRxLevel == UART_FIFO_RX6_8) ||
           (ulRxLevel == UART_FIFO_RX7_8));

    //
    // Set the FIFO interrupt levels.
    //
    xHWREG(ulBase + UART_IFLS) = ulTxLevel | ulRxLevel;
}

//*****************************************************************************
//
//! \brief Gets the FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulTxLevel is a pointer to storage for the transmit FIFO level,
//! returned as one of \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8,
//! \b UART_FIFO_TX4_8, \b UART_FIFO_TX6_8, or \b UART_FIFO_TX7_8.
//! \param pulRxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8,
//! \b UART_FIFO_RX4_8, \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function gets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOLevelGet(unsigned long ulBase, unsigned long *pulTxLevel,
                 unsigned long *pulRxLevel)
{
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Read the FIFO level register.
    //
    ulTemp = xHWREG(ulBase + UART_IFLS);

    //
    // Extract the transmit and receive FIFO levels.
    //
    *pulTxLevel = ulTemp & UART_IFLS_TX_M;
    *pulRxLevel = ulTemp & UART_IFLS_RX_M;
}

//*****************************************************************************
//
//! \brief Sets the configuration of a UART.
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
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_6, and \b UART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_1 and \b UART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE, and \b UART_CONFIG_PAR_ZERO
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//! This function replaces the original UARTConfigSet() API and performs the
//! same actions.  A macro is provided in <tt>uart.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigSetExpClk(unsigned long ulBase, unsigned long ulBaud,
                    unsigned long ulConfig)
{
    unsigned long ulDiv;
    unsigned long ulUARTClk;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulBaud != 0); 
   
    //
    // Stop the UART.
    //
    UARTDisable(ulBase, UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX);

    //
    // Get the Uart clock, the same as the processor clock.
    //
    ulUARTClk = SysCtlClockGet();
    xASSERT(ulUARTClk >= (ulBaud * UART_CLK_DIVIDER));
    
    //
    // Is the required baud rate greater than the maximum rate supported
    // without the use of high speed mode?
    //
    if((ulBaud * 16) > ulUARTClk)
    {
        //
        // Enable high speed mode.
        //
        xHWREG(ulBase + UART_CTL) |= UART_CTL_HSE;

        //
        // Half the supplied baud rate to compensate for enabling high speed
        // mode.  This allows the following code to be common to both cases.
        //
        ulBaud /= 2;
    }
    else
    {
        //
        // Disable high speed mode.
        //
        xHWREG(ulBase + UART_CTL) &= ~(UART_CTL_HSE);
    }

    //
    // Compute the fractional baud rate divider.
    //
    ulDiv = (((ulUARTClk * 8) / ulBaud) + 1) / 2;

    //
    // Set the baud rate.
    //
    xHWREG(ulBase + UART_IBRD) = ulDiv / 64;
    xHWREG(ulBase + UART_FBRD) = ulDiv % 64;

    //
    // Set parity, data length, and number of stop bits.
    //
    xHWREG(ulBase + UART_LCRH) = ulConfig;

    //
    // Clear the flags register.
    //
    xHWREG(ulBase + UART_FR) = 0;

}

//*****************************************************************************
//
//! \brief Gets the current configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulBaud is a pointer to storage for the baud rate.
//! \param pulConfig is a pointer to storage for the data format.
//!
//! The baud rate and data format for the UART is determined, given an
//! explicitly provided peripheral clock (hence the ExpClk suffix).  The
//! returned baud rate is the actual baud rate; it may not be the exact baud
//! rate requested or an ``official'' baud rate.  The data format returned in
//! \e pulConfig is enumerated the same as the \e ulConfig parameter of
//! UARTConfigSetExpClk().
//!
//! This function replaces the original UARTConfigGet() API and performs the
//! same actions.  A macro is provided in <tt>uart.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigGetExpClk(unsigned long ulBase, unsigned long *pulBaud,
                     unsigned long *pulConfig)
{
    unsigned long ulInt, ulFrac;
    unsigned long ulUARTClk;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Get the Uart clock, the same as the processor clock.
    //
    ulUARTClk = SysCtlClockGet();
        
    //
    // Compute the baud rate.
    //
    ulInt = xHWREG(ulBase + UART_IBRD);
    ulFrac = xHWREG(ulBase + UART_FBRD);
    *pulBaud = (ulUARTClk * 4) / ((64 * ulInt) + ulFrac);

    //
    // See if high speed mode enabled.
    //
    if(xHWREG(ulBase + UART_CTL) & UART_CTL_HSE)
    {
        //
        // High speed mode is enabled so the actual baud rate is actually
        // double what was just calculated.
        //
        *pulBaud *= 2;
    }

    //
    // Get the parity, data length, and number of stop bits.
    //
    *pulConfig = (xHWREG(ulBase + UART_LCRH) &
                  (UART_LCRH_SPS | UART_LCRH_WLEN_M | UART_LCRH_STP2 |
                   UART_LCRH_EPS | UART_LCRH_PEN));
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
    xASSERT((ulBlock & ~(UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE)) == 0);

    //
    // Enable RX | TX | the UART.
    //
    xHWREG(ulBase + UART_CTL) |= ulBlock & (UART_CTL_UARTEN | UART_CTL_TXE |
                                   UART_CTL_RXE);
}

//*****************************************************************************
//
//! \brief Disables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to disable. it is the logical OR of 
//! these values: \b UART_BLOCK_UART, \b UART_BLOCK_TX, \b UART_BLOCK_RX.
//!
//! Waits for the end ofransmission of the current character,
//! Clears the UARTEN or TXE or RXE bits.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDisable(unsigned long ulBase, unsigned long ulBlock)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulBlock & ~(UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE)) == 0);

    //
    // Wait for end of TX.
    //
    while(xHWREG(ulBase + UART_FR) & UART_FR_BUSY)
    {
    }

    //
    // Disable the UART/TX/RX.
    //
    xHWREG(ulBase + UART_CTL) &= ~(UART_CTL_UARTEN | UART_CTL_TXE |
                                    UART_CTL_RXE);
}

//*****************************************************************************
//
//! \brief Enables the transmit and receive FIFOs.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This functions enables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable the FIFO.
    //
    xHWREG(ulBase + UART_LCRH) |= UART_LCRH_FEN;
}

//*****************************************************************************
//
//! \brief Disables the transmit and receive FIFOs.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This functions disables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFODisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable the FIFO.
    //
    xHWREG(ulBase + UART_LCRH) &= ~(UART_LCRH_FEN);
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
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_6, and \b UART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_1 and \b UART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE, and \b UART_CONFIG_PAR_ZERO
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//! The \e ulMode parameter can be values:
//! - \b UART_IRDA_MODE_NORMAL - IrDA normal mode
//! - \b UART_IRDA_MODE_LOW_POWER - IrDA low-power mode
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIrDAConfig(unsigned long ulBase, unsigned long ulBaud, 
            unsigned long ulConfig, unsigned long ulMode)
{
    unsigned long ulUARTClk;
    unsigned long ulDiv;
    
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulBaud != 0);

    //
    // Disable IrDA, and clear low-power mode flag
    //
    xHWREG(ulBase + UART_CTL) &= ~(UART_CTL_SIREN | UART_CTL_SIRLP);

    //
    // Set baud, parity, data length, and number of stop bits.
    //
    UARTConfigSetExpClk(ulBase, ulBaud, ulConfig);
    
    if(ulMode & UART_IRDA_MODE_MASK == UART_IRDA_MODE_NORMAL)
    {
        //
        // Get the Uart clock, the same as the processor clock.
        //
        ulUARTClk = SysCtlClockGet();
            
        //
        // Set low-power mode baud
        //
        ulDiv = ulUARTClk / (ulMode & ~UART_IRDA_MODE_MASK);
        xASSERT(ulDiv < 256);
        
        xHWREG(ulBase + UART_ILPR) = ulDiv;

        //
        // Set IrDA as low-power mode
        //
        xHWREG(ulBase + UART_CTL) |= (UART_CTL_SIRLP);
         
    }
}

//*****************************************************************************
//
//! \brief Enables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables the SIREN control bit for IrDA mode on the UART.  If the
//! \e bLowPower flag is set, then SIRLP bit will also be set.
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIrDAEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable RX , TX and  the UART.
    //
    xHWREG(ulBase + UART_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |
                                    UART_CTL_RXE);

    //
    // Enable SIR and SIRLP (if appropriate).
    //
    xHWREG(ulBase + UART_CTL) |= (UART_CTL_SIREN);
}

//*****************************************************************************
//
//! \brief Disables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the SIREN (IrDA) and SIRLP (Low Power) bits.
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIrDADisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable SIR and SIRLP (if appropriate).
    //
    xHWREG(ulBase + UART_CTL) &= ~(UART_CTL_SIREN);
}

//*****************************************************************************
//
//! \brief Config LIN mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the LIN mode.
//!
//! Config details on the UART LIN mode. This call  Configure the UART for 
//! 1 start bit, 8 data bits, no parity,  and 1 stop bit. 
//! and enable the Transmit FIFO as required by LIN.
//!
//! The \e ulConfig parameter is the logical OR of three values: 
//! the mode of LIN: \b UART_LIN_MODE_MASTER, \b UART_LIN_MODE_SLAVE.
//! the Sync Break Length when in master mode:
//! - \b UART_LIN_SYNC_BREAK_LEN_13 (default)
//! - \b UART_LIN_SYNC_BREAK_LEN_14
//! - \b UART_LIN_SYNC_BREAK_LEN_15
//! - \b UART_LIN_SYNC_BREAK_LEN_16
//!
//! \return None.
//
//*****************************************************************************
void
UARTLINConfig(unsigned long ulBase, unsigned long ulBaud,
            unsigned long ulConfig) 
{
    xASSERT(ulConfig & ~( UART_LIN_MODE_MASK | 
            UART_LIN_SYNC_BREAK_LEN_MASK) == 0);
    
    xASSERT(ulBaud > 0 && ulBaud <= 20000);
    
    //
    // Configure the UART for 1 start bit, 8 data bits, no parity, 
    // and 1 stop bit. Enable the Transmit FIFO.
    //
    UARTConfigSetExpClk(ulBase, ulBaud,                                
                        UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE |  
                        UART_CONFIG_STOP_1);
   
    xHWREG(ulBase + UART_LCTL) |= ulConfig; 
}

//*****************************************************************************
//
//! \brief Enables LIN mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables the LIN control bit for LIN mode on the UART. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTLINEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable RX , TX and  the UART.
    //
    xHWREG(ulBase + UART_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |
                                    UART_CTL_RXE);

    //
    // Enable the FIFO.
    //
    xHWREG(ulBase + UART_LCRH) |= UART_LCRH_FEN;
    
    //
    // Enable LIN mode.
    //
    xHWREG(ulBase + UART_CTL) |= (UART_CTL_LIN);
}

//*****************************************************************************
//
//! \brief Disables LIN mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the LIN bit.
//!
//! \return None.
//
//*****************************************************************************
void
UARTLINDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable LIN mode.
    //
    xHWREG(ulBase + UART_CTL) &= ~(UART_CTL_LIN);
}

//*****************************************************************************
//
//! \brief Config ISO 7816 smart card mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//!
//! Config the SMART control bit for ISO 7816 smart card mode on the UART.
//! This call  sets 8 bit word length and even parity as required by ISO
//! 7816.
//!
//! \note The availability of ISO 7816 smart card mode varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSmartCardConfig(unsigned long ulBase, unsigned long ulBaud)
{
    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(UARTBaseValid(ulBase));

    //
    // Set baud, 8 bit word length, even parity, 2 stop bits (even though the STP2
    // bit is ignored when in smartcard mode, this lets the caller read back
    // the actual setting in use).
    //
    UARTConfigSetExpClk(ulBase, ulBaud, 
                        UART_CONFIG_WLEN_8 |
                        UART_CONFIG_STOP_2 |
                        UART_CONFIG_PAR_EVEN);

}

//*****************************************************************************
//
//! \brief Enables ISO 7816 smart card mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables Uart, Rx, Tx and the SMART control bit for ISO 7816 T = 0 
//! smart card mode on the UART.
//!
//! \note The availability of ISO 7816 smart card mode varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//! You should Call UARTSmartCardConfig() before this function.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSmartCardEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable RX , TX and  the UART.
    //
    xHWREG(ulBase + UART_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |
                                    UART_CTL_RXE);
    //
    // Enable SMART mode.
    //
    xHWREG(ulBase + UART_CTL) |= UART_CTL_SMART;
}

//*****************************************************************************
//
//! \brief Disables ISO 7816 smart card mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the SMART (ISO 7816 smart card) bits in the UART control register.
//!
//! \note The availability of ISO 7816 smart card mode varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSmartCardDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable the SMART bit.
    //
    xHWREG(ulBase + UART_CTL) &= ~UART_CTL_SMART;
}

//*****************************************************************************
//
//! \brief Sets the states of the DTR and/or RTS modem control signals.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulControl is a bit-mapped flag indicating which modem control bits
//! should be set.
//!
//! Sets the states of the DTR or RTS modem handshake outputs from the UART.
//!
//! The \e ulControl parameter is the logical OR of any of the following:
//!
//! - \b UART_OUTPUT_DTR - The Modem Control DTR signal
//! - \b UART_OUTPUT_RTS - The Modem Control RTS signal
//!
//! \note The availability of hardware modem handshake signals varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
void
UARTModemControlSet(unsigned long ulBase, unsigned long ulControl)
{
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(ulBase == UART1_BASE);
    xASSERT((ulControl & ~(UART_OUTPUT_RTS | UART_OUTPUT_DTR)) == 0);

    //
    // Set the appropriate modem control output bits.
    //
    ulTemp = xHWREG(ulBase + UART_CTL);
    ulTemp |= (ulControl & (UART_OUTPUT_RTS | UART_OUTPUT_DTR));
    xHWREG(ulBase + UART_CTL) = ulTemp;
}

//*****************************************************************************
//
//! \brief Clears the states of the DTR and/or RTS modem control signals.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulControl is a bit-mapped flag indicating which modem control bits
//! should be set.
//!
//! Clears the states of the DTR or RTS modem handshake outputs from the UART.
//!
//! The \e ulControl parameter is the logical OR of any of the following:
//!
//! - \b UART_OUTPUT_DTR - The Modem Control DTR signal
//! - \b UART_OUTPUT_RTS - The Modem Control RTS signal
//!
//! \note The availability of hardware modem handshake signals varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
void
UARTModemControlClear(unsigned long ulBase, unsigned long ulControl)
{
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(ulBase == UART1_BASE);
    xASSERT((ulControl & ~(UART_OUTPUT_RTS | UART_OUTPUT_DTR)) == 0);

    //
    // Set the appropriate modem control output bits.
    //
    ulTemp = xHWREG(ulBase + UART_CTL);
    ulTemp &= ~(ulControl & (UART_OUTPUT_RTS | UART_OUTPUT_DTR));
    xHWREG(ulBase + UART_CTL) = ulTemp;
}

//*****************************************************************************
//
//! \brief Gets the states of the DTR and RTS modem control signals.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current states of each of the two UART modem control signals,
//! DTR and RTS.
//!
//! \note The availability of hardware modem handshake signals varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return Returns the states of the handshake output signals.  This will be a
//! logical logical OR combination of values \b UART_OUTPUT_RTS and
//! \b UART_OUTPUT_DTR where the presence of each flag indicates that the
//! associated signal is asserted.
//
//*****************************************************************************
unsigned long
UARTModemControlGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(ulBase == UART1_BASE);

    return(xHWREG(ulBase + UART_CTL) & (UART_OUTPUT_RTS | UART_OUTPUT_DTR));
}

//*****************************************************************************
//
//! \brief Gets the states of the RI, DCD, DSR and CTS modem status signals.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current states of each of the four UART modem status signals,
//! RI, DCD, DSR and CTS.
//!
//! \note The availability of hardware modem handshake signals varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return Returns the states of the handshake output signals.  This will be a
//! logical logical OR combination of values \b UART_INPUT_RI, \b
//! UART_INPUT_DCD, \b UART_INPUT_CTS and \b UART_INPUT_DSR where the
//! presence of each flag indicates that the associated signal is asserted.
//
//*****************************************************************************
unsigned long
UARTModemStatusGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(ulBase == UART1_BASE);

    return(xHWREG(ulBase + UART_FR) & (UART_INPUT_RI | UART_INPUT_DCD |
           UART_INPUT_CTS | UART_INPUT_DSR));
}

//*****************************************************************************
//
//! \brief Sets the UART hardware flow control mode to be used.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulMode indicates the flow control modes to be used.  This is a
//! logical OR combination of values \b UART_FLOWCONTROL_TX and \b
//! UART_FLOWCONTROL_RX to enable hardware transmit (CTS) and receive (RTS)
//! flow control or \b UART_FLOWCONTROL_NONE to disable hardware flow control.
//!
//! Sets the required hardware flow control modes.  If \e ulMode contains
//! flag \b UART_FLOWCONTROL_TX, data is only transmitted if the incoming CTS
//! signal is asserted. If \e ulMode contains flag \b UART_FLOWCONTROL_RX,
//! the RTS output is controlled by the hardware and is asserted only when
//! there is space available in the receive FIFO.  If no hardware flow control
//! is required, UART_FLOWCONTROL_NONE should be passed.
//!
//! \note The availability of hardware flow control varies with the Stellaris
//! part and UART in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFlowControlSet(unsigned long ulBase, unsigned long ulMode)
{
    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulMode & ~(UART_FLOWCONTROL_TX | UART_FLOWCONTROL_RX)) == 0);

    //
    // Set the flow control mode as requested.
    //
    xHWREG(ulBase + UART_CTL) = ((xHWREG(ulBase + UART_CTL) &
                                 ~(UART_FLOWCONTROL_TX |
                                   UART_FLOWCONTROL_RX)) | ulMode);
}

//*****************************************************************************
//
//! \brief Returns the UART hardware flow control mode currently in use.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current hardware flow control mode.
//!
//! \note The availability of hardware flow control varies with the Stellaris
//! part and UART in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return Returns the current flow control mode in use.  This is a
//! logical OR combination of values \b UART_FLOWCONTROL_TX if transmit
//! (CTS) flow control is enabled and \b UART_FLOWCONTROL_RX if receive (RTS)
//! flow control is in use.  If hardware flow control is disabled, \b
//! UART_FLOWCONTROL_NONE will be returned.
//
//*****************************************************************************
unsigned long
UARTFlowControlGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(!CLASS_IS_SANDSTORM && !CLASS_IS_FURY && !CLASS_IS_DUSTDEVIL);
    xASSERT(UARTBaseValid(ulBase));

    return(xHWREG(ulBase + UART_CTL) & (UART_FLOWCONTROL_TX |
                                         UART_FLOWCONTROL_RX));
}

//*****************************************************************************
//
//! \brief Sets the operating mode for the UART transmit interrupt.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulMode is the operating mode for the transmit interrupt.  It may be
//! \b UART_TXINT_MODE_EOT to trigger interrupts when the transmitter is idle
//! or \b UART_TXINT_MODE_FIFO to trigger based on the current transmit FIFO
//! level.
//!
//! This function allows the mode of the UART transmit interrupt to be set.  By
//! default, the transmit interrupt is asserted when the FIFO level falls past
//! a threshold set via a call to UARTFIFOLevelSet().  Alternatively, if this
//! function is called with \e ulMode set to \b UART_TXINT_MODE_EOT, the
//! transmit interrupt will only be asserted once the transmitter is completely
//! idle - the transmit FIFO is empty and all bits, including any stop bits,
//! have cleared the transmitter.
//!
//! \note The availability of end-of-transmission mode varies with the
//! Stellaris part in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
void
UARTTxIntModeSet(unsigned long ulBase, unsigned long ulMode)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulMode == UART_TXINT_MODE_EOT) ||
           (ulMode == UART_TXINT_MODE_FIFO));

    //
    // Set or clear the EOT bit of the UART control register as appropriate.
    //
    xHWREG(ulBase + UART_CTL) = ((xHWREG(ulBase + UART_CTL) &
                                 ~(UART_TXINT_MODE_EOT |
                                   UART_TXINT_MODE_FIFO)) | ulMode);
}

//*****************************************************************************
//
//! \brief Returns the current operating mode for the UART transmit interrupt.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns the current operating mode for the UART transmit
//! interrupt.  The return value will be \b UART_TXINT_MODE_EOT if the
//! transmit interrupt is currently set to be asserted once the transmitter is
//! completely idle - the transmit FIFO is empty and all bits, including any
//! stop bits, have cleared the transmitter.  The return value will be \b
//! UART_TXINT_MODE_FIFO if the interrupt is set to be asserted based upon the
//! level of the transmit FIFO.
//!
//! \note The availability of end-of-transmission mode varies with the
//! Stellaris part in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return Returns \b UART_TXINT_MODE_FIFO or \b UART_TXINT_MODE_EOT.
//
//*****************************************************************************
unsigned long
UARTTxIntModeGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the current transmit interrupt mode.
    //
    return(xHWREG(ulBase + UART_CTL) & (UART_TXINT_MODE_EOT |
                                         UART_TXINT_MODE_FIFO));
}

//*****************************************************************************
//
//! \brief Determines if there are any characters in the receive FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive FIFO.
//!
//! \return Returns \b xtrue if there is data in the receive FIFO or \b xfalse
//! if there is no data in the receive FIFO.
//
//*****************************************************************************
xtBoolean
UARTCharsAvail(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the availability of characters.
    //
    return((xHWREG(ulBase + UART_FR) & UART_FR_RXFE) ? xfalse : xtrue);
}

//*****************************************************************************
//
//! \brief Determines if there is any space in the transmit FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit FIFO.
//!
//! \return Returns \b xtrue if there is space available in the transmit FIFO
//! or \b xfalse if there is no space available in the transmit FIFO.
//
//*****************************************************************************
xtBoolean
UARTSpaceAvail(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the availability of space.
    //
    return((xHWREG(ulBase + UART_FR) & UART_FR_TXFF) ? xfalse : xtrue);
}

//*****************************************************************************
//
//! \brief Receives a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.
//!
//! This function replaces the original UARTCharNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
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
    if(!(xHWREG(ulBase + UART_FR) & UART_FR_RXFE))
    {
        //
        // Read and return the next character.
        //
        return(xHWREG(ulBase + UART_DR));
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
//! \brief Waits for a character from the specified port.
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
    while(xHWREG(ulBase + UART_FR) & UART_FR_RXFE)
    {
    }

    //
    // Now get the char.
    //
    return(xHWREG(ulBase + UART_DR));
}

//*****************************************************************************
//
//! \brief Sends a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit FIFO for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b xfalse is returned, and the application must retry the function later.
//!
//! This function replaces the original UARTCharNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns \b xtrue if the character was successfully placed in the
//! transmit FIFO or \b xfalse if there was no space available in the transmit
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
    if(!(xHWREG(ulBase + UART_FR) & UART_FR_TXFF))
    {
        //
        // Write this character to the transmit FIFO.
        //
        xHWREG(ulBase + UART_DR) = ucData;

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
    while(xHWREG(ulBase + UART_FR) & UART_FR_TXFF)
    {
    }

    //
    // Send the char.
    //
    xHWREG(ulBase + UART_DR) = ucData;
}

//*****************************************************************************
//
//! \brief Causes a BREAK to be sent.
//!
//! \param ulBase is the base address of the UART port.
//! \param bBreakState controls the output level.
//!
//! Calling this function with \e bBreakState set to \b xtrue asserts a break
//! condition on the UART.  Calling this function with \e bBreakState set to
//! \b xfalse removes the break condition.  For proper transmission of a break
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
    xHWREG(ulBase + UART_LCRH) =
        (bBreakState ?
         (xHWREG(ulBase + UART_LCRH) | UART_LCRH_BRK) :
         (xHWREG(ulBase + UART_LCRH) & ~(UART_LCRH_BRK)));
}

//*****************************************************************************
//
//! \brief Determines whether the UART transmitter is busy or not.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Allows the caller to determine whether all transmitted bytes have cleared
//! the transmitter hardware.  If \b xfalse is returned, the transmit FIFO is
//! empty and all bits of the last transmitted character, including all stop
//! bits, have left the hardware shift register.
//!
//! \return Returns \b xtrue if the UART is transmitting or \b xfalse if all
//! transmissions are complete.
//
//*****************************************************************************
xtBoolean
UARTBusy(unsigned long ulBase)
{
    //
    // Check the argument.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Determine if the UART is busy.
    //
    return((xHWREG(ulBase + UART_FR) & UART_FR_BUSY) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Init the UART Interrupt Callback function.
//!
//! \param ulBase is the base address of the UART.
//! \param pfnCallback is the callback function.
//!
//! When there is any UART intrrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent is the interrupt event..
//! - ulMsgParam not used, always 0.
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xUARTIntCallbackInit(unsigned long ulBase, 
                    xtEventCallback pfnCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    
#if !xUART_CONFIG_DMA_INT
    switch(ulBase)
    {
        case UART0_BASE:
        {
            g_pfnUARTHandlerCallbacks[0] = pfnCallback;
            break;
        }
        case UART1_BASE:
        {
            g_pfnUARTHandlerCallbacks[1] = pfnCallback;
            break;
        } 
        case UART2_BASE:
        {
            g_pfnUARTHandlerCallbacks[2] = pfnCallback;
            break;
        }         
            
    }
#endif    

}


//*****************************************************************************
//
//! \brief UART0 Interrupt Handler.
//!
//! If users want to user the UART0 Callback feature, Users should promise 
//! that the UART0 Handle in the vector table is UART0IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
UART0IntHandler(void)    
{
    unsigned long ulEventFlags;
    unsigned long ulBase = UART0_BASE;

#if xUART_CONFIG_DMA_INT
    xtEventCallback pfnCallback;
    unsigned long ulChannelID;
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
#endif    
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + UART_RIS);
    

    //
    // Clear Int flag
    //
    xHWREG(ulBase + UART_ICR) = ulEventFlags;

    //
    // Clear Error flag
    //
    xHWREG(ulBase + UART_ECR) = 0;
    
#if !(xUART_CONFIG_DMA_INT)
    //
    // Call Callback function
    //
    if(ulEventFlags && g_pfnUARTHandlerCallbacks[0])
    {
        g_pfnUARTHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    }

#else
    
    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
            
    //
    // Check DMA RX flag
    //
    if(xHWREG(ulBase + UART_DMACTL) & UART_DMA_RX)
    {
        ulChannelID = xDMA_REQUEST_UART0_RX & 0x1F;
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }

    //
    // Check DMA TX flag
    //
    if(xHWREG(ulBase + UART_DMACTL) & UART_DMA_TX)
    {
        ulChannelID = xDMA_REQUEST_UART0_TX & 0x1F;
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }    
    
#endif    
}

//*****************************************************************************
//
//! \brief UART1 Interrupt Handler.
//!
//! If users want to user the UART1 Callback feature, Users should promise 
//! that the UART1 Handle in the vector table is UART0IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
UART1IntHandler(void)    
{
    unsigned long ulEventFlags;
    unsigned long ulBase = UART1_BASE;

#if xUART_CONFIG_DMA_INT
    xtEventCallback pfnCallback;
    unsigned long ulChannelID;
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
#endif 

    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + UART_RIS);
    

    //
    // Clear Int flag
    //
    xHWREG(ulBase + UART_ICR) = ulEventFlags;

    //
    // Clear Error flag
    //
    xHWREG(ulBase + UART_ECR) = 0;
 
#if !(xUART_CONFIG_DMA_INT)
    //
    // Call Callback function
    //
    if(g_pfnUARTHandlerCallbacks[0])
    {
        g_pfnUARTHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    }

#else
    
    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
            
    //
    // Check DMA RX flag
    //
    if(xHWREG(ulBase + UART_DMACTL) & UART_DMA_RX)
    {
        ulChannelID = xDMA_REQUEST_UART1_RX & 0x1F;
        
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }

        ulChannelID = (xDMA_REQUEST_UART1_RX >> 8) & 0x1F;
        
        //
        // Check channel assignment (Secondary)
        //
        if(xHWREG(UDMA_CHASGN) & (1 << ulChannelID))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }

    //
    // Check DMA TX flag
    //
    if(xHWREG(ulBase + UART_DMACTL) & UART_DMA_TX)
    {
        ulChannelID = xDMA_REQUEST_UART1_TX & 0x1F;
        
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }

        ulChannelID = (xDMA_REQUEST_UART1_TX >> 8) & 0x1F;
        
        //
        // Check channel assignment (Secondary)
        //
        if(xHWREG(UDMA_CHASGN) & (1 << ulChannelID))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }      
        
    }    
    
#endif    
}

//*****************************************************************************
//
//! \brief UART2 Interrupt Handler.
//!
//! If users want to user the UART2 Callback feature, Users should promise 
//! that the UART2 Handle in the vector table is UART0IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
UART2IntHandler(void)    
{
    unsigned long ulEventFlags;
    unsigned long ulBase = UART2_BASE;

#if xUART_CONFIG_DMA_INT
    xtEventCallback pfnCallback;
    unsigned long ulChannelID;
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
#endif    
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + UART_RIS);
    

    //
    // Clear Int flag
    //
    xHWREG(ulBase + UART_ICR) = ulEventFlags;

#if !(xUART_CONFIG_DMA_INT)    
    //
    // Clear Error flag
    //
    xHWREG(ulBase + UART_ECR) = 0;
    
    //
    // Call Callback function
    //
    if(ulEventFlags && g_pfnUARTHandlerCallbacks[0])
    {
        g_pfnUARTHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    }

#else
    
    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
            
    //
    // Check DMA RX flag
    //
    if(xHWREG(ulBase + UART_DMACTL) & UART_DMA_RX)
    {
        ulChannelID = xDMA_REQUEST_UART2_RX & 0x1F;
        //
        // Check channel assignment (Secondary)
        //
        if(xHWREG(UDMA_CHASGN) & (1 << ulChannelID))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }

    //
    // Check DMA TX flag
    //
    if(xHWREG(ulBase + UART_DMACTL) & UART_DMA_TX)
    {
        ulChannelID = xDMA_REQUEST_UART2_TX & 0x1F;
        //
        // Check channel assignment (secondary)
        //
        if(xHWREG(UDMA_CHASGN) & (1 << ulChannelID))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }    
    
#endif    
}

//*****************************************************************************
//
//! \brief Enables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b UART_INT_OE - Overrun Error interrupt
//! - \b UART_INT_BE - Break Error interrupt
//! - \b UART_INT_PE - Parity Error interrupt
//! - \b UART_INT_FE - Framing Error interrupt
//! - \b UART_INT_RT - Receive Timeout interrupt
//! - \b UART_INT_TX - Transmit interrupt
//! - \b UART_INT_RX - Receive interrupt
//! - \b UART_INT_DSR - DSR interrupt
//! - \b UART_INT_DCD - DCD interrupt
//! - \b UART_INT_CTS - CTS interrupt
//! - \b UART_INT_RI - RI interrupt
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
    xHWREG(ulBase + UART_IM) |= ulIntFlags;
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
    xHWREG(ulBase + UART_IM) &= ~(ulIntFlags);
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! \param ulBase is the base address of the UART port.
//! \param bMasked is \b xfalse if the raw interrupt status is required and
//! \b xtrue if the masked interrupt status is required.
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
UARTIntStatus(unsigned long ulBase, xtBoolean bMasked)
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
        return(xHWREG(ulBase + UART_MIS));
    }
    else
    {
        return(xHWREG(ulBase + UART_RIS));
    }
}

//*****************************************************************************
//
//! \brief Clears UART interrupt sources.
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
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
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
    xHWREG(ulBase + UART_ICR) = ulIntFlags;
}

//*****************************************************************************
//
//! \brief Enable UART DMA operation.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulDMAFlags is a bit mask of the DMA features to enable.
//!
//! The specified UART DMA features are enabled.  The UART can be
//! configured to use DMA for transmit or receive, and to disable
//! receive if an error occurs.  The \e ulDMAFlags parameter is the
//! logical OR of any of the following values:
//!
//! - UART_DMA_RX - enable DMA for receive
//! - UART_DMA_TX - enable DMA for transmit
//! - UART_DMA_ERR_RXSTOP - disable DMA receive on UART error
//!
//! \note The uDMA controller must also be set up before DMA can be used
//! with the UART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Set the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + UART_DMACTL) |= ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Disable UART DMA operation.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulDMAFlags is a bit mask of the DMA features to disable.
//!
//! This function is used to disable UART DMA features that were enabled
//! by UARTDMAEnable().  The specified UART DMA features are disabled.  The
//! \e ulDMAFlags parameter is the logical OR of any of the following values:
//!
//! - UART_DMA_RX - disable DMA for receive
//! - UART_DMA_TX - disable DMA for transmit
//! - UART_DMA_ERR_RXSTOP - do not disable DMA receive on UART error
//!
//! \return None.
//
//*****************************************************************************
void
UARTDMADisable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Clear the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + UART_DMACTL) &= ~ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Gets current receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns the current state of each of the 4 receiver error
//! sources.  The returned errors are equivalent to the four error bits
//! returned via the previous call to UARTCharGet() or UARTCharGetNonBlocking()
//! with the exception that the overrun error is set immediately the overrun
//! occurs rather than when a character is next read.
//!
//! \return Returns a logical OR combination of the receiver error flags,
//! \b UART_RXERROR_FRAMING, \b UART_RXERROR_PARITY, \b UART_RXERROR_BREAK
//! and \b UART_RXERROR_OVERRUN.
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
    return(xHWREG(ulBase + UART_RSR) & 0x0000000F);
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
    // Any write to the Error Clear Register will clear all bits which are
    // currently set.
    //
    xHWREG(ulBase + UART_ECR) = 0;
}

