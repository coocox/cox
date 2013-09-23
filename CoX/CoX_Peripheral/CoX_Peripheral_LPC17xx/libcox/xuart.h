//*****************************************************************************
//
//! \file      xuart.h
//! \brief     Prototypes for the UART Driver.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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

#ifndef __XUART_H__
#define __XUART_H__

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
//! \brief      Values that show xUART Interrupt
//!
//! \section    xUART_Ints_Section 1. Where to use this group
//!             Values that can be passed to \ref xUARTIntEnable,
//!             \ref xUARTIntDisable, and \ref xUARTIntClear as the ulIntFlags
//!             parameter, and returned from UARTIntStatus.
//!
//! \section    xUART_Ints_CoX     2. CoX Port Details
//!
//! |   xUART Interrupts        |       CoX      |          LPC17xx       |
//! |---------------------------|----------------|------------------------|
//! |   xUART_INT_ERROR         |    Mandatory   |            Y           |
//! |   xUART_INT_RT            |    Mandatory   |            N           |
//! |   xUART_INT_TX            |    Mandatory   |            Y           |
//! |   xUART_INT_RX            |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! All Error Interrupt
//
#define xUART_INT_ERROR         INT_RLS

//
//! Receive Timeout Interrupt
//
#define xUART_INT_RT            INT_RLS

//
//! Transmit Interrupt
//
#define xUART_INT_TX            INT_THRE

//
//! Receive Interrupt
//
#define xUART_INT_RX            INT_RDA

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Event_Flag xUART Event Flags
//! \brief      Values that show xUART Event Flags
//!
//! \section    xUART_Event_Flag_Section 1. Where to use this group
//!             Uart Event/Error Flag, Used by IntHandle's Event Callback
//!             Function as ulMsgParam parmeter. User Callback function can
//!             user this to detect what event happened.
//!
//! \section    xUART_Event_Flag_CoX     2. CoX Port Details
//!
//! |   xUART Events            |       CoX      |          LPC17xx       |
//! |---------------------------|----------------|------------------------|
//! |   xUART_EVENT_TX          |    Mandatory   |            Y           |
//! |   xUART_EVENT_RX          |    Mandatory   |            Y           |
//! |   xUART_EVENT_OE          |    Mandatory   |            Y           |
//! |   xUART_EVENT_FE          |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Transmit Event Mask
//
#define xUART_EVENT_TX

//
//! Receive Event Mask
//
#define xUART_EVENT_RX

//
//! Overrun Error Event Mask
//
#define xUART_EVENT_OE

//
//! Parity Error Event Mask
//
#define xUART_EVENT_PE

//
//! Framing Error Event Mask
//
#define xUART_EVENT_FE

//
//! Receive Timeout Event Mask
//
#define xUART_EVENT_RT

//
//! DSR Modem Event Mask
//
#define xUART_EVENT_DSR

//
//! DCD Modem Event Mask
//
#define xUART_EVENT_DCD

//
//! CTS Modem Event Mask
//
#define xUART_EVENT_CTS

//
//! RI Modem Event Mask
//
#define xUART_EVENT_RI

//
//! LIN Mode Sync Break Event Mask
//
#define xUART_EVENT_LMSB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Error xUART Error
//! \brief      Values that show xUART Error
//!
//! \section    xUART_Event_Flag_Section 1. Where to use this group
//!             Values returned from xUARTRxErrorGet().
//!
//! \section    xUART_Event_Flag_CoX 2. CoX Port Details
//!
//! |  xUART Error             |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xUART_RXERROR_OVERRUN   |    Mandatory   |            Y           |
//! |  xUART_RXERROR_BREAK     |    Mandatory   |            Y           |
//! |  xUART_RXERROR_PARITY    |    Mandatory   |            Y           |
//! |  xUART_RXERROR_FRAMING   |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//! Overrun error
#define xUART_RXERROR_OVERRUN   OVERRUN_ERR

//! Break error
#define xUART_RXERROR_BREAK     BREAK_INT

