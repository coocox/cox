//*****************************************************************************
//
//! \file xhw_timer.h
//! \brief Macros and defines used when accessing the TIMER hardware.
//! \version V2.2.1.0
//! \date 3/21/2012
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
//! \addtogroup HT32F175x_275x_TIMER_Register HT32F175x_275x TIMER Register
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
//! \addtogroup HT32F175x_275x_TIMER_Register_Address_Offset TIMER Register Offset(Map)
//! \brief Here is the TIMER register offset, users can get the register address
//! through <b>TIMER_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Timer Counter Configuration Register (CNTCFR)
//
#define TIMER_CNTCFR            0x00000000  

//
//! Timer Mode Configuration Register (MDCFR)
//
#define TIMER_MDCFR             0x00000004  

//
//! Timer Trigger Configuration Register (TRCFR)
//
#define TIMER_TRCFR             0x00000008

//
//! Timer Control Register (CTR)
//
#define TIMER_CTR               0x00000010

//
//! Channel 0 Input Configuration Register (CH0ICFR)
//
#define TIMER_CH0ICFR           0x00000020

//
//! Channel 1 Input Configuration Register (CH1ICFR)
//
#define TIMER_CH1ICFR           0x00000024

//
//! Channel 2 Input Configuration Register (CH2ICFR)
//
#define TIMER_CH2ICFR           0x00000028

//
//! Channel 3 Input Configuration Register (CH3ICFR)
//
#define TIMER_CH3ICFR           0x0000002C

//
//! Channel 0 Output Configuration Register	(CH0OCFR)
//
#define TIMER_CH0OCFR           0x00000040

//
//! Channel 1 Output Configuration Register	(CH1OCFR)
//
#define TIMER_CH1OCFR           0x00000044

//
//! Channel 2 Output Configuration Register	(CH2OCFR)
//
#define TIMER_CH2OCFR           0x00000048

//
//! Channel 3 Output Configuration Register	(CH3OCFR)
//
#define TIMER_CH3OCFR           0x0000004C

//
//! Channel Control Register (CHCTR) 
//
#define TIMER_CHCTR	            0x00000050

//
//! Channel Polarity Configuration Register (CHPOLR) 
//
#define TIMER_CHPOLR            0x00000054

//
//! Timer Interrupt Control Register (ICTR)
//
#define TIMER_ICTR              0x00000074

//
//! Timer Event Generator Register (EVGR) 
//
#define TIMER_EVGR              0x00000078

//
//! Timer Interrupt Status Register (INTSR) 
//
#define TIMER_INTSR             0x0000007C

//
//! Timer Counter Register (CNTR) 
//
#define TIMER_CNTR              0x00000080

//
//! Timer Prescaler Register (PSCR) 
//
#define TIMER_PSCR              0x00000084

//
//! Timer Counter Reload Register (CRR) 
//
#define TIMER_CRR               0x00000088

//
//! Channel 0 Capture/Compare Register (CH0CCR)
//
#define TIMER_CH0CCR            0x00000090

//
//! Channel 1 Capture/Compare Register (CH1CCR)
//
#define TIMER_CH1CCR            0x00000094

//
//! Channel 2 Capture/Compare Register (CH2CCR)
//
#define TIMER_CH2CCR            0x00000098

//
//! Channel 3 Capture/Compare Register (CH3CCR)
//
#define TIMER_CH3CCR            0x0000009C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CNTCFR Timer Counter 
//! Configuration Register (CNTCFR).
//! \brief Defines for the bit fields in the TIMER_CNTCFR register.
//! @{
//
//*****************************************************************************

//
//! Counting Direction (1:Count-down)
//
#define TIMER_CNTCFR_DIR        0x01000000  

//
//! Counter Mode Selection mask
//
#define TIMER_CNTCFR_CMSEL_M    0x00030000

//
//! Counter Mode 0
// 
#define TIMER_CNTCFR_CMSEL_0    0x00000000

//
//! Counter Mode 1
// 
#define TIMER_CNTCFR_CMSEL_1    0x00010000

//
//! Counter Mode 2
// 
#define TIMER_CNTCFR_CMSEL_2    0x00020000

//
//! Counter Mode 3
// 
#define TIMER_CNTCFR_CMSEL_3    0x00030000

//
//! Counter Mode Selection shift
//
#define TIMER_CNTCFR_CMSEL_S    16

//
//! Clock Division Mask
//
#define TIMER_CNTCFR_CKDIV_M    0x00000300

//
//! fD = fCLKIN 
//
#define TIMER_CNTCFR_CKDIV_1    0x00000000

//
//! fD = fCLKIN/2 
//
#define TIMER_CNTCFR_CKDIV_2    0x00000100

//
//! fD = fCLKIN/4 
//
#define TIMER_CNTCFR_CKDIV_4    0x00000200

//
//! Clock Division shift
//
#define TIMER_CNTCFR_CKDIV_S    8

//
//! Update event interrupt generation disable control 
//
#define TIMER_CNTCFR_UGDIS      0x00000002

//
//! Update event Disable control
//
#define TIMER_CNTCFR_UEVDIS     0x00000001 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_MDCFR Timer Mode Configuration 
//! Register (MDCFR)
//! \brief Defines for the bit fields in the TIMER_MDCFR register.
//! @{
//
//*****************************************************************************

//
//! Single Pulse Mode Setting
//
#define TIMER_MDCFR_SPMSET      0x01000000

//
//! Master Mode Selection mask
//
#define TIMER_MDCFR_MMSEL_M     0x00070000

