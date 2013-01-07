//*****************************************************************************
//
//! \file xuart.c
//! \brief Driver for the UART
//! \version V2.2.1.0
//! \date 5/24/2012
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
#include "xhw_config.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_uart.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xuart.h"


//*****************************************************************************
//
// This macro extracts the array index out of the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_CLK(a)                                            \
                                (((a) >> 28) & 0xf)


//*****************************************************************************
//
// An array is UART callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnUARTHandlerCallbacks[5]={0};

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
    return((ulBase == USART1_BASE) || (ulBase == USART2_BASE) ||
           (ulBase == USART3_BASE) || (ulBase == USART4_BASE) ||
           (ulBase == USART5_BASE));
}
#endif


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
void 
USART1IntHandler(void)
{
    unsigned long ulUART1IntStatus;

    ulUART1IntStatus = xHWREG(USART1_BASE + USART_SR);
    //
    // Clear Interrupt Flag
    //
    xHWREG(USART1_BASE + USART_SR) &= ~ulUART1IntStatus;

    if(g_pfnUARTHandlerCallbacks[0] != 0)
    {
        g_pfnUARTHandlerCallbacks[0](0, 0, ulUART1IntStatus, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART2 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART2.
//!
//! \return None.
//
//*****************************************************************************
void 
USART2IntHandler(void)
{
    unsigned long ulUART2IntStatus;

    ulUART2IntStatus = xHWREG(USART2_BASE + USART_SR);
    //
    // Clear Interrupt Flag
    //
    xHWREG(USART2_BASE + USART_SR) &= ~ulUART2IntStatus;

    if(g_pfnUARTHandlerCallbacks[1] != 0)
    {
        g_pfnUARTHandlerCallbacks[1](0, 0, ulUART2IntStatus, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART3 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART3.
//!
//! \return None.
//
//*****************************************************************************
void 
USART3IntHandler(void)
{
    unsigned long ulUART3IntStatus;

    ulUART3IntStatus = xHWREG(USART3_BASE + USART_SR);
    //
    // Clear Interrupt Flag
    //
    xHWREG(USART3_BASE + USART_SR) &= ~ulUART3IntStatus;

    if(g_pfnUARTHandlerCallbacks[2] != 0)
    {
        g_pfnUARTHandlerCallbacks[2](0, 0, ulUART3IntStatus, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART4 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART4.
//!
//! \return None.
//
//*****************************************************************************
void 
UART4IntHandler(void)
{
    unsigned long ulUART4IntStatus;

    ulUART4IntStatus = xHWREG(USART4_BASE + USART_SR);
    //
    // Clear Interrupt Flag
    //
    xHWREG(USART4_BASE + USART_SR) &= ~ulUART4IntStatus;

    if(g_pfnUARTHandlerCallbacks[3] != 0)
    {
        g_pfnUARTHandlerCallbacks[3](0, 0, ulUART4IntStatus, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART5 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART5.
//!
//! \return None.
//
//*****************************************************************************
void 
UART5IntHandler(void)
{
    unsigned long ulUART5IntStatus;

    ulUART5IntStatus = xHWREG(USART5_BASE + USART_SR);
    //
    // Clear Interrupt Flag
    //
    xHWREG(USART5_BASE + USART_SR) &= ~ulUART5IntStatus;

    if(g_pfnUARTHandlerCallbacks[4] != 0)
    {
        g_pfnUARTHandlerCallbacks[4](0, 0, ulUART5IntStatus, 0);
    }
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
//! \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD.
//! The last two allow direct control of the
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
           (ulParity == UART_CONFIG_PAR_ODD));

    //
    // Set the parity mode.
    //
    xHWREG(ulBase + USART_CR1) = ((xHWREG(ulBase + USART_CR1) &
                                 ~(USART_CR1_PCE | USART_CR1_PS)) | ulParity);
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
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD.
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
    return(xHWREG(ulBase + USART_CR1) & (USART_CR1_PCE | USART_CR1_PS));
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
//! \b UART_CONFIG_WLEN_9
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO 
//! \b UART_CONFIG_STOP_0P5 and \b UART_CONFIG_STOP_1P5 select one two stop
//! 1.5 or 0.5 bits (respectively).  
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,\b UART_CONFIG_PAR_ODD
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigSet(unsigned long ulBase, unsigned long ulBaud, 
              unsigned long ulConfig)
{
    unsigned long ulExtClk,ultemp,uldiv;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulBaud != 0);

    //
    // Reset UART.
    //
    if (ulBase == USART1_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_USART1);
    }
    else if (ulBase == USART2_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_USART2);
    }
    else if (ulBase == USART3_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_USART3);
    }
    else if (ulBase == USART4_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART4);
    }
    else 
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART5);
    }

    //
    // Clear STOP[13:12] bits.
    //    
    xHWREG(ulBase + USART_CR2) &= ~USART_CR2_STOP_M;

    //
    // Set STOP[13:12] bits according to USART_StopBits value .
    //  
    xHWREG(ulBase + USART_CR2) = ulConfig & UART_CONFIG_STOP_MASK;

    //
    // Clear M, PCE, PS, TE and RE bits.
    //    
    xHWREG(ulBase + USART_CR1) &= ~(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS
                                    | USART_CR1_TE | USART_CR1_RE);

    //
    // Configure the USART Word Length, Parity and mode.
    // Configure the USART Word Length, Parity and mode.
    //  
    xHWREG(ulBase + USART_CR1) = ulConfig & (UART_CONFIG_WLEN_MASK | 
                                             UART_CONFIG_PAR_MASK);
    
    if(ulBase == USART1_BASE)
    {
        ulExtClk = SysCtlAPB2ClockGet();
    }
    else
    {
        ulExtClk = SysCtlAPB1ClockGet();
    }

    //
    // Determine the integer part.
    // 
    if ((xHWREG(ulBase + USART_CR1) & 0) != 0)
    {
        //
        // Integer part computing in case Oversampling mode is 8 Samples.
        // 
        ultemp = ((25 * ulExtClk) / (2 * (ulBaud)));    
    }
    else 
    {
        //
        // Integer part computing in case Oversampling mode is 16 Samples.
        //
        ultemp = ((25 * ulExtClk) / (4 * (ulBaud)));    
    }
    uldiv = (ultemp / 100) << 4;
    
    //
    // Determine the fractional part
    // 
    ultemp = ultemp - (100 * (uldiv >> 4));

    //
    // Implement the fractional part in the register
    //
    if ((xHWREG(ulBase + USART_CR1) & 0) != 0)
    {
        uldiv |= ((((ultemp * 8) + 50) / 100)) & ((unsigned char)0x07);
    }
    else 
    {
        uldiv |= ((((ultemp * 16) + 50) / 100)) & ((unsigned char)0x0F);
    }
    //
    // Write to USART BRR
    //
    xHWREG(ulBase + USART_BRR) = uldiv;
}

//*****************************************************************************
//
//! Enables SIR (IrDA) mode on the specified UART.
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
//! data bits, the number of stop bits, and the parity.  \b xUART_CONFIG_WLEN_9,
//! \b xUART_CONFIG_WLEN_8.
//! select from eight to five data bits per byte (respectively).
//! \bX UART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE,  and
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit, 
//! even parity bit, odd parity bit, parity bit always one, and 
//! parity bit always zero, respectively).
//!
//! The \e ulMode parameter is the logical OR of two values:Prescaler value
//! and IrDA mode.
//! IrDA mode can be:
//! - \b xUART_IRDA_MODE_NORMAL - IrDA normal mode
//! - \b xUART_IRDA_MODE_LPM - IrDA low-power mode
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
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulBaud != 0);

    //
    // Disable IrDA, and clear low-power mode flag
    //
    xHWREG(ulBase + USART_CR3) &= ~(USART_CR3_IREN | USART_CR3_IRLP);

    //
    // Set baud, parity, data length, and number of stop bits.
    //
    UARTConfigSet(ulBase, ulBaud, ulConfig);
    
    xHWREG(ulBase + USART_CR3) &= ~USART_CR3_IRLP;

    if((ulMode & UART_IRDA_MODE_MASK) == UART_IRDA_MODE_LPM)
    {
        //
        // Set IrDA as low-power mode
        //
        xHWREG(ulBase + USART_CR3) |= (USART_CR3_IRLP);
    }
}
//*****************************************************************************
//
//! \brief Enables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to enable. it is the logical OR of 
//! these values:  \b UART_BLOCK_UART, \b UART_BLOCK_TX, \b UART_BLOCK_RX.
//!
//! Sets the UARTEN, or TXE or RXE bits.
//!
//! \note Do nothing in UART,In IrDA and LIN mode will set the Tx or Rx enable
//!
//! \return None.
//
//*****************************************************************************      
void UARTEnable(unsigned long ulBase, unsigned long ulBlock)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulBlock & ~(USART_CR1_UE | USART_CR1_TE | USART_CR1_RE)) == 0);

    //
    // Enable RX | TX | the UART.
    //
    xHWREG(ulBase + USART_CR1) |= ulBlock & (USART_CR1_UE | USART_CR1_TE |
                                  USART_CR1_RE);
}