//! Parity error
#define xUART_RXERROR_PARITY    PARITY_ERR

//! Framing error
#define xUART_RXERROR_FRAMING   FRAMING_ERR

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Frame_Configs xUART Frame Configuration
//! \brief      Values that show xUART Frame Configuration
//!
//! \section    xUART_Frame_Configs_Section 1. Where to use this group
//!             Uart Data Frame Configs. Such as Word Length, Parity, Stop bit.
//!             Values that can be passed to xUARTConfig as the ulConfig parameter
//!             and returned by UARTConfigGetExpClk in the pulConfig parameter.
//!             Additionally, the UART_CONFIG_PAR_* subset can be passed to
//!             UARTParityModeSet as the ulParity parameter, and are returned by
//!             UARTParityModeGet.
//!
//! \section    xUART_Frame_Configs_CoX      2. CoX Port Details
//!
//! |  xUART Frame Config      |       CoX      |          LPC17xx       |
//! |--------------------------|----------------|------------------------|
//! |  xUART_CONFIG_WLEN_MASK  |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |  xUART_CONFIG_WLEN_n     |    Mandatory   |   xUART_CONFIG_WLEN55  |
//! |                          |                |   xUART_CONFIG_WLEN_6  |
//! |                          |                |   xUART_CONFIG_WLEN_7  |
//! |                          |                |   xUART_CONFIG_WLEN_8  |
//! |  xUART_CONFIG_PAR_MASK   |    Mandatory   |            Y           |
//! |  xUART_CONFIG_PAR_NONE   |    Mandatory   |            Y           |
//! |  xUART_CONFIG_PAR_EVEN   |    Mandatory   |            Y           |
//! |  xUART_CONFIG_PAR_ODD    |    Mandatory   |            Y           |
//! |  xUART_CONFIG_PAR_ONE    |  Non-Mandatory |            Y           |
//! |  xUART_CONFIG_PAR_ZERO   |  Non-Mandatory |            Y           |
//! |  xUART_CONFIG_STOP_MASK  |    Mandatory   |            Y           |
//! |  xUART_CONFIG_STOP_1     |    Mandatory   |            Y           |
//! |  xUART_CONFIG_STOP_2     |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************
//
// Mask for extracting word length
//
#define xUART_CONFIG_WLEN_MASK  0

//
//! 5 bit data
//
#define xUART_CONFIG_WLEN_5     UART_CFG_LEN_5_BIT

//
//! 6 bit data
//
#define xUART_CONFIG_WLEN_6     UART_CFG_LEN_6_BIT

//
//! 7 bit data
//
#define xUART_CONFIG_WLEN_7     UART_CFG_LEN_7_BIT

//
//! 8 bit data
//
#define xUART_CONFIG_WLEN_8     UART_CFG_LEN_8_BIT

//
//! Mask for extracting stop bits
//
#define xUART_CONFIG_STOP_MASK  0

//
//! One stop bit
//
#define xUART_CONFIG_STOP_1     UART_CFG_STOP_1_BIT

//
//! Two stop bits
//
#define xUART_CONFIG_STOP_2     UART_CFG_STOP_2_BIT

//
//! Mask for extracting parity
//
#define xUART_CONFIG_PAR_MASK   0

//
//! No parity
//
#define xUART_CONFIG_PAR_NONE   UART_CFG_PARITY_NONE

//
//! Even parity
//
#define xUART_CONFIG_PAR_EVEN   UART_CFG_PARITY_EVEN

//
//! Odd parity
//
#define xUART_CONFIG_PAR_ODD    UART_CFG_PARITY_ODD

//
//! Parity bit is one / marked
//
#define xUART_CONFIG_PAR_ONE    UART_CFG_PARITY_1

