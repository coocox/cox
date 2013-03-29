//*****************************************************************************
//
//! \file xhw_dma.h
//! \brief Macros used when accessing the DMA hardware.
//! \version V2.2.1.0
//! \date 01/05/2012
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


#ifndef __XHW_DMA_H__
#define __XHW_DMA_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DMA
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register  STM32F1xx DMA Register
//! \brief Here are the detailed info of DMA registers.  
//!
//! it contains:
//! - Register offset.
//! - Detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register_Offsets DMA Register Offsets(Map)
//! \brief Here is the DMA register offset, users can get the register address
//! through <b>DMA_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! DMA interrupt status register.
//
#define DMA_ISR                 0x00000000 

//
//! DMA interrupt flag clear register.
//
#define DMA_IFCR                0x00000004

//
//! DMA channel 1 configuration register.
//
#define DMA_CCR1                0x00000008

//
//! DMA channel 1 number of data register.
//
#define DMA_CNDTR1              0x0000000C

//
//! DMA channel 1 peripheral address register.
//
#define DMA_CPAR1               0x00000010

//
//! DMA channel 1 memory address register.
//
#define DMA_CMAR1               0x00000014

//
//! DMA channel 2 configuration register.
//
#define DMA_CCR2                0x0000001C

//
//! DMA channel 2 number of data register.
//
#define DMA_CNDTR2              0x00000020

//
//! DMA channel 2 peripheral address register.
//
#define DMA_CPAR2               0x00000024

//
//! DMA channel 2 memory address register.
//
#define DMA_CMAR2               0x00000028

//
//! DMA channel 3 configuration register.
//
#define DMA_CCR3                0x00000030

//
//! DMA channel 3 number of data register.
//
#define DMA_CNDTR3              0x00000034

//
//! DMA channel 3 peripheral address register.
//
#define DMA_CPAR3               0x00000038

//
//! DMA channel 3 memory address register.
//
#define DMA_CMAR3               0x0000003C

//
//! DMA channel 4 configuration register.
//
#define DMA_CCR4                0x00000044

//
//! DMA channel 4 number of data register.
//
#define DMA_CNDTR4              0x00000048

//
//! DMA channel 4 peripheral address register.
//
#define DMA_CPAR4               0x0000004C

//
//! DMA channel 4 memory address register.
//
#define DMA_CMAR4               0x00000050

//
//! DMA channel 5 configuration register.
//
#define DMA_CCR5                0x00000058

//
//! DMA channel 5 number of data register.
//
#define DMA_CNDTR5              0x0000005C

//
//! DMA channel 5 peripheral address register.
//
#define DMA_CPAR5               0x00000060

//
//! DMA channel 5 memory address register.
//
#define DMA_CMAR5               0x00000064

//
//! DMA channel 6 configuration register.
//
#define DMA_CCR6                0x0000006C

//
//! DMA channel 6 number of data register.
//
#define DMA_CNDTR6              0x00000070

//
//! DMA channel 6 peripheral address register.
//
#define DMA_CPAR6               0x00000074

//
//! DMA channel 6 memory address register.
//
#define DMA_CMAR6               0x00000078

//
//! DMA channel 7 configuration register.
//
#define DMA_CCR7                0x00000080

//
//! DMA channel 7 number of data register.
//
#define DMA_CNDTR7              0x00000084

//
//! DMA channel 7 peripheral address register.
//
#define DMA_CPAR7               0x00000088

//
//! DMA channel 7 memory address register.
//
#define DMA_CMAR7               0x0000008C


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register_DMA_ISR DMA interrupt status register(DMA_ISR) 
//! \brief Defines for the bit fields in the DMA_ISR register.
//! @{
//
//*****************************************************************************

//
//! Channel 7 transfer error flag
//
#define DMA_ISR_TEIF7           0x08000000

//
//! Channel 7 half transfer flag
//
#define DMA_ISR_HTIF7           0x04000000

//
//! Channel 7 transfer complete flag
//
#define DMA_ISR_TCIF7           0x02000000

//
//! Channel 7 global interrupt flag
//
#define DMA_ISR_GIF7            0x01000000

//
//! Channel 6 transfer error flag
//
#define DMA_ISR_TEIF6           0x00800000

//
//! Channel 6 half transfer flag
//
#define DMA_ISR_HTIF6           0x00400000

//
//! Channel 6 transfer complete flag
//
#define DMA_ISR_TCIF6           0x00200000

//
//! Channel 6 global interrupt flag
//
#define DMA_ISR_GIF6            0x00100000

//
//! Channel 5 transfer error flag
//
#define DMA_ISR_TEIF5           0x00080000

