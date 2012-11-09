//*****************************************************************************
//
//! \file xuart.c
//! \brief Driver for the UART
//! \version V2.2.1.0
//! \date 08/17/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
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
static xtEventCallback g_pfnUARTHandlerCallbacks[3]={0};

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART1 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART0.
//!
//! \return None.
//
//*****************************************************************************
void UART0SEIntHandler(void)
{
    unsigned long ulEvent = 0;

    //
    // Decide the interrupt event type
    //
    ulEvent =   xHWREGB(UART0_BASE + UART_0_S2) & 0xC0;
    ulEvent <<= 8;
    ulEvent |=  xHWREGB(UART0_BASE + UART_0_S1);

    if(0 != g_pfnUARTHandlerCallbacks[0])
    {
        (*g_pfnUARTHandlerCallbacks[0])(0, ulEvent, 0, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART1 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART1.
//!
//! \return None.
//
//*****************************************************************************
void UART1SEIntHandler(void)
{
    unsigned long ulEvent = 0;
    
    ulEvent =   xHWREGB(UART1_BASE + UART_12_S2) & 0xC0;
    ulEvent <<= 8;
    ulEvent |=  xHWREGB(UART1_BASE + UART_12_S1);
    if(0 != g_pfnUARTHandlerCallbacks[1])
    {
        (*g_pfnUARTHandlerCallbacks[1])(0, ulEvent, 0, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART1 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART2.
//!
//! \return None.
//
//*****************************************************************************
void UART2SEIntHandler(void)
{
    unsigned long ulEvent = 0;

    ulEvent =   xHWREGB(UART2_BASE + UART_12_S2) & 0xC0;
    ulEvent <<= 8;
    ulEvent |=  xHWREGB(UART2_BASE + UART_12_S1);

    if(0 != g_pfnUARTHandlerCallbacks[2])
    {
        (*g_pfnUARTHandlerCallbacks[2])(0, ulEvent, 0, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief Get the uart intput clock frequency
//!
//! \param ulBase is the base address of the UART port.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! \note this function is used internally and only called by \b UARTConfigSet
//!
//! \return None.
//
//*****************************************************************************
static unsigned long GetUartClock(unsigned long ulBase)
{
    unsigned long ulUartClock = 0;

    if(UART0_BASE == ulBase)
    {
        ulUartClock = SysCtlPWMAndUART0ClkGet();
    }
    else if((UART1_BASE == ulBase) || (UART2_BASE == ulBase))
    {
        ulUartClock = SysCtlBusClkGet();
    }

    return (ulUartClock);
}

//*****************************************************************************
//
//! \brief Sets the configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, parity and oversample ratio).
//!
//! This function configures the UART for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter and the data
//! format in the \e ulConfig parameter.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! The \e ulBaud parameter can be one of the following:
//! The \e ulConfig parameter is the logical OR of four values: the number of
//! data bits, the number of stop bits, the parity and the oversample ratio.
//!
//! - \b UART_CONFIG_WLEN_8
//! - \b UART_CONFIG_WLEN_9
//! - \b UART_CONFIG_WLEN_10
//! - \b UART_CONFIG_PAR_ODD
//! - \b UART_CONFIG_PAR_EVEN
//! - \b UART_CONFIG_PAR_NONE
//! - \b UART_CONFIG_STOP_1
//! - \b UART_CONFIG_STOP_2
//! - \b UART_CONFIG_SAMPLE_RATE_DEFAULT
//! - \b UART_CONFIG_SAMPLE_RATE_xx (xx = 04,05,06 ... 32)
//!
//! \b UART_CONFIG_WLEN_8,\b UART_CONFIG_WLEN_9,\b UART_CONFIG_WLEN_10
//! select from eight to ten data bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO select one two stop
//! bits (respectively).
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,\b UART_CONFIG_PAR_ODD
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//! \b UART_CONFIG_SAMPLE_RATE_xx,  \b UART_CONFIG_SAMPLE_RATE_DEFAULT select
//! uart oversample ratio, this parameter is only used for UART0 module.
//!
//!
//! \note Oversample ratio is only used in UART 0 Module.
//! \return None.
//
//*****************************************************************************
void UARTConfigSet(unsigned long ulBase,
                   unsigned long ulBaud,
                   unsigned long ulConfig)
{
    unsigned long ulUartClock  = 0;
    unsigned long ulDivisor    = 0;
    unsigned char ulTmpReg     = 0;
    unsigned long ulSampleRate = 0;

    //
    // Check the parameters.
    //
    xASSERT((ulBase == UART0_BASE) ||
            (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(0 == (ulConfig & ~(UART_CONFIG_WLEN_8   | UART_CONFIG_WLEN_9   |
                               UART_CONFIG_WLEN_10  | UART_CONFIG_PAR_ODD  |
                               UART_CONFIG_PAR_EVEN | UART_CONFIG_PAR_NONE |
                               UART_CONFIG_STOP_1   | UART_CONFIG_STOP_2   |
                               UART_CONFIG_SAMPLE_RATE_MASK )));

    //
    // Configure UART OverSample Rate value.
    //
    switch(ulBase)
    {
        case UART0_BASE:
        {
            ulSampleRate = ((ulConfig & UART_CONFIG_SAMPLE_RATE_MASK)
                           >> UART_CONFIG_SAMPLE_RATE_SHIFT);
            ulTmpReg =  xHWREGB(ulBase + UART_0_C4);
            ulTmpReg &= (unsigned char)(~UART_0_C4_OSR_MASK);
            ulTmpReg |= (unsigned char)(ulSampleRate & UART_0_C4_OSR_MASK);
            xHWREGB(ulBase + UART_0_C4)  =  ulTmpReg;
            break;
        }
        case UART1_BASE:
        case UART2_BASE:
        {
            ulSampleRate = 16;  // UART 1/2 default over sample rate.
            break;
        }
    }

    //
    // Configure UART Baud Rate.
    //
    ulUartClock = GetUartClock(ulBase);
    ulDivisor = ulUartClock / (ulBaud * ulSampleRate);

    ulTmpReg = xHWREGB(ulBase + UART_012_BDH);
    ulTmpReg &= (unsigned char)(~UART_012_BDH_SBR_MASK);
    ulTmpReg |= (unsigned char)((ulDivisor >> 8) & UART_012_BDH_SBR_MASK);
    xHWREGB(ulBase + UART_012_BDH) = ulTmpReg;
    xHWREGB(ulBase + UART_012_BDL) = (unsigned char)(ulDivisor);

    //
    // Configure byes length
    //
    switch(ulConfig & UART_CONFIG_WEN_MASK)
    {
        case  UART_CONFIG_WLEN_8:
        {
            if(UART0_BASE == ulBase)
            {
                xHWREGB(ulBase + UART_0_C4) &= (unsigned char)(~UART_0_C4_M10_MASK);
                xHWREGB(ulBase + UART_0_C4) |= (unsigned char)(UART_0_C4_M10_8_9_BIT);
            }
            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_M_MASK);
            xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_M_8_BIT);
            break;
        }

        case  UART_CONFIG_WLEN_9:
        {
            if(UART0_BASE == ulBase)
            {
                xHWREGB(ulBase + UART_0_C4) &= (unsigned char)(~UART_0_C4_M10_MASK);
                xHWREGB(ulBase + UART_0_C4) |= (unsigned char)(UART_0_C4_M10_8_9_BIT);
            }
            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_M_MASK);
            xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_M_9_BIT);
            break;
        }

        case  UART_CONFIG_WLEN_10:
        {
            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_M_MASK);
            xHWREGB(ulBase + UART_0_C4) &= (unsigned char)(~UART_0_C4_M10_MASK);
            xHWREGB(ulBase + UART_0_C4) |= (unsigned char)(UART_0_C4_M10_10_BIT);
            break;
        }
    }

    //
    // Configure Parity
    //
    switch(ulConfig & UART_CONFIG_PAR_MASK)
    {
        case  UART_CONFIG_PAR_ODD:
        {
            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_PE_MASK);
            xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_PE_ENABLE);

            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_PT_MASK);
            xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_PT_ODD);                       
            
            break ;
        }

        case  UART_CONFIG_PAR_EVEN:
        {
            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_PE_MASK);
            xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_PE_ENABLE);

            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_PT_MASK);
            xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_PT_EVEN);

            break ;
        }

        case  UART_CONFIG_PAR_NONE:
        {
            xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_PE_MASK);
            xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_PE_DISABLE);

            break ;
        }
    }

    //
    // Configure Stop Bit
    //
    switch(ulConfig & UART_CONFIG_STOP_MASK)
    {
        case  UART_CONFIG_STOP_1:
        {
            xHWREGB(ulBase + UART_012_BDH) &= (unsigned char)(~UART_012_BDH_SBNS_MASK);
            xHWREGB(ulBase + UART_012_BDH) |= (unsigned char)(UART_012_BDH_SBNS_ONE);

            break;
        }

        case  UART_CONFIG_STOP_2:
        {
            xHWREGB(ulBase + UART_012_BDH) &= (unsigned char)(~UART_012_BDH_SBNS_MASK);
            xHWREGB(ulBase + UART_012_BDH) |= (unsigned char)(UART_012_BDH_SBNS_TWO);

            break;
        }
    }
}


