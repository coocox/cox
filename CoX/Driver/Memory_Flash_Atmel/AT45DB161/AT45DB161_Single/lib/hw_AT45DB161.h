//*****************************************************************************
//
//! \file hw_AT45DB161.h
//! \brief header file of Driver for AT45DB161
//! \version V2.1.1.0
//! \date 12/11/2012
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2012, CooCoX All rights reserved.
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



#ifndef __HW_AT45DB161_H__
#define __HW_AT45DB161_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup Memory
//! @{
//! \addtogroup SPI_Flash
//! @{
//! \addtogroup AT45DB161
//! @{
//! \addtogroup AT45DB161_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AT45DB161_CMD
//! AT45DB161 SPI Flash CMD.
//! @{
//
//*****************************************************************************

//
//! Continuous Array Read(Legacy Command)
//
#define AT45DB161_CMD_CARL       0xE8

//
//! Continuous Array Read(High Frequency Mode)
//
#define AT45DB161_CMD_CARH       0x0B

//
//! Continuous Array Read (Low Frequency Mode)
//
#define AT45DB161_CMD_RDID       0x03

//
//! Main Memory Page Read
//
#define AT45DB161_CMD_MMPR       0xD2

//
//! Buffer1 Read
//
#define AT45DB161_CMD_BF1R       0xD4
//
//! Buffer2 Read
//
#define AT45DB161_CMD_BF2R       0xD6

//
//! Buffer1 Write
//
#define AT45DB161_CMD_BF1W       0x84
//
//! Buffer2 Write
//
#define AT45DB161_CMD_BF2W       0x87

//
//! Buffer1 to Main Memory Page Program with Built-in Erase
//
#define AT45DB161_CMD_B1TMW      0x83
//
//! Buffer2 to Main Memory Page Program with Built-in Erase
//
#define AT45DB161_CMD_B2TMW      0x86

//
//! Buffer1 to Main Memory Page Program without Built-in Erase
//
#define AT45DB161_CMD_B1TMO      0x88
//
//! Buffer2 to Main Memory Page Program without Built-in Erase
//
#define AT45DB161_CMD_B2TMO      0x89

//
//! Page Erase
//
#define AT45DB161_CMD_ERPG       0x81

//
//! Block Erase
//
#define AT45DB161_CMD_ERBL       0x50

//
//! Sector Erase
//
#define AT45DB161_CMD_ERSC       0x7C

//
//! Main Memory Page to Buffer1 Transfer
//
#define AT45DB161_CMD_MTB1       0x53
//
//! Main Memory Page to Buffer2 Transfer
//
#define AT45DB161_CMD_MTB2       0x55

//
//! Auto Page Rewrite with Buffer1
//
#define AT45DB161_CMD_APR1       0x58
//
//! Auto Page Rewrite with Buffer2
//
#define AT45DB161_CMD_APR2       0x59

//
//! Status Register Read
//
#define AT45DB161_CMD_SRRD       0xD7

//
//! Manufacturer and Device ID Read
//
#define AT45DB161_CMD_MDID       0x9F

//
//! Chip Erase
//
const unsigned char AT45DB161_CMD_CPER[4] = { 0xC7, 0x94, 0x80, 0x9A};

//
//! Enable Software Sector Protection Command
//! Notice:
//!     If the device is power cycled, then the software controlled protection will be disabled.
//! Once the device is powered up, the Enable Sector Protection command  should be reissued
//! if sector protection is desired and if the WP pin is not used.
//
const unsigned char AT45DB161_CMD_ESSP[4] = { 0x3D, 0x2A, 0x7F, 0xA9};
//
//! Disable Software Sector Protection Command
//
const unsigned char AT45DB161_CMD_DSSP[4] = { 0x3D, 0x2A, 0x7F, 0x9A};

//
//! Erase Sector Protection Register Command
//
const unsigned char AT45DB161_CMD_ESPR[4] = { 0x3D, 0x2A, 0x7F, 0xCF};
//
//! Program Sector Protection Register Command
//
const unsigned char AT45DB161_CMD_PSPR[4] = { 0x3D, 0x2A, 0x7F, 0xFC};
//
//! Read Sector Protection Register Command
//
const unsigned char AT45DB161_CMD_RSPR[4] = { 0x32, 0xFF, 0xFF, 0xFF};
//
//! Sector Lockdown
//! Attention:
//!     Once a sector is locked down, it can never be erased or programmed, and it can never be unlocked.
//
const unsigned char AT45DB161_CMD_SCLD[4] = { 0x3D, 0x2A, 0x7F, 0x30};
//
//! Programming the Configuration Register
//! Attention:
//!     This ¡°power of 2¡± Command changes the page size from initial 528 bytes to 512 bytes.
//! The ¡°power of 2¡± page size is a onetime programmable configuration register and once the device is
//! configured for ¡°power of 2¡± page size, it cannot be reconfigured again.
//
const unsigned char AT45DB161_CMD_PGCR[4] = {0x3D, 0x2A, 0x80, 0xA6};

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AT45DB161_Attribute
//! AT45DB161 SPI Flash attribute.
//! @{
//
//*****************************************************************************

//
//! Status Register Bits
//
#define AT45DB161_DATA_MATCH     0x40
#define AT45DB161_IDLE           0x80
#define AT45DB161_SCPT_EN        0x20
#define AT45DB161_PGSZ           0x01

//
//! AT45DB161 default page size
//
#define AT45DB161_PAGE_SIZE_DEFAULT       528UL

//
//! AT45DB161 binary page size
//
#define AT45DB161_PAGE_SIZE_BINARY        512UL

//
//! AT45DB161 total pages
//
#define AT45DB161_PAGES                   4096UL

//
//! AT45DB161 total blocks
//
#define AT45DB161_BLOCKS                  512

//
//! AT45DB161 total sectors
//
#define AT45DB161_SECTORS                 16

//
//! AT45DB161 buffers define
//
#define AT45DB161_BUF1                    1
#define AT45DB161_BUF2                    2
//
//! AT45DB161 max SPI clock rate
//
#define AT45DB161_MAX_CLK  66000000   //unit: Hz
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



#endif // __HW_AT45DB161_H__
