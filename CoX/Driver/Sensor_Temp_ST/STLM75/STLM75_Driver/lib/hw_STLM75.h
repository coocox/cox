//*****************************************************************************
// 
//! \file xhw_STLM75.h
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

#ifndef __XHW_STLM75_H__
#define __XHW_STLM75_H__

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
//! \addtogroup STLM75_Pointer_Reg  Command/pointer register
//! @{
//
//*****************************************************************************
//
//! STLM75 Regiser Definition mask
//
#define STLM75_POINTER_REG_M    0x03
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
//! \addtogroup STLM75_Config_Reg  Configuration register
//! @{
//
//*****************************************************************************
//
//! Shutdown Control bit mask
//
#define STLM75_CFG_SHUTDOWN_MASK                                              \
                                0x01
//
//! Putting the device into Shutdown mode (low-power standby state)
//
#define STLM75_CFG_SHUTDOWN_ON  0x01
//
//! Putting the device into Normal mode
//
#define STLM75_CFG_SHUTDOWN_OFF 0x00

//
//! Thermostat Mode Bit mask
//
#define STLM75_CFG_MODE_MASK    0x02
//
//! Thermostat Mode : Comparator mode (defaults)
//
#define STLM75_CFG_MODE_CMP     0x00
//
//! Thermostat Mode : Interrupt mode
//
#define STLM75_CFG_MODE_INT     0x02

//
//! Output Polarity bit mask
//
#define STLM75_CFG_POL_MASK     0x04
//
//! Output Polarity : Low (defaults)
//
#define STLM75_CFG_POL_LOW      0x00
//
//! Output Polarity : High
//
#define STLM75_CFG_POL_HIGH     0x04

//
//! Fault Tolerance bit mask
//
#define STLM75_CFG_FT_MASK      0x18
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
//! \addtogroup STLM75_Temp_Reg  Temperature register
//! @{
//
//*****************************************************************************
//
//! two¡¯s complement sign bit
//
#define STLM75_TEMP_REG_SB      0x03

//
//! Temperature Mask
//
#define STLM75_TEMP_REG_MASK    0x7F80

//
//! Temperature shift
//
#define STLM75_TEMP_REG_SHIFT   7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_Over_Reg  Overlimit temperature register (TOS)
//! @{
//
//*****************************************************************************
//
//! two¡¯s complement sign bit
//
#define STLM75_OVER_REG_SB      0x03

//
//! Overlimit Temperature Mask
//
#define STLM75_OVER_REG_MASK    0x7F80

//
//! Overlimit Temperature shift
//
#define STLM75_OVER_REG_SHIFT   7

//
//! Overlimit Temperature defaults
//
#define STLM75_OVER_REG_DEFAULT 0x5000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_THYS_Reg  Hysteresis temperature register (THYS)
//! @{
//
//*****************************************************************************
//
//! two¡¯s complement sign bit
//
#define STLM75_THYS_REG_SB      0x03

//
//! Hysteresis Temperature Mask
//
#define STLM75_THYS_REG_MASK    0x7F80

//
//! Hysteresis Temperature shift
//
#define STLM75_THYS_REG_SHIFT   7

//
//! Hysteresis Temperature defaults
//
#define STLM75_THYS_REG_DEFAULT 0x4B00

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STLM75_Address_Mask  STLM75 Address Mask
//! @{
//
//*****************************************************************************
//
//! two¡¯s complement sign bit
//
#define STLM75_ADDRESS_MASK     0x48

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

















