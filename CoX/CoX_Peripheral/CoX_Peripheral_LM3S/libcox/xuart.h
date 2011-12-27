//*****************************************************************************
//
//! \file xuart.h
//! \brief Defines and Macros for UART API.
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

#ifndef __xUART_H__
#define __xUART_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
//extern "C"
//{
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
//! \addtogroup xUART_User_Config xUART User Config
//! @{
//
//*****************************************************************************

//
//! If the UART Using the DMA feather and interrupt enable, please set the config
//! to 1, else 0
//
#define xUART_CONFIG_DMA_INT    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************   

//*****************************************************************************
//
//! \addtogroup xUART_Ints xUART Interrupt
//!
//! \section xUART_Ints_Section 1. Where to use this group
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus. 
//! \n
//! \section xUART_Ints_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Interrupts        |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_ERROR         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RT            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_TX            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RX            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_DSR           |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_DCD           |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_CTS           |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RI            |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_LMSB          |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transmit Interrupt Mask
//
#define xUART_INT_TX            UART_INT_TX       

//
//! Receive Interrupt Mask
//
#define xUART_INT_RX            UART_INT_RX   

//
//! Line Error Interrupt Mask
//
#define xUART_INT_ERROR         UART_INT_OE | UART_INT_PE | UART_INT_FE                                
                               
//
//! Receive Timeout Interrupt Mask
//
#define xUART_INT_RT            UART_INT_RT        

//
//! DSR Modem Interrupt Mask
//
#define xUART_INT_DSR           UART_INT_DSR       

//
//! DCD Modem Interrupt Mask
//
#define xUART_INT_DCD           UART_INT_DCD       

//
//! CTS Modem Interrupt Mask
//
#define xUART_INT_CTS           UART_INT_CTS 

//
//! RI Modem Interrupt Mask
//
#define xUART_INT_RI            UART_INT_RI 

//
//! LIN Mode Sync Break Interrupt Mask
//
#define xUART_INT_LMSB          UART_INT_LMSB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup xUART_Event_Flag xUART Event Flags
//! \brief UART Event used by the intterupt callback function.
//!
//! \section xUART_Event_Flag_Section 1. Where to use this group
//! Uart Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parmeter. User Callback function can user this to detect what 
//! event happened.
//! \n
//! \section xUART_Event_Flag_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Events            |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_TX          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_RX          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_OE          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_FE          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_RT          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_PE          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_DSR         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_DCD         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_CTS         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_RI          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_LMSB        |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transmit Event Mask
//
#define xUART_EVENT_TX          UART_INT_TX       

//
//! Receive Event Mask
//
#define xUART_EVENT_RX          UART_INT_RX   

//
//! Overrun Error Event Mask
//
#define xUART_EVENT_OE          UART_INT_OE       

//
//! Parity Error Event Mask
//
#define xUART_EVENT_PE          UART_INT_PE       

//
//! Framing Error Event Mask
//
#define xUART_EVENT_FE          UART_INT_FE       

//
//! Receive Timeout Event Mask
//
#define xUART_EVENT_RT          UART_INT_RT       

//
//! DSR Modem Event Mask
//
#define xUART_EVENT_DSR         UART_INT_DSR       

//
//! DCD Modem Event Mask
//
#define xUART_EVENT_DCD         UART_INT_DCD       

//
//! CTS Modem Event Mask
//
#define xUART_EVENT_CTS         UART_INT_CTS       

//
//! RI Modem Event Mask
//
#define xUART_EVENT_RI          UART_INT_RI 

//
//! LIN Mode Sync Break Event Mask
//
#define xUART_EVENT_LMSB        UART_INT_LMSB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Error xUART Error
//!
//! \section xUART_Event_Flag_Section 1. Where to use this group
//! Values returned from xUARTRxErrorGet().
//! 
//! \section xUART_Event_Flag_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Error             |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_OVERRUN   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_BREAK     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_PARITY    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_FRAMING   |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_RXERROR_OVERRUN   UART_RXERROR_OVERRUN
#define xUART_RXERROR_BREAK     UART_RXERROR_BREAK
#define xUART_RXERROR_PARITY    UART_RXERROR_PARITY
#define xUART_RXERROR_FRAMING   UART_RXERROR_FRAMING

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Frame_Configs xUART Frame Configuration
//! \brief Uart Data Frame Configs. Such as Word Length, Parity, Stop bit.
//!
//! \section xUART_Frame_Configs_Section 1. Where to use this group
//! Values that can be passed to xUARTConfig() as the ulConfig parameter
//! and returned by UARTConfigGetExpClk() in the pulConfig parameter.
//! 
//! \section xUART_Frame_Configs_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Frame Config      |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_WLEN_MASK  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_WLEN_n     |    Mandatory   |   xUART_CONFIG_WLEN_8  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_7  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_6  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_5  |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_MASK   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_NONE   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_EVEN   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_ODD    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_ONE    |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_ZERO   |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_MASK  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_1     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_2     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_0_5   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_1_5   |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Mask for extracting word length
//
#define xUART_CONFIG_WLEN_MASK  UART_CONFIG_WLEN_MASK  