//*****************************************************************************
//
//! Disables transmitting or receiving.
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
    xASSERT((ulBlock & ~(USART_CR1_UE | USART_CR1_TE | USART_CR1_RE)) == 0);

    //
    // Wait for end of TX.
    //
    while((xHWREG(ulBase + USART_SR) & USART_SR_TC) == 0)
    {
    }

    //
    // Disable the UART/TX/RX.
    //
    xHWREG(ulBase + USART_CR1) &= ~ulBlock & (USART_CR1_UE | USART_CR1_TE |
                                   USART_CR1_RE);
}

//*****************************************************************************
//
//! \brief Enables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables the SIREN control bit for IrDA mode on the UART. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnableIrDA(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xHWREG(ulBase + USART_CR2) &= ~(USART_CR2_LINEN | USART_CR2_CLKEN | USART_CR2_STOP_M);
    xHWREG(ulBase + USART_CR3) &= ~(USART_CR3_SCEN | USART_CR3_HDSEL);
    //
    // Enable SIR.
    //
    xHWREG(ulBase + USART_CR3) |= (USART_CR3_IREN);
}

//*****************************************************************************
//
//! \brief Disables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the SIREN (IrDA) bits.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDisableIrDA(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable SIR .
    //
    xHWREG(ulBase + USART_CR3) &= ~(USART_CR3_IREN);
}

