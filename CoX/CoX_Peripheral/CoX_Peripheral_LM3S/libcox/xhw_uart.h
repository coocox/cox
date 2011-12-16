//*****************************************************************************
//
//! \file xhw_uart.h
//! \brief Macros and defines used when accessing the UART hardware.
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

#ifndef __xHW_UART_H__
#define __xHW_UART_H__

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
//! \addtogroup Stellaris_UART_Register Stellaris UART Register
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_UART_Register_Offsets Stellaris UART Register Map(Offset)
//! @{
//
//*****************************************************************************

//
//! UART Data
//
#define UART_DR                 0x00000000  

//
//! UART Receive Status
//
#define UART_RSR                0x00000004  

//
//! UART Receive Error Clear
//
#define UART_ECR                0x00000004  

//
//! UART Flag
//
#define UART_FR                 0x00000018  

//
//! UART IrDA Low-Power Register
//
#define UART_ILPR               0x00000020  

//
//! UART Integer Baud-Rate Divisor
//
#define UART_IBRD               0x00000024  

//
//! UART Fractional Baud-Rate Divisor
//
#define UART_FBRD               0x00000028  

//
//! UART Line Control
//
#define UART_LCRH               0x0000002C  

//
//! UART Control
//
#define UART_CTL                0x00000030  

//
//! UART Interrupt FIFO Level Select
//
#define UART_IFLS               0x00000034  

//
//! UART Interrupt Mask
//
#define UART_IM                 0x00000038  

//
//! UART Raw Interrupt Status
//
#define UART_RIS                0x0000003C  

//
//! UART Masked Interrupt Status
//
#define UART_MIS                0x00000040  

//
//! UART Interrupt Clear
//
#define UART_ICR                0x00000044  

//
//! UART DMA Control
//
#define UART_DMACTL             0x00000048  

//
//! UART LIN Control
//
#define UART_LCTL               0x00000090  

//
//! UART LIN Snap Shot
//
#define UART_LSS                0x00000094  

//
//! UART LIN Timer
//
#define UART_LTIM               0x00000098  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_DR UART_DR
//! @{
//
//*****************************************************************************

//
//! UART Overrun Error
//
#define UART_DR_OE              0x00000800  

//
//! UART Break Error
//
#define UART_DR_BE              0x00000400  

//
//! UART Parity Error
//
#define UART_DR_PE              0x00000200  

//
//! UART Framing Error
//
#define UART_DR_FE              0x00000100  

//
//! Data Transmitted or Received
//
#define UART_DR_DATA_M          0x000000FF  
#define UART_DR_DATA_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_RSR UART_RSR
//! @{
//
//*****************************************************************************

//
//! UART Overrun Error
//
#define UART_RSR_OE             0x00000008  

//
//! UART Break Error
//
#define UART_RSR_BE             0x00000004  

//
//! UART Parity Error
//
#define UART_RSR_PE             0x00000002  

//
//! UART Framing Error
//
#define UART_RSR_FE             0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_ECR UART_ECR
//! @{
//
//*****************************************************************************

//
//! UART Overrun Error
//
#define UART_ECR_OE             0x00000008  

//
//! UART Break Error
//
#define UART_ECR_BE             0x00000004  

//
//! UART Parity Error
//
#define UART_ECR_PE             0x00000002  

//
//! UART Framing Error
//
#define UART_ECR_FE             0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_FR UART_FR
//! @{
//
//*****************************************************************************

//
//! Ring Indicator
//
#define UART_FR_RI              0x00000100  

//
//! UART Transmit FIFO Empty
//
#define UART_FR_TXFE            0x00000080  

//
//! UART Receive FIFO Full
//
#define UART_FR_RXFF            0x00000040  

//
//! UART Transmit FIFO Full
//
#define UART_FR_TXFF            0x00000020  

//
//! UART Receive FIFO Empty
//
#define UART_FR_RXFE            0x00000010  

//
//! UART Busy
//
#define UART_FR_BUSY            0x00000008  

//
//! Data Carrier Detect
//
#define UART_FR_DCD             0x00000004  

//
//! Data Set Ready
//
#define UART_FR_DSR             0x00000002  

//
//! Clear To Send
//
#define UART_FR_CTS             0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_ILPR UART_ILPR
//! @{
//
//*****************************************************************************

