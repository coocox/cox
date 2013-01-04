//*****************************************************************************
//
//! \file AT45DB161.c
//! \brief the AT45DB161 Driver.
//! \version V2.1.1.0
//! \date 12/11/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox 
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
//*****************************************************************************

#include "hw_AT45DB161.h"
#include "AT45DB161.h"
#include "xdebug.h"
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_gpio.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xhw_spi.h"
#include "xspi.h"

#define AT45DB161_CS           xHWREGBITW(GPIO_ODR + AT45DB161_CS_PORT, GPIO_BIT_7)

//
//!Set default page size
//
static
unsigned short AT45DB161_PageSize = 528;

//*****************************************************************************
//
//! \brief Initialize AT45DB161 and SPI
//!
//! \param ulSpiClock specifies the SPI Clock Rate
//!
//! This function initialize the mcu SPI as master and specified SPI port.
//! After SPI and port was configured, the mcu send a AT45DB161_CMD_SRRD command
//! to get the page size of AT45DB161 to get prepareed for the followed read and
//! write operations.
//!
//! \return None.
//
//*****************************************************************************
void AT45DB161_Init(unsigned long ulSpiClock)
{
    unsigned char tmp;
    xASSERT((ulSpiClock > 0) && (ulSpiClock < AT45DB161_MAX_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DB161_SCK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DB161_CS_PIN));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DB161_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DB161_MOSI));
    xSysCtlPeripheralEnable2(AT45DB161_SPI_PORT);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xGPIOSPinDirModeSet(AT45DB161_CS_PIN, xGPIO_DIR_MODE_OUT);
#if (AT45DB161_WRITE_PROTECT < 1)
    xGPIOSPinDirModeSet(FLASH_PIN_WRITE_PROTECT, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 0);
#endif
    //
    // PD1 as SPI2.CLK
    //
    xSPinTypeSPI(SPI_CLK, AT45DB161_SCK);
    //
    // PD2 as SPI2.MISO
    // MISO20 => SPI0MISO
    //
    xSPinTypeSPI(SPI_MISO, AT45DB161_MISO);
    //
    // PD3 as SPI2.MOSI
    // MOSI20 => SPI0MISO
    //
    xSPinTypeSPI(SPI_MOSI, AT45DB161_MOSI);

    //xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    //! Set SPI mode.
    //
    xSPIConfigSet(AT45DB161_SPI_PORT, ulSpiClock, SPI_MODE_MASTER |
                  SPI_MSB_FIRST |
                  SPI_2LINE_FULL |
                  SPI_DATA_WIDTH8 |
                  SPI_FORMAT_MODE_4);
    SPISSModeConfig(AT45DB161_SPI_PORT, SPI_CR1_SSM);
    SPISSIConfig(AT45DB161_SPI_PORT, SPI_CR1_SSI);
    SPIEnble(AT45DB161_SPI_PORT);
    AT45DB161_CS = 1;
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0xFF);
    xSysCtlDelay(100000);
    AT45DB161_CS = 0;
    //
    //! Read AT45DB161 state register to get the page size.
    //
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_SRRD);
    tmp = xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0xFF);
    if(tmp & AT45DB161_PGSZ) AT45DB161_PageSize = 512;
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief Read AT45DB161 state register
//!
//! \param None
//!
//! This function is to Read AT45DB161 state register
//!
//! \return the value of state register
//
//*****************************************************************************
unsigned char AT45DB161_GetState(void)
{
    unsigned char temp;
    AT45DB161_CS = 0;
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_SRRD);
    temp = xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0xff);
    AT45DB161_CS = 1;
    return temp;
}

//*****************************************************************************
//
//! \brief To check and wait device ready
//!
//! \param None
//!
//! This function is to check and wait device ready. If the device still don't get
//! ready after 300 cycles of retry, the function will return 0 for not ready,
//! otherwise return 1 for ready.
//!
//! \return 0: not ready  ;  1: ready
//
//*****************************************************************************
unsigned char AT45DB161_WaitReady(void)
{
    unsigned char state_reg = 0x00;
    unsigned char retry = 0;
    do
    {
        state_reg = AT45DB161_GetState();
        retry++;
    }
    while((state_reg & AT45DB161_IDLE) == 0 && retry < 300);
    if(retry >= 300)return 0;
    else return 1;
}

