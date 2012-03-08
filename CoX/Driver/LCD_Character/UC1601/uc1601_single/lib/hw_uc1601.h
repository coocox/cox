//*****************************************************************************
//
//! \file hw_uc1601.h
//! \brief header file of Driver for uc1601
//! \version V2.1.1.0
//! \date 9/6/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX All rights reserved.
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



#ifndef __HW_UC1601_H__
#define __HW_UC1601_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib 
//! @{
//! \addtogroup Displays
//! @{
//! \addtogroup Text_Displays
//! @{
//! \addtogroup UC1601
//! @{
//! \addtogroup UC1601_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup UC1601_REG UC1601 Register
//! uc1601 Register Command.
//! @{
//
//*****************************************************************************
  
//
//! Write Data Byte to Memory  CD=1,WR=0
//
#define UC1601_WRITE_DATA       0x00 
  
//
//! Read Data Byte from Memory  CD=1,WR=1
//
#define UC1601_READ_DATA        0x00 
  
//
//! Get Status  CD=0,WR=1
//
#define UC1601_GET_STATUS       0x00
  
//
//! Set Column Address LSB  CD=0,WR=0
//
#define UC1601_SET_CA_LSB       0x00  
  
//
//! Set Column Address MSB  CD=0,WR=0
//
#define UC1601_SET_CA_MSB       0x10 
  
//
//! Set Column Address MSB or LSB MASK
//
#define UC1601_SET_CA_MASK      0x0F 
  
//
//! Set Temp. Compensation  CD=0,WR=0
//
#define UC1601_SET_TC           0x24
#define UC1601_SET_TC_MASK      0x03
  
//
//! Set Power Control  CD=0,WR=0
//
#define UC1601_SET_PC           0x28
#define UC1601_SET_PC_MASK      0x07
  
//
//! Set Scroll Line  CD=0,WR=0
//
#define UC1601_SET_SL           0x40
#define UC1601_SET_SL_MASK      0x1F
  
//
//! Set Page Address  CD=0,WR=0
//
#define UC1601_SET_PA           0xB0
#define UC1601_SET_PA_MASK      0x0F
  
//
//! Set VBIAS Potentiometer(double-byte command)  CD=0,WR=0
//
#define UC1601_SET_PM           0x81
#define UC1601_SET_PM_MASK      0xFF
  
//
//! Set Partial Display Control  CD=0,WR=0
//
#define UC1601_SET_PD_EN        0x85
#define UC1601_SET_PD_DIS       0x84
  
//
//! Set RAM Address Control  CD=0,WR=0
//
#define UC1601_SET_AC           0x88
#define UC1601_SET_AC_MASK      0x07
  
//
//! Automatic column/page wrap around.
//! 0: CA or PA (depends on AC[1]= 0 or 1) will stop increasing after reaching
//! boundary
//! 1: CA or PA (depends on AC[1]= 0 or 1) will restart, and CA or PA will 
//! increase by one.
//
#define UC1601_SET_AC_0         0x01
  
//
//! Auto-Increment order
//! 0 : column (CA) increasing (+1) first until CA reach CA boundary, then PA
//! will increase by (+/-1).
//! 1 : page (PA) increasing (+/-1) first until PA reach PA boundary, then CA 
//! will increase by (+1).
//
#define UC1601_SET_AC_1         0x02
  
//
//! PID, page address (PA) auto increment direction ( 0/1 = +/- 1 )
//! When WA=1 and CA reaches CA boundary, PID controls whether page address 
//! will be adjusted by +1 or -1.
//
#define UC1601_SET_AC_2         0x04
  
//
//! Set Frame Rate  CD=0,WR=0
//
#define UC1601_SET_LC3          0xA0
  
//
//! Frame Rate IS 80 frame-per-second
//
#define UC1601_SET_FR_80        0xA0
  
//
//! Frame Rate is 100 frame-per-second
//
#define UC1601_SET_FR_100       0xA1
  
//
//! Set All Pixel ON  CD=0,WR=0
//! Set DC[1] to force all SEG drivers to output ON signals.
//
#define UC1601_SET_DC1          0xA4
#define UC1601_SET_DC1_EN       0xA5
  
//
//! Set Inverse Display  CD=0,WR=0
//! Set DC[0] to force all SEG drivers to output the inverse of the data 
//! (bit-wise) stored in display RAM.
//
#define UC1601_SET_DC0          0xA6
#define UC1601_SET_DC0_EN       0xA7
  
//
//! Set Display Enable  CD=0,WR=0
//! This command is for programming register DC[2]. When DC[2] is set to 1, 
//! UC1601s will first exit from sleep
//! mode, restore the power and then turn on COM drivers and SEG drivers.
//
#define UC1601_SET_DC2          0xAE
#define UC1601_SET_DC2_EN       0xAF
  
//
//! Set LCD Mapping Control  CD=0,WR=0
//! Set LC[2:1] for COM (row) mirror (MY), SEG (column) mirror (MX).
//
#define UC1601_SET_LC21         0xC0
#define UC1601_SET_LC21_MASK    0x06
  
//
//! System Reset  CD=0,WR=0
//! Control register values will be reset to their default values.
//
#define UC1601_SET_SC           0xE2
  
//
//! No Operation  CD=0,WR=0
//
#define UC1601_SET_NOP          0xE3
  
//
//! Set LCD Bias Ratio  CD=0,WR=0
//
#define UC1601_SET_BR           0xE8
#define UC1601_SET_BR_6         0xE8
#define UC1601_SET_BR_7         0xE9
#define UC1601_SET_BR_8         0xEA
#define UC1601_SET_BR_9         0xEB
  
//
//! Set COM End(Double-byte command)  CD=0,WR=0
//
#define UC1601_SET_CEN          0xF1
#define UC1601_SET_CEN_MASK     0x7F
  
//
//! Set Partial Display Start(Double-byte command)  CD=0,WR=0
//
#define UC1601_SET_DST          0xF2
#define UC1601_SET_DST_MASK     0x7F
  
//
//! Set Partial Display End(Double-byte command)  CD=0,WR=0
//
#define UC1601_SET_DEN          0xF3
#define UC1601_SET_DEN_MASK     0x7F
  
//
//! Set Partial Display End(Double-byte command)  CD=0,WR=0
//
#define UC1601_SET_DEN          0xF3
#define UC1601_SET_DEN_MASK     0x7F
  
//
//! Read Data Byte from Memory(Double-byte command)  CD=1,WR=1
//
#define UC1601_READ_DATA_CMD    0xFF
#define UC1601_READ_DATA_MASK   0xFF
  
//
//! Get Status(Double-byte command)  CD=0,WR=1
//
#define UC1601_GET_STATUS_CMD   0xFE
#define UC1601_READ_DATA_MASK   0xFF



//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup uc1601_Attribute uc1601 Attribute
//! uc1601 LCD attribute.
//! @{
//
//*****************************************************************************
  
//
//! BM[1:0] = 00 {DB7, DB6} =10
//
#define UC1601_SPI_8BIT         0
  
//
//! BM[1:0] = 01 {DB7, DB6} =10
//
#define UC1601_SPI_9BIT         1
  
//
//! BM[1:0] = 01 {DB7, DB6} =11
//
#define UC1601_I2C              2
#define UC1601DataAddr          0x3D
#define UC1601CmdAddr           0x3C
  
//
//! BM[1:0] = 10 {DB7, DB6} is data
//
#define UC1601_8080             3
  
//
//! BM[1:0] = 11 {DB7, DB6} is data
//
#define UC1601_6800             4


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
//! @}
//
//*****************************************************************************      



#endif // __HW_UC1601_H__
