//*****************************************************************************
//
//! \file xhw_types.h
//! \brief Common types and macros.
//! \version V2.2.1.0
//! \date 11/20/2011
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

#ifndef __XHW_TYPES_H__
#define __XHW_TYPES_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowLayer_Exported_Types xLowLayer Types
//! \brief Some type definitions.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Define a boolean type, value can be \b xtrue and \b xfalse.
//
//*****************************************************************************
typedef unsigned char xtBoolean;

#ifndef xtrue
#define xtrue 1
#endif

#ifndef xfalse
#define xfalse 0
#endif

//*****************************************************************************
//
//! Event callback function.
//!
//! \param pvCBData is the callback pointer associated with the instance
//!  generating the callback.  This is a value provided by the client during
//! initialization of the instance making the callback.
//! \param ulEvent is the identifier of the asynchronous event which is being
//! notified to the client.
//! \param ulMsgParam is an event-specific parameter.
//! \param pvMsgData is an event-specific data pointer.
//!
//! A function pointer provided to the Cox layer by the application
//! which will be called to notify it of all asynchronous events relating to
//! data transmission or reception.  
//!
//! \return Returns an event-dependent value.
//
//*****************************************************************************
typedef unsigned long (* xtEventCallback)(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowLayer_Hardware_Access xLowLayer Hardware Access
//! \brief Macros for hardware(register) accesses, both direct and 
//! via the bit-band region.
//! @{
//
//*****************************************************************************
#define xHWREG(x)                                                             \
        (*((volatile unsigned long *)(x)))
#define xHWREGH(x)                                                            \
        (*((volatile unsigned short *)(x)))
#define xHWREGB(x)                                                            \
        (*((volatile unsigned char *)(x)))
#define xHWREGBITW(x, b)                                                      \
        xHWREG(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
              (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define xHWREGBITH(x, b)                                                      \
        xHWREGH(((unsigned long)(x) & 0xF0000000) | 0x02000000 |              \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define xHWREGBITB(x, b)                                                      \
        xHWREGB(((unsigned long)(x) & 0xF0000000) | 0x02000000 |              \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))

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

#endif // __XHW_TYPES_H__

