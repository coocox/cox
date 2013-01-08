//*****************************************************************************
//
//! \file LIS302DL.h
//! \brief Prototypes for the LIS302DL Driver.
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
#ifndef __LIS302DL_H__
#define __LIS302DL_H__

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

#include "hw_LIS302DL.h"

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
//! Select LIS302DL Communication type I2C/SPI
//! you can only select a communication type at a time
//! \b NOTE: Now the dirver support I2C only
#define LIS302DL_PORT_I2C
//#define LIS302DL_PORT_SPI

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
//! \addtogroup LIS302DL_Hardware_Information
//! @{
//
//*****************************************************************************

//! LIS302 Salve Address 7-bit mode
//! \b NOTE: R/W bit is EXCLUDE from this address
#define LIS302DL_I2C_ADDR       0x1C

//! SCK Pin
#define LIS302DL_PIN_I2C_SCK    PB6
#define LIS302DL_I2C_SCK        I2C1SCK

//! SDA Pin
#define LIS302DL_PIN_I2C_SDA    PB7
#define LIS302DL_I2C_SDA        I2C1SDA

//! I2C Base Address
#define LIS302DL_PIN_I2C_PORT   I2C1_BASE
#define LIS302DL_I2C_GPIO       SYSCTL_PERIPH_IOPB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//! Macros below is uesd for LIS302DLCfg
#define LIS302DL_CFG_MASK       ((uint64_t)0x00003FFFFFFFFFFF)

#define LIS302DL_REG_1_MASK     ((uint64_t)0x000000000000FFFF)
#define LIS302DL_REG_2_MASK     ((uint64_t)0x00000000FFFF0000)
#define LIS302DL_REG_3_MASK     ((uint64_t)0x0000FFFF00008000)

#define LIS302DL_REG1_SET_S     0
#define LIS302DL_REG1_UNSET_S   8
#define LIS302DL_REG2_SET_S     16
#define LIS302DL_REG2_UNSET_S   24
#define LIS302DL_REG3_SET_S     32
#define LIS302DL_REG3_UNSET_S   40

// Byte 0 Set
// Byte 1 Unset
#define LIS302DL_CLK_100K       ((uint64_t)0x0000000000008000)
#define LIS302DL_CLK_400K       ((uint64_t)0x0000000000000080)
#define LIS302DL_SCALE_2G       ((uint64_t)0x0000000000002000)
#define LIS302DL_SCALE_8G       ((uint64_t)0x0000000000000020)
#define LIS302DL_SELF_TEST_EN   ((uint64_t)0x0000000000000018)
#define LIS302DL_SELF_TEST_DIS  ((uint64_t)0x0000000000001800)
#define LIS302DL_X_EN           ((uint64_t)0x0000000000000001)
#define LIS302DL_X_DIS          ((uint64_t)0x0000000000000100)
#define LIS302DL_Y_EN           ((uint64_t)0x0000000000000002)
#define LIS302DL_Y_DIS          ((uint64_t)0x0000000000000200)
#define LIS302DL_Z_EN           ((uint64_t)0x0000000000000004)
#define LIS302DL_Z_DIS          ((uint64_t)0x0000000000000400)

// Byte 2 Set
// Byte 3 Unset
#define LIS302DL_HP_COEFF_MASK  ((uint64_t)0x0000000003030000)

#define LIS302DL_SPI_3_WIRE     ((uint64_t)0x0000000000800000)
#define LIS302DL_SPI_4_WIRE     ((uint64_t)0x0000000080000000)
#define LIS302DL_CONTENT_NORMAL ((uint64_t)0x0000000040000000)
#define LIS302DL_CONTENT_REBOOT ((uint64_t)0x0000000000400000)
#define LIS302DL_FILTER_EN      ((uint64_t)0x0000000000100000)
#define LIS302DL_FILTER_DIS     ((uint64_t)0x0000000010000000)
#define LIS302DL_HP_WU1_EN      ((uint64_t)0x0000000000040000)
#define LIS302DL_HP_WU1_DIS     ((uint64_t)0x0000000004000000)
#define LIS302DL_HP_WU2_EN      ((uint64_t)0x0000000000080000)
#define LIS302DL_HP_WU2_DIS     ((uint64_t)0x0000000008000000)
#define LIS302DL_HP_COEFF_8X    ((uint64_t)0x0000000003000000)
#define LIS302DL_HP_COEFF_4X    ((uint64_t)0x0000000002010000)
#define LIS302DL_HP_COEFF_2X    ((uint64_t)0x0000000001020000)
#define LIS302DL_HP_COEFF_1X    ((uint64_t)0x0000000000030000)

