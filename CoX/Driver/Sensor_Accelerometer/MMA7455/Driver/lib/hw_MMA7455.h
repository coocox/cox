//*****************************************************************************
//
//! \file hw_MMA7455.h
//! \brief header file of Driver for MMA7455
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

#ifndef __HW_MMA7455_H_
#define __HW_MMA7455_H_
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
//! \addtogroup MMA7455
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup MMA7455 Register description
//! @{
//
//*****************************************************************************

//! Bit define, used in this file only. not for USER
#define BIT_8_0                 0x01
#define BIT_8_1                 0x02
#define BIT_8_2                 0x04
#define BIT_8_3                 0x08
#define BIT_8_4                 0x10
#define BIT_8_5                 0x20
#define BIT_8_6                 0x40
#define BIT_8_7                 0x80

//! Register Address
#define MMA7455_REG_XOUTL       0x00
#define MMA7455_REG_XOUTH       0x01
#define MMA7455_REG_YOUTL       0x02
#define MMA7455_REG_YOUTH       0x03
#define MMA7455_REG_ZOUTL       0x04
#define MMA7455_REG_ZOUTH       0x05
#define MMA7455_REG_XOUT8       0x06
#define MMA7455_REG_YOUT8       0x07
#define MMA7455_REG_ZOUT8       0x08
#define MMA7455_REG_STATUS      0x09
#define MMA7455_REG_DETSRC      0x0A
#define MMA7455_REG_TOUT        0x0B
#define MMA7455_REG_I2CAD       0x0D
#define MMA7455_REG_USRINF      0x0E
#define MMA7455_REG_WHOAMI      0x0F
#define MMA7455_REG_XOFFL       0x10
#define MMA7455_REG_XOFFH       0x11
#define MMA7455_REG_YOFFL       0x12
#define MMA7455_REG_YOFFH       0x13
#define MMA7455_REG_ZOFFL       0x14
#define MMA7455_REG_ZOFFH       0x15
#define MMA7455_REG_MCTL        0x16
#define MMA7455_REG_INTRST      0x17
#define MMA7455_REG_CTL1        0x18
#define MMA7455_REG_CTL2        0x19
#define MMA7455_REG_LDTH        0x1A
#define MMA7455_REG_PDTH        0x1B
#define MMA7455_REG_PW          0x1C
#define MMA7455_REG_LT          0x1D
#define MMA7455_REG_TW          0x1E

//! MMA7455_REG_STATUS bit description
//! PERR
//! 1: Parity error is detected in trim data. Then, self-test is disabled
//! 0: Parity error is not detected in trim data
#define MMA7455_REG_STATUS_PERR BIT_8_2


//! DOVR
//! 1: Data is over written
//! 0: Data is not over written
#define MMA7455_REG_STATUS_DOVR BIT_8_1


//! DRDY
//! 1: Data is ready
//! 0: Data is not ready
#define MMA7455_REG_STATUS_DRDY BIT_8_0


//! MMA7455_REG_DETSRC
//! LDX
//! 1: Level detection detected on X-axis
//! 0: Level detection not detected on X-axis 
#define MMA7455_REG_DETSRC_LDX  BIT_8_7

//! LDY
//! 1: Level detection detected on Y-axis
//! 0: Level detection not detected on Y-axis 
#define MMA7455_REG_DETSRC_LDY  BIT_8_6

//! LDZ
//! 1: Level detection detected on Z-axis
//! 0: Level detection not detected on Z-axis 
#define MMA7455_REG_DETSRC_LDZ  BIT_8_5

//! PDX
//! 1: Pulse is detected on X-axis at single pulse detection
//! 0: Pulse is not detected on X-axis at single pulse detection 
//Note: This bit value is not valid at double pulse detection
#define MMA7455_REG_DETSRC_PDX  BIT_8_4

//! PDY
//! 1: Pulse is detected on Y-axis at single pulse detection
//! 0: Pulse is not detected on Y-axis at single pulse detection
//! Note: This bit value is not valid at double pulse detection
#define MMA7455_REG_DETSRC_PDY  BIT_8_3

//! PDZ
//! 1: Pulse is detected on Z-axis at single pulse detection
//! 0: Pulse is not detected on Z-axis at single pulse detection
//! Note: This bit value is not valid at double pulse detection
#define MMA7455_REG_DETSRC_PDZ  BIT_8_2

//! INT1
//! 1: Interrupt assigned by INTRG[1:0] bits in Control 1 Register ($18) and is
//! detected
//! 0: Interrupt assigned by INTRG[1:0] bits in Control 1 Register ($18) and is
//! not detected
#define MMA7455_REG_DETSRC_INT2 BIT_8_1

//! INT2
//! 1: Interrupt assigned by INTRG[1:0] bits in Control 1 Register ($18) and is
//! detected
//! 0: Interrupt assigned by INTRG[1:0] bits in Control 1 Register ($18) and is
//! not detected
#define MMA7455_REG_DETSRC_INT1 BIT_8_0

//! MMA7455_REG_I2CAD
//! 0: I2C and SPI are available.
//! 1: I2C is disabled.
#define MMA7455_REG_I2CAD_I2CDIS BIT_8_7


//! MMA7455_REG_MCTL
//! DRPD
//! 0: Data ready status is output to INT1/DRDY PIN
//! 1: Data ready status is not output to INT1/DRDY PIN
#define MMA7455_REG_MCTL_DRPD   BIT_8_6

//! SPI3W
//! 0: SPI is 4 wire mode
//! 1: SPI is 3 wire mode
#define MMA7455_REG_MCTL_SPI3W  BIT_8_5


//! STON
//! 0: Self-test is not enabled
//! 1: Self-test is enabled
#define MMA7455_REG_MCTL_STON   BIT_8_4

