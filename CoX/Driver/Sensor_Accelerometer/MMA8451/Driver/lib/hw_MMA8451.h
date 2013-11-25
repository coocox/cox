//*****************************************************************************
//
//! \file hw_MMA8451.h
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

#ifndef __HW_MMA8451_H_
#define __HW_MMA8451_H_
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
//! \addtogroup MMA8451
//! @{
//
//*****************************************************************************

#define BIT_8_7                         ((uint8_t)0x80)
#define BIT_8_6                         ((uint8_t)0x40)
#define BIT_8_5                         ((uint8_t)0x20)
#define BIT_8_4                         ((uint8_t)0x10)
#define BIT_8_3                         ((uint8_t)0x08)
#define BIT_8_2                         ((uint8_t)0x04)
#define BIT_8_1                         ((uint8_t)0x02)
#define BIT_8_0                         ((uint8_t)0x01)


//*****************************************************************************
//
//! \addtogroup MMA8451_Register_Base_Address MMA8451 Register base address.
//! \brief Register Base Address.
//! @{
//
//*****************************************************************************

#define MMA8451_REG_STATUSR             0x00
#define MMA8451_REG_OUT_X_MSB           0x01
#define MMA8451_REG_OUT_X_MSB           0x01
#define MMA8451_REG_OUT_X_LSB           0x02
#define MMA8451_REG_OUT_Y_MSB           0x03
#define MMA8451_REG_OUT_Y_LSB           0x04
#define MMA8451_REG_OUT_Z_MSB           0x05
#define MMA8451_REG_OUT_Z_LSB           0x06
//Reserved                              0x07
//Reserved                              0x08
#define MMA8451_REG_F_SETUP             0x09
#define MMA8451_REG_TRIG_CFG            0x0A
#define MMA8451_REG_SYSMOD              0x0B
#define MMA8451_REG_INT_SOURCE          0x0C
#define MMA8451_REG_WHO_AM_I            0x0D
#define MMA8451_REG_XYZ_DATA_CFG        0x0E
#define MMA8451_REG_HP_FILTER_CUTOFF    0x0F
#define MMA8451_REG_PL_STATUS           0x10
#define MMA8451_REG_PL_CFG              0x11
#define MMA8451_REG_PL_COUNT            0x12
#define MMA8451_REG_PL_BF_ZCOMP         0x13
#define MMA8451_REG_PL_THS_REG          0x14
#define MMA8451_REG_FF_MT_CFG           0x15
#define MMA8451_REG_FF_MT_SRC           0x16
#define MMA8451_REG_FF_MT_THS           0x17
#define MMA8451_REG_FF_MT_COUNT         0x18
//Reserved                              0x19
//Reserved                              0x1A
//Reserved                              0x1B
//Reserved                              0x1C
#define MMA8451_REG_TRANSIENT_CFG       0x1D
#define MMA8451_REG_TRANSIENT_SRC       0x1E
#define MMA8451_REG_TRANSIENT_THS       0x1F
#define MMA8451_REG_TRANSIENT_COUNT     0x20
#define MMA8451_REG_PULSE_CFG           0x21
#define MMA8451_REG_PULSE_SRC           0x22
#define MMA8451_REG_PULSE_THSX          0x23
#define MMA8451_REG_PULSE_THSY          0x24
#define MMA8451_REG_PULSE_THSZ          0x25
#define MMA8451_REG_PULSE_TMLT          0x26
#define MMA8451_REG_PULSE_LTCY          0x27
#define MMA8451_REG_PULSE_WIND          0x28
#define MMA8451_REG_ASLP_COUNT          0x29
#define MMA8451_REG_CTRL_REG1           0x2A
#define MMA8451_REG_CTRL_REG2           0x2B
#define MMA8451_REG_CTRL_REG3           0x2C
#define MMA8451_REG_CTRL_REG4           0x2D
#define MMA8451_REG_CTRL_REG5           0x2E
#define MMA8451_REG_OFF_X               0x2F
#define MMA8451_REG_OFF_Y               0x30
#define MMA8451_REG_OFF_Z               0x31
//Reserved                              0x40
//                                      ....
//Reserved                              0x7F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MMA8451_Register_Bit_desc MMA8451 Register bit description
//! \brief Register Base Address
//! @{
//
//*****************************************************************************