//
//! 8 bit data
//
#define xUART_CONFIG_WLEN_8     UART_CONFIG_WLEN_8  

//
//! 7 bit data
//
#define xUART_CONFIG_WLEN_7     UART_CONFIG_WLEN_7  

//
//! 6 bit data
//
#define xUART_CONFIG_WLEN_6     UART_CONFIG_WLEN_6

//
//! 5 bit data
//
#define xUART_CONFIG_WLEN_5     UART_CONFIG_WLEN_5

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

//#define xUART_CONFIG_STOP_0_5   0x00000000 
//#define xUART_CONFIG_STOP_1_5   0x00000000  

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
#define xUART_CONFIG_PAR_ONE    UART_CONFIG_PAR_ONE 

//
//! Parity bit is zero / space
//
#define xUART_CONFIG_PAR_ZERO   UART_CONFIG_PAR_ZERO 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_IrDA_Mode xUART IrDA Mode
//! \brief Uart IrDA mode.
//!
//! \section xUART_IrDA_Mode_Section 1. Where to use this group
//! Uart IrDA mode that con be passed to UARTIrDAConfig as the
//! ulMode parameter. 
//! \n
//! \section xUART_IrDA_Mode_CoX 2. CoX Port Details 
//! \verbatim
//! +-------------------------+----------------+------------------------+
//! |xUART IrDA Mode          |       CoX      |        Stellaris       |
//! |-------------------------|----------------|------------------------|
//! |xUART_IRDA_MODE_MASK     |  Non-Mandatory |            Y           |
//! |-------------------------|----------------|------------------------|
//! |xUART_IRDA_MODE_NORMAL   |  Non-Mandatory |            Y           |
//! |-------------------------|----------------|------------------------|
//! |xUART_IRDA_MODE_LOW_POWER|  Non-Mandatory |            Y           |
//! +-------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// IrDA Mode Mask
//
#define xUART_IRDA_MODE_MASK    UART_IRDA_MODE_MASK

//
//! IrDA Normal Mode
//
#define xUART_IRDA_MODE_NORMAL  UART_IRDA_MODE_NORMAL

//
//! IrDA Low-Power Mode
//
#define xUART_IRDA_MODE_LOW_POWER                                              \
                                UART_IRDA_MODE_LOW_POWER

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xUART_Enable_Blocks xUART Enable Blocks
//!
//! \section xUART_Enable_Blocks_Section 1. Where to use this group
//! Uart logic blocks  that can be passed to UARTEnable() or UARTDisable() as 
//! the ulBlock parameter.
//! \n
//! \section xUART_Enable_Blocks_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Enable Block      |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_BLOCK_UART        |    Mandatory   |            Y           |
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
#define xUART_BLOCK_UART        UART_BLOCK_UART

//
//! Uart transmit logic block
//
#define xUART_BLOCK_TX          UART_BLOCK_TX

//
//! uart receive logic block
//
#define xUART_BLOCK_RX          UART_BLOCK_RX

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_FIFO_TX_Tiggle_Level  xUART FIFO Tx Tiggle Level
//!
//! \section xUART_FIFO_Tx_Tiggle_Level_Section 1. Where to use this group
//! Values that can be passed to xUARTFIFOTxLevelSet() as the \b ulTxLevel 
//! parameter.
//! 
//! \section xUART_FIFO_Rx_Tiggle_Level_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |FIFO Tx Tiggle Level    |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_FIFO_TX_n         |    Mandatory   |     xUART_FIFO_TX_0    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_TX_1    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_TX_2    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_TX_4    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_TX_6    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_TX_7    |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transmit interrupt at FIFO is completely empty (0 character)
//
#define xUART_FIFO_TX_0         0x00000007  // UARTIFLS.TXIFLSEL Reserved value 

