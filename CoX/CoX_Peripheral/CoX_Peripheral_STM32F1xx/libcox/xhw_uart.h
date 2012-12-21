
//*****************************************************************************
//
//! \file xhw_uart.h
//! \brief Macros used when accessing the UART control hardware.
//! \version V2.2.1.0
//! \date 12/12/2011
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
//! \addtogroup STM32F1xx_UART_Register STM32F1xx UART Register
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
//! \addtogroup STM32F1xx_UART_Register_Offsets UART Register Offset(Map)
//! \brief Here is the UART register offset, users can get the register address
//! through <b>UART_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Status register
//
#define USART_SR                0x00000000

//
//! Data register
//
#define USART_DR                0x00000004

//
//! Baud rate register
//
#define USART_BRR               0x00000008

//
//! Control register 1
//
#define USART_CR1               0x0000000C

//
//! Control register 2
//
#define USART_CR2               0x00000010

//
//! Control register 3
//
#define USART_CR3               0x00000014

//
//! Guard time and prescaler register
//
#define USART_GTPR              0x00000018

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_USART_SR USART_SR 
//! \brief Defines for the bit fields in the USART_SR register.
//! @{
//
//*****************************************************************************

//
//!  CTS flag
//
#define USART_SR_CTS            0x00000200  

//
//!  LIN break detection flag
//
#define USART_SR_LBD            0x00000100 

//
//!  Transmit data register empty
//
#define USART_SR_TXE            0x00000080 

//
//!  Transmission complete
//
#define USART_SR_TC             0x00000040 

//
//!  Read data register not empty
//
#define USART_SR_RXNE           0x00000020 

//
//!  IDLE line detected
//
#define USART_SR_IDLE           0x00000010 

//
//!  Overrun error
//
#define USART_SR_ORE            0x00000008 

//
//!  Noise error flag
//
#define USART_SR_NE             0x00000004 

//
//!  Framing error
//
#define USART_SR_FE             0x00000002 

//
//!  Parity error
//
#define USART_SR_PE             0x00000001 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_USART_DR USART_DR 
//! \brief Defines for the bit fields in the USART_DR register.
//! @{
//
//*****************************************************************************

//
//!  Data value mask
//
#define USART_DR_DR_M           0x000000FF  

//
//!  Data value shift
//
#define USART_DR_DR_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_USART_BRR USART_BRR 
//! \brief Defines for the bit fields in the USART_BRR register.
//! @{
//
//*****************************************************************************

//
//!  mantissa of USARTDIV mask
//
#define USART_BRR_DIVM_M        0x0000FFF0  

//
//!  mantissa of USARTDIV shift
//
#define USART_BRR_DIVM_S        4

//
//!  mantissa of USARTDIV mask
//
#define USART_BRR_DIVF_M        0x0000000F  

//
//!  mantissa of USARTDIV shift
//
#define USART_BRR_DIVF_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_USART_CR1 USART_CR1 
//! \brief Defines for the bit fields in the USART_CR1 register.
//! @{
//
//*****************************************************************************

//
//!  USART enable
//
#define USART_CR1_UE            0x00002000  

//
//!  Word length
//
#define USART_CR1_M             0x00001000

//
//!  Wakeup method
//
#define USART_CR1_WAKE          0x00000800

//
//!  Parity control enable
//
#define USART_CR1_PCE           0x00000400

//
//!  Parity selection
//
#define USART_CR1_PS            0x00000200

//
//!  PE interrupt enable
//
#define USART_CR1_PEIE          0x00000100

//
//!  TXE interrupt enable
//
#define USART_CR1_TXEIE         0x00000080

//
//!  Transmission complete interrupt enable
//
#define USART_CR1_TCIE          0x00000040

//
//!  RXNE interrupt enable
//
#define USART_CR1_RXNEIE        0x00000020

//
//!  IDLE interrupt enable
//
#define USART_CR1_IDLEIE        0x00000010

//
//!  Transmitter enable
//
#define USART_CR1_TE            0x00000008

//
//!  Receiver enable
//
#define USART_CR1_RE            0x00000004

//
//!  Receiver wakeup
//
#define USART_CR1_RWE           0x00000002

//
//!  Send break
//
#define USART_CR1_SBK           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_USART_CR2 USART_CR2 
//! \brief Defines for the bit fields in the USART_CR2 register.
//! @{
//
//*****************************************************************************

//
//!  LIN mode enable
//
#define USART_CR2_LINEN         0x00004000

//
//!  STOP bits mask
//
#define USART_CR2_STOP_M        0x00003000
#define USART_CR2_STOP_1        0x00000000
#define USART_CR2_STOP_05       0x00001000
#define USART_CR2_STOP_2        0x00002000
#define USART_CR2_STOP_15       0x00003000

//
//!  STOP bits shift
//
#define USART_CR2_STOP_S        12

//
//!  Clock enable
//
#define USART_CR2_CLKEN         0x00000800

//
//!  Clock polarity
//
#define USART_CR2_CPOL          0x00000400

//
//!  Clock phase
//
#define USART_CR2_CPHA          0x00000200

//
//!  Last bit clock pulse
//
#define USART_CR2_LBCL          0x00000100

//
//!  LIN break detection interrupt enable
//
#define USART_CR2_LBDIE         0x00000040

//
//!  lin break detection length
//
#define USART_CR2_LBDL          0x00000020

//
//!  Address of the USART node mask
//
#define USART_CR2_ADD_M         0x0000000F

//
//!  Address of the USART node shift
//
#define USART_CR2_ADD_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_USART_CR3 USART_CR3 
//! \brief Defines for the bit fields in the USART_CR3 register.
//! @{
//
//*****************************************************************************

//
//!  CTS interrupt enable
//
#define USART_CR3_CTSIE         0x00000400

//
//!  CTS enable
//
#define USART_CR3_CTSE          0x00000200

//
//!  RTS enable
//
#define USART_CR3_RTSE          0x00000100

//
//!  DMA enable transmitter
//
#define USART_CR3_DMAT          0x00000080

//
//!  DMA enable receiver
//
#define USART_CR3_DMAR          0x00000040

//
//!  Smartcard mode enable
//
#define USART_CR3_SCEN          0x00000020

//
//!  Smartcard NACK enable
//
#define USART_CR3_NACK          0x00000010

//
//!  Half-duplex selection
//
#define USART_CR3_HDSEL         0x00000008

//
//!  IrDA low-power
//
#define USART_CR3_IRLP          0x00000004

//
//!  IrDA mode enable
//
#define USART_CR3_IREN          0x00000002

//
//!  Error interrupt enable
//
#define USART_CR3_EIE           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_USART_GTPR USART_GTPR 
//! \brief Defines for the bit fields in the USART_GTPR register.
//! @{
//
//*****************************************************************************

//
//!  Guard time value mask
//
#define USART_GTPR_GT_M         0x0000FF00  

//
//!  Guard time value shift
//
#define USART_GTPR_GT_S         8

//
//!  Prescaler value mask
//
#define USART_GTPR_PSC_M        0x000000FF  

//
//!  Prescaler value shift
//
#define USART_GTPR_PSC_S        0

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

