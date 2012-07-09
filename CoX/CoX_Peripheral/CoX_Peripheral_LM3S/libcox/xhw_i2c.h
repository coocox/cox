//*****************************************************************************
//
//! \file xhw_i2c.h
//! \brief Macros used when accessing the I2C master and slave hardware.
//! \version V2.1.1.0
//! \date 11/14/2011
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

#ifndef __xHW_I2C_H__
#define __xHW_I2C_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_I2C_Register
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_I2C_Register_Map I2C Register Map(Offset)
//! @{
//
//*****************************************************************************

#define I2C_MSA                 0x00000000  // I2C Master Slave Address
#define I2C_SOAR                0x00000000  // I2C Slave Own Address
#define I2C_SCSR                0x00000004  // I2C Slave Control/Status
#define I2C_MCS                 0x00000004  // I2C Master Control/Status
#define I2C_SDR                 0x00000008  // I2C Slave Data
#define I2C_MDR                 0x00000008  // I2C Master Data
#define I2C_MTPR                0x0000000C  // I2C Master Timer Period
#define I2C_SIMR                0x0000000C  // I2C Slave Interrupt Mask
#define I2C_SRIS                0x00000010  // I2C Slave Raw Interrupt Status
#define I2C_MIMR                0x00000010  // I2C Master Interrupt Mask
#define I2C_MRIS                0x00000014  // I2C Master Raw Interrupt Status
#define I2C_SMIS                0x00000014  // I2C Slave Masked Interrupt
                                            // Status
#define I2C_SICR                0x00000018  // I2C Slave Interrupt Clear
#define I2C_MMIS                0x00000018  // I2C Master Masked Interrupt
                                            // Status
#define I2C_MICR                0x0000001C  // I2C Master Interrupt Clear
#define I2C_MCR                 0x00000020  // I2C Master Configuration

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MSA I2C_MSA
//! @{
//
//*****************************************************************************

#define I2C_MSA_SA_M            0x000000FE  // I2C Slave Address
#define I2C_MSA_RS              0x00000001  // Receive not send
#define I2C_MSA_SA_S            1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_SOAR I2C_SOAR
//! @{
//
//*****************************************************************************

#define I2C_SOAR_OAR_M          0x0000007F  // I2C Slave Own Address
#define I2C_SOAR_OAR_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_SCSR I2C_SCSR
//! @{
//
//*****************************************************************************

#define I2C_SCSR_FBR            0x00000004  // First Byte Received
#define I2C_SCSR_TREQ           0x00000002  // Transmit Request
#define I2C_SCSR_DA             0x00000001  // Device Active
#define I2C_SCSR_RREQ           0x00000001  // Receive Request

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MCS I2C_MCS
//! @{
//
//*****************************************************************************

#define I2C_MCS_BUSBSY          0x00000040  // Bus Busy
#define I2C_MCS_IDLE            0x00000020  // I2C Idle
#define I2C_MCS_ARBLST          0x00000010  // Arbitration Lost
#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_SDR I2C_SDR
//! @{
//
//*****************************************************************************

#define I2C_SDR_DATA_M          0x000000FF  // Data for Transfer
#define I2C_SDR_DATA_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MDR I2C_MDR
//! @{
//
//*****************************************************************************

#define I2C_MDR_DATA_M          0x000000FF  // Data Transferred
#define I2C_MDR_DATA_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MTPR I2C_MTPR
//! @{
//
//*****************************************************************************

#define I2C_MTPR_TPR_M          0x0000007F  // SCL Clock Period
#define I2C_MTPR_TPR_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_SIMR I2C_SIMR
//! @{
//
//*****************************************************************************

#define I2C_SIMR_STOPIM         0x00000004  // Stop Condition Interrupt Mask
#define I2C_SIMR_STARTIM        0x00000002  // Start Condition Interrupt Mask
#define I2C_SIMR_DATAIM         0x00000001  // Data Interrupt Mask

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_SRIS I2C_SRIS
//! @{
//
//*****************************************************************************

#define I2C_SRIS_STOPRIS        0x00000004  // Stop Condition Raw Interrupt
                                            // Status
#define I2C_SRIS_STARTRIS       0x00000002  // Start Condition Raw Interrupt
                                            // Status
#define I2C_SRIS_DATARIS        0x00000001  // Data Raw Interrupt Status

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MIMR I2C_MIMR
//! @{
//
//*****************************************************************************

#define I2C_MIMR_IM             0x00000001  // Interrupt Mask

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MRIS I2C_MRIS
//! @{
//
//*****************************************************************************

#define I2C_MRIS_RIS            0x00000001  // Raw Interrupt Status

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_SMIS I2C_SMIS
//! @{
//
//*****************************************************************************

#define I2C_SMIS_STOPMIS        0x00000004  // Stop Condition Masked Interrupt
                                            // Status
#define I2C_SMIS_STARTMIS       0x00000002  // Start Condition Masked Interrupt
                                            // Status
#define I2C_SMIS_DATAMIS        0x00000001  // Data Masked Interrupt Status

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_SICR I2C_SICR
//! @{
//
//*****************************************************************************

#define I2C_SICR_STOPIC         0x00000004  // Stop Condition Interrupt Clear
#define I2C_SICR_STARTIC        0x00000002  // Start Condition Interrupt Clear
#define I2C_SICR_DATAIC         0x00000001  // Data Interrupt Clear

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MMIS I2C_MMIS
//! @{
//
//*****************************************************************************

#define I2C_MMIS_MIS            0x00000001  // Masked Interrupt Status

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MICR I2C_MICR
//! @{
//
//*****************************************************************************

#define I2C_MICR_IC             0x00000001  // Interrupt Clear

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_I2C_MCR I2C_MCR
//! @{
//
//*****************************************************************************

#define I2C_MCR_SFE             0x00000020  // I2C Slave Function Enable
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable
#define I2C_MCR_LPBK            0x00000001  // I2C Loopback

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

#endif // __xHW_I2C_H__