//
//! Transmit interrupt at 1 character
//
#define xUART_FIFO_TX_1         UART_FIFO_TX1_8  

//
//! Transmit interrupt at 2 character
//
#define xUART_FIFO_TX_2         UART_FIFO_TX2_8  

//
//! Transmit interrupt at 4 character
//
#define xUART_FIFO_TX_4         UART_FIFO_TX4_8  

//
//! Transmit interrupt at 6 character
//
#define xUART_FIFO_TX_6         UART_FIFO_TX6_8  

//
//! Transmit interrupt at 7 character
//
#define xUART_FIFO_TX_7         UART_FIFO_TX7_8 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_FIFO_Rx_Tiggle_Level  xUART FIFO Rx Tiggle Level
//!
//! \section xUART_FIFO_Rx_Tiggle_Level_Section 1. Where to use this group
//! Values that can be passed to xUARTFIFORxLevelSet() as the \b ulRxLevel 
//! parameter.
//! 
//! \section xUART_FIFO_Rx_Tiggle_Level_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |FIFO Rx Tiggle Level    |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_FIFO_RX_n         |    Mandatory   |     xUART_FIFO_RX_1    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_RX_2    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_RX_4    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_RX_6    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_RX_7    |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Receive interrupt at 1 character
//
#define xUART_FIFO_RX_1         UART_FIFO_RX1_8  

//
//! Receive interrupt at 2 character
//
#define xUART_FIFO_RX_2         UART_FIFO_RX2_8  

//
//! Receive interrupt at 4 character
//
#define xUART_FIFO_RX_4         UART_FIFO_RX4_8  

//
//! Receive interrupt at 6 character
//
#define xUART_FIFO_RX_6         UART_FIFO_RX6_8  

//
//! Receive interrupt at 7 character
//
#define xUART_FIFO_RX_7         UART_FIFO_RX7_8 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Modem_Output xUART Modem Output Signals
//!
//! \section xUART_Modem_Output_Section 1. Where to use this group
//! Values that can be passed to xUARTModemControlSet(), xUARTModemControlClear() 
//! or returned from xUARTModemControlGet().
//! 
//! \section xUART_Modem_Output_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Modem Output      |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_OUTPUT_RTS        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_OUTPUT_DTR        |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim

//! @{
//
//*****************************************************************************

#define xUART_OUTPUT_RTS        UART_OUTPUT_RTS
#define xUART_OUTPUT_DTR        UART_OUTPUT_DTR

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Modem_Intput xUART Modem Input Signals
//!
//! \section xUART_Modem_Intput_Section 1. Where to use this group
//! Values that can be returned from UARTModemStatusGet().
//! \n
//! \section xUART_Modem_Intput_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Modem Input       |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_CTS         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_RI          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_DCD         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_DSR         |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_INPUT_RI          UART_INPUT_RI
#define xUART_INPUT_DCD         UART_INPUT_DCD
#define xUART_INPUT_DSR         UART_INPUT_DSR
#define xUART_INPUT_CTS         UART_INPUT_CTS

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Flow_Control xUART Flow Control mode
//!
//! \section xUART_Flow_Control_Section 1. Where to use this group
//! Values that can be passed to UARTFlowControlSet() or returned from
//! UARTFlowControlGet().
//! \n
//! \section xUART_Flow_Control_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Flow Control      |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xUART_FLOWCONTROL_TX    |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_FLOWCONTROL_RX    |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_FLOWCONTROL_NONE  |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_FLOWCONTROL_TX    UART_FLOWCONTROL_TX
#define xUART_FLOWCONTROL_RX    UART_FLOWCONTROL_RX
#define xUART_FLOWCONTROL_NONE  UART_FLOWCONTROL_NONE

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_LIN_Config xUART LIN Configuration
//!
//! \section xUART_LIN_Config_Section 1. Where to use this group
//! Values that can be passed to xUARTLINConfig().
//! 
//! \section xUART_LIN_Config_CoX 2. CoX Port Details 
//! \verbatim
//! +-----------------------------+----------------+---------------------------+
//! |xUART LIN Configuration      |       CoX      |       Stellaris           |
//! |-----------------------------|----------------|---------------------------|
//! |xUART_LIN_MODE_MASK          |  Non-Mandatory |             Y             |
//! |-----------------------------|----------------|---------------------------|
//! |xUART_LIN_MODE_x             |  Non-Mandatory |xUART_LIN_MODE_MASTER      |
//! |                             |                |---------------------------|
//! |                             |                |xUART_LIN_MODE_SLAVE       |
//! |-----------------------------|----------------|---------------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_MASK|  Non-Mandatory |             Y             |
//! |-----------------------------|----------------|---------------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_x   |  Non-Mandatory |xUART_LIN_SYNC_BREAK_LEN_13|
//! |                             |                |---------------------------|
//! |                             |                |xUART_LIN_SYNC_BREAK_LEN_14|
//! |                             |                |---------------------------|
//! |                             |                |xUART_LIN_SYNC_BREAK_LEN_15|
//! |                             |                |---------------------------|
//! |                             |                |xUART_LIN_SYNC_BREAK_LEN_16|
//! +-----------------------------+----------------+---------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xUART_LIN_MODE_MASK     UART_LIN_MODE_MASK
#define xUART_LIN_MODE_MASTER   UART_LIN_MODE_MASTER
#define xUART_LIN_MODE_SLAVE    UART_LIN_MODE_SLAVE