//
//! Parity bit is zero / space
//
#define xUART_CONFIG_PAR_ZERO   UART_CFG_PARITY_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xUART_Enable_Blocks xUART Enable Blocks
//! \brief      Values that show xUART Enable Blocks
//!
//! \section    xUART_Enable_Blocks_Section 1. Where to use this group
//!             Uart logic blocks  that can be passed to UARTEnable() or
//!             UARTDisable() as the ulBlock parameter.
//!
//! \section    xUART_Enable_Blocks_CoX     2. CoX Port Details
//!
//! |    xUART Enable Block  |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |    xUART_BLOCK_UART    |    Mandatory   |            Y           |
//! |    xUART_BLOCK_RX      |    Mandatory   |            Y           |
//! |    xUART_BLOCK_TX      |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Uart logic block
//
#define xUART_BLOCK_UART        BIT_32_0

//
//! Uart transmit logic block
//
#define xUART_BLOCK_TX          BIT_32_1

//
//! uart receive logic block
//
#define xUART_BLOCK_RX          BIT_32_2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_FIFO_Rx_Tiggle_Level xUART FIFO Rx Tiggle Level
//! \brief      Values that show xUART FIFO Rx Tiggle Level
//!
//! \section    xUART_FIFO_Rx_Tiggle_Level_Section 1. Where to use this group
//!             Values that can be passed to UARTFIFORxLevelSet as the
//!             ulRxLevel parameter.
//!
//! \section    xUART_FIFO_Rx_Tiggle_Level_CoX     2. CoX Port Details
//!
//! |  FIFO Rx Tiggle Level    |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xUART_FIFO_RX_n         |  Non-Mandatory |   xUART_FIFO_RX_1      |
//! |                          |                |   xUART_FIFO_RX_4      |
//! |                          |                |   xUART_FIFO_RX_8      |
//! |                          |                |   xUART_FIFO_RX_14     |
//!
//! @{
//
//*****************************************************************************

//
//! (1 character)
//
#define xUART_FIFO_RX_1         FIFO_CFG_RX_TRI_LVL_0

//
//! (4 character)
//
#define xUART_FIFO_RX_4         FIFO_CFG_RX_TRI_LVL_1

//
//! (8 character)
//
#define xUART_FIFO_RX_8         FIFO_CFG_RX_TRI_LVL_2

//
//! (14 character)
//
#define xUART_FIFO_RX_14        FIFO_CFG_RX_TRI_LVL_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xUART_Exported_APIs xUART API
//! \brief      UART API Reference.
//! \section    xUART_Exported_APIs_Port CoX Port Details
//!
//! |       xUART API                |     CoX      |  LPC17xx  |
//! |--------------------------------|--------------|-----------|
//! | \ref xUARTConfigSet            |  Mandatory   |     Y     |
//! | \ref xUARTEnable               |  Mandatory   |     Y     |
//! | \ref xUARTDisable              |  Mandatory   |     Y     |
//! | \ref xUARTCharGetNonBlocking   |  Mandatory   |     Y     |
//! | \ref xUARTCharGet              |  Mandatory   |     Y     |
//! | \ref xUARTCharPutNonBlocking   |  Mandatory   |     Y     |
//! | \ref xUARTCharPut              |  Mandatory   |     Y     |
//! | \ref xUARTIntEnable            |  Mandatory   |     Y     |
//! | \ref xUARTIntCallbackInit      |  Mandatory   |     Y     |
//! | \ref xUARTIntDisable           |  Mandatory   |     Y     |
//! | \ref xUARTRxErrorGet           |  Mandatory   |     Y     |
//! | \ref xUARTRxErrorClear         |  Mandatory   |     Y     |
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  Sets the configuration of a UART.
//!         This function configures the UART for operation in the specified
//!         data format. The baud rate is provided in the \e ulBaud parameter
//!         and the data format in the \e ulConfig parameter.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  [in] ulBaud is the desired baud rate.
//!
//! \param  [in] ulConfig is the data format for the port (number of data bits,
//!              number of stop bits, and parity).
//!              The \e ulConfig parameter is the logical OR of three values:
//!              the number of data bits, the number of stop bits, and the parity.
//!              - \ref xUART_CONFIG_WLEN_5
//!              - \ref xUART_CONFIG_WLEN_6
//!              - \ref xUART_CONFIG_WLEN_7
//!              - \ref xUART_CONFIG_WLEN_8
//!              - \ref xUART_CONFIG_STOP_1
//!              - \ref xUART_CONFIG_STOP_2
//!              - \ref xUART_CONFIG_PAR_NONE
//!              - \ref xUART_CONFIG_PAR_EVEN
//!              - \ref xUART_CONFIG_PAR_ODD
//!              - \ref xUART_CONFIG_PAR_ONE
//!              - \ref xUART_CONFIG_PAR_ZERO
//!
//! \return None.
//
//*****************************************************************************
#define xUARTConfigSet(ulBase, ulBaud, ulConfig)                              \
         UARTCfg(ulBase, ulBaud, ulConfig)

