//*****************************************************************************
//
//! \file hw_AT25FS0x.h
//! \brief header file of Driver for AT25FS0x
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



#ifndef __HW_AT25FS0X_H__
#define __HW_AT25FS0X_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib 
//! @{
//! \addtogroup Memmory
//! @{
//! \addtogroup SPI_Flash
//! @{
//! \addtogroup AT25FS0x
//! @{
//! \addtogroup AT25FS0x_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AT25FS0x_CMD
//! AT25FS0x SPI Flash CMD.
//! @{
//
//*****************************************************************************
  
//
//! Write Enable 
//
#define AT25FS0x_CMD_WREN       0x06     
   
//
//! Write Disable
// 
#define AT25FS0x_CMD_WRDI       0x04     
     
//
//! Read Identification 
// 
#define AT25FS0x_CMD_RDID       0x9F     
       
//
//! Read Status Register 
// 
#define AT25FS0x_CMD_RDSR       0x05     
         
//
//! Write Status Register 
// 
#define AT25FS0x_CMD_WRSR       0x01     
           
//
//! Read Data Bytes 
// 
#define AT25FS0x_CMD_READ       0x03     
             
//
//! Read Data Bytes at Higher Speed 
// 
#define AT25FS0x_CMD_FAST_READ  0x0B     
               
//
//! Page Program 
// 
#define AT25FS0x_CMD_PP         0x02     
                 
//
//! Sector Erase
// 
#define AT25FS0x_CMD_SE         0xD7    
                   
//
//! Bulk Erase
// 
#define AT25FS0x_CMD_BE         0xD8     
                     
//
//! CHIP ERASE
// 
#define AT25FS0x_CMD_CE         0xC7     
  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup AT25FS0x_Attribute
//! AT25FS0x SPI Flash attribute.
//! @{
//
//*****************************************************************************

#define AT25FS_PAGE_SIZE        256UL

//
//! AT25FS010 Number of Block
// 
#define AT25FS010_BLOCKS        4  

//
//! AT25FS010 Number of Page per Sector 
//
#define AT25FS010_SECTOR_PAGE   16     

//
//! AT25FS010 Number of Sector per Block
//
#define AT25FS010_BLOCK_SECTOR  8      

//
//! AT25FS010 Page Size
//
#define AT25FS010_PAGE_SIZE     AT25FS_PAGE_SIZE  

//
//! AT25FS010 Sector Size
//
#define AT25FS010_SECTOR_SIZE   (AT25FS010_PAGE_SIZE * AT25FS010_SECTOR_PAGE)  

//
//! AT25FS010 Block Size
//
#define AT25FS010_BLOCK_SIZE    (AT25FS010_SECTOR_SIZE * AT25FS010_BLOCK_SECTOR)

//
//! AT25FS010 Chip Size
//
#define AT25FS010_CHIP_SIZE     (AT25FS010_BLOCKS * AT25FS010_BLOCK_SIZE)


//
//! AT25FS040 Number of Block
// 
#define AT25FS040_BLOCKS        8  

//
//! AT25FS040 Number of Page per Sector 
//
#define AT25FS040_SECTOR_PAGE   16     

//
//! AT25FS040 Number of Sector per Block
//
#define AT25FS040_BLOCK_SECTOR  16      

//
//! AT25FS040 Page Size
//
#define AT25FS040_PAGE_SIZE     AT25FS_PAGE_SIZE  

//
//! AT25FS040 Sector Size
//
#define AT25FS040_SECTOR_SIZE   (AT25FS010_PAGE_SIZE * AT25FS010_SECTOR_PAGE)  

//
//! AT25FS040 Block Size
//
#define AT25FS040_BLOCK_SIZE    (AT25FS010_SECTOR_SIZE * AT25FS010_BLOCK_SECTOR)

//
//! AT25FS040 Chip Size
//
#define AT25FS040_CHIP_SIZE     (AT25FS010_BLOCKS * AT25FS010_BLOCK_SIZE)

#define AT25FS010               0
#define AT25FS040               1


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



#endif // __HW_AT25FS0X_H__