#define xUART_LIN_SYNC_BREAK_LEN_MASK                                         \
                                UART_LIN_SYNC_BREAK_LEN_MASK
                                
#define xUART_LIN_SYNC_BREAK_LEN_13                                           \
                                UART_LIN_SYNC_BREAK_LEN_13

#define xUART_LIN_SYNC_BREAK_LEN_14                                           \
                                UART_LIN_SYNC_BREAK_LEN_14

#define xUART_LIN_SYNC_BREAK_LEN_15                                           \
                                UART_LIN_SYNC_BREAK_LEN_15

#define xUART_LIN_SYNC_BREAK_LEN_16                                           \
                                UART_LIN_SYNC_BREAK_LEN_16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Exported_APIs xUART API
//!
//! \section xUART_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+---------+
//! |xUART API               |       CoX      |Stellaris|
//! |------------------------|----------------|---------|
//! |xUARTConfigSet          |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTEnable             |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTDisable            |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTFIFOEnable         |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTFIFODisable        |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTFIFORxLevelSet     |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTCharsAvail         |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTSpaceAvail         |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTCharGetNonBlocking |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTCharGet            |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTCharPutNonBlocking |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTCharPut            |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTBusy               |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTIntEnable          |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTIntCallbackInit    |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTIntDisable         |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTRxErrorGet         |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTRxErrorClear       |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTModemControlSet    |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTModemControlClear  |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTModemControlGet    |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTModemStatusGet     |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTFlowControlSet     |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTFlowControlGet     |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTIrDAConfig         |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTIrDAEnable         |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTIrDADisable        |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTLINConfig          |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTLINEnable          |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! |xUARTLINDisable         |  Non-Mandatory |    Y    |
//! |------------------------|----------------|---------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Sets the configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulUARTClk is the rate of the clock supplied to the UART module.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//!
//! This function configures the UART for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter and the data
//! format in the \e ulConfig parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b xUART_CONFIG_WLEN_8,
//! \b xUART_CONFIG_WLEN_7, \b xUART_CONFIG_WLEN_6, and \b xUART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b xUART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE, and 
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit, 
//! even parity bit, odd parity bit, parity bit always one, and parity bit 
//! always zero, respectively).
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by XSysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to XSysCtlClockGet()).
//!
//! \return None.
//
//*****************************************************************************
#define xUARTConfigSet(ulBase, ulBaud, ulConfig)                              \
        UARTConfigSetExpClk(ulBase, ulBaud, ulConfig)


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
#define xUARTEnable(ulBase, ulBlock)                                          \
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
//! \return None.
//
//*****************************************************************************
#define xUARTDisable(ulBase, ulBlock)                                         \
        UARTDisable(ulBase, ulBlock)

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
#define xUARTFIFOEnable(ulBase)                                               \
        UARTFIFOEnable(ulBase)

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
#define xUARTFIFODisable(ulBase)                                              \
        UARTFIFODisable(ulBase)

