//*****************************************************************************
//
//! \file xhw_uart.h
//! \brief Macros used when accessing the UART control hardware.
//! \version V2.1.1.0
//! \date 12/12/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
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
//! \addtogroup KLx_UART_Register KLx UART Register
//! \brief Here are the detailed info of UART registers.
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREGB().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_UART_Register_Offsets UART Register Offset(Map)
//! \brief Here is the UART register offset, users can get the register address
//! through <b>UART_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! UART 0 Register offset
//

//
//! Baud rate register high
//
#define UART_0_BDH              0x00000000UL

//
//! Baud rate register low
//
#define UART_0_BDL              0x00000001UL

//
//! Control register 1
//
#define UART_0_C1               0x00000002UL

//
//! Control register 2
//
#define UART_0_C2               0x00000003UL

//
//! Status register 1
//
#define UART_0_S1               0x00000004UL

//
//! Status register 2
//
#define UART_0_S2               0x00000005UL

//
//! Control register 3
//
#define UART_0_C3               0x00000006UL

//
//! Data register
//
#define UART_0_D                0x00000007UL

//
//! Match address register 1
//
#define UART_0_MA1              0x00000008UL

//
//! Match address register 2
//
#define UART_0_MA2              0x00000009UL

//
//! Control register 4
//
#define UART_0_C4               0x0000000AUL

//
//! Control register 5
//
#define UART_0_C5               0x0000000BUL

//
//! UART 1/2 Register offset
//

//
//! Baud rate register high
//
#define UART_12_BDH             0x00000000UL

//
//! Baud rate register low
//
#define UART_12_BDL             0x00000001UL

//
//! Control register 1
//
#define UART_12_C1              0x00000002UL

//
//! Control register 2
//
#define UART_12_C2              0x00000003UL

//
//! Status register 1
//
#define UART_12_S1              0x00000004UL

//
//! Status register 2
//
#define UART_12_S2              0x00000005UL

//
//! Control register 3
//
#define UART_12_C3              0x00000006UL

//
//! Data register
//
#define UART_12_D               0x00000007UL

//
//! Control register 4
//
#define UART_12_C4              0x00000008UL

//
//! UART 0/1/2 Register Offset
//

//
//! Baud rate register high
//
#define UART_012_BDH            0x00000000UL

//
//! Baud rate register low
//
#define UART_012_BDL            0x00000001UL

//
//! Control register 1
//
#define UART_012_C1             0x00000002UL

//
//! Control register 2
//
#define UART_012_C2             0x00000003UL

//
//! Status register 1
//
#define UART_012_S1             0x00000004UL

//
//! Status register 2
//
#define UART_012_S2             0x00000005UL

//
//! Control register 3
//
#define UART_012_C3             0x00000006UL

//
//! Data register
//
#define UART_012_D              0x00000007UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_BDH UART_BDH
//! \brief Defines for the bit fields in the UART_BDH register.
//! @{
//
//*****************************************************************************

//
// NOTE:
// 1: The following registers are listed in the order of
//    appeared in Reference Manual
// 2: Name Convention
//    Kentis MCU contains three UART module: UART0 UART1 UART2
//    UART 1 and UART2 are identical, but UART0 is different.
//    So, the name convention is described as follow:
//    {Module Name}_{Module ID}_{Register Name}_{Register Bit}_{Bit Function}
//
//  For example:
//  |-----------------------------------------------|
//  | UART_012_BDH_LBKDIE_ENABLE       0x00000080   |
//  -------------------------------|-----------------
//  | Module Name                  |   UART         |
//  -------------------------------|-----------------
//  | Module ID                    |   0/1/2        |
//  -------------------------------|-----------------
//  | Register Name                |   BDH          |
//  -------------------------------|-----------------
//  | Register Bit                 |   LBKDIE       |
//  -------------------------------|----------------|
//  | Bit Function                 |   ENABLE       |
//  |-----------------------------------------------|

//
//! UART Baud Rate Register High (BDH)
//

//
//! Line break detect interrupt enable
//
#define UART_012_BDH_LBKDIE                                                  \
                                0x00000080UL

