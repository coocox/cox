//*****************************************************************************
//
//! \file M25Pxx.c
//! \brief the M25Pxx Driver.
//! \version 1.0
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
#include "Xhw_spi.h"
#include "xgpio.h"
#include "M25Pxx.h"
#include "hw_M25Pxx.h"

#if (M25Pxx_Device == M25P10)
#define M25Pxx_MAX_CLOCK        20000000

#define M25PxxPAGE_SIZE         M25P10_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P10_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P10_SECTORS
#define M25Pxx_PAGES            M25P10_PAGES
#define M25Pxx_SIZE             M25P10_SIZE

#elif (M25Pxx_Device == M25P20)
#define M25Pxx_MAX_CLOCK        25000000

#define M25PxxPAGE_SIZE         M25P20_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P20_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P20_SECTORS
#define M25Pxx_PAGES            M25P20_PAGES
#define M25Pxx_SIZE             M25P20_SIZE

#elif (M25Pxx_Device == M25P40)

#define M25Pxx_MAX_CLOCK        25000000

#define M25PxxPAGE_SIZE         M25P40_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P40_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P40_SECTORS
#define M25Pxx_PAGES            M25P40_PAGES
#define M25Pxx_SIZE             M25P40_SIZE

#elif (M25Pxx_Device == M25P80)

#define M25Pxx_MAX_CLOCK        25000000

#define M25PxxPAGE_SIZE         M25P80_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P80_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P80_SECTORS
#define M25Pxx_PAGES            M25P80_PAGES
#define M25Pxx_SIZE             M25P80_SIZE

#elif (M25Pxx_Device == M25P16)

#define M25Pxx_MAX_CLOCK        50000000

#define M25PxxPAGE_SIZE         M25P16_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P16_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P16_SECTORS
#define M25Pxx_PAGES            M25P16_PAGES
#define M25Pxx_SIZE             M25P16_SIZE

#elif (M25Pxx_Device == M25P32)

#define M25Pxx_MAX_CLOCK        50000000

#define M25PxxPAGE_SIZE         M25P32_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P32_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P32_SECTORS
#define M25Pxx_PAGES            M25P32_PAGES
#define M25Pxx_SIZE             M25P32_SIZE

#elif (M25Pxx_Device == M25P64)

#define M25Pxx_MAX_CLOCK        50000000

#define M25PxxPAGE_SIZE         M25P64_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P64_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P64_SECTORS
#define M25Pxx_PAGES            M25P64_PAGES
#define M25Pxx_SIZE             M25P64_SIZE

#elif (M25Pxx_Device == M25P128)

#define M25Pxx_MAX_CLOCK        50000000

#define M25PxxPAGE_SIZE         M25P128_PAGE_SIZE
#define M25PxxPAGES_PER_SECTORS M25P128_PAGES_PER_SECTORS
#define M25Pxx_SECTORS          M25P128_SECTORS
#define M25Pxx_PAGES            M25P128_PAGES
#define M25Pxx_SIZE             M25P128_SIZE

#endif