/////////////////////////REG_STATUSR////////////////////////////////////////////

//ZYXOW is set whenever a new acceleration data is produced before completing the
//retrieval of the previous set. This event occurs when the content of at least
//one acceleration data register (i.e., OUT_X, OUT_Y, OUT_Z) has been.overwritten.
//ZYXOW is cleared when the high-bytes of the acceleration data (OUT_X_MSB,
//OUT_Y_MSB, OUT_Z_MSB) of all the active channels are read.
#define STATUSR_ZYXOW           BIT_8_7

//ZOW is set whenever a new acceleration sample related to the Z-axis is
//generated before the retrieval of the previous sample.  When this occurs the
//previous sample is overwritten. ZOW is cleared anytime OUT_Z_MSB register is
//read.
#define STATUSR_ZOW             BIT_8_6

//YOW is set whenever a new acceleration sample related to the Y-axis is
//generated before the retrieval of the previous sample.  When this occurs the
//previous sample is overwritten. YOW is cleared anytime OUT_Y_MSB register is
//read.
#define STATUSR_YOW             BIT_8_5

//XOW is set whenever a new acceleration sample related to the X-axis is
//generated before the retrieval of the previous sample.  When this occurs the
//previous sample is overwritten. XOW is cleared anytime OUT_X_MSB register is
//read.
#define STATUSR_XOW             BIT_8_4

//ZYXDR signals that a new sample for any of the enabled channels is available.
//ZYXDR is cleared when the high-bytes of the acceleration data (OUT_X_MSB,
//OUT_Y_MSB, OUT_Z_MSB) of all the enabled channels are read.
#define STATUSR_ZYXDR           BIT_8_3

//ZDR is set whenever a new acceleration sample related to the Z-axis is
//generated. ZDR is cleared anytime OUT_Z_MSB register is read.
#define STATUSR_ZDR             BIT_8_2

//YDR is set whenever a new acceleration sample related to the Y-axis is
//generated. YDR is cleared anytime OUT_Y_MSB register is read.
#define STATUSR_YDR             BIT_8_1

//XDR is set whenever a new acceleration sample related to the X-axis is
//generated. XDR is cleared anytime OUT_X_MSB register is read.
#define STATUSR_XDR             BIT_8_0

//0 No FIFO overflow events detected.
//1 FIFO event detected; FIFO has overflowed.
#define STATUSR_F_OVF           BIT_8_7

//0 No FIFO watermark events detected.
//1 FIFO Watermark event detected. FIFO sample count is greater than watermark value.
//If F_MODE = 11, Trigger Event detected
#define STATUSR_F_WMRK_FLAG     BIT_8_6

//Indicate the number of acceleration samples currently stored in the FIFO
//buffer. Count 000000 indicates that the FIFO is empty.
#define STATUSR_F_CNT_M         (BIT_8_5 | BIT_8_4 | BIT_8_3 | \
                                 BIT_8_2 | BIT_8_1 | BIT_8_0 )



/////////////////////////REG_F_SETUP////////////////////////////////////////////
//FIFO buffer overflow mode mask.
#define F_SETUP_MODE_M          (BIT_8_7|BIT_8_6)

//FIFO Event Sample Count Watermark mask.
#define F_SETUP_WMRK_M          (BIT_8_5 | BIT_8_4 | BIT_8_3 | \
                                BIT_8_2 | BIT_8_1 | BIT_8_0 )

/////////////////////////Trigger Configuration Register////////////////////////
//Transient interrupt trigger bit. Default value: 0
#define TRIG_CFG_TRANS          BIT_8_5

//Trig_LNDPRT Landscape/Portrait Orientation interrupt trigger bit. Default value: 0
#define TRIG_CFG_LNDPRT         BIT_8_4

//Trig_PULSE Pulse interrupt trigger bit. Default value: 0
#define TRIG_CFG_PULSE          BIT_8_3

//Trig_FF_MT Freefall/Motion trigger bit. Default value: 0
#define TRIG_CFG_FF_MT          BIT_8_2

//FIFO Gate Error. Default value: 0.
//0: No FIFO Gate Error detected.
//1: FIFO Gate Error was detected.
//Emptying the FIFO buffer clears the FGERR bit in the SYS_MOD register.
//See section 0x2C: CTRL_REG3 Interrupt Control Register for more information
//on configuring the FIFO Gate function.
#define SYSMOD_FGERR            BIT_8_7

