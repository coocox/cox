//*****************************************************************************
//
//! \file MMA8451.h
//! \brief Prototypes for the MMA8451 Driver.
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
#ifndef __MMA8451_H__
#define __MMA8451_H__

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

#include "hw_MMA8451.h"

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
//! \addtogroup MMA8451
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

#define AXIS_X                   ((uint8_t) 0x00)
#define AXIS_Y                   ((uint8_t) 0x01)
#define AXIS_Z                   ((uint8_t) 0x02)

//*****************************************************************************
//
//! \addtogroup MMA8451_Hardware_Information Lower hardware information.
//! \brief I2C communcation port information, you must change this macro
//! according your hardware.
//! @{
//
//*****************************************************************************

//! Salve Address 7-bit mode
//! \b NOTE: R/W bit is EXCLUDE from this address
#define MMA8451_I2C_ADDR       0x1C

//! SCK Pin
#define MMA8451_PIN_I2C_SCK    PB6
#define MMA8451_I2C_SCK        I2C1SCK

//! SDA Pin
#define MMA8451_PIN_I2C_SDA    PB7
#define MMA8451_I2C_SDA        I2C1SDA

//! I2C Base Address
#define MMA8451_PIN_I2C_PORT   I2C1_BASE
#define MMA8451_I2C_GPIO       SYSCTL_PERIPH_IOPB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//used for 
//MMA8451_DataStatusCheck
#define AXIS_XYZ_OW             ((uint8_t) 0x80)
#define AXIS_X_OW               ((uint8_t) 0x40)
#define AXIS_Y_OW               ((uint8_t) 0x20)
#define AXIS_Z_OW               ((uint8_t) 0x10)
#define AXIS_XYZ_DR             ((uint8_t) 0x08)
#define AXIS_X_DR               ((uint8_t) 0x04)
#define AXIS_Y_DR               ((uint8_t) 0x02)
#define AXIS_Z_DR               ((uint8_t) 0x01) 


//MMA8451_IntStatusCheck
#define EVENT_ASLP              ((uint8_t) 0x80)
#define EVENT_FIFO              ((uint8_t) 0x40)
#define EVENT_TRANS             ((uint8_t) 0x20)
#define EVENT_LNDPRT            ((uint8_t) 0x10)
#define EVENT_PULSE             ((uint8_t) 0x08)
#define EVENT_FF_MT             ((uint8_t) 0x04)
#define EVENT_DRDY              ((uint8_t) 0x01)


//MMA8451_IntCfg
#define CTRL_REG3_MASK          ((uint64_t) 0x000000000000FFFF)
#define CTRL_REG4_MASK          ((uint64_t) 0x00000000FFFF0000)
#define CTRL_REG5_MASK          ((uint64_t) 0x0000FFFF00000000)

#define WAKE_TRANS_EN           ((uint64_t) 0x0000000000000040)
#define WAKE_TRANS_DIS          ((uint64_t) 0x0000000000004000)

#define WAKE_LP_EN              ((uint64_t) 0x0000000000000020)
#define WAKE_LP_DIS             ((uint64_t) 0x0000000000002000)

#define WAKE_PULSE_EN           ((uint64_t) 0x0000000000000010)
#define WAKE_PULSE_DIS          ((uint64_t) 0x0000000000001000)

#define WAKE_FFMT_EN            ((uint64_t) 0x0000000000000008)
#define WAKE_FFMT_DIS           ((uint64_t) 0x0000000000000800)

#define ACTIVE_HIGH             ((uint64_t) 0x0000000000000002)
#define ACTIVE_LOW              ((uint64_t) 0x0000000000000200)

#define PAD_OD                  ((uint64_t) 0x0000000000000001)
#define PAD_PP                  ((uint64_t) 0x0000000000000100)

#define INT_ASLP_EN             ((uint64_t) 0x0000000000800000)
#define INT_ASLP_DIS            ((uint64_t) 0x0000000080000000)

#define INT_FIFO_EN             ((uint64_t) 0x0000000000400000)
#define INT_FIFO_DIS            ((uint64_t) 0x0000000040000000)

