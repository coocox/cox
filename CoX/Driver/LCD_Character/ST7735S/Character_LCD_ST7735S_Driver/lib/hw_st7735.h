//*****************************************************************************
//
//! \file hw_ST7735.h
//! \brief Character LCD ST7735S Command definition.
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

#ifndef __HW_ST7735_H__
#define __HW_ST7735_H__

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
//! \addtogroup ST7735S
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ST7735S_Registers ST7735S Registers
//! @{
//
//*****************************************************************************

#define ST7735_DEVICE_CODE_READ_REG                                          \
                                0x00
#define ST7735_SWRESET_REG      0x01
#define ST7735_RDDID_REG        0x04
#define ST7735_RDDST_REG        0x09
#define ST7735_RDDPM_REG        0x0A
#define ST7735_RDDMADCTL_REG    0x0B
#define ST7735_RDDCOLMOD_REG    0x0C
#define ST7735_RDDIM_REG        0x0D
#define ST7735_RDDSM_REG        0x0E

#define ST7735_SLPIN_REG        0x10
#define ST7735_SLPOUT_REG       0x11
#define ST7735_PTLON_REG        0x12
#define ST7735_NORON_REG        0x13
								
#define ST7735_INVOFF_REG       0x20								
#define ST7735_INVON_REG        0x21
#define ST7735_GAMSET_REG       0x26
#define ST7735_DISPOFF_REG      0x28
#define ST7735_DISPON_REG       0x29
#define ST7735_CASET_REG        0x2A
#define ST7735_RASET_REG        0x2B
#define ST7735_RAMWR_REG        0x2C
#define ST7735_RAMRD_REG        0x2E

#define ST7735_PTLAR_REG        0x30
#define ST7735_TEOFF_REG        0x34
#define ST7735_TEON_REG         0x35
#define ST7735_MADCTL_REG       0x36
#define ST7735_IDMOFF_REG       0x38
#define ST7735_IDMON_REG        0x39
#define ST7735_COLMOD_REG       0x3A

#define ST7735_FRMCTR1_REG      0xB1
#define ST7735_FRMCTR2_REG      0xB2
#define ST7735_FRMCTR3_REG      0xB3
#define ST7735_INVCTR_REG       0xB4
#define ST7735_DISSET5_REG      0xB6

#define ST7735_PWCTR1_REG       0xC0
#define ST7735_PWCTR2_REG       0xC1
#define ST7735_PWCTR3_REG       0xC2
#define ST7735_PWCTR4_REG       0xC3
#define ST7735_PWCTR5_REG       0xC4
#define ST7735_VMCTR1_REG       0xC5
#define ST7735_VMOFCTR_REG      0xC7

#define ST7735_WRID2_REG        0xD1
#define ST7735_WRID3_REG        0xD2
#define ST7735_NVCTR1_REG       0xD9
#define ST7735_RDID1_REG        0xDA
#define ST7735_RDID2_REG        0xDB
#define ST7735_RDID3_REG        0xDC
#define ST7735_NVCTR2_REG       0xDE
#define ST7735_NVCTR3_REG       0xDF

#define ST7735_GAMCTRP1_REG     0xE0
#define ST7735_GAMCTRN1_REG     0xE1

#define ST7735_EXTCTRL_REG      0xF0
#define ST7735_PWCTR6_REG       0xFC
#define ST7735_VCOM4L_REG       0xFF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ST7735S_Instruction_WR Write Data to GDDRAM
//! @{
//
//*****************************************************************************
                                  
#define ST7735_WRITE_DATA_M    0xFF
#define ST7735_WRITE_DATA_S     0     
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ST7735S_Instruction_RD Read Data from GDDRAM
//! @{
//
//*****************************************************************************
                                  
#define ST7735_READ_DATA_M     0xFF
#define ST7735_READ_DATA_S     0
                                  
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


#endif // __HW_ST7735_H__
