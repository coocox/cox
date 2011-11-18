//*****************************************************************************
//
//! \file xhw_timer.h
//! \brief Macros and defines used when accessing the TIMER hardware.
//! \version V2.1.1.1
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
//****************************************************************************
#ifndef __XHW_TIMER_H__
#define __XHW_TIMER_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Register NUC1xx_TIMER_Register
//! \brief Here are the detailed info of TIMER registers. 
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
//! \addtogroup NUC1xx_TIMER_Register_Address_Offset TIMER Register Offset(Map)
//! \brief Here is the TIMER register offset, users can get the register address
//! through <b>TIMER_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Timer Control Register (TCSR)
//
#define TIMER_O_TCSR            0x00000000  

//
//! Timer Compare Register (TCMPR)
//
#define TIMER_O_TCMPR           0x00000004  

//
//! Timer Interrupt Status Register (TISR)
//
#define TIMER_O_TISR            0x00000008

//
//! Timer Data Register (TDR)
//
#define TIMER_O_TDR             0x0000000C

//
//! Timer Capture Data Register (TCAP)
//
#define TIMER_O_TCAPR           0x00000010

//
//! Timer External Control Register (TEXCON)
//
#define TIMER_O_TEXCON          0x00000014

//
//! Timer External Interrupt Status Register (TEISR)
//
#define TIMER_O_TEISR           0x00000018

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Register_TIMER_0_TCSR Timer Control Status Register(TIMER_0_TCSR)
//! \brief Defines for the bit fields in the TIMER_0_TCSR register.
//! @{
//
//*****************************************************************************

//
//! ICE debug mode acknowledge Disable (write-protection bit)
//
#define TIMER_TCSR_DBGACK       0x80000000  

//
//! Timer Enable Bit
//
#define TIMER_TCSR_CEN          0x40000000 

//
//! Interrupt Enable Bit
//
#define TIMER_TCSR_IE           0x20000000 

//
//! Timer Operating Mode mask
//
#define TIMER_TCSR_MODE_M       0x18000000 

//
//! The timer is operating at the one-shot mode.
//
#define TIMER_TCSR_MODE_ONESHOT 0x00000000 

//
//! The timer is operating at the periodic mode.
//
#define TIMER_TCSR_MODE_PERIODIC                                              \
                                0x08000000 

//
//! The timer is operating at the toggle mode.
//
#define TIMER_TCSR_MODE_TOGGLE  0x10000000 

//
//! The timer is operating at continuous counting mode.
//
#define TIMER_TCSR_MODE_CONTINUOUS                                            \
                                0x18000000 

//
//! Timer Operating Mode shift
//
#define TIMER_TCSR_MODE_S       27 

//
//! Timer Reset Bit
//
#define TIMER_TCSR_CRST         0x04000000

//
//! Timer Active Status Bit (Read only)
//
#define TIMER_TCSR_CACT         0x02000000

//
//! Counter Mode Enable Bit
//
#define TIMER_TCSR_CTB          0x01000000

//
//! Data Load Enable
//
#define TIMER_TCSR_CTDR_EN      0x00010000

//
//! Pre-scale Counter mask
//
#define TIMER_TCSR_PRESCALE_M   0x000000FF

//
//! Pre-scale Counter shift
//
#define TIMER_TCSR_PRESCALE_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Register_TIMER_0_TCMPR Timer Compare Register(TIMER_0_TCMPR)
//! \brief Defines for the bit fields in the TIMER_0_TCMPR register.
//! @{
//
//*****************************************************************************

//
//! Timer Compared Value mask
//
#define TIMER_TCMPR_TCMP_M      0x00FFFFFF

//
//! Timer Compared Value shift
//
#define TIMER_TCMPR_TCMP_S      0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Register_TIMER_0_TISR Timer Interrupt Status Register(TIMER_0_TISR)
//! \brief Defines for the bit fields in the TIMER_0_TISR register.
//! @{
//
//*****************************************************************************

//
//! Timer Interrupt Flag
//
#define TIMER_TISR_TIF          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Register_TIMER_O_TDR Timer Data Register(TIMER_O_TDR)
//! \brief Defines for the bit fields in the TIMER_O_TDR register.
//! @{
//
//*****************************************************************************

//
//! Timer Data Register Value mask
//
#define TIMER_TDR_DATA_M        0x00FFFFFF

//
//! Timer Data Register Value shift
//
#define TIMER_TDR_DATA_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Register_TIMER_O_TCAPR Timer Capture Data Register(TIMER_O_TCAPR)
//! \brief Defines for the bit fields in the TIMER_O_TCAPR register.
//! @{
//
//*****************************************************************************

//
//! Timer Capture Data Register Value mask
//
#define TIMER_TCAPR_CAPDATA_M   0x00FFFFFF

//
//! Timer Capture Data Register Value shift
//
#define TIMER_TCAPR_CAPDATA_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Register_TIMER_0_TEXCON Timer External Control Register(TIMER_O_TEXCON)
//! \brief Defines for the bit fields in the TIMER_0_TEXCON register.
//! @{
//
//*****************************************************************************

//
//! Timer Counter pin De-bounce enable bit
//
#define TIMER_TEXCON_TCDB       0x00000080

//
//! Timer External Capture pin De-bounce enable bit
//
#define TIMER_TEXCON_TEXDB      0x00000040

//
//! Timer External interrupt Enable Bit
//
#define TIMER_TEXCON_TEXIEN     0x00000020

//
//! Timer External Reset Counter / Capture mode select
//
#define TIMER_TEXCON_RSTCAP     0x00000010

//
//! Timer External Pin Enable.
//
#define TIMER_TEXCON_TEXEN      0x00000008

//
//! Timer External Pin Edge Detect mask
//
#define TIMER_TEXCON_TEX_EDGE_M 0x00000006

//
//! 00 = a 1 to 0 transition on TEX will be detected.
//
#define TIMER_TEXCON_TEX_EDGE_FALLING                                         \
                                0x00000000
                                
//
//! 01 = a 0 to 1 transition on TEX will be detected.
//
#define TIMER_TEXCON_TEX_EDGE_RISING                                          \
                                0x00000002
                                
//
//! 10 = either 1 to 0 or 0 to 1 transition on TEX will be detected.
//
#define TIMER_TEXCON_TEX_EDGE_BOTH                                            \
                                0x00000004

//
//! Timer External Count Phase.
//
#define TIMER_TEXCON_TX_PHASE   0x00000001

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

#endif // __XHW_TIMER_H__




