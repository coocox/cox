//*****************************************************************************
//
//! \file AT25FS0x.c
//! \brief the AT25FS0x Driver.
//! \version V2.1.1.0
//! \date 9/1/2011
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xgpio.h"
#include "AT25FS0x.h"
#include "hw_AT25FS0x.h"

#if (AT25FS0x_Device == AT25FS010)
#define M25Pxx_MAX_CLOCK        50000000

#define AT25FS0x_PAGE_SIZE      AT25FS010_PAGE_SIZE 
#define AT25FS0x_SECTOR_SIZE    AT25FS010_SECTOR_SIZE
#define AT25FS0x_BLOCK_SIZE     AT25FS010_BLOCK_SIZE
#define AT25FS0x_CHIP_SIZE      AT25FS010_CHIP_SIZE

#elif (AT25FS0x_Device == AT25FS040)
#define M25Pxx_MAX_CLOCK        50000000

#define AT25FS0x_PAGE_SIZE      AT25FS040_PAGE_SIZE 
#define AT25FS0x_SECTOR_SIZE    AT25FS040_SECTOR_SIZE
#define AT25FS0x_BLOCK_SIZE     AT25FS040_BLOCK_SIZE
#define AT25FS0x_CHIP_SIZE      AT25FS040_CHIP_SIZE
#endif 

//*****************************************************************************
//
//! \brief Initialize AT25FS0x and SPI  
//!
//! \param ulClock specifies the SPI Clock Rate
//!
//! This function initialize the mcu SPI as master and specified SPI port.Set 
//! PD0->CS PD1->CLK PD2->MISO and PD3->MOSI,most of all it check the first
//! convert is finished or not in order to execute the following operation
//! 
//! \return None.
//
//*****************************************************************************
void AT25FS0xInit(unsigned long ulSpiClock)
{
    //
    // The max clock rate of M25Pxx is 20M to 50M Hz acoording to Datasheet
    //
    xASSERT((ulSpiClock > 0) && (ulSpiClock < M25Pxx_MAX_CLOCK));
    //
    // Enable the GPIOx port which is connected with M25Pxx 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_MOSI));
    //
    // Enable the SPIx which is connected with M25Pxx
    //
    xSysCtlPeripheralEnable2(FLASH_PIN_SPI_PORT);
    //
    // Set GPIOD0 as a chip select pin and set it as OUT_MODE
    //
    xGPIOSPinDirModeSet(FLASH_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);
    
#if (AT25FS0x_HOLD > 0)
    xGPIOSPinDirModeSet(FLASH_PIN_HOLD, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(FLASH_PIN_HOLD, 1);
#endif
 
#if (AT25FS0x_WRITE_PROTECT > 0)
    xGPIOSPinDirModeSet(FLASH_PIN_WRITE_PROTECT, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 1);
#endif
     
    //
    // PD1 as SPI2.CLK
    //
    xSPinTypeSPI(SPI_CLK, FLASH_PIN_SPI_CLK);
    //
    // PD2 as SPI2.MISO
    // MISO20 => SPI0MISO
    //
    xSPinTypeSPI(SPI_MISO, FLASH_PIN_SPI_MISO);
    //
    // PD3 as SPI2.MOSI
    // MOSI20 => SPI0MISO
    //
    xSPinTypeSPI(SPI_MOSI, FLASH_PIN_SPI_MOSI); 
    //
    // Configure MCU as a master device , 16 bits data width ,MSB first,Mode_0
    //
    xSPIConfigSet(FLASH_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_0 |
                                                         xSPI_MODE_MASTER | 
                                                           xSPI_MSB_FIRST |
                                                          xSPI_DATA_WIDTH8);
    //
    // Disable M25Pxx when Power up
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief Read AT25FS0x ID
//! 
//! \param None
//!
//! This function is to Read ID
//! 
//! \return AT25FS0x ID in Hexadecimal
//
//*****************************************************************************
unsigned long AT25FS0xIDcodeGet(void)
{
    unsigned short usIDcode;
    unsigned char ucInstruction;
    unsigned char ucManuID;
    unsigned char ucHighDeviID;
    unsigned char ucLowDeviID;
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer intruction of "get ID"
    //
    ucInstruction = AT25FS0x_CMD_RDID;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucInstruction, 1);
    
    //
    // Get Manufacture ID
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, &ucManuID, 1);
    //
    // Get Devidce ID
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, &ucHighDeviID, 1);
    xSPIDataRead(FLASH_PIN_SPI_PORT, &ucLowDeviID, 1);
    //
    //Step 3 Disable chip select
    //    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);

    usIDcode = ucManuID << 16;
    usIDcode |= ucHighDeviID << 8;
    usIDcode |= ucLowDeviID;
    return usIDcode;
}

