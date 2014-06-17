//*****************************************************************************
//
//! \file xuart.h
//! \brief Prototypes for the UART Driver.
//! \version V2.2
//! \date 5/17/2012
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

#include "uart.h"
#include "CoX_base.h"

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
//! \addtogroup CoX_Peripheral_Interface
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
//! Values that can be passed to xUARTIntEnable, xUARTIntDisable as the 
//! ulIntFlags parameter
//! \n
//! \section xUART_Ints_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Interrupts        |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_ERROR         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RT            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_TX            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RX            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_DSR           |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_DCD           |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_CTS           |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RI            |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_LMSB          |  Non-Mandatory |            N           |
//!
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! All Error Interrupt Mask
//
#define xUART_INT_ERROR         UART_INT_ERROR        

//
//! Receive Timeout Interrupt Mask
//
#define xUART_INT_RT            UART_INT_RT       

//
//! Transmit Interrupt Mask
//
#define xUART_INT_TX            UART_INT_TX       

//
//! Receive Interrupt Mask
//
#define xUART_INT_RX            UART_INT_RX   

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
//! \brief Values that show xUART Event Flags
//! \n
//! \section xUART_Event_Flag_Section 1. Where to use this group
//! Uart Event Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parmeter. User Callback function can use this to detect what 
//! event happened.
//! \n
//! \section xUART_Event_Flag_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Events            |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_TX          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_RX          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_OE          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_FE          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_RT          |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_PE          |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_DSR         |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_DCD         |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_CTS         |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_RI          |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_EVENT_LMSB        |  Non-Mandatory |            N           |
//!
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transmit Event Mask
//
#define xUART_EVENT_TX          UART_EVENT_TX       

//
//! Receive Event Mask
//
#define xUART_EVENT_RX          UART_EVENT_RX   

//
//! Overrun Error Event Mask
//
#define xUART_EVENT_OE          UART_EVENT_OE       

//
//! Parity Error Event Mask
//
#define xUART_EVENT_PE          UART_EVENT_PE       

//
//! Framing Error Event Mask
//
#define xUART_EVENT_FE          UART_EVENT_FE       

//
//! Receive Timeout Event Mask
//
#define xUART_EVENT_RT          UART_EVENT_RT       

//
//! DSR Modem Event Mask
//
#define xUART_EVENT_DSR         UART_EVENT_DSR       

//
//! DCD Modem Event Mask
//
#define xUART_EVENT_DCD         UART_EVENT_DCD       

//
//! CTS Modem Event Mask
//
#define xUART_EVENT_CTS         UART_EVENT_CTS       

//
//! RI Modem Event Mask
//
#define xUART_EVENT_RI          UART_EVENT_RI 

//
//! LIN Mode Sync Break Event Mask
//
#define xUART_EVENT_LMSB        UART_EVENT_LMSB

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
//! \section xUART_RXERROR_Flag_Section 1. Where to use this group
//! Values returned from xUARTRxErrorGet().
//! \n
//! \section xUART_Event_Flag_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Error             |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_OVERRUN   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_BREAK     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_PARITY    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_RXERROR_FRAMING   |    Mandatory   |            Y           |
//!
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
//! \brief Values that show xUART Frame Configuration
//! \n
//! \section xUART_Frame_Configs_Section 1. Where to use this group
//! Uart Data Frame Configs. Such as Word Length, Parity, Stop bit.
//! Values that can be passed to xUARTConfig as the ulConfig parameter.
//!
//! \n
//! \section xUART_Frame_Configs_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Frame Config      |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_WLEN_n     |    Mandatory   |   xUART_CONFIG_WLEN_8  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_7  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_6  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_5  |
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
//! |xUART_CONFIG_STOP_1     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_2     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_0_5   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_STOP_1_5   |  Non-Mandatory |            N           |
//!
//! \endverbatim
//! @{
//
//*****************************************************************************

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
//! One stop bit
//
#define xUART_CONFIG_STOP_1     UART_CONFIG_STOP_1  

//
//! Two stop bits
//
#define xUART_CONFIG_STOP_2     UART_CONFIG_STOP_2

//
//! 0.5 stop bit
//
#define xUART_CONFIG_STOP_0_5   UART_CONFIG_STOP_0_5  

//
//! 1.5 stop bit
//
#define xUART_CONFIG_STOP_1_5   UART_CONFIG_STOP_1_5  

//
//! None parity
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
//! \brief Values that show xUART IrDA Mode
//! \n
//! \section xUART_IrDA_Mode_Section 1. Where to use this group
//! Uart IrDA mode that con be passed to xUARTIrDAConfig as the
//! ulMode parameter. 
//! \n
//! \section xUART_IrDA_Mode_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART IrDA Mode          |       CoX      |         LPC17xx        |
//! |-------------------------|----------------|------------------------|
//! |xUART_IRDA_MODE_NORMAL   |  Non-Mandatory |            Y           |
//! |-------------------------|----------------|------------------------|
//! |xUART_IRDA_MODE_LOW_POWER|  Non-Mandatory |            N           |
//!
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! IrDA Normal Mode
//
#define xUART_IRDA_MODE_NORMAL  UART_IRDA_MODE_NORMAL

