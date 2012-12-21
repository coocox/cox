//*****************************************************************************
//
//! \file xhw_tpm.h
//! \brief Macros used when accessing the system control hardware.
//! \version V2.2.1.0
//! \date 8/21/2012
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


#ifndef __XHW_TPM_H__
#define __XHW_TPM_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TPM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register KLx TPM Register
//! \brief Here are the detailed info of SysCtl registers. 
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
//! \addtogroup KLx_TPM_Register_Offsets KLx TPM Register Offsets(Map)
//! \brief Defines for the system control register addresses.
//! @{
//
//*****************************************************************************

//
//! Status and Control
//
#define TPM_SC                  0x00000000

//
//! Counter 
//
#define TPM_CNT                 0x00000004

//
//! Modulo 
//
#define TPM_MOD                 0x00000008

//
//! Channel (0) Status and Control 
//
#define TPM_C0SC                0x0000000C

//
//! Channel (0) Value
//
#define TPM_C0V                 0x00000010

//
//! Channel (1) Status and Control 
//
#define TPM_C1SC                0x00000014

//
//! Channel (1) Value
//
#define TPM_C1V                 0x00000018

//
//! Channel (2) Status and Control 
//
#define TPM_C2SC                0x0000001C

//
//! Channel (2) Value
//
#define TPM_C2V                 0x00000020

//
//! Channel (3) Status and Control 
//
#define TPM_C3SC                0x00000024

//
//! Channel (3) Value
//
#define TPM_C3V                 0x00000028

//
//! Channel (4) Status and Control 
//
#define TPM_C4SC                0x0000002C

//
//! Channel (4) Value
//
#define TPM_C4V                 0x00000030

//
//! Channel (5) Status and Control 
//
#define TPM_C5SC                0x00000034

//
//! Channel (5) Value
//
#define TPM_C5V                 0x00000038

//
//! Capture and Compare Status
//
#define TPM_STATUS              0x00000050

//
//! Configuration
//
#define TPM_CONF                0x00000084       

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register_SC TPM Register SC(TPM_SC)
//! \brief Defines for the bit fields in the TPM_SC register.
//! @{
//
//*****************************************************************************

//
//! DMA Enable
//
#define TPM_SC_DMA              0x00000100 

//
//! Timer Overflow Flag
//
#define TPM_SC_TOF              0x00000080

//
//! Timer Overflow Interrupt Enable
//
#define TPM_SC_TOIE             0x00000040

//
//! Center-aligned PWM Select
//
#define TPM_SC_CPWMS            0x00000020

//
//! Clock Mode Selection mask
//
#define TPM_SC_CMOD_M           0x00000018

//
//! LPTPM counter is disabled
//
#define TPM_SC_CMOD_DIS         0x00000000

//
//! LPTPM counter increments on every LPTPM counter clock
//
#define TPM_SC_CMOD_CLK         0x00000008

//
//! LPTPM counter increments on rising edge of LPTPM_EXTCLK
//
#define TPM_SC_CMOD_RISING      0x00000010

//
//! Clock Mode Selection shift
//
#define TPM_SC_CMOD_S           3

//
//! Prescale Factor Selection mask
//
#define TPM_SC_PS_M             0x00000007

//
//! Divide by 1
//
#define TPM_SC_PS_1             0x00000000

//
//! Divide by 2
//
#define TPM_SC_PS_2             0x00000001

//
//! Divide by 4
//
#define TPM_SC_PS_4             0x00000002

//
//! Divide by 8
//
#define TPM_SC_PS_5             0x00000003

//
//! Divide by 16
//
#define TPM_SC_PS_16            0x00000004

//
//! Divide by 32
//
#define TPM_SC_PS_32            0x00000005

//
//! Divide by 64
//
#define TPM_SC_PS_64            0x00000006

//
//! Divide by 128
//
#define TPM_SC_PS_128           0x00000007

//
//! Prescale Factor Selection shift
//
#define TPM_SC_PS_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register_CNT TPM Register CNT(TPM_CNT)
//! \brief Defines for the bit fields in the TPM_SC register.
//! @{
//
//*****************************************************************************

//
//! Counter value mask
//
#define TPM_CNT_COUNT_M         0x0000FFFF

//
//! Counter value shift
//
#define TPM_CNT_COUNT_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register_MOD TPM Register MOD(TPM_MOD)
//! \brief Defines for the bit fields in the TPM_MOD register.
//! @{
//
//*****************************************************************************

//
//! Counter value mask
//
#define TPM_MOD_COUNT_M         0x0000FFFF