//*****************************************************************************
//
//! \brief Enables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to enable. it is the logical OR of
//! these values:  \b UART_TX, \b UART_RX.
//!
//! Sets the TXE or RXE bits.
//!
//! \return None.
//
//*****************************************************************************
void UARTEnable(unsigned long ulBase, unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(0 == (ulConfig & ~(UART_TX | UART_RX)));

    xHWREGB(ulBase + UART_012_C2) |= (unsigned char)(ulConfig);
}

//*****************************************************************************
//
//! \brief Disables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to disable. it is the logical OR of
//! these values:  \b UART_TX, \b UART_RX.
//!
//! Sets the TXE or RXE bits.
//!
//! \return None.
//
//*****************************************************************************
void UARTDisable(unsigned long ulBase, unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(0 == ((ulConfig) & ~(UART_TX | UART_RX)));

    xHWREGB(ulBase + UART_012_C2) &= (unsigned char)(~(ulConfig));
}

//*****************************************************************************
//
//! \brief Determines if there are any characters in receiver register.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive register.
//!
//! \return Returns \b true if there is data in the receive register or \b false
//! if there is no data in the receive register.
//
//*****************************************************************************
xtBoolean UARTCharsAvail(unsigned long ulBase)
{
    xtBoolean ulStatus = xfalse;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    ulStatus = (xtBoolean)(xHWREGB(ulBase + UART_012_S1) &
                          ((unsigned char) UART_012_S1_RDRF_MASK));

    return (ulStatus);
}

//*****************************************************************************
//
//! \brief Determines if there are any space in the transmit register.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive register.
//!
//! \return Returns \b true if there is data in the receive register or \b false
//! if there is no data in the receive register.
//
//*****************************************************************************
xtBoolean UARTSpaceAvail(unsigned long ulBase)
{
    xtBoolean ulStatus = xfalse;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    ulStatus = (xtBoolean)(xHWREGB(ulBase + UART_012_S1) &
                          ((unsigned char) UART_012_S1_TDRE_MASK));
    if(0 != ulStatus)
    {
        ulStatus = 1;
    }
    else
    {
        ulStatus = 0;
    }
    
    return (ulStatus);
}

//*****************************************************************************
//
//! \brief Receives a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive register for the specified port.
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
unsigned long UARTCharGetNonBlocking(unsigned long ulBase)
{
    xtBoolean     ulStatus = xfalse;
    unsigned long ulChar   = 0;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    //
    // Char available?
    //
    ulStatus = (xtBoolean) (xHWREGB(ulBase + UART_012_S1) &
                           (unsigned char)(UART_012_S1_RDRF_MASK));

    if(xtrue == ulStatus)                        // Char available
    {
        ulChar = (unsigned long) xHWREGB(ulBase + UART_012_D);
    }
    else                                         // Char Not available
    {
        ulChar = (unsigned long) (-1);
    }

    return (ulChar);
}

