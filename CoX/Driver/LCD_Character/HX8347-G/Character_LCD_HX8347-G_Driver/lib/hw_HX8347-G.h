//*****************************************************************************
//
//! \file hw_HX8347-G.h
//! \brief Character LCD HX8347-G definition.
//! \version 1.0.0
//! \date 6/26/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
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
//
//*****************************************************************************

#ifndef __HW_HX8347_H__
#define __HW_HX8347_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD
//! @{
//
//*****************************************************************************
    
//*****************************************************************************
//
//! \addtogroup LCD_Graphic
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347-G
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347-G_Driver_Single
//! @{
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup HX8347-G_Register  HX8347-G Register
//! \brief Here are the detailed info of HX8347-G registers.  
//!
//! it contains:
//! - Register offset.
//! - Detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_Address HX8347 Register
//! \brief HX8347 Register Address.
//! @{
//
//*****************************************************************************

//
//! HX8347 Himax ID register.
//
#define HX8347_HIMAX_ID         0x00

//
//! HX8347 Display mode control register.
//
#define HX8347_MODE_CR          0x01

//
//! HX8347 Column address start register 1.
//
#define HX8347_COLUMN_ADDRSTR_1 0x02

//
//! HX8347 Column address start register 2.
//
#define HX8347_COLUMN_ADDRSTR_2 0x03

//
//! HX8347 Column address end register 1.
//
#define HX8347_COLUMN_ADDREND_1 0x04

//
//! HX8347 Column address end register 2.
//
#define HX8347_COLUMN_ADDREND_2 0x05

//
//! HX8347 Row address start register 1.
//
#define HX8347_ROW_ADDRSTR_1    0x06

//
//! HX8347 Row address start register 2.
//
#define HX8347_ROW_ADDRSTR_2    0x07

//
//! HX8347 Row address end register 1.
//
#define HX8347_ROW_ADDREND_1    0x08

//
//! HX8347 Row address end register 2.
//
#define HX8347_ROW_ADDREND_2    0x09

//
//! HX8347 Partial area start row register 1.
//
#define HX8347_PARTIAL_STARTROW_1                                             \
                                0x0A
//
//! HX8347 Partial area start row register 2.
//
#define HX8347_PARTIAL_STARTROW_2                                             \
                                0x0B

//
//! HX8347 Partial area end row register 1.
//
#define HX8347_PARTIAL_ENDROW_1 0x0C

//
//! HX8347 Partial aera end row register 2.
//
#define HX8347_PARTIAL_ENDROW_2 0x0D

//
//! HX8347 Vertical scroll top fixed area register 1.
//
#define HX8347_VERTICAL_SCROLLTOP_1                                           \
                                0x0E

//
//! HX8347 Vertical scroll top fixed area register 2.
//
#define HX8347_VERTICAL_SCROLLTOP_2                                           \
                                0x0F

//
//! HX8347 Vertical scroll height area register 1.
//
#define HX8347_VERTICAL_SCROLLHEIGHT_1                                        \
                                0x10

//
//! HX8347 Vertical scroll height area register 2.
//
#define HX8347_VERTICAL_SCROLLHEIGHT_2                                        \
                                0x11

//
//! HX8347 Vertical scroll button fixed area register 1
//
#define HX8347_VERTICAL_SCROLLBUTTON_1                                        \
                                0x12

//
//! HX8347 Vertical scroll button fixed area register 2
//
#define HX8347_VERTICAL_SCROLLBUTTON_2                                        \
                                0x13
//
//! HX8347 Vertical scroll start address register 1.
//
#define HX8347_VERTICAL_SCROLLSTART_1                                         \
                                0x14

//
//! HX8347 Vertical scroll start address register 2.
//
#define HX8347_VERTICAL_SCROLLSTART_2                                         \
                                0x15

//
//! HX8347 Memory access control register.
//
#define HX8347_MEMORY_CON       0x16

//
//! HX8347 COLMOD control register.
//
#define HX8347_COLMOD_CON       0x17

