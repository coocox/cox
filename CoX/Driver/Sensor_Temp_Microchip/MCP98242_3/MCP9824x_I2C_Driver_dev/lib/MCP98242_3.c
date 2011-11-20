//*****************************************************************************
//
//! \file MCP98242_3.c
//! \brief source file of Driver for MCP98242_3
//! \version 1.0
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
#include "MCP98242_3.h" 
#include "xhw_types.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xi2c.h"
#include "xsysctl.h"
#include "xgpio.h"


//*****************************************************************************
//
//! \brief Initialize the MCP98242_3 Temperature Sensor, and select I2C port.
//!
//! \param *pDev specifies the device
//! \param ulRate set the I2C transfer rate
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3SENInit(MCP98242_3Dev *pDev, unsigned long ulRate)
{
    tI2CMasterTransferCfg Cfg;

    unsigned char ucTemp[3];
    unsigned char *SendBuf;
    unsigned long SendLength = 3;
    
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength = 2;

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
 
    //
    // I2C master transfer config
    //
    Cfg.ulSlave = pDev->SensorSlaAddr;   
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0; 

    ucTemp[0] = 0x1;
    ucTemp[1] = 0x00;
    ucTemp[2] = 0x00;
    SendBuf = ucTemp;
    Cfg.pvWBuf = SendBuf;
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
void  MCP98242_3SENDeInit(MCP98242_3Dev *pDev)
{
    MCP98242_3ModeSet(pDev, MCP98242_3_SEN_SHDN);
    MCP98242_3IntDisable(pDev);
    xSysCtlPeripheralDisable2(pDev->I2CBase);
}

//*****************************************************************************
//
//! \brief Set the Config register of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param usConfig specifies Config register of Temperature Sensor.
//!
//! This function is to set the Config register of Temperature Sensor.
//!
//! The \e usConfig parameter is the logical OR of these values: event output
//! select, T_CRIT lock, and T_UPPER,T_LOWER window lock. \b EVENT_SEL_ALL and
//! \b EVENT_SEL_CRIT select output event. \b CRIT_LOCK, \b CRIT_UNLOCK, 
//! \b WIN_LOCK and \b WIN_UNLOCK set the lock bits.
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3Config(MCP98242_3Dev *pDev, unsigned short usConfig)
{
    unsigned short usTemp;

    xASSERT((usConfig == EVENT_SEL_ALL) || (usConfig == EVENT_SEL_CRIT) || 
            (usConfig == CRIT_LOCK) || (usConfig == CRIT_UNLOCK) || 
            (usConfig == WIN_LOCK) || (usConfig == WIN_UNLOCK));

    MCP98242_3RegGet(pDev, &usTemp, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    usTemp &= ~LOCK_M;
    usTemp |= (LOCK_M & usConfig);    // Set the lock bits
    usTemp &= ~EVENT_SEL_CRIT;
    usTemp |= (EVENT_SEL_CRIT & usConfig);   // Select output event

    MCP98242_3RegSet(pDev, &usTemp, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Set the value of Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param vpvalue The data to write into the specified register
//! \param ustype  The register type
//! \param cTransType I2C transfer type, Poll or Interrupt 
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3RegSet(MCP98242_3Dev *pDev, void * vpValue, unsigned short usType, 
                            char cTransType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    char ucTemp[3];
    char *SendBuf;
    unsigned long SendLength;

    //
    //Sensor address, for example: 0x1C
    //
    unsigned long SlaveAddress = pDev->SensorSlaAddr;
    
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength ;

    //
    // Set UPPER,LOWER,CRITICAL,EMBIENT Temperature
    // in float type.
    //        
    if ((usType>0x11) && (usType<0x16))
    {
        temp = (int) ((*(float *)vpValue)*10000);
        temp = temp/625;
        ucTemp[0] = ((char) usType) & 0x0F;
        ucTemp[2] = (char) temp;
        ucTemp[1] = (char) (temp>>8);
        SendBuf = ucTemp;
    }
    //
    // Set Sensor registers, except for RESOLUTION register
    // because this register is 8 bit width.
    //
    else if(usType<8)
    {
        ucTemp[0] = (char)usType;
        ucTemp[2] = (char) (*(unsigned short *)vpValue);
        ucTemp[1] = (char) ((*(unsigned short *)vpValue)>>8);
        SendBuf = ucTemp;
    }
    //
    // Set the RESOLUTION register of Sensor
    //
    else
    {
        ucTemp[0] = (char)usType;
        ucTemp[1] =  (*(char*)vpValue);
        SendBuf = ucTemp;
    }

    //
    // The RESOLUTION REGISTER is one byte long, other sensor
    // registers  are two bytes long.
    //
    if(usType == 8)
    {
        SendLength = 2;
        ReceiveLength = 1;
    }
    else
    {
        SendLength = 3;
        ReceiveLength = 2;
    }

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);
}

//*****************************************************************************
//
//! \brief Get the value of Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param value The data of the specified register or address.
//! \param usType The register type or address
//! \param cTransType I2C transfer type, Poll or Interrupt 
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3RegGet(MCP98242_3Dev *pDev, void * vpValue, unsigned short usType, 
                            char cTransType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    unsigned char *uctemp;
    unsigned char *SendBuf;
    unsigned long SendLength = 1;

    //
    //Sensor address, for example: 0x1C
    //
    unsigned long SlaveAddress = pDev->SensorSlaAddr;
    
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength = 0;

    //
    // The RESOLUTION register is one byte long, the others are 
    // two bytes long.
    //
    if(usType<8 || (usType>0x11 && usType<0x16) || (usType>0x21 && usType<0x26))
    {
        ReceiveLength = 2;
        temp = (((int)usType) & 0x0F);
        SendBuf = (unsigned char *)&temp;
    }
    //
    // Resolution register of temp sensor
    //
    else   
    {
        ReceiveLength = 1;
        SendBuf = (unsigned char *)&usType; 
    }

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);

    //
    // Get the UPPER,LOWER,CRITICAL,EMBIENT Temperature
    // in float type.
    //
    if((usType>0x11) && (usType<0x16))
    {
        temp = ((ReceiveBuf[0]<<8) + ReceiveBuf[1]) & 0x01FFF;
        if((temp & 0x1000) == 0x1000)
            temp |= 0xFFFFF000;
        *(float*)vpValue = temp * 0.0625;
    }
    //
    // Get the UPPER,LOWER,CRITICAL,EMBIENT Temperature
    // in integer type.
    //
    else if((usType>0x21) && (usType<0x26))
    {
        temp = ((ReceiveBuf[0]<<8) + ReceiveBuf[1]) & 0x01FFF;
        if((temp & 0x1000) == 0x1000)
        {
            temp |= 0xFFFFF000;
            temp += 0x10;
        }
        *(short *)vpValue = (temp>>4);
    }
    //
    // Get the register of Sensor
    //
    else if(usType<8)
    {
        *(unsigned char*)vpValue = ReceiveBuf[1];
        uctemp = vpValue;
        *(++uctemp) = ReceiveBuf[0];
    }
    //
    // Get the RESOLUTION register of Sensor
    //
    else
    {
        *(unsigned char*)vpValue = ReceiveBuf[0];
    }
}

//*****************************************************************************
//
//! \brief Enable interrupt of Event output of MCP98242_3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3IntEnable(MCP98242_3Dev *pDev)
{
    short config;
    
    MCP98242_3RegGet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Enable Event output
    //
    config |= MCP98242_3_CONF_EN;
    MCP98242_3RegSet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Enable the interrupt of the Pin which connected with
    // the Event pin of the sensor
    //
    xIntEnable(pDev->EventIntVec);
    xIntMasterEnable();
}

//*****************************************************************************
//
//! \brief Configure the GPIO pin and set callback function.
//!
//! \param *pDev specifies the device
//! \param xtIntCallback The callback function for event interrupt.
//! \param ucTrigMode The trigger condition of interrupt of Event Output.
//!  it can be: \b  MCP98242_3_HIGH_LEVEL, assert with high level
//!             \b  MCP98242_3_LOW_LEVEL, assert with low level
//! \param ulEventMode Comparator mode or Interrupt mode, it can be:
//!        \b EVENT_COMP, Comparator mode
//!        \b EVENT_INT, Interrupt mode
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3IntConfig(MCP98242_3Dev *pDev, xtEventCallback xtIntCallback, 
                 unsigned long ulTrigMode, unsigned long ulEventMode)
{
    short config;

    xASSERT((ulTrigMode == MCP98242_3_HIGH_LEVEL) || 
            (ulTrigMode == MCP98242_3_LOW_LEVEL));
    xASSERT((ulEventMode == EVENT_COMP) || 
            (ulEventMode == EVENT_INT));

    MCP98242_3RegGet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);
    
    //
    // Config the trigger level and Event Output Mode
    //
    config = (config & 0xFFFD) | ulTrigMode;
    config = (config & 0xFFFE) | ulEventMode;    
    MCP98242_3RegSet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Config the Pin mode and Set callback funciton.
    //
    xGPIODirModeSet(pDev->EventPort, pDev->EventPin, GPIO_DIR_MODE_IN);
    xGPIOPinIntCallbackInit(pDev->EventPort, pDev->EventPin, xtIntCallback);

    if(ulTrigMode & MCP98242_3_HIGH_LEVEL == MCP98242_3_HIGH_LEVEL)
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
//! \brief Disable Event output of MCP98242_3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3IntDisable(MCP98242_3Dev *pDev)
{
    short config;
    
    MCP98242_3RegGet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    config  &= ~MCP98242_3_CONF_EN;

    //
    // Disable Event Output
    //
    MCP98242_3RegSet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Disable the interrupt
    //
    xIntDisable(pDev->EventIntVec);
    xIntMasterDisable();
}

//*****************************************************************************
//
//! \brief Clear Interrupt.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3IntClear(MCP98242_3Dev *pDev)
{
    short  senconfig;

    MCP98242_3ConfigGet(pDev, &senconfig);

    senconfig |= MCP98242_3_CONF_INTCLR;

    MCP98242_3RegSet(pDev, &senconfig, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Set the mode of MCP98242_3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param cMode Sensor mode to set, it can be:
//!            \b MCP98242_3_SEN_SHDN
//!            \b MCP98242_3_SEN_CONTI
//!
//! \return \b xtrue SUCCESS
//!         \b xfalse FAILURE
//
//*****************************************************************************
xtBoolean  MCP98242_3ModeSet(MCP98242_3Dev *pDev, char cMode)
{
    unsigned short config;
    
    xASSERT((cMode == MCP98242_3_SEN_SHDN) || (cMode == MCP98242_3_SEN_CONTI));

    MCP98242_3RegGet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Shut Down mode
    //
    if(cMode == MCP98242_3_SEN_SHDN)
    {
        //
        // If bit6 or bit7 is set, it can't set to be shutdown mode.
        //
        if(config & 0xC0)
            return xfalse;
        else
        {
            config |= MCP98242_3_CONF_SHDN;
            MCP98242_3RegSet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING); 
            return xtrue;      
        } 
    }  
    //
    // Continue mode
    //
    else if(cMode == MCP98242_3_SEN_CONTI)
    {
        config &= ~MCP98242_3_CONF_SHDN;
        MCP98242_3RegSet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING); 
        return xtrue;
    } 
    else
        return xfalse;        
}

//*****************************************************************************
//
//! \brief Get the mode of MCP98242_3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return \b MCP98242_3_SEN_SHDN   Shut down mode,
//!         \b MCP98242_3_SEN_CONTI  continuously mode.
//
//*****************************************************************************
char  MCP98242_3ModeGet(MCP98242_3Dev *pDev)
{
    unsigned short  config;

    MCP98242_3RegGet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    if(config & 0x100)
        return  MCP98242_3_SEN_SHDN;
    else
        return  MCP98242_3_SEN_CONTI;
}

//*****************************************************************************
//
//! \brief Get Event Output Condition.
//!
//! \return There are four conditions:
//!        \b  EVENT_COND_1, T_A >= T_LOWER OR T_A <= T_UPPER - T_HYST
//!        \b  EVENT_COND_2, T_A < T_LOWER - T_HYST
//!        \b  EVENT_COND_3, T_A > T_UPPER OR T_A < T_CRIT - T_HYST
//!        \b  EVENT_COND_4, T_A >= T_CRIT
//
//*****************************************************************************
char  MCP98242_3EvnCondGet(MCP98242_3Dev *pDev)
{
    short s;
    MCP98242_3RegGet(pDev, &s, MCP98242_3_TEMP, I2C_TRANSFER_POLLING);  
    return (s>>13);  
}

//*****************************************************************************
//
//! \brief Set the Resolution of MCP98242_3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param ucResol The Resolution of MCP98242_3 Temperature Sensor.
//!  It can be the below value:
//!         \b RESOLUTION_5, Resolution of 0.5¡æ
//!         \b RESOLUTION_25, Resolution of 0.25¡æ
//!         \b RESOLUTION_125, Resolution of 0.125¡æ
//!         \b RESOLUTION_0625, Resolution of 0.0625¡æ
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3ResSet(MCP98242_3Dev *pDev, unsigned char ucResol)
{
    //xASSERT((ucResol & 0xFC) == 0);
    xASSERT((ucResol == RESOLUTION_5) || (ucResol == RESOLUTION_25) ||
            (ucResol == RESOLUTION_125) || (ucResol == RESOLUTION_0625));

    MCP98242_3RegSet(pDev, &ucResol, MCP98242_3_RSL, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Get the Resolution of MCP98242_3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \return the Resolution of MCP98242_3 Temperature Sensor.
//!  The return value would be:
//!         \b 0, Resolution of 0.5¡æ
//!         \b 1, Resolution of 0.25¡æ
//!         \b 2, Resolution of 0.125¡æ
//!         \b 3, Resolution of 0.0625¡æ      
//
//*****************************************************************************
char  MCP98242_3ResGet(MCP98242_3Dev *pDev)
{
    short sResol;
    MCP98242_3CapGet(pDev, &sResol);
    return (char) ((sResol & 0x18)>>3);
}

//*****************************************************************************
//
//! \brief  Set the TUPPER and TLOWER Limit Hysteresis.
//!
//! \param *pDev specifies the device
//! \param cHyst The Limit Hysteresis to set.
//!  It can be the below vaule:
//!         \b HYSTERESIS_0, 0¡æ
//!         \b HYSTERESIS_1_5, 1.5¡æ
//!         \b HYSTERESIS_3, 3¡æ
//!         \b HYSTERESIS_6, 6¡æ
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3HystSet(MCP98242_3Dev *pDev, unsigned long ulHyst)
{
    short config;

    //xASSERT((ulHyst & 0xF9FF) == 0);
    xASSERT((ulHyst == HYSTERESIS_0) || (ulHyst == HYSTERESIS_1_5) ||
            (ulHyst == HYSTERESIS_3) || (ulHyst == HYSTERESIS_6));

    MCP98242_3RegGet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    config = (config & (~HYSTERESIS_M)) | ulHyst;

    MCP98242_3RegSet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Get the TUPPER and TLOWER Limit Hysteresis .
//!
//! \param *pDev specifies the device
//!
//! \return the Hysteresis of MCP98242_3 Temperature Sensor.
//!  The return value would be:
//!         \b HYSTERESIS_0, 0.5¡æ
//!         \b HYSTERESIS_1_5, 1.5¡æ
//!         \b HYSTERESIS_3, 3¡æ
//!         \b HYSTERESIS_6, 6¡æ
//
//*****************************************************************************
unsigned short MCP98242_3HystGet(MCP98242_3Dev *pDev)
{
    short config;

    MCP98242_3RegGet(pDev, &config, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING);

    return (config & HYSTERESIS_M);
}

//*****************************************************************************
//
//! \brief Get MCP98242_3 Manufacture ID, Device ID, and Revision.
//!
//! \param *pDev specifies the device
//! \param id  The Manufacture ID, Device ID, and Revision.
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3GetID(MCP98242_3Dev *pDev, MCP98242_3_ID *id)
{
    unsigned short *s;
       
    //
    // Get MANUFACTURER ID
    //
    MCP98242_3RegGet(pDev, id, MCP98242_3_ManuID, I2C_TRANSFER_POLLING);

    //
    // Get DEVICE ID AND REVISION
    //
    s = ((unsigned short *)id);
    s++;
    MCP98242_3RegGet(pDev, s, MCP98242_3_DevID_Rev, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
// EEPROM   funcitons
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Initialize the MCP98242_3 Temperature Sensor, and select I2C port.
//!
//! \param *pDev specifies the device
//! \param ulRate Specifies the I2C clock rate.
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3EEPROMInit(MCP98242_3Dev *pDev, unsigned long ulRate)
{
    //
    // Initialize I2C port
    //
    xSysCtlPeripheralEnable2(pDev->I2CBase);
    pDev->pinSet();
    xI2CMasterInit(pDev->I2CBase, ulRate);
}

//*****************************************************************************
//
//! \brief DeInitialize EEPROM.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242_3EEPROMDeInit(MCP98242_3Dev *pDev)
{
    xSysCtlPeripheralDisable2(pDev->I2CBase);    
}

//*****************************************************************************
//
//! \brief Write one byte to EEPROM Standard Array. 
//!
//! \param pDev pointer of the device
//! \param usAddr specifies address.
//! \param cpvalue pointer of value to be writen.
//! \param TransType specifies I2C transfer type.
//!
//! This function is to write one byte to EEPROM.
//!
//! The \e usAddr should be between 0x80 to 0xff, the standard array.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//! \b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
void  MCP98242_3ByteWrite(MCP98242_3Dev *pDev, unsigned short usAddr, 
            char *cpValue, char cTransType)
{
    tI2CMasterTransferCfg Cfg;
    char ucTemp[2];
    char *SendBuf;
    unsigned long SendLength;
    unsigned long SlaveAddress;
    
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength ;

    if(usAddr>=0x80 && usAddr<0x100)
    {
        //
        // EEPROM address, for example: 0x54
        //
        SlaveAddress = pDev->EEPROMSlaAddr;
    }
    else if((((short)usAddr)>>8) == 1)
    {
        //
        // SWP address, it's fixed.
        //
        SlaveAddress = 0x31;
    }
    else if((((short)usAddr)>>8) == 2)
    {
        //
        // CWP address, it's fixed.
        //
        SlaveAddress = 0x33;   
    }
    else if((((short)usAddr)>>8) == 3)
    {
        //
        // PWP address, for example: 0x37
        //
        SlaveAddress = pDev->PWPSlaAddr;
    }
      
    ucTemp[0] = usAddr;
    ucTemp[1] =  *cpValue;
    SendBuf = ucTemp;
    SendLength = 2;
    ReceiveLength = 0;

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);
}

//*****************************************************************************
//
//! \brief Read one byte from EEPROM Standard Array. 
//!
//! \param pDev pointer of the device
//! \param usAddr specifies address.
//! \param cpvalue pointer of the received value.
//! \param TransType specifies I2C transfer type.
//!
//! This function is to read one byte from EEPROM.
//!
//! The \e usAddr should be between 0x80 to 0xff, the standard array.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//! \b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
void  MCP98242_3ByteRead(MCP98242_3Dev *pDev, unsigned short usAddr, 
                char *cpValue,  char cTransType)
{
    tI2CMasterTransferCfg Cfg;
    unsigned long SendLength = 1;
    unsigned long SlaveAddress;
    
    unsigned char ReceiveBuf[1] = {0};
    unsigned char ReceiveLength = 1;

    unsigned char *SendBuf = (unsigned char *)&usAddr;

    if(usAddr>=0x80 && usAddr<0x100)
    {
        //
        // EEPROM address, for example: 0x54
        //
        SlaveAddress = pDev->EEPROMSlaAddr;
    }
    else if((((short)usAddr)>>8) == 1)
    {
        //
        // SWP address, it's fixed.
        //
        SlaveAddress = 0x31;
    }
    else if((((short)usAddr)>>8) == 2)
    {
        //
        // CWP address, it's fixed.
        //
        SlaveAddress = 0x33;   
    }
    else if((((short)usAddr)>>8) == 3)
    {
        //
        // PWP address, for example: 0x37
        //
        SlaveAddress = pDev->PWPSlaAddr;
    }

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);

    //
    // the value from EEPROM
    //
    *(unsigned char*)cpValue = ReceiveBuf[0];
}

//*****************************************************************************
//
//! \brief Write multi-byte of EEPORM.
//!
//! \param *pDev specifies the device
//! \param usAddr The beginning address to read from
//! \param cpValue The data you read
//! \param cTransType I2C transfer type, Poll or Interrupt 
//! \param ucNum The number of bytes to write
//!
//! \return \b xtrue SUCCESS
//!         \b xfalse FAILURE
//
//*****************************************************************************
xtBoolean  MCP98242_3MutiByteWrite(MCP98242_3Dev *pDev, unsigned short usAddr, 
                char *cpValue, char cTransType, unsigned char ucNum)
{
    if((usAddr+ucNum) >= 256)
        return xfalse;

    while(ucNum--)
    {
        MCP98242_3ByteWrite(pDev, usAddr++, cpValue++, cTransType);
        xSysCtlDelay(10000);
    }

    return xtrue;
}

//*****************************************************************************
//
//! \brief Write one page to EEPROM Standard Array. 
//!
//! \param pDev specifies the device
//! \param usAddr specifies beginning address of page.
//! \param cValue specifies value.
//! \param TransType specifies I2C transfer type.
//!
//! This function is to write one page to EEPROM Standard Array.
//!
//! The \e usAddr should be between 0x80 to 0xff, the standard array. And the low
//! 4 bits should be 0.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or \b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
void MCP98242_3PageWrite(MCP98242_3Dev *pDev, unsigned short usAddr, char cValue[], 
                    char cTransType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    char ucTemp[17];
    char *SendBuf;
    unsigned long SendLength = 17;
    
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength = 0;

    //
    // EEPROM address, for example: 0x54
    //
    unsigned long SlaveAddress = pDev->EEPROMSlaAddr;

    xASSERT((sizeof(cValue) == 16) &&
            ((usAddr & 0x0F) == 0x00) &&
            (usAddr < 0xFF));

    for(temp=0; temp<16; temp++)
    {
        ucTemp[temp+1] = cValue[temp];
    }
    ucTemp[0] = usAddr;
    SendBuf = ucTemp;

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);
}

//*****************************************************************************
//
//! \brief Read from EEPROM Standard Array. 
//!
//! \param pDev pointer of the device
//! \param cAddr specifies address.
//! \param cpvalue pointer of the received value.
//! \param cTransType specifies I2C transfer type.
//! \param ucNum the number of bytes to be received.
//!
//! When usAddr and ucNum equal 0, byte of current address will be read. 
//! Otherwise, bytes with number of "ucnum" from address "usAddr" will be read.
//! 
//! The \e addr should be between 0x80 to 0xff, the standard array.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//! \b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
void MCP98242_3MemRead(MCP98242_3Dev *pDev, char cAddr, char *cpValue, 
                    char cTransType, unsigned char ucNum)
{
    tI2CMasterTransferCfg Cfg;
    int i;
    char *cp;
    char *SendBuf;
    unsigned long SendLength = 0;
    
    unsigned char ReceiveBuf[16] = {0};
    unsigned char ReceiveLength = 0;

    //
    // EEPROM address, for example: 0x54
    //
    unsigned long SlaveAddress = pDev->EEPROMSlaAddr;

    xASSERT(ucNum < 17);

    //
    // Current Address Read
    //
    if(cAddr == 0)
    {
        ReceiveLength = 1;    
    }
    //
    // Sequential Read, 16 bytes at most.
    //
    else
    {
        SendBuf = &cAddr;
        SendLength = 1;
        ReceiveLength = ucNum;
    }

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(cTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);

    //
    // Current Address Read
    //
    if(cAddr == 0)
    {
        *(unsigned char*)cpValue = ReceiveBuf[0];    
    }
    //
    // Sequential Read, 16 bytes at most.
    //
    else
    {
        cp = cpValue;
        for(i=0; i<ucNum; i++, cp++)
        {
            *cp = ReceiveBuf[i];    
        }
    }
}
