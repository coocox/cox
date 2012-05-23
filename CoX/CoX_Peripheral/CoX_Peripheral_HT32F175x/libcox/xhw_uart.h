//*****************************************************************************
//
//! \file xhw_UART.h
//! \brief Macros used when accessing the UART hardware.
//! \version V2.2.1.0
//! \date4/27/2012
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

#ifndef __XHW_UART_H__
#define __XHW_UART_H__

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
//! \addtogroup HT32F1755_UART_Register HT32F1755 UART Register
//! \brief Here are the detailed info of USART registers. 
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_Offsets USART Register Offset(Map)
//! \brief Here is the USART register offset, users can get the register address
//! through <b>USART_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Receive Buffer Register.
// 
#define USART_RBR               0x00000000

//
//! Transmit Holding Register.
// 
#define USART_THR               0x00000000

//
//! Interrupt Enable Register.
// 
#define USART_IER               0x00000004

//
//! Interrupt Identification Register.
// 
#define USART_IIR               0x00000008

//
//! FIFO Control Register.
// 
#define USART_FCR               0x0000000C

//
//! Line Control Register.
// 
#define USART_LCR               0x00000010

//
//! Modem Control Register.
// 
#define USART_MCR               0x00000014

//
//! Line Status Register.
// 
#define USART_LSR               0x00000018

//
//! Modem Status Register.
// 
#define USART_MSR               0x0000001C

//
//! Timing Parameter Register.
// 
#define USART_TPR               0x00000020

//
//! Mode Register.
// 
#define USART_MDR               0x00000024

//
//! IrDA Control Register.
// 
#define USART_IRCR              0x00000028

//
//! RS485 Control Register.
// 
#define USART_RS485CR           0x0000002C

//
//! Synchronous Control Register.
// 
#define USART_SYNCR             0x00000030

//
//! FIFO Status Register.
// 
#define USART_FSR               0x00000034

//
//! Debug/Test Register.
// 
#define USART_DEGTSTR           0x00000040

//
//! Divider Latch Register.
// 
#define USART_BAUD              0x00000038

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_RBR USART Receive Buffer Register(USART_RBR)
//! @{
//
//*****************************************************************************

//
//! 7-9-bit Received Data Mask
//
#define USART_RBR_RD_M           0x000001FF
//
//! 7-9-bit Received Data Shift
//
#define USART_RBR_RD_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_TBR USART Transmit Holding Register(USART_TBR)
//! @{
//
//*****************************************************************************

//
//! 7-9-bit Transmitted Data Mask
//
#define USART_TBR_TD_M           0x000001FF  

//
//! 7-9-bit Transmitted Data Shift
//
#define USART_TBR_TD_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_IER USART Interrupt Enable Register(USART_IER)
//! @{
//
//*****************************************************************************

//
//! Receiver FIFO Threshold Level Interrupt Enable (Irpt_RFTLI) or receiver FIFO.
//
#define USART_IER_RFTLI_RTOIE    0x00000001

//
//! Transmitter FIFO Threshold Level Interrupt (Irpt_TFTLI) Enable.
//
#define USART_IER_THRE_IEN       0x00000002

//
//! Receiver Line Status Interrupt Enable (Irpt_RLSI)
//
#define USART_IER_RLS_IEN        0x00000004

//
//! Modem Status Interrupt Enable
//
#define USART_IER_MOD_IEN        0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_IIR USART FIFO Status Register(USART_IIR)
//! @{
//
//*****************************************************************************

//
//! MODEM Status Interrupt(Irpt_MODSI).
//
#define USART_IIR_MS_IF          0x00000000

//
//! Transritter FIFO Threshold Level Interrupt(Transmitter FIFO Empty).
//
#define USART_IIR_TX_EF          0x00000002

//
//! Parity Receiver FIFO Time-out Interrupt(Irpt_RTOI).
//
#define USART_IIR_FTO            0x0000000C

//
//! Receiver FIFO Threshold Level Interrupt(Irpt_RFTLI).
//
#define USART_IIR_RFTL           0x00000004