//*****************************************************************************
//
//! \brief Main Memory Page to Buffer Transfer
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the destination.
//! \param usPageAddr specify the page address which you want to read.
//!
//! This function is to transfer data from specified page address of main memory
//! to specified AT45DB161 internal buffer.
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_Mm_to_Buf(unsigned char ucBufferNum, unsigned short usPageAddr)
{
    while(!AT45DB161_WaitReady());
    if (usPageAddr < AT45DB161_PAGES)
    {
        AT45DB161_CS = 0;
        if (ucBufferNum == AT45DB161_BUF1)
        {
            xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_MTB1);
        }
        else
        {
            xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_MTB2);
        }
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(usPageAddr >> 6));
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((usPageAddr & 0x003F) << 2));
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        AT45DB161_CS = 1;
    }
}

//*****************************************************************************
//
//! \brief Buffer to Main Memory Page Program with Built-in Erase
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the source.
//! \param usPageAddr specify the page address which you want to write.
//!
//! This function is to write data from specified internal buffer to the
//! specified main memory page address with built-in erase.
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_Buf_to_Mm(unsigned char ucBufferNum, unsigned short usPageAddr)
{
    while(!AT45DB161_WaitReady());
    if (usPageAddr < AT45DB161_PAGES)
    {
        AT45DB161_CS = 0;
        if (ucBufferNum == AT45DB161_BUF1)SPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_B1TMW);
        else SPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_B2TMW);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(usPageAddr >> 6));
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((usPageAddr & 0x003F) << 2));
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        AT45DB161_CS = 1;
    }
}

//*****************************************************************************
//
//! \brief Read data in specified AT45DB161 internal buffer
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the source.
//! \param pucBuffer to store the data read out from internal buffer
//! \param ulReadAddr specify the start address in the buffer which you want to read.
//! \param ulNumByteToRead specify how many bytes to read.
//!
//! This function is to read data from specified internal buffer. If you have
//! just a little data to be stored(less than AT45DB161_PageSize), you can temporarily
//! store them in the AT45DB161 internal buffer.It can be more fast than read write from
//! main memory
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_ReadBuffer(unsigned char ucBufferNum, unsigned char *pucBuffer,
                          unsigned long ulReadAddr, unsigned long ulNumByteToRead)
{
    if (ulReadAddr + ulNumByteToRead <= AT45DB161_PageSize)
    {
        while(!AT45DB161_WaitReady());
        AT45DB161_CS = 0;
        if (ucBufferNum == AT45DB161_BUF1)
        {
            SPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_BF1R);
        }
        else
        {
            SPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_BF2R);
        }
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((ulReadAddr & 0x0300) >> 8));
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(ulReadAddr & 0x00FF));

        xSPIDataRead(AT45DB161_SPI_PORT, pucBuffer, ulNumByteToRead);
        AT45DB161_CS = 1;
    }
}

//*****************************************************************************
//
//! \brief Write data to specified AT45DB161 internal buffer
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the destination.
//! \param pucBuffer to store the data need to be written.
//! \param ulWriteAddr specify the start address in the buffer which you want to write.
//! \param ulNumByteToRead specify how many bytes to write.
//!
//! This function is to write data to specified internal buffer. If you have
//! just a little data to be stored(less than AT45DB161_PageSize), you can temporarily
//! store them in the AT45DB161 internal buffer.It can be more fast than read write from
//! main memory.This write function doesn't affect the content in main memory.
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_WriteBuffer(unsigned char ucBufferNum, unsigned char *pucBuffer,
                           unsigned long ulWriteAddr, unsigned long ulNumByteToWrite)
{

    if (ulWriteAddr + ulNumByteToWrite <= AT45DB161_PageSize)
    {
        //    	while(!AT45DB161_WaitReady());
        AT45DB161_CS = 0;
        if (ucBufferNum == AT45DB161_BUF1)
        {
            SPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_BF1W);
        }
        else
        {
            SPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_BF2W);
        }
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((ulWriteAddr & 0x0300) >> 8));
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(ulWriteAddr & 0x00FF));
        xSPIDataWrite(AT45DB161_SPI_PORT, pucBuffer, ulNumByteToWrite);

        AT45DB161_CS = 1;
    }
}

