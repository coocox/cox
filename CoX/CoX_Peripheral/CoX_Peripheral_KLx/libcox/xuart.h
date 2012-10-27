//*****************************************************************************
//
//! \file xuart.h
//! \brief Prototypes for the UART Driver.
//! \version V2.1.1.1
//! \date 08/20/2012
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

#ifndef __xUART_H__
#define __xUART_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Ints xUART Interrupt
//! \brief Values that show xUART Interrupt
//! \n
//! \section xUART_Ints_Section 1. Where to use this group
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus.
//! \n
//! \section xUART_Ints_CoX 2. CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Interrupts        |       CoX      |         KLxx           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_ERROR         |    Mandatory   |           Y            |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RT            |    Mandatory   |           N            |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_TX            |    Mandatory   |           Y            |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RX            |    Mandatory   |           Y            |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! All Error Interrupt Mask
//
#define xUART_INT_ERROR          (UART_INT_PE | UART_INT_FE |                 \
                                  UART_INT_NE | UART_INT_OR)

//
//! Receive Timeout Interrupt Mask
//
#define xUART_INT_RT            0

//
//! Transmit Interrupt Mask
//
#define xUART_INT_TX            UART_INT_T

//
//! Receive Interrupt Mask
//
#define xUART_INT_RX            UART_INT_R

//
//! DSR Modem Interrupt Mask
//
#define xUART_INT_DSR           0

//
//! DCD Modem Interrupt Mask
//
#define xUART_INT_DCD           0

//
//! CTS Modem Interrupt Mask
//
#define xUART_INT_CTS           0

//
//! RI Modem Interrupt Mask
//
#define xUART_INT_RI            0

//
//! LIN Mode Sync Break Interrupt Mask
//
#define xUART_INT_LMSB          0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Event_Flag xUART Event Flags
//! \brief Values that show xUART Event Flags
//! \n
//! \section xUART_Event_Flag_Section 1. Where to use this group
//! Uart Event/Error Flag, Used by IntHandle's Event Callback Function as
//! ulMsgParam parmeter. User Callback function can user this to detect what
//! event happened.
//! \n
//! \section xUART_Event_Flag_CoX 2. CoX Port Details
//! \verbatim
//! +--------------------------+-----------------+------------------------+
//! |  xUART Events            |       CoX       |          KLxx          |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_TX          |    Mandatory    |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_RX          |    Mandatory    |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_OE          |    Mandatory    |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_FE          |    Mandatory    |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_LBKD        |  Non-Mandarory  |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_RXEDG       |  Non-Mandarory  |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_TC          |  Non-Mandarory  |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_IDLE        |  Non-Mandarory  |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_OR          |  Non-Mandarory  |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_NE          |  Non-Mandarory  |            Y           |
//! |--------------------------|-----------------|------------------------|
//! |  xUART_EVENT_PE          |  Non-Mandarory  |            Y           |
//! +--------------------------+-----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Idle line interrupt
//
#define xUART_EVENT_IDLE        UART_EVENT_IDLE

//
//! LIN break detection interrupt
//
#define xUART_EVENT_LBKD        UART_EVENT_LBKD

//
//! RX pin active edge interrupt
//
#define xUART_EVENT_RXEDG       UART_EVENT_RXEDG

//
//! Transmit register empty interrupt
//
#define xUART_EVENT_TX          UART_EVENT_TX

//
//! Transmit complete interrupt
//
#define xUART_EVENT_TC          UART_EVENT_TC

//
//! Receive data register full interrupt
//
#define xUART_EVENT_RX          UART_EVENT_RX

//
//! overrun error interrupt
//
#define xUART_EVENT_OR          UART_EVENT_OR

//
//! Noise error interrupt
//
#define xUART_EVENT_NE          UART_EVENT_NE

//
//! Frame error interrupt
//
#define xUART_EVENT_FE          UART_EVENT_FE

//
//! parity error interrupt
//
#define xUART_EVENT_PE          UART_EVENT_PE


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Error xUART Error
//! \brief Values that show xUART Error
//! \n
//! \section xUART_Event_Flag_Section 1. Where to use this group
//! Values returned from xUARTRxErrorGet().
//! \n
//! \section xUART_Event_Flag_CoX 2. CoX Port Details
//! \verbatim
//! +--------------------------+----------------+------------------------+
//! |  xUART Error             |       CoX      |         KLxx           |
//! |--------------------------|----------------|------------------------|
//! |  xUART_RXERROR_OVERRUN   |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |  xUART_RXERROR_BREAK     |    Mandatory   |            N           |
//! |--------------------------|----------------|------------------------|
//! |  xUART_RXERROR_PARITY    |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |  xUART_RXERROR_FRAMING   |    Mandatory   |            Y           |
//! +--------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_RXERROR_OVERRUN   UART_ERROR_OR
#define xUART_RXERROR_BREAK     0
#define xUART_RXERROR_FRAMING   UART_ERROR_FE
#define xUART_RXERROR_PARITY    UART_ERROR_PF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Frame_Configs xUART Frame Configuration
//! \brief Values that show xUART Frame Configuration
//! \n
//! \section xUART_Frame_Configs_Section 1. Where to use this group
//! Uart Data Frame Configs. Such as Word Length, Parity, Stop bit.
//! Values that can be passed to xUARTConfig as the ulConfig parameter
//! and returned by UARTConfigGetExpClk in the pulConfig parameter.
//! Additionally, the UART_CONFIG_PAR_* subset can be passed to
//! UARTParityModeSet as the ulParity parameter, and are returned by
//! UARTParityModeGet.
//! \n
//! \section xUART_Frame_Configs_CoX 2. CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Frame Config      |       CoX      |         KLxx           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_WLEN_MASK  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_WLEN_n     |    Mandatory   |   xUART_CONFIG_WLEN_8  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_9  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_10 |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_MASK   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_NONE   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_EVEN   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_ODD    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_MASK  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_1     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_2     |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
//
// Mask for extracting word length
//
#define xUART_CONFIG_WLEN_MASK  UART_CONFIG_WEN_MASK

