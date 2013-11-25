//*****************************************************************************
//
//! \file hw_ADXL345.h
//! \brief header file of Driver for MMA8451
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

#ifndef __HW_ADXL345_H_
#define __HW_ADXL345_H_
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

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup Sensor
//! @{
//! \addtogroup Accelerometer
//! @{
//! \addtogroup ADXL345
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADXL345_Register_Base_Address ADXL345 Register base address.
//! \brief Register Base Address.
//! @{
//
//*****************************************************************************

//Device ID
#define ADXL345_REG_DEVID                ((uint8_t)0x00)

//Tap threshold
#define ADXL345_REG_THRESH_TAP           ((uint8_t)0x1D)

//X-axis offset
#define ADXL345_REG_OFSX                 ((uint8_t)0x1E)

//Y-axis offset
#define ADXL345_REG_OFSY                 ((uint8_t)0x1F)

//Z-axis offset
#define ADXL345_REG_OFSZ                 ((uint8_t)0x20)

//Tap duration
#define ADXL345_REG_DUR                  ((uint8_t)0x21)

//Tap latency
#define ADXL345_REG_Latent               ((uint8_t)0x22)

//Tap window
#define ADXL345_REG_Window               ((uint8_t)0x23)

//Activity threshold
#define ADXL345_REG_THRESH_ACT           ((uint8_t)0x24)

//Inactivity threshold
#define ADXL345_REG_THRESH_INACT         ((uint8_t)0x25)

//Inactivity time
#define ADXL345_REG_TIME_INACT           ((uint8_t)0x26)

//Axis enable control for activity and inactivity detection
#define ADXL345_REG_ACT_INACT_CTL        ((uint8_t)0x27)

//Free-fall threshold
#define ADXL345_REG_THRESH_FF            ((uint8_t)0x28)

//Free-fall time
#define ADXL345_REG_TIME_FF              ((uint8_t)0x29)

//Axis control for single tap/double tap
#define ADXL345_REG_TAP_AXES             ((uint8_t)0x2A)

//Sour ce of single tap/double tap
#define ADXL345_REG_ACT_TAP_STATUS       ((uint8_t)0x2B)

//Data rate and power mode control
#define ADXL345_REG_BW_RATE              ((uint8_t)0x2C)

//Power-saving features control
#define ADXL345_REG_POWER_CTL            ((uint8_t)0x2D)

//Interrupt enable control
#define ADXL345_REG_INT_ENABLE           ((uint8_t)0x2E)

//Interrupt mapping control
#define ADXL345_REG_INT_MAP              ((uint8_t)0x2F)

//Source of interrupts
#define ADXL345_REG_INT_SOURCE           ((uint8_t)0x30)

//Data format control
#define ADXL345_REG_DATA_FORMAT          ((uint8_t)0x31)

//X-Axis Data 0
#define ADXL345_REG_DATAX0               ((uint8_t)0x32)

//X-Axis Data 1
#define ADXL345_REG_DATAX1               ((uint8_t)0x33)

//Y-Axis Data 0
#define ADXL345_REG_DATAY0               ((uint8_t)0x34)

//Y-Axis Data 1
#define ADXL345_REG_DATAY1               ((uint8_t)0x35)

//Z-Axis Data 0
#define ADXL345_REG_DATAZ0               ((uint8_t)0x36)

//Z-Axis Data 1
#define ADXL345_REG_DATAZ1               ((uint8_t)0x37)

//FIFO control
#define ADXL345_REG_FIFO_CTL             ((uint8_t)0x38)

//FIFO status
#define ADXL345_REG_FIFO_STATUS          ((uint8_t)0x39)


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

#endif  //__HW_ADXL345_H_

