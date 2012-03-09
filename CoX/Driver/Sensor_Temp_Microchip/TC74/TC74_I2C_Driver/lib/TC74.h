//*****************************************************************************
//
//! \file TC74.h
//! \brief header file of Driver for TC74
//! \version 1.0
//! \date 9/5/2011
//! \author CooCox
//! \copy
//
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

#ifndef __TC74_H__
#define __TC74_H__

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
//! \addtogroup Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Temperature_Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TC74
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TC74_Address   TC74 Address
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The address of  TC74A0-3.3VAT.
//
//*****************************************************************************

#define  TC74Address   0x48;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TC74_I2C_Set	 TC74 I2C Set
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

#define  XSYSCTL_PERIPH_I2C      xSYSCTL_PERIPH_I2C0
#define  I2C_BASE      I2C0_BASE
#define  I2CSCL_PIN    PA9
#define  I2CDATA_PIN   PA8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TC74_Mode	TC74 Mode
//! Values that can be passed to TC74ModeSet().
//! @{
//
//*****************************************************************************

//
//! TC74 standy mode
//
#define TC74_MODE_STANDBY 0x80

//
//! TC74 normal mode
//
#define TC74_MODE_NORMAL 0x00

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! \addtogroup TC74_Exported_APIs	  TC74 Exported APIs
//! @{
//
//*****************************************************************************

extern void TC74Init(unsigned long ulRate);
extern void TC74DeInit(void);
extern unsigned char TC74RegRead(unsigned char ucReg);
extern void TC74RegWrite(unsigned char ucReg, unsigned char ucValue);
extern void TC74ModeSet(unsigned char ucMode);
extern unsigned char TC74ModeGet(void);
extern xtBoolean TC74DATAReady(void);
extern char TC74TempGet(void);
       
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

#ifdef __cplusplus
}
#endif

#endif 
