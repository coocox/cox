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
#include "w25x.h"
#include "hw_w25x.h"


//*****************************************************************************
//
//! \brief Initialize W25X 
//!
//! \param ulClock specifies the SPI Clock Rate
//!
//! This function is to initialize the MCU as master and specified SPI port.Set
//! W25X_PIN_SPI_CS as CS, W25X_PIN_SPI_CLK as CLK, W25X_PIN_SPI_MISO ->MISO  
//! and W25X_PIN_SPI_MOSI->MOSI.
//! 
//! \return None.
//
//*****************************************************************************
void 
W25XInit(unsigned long ulSpiClock)
{
    //
    // The max clock rate of W25X is 75M Hz acoording to Datasheet
    //
    xASSERT((ulSpiClock > 0) && (ulSpiClock < 75000000));
    
    //
    // Configure SPI pin which is connected with W25X
    //
    xSPIPinConfigure();
    
#if WP_CONFIG > 0
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(W25X_PIN_WP));
    xGPIOSPinDirModeSet(W25X_PIN_WP, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(W25X_PIN_WP, 1);
#endif
    
#if WP_CONFIG > 0
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(W25X_PIN_HOLD));
    xGPIOSPinDirModeSet(W25X_PIN_HOLD, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(W25X_PIN_HOLD, 1);
#endif
    
    //
    // Enable the SPIx which is connected with W25X
    //
    xSysCtlPeripheralEnable2(W25X_PIN_SPI_PORT);
    
    //
    // Configure MCU as a master device , 8 bits data width ,MSB first,Mode_0
    //
    xSPIConfigSet(W25X_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_0 |
                                                        xSPI_MODE_MASTER | 
                                                          xSPI_MSB_FIRST |
                                                          xSPI_DATA_WIDTH8);
    //
    // Disable W25Xxx when Power up
    //
    W25XSPICSDisable();
}

//*****************************************************************************
//
//! \brief conversely initialize the W25Xxx
//!
//! \param None
//!
//! This function is to conversely initialize the W25x
//! 
//! \return None.
//
//*****************************************************************************
void W25XDeInit(void)
{
    xSysCtlPeripheralDisable2(W25X_PIN_SPI_PORT);
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
unsigned short 
W25XIDcodeGet(void)
{
    unsigned short usIDcode;
    unsigned char ucInstruction,ucAddr,ucManuID,ucDeviID;
    
    W25XSPICSDisable();
    
    //
    //Step 1 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer intruction of "get ID"
    //
    ucInstruction = W25X_INS_GET_ID;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucInstruction, 1);
    
    //
    //Step 3 Transfer Address
    //
    ucAddr = 0x00;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucAddr, 1);
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucAddr, 1);
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucAddr, 1); 
    
    //
    // Get Manufacture ID
    //
    xSPIDataRead(W25X_PIN_SPI_PORT, &ucManuID, 1);
    
    //
    // Get Devidce ID
    //
    xSPIDataRead(W25X_PIN_SPI_PORT, &ucDeviID, 1);
    
    //
    //Step 4 Disable chip select
    //    
    W25XSPICSDisable();

    usIDcode = ucManuID << 8;
    usIDcode |= ucDeviID;
    
    return usIDcode;
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
xtBoolean 
W25XIsBusy(void)    
{    
    //
    //Check the bit of busy whether it is clear or not.
    //
    return ((W25XStatusRegRead() & 0x01) == 0x01) ? xtrue : xfalse;
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
static void 
W25XPageWrite(unsigned char* pucBuffer, 
              unsigned long  ulWriteAddr,
              unsigned short usNumByteToWrite)
{
    unsigned char ucCommand,ucAddr;
    unsigned short i;
    
    xASSERT((usNumByteToWrite > 0) && (usNumByteToWrite <= 256));
    
    //
    //Step 1 Set write enable
    //
    W25XWriteEnable();
    W25XSPICSDisable();
    
    //
    //Step 2  Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 3 Transfer the command page program
    // 
    ucCommand = W25X_INS_PAGE_PROGRAM;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 4 Transfer the address(24bit) which data will be written
    //
    ucAddr = (unsigned char)(ulWriteAddr >> 16);
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucAddr, 1);
    ucAddr = (unsigned char)(ulWriteAddr >> 8);
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucAddr, 1);
    ucAddr = (unsigned char)(ulWriteAddr);
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucAddr, 1);
    
    //
    //Step 5 Write Data
    //
    for(i = 0; i < usNumByteToWrite; i++)
    {
        xSPIDataWrite(W25X_PIN_SPI_PORT, &pucBuffer[i], 1); 
    }
    
    //
    //Step 6  Disable chip select
    //
    W25XSPICSDisable();
    
    //
    //Step 7  wait for the operation is over
    //
    while(W25XIsBusy());       
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
void 
W25XRead(unsigned char* pucBuffer,
         unsigned long  ulReadAddr,
         unsigned long ulNumByteToRead)
{
    unsigned char ucCommand,ucAddrBuffer[3]; 
    unsigned short i;
    
    ucAddrBuffer[0] = (unsigned char)(ulReadAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulReadAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulReadAddr >> 0);
    
    W25XSPICSDisable();
    
    //
    //Step 1  Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer the command page program
    // 
    ucCommand = W25X_INS_READ_DATA;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Transfer the address(24bit) which data will be read
    //
    xSPIDataWrite(W25X_PIN_SPI_PORT, ucAddrBuffer, 3);
    
    //
    //Step 4 Read Data
    //
    for(i = 0; i <ulNumByteToRead; i++)
    {
        xSPIDataRead(W25X_PIN_SPI_PORT, &pucBuffer[i], 1); 
    }
    
    //
    //Step 5  Disable chip select
    //
    W25XSPICSDisable(); 
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
//! \return number of bytes to write to the W25X
//!  
//*****************************************************************************
unsigned long 
W25XWrite(unsigned char* pucBuffer,
          unsigned long ulWriteAddr,
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
        W25XPageWrite(pucBuffer, ulWriteAddr, usFirstSize);
        ulWriteAddrTemp += 256;
        pucWriteBuf += usFirstSize;

    while(W25XIsBusy());
  	}

  	for(i=0; i<usPageNum; i++) 
    {
        W25XPageWrite(pucWriteBuf, ulWriteAddrTemp, 256);
        ulWriteAddrTemp += 256;
        pucWriteBuf += 256;
        while(W25XIsBusy());
  	}
    
//
//! Write Last Page
//
  	if(usLastSize) 
  	{
		W25XPageWrite(pucWriteBuf, ulWriteAddrTemp, usLastSize);
    }

  	return ulNumByteToWrite;
}

