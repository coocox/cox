//*****************************************************************************
//
//! \file xhw_timer.h
//! \brief Macros and defines used when accessing the TIMER hardware.
//! \version V2.2.1.0
//! \date 6/12/2012
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
//! \addtogroup STM32F1xx_TIMER_Register STM32F1xx TIMER Register
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
//! \addtogroup STM32F1xx_TIMER_Register_Address_Offset TIMER Register Offset(Map)
//! \brief Here is the TIMER register offset, users can get the register address
//! through <b>TIMER_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Timer Counter Configuration Register1 (CR1)
//
#define TIMER_CR1               0x00000000  

//
//! Timer Counter Configuration Register2 (CR2)
//
#define TIMER_CR2               0x00000004  

//
//! Timer slave mode control register (SMCR)
//
#define TIMER_SMCR              0x00000008  

//
//! Timer DMA/interrupt enable register (DIER)
//
#define TIMER_DIER              0x0000000C

//
//! Timer status register (SR)
//
#define TIMER_SR                0x00000010

//
//! Timer event generation register (EGR)
//
#define TIMER_EGR               0x00000014

//
//! Channel capture/compare mode register (CCMR1)
//
#define TIMER_CCMR1             0x00000018

//
//! Channel capture/compare mode register 2 (CCMR2)
//
#define TIMER_CCMR2             0x0000001C

//
//! Channel capture/compare enable register (CCER)
//
#define TIMER_CCER              0x00000020

//
//! Timer counter register (CNT)
//
#define TIMER_CNT               0x00000024

//
//! Timer prescaler register (PSC)
//
#define TIMER_PSC               0x00000028

//
//! Timer auto-reload register (ARR)
//
#define TIMER_ARR               0x0000002C

//
//! Timer repetition counter register	(RCR)
//
#define TIMER_RCR               0x00000030

//
//! Timer capture/compare register 1 (CCR1) 
//
#define TIMER_CCR1	            0x00000034

//
//! Timer capture/compare register 2 (CCR2) 
//
#define TIMER_CCR2	            0x00000038

//
//! Timer capture/compare register 3 (CCR3) 
//
#define TIMER_CCR3	            0x0000003C

//
//! Timer capture/compare register 4 (CCR4) 
//
#define TIMER_CCR4	            0x00000040

//
//! Timer break and dead-time register  (BDTR) 
//
#define TIMER_BDTR              0x00000044

//
//! Timer DMA control register (DCR)
//
#define TIMER_DCR               0x00000048

//
//! Timer DMA address for full transfer (DMAR) 
//
#define TIMER_DMAR              0x0000004C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CR1 Timer Counter Configuration Register1 (CR1)
//! \brief Defines for the bit fields in the TIMER_CR1 register.
//! @{
//
//*****************************************************************************

//
//! Clock division mask
//
#define TIMER_CR1_CKD_M         0x00000300  

//
//!  tDTS=tCK_INT
//
#define TIMER_CR1_CKD0          0x00000000

//
//!  tDTS=2tCK_INT
//
#define TIMER_CR1_CKD2          0x00000100

//
//!  tDTS=4tCK_INT
//
#define TIMER_CR1_CKD4          0x00000200

//
//! Clock division shift
//
#define TIMER_CR1_CKD_S         8

//
//! Auto-reload preload enable
//
#define TIMER_CR1_ARR           0x00000080

//
//! Center-aligned mode selection mask
//
#define TIMER_CR1_CMS_M         0x00000060

//
//! Edge-aligned mode
//
#define TIMER_CR1_CMS_E         0x00000000 

//
//! Center-aligned mode 1
//
#define TIMER_CR1_CMS_1         0x00000020 

//
//! Center-aligned mode selection mask
//

#define TIMER_CR1_CMS_2         0x00000040 
//
//! Center-aligned mode selection mask
//

#define TIMER_CR1_CMS_3         0x00000060 

//
//! Center-aligned mode selection mask
//
#define TIMER_CR1_CMS_S         5

//
//! Direction
//
#define TIMER_CR1_DIR           0x00000010

//
//! One pulse mode
//
#define TIMER_CR1_OPM           0x00000008

//
//!  Update request source
//
#define TIMER_CR1_URS           0x00000004

//
//!  Update disable
//
#define TIMER_CR1_UDIS          0x00000002

//
//!  Counter enable
//
#define TIMER_CR1_CEN           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CR2 Timer Counter Configuration Register2(CR2)
//! \brief Defines for the bit fields in the TIMER_CR2 register.
//! @{
//
//*****************************************************************************

//
//! Output Idle state 4 (OC4 output)
//
#define TIMER_CR2_OIS4          0x00004000

//
//! Output Idle state 3 (OC3N output)
//
#define TIMER_CR2_OIS3N         0x00002000

//
//! Output Idle state 3 (OC3 output)
//
#define TIMER_CR2_OIS3          0x00001000

//
//! Output Idle state 2 (OC2N output)
//
#define TIMER_CR2_OIS2N         0x00000800

//
//! Output Idle state 2 (OC2 output)
//
#define TIMER_CR2_OIS2          0x00000600

//
//! Output Idle state 1 (OC1N output)
//
#define TIMER_CR2_OIS1N         0x00000200

//
//! Output Idle state 1 (OC1 output)
//
#define TIMER_CR2_OIS1          0x00000100

//
//! TI1 selection
//
#define TIMER_CR2_TI1S          0x00000080

//
//! Master mode selection mask
//
#define TIMER_CR2_MMS_M         0x00000070

//
//! Reset
//
#define TIMER_CR2_MMS_RESET     0x00000000

//
//! Enable
//
#define TIMER_CR2_MMS_ENABLE    0x00000010

//
//! Update
//
#define TIMER_CR2_MMS_UPDATE    0x00000020

//
//! Compare Pulse 
//
#define TIMER_CR2_MMS_CP        0x00000030

//
//! OC1REF
//
#define TIMER_CR2_MMS_OC1REF    0x00000040