#define INT_TRANS_EN            ((uint64_t) 0x0000000000200000)
#define INT_TRANS_DIS           ((uint64_t) 0x0000000020000000)

#define INT_LP_EN               ((uint64_t) 0x0000000000100000)
#define INT_LP_DIS              ((uint64_t) 0x0000000010000000)

#define INT_PULSE_EN            ((uint64_t) 0x0000000000080000)
#define INT_PULSE_DIS           ((uint64_t) 0x0000000008000000)

#define INT_FFMT_EN             ((uint64_t) 0x0000000000040000)
#define INT_FFMT_DIS            ((uint64_t) 0x0000000004000000)

#define INT_DRDY_EN             ((uint64_t) 0x0000000000010000)
#define INT_DRDY_DIS            ((uint64_t) 0x0000000001000000)

#define INT_ASLP_INT1           ((uint64_t) 0x0000008000000000)
#define INT_ASLP_INT2           ((uint64_t) 0x0000800000000000)

#define INT_FIFO_INT1           ((uint64_t) 0x0000004000000000)
#define INT_FIFO_INT2           ((uint64_t) 0x0000400000000000)

#define INT_TRANS_INT1          ((uint64_t) 0x0000002000000000)
#define INT_TRANS_INT2          ((uint64_t) 0x0000200000000000)

#define INT_LP_INT1             ((uint64_t) 0x0000001000000000)
#define INT_LP_INT2             ((uint64_t) 0x0000100000000000)

#define INT_PULSE_INT1          ((uint64_t) 0x0000000800000000)
#define INT_PULSE_INT2          ((uint64_t) 0x0000080000000000)

#define INT_FFMT_INT1           ((uint64_t) 0x0000000400000000)
#define INT_FFMT_INT2           ((uint64_t) 0x0000040000000000)

#define INT_DRDY_INT1           ((uint64_t) 0x0000000100000000)
#define INT_DRDY_INT2           ((uint64_t) 0x0000010000000000)

//MMA8451_Cfg
#define REG_1_MASK              ((uint64_t) 0x00000000FFFF0000)
#define REG_2_MASK              ((uint64_t) 0x000000000000FFFF)
#define DATA_CFG_1_MASK         ((uint64_t) 0x0000FFFF00000000)
#define HPF_CFG_MASK            ((uint64_t) 0xFFFF000000000000)

#define SLEEP_RATE_MASK         ((uint64_t) 0x00000000C0C00000)
#define NORMAL_RATE_MASK        ((uint64_t) 0x0000000038380000)
#define SLEEP_MODE_MASK         ((uint64_t) 0x0000000000001818)
#define ACTIVE_MODE_MASK        ((uint64_t) 0x0000000000000303)

#define HPF_CUTOFF_MASK         ((uint64_t) 0x0303000000000000)
#define RANGE_MASK              ((uint64_t) 0x0000030300000000)

#define SLEEP_RATE_50_HZ        ((uint64_t) 0x00000000C0000000)
#define SLEEP_RATE_12_5_HZ      ((uint64_t) 0x0000000080400000)
#define SLEEP_RATE_6_25_HZ      ((uint64_t) 0x0000000040800000)
#define SLEEP_RATE_1_56_HZ      ((uint64_t) 0x0000000000C00000)

#define NORMAL_RATE_800_HZ      ((uint64_t) 0x0000000038000000)
#define NORMAL_RATE_400_HZ      ((uint64_t) 0x0000000030080000)
#define NORMAL_RATE_200_HZ      ((uint64_t) 0x0000000028100000)
#define NORMAL_RATE_100_HZ      ((uint64_t) 0x0000000020180000)
#define NORMAL_RATE_50_HZ       ((uint64_t) 0x0000000018200000)
#define NORMAL_RATE_12_5_HZ     ((uint64_t) 0x0000000010280000)
#define NORMAL_RATE_6_25_HZ     ((uint64_t) 0x0000000008300000)
#define NORMAL_RATE_1_56_HZ     ((uint64_t) 0x0000000000380000)

#define LOW_NOISE_EN            ((uint64_t) 0x0000000000040000)
#define LOW_NOISE_DIS           ((uint64_t) 0x0000000004000000)

