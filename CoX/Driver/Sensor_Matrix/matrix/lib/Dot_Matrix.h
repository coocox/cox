//*****************************************************************************
//
//! \file Dot Matrix Shield.h
//! \brief Adafruit DMShield driver.
//! \version V2.1.1.0
//! \date 12/5/2012
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

#ifndef __MOTORSHIELD_H__
#define __MOTORSHIELD_H__

//*****************************************************************************
//
//! \addtogroup CoX_Shield_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DMShield 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DM163 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DMShield_Move_Dir DMShield move direction 
//!  Values that can be passed to DotMatrixRun().
//! @{
//
//*****************************************************************************

//
//! run left
//
#define DM_RUN_LEFT             0x00000000

//
//! run right
//
#define DMS_RUN_RIGHT           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DMShield_Software_Cfg DMShield Softeware Configure 
//! @{
//
//*****************************************************************************

//
//! Config the Dot Matrix Scan freq value
//
#define DM_SCAN_FREQ            5

//
//! Config the timer clock divide value
//
#define DM_SCANDIV_VALUE        1

//
//! Config the timer prescaler value
//
#define DM_SCANPSR_VALUE        99

//
//! Config the timer match value
//
//#define DM_SCANMATCH_VALUE      0x258

//
//! Configure the timer which is used for scan
//
#define DM_SCAN_TIMER           xTIMER0_BASE

//
//! Configure timer's corresponding channel
//
#define DM_SCAN_CHANNEL         xTIMER_CHANNEL0

//
//! Configure the timer scan clock source
//
#define DM_SCAN_CLKSRC          xSYSCTL_TIMER0_MAIN

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DMShield_Exported_APIs DMShied API
//! @{
//
//*****************************************************************************

extern void DM163PinInit(void);
extern void DotMatrixScanTimerInit(unsigned long ulSrcFreq,
		                    unsigned long ulScanFerq);

extern void DotMatrixSetGamma(void);
extern void DotMatrixRunRow(unsigned char ucRow);
extern void DotMatrixOpenLine(unsigned char ucLine);
extern void DotMatrixShowChar(char ch, unsigned char R, unsigned char G, 
                               unsigned char B, long lBias);
extern void DotMatrixShowPic(unsigned char ucIndex);
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

#endif // __MOTORSHIELD_H__