//
//! OC2REF
//
#define TIMER_CR2_MMS_OC2REF    0x00000050

//
//! OC3REF
//
#define TIMER_CR2_MMS_OC3REF    0x00000060

//
//! OC4REF
//
#define TIMER_CR2_MMS_OC4REF    0x00000070

//
//! Master mode selection shift
//
#define TIMER_CR2_MMS_S         4

//
//! Capture/compare DMA selection
//
#define TIMER_CR2_MMS_CCDS     0x00000008

//
//!  Capture/compare control update selection
//
#define TIMER_CR2_MMS_CCUS     0x00000004

//
//!  Capture/compare preloaded control
//
#define TIMER_CR2_MMS_CCPC     0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_SMCR Timer slave mode control register (SMCR)
//! \brief Defines for the bit fields in the TIMER_SMCR register.
//! @{
//
//*****************************************************************************

//
//! External trigger polarity
//
#define TIMER_SMCR_ETP          0x00008000

//
//! External clock enable
//							   
#define TIMER_SMCR_ECE          0x00004000

//
//! External trigger prescaler mask
//							   
#define TIMER_SMCR_ETPS_M       0x00003000

//
//! Prescaler OFF
//
#define TIMER_SMCR_ETPS_0       0x00000000

//
//! ETRP frequency divided by 2
//
#define TIMER_SMCR_ETPS_2       0x00001000

//
//! ETRP frequency divided by 4
//
#define TIMER_SMCR_ETPS_4       0x00002000

//
//! ETRP frequency divided by 8
//
#define TIMER_SMCR_ETPS_8       0x00003000

//
//! External trigger prescaler shift
//							   
#define TIMER_SMCR_ETPS_S       12

//
//! External trigger filter mask
//							   
#define TIMER_SMCR_ETF_M        0x00000F00

//
//! No filter, sampling is done at fDTS
//							   
#define TIMER_SMCR_ETF_FD       0x00000000

//
//!  fSAMPLING=fCK_INT, N=2
//							   
#define TIMER_SMCR_ETF_FCLK_2   0x00000100

//
//!  fSAMPLING=fCK_INT, N=4
//							   
#define TIMER_SMCR_ETF_FCLK_4   0x00000200

//
//!  fSAMPLING=fCK_INT, N=8
//							   
#define TIMER_SMCR_ETF_FCLK_8   0x00000300

//
//!  fSAMPLING=fDTS/2, N=6
//							   
#define TIMER_SMCR_ETF_FDTS2_6  0x00000400

//
//!  fSAMPLING=fDTS/2, N=8
//							   
#define TIMER_SMCR_ETF_FDTS2_8  0x00000500

//
//!  fSAMPLING=fDTS/4, N=6
//							   
#define TIMER_SMCR_ETF_FDTS4_6  0x00000600

//
//!  fSAMPLING=fDTS/4, N=8
//							   
#define TIMER_SMCR_ETF_FDTS4_8  0x00000700

//
//!  fSAMPLING=fDTS/8, N=6
//							   
#define TIMER_SMCR_ETF_FDTS8_6  0x00000800

//
//!  fSAMPLING=fDTS/8, N=8
//							   
#define TIMER_SMCR_ETF_FDTS8_8  0x00000900

//
//!  fSAMPLING=fDTS/16, N=5
//							   
#define TIMER_SMCR_ETF_FDTS16_5 0x00000A00
																
//
//!  fSAMPLING=fDTS/16, N=6
//							   
#define TIMER_SMCR_ETF_FDTS16_6 0x00000B00

//
//!  fSAMPLING=fDTS/16, N=8
//							   
#define TIMER_SMCR_ETF_FDTS16_8 0x00000C00
																
//
//!  fSAMPLING=fDTS/32, N=5
//							   
#define TIMER_SMCR_ETF_FDTS32_5 0x00000D00

//
//!  fSAMPLING=fDTS/32, N=6
//							   
#define TIMER_SMCR_ETF_FDTS32_6 0x00000E00

//
//!  fSAMPLING=fDTS/32, N=8
//							   
#define TIMER_SMCR_ETF_FDTS32_8 0x00000F00
																
//
//! External trigger filter shift
//							   
#define TIMER_SMCR_ETF_S        8

//
//! Master/slave mode
//							   
#define TIMER_SMCR_MSM          0x00000080

//
//! Trigger selection mask
//							   
#define TIMER_SMCR_TS_M         0x00000070

//
//! Internal Trigger 0 (ITR0) 
//							   
#define TIMER_SMCR_TS_ITR0      0x00000000

//
//! Internal Trigger 1 (ITR1) 
//							   
#define TIMER_SMCR_TS_ITR1      0x00000010

//
//! Internal Trigger 2 (ITR2) 
//							   
#define TIMER_SMCR_TS_ITR2      0x00000020

//
//! Internal Trigger 3 (ITR3) 
//							   
#define TIMER_SMCR_TS_ITR3      0x00000030

//
//! TI1 Edge Detector (TI1F_ED)
//							   
#define TIMER_SMCR_TS_TI1F_ED   0x00000040

//
//! Filtered Timer Input 1 (TI1FP1)
//							   
#define TIMER_SMCR_TS_TI1FP1    0x00000050

//
//! Filtered Timer Input 2 (TI1FP2)
//							   
#define TIMER_SMCR_TS_TI1FP2    0x00000060

//
//!  External Trigger input (ETRF)
//							   
#define TIMER_SMCR_TS_ETRF      0x00000070

//
//! Trigger selection shift
//							   
#define TIMER_SMCR_TS_S         4

//
//! Slave mode selection mask
//							   
#define TIMER_SMCR_SMS_M        0x00000007

//
//! Slave mode disabled 
//							   
#define TIMER_SMCR_SMS_DIS      0x00000000

//
//!  Encoder mode 1
//							   
#define TIMER_SMCR_SMS_EC1      0x00000001

