//*****************************************************************************
//
//! \file hw_SST25VFxx.h
//! \brief header file of Driver for SST25VFxx
//! \version V2.1.1.0
//! \date 9/6/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX All rights reserved.
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



#ifndef __HW_SST25VFXX_H__
#define __HW_SST25VFXX_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib 
//! @{
//! \addtogroup Memory
//! @{
//! \addtogroup SPI_Flash
//! @{
//! \addtogroup SST25VFxx
//! @{
//! \addtogroup SST25VFxx_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SST25VFxx_CMD
//! SST25VFxx SPI Flash CMD.
//! @{
//
//*****************************************************************************
  
//
//! Read Memory at 25 MHz
//
#define SST25VFxx_CMD_RD25      0x03
   
//
//! Read Memory at 80 MHz
// 
#define SST25VFxx_CMD_RD80      0x0B
     
//
//! Erase 4 KByte memory array
// 
#define SST25VFxx_CMD_ER4K      0x20
       
//
//! Erase 32 KByte block of memory array
// 
#define SST25VFxx_CMD_ER32K     0x52
         
//
//! Erase 64 KByte block of memory array
// 
#define SST25VFxx_CMD_ER64K     0xD8
           
//
//! Erase Full Memory Array
// 
#define SST25VFxx_CMD_ERALL_0   0x60
#define SST25VFxx_CMD_ERALL_1   0xC7
             
//
//! To Program One Data Byte
// 
#define SST25VFxx_CMD_WRBYTE    0x02
               
//
//! Auto Address Increment Programming
// 
#define SST25VFxx_CMD_AAI       0xAD
                 
//
//! Read-Status-Register
// 
#define SST25VFxx_CMD_RDSR      0x05
                   
//
//! Enable-Write-Status-Register
// 
#define SST25VFxx_CMD_EWSR      0x50
                     
//
//! Write-Status-Register
// 
#define SST25VFxx_CMD_WRSR      0x01

//
//! Write-Enable
//
#define SST25VFxx_CMD_WREN      0x06

//
//! Write-Disable
//
#define SST25VFxx_CMD_WRDI      0x04

//
//! Read-ID
//
#define SST25VFxx_CMD_RDID_0    0x90
#define SST25VFxx_CMD_RDID_1    0xAB

//
//! JEDEC ID read
//
#define SST25VFxx_CMD_RD_JEDEC  0x9F

//
//! EnableSOto output RY/BY#status during AAI programming
//
#define SST25VFxx_CMD_EBSY      0x70

//
//! Write-Disable
//
#define SST25VFxx_CMD_DBSY      0x80

  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup SST25VFxx_Attribute
//! SST25VFxx SPI Flash attribute.
//! @{
//
//*****************************************************************************

//
//! SST25VF016B SIZE
//
#define SST25VF016B_SECTOR_SIZE      4096

#define SST25VF016B_BLOCK_32K        1
#define SST25VF016B_BLOCK_64K        1
#define SST25VF016B_SIZE              2*1024*1024


#define SST25VF016B                    0

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



#endif // __HW_SST25VFXX_H__
