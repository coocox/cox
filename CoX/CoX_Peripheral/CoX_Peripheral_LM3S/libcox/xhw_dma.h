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
//! \addtogroup Stellaris_DMA_Register
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Register_Map UDMA Register Map(Address)
//! @{
//
//*****************************************************************************

#define UDMA_STAT               0x400FF000  // DMA Status
#define UDMA_CFG                0x400FF004  // DMA Configuration
#define UDMA_CTLBASE            0x400FF008  // DMA Channel Control Base Pointer
#define UDMA_ALTBASE            0x400FF00C  // DMA Alternate Channel Control
                                            // Base Pointer
#define UDMA_WAITSTAT           0x400FF010  // DMA Channel Wait-on-Request
                                            // Status
#define UDMA_SWREQ              0x400FF014  // DMA Channel Software Request
#define UDMA_USEBURSTSET        0x400FF018  // DMA Channel Useburst Set
#define UDMA_USEBURSTCLR        0x400FF01C  // DMA Channel Useburst Clear
#define UDMA_REQMASKSET         0x400FF020  // DMA Channel Request Mask Set
#define UDMA_REQMASKCLR         0x400FF024  // DMA Channel Request Mask Clear
#define UDMA_ENASET             0x400FF028  // DMA Channel Enable Set
#define UDMA_ENACLR             0x400FF02C  // DMA Channel Enable Clear
#define UDMA_ALTSET             0x400FF030  // DMA Channel Primary Alternate
                                            // Set
#define UDMA_ALTCLR             0x400FF034  // DMA Channel Primary Alternate
                                            // Clear
#define UDMA_PRIOSET            0x400FF038  // DMA Channel Priority Set
#define UDMA_PRIOCLR            0x400FF03C  // DMA Channel Priority Clear
#define UDMA_ERRCLR             0x400FF04C  // DMA Bus Error Clear
#define UDMA_CHASGN             0x400FF500  // DMA Channel Assignment

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_STAT UDMA_STAT
//! @{
//
//*****************************************************************************

#define UDMA_STAT_DMACHANS_M    0x001F0000  // Available uDMA Channels Minus 1
#define UDMA_STAT_STATE_M       0x000000F0  // Control State Machine Status
#define UDMA_STAT_STATE_IDLE    0x00000000  // Idle
#define UDMA_STAT_STATE_RD_CTRL 0x00000010  // Reading channel controller data
#define UDMA_STAT_STATE_RD_SRCENDP \
                                0x00000020  // Reading source end pointer
#define UDMA_STAT_STATE_RD_DSTENDP \
                                0x00000030  // Reading destination end pointer
#define UDMA_STAT_STATE_RD_SRCDAT \
                                0x00000040  // Reading source data
#define UDMA_STAT_STATE_WR_DSTDAT \
                                0x00000050  // Writing destination data
#define UDMA_STAT_STATE_WAIT    0x00000060  // Waiting for uDMA request to
                                            // clear
#define UDMA_STAT_STATE_WR_CTRL 0x00000070  // Writing channel controller data
#define UDMA_STAT_STATE_STALL   0x00000080  // Stalled
#define UDMA_STAT_STATE_DONE    0x00000090  // Done
#define UDMA_STAT_STATE_UNDEF   0x000000A0  // Undefined
#define UDMA_STAT_MASTEN        0x00000001  // Master Enable Status
#define UDMA_STAT_DMACHANS_S    16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_CFG UDMA_CFG
//! @{
//
//*****************************************************************************

#define UDMA_CFG_MASTEN         0x00000001  // Controller Master Enable

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_CTLBASE UDMA_CTLBASE
//! @{
//
//*****************************************************************************

#define UDMA_CTLBASE_ADDR_M     0xFFFFFC00  // Channel Control Base Address
#define UDMA_CTLBASE_ADDR_S     10

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_ALTBASE UDMA_ALTBASE
//! @{
//
//*****************************************************************************

#define UDMA_ALTBASE_ADDR_M     0xFFFFFFFF  // Alternate Channel Address
                                            // Pointer