//
//!  Encoder mode 2
//							   
#define TIMER_SMCR_SMS_EC2      0x00000002

//
//!  Encoder mode 3
//							   
#define TIMER_SMCR_SMS_EC3      0x00000003

//
//!  Reset Mode
//							   
#define TIMER_SMCR_SMS_RESET    0x00000004

//
//!  Gated Mode
//							   
#define TIMER_SMCR_SMS_GATED    0x00000005

//
//!  Trigger Mode 
//							   
#define TIMER_SMCR_SMS_TRIGGER  0x00000006

//
//!  Trigger Mode 
//							   
#define TIMER_SMCR_SMS_EXC1     0x00000007

//
//! Slave mode selection shift
//							   
#define TIMER_SMCR_SMS_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_DIER Timer Control Register(DIER).
//! @{
//
//*****************************************************************************

//
//!  Trigger DMA request enable
//
#define TIMER_DIER_TDE          0x00004000

//
//!  COM DMA request enable
//
#define TIMER_DIER_COMDE        0x00002000

//
//!  Capture/Compare 4 DMA request enable
//
#define TIMER_DIER_CC4DE        0x00001000

//
//!  Capture/Compare 3 DMA request enable
//
#define TIMER_DIER_CC3DE        0x00000800

//
//!  Capture/Compare 2 DMA request enable
//
#define TIMER_DIER_CC2DE        0x00000400

//
//!  Capture/Compare 1 DMA request enable
//
#define TIMER_DIER_CC1DE        0x00000200

//
//!  Update DMA request enable
//
#define TIMER_DIER_UDE          0x00000100

//
//!  Break interrupt enable
//
#define TIMER_DIER_BIE          0x00000080

//
//!  Trigger interrupt enable
//
#define TIMER_DIER_TIE          0x00000040

//
//!  COM interrupt enable
//
#define TIMER_DIER_COMIE        0x00000020

//
//!  Capture/Compare 4 interrupt enable
//
#define TIMER_DIER_CC4IE        0x00000010

//
//!  Capture/Compare 3 interrupt enable
//
#define TIMER_DIER_CC3IE        0x00000008

//
//!  Capture/Compare 2 interrupt enable
//
#define TIMER_DIER_CC2IE        0x00000004

//
//!  Capture/Compare 1 interrupt enable
//
#define TIMER_DIER_CC1IE        0x00000002
//
//!  Update interrupt enable
//
#define TIMER_DIER_UIE          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_SR Timer status register (SR)
//! @{
//
//*****************************************************************************

//
//! Capture/Compare 4 overcapture flag
//
#define TIMER_SR_CC4OF          0x00001000

//
//! Capture/Compare 3 overcapture flag
//
#define TIMER_SR_CC3OF          0x00000800

//
//! Capture/Compare 2 overcapture flag
//
#define TIMER_SR_CC2OF          0x00000400

//
//! Capture/Compare 1 overcapture flag
//
#define TIMER_SR_CC1OF          0x00000200

//
//!  Break interrupt flag
//
#define TIMER_SR_BIF            0x00000080

//
//!  Trigger interrupt flag
//
#define TIMER_SR_TIF            0x00000040

//
//!  COM interrupt flag
//
#define TIMER_SR_COMIF          0x00000020

//
//!  Capture/Compare 4 interrupt flag
//
#define TIMER_SR_CC4IF          0x00000010

//
//!  Capture/Compare 3 interrupt flag
//
#define TIMER_SR_CC3IF          0x00000008

//
//!  Capture/Compare 2 interrupt flag
//
#define TIMER_SR_CC2IF          0x00000004

//
//!  Capture/Compare 1 interrupt flag
//
#define TIMER_SR_CC1IF          0x00000002

//
//!  Update interrupt flag
//
#define TIMER_SR_UIF            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_EGR Timer event generation register (EGR)
//! @{
//
//*****************************************************************************

//
//! Break generation
//
#define TIMER_EGR_BG            0x00000080

//
//! Trigger generation
//
#define TIMER_EGR_TG            0x00000040

//
//! Capture/Compare control update generation
//
#define TIMER_EGR_COMG          0x00000020

//
//! Capture/Compare 4 generation
//
#define TIMER_EGR_CC4G          0x00000010

//
//! Capture/Compare 3 generation
//
#define TIMER_EGR_CC3G          0x00000008

//
//! Capture/Compare 2 generation
//
#define TIMER_EGR_CC2G          0x00000004

//
//! Capture/Compare 1 generation
//
#define TIMER_EGR_CC1G          0x00000002

//
//! Update generation
//
#define TIMER_EGR_UG            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CCMR1 Channel capture/compare mode register (CCMR1)
//! @{
//
//*****************************************************************************

//////////// Output compare mode: ///////////////////////

//
//! Output Compare 2 clear enable
//
#define TIMER_CCMR1_OC2CE       0x00008000

//
//! Output Compare 2 mode mask
//
#define TIMER_CCMR1_OC2M_M      0x00007000

//
//! Set channel 2 to active level on match
//
#define TIMER_CCMR1_OC2M_SA     0x00001000

//
//! Set channel 2 to  inactive level on match
//
#define TIMER_CCMR1_OC2M_SIA    0x00002000

//
//! Toggle 
//
#define TIMER_CCMR1_OC2M_TOGGLE 0x00003000

//
//! Force inactive level - OC1REF is forced low. 
//
#define TIMER_CCMR1_OC2M_FA     0x00004000

//
//! Force active level - OC1REF is forced high.
//
#define TIMER_CCMR1_OC2M_FIA    0x00005000

//
//! PWM mode 1
//
#define TIMER_CCMR1_OC2M_PWMM1  0x00006000

//
//! PWM mode 2
//
#define TIMER_CCMR1_OC2M_PWMM2  0x00007000

//
//! Output Compare 2 mode mask
//
#define TIMER_CCMR1_OC2M_S      12

//
//! Output Compare 2 preload enable
//
#define TIMER_CCMR1_OC2PE       0x00000800

