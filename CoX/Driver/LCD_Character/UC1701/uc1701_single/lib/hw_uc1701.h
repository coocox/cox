//*****************************************************************************
//
//! \file hw_uc1701.h
//! \brief header file of Driver for uc1701
//! \version V2.1.1.0
//! \date 1/15/2013
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



#ifndef __HW_UC1701_H__
#define __HW_UC1701_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib 
//! @{
//! \addtogroup Displays
//! @{
//! \addtogroup Text_Displays
//! @{
//! \addtogroup UC1701
//! @{
//! \addtogroup UC1701_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup UC1701_REG UC1701 Register
//! uc1701 Register Command.
//! @{
//
//*****************************************************************************
  
//
//! Write Data Byte to Memory  CD=1,WR=0
//
#define UC1701_WRITE_DATA       0x00
  
//
//! Read Data Byte from Memory  CD=1,WR=1
//
#define UC1701_READ_DATA        0x00
  
//
//! Get Status  CD=0,WR=1
//
#define UC1701_GET_STATUS       0x00
  
//
//! Set Column Address LSB  CD=0,WR=0
//
#define UC1701_SET_CA_LSB       0x00
  
//
//! Set Column Address MSB  CD=0,WR=0
//
#define UC1701_SET_CA_MSB       0x10
  
//
//! Set Column Address MSB or LSB MASK
//
#define UC1701_SET_CA_MASK      0x0F

//
//! Set Power Control  CD=0,WR=0
//
#define UC1701_SET_PC           0x28
#define UC1701_SET_PC_MASK      0x07
  
//
//! Set Scroll Line  CD=0,WR=0
//
#define UC1701_SET_SL           0x40
#define UC1701_SET_SL_MASK      0x1F
  
//
//! Set Page Address  CD=0,WR=0
//
#define UC1701_SET_PA           0xB0
#define UC1701_SET_PA_MASK      0x0F
  
//
//! Set VBIAS Potentiometer(double-byte command)  CD=0,WR=0
//
#define UC1701_SET_PM           0x81
#define UC1701_SET_PM_MASK      0x3F
  
//
//! Set All Pixel ON  CD=0,WR=0
//! Set DC[1] to force all SEG drivers to output ON signals.
//
#define UC1701_SET_DC1          0xA4
#define UC1701_SET_DC1_EN       0xA5
  
//
//! Set Inverse Display  CD=0,WR=0
//! Set DC[0] to force all SEG drivers to output the inverse of the data 
//! (bit-wise) stored in display RAM.
//
#define UC1701_SET_DC0          0xA6
#define UC1701_SET_DC0_EN       0xA7
  
//
//! Set Display Enable  CD=0,WR=0
//! This command is for programming register DC[2]. When DC[2] is set to 1, 
//! UC1701s will first exit from sleep
//! mode, restore the power and then turn on COM drivers and SEG drivers.
//
#define UC1701_SET_DC2          0xAE
#define UC1701_SET_DC2_EN       0xAF
  
//
//! Set LCD Mapping Control  CD=0,WR=0
//! Set LC[2:1] for COM (row) mirror (MY), SEG (column) mirror (MX).
//
#define UC1701_SET_LC21         0xC0
#define UC1701_SET_LC21_MASK    0x06
  
//
//! System Reset  CD=0,WR=0
//! Control register values will be reset to their default values.
//
#define UC1701_SET_SC           0xE2
  
//
//! No Operation  CD=0,WR=0
//
#define UC1701_SET_NOP          0xE3
  
//
//! Set LCD Bias Ratio  CD=0,WR=0
//
#define UC1701_SET_BR_MASK             0xA3
#define UC1701_SET_BR_7                      0xA2
#define UC1701_SET_BR_9                      0xA3

//
//! Set SEG	 Direction
//
#define UC1701_SEG_DIR_MASK              0xA1
#define UC1701_SEG_DIR_NORMAL        0xA0
#define UC1701_SET_DIR_INVERSE           0xA1

//
//! Set COM	 Direction
//
#define UC1701_COM_DIR_MASK              0xC8
#define UC1701_COM_DIR_NORMAL        0xC0
#define UC1701_COM_DIR_INVERSE           0xC8
  
//
//! Read Data Byte from Memory(Double-byte command)  CD=1,WR=1
//
#define UC1701_READ_DATA_CMD    0xFF
#define UC1701_READ_DATA_MASK   0xFF
  
//
//! Get Status(Double-byte command)  CD=0,WR=1
//
#define UC1701_GET_STATUS_CMD   0xFE
#define UC1701_READ_DATA_MASK   0xFF



//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup uc1701_Attribute uc1701 Attribute
//! uc1701 LCD attribute.
//! @{
//
//*****************************************************************************
  
//
//! BM[1:0] = 00 {DB7, DB6} =10
//
#define UC1701_SPI_8BIT         0

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



#endif // __HW_UC1701_H__
