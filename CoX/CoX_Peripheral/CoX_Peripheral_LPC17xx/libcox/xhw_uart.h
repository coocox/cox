//*****************************************************************************
//
//! \file      xhw_uart.h
//! \brief     Macros used when accessing the UART hardware.
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

#ifndef __XHW_UART_H__
#define __XHW_UART_H__

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"

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
//! \addtogroup LPC17xx_UART_Register UART Register Hardware Layer.
//! \brief      Here are detail register information.
//!             it contains:
//!                 - Register offset.
//!                 - detailed bit-field of the registers.
//!                 - Enum and mask of the registers.
//!
//! \note       Users can read or write the registers via xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_Uart_Register_Offsets Uart Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>UARTn_BASE + offset</b>, (n=0/1/...)
//! @{
//
//*****************************************************************************

//! RBR (DLAB =0) Receiver Buffer Register. Contains the next received
//! character to be read.
#define RBR                     ((unsigned long)0x00000000)

//! THR (DLAB =0) Transmit Holding Register. The next character to be
//! transmitted is written here.
#define THR                     ((unsigned long)0x00000000)

//! DLL (DLAB =1) Divisor Latch LSB. Least significant byte of the baud rate
//! divisor value. The full divisor is used to generate a baud rate from the
//! fractional rate divider.
#define DLL                     ((unsigned long)0x00000000)

//! DLM (DLAB =1) Divisor Latch MSB. Most significant byte of the baud rate
//! divisor value. The full divisor is used to generate a baud rate from the
//! fractional rate divider.
#define DLM                     ((unsigned long)0x00000004)

//! IER (DLAB =0) Interrupt Enable Register. Contains individual interrupt
//! enable bits for the 7 potential UART interrupts.
#define IER                     ((unsigned long)0x00000004)

//! IIR Interrupt ID Register. Identifies which interrupt(s) are pending.
#define IIR                     ((unsigned long)0x00000008)

//! FCR FIFO Control Register. Controls UART FIFO usage and modes.
#define FCR                     ((unsigned long)0x00000008)

//! LCR Line Control Register. Contains controls for frame formatting and break
//! generation.
#define LCR                     ((unsigned long)0x0000000C)

//! Modem Control Register. Contains controls for flow control
//! handshaking and loopback mode.
#define MCR                     ((unsigned long)0x00000010)

//! LSR Line Status Register. Contains flags for transmit and receive status,
//! including line errors.
#define LSR                     ((unsigned long)0x00000014)

//! Modem Status Register. Contains handshake signal status flags
#define MSR                     ((unsigned long)0x00000018)

//! SCR Scratch Pad Register. 8-bit temporary storage for software.
#define SCR                     ((unsigned long)0x0000001C)

//! ACR Auto-baud Control Register. Contains controls for the auto-baud feature.
#define ACR                     ((unsigned long)0x00000020)

//! ICR IrDA Control Register. Enables and configures the IrDA mode.
#define ICR                     ((unsigned long)0x00000024)

//! FDR Fractional Divider Register. Generates a clock input for the baud rate
//! divider.
#define FDR                     ((unsigned long)0x00000028)

//! TER Transmit Enable Register. Turns off UART transmitter for use with
//! software flow control.
#define TER                     ((unsigned long)0x00000030)


//! RS-485/EIA-485 Control. Contains controls to configure various
//! aspects of RS-485/EIA-485 modes.
#define RS485CTRL               ((unsigned long)0x0000004C)

//! RS-485/EIA-485 address match. Contains the address match value
//! for RS-485/EIA-485 mode.
#define ADRMATCH                ((unsigned long)0x00000050)

//! RS-485/EIA-485 direction control delay.
#define RS485DLY                ((unsigned long)0x00000054)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_DLL UART Register DLL
//! \brief      UART DLL Register description.
//!
//! @{
//
//*****************************************************************************

//! The UARTn Divisor Latch LSB Register, along with the UnDLM
//! register, determines the baud rate of the UARTn.
#define DLL_SB_M                BIT_MASK(32, 7, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_DLM UART Register DLM
//! \brief      UART DLM Register description.
//!
//! @{
//
//*****************************************************************************

//! The UARTn Divisor Latch MSB Register, along with the U0DLL register,
//! determines the baud rate of the UARTn.
#define DLM_SB_M                BIT_MASK(32, 7, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_IER UART Register IER
//! \brief      UART IER Register description.
//!
//! @{
//
//*****************************************************************************

//! Enables the Receive Data Available interrupt for UARTn. It also controls
//! the Character Receive Time-out interrupt
#define IER_RBR_INT_EN          BIT_32_0

//! Enables the THRE interrupt for UARTn. The status of this can be read
//! from UnLSR[5].
#define IER_THRE_INT_EN         BIT_32_1

//! Enables the UARTn RX line status interrupts. The status of this interrupt
//! can be read from UnLSR[4:1].
#define IER_RX_LINE_STAT_INT_EN BIT_32_2

//! Modem Status Interrupt Enable
#define IER_MODEM_STAT_INT_EN   BIT_32_3