#define UDMA_ALTBASE_ADDR_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_WAITSTAT UDMA_WAITSTAT
//! @{
//
//*****************************************************************************

#define UDMA_WAITSTAT_WAITREQ_M 0xFFFFFFFF  // Channel [n] Wait Status

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_SWREQ UDMA_SWREQ
//! @{
//
//*****************************************************************************

#define UDMA_SWREQ_M            0xFFFFFFFF  // Channel [n] Software Request

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_USEBURSTSET UDMA_USEBURSTSET
//! @{
//
//*****************************************************************************

#define UDMA_USEBURSTSET_SET_M  0xFFFFFFFF  // Channel [n] Useburst Set

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_USEBURSTCLR UDMA_USEBURSTCLR
//! @{
//
//*****************************************************************************

#define UDMA_USEBURSTCLR_CLR_M  0xFFFFFFFF  // Channel [n] Useburst Clear

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_REQMASKSET UDMA_REQMASKSET
//! @{
//
//*****************************************************************************

#define UDMA_REQMASKSET_SET_M   0xFFFFFFFF  // Channel [n] Request Mask Set

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_REQMASKCLR UDMA_REQMASKCLR
//! @{
//
//*****************************************************************************

#define UDMA_REQMASKCLR_CLR_M   0xFFFFFFFF  // Channel [n] Request Mask Clear

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_ENASET UDMA_ENASET
//! @{
//
//*****************************************************************************

#define UDMA_ENASET_SET_M       0xFFFFFFFF  // Channel [n] Enable Set

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_ENACLR UDMA_ENACLR
//! @{
//
//*****************************************************************************

#define UDMA_ENACLR_CLR_M       0xFFFFFFFF  // Clear Channel [n] Enable Clear

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_ALTSET UDMA_ALTSET
//! @{
//
//*****************************************************************************

#define UDMA_ALTSET_SET_M       0xFFFFFFFF  // Channel [n] Alternate Set

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_ALTCLR UDMA_ALTCLR
//! @{
//
//*****************************************************************************

#define UDMA_ALTCLR_CLR_M       0xFFFFFFFF  // Channel [n] Alternate Clear

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_PRIOSET UDMA_PRIOSET
//! @{
//
//*****************************************************************************

#define UDMA_PRIOSET_SET_M      0xFFFFFFFF  // Channel [n] Priority Set

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_PRIOCLR UDMA_PRIOCLR
//! @{
//
//*****************************************************************************

#define UDMA_PRIOCLR_CLR_M      0xFFFFFFFF  // Channel [n] Priority Clear

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_ERRCLR UDMA_ERRCLR
//! @{
//
//*****************************************************************************

#define UDMA_ERRCLR_ERRCLR      0x00000001  // uDMA Bus Error Status

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_CHASGN UDMA_CHASGN
//! @{
//
//*****************************************************************************

#define UDMA_CHASGN_M           0xFFFFFFFF  // Channel [n] Assignment Select
#define UDMA_CHASGN_PRIMARY     0x00000000  // Use the primary channel
                                            // assignment
#define UDMA_CHASGN_SECONDARY   0x00000001  // Use the secondary channel
                                            // assignment

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_Offset uDMA Register Offsets
//! @{
//
//*****************************************************************************

#define UDMA_O_SRCENDP          0x00000000  // DMA Channel Source Address End
                                            // Pointer
#define UDMA_O_DSTENDP          0x00000004  // DMA Channel Destination Address
                                            // End Pointer
#define UDMA_O_CHCTL            0x00000008  // DMA Channel Control Word

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_O_SRCENDP UDMA_O_SRCENDP
//! @{
//
//*****************************************************************************

#define UDMA_SRCENDP_ADDR_M     0xFFFFFFFF  // Source Address End Pointer
#define UDMA_SRCENDP_ADDR_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_O_DSTENDP UDMA_O_DSTENDP
//! @{
//
//*****************************************************************************

#define UDMA_DSTENDP_ADDR_M     0xFFFFFFFF  // Destination Address End Pointer
#define UDMA_DSTENDP_ADDR_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_UDMA_O_CHCTL UDMA_O_CHCTL
//! @{
//
//*****************************************************************************