//! Configuring the g-Select for 8-bit output using Register $16 with GLVL[1:0] bits
//!   ----------------------------------------
//!   |  GLVL[1:0]   g-Range   Sensitivity   |
//!   |  00          8g        16LSB/g       |
//!   |  01          2g        64LSB/g       |
//!   |  10          4g        32LSB/g       |
//!   ----------------------------------------
#define MMA7455_REG_MCTL_GLVL_M (BIT_8_3 | BIT_8_2)
#define MMA7455_REG_MCTL_GLVL_1 BIT_8_3
#define MMA7455_REG_MCTL_GLVL_0 BIT_8_2

//! Configuring the Mode using Register $16 with MODE[1:0] bits
//!  -------------------------------------------
//!  |    MODE[1:0]   Function                 |
//!  |    00          Standby Mode             |
//!  |    01          Measurement Mode         |
//!  |    10          Level Detection Mode     |
//!  |    11          Pulse Detection Mode     |
//!  -------------------------------------------
#define MMA7455_REG_MCTL_MODE_M (BIT_8_1 | BIT_8_0)
#define MMA7455_REG_MCTL_MODE_1 BIT_8_1
#define MMA7455_REG_MCTL_MODE_0 BIT_8_0

//! MMA7455_REG_INTRST
//! CLR_INT1
//! 1: Clear ¡°INT1¡± and LDX/LDY/LDZ or PDX/PDY/PDZ bits in Detection Source
//!    Register ($0A) depending on Control1($18) INTREG[1:0] setting.
//! 0: Do not clear ¡°INT1¡± LDX/LDY/LDZ or PDX/PDY/PDZ bits in Detection Source
//!    Register ($0A)
#define MMA7455_REG_INTRST_CLR_INT2 BIT_8_1

//! CLR_INT2
//! 1: Clear ¡°INT2¡± and LDX/LDY/LDZ or PDX/PDY/PDZ bits in Detection Source
//!    Register ($0A) depending on Control1($18) INTREG[1:0] setting.
//! 0: Do not clear ¡°INT2¡± and LDX/LDY/LDZ or PDX/PDY/PDZ bits in Detection
//!    Source Register ($0A)
#define MMA7455_REG_INTRST_CLR_INT1 BIT_8_0


//! MMA7455_REG_CTL1
//! DFBW
//! 0: Digital filter band width is 62.5 Hz
//! 1: Digital filter band width is 125 Hz
#define MMA7455_REG_CTL1_DFBW     BIT_8_7

//! THOPT (This bit is valid for level detection only, not valid for pulse detection)
//! 0: Threshold value is absolute only
//! 1: Integer value is available.
#define MMA7455_REG_CTL1_THOPT    BIT_8_6

//! ZDA
//! 1: Z-axis is disabled for detection.
//! 0: Z-axis is enabled for detection.
#define MMA7455_REG_CTL1_ZDA      BIT_8_5

//! YDA
//! 1: Y-axis is disabled for detection.
//! 0: Y-axis is enabled for detection.
#define MMA7455_REG_CTL1_YDA      BIT_8_4

//! XDA
//! 1: X-axis is disabled for detection.
//! 0: X-axis is enabled for detection.
#define MMA7455_REG_CTL1_XDA      BIT_8_3

//! Configuring the Interrupt settings using Register $18 with INTREG[1:0] bits
//! 00: INT1 Register is detecting Level while INT2 is detecting Pulse.
//! 01: INT1 Register is detecting Pulse while INT2 is detecting Level.
//! 10: INT1 Register is detecting a Single Pulse and INT2 is detecting Single
//! Pulse (if 2nd Time Window = 0) or if there is a latency time window and second
//! time window > 0 then INT2 will detect the double pulse only.
//! See the table below
//!  ------------------------------------------------------------------------------
//!  |  INTREG[1:0]   INT1_Register_Bit         INT2_Register_Bit                 |
//!  |  00            Level_detection           Pulse_Detection                   |
//!  |  01            Pulse_Detection           Level_Detection                   |
//!  |  10            Single_Pulse_detection    Single_or_Double_Pulse_Detection  |
//!  ------------------------------------------------------------------------------
#define MMA7455_REG_CTL1_INTREG_M (BIT_8_2|BIT_8_1)
#define MMA7455_REG_CTL1_INTREG_1 BIT_8_2
#define MMA7455_REG_CTL1_INTREG_0 BIT_8_1

//! INTPIN
//! 0: INT1 pin is routed to INT1 bit in Detection Source Register ($0A) and
//! INT2 pin is routed to INT2 bit in Detection Source Register ($0A).
//! 1: INT2 pin is routed to INT1 bit in Detection Source Register ($0A) and
//! INT1 pin is routed to INT2 bit in Detection Source Register ($0A).
#define   MMA7455_REG_CTL1_INTPIN BIT_8_0


//! MMA7455_REG_CTL2

//! DRVO
//! 0: Standard drive strength on SDA/SDO pin
//! 1: Strong drive strength on SDA/SDO pin
#define MMA7455_REG_CTL2_DRVO     BIT_8_2

//! PDPL
//! 0: Pulse detection polarity is positive and detecting condition is OR 3 axes.
//! 1: Pulse detection polarity is negative and detecting condition is AND 3 axes.
#define MMA7455_REG_CTL2_PDPL     BIT_8_1

//! LDPL
//! 0: Level detection polarity is positive and detecting condition is OR 3 axes.
//! 1: Level detection polarity is negative detecting condition is AND 3 axes.
#define MMA7455_REG_CTL2_LDPL     BIT_8_0


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

#endif  //__HW_MMA7455_H_