//FGT[4:0] Number of ODR time units since FGERR was asserted. Reset when FGERR
//Cleared. Default value: 0_0000
#define SYSMOD_FGT_M            ( BIT_8_6 | BIT_8_5 | BIT_8_4 | BIT_8_3 | BIT_8_2 )

//System Mode. Default value: 00.
//00: STANDBY mode
//01: WAKE mode
//10: SLEEP mode
#define SYSMOD_SYSMOD_M         ( BIT_8_1 | BIT_8_0 )


/////////////////////////System Interrupt Status Register////////////////////////
//Auto-SLEEP/WAKE interrupt status bit.
#define INT_SRC_ASLP            BIT_8_7

//FIFO interrupt status bit.
#define INT_SRC_FIFO            BIT_8_6

//Transient interrupt status bit.
#define INT_SRC_TRANS           BIT_8_5

//Landscape/Portrait Orientation interrupt status bit.
#define INT_SRC_LNDPRT          BIT_8_4

//Pulse interrupt status bit.
#define INT_SRC_PULSE           BIT_8_3

//Freefall/Motion interrupt status bit.
#define INT_SRC_FF_MT           BIT_8_2

//Data Ready Interrupt bit status.
#define INT_SRC_DRDY            BIT_8_0

/////////////////////////XYZ_DATA_CFG Register////////////////////////////////
//Enable High-pass output data
#define XYZ_DATA_CFG_HPF_OUT    BIT_8_4

//Output buffer data format full scale mask.
#define XYZ_DATA_CFG_FS_M       (BIT_8_1 | BIT_8_0)

/////////////////////////High-Pass Filter Register/////////////////////////////
//High-Pass Filter (HPF) for Pulse Processing Function.
#define HP_FILTER_CUTOFF_HPF_BYP BIT_8_5

//Low-Pass Filter (LPF) for Pulse Processing Function.
#define HP_FILTER_CUTOFF_LPF_EN  BIT_8_4

//Cutoff frequency selection
#define HP_FILTER_CUTOFF_SEL_M   (BIT_8_1 | BIT_8_0)

//////////////////////Portrait/Landscape Status Register//////////////////////
//Landscape/Portrait status change flag
#define PL_STATUS_NEWLP      BIT_8_7

//Z-Tilt Angle Lockout
#define PL_STATUS_LO         BIT_8_6

//Landscape/Portrait orientation mask.
#define PL_STATUS_LAPO_M     (BIT_8_2 | BIT_8_1)

//Back or Front orientation
#define PL_STATUS_BAFRO      BIT_8_0

//////////////////Portrait/Landscape Configuration Register ///////////////////
//Debounce counter mode selection.
#define PL_CFG_DBCNTM           BIT_8_7

//Portrait/Landscape Detection Enable.
#define PL_CFG_PL_EN            BIT_8_6

//////////////////Back/Front and Z Compensation Register//////////////////////
//Back/Front Trip Angle Threshold
#define PL_BF_ZCOMP_BKFR        (BIT_8_7 | BIT_8_6)

//Z-Lock Angle Threshold.
#define PL_BF_ZCOMP_ZLCOCK      (BIT_8_2 | BIT_8_1 |  BIT_8_0)

///////////Portrait/Landscape Threshold and Hysteresis Registe/////////////////
//Portrait/Landscape trip threshold angle from 15бу to 75бу.
#define P_L_THS_THS_M           (BIT_8_7 | BIT_8_6 |  BIT_8_5 | BIT_8_4 | BIT_8_3)

//This angle is added to the threshold angle for a smoother transition from
//Portrait to Landscape and Landscape to Portrait.
#define P_L_THS_HYS_M           (BIT_8_2 | BIT_8_1 |  BIT_8_0)

//Event Latch Enable: Event flags are latched into FF_MT_SRC register.
//Reading of the FF_MT_SRC register clears the event flag EA and all FF_MT_SRC bits.
//Default value: 0.
//0: Event flag latch disabled
//1: event flag latch enabled
#define FF_MT_CFG_ELE           BIT_8_7

//OAE bit allows the selection between Motion (logical OR combination) and Freefall
//(logical AND combination) detection.  Default value: 0. (Freefall Flag)
//0: Freefall Flag (Logical AND combination)
//1: Motion Flag (Logical OR combination)
#define FF_MT_CFG_OAE           BIT_8_6

