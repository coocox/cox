//*****************************************************************************
//
//! \file ADXL345.h
//! \brief Prototypes for the ADXL345 Driver.
//! \version V2.1.1.0
//! \date 31/12/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
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
//!
//*****************************************************************************
#ifndef __ADXL345_H__
#define __ADXL345_H__

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

#include "hw_ADXL345.h"

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
//! \addtogroup Accelerometer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADXL345
//! @{
//
//***************************************************************************** 
    
#define SUCCESS                 0
#define FAILURE                 1
typedef unsigned long int Result;

// Disable assert
#define ASSERT(x)

// use C assert
//#define ASSERT(x) assert(x)

// use Cox assert
//#define ASSERT() xASSERT()

//*****************************************************************************
//
//! \addtogroup ADXL345_Hardware_Information Lower hardware information.
//! \brief I2C communcation port information, you must change this macro
//! according your hardware.
//! @{
//
//*****************************************************************************

//! Salve Address 7-bit mode
//! \b NOTE: R/W bit is EXCLUDE from this address
#define ADXL345_I2C_ADDR        0x53

//! SCK Pin
#define ADXL345_PIN_I2C_SCK     PB6
#define ADXL345_I2C_SCK         I2C1SCK

//! SDA Pin
#define ADXL345_PIN_I2C_SDA     PB7
#define ADXL345_I2C_SDA         I2C1SDA

//! I2C Base Address
#define ADXL345_PIN_I2C_PORT    I2C1_BASE
#define ADXL345_I2C_GPIO        SYSCTL_PERIPH_IOPB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//! This paramter is used for special the axis, can be used in the follow function:
//! 1: ADXL345_ReadAccData
//! 2: ADXL345_OffSetWrite
#define AXIS_X                   ((uint8_t) 0x00)
#define AXIS_Y                   ((uint8_t) 0x01)
#define AXIS_Z                   ((uint8_t) 0x02)

// For Active Inactive control register

//! selects ac-coupled operation.
#define ACT_AC                   ((uint32_t) 0x00000080)

//! enables x-axis participation in detecting activity 
#define ACT_X_EN                 ((uint32_t) 0x00000040)

//! enables y-axis participation in detecting activity 
#define ACT_Y_EN                 ((uint32_t) 0x00000020)

//! enables z-axis participation in detecting activity 
#define ACT_Z_EN                 ((uint32_t) 0x00000010)

//! selects ac-coupled operation.
#define INACT_AC                 ((uint32_t) 0x00000008)

//! enables x-axis participation in detecting inactivity 
#define INACT_X_EN               ((uint32_t) 0x00000004)

//! enables y-axis participation in detecting inactivity 
#define INACT_Y_EN               ((uint32_t) 0x00000002)

//! enables z-axis participation in detecting inactivity 
#define INACT_Z_EN               ((uint32_t) 0x00000001)

//! selects dc-coupled operation.
#define ACT_DC                   ((uint32_t) 0x00008000)

//! disables x-axis participation in detecting activity 
#define ACT_X_DIS                ((uint32_t) 0x00004000)

//! disbles y-axis participation in detecting activity 
#define ACT_Y_DIS                ((uint32_t) 0x00002000)

//! disbles z-axis participation in detecting activity 
#define ACT_Z_DIS                ((uint32_t) 0x00001000)

//! selects dc-coupled operation.
#define INACT_DC                 ((uint32_t) 0x00000800)

//! disbles x-axis participation in detecting inactivity 
#define INACT_X_DIS              ((uint32_t) 0x00000400)

//! disbles y-axis participation in detecting inactivity 
#define INACT_Y_DIS              ((uint32_t) 0x00000200)

//! disbles z-axis participation in detecting inactivity 
#define INACT_Z_DIS              ((uint32_t) 0x00000100)

// For tap control register

//! Setting the suppress bit suppresses double tap detection if 
//! acceleration greater than the value in THRESH_TAP is present 
//! between taps
//! Suppress enable
#define TAP_SUPRESS_EN           ((uint32_t) 0x00000008)

//! Enable tap detect on x axis
#define TAP_X_EN                 ((uint32_t) 0x00000004)

//! Enable tap detect on y axis
#define TAP_Y_EN                 ((uint32_t) 0x00000002)

//! Enable tap detect on z axis
#define TAP_Z_EN                 ((uint32_t) 0x00000001)

//! Setting the suppress bit suppresses double tap detection if 
//! acceleration greater than the value in THRESH_TAP is present 
//! between taps
//! Suppress disable
#define TAP_SUPRESS_DIS          ((uint32_t) 0x00000800)