extern void xUARTFIFOTxLevelSet(unsigned long ulBase, unsigned long ulTxLevel);
extern void xUARTFIFORxLevelSet(unsigned long ulBase, unsigned long ulRxLevel);

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
//! \return Returns \b xtrue if there is space available in the transmit FIFO
//! or \b xfalse if there is no space available in the transmit FIFO.
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

extern void xUARTIntCallbackInit(unsigned long ulBase, 
                    xtEventCallback pfnCallback);

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
//! - \b xUART_INT_OE - Overrun Error interrupt
//! - \b xUART_INT_BE - Break Error interrupt
//! - \b xUART_INT_PE - Parity Error interrupt
//! - \b xUART_INT_FE - Framing Error interrupt
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
//! and \b X UART_RXERROR_OVERRUN.
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
//! - \b xUART_OUTPUT_DTR - The Modem Control DTR signal
//! - \b xUART_OUTPUT_RTS - The Modem Control RTS signal
//!
//! \note The availability of hardware modem handshake signals varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************

#define xUARTModemControlSet(ulBase, ulControl)                               \
        UARTModemControlSet(ulBase, ulControl)

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
//! - \b xUART_OUTPUT_DTR - The Modem Control DTR signal
//! - \b xUART_OUTPUT_RTS - The Modem Control RTS signal
//!
//! \note The availability of hardware modem handshake signals varies with the
//! Stellaris part and UART in use.  Please consult the datasheet for the part
//! you are using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTModemControlClear(ulBase, ulControl)                             \
        UARTModemControlClear(ulBase, ulControl)

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
//! logical logical OR combination of values \b xUART_OUTPUT_RTS and
//! \b xUART_OUTPUT_DTR where the presence of each flag indicates that the
//! associated signal is asserted.
//
//*****************************************************************************
#define xUARTModemControlGet(ulBase)                                          \
        UARTModemControlGet(ulBase)

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
//! logical logical OR combination of values \b xUART_INPUT_RI, \b
//! xUART_INPUT_DCD, \b xUART_INPUT_CTS and \b xUART_INPUT_DSR where the
//! presence of each flag indicates that the associated signal is asserted.
//
//*****************************************************************************
#define xUARTModemStatusGet(ulBase)                                           \
        UARTModemStatusGet(ulBase)

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
//! \note The availability of hardware flow control varies with the Stellaris
//! part and UART in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFlowControlSet(ulBase, ulMode)                                   \
        UARTFlowControlSet(ulBase, ulMode)

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
//! logical OR combination of values \b xUART_FLOWCONTROL_TX if transmit
//! (CTS) flow control is enabled and \b xUART_FLOWCONTROL_RX if receive (RTS)
//! flow control is in use.  If hardware flow control is disabled, \b
//! xUART_FLOWCONTROL_NONE will be returned.
//
//*****************************************************************************
#define xUARTFlowControlGet(ulBase)                                           \
        UARTFlowControlGet(ulBase)

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
#define xUARTSmartCardConfig(ulBase, ulBaud)                                  \
        UARTSmartCardConfig(ulBase, ulBaud)

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
#define xUARTSmartCardEnable(ulBase)                                          \
        UARTSmartCardEnable(ulBase)   

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
#define  xUARTSmartCardDisable(ulBase)                                        \
         UARTSmartCardDisable(ulBase)         

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
//! - \b xUART_IRDA_MODE_LOW_POWER - IrDA low-power mode
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTIrDAConfig(ulBase, ulBaud, ulConfig, ulMode)                     \
        UARTIrDAConfig(ulBase, ulBaud, ulConfig, ulMode)

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
#define xUARTIrDAEnable(ulBase)                                               \
        UARTIrDAEnable(ulBase)

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
#define xUARTIrDADisable(ulBase)                                              \
        UARTIrDADisable(ulBase)

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
//! The \e ulConfig parameter is the logical OR of two values: 
//! the mode of LIN: \b xUART_LIN_MODE_MASTER, \b xUART_LIN_MODE_SLAVE.
//! the Sync Break Length when in master mode:
//! - \b xUART_LIN_SYNC_BREAK_LEN_13 (default)
//! - \b xUART_LIN_SYNC_BREAK_LEN_14
//! - \b xUART_LIN_SYNC_BREAK_LEN_15
//! - \b xUART_LIN_SYNC_BREAK_LEN_16
//!
//! \return None.
//
//*****************************************************************************