//
//! Counter value shift
//
#define TPM_MOD_COUNT_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register_CNSC TPM Register MOD(TPM_CNSC)
//! \brief Defines for the bit fields in the TPM_CNSC register.
//! @{
//
//*****************************************************************************

//
//! Channel Flag
//
#define TPM_CNSC_CHF            0x00000080

//
//! Channel Interrupt Enable
//
#define TPM_CNSC_CHIE           0x00000040

//
//! Channel Mode Select
//
#define TPM_CNSC_MSB            0x00000020

//
//! Channel Mode Select
//
#define TPM_CNSC_MSA            0x00000010

//
//! Edge or Level Select
//
#define TPM_CNSC_ELSB           0x00000008

//
//! Edge or Level Select
//
#define TPM_CNSC_ELSA           0x00000004

//
//! DMA Enable
//
#define TPM_CNSC_DMA            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register_CNV TPM Register Channel 0 value(TPM_CNV)
//! \brief Defines for the bit fields in the TPM_CNV register.
//! @{
//
//*****************************************************************************

//
//! Channel Value mask
//
#define TPM_CNV_VAL_M           0x0000FFFF

//
//! Channel Value shift
//
#define TPM_CNV_VAL_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register_STATUS TPM Register Capture and Compare Status(TPM_STATUS)
//! \brief Defines for the bit fields in the TPM_STATUS register.
//! @{
//
//*****************************************************************************

//
//! Timer Overflow Flag
//
#define TPM_STATUS_TOF          0x00000100

//
//! Channel 5 Flag
//
#define TPM_STATUS_CH5F         0x00000020

//
//! Channel 4 Flag
//
#define TPM_STATUS_CH4F         0x00000010

//
//! Channel 3 Flag
//
#define TPM_STATUS_CH3F         0x00000008

//
//! Channel 2 Flag
//
#define TPM_STATUS_CH2F         0x00000004

//
//! Channel 1 Flag
//
#define TPM_STATUS_CH1F         0x00000002

//
//! Channel 0 Flag
//
#define TPM_STATUS_CH0F         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_TPM_Register_CONF TPM Register Configuration(TPM_CONF)
//! \brief Defines for the bit fields in the TPM_CONF register.
//! @{
//
//*****************************************************************************

//
//! Trigger Select mask
//
#define TPM_CONF_TRGSEL_M       0x0F000000

//
//! External trigger pin input (EXTRG_IN)
//
#define TPM_CONF_TRGSEL_EXTRGIN 0x00000000

//
//! HSCMP0 output
//
#define TPM_CONF_TRGSEL_HSCMP0  0x01000000

//
//! PIT trigger 0
//
#define TPM_CONF_TRGSEL_PITRG0  0x04000000

//
//! PIT trigger 1
//
#define TPM_CONF_TRGSEL_PITRG1  0x05000000

//
//! TPM0 overflow
//
#define TPM_CONF_TRGSEL_TPM0OF  0x08000000

//
//! TPM1 overflow
//
#define TPM_CONF_TRGSEL_TPM1OF  0x09000000

//
//! TPM2 overflow
//
#define TPM_CONF_TRGSEL_TPM2OF  0x0A000000

//
//! RTC alarm
//
#define TPM_CONF_TRGSEL_RTCALARM                                              \
                                0x0C000000

//
//! RTC seconds
//
#define TPM_CONF_TRGSEL_RTCSECONDS                                            \
                                0x0D000000

//
//! LPTMR trigger
//
#define TPM_CONF_TRGSEL_LPTMR   0x0E000000
                                  
//
//! Trigger Select Shift
//
#define TPM_CONF_TRGSEL_S       24 
     
//
//! Counter Reload On Trigger
//
#define TPM_CONF_CROT           0x00040000 
                                  
//
//! Counter Stop On Overflow
//
#define TPM_CONF_CSOO           0x00020000 

//
//! Counter Start on Trigger
//
#define TPM_CONF_CSOT           0x00010000
                                 
//
//! Global time base enable
//
#define TPM_CONF_GTBEEN         0x00000200
                                
//
//! Debug Mode Mask
//
#define TPM_CONF_DBGMODE_M      0x000000C0
                                 
//
//! LPTPM counter is paused 
//
#define TPM_CONF_DBGMODE_PAUSED 0x00000000
                                  
//
//! LPTPM counter is continues 
//
#define TPM_CONF_DBGMODE_CONTINUES                                            \
                                0x000000C0
                                  
//
//! Debug Mode Shift
//
#define TPM_CONF_DBGMODE_S      5
                                  
//
//! Doze Enable
//
#define TPM_CONF_DOZEEN         0x00000020    
                                  
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

#endif // __XHW_TPM_H_