//
//! 8 bit data
//
#define xUART_CONFIG_WLEN_8     UART_CONFIG_WLEN_8

//
//! 9 bit data
//
#define xUART_CONFIG_WLEN_9     UART_CONFIG_WLEN_9

//
//! 10 bit data
//
#define xUART_CONFIG_WLEN_10    UART_CONFIG_WLEN_10

//
//! Mask for extracting stop bits
//
#define xUART_CONFIG_STOP_MASK  UART_CONFIG_STOP_MASK

//
//! One stop bit
//
#define xUART_CONFIG_STOP_1     UART_CONFIG_STOP_1

//
//! Two stop bits
//
#define xUART_CONFIG_STOP_2     UART_CONFIG_STOP_2

#define xUART_CONFIG_STOP_0_5   0
#define xUART_CONFIG_STOP_1_5   0

//
//! Mask for extracting parity
//
#define xUART_CONFIG_PAR_MASK   UART_CONFIG_PAR_MASK

//
//! No parity
//
#define xUART_CONFIG_PAR_NONE   UART_CONFIG_PAR_NONE

//
//! Even parity
//
#define xUART_CONFIG_PAR_EVEN   UART_CONFIG_PAR_EVEN

//
//! Odd parity
//
#define xUART_CONFIG_PAR_ODD    UART_CONFIG_PAR_ODD

//
//! Parity bit is one / marked
//
#define xUART_CONFIG_PAR_ONE    0

//
//! Parity bit is zero / space
//
#define xUART_CONFIG_PAR_ZERO   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xUART_Enable_Blocks xUART Enable Blocks
//! \brief Values that show xUART Enable Blocks
//! \n
//! \section xUART_Enable_Blocks_Section 1. Where to use this group
//! Uart logic blocks  that can be passed to UARTEnable() or UARTDisable() as
//! the ulBlock parameter.
//! \n
//! \section xUART_Enable_Blocks_CoX 2. CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Enable Block      |       CoX      |        KLxx            |
//! |------------------------|----------------|------------------------|
//! |xUART_BLOCK_UART        |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_BLOCK_RX          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_BLOCK_TX          |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Uart logic block
//
#define xUART_BLOCK_UART        0

//
//! Uart transmit logic block
//
#define xUART_BLOCK_TX          UART_TX

//
//! uart receive logic block
//
#define xUART_BLOCK_RX          UART_RX

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_FIFO_Rx_Tiggle_Level xUART FIFO Rx Tiggle Level
//! \brief Values that show xUART FIFO Rx Tiggle Level
//! \n
//! \section xUART_FIFO_Rx_Tiggle_Level_Section 1. Where to use this group
//! Values that can be passed to UARTFIFORxLevelSet as the ulRxLevel parameter.
//! \n
//! \section xUART_FIFO_Rx_Tiggle_Level_CoX 2. CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |FIFO Rx Tiggle Level    |       CoX      |       KLxx             |
//! |------------------------|----------------|------------------------|
//! |xUART_FIFO_RX_n         |    Mandatory   |         N              |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! (1 character)
//
#define xUART_FIFO_RX_1         0

//
//! (4 character)
//
#define xUART_FIFO_RX_4         0

//
//! (8 character)
//
#define xUART_FIFO_RX_8         0

//
//! (14 character)
//
#define xUART_FIFO_RX_14        0

//
//! (30 character)
//
#define xUART_FIFO_RX_30        0

//
//! (46 character)
//
#define xUART_FIFO_RX_46        0

