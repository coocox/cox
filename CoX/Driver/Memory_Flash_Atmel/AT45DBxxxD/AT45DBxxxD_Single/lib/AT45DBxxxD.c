//*****************************************************************************
//
//! \file AT45DBxxxD.c
//! \brief the AT45DBxxxD Driver.
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

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_gpio.h"
#include "xhw_spi.h"
#include "xcore.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xspi.h"
#include "hw_AT45DBxxxD.h"
#include "AT45DBxxxD.h"

#define AT45DBxxxD_CS_SET           xGPIOSPinWrite(AT45DBxxxD_PIN_CS,1)
#define AT45DBxxxD_CS_CLR           xGPIOSPinWrite(AT45DBxxxD_PIN_CS,0)

#if AT45DBxxxD_HAS_WRITE_PROTECT
//
// Default no write protect
//
static unsigned char gucWriteProtectEn = 0;
#endif

AT45DBxxxDInfoStruct AT45DBxxxDInfo;

static unsigned char ucBinaryPageFlag = 0;

//*****************************************************************************
//
//! \brief Read AT45DBxxxD chip ID
//!
//! \param pucBuf contain the ID information
//!
//! This function is to read AT45DBxxxD chip ID, the Manufacturer and Device ID.
//!
//! \return None
//
//*****************************************************************************
void AT45DBxxxDChipIDGet(unsigned char *pucBuf)
{
    AT45DBxxxD_CS_CLR;
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_RDID);
    xSPIDataRead(AT45DBxxxD_SPI_PORT, pucBuf, 2);
    AT45DBxxxD_CS_SET;
}


//*****************************************************************************
//
//! \brief Read AT45DBxxxD status register
//!
//! \param None
//!
//! This function is to Read AT45DBxxxD status register
//!
//! \return the value of status register
//
//*****************************************************************************
unsigned char AT45DBxxxDStatusGet(void)
{
    unsigned char temp;
    AT45DBxxxD_CS_CLR;
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_SRRD);
    temp = xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0xff);
    AT45DBxxxD_CS_SET;
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
unsigned char AT45DBxxxDWaitReady(void)
{
    unsigned char state_reg = 0x00;
    unsigned char retry = 0;
    do
    {
        state_reg = AT45DBxxxDStatusGet();
        retry++;
    }
    while((state_reg & AT45DBxxxD_IDLE) == 0 && retry < 300);
    if(retry >= 300)return 0;
    else return 1;
}

