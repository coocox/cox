//*****************************************************************************
//
//! \file hw_LIS302DL.h
//! \brief header file of Driver for LIS302DL
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

#ifndef __HW_LIS302DL_H_
#define __HW_LIS302DL_H_

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
//! \addtogroup LIS302DL
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup LIS302DL Register description
//! @{
//
//*****************************************************************************


//
//! Device identification register(RO).
//! This register contains the device identifier that for LIS302DL is set to 3Bh.
//
#define WHO_AM_I                0x0F

//
//! LIS302DL Control Register(RW) 1
//
#define CTRL_REG1               0x20

//
//! DR bit
//! Allows to select the data rate at which acceleration samples are produced.
//! The default value is 0 which corresponds to a data-rate of 100Hz. By changing
//! the content of DR to ¡°1¡± the selected data-rate will be set equal to 400Hz.
//
#define CTRL_REG1_DR            0x80

//
//! PD bit
//! Allows to turn on the turn the device out of power-down mode.
//! The device is in powerdown mode when PD= ¡°0¡± (default value after boot).
//! The device is in normal mode when PD is set to 1.
//
#define CTRL_REG1_PD            0x40

//
//! Full Scale selection.
//! Default value: 0 (0: +/- 2g; 1: +/- 8g)
//
#define CTRL_REG1_FS            0x20

//
//! STP, STM
//! Is used to activate the self test function. When the bit is set to one,
//! an output change will occur to the device outputs  thus allowing to check
//! the functionality of the whole measurement chain.
//
#define CTRL_REG1_STP           0x10

//
//! STP, STM
//! Is used to activate the self test function. When the bit is set to one,
//! an output change will occur to the device outputs thus allowing to check the
//! functionality of the whole measurement chain.
//
#define CTRL_REG1_STM           0x08

//
//! Zen
//! enables the generation of Data Ready signal for Z-axis measurement channel
//! when set to 1. The default value is 1.
//
#define CTRL_REG1_Zen           0x04

//
//! Yen
//! enables the generation of Data Ready signal for Y-axis measurement channel
//! when set to 1. The default value is 1.
//
#define CTRL_REG1_Yen           0x02

//
//! Xen
//! enables the generation of Data Ready signal for X-axis measurement channel
//! when set to 1. The default value is 1.
//
#define CTRL_REG1_Xen           0x01


//
//! LIS302DL Control Register(RW) 2
//
#define CTRL_REG2               0x21

//! SIM
//! selects the SPI Serial Interface Mode. When SIM is ¡®0¡¯ (default value)
//! the 4-wire interface mode is selected. The data coming from the device are
//! sent to SDO pad. In 3-wire interface mode output data are sent to SDA_SDI pad.
#define   CTRL_REG2_SIM         0x80

//! BOOT
//! Is used to refresh the content of internal registers stored in the flash
//! memory block. At the device power up the content of the flash memory block
//! is transferred to the internal registers related to trimming functions to permit
//! a good behavior of the device itself.  If for any reason the content of trimming
//! registers was changed it is sufficient to use this bit to restore correct values.
//! When BOOT bit is set to ¡®1¡¯ the content of internal flash is copied inside
//! corresponding internal registers and it is used to calibrate the device.
//! These values are factory trimmed and they are different for every accelerometer.
//! They permit a good behavior of the device and normally they have not to be changed.
//! At the end of the boot process the BOOT bit is set again to ¡®0¡¯.
#define   CTRL_REG2_BOOT        0x40

//
//! FDS
//! enables (FDS=1) or bypass (FDS=0) the high pass filter in the signal chain of
//the sensor
//
#define   CTRL_REG2_FDS         0x10


//
//! High Pass filter enabled for Free-Fall/Wake-Up #2
//! Default value: 0 (0: filter bypassed; 1: filter enabled)
//
#define   CTRL_REG2_HP_FF_WU2   0x08

