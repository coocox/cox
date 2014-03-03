//*****************************************************************************
//
//! \file      xhw_types.h
//! \brief     Common types and macros.
//! \version   V2.1.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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

#ifndef __xHW_TYPES_H__
#define __xHW_TYPES_H__

#include <stdio.h>


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
//! \brief Bit_define  Byte/Half Word/Word Bit define
//! \note  you can use those bit macro like this to avoid hard-code in your code.
//!        - Bit define
//!          1) BIT_x_y                (x=8/16/32; y=0/1/2/../32)
//!          2) BIT_x_ALL_0            (x=8/16/32; y=0/1/2/../32)
//!          3) BIT_x_ALL_1            (x=8/16/32; y=0/1/2/../32)
//!          Meanning: <x> is data length; <y> is bit postion.
//!        - Bit mask
//!          1) BIT_MASK(Type, Begin, End)
//!          Meaning:
//!             <Type> :is data length, can be one of the following value:
//!                       8  --> Byte
//!                       16 --> Half word
//!                       32 --> Word
//!            <Begin> : is the begin of mask
//!            <End>   : is the end of mask
//!
//!          e.g. if you want to mask bit-5 to bit-13 in a word, then you can
//!               use BIT_MASK(32, 13, 5) to product this mask value 0x00003FE0.
//!
//!               0000 0000 0000 0000 0011 1111 1110 0000
//!                                     .         .
//!                                    /_\       /_\
//!                                     |         |
//!                                     |         |
//!                                    (13)      (5)
//! @{
//
//*****************************************************************************

#define BIT_8_ALL_0             ((unsigned char     ) 0x00)
#define BIT_16_ALL_0            ((unsigned short int) 0x0000)
#define BIT_32_ALL_0            ((unsigned long  int) 0x00000000)

#define BIT_8_ALL_1             ((unsigned char     ) 0xFF)
#define BIT_16_ALL_1            ((unsigned short int) 0xFFFF)
#define BIT_32_ALL_1            ((unsigned long  int) 0xFFFFFFFF)

#define BIT_8_0                 ((unsigned char     ) 0x01)
#define BIT_8_1                 ((unsigned char     ) 0x02)
#define BIT_8_2                 ((unsigned char     ) 0x04)
#define BIT_8_3                 ((unsigned char     ) 0x08)
#define BIT_8_4                 ((unsigned char     ) 0x10)
#define BIT_8_5                 ((unsigned char     ) 0x20)
#define BIT_8_6                 ((unsigned char     ) 0x40)
#define BIT_8_7                 ((unsigned char     ) 0x80)

#define BIT_16_0                ((unsigned short int) 0x0001)
#define BIT_16_1                ((unsigned short int) 0x0002)
#define BIT_16_2                ((unsigned short int) 0x0004)
#define BIT_16_3                ((unsigned short int) 0x0008)
#define BIT_16_4                ((unsigned short int) 0x0010)
#define BIT_16_5                ((unsigned short int) 0x0020)
#define BIT_16_6                ((unsigned short int) 0x0040)
#define BIT_16_7                ((unsigned short int) 0x0080)
#define BIT_16_8                ((unsigned short int) 0x0100)
#define BIT_16_9                ((unsigned short int) 0x0200)
#define BIT_16_10               ((unsigned short int) 0x0400)
#define BIT_16_11               ((unsigned short int) 0x0800)
#define BIT_16_12               ((unsigned short int) 0x1000)
#define BIT_16_13               ((unsigned short int) 0x2000)
#define BIT_16_14               ((unsigned short int) 0x4000)
#define BIT_16_15               ((unsigned short int) 0x8000)

#define BIT_32_0                ((unsigned long  int) 0x00000001)
#define BIT_32_1                ((unsigned long  int) 0x00000002)
#define BIT_32_2                ((unsigned long  int) 0x00000004)
#define BIT_32_3                ((unsigned long  int) 0x00000008)
#define BIT_32_4                ((unsigned long  int) 0x00000010)
#define BIT_32_5                ((unsigned long  int) 0x00000020)
#define BIT_32_6                ((unsigned long  int) 0x00000040)
#define BIT_32_7                ((unsigned long  int) 0x00000080)
#define BIT_32_8                ((unsigned long  int) 0x00000100)
#define BIT_32_9                ((unsigned long  int) 0x00000200)
#define BIT_32_10               ((unsigned long  int) 0x00000400)
#define BIT_32_11               ((unsigned long  int) 0x00000800)
#define BIT_32_12               ((unsigned long  int) 0x00001000)
#define BIT_32_13               ((unsigned long  int) 0x00002000)
#define BIT_32_14               ((unsigned long  int) 0x00004000)
#define BIT_32_15               ((unsigned long  int) 0x00008000)
#define BIT_32_16               ((unsigned long  int) 0x00010000)
#define BIT_32_17               ((unsigned long  int) 0x00020000)
#define BIT_32_18               ((unsigned long  int) 0x00040000)
#define BIT_32_19               ((unsigned long  int) 0x00080000)
#define BIT_32_20               ((unsigned long  int) 0x00100000)
#define BIT_32_21               ((unsigned long  int) 0x00200000)
#define BIT_32_22               ((unsigned long  int) 0x00400000)
#define BIT_32_23               ((unsigned long  int) 0x00800000)
#define BIT_32_24               ((unsigned long  int) 0x01000000)
#define BIT_32_25               ((unsigned long  int) 0x02000000)
#define BIT_32_26               ((unsigned long  int) 0x04000000)
#define BIT_32_27               ((unsigned long  int) 0x08000000)
#define BIT_32_28               ((unsigned long  int) 0x10000000)
#define BIT_32_29               ((unsigned long  int) 0x20000000)
#define BIT_32_30               ((unsigned long  int) 0x40000000)
#define BIT_32_31               ((unsigned long  int) 0x80000000)

