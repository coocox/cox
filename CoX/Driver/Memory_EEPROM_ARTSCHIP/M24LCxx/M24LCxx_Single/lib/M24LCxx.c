//*****************************************************************************
//
//! \file M24LCxx.c
//! \brief the M24LCxx Driver.
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
#include "M24LCxx.h"
#include "hw_M24LCxx.h"

#if (M24LCxx_Device == M24LC01)
#define M24LCxx_PAGESIZE         M24LC01_PAGE_SIZE 
#define M24LCxx_SIZE             M24LC01_SIZE

#elif (M24LCxx_Device == M24LC02)
#define M24LCxx_PAGESIZE         M24LC02_PAGE_SIZE 
#define M24LCxx_SIZE             M24LC02_SIZE

#elif (M24LCxx_Device == M24LC04)
#define M24LCxx_PAGESIZE         M24LC04_PAGE_SIZE 
#define M24LCxx_SIZE             M24LC04_SIZE

#elif (M24LCxx_Device == M24LC08)
#define M24LCxx_PAGESIZE         M24LC08_PAGE_SIZE 
#define M24LCxx_SIZE             M24LC08_SIZE

#elif (M24LCxx_Device == M24LC16)
#define M24LCxx_PAGESIZE         M24LC16_PAGE_SIZE 
#define M24LCxx_SIZE             M24LC16_SIZE

#elif (M24LCxx_Device == M24LC32)
#define M24LCxx_PAGESIZE         M24LC32_PAGE_SIZE 
#define M24LCxx_SIZE             M24LC32_SIZE

#elif (M24LCxx_Device == M24LC64)
#define M24LCxx_PAGESIZE         M24LC64_PAGE_SIZE
#define M24LCxx_SIZE             M24LC64_SIZE

#endif

