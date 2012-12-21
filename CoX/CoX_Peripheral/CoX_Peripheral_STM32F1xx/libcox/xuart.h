//*****************************************************************************
//
//! \file xuart.h
//! \brief Prototypes for the UART Driver.
//! \version V2.2.1.0
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
//! |xUART Interrupts        |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_ERROR         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INT_RT            |    Mandatory   |            Y           |
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
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! All Error Interrupt Mask
//
#define xUART_INT_ERROR         UART_INT_RLS        

//
//! Receive Timeout Interrupt Mask
//
#define xUART_INT_RT            UART_INT_RTO       

//
//! Transmit Interrupt Mask
//
#define xUART_INT_TX            UART_INT_THRE       

//
//! Receive Interrupt Mask
//
#define xUART_INT_RX            UART_INT_RDA   

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
//! +------------------------+----------------+------------------------+
//! |xUART Events            |       CoX      |         STM32F1xx      |
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
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transmit Event Mask
//
#define xUART_EVENT_TX          UART_INT_THRE       

//
//! Receive Event Mask
//
#define xUART_EVENT_RX          UART_INT_RDA   

//
//! Overrun Error Event Mask
//
#define xUART_EVENT_OE          UART_INT_RLS       

//
//! Parity Error Event Mask
//
#define xUART_EVENT_PE          UART_INT_RLS       

//
//! Framing Error Event Mask
//
#define xUART_EVENT_FE          UART_INT_RLS       

//
//! Receive Timeout Event Mask
//
#define xUART_EVENT_RT          UART_INT_RTO       

//
//! DSR Modem Event Mask
//
#define xUART_EVENT_DSR         0       

//
//! DCD Modem Event Mask
//
#define xUART_EVENT_DCD         0       

//
//! CTS Modem Event Mask
//
#define xUART_EVENT_CTS         0       

//
//! RI Modem Event Mask
//
#define xUART_EVENT_RI          0 

//
//! LIN Mode Sync Break Event Mask
//
#define xUART_EVENT_LMSB        0

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
//! +------------------------+----------------+------------------------+
//! |xUART Error             |       CoX      |        STM32F1xx       |
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
//! |xUART Frame Config      |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_WLEN_MASK  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_WLEN_n     |    Mandatory   |   xUART_CONFIG_WLEN_9  |
//! |                        |                |------------------------|
//! |                        |                |   xUART_CONFIG_WLEN_8  |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_MASK   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_NONE   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_EVEN   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_ODD    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_ONE    |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_CONFIG_PAR_ZERO   |  Non-Mandatory |            N           |
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
//! 9 bit data
//
#define xUART_CONFIG_WLEN_9     UART_CONFIG_WLEN_9  

//
//! 8 bit data
//
#define xUART_CONFIG_WLEN_8     UART_CONFIG_WLEN_8

//
//! Mask for extracting stop bits
//
#define xUART_CONFIG_STOP_MASK  UART_CONFIG_STOP_MASK

//
//! One stop bit
//
#define xUART_CONFIG_STOP_1     UART_CONFIG_STOP_ONE  

//
//! Two stop bits
//
#define xUART_CONFIG_STOP_2     UART_CONFIG_STOP_TWO

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
//! Uart IrDA mode that con be passed to UARTIrDAConfig as the
//! ulMode parameter. 
//! \n
//! \section xUART_IrDA_Mode_CoX 2. CoX Port Details 
//! \verbatim
//! +-------------------------+----------------+------------------------+
//! |xUART IrDA Mode          |       CoX      |         STM32F1xx      |
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
//! IrDA Normal Mode
//
#define xUART_IRDA_MODE_NORMAL  0x00000000

//
//! IrDA Low-Power Mode
//
#define xUART_IRDA_MODE_LOW_POWER                                             \
                                0x00000004

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
//! |xUART Enable Block      |       CoX      |        STM32F1xx       |
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
#define xUART_BLOCK_UART        0x00002000

//
//! Uart transmit logic block
//
#define xUART_BLOCK_TX          0x00000008