//
//! Reset Mode
//
#define TIMER_MDCFR_MMSEL_RST   0x00000000

//
//! Enable Mode
//
#define TIMER_MDCFR_MMSEL_EN	0x00010000

//
//! Update Mode
//
#define TIMER_MDCFR_MMSEL_UD    0x00020000

//
//! Capture/Compare Mode
//   
#define TIMER_MDCFR_MMSEL_CC    0x00030000

//
//! Compare output 0
//
#define TIMER_MDCFR_MMSEL_CP0   0x00040000

//
//! Compare output 1
//
#define TIMER_MDCFR_MMSEL_CP1   0x00050000

//
//! Compare output 2
//
#define TIMER_MDCFR_MMSEL_CP2   0x00060000

//
//! Compare output 3
//
#define TIMER_MDCFR_MMSEL_CP3   0x00070000

//
//! Master Mode Selection shift
//
#define TIMER_MDCFR_MMSEL_S     16

//
//! Slave Mode Selection mask
//
#define TIMER_MDCFR_SMSEL_M     0x00000700

//
//! Disable mode
//
#define TIMER_MDCFR_SMSEL_DIS   0x00000000

//
//! Qadrature Decoder Mode 1
//
#define TIMER_MDCFR_SMSEL_QD1   0x00000100

//
//! Qadrature Decoder Mode 2
//
#define TIMER_MDCFR_SMSEL_QD2   0x00000200

//
//! Qadrature Decoder Mode 3
//
#define TIMER_MDCFR_SMSEL_QD3   0x00000300

//
//! Restart Mode
//
#define TIMER_MDCFR_SMSEL_RS    0x00000400

//
//! Pause Mode
//
#define TIMER_MDCFR_SMSEL_PM    0x00000500

//
//! Trigger Mode
//
#define	TIMER_MDCFR_SMSEL_TM    0x00000600

//
//! STIED
//
#define	TIMER_MDCFR_SMSEL_STIED 0x00000700

//
//! Slave Mode Selection shift
//
#define TIMER_MDCFR_SMSEL_S     8

//
//! Timer Synchronization Enable
//
#define TIMER_MDCFR_SMSEL_TSE   0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_TRCFR Timer Trigger Configuration
//! Register (TRCFR).
//! \brief Defines for the bit fields in the TIMER_TRCFR register.
//! @{
//
//*****************************************************************************

//
//! External Clock Mode Enable
//
#define TIMER_TRCFR_ECME        0x01000000

//
//! External Trigger Polarity
//							   
#define TIMER_TRCFR_ETIPOL	    0x00010000

//
//! External Trigger Prescaler mask
//
#define TIMER_TRCFR_ETIPSC_M    0x00003000

//
//! Prescaler OFF
//
#define TIMER_TRCFR_ETIPSC_OFF  0x00000000

//
//! ETIP frequency divided by 2
//
#define TIMER_TRCFR_ETIPSC_2    0x00001000

//
//! ETIP frequency divided by 4
//
#define TIMER_TRCFR_ETIPSC_4    0x00002000

//
//! ETIP frequency divided by 8
//
#define TIMER_TRCFR_ETIPSC_8    0x00003000

//
//! Channel 3 Input Source TI3 Filter Setting mask
//
#define TIMER_TRCFR_ETF_M       0x00000F00

//
//! No filter, the sampling clock is fD.
//
#define TIMER_TRCFR_ETF_FD      0x00000000

//
//! fSAMPLING = fCLKIN, N =	2
//
#define TIMER_TRCFR_ETF_FCLK_2  0x00000100

//
//! fSAMPLING = fCLKIN, N =	4
//
#define TIMER_TRCFR_ETF_FCLK_4  0x00000200

//
//! fSAMPLING = fCLKIN, N =	8
//
#define TIMER_TRCFR_ETF_FCLK_8  0x00000300

//
//! fSAMPLING = fD / 2, = 6
//
#define TIMER_TRCFR_ETF_FD2_6	0x00000400

//
//! fSAMPLING = fD / 2, = 8
//
#define TIMER_TRCFR_ETF_FD2_8	0x00000500

//
//! fSAMPLING = fD / 4, = 6
//
#define TIMER_TRCFR_ETF_FD4_6	0x00000600

//
//! fSAMPLING = fD / 4, = 8
//
#define TIMER_TRCFR_ETF_FD4_8	0x00000700

//
//! fSAMPLING = fD / 8, = 6
//
#define TIMER_TRCFR_ETF_FD8_6	0x00000800

//
//! fSAMPLING = fD / 8, = 8
//
#define TIMER_TRCFR_ETF_FD8_8	0x00000900

//
//! fSAMPLING = fD / 16, = 5
//
#define TIMER_TRCFR_ETF_FD16_5	0x00000A00

//
//! fSAMPLING = fD / 16, = 6
//
#define TIMER_TRCFR_ETF_FD16_6	0x00000B00

//
//! fSAMPLING = fD / 16, = 8
//
#define TIMER_TRCFR_ETF_FD16_8	0x00000C00

//
//! fSAMPLING = fD / 32, = 5
//
#define TIMER_TRCFR_ETF_FD32_5	0x00000D00

//
//! fSAMPLING = fD / 32, = 6
//
#define TIMER_TRCFR_ETF_FD32_6	0x00000E00

//
//! fSAMPLING = fD / 32, = 8
//
#define TIMER_TRCFR_ETF_FD32_8	0x00000F00

//
//! Channel 3 Input Source TI3 Filter Setting shift
//
#define TIMER_TRCFR_ETF_S       8

