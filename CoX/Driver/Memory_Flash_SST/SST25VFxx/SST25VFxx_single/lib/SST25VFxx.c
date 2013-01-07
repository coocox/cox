//*****************************************************************************
//
//! \file SST25VFxx.c
//! \brief the SST25VFxx Driver.
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
#include "Xhw_spi.h"
#include "xgpio.h"
#include "SST25VFxx.h"
#include "hw_SST25VFxx.h"

#if (SST25VFxx_Device == SST25VF016B)
#define SST25VFxx_MAX_CLOCK     80000000

#define SST25VFxxSECTOR_SIZE    SST25VF016B_SECTOR_SIZE
#define SST25VFxxBLOCK_32K      SST25VF016B_BLOCK_32K
#define SST25VFxxBLOCK_64K      SST25VF016B_BLOCK_64K
#define SST25VFxx_SIZE          SST25VF016B_SIZE

#endif


//*****************************************************************************
//
//! \brief Initialize SST25VFxx and SPI
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
void SST25VFxxInit(unsigned long ulSpiClock)
{
    //
    // The max clock rate of SST25VFxx is 20M to 50M Hz acoording to Datasheet
    //
    xASSERT((ulSpiClock > 0) && (ulSpiClock < SST25VFxx_MAX_CLOCK));
    //
    // Enable the GPIOx port which is connected with SST25VFxx
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(FLASH_PIN_SPI_MOSI));
    //
    // Enable the SPIx which is connected with SST25VFxx
    //
    xSysCtlPeripheralEnable2(FLASH_PIN_SPI_PORT);
    //
    // Set GPIOD0 as a chip select pin and set it as OUT_MODE
    //
    xGPIOSPinDirModeSet(FLASH_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);
    
#if (SST25VFxx_HOLD > 0)
    xGPIOSPinDirModeSet(FLASH_PIN_HOLD, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(FLASH_PIN_HOLD, 1);
#endif
 
#if (SST25VFxx_WRITE_PROTECT > 0)
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
    xSPIConfigSet(FLASH_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_3 |
                                                  xSPI_MODE_MASTER | 
                                                  xSPI_MSB_FIRST |
                                                  xSPI_DATA_WIDTH8);
    xSPISSSet(FLASH_PIN_SPI_PORT, xSPI_SS_SOFTWARE, 0);
    //
    // Disable SST25VFxx when Power up
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    xSPIEnable(FLASH_PIN_SPI_PORT);
    
    
}

//*****************************************************************************
//
//! \brief Read SST25VFxx ID
//! 
//! \param ulIDType can be Manufacturer¡¯s ID,Device ID and both.
//!
//! This function is to Read ID
//! \e ulIDType can be: \b SST25VFxx_ID_MANUF, \b SST25VFxx_ID_DEVICE,
//! \b SST25VFxx_ID_BOTH .
//!
//! 
//! \return SST25VFxx ID in Hexadecimal,when get both,high byte is
//! Manufacturer¡¯s ID,low byte is Device ID.
//
//*****************************************************************************
unsigned long SST25VFxxIDGet(unsigned long ulIDType)
{
    unsigned char ucInstruction;
    unsigned long ucAddr = ulIDType & 0x1;
    unsigned char ucManuID[2] ={0};
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer intruction of "get ID"
    //
    ucInstruction = SST25VFxx_CMD_RDID_0;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucInstruction, 1);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, (unsigned char *)&ucAddr, 3);

    
    //
    // Get Manufacture ID Devidce ID
    //
    if(ulIDType & 0x10)
    {
        xSPIDataRead(FLASH_PIN_SPI_PORT, ucManuID, 2);
    }
    else
    {
        xSPIDataRead(FLASH_PIN_SPI_PORT, ucManuID, 1);
    }

    //
    //Step 3 Disable chip select
    //    
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    return (ucManuID[1] | (ucManuID[0]<<8));
}

//*****************************************************************************
//
//! \brief JEDEC Read SST25VFxx ID
//!
//! \param None.
//!
//! This function is to Read ID
//!
//! \return BFH 25H 41H.
//
//*****************************************************************************
unsigned long SST25VFxxJedecIDGet(void)
{
    unsigned char ucInstruction;
    unsigned char ucManuID[3] ={0};

    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer intruction of "get ID"
    //
    ucInstruction = SST25VFxx_CMD_RD_JEDEC;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucInstruction, 1);

    //
    // Get Manufacture ID Devidce ID
    //
    xSPIDataRead(FLASH_PIN_SPI_PORT, ucManuID, 3);

    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    return (ucManuID[2] | (ucManuID[1]<<8) | (ucManuID[0]<<16));
}

