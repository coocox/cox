//*****************************************************************************
//
//! \file TCN75.c
//! \brief header file of Driver for TCN75
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
#include "TCN75.h"
#include "xhw_TCN75.h"

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
TCN75Init(unsigned long ulRate)
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
//! \brief DeInialize the Temperatrue Sensor,sets the Sensor as shutdown mode, 
//! disable I2C.
//!
//! \param None 
//!
//! \return None.
//
//*****************************************************************************
void  
TCN75DeInit()
{
    TCN75ModeSet(TCN75_SHUTDOWM_ON);
   
    xSysCtlPeripheralDisable(XSYSCTL_PERIPH_I2C);
}

//*****************************************************************************
//
//! \brief When reading the value in TCN75 registers through I2C0,we can
//! set I2C0 Master transfer setup data structure using this API.
//!
//! \param ucReg The address of TC75 registers.
//!
//! The parameter \e ucReg can be one of the following values:
//!
//! - \b  TCN75_TEMP
//! - \b  TCN75_CONFIG 
//! - \b  TCN75_THYS 
//! - \b  TCN75_TSET
//!
//!
//! \return The value in TCN75 registers.
//
//*****************************************************************************
long
TCN75RegRead(unsigned char ucReg)
{
    xtI2CMasterTransferCfg Cfg;

    unsigned char ucSendBuf[1] = {0};
    unsigned long ulSendLength = 1;
    unsigned char ucReceiveBuf[2] = {0};
    unsigned long ulReceiveLength;
	long ulRegData;
	unsigned char ucFlag;

	ucSendBuf[0] = ucReg;

	if((ucReg & 0x0f) == TCN75_CONFIG)
	{
    	ulReceiveLength = 1;
	}
    else if((ucReg & 0x0f) < 0x04)
	{
		ulReceiveLength	= 2;
	}
    else
	{
		return 0;
	}
	//
    //Sets the value of member in the I2C0 Master transfer setup data structure.
    //
    Cfg.ulSlave = TCN75Address;
    Cfg.pvWBuf = ucSendBuf;
    Cfg.ulWLen = ulSendLength;
    Cfg.pvRBuf = ucReceiveBuf;
    Cfg.ulRLen = ulReceiveLength;
   
    //
    //Starts transfer.
    // 
    ucFlag = I2CMasterTransfer(I2C_BASE, &Cfg, I2C_TRANSFER_POLLING);
	if(ucFlag == xfalse)
    {
        return 0;
    }
    if((ucReg & 0x0f) == TCN75_CONFIG) 
	{
		ulRegData = ucReceiveBuf[0];	
	} 
	else if((ucReg & 0x0f) < 0x04)
	{
		ulRegData = (ucReceiveBuf[0] << 8) | ucReceiveBuf[1];
		if((ulRegData & 0x8000) == 0x8000)
            ulRegData |= 0xFFFF0000;
	}
	else
	{
		return 0;
	}
    return ulRegData;
}

//*****************************************************************************
//
//! \brief When writing a value in TCN75 registers through I2C0,we can
//! set I2C0 Master transfer setup data structure using this API.
//!
//! \param ucReg The address of TCN75 registers.
//! \param vpValue The value that be writed in corresponding TCN75 
//!  registers.
//!
//! The parameter \e ucReg can be one of the following values:
//!
//! - \b  TCN75_CONFIG 
//! - \b  TCN75_THYS 
//! - \b  TCN75_TSET
//!
//!
//! \return None.
//
//*****************************************************************************
void
TCN75RegWrite(unsigned char ucReg, void* vpValue)
{
    xtI2CMasterTransferCfg Cfg;

    unsigned char ucSendBuf[3];
    unsigned long ulSendLength;
	int iTemp;
    
	ucSendBuf[0] = ucReg;
    
	if((ucReg & 0x0f) == TCN75_CONFIG)
	{
		ucSendBuf[1] = (*(char*)vpValue);
		ulSendLength = 2;
	}
    else if((ucReg & 0x0f) < 0x04)
	{
		iTemp =(int)((*(float*)vpValue)*2);
		iTemp = iTemp << 7;
		ucSendBuf[2] = (char) iTemp;
        ucSendBuf[1] = (char) (iTemp>>8);
		ulSendLength = 3;
	}
 	else
	{
		return;
	}
    //
    // Sets the value of member in the I2C0 Master transfer setup data structure.
    //
    Cfg.ulSlave = TCN75Address;
    Cfg.pvWBuf = ucSendBuf;
    Cfg.ulWLen = ulSendLength;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    
    //
    // Starts transfer.
    // 
    I2CMasterTransfer(I2C_BASE, &Cfg, I2C_TRANSFER_POLLING);  
}

//*****************************************************************************
//
//! \brief Sets TCN75 mode.
//!
//! \param ucMode The mode of TCN75.
//!
//! The parameter \e ucMode can be one of the following values:
//!
//! - \b  TCN75_SHUTDOWM_ON 
//! - \b  TCN75_SHUTDOWN_OFF
//!
//! \return None.
//
//*****************************************************************************
void 
TCN75ModeSet(unsigned char ucMode)
{
	unsigned char ucConfig;
	
	ucConfig = TCN75RegRead(TCN75_CONFIG);

	ucConfig = (ucConfig & 0xFE) | ucMode;

	TCN75RegWrite(TCN75_CONFIG, &ucConfig);
}