//*****************************************************************************
//
//! \brief  Enables transmitting or receiving.
//!         Sets the UARTEN, or TXE or RXE bits.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  ulBlock is the block to enable. it is the logical OR of these values:
//!         - \ref xUART_BLOCK_TX
//!         - \ref xUART_BLOCK_RX
//!
//! \return None.
//! \note   Do nothing for lpc17xx mcu
//
//*****************************************************************************
#define xUARTEnable(ulBase, ulBlock)

//*****************************************************************************
//
//! \brief  Disables transmitting or receiving.
//!         Waits for the end ofransmission of the current character, then Clears
//!         the UARTEN or TXE or RXE bits.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  [in] ulBlock is the block to disable. it is the logical OR of
//!              these values:
//!              \ref xUART_BLOCK_UART
//!              \ref xUART_BLOCK_TX
//!              \ref xUART_BLOCK_RX
//!
//! \return None.
//!
//! \note   Do nothing for lpc17xx mcu
//
//*****************************************************************************
#define xUARTDisable(ulBase, ulBlock)

//*****************************************************************************
//
//! \brief  Receives a character from the specified port.
//!         Gets a character from the receive FIFO for the specified port.
//!
//!         This function replaces the original UARTCharNonBlockingGet() API and
//!         performs the same actions.  A macro is provided in <tt>uart.h</tt>
//!         to map the original API to this API.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \return Returns the character read from the specified port, cast as a
//!         \e long. A \b -1 is returned if there are no characters present in the
//!         receive FIFO. The UARTCharsAvail() function should be called before
//!         attempting to call this function.
//
//*****************************************************************************
#define xUARTCharGetNonBlocking(ulBase)                                       \
         UARTByteReadNoBlocking(ulBase)

//*****************************************************************************
//
//! \brief  Waits for a character from the specified port.
//!         Gets a character from the receive FIFO for the specified port.
//!         If there are no characters available, this function waits until a
//!         character is received before returning.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \return Returns the character read from the specified port, cast as a
//!         \e long.
//
//*****************************************************************************
#define xUARTCharGet(ulBase)                                                  \
         UARTByteRead(ulBase)

//*****************************************************************************
//
//! \brief  Sends a character to the specified port.
//!         Writes the character \e ucData to the transmit FIFO for the specified
//!         port. This function does not block, so if there is no space available,
//!         then a \b false is returned, and the application must retry the
//!         function later.
//!
//!         This function replaces the original UARTCharNonBlockingPut() API
//!         and performs the same actions.  A macro is provided in <tt>uart.h</tt>
//!         to map the original API to this API.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  [in] ucData is the character to be transmitted.
//!
//! \return Returns \b true if the character was successfully placed in the
//!         transmit FIFO or \b false if there was no space available in the
//!         transmit FIFO.
//
//*****************************************************************************
#define xUARTCharPutNonBlocking(ulBase, ucData)                               \
         UARTByteWriteNoBlocking(ulBase, ucData)