//
//! Output Compare 2 fast enable
//
#define TIMER_CCMR1_OC2FE       0x00000400

//
//! Capture/Compare 2 selection mask
//
#define TIMER_CCMR1_CC2S_M      0x00000300

//
//! CC2 channel is configured as output
//
#define TIMER_CCMR1_CC2S_OUTPUT 0x00000000

//
//! CC2 channel is configured as input, IC2 is mapped on TI2
//
#define TIMER_CCMR1_CC2S_IC2TI2 0x00000100

//
//! CC2 channel is configured as input, IC2 is mapped on TI1
//
#define TIMER_CCMR1_CC2S_IC2TI1 0x00000200

//
//! CC2 channel is configured as input, IC2 is mapped on TRC.
//
#define TIMER_CCMR1_CC2S_IC2TRC 0x00000300

//
//! Capture/Compare 2 selection shift
//
#define TIMER_CCMR1_CC2S_S      8

//
//! Output Compare 1 clear enable
//
#define TIMER_CCMR1_OC1CE       0x00000080

//
//! Output Compare 1 mode mask
//
#define TIMER_CCMR1_OC1M_M      0x00000070

//
//! Set channel 1 to active level on match
//
#define TIMER_CCMR1_OC1M_SA     0x00000010

//
//! Set channel 1 to  inactive level on match
//
#define TIMER_CCMR1_OC1M_SIA    0x00000020

//
//! Toggle 
//
#define TIMER_CCMR1_OC1M_TOGGLE 0x00000030

//
//! Force inactive level - OC1REF is forced low. 
//
#define TIMER_CCMR1_OC1M_FA     0x00000040

//
//! Force active level - OC1REF is forced high.
//
#define TIMER_CCMR1_OC1M_FIA    0x00000050

//
//! PWM mode 1
//
#define TIMER_CCMR1_OC1M_PWMM1  0x00000060

//
//! PWM mode 2
//
#define TIMER_CCMR1_OC1M_PWMM2  0x00000070

//
//! Output Compare 1 mode mask
//
#define TIMER_CCMR1_OC1M_S      4

//
//! Output Compare 1 preload enable
//
#define TIMER_CCMR1_OC1PE       0x00000008

//
//! Output Compare 1 fast enable
//
#define TIMER_CCMR1_OC1FE       0x00000004

//
//! Capture/Compare 1 selection mask
//
#define TIMER_CCMR1_CC1S_M      0x00000003

//
//! CC1 channel is configured as output
//
#define TIMER_CCMR1_CC1S_OUTPUT 0x00000000

//
//! CC1 channel is configured as input, IC1 is mapped on TI1
//
#define TIMER_CCMR1_CC1S_IC1TI1 0x00000001

//
//! CC1 channel is configured as input, IC2 is mapped on TI2
//
#define TIMER_CCMR1_CC1S_IC1TI2 0x00000002

//
//! CC1 channel is configured as input, IC2 is mapped on TRC.
//
#define TIMER_CCMR1_CC1S_IC1TRC 0x00000003

//
//! Capture/Compare 1 selection shift
//
#define TIMER_CCMR1_CC1S_S      0

//////////// Input capture mode ///////////////////////

//
//!  Input capture 2 filter mask
//							   
#define TIMER_CCMR1_IC2F_M       0x0000F000

//
//! No filter, sampling is done at fDTS
//							   
#define TIMER_CCMR1_IC2F_FD      0x00000000

//
//!  fSAMPLING=fCK_INT, N=2
//							   
#define TIMER_CCMR1_IC2F_FCLK_2  0x00001000

//
//!  fSAMPLING=fCK_INT, N=4
//							   
#define TIMER_CCMR1_IC2F_FCLK_4  0x00002000

//
//!  fSAMPLING=fCK_INT, N=8
//							   
#define TIMER_CCMR1_IC2F_FCLK_8  0x00003000

//
//!  fSAMPLING=fDTS/2, N=6
//							   
#define TIMER_CCMR1_IC2F_FDTS2_6 0x00004000

//
//!  fSAMPLING=fDTS/2, N=8
//							   
#define TIMER_CCMR1_IC2F_FDTS2_8 0x00005000

//
//!  fSAMPLING=fDTS/4, N=6
//							   
#define TIMER_CCMR1_IC2F_FDTS4_6 0x00006000

//
//!  fSAMPLING=fDTS/4, N=8
//							   
#define TIMER_CCMR1_IC2F_FDTS4_8 0x00007000

//
//!  fSAMPLING=fDTS/8, N=6
//							   
#define TIMER_CCMR1_IC2F_FDTS8_6 0x00008000

//
//!  fSAMPLING=fDTS/8, N=8
//							   
#define TIMER_CCMR1_IC2F_FDTS8_8 0x00009000

//
//!  fSAMPLING=fDTS/16, N=5
//							   
#define TIMER_CCMR1_IC2F_FDTS16_5                                             \
                                0x0000A000
														
//
//!  fSAMPLING=fDTS/16, N=6
//							   
#define TIMER_CCMR1_IC2F_FDTS16_6                                             \
                                0x0000B000

//
//!  fSAMPLING=fDTS/16, N=8
//							   
#define TIMER_CCMR1_IC2F_FDTS16_8                                             \
                                0x0000C000
														
//
//!  fSAMPLING=fDTS/32, N=5
//							   
#define TIMER_CCMR1_IC2F_FDTS32_5                                             \
                                0x0000D000

//
//!  fSAMPLING=fDTS/32, N=6
//							   
#define TIMER_CCMR1_IC2F_FDTS32_6                                             \
                                0x0000E000

//
//!  fSAMPLING=fDTS/32, N=8
//							   
#define TIMER_CCMR1_IC2F_FDTS32_8                                             \
                                0x0000F000									

//
//! Input capture 2 filter shift
//							   
#define TIMER_CCMR1_IC2F_S      12

