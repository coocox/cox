//*****************************************************************************
//
//! \file HT24Cxx.c
//! \brief the HT24Cxx Driver.
//! \version V2.1.1.0
//! \date 6/1/2012
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
#include "HT24Cxx.h"
#include "hw_HT24Cxx.h"

#if (HT24Cxx_Device == HT24C02)

#define HT24Cxx_PAGESIZE         HT24C02_PAGE_SIZE
#define HT24Cxx_SIZE             HT24C02_SIZE

#endif

#define I2C_Speed               100000

                                           
//*****************************************************************************
//
//! \brief Initialize HT24Cxx and I2C
//!
//! \param None
//!
//! This function initialize the mcu I2C as master and specified I2C port.the 
//! master block will be set up to transfer data at 400 kbps.
//! 
//! \return None.
//
//*****************************************************************************
void HT24CxxInit(void)
{
    //
    // Enable GPIO Periph clock and Alternate Fuction I/O clock.
    //  
    xSysCtlPeripheralEnable(HT24Cxx_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    // Enable the I2C which is connected with HT24Cxx
    //
    xSysCtlPeripheralEnable2(HT24Cxx_PIN_I2C_PORT);
    //
    // Set HT24Cxx_PIN_I2C_SCK as IICx.SCK
    //
    xSPinTypeI2C(HT24Cxx_I2C_SCK, HT24Cxx_PIN_I2C_SCK);
    //
    // Set HT24Cxx_PIN_I2C_SDA as I2Cx.SDA
    //
    xSPinTypeI2C(HT24Cxx_I2C_SDA, HT24Cxx_PIN_I2C_SDA);
    //
    // I2C enable
    //
    xI2CMasterEnable(HT24Cxx_PIN_I2C_PORT);
    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(HT24Cxx_PIN_I2C_PORT, I2C_Speed);
}

//*****************************************************************************
//
//! \brief Write one byte to HT24Cxx.
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr specifies the address which data will be written.
//! 
//!  This function is to write one byte to HT24Cxx,one byte will be writen in
//!  appointed address.
//!
//! \return None.
//
//*****************************************************************************
void HT24CxxByteWrite(unsigned char* pucBuffer, unsigned short usWriteAddr)
{
    xASSERT((usWriteAddr >= 0) && (usWriteAddr <= HT24Cxx_SIZE));
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the HT24Cxxs internal address.
    //
    xI2CMasterWriteS1(HT24Cxx_PIN_I2C_PORT, HT24Cxx_ADDRESS,
                     (unsigned char)((usWriteAddr & 0x00FF)),
                     xfalse);
    
    //
    // Send the byte to be written.
    //
    xI2CMasterWriteS2(HT24Cxx_PIN_I2C_PORT, *pucBuffer, xtrue);
}

//*****************************************************************************
//
//! \brief Writes buffer of data to the HT24Cxx.
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr HT24Cxx's internal address to write to.
//! \param usNumByteToWrite Number of bytes to write to the HT24Cxx.
//! 
//!  This function is to Writes more then one byte to the HT24Cxx,the appointed
//!  byte length data will be writen in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void HT24CxxBufferWrite(unsigned char* pucBuffer,
                       unsigned short usWriteAddr, 
                       unsigned short usNumByteToWrite)
{
    unsigned char ucNumOfPage = 0, ucNumOfSingle = 0, ucCount = 0;
    unsigned short usAddr = 0;
    
    usAddr = usWriteAddr % HT24Cxx_PAGESIZE;
    ucCount = HT24Cxx_PAGESIZE -usAddr;
    ucNumOfPage = usNumByteToWrite / HT24Cxx_PAGESIZE;
    ucNumOfSingle = usNumByteToWrite % HT24Cxx_PAGESIZE;
    
    //
    // if usWriteAddr is HT24Cxx_FLASH_PAGESIZE aligned.
    //
    if(usAddr == 0)
    { 
        //
        // If ucNumByteToWrite < HT24Cxx_FLASH_PAGESIZE.
        //
        if(ucNumOfPage == 0)
        {
          HT24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
          HT24CxxWaitEepromStandbyState();
        }
        //
        // If ucNumByteToWrite > HT24Cxx_FLASH_PAGESIZE.
        //
        else
        {
          while(ucNumOfPage--)
          {
            HT24CxxPageWrite(pucBuffer, usWriteAddr,
                            (unsigned char)HT24Cxx_PAGESIZE);
            HT24CxxWaitEepromStandbyState();
            usWriteAddr += HT24Cxx_PAGESIZE;
            pucBuffer +=HT24Cxx_PAGESIZE;
          }
          if(ucNumOfSingle !=0)
          {
            HT24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            HT24CxxWaitEepromStandbyState();
          }
        }
    }
    //
    // if usWriteAddr is not HT24Cxx_FLASH_PAGESIZE aligned.
    //
    else
    {
      //
      // If ucNumByteToWrite < HT24Cxx_FLASH_PAGESIZE.
      //
      if(ucNumOfPage == 0)
      {
        if(usNumByteToWrite > ucCount)
        {
            //
            // Write the data conained in same page.
            //
            HT24CxxPageWrite(pucBuffer, usWriteAddr, ucCount);
            HT24CxxWaitEepromStandbyState();
            //
            // Write the remaining data in the following page.
            //
            HT24CxxPageWrite((unsigned char*)(pucBuffer + ucCount),
                            (usWriteAddr + ucCount), 
                            (usNumByteToWrite - ucCount));
            HT24CxxWaitEepromStandbyState();
        }
        else
        {
            HT24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            HT24CxxWaitEepromStandbyState();
        }
      }
      //
      // If ucNumByteToWrite > HT24Cxx_FLASH_PAGESIZE.
      //
      else
      {
          usNumByteToWrite -= ucCount;
          ucNumOfPage = usNumByteToWrite / HT24Cxx_PAGESIZE;
          ucNumOfSingle = usNumByteToWrite % HT24Cxx_PAGESIZE;
          
          if(ucCount !=0)
          {
            HT24CxxPageWrite(pucBuffer, usWriteAddr, ucCount);
            HT24CxxWaitEepromStandbyState();
            usWriteAddr += ucCount;
            pucBuffer += ucCount;
          }
          while(ucNumOfPage --)
          {
            HT24CxxPageWrite(pucBuffer, usWriteAddr,
                            (unsigned char)HT24Cxx_PAGESIZE);
            HT24CxxWaitEepromStandbyState();
            usWriteAddr += HT24Cxx_PAGESIZE;
            pucBuffer += HT24Cxx_PAGESIZE;
          }
          if(ucNumOfSingle != 0)
          {
            HT24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            HT24CxxWaitEepromStandbyState();
          }
      }
    }
}