//
//! (62 character)
//
#define xUART_FIFO_RX_62        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_LIN_Config xUART LIN Configuration
//! \brief Values that show xUART LIN Configuration
//! \n
//! \section xUART_LIN_Config_Section 1. Where to use this group
//! Values that can be passed to xUARTLINConfig().
//! \n
//! \section xUART_LIN_Config_CoX 2. CoX Port Details
//! \verbatim
//! +---------------------------------+-----------------+-------------------+
//! |  xUART LIN Configuration        |       CoX       |      KLxx         |
//! |---------------------------------|-----------------|-------------------|
//! |  xUART_LIN_SYNC_BREAK_LEN_13    |  Non-Mandatory  |         Y         |
//! |---------------------------------|-----------------|-------------------|
//! |  xUART_LIN_SYNC_BREAK_LEN_14    |  Non-Mandatory  |         Y         |
//! |---------------------------------|-----------------|-------------------|
//! |  xUART_LIN_SYNC_BREAK_LEN_15    |  Non-Mandatory  |         Y         |
//! |---------------------------------|-----------------|-------------------|
//! |  xUART_LIN_SYNC_BREAK_LEN_16    |  Non-Mandatory  |         Y         |
//! +---------------------------------+-----------------+-------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_LIN_SYNC_BREAK_LEN_MASK                                        \
                                0


#define xUART_LIN_SYNC_BREAK_LEN_13                                          \
                                UART_LIN_SYNC_BREAK_LEN_13

#define xUART_LIN_SYNC_BREAK_LEN_14                                          \
                                UART_LIN_SYNC_BREAK_LEN_14

#define xUART_LIN_SYNC_BREAK_LEN_15                                          \
                                UART_LIN_SYNC_BREAK_LEN_15

#define xUART_LIN_SYNC_BREAK_LEN_16                                          \
                                UART_LIN_SYNC_BREAK_LEN_16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Exported_APIs xUART API
//! \brief UART API Reference.
//! \section xUART_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+-----------------+
//! |xUART API               |       CoX      |     KLxx        |
//! |------------------------|----------------|-----------------|
//! |xUARTConfigSet          |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTEnable             |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTDisable            |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTCharsAvail         |  Non-Mandatory |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTSpaceAvail         |  Non-Mandatory |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTCharGetNonBlocking |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTCharGet            |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTCharPutNonBlocking |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTCharPut            |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTBusy               |  Non-Mandatory |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTIntEnable          |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTIntCallbackInit    |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTIntDisable         |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTRxErrorGet         |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTRxErrorClear       |    Mandatory   |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTLINConfig          |  Non-Mandatory |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTLINEnable          |  Non-Mandatory |        Y        |
//! |------------------------|----------------|-----------------|
//! |xUARTLINDisable         |  Non-Mandatory |        Y        |
//! |------------------------|----------------|-----------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

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
//! \b xUART_CONFIG_WLEN_7, \b xUART_CONFIG_WLEN_6, and \b xUART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b xUART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE, and
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit,
//! even parity bit, odd parity bit, parity bit always one, and parity bit
//! always zero, respectively).
//!
//!
//! \return None.
//
//*****************************************************************************
#define xUARTConfigSet(ulBase, ulBaud, ulConfig)                               \
        UARTConfigSet(ulBase, ulBaud, ulConfig)


//*****************************************************************************
//
//! \brief Enables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to enable. it is the logical OR of
//! these values:  \b xUART_BLOCK_TX, \b xUART_BLOCK_RX.
//!
//! Sets the UARTEN, or TXE or RXE bits.
//!
//! \note Do nothing in UART,In IrDA and LIN mode will set the Tx or Rx enable
//!
//! \return None.
//
//*****************************************************************************
#define xUARTEnable(ulBase, ulBlock)                                           \
        UARTEnable(ulBase, ulBlock)

//*****************************************************************************
//
//! \brief Disables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to disable. it is the logical OR of
//! these values: \b xUART_BLOCK_UART, \b xUART_BLOCK_TX, \b xUART_BLOCK_RX.
//!
//! Waits for the end ofransmission of the current character,
//! Clears the UARTEN or TXE or RXE bits.
//!
//! \note Do nothing in NUVOTON
//!
//! \return None.
//
//*****************************************************************************
#define xUARTDisable(ulBase, ulBlock)                                          \
         UARTDisable(ulBase, ulBlock)

//*****************************************************************************
//
//! \brief Enables the transmit and receive FIFOs.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This functions enables the transmit and receive FIFOs in the UART.
//!
//! \note Do nothing in NUVOTON
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFIFOEnable(ulBase)

//*****************************************************************************
//
//! \brief Disables the transmit and receive FIFOs.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This functions disables the transmit and receive FIFOs in the UART.
//!
//! \note Do nothing in NUVOTON
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFIFODisable(ulBase)

//*****************************************************************************
//
//! \brief Sets the Rx FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulRxLevel is the receive FIFO interrupt level, specified as one of
//! \b xUART_FIFO_RX_1, \b xUART_FIFO_RX_4, \b xUART_FIFO_RX_8,
//! \b xUART_FIFO_RX_14, \b xUART_FIFO_RX_30, \b xUART_FIFO_RX_46,
//! or \b xUART_FIFO_RX_62.
//!
//! This function sets the FIFO level at which receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFIFORxLevelSet(ulBase, ulRxLevel)