#define FAST_READ_EN            ((uint64_t) 0x0000000000020000)
#define FAST_READ_DIS           ((uint64_t) 0x0000000002000000)

#define SELFTEST_EN             ((uint64_t) 0x0000000000000080)
#define SELFTEST_DIS            ((uint64_t) 0x0000000000008000)

#define RESET_EN                ((uint64_t) 0x0000000000000040)
#define RESET_DIS               ((uint64_t) 0x0000000000004000)

#define SLEEP_MODE_NOR          ((uint64_t) 0x0000000000001800)
#define SLEEP_MODE_LNLP         ((uint64_t) 0x0000000000001008)
#define SLEEP_MODE_HR           ((uint64_t) 0x0000000000000810)
#define SLEEP_MODE_LP           ((uint64_t) 0x0000000000000018)

#define AUTO_SLEEP_EN           ((uint64_t) 0x0000000000000004)
#define AUTO_SLEEP_DIS          ((uint64_t) 0x0000000000000400)

#define ACTIVE_MODE_NOR         ((uint64_t) 0x0000000000000300)
#define ACTIVE_MODE_LNLP        ((uint64_t) 0x0000000000000201)
#define ACTIVE_MODE_HR          ((uint64_t) 0x0000000000000102)
#define ACTIVE_MODE_LP          ((uint64_t) 0x0000000000000003)

#define HPF_EN                  ((uint64_t) 0x0000001000000000)
#define HPF_DIS                 ((uint64_t) 0x0000100000000000)
#define RANGE_2G                ((uint64_t) 0x0000030000000000)
#define RANGE_4G                ((uint64_t) 0x0000020100000000)
#define RANGE_8G                ((uint64_t) 0x0000010200000000)

#define HPF_CUTOFF_8X           ((uint64_t) 0x0300000000000000)
#define HPF_CUTOFF_4X           ((uint64_t) 0x0201000000000000)
#define HPF_CUTOFF_2X           ((uint64_t) 0x0102000000000000)
#define HPF_CUTOFF_1X           ((uint64_t) 0x0003000000000000)

#define PULSE_HPF_EN            ((uint64_t) 0x2000000000000000)
#define PULSE_HPF_DIS           ((uint64_t) 0x0020000000000000)

#define PULSE_LPF_EN            ((uint64_t) 0x0010000000000000)
#define PULSE_LPF_DIS           ((uint64_t) 0x1000000000000000)


//MMA8451_PLCfg
#define PL_BK_CMP_MASK          ((uint32_t) 0x0000FFFF)
#define PL_THS_MASK             ((uint32_t) 0xFFFF0000)

#define PL_CNT_DEC              ((uint32_t) 0x00008000)
#define PL_CNT_RST              ((uint32_t) 0x00000080)

#define PL_EN                   ((uint32_t) 0x00000040)
#define PL_DIS                  ((uint32_t) 0x00004000)

#define PL_BKFR_65              ((uint32_t) 0x0000C000)
#define PL_BKFR_70              ((uint32_t) 0x00008040)
#define PL_BKFR_75              ((uint32_t) 0x00004080)
#define PL_BKFR_80              ((uint32_t) 0x000000C0)

#define PL_ZLOCK_14             ((uint32_t) 0x00000700)
#define PL_ZLOCK_18             ((uint32_t) 0x00000601)
#define PL_ZLOCK_21             ((uint32_t) 0x00000502)
#define PL_ZLOCK_25             ((uint32_t) 0x00000403)
#define PL_ZLOCK_29             ((uint32_t) 0x00000304)
#define PL_ZLOCK_33             ((uint32_t) 0x00000205)
#define PL_ZLOCK_37             ((uint32_t) 0x00000106)
#define PL_ZLOCK_42             ((uint32_t) 0x00000007)

