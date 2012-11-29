//*****************************************************************************
//
//! \file hw_SSD2119.h
//! \brief Character LCD SSD2119 Command definition.
//! \version 2.1.1.0
//! \date 10/18/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX 
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

#ifndef __HW_SSD2119_H__
#define __HW_SSD2119_H__

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
//! \addtogroup LCD_Character
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Registers SSD2119 Registers
//! @{
//
//*****************************************************************************

#define SSD2119_DEVICE_CODE_READ_REG                                          \
                                0x00
#define SSD2119_OSC_START_REG   0x00
#define SSD2119_OUTPUT_CTRL_REG 0x01
#define SSD2119_LCD_DRIVE_AC_CTRL_REG                                         \
                                0x02
#define SSD2119_PWR_CTRL_1_REG  0x03
#define SSD2119_DISPLAY_CTRL_REG                                              \
                                0x07
#define SSD2119_FRAME_CYCLE_CTRL_REG                                          \
                                0x0B
#define SSD2119_PWR_CTRL_2_REG  0x0C
#define SSD2119_PWR_CTRL_3_REG  0x0D
#define SSD2119_PWR_CTRL_4_REG  0x0E
#define SSD2119_GATE_SCAN_START_REG                                           \
                                0x0F
#define SSD2119_SLEEP_MODE_1_REG                                              \
                                0x10
#define SSD2119_ENTRY_MODE_REG  0x11
#define SSD2119_GEN_IF_CTRL_REG 0x15
#define SSD2119_PWR_CTRL_5_REG  0x1E
#define SSD2119_RAM_DATA_REG    0x22
#define SSD2119_FRAME_FREQ_REG  0x25
#define SSD2119_VCOM_OTP_1_REG  0x28
#define SSD2119_VCOM_OTP_2_REG  0x29
#define SSD2119_GAMMA_CTRL_1_REG                                              \
                                0x30
#define SSD2119_GAMMA_CTRL_2_REG                                              \
                                0x31
#define SSD2119_GAMMA_CTRL_3_REG                                              \
                                0x32
#define SSD2119_GAMMA_CTRL_4_REG                                              \
                                0x33
#define SSD2119_GAMMA_CTRL_5_REG                                              \
                                0x34
#define SSD2119_GAMMA_CTRL_6_REG                                              \
                                0x35
#define SSD2119_GAMMA_CTRL_7_REG                                              \
                                0x36
#define SSD2119_GAMMA_CTRL_8_REG                                              \
                                0x37
#define SSD2119_GAMMA_CTRL_9_REG                                              \
                                0x3A
#define SSD2119_GAMMA_CTRL_10_REG                                             \
                                0x3B
#define SSD2119_V_SCROLL_CTRL_1_REG                                           \
                                0x41
#define SSD2119_V_SCROLL_CTRL_2_REG                                           \
                                0x42
#define SSD2119_V_RAM_POS_REG   0x44
#define SSD2119_H_RAM_START_REG 0x45
#define SSD2119_H_RAM_END_REG   0x46
#define SSD2119_SCREEN_1_START_POS_REG                                        \
                                0x48
#define SSD2119_SCREEN_1_END_POS_REG                                          \
                                0x49  
#define SSD2119_SCREEN_2_START_POS_REG                                        \
                                0x4A
#define SSD2119_SCREEN_2_END_POS_REG                                          \
                                0x4B                                         
#define SSD2119_X_RAM_ADDR_REG  0x4E
#define SSD2119_Y_RAM_ADDR_REG  0x4F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_DOC Driver Output Control Set
//! @{
//
//*****************************************************************************
#define SSD2119_OUTPUTCTL_REV   0x30EF

#define SSD2119_OUTPUTCTL_SET(ulConfig)                                       \
                                (ulConfig | 0x30EF)

#define SSD2119_OUTPUT_ORIGIN_UPLEFT                                          \
                                0x4200
#define SSD2119_OUTPUT_ORIGIN_DOWNLEFT                                        \
                                0x4000