//*****************************************************************************
//
//! \brief Read AT25FS0x Status Register
//! 
//! \param None
//!
//! This function is to Read AT25FS0x Status Register:the bit field follows:
//! BIT7  6   5   4   3   2   1   0 
//£¡SRWD  0   0  BP2 BP1 BP0 WEL WIP 
//! 
//! \return the value of status
//£¡
//*****************************************************************************
unsigned char AT25FS0xStatusRegRead(void)    
{   
    unsigned char ucStatus=0;
    unsigned char ucCommand;
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command Read Status Register 
    //
    ucCommand = AT25FS0x_CMD_RDSR;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Read status Register
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, &ucStatus, 1);
    //
    //Step 4 Disable chip select 
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    return ucStatus;    
}

//*****************************************************************************
//
//! \brief Wait for AT25FS0x is not busy
//! 
//! \param None
//!
//! This function is to Wait for AT25FS0x is not busy
//! 
//! \return None
//
//*****************************************************************************
void AT25FS0xWaitNotBusy(void)    
{    
    //
    //Wait the bit of busy is clear
    //
    while((AT25FS0xStatusRegRead() & 0x01) == 0x01); 
}
//*****************************************************************************
//
//! \brief AT25FS0x write enable
//! 
//! \param None
//!
//! This function is to enable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void AT25FS0xWriteEnable(void)
{
    unsigned char ucCommand;
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command Write Enable
    // 
    ucCommand = AT25FS0x_CMD_WREN;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief AT25FS0x write disable
//! 
//! \param None
//!
//! This function is to disable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void AT25FS0xWriteDisable(void)
{
    unsigned char ucCommand;
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command Write Disable
    // 
    ucCommand = AT25FS0x_CMD_WRDI;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief  write a page(1~256byte) data to AT25FS0x
//!
//! \param ucBuffer specifies the location data which will be .
//! \param ulWriteAddr specifies the address which data will be written 
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to write a page(1~256byte) data to AT25FS0x, The appointed
//! byte length data will be writen in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void AT25FS0xPageWrite(unsigned char* ucBuffer, unsigned long  ulWriteAddr,
                                               unsigned short usNumByteToWrite)
{
    unsigned char ucCommand; 
    unsigned char ucAddr;
    xASSERT((usNumByteToWrite > 0) && (usNumByteToWrite <= 256));
    //
    //Step 1 Set write enable
    //
    AT25FS0xWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command page program
    // 
    ucCommand = AT25FS0x_CMD_PP;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 4 Transfer the address(24bit) which data will be written
    //
    ucAddr = (unsigned char)(ulWriteAddr >> 16);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    ucAddr = (unsigned char)(ulWriteAddr >> 8);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    ucAddr = (unsigned char)(ulWriteAddr);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    //
    //Step 5 Write Data
    //

    xSPIDataWrite(FLASH_PIN_SPI_PORT, ucBuffer, usNumByteToWrite); 

    //
    //Step 6  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 7  wait for the operation is over
    //
    AT25FS0xWaitNotBusy();       
}

//*****************************************************************************
//
//! \brief  Writes more than one byte to the FLASH AT25FS0x
//!
//! \param ucBuffer specifies the location data which will be .
//! \param ulWriteAddr specifies the address which data will be written 
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to Writes more than one byte to the FLASH AT25FS0x, The 
//! appointed byte length data will be writen in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void M25PxxWrite(unsigned char* pucBuffer, unsigned long  ulWriteAddr,
                 unsigned short usNumByteToWrite)
{
    const unsigned char *pucWriteBuf;
    unsigned short usFirstSize, usLastSize, usPageNum, i;
    unsigned long ulWriteAdrTemp;

    usFirstSize = ulWriteAddr % AT25FS0x_PAGE_SIZE;

    ulWriteAdrTemp = ulWriteAddr - usFirstSize;
    usFirstSize = AT25FS0x_PAGE_SIZE - usFirstSize;
    pucWriteBuf = pucBuffer;

    if(usFirstSize < usNumByteToWrite) 
    {
        usPageNum  = (usNumByteToWrite - usFirstSize) / AT25FS0x_PAGE_SIZE;
        usLastSize = (usNumByteToWrite - usFirstSize) % AT25FS0x_PAGE_SIZE;
    } 
    else 
    {
        usFirstSize = usNumByteToWrite;
        usPageNum = 0;
    }
    
    //
    //Write First Page
    //
    if(usFirstSize != 0)
    {
        AT25FS0xPageWrite (pucBuffer, ulWriteAddr, usFirstSize);
        ulWriteAdrTemp += AT25FS0x_PAGE_SIZE;
        pucWriteBuf += usFirstSize;

        AT25FS0xWaitNotBusy();
    }

    for(i=0; i<usPageNum; i++) 
    {
        AT25FS0xPageWrite (pucBuffer, ulWriteAddr, AT25FS0x_PAGE_SIZE);
        ulWriteAdrTemp += AT25FS0x_PAGE_SIZE;
        pucWriteBuf += AT25FS0x_PAGE_SIZE;

        AT25FS0xWaitNotBusy();
    }
    
    //
    //Write Last Page
    //
    if(usLastSize) 
    {
        AT25FS0xPageWrite(pucBuffer, ulWriteAddr, usLastSize);
    }

    return;
}