// Byte 4 Set
// Byte 5 Unset
#define LIS302DL_INT1_MASK      ((uint64_t)0x0000383800000000)
#define LIS302DL_INT2_MASK      ((uint64_t)0x0000070700000000)

#define LIS302DL_INT_HIGH       ((uint64_t)0x0000800000000000)
#define LIS302DL_INT_LOW        ((uint64_t)0x0000008000000000)
#define LIS302DL_INT_PAD_PP     ((uint64_t)0x0000400000000000)
#define LIS302DL_INT_PAD_OD     ((uint64_t)0x0000004000000000)
#define LIS302DL_INT1_GND       ((uint64_t)0x0000380000000000)
#define LIS302DL_INT1_FF_WU_1   ((uint64_t)0x0000300800000000)
#define LIS302DL_INT1_FF_WU_2   ((uint64_t)0x0000281000000000)
#define LIS302DL_INT1_FF_WU_1_2 ((uint64_t)0x0000201800000000)
#define LIS302DL_INT1_DATA_RDY  ((uint64_t)0x0000182000000000)
#define LIS302DL_INT1_CLICK_INT ((uint64_t)0x0000003800000000)
#define LIS302DL_INT2_GND       ((uint64_t)0x0000070000000000)
#define LIS302DL_INT2_FF_WU_1   ((uint64_t)0x0000060100000000)
#define LIS302DL_INT2_FF_WU_2   ((uint64_t)0x0000050200000000)
#define LIS302DL_INT2_FF_WU_1_2 ((uint64_t)0x0000040300000000)
#define LIS302DL_INT2_DATA_RDY  ((uint64_t)0x0000030400000000)
#define LIS302DL_INT2_CLICK_INT ((uint64_t)0x0000000700000000)

//
//! Macros below is uesd for LIS302DLAccDataRead
//
#define AXIS_X                  OUT_X
#define AXIS_Y                  OUT_Y
#define AXIS_Z                  OUT_Z

//
//! Macros below is uesd for LIS302DLWUFFCfg
//
#define WUFF_CFG_MASK           0x3100FFFF

#define WUFF_INT_MASK           0x00010000

#define WUFF1_INT_EVENT_AND     0x00000080
#define WUFF1_INT_LATCH_EN      0x00000040
#define WUFF1_INT_Z_HIGH_EN     0x00000020
#define WUFF1_INT_Z_LOW_EN      0x00000010
#define WUFF1_INT_Y_HIGH_EN     0x00000008
#define WUFF1_INT_Y_LOW_EN      0x00000004
#define WUFF1_INT_X_HIGH_EN     0x00000002
#define WUFF1_INT_X_LOW_EN      0x00000001

#define WUFF1_INT_EVENT_OR      0x00008000
#define WUFF1_INT_LATCH_DIS     0x00004000
#define WUFF1_INT_Z_HIGH_DIS    0x00002000
#define WUFF1_INT_Z_LOW_DIS     0x00001000
#define WUFF1_INT_Y_HIGH_DIS    0x00000800
#define WUFF1_INT_Y_LOW_DIS     0x00000400
#define WUFF1_INT_X_HIGH_DIS    0x00000200
#define WUFF1_INT_X_LOW_DIS     0x00000100

#define WUFF2_INT_EVENT_AND     0x00010080
#define WUFF2_INT_LATCH_EN      0x00010040
#define WUFF2_INT_Z_HIGH_EN     0x00010020
#define WUFF2_INT_Z_LOW_EN      0x00010010
#define WUFF2_INT_Y_HIGH_EN     0x00010008
#define WUFF2_INT_Y_LOW_EN      0x00010004
#define WUFF2_INT_X_HIGH_EN     0x00010002
#define WUFF2_INT_X_LOW_EN      0x00010001