//*****************************************************************************
//
//! \brief Determines if there are any characters in the receive FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive FIFO.
//!
//! \return Returns \b true if there is data in the receive FIFO or \b false
//! if there is no data in the receive FIFO.
//
//*****************************************************************************
#define xUARTCharsAvail(ulBase)                                               \
         UARTCharsAvail(ulBase)

//*****************************************************************************
//
//! \brief Determines if there is any space in the transmit FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit FIFO.
//!
//! \return Returns \b true if there is space available in the transmit FIFO
//! or \b false if there is no space available in the transmit FIFO.
//
//*****************************************************************************
#define xUARTSpaceAvail(ulBase)                                               \
         UARTSpaceAvail(ulBase)


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
#define xUARTCharGetNonBlocking(ulBase)                                       \
        UARTCharGetNonBlocking(ulBase)

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
#define xUARTCharGet(ulBase)                                                  \
        UARTCharGet(ulBase)

//*****************************************************************************
//
//! \brief Sends a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit FIFO for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b false is returned, and the application must retry the function later.
//!
//! This function replaces the original UARTCharNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit FIFO or \b false if there was no space available in the transmit
//! FIFO.
//
//*****************************************************************************
#define xUARTCharPutNonBlocking(ulBase, ucData)                               \
        UARTCharPutNonBlocking(ulBase, ucData)

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
#define xUARTCharPut(ulBase, ucData)                                          \
        UARTCharPut(ulBase, ucData)

//*****************************************************************************
//
//! \brief Determines whether the UART transmitter is busy or not.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Allows the caller to determine whether all transmitted bytes have cleared
//! the transmitter hardware.  If \b false is returned, the transmit FIFO is
//! empty and all bits of the last transmitted character, including all stop
//! bits, have left the hardware shift register.
//!
//! \return Returns \b true if the UART is transmitting or \b false if all
//! transmissions are complete.
//
//*****************************************************************************
#define xUARTBusy(ulBase)                                                     \
    UARTBusy(ulBase)

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
//! - \b xUART_INT_ERROR - All Error interrupt
//! - \b xUART_INT_RT - Receive Timeout interrupt
//! - \b xUART_INT_TX - Transmit interrupt
//! - \b xUART_INT_RX - Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
#define xUARTIntEnable(ulBase, ulIntFlags)                                    \
        UARTIntEnable(ulBase, ulIntFlags)

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
#define xUARTIntCallbackInit(ulBase, xtUARTCallback)                          \
        UARTIntCallbackInit(ulBase, xtUARTCallback)

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
//! - \b xUART_INT_ERROR - All Error interrupt
//! - \b xUART_INT_RT - Receive Timeout interrupt
//! - \b xUART_INT_TX - Transmit interrupt
//! - \b xUART_INT_RX - Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
#define xUARTIntDisable(ulBase, ulIntFlags)                                   \
        UARTIntDisable(ulBase, ulIntFlags)

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
#define xUARTRxErrorGet(ulBase)                                               \
        UARTRxErrorGet(ulBase)

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
#define xUARTRxErrorClear(ulBase)                                             \
        UARTRxErrorClear(ulBase)

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
//! - \b xUART_OUTPUT_RTS - The Modem Control RTS signal
//!
//! \note It is not available on UART2.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTModemControlSet(ulBase, ulControl)

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
//! - \b xUART_OUTPUT_RTS - The Modem Control RTS signal
//!
//! \note It is not available on UART2
//!
//! \return None.
//
//*****************************************************************************
#define xUARTModemControlClear(ulBase, ulControl)

//*****************************************************************************
//
//! \brief Gets the states of the DTR and RTS modem control signals.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current states of each of the two UART modem control signals,
//! DTR and RTS.
//!
//! \note It is not available on UART2
//!
//! \return Returns the states of the handshake output signals.  This will be a
//! logical logical OR combination of values \b xUART_OUTPUT_RTS
//! where the presence of each flag indicates that the
//! associated signal is asserted.
//
//*****************************************************************************
#define xUARTModemControlGet(ulBase, ulControl)

//*****************************************************************************
//
//! \brief Gets the states of the RI, DCD, DSR and CTS modem status signals.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current states of each of the four UART modem status signals,
//! RI, DCD, DSR and CTS.
//!
//! \note It is not available on UART2
//!
//! \return Returns the states of the handshake output signals.  This will be a
//! logical logical OR combination of values \b xUART_INPUT_CTS,  where the
//! presence of each flag indicates that the associated signal is asserted.
//
//*****************************************************************************
#define xUARTModemStatusGet(ulBase)

//*****************************************************************************
//
//! \brief Sets the UART hardware flow control mode to be used.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulMode indicates the flow control modes to be used.  This is a
//! logical OR combination of values \b xUART_FLOWCONTROL_TX and \b
//! xUART_FLOWCONTROL_RX to enable hardware transmit (CTS) and receive (RTS)
//! flow control or \b xUART_FLOWCONTROL_NONE to disable hardware flow control.
//!
//! Sets the required hardware flow control modes.  If \e ulMode contains
//! flag \b xUART_FLOWCONTROL_TX, data is only transmitted if the incoming CTS
//! signal is asserted. If \e ulMode contains flag \b xUART_FLOWCONTROL_RX,
//! the RTS output is controlled by the hardware and is asserted only when
//! there is space available in the receive FIFO.  If no hardware flow control
//! is required, xUART_FLOWCONTROL_NONE should be passed.
//!
//! \note The availability of hardware flow control varies with the KLxx
//! part and UART in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFlowControlSet(ulBase, ulMode)