//*****************************************************************************
//
//! \brief  Read data from AT25FS0x
//!
//! \param ucBuffer specifies the location data which will be store.
//! \param ulWriteAddr specifies the address which data will be read 
//! \param usNumByteToWrite specifies the length of data will be read.
//!
//! This function is to read data from AT25FS0x, The appointed byte length data will
//! be read in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void AT25FS0xDataRead(unsigned char* ucBuffer, unsigned long  ulReadAddr,
                                                  unsigned long ulNumByteToRead)
{
    unsigned char ucCommand; 
    unsigned char ucAddrBuffer[3];
    ucAddrBuffer[0] = (unsigned char)(ulReadAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulReadAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulReadAddr >> 0);
//    xASSERT((usNumByteToRead > 0) && (usNumByteToRead <= 2097152));
    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command page program
    // 
    ucCommand = AT25FS0x_CMD_READ;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Transfer the address(24bit) which data will be read
    //
    xSPIDataWrite(FLASH_PIN_SPI_PORT, ucAddrBuffer, 3);
    //
    //Step 4 read Data
    //

    xSPIDataRead(FLASH_PIN_SPI_PORT, ucBuffer, ulNumByteToRead); 

    //
    //Step 5  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1); 
}

//*****************************************************************************
//
//! \brief  Read data from AT25FS0x at Higher Speed
//!
//! \param ucBuffer specifies the location data which will be store.
//! \param ulWriteAddr specifies the address which data will be read 
//! \param usNumByteToWrite specifies the length of data will be read.
//!
//! This function is to read data from AT25FS0x, The appointed byte length data will
//! be read in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void AT25FS0xDataFastRead(unsigned char* ucBuffer, unsigned long  ulReadAddr,
                                                 unsigned long ulNumByteToRead)
{
    unsigned char ucCommand; 
    unsigned char ucDummy; 
    unsigned char ucAddrBuffer[3];
    ucAddrBuffer[0] = (unsigned char)(ulReadAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulReadAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulReadAddr >> 0);
//    xASSERT((usNumByteToRead > 0) && (usNumByteToRead <= 2097152));
    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command page program
    // 
    ucCommand = AT25FS0x_CMD_READ;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Transfer the address(24bit) which data will be read
    //
    xSPIDataWrite(FLASH_PIN_SPI_PORT, ucAddrBuffer, 3);
    
    //
    //Step 3 Write Dummy Byte
    //
    ucDummy = 0xFF;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucDummy, 1); 
    //
    //Step 4 read Data
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, ucBuffer, ulNumByteToRead); 

    //
    //Step 3  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1); 
}

//*****************************************************************************
//
//! \brief Erase all chip
//! 
//! \param None
//!
//! This function is to Erase all chip
//! 
//! \return none
//
//*****************************************************************************
void AT25FS0xChipErase(void)
{
    unsigned char ucCommand;
    //
    //Step 1 Set write enable
    //
    AT25FS0xWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Chip Erase
    // 
    ucCommand = AT25FS0x_CMD_CE;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 4 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 5  wait for the operation is over
    //
    AT25FS0xWaitNotBusy(); 
}

//*****************************************************************************
//
//! \brief Erase a sector
//! 
//! \param ulDstAddr specifies the sector address which will be erased.and for
//! W25X16,it must be smaller than 512
//! This function is to Erase a sector
//! 
//! \return none
//
//*****************************************************************************
void AT25FS0xSectorErase(unsigned long ulDstAddr)
{
    unsigned char ucCommand;
    unsigned char ucAddrBuffer[3];
    ulDstAddr = ulDstAddr;
    ucAddrBuffer[0] = (unsigned char)(ulDstAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulDstAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulDstAddr >> 0);
    //
    //Step 1 Set write enable
    //
    AT25FS0xWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Sector Erase
    // 
    ucCommand = AT25FS0x_CMD_SE;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 4 Transfer the address which will be erased
    //
    xSPIDataWrite(FLASH_PIN_SPI_PORT, ucAddrBuffer, 3);
    //
    //Step 5 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 6  wait for the operation is over
    //
    AT25FS0xWaitNotBusy(); 
}