//
//! Input capture 2 prescaler mask
//							   
#define TIMER_CCMR1_IC2PSC_M    0x00000C00

//
//!  no prescaler, capture is done each time an edge is detected on the capture input
//							   
#define TIMER_CCMR1_IC2PSC_0    0x00000000

//
//!  capture is done once every 2 events
//							   
#define TIMER_CCMR1_IC2PSC_2    0x00000400

//
//!  capture is done once every 4 events
//							   
#define TIMER_CCMR1_IC2PSC_4    0x00000800

//
//!  capture is done once every 8 events
//							   
#define TIMER_CCMR1_IC2PSC_8    0x00000C00

//
//! Input capture 2 prescaler shift
//							   
#define TIMER_CCMR1_IC2PSC_S    10

//
//!  Input capture 1 filter mask
//							   
#define TIMER_CCMR1_IC1F_M       0x000000F0

//
//! No filter, sampling is done at fDTS
//							   
#define TIMER_CCMR1_IC1F_FD      0x00000000

//
//!  fSAMPLING=fCK_INT, N=2
//							   
#define TIMER_CCMR1_IC1F_FCLK_2  0x00000010

//
//!  fSAMPLING=fCK_INT, N=4
//							   
#define TIMER_CCMR1_IC1F_FCLK_4  0x00000020

//
//!  fSAMPLING=fCK_INT, N=8
//							   
#define TIMER_CCMR1_IC1F_FCLK_8  0x00000030

//
//!  fSAMPLING=fDTS/2, N=6
//							   
#define TIMER_CCMR1_IC1F_FDTS2_6 0x00000040

//
//!  fSAMPLING=fDTS/2, N=8
//							   
#define TIMER_CCMR1_IC1F_FDTS2_8 0x00000050

//
//!  fSAMPLING=fDTS/4, N=6
//							   
#define TIMER_CCMR1_IC1F_FDTS4_6 0x00000060

//
//!  fSAMPLING=fDTS/4, N=8
//							   
#define TIMER_CCMR1_IC1F_FDTS4_8 0x00000070

//
//!  fSAMPLING=fDTS/8, N=6
//							   
#define TIMER_CCMR1_IC1F_FDTS8_6 0x00000080

//
//!  fSAMPLING=fDTS/8, N=8
//							   
#define TIMER_CCMR1_IC1F_FDTS8_8 0x00000090

//
//!  fSAMPLING=fDTS/16, N=5
//							   
#define TIMER_CCMR1_IC1F_FDTS16_5                                             \
                                 0x000000A0
														
//
//!  fSAMPLING=fDTS/16, N=6
//							   
#define TIMER_CCMR1_IC1F_FDTS16_6                                             \
                                 0x000000B0

//
//!  fSAMPLING=fDTS/16, N=8
//							   
#define TIMER_CCMR1_IC1F_FDTS16_8                                             \
                                0x000000C0
														
//
//!  fSAMPLING=fDTS/32, N=5
//							   
#define TIMER_CCMR1_IC1F_FDTS32_5                                             \
                                0x000000D0

//
//!  fSAMPLING=fDTS/32, N=6
//							   
#define TIMER_CCMR1_IC1F_FDTS32_6                                             \
                                0x000000E0

//
//!  fSAMPLING=fDTS/32, N=8
//							   
#define TIMER_CCMR1_IC1F_FDTS32_8                                             \
                                0x000000F0									
				
//
//! Input capture 1 filter shift
//							   
#define TIMER_CCMR1_IC1F_S      4

//
//! Input capture 1 prescaler mask
//							   
#define TIMER_CCMR1_IC1PSC_M    0x0000000C

//
//!  no prescaler, capture is done each time an edge is detected on the capture input
//							   
#define TIMER_CCMR1_IC1PSC_0    0x00000000

//
//!  capture is done once every 2 events
//							   
#define TIMER_CCMR1_IC1PSC_2    0x00000004

//
//!  capture is done once every 4 events
//							   
#define TIMER_CCMR1_IC1PSC_4    0x00000008

//
//!  capture is done once every 8 events
//							   
#define TIMER_CCMR1_IC1PSC_8    0x0000000C

//
//! Input capture 2 prescaler shift
//							   
#define TIMER_CCMR1_IC1PSC_S    2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CCMR2 Channel capture/compare mode register 2 (CCMR2)
//! @{
//
//*****************************************************************************

//////////// Output compare mode: ///////////////////////

//
//! Output Compare 4 clear enable
//
#define TIMER_CCMR2_OC4CE       0x00008000

//
//! Output Compare 4 mode mask
//
#define TIMER_CCMR2_OC4M_M      0x00007000

//
//! Set channel 4 to active level on match
//
#define TIMER_CCMR2_OC4M_SA     0x00001000

//
//! Set channel 4 to  inactive level on match
//
#define TIMER_CCMR2_OC4M_SIA    0x00002000

//
//! Toggle 
//
#define TIMER_CCMR2_OC4M_TOGGLE 0x00003000

//
//! Force inactive level - OC4REF is forced low. 
//
#define TIMER_CCMR2_OC4M_FA     0x00004000

//
//! Force active level - OC4REF is forced high.
//
#define TIMER_CCMR2_OC4M_FIA    0x00005000

//
//! PWM mode 1
//
#define TIMER_CCMR2_OC4M_PWMM1  0x00006000

//
//! PWM mode 2
//
#define TIMER_CCMR2_OC4M_PWMM2  0x00007000

//
//! Output Compare 4 mode mask
//
#define TIMER_CCMR2_OC4M_S      12

//
//! Output Compare 4 preload enable
//
#define TIMER_CCMR2_OC4PE       0x00000800

//
//! Output Compare 4 fast enable
//
#define TIMER_CCMR2_OC4FE       0x00000400

//
//! Capture/Compare 4 selection mask
//
#define TIMER_CCMR2_CC4S_M      0x00000300

//
//! CC4 channel is configured as output
//
#define TIMER_CCMR2_CC4S_OUTPUT 0x00000000