#define UART_012_BDH_LBKDIE_MASK                                             \
                                0x00000080UL

#define UART_012_BDH_LBKDIE_DISABLE                                          \
                                0x00000000UL

#define UART_012_BDH_LBKDIE_ENABLE                                           \
                                0x00000080UL

//
//! RX input active edge interrupt enable
//
#define UART_012_BDH_RXEDGIE                                                 \
                                0x00000040UL

#define UART_012_BDH_RXEDGIE_MASK                                            \
                                0x00000040UL

#define UART_012_BDH_RXEDGIE_DISABLE                                         \
                                0x00000000UL

#define UART_012_BDH_RXEDGIE_ENABLE                                          \
                                0x00000040UL

//
//! Stop bit number select
//
#define UART_012_BDH_SBNS_MASK  0x00000020UL
#define UART_012_BDH_SBNS_ONE   0x00000000UL
#define UART_012_BDH_SBNS_TWO   0x00000020UL

//
//! Baud rate modulo divisor
//
#define UART_012_BDH_SBR_MASK   0x0000001FUL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_BDL UART_BDL
//! \brief Defines for the bit fields in the UART_BDL register.
//! @{
//
//*****************************************************************************

//
//! UART Baud Rate Register Low (BDL)
//
#define UART_012_BDL_SBR_MASK   0x000000FFUL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_C1 UART_C1
//! \brief Defines for the bit fields in the UART_C1 register.
//! @{
//
//*****************************************************************************

//
//! UART Control Register 1 (C1)
//

//
//! Loop mode select
//
#define UART_012_C1_LOOPS_MASK                                               \
                                0x00000080UL                                 \
#define UART_012_C1_LOOPS_NORMAL                                             \
                                0x00000080UL                                 \
#define UART_012_C1_LOOPS_LOOP_SINGLE                                        \
                                0x00000080UL                                 \

//
//! Doze enable
//
#define UART_012_C1_DOZEEN                                                   \
                                0x00000040UL
#define UART_012_C1_DOZEEN_MASK                                              \
                                0x00000040UL
#define UART_012_C1_DOZEEN_ENABLE                                            \
                                0x00000000UL
#define UART_012_C1_DOZEEN_DISABLE                                           \
                                0x00000040UL

//
//! Receiver source select
//
#define UART_012_C1_RSRC_MASK                                                \
                                0x00000020UL
#define UART_012_C1_RSRC_LOOP                                                \
                                0x00000000UL
#define UART_012_C1_RSRC_SINGLE_LINE                                         \
                                0x00000020UL

//
//! 9-bit or 9-bit mode select
//
#define UART_012_C1_M_MASK      0x00000010UL
#define UART_012_C1_M_8_BIT     0x00000000UL
#define UART_012_C1_M_9_BIT     0x00000010UL

//
//! Receiver wakeup mode select
//
#define UART_012_C1_WAKE_MASK                                                \
                                0x00000008UL
#define UART_012_C1_WAKE_IDLE_LINE                                           \
                                0x00000000UL
#define UART_012_C1_WAKE_ADDRESS_MARK                                        \
                                0x00000008UL

//
//! Idle line type select
//
#define UART_012_C1_ILT                                                      \
                                0x00000004UL
#define UART_012_C1_ILT_MASK                                                 \
                                0x00000004UL
#define UART_012_C1_ILT_START_BIT                                            \
                                0x00000000UL
#define UART_012_C1_ILT_STOP_BIT                                             \
                                0x00000004UL

//
//! Parity enable
//
#define UART_012_C1_PE                                                       \
                                0x00000002UL
#define UART_012_C1_PE_MASK                                                  \
                                0x00000002UL
#define UART_012_C1_PE_DISABLE                                               \
                                0x00000000UL
#define UART_012_C1_PE_ENABLE                                                \
                                0x00000002UL

//
//! Parity type
//
#define UART_012_C1_PT_MASK                                                  \
                                0x00000001UL
#define UART_012_C1_PT_EVEN                                                  \
                                0x00000000UL
