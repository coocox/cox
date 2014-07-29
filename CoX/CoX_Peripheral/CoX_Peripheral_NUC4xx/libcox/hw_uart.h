//*****************************************************************************
//
//! \file hw_uart.h
//! \brief Macros used when accessing the UART hardware.
//! \version V2.2.1.0
//! \date 6/15/2014
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
//! \addtogroup NUC4xx_UART_Register NUC4xx UART Register
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
//! \addtogroup NUC4xx_UART_Register_Offsets UART Register Offset(Map)
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
//! Alternate Control/Status Register.
// 
#define UART_ALT_CSR            0x0000002C  

//
//! Function Select Register.
// 
#define UART_FUN_SEL            0x00000030

//
//! LIN Control Register
//
#define UART_LIN_CTL            0x00000034

//
//! LIN Status Register
//
#define UART_LIN_SR             0x00000038

//
//! LIN Debug Register
//
#define UART_LIN_DEBUG          0x0000003C

//
//! SC Control Register
//
#define UART_SC_CTL             0x00000040

//
//! SC Flag Control Register
//
#define UART_SC_FSR             0x00000044

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_RBR UART Receive Buffer Register(UART_RBR)
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
//! \addtogroup NUC4xx_UART_Register_UART_THR UART Transmit Holding Register(UART_THR)
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
//! \addtogroup NUC4xx_UART_Register_UART_IER UART Interrupt Enable Register(UART_IER)
//! \brief Defines for the bit fields in the UART_IER register.
//! @{
//
//*****************************************************************************

//
//! Receive Data Available Interrupt Enable.
//
#define UART_IER_RDA_IEN        BIT_32_0  

//
//! Transmit Holding Register Empty Interrupt Enable.
//
#define UART_IER_THRE_IEN       BIT_32_1  

//
//! Receive Line Status Interrupt Enable
//
#define UART_IER_RLS_IEN        BIT_32_2  

//
//! Modem Status Interrupt Enable
//
#define UART_IER_MOD_IEN        BIT_32_3  

//
//! Rx Time out Interrupt Enable
//
#define UART_IER_RTO_IEN        BIT_32_4  

//
//! Buffer Error Interrupt Enable
//
#define UART_IER_BUF_ERR_IEN    BIT_32_5  

//
//! Wake up CPU function enable
//
#define UART_IER_WAKE_IEN       BIT_32_6  

//
//! Time-Out Counter Enable
//
#define UART_IER_LIN_EN         BIT_32_8

//
//! Time-Out Counter Enable
//
#define UART_IER_TIME_OUT_EN    BIT_32_11  

//
//! RTS Auto Flow Control Enable
//
#define UART_IER_AUTO_RTS_EN    BIT_32_12  

//
//! CTS Auto Flow Control Enable
//
#define UART_IER_AUTO_CTS_EN    BIT_32_13  

//
//! TX DMA Enable
//
#define UART_IER_DMA_TX_EN      BIT_32_14

//
//! RX DMA Enable
//
#define UART_IER_DMA_RX_EN      BIT_32_15


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_FCR  UART FIFO Control Register(UART_FCR)
//! \brief Defines for the bit fields in the UART_FCR register.
//! @{
//
//*****************************************************************************

//
//! Rx Software Reset
//
#define UART_FCR_RX_RST         BIT_32_1  

//
//! Tx Software Reset
//
#define UART_FCR_TX_RST         BIT_32_2  

//
//! Rx FIFO Interrupt(INT_RDA)Trigger Level
//
#define UART_FCR_RFITL_M        0x000000F0  

//
//! Rx FIFO Interrupt(INT_RDA)Trigger Level
//
#define UART_FCR_RFITL_S        4

//
//! Rx Disable Register
//
#define UART_FCR_RX_DIS         BIT_32_8

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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_LCR UART Line Control Register(UART_LCR)
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
#define UART_LCR_NSB            BIT_32_2  

//
//! Parity Bit Enable
//
#define UART_LCR_PBE            BIT_32_3  

//
//! Even Parity Enable
//
#define UART_LCR_EPE            BIT_32_4  

//
//! Stick Parity Enable
//
#define UART_LCR_SPE            BIT_32_5  

