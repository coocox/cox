//*****************************************************************************
//
//! \file NandFlash.h
//! \brief Prototypes for the NandFlash driver
//! \version V0.0.1
//! \date 2/5/2013
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2013, CooCoX All rights reserved.
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
#ifndef __NANDFLSAH_H__
#define __NANDFLSAH_H__

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
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup Memory
//! @{
//! \addtogroup NandFlash
//! @{
//! \addtogroup NandFlash_Driver_Single
//! @{
//! \addtogroup NandFlash_Pins NAND Flash Pins Connect
//! @{
//
//*****************************************************************************
#define NF_CLE_PIN		PD6
#define NF_ALE_PIN		PD5
#define NF_NWE_PIN		PD14
#define NF_NRE_PIN		PD15
#define NF_NCE_PIN		PD7
#define NF_NWP_PIN		PD10
#define NF_RNB_PIN		PB5

//
//! Support 8 bit Data IO interface
//
#define NF_DB0_PIN		PE0
#define NF_DB1_PIN		PE1
#define NF_DB2_PIN		PE2
#define NF_DB3_PIN		PE3
#define NF_DB4_PIN		PE4
#define NF_DB5_PIN		PE5
#define NF_DB6_PIN		PE6
#define NF_DB7_PIN		PE7

#define SEQUENCE_PIN_MODE

#ifdef SEQUENCE_PIN_MODE
#define NF_DATA_PORT	xGPIO_PORTE_BASE
//
//! NF_DATA_MASK is the mask of data port
// It is only effective when the data bus lines are connected to
// one port from GPIO 0~7.  
//
#define NF_DATA_MASK	0x00FF
#endif
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NandFlash_Character NAND Flash Character
//! \note Modify these parameter as your chip character
//! @{
//
//*****************************************************************************
#define NF_PAGE_SIZE        0x800       // 2048Bytes (Do not count redundant area!)
#define NF_BLOCK_SIZE       0x20000     // 64KBytes  (Do not count redundant area!)
#define NF_DEVICE_SIZE      0x8000000   // 128MBytes (Do not count redundant area!)
#define NF_SPARE_AREA_SIZE  64          // 64Bytes

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NandFlash_Info NAND Flash Information Structure
//! @{
//
//*****************************************************************************
typedef struct
{
	unsigned short usNandFlashID;
	unsigned char ucNandCharacter;
	unsigned long ulPageSize;
	unsigned long ulBlockSize;
//	unsigned long ulCapacity;
	unsigned char ucRDDTAreaSize;
}NandFlashInfo;

extern NandFlashInfo NandInfo;
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NandFlash_APIs NAND Flash Driver APIs
//! @{
//
//*****************************************************************************
extern void NFInit(void);
extern unsigned char NFStatusRead(void);
extern unsigned char NFBlockErase(unsigned long ulBlockAddr);
extern unsigned char NFPageRead(unsigned long ulPageAddr, unsigned char *pBuffer);
extern unsigned char NFPageCopy(unsigned long ulSrcPageAddr, unsigned long ulDestPageAddr);
extern unsigned char NFPageWrite(unsigned long ulPageAddr, unsigned char *pBuffer);
extern unsigned char NFBytesRead(unsigned long ulAddr, unsigned char *pBuffer, unsigned long ulLength);
extern unsigned char NFPageOffsetRead(unsigned short usOffSet,
                               unsigned long ulPageAddr,
                               unsigned char *pBuffer,
                               unsigned short usBytesToRead);
//*****************************************************************************
//
//! @}
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
