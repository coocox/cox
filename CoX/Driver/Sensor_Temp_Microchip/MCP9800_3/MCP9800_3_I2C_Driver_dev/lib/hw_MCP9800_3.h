//*****************************************************************************
//
//! \file hw_MCP9800_3.h
//! \brief header file of Driver for MCP9800_3
//! \version 2.1.1.0
//! \date 18/10/2011
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



#ifndef __HW_MCP9800_H__
#define __HW_MCP9800_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup Sensor 
//! @{
//! \addtogroup Temperature_Sensor  
//! @{
//! \addtogroup MCP9800_TempSensor 
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup MCP9800_Register MCP9800 Register
//! MCP9800 Temperature Sensor Registers.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP9800_Register_Offsets MCP9800 Register Offset(Map)
//! MCP9800 Temperature Sensor Registers.
//! @{
//
//*****************************************************************************

//
//! Ambient Temperature Register.
//
#define    MCP9800_TEMP         0x00000000

//
//! Temperature Sensor Lower Limit Register.
//
#define    MCP9800_CONFIG       0x00000001

//
//! Hysteresis Temperature Register.
//
#define    MCP9800_HYSTERESIS   0x00000002

//
//! Limit Temperature Register.
//
#define    MCP9800_LIMIT        0x00000003

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



#endif // __HW_MCP9800_H__