//
//! Channel 5 half transfer flag
//
#define DMA_ISR_HTIF5           0x00040000

//
//! Channel 5 transfer complete flag
//
#define DMA_ISR_TCIF5           0x00020000

//
//! Channel 5 global interrupt flag
//
#define DMA_ISR_GIF5            0x00010000

//
//! Channel 4 transfer error flag
//
#define DMA_ISR_TEIF4           0x00008000

//
//! Channel 4 half transfer flag
//
#define DMA_ISR_HTIF4           0x00004000

//
//! Channel 4 transfer complete flag
//
#define DMA_ISR_TCIF4           0x00002000

//
//! Channel 4 global interrupt flag
//
#define DMA_ISR_GIF4            0x00001000

//
//! Channel 3 transfer error flag
//
#define DMA_ISR_TEIF3           0x00000800

//
//! Channel 3 half transfer flag
//
#define DMA_ISR_HTIF3           0x00000400

//
//! Channel 3 transfer complete flag
//
#define DMA_ISR_TCIF3           0x00000200

//
//! Channel 3 global interrupt flag
//
#define DMA_ISR_GIF3            0x00000100

//
//! Channel 2 transfer error flag
//
#define DMA_ISR_TEIF2           0x00000080

//
//! Channel 2 half transfer flag
//
#define DMA_ISR_HTIF2           0x00000040

//
//! Channel 2 transfer complete flag
//
#define DMA_ISR_TCIF2           0x00000020

//
//! Channel 2 global interrupt flag
//
#define DMA_ISR_GIF2            0x00000010

//
//! Channel 1 transfer error flag
//
#define DMA_ISR_TEIF1           0x00000008

//
//! Channel 1 half transfer flag
//
#define DMA_ISR_HTIF1           0x00000004

//
//! Channel 1 transfer complete flag
//
#define DMA_ISR_TCIF1           0x00000002

//
//! Channel 1 global interrupt flag
//
#define DMA_ISR_GIF1            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register_DMA_IFCR DMA interrupt flag clear register(DMA_IFCR) 
//! \brief Defines for the bit fields in the DMA_IFCR register.
//! @{
//
//*****************************************************************************

//
//! Channel 7 transfer error clear
//
#define DMA_IFCR_CTEIF7         0x08000000

//
//! Channel 7 half transfer clear
//
#define DMA_IFCR_CHTIF7         0x04000000

//
//! Channel 7 transfer complete clear
//
#define DMA_IFCR_CTCIF7         0x02000000

//
//! Channel 7 global interrupt clear
//
#define DMA_IFCR_CGIF7          0x01000000

//
//! Channel 6 transfer error clear
//
#define DMA_IFCR_CTEIF6         0x00800000

//
//! Channel 6 half transfer clear
//
#define DMA_IFCR_CHTIF6         0x00400000

//
//! Channel 6 transfer complete clear
//
#define DMA_IFCR_CTCIF6         0x00200000

//
//! Channel 6 global interrupt clear
//
#define DMA_IFCR_CGIF6          0x00100000

//
//! Channel 5 transfer error clear
//
#define DMA_IFCR_CTEIF5         0x00080000

//
//! Channel 5 half transfer clear
//
#define DMA_IFCR_CHTIF5         0x00040000

//
//! Channel 5 transfer complete clear
//
#define DMA_IFCR_CTCIF5         0x00020000

//
//! Channel 5 global interrupt clear
//
#define DMA_IFCR_CGIF5          0x00010000

//
//! Channel 4 transfer error clear
//
#define DMA_IFCR_CTEIF4         0x00008000

//
//! Channel 4 half transfer clear
//
#define DMA_IFCR_CHTIF4         0x00004000

//
//! Channel 4 transfer complete clear
//
#define DMA_IFCR_CTCIF4         0x00002000

//
//! Channel 4 global interrupt clear
//
#define DMA_IFCR_CGIF4          0x00001000

//
//! Channel 3 transfer error clear
//
#define DMA_IFCR_CTEIF3         0x00000800

//
//! Channel 3 half transfer clear
//
#define DMA_IFCR_CHTIF3         0x00000400

//
//! Channel 3 transfer complete clear
//
#define DMA_IFCR_CTCIF3         0x00000200

//
//! Channel 3 global interrupt clear
//
#define DMA_IFCR_CGIF3          0x00000100

//
//! Channel 2 transfer error clear
//
#define DMA_IFCR_CTEIF2         0x00000080

//
//! Channel 2 half transfer clear
//
#define DMA_IFCR_CHTIF2         0x00000040