//*****************************************************************************
//
//! \brief Read data from specified page address
//!
//! \param pucBuffer to store the data read out from page.
//! \param ulPageAddr specify the page address in the main memory of AT45DB161.
//! \param ulNumByteToRead specify how many bytes to write.
//!
//! This function is to read data from specified page address.
//! The function use main memory page read command to read data directly form main memory
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_PageRead(unsigned char *pucBuffer, unsigned short usPageAddr, unsigned long ulNumByteToRead)
{
    if(usPageAddr >= AT45DB161_PAGES) return;
    if(ulNumByteToRead > AT45DB161_PageSize) ulNumByteToRead = AT45DB161_PageSize;
    while(!AT45DB161_WaitReady());
    AT45DB161_CS = 0;
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_MMPR);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(usPageAddr >> 6));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((usPageAddr & 0x003f) << 2));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPIDataRead(AT45DB161_SPI_PORT, pucBuffer, ulNumByteToRead);
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief Read data from main memory
//!
//! \param pucBuffer specifies the destination buffer pointer to store data.
//! \param ulReadAddr specifies the byte address which data will be read (0 to AT45DB161_PageSize*AT45DB161_PAGES)
//! \param ulNumByteToRead specifies the length of data will be read.
//!
//! This function is to read more than one byte from the main memory of AT45DB161.
//! The appointed byte length data will be read to appointed address.
//!
//! \return None
//!
//*****************************************************************************
void AT45DB161_Read(unsigned char *pucBuffer, unsigned long ulReadAddr, unsigned long ulNumByteToRead)
{
    unsigned short usOffAddr, usPageAddr;
    unsigned short usLeftForward = 0, usLeftBehind = 0, usPages = 0;
    unsigned long ulBytesRead = 0;

    if(ulReadAddr >= AT45DB161_PageSize * AT45DB161_PAGES) return;
    usPageAddr = ulReadAddr / AT45DB161_PageSize;
    usOffAddr = ulReadAddr % AT45DB161_PageSize;
    if((usOffAddr + ulNumByteToRead) > AT45DB161_PageSize)
    {
        usLeftForward = AT45DB161_PageSize - usOffAddr;
        usPages = (ulNumByteToRead - usLeftForward) / AT45DB161_PageSize;
        usLeftBehind = (ulNumByteToRead - usLeftForward) % AT45DB161_PageSize;
    }
    else
    {
        usLeftForward = ulNumByteToRead;
        usPages = 0;
        usLeftBehind = 0;
    }

    while(!AT45DB161_WaitReady());
    AT45DB161_CS = 0;

    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_MMPR);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(usPageAddr >> 6));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT,
                            (unsigned char)((usPageAddr & 0x003f) << 2) | (usOffAddr >> 8));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(usOffAddr & 0xff));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0);
    xSPIDataRead(AT45DB161_SPI_PORT, pucBuffer, usLeftForward);


    usPageAddr++;
    ulBytesRead += usLeftForward;

    while(usPages)
    {
        AT45DB161_PageRead(&pucBuffer[ulBytesRead], usPageAddr, AT45DB161_PageSize);
        usPageAddr++;
        ulBytesRead += AT45DB161_PageSize;
        usPages--;
    }
    if(usLeftBehind != 0)
    {
        AT45DB161_PageRead(&pucBuffer[ulBytesRead], usPageAddr, usLeftBehind);
    }

    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief Write data to main memory