//*****************************************************************************
//
//! \brief Waits for a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive register for the specified port.  If there
//! are no characters available, this function waits until a character is
//! received before returning.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.
//
//*****************************************************************************
unsigned char UARTCharGet(unsigned long ulBase)
{
    unsigned long          ulChar   = 0;
    volatile unsigned char ulStatus = 0;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    //
    // Wait until Receive a char
    //
    do
    {
        ulStatus = xHWREGB(ulBase + UART_012_S1) &
                   ((unsigned char ) UART_012_S1_RDRF_MASK);
    }while(0 == ulStatus);

    //
    // Get the char
    //
    ulChar = xHWREGB(ulBase + UART_012_D);

    return (ulChar);
}

//*****************************************************************************
//
//! \brief Sends a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit register for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b false is returned, and the application must retry the function later.
//!
//! This function replaces the original UARTCharNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit register or \b false if there was no space available in the transmit
//! register.
//
//*****************************************************************************
xtBoolean UARTCharPutNonBlocking(unsigned long ulBase, unsigned char ulData)
{
    xtBoolean     ulStatus = 0;
    xtBoolean     ulResult = 0;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    //
    // Transmit register is available ?
    //
    ulStatus = (xtBoolean) xHWREGB(ulBase + UART_012_S1) & UART_012_S1_TDRE_MASK;

    if(xtrue == ulStatus)                      // Transmit Register available
    {
        xHWREGB(ulBase + UART_012_D) = ulData;
        ulResult = xtrue;
    }
    else                                       // Transmit Register NOT available
    {
        ulResult = xfalse;
    }

    return (ulResult);
}

//*****************************************************************************
//
//! \brief Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Sends the character \e ucData to the transmit register for the specified port.
//! If there is no space available in the transmit register, this function waits
//! until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
void UARTCharPut(unsigned long ulBase, unsigned char ulData)
{
    volatile unsigned char ulStatus = 0;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    //
    // Wait until transmit register availavle
    //
    do
    {
        ulStatus = xHWREGB(ulBase + UART_012_S1) &
                   ((unsigned char) UART_012_S1_TDRE_MASK);
    }while(0 == ulStatus);

    //
    // Send the char
    //
    xHWREGB(ulBase + UART_012_D) = ulData;

}

//*****************************************************************************
//
//! \brief Determines whether the UART transmitter is busy or not.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Allows the caller to determine whether all transmitted bytes have cleared
//! the transmitter hardware.  If \b false is returned, the transmit register is
//! empty and all bits of the last transmitted character, including all stop
//! bits, have left the hardware shift register.
//!
//! \return Returns \b true if the UART is transmitting or \b false if all
//! transmissions are complete.
//
//*****************************************************************************
xtBoolean UARTBusy(unsigned long ulBase)
{
    xtBoolean ulStatus = xfalse;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    ulStatus = (xtBoolean) xHWREGB(ulBase + UART_012_S1) &
                           ((unsigned char)UART_012_S1_TDRE_MASK);

    //
    // Transmit full mean busy and vice versa
    //
    ulStatus = !ulStatus;

    return (ulStatus);
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
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//! - \b UART_INT_LBKD   - LIN RX Break Field Detected Interrupt
//! - \b UART_INT_RXEDG  - RX pin active edge interrupt
//! - \b UART_INT_T      - Transmission data register empty interrupt
//! - \b UART_INT_TC     - Transmission complete interrupt
//! - \b UART_INT_R      - Receive data register full interrupt
//! - \b UART_INT_IL     - Idle line interrupt
//! - \b UART_INT_OR     - Overrun error interrupt
//! - \b UART_INT_NE     - Noise error interrupt
//! - \b UART_INT_FE     - Frame error interrupt
//! - \b UART_INT_PE     - Parity error interrupt
//!
//! \return None.
//
//*****************************************************************************
void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    unsigned long ulTmp = 0;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(0 == ((ulIntFlags) &~ (UART_INT_LBKD | UART_INT_RXEDG |
                                   UART_INT_T    | UART_INT_TC    |
                                   UART_INT_R    | UART_INT_IL    |
                                   UART_INT_OR   | UART_INT_NE    |
                                   UART_INT_FE   | UART_INT_PE    )));

    if(0 != (ulIntFlags & UART_INT_BDH_FLAG))
    {
        ulTmp = (ulIntFlags & UART_INT_BDH_MASK) >> UART_INT_BDH_SHIFT;
        xHWREGB(ulBase + UART_012_BDH) |= ((unsigned char)ulTmp);
    }

    if(0 != (ulIntFlags & UART_INT_C2_FLAG))
    {
        ulTmp = (ulIntFlags & UART_INT_C2_MASK) >> UART_INT_C2_SHIFT;
        xHWREGB(ulBase + UART_012_C2) |= ((unsigned char)ulTmp);
    }

    if(0 != (ulIntFlags & UART_INT_C3_FLAG))
    {
        ulTmp = (ulIntFlags & UART_INT_C3_MASK) >> UART_INT_C3_SHIFT;
        xHWREGB(ulBase + UART_012_C3) |= ((unsigned char)ulTmp);
    }
}


