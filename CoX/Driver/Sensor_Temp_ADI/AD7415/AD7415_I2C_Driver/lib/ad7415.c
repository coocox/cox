//*****************************************************************************
// 
//! \file di_ad7415.c
//! \brief Temperature Sensor (AD7416) and Four Single-Channel ADC drver
//! \version V2.1.1.0
//! \date 25. Aug. 2011
//! \author CooCox
//!
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
//! AND ANY ExPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, ExEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xi2c.h"
#include "hw_ad7415.h"
#include "ad7415.h"

//*****************************************************************************
//
//! \brief Read the register of the AD7415 device.
//!
//! \param reg Register selected, it should be :
//!                     -AD7415_TEMP : Temperature Register
//!                     -AD7415_CFG : Configuration Register1
//!
//! \return Register value
//
//*****************************************************************************
short AD7415RegRead(unsigned char ucReg)
{
    xtI2CMasterTransferCfg cfg;
    unsigned char ucTemp = ucReg;
    unsigned char ucRcv[2];
    short ulRegData;  
    unsigned char ucFlag;
    
    cfg.ulSlave = AD7415_I2C_ADDRESS;
    cfg.pvWBuf = &ucTemp;
    cfg.ulWLen = 1;
    cfg.ulRLen = 0;
    cfg.pvRBuf = ucRcv;
  
    //
    // different register has different receive length
    //
    switch(ucReg) 
    {
        //
        // Temperature Register
        //
        case AD7415_TEMP:  
          cfg.ulRLen = 2; break;
        //
        // Configuration Register
        //
        case AD7415_CFG:  
        cfg.ulRLen = 1; break;        
        default :    
          break;
    }    
    
    //
    // Data transfering
    //
    ucFlag = xI2CMasterTransfer(AD7415_MASTER_BASE, &cfg, I2C_TRANSFER_POLLING);
    if(ucFlag == xfalse)
    {
        return 0;
    }
      
    //
    // Deal with the receive buffer and return the register
    //
    switch(ucReg) 
    {    
        //
        // Return the MSB 10 bits of the 16 bits register
        //
        case AD7415_TEMP:  
          ulRegData = ucRcv[0];
          ulRegData = ulRegData << 8;
          ulRegData = ulRegData & 0xff00;
          ulRegData |= ucRcv[1];
          ulRegData = ulRegData >> 6; 
          break; 
        //
        // Return the 8 bits config register
        //
        case AD7415_CFG: 
          ulRegData = ucRcv[0];
        break;
        default :     
          break;
    }
    
    return ulRegData;
}