//*****************************************************************************
//
//! \brief Initialize AT45DBxxxD and SPI
//!
//! \param ulSpiClock specifies the SPI Clock Rate
//!
//! This function initialize the mcu SPI as master and specified SPI port.
//! After SPI and port was configured, the mcu send a AT45DBxxxD_CMD_SRRD command
//! to get the page size of AT45DBxxxD to get prepareed for the followed read and
//! write operations.
//!
//! \return operation result.
//
//*****************************************************************************
unsigned char AT45DBxxxDInit(unsigned long ulSpiClock)
{
    unsigned char tmp[2];
    xASSERT((ulSpiClock > 0) && (ulSpiClock < AT45DBxxxD_MAX_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DBxxxD_PIN_SCK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DBxxxD_PIN_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DBxxxD_PIN_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(AT45DBxxxD_PIN_MOSI));
    xSysCtlPeripheralEnable2(AT45DBxxxD_SPI_PORT);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xGPIOSPinDirModeSet(AT45DBxxxD_PIN_CS, xGPIO_DIR_MODE_OUT);
#if AT45DBxxxD_HAS_WRITE_PROTECT
    xGPIOSPinDirModeSet(AT45DBxxxD_PIN_WP, xGPIO_DIR_MODE_OUT);
    if(gucWriteProtectEn)
    {
        xGPIOSPinWrite(AT45DBxxxD_PIN_WP, 0);
    }
    else
    {
    	xGPIOSPinWrite(AT45DBxxxD_PIN_WP, 1);
    }
#endif

#if AT45DBxxxD_HAS_RESET
    xGPIOSPinDirModeSet(AT45DBxxxD_PIN_RST, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(AT45DBxxxD_PIN_RST, 0);
#endif
    //
    // PB13 as SPI2.CLK
    //
    xSPinTypeSPI(SPI_CLK, AT45DBxxxD_PIN_SCK);
    //
    // PB14 as SPI2.MISO
    //
    xSPinTypeSPI(SPI_MISO, AT45DBxxxD_PIN_MISO);
    //
    // PB15 as SPI2.MOSI
    //
    xSPinTypeSPI(SPI_MOSI, AT45DBxxxD_PIN_MOSI);

    //xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    //! Set SPI mode.
    //
	xSPIConfigSet(AT45DBxxxD_SPI_PORT, ulSpiClock,
    		xSPI_MOTO_FORMAT_MODE_3 |
            xSPI_MODE_MASTER |
            xSPI_MSB_FIRST |
            xSPI_DATA_WIDTH8);

	xSPISSSet( AT45DBxxxD_SPI_PORT, xSPI_SS_SOFTWARE, xSPI_SS0 );
    SPIEnble(AT45DBxxxD_SPI_PORT);
    AT45DBxxxD_CS_CLR;
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0xFF);
    AT45DBxxxD_CS_SET;
#if AT45DBxxxD_HAS_RESET
    xGPIOSPinWrite(AT45DBxxxD_PIN_RST, 1);
#endif
    xSysCtlDelay(1000);

    AT45DBxxxDChipIDGet(tmp);
    if(tmp[0] != AT45DBxxxD_MANUFACTURER_ID) return AT45DBxxxD_OP_INVALID;
    tmp[1]=1<<((tmp[1] & 0x1F)-2);
    AT45DBxxxDInfo.usChipID = (((unsigned short)tmp[0]) << 8) + tmp[1];
    //
    //! Read AT45DBxxxD state register to get the page size.
    //
    tmp[0] = AT45DBxxxDStatusGet();
    if(tmp[0] == 0) return AT45DBxxxD_OP_INVALID;
    if(tmp[0] & AT45DBxxxD_PGSZ)
    {
    	//
    	// Binary page size
    	//
    	ucBinaryPageFlag = 1;
    	if(tmp[1] > AT45DB321D)
    	{
    		AT45DBxxxDInfo.usPageSize = AT45DBxxxD_BINARY_PAGE_SIZE_LARGE;
    	}
    	else if(tmp[1] > AT45DB081D)
    	{
    		AT45DBxxxDInfo.usPageSize = AT45DBxxxD_BINARY_PAGE_SIZE_BIG;
    	}
    	else if(tmp[1] != 0)
    	{
    		AT45DBxxxDInfo.usPageSize = AT45DBxxxD_BINARY_PAGE_SIZE_SMALL;
    	}
    	else
    	{
    		AT45DBxxxDInfo.usPageSize = 0;
    	}
    	AT45DBxxxDInfo.ulCapacity = (unsigned long)tmp[1]*131072;
    }
    else
    {
    	//
    	// default page size
    	//
    	ucBinaryPageFlag = 0;
    	if(tmp[1] > AT45DB321D)
    	{
    		AT45DBxxxDInfo.usPageSize = AT45DBxxxD_DEFAULT_PAGE_SIZE_LARGE;
    	}
    	else if(tmp[1] > AT45DB081D)
    	{
    		AT45DBxxxDInfo.usPageSize = AT45DBxxxD_DEFAULT_PAGE_SIZE_BIG;
    	}
    	else if(tmp[1] != 0)
    	{
    		AT45DBxxxDInfo.usPageSize = AT45DBxxxD_DEFAULT_PAGE_SIZE_SMALL;
    	}
    	else
    	{
    		AT45DBxxxDInfo.usPageSize = 0;
    	}
    	AT45DBxxxDInfo.ulCapacity = (unsigned long)tmp[1]*135168;
    }
    AT45DBxxxDInfo.ulBlockSize = AT45DBxxxDInfo.usPageSize * AT45DBxxxD_PAGES_PER_BLOCK;
    if(tmp[1]>2) AT45DBxxxDInfo.ulSectorSize = (unsigned long)AT45DBxxxDInfo.ulBlockSize * AT45DBxxxD_BIG_SECTOR;
    else AT45DBxxxDInfo.ulSectorSize = (unsigned long)AT45DBxxxDInfo.ulBlockSize * AT45DBxxxD_SMALL_SECTOR;
    AT45DBxxxDInfo.ulTatalPages = AT45DBxxxDInfo.ulCapacity / AT45DBxxxDInfo.usPageSize;
    AT45DBxxxD_CS_SET;
    return AT45DBxxxD_OP_OK;
}

static void AT45DBxxxDWritePageAddr(unsigned long ulPageAddr)
{
    if(ucBinaryPageFlag)
    {
    	if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB321D)
    	{
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulPageAddr >> 6));
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((ulPageAddr & 0x007F) << 2));
    	}
        else if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB081D)
        {
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulPageAddr >> 7));
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((ulPageAddr & 0x007F) << 1));
        }
        else
        {
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulPageAddr >> 8));
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulPageAddr & 0x00FF));
        }
    }
    else
    {
    	if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB321D)
    	{
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulPageAddr >> 5));
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((ulPageAddr & 0x003F) << 3));
    	}
    	else if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB081D)
        {
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulPageAddr >> 6));
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((ulPageAddr & 0x003F) << 2));
        }
        else
        {
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulPageAddr >> 7));
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((ulPageAddr & 0x007F) << 1));
        }
    }
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0x00);
}
//*****************************************************************************
//
//! \brief Main Memory Page to Buffer Transfer
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the destination.
//! \param ulPageAddr specify the page address which you want to read.
//!
//! This function is to transfer data from specified page address of main memory
//! to specified AT45DBxxxD internal buffer.
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDMmtoBuf(unsigned char ucBufferNum, unsigned long ulPageAddr)
{
	unsigned int i = 0;

	if(ulPageAddr >= AT45DBxxxDInfo.ulTatalPages) return AT45DBxxxD_OP_INVALID;
    while(!AT45DBxxxDWaitReady())
    {
    	if(++i > AT45DBxxxD_OVERTIME)
    	{
    		return AT45DBxxxD_OP_BUSY;
    	}
    }

    AT45DBxxxD_CS_CLR;
    //
    // Write main memory to buffer transfer command
    //
    if (ucBufferNum == AT45DBxxxD_BUF1)
    {
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_MTB1);
    }
    else
    {
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_MTB2);
    }

    //
    // Write page address
    //
    AT45DBxxxDWritePageAddr(ulPageAddr);
    AT45DBxxxD_CS_SET;
    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Buffer to Main Memory Page Program with Built-in Erase
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the source.
//! \param ulPageAddr specify the page address which you want to write.
//!
//! This function is to write data from specified internal buffer to the
//! specified main memory page address with built-in erase.
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDBuftoMm(unsigned char ucBufferNum, unsigned long ulPageAddr)
{
    unsigned int i = 0;

    if(ulPageAddr >= AT45DBxxxDInfo.ulTatalPages) return AT45DBxxxD_OP_INVALID;
    while(!AT45DBxxxDWaitReady())
    {
    	if(++i > AT45DBxxxD_OVERTIME)
    	{
    		return AT45DBxxxD_OP_BUSY;
    	}
    }

    AT45DBxxxD_CS_CLR;
    if (ucBufferNum == AT45DBxxxD_BUF1)
    {
    	SPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_B1TMW);
    }
    else
    {
    	SPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_B2TMW);
    }

    AT45DBxxxDWritePageAddr(ulPageAddr);

    AT45DBxxxD_CS_SET;

    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Read data in specified AT45DBxxxD internal buffer
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the source.
//! \param pucBuffer to store the data read out from internal buffer
//! \param ulOffAddr specify the start address in the buffer which you want to read.
//! \param ulNumByteToRead specify how many bytes to read.
//!
//! This function is to read data from specified internal buffer. If you have
//! just a little data to be stored(less than AT45DBxxxDInfo.usPageSize), you can temporarily
//! store them in the AT45DBxxxD internal buffer.It can be more fast than read write from
//! main memory
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDBufferRead(unsigned char ucBufferNum, unsigned char *pucBuffer,
                            unsigned long ulOffSetAddr, unsigned long ulNumByteToRead)
{
	unsigned int i = 0;
    if(ulOffSetAddr + ulNumByteToRead > AT45DBxxxDInfo.usPageSize) return AT45DBxxxD_OP_INVALID;

    while(!AT45DBxxxDWaitReady())
    {
    	if(++i > AT45DBxxxD_OVERTIME)
    	{
    		return AT45DBxxxD_OP_BUSY;
    	}
    }

    AT45DBxxxD_CS_CLR;
    if (ucBufferNum == AT45DBxxxD_BUF1)
    {
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_BF1R);
    }
    else
    {
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_BF2R);
    }
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0x00);
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulOffSetAddr >> 8));
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulOffSetAddr & 0x00FF));

    xSPIDataRead(AT45DBxxxD_SPI_PORT, pucBuffer, ulNumByteToRead);
    AT45DBxxxD_CS_SET;
    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Write data to specified AT45DBxxxD internal buffer