#define I2C_Speed               100000

                                           
//*****************************************************************************
//
//! \brief Initialize M24LCxx and I2C  
//!
//! \param None
//!
//! This function initialize the mcu I2C as master and specified I2C port.the 
//! master block will be set up to transfer data at 400 kbps.
//! 
//! \return None.
//
//*****************************************************************************
void M24LCxxInit(void)
{
    //
    // Enable GPIO Periph clock and Alternate Fuction I/O clock.
    //  
    xSysCtlPeripheralEnable(M24LCxx_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    // Enable the I2C which is connected with M24LCxx
    //
    xSysCtlPeripheralEnable2(M24LCxx_PIN_I2C_PORT);   
    //
    // Set M24LCxx_PIN_I2C_SCK as IICx.SCK
    //
    xSPinTypeI2C(M24LCxx_I2C_SCK, M24LCxx_PIN_I2C_SCK);   
    //
    // Set M24LCxx_PIN_I2C_SDA as I2Cx.SDA
    //
    xSPinTypeI2C(M24LCxx_I2C_SDA, M24LCxx_PIN_I2C_SDA);  

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(M24LCxx_PIN_I2C_PORT, I2C_Speed);
    //
    //! parameters refer to function explanation
    //
    I2CMasterInit(M24LCxx_PIN_I2C_PORT, 36000000, 0, 1);
    //
    // I2C enable
    //
    xI2CMasterEnable(M24LCxx_PIN_I2C_PORT);

}

//*****************************************************************************
//
//! \brief Write one byte to M24LCxx. 
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr specifies the address which data will be written.
//! 
//!  This function is to write one byte to M24LCxx,one byte will be writen in 
//!  appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24LCxxByteWrite(unsigned char* pucBuffer, unsigned short usWriteAddr)
{
    xASSERT((usWriteAddr >= 0) && (usWriteAddr <= M24LCxx_SIZE));
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the M24LCxxs internal address.
    //
    xI2CMasterWriteS1(M24LCxx_PIN_I2C_PORT, M24LCxx_ADDRESS, 
                     (unsigned char)((usWriteAddr & 0xFF00) >> 8), 
                     xfalse);
    //
    // Transmit the LSB of the M24LCxxs internal address.
    //  
    xI2CMasterWriteS2(M24LCxx_PIN_I2C_PORT, 
                     (unsigned char)(usWriteAddr & 0x00FF),
                     xfalse);
    
    //
    // Send the byte to be written.
    //
    xI2CMasterWriteS2(M24LCxx_PIN_I2C_PORT, *pucBuffer, xtrue);
}

//*****************************************************************************
//
//! \brief Writes buffer of data to the M24LCxx.  
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr M24LCxx's internal address to write to.
//! \param usNumByteToWrite Number of bytes to write to the M24LCxx.
//! 
//!  This function is to Writes more then one byte to the M24LCxx,the appointed 
//!  byte length data will be writen in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24LCxxBufferWrite(unsigned char* pucBuffer, 
                       unsigned short usWriteAddr, 
                       unsigned short usNumByteToWrite)
{
    unsigned char ucNumOfPage = 0, ucNumOfSingle = 0, ucCount = 0;
    unsigned short usAddr = 0;
    
    usAddr = usWriteAddr % M24LCxx_PAGESIZE;
    ucCount = M24LCxx_PAGESIZE -usAddr;
    ucNumOfPage = usNumByteToWrite / M24LCxx_PAGESIZE;
    ucNumOfSingle = usNumByteToWrite % M24LCxx_PAGESIZE;
    
    //
    // if usWriteAddr is M24LCxx_FLASH_PAGESIZE aligned.
    //
    if(usAddr == 0)
    { 
        //
        // If ucNumByteToWrite < M24LCxx_FLASH_PAGESIZE.
        //
        if(ucNumOfPage == 0)
        {
          M24LCxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
          M24LCxxWaitEepromStandbyState();
        }
        //
        // If ucNumByteToWrite > M24LCxx_FLASH_PAGESIZE.
        //
        else
        {
          while(ucNumOfPage--)
          {
            M24LCxxPageWrite(pucBuffer, usWriteAddr, 
                            (unsigned char)M24LCxx_PAGESIZE);
            M24LCxxWaitEepromStandbyState();
            usWriteAddr += M24LCxx_PAGESIZE;
            pucBuffer +=M24LCxx_PAGESIZE;
          }
          if(ucNumOfSingle !=0)
          {
            M24LCxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            M24LCxxWaitEepromStandbyState();
          }
        }
    }
    //
    // if usWriteAddr is not M24LCxx_FLASH_PAGESIZE aligned.
    //
    else
    {
      //
      // If ucNumByteToWrite < M24LCxx_FLASH_PAGESIZE.
      //
      if(ucNumOfPage == 0)
      {
        if(usNumByteToWrite > ucCount)
        {
            //
            // Write the data contained in same page.
            //
            M24LCxxPageWrite(pucBuffer, usWriteAddr, ucCount);
            M24LCxxWaitEepromStandbyState();
            //
            // Write the remaining data in the following page.
            //
            M24LCxxPageWrite((unsigned char*)(pucBuffer + ucCount), 
                            (usWriteAddr + ucCount), 
                            (usNumByteToWrite - ucCount));
            M24LCxxWaitEepromStandbyState();
        }
        else
        {
            M24LCxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            M24LCxxWaitEepromStandbyState();
        }
      }
      //
      // If ucNumByteToWrite > M24LCxx_FLASH_PAGESIZE.
      //
      else
      {
          usNumByteToWrite -= ucCount;
          ucNumOfPage = usNumByteToWrite / M24LCxx_PAGESIZE;
          ucNumOfSingle = usNumByteToWrite % M24LCxx_PAGESIZE;
          
          if(ucCount !=0)
          {
            M24LCxxPageWrite(pucBuffer, usWriteAddr, ucCount);
            M24LCxxWaitEepromStandbyState();
            usWriteAddr += ucCount;
            pucBuffer += ucCount;
          }
          while(ucNumOfPage --)
          {
            M24LCxxPageWrite(pucBuffer, usWriteAddr, 
                            (unsigned char)M24LCxx_PAGESIZE);
            M24LCxxWaitEepromStandbyState();
            usWriteAddr += M24LCxx_PAGESIZE;
            pucBuffer += M24LCxx_PAGESIZE;
          }
          if(ucNumOfSingle != 0)
          {
            M24LCxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            M24LCxxWaitEepromStandbyState();
          }
      }
    }
}

//*****************************************************************************
//
//! \brief Writes more than one byte to the M24LCxx with a single WRITE cycle.  
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr M24LCxx's internal address to write to.
//! \param ucNumByteToWrite number of byte to write to the M24LCxx
//!
//! This function is to write a page data to M24LCxx, The appointed byte length 
//! data will be written in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24LCxxPageWrite(unsigned char* pucBuffer, 
                     unsigned short usWriteAddr, 
                     unsigned char ucNumByteToWrite)
{
#if M24LCxx_Device>M24LC02
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the M24LCxxs internal address.
    //
    xI2CMasterWriteS1(M24LCxx_PIN_I2C_PORT, M24LCxx_ADDRESS,
                     (unsigned char)((usWriteAddr & 0xFF00) >> 8),
                     xfalse);
    //
    // Transmit the LSB of the M24LCxxs internal address.
    //    
    xI2CMasterWriteS2(M24LCxx_PIN_I2C_PORT,
                      (unsigned char)(usWriteAddr & 0x00FF),
                      xfalse);
#else
    xI2CMasterWriteS1(M24LCxx_PIN_I2C_PORT, M24LCxx_ADDRESS,
                         (unsigned char)((usWriteAddr & 0xFF)),
                         xfalse);
#endif
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
        xI2CMasterWriteS2(M24LCxx_PIN_I2C_PORT, *pucBuffer, xtrue);
      }	
      else
      {
        //
        // Send the byte to be written.
        //
    	xI2CMasterWriteS2(M24LCxx_PIN_I2C_PORT, *pucBuffer, xfalse);
        //
        // point to the next byte to be written.
        //
        pucBuffer++;
      } 
    }
}
    