//
//! CC4 channel is configured as input, IC4 is mapped on TI4
//
#define TIMER_CCMR2_CC4S_IC4TI4 0x00000100

//
//! CC4 channel is configured as input, IC4 is mapped on TI3
//
#define TIMER_CCMR2_CC4S_IC4TI3 0x00000200

//
//! CC4 channel is configured as input, IC4 is mapped on TRC.
//
#define TIMER_CCMR2_CC4S_IC4TRC 0x00000300

//
//! Capture/Compare 4 selection shift
//
#define TIMER_CCMR2_CC4S_S      8

//
//! Output Compare 3 clear enable
//
#define TIMER_CCMR2_OC3CE       0x00000080

//
//! Output Compare 3 mode mask
//
#define TIMER_CCMR2_OC3M_M      0x00000070

//
//! Set channel 3 to active level on match
//
#define TIMER_CCMR2_OC3M_SA     0x00000010

//
//! Set channel 3 to  inactive level on match
//
#define TIMER_CCMR2_OC3M_SIA    0x00000020

//
//! Toggle 
//
#define TIMER_CCMR2_OC3M_TOGGLE 0x00000030

//
//! Force inactive level - OC3REF is forced low. 
//
#define TIMER_CCMR2_OC3M_FA     0x00000040

//
//! Force active level - OC3REF is forced high.
//
#define TIMER_CCMR2_OC3M_FIA    0x00000050

//
//! PWM mode 1
//
#define TIMER_CCMR2_OC3M_PWMM1  0x00000060

//
//! PWM mode 2
//
#define TIMER_CCMR2_OC3M_PWMM2  0x00000070

//
//! Output Compare 3 mode mask
//
#define TIMER_CCMR2_OC3M_S      4

//
//! Output Compare 3 preload enable
//
#define TIMER_CCMR2_OC3PE       0x00000008

//
//! Output Compare 3 fast enable
//
#define TIMER_CCMR2_OC3FE       0x00000004

//
//! Capture/Compare 3 selection mask
//
#define TIMER_CCMR2_CC3S_M      0x00000003

//
//! CC3 channel is configured as output
//
#define TIMER_CCMR2_CC3S_OUTPUT 0x00000000

//
//! CC3 channel is configured as input, IC3 is mapped on TI3
//
#define TIMER_CCMR2_CC3S_IC3TI3 0x00000001

//
//! CC3 channel is configured as input, IC3 is mapped on TI4
//
#define TIMER_CCMR2_CC3S_IC3TI4 0x00000002

//
//! CC3 channel is configured as input, IC3 is mapped on TRC.
//
#define TIMER_CCMR2_CC3S_IC3TRC 0x00000003

//
//! Capture/Compare 3 selection shift
//
#define TIMER_CCMR2_CC3S_S      0

//////////// Input capture mode ///////////////////////

//
//!  Input capture 4 filter mask
//							   
#define TIMER_CCMR2_IC4F_M       0x0000F000

//
//! No filter, sampling is done at fDTS
//							   
#define TIMER_CCMR2_IC4F_FD      0x00000000

//
//!  fSAMPLING=fCK_INT, N=2
//							   
#define TIMER_CCMR2_IC4F_FCLK_2  0x00001000

//
//!  fSAMPLING=fCK_INT, N=4
//							   
#define TIMER_CCMR2_IC4F_FCLK_4  0x00002000

//
//!  fSAMPLING=fCK_INT, N=8
//							   
#define TIMER_CCMR2_IC4F_FCLK_8  0x00003000

//
//!  fSAMPLING=fDTS/2, N=6
//							   
#define TIMER_CCMR2_IC4F_FDTS2_6 0x00004000

//
//!  fSAMPLING=fDTS/2, N=8
//							   
#define TIMER_CCMR2_IC4F_FDTS2_8 0x00005000

//
//!  fSAMPLING=fDTS/4, N=6
//							   
#define TIMER_CCMR2_IC4F_FDTS4_6 0x00006000

//
//!  fSAMPLING=fDTS/4, N=8
//							   
#define TIMER_CCMR2_IC4F_FDTS4_8 0x00007000

//
//!  fSAMPLING=fDTS/8, N=6
//							   
#define TIMER_CCMR2_IC4F_FDTS8_6 0x00008000

//
//!  fSAMPLING=fDTS/8, N=8
//							   
#define TIMER_CCMR2_IC4F_FDTS8_8 0x00009000

//
//!  fSAMPLING=fDTS/16, N=5
//							   
#define TIMER_CCMR2_IC4F_FDTS16_5                                             \
                                0x0000A000
														
//
//!  fSAMPLING=fDTS/16, N=6
//							   
#define TIMER_CCMR2_IC4F_FDTS16_6                                             \
                                0x0000B000

//
//!  fSAMPLING=fDTS/16, N=8
//							   
#define TIMER_CCMR2_IC4F_FDTS16_8                                             \
                                0x0000C000
														
//
//!  fSAMPLING=fDTS/32, N=5
//							   
#define TIMER_CCMR2_IC4F_FDTS32_5                                             \
                                0x0000D000

//
//!  fSAMPLING=fDTS/32, N=6
//							   
#define TIMER_CCMR2_IC4F_FDTS32_6                                             \
                                0x0000E000

//
//!  fSAMPLING=fDTS/32, N=8
//							   
#define TIMER_CCMR2_IC4F_FDTS32_8                                             \
                                0x0000F000									

//
//! Input capture 4 filter shift
//							   
#define TIMER_CCMR2_IC4F_S      12

//
//! Input capture 4 prescaler mask
//							   
#define TIMER_CCMR2_IC4PSC_M    0x00000C00

//
//!  no prescaler, capture is done each time an edge is detected on the capture input
//							   
#define TIMER_CCMR2_IC4PSC_0    0x00000000

//
//!  capture is done once every 2 events
//							   
#define TIMER_CCMR2_IC4PSC_2    0x00000400