//Event flag enable on Z Default value: 0.
//0: event detection disabled;
//1: raise event flag on measured acceleration value beyond preset threshold
#define FF_MT_CFG_ZEFE          BIT_8_5

//Event flag enable on Y Default value: 0.
//0: event detection disabled;
//1: raise event flag on measured acceleration value beyond preset threshold
#define FF_MT_CFG_YEFE          BIT_8_4

//Event flag enable on X Default value: 0.
//0: event detection disabled;
//1: raise event flag on measured acceleration value beyond preset threshold
#define FF_MT_CFG_XEFE          BIT_8_3

//Event Active Flag. Default value: 0.
//0: No event flag has been asserted; 1: one or more event flag has been asserted.
#define FF_MT_SRC_EA            BIT_8_7

//Z Motion Flag. Default value: 0.
//0: No Z Motion event detected, 1: Z Motion has been detected
//This bit reads always zero if the ZEFE control bit is set to zero
#define FF_MT_SRC_ZHE           BIT_8_5

//Z Motion Polarity Flag. Default value: 0.
//0: Z event was Positive g, 1: Z event was Negative g
//This bit read always zero if the ZEFE control bit is set to zero
#define FF_MT_SRC_ZHP           BIT_8_4

//Y Motion Flag. Default value: 0.
//0: No Y Motion event detected, 1: Y Motion has been detected
//This bit read always zero if the YEFE control bit is set to zero
#define FF_MT_SRC_YHE           BIT_8_3

//Y Motion Polarity Flag. Default value: 0
//0: Y event detected was Positive g, 1: Y event was Negative g
//This bit reads always zero if the YEFE control bit is set to zero
#define FF_MT_SRC_YHP           BIT_8_2

//X Motion Flag. Default value: 0
//0: No X Motion event detected, 1: X Motion has been detected
//This bit reads always zero if the XEFE control bit is set to zero
#define FF_MT_SRC_XHE           BIT_8_1

//X Motion Polarity Flag. Default value: 0
//0: X event was Positive g, 1: X event was Negative g
//This bit reads always zero if the XEFE control bit is set to zero
#define FF_MT_SRC_XHP           BIT_8_0

//Debounce counter mode selection. Default value: 0.
//0: increments or decrements debounce, 1: increments or clears counter.
#define FF_MT_THS_DBCNTM        BIT_8_7

//Freefall /Motion Threshold: Default value: 000_0000.
#define FF_MT_THS_THS_M         (BIT_8_6 | BIT_8_5 | BIT_8_4 | BIT_8_3 | \
                                 BIT_8_2 | BIT_8_1 | BIT_8_0 )
//Transient event flags are latched into the TRANSIENT_SRC register.
//Reading of the TRANSIENT_SRC register clears the event
//flag. Default value: 0.
//0: Event flag latch disabled; 1: Event flag latch enabled
#define TRANSIENT_CFG_ELE     BIT_8_4

//Event flag enable on Z transient acceleration greater than transient threshold
//event. Default value: 0.
//0: Event detection disabled;
//1: Raise event flag on measured acceleration delta value greater than transient
//   threshold.
#define TRANSIENT_CFG_ZTEFE   BIT_8_3

//Event flag enable on Y transient acceleration greater than transient threshold
//event.  Default value: 0.
//0: Event detection disabled;
//1: Raise event flag on measured acceleration delta value greater than transient
//   threshold.
#define TRANSIENT_CFG_YTEFE   BIT_8_2

//Event flag enable on X transient acceleration greater than transient threshold event.
//    Default value: 0.
//0: Event detection disabled;
//1: Raise event flag on measured acceleration delta value greater than transient
//   threshold.
#define TRANSIENT_CFG_XTEFE   BIT_8_1

//Bypass High-Pass filter
//Default value: 0.
//0: Data to transient acceleration detection block is through HPF
//1: Data to transient acceleration detection block is NOT through
//HPF (similar to motion detection function)
#define TRANSIENT_CFG_HPF_BYP BIT_8_0



//Event Active Flag. Default value: 0.
//0: no event flag has been asserted; 1: one or more event flag has been asserted.
#define TRANSIENT_SCR_EA            BIT_8_6