//!
//! \param ucBufferNum specify the buffer 1 or 2 as the destination.
//! \param pucBuffer to store the data need to be written.
//! \param ulWriteAddr specify the start address in the buffer which you want to write.
//! \param ulNumByteToRead specify how many bytes to write.
//!
//! This function is to write data to specified internal buffer. If you have
//! just a little data to be stored(less than AT45DBxxxDInfo.usPageSize), you can temporarily
//! store them in the AT45DBxxxD internal buffer.It can be more fast than read write from
//! main memory.This write function doesn't affect the content in main memory.
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDBufferWrite(unsigned char ucBufferNum, unsigned char *pucBuffer,
                           unsigned long ulOffSetAddr, unsigned long ulNumByteToWrite)
{
	unsigned int i = 0;
    if (ulOffSetAddr + ulNumByteToWrite > AT45DBxxxDInfo.usPageSize) return AT45DBxxxD_OP_INVALID;
    while(!AT45DBxxxDWaitReady())
    {
        if(++i > AT45DBxxxD_OVERTIME)
        {
        	return AT45DBxxxD_OP_BUSY;
        }
    }
    AT45DBxxxD_CS_CLR;
    if (ucBufferNum == AT45DBxxxD_BUF1)
    {
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_BF1W);
    }
    else
    {
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_BF2W);
    }
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0x00);
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulOffSetAddr >> 8));
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(ulOffSetAddr & 0x00FF));
    xSPIDataWrite(AT45DBxxxD_SPI_PORT, pucBuffer, ulNumByteToWrite);
    AT45DBxxxD_CS_SET;

    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Read a quantity of bytes from start of specified main memory page address