//
//! High Pass filter enabled for Free-Fall/Wake-Up #1.
//! Default value: 0 (0: filter bypassed; 1: filter enabled)
//
#define   CTRL_REG2_HP_FF_WU1   0x04

//
//! HP_coeff[2:1]. These bits are used to configure high-pass filter cut-off frequency ft.
//!
//!    |-----------------------------------------------------------------|
//!    |     HP_coeff2,1            ft(Hz)              ft(Hz)           |
//!    |                          (DR=100 Hz)        (DR=400 Hz)         |
//!    |-----------------------------------------------------------------|
//!    |        00         |         2           |        8              |
//!    |-----------------------------------------------------------------|
//!    |        01         |         1           |        4              |
//!    |-----------------------------------------------------------------|
//!    |        10         |         0.5         |        2              |
//!    |-----------------------------------------------------------------|
//!    |        11         |         0.25        |        1              |
//!    |-----------------------------------------------------------------|
//
#define   CTRL_REG2_HP_coeff2   0x02
#define   CTRL_REG2_HP_coeff1   0x01

//
//! LIS302DL Control Register(RW) 3
//
#define CTRL_REG3               0x22

//
//! Interrupt active high/low.
//! Default value 0.  (0: active high; 1: active low)
//
#define CTRL_REG3_IHL           0x80

//
//! Push-pull/Open Drain selection on interrupt pad.
//! Default value 0.  (0: push-pull; 1: open drain)
//
#define CTRL_REG3_PP_OD         0x40

//
//! Data Signal on Int2 pad control bits. Default value 000.(see table above)
//!
//!      ------------------------------------------------------------------
//!      |       Table 25. CTRL_REG3 (22h) truth table                    |
//!      +----------------------------------------------------------------+
//!      |    I2_CFG2    | I2_CFG1    | I2_CFG0    |   Int2 Pad           |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     0      |     0      |    GND               |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     0      |     1      |    FF_WU_1           |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     1      |     0      |    FF_WU_2           |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     1      |     1      |  FF_WU_1 or FF_WU_2  |
//!      |---------------|------------|------------|----------------------|
//!      |        1      |     0      |     0      |    Data ready        |
//!      |---------------|------------|------------|----------------------|
//!      |        1      |     1      |     1      |  Click interrupt     |
//!      +----------------------------------------------------------------+
//
#define CTRL_REG3_I2CFG2        0x20
#define CTRL_REG3_I2CFG1        0x10
#define CTRL_REG3_I2CFG0        0x08

//
//! Data Signal on Int1 pad control bits. Default value 000. (see table above)
//!
//!      ------------------------------------------------------------------
//!      |       Table 25. CTRL_REG3 (22h) truth table                    |
//!      +----------------------------------------------------------------+
//!      |    I1_CFG2    | I1_CFG1    | I1_CFG0    |   Int1Pad            |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     0      |     0      |    GND               |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     0      |     1      |    FF_WU_1           |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     1      |     0      |    FF_WU_2           |
//!      |---------------|------------|------------|----------------------|
//!      |        0      |     1      |     1      |  FF_WU_1 or FF_WU_2  |
//!      |---------------|------------|------------|----------------------|
//!      |        1      |     0      |     0      |    Data ready        |
//!      |---------------|------------|------------|----------------------|
//!      |        1      |     1      |     1      |  Click interrupt     |
//!      +----------------------------------------------------------------+
//
#define CTRL_REG3_I1CFG2        0x04
#define CTRL_REG3_I1CFG1        0x02
#define CTRL_REG3_I1CFG0        0x01


//
//! Dummy register.
//! Reading at this address zeroes instantaneously the content of the internal
//! high pass-filter. If the high pass filter is enabled all three axes are
//! instantaneously set to 0g.  This allows to overcome the settling time of the
//! high pass filter.
//
#define HP_FILTER_RESET         0x23

//
//! LIS302DL Status Register(RW)
//
#define STATUS_REG              0x27