//*****************************************************************************
//
//! \brief Write the register of the AD7415 device.
//!
//! \param reg Register selected, it should be :
//!                     -AD7415_TEMP : Temperature Register
//!                     -AD7415_CFG : Configuration Register1
//!
//! \return Register value
//
//*****************************************************************************
void AD7415RegWrite(unsigned char ucReg, short ulValue)
{
    xtI2CMasterTransferCfg cfg;
    unsigned char ucSendLength;
    unsigned char ucSendBuf[3];
    short ulRegValue = ulValue;
    
    ucSendBuf[0] = ucReg;
    
    //
    //deal with the receive buffer and return the register
    //
    switch(ucReg) 
    {
        //
        // Left shift 6 bits
        //
        case AD7415_TEMP:  
          ulRegValue = ulRegValue << 6;
          ucSendBuf[1] = ulRegValue >> 8;
          ucSendBuf[2] = ulRegValue & 0xff;
          ucSendLength = 3;
          break;     
        //
        // Do not need shift
        //
        case AD7415_CFG: 
          ucSendBuf[1] = ulRegValue & 0xff;
          ucSendLength = 2;
          break;
        default :     
          break;
    }  
    
    cfg.ulSlave = AD7415_I2C_ADDRESS;
    cfg.pvWBuf = ucSendBuf;
    cfg.ulWLen = ucSendLength;
    cfg.ulRLen = 0;
    cfg.pvRBuf = 0;
   
    //
    // data transfering
    //
    xI2CMasterTransfer(AD7415_MASTER_BASE, &cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Initializes the device
//!
//! \param rate The master baud rate  
//!
//! \ulPDEnable The ulPDEnble is chose to decide enable the power down mode or 
//! not. it can be selected from: - AD7415_PowerDown_Enter
//!                               - AD7415_PowerDown_Quit
//!                               .
//!
//! \return none
//
//*****************************************************************************
void AD7415Init(unsigned long ulRate, unsigned long ulPDEnable)
{   
    unsigned long ulTemp;
    
    //
    // Config the I2C master
    //
    if (AD7415_MASTER_BASE == I2C0_BASE)
    {
        //
        // Congigure the i2c pin
        //
        xSPinTypeI2C(I2C0SCK, AD7415_PIN_I2CSCK);
        xSPinTypeI2C(I2C0SDA, AD7415_PIN_I2CSDA); 
    }
    else if(AD7415_MASTER_BASE == I2C1_BASE)
    {
        //
        // Congigure the i2c pin
        //
        xSPinTypeI2C(I2C1SCK, AD7415_PIN_I2CSCK);
        xSPinTypeI2C(I2C1SDA, AD7415_PIN_I2CSDA); 
            
    }
    else
    {
        //
        // more i2c to be enable
        //
    }
    xSysCtlPeripheralEnable2(AD7415_MASTER_BASE);
   
    //
    // Init the device rate
    //
    xI2CMasterInit(AD7415_MASTER_BASE, ulRate);
    
    if(ulPDEnable == AD7415_CFG_PD_ENABLE)
    {
        ulTemp = AD7415RegRead(AD7415_CFG);
        AD7415RegWrite(AD7415_CFG, ulPDEnable | ulTemp);      
    }  
    else
    {
        ulTemp = AD7415RegRead(AD7415_CFG);
        ulTemp &= 0x44;
        AD7415RegWrite(AD7415_CFG, ulTemp);  
    }
  
}

//*****************************************************************************
//
//! \brief Read the temperature value in integer degree celsius (°„C)
//!
//! \return temperature in integer mode
//
//*****************************************************************************
short AD7415TempReadLDC(void)
{
    short sTemp = 0;
    
    //
    // Read the temperature register
    //
    sTemp = AD7415RegRead(AD7415_TEMP);
    
    
    //
    // Conveter the temperature register data to degree celsius (°„C)
    // 
    sTemp = (short)(sTemp * 0.25); 
    return sTemp;
}

//*****************************************************************************
//
//! \brief Read the temperature value in float degree celsius (°„C)
//!
//! \return temperature in float mode
//
//*****************************************************************************
float AD7415TempReadFDC(void)
{
    short sTemp;
    float fTemp;   
    //
    // Read the temperature register
    //
    sTemp = AD7415RegRead(AD7415_TEMP);
     
    //
    // Conveter the temperature register data to degree celsius (°„C)
    //
    fTemp = (float)(sTemp * 0.25);   
    return fTemp;
}

//*****************************************************************************
//
//! \brief Read the temperature value in original rigister data
//!
//! \return temperature register value
//
//*****************************************************************************
short AD7415TempReadMSB10Bit(void)
{
    short sTemp;
    //
    // Read the temperature register
    //
    sTemp = AD7415RegRead(AD7415_TEMP);
    
    return sTemp;
}

//*****************************************************************************
//
//! \brief Enter power down mode 
//!
//! \return none
//
//*****************************************************************************
void AD7415PowerDownEnter(void)
{
    unsigned long ulTemp;
    
    ulTemp = AD7415RegRead(AD7415_CFG);
    xSysCtlDelay(5);
    AD7415RegWrite(AD7415_CFG, AD7415_CFG_PD_ENABLE | ulTemp);     
}

//*****************************************************************************
//
//! \brief Quit power down mode 
//!
//! \return none
//
//*****************************************************************************
void AD7415PowerDownQuit(void)
{
    unsigned long ulTemp;
    
    ulTemp = AD7415RegRead(AD7415_CFG);
    ulTemp &= 0x44;
    AD7415RegWrite(AD7415_CFG, ulTemp);     
}

//*****************************************************************************
//
//! \brief When the chip is in power down mode, call this function to triger one
//! temperature convst.
//!
//! \return none
//
//*****************************************************************************
void AD7415PowerDownConvert(void)
{
    unsigned long ulTemp;
    
    ulTemp = AD7415RegRead(AD7415_CFG);
    
    //
    // Set the bit.2 of config register to triger one temperature convst
    //
    AD7415RegWrite(AD7415_CFG, AD7415_CFG_ONE_SHOT_CONVERT | ulTemp);  
    xSysCtlDelay(5);
    
}

//*****************************************************************************
//
//! \brief Enable i2c filter
//!
//! \param none
//!
//! \return none
//
//*****************************************************************************
void AD7415FilterEnable(void)
{
    short ulTemp;
    
    ulTemp = AD7415RegRead(AD7415_CFG);
    
    AD7415RegWrite(AD7415_CFG, AD7415_CFG_FILTER_ENABLE | ulTemp);
}

//*****************************************************************************
//
//! \brief Disable i2c filter
//!
//! \param none
//! 
//! \return none 
//
//*****************************************************************************
void AD7415FilterDisable(void)
{
    unsigned long ulTemp;
    
    ulTemp = AD7415RegRead(AD7415_CFG);
    
    //
    // Some bits can not wirte 1
    //
    ulTemp &= 0x84; 
    
    AD7415RegWrite(AD7415_CFG, ulTemp);
}


//*****************************************************************************
//
//! \brief de-init the AD7415 device
//!
//! \return none
//
//*****************************************************************************
void AD7415DeInit(void)
{
    xSysCtlPeripheralDisable2(AD7415_MASTER_BASE);   
}