//!
//! \param pucBuffer to store the data read out from page.
//! \param ulPageAddr specify the page address in the main memory of AT45DBxxxD.
//! \param ulNumByteToRead specify how many bytes to read.
//!
//! This function is to read data from specified page address.
//! The function use main memory page read command to read data directly form main memory
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDPageRead(unsigned long ulPageAddr, unsigned char *pucBuffer, unsigned short ulNumByteToRead)
{
	unsigned int i = 0;
    if(ulPageAddr >= AT45DBxxxDInfo.ulTatalPages) return AT45DBxxxD_OP_INVALID;
    if(ulNumByteToRead > AT45DBxxxDInfo.usPageSize) ulNumByteToRead = AT45DBxxxDInfo.usPageSize;
    while(!AT45DBxxxDWaitReady())
    {
    	if(++i > AT45DBxxxD_OVERTIME)
    	{
    		return AT45DBxxxD_OP_BUSY;
    	}
    }
    AT45DBxxxD_CS_CLR;
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_MMPR);
    AT45DBxxxDWritePageAddr(ulPageAddr);
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0);
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0);
    xSPIDataRead(AT45DBxxxD_SPI_PORT, pucBuffer, ulNumByteToRead);
    AT45DBxxxD_CS_SET;
    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Write one page of bytes to specified main memory page address
