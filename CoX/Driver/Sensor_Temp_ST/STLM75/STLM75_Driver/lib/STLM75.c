//*****************************************************************************
//
//! \file STLM75.c
//! \brief Driver for digital thermometer STLM75.
//! \version V2.1.1.0
//! \date 10/18/2011
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
//
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xi2c.h"
#include "xcore.h"
#include "hw_STLM75.h"
#include "STLM75.h"


//*****************************************************************************
//
//! \brief Initializes the DS18B20 device.
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//! \param ulRate is STLM75 I2C rate. 
//!
//! \return None.
//
//*****************************************************************************
void STLM75Init(tSTLM75Dev *psDev, unsigned long ulRate)
{
    //
    // Call the callback function
    //
    psDev->PinSet();
    
    //
    // Init the MCU I2C clock and GPIO clock
    //
    xSysCtlPeripheralEnable2(psDev->ulI2CBase);
    xSysCtlPeripheralEnable2(psDev->ulIntPort);
    xSysCtlPeripheralEnable2(psDev->ulSckPort);
    xSysCtlPeripheralEnable2(psDev->ulSdaPort);

    //
    // Set the INT pin as input mode
    //
    xGPIODirModeSet(psDev->ulIntPort, psDev->ulIntPin, xGPIO_DIR_MODE_IN);
#if (STLM75_OSINT_USE_CONFIG > 0)
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(psDev->ulIntPort, psDev->ulIntPin, 
                            psDev->OSPinIntCallback);
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable(psDev->ulIntPort, psDev->ulIntPin, xGPIO_BOTH_EDGES);
    xIntEnable(xSysCtlPeripheraIntNumGet(psDev->ulIntPort));
#endif
    
    //
    // Init the device rate
    //
    xI2CMasterInit(psDev->ulI2CBase, ulRate);
    
    STLM75ConfigSet(psDev, STLM75_CFG_SHUTDOWN_OFF | STLM75_CFG_MODE_INT |
                           STLM75_CFG_POL_LOW | STLM75_CFG_FT1);
}

//*****************************************************************************
//
//! \brief Read the register of the STLM75 device.
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//! \param ucReg Register selected, it should be :\b STLM75_POINTER_REG_TEMP,
//! \b STLM75_POINTER_REG_CONF, \b STLM75_POINTER_REG_THYS,
//! \b STLM75_POINTER_REG_TOS.
//!
//! \return Register value.
//
//*****************************************************************************
unsigned short STLM75RegRead(tSTLM75Dev *psDev, unsigned char ucReg)
{
    xtI2CMasterTransferCfg cfg;
    unsigned char ucTemp = ucReg;
    unsigned char ucRcv[2];
    
    //
    // Check the arguments.
    //
    xASSERT((ucReg == STLM75_POINTER_REG_TEMP) ||
            (ucReg == STLM75_POINTER_REG_CONF) ||
            (ucReg == STLM75_POINTER_REG_THYS) ||
            (ucReg == STLM75_POINTER_REG_TOS));
    
    cfg.ulSlave = psDev->ucAddress;
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
        case STLM75_POINTER_REG_TEMP:  
            cfg.ulRLen = 2; 
            break;
  
        //
        // Configuration Register1
        //
        case STLM75_POINTER_REG_CONF:  
            cfg.ulRLen = 1; 
            break;
  
        //
        // Hysteresis REGISTER
        //
        case STLM75_POINTER_REG_THYS:  
            cfg.ulRLen = 2; 
            break; 
      
        //
        // Over-Limit Signal Temperature register
        //
        case STLM75_POINTER_REG_TOS:  
            cfg.ulRLen = 2; 
            break;
      
        default :         
            break;
    }     
    
    //
    // Data transfering
    //
    if(xI2CMasterTransfer(psDev->ulI2CBase, &cfg, I2C_TRANSFER_POLLING) == 
       xfalse)
    {
        return 0;
    }
    else
    {
        if(cfg.ulRLen == 1)
        {
            return ucRcv[0]; 
        }
        else
        {
            return (((unsigned short)ucRcv[0] << 8) | ucRcv[1]);
        }
    }
}