//
//! uart receive logic block
//
#define xUART_BLOCK_RX          0x00000004

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
//! |FIFO Rx Tiggle Level    |       CoX      |        STM32F1xx       |
//! |------------------------|----------------|------------------------|
//! |xUART_FIFO_RX_n         |  Non-Mandatory |            N           |
//! |                        |                |------------------------|
//! |                        |                |            N           |
//! |                        |                |------------------------|
//! |                        |                |            N           |
//! |                        |                |------------------------|
//! |                        |                |            N           |
//! |                        |                |------------------------|
//! |                        |                |            N           |
//! |                        |                |------------------------|
//! |                        |                |            N           |
//! |                        |                |------------------------|
//! |                        |                |            N           |
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
//! \addtogroup xUART_Modem_Output xUART Modem Output
//! \brief Values that show xUART Modem Output
//! \n
//! \section xUART_Modem_Output_Section 1. Where to use this group
//! Values that can be passed to UARTModemControlSet(), UARTModemControlClear() 
//! or returned from UARTModemControlGet().
//! \n
//! \section xUART_Modem_Output_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Modem Output      |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xUART_OUTPUT_RTS        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_OUTPUT_DTR        |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_OUTPUT_RTS        UART_OUTPUT_RTS_SET

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
//! Values that can be returned from UARTModemStatusGet().
//! \n
//! \section xUART_Modem_Intput_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Modem Input       |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_CTS         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_RI          |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_DCD         |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xUART_INPUT_DSR         |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_INPUT_CTS         UART_INPUT_CTS_L

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
//! Values that can be passed to UARTFlowControlSet() or returned from
//! UARTFlowControlGet().
//! \n
//! \section xUART_Flow_Control_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xUART Flow Control      |       CoX      |         STM32F1xx      |
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
//! \brief Values that show xUART LIN Configuration
//! \n
//! \section xUART_LIN_Config_Section 1. Where to use this group
//! Values that can be passed to xUARTLINConfig().
//! \n
//! \section xUART_LIN_Config_CoX 2. CoX Port Details 
//! \verbatim
//! +-----------------------------+----------------+-------------------+
//! |xUART LIN Configuration      |       CoX      |      STM32F1xx    |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_MODE_MASK          |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_MODE_MASTER        |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_MODE_SLAVE         |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_MASK|  Non-Mandatory |         Y         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_10  |  Non-Mandatory |         Y         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_11  |  Non-Mandatory |         Y         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_15  |  Non-Mandatory |         N         |
//! |-----------------------------|----------------|-------------------|
//! |xUART_LIN_SYNC_BREAK_LEN_16  |  Non-Mandatory |         N         |
//! +-----------------------------+----------------+-------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xUART_LIN_SYNC_BREAK_LEN_MASK                                         \
                                UART_CONFIG_BKFL_MASK
                                
#define xUART_LIN_SYNC_BREAK_LEN_10                                           \
                                UART_CONFIG_BKFL_10

#define xUART_LIN_SYNC_BREAK_LEN_11                                           \
                                UART_CONFIG_BKFL_11

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
//! +------------------------+----------------+-----------+
//! |xUART API               |       CoX      | STM32F1xx |
//! |------------------------|----------------|-----------|
//! |xUARTConfigSet          |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTEnable             |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTDisable            |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTFIFOEnable         |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xUARTFIFODisable        |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xUARTFIFORxLevelSet     |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTCharsAvail         |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTSpaceAvail         |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTCharGetNonBlocking |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTCharGet            |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTCharPutNonBlocking |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTCharPut            |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTBusy               |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xUARTIntEnable          |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTIntCallbackInit    |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTIntDisable         |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTRxErrorGet         |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTRxErrorClear       |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTModemControlSet    |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTModemControlClear  |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTModemControlGet    |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTModemStatusGet     |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTFlowControlSet     |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xUARTFlowControlGet     |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xUARTIrDAConfig         |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTIrDAEnable         |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTIrDADisable        |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTLINConfig          |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTLINEnable          |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
//! |xUARTLINDisable         |  Non-Mandatory |     Y     |
//! |------------------------|----------------|-----------|
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
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_9,
//! \b xUART_CONFIG_WLEN_8.
//! \b xUART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE, and 
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit, 
//! even parity bit, odd parity bit, parity bit always one, and parity bit 
//! always zero, respectively).
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
//! \return None.
//
//*****************************************************************************
#define xUARTDisable(ulBase, ulBlock) 

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
#define xUARTFIFOEnable(ulBase)                                               0

//*****************************************************************************
//
//! \brief Disables the transmit and receive FIFOs.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This functions disables the transmit and receive FIFOs in the UART.
//!
//! \note Do nothing in STM32F1xx
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFIFODisable(ulBase)                                              0

//*****************************************************************************
//
//! \brief Sets the Rx FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulRxLevel is the receive FIFO interrupt level
//!
//! \note Do nothing in STM32F1xx
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFIFORxLevelSet(ulBase, ulRxLevel)                                \                                      \
        UARTFIFOTriggerLevelSet(ulBase, ulRxLevel)