//
//!  capture is done once every 4 events
//							   
#define TIMER_CCMR2_IC4PSC_4    0x00000800

//
//!  capture is done once every 8 events
//							   
#define TIMER_CCMR2_IC4PSC_8    0x00000C00

//
//! Input capture 4 prescaler shift
//							   
#define TIMER_CCMR2_IC4PSC_S    10

//
//!  Input capture 3 filter mask
//							   
#define TIMER_CCMR2_IC3F_M       0x000000F0

//
//! No filter, sampling is done at fDTS
//							   
#define TIMER_CCMR2_IC3F_FD      0x00000000

//
//!  fSAMPLING=fCK_INT, N=2
//							   
#define TIMER_CCMR2_IC3F_FCLK_2  0x00000010

//
//!  fSAMPLING=fCK_INT, N=4
//							   
#define TIMER_CCMR2_IC3F_FCLK_4  0x00000020

//
//!  fSAMPLING=fCK_INT, N=8
//							   
#define TIMER_CCMR2_IC3F_FCLK_8  0x00000030

//
//!  fSAMPLING=fDTS/2, N=6
//							   
#define TIMER_CCMR2_IC3F_FDTS2_6 0x00000040

//
//!  fSAMPLING=fDTS/2, N=8
//							   
#define TIMER_CCMR2_IC3F_FDTS2_8 0x00000050

//
//!  fSAMPLING=fDTS/4, N=6
//							   
#define TIMER_CCMR2_IC3F_FDTS4_6 0x00000060

//
//!  fSAMPLING=fDTS/4, N=8
//							   
#define TIMER_CCMR2_IC3F_FDTS4_8 0x00000070

//
//!  fSAMPLING=fDTS/8, N=6
//							   
#define TIMER_CCMR2_IC3F_FDTS8_6 0x00000080

//
//!  fSAMPLING=fDTS/8, N=8
//							   
#define TIMER_CCMR2_IC3F_FDTS8_8 0x00000090

//
//!  fSAMPLING=fDTS/16, N=5
//							   
#define TIMER_CCMR2_IC3F_FDTS16_5                                             \
                                0x000000A0
														
//
//!  fSAMPLING=fDTS/16, N=6
//							   
#define TIMER_CCMR2_IC3F_FDTS16_6                                             \
                                0x000000B0

//
//!  fSAMPLING=fDTS/16, N=8
//							   
#define TIMER_CCMR2_IC3F_FDTS16_8                                             \
                                0x000000C0
														
//
//!  fSAMPLING=fDTS/32, N=5
//							   
#define TIMER_CCMR2_IC3F_FDTS32_5                                             \
                                0x000000D0

//
//!  fSAMPLING=fDTS/32, N=6
//							   
#define TIMER_CCMR2_IC3F_FDTS32_6                                             \
                                0x000000E0

//
//!  fSAMPLING=fDTS/32, N=8
//							   
#define TIMER_CCMR2_IC3F_FDTS32_8                                             \
                                0x000000F0									
				
//
//! Input capture 3 filter shift
//							   
#define TIMER_CCMR2_IC3F_S      4

//
//! Input capture 3 prescaler mask
//							   
#define TIMER_CCMR2_IC3PSC_M    0x0000000C

//
//!  no prescaler, capture is done each time an edge is detected on the capture input
//							   
#define TIMER_CCMR2_IC3PSC_0    0x00000000

//
//!  capture is done once every 2 events
//							   
#define TIMER_CCMR2_IC3PSC_2    0x00000004

//
//!  capture is done once every 4 events
//							   
#define TIMER_CCMR2_IC3PSC_4    0x00000008

//
//!  capture is done once every 8 events
//							   
#define TIMER_CCMR2_IC3PSC_8    0x0000000C

//
//! Input capture 2 prescaler shift
//							   
#define TIMER_CCMR2_IC3PSC_S    2


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CCER Channel capture/compare enable register (CCER)
//! @{
//
//*****************************************************************************

//
//! Capture/Compare 4 output polarity
//
#define TIMER_CCER_CC4P         0x00002000

//
//! Capture/Compare 4 output polarity
//
#define TIMER_CCER_CC4E         0x00001000

//
//! Capture/Compare 3 complementary output polarity
//
#define TIMER_CCER_CC3NP        0x00000800

//
//! Capture/Compare 3 complementary output enable
//
#define TIMER_CCER_CC3NE        0x00000400

//
//! Capture/Compare 3 output polarity
//
#define TIMER_CCER_CC3P         0x00000200

//
//! Capture/Compare 3 output enable
//
#define TIMER_CCER_CC3E         0x00000100

//
//! Capture/Compare 2 complementary output polarity
//
#define TIMER_CCER_CC2NP        0x00000080

//
//! Capture/Compare 2 complementary output enable
//
#define TIMER_CCER_CC2NE        0x00000040

//
//! Capture/Compare 2 output polarity
//
#define TIMER_CCER_CC2P         0x00000020

//
//! Capture/Compare 2 output enable
//
#define TIMER_CCER_CC2E         0x00000010

//
//! Capture/Compare 1 complementary output polarity
//
#define TIMER_CCER_CC1NP        0x00000008

//
//! Capture/Compare 1 complementary output enable
//
#define TIMER_CCER_CC1NE        0x00000004

//
//! Capture/Compare 1 output polarity
//
#define TIMER_CCER_CC1P         0x00000002

//
//! Capture/Compare 1 output enable
//
#define TIMER_CCER_CC1E         0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CNT Timer counter register (CNT).
//! @{
//
//*****************************************************************************

//
//!  Counter value mask
//
#define TIMER_CNT_CNT_M         0x0000FFFF

//
//!  Counter value shift
//
#define TIMER_CNT_CNT_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_PSC Timer prescaler register (PSC).
//! @{
//
//*****************************************************************************

//
//! Prescaler value mask
//
#define TIMER_PSC_M             0x0000FFFF