#define WUFF2_INT_EVENT_OR      0x00018000
#define WUFF2_INT_LATCH_DIS     0x00014000
#define WUFF2_INT_Z_HIGH_DIS    0x00012000
#define WUFF2_INT_Z_LOW_DIS     0x00011000
#define WUFF2_INT_Y_HIGH_DIS    0x00010800
#define WUFF2_INT_Y_LOW_DIS     0x00010400
#define WUFF2_INT_X_HIGH_DIS    0x00010200
#define WUFF2_INT_X_LOW_DIS     0x00010100

#define WUFF_CNT_MASK           0x30000000
#define WUFF_CNT_MODE_MASK      0x01000000
#define WUFF1_CNT_RESET         0x10000000
#define WUFF1_CNT_DEC           0x11000000
#define WUFF2_CNT_RESET         0x20000000
#define WUFF2_CNT_DEC           0x21000000

//
//! Macros below is uesd for LIS302DLWUFFEventCheck
//
#define WUFF_INT_EVENT_MASK     0x000100FF

#define WUFF1_INT_EVENT_ANY     0x00000040
#define WUFF1_INT_EVENT_ZH      0x00000020
#define WUFF1_INT_EVENT_ZL      0x00000010
#define WUFF1_INT_EVENT_YH      0x00000008
#define WUFF1_INT_EVENT_YL      0x00000004
#define WUFF1_INT_EVENT_XH      0x00000002
#define WUFF1_INT_EVENT_XL      0x00000001

#define WUFF2_INT_EVENT_ANY     0x00010040
#define WUFF2_INT_EVENT_ZH      0x00010020
#define WUFF2_INT_EVENT_ZL      0x00010010
#define WUFF2_INT_EVENT_YH      0x00010008
#define WUFF2_INT_EVENT_YL      0x00010004
#define WUFF2_INT_EVENT_XH      0x00010002
#define WUFF2_INT_EVENT_XL      0x00010001


//
//! Macros below is uesd for LIS302DLWUFFThresHold
//
#define WUFF_ID_1               0x0000000
#define WUFF_ID_2               0x0000001

//
//! Macros below is uesd for LIS302DLClickCfg
//
#define CLK_INT_MASK            0x0000FFFF

#define CLK_INT_REQ_LATCH_EN    0x00000040
#define CLK_INT_DBL_Z_EN        0x00000020
#define CLK_INT_SIG_Z_EN        0x00000010
#define CLK_INT_DBL_Y_EN        0x00000008
#define CLK_INT_SIG_Y_EN        0x00000004
#define CLK_INT_DBL_X_EN        0x00000002
#define CLK_INT_SIG_X_EN        0x00000001

#define CLK_INT_REQ_LATCH_DIS   0x00004000
#define CLK_INT_DBL_Z_DIS       0x00002000
#define CLK_INT_SIG_Z_DIS       0x00001000
#define CLK_INT_DBL_Y_DIS       0x00000800
#define CLK_INT_SIG_Y_DIS       0x00000400
#define CLK_INT_DBL_X_DIS       0x00000200
#define CLK_INT_SIG_X_DIS       0x00000100


//
//! Macros below is uesd for LIS302DLClickEventCheck
//

#define CLICK_EVENT_MASK        0x7F

#define CLICK_EVENT_SIG_X       0x01
#define CLICK_EVENT_DBL_X       0x02
#define CLICK_EVENT_SIG_Y       0x04
#define CLICK_EVENT_DBL_Y       0x08
#define CLICK_EVENT_SIG_Z       0x10
#define CLICK_EVENT_DBL_Z       0x20
#define CLICK_EVENT_ANY         0x40


//
//! Macros below is uesd for LIS302DLClickThresholdSet
//
#define THRESHOLD_RESET_ALL     0x00000000