//*****************************************************************************
//
//! \brief Returns the UART hardware flow control mode currently in use.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current hardware flow control mode.
//!
//! \note The availability of hardware flow control varies with the KLxx
//! part and UART in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return Returns the current flow control mode in use.  This is a
//! logical OR combination of values \b xUART_FLOWCONTROL_TX if transmit
//! (CTS) flow control is enabled and \b xUART_FLOWCONTROL_RX if receive (RTS)
//! flow control is in use.  If hardware flow control is disabled, \b
//! xUART_FLOWCONTROL_NONE will be returned.
//
//*****************************************************************************
#define xUARTFlowControlGet(ulBase)

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
//! \b xUART_CONFIG_WLEN_7, \b xUART_CONFIG_WLEN_6, and \b xUART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \bX UART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE,  and
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit,
//! even parity bit, odd parity bit, parity bit always one, and
//! parity bit always zero, respectively).
//!
//! The \e ulMode parameter can be values:
//! - \b xUART_IRDA_MODE_NORMAL - IrDA normal mode
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTIrDAConfig(ulBase, ulBaud, ulConfig, ulMode);

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
#define xUARTIrDAEnable(ulBase)

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
#define xUARTIrDADisable(ulBase)

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
//! Mode, the LIN Break Field Length.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTLINConfig(ulBase, ulBaud, ulConfig)                              \
        UARTLINConfig(ulBase, ulBaud, ulConfig)

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
#define xUARTLINEnable(ulBase)                                                \
        UARTLINEnable(ulBase)

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
#define xUARTLINDisable(ulBase)                                               \
        UARTLINDisable(ulBase)


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLxx_UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_INT_Type KLxx UART Interrupt Type
//! \brief Values that show KLxx UART Interrupt Type
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus.
//! @{
//
//*****************************************************************************

//
//! Idle line interrupt
//
#define UART_INT_IL             0x02001000UL

//
//! LIN break detection interrupt
//
#define UART_INT_LBKD           0x01000080UL

//
//! RX pin active edge interrupt
//
#define UART_INT_RXEDG          0x01000040UL

//
//! Transmit register empty interrupt
//
#define UART_INT_T              0x02008000UL

//
//! Transmit complete interrupt
//
#define UART_INT_TC             0x02004000UL

//
//! Receive data register full interrupt
//
#define UART_INT_R              0x02002000UL

//
//! overrun error interrupt
//
#define UART_INT_OR             0x04080000UL

//
//! Noise error interrupt
//
#define UART_INT_NE             0x04040000UL

//
//! Frame error interrupt
//
#define UART_INT_FE             0x04020000UL

//
//! parity error interrupt
//
#define UART_INT_PE             0x04010000UL

#define UART_INT_BDH_FLAG       0x01000000UL
#define UART_INT_BDH_MASK       0x000000FFUL
#define UART_INT_BDH_SHIFT      0x00000000UL

#define UART_INT_C2_FLAG        0x02000000UL
#define UART_INT_C2_MASK        0x0000FF00UL
#define UART_INT_C2_SHIFT       0x00000008UL

#define UART_INT_C3_FLAG        0x04000000UL
#define UART_INT_C3_MASK        0x00FF0000UL
#define UART_INT_C3_SHIFT       0x00000010UL


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_Line_Config KLxx UART Line Configuration
//! \brief Values that show KLxx UART Line Configuration
//! Values that can be passed to UARTConfigSet as the ulConfig parameter
//! and returned by UARTConfigGetExpClk in the pulConfig parameter.
//! Additionally, the UART_CONFIG_PAR_* subset can be passed to
//! UARTParityModeSet as the ulParity parameter, and are returned by
//! UARTParityModeGet.
//! @{
//
//*****************************************************************************

//
//! UART chars length mask
//
#define UART_CONFIG_WEN_MASK                                                 \
                                0x0000000FUL

//
//! UART Parity mask
//
#define UART_CONFIG_PAR_MASK                                                 \
                                0x000000F0UL

//
//! UART stop bits mask
//
#define UART_CONFIG_STOP_MASK                                                \
                                0x00000F00UL

//
//! UART Sample rate mask
//
#define UART_CONFIG_SAMPLE_RATE_MASK                                         \
                                0x00FF0000UL

//
//! UART Sample rate shift
//
#define UART_CONFIG_SAMPLE_RATE_SHIFT                                        \
                                0x00000010UL

//
//! UART chars length
//
#define UART_CONFIG_WLEN_8                                                   \
                                0x00000001UL
#define UART_CONFIG_WLEN_9                                                   \
                                0x00000002UL
