//*****************************************************************************
//
//! \file MCP9800_3.c
//! \brief source file of Driver for MCP9800_3
//! \version 2.1.1.0
//! \date 8/25/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
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
#include "xhw_ints.h"
#include "xdebug.h"
#include "xcore.h"
#include "xi2c.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "MCP9800_3.h"


//*****************************************************************************
//
//! \brief Initialize the MCP9800 Temperature Sensor, and select I2C port.
//!
//! \param *pDev specifies the device
//! \param ulRate set the I2C transfer rate.The maximum rate is 400 kHz.
//!
//! \return None.
//
//*****************************************************************************
void  MCP980xInit(MCP9800Dev *pDev, unsigned long ulRate)
{
    unsigned char ucConfig;

    tI2CMasterTransferCfg Cfg;

    unsigned char SendBuf[2];
    unsigned long SendLength = 2;
    
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength = 1;

    //
    // Enable I2C, GPIO clock
    // Set pins to I2C funciton
    //
    pDev->pinSet();

    //
    // Enable I2C peripheral Clock
    //
    xSysCtlPeripheralEnable2(pDev->I2CBase);

    xI2CMasterInit(pDev->I2CBase, ulRate);

    ucConfig = 0x00;

    SendBuf[0] = MCP9800_CONFIG;
    SendBuf[1] = ucConfig;
    
    //
    // I2C master transfer config
    //
    Cfg.ulSlave = pDev->SensorSlaAddr;  
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0; 

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);

}

//*****************************************************************************
//
//! \brief DeInialize the Temperatrue Sensor.
//!
//! \param *pDev specifies the device
//!
//! Set the Sensor as shutdown mode, disable interrupt and I2C.
//!
//! \return None.
//
//*****************************************************************************
void  MCP980xDeInit(MCP9800Dev *pDev)
{
    MCP980xModeSet(pDev, MCP9800_SHDN);
    xSysCtlPeripheralDisable2(pDev->I2CBase);
}

//*****************************************************************************
//
//! \brief Set the value of Temperature Sensor or EEPROM.
//!
//! \param *pDev specifies the device
//! \param vpvalue The data to write into the specified register or address.
//! \param ustype  The register type or address
//! \param cTransType I2C transfer type, Poll or Interrupt 
//!
//! \return None.
//
//*****************************************************************************
void  MCP980xRegSet(MCP9800Dev *pDev, void * vpValue, unsigned short usType, 
                            char cTransType)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char ucTemp[3];
    unsigned long SendLength;
    unsigned long SlaveAddress = pDev->SensorSlaAddr;   

    xASSERT((usType >= 0x00) && (usType < 0x04));
    
    //
    // Set the config register.
    //
    if(usType == 0x01)
    {
        ucTemp[0] = 0x01;
        ucTemp[1] =  (*(unsigned char*)vpValue);  
        SendLength = 2;  
    }
    //
    // Set UPPER,HYSTERESIS Temperature register.
    //        
    else
    {
        ucTemp[0] = (unsigned char) usType;
        ucTemp[2] = (char) (*(unsigned short *)vpValue);
        ucTemp[1] = (char) ((*(unsigned short *)vpValue)>>8);
        SendLength = 3;  
    }

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = ucTemp;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);
}

//*****************************************************************************
//
//! \brief Get the value of Temperature Sensor or EEPROM.
//!
//! \param *pDev specifies the device
//! \param value The data of the specified register or address.
//! \param usType The register type or address
//! \param cTransType I2C transfer type, Poll or Interrupt 
//!
//! \return None.
//
//*****************************************************************************
void  MCP980xRegGet(MCP9800Dev *pDev, void * vpValue, unsigned short usType, 
                            char cTransType)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char *uctemp;
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength = 0;

    xASSERT((usType >= 0x00) && (usType < 0x04));

    //
    // The config register is one byte long.
    //
    if(usType == 0x01)
    {        
        ReceiveLength = 1;
    }
    //
    // The UPPER,HYSTERESIS Temperature register is two bytes.
    //        
    else if ((usType & 0x0F) < 0x04)
    {
        ReceiveLength = 2;
    }

    Cfg.ulSlave = pDev->SensorSlaAddr;
    Cfg.pvWBuf = (unsigned char *)&usType;
    Cfg.ulWLen = 1;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);

    //
    // Get the config register.
    //
    if(usType == 0x01)
    {
        *(unsigned char*)vpValue = ReceiveBuf[0];
    }
    //
    // Get the UPPER,HYSTERESIS Temperature register.
    //
    else
    {
        *(unsigned char*)vpValue = ReceiveBuf[1];
        uctemp = vpValue;
        *(++uctemp) = ReceiveBuf[0];
    }
}