//
//! IrDA Low-Power Mode
//
#define xUART_IRDA_MODE_LOW_POWER                                             \
                                UART_IRDA_MODE_LOW_POWER

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
//! Uart logic blocks  that can be passed to xUARTEnable() or xUARTDisable() as 
//! the ulBlock parameter.
//! \n
//! \section xUART_Enable_Blocks_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Enable Block      |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_BLOCK_UART        |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_BLOCK_RX          |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_BLOCK_TX          |    Mandatory   |            Y           |
//!
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
//! \addtogroup xUART_FIFO_Rx_Tiggle_Level xUART FIFO Rx Tiggle Level
//! \brief Values that show xUART FIFO Rx Tiggle Level
//! \n
//! \section xUART_FIFO_Rx_Tiggle_Level_Section 1. Where to use this group
//! Values that can be passed to xUARTFIFORxLevelSet as the ulRxLevel parameter.
//! \n
//! \section xUART_FIFO_Rx_Tiggle_Level_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |FIFO Rx Tiggle Level    |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_FIFO_RX_n         |    Mandatory   |     xUART_FIFO_RX_1    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_RX_4    |
//! |                        |                |------------------------|
//! |                        |                |     xUART_FIFO_RX_8    |
//! |                        |                |------------------------|
//! |                        |                |    xUART_FIFO_RX_14    |
//! |                        |                |------------------------|
//! |                        |                |    xUART_FIFO_RX_30    |
//! |                        |                |------------------------|
//! |                        |                |    xUART_FIFO_RX_46    |
//! |                        |                |------------------------|
//! |                        |                |    xUART_FIFO_RX_62    |
//!
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! (1 character)
//
#define xUART_FIFO_RX_1         UART_FIFO_RX_1  

//
//! (4 character)
//
#define xUART_FIFO_RX_4         UART_FIFO_RX_4  

//
//! (8 character)
//
#define xUART_FIFO_RX_8         UART_FIFO_RX_8  

//
//! (14 character)
//
#define xUART_FIFO_RX_14        UART_FIFO_RX_14  

//
//! (30 character)
//
#define xUART_FIFO_RX_30        UART_FIFO_RX_30 

//
//! (46 character)
//
#define xUART_FIFO_RX_46        UART_FIFO_RX_46 

//
//! (62 character)
//
#define xUART_FIFO_RX_62        UART_FIFO_RX_62 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xUART_Modem_Output xUART Modem Output
//! \brief Values that show xUART Modem Output
//! \n
//! \section xUART_Modem_Output_Section 1. Where to use this group
//! Values that can be passed to xUARTModemControlSet(), xUARTModemControlClear() 
//! or returned from xUARTModemControlGet().
//! \n
//! \section xUART_Modem_Output_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Modem Output      |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_OUTPUT_RTS        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_OUTPUT_DTR        |  Non-Mandatory |            Y           |
//!
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
//! \addtogroup xUART_Modem_Intput xUART Modem Input
//! \brief Values that show xUART Modem Input
//! \n
//! \section xUART_Modem_Intput_Section 1. Where to use this group
//! Values that can be returned from xURTModemStatusGet().
//! \n
//! \section xUART_Modem_Intput_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Modem Input       |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_CTS         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_RI          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_DCD         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_DSR         |  Non-Mandatory |            Y           |
//!
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_INPUT_CTS         UART_INPUT_CTS
#define xUART_INPUT_RI          UART_INPUT_RI
#define xUART_INPUT_DCD         UART_INPUT_DCD
#define xUART_INPUT_DSR         UART_INPUT_DSR

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xUART_Flow_Control xUART Flow Control
//! \brief Values that show xUART Flow Control
//! \n
//! \section xUART_Flow_Control_Section 1. Where to use this group
//! Values that can be passed to xUARTFlowControlSet() or returned from
//! xUARTFlowControlGet().
//! \n
//! \section xUART_Flow_Control_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART Flow Control      |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |xUART_FLOWCONTROL_TX    |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_FLOWCONTROL_RX    |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_FLOWCONTROL_NONE  |  Non-Mandatory |            N           |
//!
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
//! \brief Values that show xUART LIN Configuration
//! \n
//! \section xUART_LIN_Config_Section 1. Where to use this group
//! Values that can be passed to xUARTLINConfig().
//! \n
//! \section xUART_LIN_Config_CoX 2. CoX Port Details 
//! \verbatim
//!
//! |xUART LIN Configuration      |       CoX      |      LPC17xx      |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_MODE_MASTER        |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_MODE_SLAVE         |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_13  |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_14  |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_15  |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_16  |  Non-Mandatory |         N         |
//!
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_LIN_MODE_MASTER   UART_LIN_MODE_MASTER

