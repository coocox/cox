//*****************************************************************************
//
//! \file HMC5883L.h
//! \brief Prototypes for the HMC5883L Driver.
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
#ifndef __HMC5883L_H__
#define __HMC5883L_H__

#include <stdint.h>
#include <stdio.h>

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
#include "xhw_uart.h"
#include "xuart.h"

#include "hw_HMC5883L.h"

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
//! \addtogroup HMC5883L_Hardware_Information Lower hardware information.
//! \brief I2C communcation port information, you must change this macro
//! according your hardware.
//! @{
//
//*****************************************************************************

//! HMC5883L Salve Address 7-bit mode
//! \b NOTE: R/W bit is EXCLUDE from this address
#define HMC5883L_I2C_ADDR       0x1E

//! SCK Pin
#define HMC5883L_PIN_I2C_SCK    PB6
#define HMC5883L_I2C_SCK        I2C1SCK

//! SDA Pin
#define HMC5883L_PIN_I2C_SDA    PB7
#define HMC5883L_I2C_SDA        I2C1SDA

//! I2C Base Address
#define HMC5883L_PIN_I2C_PORT   I2C1_BASE
#define HMC5883L_I2C_GPIO       SYSCTL_PERIPH_IOPB

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

#define CFG_A_M                 ((uint32_t)0x10000000)
#define CFG_B_M                 ((uint32_t)0x20000000)
#define MODE_M                  ((uint32_t)0x40000000)

//! The following paramters is used for  HMC5883L_Cfg
#define SAMPLE_1                ((uint32_t)0x10006000)
#define SAMPLE_2                ((uint32_t)0x10004020)
#define SAMPLE_4                ((uint32_t)0x10002040)
#define SAMPLE_8                ((uint32_t)0x10000060)
                                               
#define DATA_RATE_0_75          ((uint32_t)0x10001C00)        
#define DATA_RATE_1_5           ((uint32_t)0x10001804)        
#define DATA_RATE_3             ((uint32_t)0x10001408)                    
#define DATA_RATE_7_5           ((uint32_t)0x1000100C)                    
#define DATA_RATE_15            ((uint32_t)0x10000C10)                    
#define DATA_RATE_30            ((uint32_t)0x10000814)                    
#define DATA_RATE_75            ((uint32_t)0x10000418)                    

#define GAIN_1370               ((uint32_t)0x20000000)
#define GAIN_1090               ((uint32_t)0x20200000)
#define GAIN_820                ((uint32_t)0x20400000)
#define GAIN_660                ((uint32_t)0x20600000)
#define GAIN_440                ((uint32_t)0x20800000)
#define GAIN_390                ((uint32_t)0x20A00000)
#define GAIN_330                ((uint32_t)0x20C00000)
#define GAIN_230                ((uint32_t)0x20E00000)

#define MODE_CONT               ((uint32_t)0x40000000)
#define MODE_SIG                ((uint32_t)0x41000000)
#define MODE_IDLE               ((uint32_t)0x42000000)


//*****************************************************************************
//
//! \addtogroup HMC5883L_API
//! @{
//
//*****************************************************************************

extern Result HMC5883L_Init(void);
extern Result HMC5883L_RegWriteByte(uint8_t RegAddr, uint8_t Data);
extern Result HMC5883L_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf);
extern Result HMC5883L_Cfg(uint32_t Cfg);
extern Result HMC5883L_StatusCheck(uint8_t Flag);
extern Result HMC5883L_DataGet(int16_t * pDataX, int16_t * pDataY, int16_t * pDataZ);
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

#endif // __HMC5883L_H__