//
//! HX8347 OSC control register 1.
//
#define HX8347_OSC_CON_1        0x18

//
//! HX8347 OSC control register 2.
//
#define HX8347_OSC_CON_2        0x19

//
//! HX8347 Power control 1 register.
//
#define HX8347_POWER_CON_1      0x1A

//
//! HX8347 Power control 2 register
//
#define HX8347_POWER_CON_2      0x1B

//
//! HX8347 Power control 3 register
//
#define HX8347_POWER_CON_3      0x1C

//
//! HX8347 Power control 4 register
//
#define HX8347_POWER_CON_4      0x1D

//
//! HX8347 Power control 5 register
//
#define HX8347_POWER_CON_5      0x1E

//
//! HX8347 Power control 6 register
//
#define HX8347_POWER_CON_6      0x1F

//
//! HX8347 Read data register
//
#define HX8347_READ_DATA        0x22

//
//! HX8347 VCOM control 1 register.
//
#define HX8347_VCOM_CON1        0x23

//
//! HX8347 VCOM control 2 register.
//
#define HX8347_VCOM_CON2        0x24

//
//! HX8347 VCOM control 3 register.
//
#define HX8347_VCOM_CON3        0x25

//
//! HX8347 Display control 1 register
//
#define HX8347_DISPLAY_CON1     0x26

//
//! HX8347 Display control 2 register
//
#define HX8347_DISPLAY_CON2     0x27

//
//! HX8347 Display control 3 register.
//
#define HX8347_DISPLAY_CON3     0x28

//
//! HX8347 Frame control register 1.
//
#define HX8347_FRAME_CON1       0x29

//
//! HX8347 Frame control register 2.
//
#define HX8347_FRAME_CON2       0x2A

//
//! HX8347 Frame control register 3.
//
#define HX8347_FRAME_CON3       0x2B

//
//! HX8347 Frame control register 4.
//
#define HX8347_FRAME_CON4       0x2C

//
//! HX8347 Cycle cotrol register 1.
//
#define HX8347_CYCLE_CON1       0x2D

//
//! HX8347 Cycle control register 2.
//
#define HX8347_CYCLE_CON2       0x2E

//
//! HX8347 Display inversion register.
//
#define HX8347_DISPLAY_INVERSION                                             \
                                0x2F

//
//! HX8347 RGB interface control register 1.
//
#define HX8347_RGB_CON1         0x31

//
//! HX8347 RGB interface control register 2.
//
#define HX8347_RGB_CON2         0x32

//
//! HX8347 RGB interface control register 3.
//
#define HX8347_RGB_CON3         0x33

//
//! HX8347 RGB interface control register 4.
//
#define HX8347_RGB_CON4         0x34

//
//! HX8347 Panel characteristic control register.
//
#define HX8347_PANEL_CON        0x36

//
//! HX8347 OTP register 1.
//
#define HX8347_OTP1             0x38

//
//! HX8347 OTP register 2.
//
#define HX8347_OTP2             0x39

//
//! HX8347 OTP register 3.
//
#define HX8347_OTP3             0x3A

//
//! HX8347  OTP register 4.
//
#define HX8347_OTP4             0x3B

//
//! HX8347 CABC control 1 register.
//
#define HX8347_CABC_CON1        0x3C

//
//! HX8347 CABC control 2 register.
//
#define HX8347_CABC_CON2        0x3D

//
//! HX8347 CABC control 3 register.
//
#define HX8347_CABC_CON3        0x3E

//
//! HX8347 CABC control 4 register.
//
#define HX8347_CABC_CON4        0x3F

//
//! HX8347 Gamma control 1 register.
//
#define HX8347_GAMMA_CON1       0x40

//
//! HX8347 Gamma control 2 register.
//
#define HX8347_GAMMA_CON2       0x41

//
//! HX8347 Gamma control 3 register.
//
#define HX8347_GAMMA_CON3       0x42