//
//! IrDA Low-Power Divisor Mask
//
#define UART_ILPR_ILPDVSR_M     0x000000FF  

//
//! IrDA Low-Power Divisor Start Bit
//
#define UART_ILPR_ILPDVSR_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_IBRD UART_IBRD
//! @{
//
//*****************************************************************************

//
//! Integer Baud-Rate Divisor
//
#define UART_IBRD_DIVINT_M      0x0000FFFF  
#define UART_IBRD_DIVINT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_FBRD UART_FBRD
//! @{
//
//*****************************************************************************

//
//! Fractional Baud-Rate Divisor
//
#define UART_FBRD_DIVFRAC_M     0x0000003F  
#define UART_FBRD_DIVFRAC_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_LCRH UART_LCRH
//! @{
//
//*****************************************************************************

//
//! UART Stick Parity Select
//
#define UART_LCRH_SPS           0x00000080  

//
//! UART Word Length
//
#define UART_LCRH_WLEN_M        0x00000060  

//
//! 5 bits (default)
//
#define UART_LCRH_WLEN_5        0x00000000  

//
//! 6 bits
//
#define UART_LCRH_WLEN_6        0x00000020  

//
//! 7 bits
//
#define UART_LCRH_WLEN_7        0x00000040  

//
//! 8 bits
//
#define UART_LCRH_WLEN_8        0x00000060  

//
//! UART Enable FIFOs
//
#define UART_LCRH_FEN           0x00000010  

//
//! UART Two Stop Bits Select
//
#define UART_LCRH_STP2          0x00000008  

//
//! UART Even Parity Select
//
#define UART_LCRH_EPS           0x00000004  

//
//! UART Parity Enable
//
#define UART_LCRH_PEN           0x00000002  

//
//! UART Send Break
//
#define UART_LCRH_BRK           0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_CTL UART_CTL
//! @{
//
//*****************************************************************************

//
//! Enable Clear To Send
//
#define UART_CTL_CTSEN          0x00008000  

//
//! Enable Request to Send
//
#define UART_CTL_RTSEN          0x00004000  

//
//! Request to Send
//
#define UART_CTL_RTS            0x00000800  

//
//! Data Terminal Ready
//
#define UART_CTL_DTR            0x00000400  

//
//! UART Receive Enable
//
#define UART_CTL_RXE            0x00000200  

//
//! UART Transmit Enable
//
#define UART_CTL_TXE            0x00000100  

//
//! UART Loop Back Enable
//
#define UART_CTL_LBE            0x00000080  

//
//! LIN Mode Enable
//
#define UART_CTL_LIN            0x00000040  

//
//! High-Speed Enable
//
#define UART_CTL_HSE            0x00000020  

//
//! End of Transmission
//
#define UART_CTL_EOT            0x00000010  

//
//! ISO 7816 Smart Card Support
//
#define UART_CTL_SMART          0x00000008  

//
//! UART SIR Low-Power Mode
//
#define UART_CTL_SIRLP          0x00000004  

//
//! UART SIR Enable
//
#define UART_CTL_SIREN          0x00000002  

//
//! UART Enable
//
#define UART_CTL_UARTEN         0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_IFLS UART_IFLS
//! @{
//
//*****************************************************************************

//
//! UART Receive Interrupt FIFO Level Select
//
#define UART_IFLS_RX_M          0x00000038  

//
//! RX FIFO >= 1/8 full
//
#define UART_IFLS_RX1_8         0x00000000  

//
//! RX FIFO >= 1/4 full
//
#define UART_IFLS_RX2_8         0x00000008  

//
//! RX FIFO >= 1/2 full (default)
//
#define UART_IFLS_RX4_8         0x00000010  

//
//! RX FIFO >= 3/4 full
//
#define UART_IFLS_RX6_8         0x00000018  

//
//! RX FIFO >= 7/8 full
//
#define UART_IFLS_RX7_8         0x00000020  

//
//! UART Transmit Interrupt FIFO  Level Select
//
#define UART_IFLS_TX_M          0x00000007  

//
//! TX FIFO <= 1/8 full
//
#define UART_IFLS_TX1_8         0x00000000  

//
//! TX FIFO <= 1/4 full
//
#define UART_IFLS_TX2_8         0x00000001  

//
//! TX FIFO <= 1/2 full (default)
//
#define UART_IFLS_TX4_8         0x00000002  