//
//! Trigger Source Selection mask
//
#define TIMER_TRCFR_TRSEL_M     0x0000000F

//
//! Software Trigger by setting the UEVG bit
//
#define TIMER_TRCFR_TRSEL_SOF   0x00000000

//
//! Filtered input of channel 0 (TI0S0)
//
#define TIMER_TRCFR_TRSEL_FCH0  0x00000001

//
//! Filtered input of channel 1 (TI1S1)
//
#define TIMER_TRCFR_TRSEL_FCH1  0x00000002

//
//! External Trigger input (ETIF)
//
#define TIMER_TRCFR_TRSEL_ETIF  0x00000003

//
//! Channel 0 Edge Detector (TI0BED)
//
#define TIMER_TRCFR_TRSEL_TI0BED                                             \
                                0x00000008

//
//! External Trigger input ((ITI0)
//
#define TIMER_TRCFR_TRSEL_ITI0  0x00000009

//
//! External Trigger input ((ITI1)
//
#define TIMER_TRCFR_TRSEL_ITI1  0x0000000A

//
//! External Trigger input ((ITI2)
//
#define TIMER_TRCFR_TRSEL_ITI2  0x0000000B

//
//! Trigger Source Selection shift
//
#define TIMER_TRCFR_TRSEL_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CTR Timer Control Register(CTR).
//! @{
//
//*****************************************************************************

//
//! Channel Capture/Compare PDMA selection
//
#define TIMER_CTR_CHCCDS        0x00010000

//
//! Counter-Reload register Buffer Enable
//
#define TIMER_CTR_CRBE          0x00000002

//
//! Timer Enable bit
//
#define TIMER_CTR_TME           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH0ICFR Channel 0 Input 
//! Configuration Register (CH0ICFR).
//! @{
//
//*****************************************************************************

//
//! Channel 0 Input Source TI0 Selection
//
#define TIMER_CH0ICFR_TI0SRC    0x80000000

//
//! Channel 0 Capture Input Source Prescaler Setting mask
//
#define TIMER_CH0ICFR_CH0PSC_M  0x000C0000

//
//! No prescaler, channel 0 capture input signal is chosen for each active event
//
#define TIMER_CH0ICFR_CH0PSC_0  0x00000000

//
//! Channel 0 Capture input signal is chosen for every 2 events
//
#define TIMER_CH0ICFR_CH0PSC_2  0x00040000

//
//! Channel 0 Capture input signal is chosen for every 4 events
//
#define TIMER_CH0ICFR_CH0PSC_4  0x00080000

//
//! Channel 0 Capture input signal is chosen for every 8 events
//
#define TIMER_CH0ICFR_CH0PSC_8  0x000C0000

//
//! Channel 0 Capture Input Source Prescaler Setting shift
//
#define TIMER_CH0ICFR_CH0PSC_S  18

//
//! Channel 0 Capture/Compare Selection	mask
//
#define TIMER_CH0ICFR_CH0CCS_M  0x00030000

//
//! Channel 0 Capture/Compare Selection	mask
//
#define TIMER_CH0ICFR_CH0CCS_O  0x00000000

//
//! Channel 0 is configured as an input derived from the TI0 signal
//
#define TIMER_CH0ICFR_CH0CCS_TI0                                            \
                                0x00010000

//
//! Channel 0 is configured as an input derived from the TI1 signal
//
#define TIMER_CH0ICFR_CH0CCS_TI1                                            \
                                0x00020000

//
//! Channel 0 is configured as an input which comes from the TRCED signal 
//! derived from the Trigger Controller
//
#define TIMER_CH0ICFR_CH0CCS_TRCED                                          \
                                0x00030000

//
//! Channel 0 Capture/Compare Selection	shift
//
#define TIMER_CH0ICFR_CH0CCS_S  16

//
//! Channel 0 Input Source TI0 Filter Setting mask
//
#define TIMER_CH0ICFR_TI0F_M    0x0000000F

//
//! No filter, the sampling clock is fD.
//
#define TIMER_CH0ICFR_TI0F_FD   0x00000000

//
//! fSAMPLING = fCLKIN, N = 2
//
#define TIMER_CH0ICFR_TI0F_FCLK_2                                             \
                                0x00000001

//
//! fSAMPLING = fCLKIN, N = 4
//
#define TIMER_CH0ICFR_TI0F_FCLK_4                                             \
                                0x00000002

//
//! fSAMPLING = fCLKIN, N = 8
//
#define TIMER_CH0ICFR_TI0F_FCLK_8                                             \
                                0x00000003

//
//! fSAMPLING = fD / 2, = 6
//
#define TIMER_CH0ICFR_TI0F_FD2_6                                              \
                                0x00000004

//
//! fSAMPLING = fD / 2, = 8
//
#define TIMER_CH0ICFR_TI0F_FD2_8                                              \
                                0x00000005

//
//! fSAMPLING = fD / 4, = 6
//
#define TIMER_CH0ICFR_TI0F_FD4_6                                              \
                                0x00000006

//
//! fSAMPLING = fD / 4, = 8
//
#define TIMER_CH0ICFR_TI0F_FD4_8                                              \
                                0x00000007

//
//! fSAMPLING = fD / 8, = 6
//
#define TIMER_CH0ICFR_TI0F_FD8_6                                              \
                                0x00000008

//
//! fSAMPLING = fD / 8, = 8
//
#define TIMER_CH0ICFR_TI0F_FD8_8                                              \
                                0x00000009

//
//! fSAMPLING = fD / 16, = 5
//
#define TIMER_CH0ICFR_TI0F_FD16_5                                             \
                                0x0000000A