//*****************************************************************************
//
//! Enables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//! \param ulMode is the IrDA mode. 
//! \param ulPrescaler is the IrDA Prescaler value.
//!
//! This function configures the UART IrDA for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter,  the data
//! format in the \e ulConfig parameter, and the ulMode is provided in the
//! \e ulMode parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_9
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO 
//! \b UART_CONFIG_STOP_0P5 and \b UART_CONFIG_STOP_1P5 select one two stop
//! 1.5 or 0.5 bits (respectively).  
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,\b UART_CONFIG_PAR_ODD
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//! The \e ulMode parameter is the logical OR of two values:Prescaler value
//! and IrDA mode.
//! IrDA mode can be:
//! - \b UART_IRDA_MODE_NORMAL - IrDA normal mode
//! - \b UART_IRDA_MODE_LPM - IrDA low-power mode
//! Prescaler value can be: 0-255
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIrDAConfig(unsigned long ulBase, unsigned long ulBaud, 
            unsigned long ulConfig, unsigned long ulMode, unsigned long ulPrescaler)
{    
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulBaud != 0);

    //
    // Disable IrDA, and clear low-power mode flag
    //
    xHWREG(ulBase + USART_CR3) &= ~(USART_CR3_IREN | USART_CR3_IRLP);

    //
    // Set baud, parity, data length, and number of stop bits.
    //
    UARTConfigSet(ulBase, ulBaud, ulConfig);

    //
    // Set Prescaler value in normal mode
    //
    xHWREG(ulBase + USART_GTPR) &= ~(USART_GTPR_PSC_M);
    xHWREG(ulBase + USART_GTPR) |= 0x00000001;
    
    xHWREG(ulBase + USART_CR3) &= ~USART_CR3_IRLP;

    if((ulMode & UART_IRDA_MODE_MASK) == UART_IRDA_MODE_LPM)
    {
        //
        // Set Prescaler value in low-power mode
        //
        xHWREG(ulBase + USART_GTPR) &= ~(USART_GTPR_PSC_M);
        xHWREG(ulBase + USART_GTPR) |= (ulPrescaler & USART_GTPR_PSC_M);

        //
        // Set IrDA as low-power mode
        //
        xHWREG(ulBase + USART_CR3) |= (USART_CR3_IRLP);
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
void
UARTEnableLIN(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    xHWREG(ulBase + USART_CR2) &= ~(USART_CR2_CLKEN | USART_CR2_STOP_M);
    xHWREG(ulBase + USART_CR3) &= ~(USART_CR3_HDSEL | USART_CR3_SCEN | USART_CR3_IREN);
    //
    // Enable LIN Function.
    //
    xHWREG(ulBase + USART_CR2) |= (USART_CR2_LINEN);
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
void
UARTDisableLIN(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable LIN Function.
    //
    xHWREG(ulBase + USART_CR2) &= ~(USART_CR2_LINEN);
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
//! \return None.
//
//*****************************************************************************
void
UARTLINConfig(unsigned long ulBase, unsigned long ulBaud, 
              unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(((ulConfig & UART_CONFIG_BKFL_MASK) ==UART_CONFIG_BKFL_10) ||
            ((ulConfig & UART_CONFIG_BKFL_MASK) ==UART_CONFIG_BKFL_11));

    //
    // Set baud, 8 bit word length, even parity, 2 stop bits (even though the STP2
    // bit is ignored when in smartcard mode, this lets the caller read back
    // the actual setting in use).
    //
    UARTConfigSet(ulBase, ulBaud, 
                  UART_CONFIG_WLEN_8 |
                  UART_CONFIG_STOP_ONE |
                  UART_CONFIG_PAR_NONE);

    //
    // Enable LIN.
    //
    UARTEnableLIN(ulBase);

    xHWREG(ulBase + USART_CR2) &= ~UART_CONFIG_BKFL_11;
    xHWREG(ulBase + USART_CR2) = (ulConfig);

}

//*****************************************************************************
//
//! \brief Receives a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive data register for the specified port.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.  A \b -1 is returned if there are no characters present in the
//! receive data register.  The UARTCharsAvail() function should be called before
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
    // See if there are a character in the read data register.
    //
    if((xHWREG(ulBase + USART_SR) & USART_SR_RXNE))
    {
        //
        // Read and return the next character.
        //
        return(xHWREG(ulBase + USART_DR));
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
//! Gets a character from the receive data register for the specified port.  If there
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
    while(!(xHWREG(ulBase + USART_SR) & USART_SR_RXNE))
    {
    }

    //
    // Now get the char.
    //
    return(xHWREG(ulBase + USART_DR));
}

//*****************************************************************************
//
//! \brief Sends a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit data register for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b false is returned, and the application must retry the function later.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit data register or \b false if there was no space available in the transmit
//! data register.
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
    // See if there is space in the transmit data register.
    //
    if((xHWREG(ulBase + USART_SR) & USART_SR_TXE))
    {
        //
        // Write this character to the transmit data register.
        //
        xHWREG(ulBase + USART_DR) = ucData;

        //
        // Success.
        //
        return(xtrue);
    }
    else
    {
        //
        // There is no space in the transmit data register, so return a failure.
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
//! Sends the character \e ucData to the transmit data register for the specified port.
//! If there is no space available in the transmit data register, this function waits
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
    while(!(xHWREG(ulBase + USART_SR) & USART_SR_TXE))
    {
    }

    //
    // Send the char.
    //
    xHWREG(ulBase + USART_DR) = ucData;
}

//*****************************************************************************
//
//! \brief Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
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
        UARTCharPut(ulBase, ucBuffer[ulCount]);
    }
}
//*****************************************************************************
//
//! \brief Causes a BREAK to be sent.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This is to set is used to send break characters. It can be set and cleared
//! by software. It should be set by software, and will be reset by hardware
//! during the stop bit of break.
//!
//! \return None.
//
//*****************************************************************************
void
UARTBreakCtl(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Set the break condition as requested.
    //
    xHWREG(ulBase + USART_CR1) |= USART_CR1_SBK;
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
//! - \b UART_INT_LIN    - LIN RX Break Field Detected Interrupt
//! - \b UART_INT_PE     - PE interrupt
//! - \b UART_INT_TC     - Transmission complete interrupt
//! - \b UART_INT_IDLE   - IDLE interrupt
//! - \b UART_INT_ERR    - Error interrupt
//! - \b UART_INT_CTS    - CTS interrupt
//! - \b UART_INT_TXE    - Transmit Holding Register Empty
//! - \b UART_INT_RXNE   - Receive Data Available Interrupt
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
    if(ulIntFlags == UART_INT_TC)
    {
        xHWREG(ulBase + USART_CR1) |= USART_CR1_TCIE;
    }
        
    else if(ulIntFlags == UART_INT_PE)
    {
        xHWREG(ulBase + USART_CR1) |= USART_CR1_PEIE;
    }
    else if(ulIntFlags == UART_INT_TXE)
    {
        xHWREG(ulBase + USART_CR1) |= USART_CR1_TXEIE;
    }
    else if(ulIntFlags  == UART_INT_RXNE)
    {
        xHWREG(ulBase + USART_CR1) |= USART_CR1_RXNEIE;
    }
    else if(ulIntFlags  == UART_INT_IDLE)
    {
        xHWREG(ulBase + USART_CR1) |= USART_CR1_IDLEIE;
    }
    else if(ulIntFlags == UART_INT_LIN)
    {
        xHWREG(ulBase + USART_CR2) |= USART_CR2_LBDIE;
    }  
    else if(ulIntFlags == UART_INT_ERR)
    {
        xHWREG(ulBase + USART_CR3) |= USART_CR3_EIE;
    }
    else
    {
        xHWREG(ulBase + USART_CR3) |= USART_CR3_CTSIE;
    }
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
//! - \b UART_INT_LIN    - LIN RX Break Field Detected Interrupt
//! - \b UART_INT_PE     - PE interrupt
//! - \b UART_INT_TC     - Transmission complete interrupt
//! - \b UART_INT_IDLE   - IDLE interrupt
//! - \b UART_INT_ERR    - Error interrupt
//! - \b UART_INT_CTS    - CTS interrupt
//! - \b UART_INT_TXE    - Transmit Holding Register Empty
//! - \b UART_INT_RXNE   - Receive Data Available Interrupt
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
    if(ulIntFlags == UART_INT_TC)
    {
        xHWREG(ulBase + USART_CR1) &= ~USART_CR1_TCIE;
    }
        
    else if(ulIntFlags == UART_INT_PE)
    {
        xHWREG(ulBase + USART_CR1) &= ~USART_CR1_PEIE;
    }
    else if(ulIntFlags == UART_INT_TXE)
    {
        xHWREG(ulBase + USART_CR1) &= ~USART_CR1_TXEIE;
    }
    else if(ulIntFlags  == UART_INT_RXNE)
    {
        xHWREG(ulBase + USART_CR1) &= ~USART_CR1_RXNEIE;
    }
    else if(ulIntFlags  == UART_INT_IDLE)
    {
        xHWREG(ulBase + USART_CR1) &= ~USART_CR1_IDLEIE;
    }
    else if(ulIntFlags == UART_INT_LIN)
    {
        xHWREG(ulBase + USART_CR2) &= ~USART_CR2_LBDIE;
    }  
    else if(ulIntFlags == UART_INT_ERR)
    {
        xHWREG(ulBase + USART_CR3) &= ~USART_CR3_EIE;
    }
    else
    {
        xHWREG(ulBase + USART_CR3) &= ~USART_CR3_CTSIE;
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

    switch(ulBase)
    {
        case USART1_BASE:
        {
            g_pfnUARTHandlerCallbacks[0] = xtUARTCallback;
            break;
        }
        case USART2_BASE:
        {
            g_pfnUARTHandlerCallbacks[1] = xtUARTCallback;
            break;
        }
        case USART3_BASE:
        {
            g_pfnUARTHandlerCallbacks[2] = xtUARTCallback;
            break;
        }
        case USART4_BASE:
        {
            g_pfnUARTHandlerCallbacks[3] = xtUARTCallback;
            break;
        }
        case USART5_BASE:
        {
            g_pfnUARTHandlerCallbacks[4] = xtUARTCallback;
            break;
        }
        default:
            break;
    }
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! \param ulBase is the base address of the UART port.
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
UARTIntStatus(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the interrupt status .
    //
    return(xHWREG(ulBase + USART_SR) << 16);
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
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b UART_INT_LIN    - LIN RX Break Field Detected Interrupt
//! - \b UART_INT_TC     - Transmission complete interrupt
//! - \b UART_INT_CTS    - CTS interrupt
//! - \b UART_INT_RXNE   - Receive Data Available Interrupt
//!
//! \note 
//!   - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun 
//!     error) and IDLE (Idle line detected) flags are cleared by software 
//!     sequence: a read operation to USART_SR register (UARTIntStatus()) 
//!     followed by a read operation to USART_DR register (UARTCharGet()).
//!   - RXNE flag can be also cleared by a read to the USART_DR register 
//!     (UARTCharGet()).
//!   - TC flag can be also cleared by software sequence: a read operation to 
//!     USART_SR register (UARTIntStatus()) followed by a write operation
//!     to USART_DR register (UARTCharPut()).
//!   - TXE flag is cleared only by a write to the USART_DR register 
//!     (UARTCharPut()).
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
    xHWREG(ulBase + USART_SR) = ~(ulIntFlags >> 16);
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
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE) ||
            (ulBase == USART3_BASE) || (ulBase == USART4_BASE));
    xASSERT((ulDMAFlags == UART_DMA_RX) || (ulDMAFlags == UART_DMA_TX) ||
            (ulDMAFlags == (UART_DMA_RX | UART_DMA_TX)));

    //
    // Set the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + USART_CR3) |= ulDMAFlags;
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
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE) ||
            (ulBase == USART3_BASE) || (ulBase == USART4_BASE));
    xASSERT((ulDMAFlags == UART_DMA_RX) || (ulDMAFlags == UART_DMA_TX) ||
            (ulDMAFlags == (UART_DMA_RX | UART_DMA_TX)));

    //
    // Clear the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + USART_CR3) &= ~ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Set the address of the USART node.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//! \param ulAddress is to Indicate the address of the USART node.