#define xUARTLINConfig(ulBase, ulBaud, ulConfig)                              \
        UARTLINConfig(ulBase, ulBaud, ulConfig)

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
#define xUARTLINEnable(ulBase)                                                \
        UARTLINEnable(ulBase)

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
#define xUARTLINDisable(ulBase)                                               \
        UARTLINDisable(ulBase)

//*****************************************************************************
//
//! \brief Causes a LIN Sync BREAK to be sent.
//!
//! \param ulBase is the base address of the UART port.
//!
//! asserts a break condition on the UART, then keep several bits, 
//! the length is specified in the UARTLINConfig with the \b ulMode param
//! when config the uart as LIN Master mode.
//! Then removes the break condition.  
//!
//! In stellaris mcus, when the uart act as an LIN Master, the synch break 
//! will be send automaticlly in a new trasmition. So this function 
//! just do nothing.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTLINSyncBreakPut(ulBase)


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
//! \addtogroup Stellaris_UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Ints UART Interrupt
//!
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus.
//! @{
//
//*****************************************************************************

//
//! LIN Mode Sync Break Interrupt Mask
//
#define UART_INT_LMSB           0x4000

//
//! Overrun Error Interrupt Mask
//
#define UART_INT_OE             0x400       

//
//! Break Error Interrupt Mask
//
#define UART_INT_BE             0x200       

//
//! Parity Error Interrupt Mask
//
#define UART_INT_PE             0x100       

//
//! Framing Error Interrupt Mask
//
#define UART_INT_FE             0x080       

//
//! Receive Timeout Interrupt Mask
//
#define UART_INT_RT             0x040       

//
//! Transmit Interrupt Mask
//
#define UART_INT_TX             0x020       

//
//! Receive Interrupt Mask
//
#define UART_INT_RX             0x010       

//
//! DSR Modem Interrupt Mask
//
#define UART_INT_DSR            0x008       

//
//! DCD Modem Interrupt Mask
//
#define UART_INT_DCD            0x004       

//
//! CTS Modem Interrupt Mask
//
#define UART_INT_CTS            0x002       

//
//! RI Modem Interrupt Mask
//
#define UART_INT_RI             0x001       

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 


//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Frame_Configs UART Frame Configuration
//!
//! Uart Data Frame Configs. Such as Word Length, Parity, Stop bit.
//! Values that can be passed to xUARTConfig as the ulConfig parameter
//! and returned by UARTConfigGetExpClk in the pulConfig parameter.
//! Additionally, the UART_CONFIG_PAR_* subset can be passed to
//! UARTParityModeSet as the ulParity parameter, and are returned by
//! UARTParityModeGet.
//! @{
//
//*****************************************************************************
//
// Mask for extracting word length
//
#define UART_CONFIG_WLEN_MASK   0x00000060  

//
//! 8 bit data
//
#define UART_CONFIG_WLEN_8      0x00000060  

//
//! 7 bit data
//
#define UART_CONFIG_WLEN_7      0x00000040  

//
//! 6 bit data
//
#define UART_CONFIG_WLEN_6      0x00000020  

//
//! 5 bit data
//
#define UART_CONFIG_WLEN_5      0x00000000  

//
//! Mask for extracting stop bits
//
#define UART_CONFIG_STOP_MASK   0x00000008  

//
//! One stop bit
//
#define UART_CONFIG_STOP_1      0x00000000  

//
//! Two stop bits
//
#define UART_CONFIG_STOP_2      0x00000008  

//
//! Mask for extracting parity
//
#define UART_CONFIG_PAR_MASK    0x00000086  

//
//! No parity
//
#define UART_CONFIG_PAR_NONE    0x00000000  

//
//! Even parity
//
#define UART_CONFIG_PAR_EVEN    0x00000006  

//
//! Odd parity
//
#define UART_CONFIG_PAR_ODD     0x00000002  

//
//! Parity bit is one
//
#define UART_CONFIG_PAR_ONE     0x00000082  

//
//! Parity bit is zero
//
#define UART_CONFIG_PAR_ZERO    0x00000086 


//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_IrDA_Mode UART IrDA Mode
//!
//! Uart IrDA mode that con be passed to UARTIrDAConfig as the
//! ulMode parameter.
//! @{
//
//*****************************************************************************
//
// IrDA Mode Mask
//
#define UART_IRDA_MODE_MASK     0x80000000

//
//! IrDA Normal Mode
//
#define UART_IRDA_MODE_NORMAL   0x00000000

