//*****************************************************************************
//
//! \file hw_bh1750fvi.h
//! \brief BH1750FVI Instruction Set definition..
//! \version V2.2.1.0
//! \date 7/17/2012
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

#ifndef __HW_BH1750FVI_H__
#define __HW_BH1750FVI_H__

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
//! \addtogroup Light_Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup BH1750FVI
//! @{
//
//*****************************************************************************   

//*****************************************************************************
//
//! \addtogroup BH1750FVI_Instruction The Instructions of BH1750FVI
//! \brief The instructions of BH1750FVI which will be used to realize different
//! functions 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The instructions of BH1750FVI
//
#define BH1750_INS_POWER_DOWN   0x00
#define BH1750_INS_POWER_ON     0x01
#define BH1750_INS_RESET        0x07

//
//! Continuously H-Resolution Mode
//
#define BH1750_INS_CON_HR_MODE  0x10

//
//! Continuously H-Resolution Mode 2
//
#define BH1750_INS_CON_HR_MODE_2                                              \
                                0x11

//
//! Continuously L-Resolution Mode
//
#define BH1750_INS_CON_LR_MODE  0x13

//
//! One Time H-Resolution Mode 
//
#define BH1750_INS_ONE_HR_MODE  0x20

//
//! One Time H-Resolution Mode2 
//
#define BH1750_INS_ONE_HR_MODE_2                                              \
                                0x21

//
//! One Time L-Resolution Mode
//
#define BH1750_INS_ONE_LR_MODE  0x23

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


#endif // __HW_BH1750FVI_H__