//*****************************************************************************
//
//! \brief  Waits to send a character from the specified port.
//!         Sends the character \e ucData to the transmit FIFO for the specified
//!         port. If there is no space available in the transmit FIFO, this
//!         function waits until there is space available before returning.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  [in] ucData is the character to be transmitted.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTCharPut(ulBase, ucData)                                          \
         UARTByteWrite(ulBase, ucData)

//*****************************************************************************
//
//! \brief  Enables individual UART interrupt sources.
//!         Enables the indicated UART interrupt sources.  Only the sources that
//!         are enabled can be reflected to the processor interrupt; disabled
//!         sources have no effect on the processor.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  [in] ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!              this parameter is the logical OR of any of the following:
//!              - \ref xUART_INT_ERROR  All Error interrupt
//!              - \ref xUART_INT_RT     Receive Timeout interrupt
//!              - \ref xUART_INT_TX     Transmit interrupt
//!              - \ref xUART_INT_RX     Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
#define xUARTIntEnable(ulBase, ulIntFlags)                                    \
         UARTIntEnable(ulBase, ulIntFlags)

//*****************************************************************************
//
//! \brief  Disables individual UART interrupt sources.
//!         Disables the indicated UART interrupt sources.  Only the sources that
//!         are enabled can be reflected to the processor interrupt; disabled
//!         sources have no effect on the processor.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  [in] ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!              this parameter is the logical OR of any of the following:
//!              - \ref xUART_INT_ERROR  All Error interrupt
//!              - \ref xUART_INT_RT     Receive Timeout interrupt
//!              - \ref xUART_INT_TX     Transmit interrupt
//!              - \ref xUART_INT_RX     Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
#define xUARTIntDisable(ulBase, ulIntFlags)                                   \
         UARTIntDisable(ulBase, ulIntFlags)

//*****************************************************************************
//
//! \brief  Init interrupts callback for the specified UART Port.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \param  [in] xtI2CCallback is callback for the specified UART Port.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTIntCallbackInit(ulBase, xtUARTCallback)                          \
         UARTIntCallbackInit(ulBase, xtUARTCallback)

//*****************************************************************************
//
//! \brief  Gets current receiver errors.
//!         This function returns the current state of each of the 4 receiver
//!         error sources.  The returned errors are equivalent to the four error
//!         bits returned via the previous call to \ref UARTCharGet() or
//!         \ref UARTCharGetNonBlocking() with the exception that the overrun
//!         error is set immediately the overrun occurs rather than when a
//!         character is next read.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \return Returns a logical OR combination of the receiver error flags,
//!         - \ref xUART_RXERROR_FRAMING
//!         - \ref xUART_RXERROR_PARITY
//!         - \ref xUART_RXERROR_BREAK
//!         - \ref xUART_RXERROR_OVERRUN
//
//*****************************************************************************
#define xUARTRxErrorGet(ulBase)                                               \
         UARTStatGet(ulBase)

//*****************************************************************************
//
//! \brief  Clears all reported receiver errors.
//!         This function is used to clear all receiver error conditions reported
//!         via \ref UARTRxErrorGet(). If using the overrun, framing error, parity
//!         error or break interrupts, this function must be called after clearing
//!         the interrupt to ensure that later errors of the same type trigger
//!         another interrupt.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref xUART0_BASE
//!              - \ref xUART1_BASE
//!              - \ref xUART2_BASE
//!              - \ref xUART3_BASE
//!
//! \return None.
//
//*****************************************************************************
#define xUARTRxErrorClear(ulBase)                                             \
         UARTStatGet(ulBase)

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
//! \addtogroup  LPC17xx_UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  LPC17xx_UART_Cfg UART configure parameters.
//!              Values that can be passed to uart general APIs
//! @{
//
//*****************************************************************************

//! Enable FIFO.
#define FIFO_CFG_FIFO_EN               BIT_32_0

//! Disable FIFO.
#define FIFO_CFG_FIFO_DIS              BIT_32_16

//! Flush Rx FIFO.
#define FIFO_CFG_RX_FIFO_RESET         BIT_32_1

//! Flush Tx FIFO.
#define FIFO_CFG_TX_FIFO_RESET         BIT_32_2