#define UDMA_CHCTL_DSTINC_M     0xC0000000  // Destination Address Increment
#define UDMA_CHCTL_DSTINC_8     0x00000000  // Byte
#define UDMA_CHCTL_DSTINC_16    0x40000000  // Half-word
#define UDMA_CHCTL_DSTINC_32    0x80000000  // Word
#define UDMA_CHCTL_DSTINC_NONE  0xC0000000  // No increment
#define UDMA_CHCTL_DSTSIZE_M    0x30000000  // Destination Data Size
#define UDMA_CHCTL_DSTSIZE_8    0x00000000  // Byte
#define UDMA_CHCTL_DSTSIZE_16   0x10000000  // Half-word
#define UDMA_CHCTL_DSTSIZE_32   0x20000000  // Word
#define UDMA_CHCTL_SRCINC_M     0x0C000000  // Source Address Increment
#define UDMA_CHCTL_SRCINC_8     0x00000000  // Byte
#define UDMA_CHCTL_SRCINC_16    0x04000000  // Half-word
#define UDMA_CHCTL_SRCINC_32    0x08000000  // Word
#define UDMA_CHCTL_SRCINC_NONE  0x0C000000  // No increment
#define UDMA_CHCTL_SRCSIZE_M    0x03000000  // Source Data Size
#define UDMA_CHCTL_SRCSIZE_8    0x00000000  // Byte
#define UDMA_CHCTL_SRCSIZE_16   0x01000000  // Half-word
#define UDMA_CHCTL_SRCSIZE_32   0x02000000  // Word
#define UDMA_CHCTL_ARBSIZE_M    0x0003C000  // Arbitration Size
#define UDMA_CHCTL_ARBSIZE_1    0x00000000  // 1 Transfer
#define UDMA_CHCTL_ARBSIZE_2    0x00004000  // 2 Transfers
#define UDMA_CHCTL_ARBSIZE_4    0x00008000  // 4 Transfers
#define UDMA_CHCTL_ARBSIZE_8    0x0000C000  // 8 Transfers
#define UDMA_CHCTL_ARBSIZE_16   0x00010000  // 16 Transfers
#define UDMA_CHCTL_ARBSIZE_32   0x00014000  // 32 Transfers
#define UDMA_CHCTL_ARBSIZE_64   0x00018000  // 64 Transfers
#define UDMA_CHCTL_ARBSIZE_128  0x0001C000  // 128 Transfers
#define UDMA_CHCTL_ARBSIZE_256  0x00020000  // 256 Transfers
#define UDMA_CHCTL_ARBSIZE_512  0x00024000  // 512 Transfers
#define UDMA_CHCTL_ARBSIZE_1024 0x00028000  // 1024 Transfers
#define UDMA_CHCTL_XFERSIZE_M   0x00003FF0  // Transfer Size (minus 1)
#define UDMA_CHCTL_NXTUSEBURST  0x00000008  // Next Useburst
#define UDMA_CHCTL_XFERMODE_M   0x00000007  // uDMA Transfer Mode
#define UDMA_CHCTL_XFERMODE_STOP \
                                0x00000000  // Stop
#define UDMA_CHCTL_XFERMODE_BASIC \
                                0x00000001  // Basic
#define UDMA_CHCTL_XFERMODE_AUTO \
                                0x00000002  // Auto-Request
#define UDMA_CHCTL_XFERMODE_PINGPONG \
                                0x00000003  // Ping-Pong
#define UDMA_CHCTL_XFERMODE_MEM_SG \
                                0x00000004  // Memory Scatter-Gather
#define UDMA_CHCTL_XFERMODE_MEM_SGA \
                                0x00000005  // Alternate Memory Scatter-Gather
#define UDMA_CHCTL_XFERMODE_PER_SG \
                                0x00000006  // Peripheral Scatter-Gather
#define UDMA_CHCTL_XFERMODE_PER_SGA \
                                0x00000007  // Alternate Peripheral
                                            // Scatter-Gather
#define UDMA_CHCTL_XFERSIZE_S   4

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

#endif // __xHW_DMA_H__