#define UART_012_C1_PT_ODD                                                   \
                                0x00000001UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_C2 UART_C2
//! \brief Defines for the bit fields in the UART_C2  register.
//! @{
//
//*****************************************************************************

//
//! UART Control Register 2 (C2)
//

//
//! Transmit interrupt enable
//
#define UART_012_C2_TIE                                                      \
                                0x00000080UL
#define UART_012_C2_TIE_MASK                                                 \
                                0x00000080UL
#define UART_012_C2_TIE_DISABLE                                              \
                                0x00000000UL
#define UART_012_C2_TIE_ENABLE                                               \
                                0x00000080UL

//
//! Transmit complete interrupt enable
//
#define UART_012_C2_TCIE                                                     \
                                0x00000040UL
#define UART_012_C2_TCIE_MASK                                                \
                                0x00000040UL
#define UART_012_C2_TCIE_DISABLE                                             \
                                0x00000000UL
#define UART_012_C2_TCIE_ENABLE                                              \
                                0x00000040UL

//
//! Receiver interrupt enable
//
#define UART_012_C2_RIE                                                      \
                                0x00000020UL
#define UART_012_C2_RIE_MASK                                                 \
                                0x00000020UL
#define UART_012_C2_RIE_DISABLE                                              \
                                0x00000000UL
#define UART_012_C2_RIE_ENABLE                                               \
                                0x00000020UL

//
//! Idle line interrupt enable
//
#define UART_012_C2_ILIE                                                     \
                                0x00000010UL
#define UART_012_C2_ILIE_MASK                                                \
                                0x00000010UL
#define UART_012_C2_ILIE_DISABLE                                             \
                                0x00000000UL
#define UART_012_C2_ILIE_ENABLE                                              \
                                0x00000010UL

//
//! Transmitter enable
//
#define UART_012_C2_TE                                                       \
                                0x00000008UL
#define UART_012_C2_TE_MASK                                                  \
                                0x00000008UL
#define UART_012_C2_TE_DISABLE                                               \
                                0x00000000UL
#define UART_012_C2_TE_ENABLE                                                \
                                0x00000008UL

//
//! Receiver enable
//
#define UART_012_C2_RE                                                       \
                                0x00000004UL
#define UART_012_C2_RE_MASK                                                  \
                                0x00000004UL
#define UART_012_C2_RE_DISABLE                                               \
                                0x00000000UL
#define UART_012_C2_RE_ENABLE                                                \
                                0x00000004UL

//
//! Receiver wakeup control
//
#define UART_012_C2_RWU_MASK                                                 \
                                0x00000002UL
#define UART_012_C2_RWU_NORMAL                                               \
                                0x00000000UL
#define UART_012_C2_RWU_WAKEUP                                               \
                                0x00000002UL

//
//! Send break
//
#define UART_012_C2_SBK_MASK                                                 \
                                0x00000001UL
#define UART_012_C2_SBK_NORMAL                                               \
                                0x00000000UL
#define UART_012_C2_SBK_SEND_BREAK                                           \
                                0x00000001UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_S1  UART_S1
//! \brief Defines for the bit fields in the UART_S1  register.
//! @{
//
//*****************************************************************************

//
//! UART Status Register 1 (S1)
//
//! \note: To Clear IDLE/OR/NF/FE/PF Bit
//! UART0   : Write 1 to these bits
//! UART1/2 : Read S1 and Read UART Data Register
//

//
//! Transmit data register empty
//
#define UART_012_S1_TDRE_MASK                                                \
                                0x00000080UL
#define UART_012_S1_TDRE                                                     \
                                0x00000080UL

//
//! Transmit complete
//
#define UART_012_S1_TC_MASK                                                  \
                                0x00000040UL
#define UART_012_S1_TC                                                       \
                                0x00000040UL

//
//! Receive data register full flag
//
#define UART_012_S1_RDRF_MASK                                                \
                                0x00000020UL
#define UART_012_S1_RDRF                                                     \
                                0x00000020UL

//
//! Idle line flag
//
#define UART_012_S1_IDLE_MASK                                                \
                                0x00000010UL