#define PL_THRESHOLD_15         ((uint32_t) 0xC0380000)
#define PL_THRESHOLD_20         ((uint32_t) 0xB0480000)
#define PL_THRESHOLD_30         ((uint32_t) 0x98600000)
#define PL_THRESHOLD_35         ((uint32_t) 0x90680000)
#define PL_THRESHOLD_40         ((uint32_t) 0x80780000)
#define PL_THRESHOLD_45         ((uint32_t) 0x78800000)
#define PL_THRESHOLD_55         ((uint32_t) 0x60980000)
#define PL_THRESHOLD_60         ((uint32_t) 0x58A00000)
#define PL_THRESHOLD_70         ((uint32_t) 0x40B80000)
#define PL_THRESHOLD_75         ((uint32_t) 0x30C80000)

#define PL_HYS_0                ((uint32_t) 0x07000000)
#define PL_HYS_4                ((uint32_t) 0x06010000)
#define PL_HYS_7                ((uint32_t) 0x05020000)
#define PL_HYS_11               ((uint32_t) 0x04030000)
#define PL_HYS_14               ((uint32_t) 0x03040000)
#define PL_HYS_17               ((uint32_t) 0x02050000)
#define PL_HYS_21               ((uint32_t) 0x01060000)
#define PL_HYS_24               ((uint32_t) 0x00070000)


//MMA8451_FFMTStatusCheck
#define FFMT_EA                 ((uint8_t) 0x80)
#define FFMT_MOTION_Z           ((uint8_t) 0x20)
#define FFMT_POLARITY_Z         ((uint8_t) 0x10)
#define FFMT_MOTION_Y           ((uint8_t) 0x08)
#define FFMT_POLARITY_Y         ((uint8_t) 0x04)
#define FFMT_MOTION_X           ((uint8_t) 0x02)
#define FFMT_POLARITY_X         ((uint8_t) 0x01)


//MMA8451_FFMTCfg
#define FFMT_CFG_MASK           ((uint32_t) 0x0000FFFF)
#define FFTS_CNT_MASK           ((uint32_t) 0x80800000)

#define FFMT_INT_LATCH_EN       ((uint32_t) 0x00000080)
#define FFMT_INT_LATCH_DIS      ((uint32_t) 0x00008000)

#define FFMT_FREEFALL           ((uint32_t) 0x00004000)
#define FFMT_MOTION             ((uint32_t) 0x00000040)

#define FFMT_INT_Z_EN           ((uint32_t) 0x00000020)
#define FFMT_INT_Y_EN           ((uint32_t) 0x00000010)
#define FFMT_INT_X_EN           ((uint32_t) 0x00000008)

#define FFMT_INT_Z_DIS          ((uint32_t) 0x00002000)
#define FFMT_INT_Y_DIS          ((uint32_t) 0x00001000)
#define FFMT_INT_X_DIS          ((uint32_t) 0x00000800)

#define FFMT_CNT_DEC            ((uint32_t) 0x80000000)
#define FFMT_CNT_RST            ((uint32_t) 0x00800000)

// MMA8451_TransCfg
#define TS_EA                   ((uint8_t) 0x40)
#define TS_EVENT_Z              ((uint8_t) 0x20)
#define TS_POLARITY_Z           ((uint8_t) 0x10)
#define TS_EVENT_Y              ((uint8_t) 0x08)
#define TS_POLARITY_Y           ((uint8_t) 0x04)
#define TS_EVENT_X              ((uint8_t) 0x02)
#define TS_POLARITY_X           ((uint8_t) 0x01)

//MMA8451_PulseStatusCheck
#define PULSE_EA                ((uint8_t) 0x80)
#define PULSE_EVENT_Z           ((uint8_t) 0x40)
#define PULSE_EVENT_Y           ((uint8_t) 0x20)
#define PULSE_EVENT_X           ((uint8_t) 0x10)
#define PULSE_DOUBLE            ((uint8_t) 0x08)
#define PULSE_POL_Z             ((uint8_t) 0x04)
#define PULSE_POL_Y             ((uint8_t) 0x02)
#define PULSE_POL_X             ((uint8_t) 0x01)


//MMA8451_PulseCfg
#define DP_ABORT_EN             ((uint32_t) 0x0080)
#define DP_ABORT_DIS            ((uint32_t) 0x8000)