//*****************************************************************************
//
//! \brief Erase a Block
//! 
//! \param ulDstAddr specifies the Block address which will be erased.and for
//! AT25FS0x,
//! This function is to Erase a Block
//! 
//! \return none
//
//*****************************************************************************
void AT25FS0xBlockErase(unsigned long ulDstAddr)
{
    unsigned char ucCommand;
    unsigned char ucAddrBuffer[3];
    ulDstAddr = ulDstAddr;
    ucAddrBuffer[0] = (unsigned char)(ulDstAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulDstAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulDstAddr >> 0);
    //
    //Step 1 Set write enable
    //
    AT25FS0xWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Sector Erase
    // 
    ucCommand = AT25FS0x_CMD_BE;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 4 Transfer the address which will be erased
    //
    xSPIDataWrite(FLASH_PIN_SPI_PORT, ucAddrBuffer, 3);
    //
    //Step 5 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 6  wait for the operation is over
    //
    AT25FS0xWaitNotBusy(); 
}
//*****************************************************************************
//
//! \brief AT25FS0x write status register
//! 
//! \param ulDstAddr specifies the status value which will be writen
//!
//! This function is to write status value to status register
//! 
//! \return none
//
//*****************************************************************************
void AT25FS0xStatusRegWrite(unsigned char ucStatusVal)
{
    unsigned char ucCommand;
    unsigned char ucStatus;
    ucStatus = ucStatusVal;
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command Write Status Value
    // 
    ucCommand = AT25FS0x_CMD_WRSR;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Write your status value that you need
    //
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucStatus, 1);
    //
    //Step 4 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief Disable AT25FS0x 
//!
//! \param None
//!
//! This function is to Disable AT25FS0x
//! 
//! \return None.
//
//*****************************************************************************
void AT25FS0xDisable(void)
{
    xSysCtlPeripheralDisable(FLASH_PIN_SPI_PORT);
}


//*****************************************************************************
//
//! \brief Get AT25FS0x Page Size
//! 
//! \param None
//!
//! This function is to get AT25FS0x Page Size
//! 
//! \return AT25FS0x Page Size
//
//*****************************************************************************
unsigned long AT25FS0xPageSizeGet(void)
{
    return AT25FS0x_PAGE_SIZE;
}

//*****************************************************************************
//
//! \brief Get AT25FS0x Sector Size
//! 
//! \param None
//!
//! This function is to get AT25FS0x Sector Size
//! 
//! \return AT25FS0x Sector Size
//
//*****************************************************************************
unsigned long AT25FS0xSectorSizeGet(void)
{
    return AT25FS0x_SECTOR_SIZE;
}

//*****************************************************************************
//
//! \brief Get AT25FS0x Chip Size
//! 
//! \param None
//!
//! This function is to get AT25FS0x Chip Size
//! 
//! \return AT25FS0x Chip Size
//
//*****************************************************************************
unsigned long AT25FS0xChipSizeGet(void)
{
    return AT25FS0x_CHIP_SIZE;
}

#if (AT25FS0x_HOLD > 0)

//*****************************************************************************
//
//! \brief Enable AT25FS0x hold input
//! 
//! \param None
//!
//! This function is to enable AT25FS0x hold input.
//! 
//! \return None.
//
//*****************************************************************************
void AT25FS0xHoldEnable(void)
{
    xGPIOSPinWrite(FLASH_PIN_HOLD, 0);
}

//*****************************************************************************
//
//! \brief Disable AT25FS0x hold input
//! 
//! \param None
//!
//! This function is to disable AT25FS0x hold input.
//! 
//! \return None.
//
//*****************************************************************************
void AT25FS0xHoldDisable(void)
{
    xGPIOSPinWrite(FLASH_PIN_HOLD, 1);
}
#endif
 
#if (AT25FS0x_WRITE_PROTECT > 0)

//*****************************************************************************
//
//! \brief Enable AT25FS0x write protect .
//! 
//! \param None
//!
//! This function is to enable AT25FS0x write protect .
//! 
//! \return None.
//
//*****************************************************************************
void AT25FS0xWriteProtectEnable(void)
{
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 0);
}

//*****************************************************************************
//
//! \brief Disable AT25FS0x write protect .
//! 
//! \param None
//!
//! This function is to disable AT25FS0x write protect .
//! 
//! \return None.
//
//*****************************************************************************
void AT25FS0xWriteProtectDisable(void)
{
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 1);
}
#endif