//
//! X, Y and Z axis data overrun. Default value: 0
//! 0: no overrun has occurred;
//! 1:new data has over written the previous one before it was read
//
#define STATUS_REG_ZXYOR        0x80

//
//! Z axis data overrun. Default value: 0
//! 0: no overrun has occurred;
//! 1: a new/data for the Z-axis has overwritten the previous one
//
#define STATUS_REG_ZOR          0x40

//
//! Y axis data overrun. Default value: 0
//! 0: no overrun has occurred;
//! 1: a new data for the Y-axis has overwritten the previous one
//
#define STATUS_REG_YOR          0x20

//
//! X axis data overrun. Default value: 0
//! 0: no overrun has occurred;
//! 1: a new data for the X-axis has overwritten the previous one
//
#define STATUS_REG_XOR          0x10

//
//! X, Y and Z axis new data available. Default value: 0
//! 0: a new set of data is not yet available;
//! 1: a new set of data is available
//
#define STATUS_REG_ZYXDA        0x08

//
//! Z axis new data available. Default value: 0
//! 0: a new data for the Z-axis is not yet available;
//! 1: a new data for the Z-axis is available
//
#define STATUS_REG_ZDA          0x04

//
//! Y axis new data available. Default value: 0
//! 0: a new data for the Y-axis is not yet available;
//! 1: a new data for the Y-axis is available
//
#define STATUS_REG_YDA          0x02

//
//! X axis new data available. Default value: 0
//! 0: a new data for the X-axis is not yet available;
//! 1: a new data for the X-axis is available
//
#define STATUS_REG_XDA          0x01


//
//! X axis output data register(RO)
//
#define OUT_X                   0x29

//
//! Y axis output data register(RO)
//
#define OUT_Y                   0x2b

//
//! Z axis output data register(RO)
//
#define OUT_Z                   0x2d

//
//! LIS302DL Free-Fall/Wake-UP Configure Register 1/2
//
#define FF_WU_CFG_1             0x30
#define FF_WU_CFG_2             0x34

//
//! And/or combination of Interrupt events. Default value: 0
//! 0: OR combination of interrupt events;
//! 1: AND combination of interrupt events
//
#define FF_WU_CFG_AOI           0x80

//
//! Latch Interrupt request into FF_WU_SRC reg with the FF_WU_SRC reg cleared by
//! reading FF_WU_SRC_1 reg. Default value: 0
//! 0: interrupt request not latched;
//! 1: interrupt request latched
//
#define FF_WU_CFG_LIR           0x40

//
//! Enable interrupt generation on Z high event. Default value: 0
//! 0: disable interrupt request;
//! 1: enable interrupt request on measured accel. value higher than preset threshold
//
#define FF_WU_CFG_ZHIE          0x20

//
//! Enable interrupt generation on Z low event. Default value: 0
//! 0: disable interrupt request;
//! 1: enable interrupt request on measured accel. value lower than preset threshold
//
#define FF_WU_CFG_ZLIE          0x10

//
//! Enable interrupt generation on Y high event. Default value: 0
//! 0: disable interrupt request;
//! 1: enable interrupt request on measured accel. value higher than preset threshold
//
#define FF_WU_CFG_YHIE          0x08

//
//! Enable interrupt generation on Y low event. Default value: 0
//! 0: disable interrupt request;
//! 1: enable interrupt request on measured accel. value lower than preset threshold
//
#define FF_WU_CFG_YLIE          0x04

//
//! Enable interrupt generation on X high event. Default value: 0
//! 0: disable interrupt request;
//! 1: enable interrupt request on measured accel. value higher than preset threshold
//
#define FF_WU_CFG_XHIE          0x02

//
//! Enable interrupt generation on X low event. Default value: 0
//! 0: disable interrupt request;
//! 1: enable interrupt request on measured accel. value lower than preset threshold
//
#define FF_WU_CFG_XLIE          0x01