//! Enable DMA Mode.
#define FIFO_CFG_DMA_EN                BIT_32_3

//! Disable DMA Mode.
#define FIFO_CFG_DMA_DIS               BIT_32_19

//! Trigger level 0 (1 character)
#define FIFO_CFG_RX_TRI_LVL_0          (BIT_32_23 | BIT_32_22)

//! Trigger level 1 (4 characters)
#define FIFO_CFG_RX_TRI_LVL_1          (BIT_32_23 | BIT_32_6)

//! Trigger level 2 (8 characters)
#define FIFO_CFG_RX_TRI_LVL_2          (BIT_32_22 | BIT_32_7)

//! Trigger level 3 (14 characters)
#define FIFO_CFG_RX_TRI_LVL_3          (BIT_32_7  | BIT_32_6)

//! The UART receiver FIFO is not empty.
#define RX_FIFO_NOT_EMPTY              BIT_32_0

//! Overrun error.
#define OVERRUN_ERR                    BIT_32_1

//! Parity error.
#define PARITY_ERR                     BIT_32_2

//! Framing error.
#define FRAMING_ERR                    BIT_32_3

//! Break interrupt.
#define BREAK_INT                      BIT_32_4

//! Transmitter holding register empty.
//! \note THRE is set immediately upon detection of an empty UART THR and
//!       is cleared on a THR write.
#define TX_FIFO_EMPTY                  BIT_32_5

//! Transmitter empty.
//! \note TEMT is set when both THR and TSR are empty; TEMT is cleared when
//!       either the TSR or the THR contain valid data.
#define TX_EMPTY                       BIT_32_6

//! Error in Rx FIFO
#define RX_FIFO_ERR                    BIT_32_7

//! Invert input serial.
#define IRDA_INV_EN                    BIT_32_1

//! Not Invert input serial.
#define IRDA_INV_DIS                   BIT_32_17

//! Disable fixed pulse width mode.
#define IRDA_FIX_PULSE_DIS             BIT_32_18

//! Fixed pulse width: 2*Tpclk.
#define IRDA_FIX_PULSE_2               (BIT_32_2 | BIT_32_21 | BIT_32_20 | BIT_32_19)

//! Fixed pulse width: 4*Tpclk.
#define IRDA_FIX_PULSE_4               (BIT_32_2 | BIT_32_21 | BIT_32_20 | BIT_32_3)

//! Fixed pulse width: 8*Tpclk.
#define IRDA_FIX_PULSE_8               (BIT_32_2 | BIT_32_21 | BIT_32_4  | BIT_32_19)

//! Fixed pulse width: 16*Tpclk.
#define IRDA_FIX_PULSE_16              (BIT_32_2 | BIT_32_21 | BIT_32_4  | BIT_32_3)

//! Fixed pulse width: 32*Tpclk.
#define IRDA_FIX_PULSE_32              (BIT_32_2 | BIT_32_5  | BIT_32_20 | BIT_32_19)

//! Fixed pulse width: 64*Tpclk.
#define IRDA_FIX_PULSE_64              (BIT_32_2 | BIT_32_5  | BIT_32_20 | BIT_32_3)

//! Fixed pulse width: 128*Tpclk.
#define IRDA_FIX_PULSE_128             (BIT_32_2 | BIT_32_5  | BIT_32_4  | BIT_32_19)

//! Fixed pulse width: 256*Tpclk.
#define IRDA_FIX_PULSE_256             (BIT_32_2 | BIT_32_5  | BIT_32_4  | BIT_32_3)

//! UART Data Length 5-bit.
#define UART_CFG_LEN_5_BIT             (BIT_32_17 | BIT_32_16)

//! UART Data Length 6-bit.
#define UART_CFG_LEN_6_BIT             (BIT_32_17 | BIT_32_0)

//! UART Data Length 7-bit.
#define UART_CFG_LEN_7_BIT             (BIT_32_1  | BIT_32_16)