#define THRESHOLD_X_MASK        0x0000000F
#define THRESHOLD_X_0_5_G       0x00000001
#define THRESHOLD_X_1_0_G       0x00000002
#define THRESHOLD_X_1_5_G       0x00000003
#define THRESHOLD_X_2_0_G       0x00000004
#define THRESHOLD_X_2_5_G       0x00000005
#define THRESHOLD_X_3_0_G       0x00000006
#define THRESHOLD_X_3_5_G       0x00000007
#define THRESHOLD_X_4_0_G       0x00000008
#define THRESHOLD_X_4_5_G       0x00000009
#define THRESHOLD_X_5_0_G       0x0000000A
#define THRESHOLD_X_5_5_G       0x0000000B
#define THRESHOLD_X_6_0_G       0x0000000C
#define THRESHOLD_X_6_5_G       0x0000000D
#define THRESHOLD_X_7_0_G       0x0000000E
#define THRESHOLD_X_7_5_G       0x0000000F


#define THRESHOLD_Y_MASK        0x000000F0
#define THRESHOLD_Y_0_5_G       0x00000010
#define THRESHOLD_Y_1_0_G       0x00000020
#define THRESHOLD_Y_1_5_G       0x00000030
#define THRESHOLD_Y_2_0_G       0x00000040
#define THRESHOLD_Y_2_5_G       0x00000050
#define THRESHOLD_Y_3_0_G       0x00000060
#define THRESHOLD_Y_3_5_G       0x00000070
#define THRESHOLD_Y_4_0_G       0x00000080
#define THRESHOLD_Y_4_5_G       0x00000090
#define THRESHOLD_Y_5_0_G       0x000000A0
#define THRESHOLD_Y_5_5_G       0x000000B0
#define THRESHOLD_Y_6_0_G       0x000000C0
#define THRESHOLD_Y_6_5_G       0x000000D0
#define THRESHOLD_Y_7_0_G       0x000000E0
#define THRESHOLD_Y_7_5_G       0x000000F0


#define THRESHOLD_Z_MASK        0x00000F00
#define THRESHOLD_Z_0_5_G       0x00000100
#define THRESHOLD_Z_1_0_G       0x00000200
#define THRESHOLD_Z_1_5_G       0x00000300
#define THRESHOLD_Z_2_0_G       0x00000400
#define THRESHOLD_Z_2_5_G       0x00000500
#define THRESHOLD_Z_3_0_G       0x00000600
#define THRESHOLD_Z_3_5_G       0x00000700
#define THRESHOLD_Z_4_0_G       0x00000800
#define THRESHOLD_Z_4_5_G       0x00000900
#define THRESHOLD_Z_5_0_G       0x00000A00
#define THRESHOLD_Z_5_5_G       0x00000B00
#define THRESHOLD_Z_6_0_G       0x00000C00
#define THRESHOLD_Z_6_5_G       0x00000D00
#define THRESHOLD_Z_7_0_G       0x00000E00
#define THRESHOLD_Z_7_5_G       0x00000F00


//*****************************************************************************
//
//! \addtogroup LIS302DL_API
//! @{
//
//*****************************************************************************


extern Result LIS302DLInit(void);
extern Result LIS302DLRegWriteByte(uint8_t RegAddr, uint8_t Data);
extern Result LIS302DLRegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf);
extern Result LIS302DLCfg(uint64_t Cfg);
extern Result LIS302DLHPFilterReset(void);
extern Result LIS302DLAccDataRead(uint8_t Axis, uint8_t * DataRecvBuf);
extern Result LIS302DLIDGet(uint8_t * ID);
extern Result LIS302DLStart(void);
extern Result LIS302DLStop(void);
extern Result LIS302DLWUFFCfg(uint32_t Cfg);
extern Result LIS302DLWUFFEventCheck(uint32_t Event);
extern Result LIS302DLWUFFThresHoldSet(uint8_t ID, uint8_t ThresHold);
extern Result LIS302DLWUFFDurValueSet(uint8_t ID, uint8_t DurValue);
extern Result LIS302DLClickCfg(uint32_t Cfg);
extern Result LIS302DLClickEventCheck(uint8_t Event);
extern Result LIS302DLClickThresholdSet(uint32_t ThresHold);
extern Result LIS302DLClickTimeLimitSet(uint8_t TimeLimit);
extern Result LIS302DLClickLatencySet(uint8_t Latency);
extern Result LIS302DLClickWindowSet(uint8_t Window);


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

#endif // __LIS302DL_H__

