//*****************************************************************************
//
//! \file AT45DBxxxD.h
//! \brief header file of Driver for AT45DBxxxD
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

#ifndef __AT45DBxxxD_H__
#define __AT45DBxxxD_H__

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
//! \addtogroup SPI_Flash
//! @{
//! \addtogroup AT45DBxxxD
//! @{
//! \addtogroup AT45DBxxxD_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AT45DBxxxD_Pin_Config
//! AT45DBxxxD SPI DataFlash Pin Configuration.
//! @{
//
//*****************************************************************************

//
//! Modify the pin configuration to transplant the code to your application
//

#define AT45DBxxxD_PIN_CS       PC7
#define AT45DBxxxD_PIN_SCK      PB13
#define AT45DBxxxD_PIN_MISO     PB14
#define AT45DBxxxD_PIN_MOSI     PB15

#define AT45DBxxxD_SPI_PORT     SPI2_BASE
#define SPI_CLK                SPI2CLK(APP)
#define SPI_MOSI               SPI2MOSI(APP)
#define SPI_MISO               SPI2MISO(FIN)

//
//! Define AT45DBxxxD_HAS_WRITE_PROTECT macro to enable write protection function
//

#ifdef AT45DBxxxD_HAS_WRITE_PROTECT
//
//! Configure GPIOB.12 as Write Protect Pin
//
#define AT45DBxxxD_PIN_WP PB12

#endif

#ifdef AT45DBxxxD_HAS_RESET
//
//! Configure GPIOB.11 as Reset Pin
//
#define AT45DBxxxD_PIN_RST PB11

#endif
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AT45DBxxxD_CHIP_TYPE
//! AT45DBxxxD SPI DataFlash Chip Type Define.
//! @{
//
//*****************************************************************************
#define AT45DB011D     1  // 1 buffer,264B/page,2KB block,32KB sector,128KB chip
#define AT45DB021D     2  // 2 buffer,264B/page,2KB block,32KB sector,256KB chip
#define AT45DB041D     4  // 2 buffer,264B/page,2KB block,64KB sector,512KB chip
#define AT45DB081D     8  // 2 buffer,264B/page,2KB block,64KB sector,1MB chip
#define AT45DB161D     16 // 2 buffer,528B/page,4KB block,128KB sector,2MB chip
#define AT45DB321D     32 // 2 buffer,528B/page,4KB block,128KB sector,4MB chip
#define AT45DB642D     64 // 2 buffer,1056B/page,8KB block,256KB sector,8MB chip

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AT45DBxxxD_Attribute
//! AT45DBxxxD SPI DataFlash attribute.
//! @{
//
//*****************************************************************************

#define AT45DBxxxD_DEFAULT_PAGE_SIZE_LARGE    1056
#define AT45DBxxxD_BINARY_PAGE_SIZE_LARGE     1024
#define AT45DBxxxD_DEFAULT_PAGE_SIZE_BIG      528
#define AT45DBxxxD_BINARY_PAGE_SIZE_BIG       512
#define AT45DBxxxD_DEFAULT_PAGE_SIZE_SMALL    264
#define AT45DBxxxD_BINARY_PAGE_SIZE_SMALL     256

#define AT45DBxxxD_BIG_SECTOR                 32
#define AT45DBxxxD_SMALL_SECTOR               16

#define AT45DBxxxD_PAGES_PER_BLOCK            8


//
//! AT45DBxxxD buffers define
//
#define AT45DBxxxD_BUF1                    1
#define AT45DBxxxD_BUF2                    2

//
//! AT45DBxxxD max SPI clock rate
//
#define AT45DBxxxD_MAX_CLK                  66000000   //unit: Hz

//
// over time define
//
#define AT45DBxxxD_OVERTIME                 100000

//
//! AT45DBxxxD operation result
//
#define AT45DBxxxD_OP_OK                    0
#define AT45DBxxxD_OP_BUSY                  1
#define AT45DBxxxD_OP_INVALID               2
#define AT45DBxxxD_OP_WRITEPROTECT          3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
typedef struct{
	unsigned short usChipID;
	unsigned short usPageSize;
	unsigned short ulBlockSize;
	unsigned long ulSectorSize;
	unsigned long ulCapacity;
	unsigned long ulTatalPages;
}AT45DBxxxDInfoStruct;

//*****************************************************************************
//
//! \addtogroup AT45DBxxxD_APIs
//! AT45DBxxxD SPI DataFlash Exported APIs.
//! @{
//
//*****************************************************************************
extern unsigned char AT45DBxxxDInit(unsigned long ulSpiClock);
extern unsigned char AT45DBxxxDStatusGet(void);
extern void AT45DBxxxDChipIDGet(unsigned char *pucBuf);
extern unsigned char AT45DBxxxDBuftoMm(unsigned char ucBufferNum, unsigned long ulPageAddr);
extern unsigned char AT45DBxxxDMmtoBuf(unsigned char ucBufferNum, unsigned long ulPageAddr);
extern unsigned char AT45DBxxxDPageRead(unsigned long ulPageAddr, unsigned char *pucBuffer,
		                      unsigned short ulNumByteToRead);
extern unsigned char AT45DBxxxDPageWrite(unsigned long ulPageAddr, unsigned char *pucBuffer);
extern unsigned char AT45DBxxxDBufferRead(unsigned char ucBufferNum, unsigned char *pucBuffer,
                                unsigned long ulOffSetAddr, unsigned long ulNumByteToRead);
extern unsigned char AT45DBxxxDBufferWrite(unsigned char ucBufferNum, unsigned char *pucBuffer,
                                 unsigned long ulOffSetAddr, unsigned long ulNumByteToWrite);
extern unsigned char AT45DBxxxDRead(unsigned char *pucBuffer, unsigned long ulReadAddr, unsigned long ulNumByteToRead);
extern unsigned char AT45DBxxxDWrite(unsigned char *pucBuffer, unsigned long ulWriteAddr, unsigned long ulNumByteToWrite);
extern unsigned char AT45DBxxxDPageErase(unsigned long ulPageAddr);
extern unsigned char AT45DBxxxDBlockErase(unsigned short ulBlockAddr);
extern unsigned char AT45DBxxxDSectorErase(unsigned char ulSectorAddr);
extern unsigned char AT45DBxxxDChipErase(void);
extern unsigned char AT45DBxxxDSectorProtectionEnable(void);
extern unsigned char AT45DBxxxDSectorProtectionDisable(void);
extern unsigned char AT45DBxxxDSecProtRegWrite(unsigned char *pucSectors);
extern unsigned char AT45DBxxxDSecProtRegRead(unsigned char *pucSectors);
extern void AT45DBxxxDBinaryPageSet(void);

#ifdef AT45DBxxxD_HAS_WRITE_PROTECT
extern void AT45DBxxxDWriteProtectDisable(void);
extern void AT45DBxxxDWriteProtectEnable(void);
#endif

#if AT45DBxxxD_HAS_RESET
extern void AT45DBxxxDReset(void);
#endif
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__AT45DBxxxD_H__

