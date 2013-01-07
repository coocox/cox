//*****************************************************************************
//
//! \file AT45DB161.h
//! \brief header file of Driver for AT45DB161
//! \version V2.1.1.0
//! \date 12/11/2012
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2012, CooCoX All rights reserved.
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

#ifndef __AT45DB161_H__
#define __AT45DB161_H__

#ifdef __cplusplus
extern "C"
{
#endif

    //
    //! User write protect config,it can be 0 or 1
    //! If you want to have hardware write protect, set it to 1
    //
#define AT45DB161_WRITE_PROTECT  1
#if (AT45DB161_WRITE_PROTECT < 1)
    //
    //! Configure GPIOB.12 as Write Protect Pin
    //
#define FLASH_PIN_WRITE_PROTECT PB12

#endif

    //
    //! Modify the pin configuration to transplant the code to your application
    //
#define AT45DB161_CS_PORT      GPIOC_BASE
#define AT45DB161_CS_PIN       PC7
#define AT45DB161_SPI_PORT     SPI2_BASE
#define AT45DB161_SCK          PB13
#define AT45DB161_MISO         PB14
#define AT45DB161_MOSI         PB15
#define SPI_CLK                SPI2CLK(APP)
#define SPI_MOSI               SPI2MOSI(APP)
#define SPI_MISO               SPI2MISO(FIN)

    //
    //! Be aware, if you have enabled the write protect character,
    //! some function may be blocked like write and erase operation.
    //
    extern void AT45DB161_Init(unsigned long ulSpiClock);
    extern unsigned char AT45DB161_GetState(void);
    extern void AT45DB161_GetChipID(unsigned char *pucBuf);
    extern void AT45DB161_Buf_to_Mm(unsigned char ucBufferNum, unsigned short usPageAddr);
    extern void AT45DB161_Mm_to_Buf(unsigned char ucBufferNum, unsigned short usPageAddr);
    extern void AT45DB161_PageRead(unsigned char *pucBuffer, unsigned short usPageAddr, unsigned long ulNumByteToWrite);
    extern void AT45DB161_ReadBuffer(unsigned char ucBufferNum, unsigned char *pucBuffer,
                                     unsigned long ulReadAddr, unsigned long ulNumByteToRead);
    extern void AT45DB161_WriteBuffer(unsigned char ucBufferNum, unsigned char *pucBuffer,
                                      unsigned long ulWriteAddr, unsigned long ulNumByteToWrite);
    extern void AT45DB161_Read(unsigned char *pucBuffer, unsigned long ulReadAddr, unsigned long ulNumByteToRead);
    extern void AT45DB161_Write(unsigned char *pucBuffer, unsigned long ulWriteAddr, unsigned long ulNumByteToWrite);
    extern void AT45DB161_ErasePage(unsigned short ulPageAddr);
    extern void AT45DB161_EraseBlock(unsigned short ulBlockAddr);
    extern void AT45DB161_EraseSector(unsigned char ulSectorAddr);
    extern void AT45DB161_SectorProtectionEn(void);
    extern void AT45DB161_SectorProtectionDi(void);
    extern void AT45DB161_ProgSecProtReg(unsigned char *pucSectors);
    extern void AT45DB161_RdSecProtReg(unsigned char *pucSectors);
    extern void AT45DB161_EraseChip(void);

#if (AT45DB161_WRITE_PROTECT < 1)
    extern void AT45DB161_WriteProtectDisable(void);
    extern void AT45DB161_WriteProtectEnable(void);
#endif

#ifdef __cplusplus
}
#endif

#endif //__AT45DB161_H__

