//*****************************************************************************
//
//! \file MMA7455.h
//! \brief Prototypes for the MMA7455 Driver.
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
#ifndef __MMA7455_H__
#define __MMA7455_H__

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

#include "hw_MMA7455.h"

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
//! \addtogroup LIS302DL
//! @{
//
//***************************************************************************** 
    
#define SUCCESS                 0
#define FAILURE                 1
typedef unsigned long int Result;

//
//! Select MMA7455 Communication type I2C/SPI
//! you can only select a communication type at a time
//! \b NOTE: Now the dirver support I2C only
#define MMA7455_PORT_I2C
//#define MMA7455_PORT_SPI

//
//! Select assert implements, you can only use one type at a time.
//

// Disable assert
#define ASSERT(x)

// use C assert
//#define ASSERT(x) assert(x)

// use Cox assert
//#define ASSERT() xASSERT()


//*****************************************************************************
//
//! \addtogroup MMA7455_Hardware_Information Lower hardware information.
//! \brief I2C communcation port information, you must change this macro
//! according your hardware.
//! @{
//
//*****************************************************************************

//! LIS302 Salve Address 7-bit mode
//! \b NOTE: R/W bit is EXCLUDE from this address
#define MMA7455_I2C_ADDR       0x1D

//! SCK Pin
#define MMA7455_PIN_I2C_SCK    PB6
#define MMA7455_I2C_SCK        I2C1SCK

//! SDA Pin
#define MMA7455_PIN_I2C_SDA    PB7
#define MMA7455_I2C_SDA        I2C1SDA

//! I2C Base Address
#define MMA7455_PIN_I2C_PORT   I2C1_BASE
#define MMA7455_I2C_GPIO       SYSCTL_PERIPH_IOPB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
 
//
//! The macro below is used for
//! Function: MMA7455_ReadAccData_8 and MMA7455_ReadAccData_10 and
//! MMA7455_OffSetWrite
//! Param   : Axis
//
#define AXIS_X                      ((uint32_t)0x00100600)
#define AXIS_Y                      ((uint32_t)0x00120702)
#define AXIS_Z                      ((uint32_t)0x00140804)

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//
//! The macro below is used for
//! Function: MMA7455_EventCheck
//! Param   : Event
//
#define ENEVT_MASK                  0xFF07

//! Data is ready ?
#define ENEVT_DATA_READY            0x0001

//! Data is over written ?
#define ENEVT_DATA_OVER_WRITE       0x0002

//! Parity error is detected in trim data ?
#define ENEVT_PARITY_ERROR          0x0004

//! Level detection detected on X-axis ?
#define ENEVT_LEVEL_X               0x8000

//! Level detection detected on Y-axis ?
#define ENEVT_LEVEL_Y               0x4000

//! Level detection detected on Z-axis ?
#define ENEVT_LEVEL_Z               0x2000

//! Pulse detection detected on X-axis ?
#define ENEVT_PULSE_X               0x1000

//! Pulse detection detected on Y-axis ?
#define ENEVT_PULSE_Y               0x0800

//! Pulse detection detected on Z-axis ?
#define ENEVT_PULSE_Z               0x0400

//! INT1 is detected ?
#define ENEVT_INT_1                 0x0200

//! INT2 is detected ?
#define ENEVT_INT_2                 0x0100  

//
//! The macro below is used for
//! Function: MMA7455_Cfg
//! Param   : Cfg
// 
#define CFG_MASK                    (uint64_t)0x0000FFFFFFFFFFFF
#define CFG_MASK_1                  (uint64_t)0x000000000000FFFF
#define CFG_MASK_2                  (uint64_t)0x00000000FFFF0000
#define CFG_MASK_3                  (uint64_t)0x0000FFFF00000000

//$16: Mode Control Register (Read/Write)

//! Data ready status is output to INT1/DRDY PIN
#define CFG_DATA_RDY_OUT_EN         (uint64_t)0x0000000000004000

//! Data ready status is not output to INT1/DRDY PIN
#define CFG_DATA_RDY_OUT_DIS        (uint64_t)0x0000000000000040

//! Set SPI to 3-Wire mode
#define CFG_SPI_3_WIRE              (uint64_t)0x0000000000000020

//! Set SPI to 4-Wire mode
#define CFG_SPI_4_WIRE              (uint64_t)0x0000000000002000

//! Enable Self-test
#define CFG_SELFTEST_EN             (uint64_t)0x0000000000000010

//! Disable Self-test
#define CFG_SELFTEST_DIS            (uint64_t)0x0000000000001000

//! Used in function internal, not for user
#define CFG_RANGE_MASK              (uint64_t)0x0000000000000C0C

//! Set measurement range to +-2G
#define CFG_RANGE_2G                (uint64_t)0x0000000000000804

//! Set measurement range to +-4G
#define CFG_RANGE_4G                (uint64_t)0x0000000000000408

//! Set measurement range to +-8G
#define CFG_RANGE_8G                (uint64_t)0x0000000000000C00

//! Used in function internal, not for user
#define CFG_MODE_MASK               (uint64_t)0x0000000000000303

//! configure to Standby mode
#define CFG_MODE_STANDBY            (uint64_t)0x0000000000000300

