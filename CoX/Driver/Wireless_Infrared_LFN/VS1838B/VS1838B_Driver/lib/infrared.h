//*****************************************************************************
//
//! \file infrared.h
//! \brief Prototypes for the infrared driver APIs.
//! \version V0.0.0.1
//! \date 2/27/2013
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
//*****************************************************************************
#ifndef __INFRARED_H__
#define __INFRARED_H__

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
//! \addtogroup Wireless
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Infrared
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup VS1838B
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup VS1838B_Connection  VS1838B Pin Connection.
//! \note The receive pin must according to timer number and timer channel
//! @{
//
//*****************************************************************************
#define VS1838B_RECEIVER_PIN  PB7
#define VS1838B_TIMER_BASE    xTIMER4_BASE
#define VS1838B_TIMER_CHANNEL xTIMER_CHANNEL1
#define VS1838B_TIMER_INT     xINT_TIMER4
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Infrared_Code  Infrared Code protocol(pulse width).
//! @{
//
//*****************************************************************************

//
//! The time error value should not be smaller than 150 or the decode number may be error
//
#define INFRARED_TIME_ERROR    200
#define INFRARED_CODE_START    4500 //4500us high level pulse stands for start signal
#define INFRARED_CODE_0        560  //560us high level pulse stands for bit 0
#define INFRARED_CODE_1        1690 //1690us high level pulse stands for bit 1
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//
//! timer reload value. Don't need to modify
//
#define MAX_RELOAD_VAL         6000

//
//! This variable can be a flag detected by other program to decide whether decode is OK.
//
extern unsigned char g_ucIRDecodeOK;

//*****************************************************************************
//
//! \addtogroup Exported_APIs  Infrared Decode APIs.
//! @{
//
//*****************************************************************************
extern void IRInit(void);
extern unsigned short IRKeyValueGet(void);
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
#ifdef __cplusplus
extern "C"
}
#endif

#endif