//*****************************************************************************
//
//! \brief Disables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Disables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//! - \b UART_INT_LBKD   - LIN RX Break Field Detected Interrupt
//! - \b UART_INT_RXEDG  - RX pin active edge interrupt
//! - \b UART_INT_T      - Transmission data register empty interrupt
//! - \b UART_INT_TC     - Transmission complete interrupt
//! - \b UART_INT_R      - Receive data register full interrupt
//! - \b UART_INT_IL     - Idle line interrupt
//! - \b UART_INT_OR     - Overrun error interrupt
//! - \b UART_INT_NE     - Noise error interrupt
//! - \b UART_INT_FE     - Frame error interrupt
//! - \b UART_INT_PE     - Parity error interrupt
//!
//! \return None.
//
//*****************************************************************************
void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    unsigned long ulTmp = 0;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(0 == ((ulIntFlags) &~ (UART_INT_LBKD | UART_INT_RXEDG |
                                   UART_INT_T    | UART_INT_TC    |
                                   UART_INT_R    | UART_INT_IL    |
                                   UART_INT_OR   | UART_INT_NE    |
                                   UART_INT_FE   | UART_INT_PE    )));

    if(0 != (ulIntFlags & UART_INT_BDH_FLAG))
    {
        ulTmp = (ulIntFlags & UART_INT_BDH_MASK) >> UART_INT_BDH_SHIFT;
        xHWREGB(ulBase + UART_012_BDH) &= ((unsigned char)~ulTmp);
    }

    if(0 != (ulIntFlags & UART_INT_C2_FLAG))
    {
        ulTmp = (ulIntFlags & UART_INT_C2_MASK) >> UART_INT_C2_SHIFT;
        xHWREGB(ulBase + UART_012_C2) &= ((unsigned char)~ulTmp);
    }

    if(0 != (ulIntFlags & UART_INT_C3_FLAG))
    {
        ulTmp = (ulIntFlags & UART_INT_C3_MASK) >> UART_INT_C3_SHIFT;
        xHWREGB(ulBase + UART_012_C3) &= ((unsigned char)~ulTmp);
    }
}


//*****************************************************************************
//
//! \brief Init interrupts callback for the specified UART Port.
//!
//! \param ulPort is the base address of the UART port.
//! \param xtUARTCallback is callback for the specified UART Port.
//!
//! Init interrupts callback for the specified UART Port.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! \return None.
//
//*****************************************************************************
void UARTIntCallbackInit(unsigned long ulBase,
                    xtEventCallback pfnCallback)
{
    //
    // Check the parameters.
    //
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    //
    // Register user's handler function.
    //
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
        default:
        {
            break;
        }
    }
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
//! \b xUART_RXERROR_FRAMING, \b xUART_RXERROR_PARITY, \b xUART_RXERROR_BREAK
//! and \b xUART_RXERROR_OVERRUN.
//
//*****************************************************************************
unsigned long UARTRxErrorGet(unsigned long ulBase)
{
    unsigned long ulErrorFlag = 0;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    ulErrorFlag = ((unsigned long)xHWREGB(ulBase + UART_012_S1)) &
                                                               UART_ERROR_MASK;

    return ulErrorFlag;
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
void UARTRxErrorClear(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    switch(ulBase)
    {
        case UART0_BASE:
        {
            xHWREGB(ulBase + UART_012_S1) |= UART_ERROR_MASK;

            break;
        }

        case UART1_BASE:
        case UART2_BASE:
        {
            (void)xHWREGB(ulBase + UART_012_S1);
            (void)xHWREGB(ulBase + UART_012_D);

            break;
        }
    }
}



//*****************************************************************************
//
//! \brief Open LIN mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulConfig is the Config of the UART port in LIN mode.
//!
//! Open the LIN mode for the UART.
//!
//! The \e ulConfig parameter is the logical OR of three values: the LIN Tx or Rx
//! Mode, the LIN Break Field Length.\b UART_CONFIG_LIN_RX_EN ,and \b
//! UART_CONFIG_LIN_TX_EN is to enable LIN Rx or Tx.
//!
//! \note
//!  ------------------------------------------------
//!  |  S2    | C1 | C4  | BDH  |   Break Character |
//!  |  BPK13 | M  | M10 | SBNS |   Length          |
//!  |--------|----|-----|------|-------------------|
//!  |  0     | 0  | 0   | 0    |   10              |
//!  |  0     | 0  | 0   | 1    |   11              |
//!  |  0     | 1  | 0   | 1    |   12              |
//!  |  1     | 0  | 0   | 0    |   13              |
//!  |  1     | 0  | 0   | 1    |   14              |
//!  |  1     | 1  | 0   | 1    |   15              |
//!  |  1     | 0  | 1   | 1    |   16              |
//!  ------------------------------------------------
//!  .
//! \return None.
//
//*****************************************************************************
void UARTLINConfig(unsigned long ulBase, unsigned long ulBaud,
                   unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT((ulConfig == UART_LIN_SYNC_BREAK_LEN_10) ||
            (ulConfig == UART_LIN_SYNC_BREAK_LEN_11) ||
            (ulConfig == UART_LIN_SYNC_BREAK_LEN_12) ||
            (ulConfig == UART_LIN_SYNC_BREAK_LEN_13) ||
            (ulConfig == UART_LIN_SYNC_BREAK_LEN_14) ||
            (ulConfig == UART_LIN_SYNC_BREAK_LEN_15) ||
            (ulConfig == UART_LIN_SYNC_BREAK_LEN_16) );

    //
    // General UART 8-N-1
    //

    UARTConfigSet(ulBase, ulBaud, (UART_CONFIG_WLEN_8   |
                UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_1));

    switch(ulBase)
    {
        case UART0_BASE:
        {
            unsigned char tmp = 0;
            
            //
            // Clear S2 C1 C4 SBNS Bit
            //
            xHWREGB(ulBase + UART_012_S2 ) &= (unsigned char)(~UART_012_S2_BRK13_MASK);
            xHWREGB(ulBase + UART_012_C1 ) &= (unsigned char)(~UART_012_C1_M_MASK);
            xHWREGB(ulBase + UART_0_C4 )   &= (unsigned char)(~UART_0_C4_M10_MASK);
            xHWREGB(ulBase + UART_012_BDH) &= (unsigned char)(~UART_012_BDH_SBNS_MASK);

            //
            // Configure Break Length
            //
            xHWREGB(ulBase + UART_0_S2 ) |= (unsigned char)(ulConfig >> 24);
            xHWREGB(ulBase + UART_0_C1 ) |= (unsigned char)(ulConfig >> 16);
            xHWREGB(ulBase + UART_0_C4 ) |= (unsigned char)(ulConfig >> 8 );
            xHWREGB(ulBase + UART_0_BDH) |= (unsigned char)(ulConfig      );
            tmp = xHWREGB(ulBase + UART_0_BDH);

            break;
        }

        case UART1_BASE:
        case UART2_BASE:
        {
            //
            // Clear S2 C1 SBNS Bit
            //
            xHWREGB(ulBase + UART_12_S2 ) &= (unsigned char)(~UART_012_S2_BRK13_MASK);
            xHWREGB(ulBase + UART_12_C1 ) &= (unsigned char)(~UART_012_C1_M_MASK);
            xHWREGB(ulBase + UART_12_BDH) &= (unsigned char)(~UART_012_BDH_SBNS_MASK);

            //
            // Configure Break Length
            //
            xHWREGB(ulBase + UART_12_S2 ) |= (unsigned char)(ulConfig >> 24);
            xHWREGB(ulBase + UART_12_C1 ) |= (unsigned char)(ulConfig >> 16);
            xHWREGB(ulBase + UART_12_BDH) |= (unsigned char)(ulConfig      );
            break;
        }
    }
}


//*****************************************************************************
//
//! \brief Enables LIN Function mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables the SIREN control bit for LIN Function on the UART.
//!
//! \return None.
//
//*****************************************************************************
void UARTLINEnable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xHWREGB(ulBase + UART_012_S2) |= (unsigned char)(UART_012_S2_LBKDE);
}