//
//! fSAMPLING = fD / 16, = 6
//
#define TIMER_CH0ICFR_TI0F_FD16_6                                             \
                                0x0000000B

//
//! fSAMPLING = fD / 16, = 8
//
#define TIMER_CH0ICFR_TI0F_FD16_8                                             \
                                0x0000000C

//
//! fSAMPLING = fD / 32, = 5
//
#define TIMER_CH0ICFR_TI0F_FD32_5                                             \
                                0x0000000D

//
//! fSAMPLING = fD / 32, = 6
//
#define TIMER_CH0ICFR_TI0F_FD32_6                                             \
                                0x0000000E

//
//! fSAMPLING = fD / 32, = 8
//
#define TIMER_CH0ICFR_TI0F_FD32_8                                             \
                                0x0000000F

//
//! Channel 0 Input Source TI0 Filter Setting shift
//
#define TIMER_CH0ICFR_TI0F_S    0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH1ICFR Channel 1 Input 
//! Configuration Register (CH1ICFR).
//! @{
//
//*****************************************************************************

//
//! Channel 1 Capture Input Source Prescaler Setting mask
//
#define TIMER_CH1ICFR_CH1PSC_M  0x000C0000

//
//! No prescaler, Channel 1 capture input signal is chosen for each active event
//
#define TIMER_CH1ICFR_CH1PSC_0  0x00000000

//
//! Channel 1 Capture input signal is chosen for every 2 events
//
#define TIMER_CH1ICFR_CH1PSC_2  0x00040000

//
//! Channel 1 Capture input signal is chosen for every 4 events
//
#define TIMER_CH1ICFR_CH1PSC_4  0x00080000

//
//! Channel 1 Capture input signal is chosen for every 8 events
//
#define TIMER_CH1ICFR_CH1PSC_8  0x000C0000

//
//! Channel 1 Capture Input Source Prescaler Setting shift
//
#define TIMER_CH1ICFR_CH1PSC_S  18

//
//! Channel 1 Capture/Compare Selection	mask
//
#define TIMER_CH1ICFR_CH1CCS_M  0x00030000

//
//! Channel 1 Capture/Compare Selection	mask
//
#define TIMER_CH1ICFR_CH1CCS_O  0x00000000

//
//! Channel 1 is configured as an input derived from the TI1 signal
//
#define TIMER_CH1ICFR_CH1CCS_TI1                                            \
                                0x00010000

//
//! Channel 1 is configured as an input derived from the TI0 signal
//
#define TIMER_CH1ICFR_CH1CCS_TI0                                            \
                                0x00020000

//
//! Channel 1 is configured as an input which comes from the TRCED signal 
//! derived from the Trigger Controller
//
#define TIMER_CH1ICFR_CH1CCS_TRCED                                          \
                                0x00030000

//
//! Channel 1 Capture/Compare Selection	shift
//
#define TIMER_CH1ICFR_CH1CCS_S  16

//
//! Channel 1 Input Source TI1 Filter Setting mask
//
#define TIMER_CH1ICFR_TI1F_M    0x0000000F

//
//! No filter, the sampling clock is fD.
//
#define TIMER_CH1ICFR_TI1F_FD   0x00000000

//
//! fSAMPLING = fCLKIN, N = 2
//
#define TIMER_CH1ICFR_TI1F_FCLK_2                                             \
                                0x00000001

//
//! fSAMPLING = fCLKIN, N = 4
//
#define TIMER_CH1ICFR_TI1F_FCLK_4                                             \
                                0x00000002

//
//! fSAMPLING = fCLKIN, N = 8
//
#define TIMER_CH1ICFR_TI1F_FCLK_8                                             \
                                0x00000003

//
//! fSAMPLING = fD / 2, = 6
//
#define TIMER_CH1ICFR_TI1F_FD2_6                                              \
                                0x00000004

//
//! fSAMPLING = fD / 2, = 8
//
#define TIMER_CH1ICFR_TI1F_FD2_8                                              \
                                0x00000005

//
//! fSAMPLING = fD / 4, = 6
//
#define TIMER_CH1ICFR_TI1F_FD4_6                                              \
                                0x00000006

//
//! fSAMPLING = fD / 4, = 8
//
#define TIMER_CH1ICFR_TI1F_FD4_8                                              \
                                0x00000007

//
//! fSAMPLING = fD / 8, = 6
//
#define TIMER_CH1ICFR_TI1F_FD8_6                                              \
                                0x00000008

//
//! fSAMPLING = fD / 8, = 8
//
#define TIMER_CH1ICFR_TI1F_FD8_8                                              \
                                0x00000009

//
//! fSAMPLING = fD / 16, = 5
//
#define TIMER_CH1ICFR_TI1F_FD16_5                                             \
                                0x0000000A

//
//! fSAMPLING = fD / 16, = 6
//
#define TIMER_CH1ICFR_TI1F_FD16_6                                             \
                                0x0000000B

//
//! fSAMPLING = fD / 16, = 8
//
#define TIMER_CH1ICFR_TI1F_FD16_8                                             \
                                0x0000000C

//
//! fSAMPLING = fD / 32, = 5
//
#define TIMER_CH1ICFR_TI1F_FD32_5                                             \
                                0x0000000D

//
//! fSAMPLING = fD / 32, = 6
//
#define TIMER_CH1ICFR_TI1F_FD32_6                                             \
                                0x0000000E

//
//! fSAMPLING = fD / 32, = 8
//
#define TIMER_CH1ICFR_TI1F_FD32_8                                             \
                                0x0000000F