//
//! Receiver Line Status Interrupt(Irpt_RLSI).
//
#define USART_IIR_RLS            0x00000006

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_FCR  USART FIFO Control Register(USART_FCR)
//! @{
//
//*****************************************************************************

//
//! FIFO Mode Enable
//
#define USART_FCR_FIFO_MOD_EN   0x00000001

//
//! Rx Software Reset
//
#define USART_FCR_RX_RST        0x00000002

//
//! Tx Software Reset
//
#define USART_FCR_TX_RST        0x00000004

//
//! TX FIFO Threshold Level Setting Mask
//
#define USART_FCR_TFTL_M        0x00000030

//
//! TX FIFO Threshold Level Setting Shift
//
#define USART_FCR_TFTL_S        4

//
//! 0 Byte
//
#define USART_FCR_TFTL_0        0x00000000

//
//! 2 Bytes
//
#define USART_FCR_TFTL_2        0x00000010

//
//! 4 Bytes
//
#define USART_FCR_TFTL_4        0x00000020

//
//! 8 Bytes
//
#define USART_FCR_TFTL_8        0x00000030

//
//! RX FIFO Threshold Level Setting Mask
//
#define USART_FCR_RFTL_M        0x000000C0

//
//! RX FIFO Threshold Level Setting Shift
//
#define USART_FCR_RFTL_S        6

//
//! 1 Byte
//
#define USART_FCR_RFTL_1        0x00000000

//
//! 4 Bytes
//
#define USART_FCR_RFTL_4        0x00000040

//
//! 8 Bytes
//
#define USART_FCR_RFTL_8        0x00000080

//
//! 14 Bytes
//
#define USART_FCR_RFTL_14       0x000000C0

//
//! USART TX enable
//
#define USART_FCR_TX_EN         0x00000100

//
//! USART RX enable
//
#define USART_FCR_RX_EN         0x00000200
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_LCR USART Line Control Register(USART_LCR)
//! @{
//
//*****************************************************************************

//
//! Word Length Select Mask
//
#define USART_LCR_WLS_M         0x00000003

//
//! Word Length Select Shift
//
#define USART_LCR_WLS_S         0

//
//! 7 bits Length
//
#define USART_LCR_WLS_7         0x00000000

//
//! 8 bits Length
//
#define USART_LCR_WLS_8         0x00000001

//
//! 9 bits Length
//
#define USART_LCR_WLS_9         0x00000002

//
//! Number of ¡°STOP bit¡±
//
#define USART_LCR_NSB           0x00000004

//
//! Parity Bit Enable
//
#define USART_LCR_PBE           0x00000008

//
//! Even Parity Enable
//
#define USART_LCR_EPE           0x00000010

//
//! Stick Parity Enable
//
#define USART_LCR_SPE           0x00000020

//
//! Break Control Bit
//
#define USART_LCR_BCB           0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_MCR USART Modem Control Register(USART_MCR)
//! @{
//
//*****************************************************************************

//
//! DTR (Data-Terminal-Ready) Signal(low level)
//
#define USART_MCR_DTR_L         0x00000001

//
//! RTS (Request-To-Send) Signal(low level)
//
#define USART_MCR_RTS_L         0x00000002

//
//! DTR (Data-Terminal-Ready) Signal(high level)
//
#define USART_MCR_DTR_H         0x00000000

//
//! RTS (Request-To-Send) Signal(high level)
//
#define USART_MCR_RTS_H         0x00000000

//
//! Hardware flow control enable
//
#define USART_MCR_HFC_EN        0x00000004
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_LSR USART Line Status Register(USART_LSR)
//! @{
//
//*****************************************************************************

//
//! RX FIFO Data Ready
//
#define USART_LSR_RXFIFO_READY  0x00000001

//
//! Overrun Error Indicator
//
#define USART_LSR_OVERRUN_FLAG  0x00000002