//! UART Data Length 8-bit.
#define UART_CFG_LEN_8_BIT             (BIT_32_1  | BIT_32_0)

//! UART Stop 1-bit.
#define UART_CFG_STOP_1_BIT            BIT_32_18

//! UART Stop 2-bit.
#define UART_CFG_STOP_2_BIT            BIT_32_2

//! UART None Parity.
#define UART_CFG_PARITY_NONE           (BIT_32_21 | BIT_32_20 | BIT_32_19)

//! UART odd parity.
#define UART_CFG_PARITY_ODD            (BIT_32_21 | BIT_32_20 | BIT_32_3)

//! UART even parity.
#define UART_CFG_PARITY_EVEN           (BIT_32_21 | BIT_32_4  | BIT_32_3)

//! UART forced 1 stick parity.
#define UART_CFG_PARITY_1              (BIT_32_5  | BIT_32_20 | BIT_32_3)

//! UART forced 0 stick parity.
#define UART_CFG_PARITY_0              (BIT_32_5  | BIT_32_4  | BIT_32_3)

//! Enable break transmission.
#define UART_CFG_BREAK_EN              BIT_32_6

//! Disable break transmission.
#define UART_CFG_BREAK_DIS             BIT_32_22

//! Enable Modem loopback mode.
#define LOOPBACK_MODE_EN               BIT_32_4

//! Disable Modem loopback mode.
#define LOOPBACK_MODE_DIS              BIT_32_20

//! Enable Auto-RTS Flow control.
#define AUTO_RTS_EN                    BIT_32_6

//! Disable Auto-RTS Flow control.
#define AUTO_RTS_DIS                   BIT_32_22

//! Enable Auto-CTS Flow control.
#define AUTO_CTS_EN                    BIT_32_7

//! Disable Auto-CTS Flow control.
#define AUTO_CTS_DIS                   BIT_32_23

//! RS-485/EIA-485 Normal Multidrop Mode (NMM) is disabled
#define RS485_NMM_DIS                  BIT_32_16

//! RS-485/EIA-485 Normal Multidrop Mode (NMM) is enabled.In this mode,
//! an address is detected when a received byte causes the UART to set
//! the parity error and generate an interrupt
#define RS485_NMM_EN                   BIT_32_0

//! Enable receiver.
#define RS485_RX_EN                    BIT_32_17

//! Disable receiver.
#define RS485_RX_DIS                   BIT_32_1

//! Enable Auto Address detect.
#define RS485_AUTO_ADDR_EN             BIT_32_2

//! Disable Auto Address detect.
#define RS485_AUTO_ADDR_DIS            BIT_32_18

//! Disable Auto Direction Control.
#define RS485_AUTO_DIR_DIS             BIT_32_20

//! Enable Auto Direction Control, use pin RTS as direction control.
#define RS485_AUTO_DIR_RTS             (BIT_32_4 | BIT_32_19)

//! Enable Auto Direction Control, use pin DTR as direction control.
#define RS485_AUTO_DIR_DTR             (BIT_32_4 | BIT_32_3)

//! The direction control pin will be driven to logic '1' when the
//! transmitter has data to be sent.It will be driven to logic '0'
//! after the last bit of data has been transmitted
#define RS485_AUTO_DIR_INV_EN          BIT_32_5

//! The direction control pin will be driven to logic '0' when the
//! transmitter has data to be sent.It will be driven to logic '1'
//! after the last bit of data has been transmitted.
#define RS485_AUTO_DIR_INV_DIS         BIT_32_21

//! State change detected on modem input CTS.
#define MODEM_DELTA_CTS                BIT_32_0

//! State change detected on modem input DSR.
#define MODEM_DELTA_DSR                BIT_32_1

//! State change detected on modem input RI.
#define MODEM_TRIL_EDGE_RI             BIT_32_2

//! State change detected on modem input DCD.
#define MODEM_DELTA_DCD                BIT_32_3

//! Clear To Send State.
#define MODEM_CTS                      BIT_32_4

