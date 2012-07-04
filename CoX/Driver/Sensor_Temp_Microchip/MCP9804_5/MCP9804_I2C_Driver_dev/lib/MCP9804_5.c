//*****************************************************************************
//
//! \file MCP9804_5.c
//! \brief source file of Driver for MCP9804/5
//! \version 2.1.2.0
//! \date 20/11/2011
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
#include "MCP9804_5.h" 
#include "xhw_types.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xi2c.h"
#include "xsysctl.h"
#include "xgpio.h"


//*****************************************************************************
//
//! \brief Initialize the MCP9804/5 Temperature Sensor, and select I2C port.
//!
//! \param *pDev specifies the device
//! \param ulRate set the I2C transfer rate
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804Init(MCP9804Dev *pDev, unsigned long ulRate)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char ucTemp[3];   

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
    Cfg.ulWLen = 3;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0; 

    ucTemp[0] = 0x1;
    ucTemp[1] = 0x00;
    ucTemp[2] = 0x00;
    Cfg.pvWBuf = ucTemp;

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Get Capability of MCP9804/5 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return the content of Capability Register of MCP9804/5.
//
//*****************************************************************************
unsigned short MCP9804CapGet(MCP9804Dev *pDev)
{
    unsigned short usCap;
    MCP9804RegGet(pDev, &usCap, MCP9804_Cap, I2C_TRANSFER_POLLING);
    return usCap;
}
//*****************************************************************************
//
//! \brief Set the Config register of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param usConfig specifies Config register of Temperature Sensor.
//! \param ulResol The Resolution of MCP9804 Temperature Sensor.
//!  It can be the below value:
//!         \b MCP_RESOLUTION_5, Resolution of 0.5¡æ
//!         \b MCP_RESOLUTION_25, Resolution of 0.25¡æ
//!         \b MCP_RESOLUTION_125, Resolution of 0.125¡æ
//!         \b MCP_RESOLUTION_0625, Resolution of 0.0625¡æ
//! \param ulHyst The Limit Hysteresis to set.
//!  It can be the below vaule:
//!         \b MCP_HYSTERESIS_0, 0¡æ
//!         \b MCP_HYSTERESIS_1_5, 1.5¡æ
//!         \b MCP_HYSTERESIS_3, 3¡æ
//!         \b MCP_HYSTERESIS_6, 6¡æ
//!
//! The \e usConfig parameter is the logical OR of these values: event output
//! select, T_CRIT lock, and MCP_UPPER,MCP_LOWER window lock. \b MCP_EVENT_SEL_ALL and
//! \b MCP_EVENT_SEL_CRIT select output event. \b MCP_CRIT_LOCK, \b MCP_CRIT_UNLOCK, 
//! \b MCP_WIN_LOCK and \b MCP_WIN_UNLOCK set the lock bits.
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804Config(MCP9804Dev *pDev, unsigned short usConfig, 
                     unsigned long ulResol, unsigned long ulHyst)
{
    unsigned short config;

    xASSERT((usConfig == MCP_EVENT_SEL_ALL) || (usConfig == MCP_EVENT_SEL_CRIT) || 
            (usConfig == MCP_CRIT_LOCK) || (usConfig == MCP_CRIT_UNLOCK) || 
            (usConfig == MCP_WIN_LOCK) || (usConfig == MCP_WIN_UNLOCK));

    xASSERT((ucResol == MCP_RESOLUTION_5) || (ucResol == MCP_RESOLUTION_25) ||
            (ucResol == MCP_RESOLUTION_125) || (ucResol == MCP_RESOLUTION_0625));

    xASSERT((ulHyst == MCP_HYSTERESIS_0) || (ulHyst == MCP_HYSTERESIS_1_5) ||
            (ulHyst == MCP_HYSTERESIS_3) || (ulHyst == MCP_HYSTERESIS_6));

    MCP9804RegGet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

    config &= ~MCP_LOCK_M;
    config |= (MCP_LOCK_M & usConfig);           // Set the lock bits
    config &= ~MCP_EVENT_SEL_CRIT;
    config |= (MCP_EVENT_SEL_CRIT & usConfig);   // Select output event
    config = (config & (~MCP_HYSTERESIS_M)) | ulHyst;

    MCP9804RegSet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);    

    MCP9804RegSet(pDev, &ulResol, MCP9804_RSL, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Set the value of Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param *vpvalue The data to write into the specified register
//! \param ucType  The register type
//! \param ucTransType I2C transfer type, Poll or Interrupt 
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804RegSet(MCP9804Dev *pDev, void * vpValue, unsigned char ucType, 
                     unsigned char ucTransType)
{
    tI2CMasterTransferCfg Cfg;
    char ucTemp[3];
    char *SendBuf;
    unsigned long SendLength;

    //
    //Sensor address, for example: 0x1C
    //
    unsigned long SlaveAddress = pDev->SensorSlaAddr;

    xASSERT(ucType <= 8);

    //
    // Set Sensor registers, except for RESOLUTION register
    // because this register is 8 bit width.
    //
    if(ucType<8)
    {
        ucTemp[0] = ucType;
        ucTemp[2] = (char) (*(unsigned short *)vpValue);
        ucTemp[1] = (char) ((*(unsigned short *)vpValue)>>8);
        SendBuf = ucTemp;
        SendLength = 3;
    }
    //
    // Set the RESOLUTION register of Sensor
    //
    else
    {
        ucTemp[0] = 0x08;
        ucTemp[1] =  (*(char*)vpValue);
        SendBuf = ucTemp;
        SendLength = 2;
    }

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0;  

    if(ucTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);
}

//*****************************************************************************
//
//! \brief Get the value of Temperature Sensor.
//!
//! \param *pDev specifies the device
//! \param *vpValue The data of the specified register or address.
//! \param ucType The register type or address
//! \param ucTransType I2C transfer type, Poll or Interrupt 
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804RegGet(MCP9804Dev *pDev, void * vpValue, unsigned char ucType, 
                     unsigned char ucTransType)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char *uctemp;
    
    unsigned char ReceiveBuf[2] = {0};
    unsigned char ReceiveLength = 0;

    xASSERT(ucType <= 8);

    //
    // The RESOLUTION register is one byte long, the others are 
    // two bytes long.
    //
    if(ucType<8)
    {
        ReceiveLength = 2;        
    }
    //
    // Resolution register of temp sensor
    //
    else   
    {
        ReceiveLength = 1;
    }

    Cfg.ulSlave = pDev->SensorSlaAddr;
    Cfg.pvWBuf = &ucType;
    Cfg.ulWLen = 1;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    if(ucTransType == ((char)I2C_TRANSFER_POLLING))
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
    else
        xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_INTERRUPT);

    //
    // Get the register of Sensor
    //
    if(ucType<8)
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
//! \brief Enable interrupt of Event output of MCP9804/5 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804IntEnable(MCP9804Dev *pDev)
{
    unsigned short config;
    
    MCP9804RegGet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Enable Event output
    //
    config |= MCP9804_CONF_EN;
    MCP9804RegSet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

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
//!  it can be: \b  MCP9804_HIGH_LEVEL, assert with high level
//!             \b  MCP9804_LOW_LEVEL, assert with low level
//! \param ulEventMode Comparator mode or Interrupt mode, it can be:
//!        \b MCP_EVENT_COMP, Comparator mode
//!        \b MCP_EVENT_INT, Interrupt mode
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804IntConfig(MCP9804Dev *pDev, xtEventCallback xtIntCallback, 
                 unsigned long ulTrigMode, unsigned long ulEventMode)
{
    unsigned short config;

    xASSERT((ulTrigMode == MCP9804_HIGH_LEVEL) || 
            (ulTrigMode == MCP9804_LOW_LEVEL));
    xASSERT((ulEventMode == MCP_EVENT_COMP) || 
            (ulEventMode == MCP_EVENT_INT));

    MCP9804RegGet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);
    
    //
    // Config the trigger level and Event Output Mode
    //
    config = (config & 0xFFFD) | ulTrigMode;
    config = (config & 0xFFFE) | ulEventMode;    
    MCP9804RegSet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Config the Pin mode and Set callback funciton.
    //
    xGPIODirModeSet(pDev->EventPort, pDev->EventPin, GPIO_DIR_MODE_IN);
    xGPIOPinIntCallbackInit(pDev->EventPort, pDev->EventPin, xtIntCallback);

    if(ulTrigMode & MCP9804_HIGH_LEVEL == MCP9804_HIGH_LEVEL)
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
//! \brief Disable Event output of MCP9804 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804IntDisable(MCP9804Dev *pDev)
{
    unsigned short config;
    
    MCP9804RegGet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

    config  &= ~MCP9804_CONF_EN;

    //
    // Disable Event Output
    //
    MCP9804RegSet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

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
void  MCP9804IntClear(MCP9804Dev *pDev)
{
    unsigned short  senconfig;

    MCP9804RegGet(pDev, &senconfig, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

    senconfig |= MCP9804_CONF_INTCLR;

    MCP9804RegSet(pDev, &senconfig, MCP9804_CONFIG, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Get into shut down mode.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
xtBoolean  MCP9804SHDNEnable(MCP9804Dev *pDev)
{
    unsigned short config;

    MCP9804RegGet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);

    //
    // If bit6 or bit7 is set, it can't set to be shutdown mode.
    //
    if(config & 0xC0)
        return xfalse;
    else
    {
        config |= MCP9804_CONF_SHDN;
        MCP9804RegSet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING); 
        return xtrue;      
    } 
}

//*****************************************************************************
//
//! \brief Get out of shut down mode.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804SHDNDisable(MCP9804Dev *pDev)
{
    unsigned short config;

    MCP9804RegGet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);
    config &= ~MCP9804_CONF_SHDN;
    MCP9804RegSet(pDev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING); 
}

//*****************************************************************************
//
//! \brief Get Event Output Condition.
//!
//! \return There are four conditions:
//!        \b  MCP_EVENT_COND_1, T_A >= MCP_LOWER OR T_A <= MCP_UPPER - T_HYST
//!        \b  MCP_EVENT_COND_2, T_A < MCP_LOWER - T_HYST
//!        \b  MCP_EVENT_COND_3, T_A > MCP_UPPER OR T_A < T_CRIT - T_HYST
//!        \b  MCP_EVENT_COND_4, T_A >= T_CRIT
//
//*****************************************************************************
char  MCP9804EvnCondGet(MCP9804Dev *pDev)
{
    unsigned short s;
    MCP9804RegGet(pDev, &s, MCP9804_TEMP, I2C_TRANSFER_POLLING);  
    return (s>>13);  
}

//*****************************************************************************
//
//! \brief Set the limit temperature of Temperature Sensor. 
//!
//! \param *pDev specifies the device
//! \param *vpValue specifies limit temperature.
//! \param ucLimitType specifies limit type.
//!  it can be: \b  MCP_UPPER
//!             \b  MCP_LOWER
//!             \b  MCP_CRITICAL
//!
//! The \e *vpValue can be type of short or float. 
//!
//! \return None.
//
//***************************************************************************** 
void  MCP9804LimitSet(MCP9804Dev *pDev, void *vpValue, 
                       unsigned char ucLimitType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    unsigned char ucTemp[3];  

    xASSERT((ucLimitType == MCP_UPPER) ||
            (ucLimitType == MCP_LOWER) ||
            (ucLimitType == MCP_CRITICAL));

    //
    // Set UPPER,LOWER,CRITICAL Temperature in Float type.
    //        
    temp = (int) ((*(float *)vpValue)*10000);
    temp = temp/625;
    ucTemp[0] = ucLimitType;
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
//! \brief Get the ambient temperature of Temperature Sensor. 
//!
//! \param *pDev specifies the device
//! \param *vpValue the ambient temperature.
//! \param ucDataType the temperature data type, \b MCP_FLOAT or \b MCP_INT.
//!
//! \return None.
//
//***************************************************************************** 
void  MCP9804TempGet(MCP9804Dev *pDev, void *vpValue, 
                      unsigned char ucDataType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    char cTempReg = 0x05;
    unsigned char ReceiveBuf[2] = {0};

    xASSERT((ucDataType == MCP_FLOAT) || (ucDataType == MCP_INT));
   
    Cfg.ulSlave = pDev->SensorSlaAddr;
    Cfg.pvWBuf = &cTempReg;
    Cfg.ulWLen = 1;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = 2;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);

    //
    // Get AMBIENT Temperature in float type.
    //
    if(ucDataType == MCP_FLOAT)
    {
        temp = ((ReceiveBuf[0]<<8) + ReceiveBuf[1]) & 0x01FFF;
        if((temp & 0x1000) == 0x1000)
            temp |= 0xFFFFF000;
        *(float*)vpValue = temp * 0.0625;
    }
    //
    // Get AMBIENT Temperature in integer type.
    //
    else
    {
        temp = ((ReceiveBuf[0]<<8) + ReceiveBuf[1]) & 0x01FFF;
        if((temp & 0x1000) == 0x1000)
        {
            temp |= 0xFFFFF000;
            temp += 0x10;
        }
        *(short *)vpValue = (temp>>4);
    }
}

//*****************************************************************************
//
//! \brief Get MCP9804 Manufacture ID, Device ID, and Revision.
//!
//! \param *pDev specifies the device
//! \param id  The Manufacture ID, Device ID, and Revision.
//!
//! \return None.
//
//*****************************************************************************
void  MCP9804GetID(MCP9804Dev *pDev, MCP9804_ID *id)
{
    unsigned short *s;
       
    //
    // Get MANUFACTURER ID
    //
    MCP9804RegGet(pDev, id, MCP9804_ManuID, I2C_TRANSFER_POLLING);

    //
    // Get DEVICE ID AND REVISION
    //
    s = ((unsigned short *)id);
    s++;
    MCP9804RegGet(pDev, s, MCP9804_DevID_Rev, I2C_TRANSFER_POLLING);
}