//! Disable tap detect on x axis
#define TAP_X_DIS                ((uint32_t) 0x00000400)

//! Disable tap detect on y axis
#define TAP_Y_DIS                ((uint32_t) 0x00000200)

//! Disable tap detect on z axis
#define TAP_Z_DIS                ((uint32_t) 0x00000100)

//! Accelerometer status Flag
//! you can use those parameters in ADXL345_StatusCheck function

#define EVENT_ACT_X              ((uint32_t) 0x00000040)
#define EVENT_ACT_Y              ((uint32_t) 0x00000020)
#define EVENT_ACT_Z              ((uint32_t) 0x00000010)
#define EVENT_ASLEEP             ((uint32_t) 0x00000008)
#define EVENT_TAP_X              ((uint32_t) 0x00000004)
#define EVENT_TAP_Y              ((uint32_t) 0x00000002)
#define EVENT_TAP_Z              ((uint32_t) 0x00000001)
#define EVENT_DATA_READY         ((uint32_t) 0x00008000)
#define EVENT_SINGLE_TAP         ((uint32_t) 0x00004000)
#define EVENT_DOUBLE_TAP         ((uint32_t) 0x00002000)
#define EVENT_ACTIVITY           ((uint32_t) 0x00001000)
#define EVENT_INACTIVITY         ((uint32_t) 0x00000800)
#define EVENT_FREE_FALL          ((uint32_t) 0x00000400)
#define EVENT_WATERMARK          ((uint32_t) 0x00000200)
#define EVENT_OVERRUN            ((uint32_t) 0x00000100)
#define EVENT_FIFO_TRG           ((uint32_t) 0x00800000) 

//! Parameter used in function ADXL345_PowerCfg
//! Enable Low power mode
#define LOW_POWER_EN             ((uint32_t) 0x00000010)

//! Disable Low power mode
#define LOW_POWER_DIS            ((uint32_t) 0x00001000)

//! Set Output data rate 3200 Hz
#define OUTPUT_RATE_3200         ((uint32_t) 0x0000000F)

//! Set Output data rate 1600 Hz
#define OUTPUT_RATE_1600         ((uint32_t) 0x0000010E)

//! Set Output data rate 800 Hz
#define OUTPUT_RATE_800          ((uint32_t) 0x0000020D)

//! Set Output data rate 400 Hz
#define OUTPUT_RATE_400          ((uint32_t) 0x0000030C)

//! Set Output data rate 200 Hz
#define OUTPUT_RATE_200          ((uint32_t) 0x0000040B)

//! Set Output data rate 100 Hz
#define OUTPUT_RATE_100          ((uint32_t) 0x0000050A)

//! Set Output data rate 50 Hz
#define OUTPUT_RATE_50           ((uint32_t) 0x00000609)

//! Set Output data rate 25 Hz
#define OUTPUT_RATE_25           ((uint32_t) 0x00000708)

//! Set Output data rate 12.5 Hz
#define OUTPUT_RATE_12_5         ((uint32_t) 0x00000807)

//! Set Output data rate 6.25 Hz
#define OUTPUT_RATE_6_25         ((uint32_t) 0x00000906)

//! Set Output data rate 3.13 Hz
#define OUTPUT_RATE_3_13         ((uint32_t) 0x00000A05)

//! Set Output data rate 1.56 Hz
#define OUTPUT_RATE_1_56         ((uint32_t) 0x00000B04)

//! Set Output data rate 0.78 Hz
#define OUTPUT_RATE_0_78         ((uint32_t) 0x00000C03)

//! Set Output data rate 0.39 Hz
#define OUTPUT_RATE_0_39         ((uint32_t) 0x00000D02)

//! Set Output data rate 0.20 Hz
#define OUTPUT_RATE_0_20         ((uint32_t) 0x00000E01)

//! Set Output data rate 0.10 Hz
#define OUTPUT_RATE_0_10         ((uint32_t) 0x00000F00)

//! Enable Link
//! A setting of 1 in the link bit with both the activity and inactivity 
//! functions enabled delays the start of the activity function until 
//! inactivity is detected. After activity is detected, inactivity detection 
//! begins, preventing the detection of activity. This bit serially links 
//! the activity and inactivity functions. 
#define LINK_EN                  ((uint32_t) 0x00200000)

//! Enable auto sleep mode
#define AUTO_SLEEP_EN            ((uint32_t) 0x00100000)

