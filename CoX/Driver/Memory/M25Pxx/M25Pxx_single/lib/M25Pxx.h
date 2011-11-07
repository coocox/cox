//*****************************************************************************
//
//! \file M25Pxx.h
//! \brief Prototypes for the M25Pxx Driver.
//! \version 1.0
//! \date 9/22/2011
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
//!
//*****************************************************************************
#ifndef __M25PXX_H__
#define __M25PXX_H__

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
//! \addtogroup COX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Memmory
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
//! \addtogroup M25Pxx
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup M25Pxx_Driver_Single
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//! \addtogroup M25Pxx_User_Config
//! @{
//
//*****************************************************************************
  
//
//! User write protect config,it can be 0 or 1
//
#define M25Pxx_WRITE_PROTECT    0 
  
//
//! User hold input config,it can be 0 or 1
//
#define M25Pxx_HOLD             0 

//
//! User device config,it can only be M25P10 M25P20 M25P40 M25P80 M25P16 M25P32
//! M25P64 M25P128
// 
#define M25Pxx_Device           M25P64 
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup M25Pxx_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define SPIx as a port connecting M25Pxx which can be configured
//
#define FLASH_PIN_SPI_CLK       PC9
#define SPI_CLK                 SPI1CLK  
#define FLASH_PIN_SPI_MISO      PC10
#define SPI_MISO                SPI1MISO
#define FLASH_PIN_SPI_MOSI      PC11
#define SPI_MOSI                SPI1MOSI
#define FLASH_PIN_SPI_PORT      SPI1_BASE
  
//
//! Configure GPIOC.0 as chip Select
//
#define FLASH_PIN_SPI_CS        PC8

#if (M25Pxx_HOLD > 0)
//
//! Configure GPIOA.1 as hold in
//
#define FLASH_PIN_HOLD          PA1
  
#endif
 

#if (M25Pxx_WRITE_PROTECT > 0)
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
//
//! \addtogroup COX_M25Pxx_Exported_APIs
//! @{
//
//*****************************************************************************
extern void M25PxxInit(unsigned long ulSpiClock);
extern unsigned long M25PxxIDcodeGet(void);
extern unsigned char M25PxxStatusRegRead(void);
extern void M25PxxWaitNotBusy(void);
extern void M25PxxWriteEnable(void);
extern void M25PxxWriteDisable(void);
extern void M25PxxPageWrite(unsigned char* ucBuffer, unsigned long ulWriteAddr,
                            unsigned short usNumByteToWrite);
extern void M25PxxWrite(unsigned char* pucBuffer, unsigned long  ulWriteAddr,
                        unsigned short usNumByteToWrite);
extern void M25PxxDataRead(unsigned char* ucBuffer, unsigned long ulReadAddr,
                           unsigned long ulNumByteToRead);
extern void M25PxxDataFastRead(unsigned char* ucBuffer, unsigned long ulReadAddr,
                               unsigned long ulNumByteToRead);
extern void M25PxxChipErase(void);
extern void M25PxxSectorErase(unsigned long ulDstAddr);
extern void M25PxxStatusRegWrite(unsigned char ucStatusVal);
extern void M25PxxDisable(void);
extern unsigned short M25PxxEScodeGet(void);
extern unsigned long M25PxxPageSizeGet(void);
extern unsigned long M25PxxSectorSizeGet(void);
extern unsigned long M25PxxChipSizeGet(void);

#if (M25Pxx_HOLD > 0)
extern void M25PxxHoldEnable(void);
extern void M25PxxHoldDisable(void);  
#endif
 
#if (M25Pxx_WRITE_PROTECT > 0)
extern void M25PxxWriteProtectEnable(void);
extern void M25PxxWriteProtectDisable(void);   
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

#endif //__M25PXX_H__