//!
//! \param pucBuffer to store the data read out from page.
//! \param ulPageAddr specify the page address in the main memory of AT45DBxxxD.
//!
//! This function is to write data to specified page address.
//! The function first write data to buffer then using buffer
//! to main memory transfer to write data to main memory.
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDPageWrite(unsigned long ulPageAddr, unsigned char *pucBuffer)
{
	unsigned int i = 0;
    if(ulPageAddr >= AT45DBxxxDInfo.ulTatalPages) return AT45DBxxxD_OP_INVALID;
    while(!AT45DBxxxDWaitReady())
    {
    	if(++i > AT45DBxxxD_OVERTIME)
    	{
    		return AT45DBxxxD_OP_BUSY;
    	}
    }
    AT45DBxxxDBufferWrite(AT45DBxxxD_BUF1, pucBuffer, 0, AT45DBxxxDInfo.usPageSize);
    AT45DBxxxDBuftoMm(AT45DBxxxD_BUF1, ulPageAddr);

    return AT45DBxxxD_OP_OK;
}
//*****************************************************************************
//
//! \brief Read data from main memory
//!
//! \param pucBuffer specifies the destination buffer pointer to store data.
//! \param ulReadAddr specifies the byte address which data will be read (0 to AT45DBxxxDInfo.usPageSize*AT45DBxxxDInfo.ulTatalPages-1)
//! \param ulNumByteToRead specifies the length of data will be read.
//!
//! This function is to read a quantity of bytes from specified byte
//! address in main memory of AT45DBxxxD.
//!
//! \return operation result
//!
//*****************************************************************************
unsigned char AT45DBxxxDRead(unsigned char *pucBuffer, unsigned long ulReadAddr, unsigned long ulNumByteToRead)
{
    unsigned short usOffAddr;
    unsigned long ulPageAddr;
    unsigned short usLeftForward = 0, usLeftBehind = 0, usPages = 0;
    unsigned long ulBytesRead = 0;
    //
    // if read address exceed chip size, return.
    //
    if(ulReadAddr >= AT45DBxxxDInfo.usPageSize * AT45DBxxxDInfo.ulTatalPages) return AT45DBxxxD_OP_INVALID;
    //
    // calculate page address and offset address in page
    //
    ulPageAddr = ulReadAddr / AT45DBxxxDInfo.usPageSize;
    usOffAddr = ulReadAddr % AT45DBxxxDInfo.usPageSize;

    if((usOffAddr + ulNumByteToRead) > AT45DBxxxDInfo.usPageSize)
    {
    	//
    	// if reading data exceeds the boundary of a page,
    	// divide data into 3 parts:
    	// 1: start address to the boundary of the first page
    	// 2: second page to the last complete pages counts
    	// 3: the last incomplete page to the last byte
    	//
        usLeftForward = AT45DBxxxDInfo.usPageSize - usOffAddr;
        usPages = (ulNumByteToRead - usLeftForward) / AT45DBxxxDInfo.usPageSize;
        usLeftBehind = (ulNumByteToRead - usLeftForward) % AT45DBxxxDInfo.usPageSize;
    }
    else
    {
    	//
    	// if reading data dosen't exceed one page
    	//
        usLeftForward = ulNumByteToRead;
        usPages = 0;
        usLeftBehind = 0;
    }

//    while(!AT45DBxxxDWaitReady());

    //
    // read first part of data
    //
    AT45DBxxxDMmtoBuf(AT45DBxxxD_BUF1, ulPageAddr);
    AT45DBxxxDBufferRead(AT45DBxxxD_BUF1, pucBuffer, usOffAddr, usLeftForward);

    ulPageAddr++;
    ulBytesRead += usLeftForward;

    //
    // read second part of data
    //
    while(usPages)
    {
        AT45DBxxxDPageRead(ulPageAddr, &pucBuffer[ulBytesRead], AT45DBxxxDInfo.usPageSize);
        ulPageAddr++;
        ulBytesRead += AT45DBxxxDInfo.usPageSize;
        usPages--;
    }
    //
    // read last part of data
    //
    if(usLeftBehind != 0)
    {
        AT45DBxxxDPageRead(ulPageAddr, &pucBuffer[ulBytesRead], usLeftBehind);
    }
    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Write data to main memory
//!
//! \param pucBuffer specifies the source data buffer pointer.
//! \param ulWriteAddr specifies the byte address which data will be written to. (0 to AT45DBxxxDInfo.usPageSize*AT45DBxxxDInfo.ulTatalPages)
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to write a quantity of byte to specified byte address in
//! the main memory of AT45DBxxxD.
//!
//! \return operation result
//!
//*****************************************************************************
unsigned char AT45DBxxxDWrite(unsigned char *pucBuffer, unsigned long ulWriteAddr, unsigned long ulNumByteToWrite)
{
    unsigned short usOffAddr;
    unsigned long ulPageAddr;
    unsigned short usLeftForward = 0, usLeftBehind = 0, usPages = 0;
    unsigned long ulBytesWritten = 0;

    //
    // If write data length == 0
    //
    if(ulNumByteToWrite == 0) return AT45DBxxxD_OP_OK;
    //
    // if write address exceed chip size, return.
    //
    if(ulWriteAddr >= AT45DBxxxDInfo.usPageSize * AT45DBxxxDInfo.ulTatalPages) return AT45DBxxxD_OP_INVALID;
    //
    // calculate page address and offset address in page
    //
    ulPageAddr = ulWriteAddr / AT45DBxxxDInfo.usPageSize;
    usOffAddr = ulWriteAddr % AT45DBxxxDInfo.usPageSize;
    if((usOffAddr + ulNumByteToWrite) > AT45DBxxxDInfo.usPageSize)
    {
    	//
    	// if writing data exceeds the boundary of a page,
    	// divide data into 3 parts:
    	// 1: start address to the boundary of the first page
    	// 2: second page to the last complete pages counts
    	// 3: the last incomplete page to the last byte
    	//
        usLeftForward = AT45DBxxxDInfo.usPageSize - usOffAddr;
        usPages = (ulNumByteToWrite - usLeftForward) / AT45DBxxxDInfo.usPageSize;
        usLeftBehind = (ulNumByteToWrite - usLeftForward) % AT45DBxxxDInfo.usPageSize;
    }
    else
    {
    	//
    	// if reading data dosen't exceed one page
    	//
        usLeftForward = ulNumByteToWrite;
        usPages = 0;
        usLeftBehind = 0;
    }

//    while(!AT45DBxxxDWaitReady());

    //
    // read the first page from ulPageAddr to buffer
    //
    AT45DBxxxDMmtoBuf(AT45DBxxxD_BUF1, ulPageAddr);
    //
    // Write the 1st part of data to buffer
    //
    AT45DBxxxDBufferWrite(AT45DBxxxD_BUF1, pucBuffer, usOffAddr, usLeftForward);
    //
    // write buffer data to original page address
    //
    AT45DBxxxDBuftoMm(AT45DBxxxD_BUF1, ulPageAddr);

    ulBytesWritten += usLeftForward;
    ulPageAddr++;

    //
    // Write the 2nd part of data to buffer
    //
    while(usPages)
    {
        AT45DBxxxDBufferWrite(AT45DBxxxD_BUF1, &pucBuffer[ulBytesWritten],
                              0, AT45DBxxxDInfo.usPageSize);
        AT45DBxxxDBuftoMm(AT45DBxxxD_BUF1, ulPageAddr);
        if(AT45DBxxxDStatusGet()&AT45DBxxxD_SCPT_EN) return AT45DBxxxD_OP_INVALID;
        ulBytesWritten += AT45DBxxxDInfo.usPageSize;
        ulPageAddr++;
        usPages--;
    }
    //
    // Write the 3rd part of data to buffer
    //
    if(usLeftBehind != 0)
    {
        AT45DBxxxDMmtoBuf(AT45DBxxxD_BUF1, ulPageAddr);
        AT45DBxxxDBufferWrite(AT45DBxxxD_BUF1, &pucBuffer[ulBytesWritten], 0, usLeftBehind);
        AT45DBxxxDBuftoMm(AT45DBxxxD_BUF1, ulPageAddr);
        if(AT45DBxxxDStatusGet()&AT45DBxxxD_SCPT_EN) return AT45DBxxxD_OP_INVALID;
    }
    return AT45DBxxxD_OP_OK;
}


//*****************************************************************************
//
//! \brief  Erase specified page
//!
//! \param ulPageAddr specifies the page address.
//!
//! This function is to Erase the specified page
//!
//! \return operation result
//!
//*****************************************************************************
unsigned char AT45DBxxxDPageErase(unsigned long ulPageAddr)
{
	unsigned int i = 0;
	if(ulPageAddr >= AT45DBxxxDInfo.ulTatalPages) return AT45DBxxxD_OP_INVALID;
	while(!AT45DBxxxDWaitReady())
	{
		if(++i > AT45DBxxxD_OVERTIME)
		{
			return AT45DBxxxD_OP_BUSY;
		}
	}

    AT45DBxxxD_CS_CLR;
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_ERPG);
    AT45DBxxxDWritePageAddr(ulPageAddr);
    AT45DBxxxD_CS_SET;

    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief  Erase specified block
//!
//! \param ulPageAddr specifies the block address(0~total blocks).
//!
//! This function is to Erase the specified block
//!
//! \return operation result
//!
//*****************************************************************************
unsigned char AT45DBxxxDBlockErase(unsigned short usBlockAddr)
{
	unsigned int i = 0;

    if(usBlockAddr >= AT45DBxxxDInfo.ulTatalPages/AT45DBxxxD_PAGES_PER_BLOCK) return AT45DBxxxD_OP_INVALID;
    while(!AT45DBxxxDWaitReady())
    {
    	if(++i > AT45DBxxxD_OVERTIME)
    	{
    		return AT45DBxxxD_OP_BUSY;
    	}
    }

    AT45DBxxxD_CS_CLR;
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_ERBL);
    if(ucBinaryPageFlag)
    {
    	if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB321D)
    	{
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(usBlockAddr >> 3));
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((usBlockAddr & 0x00FF) << 5));
    	}
        else if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB081D)
        {
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(usBlockAddr >> 4));
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((usBlockAddr & 0x000F) << 4));
        }
        else
        {
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(usBlockAddr >> 5));
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((usBlockAddr & 0x001F) << 3));
        }
    }
    else
    {
    	if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB321D)
    	{
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(usBlockAddr >> 2));
    		xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((usBlockAddr & 0x00FF) << 6));
    	}
        else if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB081D)
        {
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(usBlockAddr >> 3));
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((usBlockAddr & 0x0007) << 5));
        }
        else
        {
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)(usBlockAddr >> 4));
            xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, (unsigned char)((usBlockAddr & 0x000F) << 4));
        }
    }
    xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0x00);
    AT45DBxxxD_CS_SET;

    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief  Erase specified sector