//! Mask macro define
//! \note Internal use, User MUST not use those macro
//! @{

#define _M_8_0_P                ((unsigned      char) 0x01)
#define _M_8_1_P                ((unsigned      char) 0x03)
#define _M_8_2_P                ((unsigned      char) 0x07)
#define _M_8_3_P                ((unsigned      char) 0x0F)
#define _M_8_4_P                ((unsigned      char) 0x1F)
#define _M_8_5_P                ((unsigned      char) 0x3F)
#define _M_8_6_P                ((unsigned      char) 0x7F)
#define _M_8_7_P                ((unsigned      char) 0xFF)

#define _M_8_0_N                ((unsigned      char) 0xFF)
#define _M_8_1_N                ((unsigned      char) 0xFE)
#define _M_8_2_N                ((unsigned      char) 0xFC)
#define _M_8_3_N                ((unsigned      char) 0xF8)
#define _M_8_4_N                ((unsigned      char) 0xF0)
#define _M_8_5_N                ((unsigned      char) 0xE0)
#define _M_8_6_N                ((unsigned      char) 0xC0)
#define _M_8_7_N                ((unsigned      char) 0x80)

#define _M_16_0_P               ((unsigned short int) 0x0001)
#define _M_16_1_P               ((unsigned short int) 0x0003)
#define _M_16_2_P               ((unsigned short int) 0x0007)
#define _M_16_3_P               ((unsigned short int) 0x000F)
#define _M_16_4_P               ((unsigned short int) 0x001F)
#define _M_16_5_P               ((unsigned short int) 0x003F)
#define _M_16_6_P               ((unsigned short int) 0x007F)
#define _M_16_7_P               ((unsigned short int) 0x00FF)
#define _M_16_8_P               ((unsigned short int) 0x01FF)
#define _M_16_9_P               ((unsigned short int) 0x03FF)
#define _M_16_10_P              ((unsigned short int) 0x07FF)
#define _M_16_11_P              ((unsigned short int) 0x0FFF)
#define _M_16_12_P              ((unsigned short int) 0x1FFF)
#define _M_16_13_P              ((unsigned short int) 0x3FFF)
#define _M_16_14_P              ((unsigned short int) 0x7FFF)
#define _M_16_15_P              ((unsigned short int) 0xFFFF)

#define _M_16_0_N               ((unsigned short int) 0xFFFF)
#define _M_16_1_N               ((unsigned short int) 0xFFFE)
#define _M_16_2_N               ((unsigned short int) 0xFFFC)
#define _M_16_3_N               ((unsigned short int) 0xFFF8)
#define _M_16_4_N               ((unsigned short int) 0xFFF0)
#define _M_16_5_N               ((unsigned short int) 0xFFE0)
#define _M_16_6_N               ((unsigned short int) 0xFFC0)
#define _M_16_7_N               ((unsigned short int) 0xFF80)
#define _M_16_8_N               ((unsigned short int) 0xFF00)
#define _M_16_9_N               ((unsigned short int) 0xFE00)
#define _M_16_10_N              ((unsigned short int) 0xFC00)
#define _M_16_11_N              ((unsigned short int) 0xF800)
#define _M_16_12_N              ((unsigned short int) 0xF000)
#define _M_16_13_N              ((unsigned short int) 0xE000)
#define _M_16_14_N              ((unsigned short int) 0xC000)
#define _M_16_15_N              ((unsigned short int) 0x8000)