//
//! Break Control Bit
//
#define UART_LCR_BCB            BIT_32_6  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_MCR UART Modem Control Register(UART_MCR)
//! \brief Defines for the bit fields in the UART_MCR register.
//! @{
//
//*****************************************************************************

//
//! RTS (Request-To-Send) Signal
//
#define UART_MCR_RTS            BIT_32_1  

//
//! RTS Trigger Level
//
#define UART_MCR_LEV_RTS        BIT_32_9  

//
//! This bit is the pin status of RTS.
//
#define UART_MCR_RTS_ST         BIT_32_13  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_MSR UART Modem Status Register(UART_MSR)
//! \brief Defines for the bit fields in the UART_MSR register.
//! @{
//
//*****************************************************************************

//
//! CTS Trigger Level
//
#define UART_MSR_LEV_CTS        BIT_32_8  

//
//! This bit is the pin status of CTS.
//
#define UART_MSR_CTS_ST         BIT_32_4  

//
//! Detect CTS State Change Flag
//
#define UART_MSR_DCTSF          BIT_32_0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_FSR UART FIFO Status Register(UART_FSR)
//! \brief Defines for the bit fields in the UART_FSR register.
//! @{
//
//*****************************************************************************

//
//! Rx overflow Error IF.
//
#define UART_FSR_RXO_IF         BIT_32_0

//
//! Smart Card Over Error Retry Flag
//!
#define UART_FSR_SC_OVEREF      BIT_32_2

//
//! RS-485 Address Byte Detection Flag
//
#define UART_FSR_RS485_ABDF     BIT_32_3

//
//! Parity Error Flag.
//
#define UART_FSR_PEF            BIT_32_4  

//
//! Framing Error Flag.
//
#define UART_FSR_FEF            BIT_32_5  

//
//! Break Interrupt Flag.
//
#define UART_FSR_BIF            BIT_32_6  

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
#define UART_FSR_RX_EF          BIT_32_14  

//
//! Receiver FIFO Full.
//
#define UART_FSR_RX_FF          BIT_32_15  

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
#define UART_FSR_TX_EF          BIT_32_22  

//
//! Transmitter FIFO Full.
//
#define UART_FSR_TX_FF          BIT_32_23  

//
//! Tx Overflow Error Interrupt Flag.
//
#define UART_FSR_TXO_IF         BIT_32_24  

//
//! Transmitter Empty Flag.
//
#define UART_FSR_TE_FLAG        BIT_32_28  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_ISR UART Interrupt Status Register(UART_ISR)
//! \brief Defines for the bit fields in the UART_ISR register.
//! @{
//
//*****************************************************************************

//
//! Receive Data Available Interrupt Flag.
//
#define UART_ISR_RDA_IF         BIT_32_0  

//
//! Transmit Holding Register Empty Interrupt Flag.
//
#define UART_ISR_THRE_IF        BIT_32_1

//
//! Receive Line Interrupt Flag.
//
#define UART_ISR_RLS_IF         BIT_32_2  

//
//! MODEM Interrupt Flag.
//
#define UART_ISR_MOD_IF         BIT_32_3  

//
//! Time Out Interrupt Flag.
//
#define UART_ISR_TOUT_IF        BIT_32_4  

//
//! Buffer Error Interrupt Flag.
//
#define UART_ISR_BUFERR_IF      BIT_32_5 
//
//! LIN Interrupt Flag.
//
#define UART_ISR_LIN_IF         BIT_32_7

//
//! Receive Data Available Interrupt.
//
#define UART_ISR_RDA_INT        BIT_32_8 

//
//! Transmit Holding Register Empty Interrupt.
//
#define UART_ISR_THRE_INT       BIT_32_9  

//
//! Receive Line Status Interrupt.
//
#define UART_ISR_RLS_INT        BIT_32_10  

//
//! MODEM Status Interrupt.
//
#define UART_ISR_MOD_INT        BIT_32_11  

//
//! RTime Out Interrupt.
//
#define UART_ISR_TOUT_INT       BIT_32_12  

//
//! Buffer Error Interrupt.
//
#define UART_ISR_BUFERR_INT     BIT_32_13  

//
//! LIN Bus Interrupt Indicator
//
#define UART_ISR_LIN_INT        BIT_32_15

