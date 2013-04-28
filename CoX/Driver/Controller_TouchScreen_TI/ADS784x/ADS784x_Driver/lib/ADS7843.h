//*****************************************************************************
//
//! \file ADS7843.c
//! \brief Driver head file for ADS7843 touch screen controller
//! \version V0.0.1
//! \date 4/27/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2013, CooCox 
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
#ifndef __ADS7843_H__
#define __ADS7843_H__
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
//! \addtogroup Controller
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Touch_Screen_Controller
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADS7843
//! @{
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup ADS7843_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup ADS7843_User_Config
//! \brief User modify filed(according to the hardware connection)
//! @{
//
//*****************************************************************************
#define __DEBUG_PRINT__

#define ADS7843_PIN_CS             PC6
#define ADS7843_PIN_INT            PC4
#define ADS7843_PIN_CLK            PA5
#define ADS7843_PIN_MOSI           PA7
#define ADS7843_PIN_MISO           PA6

#define ADS7843_SPI_BASE           xSPI1_BASE
#define ADS7843_SPI_CLK            SPI1CLK(APP)
#define ADS7843_SPI_MOSI           SPI1MOSI(APP)
#define ADS7843_SPI_MISO           SPI1MISO(FIN)

#ifdef ADS7843_USE_PIN_BUSY
#define ADS7843_PIN_BUSY           PB11
#endif

//
// Enable touch interrupt
//
//#define ADS7843_ENABLE_TOUCH_INT

#define TOUCH_SCREEN_WIDTH         240
#define TOUCH_SCREEN_HEIGHT        320

#define TOUCH_SMAPLE_LEN           8
//#define TOUCH_DISCARD_SAMPLES      1

#define TOUCH_AD_X_MAX             1840
#define TOUCH_AD_X_MIN             200
#define TOUCH_AD_Y_MAX             1830
#define TOUCH_AD_Y_MIN             200//125
//#define TOUCH_AD_Y_MIN_SCREEN      200
#define TOUCH_AD_CALIB_ERROR       80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADS7843_Config ADS7843 Driver Predefines
//! \brief This part defines the slave address and register address of ADS7843.
//! @{
//
//*****************************************************************************
#define ADS7843_READ_X             0xD0
#define ADS7843_READ_Y             0x90
#define ADS7843_READ_IN3           0xA0
#define ADS7843_READ_IN4           0xE0
#define ADS7843_NO_POWERDOWN       0x03

#define TOUCH_STATUS_PENDOWN       0x01
#define TOUCH_STATUS_PENUP         0x02

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup ADS7843_Data_Struct
//! @{
//
//*****************************************************************************
//typedef struct
//{
//	unsigned short x;
//	unsigned short y;
//}TouchPoint;

typedef struct
{
	unsigned short th_ad_left;
	unsigned short th_ad_right;
	unsigned short th_ad_up;
	unsigned short th_ad_down;
	unsigned short last_x;
	unsigned short last_y;
	unsigned short cur_x;
	unsigned short cur_y;
	unsigned char touch_status;
}TouchInfo;

extern TouchInfo tTouchData;
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADS7843_Exported_APIs
//! @{
//
//*****************************************************************************

extern void ADS7843Init(void);

//
//! Read raw value of x,y axis's AD conversion value.
//
extern void ADS7843ReadADXYRaw(unsigned short *x, unsigned short *y);

//
//! Read x,y axis's AD conversion value with software filter.
//
extern void ADS7843ReadADXY(unsigned short *x, unsigned short *y);

//
//! Read x,y coordinate.
//
extern unsigned char ADS7843ReadPiontXY(unsigned short *x, unsigned short *y);

//
//! Get pen status (pen down or pen up).
//
extern unsigned long ADS7843PenInq(void);

//
//! Touch screen calibration.
//
extern unsigned char ADS7843Calibration(void);

//
//! Read single channel of conversion(x,y,IN3,IN4).
//
extern unsigned short ADS7843ReadInputChannel(unsigned char ucChannel);

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
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
