//*****************************************************************************
//
//! \file SST25VFxx.h
//! \brief Prototypes for the SST25VFxx Driver.
//! \version V2.1.1.0
//! \date 9/22/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX 
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
//!
//*****************************************************************************
#ifndef __SST25VFxx_H__
#define __SST25VFxx_H__

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
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Memory
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup SPI_Flash
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SST25VFxx
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup SST25VFxx_Driver_Single
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//! \addtogroup SST25VFxx_User_Config
//! @{
//
//*****************************************************************************
  
//
//! User write protect config,it can be 0 or 1
//
#define SST25VFxx_WRITE_PROTECT    0
  
//
//! User hold input config,it can be 0 or 1
//
#define SST25VFxx_HOLD             0

//
//! User device config,it can only be M25P10 M25P20 M25P40 M25P80 M25P16 M25P32
//! M25P64 M25P128
// 
#define SST25VFxx_Device           SST25VF016B
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup SST25VFxx_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define SPIx as a port connecting SST25VFxx which can be configured
//
#define FLASH_PIN_SPI_CLK       PC1
#define SPI_CLK                 SPI1CLK  
#define FLASH_PIN_SPI_MISO      PC3
#define SPI_MISO                SPI1MISO
#define FLASH_PIN_SPI_MOSI      PC2
#define SPI_MOSI                SPI1MOSI
#define FLASH_PIN_SPI_PORT      SPI1_BASE
  
//
//! Configure GPIOC.0 as chip Select
//
#define FLASH_PIN_SPI_CS        PC0

#if (SST25VFxx_HOLD > 0)
//
//! Configure GPIOA.1 as hold in
//
#define FLASH_PIN_HOLD          PA1
  
#endif
 

#if (SST25VFxx_WRITE_PROTECT > 0)
//
//! Configure GPIOA.2 as hold in
//
#define FLASH_PIN_WRITE_PROTECT PA2 
  
#endif
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//! \addtogroup SST25VFxx_Id_Type
//! @{
//
//*****************************************************************************

//
//! Get Manufacturer¡¯s ID
//
#define SST25VFxx_ID_MANUF     0x00000000

//
//! Get Device ID
//
#define SST25VFxx_ID_DEVICE    0x00000001

//
//! Get both Device ID and Manufacturer¡¯s ID
//
#define SST25VFxx_ID_BOTH      0x00000010


//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup CoX_SST25VFxx_Exported_APIs
//! @{
//
//*****************************************************************************
extern void SST25VFxxInit(unsigned long ulSpiClock);
extern unsigned long SST25VFxxIDGet(unsigned long ulIDType);
extern unsigned long SST25VFxxJedecIDGet(void);
extern unsigned char SST25VFxxStatusRegRead(void);
extern void SST25VFxxWaitNotBusy(void);
extern void SST25VFxxWriteEnable(void);
extern void SST25VFxxWriteDisable(void);

extern void SST25VFxxByteWrite(unsigned long ulWriteAddr, unsigned char ucByte);
extern void SST25VFxxAAIWriteA(unsigned long ulWriteAddr, unsigned char ucByte1,
                               unsigned char ucByte2);
extern void SST25VFxxAAIWriteB(unsigned char ucByte1, unsigned char ucByte2);
extern void SST25VFxxAAIEBusyWriteA(unsigned long ulWriteAddr,
                                    unsigned char ucByte1,
                                    unsigned char ucByte2);
extern void SST25VFxxAAIEBusyWriteB(unsigned char ucByte1,
                                    unsigned char ucByte2);
extern void SST25VFxxWrite(unsigned char* pucBuffer, unsigned long  ulWriteAddr,
                           unsigned long usNumByteToWrite);

extern void SST25VFxxDataRead(unsigned char* ucBuffer,
                              unsigned long ulReadAddr,
                              unsigned long ulNumByteToRead);
extern void SST25VFxxDataFastRead(unsigned char* ucBuffer,
                                  unsigned long ulReadAddr,
                                  unsigned long ulNumByteToRead);

extern void SST25VFxxChipErase(void);
extern void SST25VFxxSectorErase(unsigned long ulDstAddr);
extern void SST25VFxxBlock32Erase(unsigned long ulDstAddr);
extern void SST25VFxxBlock64Erase(unsigned long ulDstAddr);
extern void SST25VFxxStatusRegWrite(unsigned char ucStatusVal);
extern void SST25VFxxDisable(void);
extern unsigned long SST25VFxxChipSizeGet(void);

#if (SST25VFxx_HOLD > 0)
extern void SST25VFxxHoldEnable(void);
extern void SST25VFxxHoldDisable(void);
#endif
 
#if (SST25VFxx_WRITE_PROTECT > 0)
extern void SST25VFxxWriteProtectEnable(void);
extern void SST25VFxxWriteProtectDisable(void);
#endif


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
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__SST25VFxx_H__