//
//! IrDA Low-Power Mode
//
#define UART_IRDA_MODE_LOW_POWER                                              \
                                0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Enable_Blocks UART Enable Blocks
//!
//! Uart logic blocks that can be passed to UARTEnable or UARTDisable as 
//! the ulBlock parameter.
//! @{
//
//*****************************************************************************

//
//! Uart block
//
#define UART_BLOCK_UART         0x00000001

//
//! Uart transmit block
//
#define UART_BLOCK_TX           0x00000100

//
//! uart receive block
//
#define UART_BLOCK_RX           0x00000200

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_FIFO_TX_Tiggle_Level UART FIFO Tx Tiggle Level
//!
//! Values that can be passed to UARTFIFOTxLevelSet as the ulTxLevel parameter and
//! returned by UARTFIFOLevelGet in the pulTxLevel.
//! @{
//
//*****************************************************************************

//
//! Transmit interrupt at 1/8 Full
//
#define UART_FIFO_TX1_8         0x00000000  

//
//! Transmit interrupt at 1/4 Full
//
#define UART_FIFO_TX2_8         0x00000001  

//
//! Transmit interrupt at 1/2 Full
//
#define UART_FIFO_TX4_8         0x00000002  

//
//! Transmit interrupt at 3/4 Full
//
#define UART_FIFO_TX6_8         0x00000003  

//
//! Transmit interrupt at 7/8 Full
//
#define UART_FIFO_TX7_8         0x00000004  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_FIFO_Rx_Tiggle_Level UART FIFO Rx Tiggle Level
//!
//! Values that can be passed to UARTFIFORxLevelSet as the ulRxLevel parameter.
//! @{
//
//*****************************************************************************

//
//! Receive interrupt at 1/8 Full
//
#define UART_FIFO_RX1_8         0x00000000  

//
//! Receive interrupt at 1/4 Full
//
#define UART_FIFO_RX2_8         0x00000008  

//
//! Receive interrupt at 1/2 Full
//
#define UART_FIFO_RX4_8         0x00000010  

//
//! Receive interrupt at 3/4 Full
//
#define UART_FIFO_RX6_8         0x00000018  

//
//! Receive interrupt at 7/8 Full
//
#define UART_FIFO_RX7_8         0x00000020  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_DMA_Control UART DMA Control
//!
//! Values that can be passed to UARTDMAEnable() and UARTDMADisable().
//! @{
//
//*****************************************************************************

//
// Stop DMA receive if UART error
//
#define UART_DMA_ERR_RXSTOP     0x00000004  

//
// Enable DMA for transmit
//
#define UART_DMA_TX             0x00000002  

//
// Enable DMA for receive
//
#define UART_DMA_RX             0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Error UART Error
//!
//! Values returned from UARTRxErrorGet().
//! @{
//
//*****************************************************************************

#define UART_RXERROR_OVERRUN    0x00000008
#define UART_RXERROR_BREAK      0x00000004
#define UART_RXERROR_PARITY     0x00000002
#define UART_RXERROR_FRAMING    0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Modem_Output UART Modem Output Signals
//!
//! Values that can be passed to UARTModemControlSet(), UARTModemControlClear() 
//! or returned from UARTModemControlGet().
//! @{
//
//*****************************************************************************

#define UART_OUTPUT_RTS         0x00000800
#define UART_OUTPUT_DTR         0x00000400

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Modem_Intput UART Modem Input Signals
//!
//! Values that can be returned from UARTModemStatusGet().
//! @{
//
//*****************************************************************************

#define UART_INPUT_RI           0x00000100
#define UART_INPUT_DCD          0x00000004
#define UART_INPUT_DSR          0x00000002
#define UART_INPUT_CTS          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Flow_Control UART Flow Control
//!
//! Values that can be passed to UARTFlowControlSet() or returned from
//! UARTFlowControlGet().
//! @{
//
//*****************************************************************************

#define UART_FLOWCONTROL_TX     0x00008000
#define UART_FLOWCONTROL_RX     0x00004000
#define UART_FLOWCONTROL_NONE   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Int_Mode UART Interrupt Mode
//!
//! Values that can be passed to UARTTxIntModeSet() or returned from
//! UARTTxIntModeGet().
//! @{
//
//*****************************************************************************

