//*****************************************************************************
// 
//! \file STLM75.h
//! \brief Macros used when accessing the STLM75 control hardware.
//! \version V2.1.1.0
//! \date 6. Nov. 2011
//! \author  CooCox
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

#ifndef __STLM75_H__
#define __STLM75_H__

//*****************************************************************************
//
//! \addtogroup COX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor
//! @{
//
//*****************************************************************************
    
//*****************************************************************************
//
//! \addtogroup Sensor_Temp
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_Config STLM75 Driver Config
//! \brief Configurtions something before using this driver.
//! 
//! @{
//
//*****************************************************************************

//
//! It can only be config to 0 or 1
//
#define STLM75_OSINT_USE_CONFIG (1)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_Config STLM75 Driver Config
//! \brief Configurtions something before using this driver.
//! Values that can be passed to STLM75ConfigSet as the ulConfig 
//! parameter.
//! 
//! @{
//
//*****************************************************************************

//
//! Putting the device into Shutdown mode (low-power standby state)
//
#define STLM75_CFG_SHUTDOWN_ON  0x01
//
//! Putting the device into Normal mode
//
#define STLM75_CFG_SHUTDOWN_OFF 0x00

//
//! Thermostat Mode : Comparator mode (defaults)
//
#define STLM75_CFG_MODE_CMP     0x00
//
//! Thermostat Mode : Interrupt mode
//
#define STLM75_CFG_MODE_INT     0x02

//
//! Output Polarity : Low (defaults)
//
#define STLM75_CFG_POL_LOW      0x00
//
//! Output Polarity : High
//
#define STLM75_CFG_POL_HIGH     0x04

//
//! Fault Tolerance, consecutive number : 1 (defaults)
//
#define STLM75_CFG_FT1          0x00
//
//! Fault Tolerance, consecutive number : 2
//
#define STLM75_CFG_FT2          0x08
//
//! Fault Tolerance, consecutive number : 4
//
#define STLM75_CFG_FT4          0x10
//
//! Fault Tolerance, consecutive number : 6
//
#define STLM75_CFG_FT6          0x18

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_Reg_NUM  Command/pointer register
//! @{
//
//*****************************************************************************

//
//! Temperature Register  (defaults)
//
#define STLM75_POINTER_REG_TEMP 0x00
//
//! Configuration Register
//
#define STLM75_POINTER_REG_CONF 0x01
//
//! Hysteresis Register
//
#define STLM75_POINTER_REG_THYS 0x02
//
//! Over-Limit Signal Temperature register
//
#define STLM75_POINTER_REG_TOS  0x03

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_Device STLM75 Driver Device
//! \brief Configurtions such as the GPIO Pin used should be set before using
//! this driver.
//! @{
//
//*****************************************************************************

typedef struct 
{
    //
    //! STLM75 SCK port
    // 
    unsigned long ulSckPort;     
    //
    //! STLM75 SCK pin
    // 
    unsigned long ulSckPin;
    //
    //! STLM75 SDA port
    // 
    unsigned long ulSdaPort;     
    //
    //! STLM75 SDA pin
    // 
    unsigned long ulSdaPin;
    //
    //! STLM75 INT port
    // 
    unsigned long ulIntPort;     
    //
    //! STLM75 INT pin
    // 
    unsigned long ulIntPin;
    
    //
    //! STLM75 I2C Base
    // 
    unsigned long ulI2CBase;
    
    //
    //! STLM75 I2C Base
    // 
    void (*PinSet)(void);
    
#if (STLM75_OSINT_USE_CONFIG > 0)
    xtEventCallback OSPinIntCallback;
#endif
    
    //
    //! STLM75 Address
    // 
    unsigned char ucAddress; 
} 
tSTLM75Dev;


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_Exported_APIs  STLM75 Driver APIs
//! \brief API Reference of STLM75 Driver.
//! @{
//
//*****************************************************************************
extern void STLM75Init(tSTLM75Dev *psDev, unsigned long ulRate);
extern float STLM75TempRead(tSTLM75Dev *psDev);
extern void STLM75LimitSet(tSTLM75Dev *psDev, float fTemp, 
                           unsigned char ucIndex);
extern float STLM75LimitRead(tSTLM75Dev *psDev, unsigned char ucIndex);
extern void STLM75ConfigSet(tSTLM75Dev *psDev, unsigned char ucConfig);
extern unsigned char STLM75ConfigRead(tSTLM75Dev *psDev);


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif
