//
//! Free-fall and wake-up source register.
//! Reading at this address clears FF_WU_SRC_1/2 register and the FF, WU 1/2 interrupt
//! and allows the refreshment of data in the FF_WU_SRC_1/2 register if the latched
//! option was chosen.
//
#define FF_WU_SRC_1             0x31
#define FF_WU_SRC_2             0x35

//
//! Interrupt active. Default value: 0
//! 0: no interrupt has been generated;
//! 1: one ore more interrupt has been generated
//
#define FF_WU_SRC_IA            0x40

//
//! Z high. Default value: 0
//! 0: no interrupt
//! 1: ZH event has occurred
//
#define FF_WU_SRC_ZH            0x20

//
//! Z low. Default value: 0
//! 0: no interrupt
//! 1: ZL event has occurred
//
#define FF_WU_SRC_ZL            0x10

//
//! Y high. Default value: 0 (0: no interrupt, 1: YH event has occurred)
//
#define FF_WU_SRC_YH            0x08

//
//! Y low. Default value: 0 (0: no interrupt, 1: YL event has occurred)
//
#define FF_WU_SRC_YL            0x04

//
//! X high. Default value: 0 (0: no interrupt, 1: XH event has occurred)
//
#define FF_WU_SRC_XH            0x02

//
//! X low. Default value: 0 (0: no interrupt, 1: XL event has occurred)
//
#define FF_WU_SRC_XL            0x01

//
//! Most significant bit (DCRM) is used to select the resetting mode of the
//! duration counter. If DCRM=0 counter is resetted when the interrupt is no more
//! active else if DCRM=1 duration counter is decremented.
//
#define FF_WU_THS_1             0x32
#define FF_WU_THS_2             0x36

//
//! Resetting mode selection. Default value: 0
//! 0: counter resetted
//! 1: counter decremented
//
#define FF_WU_THS_DCRM          0x80

//
//! THS6-->THS0 Free-fall / wake-up threshold: default value: 000 000x
//
#define FF_WU_THS_THS_MASK      0x7F

//
//! Duration register for Free-Fall/Wake-Up interrupt 1/2. Duration step and maximum
//! value depend on the ODR chosen. Step 2.5 msec, from 0 to 637.5 msec if
//! ODR=400Hz, else step 10 msec, from 0 to 2.55 sec when ODR=100Hz. The counter
//! used to implement duration function is blocked when LIR=1 in configuration
//! register and the interrupt event is verified
//
#define FF_WU_DURATION_1        0x33
#define FF_WU_DURATION_2        0x37

//Duration value mask
#define FF_WU_DURATION_D_MASK   0xFF


//
//!LIS302DL Click Configure register
//!   ----------------------------------------------------
//!   |          CLICK_CFG (38h) truth table             |
//!   +--------------------------------------------------+
//!   |  double_z/y/x | single_z/y/x |   clickoutput     |
//!   |---------------|--------------|-------------------|
//!   |       0       |      0       |        0          |
//!   |---------------|--------------|-------------------|
//!   |       0       |      1       |    single         |
//!   |---------------|--------------|-------------------|
//!   |       1       |      0       |    double         |
//!   |---------------|--------------|-------------------|
//!   |       1       |      1       |  single or double |
//!   +--------------------------------------------------+
//
#define CLICK_CFG               0x38

//
//! Latch interrupt request into CLICK_SRC reg with the CLICK_SRC reg refreshed by
//! reading CLICK_SRC reg. Default value: 0
//! 0: interrupt request not latched
//! 1: interrupt request latched)
//
#define CLICK_CFG_LIR           0x40

//
//! Enable interrupt generation on double click event on Z axis. Default value: 0
//! 0: disable interrupt request
//! 1: enable interrupt request
//
#define CLICK_CFG_Double_Z      0x20