//*****************************************************************************
//
//! \brief Read SST25VFxx Status Register
//! 
//! \param None
//!
//! This function is to Read SST25VFxx Status Register:the bit field follows:
//! BIT7  6   5   4   3   2   1   0 
//£¡BPL  AAI BP3 BP2 BP1 BP0 WEL BUSY
//! 
//! \return the value of status
//£¡
//*****************************************************************************
unsigned char SST25VFxxStatusRegRead(void)
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
    ucCommand = SST25VFxx_CMD_RDSR;
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
//! \brief Wait for SST25VFxx is not busy
//! 
//! \param None
//!
//! This function is to Wait for SST25VFxx is not busy
//! 
//! \return None
//
//*****************************************************************************
void SST25VFxxWaitNotBusy(void)
{    
    //
    //Wait the bit of busy is clear
    //
    while((SST25VFxxStatusRegRead() & 0x01) == 0x01);
}

//*****************************************************************************
//
//! \brief SST25VFxx write enable
//! 
//! \param None
//!
//! This function is to enable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void SST25VFxxWriteEnable(void)
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
    ucCommand = SST25VFxx_CMD_WREN;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief SST25VFxx Auto Address Increment (AAI) Word-Program busy enable
//!
//! \param None
//!
//! This function is to enable the (AAI) Word-Program busy
//!
//! \return none
//
//*****************************************************************************
void SST25VFxxAAIBusyEnable(void)
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
    ucCommand = SST25VFxx_CMD_EBSY;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief SST25VFxx Auto Address Increment (AAI) Word-Program busy disable
//!
//! \param None
//!
//! This function is to disable the (AAI) Word-Program busy
//!
//! \return none
//
//*****************************************************************************
void SST25VFxxAAIBusyDisable(void)
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
    ucCommand = SST25VFxx_CMD_DBSY;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief SST25VFxx write disable
//! 
//! \param None
//!
//! This function is to disable the function 0f writing
//! 
//! \return none
//
//*****************************************************************************
void SST25VFxxWriteDisable(void)
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
    ucCommand = SST25VFxx_CMD_WRDI;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief  write a Byte data to SST25VFxx
//!
//! \param ulWriteAddr specifies the address which data will be written 
//! \param ucByte specifies the data will be write.
//!
//! This function is to write a Byte data to SST25VFxx, The appointed
//! byte length data will be writen in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void SST25VFxxByteWrite(unsigned long ulWriteAddr, unsigned char ucByte)
{
    unsigned char ucCommand; 
    unsigned char ucAddr;

    //
    //Step 1 Set write enable
    //
    SST25VFxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command page program
    // 
    ucCommand = SST25VFxx_CMD_WRBYTE;
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

    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte, 1);

    //
    //Step 6  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 7  wait for the operation is over
    //
    SST25VFxxWaitNotBusy();
}

//*****************************************************************************
//
//! \brief  write 2 Byte data to SST25VFxx using AAI first time.
//!
//! \param ulWriteAddr specifies the address which data will be written
//! \param ucByte1 specifies the first data will be write.
//! \param ucByte2 specifies the second data will be write.
//!
//! This procedure programs consecutive addresses of 2 bytes of data into
//! the device:  1st data byte will be programmed into the initial
//! address [A23-A1] and with A0 = 0.  The 2nd data byte will be be
//! programmed into initial address [A23-A1] and with A0  = 1.  This
//! is used to to start the AAI process.  It should be followed by
//! SST25VFxxAAIWriteB.
//! Assumption:  Address being programmed is already erased and is NOT
//!        block protected.
//!
//!
//! Note: Only RDSR command can be executed once in AAI mode with SO
//!      disable to output RY/BY# status.  Use WRDI to exit AAI mode
//!     unless AAI is programming the last address or last address of
//!      unprotected block, which automatically exits AAI mode.
//!
//! \return None
//!
//*****************************************************************************
void SST25VFxxAAIWriteA(unsigned long ulWriteAddr, unsigned char ucByte1,
                        unsigned char ucByte2)
{
    unsigned char ucCommand;
    unsigned char ucAddr;

    //
    //Step 1 Set write enable
    //
    SST25VFxxAAIBusyEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command page program
    //
    ucCommand = SST25VFxx_CMD_AAI;
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

    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte1, 1);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte2, 1);

    //
    //Step 6  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 7  wait for the operation is over,wait
    //
}