//*****************************************************************************
//
//! \brief Determines if there are any characters in the receive FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive FIFO.
//!
//! \note Do nothing in STM32F1xx
//!
//! \return Returns \b true if there is data in the receive FIFO or \b false
//! if there is no data in the receive FIFO.
//
//*****************************************************************************
#define xUARTCharsAvail(ulBase)                                               \
        UARTFIFORxIsEmpty(ulBase)

//*****************************************************************************
//
//! \brief Determines if there is any space in the transmit FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit FIFO.
//!
//! \note Do nothing in STM32F1xx
//!
//! \return Returns \b true if there is space available in the transmit FIFO
//! or \b false if there is no space available in the transmit FIFO.
//
//*****************************************************************************
#define xUARTSpaceAvail(ulBase)                                               \
        UARTFIFOTxIsEmpty(ulBase)


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
#define xUARTBusy(ulBase) 

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
//! \note It is not available on UART4 and UART5.
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
//! - \b xUART_OUTPUT_RTS - The Modem Control RTS signal
//!
//! \note It is not available on UART4 and UART5
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
//! \note It is not available on UART4 and UART5
//!
//! \return Returns the states of the handshake output signals.  This will be a
//! logical logical OR combination of values \b xUART_OUTPUT_RTS 
//! where the presence of each flag indicates that the
//! associated signal is asserted.
//
//*****************************************************************************
#define xUARTModemControlGet(ulBase, ulControl)                               \
        UARTModemControlGet(ulBase, ulControl)

//*****************************************************************************
//
//! \brief Gets the states of the RI, DCD, DSR and CTS modem status signals.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current states of each of the four UART modem status signals,
//! RI, DCD, DSR and CTS.
//!
//! \note It is not available on UART4 and UART5
//!
//! \return Returns the states of the handshake output signals.  This will be a
//! logical logical OR combination of values \b xUART_INPUT_CTS,  where the
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
//! \note The availability of hardware flow control varies with the STM32F1xx
//! part and UART in use.  Please consult the datasheet for the part you are
//! using to determine whether this support is available.
//!
//! \return None.
//
//*****************************************************************************
#define xUARTFlowControlSet(ulBase, ulMode)                                   0

//*****************************************************************************
//
//! \brief Returns the UART hardware flow control mode currently in use.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current hardware flow control mode.
//!
//! \note The availability of hardware flow control varies with the STM32F1xx
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
#define xUARTFlowControlGet(ulBase)                                           0
        
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
//! The \e ulMode parameter can be values:
//! - \b xUART_IRDA_MODE_NORMAL - IrDA normal mode
//! - \b xUART_IRDA_MODE_LOW_POWER - low power mpde
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
#define xUARTIrDAEnable(ulBase)                                               \
        UARTEnableIrDA(ulBase)

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
#define xUARTIrDADisable(ulBase)                                              \
        UARTDisableIrDA(ulBase)

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
        UARTEnableLIN(ulBase)

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
        UARTDisableLIN(ulBase)
    

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
//! \addtogroup STM32F1xx_UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_INT_Type STM32F1xx UART Interrupt Type
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus.
//! @{
//
//*****************************************************************************

//
//! PE interrupt
//
#define UART_INT_PE             0x00010100

//
//! TXE interrupt
//
#define UART_INT_TXE            0x00800080

//
//! Transmission complete interrupt
//
#define UART_INT_TC             0x00400040

//
//! RXNE interrupt
//
#define UART_INT_RXNE           0x00200020

//
//! IDLE interrupt
//
#define UART_INT_IDLE           0x00100010

//
//! LIN break detection interrupt
//
#define UART_INT_LIN            0x01001020

//
//! Error interrupt
//
#define UART_INT_ERR            0x000E2001

//
//! CTS interrupt
//
#define UART_INT_CTS            0x02002400


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Line_Config STM32F1xx UART Line Configuration
//! Values that can be passed to UARTConfigSetExpClk as the ulConfig parameter
//! and returned by UARTConfigGetExpClk in the pulConfig parameter.
//! Additionally, the UART_CONFIG_PAR_* subset can be passed to
//! UARTParityModeSet as the ulParity parameter, and are returned by
//! UARTParityModeGet.
//! @{
//
//*****************************************************************************

//
//! Mask for extracting word length
//
#define UART_CONFIG_WLEN_MASK   0x00001000

//
//! 8 bit data
//
#define UART_CONFIG_WLEN_8      0x00000000