//! Enable measure mode
#define MEASURE_EN               ((uint32_t) 0x00080000)

//! Enable Sleep mode
#define SLEEP_EN                 ((uint32_t) 0x00040000)

//! Disable Link
//! When clearing the link bit, it is recommended that the part be 
//! placed into standby mode and then set back to measurement 
//! mode with a subsequent write. This is done to ensure that the 
//! device is properly biased if sleep mode is manually disabled; 
//! otherwise, the first few samples of data after the link bit is cleared 
//! may have additional noise, especially if the device was asleep 
//! when the bit was cleared.
#define LINK_DIS                 ((uint32_t) 0x20000000)

//! Disable auto sleep mode
#define AUTO_SLEEP_DIS           ((uint32_t) 0x10000000)

//! Disable measure mode
//! that's mean enter standby mode
#define MEASURE_DIS              ((uint32_t) 0x08000000)

//! Disable Sleep mode
#define SLEEP_DIS                ((uint32_t) 0x04000000)

//!Set the frequency of readings in sleep mode to 8Hz
#define SLEEP_RATE_8             ((uint32_t) 0x03000000)

//!Set the frequency of readings in sleep mode to 4Hz
#define SLEEP_RATE_4             ((uint32_t) 0x02010000)

//!Set the frequency of readings in sleep mode to 2Hz
#define SLEEP_RATE_2             ((uint32_t) 0x01020000)

//!Set the frequency of readings in sleep mode to 1Hz
#define SLEEP_RATE_1             ((uint32_t) 0x00030000)

//For interrupt control register
//! Enable data ready interrupt
#define INT_DATA_READY_EN        ((uint32_t) 0x00000080)

//! Enable single tap interrupt
#define INT_SINGLE_TAP_EN        ((uint32_t) 0x00000040)

//! Enable double tap interrupt
#define INT_DOUBLE_TAP_EN        ((uint32_t) 0x00000020)

//! Enable activity interrupt
#define INT_ACTIVITY_EN          ((uint32_t) 0x00000010)

//! Enable inactivity interrupt
#define INT_INACTIVITY_EN        ((uint32_t) 0x00000008)

//! Enable freefall interrupt
#define INT_FREE_FALL_EN         ((uint32_t) 0x00000004)

//! Enable watermark interrupt
#define INT_WATERMARK_EN         ((uint32_t) 0x00000002)

//! Enable overrun interrupt
#define INT_OVERRUN_EN           ((uint32_t) 0x00000001)

//! Disable data ready interrupt
#define INT_DATA_READY_DIS       ((uint32_t) 0x00008000)

//! Disable single tap interrupt
#define INT_SINGLE_TAP_DIS       ((uint32_t) 0x00004000)

//! Disable double tap interrupt
#define INT_DOUBLE_TAP_DIS       ((uint32_t) 0x00002000)

//! Disable activity interrupt
#define INT_ACTIVITY_DIS         ((uint32_t) 0x00001000)

//! Disable inactivity interrupt
#define INT_INACTIVITY_DIS       ((uint32_t) 0x00000800)

//! Disable freefall interrupt
#define INT_FREE_FALL_DIS        ((uint32_t) 0x00000400)

//! Disable watermark interrupt
#define INT_WATERMARK_DIS        ((uint32_t) 0x00000200)

//! Disable overrun interrupt
#define INT_OVERRUN_DIS          ((uint32_t) 0x00000100)

//For interrupt map register
//! Map data ready signal to int1 pin
#define DATA_READY_INT1          ((uint32_t) 0x80000000)

//! Map single tap signal to int1 pin
#define SINGLE_TAP_INT1          ((uint32_t) 0x40000000)

//! Map double tap signal to int1 pin
#define DOUBLE_TAP_INT1          ((uint32_t) 0x20000000)

//! Map activity signal to int1 pin
#define ACTIVITY_INT1            ((uint32_t) 0x10000000)

//! Map inactivity signal to int1 pin
#define INACTIVITY_INT1          ((uint32_t) 0x08000000)

//! Map freefall signal to int1 pin
#define FREE_FALL_INT1           ((uint32_t) 0x04000000)

//! Map watermark signal to int1 pin
#define WATERMARK_INT1           ((uint32_t) 0x02000000)

//! Map overrun signal to int1 pin
#define OVERRUN_INT1             ((uint32_t) 0x01000000)

//! Map data ready signal to int2 pin
#define DATA_READY_INT2          ((uint32_t) 0x00800000)

//! Map single tap signal to int2 pin
#define SINGLE_TAP_INT2          ((uint32_t) 0x00400000)