//
//! Channel 1 Input Source TI1 Filter Setting shift
//
#define TIMER_CH1ICFR_TI1F_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH2ICFR Channel 2 Input 
//! Configuration Register (CH2ICFR).
//! @{
//
//*****************************************************************************

//
//! Channel 2 Capture Input Source Prescaler Setting mask
//
#define TIMER_CH2ICFR_CH2PSC_M  0x000C0000

//
//! No prescaler, Channel 2 capture input signal is chosen for each active event
//
#define TIMER_CH2ICFR_CH2PSC_0  0x00000000

//
//! Channel 2 Capture input signal is chosen for every 2 events
//
#define TIMER_CH2ICFR_CH2PSC_2  0x00040000

//
//! Channel 2 Capture input signal is chosen for every 4 events
//
#define TIMER_CH2ICFR_CH2PSC_4  0x00080000

//
//! Channel 2 Capture input signal is chosen for every 8 events
//
#define TIMER_CH2ICFR_CH2PSC_8  0x000C0000

//
//! Channel 2 Capture Input Source Prescaler Setting shift
//
#define TIMER_CH2ICFR_CH2PSC_S  18

//
//! Channel 2 Capture/Compare Selection	mask
//
#define TIMER_CH2ICFR_CH2CCS_M  0x00030000

//
//! Channel 2 Capture/Compare Selection	mask
//
#define TIMER_CH2ICFR_CH2CCS_O  0x00000000

//
//! Channel 2 is configured as an input derived from the TI2 signal
//
#define TIMER_CH2ICFR_CH2CCS_TI2                                            \
                                0x00010000

//
//! Channel 2 is configured as an input derived from the TI3 signal
//
#define TIMER_CH2ICFR_CH2CCS_TI3                                            \
                                0x00020000

//
//! Channel 2 is configured as an input which comes from the TRCED signal 
//! derived from the Trigger Controller
//
#define TIMER_CH2ICFR_CH2CCS_TRCED                                          \
                                0x00030000

//
//! Channel 2 Capture/Compare Selection	shift
//
#define TIMER_CH2ICFR_CH2CCS_S 16

//
//! Channel 2 Input Source TI2 Filter Setting mask
//
#define TIMER_CH2ICFR_TI2F_M    0x0000000F

//
//! No filter, the sampling clock is fD.
//
#define TIMER_CH2ICFR_TI2F_FD   0x00000000

//
//! fSAMPLING = fCLKIN, N = 2
//
#define TIMER_CH2ICFR_TI2F_FCLK_2                                             \
                                0x00000001

//
//! fSAMPLING = fCLKIN, N = 4
//
#define TIMER_CH2ICFR_TI2F_FCLK_4                                             \
                                0x00000002

//
//! fSAMPLING = fCLKIN, N = 8
//
#define TIMER_CH2ICFR_TI2F_FCLK_8                                             \
                                0x00000003

//
//! fSAMPLING = fD / 2, = 6
//
#define TIMER_CH2ICFR_TI2F_FD2_6                                              \
                                0x00000004

//
//! fSAMPLING = fD / 2, = 8
//
#define TIMER_CH2ICFR_TI2F_FD2_8                                              \
                                0x00000005

//
//! fSAMPLING = fD / 4, = 6
//
#define TIMER_CH2ICFR_TI2F_FD4_6                                              \
                                0x00000006

//
//! fSAMPLING = fD / 4, = 8
//
#define TIMER_CH2ICFR_TI2F_FD4_8                                              \
                                0x00000007

//
//! fSAMPLING = fD / 8, = 6
//
#define TIMER_CH2ICFR_TI2F_FD8_6                                              \
                                0x00000008

//
//! fSAMPLING = fD / 8, = 8
//
#define TIMER_CH2ICFR_TI2F_FD8_8                                              \
                                0x00000009

//
//! fSAMPLING = fD / 16, = 5
//
#define TIMER_CH2ICFR_TI2F_FD16_5                                             \
                                0x0000000A

//
//! fSAMPLING = fD / 16, = 6
//
#define TIMER_CH2ICFR_TI2F_FD16_6                                             \
                                0x0000000B

//
//! fSAMPLING = fD / 16, = 8
//
#define TIMER_CH2ICFR_TI2F_FD16_8                                             \
                                0x0000000C

//
//! fSAMPLING = fD / 32, = 5
//
#define TIMER_CH2ICFR_TI2F_FD32_5                                             \
                                0x0000000D

//
//! fSAMPLING = fD / 32, = 6
//
#define TIMER_CH2ICFR_TI2F_FD32_6                                             \
                                0x0000000E

//
//! fSAMPLING = fD / 32, = 8
//
#define TIMER_CH2ICFR_TI2F_FD32_8                                             \
                                0x0000000F

//
//! Channel 2 Input Source TI2 Filter Setting shift
//
#define TIMER_CH2ICFR_TI2F_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH3ICFR Channel 3 Input 
//! Configuration Register (CH3ICFR).
//! @{
//
//*****************************************************************************

//
//! Channel 3 Capture Input Source Prescaler Setting mask
//
#define TIMER_CH3ICFR_CH3PSC_M  0x000C0000

//
//! No prescaler, Channel 3 capture input signal is chosen for each active event
//
#define TIMER_CH3ICFR_CH3PSC_0  0x00000000

//
//! Channel 3 Capture input signal is chosen for every 2 events
//
#define TIMER_CH3ICFR_CH3PSC_2  0x00040000

//
//! Channel 3 Capture input signal is chosen for every 4 events
//
#define TIMER_CH3ICFR_CH3PSC_4  0x00080000