//
//! Prescaler value shift

//
#define TIMER_PSC_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_ARR Timer auto-reload register (ARR)
//! @{
//
//*****************************************************************************

//
//!  Auto reload value mask
//
#define TIMER_ARR_CH3IMAE_M     0x0000FFFF

//
//!  Auto reload value shift
//
#define TIMER_ARR_CH3IMAE_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_RCR Timer repetition counter registe(RCR)
//! @{
//
//*****************************************************************************

//
//! Repetition counter value mask
//
#define TIMER_RCR_REP_M         0x000000FF

//
//! Repetition counter value shift
//
#define TIMER_RCR_REP_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CCR1 Timer capture/compare register 1 (CCR1) 
//! @{
//
//*****************************************************************************

//
//! Capture/Compare 1 value mask
//
#define TIMER_CCR1_CCR1_M       0x0000FFFF

//
//! Capture/Compare 1 value shift
//
#define TIMER_CCR1_CCR1_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CCR2 Timer capture/compare register 2 (CCR2) 
//! @{
//
//*****************************************************************************

//
//! Capture/Compare 2 value mask
//
#define TIMER_CCR2_CCR2_M       0x0000FFFF

//
//! Capture/Compare 1 value shift
//
#define TIMER_CCR2_CCR2_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CCR3 Timer capture/compare register 3 (CCR3) 
//! @{
//
//*****************************************************************************

//
//! Capture/Compare 3 value mask
//
#define TIMER_CCR3_CCR3_M       0x0000FFFF

//
//! Capture/Compare 3 value shift
//
#define TIMER_CCR3_CCR3_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_CCR4 Timer capture/compare register 4 (CCR4) 
//! @{
//
//*****************************************************************************

//
//! Capture/Compare 4 value mask
//
#define TIMER_CCR4_CCR4_M       0x0000FFFF

//
//! Capture/Compare 4 value shift
//
#define TIMER_CCR4_CCR4_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_BDTR Timer break and dead-time register (BDTR) 
//! @{
//
//*****************************************************************************

//
//! Main output enable
//
#define TIMER_BDTR_MOE          0x00008000

//
//!  Automatic output enable
//
#define TIMER_BDTR_AOE          0x00004000

//
//!  Break polarity
//
#define TIMER_BDTR_BKP          0x00002000

//
//!  Break enable
//
#define TIMER_BDTR_BKE          0x00001000

//
//!  Off-state selection for Run mode
//
#define TIMER_BDTR_OSSR         0x00000800

//
//!  Off-state selection for Idle mode
//
#define TIMER_BDTR_OSSI         0x00000400

//
//!  Lock configuration mask
//
#define TIMER_BDTR_LOCK_M       0x00000300

//
//!  LOCK OFF - No bit is write protected.
//
#define TIMER_BDTR_LOCK_OFF     0x00000000

//
//!  LOCK Level 1 = DTG bits in TIMx_BDTR register, OISx and OISxN bits in TIMx_CR2 
//! register and BKE/BKP/AOE bits in TIMx_BDTR register can no longer be written.
//
#define TIMER_BDTR_LOCK_LEVEL1  0x00000100

//
//!  LOCK Level 2 = LOCK Level 1 + CC Polarity bits (CCxP/CCxNP bits in TIMx_CCER 
//!  register, as long as the related channel is configured in output through 
//! the CCxS bits) as well as OSSR and OSSI bits can no longer be written.
//
#define TIMER_BDTR_LOCK_LEVEL2  0x00000200

//
//!   LOCK Level 3 = LOCK Level 2 + CC Control bits (OCxM and OCxPE bits in 
//!  TIMx_CCMRx registers, as long as the related channel is configured in output through the 
//!  CCxS bits) can no longer be written.
//
#define TIMER_BDTR_LOCK_LEVEL3  0x00000300

//
//!  Lock configuration shift
//
#define TIMER_BDTR_LOCK_S       8

//
//!  Dead-time generator setup mask
//
#define TIMER_BDTR_DTG_M        0x000000FF

//
//!  Dead-time generator setup shift
//
#define TIMER_BDTR_DTG_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_DCR Timer DMA control register (DCR)
//! @{
//
//*****************************************************************************

//
//! DMA burst length mask
//
#define TIMER_DCR_DBL_M         0x00001F00

//
//! transfer length
//
#define TIMER_DCR_DBL_1         0x00000000
#define TIMER_DCR_DBL_2         0x00000100
#define TIMER_DCR_DBL_3         0x00000200
#define TIMER_DCR_DBL_4         0x00000300
#define TIMER_DCR_DBL_5         0x00000400
#define TIMER_DCR_DBL_6         0x00000500
#define TIMER_DCR_DBL_7         0x00000600
#define TIMER_DCR_DBL_8         0x00000700
#define TIMER_DCR_DBL_9         0x00000800
#define TIMER_DCR_DBL_10        0x00000900
#define TIMER_DCR_DBL_11        0x00000A00
#define TIMER_DCR_DBL_12        0x00000B00
#define TIMER_DCR_DBL_13        0x00000C00
#define TIMER_DCR_DBL_14        0x00000D00
#define TIMER_DCR_DBL_15        0x00000E00
#define TIMER_DCR_DBL_16        0x00000F00
#define TIMER_DCR_DBL_17        0x00001000
#define TIMER_DCR_DBL_18        0x00001100

//
//! DMA burst length shift
//
#define TIMER_DCR_DBL_S         8

//
//! DMA base address mask
//
#define TIMER_DCR_DBA_M         0x0000001F

//
//! DMA base address shift
//
#define TIMER_DCR_DBA_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Register_TIMER_DMAR Timer DMA address for full transfer (DMAR) 
//! @{
//
//*****************************************************************************

//
//! DMA register for burst accesses mask
//
#define TIMER_DMAR_DMAB_M       0x0000FFFF

//
//! DMA register for burst accesses shift
//
#define TIMER_DMAR_DMAB_S       0

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