#define UART_TXINT_MODE_FIFO    0x00000000
#define UART_TXINT_MODE_EOT     0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_LIN_Config UART LIN Configuration
//!
//! Values that can be passed to UARTLINConfig().
//! @{
//
//*****************************************************************************
#define UART_LIN_MODE_MASK      0x00000001
#define UART_LIN_MODE_MASTER    0x00000000
#define UART_LIN_MODE_SLAVE     0x00000001

#define UART_LIN_SYNC_BREAK_LEN_MASK                                          \
                                0x00000030
                                
#define UART_LIN_SYNC_BREAK_LEN_13                                            \
                                0x00000000

#define UART_LIN_SYNC_BREAK_LEN_14                                            \
                                0x00000010

#define UART_LIN_SYNC_BREAK_LEN_15                                            \
                                0x00000020

#define UART_LIN_SYNC_BREAK_LEN_16                                            \
                                0x00000030

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Exported_APIs UART API
//! @{
//
//*****************************************************************************

extern void UARTParityModeSet(unsigned long ulBase, unsigned long ulParity);
extern unsigned long UARTParityModeGet(unsigned long ulBase);
extern void UARTFIFOLevelSet(unsigned long ulBase, unsigned long ulTxLevel,
                             unsigned long ulRxLevel);
extern void UARTFIFOLevelGet(unsigned long ulBase, unsigned long *pulTxLevel,
                             unsigned long *pulRxLevel);
extern void UARTConfigSetExpClk(unsigned long ulBase, unsigned long ulBaud,
                                unsigned long ulConfig);
extern void UARTConfigGetExpClk(unsigned long ulBase, unsigned long *pulBaud,
                                unsigned long *pulConfig);
extern void UARTEnable(unsigned long ulBase, unsigned long ulBlock);
extern void UARTDisable(unsigned long ulBase, unsigned long ulBlock);
extern void UARTFIFOEnable(unsigned long ulBase);
extern void UARTFIFODisable(unsigned long ulBase);

extern xtBoolean UARTCharsAvail(unsigned long ulBase);
extern xtBoolean UARTSpaceAvail(unsigned long ulBase);
extern long UARTCharGetNonBlocking(unsigned long ulBase);
extern long UARTCharGet(unsigned long ulBase);
extern xtBoolean UARTCharPutNonBlocking(unsigned long ulBase,
                                       unsigned char ucData);
extern void UARTCharPut(unsigned long ulBase, unsigned char ucData);
extern void UARTBreakCtl(unsigned long ulBase, xtBoolean bBreakState);
extern xtBoolean UARTBusy(unsigned long ulBase);

extern void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long UARTIntStatus(unsigned long ulBase, xtBoolean bMasked);
extern void UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags);

extern unsigned long UARTRxErrorGet(unsigned long ulBase);
extern void UARTRxErrorClear(unsigned long ulBase);

extern void UARTDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags);
extern void UARTDMADisable(unsigned long ulBase, unsigned long ulDMAFlags);

extern void UARTSmartCardConfig(unsigned long ulBase, unsigned long ulBaud);

extern void UARTSmartCardEnable(unsigned long ulBase);
extern void UARTSmartCardDisable(unsigned long ulBase);

extern void UARTModemControlSet(unsigned long ulBase,
                                unsigned long ulControl);
extern void UARTModemControlClear(unsigned long ulBase,
                                  unsigned long ulControl);
extern unsigned long UARTModemControlGet(unsigned long ulBase);
extern unsigned long UARTModemStatusGet(unsigned long ulBase);

extern void UARTFlowControlSet(unsigned long ulBase, unsigned long ulMode);
extern unsigned long UARTFlowControlGet(unsigned long ulBase);

extern void UARTTxIntModeSet(unsigned long ulBase, unsigned long ulMode);
extern unsigned long UARTTxIntModeGet(unsigned long ulBase);

extern void UARTIrDAConfig(unsigned long ulBase, unsigned long ulBaud, 
                unsigned long ulConfig, unsigned long ulMode);
extern void UARTIrDAEnable(unsigned long ulBase);
extern void UARTIrDADisable(unsigned long ulBase);

extern void UARTLINConfig(unsigned long ulBase, unsigned long ulBaud,
                    unsigned long ulConfig);
extern void UARTLINEnable(unsigned long ulBase);
extern void UARTLINDisable(unsigned long ulBase);

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
//}
#endif

#endif //  __xUART_H__