//!
//! This function is used to set the address of the USART node.  The
//! \e ulAddress parameter can be the following values: 0 - 15
//!
//! \return None.
//
//*****************************************************************************
void
UARTAddressSet(unsigned long ulBase, unsigned long ulAddress)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulAddress < 16);

    //
    // Set the address of the USART node.
    //
    xHWREG(ulBase + USART_CR2) &= ~USART_CR2_ADD_M;
    xHWREG(ulBase + USART_CR2) |= ulAddress;
}

//*****************************************************************************
//
//! \brief Selects the USART WakeUp method.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//! \param ulWakeup is the specifies the USART wakeup method.
//!
//! This function is used to set the address of the USART node.  The
//! \e ulAddress parameter can be the following values:
//!
//! - UART_WAKEUP_IDLE
//! - UART_WAKEUP_ADDRESS
//!
//! \return None.
//
//*****************************************************************************
void
UARTWakeUpConfig(unsigned long ulBase, unsigned long ulWakeup)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulWakeup == UART_WAKEUP_IDLE) || (ulWakeup == UART_WAKEUP_ADDRESS));

    //
    // Selects the USART WakeUp method.
    //
    xHWREG(ulBase + USART_CR1) &= ~USART_CR1_WAKE;
    xHWREG(ulBase + USART_CR1) |= ulWakeup;
}