//*****************************************************************************
//
//! \brief Disables LIN Function mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the LIN Function bits.
//!
//! \return None.
//
//*****************************************************************************
void UARTLINDisable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_S2) &= (unsigned char)(~UART_012_S2_LBKDE);
}

//*****************************************************************************
//
//! \brief Send sync break chars.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Send synch break chars.
//!
//! \return None.
//
//*****************************************************************************
void UARTLINSyncBreakPut(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    //
    // Wait until Transmit Register available
    //
    while(0 == (xHWREGB(ulBase + UART_012_S1) & UART_012_S1_TDRE_MASK));

    //
    //
    //
    xHWREGB(ulBase + UART_012_C2) |= (unsigned char)(UART_012_C2_SBK_MASK);
    xHWREGB(ulBase + UART_012_C2) &= (unsigned char)(~UART_012_C2_SBK_MASK);
}


//*****************************************************************************
//
//! \brief Enables individual UART DMA sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulConfig is the bit mask of the DMA sources.
//!
//! When a flag is configured for a DMA request, its associated DMA request
//! is asserted when the flag is set. The DMA request remains asserted until
//! an indication is received that the DMA transactions are done. When this
//! indication is received, the flag bit and the associated DMA request are
//! cleared. If the DMA operation failed to remove the situation that caused
//! the DMA request another request will be issued
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! The \e ulConfig parameter is the logical OR of any of the following
//! - \b UART_DMA_T      Transmit register empty
//! - \b UART_DMA_TC     Transmit complete
//! - \b UART_DMA_R      Receive register full
//! - \b UART_DMA_IDLE   Idle line detect
//! - \b UART_DMA_LBKD   LIN break
//!
//! \return None.
//
//*****************************************************************************
void UARTDMAEnable(unsigned long ulBase, unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(0 == (ulConfig & (UART_DMA_T | UART_DMA_TC | UART_DMA_R |
                              UART_DMA_IDLE | UART_DMA_LBKD)));
    switch(ulBase)
    {
        case UART0_BASE:
            {
                xHWREGB(ulBase + UART_0_C5) |= (unsigned char) ulConfig;
                break;
            }
        case UART1_BASE:
        case UART2_BASE:
            {
                xHWREGB(ulBase + UART_12_C4) |= (unsigned char) ulConfig;
                break;
            }
    }
}

//*****************************************************************************
//
//! \brief Disables individual UART DMA sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulConfig is the bit mask of the DMA sources.
//!
//! When a flag is configured for a DMA request, its associated DMA request
//! is asserted when the flag is set. The DMA request remains asserted until
//! an indication is received that the DMA transactions are done. When this
//! indication is received, the flag bit and the associated DMA request are
//! cleared. If the DMA operation failed to remove the situation that caused
//! the DMA request another request will be issued
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! The \e ulConfig parameter is the logical OR of any of the following
//! - \b UART_DMA_T      Transmit register empty
//! - \b UART_DMA_TC     Transmit complete
//! - \b UART_DMA_R      Receive register full
//! - \b UART_DMA_IDLE   Idle line detect
//! - \b UART_DMA_LBKD   LIN break
//!
//! \return None.
//
//*****************************************************************************
void UARTDMADisable(unsigned long ulBase, unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(0 == (ulConfig & (UART_DMA_T | UART_DMA_TC | UART_DMA_R |
                              UART_DMA_IDLE | UART_DMA_LBKD)));
    switch(ulBase)
    {
        case UART0_BASE:
            {
                xHWREGB(ulBase + UART_0_C5) &= (unsigned char)(~ulConfig);
                break;
            }
        case UART1_BASE:
        case UART2_BASE:
            {
                xHWREGB(ulBase + UART_12_C4) &= (unsigned char)(~ulConfig);
                break;
            }
    }
}

//*****************************************************************************
//
//! \brief Invert the uart output signal.
//!
//! \param ulPort is the base address of the UART port.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! \return None.
//
//*****************************************************************************
void UARTTxInvertEnable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_C3) &= (unsigned char)(~UART_012_C3_TXINV_MASK);
    xHWREGB(ulBase + UART_012_C3) |= (unsigned char)(UART_012_C3_TXINV_INVERT);
}

//*****************************************************************************
//
//! \brief NOT Invert the uart output signal.
//!
//! \param ulPort is the base address of the UART port.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! \return None.
//
//*****************************************************************************
void UARTTxInvertDisable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_C3) &= (unsigned char)(~UART_012_C3_TXINV_MASK);
    xHWREGB(ulBase + UART_012_C3) |= (unsigned char)(UART_012_C3_TXINV_NORMAL);
}