//
//! In DMA Mode, Receive Line Status Flag (Read Only)
//
#define UART_ISR_HW_RLS_IF      BIT_32_18

//
//! In DMA Mode, MODEM Interrupt Flag (Read Only)
//
#define UART_ISR_HW_MODEM_IF    BIT_32_19

//
//! In DMA Mode, Time Out Interrupt Flag (Read Only)
//
#define UART_ISR_HW_TOUT_IF     BIT_32_20

//
//! In DMA Mode, Buffer Error Interrupt Flag (Read Only)
//
#define UART_ISR_HW_BUF_ERR_IF  BIT_32_21

//
//! In DMA Mode, Receive Line Status Interrupt Indicator (Read Only)
//
#define UART_ISR_HW_RLS_INT     BIT_32_26

//
//! In DMA Mode, MODEM Status Interrupt Indicator (Read Only)
//
#define UART_ISR_HW_MODEM_INT   BIT_32_27

//
//! In DMA Mode, Time Out Interrupt Indicator (Read Only)
//
#define UART_ISR_HW_TOUT_INT    BIT_32_28


//
//! In DMA Mode, Buffer Error Interrupt Indicator (Read Only)
//
#define UART_ISR_HW_BUF_ERR_INT BIT_32_29


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_TOR UART Time Out Register(UART_TOR)
//! \brief Defines for the bit fields in the UART_TOR register.
//! @{
//
//*****************************************************************************

//
//! Time Out Interrupt Comparator.
//
#define UART_TOR_TOIC_M         0x000000FF  

//
//! Time Out Interrupt Comparator.
//
#define UART_TOR_TOIC_S         0

//
//! Tx Delay Time Value
//
#define UART_TOR_TDTV_M         0x0000FF00

//
//! Tx Delay Time Value
//
#define UART_TOR_TDTV_S         8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_BAUD UART Baud Rate Divisor Register(UART_BAUD)
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
#define UART_BAUD_DIV_X_ONE     BIT_32_28  

//
//! Divider X Enable.
//
#define UART_BAUD_DIV_X_EN      BIT_32_29  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_IRCR UART IrDA Control Register(UART_IRCR)
//! \brief Defines for the bit fields in the IRCR register.
//! @{
//
//*****************************************************************************

//
//! Tx_SELECT.
//
#define UART_IRCR_TX_SELECT     BIT_32_1  

//
//! Inverse Tx output signal.
//
#define UART_IRCR_INV_TX        BIT_32_5  

//
//! Inverse Rx output signal.
//
#define UART_IRCR_INV_RX        BIT_32_6

//
//! Pulse width of TX is fixed 1.6us
//
#define UART_IRCR_TPS           BIT_32_7  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_ALT_CSR UART Alternate Control/Status Register(UART_ALT_CSR)
//! \brief Defines for the bit fields in the UART_ALT_CSR register.
//! @{
//
//*****************************************************************************

#define UART_ALT_CSR_LIN_BKFL_M BIT_MASK(32,3,0)

#define UART_ALT_CSR_LIN_RX_EN  BIT_32_6
#define UART_ALT_CSR_LIN_TX_EN  BIT_32_7

//
//! RS-485 Normal Multi-drop Operation Mode 
//
#define UART_ALT_CSR_RS485_NMM  BIT_32_8

//
//! RS-485 Auto Address Detection Operation Mode
//
#define UART_ALT_CSR_RS485_ADD  BIT_32_9

//
//! RS-485 Auto Direction Mode
//
#define UART_ALT_CSR_RS485_AUD  BIT_32_10

//
//! RS-485 Address Detection Enable
//
#define UART_ALT_CSR_RS485_ADD_EN                                             \
                                BIT_32_15

//
//! Address Match Value Register
//
#define UART_ALT_CSR_ADDR_MATCH_M                                             \
                                0xFF0000000

//
//! Address Match Value Register
//
#define UART_ALT_CSR_ADDR_MATCH_S                                             \
                                24

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_FUN_SEL UART Function Select Register(UART_FUN_SEL)
//! \brief Defines for the bit fields in the UART_FUN_SEL register.
//! @{
//
//*****************************************************************************

