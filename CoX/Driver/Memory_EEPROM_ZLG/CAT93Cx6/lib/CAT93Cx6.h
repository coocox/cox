//*****************************************************************************
//
//! \file CAT93Cx6.h
//! \brief Prototypes for EEPROM CAT93Cx6 Driver.
//! \version 2.1.1.0
//! \date 10/18/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX 
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

#ifndef _CAT93Cx6_H_
#define _CAT93Cx6_H_

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
//! \addtogroup Memory
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup EEPROM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CAT93Cx6
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CAT93Cx6_Config CAT93Cx6 Driver Configuration
//!
//! \brief Configurations such as the GPIO Pin used should be set before using
//! this driver.
//!    
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CAT93Cx6_Config_Pins CAT93Cx6 Driver Pin Configuration
//!
//! \brief GPIO Pins Configurations that communication with the EEPROM should be
//! set before using this driver.
//!    
//! @{
//
//*****************************************************************************   

#define CAT93Cx6_CS             PA0
#define CAT93Cx6_SCK            PA0
#define CAT93Cx6_DI             PA0
#define CAT93Cx6_DO             PA0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CAT93Cx6_Config_Model CAT93Cx6 Device model Configuration
//!
//! \brief Configure the EEPROM model. such as CAT93C46, CAT93C56, CAT93C66,  
//! CAT93C57, CAT93C86. set before using this driver.
//!    
//! @{
//
//*****************************************************************************

#define CAT93Cx6_DEVICE         CAT93C46

//*****************************************************************************
//
//! @}
//
//*****************************************************************************                                 

//*****************************************************************************
//
//! \addtogroup CAT93Cx6_Config_Register CAT93Cx6 Driver Register Configuration
//!
//! \brief Configure the EEPROM register moudle.
//!    
//! @{
//
//*****************************************************************************
//
//! The CAT93Cx6 register moudle.
//!
//! Can be set to:
//! - CAT93Cx6_REGISTER_X16 - Be organized as X16.
//! - CAT93Cx6_REGISTER_X8 - Be organized as X8.
//! .
//
#define CAT93Cx6_REGISTER_ORGANIZE                                            \
                                CAT93Cx6_REGISTER_X16
								
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
//! \addtogroup CAT93Cx6_Config_Model Device Model
//!
//! \brief CAT93Cx6 Device Model setting. 
//!    
//! @{
//
//*****************************************************************************								
#define CAT93C46                1
#define CAT93C56                2
#define CAT93C66                3
#define CAT93C57                4
#define CAT93C86                5
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CAT93Cx6_Register_Moudle Register Moudle
//!
//! \brief CAT93Cx6 Register Moudle setting. 
//!    
//! @{
//
//*****************************************************************************
//
//! The CAT93Cx6's registers can be organized as 16 bits.
//
#define CAT93Cx6_REGISTER_X16   0

//
//! The CAT93Cx6's registers can be organized as 8 bits.
//
#define CAT93Cx6_REGISTER_X8    1
//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! \addtogroup CAT93Cx6_Exported_APIs  CAT93Cx6 Driver APIs
//! \brief API Reference of CAT93Cx6 Driver.
//! @{
//
//*****************************************************************************
extern void CAT93Cx6_Init(void);
extern void CAT93Cx6_ProgrammOpen(void);
extern void CAT93Cx6_ProgrammClose(void);
extern unsigned long CAT93Cx6_ReadFromAddress(unsigned long ulAddress);
extern unsigned char CAT93Cx6_WriteToAddress(unsigned long ulAddress, unsigned long dat);
extern unsigned char CAT93Cx6_EraseToAddress(unsigned long ulAddress);
extern unsigned char CAT93Cx6_EraseToAll(void);
extern unsigned char CAT93Cx6_WriteToAll(unsigned long dat);

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
}
#endif

#endif //__CAT93Cx6_H__
