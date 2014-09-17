//*****************************************************************************
//
//! \file      uart.h
//! \brief     The uart implementation port file.
//! \version   V3.0.0.1
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

///////////////////////////////////////////////////////////////////////////////
//  define for port to cox 'x' prefixed interface
///////////////////////////////////////////////////////////////////////////////
#define UART_INT_ERROR                 INT_RLS
#define UART_INT_RT                    INT_RLS
#define UART_INT_TX                    INT_THRE
#define UART_INT_RX                    INT_RDA

#define UART_RXERROR_OVERRUN           OVERRUN_ERR
#define UART_RXERROR_BREAK             BREAK_INT
#define UART_RXERROR_PARITY            PARITY_ERR
#define UART_RXERROR_FRAMING           FRAMING_ERR

#define UART_CONFIG_WLEN_8             UART_CFG_LEN_8_BIT
#define UART_CONFIG_WLEN_7             UART_CFG_LEN_7_BIT
#define UART_CONFIG_WLEN_6             UART_CFG_LEN_6_BIT
#define UART_CONFIG_WLEN_5             UART_CFG_LEN_5_BIT

#define UART_CONFIG_STOP_1             UART_CFG_STOP_1_BIT
#define UART_CONFIG_STOP_2             UART_CFG_STOP_2_BIT

#define UART_CONFIG_PAR_ONE            UART_CFG_PARITY_1
#define UART_CONFIG_PAR_ZERO           UART_CFG_PARITY_0

#define UART_BLOCK_UART                BIT_32_0
#define UART_BLOCK_TX                  BIT_32_1
#define UART_BLOCK_RX                  BIT_32_2

#define UART_FIFO_RX_1                 FIFO_CFG_RX_TRI_LVL_0
#define UART_FIFO_RX_4                 FIFO_CFG_RX_TRI_LVL_1
#define UART_FIFO_RX_8                 FIFO_CFG_RX_TRI_LVL_2
#define UART_FIFO_RX_14                FIFO_CFG_RX_TRI_LVL_3


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