//*****************************************************************************
//
//! \brief  write 2 Byte data to SST25VFxx using AAI after first time.
//!
//! \param ucByte1 specifies the first data will be write.
//! \param ucByte2 specifies the second data will be write.
//!
//! This procedure programs consecutive addresses of 2 bytes of data into
//! the device:  1st data byte will be programmed into the initial
//! address [A23-A1] and with A0 = 0.  The 2nd data byte will be be
//! programmed into initial address [A23-A1] and with A0  = 1.    This
//! is used after SST25VFxxAAIWriteA.
//! Assumption:  Address being programmed is already erased and is NOT
//!        block protected.
//!
//! Note: Only WRDI and AAI command can be executed once in AAI mode
//!     with SO enabled as RY/BY# status.  When the device is busy
//!     asserting CE# will output the status of RY/BY# on SO.  Use WRDI
//!      to exit AAI mode unless AAI is programming the last address or
//!     last address of unprotected block, which automatically exits
//!     AAI mode.
//!
//! \return None
//!
//*****************************************************************************
void SST25VFxxAAIWriteB(unsigned char ucByte1, unsigned char ucByte2)
{
    unsigned char ucCommand;

    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command page program
    //
    ucCommand = SST25VFxx_CMD_AAI;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);

    //
    //Step 3 Write Data
    //

    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte1, 1);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte2, 1);

    //
    //Step 4  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 5  wait for the operation is over,wait
    //
}

//*****************************************************************************
//
//! \brief  write 2 Byte data to SST25VFxx using AAI first time with busy bit.
//!
//! \param ulWriteAddr specifies the address which data will be written
//! \param ucByte1 specifies the first data will be write.
//! \param ucByte2 specifies the second data will be write.
//!
//! This procedure programs consecutive addresses of 2 bytes of data into
//! the device:  1st data byte will be programmed into the initial
//! address [A23-A1] and with A0 = 0.  The 2nd data byte will be be
//! programmed into initial address [A23-A1] and with A0  = 1.  This
//! is used to to start the AAI process.  It should be followed by
//! SST25VFxxAAIWriteB.
//! Assumption:  Address being programmed is already erased and is NOT
//!        block protected.
//!
//!
//! Note: Only RDSR command can be executed once in AAI mode with SO
//!      disable to output RY/BY# status.  Use WRDI to exit AAI mode
//!     unless AAI is programming the last address or last address of
//!      unprotected block, which automatically exits AAI mode.
//!
//! \return None
//!
//*****************************************************************************
void SST25VFxxAAIEBusyWriteA(unsigned long ulWriteAddr, unsigned char ucByte1,
                             unsigned char ucByte2)
{
    unsigned char ucCommand;
    unsigned char ucAddr;

    //
    //Step 1 Set write enable
    //
    SST25VFxxAAIBusyEnable();

    //
    //Step 2 Set write enable
    //
    SST25VFxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 3  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 4 Transfer the command page program
    //
    ucCommand = SST25VFxx_CMD_AAI;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 5 Transfer the address(24bit) which data will be written
    //
    ucAddr = (unsigned char)(ulWriteAddr >> 16);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    ucAddr = (unsigned char)(ulWriteAddr >> 8);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    ucAddr = (unsigned char)(ulWriteAddr);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucAddr, 1);
    //
    //Step 6 Write Data
    //

    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte1, 1);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte2, 1);

    //
    //Step 7  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 8  wait for the operation is over,wait
    //
    SST25VFxxWaitNotBusy();
}

//*****************************************************************************
//
//! \brief  write 2 Byte data to SST25VFxx using AAI after first time.
//!
//! \param ucByte1 specifies the first data will be write.
//! \param ucByte2 specifies the second data will be write.
//!
//! This procedure programs consecutive addresses of 2 bytes of data into
//! the device:  1st data byte will be programmed into the initial
//! address [A23-A1] and with A0 = 0.  The 2nd data byte will be be
//! programmed into initial address [A23-A1] and with A0  = 1.    This
//! is used after SST25VFxxAAIWriteA.
//! Assumption:  Address being programmed is already erased and is NOT
//!        block protected.
//!
//! Note: Only WRDI and AAI command can be executed once in AAI mode
//!     with SO enabled as RY/BY# status.  When the device is busy
//!     asserting CE# will output the status of RY/BY# on SO.  Use WRDI
//!      to exit AAI mode unless AAI is programming the last address or
//!     last address of unprotected block, which automatically exits
//!     AAI mode.
//!
//! \return None
//!
//*****************************************************************************
void SST25VFxxAAIEBusyWriteB(unsigned char ucByte1, unsigned char ucByte2)
{
    unsigned char ucCommand;

    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 1  Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command page program
    //
    ucCommand = SST25VFxx_CMD_AAI;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);

    //
    //Step 3 Write Data
    //

    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte1, 1);
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucByte2, 1);

    //
    //Step 4  Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 5  wait for the operation is over,wait
    //
    SST25VFxxWaitNotBusy();
}

