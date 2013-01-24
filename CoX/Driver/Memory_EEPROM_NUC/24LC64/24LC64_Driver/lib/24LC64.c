//*****************************************************************************
//
//! \file _24LC64_.c
//! \brief the _24LC64_ Driver.
//! \version V2.1.1.0
//! \date 12/21/2012
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
#include "xi2c.h"
#include "xhw_i2c.h"
#include "xgpio.h"
#include "24LC64.h"
#include "hw_24LC64.h"

#define I2C_Speed               50000

//*****************************************************************************
//
//! \brief Initialize  24LC64 and I2C
//!
//! \param None
//!
//! This function initialize the mcu I2C as master and specified I2C port.the 
//! master block will be set up to transfer data at 400 kbps.
//! 
//! \return None.
//
//*****************************************************************************
void _24LC64_Init(void)
{
    //
    // Enable GPIO Periph clock and Alternate Fuction I/O clock.
    //  
    xSysCtlPeripheralEnable(_24LC64_I2C_GPIO);
    //
    // Enable the I2C which is connected with _24LC64_
    //
    xSysCtlPeripheralEnable2(_24LC64_I2C_PORT);
    //
    // Set _24LC64_PIN_I2C_SCK as IICx.SCK
    //
    xSPinTypeI2C(_24LC64_I2C_SCK, _24LC64_PIN_I2C_SCK);
    //
    // Set _24LC64_PIN_I2C_SDA as I2Cx.SDA
    //
    xSPinTypeI2C(_24LC64_I2C_SDA, _24LC64_PIN_I2C_SDA);

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(_24LC64_I2C_PORT, I2C_Speed);

}

//*****************************************************************************
//
//! \brief Write one byte to 24LC64.
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr specifies the address which data will be written.
//! 
//!  This function is to write one byte to 24LC64,one byte will be writen in
//!  appointed address.
//!
//! \return None.
//
//*****************************************************************************
void _24LC64_ByteWrite(unsigned char* pucBuffer, unsigned short usWriteAddr)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char SendBuf[3];
	unsigned long SendLength;
	SendBuf[0] = (usWriteAddr & 0xFF00) >> 8;
	SendBuf[1] = (usWriteAddr & 0x00FF);
	SendBuf[2] = * pucBuffer;

    SendLength = 3;
    
    
	Cfg.ulSlave = _24LC64_ADDRESS;

	Cfg.pvWBuf = SendBuf;
	Cfg.ulWLen = SendLength;
	Cfg.ulWCount = 0;
	Cfg.pvRBuf = 0;
	Cfg.ulRLen = 0;
	Cfg.ulRCount = 0;

	I2CMasterTransfer(_24LC64_I2C_PORT, &Cfg, I2C_TRANSFER_POLLING);
	_24LC64_WaitEepromStandbyState();
}