//
//! Channel 3 Capture input signal is chosen for every 8 events
//
#define TIMER_CH3ICFR_CH3PSC_8  0x000C0000

//
//! Channel 3 Capture Input Source Prescaler Setting shift
//
#define TIMER_CH3ICFR_CH3PSC_S  18

//
//! Channel 3 Capture/Compare Selection	mask
//
#define TIMER_CH3ICFR_CH3CCS_M  0x00030000

//
//! Channel 3 Capture/Compare Selection	mask
//
#define TIMER_CH3ICFR_CH3CCS_O  0x00000000

//
//! Channel 3 is configured as an input derived from the TI3 signal
//
#define TIMER_CH3ICFR_CH3CCS_TI3                                            \
                                0x00010000

//
//! Channel 3 is configured as an input derived from the TI2 signal
//
#define TIMER_CH3ICFR_CH3CCS_TI2                                            \
                                0x00020000

//
//! Channel 3 is configured as an input which comes from the TRCED signal 
//! derived from the Trigger Controller
//
#define TIMER_CH3ICFR_CH3CCS_TRCED                                          \
                                0x00030000

//
//! Channel 3 Capture/Compare Selection	shift
//
#define TIMER_CH3ICFR_CH3CCS_S 16

//
//! Channel 3 Input Source TI3 Filter Setting mask
//
#define TIMER_CH3ICFR_TI3F_M    0x0000000F

//
//! No filter, the sampling clock is fD.
//
#define TIMER_CH3ICFR_TI3F_FD   0x00000000

//
//! fSAMPLING = fCLKIN, N = 2
//
#define TIMER_CH3ICFR_TI3F_FCLK_2                                             \
                                0x00000001

//
//! fSAMPLING = fCLKIN, N = 4
//
#define TIMER_CH3ICFR_TI3F_FCLK_4                                             \
                                0x00000002

//
//! fSAMPLING = fCLKIN, N = 8
//
#define TIMER_CH3ICFR_TI3F_FCLK_8                                             \
                                0x00000003

//
//! fSAMPLING = fD / 2, = 6
//
#define TIMER_CH3ICFR_TI3F_FD2_6                                              \
                                0x00000004

//
//! fSAMPLING = fD / 2, = 8
//
#define TIMER_CH3ICFR_TI3F_FD2_8                                              \
                                0x00000005

//
//! fSAMPLING = fD / 4, = 6
//
#define TIMER_CH3ICFR_TI3F_FD4_6                                              \
                                0x00000006

//
//! fSAMPLING = fD / 4, = 8
//
#define TIMER_CH3ICFR_TI3F_FD4_8                                              \
                                0x00000007

//
//! fSAMPLING = fD / 8, = 6
//
#define TIMER_CH3ICFR_TI3F_FD8_6                                              \
                                0x00000008

//
//! fSAMPLING = fD / 8, = 8
//
#define TIMER_CH3ICFR_TI3F_FD8_8                                              \
                                0x00000009

//
//! fSAMPLING = fD / 16, = 5
//
#define TIMER_CH3ICFR_TI3F_FD16_5                                             \
                                0x0000000A

//
//! fSAMPLING = fD / 16, = 6
//
#define TIMER_CH3ICFR_TI3F_FD16_6                                             \
                                0x0000000B

//
//! fSAMPLING = fD / 16, = 8
//
#define TIMER_CH3ICFR_TI3F_FD16_8                                             \
                                0x0000000C

//
//! fSAMPLING = fD / 32, = 5
//
#define TIMER_CH3ICFR_TI3F_FD32_5                                             \
                                0x0000000D

//
//! fSAMPLING = fD / 32, = 6
//
#define TIMER_CH3ICFR_TI3F_FD32_6                                             \
                                0x0000000E

//
//! fSAMPLING = fD / 32, = 8
//
#define TIMER_CH3ICFR_TI3F_FD32_8                                             \
                                0x0000000F

//
//! Channel 3 Input Source TI3 Filter Setting shift
//
#define TIMER_CH3ICFR_TI3F_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH0OCFR Channel 0 Output 
//! Configuration Register (CH0OCFR).
//! @{
//
//*****************************************************************************

//
//! Channel 0 Immediate Active Enable
//
#define TIMER_CH0OCFR_CH0IMAE   0x00000020

//
//! Channel 0 Capture/Compare Register (CH0CCR) Preload Enable
//
#define TIMER_CH0OCFR_CH0PRE    0x00000010

//
//! Channel 0 Reference Output Clear Enable
//
#define TIMER_CH0OCFR_REF0CE    0x00000008

//
//! Channel 0 Output Mode Setting mask
//
#define TIMER_CH0OCFR_CH0OM_M   0x00000007

//
//! No Change
//
#define TIMER_CH0OCFR_CH0OM_NOCHG                                            \
                                0x00000000

//
//! Output 0 on compare match
//
#define TIMER_CH0OCFR_CH0OM_0                                                \
                                0x00000001

//
//! Output 1 on compare match
//
#define TIMER_CH0OCFR_CH0OM_1                                                \
                                0x00000002

//
//! Output toggles on compare match
//
#define TIMER_CH0OCFR_CH0OM_TOGGLE                                           \
                                0x00000003

//
//! Force inactive 每 CH0OREF is forced to 0
//
#define TIMER_CH0OCFR_CH0OM_INACTIVE                                         \
                                0x00000004

//
//! Force active 每 CH0OREF is forced to 1
//
#define TIMER_CH0OCFR_CH0OM_ACTIVE                                          \
                                0x00000005