//*****************************************************************************
//
//! \brief Configure MCP9800/3.
//!
//! \param *pDev specifies the device
//! \param ucConfig configuration of MCP9800/3
//!  it can be logic OR of: 
//!       - \b MCP9800_RESOL_5, Resolution of 0.5¡æ
//!       - \b MCP9800_RESOL_25, Resolution of 0.25¡æ
//!       - \b MCP9800_RESOL_125, Resolution of 0.125¡æ
//!       - \b MCP9800_RESOL_0625, Resolution of 0.0625¡æ
//!       - \b MCP9800_FAULTQUE_1, set fault queue to be 1
//!       - \b MCP9800_FAULTQUE_2, set fault queue to be 2
//!       - \b MCP9800_FAULTQUE_4, set fault queue to be 4
//!       - \b MCP9800_FAULTQUE_6, set fault queue to be 6
//!       .
//!
//! \return None.
//
//*****************************************************************************
void  MCP980xConfig(MCP9800Dev *pDev, unsigned char ucConfig)
{
    unsigned char ucTemp;

    xASSERT(((ucConfig & (~MCP9800_RESOL_M)) &
             (~MCP9800_FAULTQUE_M)) == 0);

    MCP980xRegGet(pDev, &ucTemp, MCP9800_CONFIG, 0);
    
    ucTemp = (ucTemp & (~(MCP9800_RESOL_M | MCP9800_FAULTQUE_M))) | 
             ucConfig; 
    
    MCP980xRegSet(pDev, &ucTemp, MCP9800_CONFIG, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Configure the GPIO pin and set callback function.
//!
//! \param *pDev specifies the device
//! \param xtIntCallback The callback function for event interrupt.
//! \param ucTrigMode The trigger condition of interrupt of Event Output.
//!  it can be: 
//!       - \b ALERTPOL_HIGH, assert with high level
//!       - \b ALERTPOL_LOW, assert with low level
//! \param ulEventMode Comparator mode or Interrupt mode, it can be:
//!        - \b EVENT_COMP, Comparator mode
//!        - \b EVENT_INT, Interrupt mode
//!
//! \return None.
//
//*****************************************************************************
void  MCP980xIntConfig(MCP9800Dev *pDev, xtEventCallback xtIntCallback, 
                 unsigned long ulTrigMode, unsigned long ulEventMode)
{
    unsigned char ucConfig;
    
    xASSERT((ulTrigMode == ALERTPOL_HIGH) || 
            (ulTrigMode == ALERTPOL_LOW));
    xASSERT((ulEventMode == EVENT_COMP) || 
            (ulEventMode == EVENT_INT));

    MCP980xRegGet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING);
    
    //
    // Config the trigger level and Event Output Mode
    //
    ucConfig = (ucConfig & 0xFB) | ulTrigMode;
    ucConfig = (ucConfig & 0xFD) | (ulEventMode<<1);    
    MCP980xRegSet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Config the Pin mode and Set callback funciton.
    //
    xGPIODirModeSet(pDev->EventPort, pDev->EventPin, GPIO_DIR_MODE_IN);
    xGPIOPinIntCallbackInit(pDev->EventPort, pDev->EventPin, xtIntCallback);

    if(ulTrigMode & MCP9800_ALERTPOL_HIGH == MCP9800_ALERTPOL_HIGH)
    {
        xGPIOPinIntEnable(pDev->EventPort, pDev->EventPin, GPIO_HIGH_LEVEL);   
    }
    else
    {
        xGPIOPinIntEnable(pDev->EventPort, pDev->EventPin, GPIO_LOW_LEVEL);
    } 
}

//*****************************************************************************
//
//! \brief Clear Interrupt, the interrupt is cleared by read any register.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP980xIntClear(MCP9800Dev *pDev)
{
    unsigned char ucTemp;

    //
    // The interrupt is cleared by read any register.
    //
    MCP980xTempGet(pDev, &ucTemp, MCP_INT);  
}

//*****************************************************************************
//
//! \brief Set the mode of MCP9800 Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param cMode Sensor mode to set, it can be:
//!            - \b MCP9800_SHDN, shut down mode
//!            - \b MCP9800_ONESHOT, one shot mode
//!            - \b MCP9800_CONTI, continuous mode
//!
//! \return   xtrue    SUCCESS
//!           xfalse   FAILURE
//
//*****************************************************************************
xtBoolean  MCP980xModeSet(MCP9800Dev *pDev, char cMode)
{
    unsigned char ucConfig;
    
    xASSERT((cMode == MCP9800_SHDN) || 
            (cMode == MCP9800_ONESHOT) || 
            (cMode == MCP9800_CONTI));

    MCP980xRegGet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Shut Down mode, one shot (bit7):0, shut down (bit0):1.
    //
    if(cMode == MCP9800_SHDN)
    {
        ucConfig = (ucConfig & 0x7F) | 0x01;
        MCP980xRegSet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING); 
        return xtrue;       
    }  
    //
    // Continue mode, shut down (bit0):0.
    //
    else if(cMode == MCP9800_CONTI)
    {
        ucConfig = ucConfig & 0xFE;
        MCP980xRegSet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING); 
        return xtrue;
    } 
    //
    // One-Shot mode, one shot (bit7):1, shut down (bit0):1. 
    //
    else if(cMode == MCP9800_ONESHOT)
    {
        //
        // Set shut down mode first.
        //
        ucConfig = (ucConfig & 0x7F) | 0x01;                                                
        MCP980xRegSet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING); 

        //
        // one shot mode.
        //
        ucConfig = ucConfig | 0x81;                                                
        MCP980xRegSet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING); 
        return xtrue;
    }
    else
        return xfalse;
            
}

