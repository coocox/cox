//*****************************************************************************
//
//! \file xhw_uart.h
//! \brief Macros used when accessing the UART hardware.
//! \version V2.1.1.1
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
//! \addtogroup NUC1xx_UART_Register NUC1xx UART Register
//! \brief Here are the detailed info of UART registers. 
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
//! \addtogroup NUC1xx_UART_Register_Offsets UART Register Offset(Map)
//! \brief Here is the UART register offset, users can get the register address
//! through <b>UART_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Receive Buffer Register.
// 
#define UART_RBR                0x00000000  

//
//! Transmit Holding Register.
// 
#define UART_THR                0x00000000  

//
//! Interrupt Enable Register.
// 
#define UART_IER                0x00000004  

//
//! FIFO Control Register.
// 
#define UART_FCR                0x00000008  

//
//! Line Control Register.
// 
#define UART_LCR                0x0000000C  

//
//! Modem Control Register.
// 
#define UART_MCR                0x00000010  

//
//! Modem Control Register.
// 
#define UART_MSR                0x00000014  

//
//! FIFO Status Register.
// 
#define UART_FSR                0x00000018  

//
//! Interrupt Status Register.
// 
#define UART_ISR                0x0000001C  

//
//! Time Out Register.
// 
#define UART_TOR                0x00000020  

//
//! Baud Rate Divisor Register.
// 
#define UART_BAUD               0x00000024  

//
//! IrDA Control Register.
// 
#define UART_IRCR               0x00000028  

//
//! LIN Break Failed Count Register.
// 
#define UART_LIN_BCNT           0x0000002C  

//
//! Function Select Register.
// 
#define UART_FUN_SEL            0x00000030  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_RBR UART Receive Buffer Register(UART_RBR)
//! \brief Defines for the bit fields in the UART_RBR register.
//! @{
//
//*****************************************************************************

#define UART_RBR_RD_M           0x000000FF  // 8-bit Received Data
#define UART_RBR_RD_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_THR UART Transmit Holding Register(UART_THR)
//! \brief Defines for the bit fields in the UART_THR register.
//! @{
//
//*****************************************************************************

//
//! 8-bit Transmitted Data Mask
//
#define UART_THR_TD_M           0x000000FF  

//
//! 8-bit Transmitted Data Shift
//
#define UART_THR_TD_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_IER UART Interrupt Enable Register(UART_IER)
//! \brief Defines for the bit fields in the UART_IER register.
//! @{
//
//*****************************************************************************

//
//! Receive Data Available Interrupt Enable.
//
#define UART_IER_RDA_IEN        0x00000001  

//
//! Transmit Holding Register Empty Interrupt Enable.
//
#define UART_IER_THRE_IEN       0x00000002  

//
//! Receive Line Status Interrupt Enable
//
#define UART_IER_RLS_IEN        0x00000004  

//
//! Modem Status Interrupt Enable
//
#define UART_IER_MOD_IEN        0x00000008  

//
//! Rx Time out Interrupt Enable
//
#define UART_IER_RTO_IEN        0x00000010  

//
//! Buffer Error Interrupt Enable
//
#define UART_IER_BUF_ERR_IEN    0x00000020  

//
//! Wake up CPU function enable
//
#define UART_IER_WAKE_IEN       0x00000040  

//
//! LIN RX Break Field Detected Interrupt Enable
//
#define UART_IER_LIN_RX_BRK_IEN 0x00000100  

//
//! Time-Out Counter Enable
//
#define UART_IER_TIME_OUT_EN    0x00000800  

//
//! RTS Auto Flow Control Enable
//
#define UART_IER_AUTO_RTS_EN    0x00001000  

//
//! CTS Auto Flow Control Enable
//
#define UART_IER_AUTO_CTS_EN    0x00002000  

//
//! Tx DMA Enable
//
#define UART_IER_DMA_TX_EN      0x00004000  