//*****************************************************************************
//
//! \brief  Writes more than one byte to the FLASH SST25VFxx
//!
//! \param ucBuffer specifies the location data which will be .
//! \param ulWriteAddr specifies the address which data will be written 
//! \param ulNumByteToWrite specifies the length of data will be write.
//!
//! This function is to Writes more than one byte to the FLASH SST25VFxx, The
//! appointed byte length data will be writen in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void SST25VFxxWrite(unsigned char* pucBuffer, unsigned long  ulWriteAddr,
                    unsigned long ulNumByteToWrite)
{
    const unsigned char *pucWriteBuf;
    unsigned char ucFirstSize;
    unsigned long ulAAINum, i;
    unsigned long ulWriteAdrTemp = ulWriteAddr;
    xASSERT(ulNumByteToWrite > 0);

    pucWriteBuf = pucBuffer;

    ucFirstSize = ulNumByteToWrite % 2;
    if(ulNumByteToWrite >= 2)
    {
        ulAAINum  = (ulNumByteToWrite - ucFirstSize) / 2;
    } 
    else 
    {
        ulAAINum = 0;
    }
    
    //
    //Write First byte
    //
    if(ucFirstSize != 0)
    {
        SST25VFxxByteWrite (ulWriteAdrTemp, *pucWriteBuf);
        ulWriteAdrTemp += ucFirstSize;
        pucWriteBuf += ucFirstSize;
        SST25VFxxWaitNotBusy();
    }

    for(i=0; i<ulAAINum; i++)
    {
        if(i == 0)
        {
            SST25VFxxAAIEBusyWriteA(ulWriteAddr, *pucWriteBuf, *(pucWriteBuf+1));
        }
        else
        {
            SST25VFxxAAIEBusyWriteB(*pucWriteBuf, *(pucWriteBuf+1));
        }
        pucWriteBuf += 2;
        SST25VFxxWaitNotBusy();
    }
    //
    // Set write disable
    //
    SST25VFxxWriteDisable();

    //
    // Set write disable
    //
    SST25VFxxAAIBusyDisable();


    return;
}

//*****************************************************************************
//
//! \brief  Read data from SST25VFxx
//!
//! \param ucBuffer specifies the location data which will be store.
//! \param ulWriteAddr specifies the address which data will be read 
//! \param usNumByteToWrite specifies the length of data will be read.
//!
//! This function is to read data from SST25VFxx, The appointed byte length data will
//! be read in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void SST25VFxxDataRead(unsigned char* ucBuffer, unsigned long  ulReadAddr,
                       unsigned long ulNumByteToRead)
{
    unsigned char ucCommand; 
    unsigned char ucAddrBuffer[3];
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
    ucCommand = SST25VFxx_CMD_RD25;
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
//! \brief  Read data from SST25VFxx at Higher Speed
//!
//! \param ucBuffer specifies the location data which will be store.
//! \param ulWriteAddr specifies the address which data will be read 
//! \param usNumByteToWrite specifies the length of data will be read.
//!
//! This function is to read data from SST25VFxx, The appointed byte length data will
//! be read in appointed address.
//!
//! \return None
//!  
//*****************************************************************************
void SST25VFxxDataFastRead(unsigned char* ucBuffer, unsigned long  ulReadAddr,
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
    ucCommand = SST25VFxx_CMD_RD80;
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
void SST25VFxxChipErase(void)
{
    unsigned char ucCommand;
    //
    //Step 1 Set write enable
    //
    SST25VFxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Chip Erase
    // 
    ucCommand = SST25VFxx_CMD_ERALL_0;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 4 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 5  wait for the operation is over
    //
    SST25VFxxWaitNotBusy();
}

//*****************************************************************************
//
//! \brief Erase a sector
//! 
//! \param ulDstAddr specifies the sector address which will be erased.
//! This function is to Erase a sector
//! 
//! \return none
//
//*****************************************************************************
void SST25VFxxSectorErase(unsigned long ulDstAddr)
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
    SST25VFxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Sector Erase
    // 
    ucCommand = SST25VFxx_CMD_ER4K;
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
    SST25VFxxWaitNotBusy();
}

//*****************************************************************************
//
//! \brief Erase a 32k Block
//!
//! \param ulDstAddr specifies the 32k Block address which will be erased.
//! This function is to Erase a 32k Block
//!
//! \return none
//
//*****************************************************************************
void SST25VFxxBlock32Erase(unsigned long ulDstAddr)
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
    SST25VFxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Sector Erase
    //
    ucCommand = SST25VFxx_CMD_ER32K;
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
    SST25VFxxWaitNotBusy();
}