//Z transient event. Default value: 0.
//0: no interrupt
//1: Z Transient acceleration greater than the value of TRANSIENT_THS event has occurred
#define TRANSIENT_SCR_ZTRANSE       BIT_8_5

//Polarity of Z Transient Event that triggered interrupt. Default value: 0.
//0: Z event was Positive g
//1: Z event was Negative g
#define TRANSIENT_SCR_Z_TRANS_POL   BIT_8_4

//Y transient event. Default value: 0.
//0: no interrupt
//1: Y Transient acceleration greater than the value of TRANSIENT_THS event has occurred
#define TRANSIENT_SCR_YTRANSE       BIT_8_3

//Polarity of Y Transient Event that triggered interrupt. Default value: 0.
//0: Y event was Positive g
//1: Y event was Negative g
#define TRANSIENT_SCR_Y_TRANS_POL   BIT_8_2

//X transient event. Default value: 0.
//0: no interrupt
//1: X Transient acceleration greater than the value of TRANSIENT_THS event has occurred
#define TRANSIENT_SCR_XTRANSE       BIT_8_1

//Polarity of X Transient Event that triggered interrupt. Default value: 0.
//0: X event was Positive g
//1: X event was Negative g
#define TRANSIENT_SCR_X_TRANS_POL   BIT_8_0


//Debounce counter mode selection. Default value: 0.
//0: increments or decrements debounce
//1: increments or clears counter.
#define TRANSIENT_THS_DBCNTM        BIT_8_7

//Transient Threshold: Default value: 000_0000.
#define TRANSIENT_THS_THS_M         (BIT_8_6 | BIT_8_5 | BIT_8_4 | BIT_8_3 | \
                                     BIT_8_2 | BIT_8_1 | BIT_8_0 )

//Double Pulse Abort. Default value: 0.
//0: Double Pulse detection is not aborted if the start of a pulse is detected
//during the time period specified by the PULSE_LTCY register.
//1: Setting the DPA bit momentarily suspends the double tap detection if the
//start of a pulse is detected during the time period specified by the PULSE_LTCY
//register and the pulse ends before the end of the time period specified by the
//PULSE_LTCY register.
#define PULSE_CFG_DPA           BIT_8_7

//Pulse event flags are latched into the PULSE_SRC register.
//Reading of the PULSE_SRC register clears the event flag.  Default value: 0.
//0: Event flag latch disabled; 1: Event flag latch enabled
#define PULSE_CFG_ELE           BIT_8_6

//Event flag enable on double pulse event on Z-axis. Default value: 0.
//0: Event detection disabled; 1: Event detection enabled
#define PULSE_CFG_ZDPEFE        BIT_8_5

//Event flag enable on single pulse event on Z-axis. Default value: 0.
//0: Event detection disabled; 1: Event detection enabled
#define PULSE_CFG_ZSPEFE        BIT_8_4

//Event flag enable on double pulse event on Y-axis. Default value: 0.
//0: Event detection disabled; 1: Event detection enabled
#define PULSE_CFG_YDPEFE        BIT_8_3

//Event flag enable on single pulse event on Y-axis. Default value: 0.
//0: Event detection disabled; 1: Event detection enabled
#define PULSE_CFG_YSPEFE        BIT_8_2

//Event flag enable on double pulse event on X-axis. Default value: 0.
//0: Event detection disabled; 1: Event detection enabled
#define PULSE_CFG_XDPEFE        BIT_8_1

//Event flag enable on single pulse event on X-axis. Default value: 0.
//0: Event detection disabled; 1: Event detection enabled
#define PULSE_CFG_XSPEFE        BIT_8_0

//Event Active Flag. Default value: 0.
//0: No interrupt has been generated
//1: One or more interrupt events have been generated
#define PULSE_SRC_EA            BIT_8_7

//Z-axis event. Default value: 0.
//0: No interrupt; 1: Z-axis event has occurred
#define PULSE_SRC_AXZ           BIT_8_6

//Y-axis event. Default value: 0.
//0: No interrupt; 1: Y-axis event has occurred
#define PULSE_SRC_AXY           BIT_8_5

//X-axis event. Default value: 0.
//0: No interrupt; 1: X-axis event has occurred
#define PULSE_SRC_AXX 10        BIT_8_4