//
//! Channel 2 transfer complete clear
//
#define DMA_IFCR_CTCIF2         0x00000020

//
//! Channel 2 global interrupt clear
//
#define DMA_IFCR_CGIF2          0x00000010

//
//! Channel 1 transfer error clear
//
#define DMA_IFCR_CTEIF1         0x00000008

//
//! Channel 1 half transfer clear
//
#define DMA_IFCR_CHTIF1         0x00000004

//
//! Channel 1 transfer complete clear
//
#define DMA_IFCR_CTCIF1         0x00000002

//
//! Channel 1 global interrupt clear
//
#define DMA_IFCR_CGIF1          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register_DMA_CCR1 DMA channel 7 configuration register(DMA_CCR1) 
//! \brief Defines for the bit fields in the DMA_CCR1 register.
//! @{
//
//*****************************************************************************

//
//! Memory to memory mode
//
#define DMA_CCR1_MEM2MEM        0x00004000

//
//! Channel priority level mask
//
#define DMA_CCR1_PL_M           0x00003000

//
//! Channel priority level shift
//
#define DMA_CCR1_PL_S           12

//
//! Channel priority level Low
//
#define DMA_CCR1_PL_LOW         0x00000000

//
//! Channel priority level Medium
//
#define DMA_CCR1_PL_MED         0x00001000

//
//! Channel priority level High
//
#define DMA_CCR1_PL_HIGH        0x00002000

//
//! Channel priority level Very high
//
#define DMA_CCR1_PL_VHIGH       0x00003000

//
//! Memory size mask
//
#define DMA_CCR1_MSIZE_M        0x00000C00

//
//! Memory size shift
//
#define DMA_CCR1_MSIZE_S        10

//
//! Memory size 8-bits
//
#define DMA_CCR1_MSIZE_8B       0x00000000

//
//! Memory size 16-bits
//
#define DMA_CCR1_MSIZE_16B      0x00000400

//
//! Memory size 32-bits
//
#define DMA_CCR1_MSIZE_32B      0x00000800

//
//! Peripheral size mask
//
#define DMA_CCR1_PSIZE_M        0x00000300

//
//! Peripheral size shift
//
#define DMA_CCR1_PSIZE_S        8

//
//! Peripheral size 8-bits
//
#define DMA_CCR1_PSIZE_8B       0x00000000

//
//! Peripheral size 16-bits
//
#define DMA_CCR1_PSIZE_16B      0x00000100

//
//! Peripheral size 32-bits
//
#define DMA_CCR1_PSIZE_32B      0x00000200

//
//! Memory increment mode
//
#define DMA_CCR1_MINC           0x00000080

//
//! Peripheral increment mode
//
#define DMA_CCR1_PINC           0x00000040

//
//! Circular mode
//
#define DMA_CCR1_CIRC           0x00000020

//
//! Data transfer direction
//
#define DMA_CCR1_DIR            0x00000010

//
//! Transfer error interrupt enable
//
#define DMA_CCR1_TEIE           0x00000008

//
//! Half transfer interrupt enable
//
#define DMA_CCR1_HTIE           0x00000004

//
//! Transfer complete interrupt enable
//
#define DMA_CCR1_TCIE           0x00000002

//
//! Channel enable
//
#define DMA_CCR1_EN             0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register_DMA_CNDTR1 DMA channel 1 number of data register(DMA_CNDTR1) 
//! \brief Defines for the bit fields in the DMA_CNDTR1 register.
//! @{
//
//*****************************************************************************

//
//! DMA channel 1 number of data register mask
//
#define DMA_CNDTR1_NDT_M        0x0000FFFF

//
//! DMA channel 1 number of data register shift
//
#define DMA_CNDTR1_NDT_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register_DMA_CPAR1 DMA channel 1 peripheral address register 
//! \brief Defines for the bit fields in the DMA_CPAR1 register.
//! @{
//
//*****************************************************************************

//
//! DMA channel 1 peripheral address register mask
//
#define DMA_CPAR1_PA_M          0xFFFFFFFF

//
//! DMA channel 1 peripheral address register shift
//
#define DMA_CPAR1_PA_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_DMA_Register_DMA_CMAR1 DMA channel 1 memory address register 
//! \brief Defines for the bit fields in the DMA_CMAR1 register.
//! @{
//
//*****************************************************************************

//
//! DMA channel 1 memory address register mask
//
#define DMA_CMAR1_MA_M          0xFFFFFFFF

//
//! DMA channel 1 memory address register shift
//
#define DMA_CMAR1_MA_S          0

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
#endif // __XHW_DMA_H__



