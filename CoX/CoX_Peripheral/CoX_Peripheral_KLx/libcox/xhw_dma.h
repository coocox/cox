//*****************************************************************************
//
//! \file xhw_dma.h
//! \brief Macros for use in accessing the DMA registers.
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

#ifndef __xHW_DMA_H__
#define __xHW_DMA_H__

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
//! \addtogroup KLx_DMA_Register
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_DMA_Register_Map DMA Register Map(Address)
//! @{
//
//*****************************************************************************

//
//! DMA Channel n Source Address register (32-bit)
//
#define DMA_SAR                 0x00000000 

//
//! DMA Channel n Destination Address register (32-bit)
//
#define DMA_DAR                 0x00000004

//
//! DMA Channel n Status/Byte-Count register (32-bit)
//
#define DMA_DSR_BCR             0x00000008

//
//! DMA Channel n Control register (32-bit)
//
#define DMA_DCR                 0x0000000C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_DMA_Register_DMAMUX0_CHCFG DMA Channel n(0~3) Configuration register(DMAMUX0_CHCFGn)
//! @{
//
//*****************************************************************************

//
//! DMA Channel n Enable
//
#define DMAMUX0_CHCFG_ENBL      0x80

//
//! DMA Channel n Trigger Enable
//
#define DMAMUX0_CHCFG_TRIG      0x40

//
//! DMA Channel n Source(Slot) mask
//
#define DMAMUX0_CHCFG_SOURCE_M  0x3F

//
//! DMA Channel n Source(Slot) shift
//
#define DMAMUX0_CHCFG_SOURCE_S  0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_DMA_Register_DMA_SAR DMA Channel n(0~3) Source Address register(DMA_SARn)
//! @{
//
//*****************************************************************************

//
//! DMA Channel n Source Address mask
//
#define DMA_SAR_SAR_M           0x00FFFFFF

//
//! DMA Channel n Source Address shift
//
#define DMA_SAR_SAR_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_DMA_Register_DMA_DAR DMA Channel n(0~3) Destination Address register(DMA_DARn)
//! @{
//
//*****************************************************************************

//
//! DMA Channel n Destination Address mask
//
#define DMA_DAR_DAR_M           0x00FFFFFF

//
//! DMA Channel n Destination Address shift
//
#define DMA_DAR_DAR_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_DMA_Register_DMA_DSR_BCR DMA Channel n(0~3) Status/Byte-Count register(DMA_DSR_BCRn)
//! @{
//
//*****************************************************************************

//
//! DMA Configuration error
//
#define DMA_DSR_BCR_CE          0x40000000

//
//! DMA Bus error on source
//
#define DMA_DSR_BCR_BES         0x20000000

//
//! DMA Bus error on Destination
//
#define DMA_DSR_BCR_BED         0x10000000

//
//! DMA Request
//
#define DMA_DSR_BCR_REQ         0x04000000

//
//! DMA Busy
//
#define DMA_DSR_BCR_BSY         0x02000000

//
//! DMA Transactions done
//
#define DMA_DSR_BCR_DONE        0x01000000

//
//! The number of bytes yet to be transferred for a given block mask
//
#define DMA_DSR_BCR_BCR_M       0x000FFFFF

//
//! The number of bytes yet to be transferred for a given block shift
//
#define DMA_DSR_BCR_BCR_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_DMA_Register_DMA_DCR DMA Channel n(0~3) Control register(DMA_DCRn)
//! @{
//
//*****************************************************************************

//
//! Enable interrupt on completion of transfer
//
#define DMA_DCR_EINT            0x80000000

//
//! Enable  peripheral request
//
#define DMA_DCR_ERQ             0x40000000

//
//! Cycle steal
//
#define DMA_DCR_CS              0x20000000

//
//! Auto-align
//
#define DMA_DCR_AA              0x10000000

//
//! Enable asynchronous DMA requests
//
#define DMA_DCR_EADREQ          0x00800000

//
//! Source increment
//
#define DMA_DCR_SINC            0x00400000

//
//! Source size mask
//
#define DMA_DCR_SSIZE_M         0x00300000

//
//! Source size shift
//
#define DMA_DCR_SSIZE_S         20

//
//! Destination increment
//
#define DMA_DCR_DINC            0x00080000

//
//! Destination size mask
//
#define DMA_DCR_DSIZE_M         0x00060000

//
//! Destination size shift
//
#define DMA_DCR_DSIZE_S         17

//
//! DMA Start transfer
//
#define DMA_DCR_START           0x00010000

//
//! Source address modulo mask
//
#define DMA_DCR_SMOD_M          0x0000F000

//
//! Source address modulo shift
//
#define DMA_DCR_SMOD_S          12

//
//! Destination address modulo mask
//
#define DMA_DCR_DMOD_M          0x00000F00

//
//! Destination address modulo shift
//
#define DMA_DCR_DMOD_S          8

//
//! DMA Disable request
//
#define DMA_DCR_D_REQ           0x00000080

//
//! Link channel control mask
//
#define DMA_DCR_LINKCC_M        0x00000030

//
//! Link channel control shift
//
#define DMA_DCR_LINKCC_S        4

//
//! Link channel 1 mask
//
#define DMA_DCR_LCH1_M          0x0000000C

//
//! Link channel 1 shift
//
#define DMA_DCR_LCH1_S          2

//
//! Link channel 2 mask
//
#define DMA_DCR_LCH2_M          0x00000003

//
//! Link channel 2 shift
//
#define DMA_DCR_LCH2_S          0

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