//
//! 9 bit data
//
#define UART_CONFIG_WLEN_9      0x00001000

//
//! Mask for extracting stop bits
//
#define UART_CONFIG_STOP_MASK   0x00003000

//
//! One stop bit
//
#define UART_CONFIG_STOP_ONE    0x00000000

//
//! Two stop bits
//
#define UART_CONFIG_STOP_TWO    0x00002000

//
//! 0.5 stop bits
//
#define UART_CONFIG_STOP_0P5    0x00001000

//
//! 1.5 stop bits
//
#define UART_CONFIG_STOP_1P5    0x00003000

//
//! Mask for extracting parity
//
#define UART_CONFIG_PAR_MASK    0x00000600

//
//! No parity
//
#define UART_CONFIG_PAR_NONE    0x00000000

//
//! Even parity
//
#define UART_CONFIG_PAR_EVEN    0x00000400

//
//! Odd parity
//
#define UART_CONFIG_PAR_ODD     0x00000600

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Enable_Blocks STM32F1xx UART Enable Blocks
//! Uart logic blocks  that can be passed to UARTEnable or UARTDisable as 
//! the ulBlock parameter.
//! @{
//
//*****************************************************************************

//
//! Uart block
//
#define UART_BLOCK_UART         0x00002000

//
//! Uart transmit block
//
#define UART_BLOCK_TX           0x00000008

//
//! uart receive block
//
#define UART_BLOCK_RX           0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Clock_Config STM32F1xx UART clock Configuration
//! Values that can be passed to UARTClockConfig as the ulClkConfig parameter.
//! @{
//
//*****************************************************************************

//
//! Clock pin enable
//
#define UART_CLK_EN             0x00000800

//
//! Clock pin disabled
//
#define UART_CLK_DIS            0x00000000

//
//! Steady low value on CK pin outside transmission window.
//
#define UART_CPOL_LOW           0x00000800

//
//! Steady high value on CK pin outside transmission window.
//
#define UART_CPOL_HIGH          0x00000400

//
//! The first clock transition is the first data capture edge.
//
#define UART_CPHA_1EDHGE        0x00000000

//
//! The second clock transition is the first data capture edge.
//
#define UART_CPHA_2EDHGE        0x00000200

//
//! The clock pulse of the last data bit is output to the CK pin
//
#define UART_LASTBIT_EN         0x00000100

//
//! The clock pulse of the last data bit is not output to the CK pin
//
#define UART_LASTBIT_DIS        0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_DMA_Flag STM32F1xx UART DMA Flag
//! Values that can be passed to UARTDMAEnable() and UARTDMADisable().
//! @{
//
//*****************************************************************************

//
//! Enable DMA for transmit
//
#define UART_DMA_TX             0x00000080

//
//! Enable DMA for receive
//
#define UART_DMA_RX             0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_SMARTCARD_Flag STM32F1xx UART Smartcard Flag
//! Values that can be passed to UARTSmartCardEnable().
//! @{
//
//*****************************************************************************

//
//! Enable Smartcard for transmit
//
#define UART_SC_TX              0x00000080

//
//! Enable Smartcard for receive
//
#define UART_SC_RX              0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_SYN_CONFIG STM32F1xx UART synchronous mode configuration
//! Values that can be passed to UARTSynModeSet().
//! @{
//
//*****************************************************************************

//
//!  Clock polarity
//
#define UART_SYN_CPOL          0x00000400

//
//!  Clock phase
//
#define UART_SYN_CPHA          0x00000200

//
//!  Last bit clock pulse
//
#define UART_SYN_LBCL          0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Wake_Up STM32F1xx UART Wake Up
//! Values that can be passed to UARTWakeUpConfig().
//! @{
//
//*****************************************************************************

//
//! WakeUp by an idle line detection
//
#define UART_WAKEUP_IDLE        0x00000000

//
//! WakeUp by an address mark
//
#define UART_WAKEUP_ADDRESS     0x00000800

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Modem_Mode STM32F1xx UART Modem Mode
//! Values that can be passed to UARTModemSet().
//! @{
//
//*****************************************************************************

//
//! RTS
//
#define UART_MODEM_RTS          0x00000100

//
//! CTS
//
#define UART_MODEM_CTS          0x00000200

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Flow_Control STM32F1xx UART Flow Control
//! Values that can be passed to UARTFlowControlSet() or returned from
//! UARTFlowControlGet().
//! @{
//
//*****************************************************************************

//
//! RTS enable
//
#define UART_FLOWCONTROL_TX     0x00000100

//
//! CTS enable
//
#define UART_FLOWCONTROL_RX     0x00000200