//! configure to measurement mode
#define CFG_MODE_MEASUREMENT        (uint64_t)0x0000000000000201

//! configure to level mode
#define CFG_MODE_LEVEL              (uint64_t)0x0000000000000102

//! configure to pulse mode
#define CFG_MODE_PULSE              (uint64_t)0x0000000000000003

//$18 Control 1 (Read/Write)
//! Digital filter band width is 62.5 Hz
#define CFG_FILTER_BAND_62_5        (uint64_t)0x0000000080000000

//! Digital filter band width is 125 Hz
#define CFG_FILTER_BAND_125         (uint64_t)0x0000000000800000

//! Threshold value is absolute only
#define CFG_THRESHOLD_VALUE_ABS     (uint64_t)0x0000000040000000

//! Integer value is available.
#define CFG_THRESHOLD_VALUE_INT     (uint64_t)0x0000000000400000

//! Z-axis is enabled for detection.
#define CFG_AXIS_Z_EN               (uint64_t)0x0000000020000000

//! Z-axis is disabled for detection
#define CFG_AXIS_Z_DIS              (uint64_t)0x0000000000200000

//! Y-axis is enabled for detection.
#define CFG_AXIS_Y_EN               (uint64_t)0x0000000010000000

//! Y-axis is disabled for detection.
#define CFG_AXIS_Y_DIS              (uint64_t)0x0000000000100000

//! X-axis is enabled for detection.
#define CFG_AXIS_X_EN               (uint64_t)0x0000000008000000

//! X-axis is disabled for detection.
#define CFG_AXIS_X_DIS              (uint64_t)0x0000000000080000

//! Internal use, NOT for user. 
#define CFG_INT_MODE_M              (uint64_t)0x0000000006060000

//! INT1 Register is detecting Level while INT2 is detecting Pulse.
#define CFG_INT_MODE_0              (uint64_t)0x0000000006000000

//! INT1 Register is detecting Pulse while INT2 is detecting Level
#define CFG_INT_MODE_1              (uint64_t)0x0000000004020000

//! INT1 Register is detecting a Single Pulse and INT2 is detecting Single Pulse
//!     (if 2nd Time Window = 0) or if there is a latency time window and second
//!     time window > 0 then INT2 will detect the double pulse only.
#define CFG_INT_MODE_2              (uint64_t)0x0000000002040000

//! INT1 pin is routed to INT1 bit in Detection Source Register ($0A) and INT2 pin
//! is routed to INT2 bit in Detection Source Register ($0A).
#define CFG_INT_PIN_NORMAL          (uint64_t)0x0000000001000000

//! INT2 pin is routed to INT1 bit in Detection Source Register ($0A) and INT1 pin
//! is routed to INT2 bit in Detection Source Register ($0A).
#define CFG_INT_PIN_EXCHANGE        (uint64_t)0x0000000000010000

//$19 Control 2 (Read/Write)

//! Standard drive strength on SDA/SDO pin
#define CFG_STRENGTH_STANDARD       (uint64_t)0x0000040000000000

//! Strong drive strength on SDA/SDO pin
#define CFG_STRENGTH_STRONGE        (uint64_t)0x0000000400000000

//! Pulse detection polarity is positive and detecting condition is OR 3 axes.
#define CFG_PULSE_DETECTION_OR      (uint64_t)0x0000020000000000

//! Pulse detection polarity is negative and detecting condition is AND 3 axes.
#define CFG_PULSE_DETECTION_AND     (uint64_t)0x0000000200000000

//! Level detection polarity is positive and detecting condition is OR 3 axes.
#define CFG_LEVEL_DETECTION_OR      (uint64_t)0x0000010000000000

//! Level detection polarity is negative detecting condition is AND 3 axes.
#define CFG_LEVEL_DETECTION_AND     (uint64_t)0x0000000100000000

//
//! The macro below is used for
//! Function: MMA7455_IntFlagClear
//! Param   : IntID
//  
//! Internal use, NOT for user. 
#define INT_ID_M                    0x03

#define INT_ID_1                    0x01
#define INT_ID_2                    0x02  

//*****************************************************************************
//
//! \addtogroup MMA7455_API
//! @{
//
//*****************************************************************************

Result MMA7455_Init(void);
Result MMA7455_ReadAccData_8(uint32_t Axis, int8_t * DataRecvBuf);
Result MMA7455_ReadAccData_10(uint32_t Axis, int16_t * DataRecvBuf);
Result MMA7455_EventCheck(uint16_t Event);
Result MMA7455_GetID(uint8_t * ID);
Result MMA7455_OffSetWrite(uint32_t Axis, uint16_t OffSet);
Result MMA7455_Cfg(uint64_t Cfg);
Result MMA7455_IntFlagClear(uint8_t IntID);
Result MMA7455_LevelThresHoldSet(uint8_t ThresHold);
Result MMA7455_PulseThresHoldSet(uint8_t ThresHold);
Result MMA7455_PulseDurationSet(uint8_t Dur);
Result MMA7455_LatencyTimeSet(uint8_t Latency);
Result MMA7455_WindowsSet(uint8_t Windows);
Result MMA7455_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf);
Result MMA7455_RegWriteByte(uint8_t RegAddr, uint8_t Data);

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

#endif // __MMA7455_H__