#define UART_CONFIG_WLEN_10                                                  \
                                0x00000004UL

//
//! Odd parity
//
#define UART_CONFIG_PAR_ODD                                                  \
                                0x00000010UL

//
//! Even parity
//
#define UART_CONFIG_PAR_EVEN                                                 \
                                0x00000020UL

//
//! No parity
//
#define UART_CONFIG_PAR_NONE                                                 \
                                0x00000040UL

//
//! 1 stop bit
//
#define UART_CONFIG_STOP_1                                                   \
                                0x00000100UL

//
//! 2 stop bit
//
#define UART_CONFIG_STOP_2                                                   \
                                0x00000200UL

//
//! UART Oversample default ratio
//
#define UART_CONFIG_SAMPLE_RATE_DEFAULT                                      \
                                0x000F0000UL

//
//! UART Oversample ratio
//
#define UART_CONFIG_SAMPLE_RATE_04                                           \
                                0x00030000UL

#define UART_CONFIG_SAMPLE_RATE_05                                           \
                                0x00040000UL

#define UART_CONFIG_SAMPLE_RATE_06                                           \
                                0x00050000UL

#define UART_CONFIG_SAMPLE_RATE_07                                           \
                                0x00060000UL

#define UART_CONFIG_SAMPLE_RATE_08                                           \
                                0x00070000UL

#define UART_CONFIG_SAMPLE_RATE_09                                           \
                                0x00080000UL

#define UART_CONFIG_SAMPLE_RATE_10                                           \
                                0x00090000UL

#define UART_CONFIG_SAMPLE_RATE_11                                           \
                                0x000A0000UL

#define UART_CONFIG_SAMPLE_RATE_12                                           \
                                0x000B0000UL

#define UART_CONFIG_SAMPLE_RATE_13                                           \
                                0x000C0000UL

#define UART_CONFIG_SAMPLE_RATE_14                                           \
                                0x000D0000UL

#define UART_CONFIG_SAMPLE_RATE_15                                           \
                                0x000E0000UL

#define UART_CONFIG_SAMPLE_RATE_16                                           \
                                0x000F0000UL

#define UART_CONFIG_SAMPLE_RATE_17                                           \
                                0x00100000UL

#define UART_CONFIG_SAMPLE_RATE_18                                           \
                                0x00110000UL

#define UART_CONFIG_SAMPLE_RATE_19                                           \
                                0x00120000UL

#define UART_CONFIG_SAMPLE_RATE_20                                           \
                                0x00130000UL

#define UART_CONFIG_SAMPLE_RATE_21                                           \
                                0x00140000UL

#define UART_CONFIG_SAMPLE_RATE_22                                           \
                                0x00150000UL

#define UART_CONFIG_SAMPLE_RATE_23                                           \
                                0x00160000UL

#define UART_CONFIG_SAMPLE_RATE_24                                           \
                                0x00170000UL

#define UART_CONFIG_SAMPLE_RATE_25                                           \
                                0x00180000UL

#define UART_CONFIG_SAMPLE_RATE_26                                           \
                                0x00190000UL

#define UART_CONFIG_SAMPLE_RATE_27                                           \
                                0x001A0000UL

#define UART_CONFIG_SAMPLE_RATE_28                                           \
                                0x001B0000UL

#define UART_CONFIG_SAMPLE_RATE_29                                           \
                                0x001C0000UL

#define UART_CONFIG_SAMPLE_RATE_30                                           \
                                0x001D0000UL

#define UART_CONFIG_SAMPLE_RATE_31                                           \
                                0x001E0000UL

#define UART_CONFIG_SAMPLE_RATE_32                                           \
                                0x001F0000UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLxx_UART_DMA_Flag KLxx UART DMA Flag
//! \brief Values that show KLxx UART DMA Flag
//! Values that can be passed to UARTDMAEnable() and UARTDMADisable().
//! @{
//
//*****************************************************************************

//
//! Enable DMA for transmit
//
#define UART_DMA_TX             0x00000080UL

//
//! Enable DMA for receive
//
#define UART_DMA_RX             0x00000040UL

//
//! DMA for transmit register empty
//
#define UART_DMA_T              0x00000080UL

//
//! DMA for transmit complete
//
#define UART_DMA_TC             0x00000040UL

//
//! DMA for receive register full
//
#define UART_DMA_R              0x00000020UL

//
//! DMA for idle line
//
#define UART_DMA_IDLE           0x00000010UL

//
//! DMA for line break detect
//
#define UART_DMA_LBKD           0x00000008UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_Wake_Up KLxx UART Wake Up
//! \brief Values that show KLxx UART Wake Up method.
//! Values that can be passed to UARTWakeUpConfig().
//! @{
//
//*****************************************************************************

//
//! UART wakeup mask
//
#define UART_WAKEUP_MASK        0x00000008UL

//
//! WakeUp by an idle line detection
//
#define UART_WAKEUP_IDLE_LINE   0x00000000UL

//
//! WakeUp by an address mark
//
#define UART_WAKEUP_ADDRESS_MARK                                              \
                                0x00000008UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLxx_Idle_line_type KLxx UART Idle line type.