//!
//! \param pucBuffer specifies the source data buffer pointer.
//! \param ulWriteAddr specifies the byte address which data will be written to. (0 to AT45DB161_PageSize*AT45DB161_PAGES)
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to Write more than one byte to the main memory of AT45DB161.
//! The appointed byte length data will be write to appointed address.
//!
//! \return None
//!
//*****************************************************************************
void AT45DB161_Write(unsigned char *pucBuffer, unsigned long ulWriteAddr, unsigned long ulNumByteToWrite)
{
    unsigned short usOffAddr, usPageAddr;
    unsigned short usLeftForward = 0, usLeftBehind = 0, usPages = 0;
    unsigned long ulBytesWritten = 0;

    if(ulWriteAddr >= AT45DB161_PageSize * AT45DB161_PAGES) return;
    usPageAddr = ulWriteAddr / AT45DB161_PageSize;
    usOffAddr = ulWriteAddr % AT45DB161_PageSize;
    if((usOffAddr + ulNumByteToWrite) > AT45DB161_PageSize)
    {
        usLeftForward = AT45DB161_PageSize - usOffAddr;
        usPages = (ulNumByteToWrite - usLeftForward) / AT45DB161_PageSize;
        usLeftBehind = (ulNumByteToWrite - usLeftForward) % AT45DB161_PageSize;
    }
    else
    {
        usLeftForward = ulNumByteToWrite;
        usPages = 0;
        usLeftBehind = 0;
    }
    //
    //! read the first page from usPageAddr to buffer
    //
    AT45DB161_Mm_to_Buf(AT45DB161_BUF1, usPageAddr);
    while(!AT45DB161_WaitReady());
    if(usPages)
    {
        AT45DB161_Mm_to_Buf(AT45DB161_BUF2, usPageAddr + 1);
    }

    AT45DB161_WriteBuffer(AT45DB161_BUF1, pucBuffer, usOffAddr, usLeftForward);
    //
    //! Write the data of the buffer back to the same page address in main memory
    //
    AT45DB161_Buf_to_Mm(AT45DB161_BUF1, usPageAddr);
    while(!AT45DB161_WaitReady());
    ulBytesWritten += usLeftForward;
    usPageAddr++;

    while(usPages)
    {
        AT45DB161_WriteBuffer(AT45DB161_BUF1, &pucBuffer[ulBytesWritten],
                              0, AT45DB161_PageSize);
        AT45DB161_Buf_to_Mm(AT45DB161_BUF1, usPageAddr);
        ulBytesWritten += AT45DB161_PageSize;
        usPageAddr++;
        usPages--;
        while(!AT45DB161_WaitReady());
    }
    if(usLeftBehind != 0)
    {
        //while(!AT45DB161_WaitReady());
        AT45DB161_Mm_to_Buf(AT45DB161_BUF2, usPageAddr);
        while(!AT45DB161_WaitReady());
        AT45DB161_WriteBuffer(AT45DB161_BUF2, &pucBuffer[ulBytesWritten], 0, usLeftBehind);
        AT45DB161_Buf_to_Mm(AT45DB161_BUF2, usPageAddr);
    }
    AT45DB161_CS = 1;
}


//*****************************************************************************
//
//! \brief  Erase specified page
//!
//! \param usPageAddr specifies the page address.(page address < 4096)
//!
//! This function is to Erase the specified page
//!
//! \return None
//!
//*****************************************************************************
void AT45DB161_ErasePage(unsigned short usPageAddr)
{
    if(AT45DB161_WaitReady() == 0) return;
    if(usPageAddr >= AT45DB161_PAGES) return;
    AT45DB161_CS = 0;
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_ERPG);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(usPageAddr >> 6));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((usPageAddr & 0x003F) << 2));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief  Erase specified block
//!
//! \param usPageAddr specifies the block address.(block address < 512)
//!
//! This function is to Erase the specified block
//!
//! \return None
//!
//*****************************************************************************
void AT45DB161_EraseBlock(unsigned short usBlockAddr)
{
    if(AT45DB161_WaitReady() == 0) return;
    if(usBlockAddr >= AT45DB161_BLOCKS) return;
    AT45DB161_CS = 0;
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_ERBL);
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)(usBlockAddr >> 3));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((usBlockAddr & 0x000F) << 5));
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief  Erase specified sector
//!
//! \param usPageAddr specifies the sector address.(sector address < 16)
//!
//! This function is to Erase the specified sector
//!
//! \return None
//!
//*****************************************************************************
void AT45DB161_EraseSector(unsigned char usSectorAddr)
{
    if(AT45DB161_WaitReady() == 0) return;
    if(usSectorAddr >= AT45DB161_SECTORS) return;

    if(usSectorAddr == 0)
    {
        //
        //! erase 0a sector of sector 0
        //
        AT45DB161_CS = 0;
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_ERSC);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        AT45DB161_CS = 1;
        xSysCtlDelay(10000);
        if(AT45DB161_WaitReady() == 0) return;
        //
        //! erase 0b sector of sector 0
        //
        AT45DB161_CS = 0;
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_ERSC);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x20);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        AT45DB161_CS = 1;
    }
    else
    {
        AT45DB161_CS = 0;
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_ERSC);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, (unsigned char)((usSectorAddr & 0x0F) << 2));
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        xSPISingleDataReadWrite(AT45DB161_SPI_PORT, 0x00);
        AT45DB161_CS = 1;
    }
}