//*****************************************************************************
//
//! \brief Sets the specified USART guard time.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//! \param ulGuardTime specifies the guard time.
//!
//! This function is used to set the specified USART guard time.
//! The ulGuardTime can be 0-255.
//!
//! \note The guard time bits are not available for UART4 and UART5. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTGuardTimeSet(unsigned long ulBase, unsigned long ulGuardTime)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Sets the specified USART guard time.
    //
    xHWREG(ulBase + USART_GTPR) &= ~USART_GTPR_GT_M;
    xHWREG(ulBase + USART_GTPR) |= (ulGuardTime << USART_GTPR_GT_S)
                                   &USART_GTPR_GT_M;
}

//*****************************************************************************
//
//! \brief Enables the USART's Half Duplex communication.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//!
//! This function is used to enable the USART's Half Duplex communication.
//!
//! \note None. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTHalfDuplexEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    xHWREG(ulBase + USART_CR2) &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
    xHWREG(ulBase + USART_CR3) &= ~(USART_CR3_SCEN | USART_CR3_IREN);
    //
    // Enables the USART's Half Duplex communication.
    //
    xHWREG(ulBase + USART_CR3) |= USART_CR3_HDSEL;
}

//*****************************************************************************
//
//! \brief Disables the USART's Half Duplex communication.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//!
//! This function is used to disable the USART's Half Duplex communication.
//!
//! \note None. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTHalfDuplexDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disables the USART's Half Duplex communication.
    //
    xHWREG(ulBase + USART_CR3) &= ~USART_CR3_HDSEL;
}