//
//! Parity Error Indicator
//
#define USART_LSR_PARITY_ERROR_FLAG                                           \
                                0x00000004

//
//! Framing Error Indicator
//
#define USART_LSR_FRAMING_ERROR_FLAG                                          \
                                0x00000008

//
//! Break Interrupt Indicator
//
#define USART_LSR_BREAK_INT_FLAG                                              \
                                0x00000010

//
//! Transmitter FIFO Empty
//
#define USART_LSR_TX_FIFO_EMPTY                                               \
                                0x00000020

//
//! Transmitter Empty
//
#define USART_LSR_TX_EMPTY      0x00000040

//
//! RX FIFO Error
//
#define USART_LSR_RX_FIFO_ERROR                                              \
                                0x00000080

//
//! RS485 Address detection Flag
//
#define USART_LSR_RSADDEF_FLAG  0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_MSR USART Modem Status Register(USART_MSR)
//! @{
//
//*****************************************************************************

//
//! Detect CTS State Change Flag
//
#define USART_MSR_DCTSF         0x00000001

//
//! Detect DSR State Change Flag
//
#define USART_MSR_DDTSF         0x00000002

//
//! Detect DRI State Change Flag
//
#define USART_MSR_DRISF         0x00000004

//
//! Detect DDCT State Change Flag
//
#define USART_MSR_DDCTSF        0x00000008

//
//! UR_CTS Clear-To-Send Status
//
#define USART_MSR_CTSS          0x00000010

//
//! UR_DSR Data-Set-Ready Status
//
#define USART_MSR_DSRS          0x00000020

//
//! UR_RI Ring-Indicator Status
//
#define USART_MSR_RIS           0x00000040

//
//! UR_DCD - Data-Carrier-Detect Status
//
#define USART_MSR_DCDS          0x00000080

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_TPR USART Timing Parameter Register(USART_TPR)
//! @{
//
//*****************************************************************************

//
//! Receiver FIFO Time-Out Interrupt Compare value Mask.
//
#define USART_TPR_RTOIC_M       0x0000007F

//
//! Receiver FIFO Time-Out Interrupt Compare value Shift.
//
#define USART_TPR_RTOIC_S       0

//
//! Receiver FIFO Time Out Interrupt Enanle.
//
#define USART_TPR_RTOI_EN       0x00000080

//
//! Transmitter Time Guard Mask.
//
#define USART_TPR_TG_M          0x0000FF00

//
//! Transmitter Time Guard Shift.
//
#define USART_TPR_TG_S          8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_FUN_SEL USART Function Select Register(USART_FUN_SEL)
//! @{
//
//*****************************************************************************

//
//! USART Function Select Mask
//
#define USART_FUN_SEL_M         0x00000003

//
//! USART Function Select Shift
//  
#define USART_FUN_SEL_S         0

//
//! USART Function
//  
#define USART_FUN_SEL_USART_EN  0x00000000

//
//! IrDA Function Enable.
//
#define USART_FUN_SEL_IRDA_EN   0x00000001

//
//! RS-485 Function Enable
//
#define USART_FUN_SEL_RS485_EN  0x00000002

//
//! Synchronous Function Enable.
//
#define USART_FUN_SEL_SYN_EN    0x00000003

//
//! Transfer Mode Selection:MSB first.
//
#define USART_MDR_MSB           0x00000004

//
//! Transfer Mode Selection:LSB first.
//
#define USART_MDR_LSB           0x00000000

//
//! TX DMA enable.
//
#define USART_MDR_TXDMA_EN      0x00000010

//
//! RX DMA enable.
//
#define USART_MDR_RXDMA_EN      0x00000020
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_IRCR USART IrDA Control Register(USART_IRCR)
//! @{
//
//*****************************************************************************

//
//! IrDA Enanle control.
//
#define USART_IRCR_IRDA_EN      0x00000001

//
//! IrDA Normal Mode:Normal mode.
//
#define USART_IRCR_IRDA_NORMAL  0x00000000