//*****************************************************************************
//
//! \brief Write the register of the STLM75 device.
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//! \param ucReg Register selected, it should be :\b STLM75_POINTER_REG_TOS,
//! \b STLM75_POINTER_REG_CONF, \b STLM75_POINTER_REG_THYS.
//!
//! \return None.
//
//*****************************************************************************
void STLM75RegWrite(tSTLM75Dev *psDev, unsigned char ucReg,
                    unsigned short usRegValue)
{
    xtI2CMasterTransferCfg cfg;
    unsigned char ucTemp[3];
    
    //
    // Check the arguments.
    //
    xASSERT((ucReg == STLM75_POINTER_REG_CONF) ||
            (ucReg == STLM75_POINTER_REG_THYS) ||
            (ucReg == STLM75_POINTER_REG_TOS));
      
    ucTemp[0] = ucReg;
    ucTemp[1] = (usRegValue >> 8) & 0xFF;
    ucTemp[2] = (usRegValue >> 0) & 0xFF;
    
    cfg.ulSlave = psDev->ucAddress;
    cfg.pvWBuf = &ucTemp;
    cfg.ulWLen = 0;
    cfg.ulRLen = 0;
    cfg.pvRBuf = 0;
    
    //
    // different register has different receive length
    //
    switch(ucReg) 
    {
        //
        // Configuration Register1
        //
        case STLM75_POINTER_REG_CONF:  
            cfg.ulWLen = 1; 
            break;
  
        //
        // Hysteresis REGISTER
        //
        case STLM75_POINTER_REG_THYS:  
            cfg.ulWLen = 2; 
            break; 
      
        //
        // Over-Limit Signal Temperature register
        //
        case STLM75_POINTER_REG_TOS:  
            cfg.ulWLen = 2; 
            break;
      
        default :         
            break;
    } 
    if(cfg.ulWLen == 1) 
    {
        ucTemp[1] = usRegValue & 0xFF;
    } 
    cfg.ulWLen++; 
    xI2CMasterTransfer(psDev->ulI2CBase, &cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief Read the temperature value in degree celsius (°„C).
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//!
//! \return The temperature value in degree celsius.
//
//*****************************************************************************
float STLM75TempRead(tSTLM75Dev *psDev)
{
    unsigned long ulTemp;
    float fTemp;
    unsigned char ucSign = 0;
    
    ulTemp = STLM75RegRead(psDev, STLM75_POINTER_REG_TEMP);
    if(ulTemp & 0x8000) 
    {
        ucSign = 1;
        ulTemp = 0x10000 - ulTemp;
    }

    fTemp =((ulTemp >> 5) & 0x7) / 8.0;
    fTemp += ulTemp >> 8;
  
    if(ucSign == 1) 
    {
        fTemp = 0 - fTemp;
    }
  
    return fTemp;
}

//*****************************************************************************
//
//! \brief Configure the threshold value in degree celsius (°„C).
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//! \param fTemp Temperature value in degree celsius
//! \param ucIndex Threshold type selected
//!                - 0 : Upper trip-point temperature
//!                - 1 : Lower trip-point temperature
//!
//! \return None.
//
//*****************************************************************************
void STLM75LimitSet(tSTLM75Dev *psDev, float fTemp, unsigned char ucIndex)
{
    unsigned short usTemp;
    unsigned short usTempHex;
    unsigned char ucSign;

    //
    // Check the arguments.
    //
    xASSERT((fTemp <= 125) && (fTemp >= -55));
    
    if(fTemp < 0) 
    {
        ucSign = 1;
        fTemp = -fTemp;
    }

    usTemp = (unsigned short)fTemp;

    fTemp = fTemp - usTemp;
    fTemp = fTemp * 8;
    usTempHex = (unsigned short)fTemp;
    usTempHex &= 0x7;
    usTempHex |= (usTemp << 3);
    usTempHex = usTempHex << 5;

    if(ucSign == 1) 
    {
        usTempHex = 0xFFFF - usTempHex + 1;
        usTempHex |= 0x8000;      
    }

    if(ucIndex == 0) 
    {
        STLM75RegWrite(psDev, STLM75_POINTER_REG_THYS, usTempHex);
    }
    else 
    {
        STLM75RegWrite(psDev, STLM75_POINTER_REG_TOS, usTempHex);
    }
}

//*****************************************************************************
//
//! \brief Read the threshold value in degree celsius (°„C).
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//! \param ucIndex Threshold type selected
//!                - 0 : Upper trip-point temperature
//!                - 1 : Lower trip-point temperature
//!
//! \return Temperature value in degree celsius (°„C).
//
//*****************************************************************************
float STLM75LimitRead(tSTLM75Dev *psDev, unsigned char ucIndex)
{
    unsigned short usTempHex;
    unsigned char ucSign;
    float fTemp;
    
    if(ucIndex == 0) 
    {
        usTempHex = STLM75RegRead(psDev, STLM75_POINTER_REG_THYS);
    } 
    else 
    {
        usTempHex = STLM75RegRead(psDev, STLM75_POINTER_REG_TOS);  
    }

    if(usTempHex & 0x8000)
    {
        ucSign = 1;
        usTempHex = 0xFFFF - usTempHex + 1;
    }

    fTemp =((usTempHex >> 5) & 0x7) / 8.0;
    fTemp += usTempHex >> 8;

    if(ucSign == 1)
    {
        fTemp = 0 - fTemp;
    }

    return fTemp;
}

//*****************************************************************************
//
//! \brief Configure the STLM75 device.
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//! \param ulConfig is the value of configuration register
//! 
//! The \e ucConfig parameter is the logical OR of four values: the Shutdown 
//! mode, the Thermostat Mode,the Output Polarity and the Fault Tolerance.
//!
//! \b STLM75_CFG_SHUTDOWN_ON, \b STLM75_CFG_SHUTDOWN_OFF is to trun on or off
//! the Shutdown mode; \b STLM75_CFG_MODE_CMP, \b STLM75_CFG_MODE_INT is to 
//! select the Thermostat Mode; \b STLM75_CFG_POL_LOW, \b STLM75_CFG_POL_HIGH
//! is to select the Output Polarity; \b STLM75_CFG_FT1, \b STLM75_CFG_FT2
//! \b STLM75_CFG_FT4, \b STLM75_CFG_FT6 is to select  the Fault Tolerance.
//!
//! \return None.
//
//*****************************************************************************
void STLM75ConfigSet(tSTLM75Dev *psDev, unsigned char ucConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((((ucConfig & STLM75_CFG_SHUTDOWN_MASK) == STLM75_CFG_SHUTDOWN_OFF) ||
             ((ucConfig & STLM75_CFG_SHUTDOWN_MASK) == STLM75_CFG_SHUTDOWN_ON)) &&
            (((ucConfig & STLM75_CFG_MODE_MASK) == STLM75_CFG_MODE_CMP) ||
             ((ucConfig & STLM75_CFG_MODE_MASK) == STLM75_CFG_MODE_INT)) &&
            (((ucConfig & STLM75_CFG_POL_MASK) == STLM75_CFG_POL_LOW) ||
             ((ucConfig & STLM75_CFG_POL_MASK) == STLM75_CFG_POL_HIGH)) &&
            (((ucConfig & STLM75_CFG_FT_MASK) == STLM75_CFG_FT1) ||
             ((ucConfig & STLM75_CFG_FT_MASK) == STLM75_CFG_FT2) ||
             ((ucConfig & STLM75_CFG_FT_MASK) == STLM75_CFG_FT4) ||
             ((ucConfig & STLM75_CFG_FT_MASK) == STLM75_CFG_FT6))
            );
#if (STLM75_OSINT_USE_CONFIG > 0)
    if(ucConfig & STLM75_CFG_MODE_INT)
    {
        if(ucConfig & STLM75_CFG_POL_HIGH)
        {
            xGPIOPinIntEnable(psDev->ulIntPort, psDev->ulIntPin, 
                              xGPIO_RISING_EDGE);
        }
        else
        {
            xGPIOPinIntEnable(psDev->ulIntPort, psDev->ulIntPin, 
                              xGPIO_FALLING_EDGE);
        }
    }
    else
    {
        xGPIOPinIntEnable(psDev->ulIntPort, psDev->ulIntPin, xGPIO_BOTH_EDGES);
    }
#endif
    STLM75RegWrite(psDev, STLM75_POINTER_REG_CONF, ucConfig);
}

//*****************************************************************************
//
//! \brief read the STLM75 device configuration.
//!
//! \param psDev is a pointer which contains a STLM75 device information.
//!
//! \return the STLM75 device configuration.
//
//*****************************************************************************
unsigned char STLM75ConfigRead(tSTLM75Dev *psDev)
{
    return STLM75RegRead(psDev, STLM75_POINTER_REG_CONF);
}