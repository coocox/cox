//*****************************************************************************
//
//! \file w25Xxx.c
//! \brief Driver for flash W25Xxx.
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
#include "w25xxx.h"
#include "hw_W25Xxx.h"


//*****************************************************************************
//
//! \brief Initialize W25Xxx and SPI  
//!
//! \param ulClock specifies the SPI Clock Rate
//!
//! This function is to initialize the MCU as master and specified SPI port.Set
//! FLASH_PIN_SPI_CS as CS, FLASH_PIN_SPI_CLK as CLK, FLASH_PIN_SPI_MISO ->MISO  
//! and FLASH_PIN_SPI_MOSI->MOSI.
//! 
//! \return None.
//
//*****************************************************************************
void W25XxxInit(unsigned long ulSpiClock)
{
    //
    // The max clock rate of W25Xxx is 75M Hz acoording to Datasheet
    //
    xASSERT((ulSpiClock > 0) && (ulSpiClock < 75000000));
    
    //
    // Enable the GPIOx port which is connected with W25Xxx 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_CS));
    
    //
    // Enable the SPIx which is connected with W25Xxx
    //
    xSysCtlPeripheralEnable2(FLASH_PIN_SPI_PORT);
    
    //
    // Set FLASH_PIN_SPI_CS as a chip select pin and set it as OUT_MODE
    //
    xGPIOSPinDirModeSet(FLASH_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);
    
    //
    // Set FLASH_PIN_SPI_CLK as SPI2.CLK
    //
    xSPinTypeSPI(SPI2CLK, FLASH_PIN_SPI_CLK);
    
    //
    // Set FLASH_PIN_SPI_MISO as SPI2.MISO
    //
    xSPinTypeSPI(SPI2MISO, FLASH_PIN_SPI_MISO);
    
    //
    // Set FLASH_PIN_SPI_MOSI as SPI2.MOSI
    //
    xSPinTypeSPI(SPI2MOSI, FLASH_PIN_SPI_MOSI);
    
    //
    // Configure MCU as a master device , 8 bits data width ,MSB first,Mode_0
    //
    xSPIConfigSet(FLASH_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_0 |
                                                         xSPI_MODE_MASTER | 
                                                           xSPI_MSB_FIRST |
                                                          xSPI_DATA_WIDTH8);
    //
    // Disable W25Xxx when Power up
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief Read W25Xxx ID
//! 
//! \param None
//!
//! This function is to Read ID
//! 
//! \return W25Xxx ID in Hexadecimal
//
//*****************************************************************************
unsigned short W25XxxIDcodeGet(void)
{
    unsigned short usIDcode;
    unsigned char ucInstruction,ucAddr,ucManuID,ucDeviID;
    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 2 Transfer intruction of "get ID"
    //
    ucInstruction = W25Xxx_INS_GET_ID;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucInstruction, 1);
    
    //
    //Step 3 Transfer Address
    //
    ucAddr = 0x00;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1); 
    
    //
    // Get Manufacture ID
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, &ucManuID, 1);
    
    //
    // Get Devidce ID
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, &ucDeviID, 1);
    
    //
    //Step 4 Disable chip select
    //    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);

    usIDcode = ucManuID << 8;
    usIDcode |= ucDeviID;
    
    return usIDcode;
}

//*****************************************************************************
//
//! \brief Read W25Xxx Status Register
//! 
//! \param None
//!
//! This function is to Read W25Xxx Status Register:the bit field follows:
//! BIT7  6   5   4   3   2   1   0 
//! SPR   RV  TB BP2 BP1 BP0 WEL BUSY 
//! 
//! \return the value of status register
//!
//*****************************************************************************
unsigned char W25XxxStatusRegRead(void)    
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
    ucCommand = W25Xxx_INS_READ_SR;
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
//! \brief Wait for W25Xxx is not busy
//! 
//! \param None
//!
//! This function is to Wait for W25Xxx is not busy
//! 
//! \return None
//
//*****************************************************************************
void W25XxxWaitNotBusy(void)    
{    
    //
    //Wait the bit of busy is clear
    //
    while((W25XxxStatusRegRead() & 0x01) == 0x01); 
}

//*****************************************************************************
//
//! \brief W25Xxx write enable
//! 
//! \param None
//!
//! This function is to enable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void W25XxxWriteEnable(void)
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
    ucCommand = W25Xxx_INS_WRITE_ENABLE;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief  write a page(1~256byte) data to W25Xxx
//!
//! \param ucBuffer specifies the location data which will be .
//! \param ulWriteAddr specifies the address which data will be written 
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to write a page(1~256byte) data to W25Xxx, The appointed
//! byte length data will be writen in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void W25XxxPageWrite(unsigned char* pucBuffer, unsigned long  ulWriteAddr,
                                               unsigned short usNumByteToWrite)
{
    unsigned char ucCommand,ucAddr;
    unsigned short i;
    
    xASSERT((usNumByteToWrite > 0) && (usNumByteToWrite <= 256));
    
    //
    //Step 1 Set write enable
    //
    W25XxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 2  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 3 Transfer the command page program
    // 
    ucCommand = W25Xxx_INS_PAGE_PROGRAM;
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
    for(i = 0; i < usNumByteToWrite; i++)
    {
        xSPIDataWrite(FLASH_PIN_SPI_PORT, &pucBuffer[i], 1); 
    }
    
    //
    //Step 6  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 7  wait for the operation is over
    //
    W25XxxWaitNotBusy();       
}