#define PULSE_INT_LATCH_EN      ((uint32_t) 0x0040)
#define PULSE_INT_LATCH_DIS     ((uint32_t) 0x4000)

#define PULSE_SGL_X_EN          ((uint32_t) 0x0001)
#define PULSE_SGL_Y_EN          ((uint32_t) 0x0004)
#define PULSE_SGL_Z_EN          ((uint32_t) 0x0010)

#define PULSE_SGL_X_DIS         ((uint32_t) 0x0100)
#define PULSE_SGL_Y_DIS         ((uint32_t) 0x0400)
#define PULSE_SGL_Z_DIS         ((uint32_t) 0x1000)

#define PULSE_DBL_X_EN          ((uint32_t) 0x0002)
#define PULSE_DBL_Y_EN          ((uint32_t) 0x0008)
#define PULSE_DBL_Z_EN          ((uint32_t) 0x0020)

#define PULSE_DBL_X_DIS         ((uint32_t) 0x0200)
#define PULSE_DBL_Y_DIS         ((uint32_t) 0x0800)
#define PULSE_DBL_Z_DIS         ((uint32_t) 0x2000)



#define TS_CFG_MASK             ((uint32_t) 0x0000FFFF)
#define TS_CNT_MASK             ((uint32_t) 0x80800000)

#define TS_INT_LATCH_EN         ((uint32_t) 0x00000010)
#define TS_INT_LATCH_DIS        ((uint32_t) 0x00001000)
#define TS_X_EN                 ((uint32_t) 0x00000002)
#define TS_Y_EN                 ((uint32_t) 0x00000004)
#define TS_Z_EN                 ((uint32_t) 0x00000008)
#define TS_X_DIS                ((uint32_t) 0x00000200)
#define TS_Y_DIS                ((uint32_t) 0x00000400)
#define TS_Z_DIS                ((uint32_t) 0x00000800)
#define TS_HPF_EN               ((uint32_t) 0x00000100)
#define TS_HPF_DIS              ((uint32_t) 0x00000001)

#define TS_CNT_DEC              ((uint32_t) 0x80000000)
#define TS_CNT_RST              ((uint32_t) 0x00800000)




//*****************************************************************************
//
//! \addtogroup MMA8451_API
//! @{
//
//*****************************************************************************

Result MMA8451_Init(void);
Result MMA8451_GetID(uint8_t * ID);
Result MMA8451_ReadAccData_8(uint8_t Axis, int8_t * DataRecvBuf);
Result MMA8451_ReadAccData_14(uint8_t Axis, int16_t * DataRecvBuf);
Result MMA8451_DataStatusCheck(uint8_t Flag);
Result MMA8451_IntStatusCheck(uint8_t Event);
Result MMA8451_Active(void);
Result MMA8451_Standby(void);
Result MMA8451_IntCfg(uint64_t Cfg);
Result MMA8451_Cfg(uint64_t Cfg);
Result MMA8451_PLCfg(uint32_t Cfg, uint32_t Angle, uint8_t Cnt);
Result MMA8451_FFMTStatusCheck(uint8_t Event);
Result MMA8451_FFMTCfg(uint32_t Cfg, uint8_t ThresHold, uint8_t Cnt);
Result MMA8451_TSStatusCheck(uint8_t Event);
Result MMA8451_TransCfg(uint32_t Cfg, uint8_t ThresHold, uint8_t Cnt);
Result MMA8451_PulseStatusCheck(uint8_t Event);
Result MMA8451_PulseCfg(uint32_t Cfg);
Result MMA8451_PulseThresHoldSet(uint8_t Axis, uint8_t ThresHold);
Result MMA8451_PulseLimitSet(uint8_t Limit);
Result MMA8451_PulseLatencySet(uint8_t Latency);
Result MMA8451_PulseWindowSet(uint8_t Window);
Result MMA8451_SleepCntSet(uint8_t Cnt);
Result MMA8451_OffSetWrite(uint32_t Axis, uint8_t OffSet);
Result MMA8451_RegWriteByte(uint8_t RegAddr, uint8_t Data);
Result MMA8451_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf);

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

#endif // __MMA8451_H__