//
//! Rx DMA Enable
//
#define UART_IER_DMA_RX_EN      0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_FCR  UART FIFO Control Register(UART_FCR)
//! \brief Defines for the bit fields in the UART_FCR register.
//! @{
//
//*****************************************************************************

//
//! Rx Software Reset
//
#define UART_FCR_RX_RST         0x00000002  

//
//! Tx Software Reset
//
#define UART_FCR_TX_RST         0x00000004  

//
//! Rx FIFO Interrupt(INT_RDA)Trigger Level
//
#define UART_FCR_RFITL_M        0x000000F0  

//
//! Rx FIFO Interrupt(INT_RDA)Trigger Level
//
#define UART_FCR_RFITL_S        4

//
//! 1 Bytes
//
#define UART_FCR_RFITL_1        0x00000000  

//
//! 4 Bytes
//
#define UART_FCR_RFITL_4        0x00000010 

//
//! 8 Bytes
//
#define UART_FCR_RFITL_8        0x00000020  

//
//! 14 Bytes
//
#define UART_FCR_RFITL_14       0x00000030  

//
//! 30/14 (High Speed/Normal Speed)
//
#define UART_FCR_RFITL_30_14    0x00000040  

//
//! 46/14 (High Speed/Normal Speed)
//
#define UART_FCR_RFITL_46_14    0x00000050  

//
//! 62/14 (High Speed/Normal Speed)
//
#define UART_FCR_RFITL_62_14    0x00000060  

//
//! RTS Trigger Level for Auto-flow Control Use
//
#define UART_FCR_RTSTL_M        0x000F0000  

//
//! RTS Trigger Level for Auto-flow Control Use
//
#define UART_FCR_RTSTL_S        16

//
//! 1 Bytes
//
#define UART_FCR_RTSTL_1        0x00000000  

//
//! 4 Bytes
//
#define UART_FCR_RTSTL_4        0x00010000  

//
//! 8 Bytes
//
#define UART_FCR_RTSTL_8        0x00020000  

//
//! 14 Bytes
//
#define UART_FCR_RTSTL_14       0x00030000  

//
//! 30/14 (High Speed/Normal Speed)
//
#define UART_FCR_RTSTL_30_14    0x00040000  

//
//! 46/14 (High Speed/Normal Speed)
//
#define UART_FCR_RTSTL_46_14    0x00050000  

//
//! 62/14 (High Speed/Normal Speed)
//
#define UART_FCR_RTSTL_62_14    0x00060000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_LCR UART Line Control Register(UART_LCR)
//! \brief Defines for the bit fields in the UART_LCR register.
//! @{
//
//*****************************************************************************

//
//! Word Length Select
//
#define UART_LCR_WLS_M          0x00000003  

//
//! Word Length Select
//
#define UART_LCR_WLS_S          0

//
//! 5 bits
//
#define UART_LCR_WLS_5          0x00000000  

//
//! 6 bits
//
#define UART_LCR_WLS_6          0x00000001  

//
//! 7 bits
//
#define UART_LCR_WLS_7          0x00000002  

//
//! 8 bits
//
#define UART_LCR_WLS_8          0x00000003  

//
//! Number of ¡°STOP bit¡±
//
#define UART_LCR_NSB            0x00000004  

//
//! Parity Bit Enable
//
#define UART_LCR_PBE            0x00000008  

//
//! Even Parity Enable
//
#define UART_LCR_EPE            0x00000010  

//
//! Stick Parity Enable
//
#define UART_LCR_SPE            0x00000020  

//
//! Break Control Bit
//
#define UART_LCR_BCB            0x00000040  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_MCR UART Modem Control Register(UART_MCR)
//! \brief Defines for the bit fields in the UART_MCR register.
//! @{
//
//*****************************************************************************

//
//! RTS (Request-To-Send) Signal
//
#define UART_MCR_RTS            0x00000002  

//
//! RTS Trigger Level
//
#define UART_MCR_LEV_RTS        0x00000200  

