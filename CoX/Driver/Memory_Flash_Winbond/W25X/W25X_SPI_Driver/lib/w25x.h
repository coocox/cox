//*****************************************************************************
//
//! \file w25x.h
//! \brief Prototypes for the w25xx Driver.
//! \version V2.1.1.0
//! \date 10/6/2011
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
#ifndef __W25X_H__
#define __W25X_H__

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
//! \addtogroup W25X
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup W25X_Connection W25X Configuration
//! \brief Values can be used in W25XInit(),Define SPIx as a port connecting W25X
//! which can be configured,when you use a different SPI port you must configure
//! them again.
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

#define W25X_PIN_SPI_PORT       SPI2_BASE

#if WP_CONFIG > 0
#define W25X_PIN_WP             PE2
#endif
  
#if HOLD_CONFIG > 0
#define W25X_PIN_HOLD           PE3   
#endif

//
//! Configure PD1->SPI2CLK,PD2->SPI2MISO,PD3->MOSI and Set PD0 as a chip select
//! pin,at the same time,enable these GPIO pins which are multiplex.If you use 
//! a different SPIx Port,you have to configure them again.
//
#define xSPIPinConfigure(void)                                                \
        do                                                                    \
        {                                                                     \
            xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PD1));            \
            xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PD2));            \
            xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PD3));            \
            xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PD0));            \
            xSPinTypeSPI(SPI2CLK, PD1);                                       \
            xSPinTypeSPI(SPI2MISO, PD2);                                      \
            xSPinTypeSPI(SPI2MOSI, PD3);                                      \
            xGPIOSPinDirModeSet(PD0, xGPIO_DIR_MODE_OUT);                     \
        }                                                                     \
        while(0)
//
//! Set CS valid,start communication.
//  
#define W25XSPICSAssert()                                                     \
        xGPIOSPinWrite(PD0, 0)
//
//! Set CS invalid,stop communication.
//
#define W25XSPICSDisable()                                                    \
        xGPIOSPinWrite(PD0, 1)
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup W25X_Block_Protect W25X Block Protect
//! \brief Values can be passed to W25XWriteProtect(),you can use them when you  
//! want to protect different blocks according to your system. 
//! @{
//
//*****************************************************************************
//
//! The chip will not be protected for W25X. 
//
#define W25X_NOPROTECT          0x00

//
//! The upper 1/MemorySize will be protected(MemorySize is 64 for W25X64 and W25X32,
//! MemorySizeis 32 for W25X16).
//
#define W25X_REGION1            0x04

//
//! The upper 2/MemorySize will be protected
//
#define W25X_REGION2            0x08

//
//! The upper 4/MemorySize will be protected
//
#define W25X_REGION3            0x0c

//
//! The upper 8/MemorySize will be protected
//
#define W25X_REGION4            0x10
  
//
//! The upper 16/MemorySize will be protected
//
#define W25X_REGION5            0x14

//
//! The upper 32/MemorySize will be protected
//
#define W25X_REGION6            0x18

//
//! The lower 1/MemorySize will be protected
//
#define W25X_REGION7            0x24

//
//! The lower 2/MemorySize will be protected
//
#define W25X_REGION8            0x28

//
//! The lower 4/MemorySize will be protected
//
#define W25X_REGION9            0x2c
  
//
//! The lower 8/MemorySize will be protected
//
#define W25X_REGION11           0x30
  
//
//! The lower 16/MemorySize will be protected
//
#define W25X_REGION12           0x34
  
//
//! The lower 32/MemorySize will be protected
//
#define W25X_REGION13           0x38
  
//
//! The chip will be protected for W25X. 
//
#define W25X_ALLPROTECT         0x3c

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
extern void W25XInit(unsigned long ulSpiClock);
extern unsigned short W25XIDcodeGet(void);
extern unsigned long W25XWrite(unsigned char* pucBuffer,
                               unsigned long ulWriteAddr,
                               unsigned long ulNumByteToWrite);
extern void W25XRead(unsigned char* pucBuffer, 
                     unsigned long  ulReadAddr,
                     unsigned long ulNumByteToRead);
extern unsigned long W25XVerify(unsigned char* pucWriteBuffer,
                                unsigned long  ulReadAddr,
                                unsigned long ulNumByteToWrite);
extern void W25XChipErase(void);
extern void W25XSectorErase(unsigned long ulDstAddr);
extern void W25XBlockErase(unsigned long ulDstAddr);
extern void W25XPowerDown(void);
extern void W25XWakeUp(void);
void W25XWriteProtect(unsigned char ucBlock);
extern unsigned char W25XStatusRegRead(void);
xtBoolean W25XIsBusy(void);
extern void W25XDeInit(void);
extern void W25XWriteEnable(void);
extern void W25XWriteDisable(void);

#if WP_CONFIG > 0
extern void W25XWpDisable(void);
extern void W25XWpEnable(void);
#endif

#if HOLD_CONFIG > 0
extern void W25XHoldDisable(void);
extern void W25XHoldEnable(void);
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

#endif //__W25X_H__