//!
//! \param usSectorAddr specifies the sector address.
//!
//! This function is to Erase the specified sector
//!
//! \return operation result
//!
//*****************************************************************************
unsigned char AT45DBxxxDSectorErase(unsigned char usSectorAddr)
{
	unsigned int i = 0;

    if(usSectorAddr >= AT45DBxxxDInfo.ulCapacity / AT45DBxxxDInfo.ulSectorSize)
    	return AT45DBxxxD_OP_INVALID;

    while(!AT45DBxxxDWaitReady())
    {
    	if(++i > AT45DBxxxD_OVERTIME)
    	{
    		return AT45DBxxxD_OP_BUSY;
    	}
    }

    if(usSectorAddr == 0)
    {
        for(i=0; i<AT45DBxxxDInfo.ulSectorSize/AT45DBxxxDInfo.ulBlockSize; i++)
        	AT45DBxxxDBlockErase(i);
    }
    else  //if(usSectorAddr != 0)
    {
    	AT45DBxxxD_CS_CLR;
    	xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_ERSC);
        if(ucBinaryPageFlag)
        {
        	//
        	// Binary page size
        	//
        	if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB161D)
        	{
        		xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)((usSectorAddr & 0x1F) << 2) );
        		xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, 0);
        	}
            else if((AT45DBxxxDInfo.usChipID & 0xFF) == AT45DB161D)
        	{
        		xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)((usSectorAddr & 0x0F) << 1) );
        		xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, 0);
        	}
        	else if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB021D)
            {
    		        xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)(usSectorAddr & 0x07) );
                    xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, 0);
            }
    	    else
    	    {
    	        xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)((usSectorAddr & 0x3) >> 1) );
    	        xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)((usSectorAddr & 0x3) << 7) );
    	    }
        }
        else
        {
        	if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB161D)
        	{
        		xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)(usSectorAddr << 3) );
        	}
            else if((AT45DBxxxDInfo.usChipID & 0xFF) == AT45DB161D)
        	{
                xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)((usSectorAddr & 0x0F) << 2) );
        	}
        	else if((AT45DBxxxDInfo.usChipID & 0xFF) > AT45DB021D)
            {
                xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)((usSectorAddr & 0x07) << 1) );
            }
        	else
        	{
                xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, (unsigned char)(usSectorAddr & 0xF) );
            }
            xSPISingleDataReadWrite( AT45DBxxxD_SPI_PORT, 0);
        }
        xSPISingleDataReadWrite(AT45DBxxxD_SPI_PORT, 0x00);
        AT45DBxxxD_CS_SET;
    }
    return AT45DBxxxD_OP_OK;
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
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDChipErase()
{
	unsigned int i = 0;
	if(AT45DBxxxDStatusGet() & AT45DBxxxD_SCPT_EN) return AT45DBxxxD_OP_INVALID;
	while(!AT45DBxxxDWaitReady())
	{
	    if(++i > AT45DBxxxD_OVERTIME)
	    {
	    	return AT45DBxxxD_OP_BUSY;
	    }
	}
    AT45DBxxxD_CS_CLR;

    if(AT45DBxxxDStatusGet() & AT45DBxxxD_SCPT_EN) return AT45DBxxxD_OP_WRITEPROTECT;

    xSPIDataWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_CPER, 4);
    AT45DBxxxD_CS_SET;
    return AT45DBxxxD_OP_OK;
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
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDSectorProtectionEnable(void)
{
	unsigned char i = 0;
	while(!AT45DBxxxDWaitReady())
	{
	    if(++i > AT45DBxxxD_OVERTIME)
	    {
	    	return AT45DBxxxD_OP_BUSY;
	    }
	}

	AT45DBxxxD_CS_CLR;
	xSPIDataWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_ESSP, 4);
	AT45DBxxxD_CS_SET;