//*****************************************************************************
//
//! \brief Gets TCN75 mode.
//!
//! \param None.
//!
//! \return the following value.
//!            - \ref TCN75_SHUTDOWM_ON, shut down mode
//!            - \ref TCN75_SHUTDOWN_OFF, normal mode
//
//*****************************************************************************
unsigned char
TCN75ModeGet()
{
	return TCN75RegRead(TCN75_CONFIG) & 0x1;
}

//*****************************************************************************
//
//! \brief Sets the Fault Queue of TCN75 Temperature Sensor.
//!
//! \param ucFq The Fault Queue of TCN75 Temperature Sensor.
//!       - \ref TCN75_FAULTQUE_1, 1
//!       - \ref TCN75_FAULTQUE_2, 2
//!       - \ref TCN75_FAULTQUE_4, 4
//!       - \ref TCN75_FAULTQUE_6, 6
//!
//! \return None.
//
//*****************************************************************************
void 
TCN75FaultQueSet(unsigned char ucFq)
{
	unsigned char ucConfig;

	ucConfig = TCN75RegRead(TCN75_CONFIG);

	ucConfig = (ucConfig & 0xE7) | ucFq;

	TCN75RegWrite(TCN75_CONFIG, &ucConfig);
}
//*****************************************************************************
//
//! \brief Gets the Fault Queue of TCN75 Temperature Sensor.
//!
//! \param None
//! 
//! \return the Fault Queue of TCN75 Temperature Sensor.
//
//*****************************************************************************
unsigned char
TCN75FaultQueGet()
{
	return TCN75RegRead(TCN75_CONFIG) & 0x18;
}

//*****************************************************************************
//
//! \brief Configures the GPIO pin and set callback function.
//!
//! \param xtIntCallback The callback function for event interrupt.
//! \param ucTrigMode The trigger condition of interrupt of Event Output.
//!  it can be: 
//!       - \ref ALERTPOL_HIGH, assert with high level
//!       - \ref ALERTPOL_LOW, assert with low level
//! \param ulEventMode Comparator mode or Interrupt mode, it can be:
//!        - \ref TCN75_MODE_CMP, Comparator mode
//!        - \ref TCN75_MODE_INT, Interrupt mode
//!
//! \return None.
//
//*****************************************************************************
void  
TCN75IntConfig(xtEventCallback xtIntCallback, 
                 unsigned long ulTrigMode, unsigned long ulEventMode)
{
    unsigned char ucConfig;
    
    ucConfig = TCN75RegRead(TCN75_CONFIG);
    
    //
    // Config the trigger level and Event Output Mode
    //
    ucConfig = (ucConfig & 0xFB) | ulTrigMode;
    ucConfig = (ucConfig & 0xFD) | (ulEventMode<<1);    
    TCN75RegWrite(TCN75_CONFIG, &ucConfig);

    //
    // Config the Pin mode and Set callback funciton.
    //
    xGPIODirModeSet(EventPORT, EventPIN, GPIO_DIR_MODE_IN);
    xGPIOPinIntCallbackInit(EventPORT, EventPIN, xtIntCallback);

    if(ulTrigMode & ALERTPOL_HIGH == ALERTPOL_HIGH)
    {
        xGPIOPinIntEnable(EventPORT, EventPIN, GPIO_HIGH_LEVEL);   
    }
    else
    {
        xGPIOPinIntEnable(EventPORT, EventPIN, GPIO_LOW_LEVEL);
    } 
}
//*****************************************************************************
//
//! \brief Gets temperature from TCN75 register.
//!
//! \param ucReg The register that stores temperature.
//!
//! The parameter \e ucReg can be one of the following values:
//!
//! - \b   TCN75_TEMP
//! - \b   TCN75_THYS 
//! - \b   TCN75_TSET
//!
//! \return Returns  temperature.
//
//*****************************************************************************
long 
TCN75TempGet(unsigned char ucReg)
{
    return TCN75RegRead(ucReg)>>7; 
}

//*****************************************************************************
//
//! \brief Read the temperature value in float degree celsius (°„C)
//!
//! \param ucReg The register that stores temperature.
//!
//! The parameter \e ucReg can be one of the following values:
//!
//! -\b  TCN75_TEMP
//! -\b	 TCN75_THYS 
//! -\b	 TCN75_TSET
//!
//! \return temperature in 	parameter \e ucReg.
//
//*****************************************************************************
float 
TCN75TempReadFDC(unsigned char ucReg)
{
    long ulTemp;
	float fTemp;
       
    //
    // Read the temperature register
    //
    ulTemp = TCN75RegRead(ucReg);
	ulTemp = ulTemp>>7;
    
    //
    // Conveter the temperature register data to degree celsius (°„C)
    //
    fTemp = (float)(ulTemp * 0.5);   
    return fTemp;
}





