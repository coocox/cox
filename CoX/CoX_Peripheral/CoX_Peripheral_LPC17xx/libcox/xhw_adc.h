//*****************************************************************************
//
//! \file      xhw_adc.h
//! \brief     Macros used when accessing ADC Module.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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


#ifndef __XHW_ADC_H__
#define __XHW_ADC_H__

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_ADC_Register ADC Register Hardware Layer.
//! \brief      Here are detail register information.
//!             it contains:
//!                 - Register offset.
//!                 - detailed bit-field of the registers.
//!                 - Enum and mask of the registers.
//!
//! \note        Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_ADC_Register_Offsets ADC Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>ADC_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//! A/D Control Register.The ADCR register must be written to select the
//! operating mode before A/D conversion can occur.
#define AD_CR                   ((unsigned long)0x00000000)

//! A/D Global Data Register.This register contains the ADC¡¯s DONE bit and the
//! result of the most recent A/D conversion.
#define AD_GDR                  ((unsigned long)0x00000004)

//! A/D Interrupt Enable Register.This register contains enable bits that allow
//! the DONE flag of each A/D channel to be included or excluded from
//! contributing to the generation of an A/D interrupt.
#define AD_INTEN                ((unsigned long)0x0000000C)

//! A/D Channel 0 Data Register.This register contains the result of the most
//! recent conversion completed on channel 0.
#define AD_DR0                  ((unsigned long)0x00000010)

//! A/D Channel 1 Data Register.This register contains the result of the most
//! recent conversion completed on channel 1.
#define AD_DR1                  ((unsigned long)0x00000014)

//! A/D Channel 2 Data Register.This register contains the result of the most
//! recent conversion completed on channel 2.
#define AD_DR2                  ((unsigned long)0x00000018)

//! A/D Channel 3 Data Register.This register contains the result of the most
//! recent conversion completed on channel 3.
#define AD_DR3                  ((unsigned long)0x0000001C)

//! A/D Channel 4 Data Register.This register contains the result of the most
//! recent conversion completed on channel 4.
#define AD_DR4                  ((unsigned long)0x00000020)

//! A/D Channel 5 Data Register.This register contains the result of the most
//! recent conversion completed on channel 5.
#define AD_DR5                  ((unsigned long)0x00000024)

//! A/D Channel 6 Data Register.This register contains the result of the most
//! recent conversion completed on channel 6.
#define AD_DR6                  ((unsigned long)0x00000028)

//! A/D Channel 7 Data Register.This register contains the result of the most
//! recent conversion completed on channel 7.
#define AD_DR7                  ((unsigned long)0x0000002C)

//! A/D Status Register.This register contains DONE and OVERRUN flags for all of
//! the A/D channels, as well as the A/D interrupt/DMA flag.
#define AD_STAT                 ((unsigned long)0x00000030)

//! ADC trim register.
#define AD_TRM                  ((unsigned long)0x00000034)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_ADC_Register_CR ADC Register CR
//! \brief      ADC CR Register description.
//!
//! @{
//
//*****************************************************************************

//! Selects which of the AD0.7:0 pins is (are) to be sampled and converted.
#define CR_SEL_M                BIT_MASK(32, 7, 0)
#define CR_SEL_S                0

//! APB Clock divider.
#define CR_CLKDIV_M             BIT_MASK(32, 15, 8)
#define CR_CLKDIV_S             8

//! ADC Burst mode.
#define CR_BURST                BIT_32_16

//! ADC Power-down mode.
#define CR_PDN                  BIT_32_21

//! Start conversion edge.
#define CR_EDGE                 BIT_32_27

//! Start conversion bits mask
#define CR_START_M              (BIT_32_26 | BIT_32_25 | BIT_32_24)

//! Start conversion now
#define CR_START_NOW            (BIT_32_24                        )

//! Start conversion when the edge selected by bit 27 occurs on P2.10/EINT0
#define CR_START_EINT0          (BIT_32_25                        )

//! Start conversion when the edge selected by bit 27 occurs on P1.27/CAP0.1
#define CR_START_CAP01          (BIT_32_25 | BIT_32_24            )

//! Start conversion when the edge selected by bit 27 occurs on MAT0.1
#define CR_START_MAT01          (BIT_32_26                        )