//*****************************************************************************
//
//! \brief Get the mode of MCP9800 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return The below value:
//!            - \b MCP9800_SHDN, shut down mode
//!            - \b MCP9800_ONESHOT, one shot mode
//!            - \b MCP9800_CONTI, continuous mode
//
//*****************************************************************************
char  MCP980xModeGet(MCP9800Dev *pDev)
{
    unsigned char ucConfig;
    
    MCP980xRegGet(pDev, &ucConfig, MCP9800_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Shut Down mode, one shot (bit7):0, shut down (bit0):1.
    //
    if((ucConfig & 0x81) == 0x01)
    {
        return MCP9800_SHDN;       
    }  
    //
    // Continue mode, shut down (bit0):0.
    //
    else if((ucConfig & 0x01) == 0x00)
    {
        return MCP9800_CONTI;
    } 
    //
    // One-Shot mode, one shot (bit7):1, shut down (bit0):1. 
    //
    else if((ucConfig & 0x81) == 0x81)
    {
        return MCP9800_ONESHOT;
    }
    return 3;
}

//*****************************************************************************
//
//! \brief Set the Limit Temperature of MCP9800 Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param *vpValue the temperature to be set
//! \param ulType specifies the limit register
//!  It can be:
//!            - \b MCP9800_LIMIT, Limit-set register
//!            - \b MCP9800_HYSTERESIS, Hysteresis register
//!            .
//! \return None
//
//*****************************************************************************
void  MCP980xLimitSet(MCP9800Dev *pDev, void *vpValue, 
                               unsigned long ulType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    char ucTemp[3];

    xASSERT((ulType == MCP9800_LIMIT) ||
            (ulType == MCP9800_HYST));
    
    //
    // Set UPPER,HYSTERESIS Temperature in float type.
    //        
    temp = (int) ((*(float *)vpValue)*2);
    temp = temp<<7;
    ucTemp[0] = (char) ulType;
    ucTemp[2] = (char) temp;
    ucTemp[1] = (char) (temp>>8);

    Cfg.ulSlave = pDev->SensorSlaAddr;
    Cfg.pvWBuf = ucTemp;
    Cfg.ulWLen = 3;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Get the ambient Temperature in float or integer datatype.
//!
//! \param *pDev specifies the device
//! \param *vpValue the temperature to be read
//! \param ulDataType specifies the data type
//!  It can be:
//!            - \b MCP_FLOAT, Limit-set register
//!            - \b MCP_INT, Hysteresis register
//!            .
//! \return None
//
//*****************************************************************************
void  MCP980xTempGet(MCP9800Dev *pDev, void *vpValue, 
                              unsigned long ulDataType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    unsigned char SendBuf = 0x00;
    unsigned char ReceiveBuf[2] = {0};

    xASSERT((ulDataType == MCP_FLOAT) ||
            (ulDataType == MCP_INT));

    Cfg.ulSlave = pDev->SensorSlaAddr;
    Cfg.pvWBuf = &SendBuf;
    Cfg.ulWLen = 1;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = 2;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);

    //
    // Get the Temperature in float type.
    //
    if(ulDataType == MCP_FLOAT)
    {
        temp = (ReceiveBuf[0]<<8) + ReceiveBuf[1];
        if((temp & 0x8000) == 0x8000)
            temp |= 0xFFFF0000;
        temp = temp>>4;
        *(float*)vpValue = temp * 0.0625;
    }
    //
    // Get the Temperature in integer type.
    //
    else
    {
        *(char *)vpValue = ReceiveBuf[0];
    }
}
