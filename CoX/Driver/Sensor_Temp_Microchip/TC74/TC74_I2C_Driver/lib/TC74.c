//*****************************************************************************
//
//! \file TC74.c
//! \brief header file of Driver for TC74
//! \version 1.0
//! \date 9/5/2011
//! \author CooCox
//! \copy
//
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
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xi2c.h"
#include "TC74.h"
#include "xhw_TC74.h"

//*****************************************************************************
//
//! \brief Uses I2C0 as master.
//!
//! \param None
//! 
//! \return None
//
//*****************************************************************************
void 
TC74Init(unsigned long ulRate)
{
    //
    //Enable I2C0.
    //
    xSysCtlPeripheralEnable(XSYSCTL_PERIPH_I2C);

    //
    //Select PA8 as the SDA of I2C0.
    //
    xSPinTypeI2C(I2C0SDA, I2CDATA_PIN); 

    //
    //Select PA9 as the SCL of I2C0.
    //
    xSPinTypeI2C(I2C0SCL, I2CSCL_PIN);

    //
    //Set the clock rate of the I2C0.
    //
    xI2CMasterInit(I2C_BASE, ulRate);
}

//*****************************************************************************
//
//! \brief DeInialize the Temperatrue Sensor,sets the Sensor as standby mode, 
//! disable I2C.
//!
//! \param None 
//!
//! \return None.
//
//*****************************************************************************
void  
TC74DeInit()
{
    TC74ModeSet(TC74_MODE_STANDBY);
   
    xSysCtlPeripheralDisable(XSYSCTL_PERIPH_I2C);
}

//*****************************************************************************
//
//! \brief When reading the value in TC74 registers through I2C0,we can
//! set I2C0 Master transfer setup data structure using this API.
//!
//! \param ucReg The address of TC74 registers.
//!
//! The parameter \e ucReg can be one of the following values:
//!
//! - \b TC74_CONFIG 
//! - \b TC74_TEMP
//!
//! \return The value of master receivebuf[0].
//
//*****************************************************************************
unsigned char 
TC74RegRead(unsigned char ucReg)
{
    xtI2CMasterTransferCfg Cfg;

    unsigned char ucSendBuf[1] = {0};
    unsigned long ulSendLength = 1;
    unsigned char ucReceiveBuf[1] = {0};
    unsigned long ulReceiveLength = 1;

    ucSendBuf[0] = ucReg;
    
    //
    //Sets the value of member in the I2C0 Master transfer setup data structure.
    //
    Cfg.ulSlave = TC74Address;
    Cfg.pvWBuf = ucSendBuf;
    Cfg.ulWLen = ulSendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ucReceiveBuf;
    Cfg.ulRLen = ulReceiveLength;
    Cfg.ulRCount = 0; 
    
    //
    //Starts transfer.
    // 
    I2CMasterTransfer(I2C_BASE, &Cfg, I2C_TRANSFER_POLLING);

    return ucReceiveBuf[0];
}

//*****************************************************************************
//
//! \brief When writing a value in TC74 registers through I2C0,we can
//! set I2C0 Master transfer setup data structure using this API.
//!
//! \param ucReg The address of TC74 registers.
//! \param ulValue The value that be writed in corresponding TC74 
//!  registers.
//!
//! The parameter \e ucReg can be one of the following values:
//!
//! - \b TC74_CONFIG 
//!
//! \return None.
//
//*****************************************************************************
void
TC74RegWrite(unsigned char ucReg, unsigned char ucValue)
{
    xtI2CMasterTransferCfg Cfg;

    unsigned char ucSendBuf[2];
    unsigned long ulSendLength = 2;
    unsigned char ucReceiveBuf[1] ={0};
    unsigned long ulReceiveLength = 0;
    
    ucSendBuf[0] = ucReg;
    ucSendBuf[1] = ucValue;
   
    //
    //Sets the value of member in the I2C0 Master transfer setup data structure.
    //
    Cfg.ulSlave = TC74Address;
    Cfg.pvWBuf = ucSendBuf;
    Cfg.ulWLen = ulSendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ucReceiveBuf;
    Cfg.ulRLen = ulReceiveLength;
    Cfg.ulRCount = 0;
    
    //
    //Starts transfer.
    // 
    I2CMasterTransfer(I2C_BASE, &Cfg, I2C_TRANSFER_POLLING);  
}

//*****************************************************************************
//
//! \brief Sets the TC74  mode through i2c0.
//!
//! \param ucMode is the mode of TC74A0.
//! 
//! The parameter \e ucMode can be one of the following values:
//!
//! - \b TC74_MODE_STANDBY
//! - \b TC74_MODE_NORMAL
//!
//! \return None
//
//*****************************************************************************
void 
TC74ModeSet(unsigned char ucMode)
{   
    unsigned char ucValue;

    if (ucMode == TC74_MODE_STANDBY)
    { 
        ucValue = TC74_MODE_STANDBY;
    }
    else
    { 
        ucValue = TC74_MODE_NORMAL;
    }
    
    TC74RegWrite(TC74_CONFIG, ucValue);
}

//*****************************************************************************
//
//! \brief Gets the mode(standy/normal) of TC74 through i2c.
//!
//! \param None
//! 
//! \return Returns a bit that indicates whether TC74 is in standy mode or not.
//
//*****************************************************************************
unsigned char 
TC74ModeGet(void)
{
    return  TC74RegRead(TC74_CONFIG)>>7; 
}

//*****************************************************************************
//
//! \brief Checks whether data is ready or not.
//!
//! \param None
//! 
//! \return Returns xtrue if data is ready,else return xfalse.
//
//*****************************************************************************
xtBoolean 
TC74DATAReady(void)
{       
    if (TC74RegRead(TC74_CONFIG)>>6 & 0x1)
    {
        return xtrue;
    }
    else 
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief Gets temperature from TC74_TEMP register.
//!
//! \param None
//! 
//! \return Returns current temperature.
//
//*****************************************************************************
char 
TC74TempGet(void)
{
    return TC74RegRead(TC74_TEMP); 
}


