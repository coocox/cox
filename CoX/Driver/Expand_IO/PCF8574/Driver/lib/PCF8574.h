//*****************************************************************************
//
//! \file hw_PCF8574.h
//! \brief header file of Driver for PCF8574 I2C bus port.
//! \version V2.1.1.0
//! \date 31/12/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox All rights reserved.
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

#ifndef __HW_PCF8574_H_
#define __HW_PCF8574_H_

#include <stdint.h>

#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_i2c.h"
#include "xi2c.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#define SUCCESS                 0
#define FAILURE                 1
typedef unsigned long int Result; 
  
//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup Expand Bus
//! @{
//! \addtogroup I2C_Port_Bus
//! @{
//! \addtogroup PCF8574
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PCF8574_Hardware_Information Lower hardware information.
//! \brief I2C communcation port information, you must change this macro
//! according your hardware.
//! @{
//
//*****************************************************************************

  
//! PCF8574 Salve Address 7-bit mode
//! \b NOTE: R/W bit is EXCLUDE from this address
#define PCF8574_I2C_ADDR       0x20

//! SCK Pin
#define PCF8574_PIN_I2C_SCK    PB6
#define PCF8574_I2C_SCK        I2C1SCK

//! SDA Pin
#define PCF8574_PIN_I2C_SDA    PB7
#define PCF8574_I2C_SDA        I2C1SDA

//! I2C Base Address
#define PCF8574_PIN_I2C_PORT   I2C1_BASE
#define PCF8574_I2C_GPIO       SYSCTL_PERIPH_IOPB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


Result PCF8574_Init(void);
Result PCF8574_WriteByte(uint8_t Val);
Result PCF8574_ReadByte(uint8_t * pVal);
Result PCF8574_WriteBits(uint8_t Mask, uint8_t Val);
Result PCF8574_ReadBits(uint8_t Mask, uint8_t * pVal);


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

//*****************************************************************************
//
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  //__HW_PCF8574_H_

