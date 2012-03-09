//*****************************************************************************
//
//! \file hw_w25x.h
//! \brief W25X Command definition.
//! \version V2.1.1.0
//! \date 10/6/2011
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



#ifndef __HW_W25X_H__
#define __HW_W25X_H__

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
//! \addtogroup SPI_Flash
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup W25X
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup W25X_Instruction The Instructions of W25X
//! \brief The instruction of W25X which will be used to realize different functions 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The instructions of W25X
//
#define W25X_INS_FAST_READ      0x0B
#define W25X_INS_GET_ID         0x90
#define W25X_INS_WRITE_ENABLE   0x06
#define W25X_INS_WRITE_DISABLE  0x04
#define W25X_INS_PAGE_PROGRAM   0x02
#define W25X_INS_READ_SR        0x05
#define W25X_INS_READ_DATA      0x03
#define W25X_INS_CHIP_ERASE     0xc7
#define W25X_INS_SECTOR_ERASE   0x20
#define W25X_INS_BLOCK_ERASE    0xd8
#define W25X_INS_POWER_DOWN     0xb9
#define W25X_INS_WAKE_UP        0xab
#define W25X_INS_WRITE_SR       0x01
#define W25X_INS_FAST_READ_DUAL_OUT                                            \
                                0x3b

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


#endif // __HW_W25X_H__
