//*****************************************************************************
//
//! \file hw_M24LCxx.h
//! \brief header file of Driver for M24LCxx
//! \version V2.1.1.0
//! \date 6/1/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
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



#ifndef __HW_M24LCxx_H__
#define __HW_M24LCxx_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib 
//! @{
//! \addtogroup Memory
//! @{
//! \addtogroup I2C_Eeprom
//! @{
//! \addtogroup M24LCxx
//! @{
//! \addtogroup M24LCxx_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M24LCxx_Attribute
//! M24LCxx I2C attribute.
//! @{
//
//*****************************************************************************

//
//! M24LC01 SIZE
//
#define M24LC01_PAGE_SIZE        8UL
#define M24LC01_SIZE             128UL

//
//! M24LC02 SIZE
//
#define M24LC02_PAGE_SIZE        8UL
#define M24LC02_SIZE             256UL

//
//! M24LC04 SIZE
//
#define M24LC04_PAGE_SIZE        16UL
#define M24LC04_SIZE             512UL

//
//! M24LC08 SIZE
//
#define M24LC08_PAGE_SIZE        16UL
#define M24LC08_SIZE             1024UL

//
//! M24LC16 SIZE
//
#define M24LC16_PAGE_SIZE        16UL
#define M24LC16_SIZE             2408UL

//
//! M24LC32 SIZE
//
#define M24LC32_PAGE_SIZE        32UL
#define M24LC32_SIZE             4096UL

//
//! M24LC64 SIZE
//
#define M24LC64_PAGE_SIZE        32UL
#define M24LC64_SIZE             8192UL

#define M24LC01                  0
#define M24LC02                  1
#define M24LC04                  2
#define M24LC08                  3
#define M24LC16                  4
#define M24LC32                  5
#define M24LC64                  6

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



#endif // __HW_M24LCxx_H__