//
//! TX FIFO <= 3/4 full
//
#define UART_IFLS_TX6_8         0x00000003  

//
//! TX FIFO <= 7/8 full
//
#define UART_IFLS_TX7_8         0x00000004  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_IM UART_IM
//! @{
//
//*****************************************************************************

//
//! LIN Mode Edge 5 Interrupt Mask
//
#define UART_IM_LME5IM          0x00008000  

//
//! LIN Mode Edge 1 Interrupt Mask
//
#define UART_IM_LME1IM          0x00004000  

//
//! LIN Mode Sync Break Interrupt Mask
//
#define UART_IM_LMSBIM          0x00002000  

//
//! UART Overrun Error Interrupt Mask
//
#define UART_IM_OEIM            0x00000400  

//
//! UART Break Error Interrupt Mask
//
#define UART_IM_BEIM            0x00000200  

//
//! UART Parity Error Interrupt Mask
//
#define UART_IM_PEIM            0x00000100  

//
//! UART Framing Error Interrupt Mask
//
#define UART_IM_FEIM            0x00000080  

//
//! UART Receive Time-Out Interrupt Mask
//
#define UART_IM_RTIM            0x00000040  

//
//! UART Transmit Interrupt Mask
//
#define UART_IM_TXIM            0x00000020  

//
//! UART Receive Interrupt Mask
//
#define UART_IM_RXIM            0x00000010  

//
//! UART Data Set Ready Modem Interrupt Mask
//
#define UART_IM_DSRMIM          0x00000008  

//
//! UART Data Carrier Detect Modem Interrupt Mask 
//
#define UART_IM_DCDMIM          0x00000004  

//
//! UART Clear to Send Modem Interrupt Mask
//
#define UART_IM_CTSMIM          0x00000002  

//
//! UART Ring Indicator Modem Interrupt Mask
//
#define UART_IM_RIMIM           0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_RIS UART_RIS
//! @{
//
//*****************************************************************************

//
//! LIN Mode Edge 5 Raw Interrupt Status
//
#define UART_RIS_LME5RIS        0x00008000  

//
//! LIN Mode Edge 1 Raw Interrupt Status
//
#define UART_RIS_LME1RIS        0x00004000  

//
//! LIN Mode Sync Break Raw Interrupt Status
//
#define UART_RIS_LMSBRIS        0x00002000  

//
//! UART Overrun Error Raw Interrupt Status
//
#define UART_RIS_OERIS          0x00000400  

//
//! UART Break Error Raw Interrupt Status
//
#define UART_RIS_BERIS          0x00000200  

//
//! UART Parity Error Raw Interrupt Status
//
#define UART_RIS_PERIS          0x00000100  

//
//! UART Framing Error Raw Interrupt Status
//
#define UART_RIS_FERIS          0x00000080  

//
//! UART Receive Time-Out Raw Interrupt Status
//
#define UART_RIS_RTRIS          0x00000040  

//
//! UART Transmit Raw Interrupt Status
//
#define UART_RIS_TXRIS          0x00000020  

//
//! UART Receive Raw Interrupt Status
//
#define UART_RIS_RXRIS          0x00000010  

//
//! UART Data Set Ready Modem Raw Interrupt Status
//
#define UART_RIS_DSRRIS         0x00000008  

//
//! UART Data Carrier Detect Modem Raw Interrupt Status
//
#define UART_RIS_DCDRIS         0x00000004  

//
//! UART Clear to Send Modem Raw Interrupt Status
//
#define UART_RIS_CTSRIS         0x00000002  

//
//! UART Ring Indicator Modem Raw Interrupt Status
//
#define UART_RIS_RIRIS          0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_MIS UART_MIS
//! @{
//
//*****************************************************************************

//
//! LIN Mode Edge 5 Masked Interrupt Status
//
#define UART_MIS_LME5MIS        0x00008000  

//
//! LIN Mode Edge 1 Masked Interrupt Status
//
#define UART_MIS_LME1MIS        0x00004000  

//
//! LIN Mode Sync Break Masked Interrupt Status
//
#define UART_MIS_LMSBMIS        0x00002000  

//
//! UART Overrun Error Masked Interrupt Status
//
#define UART_MIS_OEMIS          0x00000400  

//
//! UART Break Error Masked Interrupt Status
//
#define UART_MIS_BEMIS          0x00000200  