//
//! HX8347 Gamma control 4 register.
//
#define HX8347_GAMMA_CON4       0x43

//
//! HX8347 Gamma control 5 register.
//
#define HX8347_GAMMA_CON5       0x44

//
//! HX8347 Gamma control 6 register.
//
#define HX8347_GAMMA_CON6       0x45

//
//! HX8347 Gamma control 7 register.
//
#define HX8347_GAMMA_CON7       0x46

//
//! HX8347 Gamma control 8 register.
//
#define HX8347_GAMMA_CON8       0x47

//
//! HX8347 Gamma control 9 register.
//
#define HX8347_GAMMA_CON9       0x48

//
//! HX8347 Gamma control 10 register.
//
#define HX8347_GAMMA_CON10      0x49

//
//! HX8347 Gamma control 11 register.
//
#define HX8347_GAMMA_CON11      0x4A

//
//! HX8347 Gamma control 12 register.
//
#define HX8347_GAMMA_CON12      0x4B

//
//! HX8347 Gamma control 13 register.
//
#define HX8347_GAMMA_CON13      0x4C

//
//! HX8347 Gamma control 14 register.
//
#define HX8347_GAMMA_CON14      0x50

//
//! HX8347 Gamma control 15 register.
//
#define HX8347_GAMMA_CON15      0x51

//
//! HX8347 Gamma control 16 register.
//
#define HX8347_GAMMA_CON16      0x52

//
//! HX8347 Gamma control 17 register.
//
#define HX8347_GAMMA_CON17      0x53

//
//! HX8347 Gamma control 18 register.
//
#define HX8347_GAMMA_CON18      0x54

//
//! HX8347 Gamma control 19 register.
//
#define HX8347_GAMMA_CON19      0x55

//
//! HX8347 Gamma control 20 register.
//
#define HX8347_GAMMA_CON20      0x56

//
//! HX8347 Gamma control 21 register.
//
#define HX8347_GAMMA_CON21      0x57

//
//! HX8347 Gamma control 22 register.
//
#define HX8347_GAMMA_CON22      0x58

//
//! HX8347 Gamma control 23 register.
//
#define HX8347_GAMMA_CON23      0x59

//
//! HX8347 Gamma control 24 register.
//
#define HX8347_GAMMA_CON24      0x5A

//
//! HX8347 Gamma control 25 register.
//
#define HX8347_GAMMA_CON25      0x5B

//
//! HX8347 Gamma control 26 register.
//
#define HX8347_GAMMA_CON26      0x5C

//
//! HX8347 Gamma control 27 register.
//
#define HX8347_GAMMA_CON27      0x5D

//
//! HX8347 TE control register.
//
#define HX8347_TE_CON           0x60

//
//! HX8347 TE output line2 register.
//
#define HX8347_TE_LINE2         0x84

//
//! HX8347 TE output line1 register.
//
#define HX8347_TE_LINE1         0x85

//
//! HX8347 ID register 1.
//
#define HX8347_ID1              0x61

//
//! HX8347 ID register 2.
//
#define HX8347_ID2              0x62

//
//! HX8347 ID register 3.
//
#define HX8347_ID3              0x63

//
//! HX8347 Power saving internal control register 1
//
#define HX8347_POWER_SAVING_CON1                                              \
                                0x68

//
//! HX8347 Power saving internal control register 2
//
#define HX8347_POWER_SAVING_CON2                                              \
                                0x69

//
//! HX8347 Power saving internal control register 3
//
#define HX8347_POWER_SAVING_CON3                                              \
                                0x70

//
//! HX8347 Power saving internal control register 4
//
#define HX8347_POWER_SAVING_CON4                                              \
                                0x71

//
//! HX8347 Source OP control 1
//
#define HX8347_OP_CON1          0xE8

//
//! HX8347 Source OP control 2
//
#define HX8347_OP_CON2          0xE9

//
//! HX8347 Power control internal used register.
//
#define HX8347_POWER_CON_INTERNAL_1                                          \
                                0xEA

