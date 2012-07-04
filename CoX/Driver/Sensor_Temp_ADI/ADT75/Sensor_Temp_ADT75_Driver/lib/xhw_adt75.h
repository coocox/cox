//*****************************************************************************
// 
//! \file xhw_adt75.h
//! \brief Macros used when accessing the ADT75 control hardware.
//! \version 1.0
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

#ifndef __XHW_ADT75__
#define __XHW_ADT75__

//*****************************************************************************
//
//! \addtogroup ADT75
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADT75_Register_Point_Address ADT75 Regisrer Pointer Address
//! \brief These value is send to ADDRESS register to select the register which 
//! to be wrote or read.
//! @{
//
//*****************************************************************************

//
//! Temperature register
//
#define  ADT75_REGISTER_TEMP    0x00000000        

//
//! Configuration register
//
#define  ADT75_REGISTER_CFG     0x00000001        

//
//! THYST setpoint register
//
#define  ADT75_REGISTER_THYS    0x00000002      

//
//! TOTI setpoint register
//
#define  ADT75_REGISTER_TOS     0x00000003    

//
//! One shot mode register
//
#define ADT75_REGISTER_ONTSHOT  0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADT75_Register_CON Register Configure
//! \brief ADT75 Cfg register bit fileds definition
//! @{
//
//*****************************************************************************

//
//! Shut down mode 
//
#define ADT75_CFG_POWER_SHOTDOWN                                              \
                                0x00000001

//
//! Normal mode (default mode)
//
#define ADT75_CFG_POWER_NORMAL                                                \
                                0x00000000


//
//! Select the compare mode
//
#define ADT75_CFG_OPEMODE_CMP                                                 \
                                0x00000000

//
//! Select the int mode
//
#define ADT75_CFG_OPEMODE_INT                                                 \
                                0x00000002
                                
//
//! Select OS/ALERT polarity active low 
//
#define ADT75_CFG_OSALERT_LOW                                                 \
                                0x00000000

//
//! Select OS/ALERT polarity active high
//
#define ADT75_CFG_OSALERT_HIGH                                                \
                                0x00000004

//
//!  Over temprature Fault Queue bits mask
//
#define ADT75_CFG_FAULTQUE_MASK                                               \
                                0x00000018
//
//! Queue number configure bits shift
//
#define ADT75_CFG_FAULTQUE_S    0x00000003

//
//! Set the Queue num
//
#define ADT75_CFG_FAULTQUE_1    0x00000000
#define ADT75_CFG_FAULTQUE_2    0x00000008
#define ADT75_CFG_FAULTQUE_4    0x00000010
#define ADT75_CFG_FAULTQUE_6    0x00000018

//
//! Select one shot mode
//
#define ADT75_CFG_MODE_ONTSHOT  0x00000020

//
//! Disable SMBus alert function
//
#define ADT75_CFG_ALERT_ENABLE  0x00000080

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

