//Double pulse on first event. Default value: 0.
//0: Single Pulse Event triggered interrupt
//1: Double Pulse Event triggered interrupt
#define PULSE_SRC_DPE           BIT_8_3

//Pulse polarity of Z-axis Event. Default value: 0.
//0: Pulse Event that triggered interrupt was Positive
//1: Pulse Event that triggered interrupt was negative
#define PULSE_SRC_POLZ          BIT_8_2

//Pulse polarity of Y-axis Event. Default value: 0.
//0: Pulse Event that triggered interrupt was Positive
//1: Pulse Event that triggered interrupt was negative
#define PULSE_SRC_POLY          BIT_8_1

//Pulse polarity of X-axis Event. Default value: 0.
//0: Pulse Event that triggered interrupt was Positive
//1: Pulse Event that triggered interrupt was negative
#define PULSE_SRC_POLX          BIT_8_0

//Pulse Threshold on X-axis mask.
#define PULSE_THSX_M            ( BIT_8_6 | BIT_8_5 | BIT_8_4 | BIT_8_3 | \
                                  BIT_8_2 | BIT_8_1 | BIT_8_0  )

//Pulse Threshold on Y-axis mask.
#define PULSE_THSY_M            ( BIT_8_6 | BIT_8_5 | BIT_8_4 | BIT_8_3 | \
                                  BIT_8_2 | BIT_8_1 | BIT_8_0  )

//Pulse Threshold on Z-axis mask.
#define PULSE_THSZ_M            ( BIT_8_6 | BIT_8_5 | BIT_8_4 | BIT_8_3 | \
                                  BIT_8_2 | BIT_8_1 | BIT_8_0  )

//Configures the Auto-WAKE sample frequency when the device is in SLEEP Mode. Default value: 00.
#define CTRL_REG1_ASLP_RATE_M    (BIT_8_7 | BIT_8_6 )

//Data rate selection. Default value: 000.
#define CTRL_REG1_DR_M           (BIT_8_5 | BIT_8_4 | BIT_8_3 )

//Reduced noise reduced Maximum range mode. Default value: 0.
//0: Normal mode
//1: Reduced Noise mode
#define CTRL_REG1_LNOISE         BIT_8_2

//Fast Read mode: Data format limited to single Byte Default value: 0.
//0: Normal mode
//1: Fast Read Mode
#define CTRL_REG1_F_READ         BIT_8_1

//Full Scale selection. Default value: 00.
//0: STANDBY mode
//1: ACTIVE mode
#define CTRL_REG1_ACTIVE         BIT_8_0

//Self-Test Enable. Default value: 0.
//0: Self-Test disabled
//1: Self-Test enabled
#define CTRL_REG2_ST             BIT_8_7

//Software Reset. Default value: 0.
//0: Device reset disabled
//1: Device reset enabled.
#define CTRL_REG2_RST            BIT_8_6

//SLEEP mode power scheme selection.
#define CTRL_REG2_SMODS_M        (BIT_8_4 | BIT_8_3)

//Auto-SLEEP enable. Default value: 0.
//0: Auto-SLEEP is not enabled;
//1: Auto-SLEEP is enabled.
#define CTRL_REG2_SLPE           BIT_8_2

//ACTIVE mode power scheme selection
#define CTRL_REG2_MODS_M         (BIT_8_1 | BIT_8_0 )

//0: FIFO gate is bypassed. FIFO is flushed upon the system mode transitioning
//    from WAKE to SLEEP mode or from SLEEP to WAKE mode. Default value: 0.
//1: The FIFO input buffer is blocked when transitioning from WAKE to SLEEP mode
//or from SLEEP to WAKE mode until the FIFO is flushed. Although the system
//transitions from WAKE to SLEEP or from SLEEP to WAKE the contents of the FIFO
//buffer are preserved, new data samples are ignored until the FIFO is emptied by
//the host application.
//
//If the FIFO_GATE bit is set to logic бо1бп and the FIFO buffer is not emptied
//before the arrival of the next sample, then the FGERR bit in the SYS_MOD
//register (0x0B) will be asserted. The FGERR bit remains asserted as long as the
//FIFO buffer remains un-emptied.
//
//Emptying the FIFO buffer clears the FGERR bit in the SYS_MOD register.
#define CTRL_REG3_FIFO_GATE      BIT_8_7

