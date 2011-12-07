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
#include "hw_TCN75.h"

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
    // Config the I2C pin
    //
    if(TCN75_MASTER_BASE == xI2C0_BASE)
    {
        xSPinTypeI2C(I2C0SCK, TCN75_PIN_I2CSCK);
        xSPinTypeI2C(I2C0SDA, TCN75_PIN_I2CSDA);
    }
    else
    {
        xSPinTypeI2C(I2C1SCK, TCN75_PIN_I2CSCK);
        xSPinTypeI2C(I2C1SDA, TCN75_PIN_I2CSDA);
    }
    
    //
    // Config the I2C master
    //
    xSysCtlPeripheralEnable2(TCN75_MASTER_BASE);
   
    //
    // Init the device rate
    //
    xI2CMasterInit(TCN75_MASTER_BASE, ulRate);
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
    TCN75Shutdown();
   
    xSysCtlPeripheralDisable2(TCN75_MASTER_BASE);
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
    ucFlag = I2CMasterTransfer(TCN75_MASTER_BASE, &Cfg, I2C_TRANSFER_POLLING);
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
    I2CMasterTransfer(TCN75_MASTER_BASE, &Cfg, I2C_TRANSFER_POLLING);  
}

//*****************************************************************************
//
//! \brief Sets TCN75 as shutdown mode.
//!
//! \param ucMode None.
//!
//! \return None.
//
//*****************************************************************************
void 
TCN75Shutdown(void)
{
	unsigned char ucConfig;
    
    //
    // Enables shut down mode.
    //
	ucConfig = TCN75RegRead(TCN75_CONFIG);

	ucConfig = (ucConfig & 0xFE) | TCN75_SHUTDOWM_ON;

	TCN75RegWrite(TCN75_CONFIG, &ucConfig);
}

//*****************************************************************************
//
//! \brief Disable the sensor's shut dowm mode
//! 
//! \param none
//! 
//! \return none
//
//*****************************************************************************
void 
TCN75WakeUp(void)
{
    unsigned char ucConfig;
    //
    // Disables shut down mode.
    //
    ucConfig = TCN75RegRead(TCN75_CONFIG);

	ucConfig = (ucConfig & 0xFE) | TCN75_SHUTDOWN_OFF;

	TCN75RegWrite(TCN75_CONFIG, &ucConfig);
}

//*****************************************************************************
//
//! \brief Configuration of TCN75. 
//! 
//! \param ucCfg The value of TCN75 Config register.
//!
//! The \e ucCfg parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The operation mode bits can be selected from one of the following value:
//! \b TCN75_MODE_CMP , \b TCN75_MODE_INT.
//!
//! The polarity bit can selected form one of the following bit:
//! \b TCN75_POLARITY_LOW  , \b TCN75_POLARITY_HIGH 
//!
//! The Fault Queue bits can be selected form one of the following bits:
//! \b TCN75_FAULTQUE_1, \b TCN75_FAULTQUE_2, 
//! \b TCN75_FAULTQUE_4, \b TCN75_FAULTQUE_6.
//!
//! \return none.
//
//*****************************************************************************
void
TCN75Config(unsigned char ucCfg)
{
    unsigned char ucTemp;
    
    ucTemp = TCN75RegRead(TCN75_CONFIG);
      
    //
    // TCN75 mode set.
    //
    if((ucCfg & TCN75_MODE_INT) == 0)
    {
        ucTemp = ucTemp & (~TCN75_MODE_INT);    
    }
    else
    {
        ucTemp |= TCN75_MODE_INT;
    }
    
    //
    // OTI active level set
    //
    if((ucCfg & TCN75_POLARITY_HIGH) == 0)
    {
        ucTemp = ucTemp & (~TCN75_POLARITY_HIGH);
    }
    else
    {
        ucTemp |= TCN75_POLARITY_HIGH;
    }
    
    //
    // Fault queue set
    //
    ucTemp = ucTemp & (~TCN75_FAULTQUE_M);
    ucTemp |= (ucCfg & TCN75_FAULTQUE_M);
    
    TCN75RegWrite(TCN75_CONFIG, &ucTemp);
}