//*****************************************************************************
//
//! \brief W25X Verify
//! 
//! \param ucBlock specifies the block or blocks which will be protected.
//!
//! This function is to verify whether the data writing is sucessful or not.
//! 
//! \return the number bytes which have been written successly. 
//
//*****************************************************************************
unsigned long 
W25XVerify(unsigned char* pucWriteBuffer,
           unsigned long  ulReadAddr,
           unsigned long ulNumByteToWrite)
{
    unsigned long i;
    unsigned char* pucRead;

    for(i=0; i < ulNumByteToWrite; i++)
    {
    //
    // Step 1 Read the data from W25X
    //
        W25XRead(pucRead, ulReadAddr, 1);
    
    //
    // Step 2 Check the data which have been written to W25X
    //
        if(*pucRead != pucWriteBuffer[i])
        {
            break;
        }
    }
    return i;
}
//*****************************************************************************
//
//! \brief W25X write protect
//! 
//! \param ucBlock specifies the block or blocks which will be protected.
//!
//! This function is to write status value to protect some blocks.
//! 
//! \return none
//
//*****************************************************************************
void W25XWriteProtect(unsigned char ucBlock)
{
    unsigned char ucCommand,ucBlockNum;
    
    ucBlockNum = ucBlock;
    
    W25XWriteEnable();
    W25XSPICSDisable();
    
    //
    //Step 1 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer the command Write Status Value
    // 
    ucCommand = W25X_INS_WRITE_SR;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Write your block number that you will protect.
    //
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucBlockNum, 1);
    
    //
    //Step 4 Disable chip select
    //
    W25XSPICSDisable();
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
void W25XChipErase(void)
{
    unsigned char ucCommand;
    
    //
    //Step 1 Set write enable
    //
    W25XWriteEnable();
    
    while(W25XIsBusy());
    
    //
    //Step 2 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 3 Transfer the command Chip Erase
    // 
    ucCommand = W25X_INS_CHIP_ERASE;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 4 Disable chip select
    //
    W25XSPICSDisable();
    
    //
    //Step 5  wait for the operation is over
    //
    while(W25XIsBusy()); 
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
void W25XSectorErase(unsigned long ulDstAddr)
{
    unsigned char ucCommand,ucAddrBuffer[3];
    
    ulDstAddr = ulDstAddr * 4096;
    ucAddrBuffer[0] = (unsigned char)(ulDstAddr >> 16);
    ucAddrBuffer[1] = (unsigned char)(ulDstAddr >> 8);
    ucAddrBuffer[2] = (unsigned char)(ulDstAddr >> 0);
    
    //
    //Step 1 Set write enable
    //
    W25XWriteEnable();
    W25XSPICSDisable();
    
    //
    //Step 2 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 3 Transfer the command Sector Erase
    // 
    ucCommand = W25X_INS_SECTOR_ERASE;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 4 Transfer the address which will be erased
    //
    xSPIDataWrite(W25X_PIN_SPI_PORT, ucAddrBuffer, 3);
    
    //
    //Step 5 Disable chip select
    //
    W25XSPICSDisable();
    
    //
    //Step 6  wait for the operation is over
    //
    while(W25XIsBusy()); 
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
void W25XBlockErase(unsigned long ulDstAddr)
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
    W25XWriteEnable();
    W25XSPICSDisable();
    
    //
    //Step 2 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 3 Transfer the command Block Erase
    // 
    ucCommand = W25X_INS_BLOCK_ERASE;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 4 Transfer the address which will be erased
    //
    xSPIDataWrite(W25X_PIN_SPI_PORT, ucAddrBuffer, 3);
    
    //
    //Step 5 Disable chip select
    //
    W25XSPICSDisable();
    
    //
    //Step 6  wait for the operation is over
    //
    while(W25XIsBusy()); 
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
unsigned char W25XStatusRegRead(void)    
{   
    unsigned char ucStatus,ucCommand;
    
    W25XSPICSDisable();
    
    //
    //Step 1 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer the command Read Status Register 
    //
    ucCommand = W25X_INS_READ_SR;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Read status Register
    //
    xSPIDataRead(W25X_PIN_SPI_PORT, &ucStatus, 1);
    
    //
    //Step 4 Disable chip select 
    //
    W25XSPICSDisable();
    
    return ucStatus;    
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
void W25XPowerDown(void)
{
    unsigned char ucCommand;
    unsigned long ulClock;
    W25XSPICSDisable();
    
    //
    //Step 1 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer the command Enter power down mode
    // 
    ucCommand = W25X_INS_POWER_DOWN;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    W25XSPICSDisable();
    
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
void W25XWakeUp(void)
{
    unsigned char ucCommand;
    unsigned long ulClock;
    W25XSPICSDisable();
    
    //
    //Step 1 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer the command wake up
    // 
    ucCommand = W25X_INS_WAKE_UP;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    W25XSPICSDisable();
    
    //
    //Delay tRES1 then wake up W25Xxx from power down according to datasheet
    //
    ulClock = xSysCtlClockGet();
    xSysCtlDelay(ulClock /100000);
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
        xGPIOSPinWrite(W25X_PIN_WP, 0);       
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
        xGPIOSPinWrite(W25X_PIN_WP, 1);       
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
        xGPIOSPinWrite(W25X_PIN_HOLD, 0);         
    }
#endif

//*****************************************************************************
//
//! \brief W25X Disable the function of Hold 
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
        xGPIOSPinWrite(W25X_PIN_HOLD, 1);     
    }
#endif

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
void W25XWriteEnable(void)
{
    unsigned char ucCommand;
    W25XSPICSDisable();
    
    //
    //Step 1 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer the command Write Enable
    // 
    ucCommand = W25X_INS_WRITE_ENABLE;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    W25XSPICSDisable();
}

//*****************************************************************************
//
//! \brief W25X write disable
//! 
//! \param None.
//!
//! This function is to disable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void W25XWriteDisable(void)
{
    unsigned char ucCommand;
    
    W25XSPICSDisable();
    
    //
    //Step 1 Select Chip
    //
    W25XSPICSAssert();
    
    //
    //Step 2 Transfer the command Write Enable
    // 
    ucCommand = W25X_INS_WRITE_DISABLE;
    xSPIDataWrite(W25X_PIN_SPI_PORT, &ucCommand, 1);
    
    //
    //Step 3 Disable chip select
    //
    W25XSPICSDisable();
}