#define UART_012_S1_IDLE                                                     \
                                0x00000010UL

//
//! Receiver overrun flag
//
#define UART_012_S1_OR_MASK                                                  \
                                0x00000008UL
#define UART_012_S1_OR                                                       \
                                0x00000008UL

//
//! Receiver noise flag
//
#define UART_012_S1_NF_MASK                                                  \
                                0x00000004UL
#define UART_012_S1_NF                                                       \
                                0x00000004UL

//
//! Receiver frame error flag
//
#define UART_012_S1_FE_MASK                                                  \
                                0x00000002UL
#define UART_012_S1_FE                                                       \
                                0x00000002UL

//
//! Parity error flag
//
#define UART_012_S1_PF_MASK                                                  \
                                0x00000001UL
#define UART_012_S1_PF                                                       \
                                0x00000001UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_S2  UART_S2
//! \brief Defines for the bit fields in the UART_S2  register.
//! @{
//
//*****************************************************************************

//
//! UART Status Register 2 (S2)
//! \note:
//! MSBF only exist in UART0 Module and RAF is ReadOnly
//

//
//! LIN break detect interrupt flag
//
#define UART_012_S2_LBKDIF_MASK                                              \
                                0x00000080UL
#define UART_012_S2_LBKDIF                                                   \
                                0x00000080UL

//
//! RX pin active edge interrupt flag
//
#define UART_012_S2_RXEDGIF_MASK                                             \
                                0x00000040UL
#define UART_012_S2_RXEDGIF                                                  \
                                0x00000040UL

//
//! MSB first
//
#define UART_0_S2_MSBF_MASK                                                  \
                                0x00000020UL
#define UART_0_S2_MSBF_LSB                                                   \
                                0x00000000UL
#define UART_0_S2_MSBF_MSB                                                   \
                                0x00000020UL

//
//! Receive data inversion
//
#define UART_012_S2_RXINV_MASK                                               \
                                0x00000010UL
#define UART_012_S2_RXINV_NORMAL                                             \
                                0x00000000UL
#define UART_012_S2_RXINV_INVERT                                             \
                                0x00000010UL

//
//! Receive wakeup idle detect
//
#define UART_012_S2_RWUID_MASK                                               \
                                0x00000008UL
#define UART_012_S2_RWUID_NOT_RECEIVE                                        \
                                0x00000000UL
#define UART_012_S2_RWUID_RECEIVE                                            \
                                0x00000008UL

//
//! Break character generation length
//
#define UART_012_S2_BRK13_MASK                                               \
                                0x00000004UL
#define UART_012_S2_BRK13                                                    \
                                0x00000004UL

//
//! LIN break detect enable
//
#define UART_012_S2_LBKDE                                                    \
                                0x00000002UL
#define UART_012_S2_LBKDE_MASK                                               \
                                0x00000002UL
#define UART_012_S2_LBKDE_DISABLE                                            \
                                0x00000000UL
#define UART_012_S2_LBKDE_ENABLE                                             \
                                0x00000002UL

//
//! Receiver active flag
//
#define UART_012_S2_RAF_MASK                                                 \
                                0x00000001UL
#define UART_012_S2_RAF                                                      \
                                0x00000001UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_C3  UART_C3
//! \brief Defines for the bit fields in the UART_C3  register.
//! @{
//
//*****************************************************************************

//
//! UART Control Register 3 (C3)
//! \note:
//!     for UART 1/2 :
//!         Bit7 R8   ReadOnly
//!         Bit6 T8   ReadWrite
//!
//!     for UART 0   :
//!         Bit7 R8T9 ReadWrite
//!         Bit6 R9T8 ReadWrite
//

//
//! Receive bit 8 / Transmit bit 9
//
#define UART_012_C3_R8T9_MASK                                                \
                                0x00000080UL

//
//! Receive bit 9 / Transmit bit 8
//
#define UART_012_C3_R9T8_MASK                                                \
                                0x00000040UL

//
//! TX pin direction in single-wire mode
//
#define UART_012_C3_TXDIR_MASK                                               \
                                0x00000020UL