//
//!  HX8347 Power control internal used register.
//
#define HX8347_POWER_CON_INTERNAL_2                                           \
                                0xEB

//
//! HX8347 Source control internal used register.
//
#define HX8347_SOURCE_CON_INTERNAL_1                                          \
                                0xEC

//
//! HX8347 Source control internal used register.
//
#define HX8347_SOURCE_CON_INTERNAL_2                                          \
                                0xED

//
//! HX8347 Command page select register.
//
#define HX8347_COMMAND_PAGE_SELECT                                            \
                                0xFF

//
//! HX8347 DGC Control register.
//
#define HX8347_DGC_CON          0x00

//
//! HX8347 DGC LUT register.
//
#define HX8347_DGC_LUT          0x01

//
//! HX8347 CABC control 5 register.
//
#define HX8347_CABC_CON5        0xC3

//
//! HX8347 CABC control 6 register.
//
#define HX8347_CABC_CON6        0xC5

//
//! HX8347 CABC control 7 register.
//
#define HX8347_CABC_CON7        0xC7

//
//! HX8347 Gain select register 0
//
#define HX8347_GAIN_SELECT_0    0xCB

//
//! HX8347 Gain select register 1
//
#define HX8347_GAIN_SELECT_1    0xCC

//
//! HX8347 Gain select register 2
//
#define HX8347_GAIN_SELECT_2    0xCD

//
//! HX8347 Gain select register 3
//
#define HX8347_GAIN_SELECT_3    0xCE

//
//! HX8347 Gain select register 4
//
#define HX8347_GAIN_SELECT_4    0xCF

//
//! HX8347 Gain select register 5
//
#define HX8347_GAIN_SELECT_5    0xD0

//
//! HX8347 Gain select register 6
//
#define HX8347_GAIN_SELECT_6    0xD1

//
//! HX8347 Gain select register 7
//
#define HX8347_GAIN_SELECT_7    0xD2

//
//! HX8347 Gain select register 8
//
#define HX8347_GAIN_SELECT_8    0xD3

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_DISPLAY_CON1 HX8347_DISPLAY_CON1
//! \brief Defines for the bit fields in the Display control 1 register.
//! @{
//
//*****************************************************************************

//
//!  ISC data mask
// 
#define HX8347_DISPLAY_CON1_ISC_M                                             \
                                0x0F

//
//!  ISC shift
//
#define HX8347_DISPLAY_CON1_ISC_S                                             \
                                0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
                                  
//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_DISPLAY_CON2 HX8347_DISPLAY_CON2
//! \brief Defines for the bit fields in the Display control 2 register.
//! @{
//
//*****************************************************************************

//
//!  REF bit. Refresh display in non-display area in Partial mode enable bit.
// 
#define HX8347_DISPLAY_CON2_REF 0x01
                                  
//
//!  PTG bit. Specify the scan mode of gate driver in non-display area.
// 
#define HX8347_DISPLAY_CON2_PTG 0x02

//
//!  PTV. specify the scan mode of VCOM in non-display area.
//
#define HX8347_DISPLAY_CON2_NORMAL                                            \
                                0x00
#define HX8347_DISPLAY_CON2_VCOML                                             \
                                0X10
#define HX8347_DISPLAY_CON2_GND 0x20
#define HX8347_DISPLAY_CON2_INHIBITED                                         \
                                0x30
//
//! PT bits mask
//
#define HX8347_DISPLAY_CON2_PT_M                                              \
                                0x3
//
//! PT bits shift
//
#define HX8347_DISPLAY_CON2_PT_S                                              \
                                6
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_DISPLAY_CON3 HX8347_DISPLAY_CON3
//! \brief Defines for the bit fields in the Display control 3 register.
//! @{
//
//*****************************************************************************

//
//! when D0=0, D1=0, source output is VSSD, Gate-Driver Control signals is halt
// 
#define HX8347_DISPLAY_CON3_MODE1  0x00