//*****************************************************************************
//
//! \brief Writes more than one byte to the HT24Cxx with a single WRITE cycle.
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr HT24Cxx's internal address to write to.
//! \param ucNumByteToWrite number of byte to write to the HT24Cxx
//!
//! This function is to write a page data to HT24Cxx, The appointed byte length
//! data will be written in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void HT24CxxPageWrite(unsigned char* pucBuffer,
                     unsigned short usWriteAddr, 
                     unsigned char ucNumByteToWrite)
{ 
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the HT24Cxxs internal address.
    //
    xI2CMasterWriteS1(HT24Cxx_PIN_I2C_PORT, HT24Cxx_ADDRESS,
                     (unsigned char)((usWriteAddr & 0x00FF)),
                     xfalse);
	  
    //
    // While there is data to be written.
    //
    while(ucNumByteToWrite--)  
    {     
      if(ucNumByteToWrite == 0)
      {
        //
        // Send the byte to be written and STOP condition.
        //
        xI2CMasterWriteS2(HT24Cxx_PIN_I2C_PORT, *pucBuffer, xtrue);
      }	
      else
      {
        //
        // Send the byte to be written.
        //
    	xI2CMasterWriteS2(HT24Cxx_PIN_I2C_PORT, *pucBuffer, xfalse);
        //
        // point to the next byte to be written.
        //
        pucBuffer++;
      } 
    }
}
    