#define UART_012_C3_TXDIR_IN                                                 \
                                0x00000000UL
#define UART_012_C3_TXDIR_OUT                                                \
                                0x00000020UL

//
//! Transmit data inversion
//
#define UART_012_C3_TXINV_MASK                                               \
                                0x00000010UL
#define UART_012_C3_TXINV_NORMAL                                             \
                                0x00000000UL
#define UART_012_C3_TXINV_INVERT                                             \
                                0x00000010UL

//
//! Overrun interrupt enable
//
#define UART_012_C3_ORIE                                                     \
                                0x00000008UL
#define UART_012_C3_ORIE_MASK                                                \
                                0x00000008UL
#define UART_012_C3_ORIE_DISABLE                                             \
                                0x00000000UL
#define UART_012_C3_ORIE_ENABLE                                              \
                                0x00000008UL

//
//! Noise error enable
//
#define UART_012_C3_NEIE                                                     \
                                0x00000004UL
#define UART_012_C3_NEIE_MASK                                                \
                                0x00000004UL
#define UART_012_C3_NEIE_DISABLE                                             \
                                0x00000000UL
#define UART_012_C3_NEIE_ENABLE                                              \
                                0x00000004UL

//
//! Frame error flag
//
#define UART_012_C3_FEIE                                                     \
                                0x00000002UL
#define UART_012_C3_FEIE_MASK                                                \
                                0x00000002UL
#define UART_012_C3_FEIE_DISABLE                                             \
                                0x00000000UL
#define UART_012_C3_FEIE_ENABLE                                              \
                                0x00000002UL

//
//! Parity error flag
//
#define UART_012_C3_PEIE                                                     \
                                0x00000001UL
#define UART_012_C3_PEIE_MASK                                                \
                                0x00000001UL
#define UART_012_C3_PEIE_DISABLE                                             \
                                0x00000000UL
#define UART_012_C3_PEIE_ENABLE                                              \
                                0x00000001UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_D UART_D
//! \brief Defines for the bit fields in the UART_D register.
//! @{
//
//*****************************************************************************

//
//! UART Data Register (D)
//
#define UART_012_D_MASK                                                      \
                                0x000000FFUL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_C4  UART_C4
//! \brief Defines for the bit fields in the UART_C4  register.
//! @{
//
//*****************************************************************************

//
//! UART Control Register 4 (C4)
//! \note: UART0 and UART1/2 are difference
//! +--------------------------------------------------------------------------+
//! |  UART ID | Bit7  | Bit6   | Bit5  | Bit4   | Bit3  |  Bit2 | Bit1 | Bit0 |
//! |----------|-------|--------|-------|--------------------------------------|
//! |  0       | MAEN1 | MAEN2  | M10   |              OSR                     |
//! |----------|-------|--------|-------|--------------------------------------|
//! |  1/2     | TDMAS | TCDMAS | RDMAS | ILDMAS | LBKDDMAS                    |
//! +--------------------------------------------------------------------------+
//

//
//! Match address mode enable 1
//
#define UART_0_C4_MAEN1                                                      \
                                0x00000080UL
#define UART_0_C4_MAEN1_MASK                                                 \
                                0x00000080UL
#define UART_0_C4_MAEN1_DISABLE                                              \
                                0x00000000UL
#define UART_0_C4_MAEN1_ENABLE                                               \
                                0x00000080UL

//
//! Transmitter DMA select
//
#define UART_12_C4_TDMAS_MASK                                                \
                                0x00000080UL
#define UART_12_C4_TDMAS_INTERRUPT                                           \
                                0x00000000UL
#define UART_12_C4_TDMAS_DMA                                                 \
                                0x00000080UL

//
//! Match address mode enable 2
//
#define UART_0_C4_MAEN2                                                      \
                                0x00000040UL
#define UART_0_C4_MAEN2_MASK                                                 \
                                0x00000040UL
#define UART_0_C4_MAEN2_DISABLE                                              \
                                0x00000000UL