//
//! when D0=1, D1=0, source output is VSSD, Gate-Driver Control signals is 
//! operate.
// 
#define HX8347_DISPLAY_CON3_MODE2  0x04                                 

//
//! when D0=1, D1=0, source output is PT(0,0), Gate-Driver Control signals is 
//! operate.
// 
#define HX8347_DISPLAY_CON3_MODE3  0x08

//
//! when D0=1, D1=1, source output is Display, Gate-Driver Control signals is 
//! operate.
// 
#define HX8347_DISPLAY_CON3_MODE4  0x0C  

//
//! Set gate output.
//
#define HX8347_DISPLAY_CON3_VGH    0x00
#define HX8347_DISPLAY_CON3_VGL    0x20
#define HX8347_DISPLAY_CON3_VGHL   0x30
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_OSC_CON_1 HX8347_OSC_CON_1
//! \brief Defines for the bit fields in the OSC control 1 register.
//! @{
//
//*****************************************************************************

//
//! N/P_RADJ internal osc frequency adjusts in normal/Partial mode mask.
// 
#define HX8347_OSC_CON_NP_M     0xF

//
//! N/P_RADJ internal osc frequency adjusts in normal/Partial mode shift.
// 
#define HX8347_OSC_CON_NP_S     0

//
//! N/P_RADJ internal osc frequency adjusts in idle/Partial idle mode mask.
// 
#define HX8347_OSC_CON_NPI_M    0xF

//
//! N/P_RADJ internal osc frequency adjusts in idle/Partial idle mode shift.
// 
#define HX8347_OSC_CON_NPI_S    4
                              
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_OSC_CON_2 HX8347_OSC_CON_2
//! \brief Defines for the bit fields in the OSC control 1 register.
//! @{
//
//*****************************************************************************

//
//! Enable internal oscillator enable.
// 
#define HX8347_OSC_CON_OSCEN    0x1
                              
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_MODE_CR HX8347_MODE_CR
//! \brief Defines for the bit fields in the Display mode control register.
//! @{
//
//*****************************************************************************

//
//! Turn on Partial mode.
//
#define HX8347_MODE_CR_PTLON    0x1

//
//! Display inversion mode enable bit.
//
#define HX8347_MODE_CR_INVO     0x2 

//
//! Enable idle mode.
//
#define HX8347_MODE_CR_IDMON    0x4

//
//! Turn on scroll mode.
//
#define HX8347_MODE_CR__SCROLL  0x8

//
//! Deep standy standby mode setting
//
#define HX8347_MODE_CR_STBS     0x40

//
//! Standy standby mode setting bit
//
#define HX8347_MODE_CR_STB     0x80
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_POWER_CON_6 HX8347_POWER_CON_6
//! \brief Defines for the bit fields in the power control 6 register.
//! @{
//
//*****************************************************************************

//
//! Specify on control of step-up circuit 2 for VCL, VGL voltage generation.
//
#define HX8347_POWER_CON_6_PON  0x10

//
//! Specify on control of step-up circuit 1 for DDVDH voltage generation.
//
#define HX8347_POWER_CON_6_DK   0x08

//
//! Enter standby mode.
//
#define HX8347_POWER_CON_6_STB  0x01

//
//! Specify the ratio of step_up circuit for DDVDH voltage generation.
//
#define HX8347_POWER_CON_6_XDK  0x04

//
//! Specify the ratio of step_up circuit for DDVDH voltage generation.
//
#define HX8347_POWER_CON_6_DDVDH                                              \
                                0x02

//
//! Stand for abnormal power-off monitor function when the power is off.
//
#define HX8347_POWER_CON_6_GASEN                                              \
                                0x80

//
//! Set VCOML voltage can output to negative voltage
//
#define HX8347_POWER_CON_6_VCOMG                                              \
                                0x40
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_COLMOD_CON HX8347_COLMOD_CON
//! \brief Defines for the bit fields in the COLMOD control register.
//! @{
//
//*****************************************************************************