//*****************************************************************************
//
//! \brief Enables the USART's Smart Card mode.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//! \param ulSCMode is the mode of Smartcrd, it can be UART_SC_TX or UART_SC_RX.
//!
//! This function is used to enable the USART's Smart Card mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSmartCardEnable(unsigned long ulBase, unsigned long ulSCMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE)
                                    || (ulBase == USART3_BASE));
    xASSERT((ulSCMode == UART_SC_TX) || (ulSCMode == UART_SC_RX));

    //
    // LINEN,HDSEL and IREN bits must be kept cleared
    //
    xHWREG(ulBase + USART_CR2) &= ~USART_CR2_LINEN;
    xHWREG(ulBase + USART_CR3) &= ~USART_CR3_HDSEL;
    xHWREG(ulBase + USART_CR3) &= ~USART_CR3_IREN;
    
    //
    // 8 bits plus parity
    //
    xHWREG(ulBase + USART_CR1) |= USART_CR1_M;
    xHWREG(ulBase + USART_CR1) |= USART_CR1_PCE;
    
    xHWREG(ulBase + USART_CR2) &= ~USART_CR2_STOP_15;
    if(ulSCMode == UART_SC_TX)
    {
        xHWREG(ulBase + USART_CR2) |= USART_CR2_STOP_05;
    }
    else
    {
        xHWREG(ulBase + USART_CR2) |= USART_CR2_STOP_15;
    }
    //
    // Enables the USART's Smart Card mode.
    //
    xHWREG(ulBase + USART_CR3) |= USART_CR3_SCEN;
}

