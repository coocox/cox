//*****************************************************************************
//
//! \file hw_M25Pxx.h
//! \brief header file of Driver for M25Pxx
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



#ifndef __HW_M25PXX_H__
#define __HW_M25PXX_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib 
//! @{
//! \addtogroup Memory
//! @{
//! \addtogroup SPI_Flash
//! @{
//! \addtogroup M25Pxx
//! @{
//! \addtogroup M25Pxx_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M25Pxx_CMD
//! M25Pxx SPI Flash CMD.
//! @{
//
//*****************************************************************************
  
//
//! Write Enable 
//
#define M25Pxx_CMD_WREN         0x06     
   
//
//! Write Disable
// 
#define M25Pxx_CMD_WRDI         0x04     
     
//
//! Read Identification 
// 
#define M25Pxx_CMD_RDID         0x9F     
       
//
//! Read Status Register 
// 
#define M25Pxx_CMD_RDSR         0x05     
         
//
//! Write Status Register 
// 
#define M25Pxx_CMD_WRSR         0x01     
           
//
//! Read Data Bytes 
// 
#define M25Pxx_CMD_READ         0x03     
             
//
//! Read Data Bytes at Higher Speed 
// 
#define M25Pxx_CMD_FAST_READ    0x0B     
               
//
//! Page Program 
// 
#define M25Pxx_CMD_PP           0x02     
                 
//
//! Sector Erase
// 
#define M25Pxx_CMD_SE           0xD8    
                   
//
//! Bulk Erase
// 
#define M25Pxx_CMD_BE           0xC7     
                     
//
//! Read Electronic Signature
// 
#define M25Pxx_CMD_RES          0xAB     
  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup M25Pxx_Attribute
//! M25Pxx SPI Flash attribute.
//! @{
//
//*****************************************************************************

//
//! M25P10 SIZE
//
#define M25P10_PAGE_SIZE        256UL
#define M25P10_PAGES_PER_SECTORS                                              \
                                256UL
#define M25P10_SECTORS          2UL
#define M25P10_PAGES            (M25P10_SECTORS * M25P10_PAGES_PER_SECTORS)
#define M25P10_SIZE             (M25P10_SECTORS * M25P10_PAGES_PER_SECTORS *  \
                                M25P10_PAGE_SIZE)
//
//! M25P20 SIZE
//
#define M25P20_PAGE_SIZE        256UL
#define M25P20_PAGES_PER_SECTORS                                              \
                                256UL
#define M25P20_SECTORS          4UL
#define M25P20_PAGES            (M25P20_SECTORS * M25P20_PAGES_PER_SECTORS)
#define M25P20_SIZE             (M25P20_SECTORS * M25P20_PAGES_PER_SECTORS *  \
                                M25P20_PAGE_SIZE)

//
//! M25P40 SIZE
//
#define M25P40_PAGE_SIZE        256UL
#define M25P40_PAGES_PER_SECTORS                                              \
                                256UL
#define M25P40_SECTORS          8UL
#define M25P40_PAGES            (M25P40_SECTORS * M25P40_PAGES_PER_SECTORS)
#define M25P40_SIZE             (M25P40_SECTORS * M25P40_PAGES_PER_SECTORS *  \
                                M25P40_PAGE_SIZE)

//
//! M25P80 SIZE
//
#define M25P80_PAGE_SIZE        256UL
#define M25P80_PAGES_PER_SECTORS                                              \
                                256UL
#define M25P80_SECTORS          16UL
#define M25P80_PAGES            (M25P80_SECTORS * M25P80_PAGES_PER_SECTORS)
#define M25P80_SIZE             (M25P80_SECTORS * M25P80_PAGES_PER_SECTORS *  \
                                M25P80_PAGE_SIZE)

//
//! M25P16 SIZE
//
#define M25P16_PAGE_SIZE        256UL
#define M25P16_PAGES_PER_SECTORS                                              \
                                256UL
#define M25P16_SECTORS          32UL
#define M25P16_PAGES            (M25P16_SECTORS * M25P16_PAGES_PER_SECTORS)
#define M25P16_SIZE             (M25P16_SECTORS * M25P16_PAGES_PER_SECTORS *  \
                                M25P16_PAGE_SIZE)

//
//! M25P32 SIZE
//
#define M25P32_PAGE_SIZE        256UL
#define M25P32_PAGES_PER_SECTORS                                              \
                                256UL
#define M25P32_SECTORS          64UL
#define M25P32_PAGES            (M25P32_SECTORS * M25P32_PAGES_PER_SECTORS)
#define M25P32_SIZE             (M25P32_SECTORS * M25P32_PAGES_PER_SECTORS *  \
                                M25P32_PAGE_SIZE)

//
//! M25P64 SIZE
//
#define M25P64_PAGE_SIZE        256UL
#define M25P64_PAGES_PER_SECTORS                                              \
                                256UL
#define M25P64_SECTORS          128UL
#define M25P64_PAGES            (M25P64_SECTORS * M25P64_PAGES_PER_SECTORS)       
#define M25P64_SIZE             (M25P64_SECTORS * M25P64_PAGES_PER_SECTORS *  \
                                M25P64_PAGE_SIZE)

//
//! M25P128 SIZE
//
#define M25P128_PAGE_SIZE       256UL
#define M25P128_PAGES_PER_SECTORS                                             \
                                256UL
#define M25P128_SECTORS         256UL
#define M25P128_PAGES           (M25P128_SECTORS * M25P128_PAGES_PER_SECTORS)
#define M25P128_SIZE            (M25P128_SECTORS * M25P128_PAGES_PER_SECTORS  \
                                * M25P128_PAGE_SIZE)

#define M25P10                    0
#define M25P20                    1
#define M25P40                    2
#define M25P80                    3
#define M25P16                    4
#define M25P32                    5
#define M25P64                    6
#define M25P128                   7

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



#endif // __HW_M25PXX_H__
