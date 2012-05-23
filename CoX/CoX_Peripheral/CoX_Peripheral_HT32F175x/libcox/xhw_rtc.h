//*****************************************************************************
//
//! \file xhw_rtc.h
//! \brief Macros and defines used when accessing the RTC hardware.
//! \version V2.1.1.0
//! \date 5/5/2012
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
//****************************************************************************
#ifndef __XHW_RTC_H__
#define __XHW_RTC_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_RTC_Register HT32F175x/275x RTC Register
//! \brief Here are the detailed info of RTC registers. 
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_RTC_Register_RTC_Address RTC Address Register
//! \brief Defines for the bit fields in the RTC_Register_Address register.
//! @{
//
//*****************************************************************************

//
//! RTC Counter Register (RTCCNT)
//
#define RTC_CNT                 0x4006A000  

//
//! RTC Compare Register
//
#define RTC_CMP                 0x4006A004

//
//! RTC Control Register
//
#define RTC_CR                  0x4006A008

//
//! RTC Status Register
//
#define RTC_SR                  0x4006A00C

//
//! RTC Interrupt and Wakeup Enable Register
//
#define RTC_IWEN                0x4006A010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_RTC_Register_RTC_CNT RTC Counter Register(RTC_CNT)
//! \brief Defines for the bit fields in the RTC_CNT register.
//! @{
//
//*****************************************************************************

//
//! RTC Counter mask
//
#define RTC_CNT_M               0xFFFFFFFF  

//
//! RTC Counter shift
//
#define RTC_CNT_S               0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_RTC_Register_RTC_CMP RTC Compare Register(RTC_CMP)
//! \brief Defines for the bit fields in the RTC_CMP register.
//! @{
//
//*****************************************************************************

//
//! RTC Compare mask
//
#define RTC_CMP_M               0xFFFFFFFF  

//
//! RTC Compare shift
//
#define RTC_CMP_S               0 


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_RTC_Register_RTC_CR RTC Control Register(RTC_CR)
//! \brief Defines for the bit fields in the RTC_CR register.
//! @{
//
//*****************************************************************************

//
//! RTCOUT Level Mode Flag
//
#define RTC_CR_ROLF             0x00100000  

//
//! RTCOUT Output Active Polarity.
//
#define RTC_CR_ROAP             0x00080000  

//
//! RTCOUT Output Waveform Mode
//
#define RTC_CR_ROWM             0x00040000 

//
//! RTCOUT Output Event Selection.
//
#define RTC_CR_ROES             0x00020000 

//
//! RTCOUT Signal Output Enable.
//
#define RTC_CR_ROEN             0x00010000 

//
//! RTC Clock Prescaler Select mask.
//
#define RTC_CR_RPRE_M           0x00000F00 

//
//! RTC Clock Prescaler Select shift.
//
#define RTC_CR_RPRE_S           8

//
//! LSE oscillator Startup Mode.
//
#define RTC_CR_LSESM            0x00000020 

//
//! Compare Match Counter Clear.
//
#define RTC_CR_CMPCLR           0x00000010 

//
//! LSE oscillator Enable.
//
#define RTC_CR_LSEEN            0x00000008 

//
//! LSI oscillator Enable.
//
#define RTC_CR_LSIEN            0x00000004

//
//! RTC Clock Source is LSE.
//
#define RTC_CR_RTCSRC_LSE       0x00000002

//
//! RTC Clock Source is LSI.
//
#define RTC_CR_RTCSRC_LSI       0x00000000

//
//! RTC Enable Control.
//
#define RTC_CR_RTCEN            0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_RTC_Register_RTC_SR RTC Status Register(RTC_SR)
//! \brief Defines for the bit fields in the RTC_SR register
//! @{
//
//*****************************************************************************

//
//! Counter Overflow Flag
//
#define RTC_SR_OVFLAG           0x00000004  

//
//! Compare Match Condition Flag
//
#define RTC_SR_CMFLAG           0x00000002 

//
//! CK_SECOND Occurrence Flag
//
#define RTC_SR_CSECFLAG         0x00000001 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_RTC_Register_RTC_IWEN RTC Interrupt and Wakeup Register(RTC_IWEN)
//! \brief Defines for the bit fields in the RTC_IWEN register
//! @{
//
//*****************************************************************************

//
//! Counter Overflow Wakeup Enable
//
#define RTC_IWEN_OVWEN          0x00000400

//
//! Compare Match Wakeup Enable
//
#define RTC_IWEN_CMWEN          0x00000200

//
//! Counter Clock CK_SECOND Wakeup Enable
//
#define RTC_IWEN_CSECWEN        0x00000100

//
//! Counter Overflow Interrupt Enable
//
#define RTC_IWEN_OVIEN          0x00000004

//
//! Compare Match Interrupt Enable
//
#define RTC_IWEN_CMIEN          0x00000002

//
//! Counter Clock CK_SECOND Interrupt Enable
//
#define RTC_IWEN_CSECIEN        0x00000001

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

#endif // __XHW_RTC_H__