//*****************************************************************************
//
//! \brief Disables the USART's Smart Card mode.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//!
//! This function is used to disable the USART's Smart Card mode.
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
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE) || (ulBase == USART3_BASE));

    //
    // Disables the USART's Smart Card mode.
    //
    xHWREG(ulBase + USART_CR3) &= ~USART_CR3_SCEN;
}

//*****************************************************************************
//
//! \brief Enables and set the USART's synchronous mode.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//! \param ulConfig is the configuration of synchronous mode.it is the logical  
//! OR of these values:  \b UART_SYN_CPOL, \b UART_SYN_CPHA, \b UART_SYN_LBCL.
//!
//! This function is used to enable the synchronous mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSynModeSet(unsigned long ulBase, unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE) || (ulBase == USART3_BASE));

    //
    // LINEN,HDSEL and IREN bits must be kept cleared
    //
    xHWREG(ulBase + USART_CR2) &= ~USART_CR2_LINEN;
    xHWREG(ulBase + USART_CR3) &= ~USART_CR3_HDSEL;
    xHWREG(ulBase + USART_CR3) &= ~(USART_CR3_IREN | USART_CR3_SCEN);

    //
    // Enables the USART's  and set synchronous mode.
    //
    xHWREG(ulBase + USART_CR2) |= (USART_CR2_CLKEN | ulConfig);
}

//*****************************************************************************
//
//! \brief Disable the USART's synchronous mode.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//!
//! This function is used to enable the synchronous mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSYNDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE) || (ulBase == USART3_BASE));

    //
    // Enables the USART's  and set synchronous mode.
    //
    xHWREG(ulBase + USART_CR2) &= ~USART_CR2_CLKEN;
}
//*****************************************************************************
//
//! \brief Set the USART's modem mode.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//! \param ulControl is the mode of UART modem mode.it is the logical OR of these 
//! values: \b UART_MODEM_RTS, \b UART_MODEM_CTS.
//!
//! This function is used to Set the USART's modem mode.
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
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE) || (ulBase == USART3_BASE));
    xASSERT((ulControl == UART_MODEM_RTS) || (ulControl == UART_MODEM_CTS) || 
            (ulControl == (UART_MODEM_RTS | UART_MODEM_CTS)));
    //
    // Set the USART's modem mode.
    //
    xHWREG(ulBase + USART_CR3) |= ulControl;
}

//*****************************************************************************
//
//! \brief Clear the USART's modem mode.
//!
//! \param ulBase is the base address the USART or the UART peripheral.
//! \param ulControl is the mode of UART modem mode.it is the logical OR of these 
//! values: \b UART_MODEM_RTS, \b UART_MODEM_CTS.
//!
//! This function is used to Clear the USART's modem mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTModemControlClear(unsigned long ulBase, unsigned long ulControl)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == USART1_BASE) || (ulBase == USART2_BASE) || (ulBase == USART3_BASE));
    xASSERT((ulControl == UART_MODEM_RTS) || (ulControl == UART_MODEM_CTS) || 
            (ulControl == (UART_MODEM_RTS | UART_MODEM_CTS)));
    //
    // Clear the USART's modem mode.
    //
    xHWREG(ulBase + USART_CR3) &= ~ulControl;
}