//! \brief Values that used to configures UART Idle line type.
//! Values that can be passed to UARTIdleLineTypeConfig.
//! @{
//
//*****************************************************************************

//
//! UART Idle Line type
//
#define UART_IDLE_TYPE_AFTER_START                                           \
                                0x00000000UL

//
//! UART Idle Line type
//
#define UART_IDLE_TYPE_AFTER_STOP                                            \
                                0x00000004UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLxx_Match_address KLxx UART Match Address.
//! \brief Values that used to configures UART match address.
//! Values that can be passed to UARTMatchAddressSet / UARTMatchAddrModeEnable
//! UARTMatchAddrModeDisable.
//! @{
//
//*****************************************************************************

//
//! UART Match address 1
//
#define UART_ADDRESS_CHL_1     0x00000001UL

//
//! UART Match address 2
//
#define UART_ADDRESS_CHL_2     0x00000002UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_Wakeup KLxx UART Wakeup Mode.
//! \brief Values that used to configures UART wakeup mode.
//! Values that can be passed to UARTWakeupMethodConfig.
//! @{
//
//*****************************************************************************

//
//! UART Wakeup Method Mask
//
#define UART_WAKEUP_MASK                                                     \
                                0x00000008UL

//
//! UART wakeup by Idle line
//
#define UART_WAKEUP_IDLE_LINE                                                \
                                0x00000000UL

//
//! UART wakeup by match address
//
#define UART_WAKEUP_ADDRESS_MARK                                             \
                                0x00000008UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_ERROR_FLAG KLxx UART Error Flag and Mask.
//! \brief Values that show KLxx UART Error Flag and mask.
//! Values that can be passed to UARTRxErrorGet() and UARTRxErrorClear().
//! @{
//
//*****************************************************************************

//
// Error Mask
//
#define UART_ERROR_MASK            0x0000000FUL

//
// Overrun Error Flag
//
#define UART_ERROR_OR              0x00000008UL

//
// Noise Error Flag
//
#define UART_ERROR_NF              0x00000004UL

//
// Frame Error Flag
//
#define UART_ERROR_FE              0x00000002UL

//
// Parity Error Flag
//
#define UART_ERROR_PF              0x00000001UL


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_Enable_Disable KLxx UART Enable Disable.
//! \brief Values that show KLxx UART Wake Up method.
//! Values that can be passed to UARTEnable() UARTDisable().
//! @{
//
//*****************************************************************************

#define UART_TX                 0x00000008UL
#define UART_RX                 0x00000004UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_EVEN_TYPE KLxx UART Interrupt Event type.
//! \brief Values that show KLxx Interrupt Event type.
//! @{
//
//*****************************************************************************



//
//! LIN break detection interrupt
//
#define UART_EVENT_LBKD         0x00008000UL

//
//! RX pin active edge interrupt
//
#define UART_EVENT_RXEDG        0x00004000UL

//
//! Transmit register empty interrupt
//
#define UART_EVENT_TX           0x00000080UL

//
//! Transmit complete interrupt
//
#define UART_EVENT_TC           0x00000040UL

//
//! Receive data register full interrupt
//
#define UART_EVENT_RX           0x00000020UL

//
//! Idle line interrupt
//
#define UART_EVENT_IDLE         0x00000010UL

//
//! overrun error interrupt
//
#define UART_EVENT_OR           0x00000008UL

//
//! Noise error interrupt
//
#define UART_EVENT_NE           0x00000004UL

//
//! Frame error interrupt
//
#define UART_EVENT_FE           0x00000002UL

//
//! parity error interrupt
//
#define UART_EVENT_PE           0x00000001UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_OutMode KLxx UART OutMode.
//! \brief Values that configure KLxx UART Output Mode.
//! Values that can be passed to UARTOutModeConfig.
//! @{
//
//*****************************************************************************

//
//! Mode Mask
//
#define UART_MODE_MASK          0x000000A0UL

//
//! Normal mode
//
#define UART_MODE_NORMAL        0x00000000UL

//
//! Single Line Mode
//
#define UART_MODE_SINGLE_LINE   0x000000A0UL

//
//! Loops Mode
//
#define UART_MODE_LOOP          0x00000080UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! \addtogroup KLxx_UART_LIN_Config KLxx UART LIN Configuration
//! \brief Values that show KLxx UART LIN Configuration
//! Values that can be passed to UARTLINConfig as the ulConfig parameter
//! @{
//
//*****************************************************************************

//
//! Mask for LIN Break Field Length
//
#define UART_CONFIG_BKFL_MASK                                                \
                                0x00000020UL

//
//! LIN Break Field Length 10
//
#define UART_LIN_SYNC_BREAK_LEN_10                                           \
                                0x00000000UL


//
//! LIN Break Field Length 11
//
#define UART_LIN_SYNC_BREAK_LEN_11                                           \
                                0x00000020UL