//
//! This bit is the pin status of RTS.
//
#define UART_MCR_RTS_ST         0x00002000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_MSR UART Modem Status Register(UART_MSR)
//! \brief Defines for the bit fields in the UART_MSR register.
//! @{
//
//*****************************************************************************

//
//! Detect CTS State Change Flag
//
#define UART_MSR_DCTSF          0x00000001  

//
//! CTS Trigger Level
//
#define UART_MSR_LEV_CTS        0x00000100  

//
//! This bit is the pin status of CTS.
//
#define UART_MSR_CTS_ST         0x00000010  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_FSR UART FIFO Status Register(UART_FSR)
//! \brief Defines for the bit fields in the UART_FSR register.
//! @{
//
//*****************************************************************************

//
//! Rx overflow Error IF.
//
#define UART_FSR_RXOIF          0x00000001  

//
//! Parity Error Flag.
//
#define UART_FSR_PEF            0x00000010  

//
//! Framing Error Flag.
//
#define UART_FSR_FEF            0x00000020  

//
//! Break Interrupt Flag.
//
#define UART_FSR_BIF            0x00000040  

//
//! Rx FIFO pointer.
//
#define UART_FSR_RXP_M          0x00003F00  

//
//! Rx FIFO pointer.
//
#define UART_FSR_RXP_S          8

//
//! Receiver FIFO Empty.
//
#define UART_FSR_RX_EF          0x00004000  

//
//! Receiver FIFO Full.
//
#define UART_FSR_RX_FF          0x00008000  

//
//! TX FIFO Pointer.
//
#define UART_FSR_TXP_M          0x003F0000  

//
//! This bit is the pin status of CTS.
//
#define UART_FSR_TXP_S          16

//
//! Transmitter FIFO Empty.
//
#define UART_FSR_TX_EF          0x00400000  

//
//! Transmitter FIFO Full.
//
#define UART_FSR_TX_FF          0x00800000  

//
//! Tx Overflow Error Interrupt Flag.
//
#define UART_FSR_TXO_IF         0x01000000  

//
//! Transmitter Empty Flag.
//
#define UART_FSR_TE_F           0x01000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_ISR UART Interrupt Status Register(UART_ISR)
//! \brief Defines for the bit fields in the UART_ISR register.
//! @{
//
//*****************************************************************************

//
//! Receive Data Available Interrupt Flag.
//
#define UART_ISR_RDA_IF         0x00000001  

//
//! Transmit Holding Register Empty Interrupt Flag.
//
#define UART_ISR_THRE_IF        0x00000002  

//
//! Receive Line Interrupt Flag.
//
#define UART_ISR_RLS_IF         0x00000004  

//
//! MODEM Interrupt Flag.
//
#define UART_ISR_MOD_IF         0x00000008  

//
//! Time Out Interrupt Flag.
//
#define UART_ISR_TOUT_IF        0x00000010  

//
//! Buffer Error Interrupt Flag.
//
#define UART_ISR_BUFERR_IF      0x00000020  

//
//! LIN Bus Rx Break Field Detected Flag.
//
#define UART_ISR_LINRXB_IF      0x00000080  

//
//! Receive Data Available Interrupt.
//
#define UART_ISR_RDA_INT        0x00000100 

//
//! Transmit Holding Register Empty Interrupt.
//
#define UART_ISR_THRE_INT       0x00000200  

//
//! Receive Line Status Interrupt.
//
#define UART_ISR_RLS_INT        0x00000400  

//
//! MODEM Status Interrupt.
//
#define UART_ISR_MOD_INT        0x00000800  

//
//! RTime Out Interrupt.
//
#define UART_ISR_TOUT_INT       0x00001000  

//
//! Buffer Error Interrupt.
//
#define UART_ISR_BUFERR_INT     0x00002000  

//
//! LIN Bus Rx Break Field Detected Interrupt.
//
#define UART_ISR_LINRXB_INT     0x00008000  

//
//! In DMA mode, Receive Line Status Flag.
//
#define UART_ISR_HW_RLS_IF      0x00040000  