//*****************************************************************************
//
//! \brief Initialize M25Pxx and SPI  
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
void M25PxxInit(unsigned long ulSpiClock)
{
    //
    // The max clock rate of M25Pxx is 20M to 50M Hz acoording to Datasheet
    //
    xASSERT((ulSpiClock > 0) && (ulSpiClock < M25Pxx_MAX_CLOCK));
    //
    // Enable the GPIOx port which is connected with M25Pxx 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPort(FLASH_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(FLASH_PIN_SPI_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(FLASH_PIN_SPI_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(FLASH_PIN_SPI_MOSI));
    //
    // Enable the SPIx which is connected with M25Pxx
    //
    xSysCtlPeripheralEnable2(FLASH_PIN_SPI_PORT);
    //
    // Set GPIOD0 as a chip select pin and set it as OUT_MODE
    //
    xGPIOSPinDirModeSet(FLASH_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);
    
#if (M25Pxx_HOLD > 0)
    xGPIOSPinDirModeSet(FLASH_PIN_HOLD, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(FLASH_PIN_HOLD, 1);
#endif
 
#if (M25Pxx_WRITE_PROTECT > 0)
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
//! \brief Read M25Pxx ID
//! 
//! \param None
//!
//! This function is to Read ID
//! 
//! \return M25Pxx ID in Hexadecimal
//
//*****************************************************************************
unsigned long M25PxxIDcodeGet(void)
{
    unsigned long ulIDcode;
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
    ucInstruction = M25Pxx_CMD_RDID;
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
    xSPIDataRead(FLASH_PIN_SPI_PORT, &ucLowDeviID, 1);
    //
    //Step 3 Disable chip select
    //    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);

    ulIDcode = ucManuID << 16;
    ulIDcode |= ucHighDeviID << 8;
    ulIDcode |= ucLowDeviID;
    return ulIDcode;
}

//*****************************************************************************
//
//! \brief Read M25Pxx Status Register
//! 
//! \param None
//!
//! This function is to Read M25Pxx Status Register:the bit field follows:
//! BIT7  6   5   4   3   2   1   0 
//£¡SRWD  0   0  BP2 BP1 BP0 WEL WIP 
//! 
//! \return the value of status
//£¡
//*****************************************************************************
unsigned char M25PxxStatusRegRead(void)    
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
    ucCommand = M25Pxx_CMD_RDSR;
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
//! \brief Wait for M25Pxx is not busy
//! 
//! \param None
//!
//! This function is to Wait for M25Pxx is not busy
//! 
//! \return None
//
//*****************************************************************************
void M25PxxWaitNotBusy(void)    
{    
    //
    //Wait the bit of busy is clear
    //
    while((M25PxxStatusRegRead() & 0x01) == 0x01); 
}
//*****************************************************************************
//
//! \brief M25Pxx write enable
//! 
//! \param None
//!
//! This function is to enable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void M25PxxWriteEnable(void)
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
    ucCommand = M25Pxx_CMD_WREN;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief M25Pxx write disable
//! 
//! \param None
//!
//! This function is to disable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void M25PxxWriteDisable(void)
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
    ucCommand = M25Pxx_CMD_WRDI;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief  write a page(1~256byte) data to M25Pxx
//!
//! \param ucBuffer specifies the location data which will be .
//! \param ulWriteAddr specifies the address which data will be written 
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to write a page(1~256byte) data to M25Pxx, The appointed
//! byte length data will be writen in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void M25PxxPageWrite(unsigned char* ucBuffer, unsigned long  ulWriteAddr,
                     unsigned short usNumByteToWrite)
{
    unsigned char ucCommand; 
    unsigned char ucAddr;
    xASSERT((usNumByteToWrite > 0) && (usNumByteToWrite <= 256));
    //
    //Step 1 Set write enable
    //
    M25PxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command page program
    // 
    ucCommand = M25Pxx_CMD_PP;
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
    M25PxxWaitNotBusy();       
}

//*****************************************************************************
//
//! \brief  Writes more than one byte to the FLASH M25Pxx
//!
//! \param ucBuffer specifies the location data which will be .
//! \param ulWriteAddr specifies the address which data will be written 
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to Writes more than one byte to the FLASH M25Pxx, The 
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

    usFirstSize = ulWriteAddr % M25PxxPAGE_SIZE;

    ulWriteAdrTemp = ulWriteAddr - usFirstSize;
    usFirstSize = M25PxxPAGE_SIZE - usFirstSize;
    pucWriteBuf = pucBuffer;

    if(usFirstSize < usNumByteToWrite) 
    {
        usPageNum  = (usNumByteToWrite - usFirstSize) / M25PxxPAGE_SIZE;
        usLastSize = (usNumByteToWrite - usFirstSize) % M25PxxPAGE_SIZE;
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
        M25PxxPageWrite (pucBuffer, ulWriteAddr, usFirstSize);
        ulWriteAdrTemp += M25PxxPAGE_SIZE;
        pucWriteBuf += usFirstSize;

        M25PxxWaitNotBusy();
    }

    for(i=0; i<usPageNum; i++) 
    {
        M25PxxPageWrite (pucBuffer, ulWriteAddr, M25PxxPAGE_SIZE);
        ulWriteAdrTemp += M25PxxPAGE_SIZE;
        pucWriteBuf += M25PxxPAGE_SIZE;

        M25PxxWaitNotBusy();
    }
    
    //
    //Write Last Page
    //
    if(usLastSize) 
    {
        M25PxxPageWrite(pucBuffer, ulWriteAddr, usLastSize);
    }

    return;
}

