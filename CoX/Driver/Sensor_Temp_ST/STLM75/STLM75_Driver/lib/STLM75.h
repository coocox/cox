//*****************************************************************************
// 
//! \file STLM75.h
//! \brief Macros used when accessing the STLM75 control hardware.
//! \version 1.0
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

#define STLM75_

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

//#define STLM75_PIN_DIO         PA0
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
    //! Init the STLM75 pin function
    //! Enable the pin corresponding peripheral
    //
    void (*PinSet)(void);
    
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
extern void STLM75Init(tSTLM75Dev *psDev);



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

