//*****************************************************************************
//
//! \brief Erase whole chip memory with build-in erase program
//!
//! \param None
//!
//! This function is to Erase whole chip with build-in erase program. the value of
//! the erased data will be 0xFF;
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_EraseChip()
{
    if(AT45DB161_WaitReady() == 0)return;
    AT45DB161_CS = 0;

    xSPIDataWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_CPER, 4);
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief Read AT45DB161 chip ID
//!
//! \param pucBuf contain the ID information
//!
//! This function is to read AT45DB161 chip ID, the Manufacturer and Device ID
//! will be put into pucBuf.
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_GetChipID(unsigned char *pucBuf)
{
    AT45DB161_CS = 0;
    xSPISingleDataReadWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_MDID);
    xSPIDataRead(AT45DB161_SPI_PORT, pucBuf, 4);
    if(AT45DB161_PageSize == 528) pucBuf[4] = 0xFE;
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief Enable Sector Protection
//!
//! \param None
//!
//! This function is to enable sector protection
//! Sectors specified for protection in the Sector Protection Register can be protected
//! from program and erase operations by issuing the Enable Sector Protection command.
//! If the device is power cycled, then the software controlled protection will be disabled.
//! Once the device is powered up, the Enable Sector Protection command should be reissued
//! if sector protection is desired and if the WP pin is not used.
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_SectorProtectionEn(void)
{
    if(AT45DB161_WaitReady() == 0)return;

    AT45DB161_CS = 0;
    xSPIDataWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_ESSP, 4);
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief Disable Sector Protection
//!
//! \param None
//!
//! This function is to disable sector protection
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_SectorProtectionDi(void)
{
    if(AT45DB161_WaitReady() == 0)return;
#if (AT45DB161_WRITE_PROTECT < 1)
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 1);
#endif
    AT45DB161_CS = 0;
    xSPIDataWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_DSSP, 4);
    AT45DB161_CS = 1;
#if (AT45DB161_WRITE_PROTECT < 1)
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 0);
#endif
}

//*****************************************************************************
//
//! \brief Program the Sector Protection Register
//!
//! \param  pucSectors consists of 16 bytes that specify whether sectors 0 through 15 will be protected or unprotected.
//!
//! This function is to Program the Sector Protection Register to specifies which
//! sectors are to be protected or unprotected with either the software or hardware
//! controlled protection methods
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_ProgSecProtReg(unsigned char *pucSectors)
{
    if(AT45DB161_WaitReady() == 0)return;

#if (AT45DB161_WRITE_PROTECT < 1)
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 1);
#endif
    AT45DB161_CS = 0;
    xSPIDataWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_ESPR, 4);
    AT45DB161_CS = 1;
    xSysCtlDelay(10000);
    while(!AT45DB161_WaitReady());
    AT45DB161_CS = 0;
    xSPIDataWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_PSPR, 4);
    xSPIDataWrite(AT45DB161_SPI_PORT, pucSectors, 16);
    AT45DB161_CS = 1;
#if (AT45DB161_WRITE_PROTECT < 1)
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 0);
#endif
}

//*****************************************************************************
//
//! \brief Read the Sector Protection Register
//!
//! \param  pucSectors to store the value of Sector Protection Register after read.
//!
//! This function is to read the sector protection register to get the information
//! of which sectors are to be protected or unprotected
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_RdSecProtReg(unsigned char *pucSectors)
{
    if(AT45DB161_WaitReady() == 0)return;
    AT45DB161_CS = 0;
    xSPIDataWrite(AT45DB161_SPI_PORT, AT45DB161_CMD_RSPR, 4);
    xSPIDataRead(AT45DB161_SPI_PORT, pucSectors, 16);
    AT45DB161_CS = 1;
}

//*****************************************************************************
//
//! \brief AT45DB161 Write Protect Disable
//!
//! \param  None
//!
//! This function is to disable hardware AT45DB161 Write Protect
//! by set WP Pin to 0
//!
//! \return None
//
//*****************************************************************************
#if (AT45DB161_WRITE_PROTECT < 1)
void AT45DB161_WriteProtectDisable(void)
{
	xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 1);
}

//*****************************************************************************
//
//! \brief AT45DB161 Write Protect Enable
//!
//! \param  None
//!
//! This function is to enable hardware AT45DB161 Write Protect
//! by set WP Pin to 1
//!
//! \return None
//
//*****************************************************************************
void AT45DB161_WriteProtectEnable(void)
{
	xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 0);
}
#endif