//
//! LIN Break Field Length 12
//
#define UART_LIN_SYNC_BREAK_LEN_12                                           \
                                0x00100020UL


//
//! LIN Break Field Length 13
//
#define UART_LIN_SYNC_BREAK_LEN_13                                           \
                                0x04000000UL

//
//! LIN Break Field Length 14
//
#define UART_LIN_SYNC_BREAK_LEN_14                                           \
                                0x04000020UL

//
//! LIN Break Field Length 15
//
#define UART_LIN_SYNC_BREAK_LEN_15                                           \
                                0x04100020UL

//
//! LIN Break Field Length 16
//
#define UART_LIN_SYNC_BREAK_LEN_16                                           \
                                0x04002020UL

//
//! S2 mask and shift
//
#define UART_LIN_SYNC_BREAK_S2_MASK                                          \
                                0xFF000000UL
#define UART_LIN_SYNC_BREAK_S2_SHIFT                                         \
                                0x00000018UL

//
//! C1 mask and shift
//
#define UART_LIN_SYNC_BREAK_C1_MASK                                          \
                                0x00FF0000UL
#define UART_LIN_SYNC_BREAK_C1_SHIFT                                         \
                                0x00000010UL

//
//! C4 mask and shift
//
#define UART_LIN_SYNC_BREAK_C4_MASK                                          \
                                0x0000FF00UL
#define UART_LIN_SYNC_BREAK_C4_SHIFT                                         \
                                0x00000008UL

//
//! BDH mask and shift
//
#define UART_LIN_SYNC_BREAK_BDH_MASK                                         \
                                0x000000FFUL
#define UART_LIN_SYNC_BREAK_BDH_SHIFT                                        \
                                0x00000000UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_UART_Exported_APIs KLxx UART API
//! \brief KLxx UART API Reference.
//! @{
//
//*****************************************************************************


void UARTConfigSet(unsigned long ulBase, unsigned long ulBaud,
                   unsigned long ulConfig);

void UARTEnable(unsigned long ulBase, unsigned long ulConfig);

void UARTDisable(unsigned long ulBase, unsigned long ulConfig);

xtBoolean UARTCharsAvail(unsigned long ulBase);

xtBoolean UARTSpaceAvail(unsigned long ulBase);

unsigned long UARTCharGetNonBlocking(unsigned long ulBase);

unsigned char UARTCharGet(unsigned long ulBase);

xtBoolean UARTCharPutNonBlocking(unsigned long ulBase, unsigned char ulData);

void UARTCharPut(unsigned long ulBase, unsigned char ulData);

xtBoolean UARTBusy(unsigned long ulBase);

void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags);

void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags);

void UARTIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback);

unsigned long UARTRxErrorGet(unsigned long ulBase);

void UARTRxErrorClear(unsigned long ulBase);

void UARTLINConfig(unsigned long ulBase, unsigned long ulBaud,
                   unsigned long ulConfig);

void UARTLINEnable(unsigned long ulBase);

void UARTLINDisable(unsigned long ulBase);

void UARTLINSyncBreakPut(unsigned long ulBase);

void UARTDMAEnable(unsigned long ulBase, unsigned long ulConfig);

void UARTDMADisable(unsigned long ulBase, unsigned long ulConfig);

void UARTTxInvertEnable(unsigned long ulBase);

void UARTTxInvertDisable(unsigned long ulBase);

void UARTRxInvertEnable(unsigned long ulBase);

void UARTRxInvertDisable(unsigned long ulBase);

void UARTOutModeConfig(unsigned long ulBase, unsigned long ulConfig);

void UARTWaitModeRun(unsigned long ulBase);

void UARTWaitModeStop(unsigned long ulBase);

void UARTWakeupMethodConfig(unsigned long ulBase, unsigned long ulConfig);

void UARTMsbFirst(unsigned long ulBase);

void UARTLsbFirst(unsigned long ulBase);

xtBoolean UARTReceiverStatus(unsigned long ulBase);

void UARTMatchAddressSet(unsigned long ulBase, unsigned long ulChl,
                         unsigned long ulAddr);

void UARTMatchAddrModeEnable(unsigned long ulBase, unsigned long ulChl);

void UARTMatchAddrModeDisable(unsigned long ulBase, unsigned long ulChl);

xtBoolean UARTIdleFlagGet(unsigned long ulBase);

unsigned char UARTGetBit9(unsigned long ulBase);

unsigned char UARTGetBit10(unsigned long ulBase);

void UARTBothEdgeSampleEnable (unsigned long ulBase);

void UARTBothEdgeSampleDisable(unsigned long ulBase);

void UARTReSyncEnable(unsigned long ulBase);

void UARTReSyncDisable (unsigned long ulBase);

void UARTSetBit9(unsigned long ulBase, unsigned char ulCh);

void UARTSetBit10(unsigned long ulBase, unsigned char ulCh);

void UARTIdleConfig(unsigned long ulBase, unsigned long ulConfig);

void UARTIdleFlagClear(unsigned long ulBase);

void UARTIdleSend(unsigned long ulBase);


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __xUART_H__