//*****************************************************************************
//
//! \brief Invert the uart input signal.
//!
//! \param ulPort is the base address of the UART port.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! \return None.
//
//*****************************************************************************
void UARTRxInvertEnable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_S2) &= (unsigned char)(~UART_012_S2_RXINV_MASK);
    xHWREGB(ulBase + UART_012_S2) |= (unsigned char)(UART_012_S2_RXINV_INVERT);
}

//*****************************************************************************
//
//! \brief NOT Invert the uart input signal.
//!
//! \param ulPort is the base address of the UART port.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//!
//! \return None.
//
//*****************************************************************************
void UARTRxInvertDisable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_S2) &= (unsigned char)(~UART_012_S2_RXINV_MASK);
    xHWREGB(ulBase + UART_012_S2) |= (unsigned char)(UART_012_S2_RXINV_NORMAL);
}


//*****************************************************************************
//
//! \brief Configure UART output Mode.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulConfig is the UART mode.
//!
//!  UART can be set to three operate mode:
//!  \b NORMAL, \b SINGLE_LINE ,\b LOOPS
//!  in \b NORMAL mode, RX and TX is separate pin; in \b SINGLE_LINE mode RX and
//!  TX use a common pin(TX Pin); in \b LOOPS mode UART does output signal,and
//!  TX is connected to RX pin internal.
//!
//! The \e ulBase parameter can be one of the following:
//! - \b UART0_BASE    = UART 0 Module base address
//! - \b UART1_BASE    = UART 1 Module base address
//! - \b UART2_BASE    = UART 2 Module base address
//! The \e ulConfig parameter can be one of the following:
//!
//! - \b UART_MODE_NORMAL       Normal Mode
//! - \b UART_MODE_SINGLE_LINE  Single line Mode
//! - \b UART_MODE_LOOP         Loops Mode
//
//! \return None.
//
//*****************************************************************************
void UARTOutModeConfig(unsigned long ulBase, unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_MODE_MASK);
    xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(ulConfig);
}

//*****************************************************************************
//
//! \brief Enable UART in wait mode.
//!
//! \param ulPort is the base address of the UART port.
//!
//! UART clocks continue to run in wait mode so the UART can be the source of
//! an interrupt that wakes up the CPU.
//!
//! \return None.
//
//*****************************************************************************
void UARTWaitModeRun(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_DOZEEN_ENABLE);
}

//*****************************************************************************
//
//! \brief Disable UART in wait mode.
//!
//! \param ulPort is the base address of the UART port.
//!
//! UART clocks freeze while CPU is in wait mode.
//!
//! \return None.
//
//*****************************************************************************
void UARTWaitModeStop(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );

    xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(UART_012_C1_DOZEEN_DISABLE);
}

//*****************************************************************************
//
//! \brief Receiver wakeup mode select.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulConfig is the wakeup mode select.
//!
//! Receiver wakeup is a hardware mechanism that allows an UART receiver to
//! ignore the characters in a message intended for a different UART receiver.
//!
//! The \e ulConfig parameter can be one of the followings:
//! - \b UART_WAKEUP_IDLE_LINE Idle line wakeup mode.
//! - \b UART_WAKEUP_ADDRESS_MARK Address match wakeup mode.
//!
//! \return None.
//
//*****************************************************************************
void UARTWakeupMethodConfig(unsigned long ulBase, unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT((ulBase == UART_WAKEUP_IDLE_LINE   ) ||
            (ulBase == UART_WAKEUP_ADDRESS_MARK) );
    xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_WAKEUP_MASK);
    xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(ulConfig);
}

//*****************************************************************************
//
//! \brief Configure MSB of chars to be sent first.
//!
//! \param ulPort is the base address of the UART port.
//!
//! Setting this bit reverses the order of the bits that are transmitted and
//! received on the wire. this bit does not affect the polarity of the bits,
//! the location of the parity bit or the location of the start or stop bits.
//! This bit should only be changed when the transmitter and receiver are both
//! disabled.
//!
//! \return None.
//
//*****************************************************************************
void UARTMsbFirst(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE));
    xHWREGB(UART0_BASE + UART_0_S2) &= (unsigned char)(~UART_0_S2_MSBF_MASK);
    xHWREGB(UART0_BASE + UART_0_S2) |= (unsigned char)(UART_0_S2_MSBF_MSB);
}

//*****************************************************************************
//
//! \brief Configure LSB of chars to be sent first.
//!
//! \param ulPort is the base address of the UART port.
//!
//! Setting this bit reverses the order of the bits that are transmitted and
//! received on the wire. this bit does not affect the polarity of the bits,
//! the location of the parity bit or the location of the start or stop bits.
//! This bit should only be changed when the transmitter and receiver are both
//! disabled.
//!
//! \return None.
//
//*****************************************************************************
void UARTLsbFirst(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE));
    xHWREGB(UART0_BASE + UART_0_S2) &= (unsigned char)(~UART_0_S2_MSBF_MASK);
    xHWREGB(UART0_BASE + UART_0_S2) |= (unsigned char)(UART_0_S2_MSBF_LSB);
}

//*****************************************************************************
//
//! \brief Get receiver status.
//!
//! \param ulPort is the base address of the UART port.
//!
//! Get the receiver status, active or idle?
//!
//! \return Receiver status, this value is one of the followings:
//! \b xtrue   UART receiver active.
//! \b xfalse  UART receiver idle waitting for a start bit.
//
//*****************************************************************************
xtBoolean UARTReceiverStatus(unsigned long ulBase)
{
    xtBoolean ulStatus = xfalse;
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    ulStatus = (xtBoolean) (xHWREGB(ulBase + UART_012_S2) &
                           (unsigned char)UART_012_S2_RAF);

    return (ulStatus);
}

