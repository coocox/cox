//*****************************************************************************
//
//! \file MCP98242_3.c
//! \brief source file of Driver for MCP98242/3
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
//! \brief Initialize the MCP98242/3 Temperature Sensor, and select I2C port.
//!
//! \param *pDev specifies the device
//! \param ulRate set the I2C transfer rate
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242SensorInit(MCP98242Dev *pDev, unsigned long ulRate)
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
//! \brief Get Capability of MCP98242/3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return the content of Capability Register of MCP98242/3.
//
//*****************************************************************************
unsigned short MCP98242CapGet(MCP98242Dev *pDev)
{
    unsigned short usCap;
    MCP98242RegGet(pDev, &usCap, MCP98242_Cap, I2C_TRANSFER_POLLING);
    return usCap;
}
//*****************************************************************************
//
//! \brief Set the Config register of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param usConfig specifies Config register of Temperature Sensor.
//! \param ulResol The Resolution of MCP98242 Temperature Sensor.
//!  It can be the below value:
//!         \b RESOLUTION_5, Resolution of 0.5¡æ
//!         \b RESOLUTION_25, Resolution of 0.25¡æ
//!         \b RESOLUTION_125, Resolution of 0.125¡æ
//!         \b RESOLUTION_0625, Resolution of 0.0625¡æ
//! \param ulHyst The Limit Hysteresis to set.
//!  It can be the below vaule:
//!         \b HYSTERESIS_0, 0¡æ
//!         \b HYSTERESIS_1_5, 1.5¡æ
//!         \b HYSTERESIS_3, 3¡æ
//!         \b HYSTERESIS_6, 6¡æ
//!
//! The \e usConfig parameter is the logical OR of these values: event output
//! select, T_CRIT lock, and T_UPPER,T_LOWER window lock. \b EVENT_SEL_ALL and
//! \b EVENT_SEL_CRIT select output event. \b CRIT_LOCK, \b CRIT_UNLOCK, 
//! \b WIN_LOCK and \b WIN_UNLOCK set the lock bits.
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242Config(MCP98242Dev *pDev, unsigned short usConfig, 
                     unsigned long ulResol, unsigned long ulHyst)
{
    unsigned short config;

    xASSERT((usConfig == EVENT_SEL_ALL) || (usConfig == EVENT_SEL_CRIT) || 
            (usConfig == CRIT_LOCK) || (usConfig == CRIT_UNLOCK) || 
            (usConfig == WIN_LOCK) || (usConfig == WIN_UNLOCK));

    xASSERT((ucResol == RESOLUTION_5) || (ucResol == RESOLUTION_25) ||
            (ucResol == RESOLUTION_125) || (ucResol == RESOLUTION_0625));

    xASSERT((ulHyst == HYSTERESIS_0) || (ulHyst == HYSTERESIS_1_5) ||
            (ulHyst == HYSTERESIS_3) || (ulHyst == HYSTERESIS_6));

    MCP98242RegGet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

    config &= ~LOCK_M;
    config |= (LOCK_M & usConfig);    // Set the lock bits
    config &= ~EVENT_SEL_CRIT;
    config |= (EVENT_SEL_CRIT & usConfig);   // Select output event
    config = (config & (~HYSTERESIS_M)) | ulHyst;

    MCP98242RegSet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);    

    MCP98242RegSet(pDev, &ulResol, MCP98242_RSL, I2C_TRANSFER_POLLING);
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
void  MCP98242RegSet(MCP98242Dev *pDev, void * vpValue, unsigned char ucType, 
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
void  MCP98242RegGet(MCP98242Dev *pDev, void * vpValue, unsigned char ucType, 
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
//! \brief Enable interrupt of Event output of MCP98242/3 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242IntEnable(MCP98242Dev *pDev)
{
    unsigned short config;
    
    MCP98242RegGet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Enable Event output
    //
    config |= MCP98242_CONF_EN;
    MCP98242RegSet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

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
//!  it can be: \b  MCP98242_HIGH_LEVEL, assert with high level
//!             \b  MCP98242_LOW_LEVEL, assert with low level
//! \param ulEventMode Comparator mode or Interrupt mode, it can be:
//!        \b EVENT_COMP, Comparator mode
//!        \b EVENT_INT, Interrupt mode
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242IntConfig(MCP98242Dev *pDev, xtEventCallback xtIntCallback, 
                 unsigned long ulTrigMode, unsigned long ulEventMode)
{
    unsigned short config;

    xASSERT((ulTrigMode == MCP98242_HIGH_LEVEL) || 
            (ulTrigMode == MCP98242_LOW_LEVEL));
    xASSERT((ulEventMode == EVENT_COMP) || 
            (ulEventMode == EVENT_INT));

    MCP98242RegGet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);
    
    //
    // Config the trigger level and Event Output Mode
    //
    config = (config & 0xFFFD) | ulTrigMode;
    config = (config & 0xFFFE) | ulEventMode;    
    MCP98242RegSet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

    //
    // Config the Pin mode and Set callback funciton.
    //
    xGPIODirModeSet(pDev->EventPort, pDev->EventPin, GPIO_DIR_MODE_IN);
    xGPIOPinIntCallbackInit(pDev->EventPort, pDev->EventPin, xtIntCallback);

    if(ulTrigMode & MCP98242_HIGH_LEVEL == MCP98242_HIGH_LEVEL)
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
//! \brief Disable Event output of MCP98242 Temperature Sensor.
//!
//! \param *pDev specifies the device
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242IntDisable(MCP98242Dev *pDev)
{
    unsigned short config;
    
    MCP98242RegGet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

    config  &= ~MCP98242_CONF_EN;

    //
    // Disable Event Output
    //
    MCP98242RegSet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

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
void  MCP98242IntClear(MCP98242Dev *pDev)
{
    unsigned short  senconfig;

    MCP98242RegGet(pDev, &senconfig, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

    senconfig |= MCP98242_CONF_INTCLR;

    MCP98242RegSet(pDev, &senconfig, MCP98242_CONFIG, I2C_TRANSFER_POLLING);
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
xtBoolean  MCP98242SHDNEnable(MCP98242Dev *pDev)
{
    unsigned short config;

    MCP98242RegGet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);

    //
    // If bit6 or bit7 is set, it can't set to be shutdown mode.
    //
    if(config & 0xC0)
        return xfalse;
    else
    {
        config |= MCP98242_CONF_SHDN;
        MCP98242RegSet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING); 
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
void  MCP98242SHDNDisable(MCP98242Dev *pDev)
{
    unsigned short config;

    MCP98242RegGet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);
    config &= ~MCP98242_CONF_SHDN;
    MCP98242RegSet(pDev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING); 
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
char  MCP98242EvnCondGet(MCP98242Dev *pDev)
{
    unsigned short s;
    MCP98242RegGet(pDev, &s, MCP98242_TEMP, I2C_TRANSFER_POLLING);  
    return (s>>13);  
}

//*****************************************************************************
//
//! \brief Set the limit temperature of Temperature Sensor. 
//!
//! \param *pDev specifies the device
//! \param *vpValue specifies limit temperature.
//! \param ucLimitType specifies limit type.
//!  it can be: \b  T_UPPER
//!             \b  T_LOWER
//!             \b  T_CRITICAL
//!
//! The \e *vpValue can be type of short or float. 
//!
//! \return None.
//
//***************************************************************************** 
void  MCP98242LimitSet(MCP98242Dev *pDev, void *vpValue, 
                       unsigned char ucLimitType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    unsigned char ucTemp[3];  

    xASSERT((ucLimitType == T_UPPER) ||
            (ucLimitType == T_LOWER) ||
            (ucLimitType == T_CRITICAL));

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
//! \param ucDataType the temperature data type, \b T_FLOAT or \b T_INT.
//!
//! \return None.
//
//***************************************************************************** 
void  MCP98242TempGet(MCP98242Dev *pDev, void *vpValue, 
                      unsigned char ucDataType)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    char cTempReg = 0x05;
    unsigned char ReceiveBuf[2] = {0};

    xASSERT((ucDataType == T_FLOAT) || (ucDataType == T_INT));
   
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
    if(ucDataType == T_FLOAT)
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
//! \brief Get MCP98242 Manufacture ID, Device ID, and Revision.
//!
//! \param *pDev specifies the device
//! \param id  The Manufacture ID, Device ID, and Revision.
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242GetID(MCP98242Dev *pDev, MCP98242_ID *id)
{
    unsigned short *s;
       
    //
    // Get MANUFACTURER ID
    //
    MCP98242RegGet(pDev, id, MCP98242_ManuID, I2C_TRANSFER_POLLING);

    //
    // Get DEVICE ID AND REVISION
    //
    s = ((unsigned short *)id);
    s++;
    MCP98242RegGet(pDev, s, MCP98242_DevID_Rev, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
// EEPROM   funcitons
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Initialize the MCP98242 Temperature Sensor, and select I2C port.
//!
//! \param *pDev specifies the device
//! \param ulRate Specifies the I2C clock rate.
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242EEPROMInit(MCP98242Dev *pDev, unsigned long ulRate)
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
//! \brief Write one byte to EEPROM Standard Array. 
//!
//! \param pDev pointer of the device
//! \param ucAddr specifies address.
//! \param ucValue value to be writen.
//!
//! The \e ucAddr should be between 0x80 to 0xff, the standard array.
//!
//! \return None.
//
//***************************************************************************** 
void  MCP98242ByteWrite(MCP98242Dev *pDev, unsigned char ucAddr, 
                        unsigned char ucValue)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char ucTemp[2];

    xASSERT((ucAddr >= 0x80) && (ucAddr <= 0xFF));
    
    ucTemp[0] = ucAddr;
    ucTemp[1] = ucValue;

    Cfg.ulSlave = pDev->EEPROMSlaAddr;
    Cfg.pvWBuf = ucTemp;
    Cfg.ulWLen = 2;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
}


//*****************************************************************************
//
//! \brief Write one page to EEPROM Standard Array. 
//!
//! \param pDev specifies the device
//! \param ucAddr specifies beginning address of page.
//! \param ucpValue specifies value.
//!
//! This function is to write one page to EEPROM Standard Array.
//!
//! The \e usAddr should be between 0x80 to 0xff, the standard array. 
//! And the low 4 bits should be 0.
//!
//! \return None.
//
//***************************************************************************** 
void MCP98242PageWrite(MCP98242Dev *pDev, unsigned char ucAddr, 
                       unsigned char *ucpValue)
{
    tI2CMasterTransferCfg Cfg;
    int temp;
    unsigned char ucTemp[17];      

    xASSERT(((ucAddr & 0x0F) == 0x00) &&
             (ucAddr >= 0x80) && (ucAddr < 0xFF)); 

    for(temp=0; temp<16; temp++)
    {
        ucTemp[temp+1] = ucpValue[temp];
    }
    ucTemp[0] = ucAddr;

    Cfg.ulSlave = pDev->EEPROMSlaAddr;
    Cfg.pvWBuf = ucTemp;
    Cfg.ulWLen = 17;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
}


//*****************************************************************************
//
//! \brief Read one byte from EEPROM. 
//!
//! \param pDev pointer of the device
//! \param ucAddr specifies address.
//!
//! The \e usAddr should be between 0x00 to 0xff, the whole region.
//!
//! \return value of the specified address.
//
//***************************************************************************** 
unsigned char MCP98242ByteRead(MCP98242Dev *pDev, unsigned char ucAddr)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char ReceiveBuf[1] = {0};

    xASSERT((ucAddr >= 0x00) && (ucAddr <= 0xFF));

    Cfg.ulSlave = pDev->EEPROMSlaAddr;
    Cfg.pvWBuf = &ucAddr;
    Cfg.ulWLen = 1;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = 1;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);

    //
    // the value from EEPROM
    //
    return ReceiveBuf[0];
}

//*****************************************************************************
//
//! \brief Current address or Sequential Read from EEPROM. 
//!
//! \param pDev pointer of the device
//! \param ucAddr specifies address.
//! \param ucpValue pointer of the received value.
//! \param ucNum the number of bytes to be received.
//!
//! When ucAddr and ucNum equal 0, byte of current address will be read. 
//! Otherwise, bytes with number of "ucnum" from address "usAddr" will be read.
//!
//! \return None.
//
//***************************************************************************** 
void MCP98242MemRead(MCP98242Dev *pDev, unsigned char ucAddr, 
                     unsigned char *ucpValue, unsigned char ucNum)
{
    tI2CMasterTransferCfg Cfg;
    int i;
    unsigned char *cp;
    unsigned char *SendBuf;
    unsigned long SendLength = 0;
    
    unsigned char ReceiveBuf[16] = {0};
    unsigned char ReceiveLength = 0;

    xASSERT(ucNum < 17);

    //
    // Current Address Read
    //
    if(ucAddr == 0)
    {
        ReceiveLength = 1;    
    }
    //
    // Sequential Read, 16 bytes at most.
    //
    else
    {
        SendBuf = &ucAddr;
        SendLength = 1;
        ReceiveLength = ucNum;
    }

    Cfg.ulSlave = pDev->EEPROMSlaAddr;
    Cfg.pvWBuf = SendBuf;
    Cfg.ulWLen = SendLength;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = ReceiveBuf;
    Cfg.ulRLen = ReceiveLength;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);

    //
    // Current Address Read
    //
    if(ucAddr == 0)
    {
        *ucpValue = ReceiveBuf[0];    
    }
    //
    // Sequential Read, 16 bytes at most.
    //
    else
    {
        cp = ucpValue;
        for(i=0; i<ucNum; i++, cp++)
        {
            *cp = ReceiveBuf[i];    
        }
    }
}

//*****************************************************************************
//
//! \brief Write one byte to EEPROM Write-Protected Array. 
//!
//! \param pDev pointer of the device
//! \param ucAddr specifies address.
//! \param ucValue value to be writen.
//! \param ucType type of different writing.
//!  It can be : \b EEPROM_SWP
//!              \b EEPROM_CWP
//!              \b EEPROM_PWP
//!
//! The \e ucAddr should be between 0x00 to 0x7f, the Write-Protected array.
//!
//! \return None.
//
//***************************************************************************** 
void  MCP98242ProtWrite(MCP98242Dev *pDev, unsigned char ucAddr,  
                        unsigned char ucValue, unsigned char ucType)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char ucTemp[2];
    unsigned long SlaveAddress;

    if(ucType == EEPROM_SWP)
    {
        //
        // SWP address, it's fixed.
        //
        SlaveAddress = 0x31;
    }
    else if(ucType == EEPROM_CWP)
    {
        //
        // CWP address, it's fixed.
        //
        SlaveAddress = 0x33;   
    }
    else if(ucType == EEPROM_PWP)
    {
        //
        // PWP address, for example: 0x37
        //
        SlaveAddress = pDev->PWPSlaAddr;
    }
      
    ucTemp[0] = ucAddr;
    ucTemp[1] = ucValue;

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = ucTemp;
    Cfg.ulWLen = 2;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Clear the SWP. 
//!
//! \param pDev pointer of the device
//! \param ucAddr specifies address to be cleared.
//!
//! The \e ucAddr should be between 0x00 to 0x7f, the Write-Protected array.
//!
//! \return None.
//
//*****************************************************************************
void  MCP98242ProtClear(MCP98242Dev *pDev, unsigned char ucAddr)
{
    tI2CMasterTransferCfg Cfg;
    unsigned char ucTemp[2];

    //
    // CWP address, it's fixed.
    //
    unsigned long SlaveAddress = 0x33;
   
    ucTemp[0] = ucAddr;
    ucTemp[1] = 0x00;

    Cfg.ulSlave = SlaveAddress;
    Cfg.pvWBuf = ucTemp;
    Cfg.ulWLen = 2;
    Cfg.ulWCount = 0;
    Cfg.pvRBuf = 0;
    Cfg.ulRLen = 0;
    Cfg.ulRCount = 0;  

    xI2CMasterTransfer(pDev->I2CBase, &Cfg, I2C_TRANSFER_POLLING);   
}