#define SSD2119_OUTPUT_ORIGIN_UPRIGHT                                         \
                                0x0200
#define SSD2119_OUTPUT_ORIGIN_DOWNRIGHT                                       \
                                0x0000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_LWC LCD-Driving-Waveform Control Set
//! @{
//
//*****************************************************************************
                                  
#define SSD2119_LCD_WAVEFORM_REV                                              \
                                0x30EF                                 
//
//! It is 3 field driving, which also limit VBP = 1. 
//
#define SSD2119_3DIV_SCR_MODE    0x1000

#define SSD2119_WSYNC_MODE1      0x0800
#define SSD2119_WSYNC_MODE2      0x0900

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_PC1 Power Control 1 Set
//! @{
//
//*****************************************************************************
#define SSD2119_PC1_8COLOR_DTC_SET(ucConfig)                                  \
                                 ((0x0f & ucConfig) << 12)

#define SSD2119_PC1_8COLOR_BT_SET(ucConfig)                                   \
                                 ((0x07 & ucConfig) << 9)	

#define SSD2119_PC1_26KCOLOR_DC_SET(ucConfig)                                 \
                                 ((0x0F & ucConfig) << 4)	

#define SSD2119_PC1_26KCOLOR_AP_SET(ucConfig)                                 \
                                 ((0x0E & ucConfig) << 0)									 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_DC Display Control Set
//! @{
//
//*****************************************************************************
#define SSD2119_DISPLAY_MODE_DEFAULT                                          \
                                0x0033
                                  
#define SSD2119_DISPLAY_MODE_SET(x)                                           \
                                ((x) | 0x0033)                                 

#define SSD2119_SCREEN_TWODIV_ENABLE                                          \
                                0x0100
#define SSD2119_SCREEN_TWODIV_DATA18                                          \
                                0x0200
#define SSD2119_SCREEN_TWODIV_DATA9                                           \
                                0x0600
                                  
#define SSD2119_DISPLAY_8COLOR  0x0008								
								
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_FCC Frame Cycle Control Set
//! @{
//
//*****************************************************************************
#define SSD2119_FCC_NO_SET(ucConfig)                                          \
                                ((ucConfig & 0x3) << 14)

#define SSD2119_FCC_SDT_SET(ucConfig)                                         \
                                ((ucConfig & 0x3) << 12)

#define SSD2119_FCC_EQ_SET(ucConfig)                                          \
                                ((ucConfig & 0x7) << 8)

#define SSD2119_FCC_DIV_SET(ucConfig)                                         \
                                ((ucConfig & 0x3) << 6)	

#define SSD2119_FCC_DIV_ENABLE  0x0020

#define SSD2119_FCC_RTN_ENABLE  0x0010

#define SSD2119_FCC_RTN_SET(ucConfig)                                         \
                                ((ucConfig & 0xF) << 0)	
																
								
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_PC2 Power Control 2 Set
//! @{
//
//*****************************************************************************
#define SSD2119_OUTPUT_VOLTAGE_SET(ulConfig)                                  \
                               (ulConfig & 0x7)
#define SSD2119_OUTPUT_VOLTAGE_5_1V                                           \
                                0x0000
#define SSD2119_OUTPUT_VOLTAGE_5_3V                                           \
                                0x0001
#define SSD2119_OUTPUT_VOLTAGE_5_5V                                           \
                                0x0002
#define SSD2119_OUTPUT_VOLTAGE_5_7V                                           \
                                0x0003
#define SSD2119_OUTPUT_VOLTAGE_5_9V                                           \
                                0x0004                                  
#define SSD2119_OUTPUT_VOLTAGE_6_1V                                           \
                                0x0005
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_PC3 Power Control 3 Set
//! @{
//
//*****************************************************************************
#define SSD2119_VLCD63_SET(ulConfig)                                          \
                                (ulConfig)
                                  
