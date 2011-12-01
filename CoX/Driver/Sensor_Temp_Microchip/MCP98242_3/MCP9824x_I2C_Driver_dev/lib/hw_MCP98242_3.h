//*****************************************************************************
//
//! \file xhw_MCP98242.h
//! \brief header file of Driver for MCP98242/3
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



#ifndef __HW_MCP98242_H__
#define __HW_MCP98242_H__

//*****************************************************************************
//
//! \addtogroup COX_Driver_Lib
//! @{
//! \addtogroup Sensor 
//! @{
//! \addtogroup Temperature_Sensor  Temperature Sensor
//! @{
//! \addtogroup MCP98242_TempSensor_EEPROM MCP98242 TempSensor EEPROM
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup MCP98242_Register MCP98242 Register
//! MCP98242 Temperature Sensor Registers.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_Register_Offsets MCP98242 Register Offset(Map)
//! MCP98242 Temperature Sensor Registers.
//! @{
//
//*****************************************************************************

//
//! Temperature Sensor Capability Register.
//
#define MCP98242_Cap            0x00000000

//
//! Temperature Sensor Configuration Register.
//
#define MCP98242_CONFIG         0x00000001

//
//! Temperature Sensor Upper Limit Register.
//
#define MCP98242_UPPER          0x00000002

//
//! Temperature Sensor Lower Limit Register.
//
#define MCP98242_LOWER          0x00000003

//
//! Temperature Sensor Critical Limit Register.
//
#define MCP98242_CRITICAL       0x00000004

//
//! Temperature Sensor Temperatrue Register.
//
#define MCP98242_TEMP           0x00000005

//
//! MANUFACTURER ID Register.
//
#define MCP98242_ManuID         0x00000006

//
//! DEVICE ID AND REVISION REGISTER ID Register.
//
#define MCP98242_DevID_Rev      0x00000007   

//
//! Temperature Sensor RESOLUTION Register.
//
#define MCP98242_RSL            0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_Cap MCP98242 CAPABILITY
//! MCP98242 Temperature Sensor Capability Register
//! @{
//
//*****************************************************************************


//
//! Temperature Alarm Enable.
//
#define MCP98242_CAP_ALARM      0x00000001

//
//! Temperature Accuracy: ¡À1¡ãC from +75¡ãC to +95¡ãC (Active Range) and 
//! ¡À2¡ãC from +40¡ãC to +125¡ãC.
//
#define MCP98242_CAP_ACR        0x00000002

//
//! Temperature Measurement Range: The part can measure 
//! temperature below 0¡ãC (power-up default).
//
#define MCP98242_CAP_MEAS       0x00000004

#ifdef   MCP98243

//
//! Pin A0 accepts High Voltage for the EEPROM Write Protect 
//! feature (power-up default).
//
#define MCP98242_CAP_HV         0x00000020

//
//! Bus time-out range is 25 ms to 35 ms.
//
#define MCP98242_CAP_TOUT       0x00000040

//
//! Event output de-asserts during shutdown. After shutdown, 
//! it takes T_CONV to re-assert the Event output (power-up default)
//
#define MCP98242_CAP_SHDN_DE    0x00000080

#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_Config  MCP98242 Configuration
//! MCP98242 Temperature Sensor Configuration Register
//! @{
//
//*****************************************************************************

//
//! Event Output Mode: Interrupt output.
//
#define MCP98242_CONF_EVMODE    0x00000001

//
//! Event Output Polarity.
//
#define MCP98242_HIGH_LEVEL     0x00000002

//
//! Event Output Select: TA > TCRIT only.
//
#define MCP98242_CONF_SEL       0x00000004

//
//! Event Output Enable.
//
#define MCP98242_CONF_EN        0x00000008

//
//! Event Output Status: asserted.
//
#define MCP98242_CONF_STAT      0x00000010

//
//! Event Output Interrupt Clear.
//
#define MCP98242_CONF_INTCLR    0x00000020

//
//! TUPPER and TLOWER Window Lock.
//
#define MCP98242_CONF_WINLOCK   0x00000040

//
//! TCRIT Lock.
//
#define MCP98242_CONF_CRTLOCK   0x00000080

//
//! Shutdown Mode.
//
#define MCP98242_CONF_SHDN      0x00000100

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
//! @}
//! @}
//! @}
//
//*****************************************************************************      



#endif // __HW_MCP98242_H__