//*****************************************************************************
//
//! \brief Reads a block of data from the HT24Cxx.
//!
//! \param pucBuffer specifies the location data which will be store
//! \param usReadAddr HT24Cxx internal address to read from.
//! \param usNumByteToRead number of bytes to read from the HT24Cxx.
//!
//! This function is to read data from HT24Cxx, the appointed byte length data
//! will be read in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void HT24CxxBufferRead(unsigned char* pucBuffer,
                      unsigned short usReadAddr,
                      unsigned short usNumByteToRead)
{
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the HT24Cxxs internal address.
    //
    xI2CMasterWriteS1(HT24Cxx_PIN_I2C_PORT, HT24Cxx_ADDRESS,
                     (unsigned char)((usReadAddr & 0x00ff)), xfalse);
    //
    // Transmit the LSB of the HT24Cxxs internal address.
    // 
//    xI2CMasterWriteS2(HT24Cxx_PIN_I2C_PORT,
//                     (unsigned char)(usReadAddr & 0x00FF),xfalse);
    //
    // Only read one byte,after read,send STOP condition.
    //
    if(usNumByteToRead == 1)
    {
      xI2CMasterReadS1(HT24Cxx_PIN_I2C_PORT, HT24Cxx_ADDRESS, pucBuffer, xtrue);
    } 
    else
    {
      xI2CMasterReadS1(HT24Cxx_PIN_I2C_PORT, HT24Cxx_ADDRESS, pucBuffer, xfalse);
    } 
    
    usNumByteToRead--;
    //
    // While there is data to be read.
    //
    while(usNumByteToRead)
    {
    	if(usNumByteToRead == 1)
    	{
          //
          // Disable ACK,read data,and then send STOP condition.
          //
      	  xI2CMasterReadS2(HT24Cxx_PIN_I2C_PORT, pucBuffer, xtrue);
    	}	
    	else
        {
          //
          // Point to the next location where the byte read will saved.
          //
          pucBuffer++;
          //
          // read data.
          //
    	  xI2CMasterReadS2(HT24Cxx_PIN_I2C_PORT, pucBuffer, xfalse);
        }  
        usNumByteToRead--;        
    }
}   
//*****************************************************************************
//
//! \brief Wait for HT24Cxx Standby state.
//!
//! A Stop condition at the end of a Write command triggers the internal
//! Write cycle.
//!
//! \return None.
//
//*****************************************************************************
void HT24CxxWaitEepromStandbyState(void)
{
//    volatile unsigned long ulStatus = 0;
//
//    //
//    // Waitting the I2C Control & I2C bus to idle
//    //
//    do
//    {
//        ulStatus = xHWREG(HT24Cxx_PIN_I2C_PORT + I2C_CSR);
//    }while((ulStatus & I2C_CSR_BUSBUSY));
//    //
//    // Send start and address
//    //
////    xHWREG(HT24Cxx_PIN_I2C_PORT + I2C_TAR) = HT24Cxx_ADDRESS | 0;
//    do
//    {
//        xHWREG(HT24Cxx_PIN_I2C_PORT + I2C_TAR) = HT24Cxx_ADDRESS | 0;
//        xSysCtlDelay(100000);
//        ulStatus = I2CStatusGet(HT24Cxx_PIN_I2C_PORT);
//        if(ulStatus == I2C_MASTER_TRANSMITTER_MODE)
//        {
//        	break;
//        }
//        else
//        {
//        	I2CFlagStatusClear(HT24Cxx_PIN_I2C_PORT, I2C_EVENT_RXNACK);
//        	I2CStopSend(HT24Cxx_PIN_I2C_PORT);
//        }
//    }
//    while(1);
//
//    I2CFlagStatusClear(HT24Cxx_PIN_I2C_PORT, I2C_EVENT_RXNACK);
//    //
//    // Send STOP condition.
//    //
//    I2CStopSend(HT24Cxx_PIN_I2C_PORT);
    xSysCtlDelay(40000);
}