#define SSD2119_VREF_TIMES_1_78 0x0003
#define SSD2119_VREF_TIMES_1_85 0x0004
#define SSD2119_VREF_TIMES_1_93 0x0005
#define SSD2119_VREF_TIMES_2_02 0x0006
#define SSD2119_VREF_TIMES_2_09 0x0007
#define SSD2119_VREF_TIMES_2_165                                              \
                                0x0008
#define SSD2119_VREF_TIMES_2_245                                              \
                                0x0009
#define SSD2119_VREF_TIMES_2_335                                              \
                                0x000A
#define SSD2119_VREF_TIMES_2_40 0x000B
#define SSD2119_VREF_TIMES_2_45 0x000C
#define SSD2119_VREF_TIMES_2_57 0x000D
#define SSD2119_VREF_TIMES_2_645                                              \
                                0x000E                                 
#define SSD2119_VREF_TIMES_2_725                                              \
                                0x000F
#define SSD2119_VREF_TIMES_2_81 0x0000
#define SSD2119_VREF_TIMES_2_90 0x0001
#define SSD2119_VREF_TIMES_3_00 0x0002 

#define SSD2119_VREF_VOLTAGE    2.0     
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_PC4 Power Control 4 Set
//! @{
//
//*****************************************************************************

#define SSD2119_VCOM_SET(ulConfig)                                            \
                                (ulConfig)
                               
#define SSD2119_VLCD63_TIMES_0_60                                             \
                                0x2000	
#define SSD2119_VLCD63_TIMES_0_63                                             \
                                0x2100
#define SSD2119_VLCD63_TIMES_0_66                                             \
                                0x2200
#define SSD2119_VLCD63_TIMES_0_69                                             \
                                0x2300
#define SSD2119_VLCD63_TIMES_0_72                                             \
                                0x2400
#define SSD2119_VLCD63_TIMES_0_75                                             \
                                0x2500
#define SSD2119_VLCD63_TIMES_0_78                                             \
                                0x2600
#define SSD2119_VLCD63_TIMES_0_81                                             \
                                0x2700
#define SSD2119_VLCD63_TIMES_0_84                                             \
                                0x2800
#define SSD2119_VLCD63_TIMES_0_87                                             \
                                0x2900
#define SSD2119_VLCD63_TIMES_0_90                                             \
                                0x2A00
#define SSD2119_VLCD63_TIMES_0_93                                             \
                                0x2B00 
#define SSD2119_VLCD63_TIMES_0_96                                             \
                                0x2C00 
#define SSD2119_VLCD63_TIMES_0_99                                             \
                                0x2D00
#define SSD2119_VLCD63_TIMES_1_02                                             \
                                0x2E00 
#define SSD2119_VLCD63_TIMES_1_05                                             \
                                0x3000 
#define SSD2119_VLCD63_TIMES_1_08                                             \
                                0x3100 
#define SSD2119_VLCD63_TIMES_1_11                                             \
                                0x3200 
#define SSD2119_VLCD63_TIMES_1_14                                             \
                                0x3300 
#define SSD2119_VLCD63_TIMES_1_17                                             \
                                0x3400
#define SSD2119_VLCD63_TIMES_1_20                                             \
                                0x3500 
#define SSD2119_VLCD63_TIMES_1_23                                             \
                                0x3600  
#define SSD2119_VLCD63_TIMES_EXT                                              \
                                0x2F00                                 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_GSP Gate Scan Position Set(0 ~ 240)
//! @{
//
//*****************************************************************************

#define SSD2119_SCN_STAART_GATE_SET(ulConfig)                                 \
                                (ulConfig & 0x1FF)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_SLP Sleep Mode Set
//! @{
//
//*****************************************************************************
                                  
#define SSD2119_SLEEP_MODE_ENTER                                              \
                                0x0001
#define SSD2119_SLEEP_MODE_EXIT 0x0000
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************                                 
                                  