//! CTS Interrupt Enable
#define IER_CTS_INT_EN          BIT_32_7

//! Enables the end of auto-baud interrupt.
#define IER_ABEO_INT_EN         BIT_32_8

//! Enables the auto-baud time-out interrupt.
#define IER_ABTO_INT_EN         BIT_32_9

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_IIR UART Register IIR
//! \brief      UART IIR Register description.
//!
//! @{
//
//*****************************************************************************

//! Interrupt status. Note that UnIIR[0] is active low. The pending interrupt can
//! be determined by evaluating UnIIR[3:1].
//! 0 At least one interrupt is pending.
//! 1 No interrupt is pending.
#define IIR_INT_STAT            BIT_32_0

//! Interrupt identification. UnIER[3:1] identifies an interrupt corresponding to the
//! UARTn Rx or TX FIFO. All other combinations of UnIER[3:1] not listed below
//! are reserved (000,100,101,111).
//! 011 1  - Receive Line Status (RLS).
//! 010 2a - Receive Data Available (RDA).
//! 110 2b - Character Time-out Indicator (CTI).
//! 001 3  - THRE Interrupt
#define IIR_INT_ID_M            BIT_MASK(32, 3, 1)

//! Receive Line Status
#define IIR_INT_ID_RLS          (BIT_32_2 | BIT_32_1)

//! Receive Data Available
#define IIR_INT_ID_RDA          BIT_32_2

//! Character Time-Out Indicator
#define IIR_INT_ID_CTI          BIT_32_3 | BIT_32_2

//! THRE Interrupt
#define IIR_INT_ID_THRE         BIT_32_1

//! Modem Interrupt
#define IIR_INT_ID_MODEM        BIT_32_ALL_0

//! Copies of UnFCR
#define IIR_FIFO_EN_M           BIT_MASK(32, 7, 6)

//! End of auto-baud interrupt.
#define IIR_ABEO_INT            BIT_32_8

//! Auto-baud time-out interrupt.
#define IIR_ABTO_INT            BIT_32_9

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_FCR UART Register FCR
//! \brief      UART FCR Register description.
//!
//! @{
//
//*****************************************************************************

//! FIFO Enable
#define FCR_FIFO_EN             BIT_32_0

//! Reset RX FIFO
#define FCR_RX_FIFO_RESET       BIT_32_1

//! Reset TX FIFO
#define FCR_TX_FIFO_RESET       BIT_32_2

//! DMA Mode Select
#define FCR_DMA_MODE            BIT_32_3

//! RX Trigger Level.
#define FCR_RX_TRI_LEVEL_M      BIT_MASK(32, 7, 6)

//! Trigger level 0 (1 character)
#define FCR_RX_TRI_LEVEL_0      BIT_32_ALL_0

//! Trigger level 1 (4 character)
#define FCR_RX_TRI_LEVEL_1      BIT_32_6

//! Trigger level 2 (8 character)
#define FCR_RX_TRI_LEVEL_2      BIT_32_7

//! Trigger level 3 (14 character)
#define FCR_RX_TRI_LEVEL_3      (BIT_32_7 | BIT_32_6)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_LCR UART Register LCR
//! \brief      UART LCR Register description.
//!
//! @{
//
//*****************************************************************************

//! Character Length
#define LCR_WORD_LEN_M          BIT_MASK(32, 1, 0)

//! 5-bit length
#define LCR_WORD_LEN_5_BIT      BIT_32_ALL_0

//! 6-bit length
#define LCR_WORD_LEN_6_BIT      BIT_32_0

//! 7-bit length
#define LCR_WORD_LEN_7_BIT      BIT_32_1

//! 8-bit length
#define LCR_WORD_LEN_8_BIT      (BIT_32_1 | BIT_32_0)

//! Stop Bit
#define LCR_STOP_BIT            BIT_32_2

//! Parity Enable
#define LCR_PARITY_EN           BIT_32_3

//! Parity Select
#define LCR_PARITY_SEL_M        BIT_MASK(32, 5, 4)

//! Odd parity
#define LCR_PARITY_ODD          BIT_32_ALL_0

//! Even parity
#define LCR_PARITY_EVEN         BIT_32_4

//! Stick to 1 parity
#define LCR_PARITY_1            BIT_32_5

//! Stick to 0 parity
#define LCR_PARITY_0            (BIT_32_5 | BIT_32_4)

//! Break Control
#define LCR_BREAK_CTL           BIT_32_6

//! Divisor Latch Acess Bit(DLAB)
#define LCR_DLAB                BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_MCR UART Register MCR
//! \brief      UART MCR Register description.
//!
//! @{
//
//*****************************************************************************

//! Source for modem output pin, DTR. This bit reads as 0 when modem loopback mode
//! is active.
#define MCR_DTR_CTL            BIT_32_0

//! Source for modem output pin RTS. This bit reads as 0 when modem loopback mode is
//! active.
#define MCR_RTS_CTL            BIT_32_1