//
//! In DMA mode, MODEM Interrupt Flag.
//
#define UART_ISR_HW_MOD_IF      0x00080000  

//
//! IIn DMA mode, Time out Interrupt Flag.
//
#define UART_ISR_HW_TOUT_IF     0x00100000  

//
//! In DMA mode, Buffer Error Interrupt Flag.
//
#define UART_ISR_HW_BUFERR_IF   0x00200000  

//
//! In DMA mode, LIN Bus Rx Break Field Detect Interrupt Flag.
//
#define UART_ISR_HW_LINRXB_IF   0x00800000 

//
//! In DMA mode, Receive Line Status Interrupt.
//
#define UART_ISR_HW_RLS_INT     0x04000000  

//
//! In DMA mode, MODEM Status Interrupt.
//
#define UART_ISR_HW_MOD_INT     0x08000000  

//
//! In DMA mode, Time Out Interrupt.
//
#define UART_ISR_HW_TOUT_INT    0x10000000  

//
//! In DMA mode, Buffer Error Interrupt.
//
#define UART_ISR_HW_BUFERR_INT  0x20000000  

//
//! In DMA mode, LIN Bus Rx Break Field Detected Interrupt.
//
#define UART_ISR_HW_LINRXB_INT  0x80000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_TOR UART Time Out Register(UART_TOR)
//! \brief Defines for the bit fields in the UART_TOR register.
//! @{
//
//*****************************************************************************

//
//! Time Out Interrupt Comparator.
//
#define UART_TOR_TOIC_M         0x0000007F  

//
//! Time Out Interrupt Comparator.
//
#define UART_TOR_TOIC_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_BAUD UART Baud Rate Divisor Register(UART_BAUD)
//! \brief Defines for the bit fields in the UART_BAUD register.
//! @{
//
//*****************************************************************************

//
//! Baud Rate Divider.
//
#define UART_BAUD_BRD_M         0x0000FFFF  

//
//! Baud Rate Divider.
//
#define UART_BAUD_BRD_S         0

//
//! TDivider X.
//
#define UART_BAUD_DIV_X_M       0x0F000000 

//
//! Divider X.
//
#define UART_BAUD_DIV_X_S       24

//
//! Divider X equal 1.
//
#define UART_BAUD_DIV_X_ONE     0x10000000  

//
//! Divider X Enable.
//
#define UART_BAUD_DIV_X_EN      0x20000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_IRCR UART IrDA Control Register(UART_IRCR)
//! \brief Defines for the bit fields in the IRCR register.
//! @{
//
//*****************************************************************************

//
//! Tx_SELECT.
//
#define UART_IRCR_TX_SELECT     0x00000002  

//
//! Inverse Tx output signal.
//
#define UART_IRCR_INV_TX        0x00000020  

//
//! Inverse Rx output signal.
//
#define UART_IRCR_INV_RX        0x00000020  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_ALT_CSR UART Alternate Control/Status Register(UART_ALT_CSR)
//! \brief Defines for the bit fields in the UART_ALT_CSR register.
//! @{
//
//*****************************************************************************

//
//! UART LIN Break Field Length master.
//
#define UART_LIN_BCNT_BKFL_M    0x0000000F  

//
//! UART LIN Break Field Length shift.
//
#define UART_LIN_BCNT_BKFL_S    0

//
//! LIN RX Enable.
//
#define UART_LIN_BCNT_RX_EN     0x00000040  

//
//! LIN TX Enable.
//
#define UART_LIN_BCNT_TX_EN     0x00000080  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_UART_Register_UART_FUN_SEL UART Function Select Register(UART_FUN_SEL)
//! \brief Defines for the bit fields in the UART_FUN_SEL register.
//! @{
//
//*****************************************************************************

//
//! LIN Function Enable.
//
#define UART_FUN_SEL_LIN_EN     0x00000001  

//
//! IrDA Function Enable.
//
#define UART_FUN_SEL_IRDA_EN    0x00000002  

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