#define xUART_LIN_MODE_SLAVE    UART_LIN_MODE_SLAVE	
                    
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
//! \brief UART API Reference.
//! \section xUART_Exported_APIs_Port CoX Port Details
//! \verbatim
//!
//! |xUART API               |       CoX      | LPC17xx|
//! |------------------------|----------------|--------|
//! |xUARTConfigSet          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTEnable             |    Mandatory   |    N   |
//! |------------------------|----------------|--------|
//! |xUARTDisable            |    Mandatory   |    N   |
//! |------------------------|----------------|--------|
//! |xUARTFIFOEnable         |  Non-Mandatory |    N   |
//! |------------------------|----------------|--------|
//! |xUARTFIFODisable        |  Non-Mandatory |    N   |
//! |------------------------|----------------|--------|
//! |xUARTFIFORxLevelSet     |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTCharsAvail         |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTSpaceAvail         |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTCharGetNonBlocking |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTCharGet            |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTCharPutNonBlocking |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTCharPut            |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTBusy               |  Non-Mandatory |    N   |
//! |------------------------|----------------|--------|
//! |xUARTIntEnable          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTIntCallbackInit    |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTIntDisable         |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTIntStatus          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTRxErrorGet         |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTRxErrorClear       |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTModemControlSet    |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTModemControlClear  |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTModemControlGet    |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTModemStatusGet     |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTFlowControlSet     |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTFlowControlGet     |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTIrDAConfig         |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTIrDAEnable         |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTIrDADisable        |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTLINConfig          |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTLINEnable          |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xUARTLINDisable         |  Non-Mandatory |    Y   |
//!
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

extern void xUARTConfigSet(unsigned long ulBase, unsigned long ulBaud, unsigned long ulConfig);

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
extern void xUARTEnable(unsigned long ulBase, unsigned long ulBlock);                                

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
extern void xUARTDisable(unsigned long ulBase, unsigned long ulBlock); 

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
extern void xUARTFIFOEnable(unsigned long ulBase); 

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
extern void xUARTFIFODisable(unsigned long ulBase); 

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
extern xtBoolean xUARTCharsAvail(unsigned long ulBase);

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
extern xtBoolean xUARTSpaceAvail(unsigned long ulBase);


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
extern long xUARTCharGetNonBlocking(unsigned long ulBase);

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
extern long xUARTCharGet(unsigned long ulBase);

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
extern xtBoolean xUARTCharPutNonBlocking(unsigned long ulBase, unsigned char ucData);

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
extern void xUARTCharPut(unsigned long ulBase, unsigned char ucData);

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
extern xtBoolean xUARTBusy(unsigned long ulBase);

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
extern void xUARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags);

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
extern void xUARTIntCallbackInit(unsigned long ulBase, 
                                 xtEventCallback xtUARTCallback);
        
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
extern void xUARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags);


extern unsigned long xUARTIntStatus(unsigned long ulBase, xtBoolean bMasked);

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
extern unsigned long xUARTRxErrorGet(unsigned long ulBase);

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
extern void xUARTRxErrorClear(unsigned long ulBase);

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
extern void xUARTModemControlSet(unsigned long ulBase, 
                                 unsigned long ulControl);

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
extern void xUARTModemControlClear(unsigned long ulBase, 
                                   unsigned long ulControl);

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
extern unsigned long xUARTModemControlGet(unsigned long ulBase, unsigned long ulControl);

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
extern unsigned long xUARTModemStatusGet(unsigned long ulBase);

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
extern void xUARTFlowControlSet(unsigned long ulBase, unsigned long ulMode);

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
extern unsigned long xUARTFlowControlGet(unsigned long ulBase);
        
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
//! - \b xUART_IRDA_MODE_NORMAL     - IrDA normal mode
//! - \b xUART_IRDA_MODE_LOW_POWER  - IrDA Low-Power Mode
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
extern void xUARTIrDAConfig(unsigned long ulBase, unsigned long ulBaud, 
                            unsigned long ulConfig, unsigned long ulMode);                     

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
extern void xUARTIrDAEnable(unsigned long ulBase);

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
extern void xUARTIrDADisable(unsigned long ulBase);

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
extern void xUARTLINConfig(unsigned long ulBase, unsigned long ulBaud, 
                           unsigned long ulConfig);
        
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
extern void xUARTLINEnable(unsigned long ulBase);

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
extern void xUARTLINDisable(unsigned long ulBase);
    

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
