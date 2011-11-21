//*****************************************************************************
//
//! \file W25XxxDriver.h
//! \brief Prototypes for the w25xx Driver.
//! \version V2.1.1.0
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
#ifndef __W25XXX_H__
#define __W25XXX_H__

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
//! \addtogroup W25Xxx
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup W25Xxx_Connection W25Xxx SPI Connection
//! \brief Values that can be passed to  W25XxxInit(),Define SPIx as a port 
//! connecting W25XxxInit which can be configured,when you use a different SPI  
//! port you must configure them again.
//! @{
//
//*****************************************************************************

//
//! The configuration of write protect function,if the value is bigger than 0
//
#define WP_CONFIG               0

//
//! The configuration of "hold" function,if the value is bigger than 0
//
#define HOLD_CONFIG             0
//
//! Define SPIx as a port connecting W25Xxx which can be configured
//
#define FLASH_PIN_SPI_CLK       PD1
#define FLASH_PIN_SPI_MISO      PD2
#define FLASH_PIN_SPI_MOSI      PD3
#define FLASH_PIN_SPI_PORT      SPI2_BASE
//
//! Configure GPIOC.0 as chip Select
//
#define FLASH_PIN_SPI_CS        PD0

#if WP_CONFIG > 0
#define FLASH_PIN_WP            PE2
#endif
#if HOLD_CONFIG > 0
#define FLASH_PIN_HOLD          PE3   
#endif  
 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup W25Xxx_Exported_APIs W25Xxx Driver APIs
//! \brief API Refrence of W25Xxx Driver.
//! @{
//
//*****************************************************************************
extern void W25XxxInit(unsigned long ulSpiClock);
extern unsigned short W25XxxIDcodeGet(void);
extern void W25XxxWriteEnable(void);
extern void W25XxxWriteDisable(void);
extern void W25XxxPageWrite(unsigned char* pucBuffer, unsigned long  ulWriteAddr,
                                               unsigned short usNumByteToWrite);
extern void W25XxxWaitNotBusy(void);
extern unsigned char W25XxxStatusRegRead(void);
extern void W25XxxDataRead(unsigned char* pucBuffer, unsigned long  ulReadAddr,
                                                unsigned long ulNumByteToRead);
extern void W25XxxChipErase(void);
extern void W25XxxSectorErase(unsigned long ulDstAddr);
extern void W25XxxBlockErase(unsigned long ulDstAddr);
extern void W25XxxEnterPowerDown(void);
extern void W25XxxWakeUp(void);
extern void W25XxxStatusRegWrite(unsigned char ucStatusVal);

extern unsigned long W25XxxWrite(unsigned char* pucBuffer,unsigned long ulWriteAddr,
                                                unsigned long ulNumByteToWrite);
extern void W25XxxDeInit(void);

#if WP_CONFIG > 0
extern void W25XxxWpDisable(void);
#endif

#if WP_CONFIG > 0
extern void W25XxxWpEnable(void);
#endif

#if HOLD_CONFIG > 0
extern void W25XxxHoldDisable(void);
#endif

#if HOLD_CONFIG > 0
extern void W25XxxHoldEnable(void);
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
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__W25XXX_H__