//
//! PWM mode 1
//
#define TIMER_CH0OCFR_CH0OM_PWMM1                                            \
                                0x00000006

//
//! PWM mode 2
//
#define TIMER_CH0OCFR_CH0OM_PWMM2                                            \
                                0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH1OCFR Channel 1 Output 
//! Configuration Register (CH1OCFR).
//! @{
//
//*****************************************************************************

//
//! Channel 1 Immediate Active Enable
//
#define TIMER_CH1OCFR_CH1IMAE   0x00000020

//
//! Channel 1 Capture/Compare Register (CH1CCR) Preload Enable
//
#define TIMER_CH1OCFR_CH1PRE    0x00000010

//
//! Channel 1 Reference Output Clear Enable
//
#define TIMER_CH1OCFR_REF0CE    0x00000008

//
//! Channel 1 Output Mode Setting mask
//
#define TIMER_CH1OCFR_CH1OM_M   0x00000007

//
//! No Change
//
#define TIMER_CH1OCFR_CH1OM_NOCHG                                            \
                                0x00000000

//
//! Output 0 on compare match
//
#define TIMER_CH1OCFR_CH1OM_0                                                \
                                0x00000001

//
//! Output 1 on compare match
//
#define TIMER_CH1OCFR_CH1OM_1                                                \
                                0x00000002

//
//! Output toggles on compare match
//
#define TIMER_CH1OCFR_CH1OM_TOGGLE                                           \
                                0x00000003

//
//! Force inactive 每 CH1OREF is forced to 0
//
#define TIMER_CH1OCFR_CH1OM_INACTIVE                                         \
                                0x00000004

//
//! Force active 每 CH1OREF is forced to 1
//
#define TIMER_CH1OCFR_CH1OM_ACTIVE                                          \
                                0x00000005

//
//! PWM mode 1
//
#define TIMER_CH1OCFR_CH1OM_PWMM1                                            \
                                0x00000006

//
//! PWM mode 2
//
#define TIMER_CH1OCFR_CH1OM_PWMM2                                            \
                                0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH2OCFR Channel 2 Output 
//! Configuration Register (CH2OCFR).
//! @{
//
//*****************************************************************************

//
//! Channel 2 Immediate Active Enable
//
#define TIMER_CH2OCFR_CH2IMAE   0x00000020

//
//! Channel 2 Capture/Compare Register (CH2CCR) Preload Enable
//
#define TIMER_CH2OCFR_CH2PRE    0x00000010

//
//! Channel 2 Reference Output Clear Enable
//
#define TIMER_CH2OCFR_REF0CE    0x00000008

//
//! Channel 2 Output Mode Setting mask
//
#define TIMER_CH2OCFR_CH2OM_M   0x00000007

//
//! No Change
//
#define TIMER_CH2OCFR_CH2OM_NOCHG                                            \
                                0x00000000

//
//! Output 0 on compare match
//
#define TIMER_CH2OCFR_CH2OM_0                                                \
                                0x00000001

//
//! Output 1 on compare match
//
#define TIMER_CH2OCFR_CH2OM_1                                                \
                                0x00000002

//
//! Output toggles on compare match
//
#define TIMER_CH2OCFR_CH2OM_TOGGLE                                           \
                                0x00000003

//
//! Force inactive 每 CH2OREF is forced to 0
//
#define TIMER_CH2OCFR_CH2OM_INACTIVE                                         \
                                0x00000004

//
//! Force active 每 CH2OREF is forced to 1
//
#define TIMER_CH2OCFR_CH2OM_ACTIVE                                           \
                                0x00000005

//
//! PWM mode 1
//
#define TIMER_CH2OCFR_CH2OM_PWMM1                                            \
                                0x00000006

//
//! PWM mode 2
//
#define TIMER_CH2OCFR_CH2OM_PWMM2                                            \
                                0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CH3OCFR Channel 3 Output 
//! Configuration Register (CH3OCFR).
//! @{
//
//*****************************************************************************

//
//! Channel 3 Immediate Active Enable
//
#define TIMER_CH3OCFR_CH3IMAE   0x00000020

//
//! Channel 3 Capture/Compare Register (CH3CCR) Preload Enable
//
#define TIMER_CH3OCFR_CH3PRE    0x00000010

//
//! Channel 3 Reference Output Clear Enable
//
#define TIMER_CH3OCFR_REF0CE    0x00000008

//
//! Channel 3 Output Mode Setting mask
//
#define TIMER_CH3OCFR_CH3OM_M   0x00000007

//
//! No Change
//
#define TIMER_CH3OCFR_CH3OM_NOCHG                                            \
                                0x00000000

//
//! Output 0 on compare match
//
#define TIMER_CH3OCFR_CH3OM_0                                                \
                                0x00000001

//
//! Output 1 on compare match
//
#define TIMER_CH3OCFR_CH3OM_1                                                \
                                0x00000002

//
//! Output toggles on compare match
//
#define TIMER_CH3OCFR_CH3OM_TOGGLE                                           \
                                0x00000003

//
//! Force inactive 每 CH3OREF is forced to 0
//
#define TIMER_CH3OCFR_CH3OM_INACTIVE                                         \
                                0x00000004

//
//! Force active 每 CH3OREF is forced to 1
//
#define TIMER_CH3OCFR_CH3OM_ACTIVE                                          \
                                0x00000005

//
//! PWM mode 1
//
#define TIMER_CH3OCFR_CH3OM_PWMM1                                            \
                                0x00000006

//
//! PWM mode 2
//
#define TIMER_CH3OCFR_CH3OM_PWMM2                                            \
                                0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CHCTR Channel Control Register(CHCTR)