#define _M_32_0_P               ((unsigned long  int) 0x00000001)
#define _M_32_1_P               ((unsigned long  int) 0x00000003)
#define _M_32_2_P               ((unsigned long  int) 0x00000007)
#define _M_32_3_P               ((unsigned long  int) 0x0000000F)
#define _M_32_4_P               ((unsigned long  int) 0x0000001F)
#define _M_32_5_P               ((unsigned long  int) 0x0000003F)
#define _M_32_6_P               ((unsigned long  int) 0x0000007F)
#define _M_32_7_P               ((unsigned long  int) 0x000000FF)
#define _M_32_8_P               ((unsigned long  int) 0x000001FF)
#define _M_32_9_P               ((unsigned long  int) 0x000003FF)
#define _M_32_10_P              ((unsigned long  int) 0x000007FF)
#define _M_32_11_P              ((unsigned long  int) 0x00000FFF)
#define _M_32_12_P              ((unsigned long  int) 0x00001FFF)
#define _M_32_13_P              ((unsigned long  int) 0x00003FFF)
#define _M_32_14_P              ((unsigned long  int) 0x00007FFF)
#define _M_32_15_P              ((unsigned long  int) 0x0000FFFF)
#define _M_32_16_P              ((unsigned long  int) 0x0001FFFF)
#define _M_32_17_P              ((unsigned long  int) 0x0003FFFF)
#define _M_32_18_P              ((unsigned long  int) 0x0007FFFF)
#define _M_32_19_P              ((unsigned long  int) 0x000FFFFF)
#define _M_32_20_P              ((unsigned long  int) 0x001FFFFF)
#define _M_32_21_P              ((unsigned long  int) 0x003FFFFF)
#define _M_32_22_P              ((unsigned long  int) 0x007FFFFF)
#define _M_32_23_P              ((unsigned long  int) 0x00FFFFFF)
#define _M_32_24_P              ((unsigned long  int) 0x01FFFFFF)
#define _M_32_25_P              ((unsigned long  int) 0x03FFFFFF)
#define _M_32_26_P              ((unsigned long  int) 0x07FFFFFF)
#define _M_32_27_P              ((unsigned long  int) 0x0FFFFFFF)
#define _M_32_28_P              ((unsigned long  int) 0x1FFFFFFF)
#define _M_32_29_P              ((unsigned long  int) 0x3FFFFFFF)
#define _M_32_30_P              ((unsigned long  int) 0x7FFFFFFF)
#define _M_32_31_P              ((unsigned long  int) 0xFFFFFFFF)

#define _M_32_0_N               ((unsigned long  int) 0xFFFFFFFF)
#define _M_32_1_N               ((unsigned long  int) 0xFFFFFFFE)
#define _M_32_2_N               ((unsigned long  int) 0xFFFFFFFC)
#define _M_32_3_N               ((unsigned long  int) 0xFFFFFFF8)
#define _M_32_4_N               ((unsigned long  int) 0xFFFFFFF0)
#define _M_32_5_N               ((unsigned long  int) 0xFFFFFFE0)
#define _M_32_6_N               ((unsigned long  int) 0xFFFFFFC0)
#define _M_32_7_N               ((unsigned long  int) 0xFFFFFF80)
#define _M_32_8_N               ((unsigned long  int) 0xFFFFFF00)
#define _M_32_9_N               ((unsigned long  int) 0xFFFFFE00)
#define _M_32_10_N              ((unsigned long  int) 0xFFFFFC00)
#define _M_32_11_N              ((unsigned long  int) 0xFFFFF800)
#define _M_32_12_N              ((unsigned long  int) 0xFFFFF000)
#define _M_32_13_N              ((unsigned long  int) 0xFFFFE000)
#define _M_32_14_N              ((unsigned long  int) 0xFFFFC000)
#define _M_32_15_N              ((unsigned long  int) 0xFFFF8000)
#define _M_32_16_N              ((unsigned long  int) 0xFFFF0000)
#define _M_32_17_N              ((unsigned long  int) 0xFFFE0000)
#define _M_32_18_N              ((unsigned long  int) 0xFFFC0000)
#define _M_32_19_N              ((unsigned long  int) 0xFFF80000)
#define _M_32_20_N              ((unsigned long  int) 0xFFF00000)
#define _M_32_21_N              ((unsigned long  int) 0xFFE00000)
#define _M_32_22_N              ((unsigned long  int) 0xFFC00000)
#define _M_32_23_N              ((unsigned long  int) 0xFF800000)
#define _M_32_24_N              ((unsigned long  int) 0xFF000000)
#define _M_32_25_N              ((unsigned long  int) 0xFE000000)
#define _M_32_26_N              ((unsigned long  int) 0xFC000000)
#define _M_32_27_N              ((unsigned long  int) 0xF8000000)
#define _M_32_28_N              ((unsigned long  int) 0xF0000000)
#define _M_32_29_N              ((unsigned long  int) 0xE0000000)
#define _M_32_30_N              ((unsigned long  int) 0xC0000000)
#define _M_32_31_N              ((unsigned long  int) 0x80000000)

//! @}

#define BIT_MASK(Type, Begin, End) (_M_##Type##_##Begin##_P & _M_##Type##_##End##_N)
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


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

#endif // __xHW_TYPES_H__

