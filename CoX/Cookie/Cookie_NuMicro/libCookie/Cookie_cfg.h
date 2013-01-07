//*****************************************************************************
//
//! \file cookie_cfg.h
//! \brief Configuration of Cookie board.
//! \version V2.1.1.0
//! \date 12/29/2011
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

#ifndef __COOKIE_CFG_H__
#define __COOKIE_CFG_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
//extern "C"
//{
#endif

//*****************************************************************************
//
//! \addtogroup Cookie
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_Board_Res
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Compatible 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Config  
//! @{
//
//*****************************************************************************

//
//! Arduino compatible Pin D10 Peripheral Function select, it can be set :
//! - \ref sD10_FUNC_SPI_SS  to set D10 as an SlaveSelect signal of SPI, 
//! - \ref sD10_FUNC_PWM to set D10 as PWM
//! please refrence \ref CS_B_Arduino_Pin_D10_Map.
//
#define sD10_FUNC_MAP           sD10_FUNC_PWM

//
//! Arduino compatible Pin D11 Peripheral Function select, it can be set :
//! - \ref sD11_FUNC_SPI_MOSI  to set D10 as an MOSI signal of SPI, 
//! - \ref sD11_FUNC_PWM to set D11 as PWM
//! please refrence \ref CS_B_Arduino_Pin_D11_Map.
//
#define sD11_FUNC_MAP           sD11_FUNC_PWM    

//
//! Arduino compatible Pin A4 Peripheral Function select, it can be set :
//! - \ref sA4_FUNC_AIN  to set A4 as an Analog input of ADC, 
//! - \ref sA4_FUNC_I2C_SDA to set A4 as SDA signal of I2C
//!
//! please refrence \ref CS_B_Arduino_Pin_A4_Map.
//
#define sA4_FUNC_MAP            sA4_FUNC_AIN

//
//! Arduino compatible Pin A4 Peripheral Function select, it can be set :
//! - \ref sA4_FUNC_AIN  to set A4 as an Analog input of ADC
//! - \ref sA4_FUNC_I2C_SDA to set A4 as SDA signal of I2C
//!
//!please refrence \ref CS_B_Arduino_Pin_A4_Map.
//
#define sA5_FUNC_MAP            sA5_FUNC_AIN

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Pin_D10_Map  
//! @{
//
//*****************************************************************************

#define sD10_FUNC_SPI_SS        0
#define sD10_FUNC_PWM           1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Pin_D11_Map  
//! @{
//
//*****************************************************************************

#define sD11_FUNC_SPI_MOSI      0
#define sD11_FUNC_PWM           1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Pin_A4_Map  
//! @{
//
//*****************************************************************************

#define sA4_FUNC_AIN            0
#define sA4_FUNC_I2C_SDA        1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Pin_A5_Map  
//! @{
//
//*****************************************************************************

#define sA5_FUNC_AIN            0
#define sA5_FUNC_I2C_SCL        1

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

     
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
//}
#endif

#endif // __COOKIE_CFG_H__