//*****************************************************************************
//
//! \brief  Read data from M25Pxx
//!
//! \param ucBuffer specifies the location data which will be store.
//! \param ulWriteAddr specifies the address which data will be read 
//! \param usNumByteToWrite specifies the length of data will be read.
//!
//! This function is to read data from M25Pxx, The appointed byte length data will
//! be read in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void M25PxxDataRead(unsigned char* ucBuffer, unsigned long  ulReadAddr,
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
    ucCommand = M25Pxx_CMD_READ;
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
//! \brief  Read data from M25Pxx at Higher Speed
//!
//! \param ucBuffer specifies the location data which will be store.
//! \param ulWriteAddr specifies the address which data will be read 
//! \param usNumByteToWrite specifies the length of data will be read.
//!
//! This function is to read data from M25Pxx, The appointed byte length data will
//! be read in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void M25PxxDataFastRead(unsigned char* ucBuffer, unsigned long  ulReadAddr,
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
    ucCommand = M25Pxx_CMD_READ;
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
void M25PxxChipErase(void)
{
    unsigned char ucCommand;
    //
    //Step 1 Set write enable
    //
    M25PxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Chip Erase
    // 
    ucCommand = M25Pxx_CMD_BE;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 4 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 5  wait for the operation is over
    //
    M25PxxWaitNotBusy(); 
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
void M25PxxSectorErase(unsigned long ulDstAddr)
{
    unsigned char ucCommand;
    unsigned char ucAddrBuffer[3];
    ulDstAddr = ulDstAddr * 4096;
    ucAddrBuffer[0] = (unsigned char)(ulDstAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulDstAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulDstAddr >> 0);
    //
    //Step 1 Set write enable
    //
    M25PxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Sector Erase
    // 
    ucCommand = M25Pxx_CMD_SE;
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
    M25PxxWaitNotBusy(); 
}

//*****************************************************************************
//
//! \brief M25Pxx write status register
//! 
//! \param ulDstAddr specifies the status value which will be writen
//!
//! This function is to write status value to status register
//! 
//! \return none
//
//*****************************************************************************
void M25PxxStatusRegWrite(unsigned char ucStatusVal)
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
    ucCommand = M25Pxx_CMD_WRSR;
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
//! \brief Disable M25Pxx 
//!
//! \param None
//!
//! This function is to Disable M25Pxx
//! 
//! \return None.
//
//*****************************************************************************
void M25PxxDisable(void)
{
    //xSysCtlPeripheralDisable(FLASH_PIN_SPI_PORT);
}

//*****************************************************************************
//
//! \brief Read M25Pxx Electronic Signature
//! 
//! \param None
//!
//! This function is to Read Electronic Signature
//! 
//! \return M25Pxx Electronic Signature in Hexadecimal
//
//*****************************************************************************
unsigned short M25PxxEScodeGet(void)
{
    unsigned char usEScode;
    unsigned char usDummy;
    unsigned char ucInstruction;

    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer intruction of "get ID"
    //
    ucInstruction = M25Pxx_CMD_RES;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucInstruction, 1);
    //
    //Step 3 Transfer 3 Dummy Bytes
    //
    usDummy = 0xFF;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &usDummy, 3);
    //
    // Get Electronic Signature 
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, &usEScode, 1);
    
    //
    //Step 4 Disable chip select
    //    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    return usEScode;
}

//*****************************************************************************
//
//! \brief Get M25Pxx Page Size
//! 
//! \param None
//!
//! This function is to get M25Pxx Page Size
//! 
//! \return M25Pxx Page Size
//
//*****************************************************************************
unsigned long M25PxxPageSizeGet(void)
{
    return M25PxxPAGE_SIZE;
}

//*****************************************************************************
//
//! \brief Get M25Pxx Sector Size
//! 
//! \param None
//!
//! This function is to get M25Pxx Sector Size
//! 
//! \return M25Pxx Sector Size
//
//*****************************************************************************
unsigned long M25PxxSectorSizeGet(void)
{
    return (M25PxxPAGE_SIZE * M25PxxPAGES_PER_SECTORS);
}

//*****************************************************************************
//
//! \brief Get M25Pxx Chip Size
//! 
//! \param None
//!
//! This function is to get M25Pxx Chip Size
//! 
//! \return M25Pxx Chip Size
//
//*****************************************************************************
unsigned long M25PxxChipSizeGet(void)
{
    return M25Pxx_SIZE;
}

#if (M25Pxx_HOLD > 0)

//*****************************************************************************
//
//! \brief Enable M25Pxx hold input
//! 
//! \param None
//!
//! This function is to enable M25Pxx hold input.
//! 
//! \return None.
//
//*****************************************************************************
void M25PxxHoldEnable(void)
{
    xGPIOSPinWrite(FLASH_PIN_HOLD, 0);
}

//*****************************************************************************
//
//! \brief Disable M25Pxx hold input
//! 
//! \param None
//!
//! This function is to disable M25Pxx hold input.
//! 
//! \return None.
//
//*****************************************************************************
void M25PxxHoldDisable(void)
{
    xGPIOSPinWrite(FLASH_PIN_HOLD, 1);
}
#endif
 
#if (M25Pxx_WRITE_PROTECT > 0)

//*****************************************************************************
//
//! \brief Enable M25Pxx write protect .
//! 
//! \param None
//!
//! This function is to enable M25Pxx write protect .
//! 
//! \return None.
//
//*****************************************************************************
void M25PxxWriteProtectEnable(void)
{
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 0);
}

//*****************************************************************************
//
//! \brief Disable M25Pxx write protect .
//! 
//! \param None
//!
//! This function is to disable M25Pxx write protect .
//! 
//! \return None.
//
//*****************************************************************************
void M25PxxWriteProtectDisable(void)
{
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 1);
}
#endif