//! Data Set Ready State.
#define MODEM_DSR                      BIT_32_5

//! Ring indicator state.
#define MODEM_RI                       BIT_32_6

//! Data carrier detect state.
#define MODEM_DCD                      BIT_32_7


//! Receive data available interrupt.
#define INT_RDA                        BIT_32_0

//! Transfer hold register empty interrupt.
#define INT_THRE                       BIT_32_1

//! Receive line status interrupt.
#define INT_RLS                        BIT_32_2

//! UART modem interrupt.
//! \note This parameter is only suit for UART1.
#define INT_MODEM                      BIT_32_3

//! Clear to send interrupt.
#define INT_CTS                        BIT_32_7

//! Auto-baud end interrupt.
#define INT_ABEO                       BIT_32_8

//! Auto-baud time-out interrupt.
#define INT_ABTO                       BIT_32_9

//! \note Those parameters is only suit for UARTIntCheck function.
//! Receive Line Status
#define INT_FLAG_RLS                   ((unsigned long)0x03)

//! Receive Data Available
#define INT_FLAG_RDA                   ((unsigned long)0x02)

//! Character Time-Out Indicator
#define INT_FLAG_CTI                   ((unsigned long)0x06)

//! THRE Interrupt
#define INT_FLAG_THRE                  ((unsigned long)0x01)

//! Modem Interrupt
#define INT_FLAG_MODEM                 ((unsigned long)0x00)

//! End of auto-baud interrupt.
#define INT_FLAG_ABEO                  BIT_32_8

//! Auto-baud time-out interrupt.
#define INT_FLAG_ABTO                  BIT_32_9

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  LPC17xx _UART_Exported_APIs  LPC17xx  UART API
//! \brief  LPC17xx  UART API Reference.
//! @{
//
//*****************************************************************************

extern void UARTCfg(unsigned long ulBase, unsigned long ulBaud, unsigned long ulCfg);
extern unsigned char UARTByteRead(unsigned long ulBase);
extern void UARTByteWrite(unsigned long ulBase, unsigned char ucData);
extern unsigned long UARTByteReadNoBlocking(unsigned long ulBase);
extern xtBoolean UARTByteWriteNoBlocking(unsigned long ulBase, unsigned char ucData);
extern void UARTStrSend(unsigned long ulBase, unsigned char * pStr);
extern void UARTBufWrite(unsigned long ulBase, unsigned char * pBuf, unsigned long ulLen);
extern void UARTBufRead(unsigned long ulBase, unsigned char * pBuf, unsigned long ulLen);
extern void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long UARTIntStatusGet(unsigned long ulBase);
extern xtBoolean UARTIntStatusCheck(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTIntFlagClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTFIFOCfg(unsigned long ulBase, unsigned long ulCfg);
extern void UARTTransStop(unsigned long ulBase);
extern void UARTTransStart(unsigned long ulBase);
extern unsigned long UARTStatGet(unsigned long ulBase);
extern xtBoolean UARTStatCheck(unsigned long ulBase, unsigned long ulFlags);
extern void UARTIrDACfg(unsigned long ulBase, unsigned long ulCfg);
extern void UARTIrDAEnable(unsigned long ulBase);
extern void UARTIrDADisable(unsigned long ulBase);
extern void UARTModemCfg(unsigned long ulBase, unsigned long ulCfg);
extern void UARTRS485Cfg(unsigned long ulBase, unsigned long ulCfg);
extern void UARTRS485AddrSet(unsigned long ulBase, unsigned long ulAddr);
extern void UARTRS485DlyTimeSet(unsigned long ulBase, unsigned long ulVal);
extern unsigned long UARTModemStatGet(unsigned long ulBase);
extern xtBoolean UARTModemStatCheck(unsigned long ulBase, unsigned long ulFlags);
extern unsigned long UARTIntCallbackInit(unsigned long ulBase,
        xtEventCallback pfnCallback);

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

#endif // __XUART_H__

