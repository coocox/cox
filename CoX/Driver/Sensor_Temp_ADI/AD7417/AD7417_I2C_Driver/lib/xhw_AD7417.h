//*****************************************************************************
// 
//! \file xhw_ad7417arz.h
//! \brief Macros used when accessing the AD7417ARZ control hardware.
//! \version V2.1.1.0
//! \date 6. Sem. 2011
//! \author CooCox
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

#ifndef __XHW_AD7417_H__
#define __XHW_AD7417_H__

//*****************************************************************************
//
//! \addtogroup AD7417
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7417_Register  AD7417 Register
//! \brief AD7417 Register ID, which can be passed to AD7417RegRead(), 
//!  AD7417RegWrite().
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! AD7417 register index Define 
//
//*****************************************************************************

//
//! Temperature Register
//
#define  AD7417_TEMP            0        

//
//! Configuration Register1
//
#define  AD7417_CFG1            1        

//
//! THYST SETPOINT REGISTER
//
#define  AD7417_THYS            2      

//
//! TOTI SETPOINT REGISTER
//
#define  AD7417_TOTI            3    

//
//! ADC Value Register
//
#define  AD7417_ADC             4

//
//! Configuration Register2
//
#define  AD7417_CFG2            5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7417_Register_Cfg1_CON AD7417 Register Cfg1 CON 
//! \brief Values that can be used to configure the Cfg1 register
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! AD7417 Cfg1 register definition
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7417_ShutDown_Mode_Cfg AD7417 shut down mode configure
//! \brief Values that can be used to enable or disable shutdown mode.
//! @{
//
//*****************************************************************************

//
//! Select the shut down mode (default mode)
//
#define AD7417_CFG1_SHUTDOWN_ON                                              \
                                0x00000001

//
//! Don't select shut down mode 
//
#define AD7417_CFG1_SHUTDOWN_OFF                                             \
                                0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup AD7417_Temperature_Mode_Cfg AD7417 temperature mode configure
//! \brief Values that can be used to configure OTI mode. Either Temperature
//! mode or ADC mode be configured at one time. 
//! @{
//
//*****************************************************************************

//
//! Select the compare mode
//
#define AD7417_CFG1_OPEMODE_CMP                                              \
                                0x00000000

//
//! Select the int mode
//
#define AD7417_CFG1_OPEMODE_INT                                              \
                                0x00000002
                                
//
//! Select OTI polarity low value 
//
#define AD7417_CFG1_OTIPOLAR_LOW                                             \
                                0x00000000

//
//! Select OTI polarity high value
//
#define AD7417_CFG1_OTIPOLAR_HIGH                                            \
                                0x00000004

//
//! Fault Queue bits mask
//
#define AD7417_CFG1_FAULTQUE_M  0x00000018

// 
//! Fault Queue bits offset
//
#define AD7414_CFG1_FAULTQUE_S  3


//
//! Set the Queue num
//
#define AD7417_CFG1_FAULTQUE_1  0x00000000
#define AD7417_CFG1_FAULTQUE_2  0x00000008
#define AD7417_CFG1_FAULTQUE_4  0x00000010
#define AD7417_CFG1_FAULTQUE_6  0x00000018

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7417_ADC_Channel_Select AD7417 ADC channel select
//! \brief Values that can be used to select ADC convert channel. Either Temperature
//! mode or ADC mode be configured at one time. 
//! @{
//
//*****************************************************************************

//
//! Channel selection bits mask
//
#define AD7417_CFG1_CHNSEL_M    0x000000e0

//
//! Channel selection bits offset
//
#define AD7417_CFG1_CHNSEL_S    5

//
//! Channel value selection
//
#define AD7417_CFG1_CHNSEL_TEMP                                              \
                                0x00000000
#define AD7417_CFG1_CHNSEL_AIN1                                              \
                                0x00000020
#define AD7417_CFG1_CHNSEL_AIN2                                              \
                                0x00000040
#define AD7417_CFG1_CHNSEL_AIN3                                              \
                                0x00000060
#define AD7417_CFG1_CHNSEL_AIN4                                              \
                                0x00000080

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
//! \addtogroup AD7417_Register_Cfg2_CON AD7417 AD7417 Register Cfg2 CON 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! AD7417 CFG2 register definition
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7417_I2C_Filter_Control AD7417 I2C filter control
//! \brief Values that used to enable or disable I2C filter.
//! @{
//
//*****************************************************************************

//
//! I2C filters are enable
//
#define AD7417_CFG2_TEST_0      0x00000000

//
//! I2C filters are disable
//
#define AD7417_CFG2_TEST_1      0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7417_Convert_Mode_Cfg AD7417 convert mode configure
//! \brief Values that used to configure the trigger mode.
//! @{
//
//*****************************************************************************

//
//! Select the conversion as auto mose (conversion every 355us)(defalut)
//
#define AD7417_CFG2_COVMODE_AUTO                                             \
                                0x00000000

//
//! Select the conversion as triger mode
//
#define AD7417_CFG2_COVMODE_TRIGER                                           \
                                0x00000080

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


#endif

