#if AT45DBxxxD_HAS_WRITE_PROTECT
	AT45DBxxxDWriteProtectEnable();
#endif
	return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Disable Sector Protection
//!
//! \param None
//!
//! This function is to disable sector protection
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDSectorProtectionDisable(void)
{
	unsigned char i = 0;
	while(!AT45DBxxxDWaitReady())
	{
		if(++i > AT45DBxxxD_OVERTIME)
		{
		    return AT45DBxxxD_OP_BUSY;
		}
	}
#if AT45DBxxxD_HAS_WRITE_PROTECT
	AT45DBxxxDWriteProtectDisable();
#endif
    AT45DBxxxD_CS_CLR;
    xSPIDataWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_DSSP, 4);
    AT45DBxxxD_CS_SET;

    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Program the Sector Protection Register
//!
//! \param  pucBuffer specify whether sectors will be protected or unprotected.
//!
//! This function is to Program the Sector Protection Register to specifies which
//! sectors are to be protected or unprotected with either the software or hardware
//! controlled protection methods. 0xFF needs to be written into the register to
//! enable the sector to be write protected. On the opposite, 0x00 needs to be written
//! to the register to disable write protect.
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDSecProtRegWrite(unsigned char *pucBuffer)
{
	unsigned char i = 0;
	while(!AT45DBxxxDWaitReady())
	{
		if(++i > AT45DBxxxD_OVERTIME)
		{
		    return AT45DBxxxD_OP_BUSY;
		}
	}
	//
	// AT45DB011D has no sector protect register
	//
	if((AT45DBxxxDInfo.usChipID & 0xFF) == 1) return AT45DBxxxD_OP_INVALID;

#if AT45DBxxxD_HAS_WRITE_PROTECT
	if(gucWriteProtectEn) return AT45DBxxxD_OP_INVALID;
#endif
    AT45DBxxxD_CS_CLR;
    //
    // First erase sector protect register
    //
    xSPIDataWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_ESPR, 4);
    AT45DBxxxD_CS_SET;
    xSysCtlDelay(10000);
    while(!AT45DBxxxDWaitReady());
    AT45DBxxxD_CS_CLR;
    //
    // Then write sector protect register
    //
    xSPIDataWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_PSPR, 4);
    if((AT45DBxxxDInfo.usChipID & 0xFF) <= 4)
    {
    	//
    	// 8 sector protect register
    	//
    	xSPIDataWrite(AT45DBxxxD_SPI_PORT, pucBuffer, 8);

    }
    else if((AT45DBxxxDInfo.usChipID & 0xFF) <= 6)
    {
    	//
    	// 16 sector protect register
    	//
        xSPIDataWrite(AT45DBxxxD_SPI_PORT, pucBuffer, 16);
    }
    else if((AT45DBxxxDInfo.usChipID & 0xFF) <= 7)
    {
    	//
    	// 64 sector protect register
    	//
        xSPIDataWrite(AT45DBxxxD_SPI_PORT, pucBuffer,64);
    }
    else if((AT45DBxxxDInfo.usChipID & 0xFF) <= 8)
    {
    	//
    	// 64 sector protect register
    	//
        xSPIDataWrite(AT45DBxxxD_SPI_PORT, pucBuffer,32);
    }
    AT45DBxxxD_CS_SET;

    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Read the Sector Protection Register