//
//! Enable interrupt generation on single click event on Z axis. Default value: 0
//! 0: disable interrupt request
//! 1: enable interrupt request
//
#define CLICK_CFG_Single_Z      0x10

//
//! Enable interrupt generation on double click event on Y axis. Default value: 0
//! 0: disable interrupt request
//! 1: enable interrupt request
//
#define CLICK_CFG_Double_Y      0x08

//
//! Enable interrupt generation on single click event on Y axis. Default value: 0
//! 0: disable interrupt request
//! 1: enable interrupt request
//
#define CLICK_CFG_Single_Y      0x04

//
//! Enable interrupt generation on double click event on X axis. Default value: 0
//! 0: disable interrupt request
//! 1: enable interrupt request
//
#define CLICK_CFG_Double_X      0x02

//
//! Enable interrupt generation on single click event on X axis. Default value: 0
//! 0: disable interrupt request
//! 1: enable interrupt request
//
#define CLICK_CFG_Single_X      0x01

//
//! LIS302DL Click Status Register(RO)
//
#define CLICK_SRC               0x39

//
//! Interrupt active. Default value: 0
//! 0: no interrupt has been generated
//! 1: one or more interrupt event has been generated
//
#define CLICK_SRC_IA            0x40

//
//! Double click on Z axis event. Default value: 0
//! 0: no interrupt
//! 1: Double Z event has occurred
//
#define CLICK_SRC_Double_Z      0x20

//
//! Single click on Z axis event. Default value: 0
//! 0: no interrupt
//! 1: Single Z event has occurred
//
#define CLICK_SRC_Single_Z      0x10

//
//! Double click on Y axis event. Default value: 0
//! 0: no interrupt
//! 1: Double Y event has occurred
//
#define CLICK_SRC_Double_Y      0x08

//
//! Single click on Y axis event. Default value: 0
//! 0: no interrupt
//! 1: Single Y event has occurred
//
#define CLICK_SRC_Single_Y      0x04

//
//! Double click on X axis event. Default value: 0
//! 0: no interrupt
//! 1: Double X event has occurred
//
#define CLICK_SRC_Double_X      0x02

//
//! Single click on X axis event. Default value: 0
//! 0: no interrupt
//! 1: Single X event has occurred
//
#define CLICK_SRC_Single_X      0x01


//
//! LIS302DL Click Threshold X_Y register(RW)
//! From 0.5g(0001) to 7.5g(1111) with step of 0.5g.
//
#define CLICK_THSY_X            0x3B

//
//! THSy3-THSy0 Click threshold on Y axis. Default value: 0000
//
#define CLICK_THSY_X_THSy_MASK  0xF0

//
//! THSx3-THSx0 Click threshold on X axis. Default value: 0000
//
#define CLICK_THSY_X_THSx_MASK  0x0F

//
//! LIS302DL Click Threshold Z register(RW)
//! From 0.5g(0001) to 7.5g(1111) with step of 0.5g.
//
#define CLICK_THSZ              0x3C

//
//! THSz3-THSz0 Click threshold on Z axis. Default value: 0000
//
#define CLICK_THSZ_THSz_MASK    0x0F

//
//! LIS302DL Click TimeLimit register(RW)
//! From 0 to 127.5msec with step of 0.5 msec,
//
#define CLICK_TiMELIMIT         0x3D

//
//! Time limit value mask
//
#define CLICK_TiMELIMIT_MASK    0xFF

//
//! LIS302DL Click Latency register(RW)
//! From 0 to 255 msec with step of 1 msec.
//
#define CLICK_LATENCY           0x3E

//
//! Time Latency value mask
//
#define CLICK_LATENCY_MASK      0x3E

//
//! LIS302DL Click Window register(RW)
//! From 0 to 255 msec with step of 1 msec.
//
#define CLICK_WINDOW            0x3F

//
//! Time window value mask
//
#define CLICK_WINDOW_MASK       0x3F

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

#endif  //__HW_LIS302DL_H_