//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_EM Entry Mode Set
//! @{
//
//*****************************************************************************
#define SSD2119_ENTRY_MODE_DEFAULT                                            \
                                0x6830
#define SSD2119_ENTRY_MODE_SET(x)                                             \
                                ((SSD2119_ENTRY_MODE_DEFAULT & 0xFF00) | (x))
                                  
#define SSD2119_EM_VSYNC_INPUT  0x8000

#define SSD2119_EM_65KCOLOR     0x6000

#define SSD2119_EM_262KCOLOR    0x4000

#define SSD2119_EM_HVSYNC_OFF   0x0800

#define SSD2119_EM_RAM_RGB      0x0400

#define SSD2119_EM_RAM_SPI      0x0000

#define SSD2119_EM_DM_CHANGE_IMMEDIATELY                                      \
                                0x0200
#define SSD2119_EM_DM_CHANNGE_START                                           \
                                0x0000
							
#define SSD2119_EM_CLOCK_OSC    0x0100

#define SSD2119_EM_CLOCK_DOTCLK 0x0000

#define SSD2119_EM_262K_TY_A    0x0000
#define SSD2119_EM_262K_TY_B    0x0040
#define SSD2119_EM_262K_TY_C    0x0080

#define SSD2119_EM_ADDR_INC     0x0010
#define SSD2119_EM_ADDR_DEC     0x0000

#define SSD2119_EM_DIRECTION_H  0x0000
#define SSD2119_EM_DIRECTION_V  0x0008							

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_GIC Generic Interface Control Set
//! @{
//
//*****************************************************************************

#define SSD2119_GIC_LATCH_POS   0x0000
#define SSD2119_GIC_LATCH_NEG   0x0008

#define SSD2119_GIC_DEN_H       0x0000
#define SSD2119_GIC_DEN_L       0x0004

#define SSD2119_GIC_VHS_H       0x0002
#define SSD2119_GIC_VHS_L       0x0000

#define SSD2119_GIC_VVS_H       0x0001
#define SSD2119_GIC_VVS_L       0x0000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_PC5  Power Control 5 Set
//! @{
//
//*****************************************************************************

#define SSD2119_VCOMH_SET(ulConfig)                                           \
                                (ulConfig | 0xFF)
