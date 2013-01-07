//*****************************************************************************
//
//! \file hw_SSD1298.h
//! \brief 240 RGB x 320 TFT LCD Controller SSD1298 Command definition.
//! \version 2.1.1.0
//! \date 12/20/2012
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

#ifndef __HW_SSD1298_H__
#define __HW_SSD1298_H__

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
//! \addtogroup SSD1298
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD1298_Commands SSD1298 Commands/Registers
//! @{
//
//*****************************************************************************
#define SSD1298_OSC_START					0x00
#define	SSD1298_DRIVER_OUTPUT_CONTROL		0x01
#define SSD1298_LCD_DRIVE_AC_CONTROL		0x02
#define SSD1298_POWER_CONTROL_1				0x03
#define SSD1298_DISPLAY_CONTROL				0x07
#define SSD1298_FRAME_CYCLE_CONTROL			0x0B
#define SSD1298_POWER_CONTROL_2				0x0C
#define SSD1298_POWER_CONTROL_3				0x0D
#define SSD1298_POWER_CONTROL_4				0x0E
#define SSD1298_GATESCAN_START_POS			0x0F
#define SSD1298_SLEEP_MODE					0x10
#define SSD1298_ENTRY_MODE_1				0x11
#define SSD1298_ENTRY_MODE_2				0x15
#define SSD1298_POWER_CONTROL_5			`	0x1E
#define SSD1298_RAM_DATA_RW					0x22
#define SSD1298_RAM_DATA_WRITE_MASK_1		0x23
#define SSD1298_RAM_DATA_WRITE_MASK_2		0x24
#define SSD1298_FRAME_FREQUENCY				0x25
#define SSD1298_VCOM_OTP_1					0x28
#define SSD1298_VCOM_OTP_2					0x29
#define SSD1298_GAMA_CONTROL_1				0x30
#define SSD1298_GAMA_CONTROL_2				0x31
#define SSD1298_GAMA_CONTROL_3				0x32
#define SSD1298_GAMA_CONTROL_4				0x33
#define SSD1298_GAMA_CONTROL_5				0x34
#define SSD1298_GAMA_CONTROL_6				0x35
#define SSD1298_GAMA_CONTROL_7				0x36
#define SSD1298_GAMA_CONTROL_8				0x37
#define SSD1298_GAMA_CONTROL_9				0x3A
#define SSD1298_GAMA_CONTROL_10				0x3B
#define SSD1298_VERTICAL_SCROLL_CONTROL_1	0x41
#define SSD1298_VERTICAL_SCROLL_CONTROL_2	0x42
#define SSD1298_HORIZ_RAM_ADDR_POS			0x44
#define SSD1298_VERTC_RAM_ADDR_START_POS	0x45
#define SSD1298_VERTC_RAM_ADDR_END_POS		0x46
#define SSD1298_FIRST_WINDOW_START			0x48
#define SSD1298_FIRST_WINDOW_END			0x49
#define SSD1298_SECOND_WINDOW_START			0x4A
#define SSD1298_SECOND_WINDOW_END			0x4B
#define SSD1298_SET_GDDRAM_X_ADDR_CNT		0x4E
#define SSD1298_SET_GDDRAM_Y_ADDR_CNT		0x4F

#define	R00h		SSD1298_OSC_START//0x00
#define	R01h		SSD1298_DRIVER_OUTPUT_CONTROL//0x01
#define	R02h		SSD1298_LCD_DRIVE_AC_CONTROL//0x02

#define	R07h		SSD1298_DISPLAY_CONTROL//0x07

#define	R0Bh		SSD1298_FRAME_CYCLE_CONTROL//0x0B
#define	R25h		SSD1298_FRAME_FREQUENCY//0x25

#define	R03h		SSD1298_POWER_CONTROL_1//0x03
#define	R0Ch		SSD1298_POWER_CONTROL_2//0x0C
#define	R0Dh		SSD1298_POWER_CONTROL_3//0x0D
#define	R0Eh		SSD1298_POWER_CONTROL_4//0x0E
#define	R1Eh		SSD1298_POWER_CONTROL_5//0x1E

#define	R0Fh		SSD1298_GATESCAN_START_POS//0x0F
#define	R10h		SSD1298_SLEEP_MODE//0x10
#define	R11h		SSD1298_ENTRY_MODE_1//0x11
#define	R15h		SSD1298_ENTRY_MODE_2//0x15

#define	R22h		SSD1298_RAM_DATA_RW//0x22
#define	R23h		SSD1298_RAM_DATA_WRITE_MASK_1//0x23
#define	R24h		SSD1298_RAM_DATA_WRITE_MASK_2//0x24

#define	R28h		SSD1298_VCOM_OTP_1//0x28
#define	R29h		SSD1298_VCOM_OTP_2//0x29
#define	R30h		SSD1298_GAMA_CONTROL_1//0x30
#define	R31h		SSD1298_GAMA_CONTROL_2//0x31
#define	R32h		SSD1298_GAMA_CONTROL_3//0x32
#define	R33h		SSD1298_GAMA_CONTROL_4//0x33
#define	R34h		SSD1298_GAMA_CONTROL_5//0x34
#define	R35h		SSD1298_GAMA_CONTROL_6//0x35
#define	R36h		SSD1298_GAMA_CONTROL_7//0x36
#define	R37h		SSD1298_GAMA_CONTROL_8//0x37
#define	R3Ah		SSD1298_GAMA_CONTROL_9//0x3A
#define	R3Bh		SSD1298_GAMA_CONTROL_10//0x3B
#define	R41h		SSD1298_VERTICAL_SCROLL_CONTROL_1//0x41
#define	R42h		SSD1298_VERTICAL_SCROLL_CONTROL_2//0x42
#define	R44h		SSD1298_HORIZ_RAM_ADDR_POS//0x44
#define	R45h		SSD1298_VERTC_RAM_ADDR_START_POS//0x45
#define	R46h		SSD1298_VERTC_RAM_ADDR_END_POS//0x46
#define	R48h		SSD1298_FIRST_WINDOW_START//0x48
#define	R49h		SSD1298_FIRST_WINDOW_END//0x49
#define	R4Ah		SSD1298_SECOND_WINDOW_START//0x4A
#define	R4Bh		SSD1298_SECOND_WINDOW_END//0x4B
#define	R4Eh		SSD1298_SET_GDDRAM_X_ADDR_CNT//0x4E
#define	R4Fh		SSD1298_SET_GDDRAM_Y_ADDR_CNT//0x4F

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
#endif