//! Loopback Mode Select
#define MCR_LOOPBACK_SEL       BIT_32_4

//! Auto-RTS Flow control
#define MCR_RTS_EN             BIT_32_6

//! Auto-CTS Flow control
#define MCR_CTS_EN             BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_LSR UART Register LSR
//! \brief      UART LSR Register description.
//!
//! @{
//
//*****************************************************************************

//! Receiver Data Ready
#define LSR_RDR                 BIT_32_0

//! Overrun Error
#define LSR_OE                  BIT_32_1

//! Parity Error
#define LSR_PE                  BIT_32_2

//! Framing Error
#define LSR_FE                  BIT_32_3

//! Break Interrupt
#define LSR_BI                  BIT_32_4

//! Transmitter Holding Register Empty
#define LSR_THRE                BIT_32_5

//! Transmitter Empty
#define LSR_TEMT                BIT_32_6

//! Error in RX FIFO
#define LSR_RXFE                BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_MSR UART Register MSR
//! \brief      UART MSR Register description.
//!
//! @{
//
//*****************************************************************************

//! Delta CTS
#define MSR_DELTA_CTS           BIT_32_0

//! Delta DSR
#define MSR_DELTA_DSR           BIT_32_1

//! Trailing Edge RI
//! Set upon low to high transition of input RI. Cleared on an U1MSR read
#define MSR_TRAIL_EDGE_RI       BIT_32_2

//! Delta DCD
#define MSR_DELTA_DCD           BIT_32_3

//! Clear to Send State.
#define MSR_CTS                 BIT_32_4

//! Data Set Ready State.
#define MSR_DSR                 BIT_32_5

//! Ring Indicator State.
#define MSR_RI                  BIT_32_6

//! Data Carrier Detect State.
#define MSR_DCD                 BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_SCR UART Register SCR
//! \brief      UART SCR Register description.
//!
//! @{
//
//*****************************************************************************

//! UART Scratch Pad Mask
#define SCR_PAD_M               BIT_MASK(32, 7, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_ACR UART Register ACR
//! \brief      UART ACR Register description.
//!
//! @{
//
//*****************************************************************************

//! Start Auto-Baud
#define ACR_START               BIT_32_0

//! Auto-Baud Mode Select bit.
#define ACR_MODE                BIT_32_1

//! Auto ReStart
#define ACR_AUTO_RESTART        BIT_32_2

//! End of auto-baud interrupt clear bit.
#define ACR_ABEO_INT_CLR        BIT_32_8

//! Auto-baud time-out interrupt clear bit.
#define ACR_ABTO_INT_CLR        BIT_32_9

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_ICR UART Register ICR
//! \brief      UART ICR Register description.
//!
//! @{
//
//*****************************************************************************

//! IrDA Enable
#define ICR_IRDA_EN             BIT_32_0

//! IrDA Invert
#define ICR_IRDA_INV            BIT_32_1

//! Enable IrDA Fixed Pulse width mode.
#define ICR_FIX_PULSE_EN        BIT_32_2

//! Pulse Divider.
#define ICR_PULSE_DIV_M         BIT_MASK(32, 5, 3)
#define ICR_PULSE_DIV_S         3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_FDR UART Register FDR
//! \brief      UART FDR Register description.
//!
//! @{
//
//*****************************************************************************

//! Baud-rate generation pre-scaler divisor value.
#define FDR_DIVADDVAL_M         BIT_MASK(32, 3, 0)
#define FDR_DIVADDVAL_S         0

//! Baud-rate pre-scaler multiplier value.
#define FDR_MULVAL_M            BIT_MASK(32, 7, 4)
#define FDR_MULVAL_S            4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_TER UART Register TER
//! \brief      UART TER Register description.
//!
//! @{
//
//*****************************************************************************

//! Transmitter Enable
#define TER_TX_EN               BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_RS485CTRL UART Register RS485CTRL
//! \brief      UART RS485CTRL Register description.
//!
//! @{
//
//*****************************************************************************

//! Normal Mulitdrop Mode.
#define RS485CTRL_NMMEN         BIT_32_0

//! Receive Disable.
#define RS485CTRL_RXDIS         BIT_32_1

//! Auto Address Detect
#define RS485CTRL_AADEN         BIT_32_2

//! Direct pin select
#define RS485CTRL_SEL           BIT_32_3

//! Direction control
#define RS485CTRL_DCTRL         BIT_32_4

//! Direction Control Invert
#define RS485CTRL_OINV          BIT_32_5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_RS485ADRMATCH UART Register RS485ADRMATCH
//! \brief      UART RS485ADRMATCH Register description.
//!
//! @{
//
//*****************************************************************************

//! Address match value.
#define RS485ADRMATCH_ADRMATCH_M   BIT_MASK(32, 7, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_UART_Register_RS485DLY UART Register RS485DLY
//! \brief      UART RS485DLY Register description.
//!
//! @{
//
//*****************************************************************************

//! Direction control delay value.
#define RS485DLY_DLY_M          BIT_MASK(32, 7, 0)

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

#endif // __XHW_UART_H__