//!
//! \param  pucBuffer to store the value of Sector Protection Register after read.
//!
//! This function is to read the sector protection register to get the information
//! of which sectors are to be protected or unprotected
//!
//! \return operation result
//
//*****************************************************************************
unsigned char AT45DBxxxDSecProtRegRead(unsigned char *pucBuffer)
{
	unsigned char i = 0;

	//
	// AT45DB011D has no sector protect register
	//
	if((AT45DBxxxDInfo.usChipID & 0xFF) == 1) return AT45DBxxxD_OP_INVALID;

	while(!AT45DBxxxDWaitReady())
	{
		if(++i > AT45DBxxxD_OVERTIME)
		{
		    return AT45DBxxxD_OP_BUSY;
		}
	}
    AT45DBxxxD_CS_CLR;
    xSPIDataWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_RSPR, 4);
    if((AT45DBxxxDInfo.usChipID & 0xFF) <= 4)
    {
    	//
    	// 8 sector protect register
    	//
    	xSPIDataRead(AT45DBxxxD_SPI_PORT, pucBuffer, 8);

    }
    else if((AT45DBxxxDInfo.usChipID & 0xFF) <= 6)
    {
    	//
    	// 16 sector protect register
    	//
        xSPIDataRead(AT45DBxxxD_SPI_PORT, pucBuffer, 16);
    }
    else if((AT45DBxxxDInfo.usChipID & 0xFF) <= 7)
    {
    	//
    	// 64 sector protect register
    	//
        xSPIDataRead(AT45DBxxxD_SPI_PORT, pucBuffer,64);
    }
    else if((AT45DBxxxDInfo.usChipID & 0xFF) <= 8)
    {
    	//
    	// 64 sector protect register
    	//
        xSPIDataRead(AT45DBxxxD_SPI_PORT, pucBuffer,32);
    }
    AT45DBxxxD_CS_SET;
    return AT45DBxxxD_OP_OK;
}

//*****************************************************************************
//
//! \brief Set AT45DBxxxD page to binary page
//!
//! \param  None
//!
//! This function is to Set AT45DBxxxD page to binary page.
//! \note once the device is configured to binary page size, it cannot be reconfigured again.
//! \note this operation is effective after one power cycle(power down then up)
//!
//! \return None
//
//*****************************************************************************
void AT45DBxxxDBinaryPageSet(void)
{

    AT45DBxxxD_CS_CLR;
    xSPIDataWrite(AT45DBxxxD_SPI_PORT, AT45DBxxxD_CMD_PGCR, 4);
    AT45DBxxxD_CS_SET;
    ucBinaryPageFlag = 1;
}

#if AT45DBxxxD_HAS_WRITE_PROTECT
//*****************************************************************************
//
//! \brief AT45DBxxxD Write Protect Disable
//!
//! \param  None
//!
//! This function is to disable hardware AT45DBxxxD Write Protect
//! by set WP Pin to 0
//!
//! \return None
//
//*****************************************************************************
void AT45DBxxxDWriteProtectDisable(void)
{
	gucWriteProtectEn = 0;
	xGPIOSPinWrite(AT45DBxxxD_PIN_WP, 1);
}

//*****************************************************************************
//
//! \brief AT45DBxxxD Write Protect Enable
//!
//! \param  None
//!
//! This function is to enable hardware AT45DBxxxD Write Protect
//! by set WP Pin to 1
//!
//! \return None
//
//*****************************************************************************
void AT45DBxxxDWriteProtectEnable(void)
{
	gucWriteProtectEn = 1;
	xGPIOSPinWrite(AT45DBxxxD_PIN_WP, 0);
}
#endif

#if AT45DBxxxD_HAS_RESET
void AT45DBxxxDReset(void)
{
	xGPIOSPinWrite(AT45DBxxxD_PIN_RST, 0);
	xSysCtlDelay(10000);
	xGPIOSPinWrite(AT45DBxxxD_PIN_RST, 1);
}
#endif