//! Start conversion when the edge selected by bit 27 occurs on MAT0.3
#define CR_START_MAT03          (BIT_32_26 | BIT_32_24            )

//! Start conversion when the edge selected by bit 27 occurs on MAT1.0
#define CR_START_MAT10          (BIT_32_26 | BIT_32_24            )

//! Start conversion when the edge selected by bit 27 occurs on MAT1.1
#define CR_START_MAT11          (BIT_32_26 | BIT_32_25 | BIT_32_24)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_ADC_Register_GDR ADC Register GDR
//! \brief      ADC GDR Register description.
//!
//! @{
//
//*****************************************************************************

//! ADC convert Result
#define GDR_RESULT_M            BIT_MASK(32, 15, 4)
#define GDR_RESULT_S            4

//! Current convert channel id
#define GDR_CHN_M               BIT_MASK(32, 26, 24)
#define GDR_CHN_S               24

//! Overrun flag
#define GDR_OVERRUN             BIT_32_30

//! Done flag
#define GDR_DONE                BIT_32_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_ADC_Register_INTEN ADC Register INTEN
//! \brief      ADC INTEN Register description.
//!
//! @{
//
//*****************************************************************************

//! Enable ADC channel 0.
#define INTEN_EN0               BIT_32_0

//! Enable ADC channel 1.
#define INTEN_EN1               BIT_32_1

//! Enable ADC channel 2.
#define INTEN_EN2               BIT_32_2

//! Enable ADC channel 3.
#define INTEN_EN3               BIT_32_3

//! Enable ADC channel 4.
#define INTEN_EN4               BIT_32_4

//! Enable ADC channel 5.
#define INTEN_EN5               BIT_32_5

//! Enable ADC channel 6.
#define INTEN_EN6               BIT_32_6

//! Enable ADC channel 7.
#define INTEN_EN7               BIT_32_7

//! Enable global interrupt.
#define INTEN_GEN               BIT_32_8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_ADC_Register_DR ADC Register DR
//! \brief      ADC DR Register description.
//!
//! @{
//
//*****************************************************************************

//! ADC convert data mask
#define DR_RESULT_M             BIT_MASK(32, 15, 4)

//! ADC convert data shift
#define DR_RESULT_S             4

//! ADC overrun flag
#define DR_OVERRUN              BIT_32_30

//! ADC done flag
#define DR_DONE                 BIT_32_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_ADC_Register_STAT ADC Register STAT
//! \brief      ADC STAT Register description.
//!
//! @{
//
//*****************************************************************************

//! ADC channel 0 convert done flag
#define STAT_DONE_0             BIT_32_0

//! ADC channel 1 convert done flag
#define STAT_DONE_1             BIT_32_1

//! ADC channel 2 convert done flag
#define STAT_DONE_2             BIT_32_2

//! ADC channel 3 convert done flag
#define STAT_DONE_3             BIT_32_3

//! ADC channel 4 convert done flag
#define STAT_DONE_4             BIT_32_4

//! ADC channel 5 convert done flag
#define STAT_DONE_5             BIT_32_5

//! ADC channel 6 convert done flag
#define STAT_DONE_6             BIT_32_6

//! ADC channel 7 convert done flag
#define STAT_DONE_7             BIT_32_7

//! ADC channel 0 overrun flag
#define STAT_OVERRUN_0          BIT_32_8

//! ADC channel 1 overrun flag
#define STAT_OVERRUN_1          BIT_32_9

//! ADC channel 2 overrun flag
#define STAT_OVERRUN_2          BIT_32_10

//! ADC channel 3 overrun flag
#define STAT_OVERRUN_3          BIT_32_11

//! ADC channel 4 overrun flag
#define STAT_OVERRUN_4          BIT_32_12

//! ADC channel 5 overrun flag
#define STAT_OVERRUN_5          BIT_32_13

//! ADC channel 6 overrun flag
#define STAT_OVERRUN_6          BIT_32_14

//! ADC channel 7 overrun flag
#define STAT_OVERRUN_7          BIT_32_15

//! ADC interrupt flag
#define STAT_ADINT              BIT_32_16

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

#endif // __XHW_ADC_H__