//*****************************************************************************
//
//! \brief Configures the GPIO pin and set callback function.
//!
//! \param xtIntCallback The callback function for event interrupt
//!
//! \return None.
//
//*****************************************************************************
void  
TCN75IntConfig(xtEventCallback xtIntCallback)
                
{
    unsigned char ucTemp;
    
    ucTemp = TCN75RegRead(TCN75_CONFIG);
    
	//
    // Config the Pin mode and Set callback funciton.
    //
   	xGPIOSPinTypeGPIOInput(TCN75_EVENTPIN);
    xGPIOPinIntCallbackInit(xGPIOSPinToPort(TCN75_EVENTPIN), 
	                          xGPIOSPinToPin(TCN75_EVENTPIN), xtIntCallback);

    if(ucTemp & TCN75_POLARITY_HIGH)
    {
        xGPIOSPinIntEnable(TCN75_EVENTPIN, GPIO_HIGH_LEVEL);   
    }
    else
    {
        xGPIOSPinIntEnable(TCN75_EVENTPIN, GPIO_LOW_LEVEL);
    } 
}

//*****************************************************************************
//
//!
//! \brief Sets THYST setpoint register in float degree celsius (°„C)
//!
//! \param fTemp Temperature value in degree celsius (-55°„C ~125 °„C)
//!
//! \return none
//
//*****************************************************************************
void 
TCN75LowLimitSet(float fTemp)
{   
    TCN75RegWrite(TCN75_THYS, &fTemp);
}

//*****************************************************************************
//
//!
//! \brief Gets the value of THYST setpoint register.
//!
//! \param None
//!
//! \return The temperature value in THYST register.
//
//*****************************************************************************
float 
TCN75LowLimitGet(void)
{
    long ulTemp;
	float fTemp;
       
    //
    // Read the THYS register
    //
    ulTemp = TCN75RegRead(TCN75_THYS);
	ulTemp = ulTemp>>7;
    
    //
    // Conveter the temperature register data to degree celsius (°„C)
    //
    fTemp = (float)(ulTemp * 0.5);   
    return fTemp;
}

//*****************************************************************************
//
//!
//! \brief Sets setpoint register in float degree celsius (°„C)
//!
//! \param fTemp Temperature value in degree celsius (-55°„C ~125 °„C)
//!
//! \return none
//
//*****************************************************************************
void 
TCN75UpLimitSet(float fTemp)
{      
    TCN75RegWrite(TCN75_TSET, &fTemp);
}

//*****************************************************************************
//
//!
//! \brief Gets the value of TSET register.
//!
//! \param None
//!
//! \return The temperature value in TSET register.
//
//*****************************************************************************
float 
TCN75UpLimitGet(void)
{
    long ulTemp;
	float fTemp;
       
    //
    // Read the TSET register
    //
    ulTemp = TCN75RegRead(TCN75_TSET);
	ulTemp = ulTemp>>7;
    
    //
    // Conveter the temperature register data to degree celsius (°„C)
    //
    fTemp = (float)(ulTemp * 0.5);   
    return fTemp;
}

//*****************************************************************************
//
//! \brief Gets current temperature.
//!
//! \param None.
//!
//! \return Returns  temperature.
//
//*****************************************************************************
float 
TCN75TempReadFDC(void)
{
    long ulTemp;
	float fTemp;
       
    //
    // Read the temperature register
    //
    ulTemp = TCN75RegRead(TCN75_TEMP);
	ulTemp = ulTemp>>7;
    
    //
    // Conveter the temperature register data to degree celsius (°„C)
    //
    fTemp = (float)(ulTemp * 0.5);   
    return fTemp;
}