//*****************************************************************************
//
//! \brief Reads a block of data from the M24LCxx.  
//!
//! \param pucBuffer specifies the location data which will be store
//! \param usReadAddr M24LCxx internal address to read from.
//! \param usNumByteToRead number of bytes to read from the M24LCxx.
//!
//! This function is to read data from M24LCxx, the appointed byte length data 
//! will be read in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24LCxxBufferRead(unsigned char* pucBuffer, 
                      unsigned short usReadAddr,
                      unsigned short usNumByteToRead)
{

#if	M24LCxx_Device>M24LC02
		//
	    // Transmit the START condition, the slave address and the MSB of
	    // the M24LCxxs internal address.
	    //
	xI2CMasterWriteS1(M24LCxx_PIN_I2C_PORT, M24LCxx_ADDRESS,
                     (unsigned char)((usReadAddr & 0xFF00) >> 8), xfalse);
			//
	        // Transmit the LSB of the M24LCxxs internal address.
	        //
    xI2CMasterWriteS2(M24LCxx_PIN_I2C_PORT,
                     (unsigned char)(usReadAddr & 0x00FF),xfalse);
#else
    xI2CMasterWriteS1(M24LCxx_PIN_I2C_PORT, M24LCxx_ADDRESS, 
                     (unsigned char)((usReadAddr & 0xFF)), xfalse);
#endif

    //
    // Only read one byte,after read,send STOP condition.
    //
    if(usNumByteToRead == 1)
    {
      xI2CMasterReadS1(M24LCxx_PIN_I2C_PORT, M24LCxx_ADDRESS, pucBuffer, xtrue);     
    } 
    else
    {
      xI2CMasterReadS1(M24LCxx_PIN_I2C_PORT, M24LCxx_ADDRESS, pucBuffer, xfalse);
    } 
    pucBuffer++;
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
      	  xI2CMasterReadS2(M24LCxx_PIN_I2C_PORT, pucBuffer, xtrue);
    	}	
    	else
        {
          //
          // read data.
          //
    	  xI2CMasterReadS2(M24LCxx_PIN_I2C_PORT, pucBuffer, xfalse);
    	  //
    	  // Point to the next location where the byte read will saved.
    	  //
    	  pucBuffer++;

        }  
        usNumByteToRead--;        
    }
}   
//*****************************************************************************
//
//! \brief Wait for M24LCxx Standby state.  
//!
//! A Stop condition at the end of a Write command triggers the internal
//! Write cycle.
//!
//! \return None.
//
//*****************************************************************************
void M24LCxxWaitEepromStandbyState(void)
{
    volatile unsigned short usSR1Tmp = 0; 
    do
    {
      //
      // Send START condition.
      //
      //I2CStartSend(M24LCxx_PIN_I2C_PORT);
      xHWREG(M24LCxx_PIN_I2C_PORT + I2C_CR1) |= I2C_CR1_START;
      //
      // Read I2C SR1 register to clear pending flags.
      //
      usSR1Tmp = xHWREG(M24LCxx_PIN_I2C_PORT + I2C_SR1);
      //
      // Send M24LCxx address for write.
      //
      xI2CMasterDataPut(M24LCxx_PIN_I2C_PORT, (M24LCxx_ADDRESS << 1) | 0);
    }while(!((xHWREG(M24LCxx_PIN_I2C_PORT + I2C_SR1)) & I2C_SR1_ADDR));   
    //
    // Clear Af flag.
    // 
    I2CFlagStatusClear(M24LCxx_PIN_I2C_PORT, I2C_SR1_AF);
    //
    // Send STOP condition.
    //
    //xI2CMasterStop(M24LCxx_PIN_I2C_PORT);
    xHWREG(M24LCxx_PIN_I2C_PORT + I2C_CR1) |= I2C_CR1_STOP;
}