//! Map double tap signal to int2 pin
#define DOUBLE_TAP_INT2          ((uint32_t) 0x00200000)

//! Map activity signal to int2 pin
#define ACTIVITY_INT2            ((uint32_t) 0x00100000)

//! Map inactivity signal to int2 pin
#define INACTIVITY_INT2          ((uint32_t) 0x00080000)

//! Map freefall signal to int2 pin
#define FREE_FALL_INT2           ((uint32_t) 0x00040000)

//! Map watermark signal to int2 pin
#define WATERMARK_INT2           ((uint32_t) 0x00020000)

//! Map overrun signal to int2 pin
#define OVERRUN_INT2             ((uint32_t) 0x00010000)

// For Data format register
//! Enable selftest function 
#define SELF_TEST_EN             ((uint32_t) 0x00000080)

//! Set SPI 3 Wire mode
#define SPI_3_WIRE               ((uint32_t) 0x00000040)

//! interrupt pin low when activity
#define INT_LOW                  ((uint32_t) 0x00000020)

//! Set to full resolution mode
#define FULL_RES_EN              ((uint32_t) 0x00000008)

//! left-justified mode
#define JUSTIFY_LEFT             ((uint32_t) 0x00000004)

//! Disable selftest function 
#define SELF_TEST_DIS            ((uint32_t) 0x00008000)

//! Set SPI 4 Wire mode
#define SPI_4_WIRE               ((uint32_t) 0x00004000)

//! interrupt pin high when activity
#define INT_HIGH                 ((uint32_t) 0x00002000)

//! Set to full resolution mode
#define FULL_RES_DIS             ((uint32_t) 0x00000800)

//! right-justified mode
#define JUSTIFY_RIGHT            ((uint32_t) 0x00000400)

//Set measurement range to +/- 2G
#define RANGE_2_G                ((uint32_t) 0x00000300)

//Set measurement range to +/- 4G
#define RANGE_4_G                ((uint32_t) 0x00000201)

//Set measurement range to +/- 8G
#define RANGE_8_G                ((uint32_t) 0x00000102)

//Set measurement range to +/- 16G
#define RANGE_16_G               ((uint32_t) 0x00000003)

// For FIFO Configure register
//! Disable FIFO mode
#define MODE_BYPASS              ((uint32_t) 0x0000C000)

//! Set FIFO FIFO Mode
#define MODE_FIFO                ((uint32_t) 0x00008040)

//! Set FIFO Stream Mode
#define MODE_STREAM              ((uint32_t) 0x00004080)

//! Set FIFO Trigger Mode
#define MODE_TRIGGER             ((uint32_t) 0x000000C0)

//! Map FIFO to interrupt pin 1
#define FIFO_INT1                ((uint32_t) 0x00002000)

//! Map FIFO to interrupt pin 2
#define FIFO_INT2                ((uint32_t) 0x00000020)

//*****************************************************************************
//
//! \addtogroup ADXL345_API
//! @{
//
//*****************************************************************************

Result ADXL345_Init(void);
Result ADXL345_ReadAccData(uint8_t Axis, int16_t * DataRecvBuf);
Result ADXL345_OffSetWrite(uint8_t Axis, uint8_t OffSet);
Result ADXL345_RegWriteByte(uint8_t RegAddr, uint8_t Data);
Result ADXL345_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf);
Result ADXL345_TapThresholdSet(uint8_t ThresHold);
Result ADXL345_WindowSet(uint8_t Window);
Result ADXL345_LatencySet(uint8_t Latency);
Result ADXL345_DurationSet(uint8_t Duration);
Result ADXL345_ActThresholdSet(uint8_t ThresHold);
Result ADXL345_InactThresholdSet(uint8_t ThresHold);
Result ADXL345_InactTimeSet(uint8_t Time);
Result ADXL345_ActCfg(uint32_t Cfg);
Result ADXL345_FFThresholdSet(uint8_t ThresHold);
Result ADXL345_FFTimeSet(uint8_t Time);
Result ADXL345_TapCfg(uint32_t Cfg);
Result ADXL345_StatusCheck(uint32_t Event);
Result ADXL345_PowerCfg(uint32_t Cfg);
Result ADXL345_IntCfg(uint32_t Cfg);
Result ADXL345_DataCfg(uint32_t Cfg);
Result ADXL345_FIFOCfg(uint32_t Cfg, uint8_t Sample);
Result ADXL345_EntryGet(uint8_t * pEntry);

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
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif  

#endif // __ADXL345_H__