//*****************************************************************************
//
//! \brief Writes buffer of data to the  24LC64 .
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr 24LC64's internal address to write to.
//! \param usNumByteToWrite Number of bytes to write to the _24LC64_.
//! 
//!  This function is to Writes more then one byte to the 24LC64,the appointed
//!  byte length data will be writen in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void _24LC64_BufferWrite(unsigned char* pucBuffer,
                       unsigned short usWriteAddr, 
                       unsigned short usNumByteToWrite)
{
    unsigned char ucNumOfPage = 0, ucNumOfSingle = 0, ucCount = 0;
    unsigned short usAddr = 0;
    
    usAddr = usWriteAddr % _24LC64_PAGESIZE;
    ucCount = _24LC64_PAGESIZE -usAddr;
    ucNumOfPage = usNumByteToWrite / _24LC64_PAGESIZE;
    ucNumOfSingle = usNumByteToWrite % _24LC64_PAGESIZE;
    
    //
    // if usWriteAddr is 24LC64  PAGESIZE aligned.
    //
    if(usAddr == 0)
    { 
        //
        // If ucNumByteToWrite < PAGESIZE.
        //
        if(ucNumOfPage == 0)
        {
          _24LC64_PageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
          _24LC64_WaitEepromStandbyState();
        }
        //
        // If ucNumByteToWrite > PAGESIZE.
        //
        else
        {
          while(ucNumOfPage--)
          {
            _24LC64_PageWrite(pucBuffer, usWriteAddr,
                            (unsigned char)_24LC64_PAGESIZE);
            _24LC64_WaitEepromStandbyState();
            usWriteAddr += _24LC64_PAGESIZE;
            pucBuffer +=_24LC64_PAGESIZE;
          }
          if(ucNumOfSingle !=0)
          {
            _24LC64_PageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            _24LC64_WaitEepromStandbyState();
          }
        }
    }
    //
    // if usWriteAddr is not PAGESIZE aligned.
    //
    else
    {
      //
      // If ucNumByteToWrite < PAGESIZE.
      //
      if(ucNumOfPage == 0)
      {
        if(usNumByteToWrite > ucCount)
        {
            //
            // Write the data contained in same page.
            //
            _24LC64_PageWrite(pucBuffer, usWriteAddr, ucCount);
            _24LC64_WaitEepromStandbyState();
            //
            // Write the remaining data in the following page.
            //
            _24LC64_PageWrite((unsigned char*)(pucBuffer + ucCount),
                            (usWriteAddr + ucCount), 
                            (usNumByteToWrite - ucCount));
            _24LC64_WaitEepromStandbyState();
        }
        else
        {
            _24LC64_PageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            _24LC64_WaitEepromStandbyState();
        }
      }
      //
      // If ucNumByteToWrite > PAGESIZE.
      //
      else
      {
          usNumByteToWrite -= ucCount;
          ucNumOfPage = usNumByteToWrite / _24LC64_PAGESIZE;
          ucNumOfSingle = usNumByteToWrite % _24LC64_PAGESIZE;
          
          if(ucCount !=0)
          {
            _24LC64_PageWrite(pucBuffer, usWriteAddr, ucCount);
            _24LC64_WaitEepromStandbyState();
            usWriteAddr += ucCount;
            pucBuffer += ucCount;
          }
          while(ucNumOfPage --)
          {
            _24LC64_PageWrite(pucBuffer, usWriteAddr,
                            (unsigned char)_24LC64_PAGESIZE);
            _24LC64_WaitEepromStandbyState();
            usWriteAddr += _24LC64_PAGESIZE;
            pucBuffer += _24LC64_PAGESIZE;
          }
          if(ucNumOfSingle != 0)
          {
            _24LC64_PageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            _24LC64_WaitEepromStandbyState();
          }
      }
    }
}

//*****************************************************************************
//
//! \brief Writes more than one byte to the 24LC64 with a single WRITE cycle.
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr 24LC64's internal address to write to.
//! \param ucNumByteToWrite number of byte to write to the 24LC64
//!
//! This function is to write a page data to 24LC64, The appointed byte length
//! data will be written in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void _24LC64_PageWrite(unsigned char* pucBuffer,
                     unsigned short usWriteAddr, 
                     unsigned char ucNumByteToWrite)
{
	unsigned char SendBuf[34];
    unsigned long SendLength;
	unsigned char * pucbuff = pucBuffer;
	tI2CMasterTransferCfg Cfg;
	int i;
	if(usWriteAddr%_24LC64_PAGESIZE + ucNumByteToWrite>_24LC64_PAGESIZE)
		SendLength = _24LC64_PAGESIZE - usWriteAddr%_24LC64_PAGESIZE;
	else
		SendLength = ucNumByteToWrite;

	
	SendBuf[0] = (usWriteAddr & 0xFF00) >> 8;
	SendBuf[1] = usWriteAddr & 0x00FF;
	
	
	for(i=0; i<SendLength; i++)
	{
		SendBuf[i+2] = * pucbuff;
		pucbuff++;
	}

    
	Cfg.ulSlave = _24LC64_ADDRESS;

	Cfg.pvWBuf = SendBuf;
	Cfg.ulWLen = SendLength+2;
	Cfg.ulWCount = 0;
	Cfg.pvRBuf = 0;
	Cfg.ulRLen = 0;
	Cfg.ulRCount = 0;

	I2CMasterTransfer(_24LC64_I2C_PORT, &Cfg, I2C_TRANSFER_POLLING);
	_24LC64_WaitEepromStandbyState();
}
    