#define UART_0_C4_MAEN2_ENABLE                                               \
                                0x00000040UL

//
//! Transmission complete DMA select
//
#define UART_12_C4_TCDMAS_MASK                                               \
                                0x00000040UL
#define UART_12_C4_TCDMAS_INTERRUPT                                          \
                                0x00000000UL
#define UART_12_C4_TCDMAS_DMA                                                \
                                0x00000040UL

//
//! 10 bit mode select
//
#define UART_0_C4_M10_MASK                                                   \
                                0x00000020UL
#define UART_0_C4_M10_8_9_BIT                                                \
                                0x00000000UL
#define UART_0_C4_M10_10_BIT                                                 \
                                0x00000020UL

//
//! Receiver full DMA select
//
#define UART_12_C4_RDMAS_MASK                                                \
                                0x00000020UL
#define UART_12_C4_RDMAS_INTERRUPT                                           \
                                0x00000000UL
#define UART_12_C4_RDMAS_DMA                                                 \
                                0x00000020UL

//
//! Over sampling ratio
//
#define UART_0_C4_OSR_MASK                                                   \
                                0x0000001FUL
#define UART_0_C4_OSR_DEFAULT                                                \
                                0x0000000FUL

//
//! Idle line DMA select
//
#define UART_12_C4_ILDMAS_MASK                                               \
                                0x00000010UL
#define UART_12_C4_ILDMAS_INTERRUPT                                          \
                                0x00000000UL
#define UART_12_C4_ILDMAS_DMA                                                \
                                0x00000010UL

//
//! lIN break detect DMA select bit
//
#define UART_12_C4_LBKDDMAS_MASK                                             \
                                0x00000008UL
#define UART_12_C4_LBKDDMAS_INTERRUPT                                        \
                                0x00000000UL
#define UART_12_C4_LBKDDMAS_DMA                                              \
                                0x00000008UL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_MA1 UART_MA1
//! \brief Defines for the bit fields in the UART_MA1 register.
//! @{
//
//*****************************************************************************

//
//! UART Match Address Registers 1 (MA1)
//
#define UART_0_MA1_MASK                                                      \
                               0x000000FFUL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_MA2 UART_MA2
//! \brief Defines for the bit fields in the UART_MA2 register.
//! @{
//
//*****************************************************************************

//
//! UART Match Address Registers 2 (MA2)
//
#define UART_0_MA2_MASK                                                      \
                               0x000000FFUL

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_UART_Register_UART_C5 UART_C5
//! \brief Defines for the bit fields in the UART_C5 register.
//! @{
//
//*****************************************************************************

//
//! UART Control Register 5 (C5)
//

//
//! Transmitter DMA enable
//
#define UART_0_C5_TDMAE                                                      \
                                0x00000080UL
#define UART_0_C5_TDMAE_MASK                                                 \
                                0x00000080UL
#define UART_0_C5_TDMAE_DISABLE                                              \
                                0x00000000UL
#define UART_0_C5_TDMAE_ENABLE                                               \
                                0x00000080UL

//
//! Receiver full DMA enable
//
#define UART_0_C5_RDMAE                                                      \
                                0x00000020UL
#define UART_0_C5_RDMAE_MASK                                                 \
                                0x00000020UL
#define UART_0_C5_RDMAE_DISABLE                                              \
                                0x00000000UL
#define UART_0_C5_RDMAE_ENABLE                                               \
                                0x00000020UL

//
//! Both edge sampling
//
#define UART_0_C5_BOTHEDGE_MASK                                              \
                                0x00000002UL
#define UART_0_C5_BOTHEDGE                                                   \
                                0x00000002UL

//
//! Resynchronization disable
//
#define UART_0_C5_RESYNCDIS                                                  \
                                0x00000001UL
#define UART_0_C5_RESYNCDIS_MASK                                             \
                                0x00000001UL
#define UART_0_C5_RESYNCDIS_ENABLE                                           \
                                0x00000000UL
#define UART_0_C5_RESYNCDIS_DISABLE                                          \
                                0x00000001UL

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

#endif // End of __XHW_UART_H__