//0: Transient function is bypassed in SLEEP mode. Default value: 0.
//1: Transient function interrupt can wake up system
#define CTRL_REG3_WAKE_TRANS     BIT_8_6

//0: Orientation function is bypassed in SLEEP mode. Default value: 0.
//1: Orientation function interrupt can wake up system
#define CTRL_REG3_WAKE_LNDPRT    BIT_8_5

//0: Pulse function is bypassed in SLEEP mode. Default value: 0.
//1: Pulse function interrupt can wake up system
#define CTRL_REG3_WAKE_PULSE     BIT_8_4

//0: Freefall/Motion function is bypassed in SLEEP mode. Default value: 0.
//1: Freefall/Motion function interrupt can wake up
#define CTRL_REG3_WAKE_FF_MT     BIT_8_3

//Interrupt polarity ACTIVE high, or ACTIVE low. Default value: 0.
//0: ACTIVE low
//1: ACTIVE high
#define CTRL_REG3_IPOL           BIT_8_1

//Push-Pull/Open Drain selection on interrupt pad. Default value: 0.
//0: Push-Pull
//1: Open Drain
#define CTRL_REG3_PP_OD          BIT_8_0

//Interrupt Enable. Default value: 0.
//0: Auto-SLEEP/WAKE interrupt disabled
//1: Auto-SLEEP/WAKE interrupt enabled.
#define CTRL_REG4_INT_EN_ASLP   BIT_8_7

//Interrupt Enable. Default value: 0.
//0: FIFO interrupt disabled
//1: FIFO interrupt enabled.
#define CTRL_REG4_INT_EN_FIFO   BIT_8_6

//Interrupt Enable. Default value: 0.
//0: Transient interrupt disabled
//1: Transient interrupt enabled.
#define CTRL_REG4_INT_EN_TRANS  BIT_8_5

//Interrupt Enable. Default value: 0.
//0: Orientation (Landscape/Portrait) interrupt disabled.
//1: Orientation (Landscape/Portrait) interrupt enabled.
#define CTRL_REG4_INT_EN_LNDPR  BIT_8_4

//Interrupt Enable. Default value: 0.
//0: Pulse Detection interrupt disabled
//1: Pulse Detection interrupt enabled
#define CTRL_REG4_INT_EN_PULSE  BIT_8_3

//Interrupt Enable. Default value: 0.
//0: Freefall/Motion interrupt disabled
//1: Freefall/Motion interrupt enabled
#define CTRL_REG4_INT_EN_FF_MT  BIT_8_2

//Interrupt Enable. Default value: 0.
//0: Data Ready interrupt disabled
//1: Data Ready interrupt enabled
#define CTRL_REG4_INT_EN_DRDY   BIT_8_0

//INT1/INT2 Configuration. Default value: 0.
//0: Interrupt is routed to INT2 pin
//1: Interrupt is routed to INT1 pin
#define CTRL_REG5_INT_CFG_ASLP   BIT_8_7

//INT1/INT2 Configuration. Default value: 0.
//0: Interrupt is routed to INT2 pin
//1: Interrupt is routed to INT1 pin
#define CTRL_REG5_INT_CFG_FIFO   BIT_8_6

//INT1/INT2 Configuration. Default value: 0.
//0: Interrupt is routed to INT2 pin
//1: Interrupt is routed to INT1 pin
#define CTRL_REG5_INT_CFG_TRANS  BIT_8_5

//INT1/INT2 Configuration. Default value: 0.
//0: Interrupt is routed to INT2 pin
//1: Interrupt is routed to INT1 pin
#define CTRL_REG5_INT_CFG_LNDPRT BIT_8_4

//INT1/INT2 Configuration. Default value: 0.
//0: Interrupt is routed to INT2 pin
//1: Interrupt is routed to INT1 pin
#define CTRL_REG5_INT_CFG_PULSE  BIT_8_3

//INT1/INT2 Configuration. Default value: 0.
//0: Interrupt is routed to INT2 pin
//1: Interrupt is routed to INT1 pin
#define CTRL_REG5_INT_CFG_FF_MT  BIT_8_2

//INT1/INT2 Configuration. Default value: 0.
//0: Interrupt is routed to INT2 pin
//1: Interrupt is routed to INT1 pin
#define CTRL_REG5_INT_CFG_DRDY   BIT_8_0


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

#endif  //__HW_MMA8451_H_

