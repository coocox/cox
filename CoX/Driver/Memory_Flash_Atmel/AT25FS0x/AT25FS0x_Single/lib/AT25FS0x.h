//*****************************************************************************
//
//! \file AT25FS0x.h
//! \brief Prototypes for the AT25FS0x Driver.
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
#ifndef __AT25FS0X_H__
#define __AT25FS0X_H__

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
//! \addtogroup AT25FS0x
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup AT25FS0x_Driver_Single
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//! \addtogroup AT25FS0x_User_Config
//! @{
//
//*****************************************************************************
  
//
//! User write protect config,it can be 0 or 1
//
#define AT25FS0x_WRITE_PROTECT  0 
  
//
//! User hold input config,it can be 0 or 1
//
#define AT25FS0x_HOLD           0 

//
//! User device config,it can only be M25P10 M25P20 M25P40 M25P80 M25P16 M25P32
//! M25P64 M25P128
// 
#define AT25FS0x_Device         AT25FS040 
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup AT25FS0x_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define SPIx as a port connecting AT25FS0x which can be configured
//
#define FLASH_PIN_SPI_CLK       PD1
#define SPI_CLK                 SPI2CLK  
#define FLASH_PIN_SPI_MISO      PD2
#define SPI_MISO                SPI2MISO
#define FLASH_PIN_SPI_MOSI      PD3
#define SPI_MOSI                SPI2MOSI
#define FLASH_PIN_SPI_PORT      SPI2_BASE
  
//
//! Configure GPIOC.0 as chip Select
//
#define FLASH_PIN_SPI_CS        PD0

#if (AT25FS0x_HOLD > 0)
//
//! Configure GPIOA.1 as hold in
//
#define FLASH_PIN_HOLD          PA1
  
#endif
 

#if (AT25FS0x_WRITE_PROTECT > 0)
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
//! \addtogroup CoX_AT25FS0x_Exported_APIs
//! @{
//
//*****************************************************************************
extern void AT25FS0xInit(unsigned long ulSpiClock);
extern unsigned long AT25FS0xIDcodeGet(void);
extern unsigned char AT25FS0xStatusRegRead(void);
extern void AT25FS0xWaitNotBusy(void);
extern void AT25FS0xWriteEnable(void);
extern void AT25FS0xWriteDisable(void);
extern void AT25FS0xPageWrite(unsigned char* ucBuffer, unsigned long ulWriteAddr,
                              unsigned short usNumByteToWrite);
extern void AT25FS0xWrite(unsigned char* ucBuffer, unsigned long ulWriteAddr,
                          unsigned short usNumByteToWrite);
extern void AT25FS0xDataRead(unsigned char* ucBuffer, unsigned long ulReadAddr,
                             unsigned long ulNumByteToRead);
extern void AT25FS0xDataFastRead(unsigned char* ucBuffer, unsigned long ulReadAddr,
                               unsigned long ulNumByteToRead);
extern void AT25FS0xChipErase(void);
extern void AT25FS0xBlockErase(unsigned long ulDstAddr);
extern void AT25FS0xSectorErase(unsigned long ulDstAddr);
extern void AT25FS0xStatusRegWrite(unsigned char ucStatusVal);
extern void AT25FS0xDisable(void);
extern unsigned short AT25FS0xEScodeGet(void);
extern unsigned long AT25FS0xPageSizeGet(void);
extern unsigned long AT25FS0xSectorSizeGet(void);
extern unsigned long AT25FS0xChipSizeGet(void);

#if (AT25FS0x_HOLD > 0)
extern void AT25FS0xHoldEnable(void);
extern void AT25FS0xHoldDisable(void);  
#endif
 
#if (AT25FS0x_WRITE_PROTECT > 0)
extern void AT25FS0xWriteProtectEnable(void);
extern void AT25FS0xWriteProtectDisable(void);   
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

#endif //__AT25FS0X_H__