//*****************************************************************************
//
//! \brief Erase a 64k Block
//!
//! \param ulDstAddr specifies the 64k Block address which will be erased.
//! This function is to Erase a 64k Block
//!
//! \return none
//
//*****************************************************************************
void SST25VFxxBlock64Erase(unsigned long ulDstAddr)
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
    SST25VFxxWriteEnable();
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);
    //
    //Step 2 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 3 Transfer the command Sector Erase
    //
    ucCommand = SST25VFxx_CMD_ER64K;
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
    SST25VFxxWaitNotBusy();
}

//*****************************************************************************
//
//! \brief SST25VFxx write status register
//! 
//! \param ulDstAddr specifies the status value which will be writen
//!
//! This function is to write status value to status register
//! 
//! \return none
//
//*****************************************************************************
void SST25VFxxStatusRegWrite(unsigned char ucStatusVal)
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
    ucCommand = SST25VFxx_CMD_EWSR;
    xSPIDataWrite(FLASH_PIN_SPI_PORT, &ucCommand, 1);
    //
    //Step 3 Disable chip select
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 1);

    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(FLASH_PIN_SPI_CS, 0);
    //
    //Step 2 Transfer the command Write Status Value
    //
    ucCommand = SST25VFxx_CMD_WRSR;
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
//! \brief Disable SST25VFxx
//!
//! \param None
//!
//! This function is to Disable SST25VFxx
//! 
//! \return None.
//
//*****************************************************************************
void SST25VFxxDisable(void)
{
    xSysCtlPeripheralDisable2(FLASH_PIN_SPI_PORT);
}

//*****************************************************************************
//
//! \brief Get SST25VFxx Sector Size
//! 
//! \param None
//!
//! This function is to get SST25VFxx Sector Size
//! 
//! \return SST25VFxx Sector Size
//
//*****************************************************************************
unsigned long SST25VFxxSectorSizeGet(void)
{
    return 4096;
}

//*****************************************************************************
//
//! \brief Get SST25VFxx Chip Size
//! 
//! \param None
//!
//! This function is to get SST25VFxx Chip Size
//! 
//! \return SST25VFxx Chip Size
//
//*****************************************************************************
unsigned long SST25VFxxChipSizeGet(void)
{
    return SST25VFxx_SIZE;
}

#if (SST25VFxx_HOLD > 0)

//*****************************************************************************
//
//! \brief Enable SST25VFxx hold input
//! 
//! \param None
//!
//! This function is to enable SST25VFxx hold input.
//! 
//! \return None.
//
//*****************************************************************************
void SST25VFxxHoldEnable(void)
{
    xGPIOSPinWrite(FLASH_PIN_HOLD, 0);
}

//*****************************************************************************
//
//! \brief Disable SST25VFxx hold input
//! 
//! \param None
//!
//! This function is to disable SST25VFxx hold input.
//! 
//! \return None.
//
//*****************************************************************************
void SST25VFxxHoldDisable(void)
{
    xGPIOSPinWrite(FLASH_PIN_HOLD, 1);
}
#endif
 
#if (SST25VFxx_WRITE_PROTECT > 0)

//*****************************************************************************
//
//! \brief Enable SST25VFxx write protect .
//! 
//! \param None
//!
//! This function is to enable SST25VFxx write protect .
//! 
//! \return None.
//
//*****************************************************************************
void SST25VFxxWriteProtectEnable(void)
{
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 0);
}

//*****************************************************************************
//
//! \brief Disable SST25VFxx write protect .
//! 
//! \param None
//!
//! This function is to disable SST25VFxx write protect .
//! 
//! \return None.
//
//*****************************************************************************
void SST25VFxxWriteProtectDisable(void)
{
    xGPIOSPinWrite(FLASH_PIN_WRITE_PROTECT, 1);
}
#endif