//
//! System interface format.
// 
#define HX8347_COLMOD_CON_SYS12 0x03
#define HX8347_COLMOD_CON_SYS16 0x05
#define HX8347_COLMOD_CON_SYS18 0x06
#define HX8347_COLMOD_CON_SYS18_2                                             \
                                0x07

//
//! RGB interface format.
//
#define HX8347_COLMOD_CON_RGB16 0x50
#define HX8347_COLMOD_CON_RGB18 0x60
#define HX8347_COLMOD_CON_RGB6  0xE0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_PANEL_CON HX8347_PANEL_CON
//! \brief Defines for the bit fields in panel characteristic control register.
//! @{
//
//*****************************************************************************

//
//! The source output data polarity selected.
// 
#define HX8347_PANEL_CON_REV    0x02

//
//! The color filter order direction selected.
//
#define HX8347_PANEL_CON_BGR    0x01

//
//! The gate driver output shift direction selected.
//
#define HX8347_PANEL_CON_GS     0x04

//
//! The source driver output shift direction selected.
//
#define HX8347_PANEL_CON_ss     0x08
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_MEMORY_CON HX8347_MEMORY_CON
//! \brief Defines for the bit fields in memory access control register.
//! @{
//
//*****************************************************************************

//
//! The source output data polarity selected.
// 
#define HX8347_PANEL_CON_REV    0x02

//
//! Page address order.
//
#define HX8347_MEMORY_CON_MY    0x80

//
//! `Column address order.
//
#define HX8347_MEMORY_CON_MX    0x40

//
//!  Page/Column selection. 
//
#define HX8347_MEMORY_CON_MV    0x20

//
//! Vertical order.
//
#define HX8347_MEMORY_CON_ML    0x10

//
//! RGB-BGR order.
//
#define HX8347_MEMORY_CON_BGR   0x08
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_COLUMN_ADDRSTR HX8347_COLUMN_ADDRSTR
//! \brief Defines for the bit fields in column address start register.
//! @{
//
//*****************************************************************************

//
//! Column address start register byte mask.
// 
#define HX8347_COLUMN_ADDRSTR_M 0xFF

//
//! Column address start register upper byte shift.
//
#define HX8347_COLUMN_ADDRSTR_1_S                                             \
                                8
//
//! Column address start register low byte shift.
//
#define HX8347_COLUMN_ADDRSTR_2_S                                             \
                                0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_COLUMN_ADDREND HX8347_COLUMN_ADDREND
//! \brief Defines for the bit fields in column address end register.
//! @{
//
//*****************************************************************************

//
//! Column address end register byte mask.
// 
#define HX8347_COLUMN_ADDREND_M 0xFF

//
//! Column address end register low byte shift.
//
#define HX8347_COLUMN_ADDREND_2_S                                            \
                                0

//
//! Column address end register upper byte shift.
//
#define HX8347_COLUMN_ADDREND_1_S                                            \
                                8
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_ROW_ADDRSTR HX8347_ROW_ADDRSTR
//! \brief Defines for the bit fields in row address start register.
//! @{
//
//*****************************************************************************

//
//! Row address start register byte mask.
// 
#define HX8347_ROW_ADDRSTR_M 0xFF

//
//! Row address start register low byte shift.
//
#define HX8347_ROW_ADDRSTR_2_S                                                \
                             0

//
//! Row address start register upper byte shift.
//
#define HX8347_ROW_ADDRSTR_1_S                                                \
                             8
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HX8347_Register_HX8347_ROW_ADDRSTR HX8347_ROW_ADDRSTR
//! \brief Defines for the bit fields in row address end register.
//! @{
//
//*****************************************************************************

//
//! Row address end register byte mask.
// 
#define HX8347_ROW_ADDREND_M 0xFF

//
//! Row address end register low byte shift.
//
#define HX8347_ROW_ADDREND_2_S                                                \
                             0

//
//! Row address end register upper byte shift.
//
#define HX8347_ROW_ADDREND_1_S                                                \
                             8
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
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif // __HW_HX8347_H__