//
//! UART Parity Error Masked Interrupt Status
//
#define UART_MIS_PEMIS          0x00000100  

//
//! UART Framing Error Masked Interrupt Status
//
#define UART_MIS_FEMIS          0x00000080  

//
//! UART Receive Time-Out Masked Interrupt Status
//
#define UART_MIS_RTMIS          0x00000040  

//
//! UART Transmit Masked Interrupt Status
//
#define UART_MIS_TXMIS          0x00000020  

//
//! UART Receive Masked Interrupt Status
//
#define UART_MIS_RXMIS          0x00000010  

//
//! UART Data Set Ready Modem Masked Interrupt Status
//
#define UART_MIS_DSRMIS         0x00000008  

//
//! UART Data Carrier Detect Modem Masked Interrupt Status
//
#define UART_MIS_DCDMIS         0x00000004  

//
//! UART Clear to Send Modem Masked Interrupt Status
//
#define UART_MIS_CTSMIS         0x00000002  

//
//! UART Ring Indicator Modem Masked Interrupt Status
//
#define UART_MIS_RIMIS          0x00000001  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_ICR UART_ICR
//! @{
//
//*****************************************************************************

//
//! LIN Mode Edge 5 Interrupt Clear
//
#define UART_ICR_LME5MIC        0x00008000  

//
//! LIN Mode Edge 1 Interrupt Clear
//
#define UART_ICR_LME1MIC        0x00004000  

//
//! LIN Mode Sync Break Interrupt Clear
//
#define UART_ICR_LMSBMIC        0x00002000  

//
//! Overrun Error Interrupt Clear
//
#define UART_ICR_OEIC           0x00000400  

//
//! Break Error Interrupt Clear
//
#define UART_ICR_BEIC           0x00000200  

//
//! Parity Error Interrupt Clear
//
#define UART_ICR_PEIC           0x00000100  

//
//! Framing Error Interrupt Clear
//
#define UART_ICR_FEIC           0x00000080  

//
//! Receive Time-Out Interrupt Clear
//
#define UART_ICR_RTIC           0x00000040  

//
//! Transmit Interrupt Clear
//
#define UART_ICR_TXIC           0x00000020  

//
//! Receive Interrupt Clear
//
#define UART_ICR_RXIC           0x00000010  

//
//! UART Data Set Ready Modem Interrupt Clear
//
#define UART_ICR_DSRMIC         0x00000008  

//
//! UART Data Carrier Detect Modem Interrupt Clear
//
#define UART_ICR_DCDMIC         0x00000004  

//
//! UART Clear to Send Modem Interrupt Clear
//
#define UART_ICR_CTSMIC         0x00000002  

//
//! UART Ring Indicator Modem Interrupt Clear
//
#define UART_ICR_RIMIC          0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_DMACTL UART_DMACTL
//! @{
//
//*****************************************************************************

//
//! DMA on Error
//
#define UART_DMACTL_DMAERR      0x00000004  

//
//! Transmit DMA Enable
//
#define UART_DMACTL_TXDMAE      0x00000002  

//
//! Receive DMA Enable
//
#define UART_DMACTL_RXDMAE      0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_LCTL UART_LCTL
//! @{
//
//*****************************************************************************

//
//! Sync Break Length
//
#define UART_LCTL_BLEN_M        0x00000030  

//
//! Sync break length is 13T bits (default)
//
#define UART_LCTL_BLEN_13T      0x00000000  

//
//! Sync break length is 14T bits
//
#define UART_LCTL_BLEN_14T      0x00000010  

//
//! Sync break length is 15T bits
//
#define UART_LCTL_BLEN_15T      0x00000020  

//
//! Sync break length is 16T bits
//
#define UART_LCTL_BLEN_16T      0x00000030  

//
//! LIN Master Enable
//
#define UART_LCTL_MASTER        0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_LSS UART_LSS
//! @{
//
//*****************************************************************************

//
//! Timer Snap Shot
//
#define UART_LSS_TSS_M          0x0000FFFF
#define UART_LSS_TSS_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UART_LTIM UART_LTIM
//! @{
//
//*****************************************************************************

//
//! Timer Value Mask
//
#define UART_LTIM_TIMER_M       0x0000FFFF  
#define UART_LTIM_TIMER_S       0

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

#endif // __xHW_UART_H__