//! @{
//
//*****************************************************************************

//
//! Channel 3 Capture/Compare Enable
//
#define TIMER_CHCTR_CH3E        0x00000040

//
//! Channel 2 Capture/Compare Enable
//
#define TIMER_CHCTR_CH2E        0x00000010

//
//! Channel 1 Capture/Compare Enable
//
#define TIMER_CHCTR_CH1E        0x00000004

//
//! Channel 0 Capture/Compare Enable
//
#define TIMER_CHCTR_CH0E        0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CHPOLR Channel Polarity 
//! Configuration Register
//! @{
//
//*****************************************************************************

//
//! Channel 3 Capture/Compare Polarity
//
#define TIMER_CHCTR_CH3P        0x00000040

//
//! Channel 2 Capture/Compare Polarity
//
#define TIMER_CHCTR_CH2P        0x00000010

//
//! Channel 1 Capture/Compare Polarity
//
#define TIMER_CHCTR_CH1P        0x00000004

//
//! Channel 0 Capture/Compare Polarity
//
#define TIMER_CHCTR_CH0P        0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_ICTR Timer Interrupt Control 
//! Register (ICTR)
//! @{
//
//*****************************************************************************

//
//! Trigger the event PDMA Request Enable
//
#define TIMER_DICTR_TEVDE       0x04000000

//
//! Update event PDMA Request Enable
//
#define TIMER_DICTR_UEVDE       0x02000000

//
//! Channal 3 Capture/Compare PDMA Request ENABLE
//
#define TIMER_DICTR_CH3CCDE     0x00080000

//
//! Channal 2 Capture/Compare PDMA Request ENABLE
//
#define TIMER_DICTR_CH2CCDE     0x00040000

//
//! Channal 1 Capture/Compare PDMA Request ENABLE
//
#define TIMER_DICTR_CH1CCDE     0x00020000

//
//! Channal 0 Capture/Compare PDMA Request ENABLE
//
#define TIMER_DICTR_CH0CCDE     0x00010000

//
//! Trigger event Interrupt Enable
//
#define TIMER_DICTR_TEVIE       0x00000400

//
//! Update event Interrupt Enable
//
#define TIMER_DICTR_UEVIE       0x00000100

//
//! Channel 3 Capture/Compare Interrupt Enable
//
#define TIMER_DICTR_CH3CCIE     0x00000008

//
//! Channel 2 Capture/Compare Interrupt Enable
//
#define TIMER_DICTR_CH2CCIE     0x00000004

//
//! Channel 1 Capture/Compare Interrupt Enable
//
#define TIMER_DICTR_CH1CCIE     0x00000002

//
//! Channel 0 Capture/Compare Interrupt Enable
//
#define TIMER_DICTR_CH0CCIE     0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_EVGR Timer Event Generator 
//! Register (EVGR)
//! @{
//
//*****************************************************************************

//
//! Trigger Event Generation
//
#define TIMER_EVGR_TEVG         0x00000400

//
//! Update Event Generation
//
#define TIMER_EVGR_UEVG         0x00000100

//
//! Channel 3 Capture/Compare Generation
//
#define TIMER_EVGR_CH3CCG       0x00000008

//
//! Channel 2 Capture/Compare Generation
//
#define TIMER_EVGR_CH2CCG       0x00000004

//
//! Channel 1 Capture/Compare Generation
//
#define TIMER_EVGR_CH1CCG       0x00000002

//
//! Channel 0 Capture/Compare Generation
//
#define TIMER_EVGR_CH0CCG       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_INTSR Timer Interrupt Status 
//! Register (INTSR)
//! @{
//
//*****************************************************************************

//
//! Trigger Event Generation
//
#define TIMER_INTSR_TEVIF       0x00000400

//
//! Update Event Interrupt Flag.
//
#define TIMER_INTSR_UEVIF       0x00000100

//
//! Channel 3 Over-Capture Flag
//
#define TIMER_INTSR_CH3OCF      0x00000080

//
//! Channel 2 Over-Capture Flag
//
#define TIMER_INTSR_CH2OCF      0x00000040

//
//! Channel 1 Over-Capture Flag
//
#define TIMER_INTSR_CH1OCF      0x00000020

//
//! Channel 0 Over-Capture Flag
//
#define TIMER_INTSR_CH0OCF      0x00000010

//
//! Channel 3 Capture/Compare Interrupt Flag
//
#define TIMER_INTSR_CH3CCIF     0x00000008

//
//! Channel 2 Capture/Compare Interrupt Flag
//
#define TIMER_INTSR_CH2CCIF     0x00000004

//
//! Channel 1 Capture/Compare Interrupt Flag
//
#define TIMER_INTSR_CH1CCIF     0x00000002

//
//! Channel 0 Capture/Compare Interrupt Flag
//
#define TIMER_INTSR_CH0CCIF     0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CNTR Timer Counter Register (CNTR)
//! @{
//
//*****************************************************************************

//
//! Timer Prescaler Register mask
//
#define TIMER_CNTR_CNTV_M       0x0000FFFF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_PSCR Timer Counter Register (PSCR)
//! @{
//
//*****************************************************************************

//
//! Timer Prescaler Register (PSCR)
//
#define TIMER_PSCR_PSCV_M       0x0000FFFF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Register_TIMER_CRR Timer Counter Reload Register
//! (CRR)
//! @{
//
//*****************************************************************************

//
//! Timer Prescaler Register (CRR)
//
#define TIMER_CRR_CRV_M         0x0000FFFF

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