//
//! IrDA Low Power Mode: IrDA low power mode.
//
#define USART_IRCR_IRDA_LOWPOWER                                             \
                                0x00000002

//
//! Transceiver Select: Enable IrDA receiver.
//
#define USART_IRCR_TXSEL_RX     0x00000000

//
//! Transceiver Select: Enable IrDA transmitter.
//
#define USART_IRCR_TXSEL_TX     0x00000004

//
//! IrDA Loop Back Mode Enable.
//
#define USART_IRCR_LB_EN        0x00000008

//
//! TX inverse.
//
#define USART_IRCR_TXINV        0x00000010

//
//! RX inverse.
//
#define USART_IRCR_RXINV        0x00000020

//
//! IrDA Prescaler value Mask.
//
#define USART_IRCR_IRDAPSC_M    0x0000FF00

//
//! IrDA Prescaler value Shift.
//
#define USART_IRCR_IRDAPSC_S    8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_RS485CR USART 485 Control Register(USART_RS485CR)
//! @{
//
//*****************************************************************************

//
//! UR_RTS/TXE pin Polarity is 1.
//
#define USART_RS485CR_TXEP      0x00000000

//
//! UR_RTS/TXE pin Polarity is 0.
//
#define USART_RS485CR_TXEN      0x00000001

//
//! RS485 Normal Multi-drop Operation mode enable.
//
#define USART_RS485CR_NMM_EN    0x00000002

//
//! RS485 Auto Address detection Operation mode enable.
//
#define USART_RS485CR_AAD_EN    0x00000004

//
//! Address Match value Mask.
//
#define USART_RS485CR_ADDMATCH_M                                              \
                                0x0000FF00

//
//! Address Match value Shift.
//
#define USART_RS485CR_ADDMATCH_S                                              \
                                8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_SYNCR Synchronous Control Register (SYNCR)
//! @{
//
//*****************************************************************************

//
//! UR_CTS/SCK pin idle state is low.
//
#define USART_SYNCR_CPO_L    0x00000000

//
//! UR_CTS/SCK pin idle state is high.
//
#define USART_SYNCR_CPO_H    0x00000008

//
//! Data is captured on the first clock edge.
//
#define USART_SYNCR_CPS_F    0x00000000

//
// Data is captured on the second clock edge.
//
#define USART_SYNCR_CPS_S    0x00000004

//
//! UR_CTS/SCK pin enabled.
//
#define USART_SYNCR_CLK_EN   0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_FSR FIFO Status Register (FSR)
//! @{
//
//*****************************************************************************

//
//! TX FIFO Contains Status Mask.
//
#define USART_FSR_TXFS_M        0x0000001F

//
//! TX FIFO Contains Status Shift.
//
#define USART_FSR_TXFS_S        0

//
//! RX FIFO Contains Status Mask.
//
#define USART_FSR_RXFS_M        0x00001F00

//
//! RX FIFO Contains Status Shift.
//
#define USART_FSR_RXFS_S        8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_BAUD USART Baud Rate Divisor Register(USART_BAUD)
//! @{
//
//*****************************************************************************

//
//! Baud Rate Divider Mask.
//
#define USART_BAUD_BRD_M         0x0000FFFF

//
//! Baud Rate Divider Shift.
//
#define USART_BAUD_BRD_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F1755_USART_Register_USART_DEGTSTR USART Debug Mode Register(USART_DEGTSTR)
//! @{
//
//*****************************************************************************

//
//! Loopback Test Mode Select Mask
//
#define USART_DEGTSTR_LBM_M     0x00000003

//
//! Loopback Test Mode Select Shift
//
#define USART_DEGTSTR_LBM_S     0

//
//! normal Operation
//
#define USART_DEGTSTR_LBM_NORMAL                                              \
                                0x00000000

//
//! Automatic Echo Mode
//
#define USART_DEGTSTR_LBM_AUTOECHO                                            \
                                0x00000002

//
//! Loopback Mode
//
#define USART_DEGTSTR_LBM_LOOPBACK                                            \
                                0x00000003

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