//*****************************************************************************
//
//! \brief Configure the UART Match address.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulChl  is the match address ID.
//! \param ulAddr is the user's address.
//!
//! The Match register are compared to input data addresses when the most
//! significant bit is set and the associated bit is set. If a match occurs,
//! the following data is transferred to the data register. if a match fails,
//! the following data is discarded. This function can be called at anytime.
//!
//! The \e ulChl parameter can be one of the following:
//! \b UART_ADDRESS_CHL_1 \b UART_ADDRESS_CHL_2
//! The \b ulAddr parameter must <= 255.
//!
//! \return None.
//
//*****************************************************************************
void UARTMatchAddressSet(unsigned long ulBase, unsigned long ulChl,
                         unsigned long ulAddr)
{
    xASSERT((ulBase == UART0_BASE));
    xASSERT((ulBase == UART_ADDRESS_CHL_1) || (ulBase == UART_ADDRESS_CHL_2));
    xASSERT(ulAddr < 0x00000100UL);

    //
    // Avoid compiler warning
    //
    ulBase = ulBase;

    if(UART_ADDRESS_CHL_1 == ulChl)
    {
        xHWREGB(UART0_BASE + UART_0_MA1) = (unsigned char)(ulAddr);
    }
    else if(UART_ADDRESS_CHL_2 == ulChl)
    {
        xHWREGB(UART0_BASE + UART_0_MA2) = (unsigned char)(ulAddr);
    }
}


//*****************************************************************************
//
//! \brief Enable Address match mode.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulChl  is the match address ID.
//!
//! The Match register are compared to input data addresses when the most
//! significant bit is set and the associated bit is set. If a match occurs,
//! the following data is transferred to the data register. if a match fails,
//! the following data is discarded. This function can be called at anytime.
//!
//! The \e ulChl parameter can be one of the following:
//! \b UART_ADDRESS_CHL_1 \b UART_ADDRESS_CHL_2
//!
//! \return None.
//
//*****************************************************************************
void UARTMatchAddrModeEnable(unsigned long ulBase, unsigned long ulChl)
{
    xASSERT((ulBase == UART0_BASE));
    xASSERT((ulBase == UART_ADDRESS_CHL_1) || (ulBase == UART_ADDRESS_CHL_2));

    //
    // Avoid compiler warning
    //
    ulBase = ulBase;

    if(UART_ADDRESS_CHL_1 == ulChl)
    {
        xHWREGB(UART0_BASE + UART_0_C4) |= (unsigned char)(UART_0_C4_MAEN1_MASK);
    }
    else if(UART_ADDRESS_CHL_2 == ulChl)
    {
        xHWREGB(UART0_BASE + UART_0_C4) |= (unsigned char)(UART_0_C4_MAEN2_MASK);
    }
}

//*****************************************************************************
//
//! \brief Disable Address match mode.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulChl  is the match address ID.
//!
//! The Match register are compared to input data addresses when the most
//! significant bit is set and the associated bit is set. If a match occurs,
//! the following data is transferred to the data register. if a match fails,
//! the following data is discarded. This function can be called at anytime.
//!
//! The \e ulChl parameter can be one of the following:
//! \b UART_ADDRESS_CHL_1 \b UART_ADDRESS_CHL_2
//!
//! \return None.
//
//*****************************************************************************
void UARTMatchAddrModeDisable(unsigned long ulBase, unsigned long ulChl)
{
    xASSERT((ulBase == UART0_BASE));
    xASSERT((ulBase == UART_ADDRESS_CHL_1) || (ulBase == UART_ADDRESS_CHL_2));

    //
    // Avoid compiler warning
    //
    ulBase = ulBase;

    if(UART_ADDRESS_CHL_1 == ulChl)
    {
        xHWREGB(UART0_BASE + UART_0_C4) &= (unsigned char)(~UART_0_C4_MAEN1_MASK);
    }
    else if(UART_ADDRESS_CHL_2 == ulChl)
    {
        xHWREGB(UART0_BASE + UART_0_C4) &= (unsigned char)(~UART_0_C4_MAEN2_MASK);
    }
}


//*****************************************************************************
//
//! \brief Enable both edge sampling function.
//!
//! \param ulPort is the base address of the UART port.
//!
//! Enables sampling of the received data on both edges of the baud clock,
//! effectively doubling the number of times the receiver samples the input data
//! for a given oversampling ratio. This bit must be set for oversampling ratios
//! between x4 and x8 and is optional for highter oversampling ratios.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
void UARTBothEdgeSampleEnable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE));
    xHWREGB(UART0_BASE + UART_0_C5) |= (unsigned char)UART_0_C5_BOTHEDGE;
}

//*****************************************************************************
//
//! \brief Disable both edge sampling function.
//!
//! \param ulPort is the base address of the UART port.
//!
//! Enables sampling of the received data on both edges of the baud clock,
//! effectively doubling the number of times the receiver samples the input data
//! for a given oversampling ratio. This bit must be set for oversampling ratios
//! between x4 and x8 and is optional for highter oversampling ratios.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
void UARTBothEdgeSampleDisable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE));
    xHWREGB(UART0_BASE + UART_0_C5) &= (unsigned char)(~UART_0_C5_BOTHEDGE);
}

//*****************************************************************************
//
//! \brief Enable UART resynchronization function.
//!
//! \param ulPort is the base address of the UART port.
//!
//! Enable the resynchronization of the received data word when a data one
//! followed by data zero transition is detected.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
void UARTReSyncEnable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE));
    xHWREGB(UART0_BASE + UART_0_C5) &= (unsigned char)(~UART_0_C5_RESYNCDIS);
}

//*****************************************************************************
//
//! \brief Disable UART resynchronization function.
//!
//! \param ulPort is the base address of the UART port.
//!
//! Disable the resynchronization of the received data word when a data one
//! followed by data zero transition is detected.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
void UARTReSyncDisable(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE));
    xHWREGB(UART0_BASE + UART_0_C5) |= (unsigned char)(UART_0_C5_RESYNCDIS);
}