//*****************************************************************************
//
//! \brief  Read data from W25Xxx
//!
//! \param ucBuffer specifies the location data which will be store.
//! \param ulWriteAddr specifies the address which data will be read 
//! \param usNumByteToWrite specifies the length of data will be read.
//!
//! This function is to read data from W25Xxx, The appointed byte length data will
//! be read in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void W25XxxDataRead(unsigned char* pucBuffer, unsigned long  ulReadAddr,
                                                  unsigned long ulNumByteToRead)
{
    unsigned char ucCommand,ucAddrBuffer[3]; 
    unsigned short i;
    
    ucAddrBuffer[0] = (unsigned char)(ulReadAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulReadAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulReadAddr >> 0);
    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 1  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 2 Transfer the command page program
    // 
    ucCommand = W25Xxx_INS_READ_DATA;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Transfer the address(24bit) which data will be read
    //
    xSPIDataWrite(FLASH_PIN_SPI_PORT, ucAddrBuffer, 3);
    
    //
    //Step 4 Write Data
    //
    for(i = 0; i <ulNumByteToRead; i++)
    {
        xSPIDataRead(FLASH_PIN_SPI_PORT, &pucBuffer[i], 1); 
    }
    
    //
    //Step 5  Disable chip select
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
void W25XxxChipErase(void)
{
    unsigned char ucCommand;
    
    //
    //Step 1 Set write enable
    //
    W25XxxWriteEnable();
    
    W25XxxWaitNotBusy();
    
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 3 Transfer the command Chip Erase
    // 
    ucCommand = W25Xxx_INS_CHIP_ERASE;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 4 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 5  wait for the operation is over
    //
    W25XxxWaitNotBusy(); 
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
void W25XxxSectorErase(unsigned long ulDstAddr)
{
    unsigned char ucCommand,ucAddrBuffer[3];
    
    ulDstAddr = ulDstAddr * 4096;
    ucAddrBuffer[0] = (unsigned char)(ulDstAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulDstAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulDstAddr >> 0);
    
    //
    //Step 1 Set write enable
    //
    W25XxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 3 Transfer the command Sector Erase
    // 
    ucCommand = W25Xxx_INS_SECTOR_ERASE;
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
    W25XxxWaitNotBusy(); 
}

//*****************************************************************************
//
//! \brief Erase a block
//! 
//! \param ulDstAddr specifies the block address which will be erased.and for
//! W25X16,it must be smaller than 32
//!
//! This function is to Erase a block
//! 
//! \return none
//
//*****************************************************************************
void W25XxxBlockErase(unsigned long ulDstAddr)
{
    unsigned char ucCommand;
    unsigned char ucAddrBuffer[3];
    ulDstAddr = ulDstAddr * 65536;
    ucAddrBuffer[0] = (unsigned char)(ulDstAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulDstAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulDstAddr >> 0);
    
    //
    //Step 1 Set write enable
    //
    W25XxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 3 Transfer the command Block Erase
    // 
    ucCommand = W25Xxx_INS_BLOCK_ERASE;
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
    W25XxxWaitNotBusy(); 
}

//*****************************************************************************
//
//! \brief W25Xxx Enter power down mode
//! 
//! \param None
//!
//! This function is to Enter power down mode
//! 
//! \return none
//
//*****************************************************************************
void W25XxxEnterPowerDown(void)
{
    unsigned char ucCommand;
    unsigned long ulClock;
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 2 Transfer the command Enter power down mode
    // 
    ucCommand = W25Xxx_INS_POWER_DOWN;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Delay tDP then wake up W25Xxx from stand by mode according to datasheet
    //
    ulClock = xSysCtlClockGet();
    xSysCtlDelay(ulClock /100000);
}

//*****************************************************************************
//
//! \brief wake up W25Xxx
//! 
//! \param None
//!
//! This function is to wake up W25Xxx
//! 
//! \return none
//
//*****************************************************************************
void W25XxxWakeUp(void)
{
    unsigned char ucCommand;
    unsigned long ulClock;
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 2 Transfer the command wake up
    // 
    ucCommand = W25Xxx_INS_WAKE_UP;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Delay tRES1 then wake up W25Xxx from power down according to datasheet
    //
    ulClock = xSysCtlClockGet();
    xSysCtlDelay(ulClock /100000);
}

//*****************************************************************************
//
//! \brief W25Xxx write status register
//! 
//! \param ulDstAddr specifies the status value which will be writen
//!
//! This function is to write status value to status register
//! 
//! \return none
//
//*****************************************************************************
void W25XxxStatusRegWrite(unsigned char ucStatusVal)
{
    unsigned char ucCommand,ucStatus;
    
    ucStatus = ucStatusVal;
    
    W25XxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    
    //
    //Step 2 Transfer the command Write Status Value
    // 
    ucCommand = W25Xxx_INS_WRITE_SR;
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
//! \brief  write some data to W25Xxx
//!
//! \param ucBuffer specifies the location data which will be .
//! \param ulWriteAddr specifies the address which data will be written 
//! \param usNumByteToWrite specifies the length of data will be write.
//!
//! This function is to write data to W25Xxx, The appointed byte length data
//! will be writen in appointed address.
//!
//! \return number of bytes to write to the FLASH
//!  
//*****************************************************************************
unsigned long W25XxxWrite(unsigned char* pucBuffer,unsigned long ulWriteAddr,
                                                 unsigned long ulNumByteToWrite)
{
    unsigned char *pucWriteBuf;
  	unsigned short usFirstSize, usLastSize, usPageNum, i;
  	unsigned long ulWriteAddrTemp;
	
  	usFirstSize = ulWriteAddr % 256;

  	ulWriteAddrTemp = ulWriteAddr - usFirstSize;
  	usFirstSize = 256 - usFirstSize;
  	pucWriteBuf = pucBuffer;

  	if(usFirstSize < ulNumByteToWrite) 
  	{
    		usPageNum  = (ulNumByteToWrite - usFirstSize) / 256;
    		usLastSize = (ulNumByteToWrite - usFirstSize) % 256;
  	} 
  	else 
  	{
    		usFirstSize = ulNumByteToWrite;
    		usPageNum = 0;
  	}
    
//
//! Write First Page
//
  	if(usFirstSize != 0) 
  	{
        W25XxxPageWrite(pucBuffer, ulWriteAddr, usFirstSize);
        ulWriteAddrTemp += 256;
        pucWriteBuf += usFirstSize;

        W25XxxWaitNotBusy();
  	}

  	for(i=0; i<usPageNum; i++) 
    {
        W25XxxPageWrite(pucWriteBuf, ulWriteAddrTemp, 256);
        ulWriteAddrTemp += 256;
        pucWriteBuf += 256;
        W25XxxWaitNotBusy();
  	}
    
//
//! Write Last Page
//
  	if(usLastSize) 
  	{
		W25XxxPageWrite(pucWriteBuf, ulWriteAddrTemp, usLastSize);
    }

  	return ulNumByteToWrite;
}

//*****************************************************************************
//
//! \brief conversely initialize the W25Xxx
//!
//! \param None
//!
//! This function is to conversely initialize the W25Xxx
//! 
//! \return None.
//
//*****************************************************************************
void W25XxxDeInit(void)
{
    xSysCtlPeripheralDisable2(FLASH_PIN_SPI_PORT);
}

//*****************************************************************************
//
//! \brief Enable the function of Write Protect
//!
//! \param None
//!
//! This function is to enable the function of Write Protect
//! 
//! \return None.
//
//*****************************************************************************
#if WP_CONFIG > 0
    void W25XxxWpEnable(void)
    {
        xGPIOSPinDirModeSet(FLASH_PIN_WP, xGPIO_DIR_MODE_IN);
        xGPIOSPinWrite(FLASH_PIN_WP, 0);       
    }
#endif

//*****************************************************************************
//
//! \brief Disable the function of Write Protect 
//!
//! \param None.
//!
//! This function is to disable the function of Write Protect
//! 
//! \return None.
//
//*****************************************************************************
#if WP_CONFIG > 0
    void W25XxxWpEnable(void)
    {
        xGPIOSPinDirModeSet(FLASH_PIN_WP, xGPIO_DIR_MODE_OUT);
        xGPIOSPinWrite(FLASH_PIN_WP, 1);       
    }
#endif

//*****************************************************************************
//
//! \brief Enable the function of Hold
//!
//! \param None.
//!
//! This function is to enable the function of Hold
//! 
//! \return None.
//
//*****************************************************************************
#if HOLD_CONFIG > 0
    void W25XxxHoldEnable(void)
    {
        xGPIOSPinDirModeSet(FLASH_PIN_HOLD, xGPIO_DIR_MODE_OUT);
        xGPIOSPinWrite(FLASH_PIN_HOLD, 0);         
    }
#endif

//*****************************************************************************
//
//! \brief Disable the function of Hold 
//!
//! \param None.
//!
//! This function is to Disable the function of Write Protect
//! 
//! \return None.
//
//*****************************************************************************
#if HOLD_CONFIG > 0
    void W25XxxHoldDisable(void)
    {
        xGPIOSPinDirModeSet(FLASH_PIN_HOLD, xGPIO_DIR_MODE_OUT);
        xGPIOSPinWrite(FLASH_PIN_HOLD, 1);     
    }
#endif

//*****************************************************************************
//
//! \brief W25Xxx write disable
//! 
//! \param None.
//!
//! This function is to disable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void W25XxxWriteDisable(void)
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
    ucCommand = W25Xxx_INS_WRITE_DISABLE;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}