#define SSD2119_VCOMH_OTP       0x0000
#define SSD2119_VLCD_TIMES_0_36 0x0080
#define SSD2119_VLCD_TIMES_0_37 0x0081
#define SSD2119_VLCD_TIMES_0_38 0x0082
#define SSD2119_VLCD_TIMES_0_39 0x0083
#define SSD2119_VLCD_TIMES_0_40 0x0084
#define SSD2119_VLCD_TIMES_0_41 0x0085
#define SSD2119_VLCD_TIMES_0_42 0x0086
#define SSD2119_VLCD_TIMES_0_43 0x0087
#define SSD2119_VLCD_TIMES_0_44 0x0088
#define SSD2119_VLCD_TIMES_0_45 0x0089
#define SSD2119_VLCD_TIMES_0_46 0x008A
#define SSD2119_VLCD_TIMES_0_47 0x008B
#define SSD2119_VLCD_TIMES_0_48 0x008C
#define SSD2119_VLCD_TIMES_0_49 0x008D
#define SSD2119_VLCD_TIMES_0_50 0x008E
#define SSD2119_VLCD_TIMES_0_51 0x008F
#define SSD2119_VLCD_TIMES_0_52 0x0090
#define SSD2119_VLCD_TIMES_0_53 0x0091
#define SSD2119_VLCD_TIMES_0_54 0x0092
#define SSD2119_VLCD_TIMES_0_55 0x0093
#define SSD2119_VLCD_TIMES_0_56 0x0094
#define SSD2119_VLCD_TIMES_0_57 0x0095
#define SSD2119_VLCD_TIMES_0_58 0x0096
#define SSD2119_VLCD_TIMES_0_59 0x0097
#define SSD2119_VLCD_TIMES_0_60 0x0098
#define SSD2119_VLCD_TIMES_0_61 0x0099
#define SSD2119_VLCD_TIMES_0_62 0x009A
#define SSD2119_VLCD_TIMES_0_63 0x009B
#define SSD2119_VLCD_TIMES_0_64 0x009C
#define SSD2119_VLCD_TIMES_0_65 0x009D
#define SSD2119_VLCD_TIMES_0_66 0x009E
#define SSD2119_VLCD_TIMES_0_67 0x009F
#define SSD2119_VLCD_TIMES_0_68 0x00A0
#define SSD2119_VLCD_TIMES_0_69 0x00A1
#define SSD2119_VLCD_TIMES_0_70 0x00A2
#define SSD2119_VLCD_TIMES_0_71 0x00A3
#define SSD2119_VLCD_TIMES_0_72 0x00A4
#define SSD2119_VLCD_TIMES_0_73 0x00A5
#define SSD2119_VLCD_TIMES_0_74 0x00A6
#define SSD2119_VLCD_TIMES_0_75 0x00A7
#define SSD2119_VLCD_TIMES_0_76 0x00A8
#define SSD2119_VLCD_TIMES_0_77 0x00A9
#define SSD2119_VLCD_TIMES_0_78 0x00AA
#define SSD2119_VLCD_TIMES_0_79 0x00AB
#define SSD2119_VLCD_TIMES_0_80 0x00AC
#define SSD2119_VLCD_TIMES_0_81 0x00AD
#define SSD2119_VLCD_TIMES_0_82 0x00AE
#define SSD2119_VLCD_TIMES_0_83 0x00AF
#define SSD2119_VLCD_TIMES_0_84 0x00B0
#define SSD2119_VLCD_TIMES_0_85 0x00B1
#define SSD2119_VLCD_TIMES_0_86 0x00B2
#define SSD2119_VLCD_TIMES_0_87 0x00B3
#define SSD2119_VLCD_TIMES_0_88 0x00B4
#define SSD2119_VLCD_TIMES_0_89 0x00B5
#define SSD2119_VLCD_TIMES_0_90 0x00B6
#define SSD2119_VLCD_TIMES_0_91 0x00B7
#define SSD2119_VLCD_TIMES_0_92 0x00B8
#define SSD2119_VLCD_TIMES_0_93 0x00B9
#define SSD2119_VLCD_TIMES_0_94 0x00BA
#define SSD2119_VLCD_TIMES_0_95 0x00BB
#define SSD2119_VLCD_TIMES_0_96 0x00BC
#define SSD2119_VLCD_TIMES_0_97 0x00BD
#define SSD2119_VLCD_TIMES_0_98 0x00BE
#define SSD2119_VLCD_TIMES_0_99 0x00BF
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_WR Write Data to GDDRAM
//! @{
//
//*****************************************************************************
                                  
#define SSD2119_WRITE_DATA_M    0x3FFFF
#define SSD2119_WRITE_DATA_S     0     
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_RD Read Data from GDDRAM
//! @{
//
//*****************************************************************************
                                  
#define SSD2119_READ_DATA_M     0x3FFFF
#define SSD2119_READ_DATA_S     0
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Instruction_FFC Frame Frequency Control Set
//! @{
//
//*****************************************************************************

#define SSD2119_FRAME_FREQ_SET(ulConfig)                                      \
                                (ulConfig)
#define SSD2119_FRAME_FREQ_50HZ 0x0000                                
#define SSD2119_FRAME_FREQ_55HZ 0x2000
#define SSD2119_FRAME_FREQ_60HZ 0x5000
#define SSD2119_FRAME_FREQ_65HZ 0x8000
#define SSD2119_FRAME_FREQ_70HZ 0xA000
#define SSD2119_FRAME_FREQ_75HZ 0xC000
#define SSD2119_FRAME_FREQ_80HZ 0xE000                                 
                                  
                                  
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


#endif // __HW_SSD2119_H__