//*****************************************************************************
//
//! \brief Get 9-th bit of the transmit data.
//!
//! \param ulPort is the base address of the UART port.
//!
//! when configure UART to 9bits mode, you can use this function to get 9-th bit.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
unsigned char UARTGetBit9(unsigned long ulBase)
{
    unsigned char ulTmp   = 0;
    unsigned char ulValue = 0;
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    ulTmp = xHWREGB(ulBase + UART_012_C3) &
        (unsigned char)UART_012_C3_R8T9_MASK;
    if(0 != ulTmp)
    {
        ulValue = 0x01;
    }
    else
    {
        ulValue = 0x00;
    }
    return (ulValue);
}

//*****************************************************************************
//
//! \brief Get 10-th bit of the transmit data.
//!
//! \param ulPort is the base address of the UART port.
//!
//! when configure UART to 10bits mode, you can use this function to get
//! 10-th bit.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
unsigned char UARTGetBit10(unsigned long ulBase)
{
    

    unsigned char ulTmp   = 0;
    unsigned char ulValue = 0;
    xASSERT((ulBase == UART0_BASE));
    xASSERT((ulBase == UART0_BASE));
    ulTmp = xHWREGB(UART0_BASE + UART_012_C3) &
        (unsigned char)UART_012_C3_R9T8_MASK;

    if(0 != ulTmp)
    {
        ulValue = 0x01;
    }
    else
    {
        ulValue = 0x00;
    }
    return (ulValue);
}

//*****************************************************************************
//
//! \brief Set 9-th bit of the transmit data.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulCh is the bit 9 of the send chars.
//!
//! when configure UART to 9bits mode, you can use this function to set 9-th bit.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
void UARTSetBit9(unsigned long ulBase, unsigned char ulCh)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    if(0 == ulCh)
    {
        xHWREGB(ulBase + UART_012_C3) &=
            (unsigned char)(~UART_012_C3_R9T8_MASK);
    }
    else
    {
        xHWREGB(ulBase + UART_012_C3) |=
            (unsigned char)(UART_012_C3_R9T8_MASK);
    }
}

//*****************************************************************************
//
//! \brief Set 10-th bit of the transmit data.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulCh is the bit 10 of the send chars.
//!
//! when configure UART to 10 bits mode, you can use this function to set 10-th
//! bit.
//!
//! \note This function is UART0 special function
//!
//! \return None.
//
//*****************************************************************************
void UARTSetBit10(unsigned long ulBase, unsigned char ulCh)
{
    xASSERT((ulBase == UART0_BASE));
    if(0 == ulCh)
    {
        xHWREGB(UART0_BASE + UART_012_C3) &=
            (unsigned char)(~UART_012_C3_R8T9_MASK);
    }
    else
    {
        xHWREGB(UART0_BASE + UART_012_C3) |=
            (unsigned char)(UART_012_C3_R8T9_MASK);
    }
}


//*****************************************************************************
//
//! \brief Configure the idle line type.
//!
//! \param ulPort is the base address of the UART port.
//! \param ulConfig is the idle line type.
//!
//! When configure UART to "after stop" mode, module ensures that stop bits and
//! logic 1 bits at the end of a character do not count toward the 10 to 13 bit
//! times of logic high level needed by the idle line detection logic.
//!
//! The \e ulConfig parameter can be one of the following:
//! - \b UART_IDLE_TYPE_AFTER_START
//! - \b UART_IDLE_TYPE_AFTER_STOP
//!
//! \return None.
//
//*****************************************************************************
void UARTIdleLineTypeConfig(unsigned long ulBase, unsigned long ulConfig)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT(
            (UART_IDLE_TYPE_AFTER_START == ulConfig) ||
            (UART_IDLE_TYPE_AFTER_START == ulConfig) );

    xHWREGB(ulBase + UART_012_C1) &= (unsigned char)(~UART_012_C1_ILT_MASK);
    xHWREGB(ulBase + UART_012_C1) |= (unsigned char)(ulConfig);

}

//*****************************************************************************
//
//! \brief Get the idle line flag.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Idle line is set when the UART receive line becomes idles for a full
//! character time after a period of activity.
//!
//! \return Returns the idle line status, can be one of the following:
//! - \b xtrue  Idle line was detected.
//! - \b xfalse No idle line was detected.
//
//*****************************************************************************
xtBoolean UARTIdleFlagGet(unsigned long ulBase)
{
    unsigned char ulStatus = 0;
    xtBoolean     ulFlag   = xfalse;

    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    ulStatus = xHWREGB(ulBase + UART_012_S1) &
        (unsigned char)UART_012_S1_IDLE_MASK;
    if(0 != ulStatus)
    {
        ulFlag = xtrue;
    }
    else
    {
        ulFlag = xfalse;
    }
    return (ulFlag);
}

//*****************************************************************************
//
//! \brief Clear the idle line flag.
//!
//! \param ulBase is the base address of the UART port.
//!
//! To clear idle line flag.
//!
//! \note After flag has been cleared, it cannot become set again until after
//! a new character has been received and receiver data register full. IDLE
//! is set only once even if the receive line remains idle for an extended period.
//!
//! \return None.
//
//*****************************************************************************
void UARTIdleFlagClear(unsigned long ulBase)
{
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    switch(ulBase)
    {
        case UART0_BASE:
            {
                xHWREGB(UART0_BASE + UART_012_S1) |=
                    (unsigned char)UART_012_S1_IDLE_MASK;
                break;
            }
        case UART1_BASE:
        case UART2_BASE:
            {
                (void)xHWREGB(UART0_BASE + UART_012_S1);
                (void)xHWREGB(UART0_BASE + UART_012_D);
                break;
            }
    }
}


//*****************************************************************************
//
//! \brief Send queued idle characters.
//!
//! \param ulBase is the base address of the UART port.
//!
//! \return None.
//
//*****************************************************************************
void UARTIdleSend(unsigned long ulBase)
{
    //
    // Wait until Transmit Register available
    //
    while(0 == (xHWREGB(ulBase + UART_012_S1) & UART_012_S1_TDRE_MASK));

    xHWREGB(ulBase + UART_012_C2) |= (unsigned char)(UART_012_C2_TE_MASK);
    xHWREGB(ulBase + UART_012_C2) &= (unsigned char)(~UART_012_C2_TE_MASK);
}

