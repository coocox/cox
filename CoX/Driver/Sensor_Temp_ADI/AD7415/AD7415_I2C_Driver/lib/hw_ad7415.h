//*****************************************************************************
// 
//! \file xhw_ad7415arz.h
//! \brief Macros used when accessing the AD7415ARZ control hardware.
//! \version V2.1.1.0
//! \date 6. Sem. 2011
//! \author  CooCox
//!
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

#ifndef __HW_AD7415_H__
#define __HW_AD7415_H__

//*****************************************************************************
//
//! \addtogroup AD7415
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7415_Register AD7415 Register
//! \brief AD7415 Register ID,which can be passed to point register.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! AD7415 register index Define 
//
//*****************************************************************************

//
//! Temperature Register
//
#define  AD7415_TEMP            0        

//
//! ADC Value Register
//
#define  AD7415_CFG             1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7415_Register_Cfg_CON AD7415 cfg Register configure
//! AD7415 Cfg register definition
//! @{
//
//*****************************************************************************

//
//! Power mode control bit 
//
#define AD7415_CFG_PD_ENABLE    0x80
#define AD7415_CFG_PD_DISABLE   0x00

//
//! I2C Filter control bit
//
#define AD7415_CFG_FILTER_ENABLE                                              \
                                0x40
#define AD7415_CFG_FILTER_DISABLE                                             \
                                0x00

//
//! Initiate a one-shot temperature conversion
//
#define AD7415_CFG_ONE_SHOT_CONVERT                                            \
                                0x04

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

