//*****************************************************************************
//
//! \brief Reads a block of data from the 24LC64.
//!
//! \param pucBuffer specifies the location data which will be store
//! \param usReadAddr 24LC64 internal address to read from.
//! \param usNumByteToRead number of bytes to read from the 24LC64.
//!
//! This function is to read data from 24LC64, the appointed byte length data
//! will be read in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void _24LC64_BufferRead(unsigned char* pucBuffer,
                      unsigned short usReadAddr,
                      unsigned short usNumByteToRead)
{
	xtBoolean bAck;
	tI2CMasterTransferCfg Cfg;
	unsigned long ReadLength;
	unsigned char SendBuf[2];
	if(usReadAddr+usNumByteToRead>_24LC64_SIZE)
		ReadLength = _24LC64_SIZE - usReadAddr;
	else
		ReadLength = usNumByteToRead;
    
	SendBuf[0] = (usReadAddr & 0xFF00) >> 8;
	SendBuf[1] = usReadAddr & 0x00FF;
	
	Cfg.ulSlave = _24LC64_ADDRESS;
	Cfg.pvWBuf = SendBuf;
	Cfg.ulWLen = 2;
	Cfg.ulWCount = 0;
	Cfg.pvRBuf = 0;
	Cfg.ulRLen = 0;
	Cfg.ulRCount = 0;

	//
	// send control byte and address
	//
	bAck = I2CMasterTransfer(_24LC64_I2C_PORT, &Cfg, I2C_TRANSFER_POLLING);
	if(!bAck)
		return ;

	Cfg.pvWBuf = 0;
	Cfg.ulWLen = 0;
	Cfg.pvRBuf = pucBuffer;
	Cfg.ulRLen = ReadLength;

	//
	// get data
	//
	I2CMasterTransfer(_24LC64_I2C_PORT, &Cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Reads data in current address from the 24LC64.
//!
//! \param pucBuffer specifies the location data which will be store
//!
//! \return None.
//
//*****************************************************************************
void _24LC64_CurrentAddrRead(unsigned char* pucBuffer)
{
	tI2CMasterTransferCfg Cfg;
	Cfg.ulSlave = _24LC64_ADDRESS;
	Cfg.pvWBuf = 0;
	Cfg.ulWLen = 0;
	Cfg.ulWCount = 0;
	Cfg.pvRBuf = pucBuffer;
	Cfg.ulRLen = 1;
	Cfg.ulRCount = 0;

	//
	// get one byte from the current address
	//
	I2CMasterTransfer(_24LC64_I2C_PORT, &Cfg, I2C_TRANSFER_POLLING);
}

static unsigned long I2CStartSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
	xHWREG(ulBase + I2C_O_CON) |= I2C_CON_STA;

    //
    // Wait for complete
    //
	while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));

	return (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
}

static unsigned long I2CByteSend (unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    //
    // Make sure start bit is not active,but do not clear SI
    //
    if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
    }

    //
    // Send i2c address and RW bit
    //
	xHWREG(ulBase + I2C_O_DAT) = ucData;

    //
    // Make sure AA and EI bit is not active,and clear SI
    //
	xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_AA | I2C_CON_EI);

    //
    // Wait the SI be set again by hardware
    //
	while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));

    //
    // Return the i2c status
    //
    return (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
}


static void I2CStopSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_STA;
    }
	xHWREG(ulBase + I2C_O_CON) |= I2C_CON_STO;
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;

	xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
}
//*****************************************************************************
//
//! \brief Wait for 24LC64 Standby state.
//!
//! A Stop condition at the end of a Write command triggers the internal
//! Write cycle.
//!
//! \return None.
//
//*****************************************************************************
void _24LC64_WaitEepromStandbyState(void)
{
	unsigned long ulCodeStatus;

	do
	{
		//
		// Start command
		//
		ulCodeStatus = I2CStartSend(_24LC64_I2C_PORT);
		if ((ulCodeStatus != I2C_I2STAT_M_TX_START) &&
			(ulCodeStatus != I2C_I2STAT_M_TX_RESTART))
		{
			I2CStopSend(_24LC64_I2C_PORT);
			continue;
		}

		//
		// Send slave address + WR direction bit = 0
		//
		ulCodeStatus = I2CByteSend(_24LC64_I2C_PORT, (_24LC64_ADDRESS << 1));
		if (ulCodeStatus != I2C_I2STAT_M_TX_SLAW_ACK)
		{
			I2CStopSend(_24LC64_I2C_PORT);
		}
	}while(ulCodeStatus != I2C_I2STAT_M_TX_SLAW_ACK);
}