#define UART_FUN_SEL_MASK       BIT_MASK(32,1,0)
//
//! UART Function
//  
#define UART_FUN_SEL_UART_EN    0x00000000 

#define UART_FUN_SEL_LIN_EN     0x00000001

//
//! IrDA Function Enable.
//
#define UART_FUN_SEL_IRDA_EN    0x00000002  
                                  
//
//! RS-485 Function Enable
//
#define UART_FUN_SEL_RS485_EN   0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_LIN_CTL UART LIN Control Register(UART_LIN_CTL)
//! \brief Defines for the bit fields in the UART_LIN_CTL register.
//! @{
//
//*****************************************************************************

//
//! LIN frame ID value
//
#define UART_LIN_CTL_PID_M      0xFF000000
#define UART_LIN_CTL_PID_S      24

//
//! LIN Header Selection
//
#define UART_LIN_CTL_HEAD_SEL_M 0x00C00000
#define UART_LIN_CTL_HEAD_SEL_S 22

//
//! LIN Header Selection
//
#define UART_LIN_CTL_BS_LEN_M   0x00300000
#define UART_LIN_CTL_BS_LEN_S   20

//
//! LIN Break Field Length
//
#define UART_LIN_CTL_LIN_BKFL_M 0x000F0000
#define UART_LIN_CTL_LIN_BKFL_S 16

//
//! Bit Error Detect Enable Control
//
#define UART_LIN_CTL_BITERR_EN  BIT_32_12

//
//! Bit error detection Enable Control
//
#define UART_LIN_CTL_LINRX_DIS  BIT_32_11

//
//! LIN Break Detection Enable Control
//
#define UART_LIN_CTL_BKDET_EN   BIT_32_10

//
//! LIN ID Parity Enable Control
//
#define UART_LIN_CTL_LIN_IDPEN  BIT_32_9

//
//! LIN TX Send Header Enable Control
//
#define UART_LIN_CTL_LIN_SHD    BIT_32_8

//
//! LIN Mute Mode Enable Control
//
#define UART_LIN_CTL_LIN_MUTE   BIT_32_4

//
//! LIN Slave Divider Update Method Enable Control
//
#define UART_LIN_CTL_LINS_DUM   BIT_32_3

//
//! LIN Slave Automatic Resynchronization Mode Enable Control
//
#define UART_LIN_CTL_LINS_ARS   BIT_32_2

//
//! LIN Slave Header Detection Enable Control
//
#define UART_LIN_CTL_LINS_HDET  BIT_32_1

//
//! LIN Slave Mode Enable Control
//
#define UART_LIN_CTL_LINS_EN    BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_LIN_SR UART LIN Status Register(UART_LIN_SR)
//! \brief Defines for the bit fields in the UART_LIN_SR register.
//! @{
//
//*****************************************************************************

//
//! Bit Error Detect Status Flag
//
#define UART_LIN_SR_ERR_F       BIT_32_9

//
//! LIN Break Detection Flag
//
#define UART_LIN_SR_BKDET_F     BIT_32_8

//
//! LIN Slave Sync Field
//
#define UART_LIN_SR_SYNC_F      BIT_32_3

//
//! LIN Slave ID Parity Error Flag
//
#define UART_LIN_SR_IDPERR_F    BIT_32_2

//
//! LIN Slave Header Error Flag
//
#define UART_LIN_SR_HERR_F      BIT_32_1

//
//! LIN Slave Header Detection Flag
//
#define UART_LIN_SR_HDET_F      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_UART_Register_UART_LIN_DEBUG UART LIN Debug Register(UART_LIN_DEBUG)
//! \brief Defines for the bit fields in the UART_LIN_DEBUG register.
//! @{
//
//*****************************************************************************

//
//! LIN Header Sync Data Error
//
#define UART_LIN_DEBUG_SYNC_F   BIT_32_3

//
//! LIN Header Frame Error Flag
//
#define UART_LIN_DEBUG_HEFE_F   BIT_32_2

//
//! LIN Header Time-out
//
#define UART_LIN_DEBUG_HETIME_F BIT_32_1

//
//! LIN Header Deviation Error
//
#define UART_LIN_DEBUG_DIVIA_F  BIT_32_0 
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