//
//! RTS CTS disable
//
#define UART_FLOWCONTROL_NONE   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Error STM32F1xx UART Error
//! Values returned from UARTRxErrorGet().
//! @{
//
//*****************************************************************************

//
//! Overrun error
//
#define UART_RXERROR_OVERRUN    0x00000008

//
//! Noise error flag
//
#define UART_RXERROR_NE         0x00000004

//
//! Parity error
//
#define UART_RXERROR_PARITY     0x00000001

//
//! Framing error
//
#define UART_RXERROR_FRAMING    0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_LIN_Config STM32F1xx UART LIN Configuration
//! Values that can be passed to UARTLINConfig as the ulConfig parameter
//! @{
//
//*****************************************************************************

//
//! Mask for LIN Break Field Length
//
#define UART_CONFIG_BKFL_MASK   0x00000020

//
//! LIN Break Field Length 10
//
#define UART_CONFIG_BKFL_10     0x00000000

//
//! LIN Break Field Length 11
//
#define UART_CONFIG_BKFL_11     0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_IrDA_Mode STM32F1xx UART IrDA mode Configuration
//! Values that can be passed to UARTIrDAConfig as the ulMode parameter
//! @{
//
//*****************************************************************************

//
// IrDA Mode Mask
//
#define UART_IRDA_MODE_MASK     0x80000000

//
//! IrDA low-power mode
//
#define UART_IRDA_MODE_LPM      0x80000000

//
//! Normal mode
//
#define UART_IRDA_MODE_NORMAL   0x00000000

//
// IrDA Mode Prescaler value Mask
//
#define UART_IRDA_PRES_MASK     0x000000FF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Exported_APIs STM32F1xx UART API
//! \brief STM32F1xx UART API Reference.
//! @{
//
//*****************************************************************************
extern void UARTParityModeSet(unsigned long ulBase, unsigned long ulParity);
extern unsigned long UARTParityModeGet(unsigned long ulBase);
extern void UARTConfigSet(unsigned long ulBase, unsigned long ulBaud, 
                          unsigned long ulConfig);
extern void UARTEnable(unsigned long ulBase, unsigned long ulBlock);
extern void UARTDisable(unsigned long ulBase, unsigned long ulBlock);
extern void UARTEnableIrDA(unsigned long ulBase);
extern void UARTDisableIrDA(unsigned long ulBase);
extern void UARTIrDAConfig(unsigned long ulBase, unsigned long ulBaud, 
            unsigned long ulConfig, unsigned long ulMode, unsigned long ulPrescaler);
extern void UARTEnableLIN(unsigned long ulBase);
extern void UARTDisableLIN(unsigned long ulBase);
extern void UARTLINConfig(unsigned long ulBase, unsigned long ulBaud, 
                          unsigned long ulConfig);
extern long UARTCharGetNonBlocking(unsigned long ulBase);
extern long UARTCharGet(unsigned long ulBase);
extern xtBoolean UARTCharPutNonBlocking(unsigned long ulBase, 
                                        unsigned char ucData);
extern void UARTCharPut(unsigned long ulBase, unsigned char ucData);
extern void UARTBufferWrite(unsigned long ulBase, unsigned char *ucBuffer,
                            unsigned long ulLength);
extern void UARTBreakCtl(unsigned long ulBase);
extern void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTIntCallbackInit(unsigned long ulBase, 
                                xtEventCallback xtUARTCallback);
extern unsigned long UARTIntStatus(unsigned long ulBase);
extern void UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags);
extern void UARTDMADisable(unsigned long ulBase, unsigned long ulDMAFlags);
extern void UARTAddressSet(unsigned long ulBase, unsigned long ulAddress);
extern void UARTWakeUpConfig(unsigned long ulBase, unsigned long ulWakeup);
extern void UARTGuardTimeSet(unsigned long ulBase, unsigned long ulGuardTime);
extern void UARTHalfDuplexEnable(unsigned long ulBase);
extern void UARTHalfDuplexDisable(unsigned long ulBase);
extern void UARTSmartCardEnable(unsigned long ulBase, unsigned long ulSCMode);
extern void UARTSmartCardDisable(unsigned long ulBase);
extern void UARTSynModeSet(unsigned long ulBase, unsigned long ulConfig);
extern void UARTSYNDisable(unsigned long ulBase);
extern void UARTModemControlSet(unsigned long ulBase, unsigned long ulControl);
extern void UARTModemControlClear(unsigned long ulBase, unsigned long ulControl);
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

