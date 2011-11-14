//*****************************************************************************
//
//! \file xhw_adc.h
//! \brief Macros used when accessing the ADC hardware.
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
//*****************************************************************************

#ifndef __XHW_ADC_H__
#define __XHW_ADC_H__

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
//! \addtogroup NUC1xx_ADC_Register NUC1xx ADC Register
//! \brief Here are the detailed info of ADC registers. 
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
//! \addtogroup NUC1xx_ADC_Register_Offset ADC Register Offset(Map)
//! \brief Here is the ADC register offset, users can get the register address
//! through <b>ADC_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! A/D Data Register 0
//
#define ADC_DR0                 0x00000000

//
//! A/D Data Register 1
//
#define ADC_DR1                 0x00000004

//
//! A/D Data Register 2
//
#define ADC_DR2                 0x00000008

//
//! A/D Data Register 3
//
#define ADC_DR3                 0x0000000C

//
//! A/D Data Register 4
//
#define ADC_DR4                 0x00000010

//
//! A/D Data Register 5
//
#define ADC_DR5                 0x00000014

//
//! A/D Data Register 6
//
#define ADC_DR6                 0x00000018

//
//! A/D Data Register 7
//
#define ADC_DR7                 0x0000001C

//
//! A/D Control Register
//
#define ADC_CR                  0x00000020

//
//! A/D Channel Enable Register
//
#define ADC_CHER                0x00000024

//
//! A/D Compare Register 0
//
#define ADC_CMPR0               0x00000028

//
//! A/D Compare Register 1 
//
#define ADC_CMPR1               0x0000002C

//
//! A/D Status Register
//
#define ADC_SR                  0x00000030

//
//! A/D Calibration Register
//
#define ADC_CALR                0x00000034

//
//! ADC PDMA current transfer data
//
#define ADC_PDMA                0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_DRx A/D Data Registers (ADC_DRx(0-7))
//! \brief Defines for the bit fields in the \ref ADC_DR0 - \ref ADC_DR7 register.
//! @{
//
//*****************************************************************************

//
//!Valid Flag 
//
#define ADC_DRX_VALID           0x00020000

//
//! Over Run Flag
//
#define ADC_DRX_OVERRUN         0x00010000

//
//! A/D Conversion Result (mask)
//
#define ADC_DRX_RSLT_M          0x0000FFFF

//
//! A/D Conversion Result (shift)
//
#define ADC_DRX_RSLT_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_CR A/D Control Register (ADC_CR)
//! \brief Defines for the bit fields in the \ref ADC_CR register.
//! @{
//
//*****************************************************************************

//
//! A/D differential input Mode Output Format
//
#define ADC_CR_DMOF             0x80000000

//
//! A/D Conversion Start
//
#define ADC_CR_ADST             0x00000800
    
//
//! Differential Input Mode Enable
//
#define ADC_CR_DIFFEN           0x00000400

//
//! PDMA Transfer Enable
//
#define ADC_CR_PTEN             0x00000200

//
//! External Trigger Enable
//
#define ADC_CR_TRGEN            0x00000100

//
//! External Trigger Condition (mask)
//
#define ADC_CR_TRGCOND_M        0x000000C0

//
//! External Trigger Condition (shift)
//
#define ADC_CR_TRGCOND_S        6

//
//! External Trigger Condition is low level
//
#define ADC_CR_TRGCOND_LOW_LEVEL                                              \
                                0x00000000

//
//! External Trigger Condition is high level
//
#define ADC_CR_TRGCOND_HIGH_LEVEL                                             \
                                0x00000040

//
//! External Trigger Condition is falling edge
//
#define ADC_CR_TRGCOND_FALLING_EDGE                                           \
                                0x00000080

//
//! External Trigger Condition is rising edge
//
#define ADC_CR_TRGCOND_RISING_EDGE                                            \
                                0x000000C0

//
//! Hardware Trigger Source (mask)
//
#define ADC_CR_TRGS_M           0x00000030

//
//! Hardware Trigger Source (shift)
//
#define ADC_CR_TRGS_S           4

//
//! A/D Converter Operation Mode (mask)
//
#define ADC_CR_ADMD_M           0x0000000C

//
//! A/D Converter Operation Mode (shift)
//
#define ADC_CR_ADMD_S           2

//
//! Single conversion Mode
//
#define ADC_CR_ADMD_SINGLE      0x00000000

//
//! Single-cycle scan conversion Mode
//
#define ADC_CR_ADMD_SINGLE_CYCLE                                              \
                                0x00000008

//
//! Continuous scan Mode
//
#define ADC_CR_ADMD_CONTINUOUS  0x0000000C


//
//! A/D Interrupt Enable
//
#define ADC_CR_ADIE             0x00000002

//
//! A/D Converter Enable
//
#define ADC_CR_ADEN             0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_CHER A/D Channel Enable Register (ADC_CHER)
//! \brief Defines for the bit fields in the \ref ADC_CHER register.
//! @{
//
//*****************************************************************************

//
//! Analog Input Channel 7 select Mask
//
#define ADC_CHER_PRESEL_M       0x00000300

//
//! Analog Input Channel 7 select (shift)
//
#define ADC_CHER_PRESEL_S       8

//
//! Analog Input Channel 7 is External analog input 
//
#define ADC_CHER_PRESEL_EXT     0x00000000

//
//! Analog Input Channel 7 is Internal bandgap voltage 
//
#define ADC_CHER_PRESEL_INT_BG  0x00000100

//
//! Analog Input Channel 7 is Internal temperature sensor
//
#define ADC_CHER_PRESEL_INT_TS  0x00000200

//
//! Analog Input Channel 7 Enable
//
#define ADC_CHER_CHEN7          0x00000080

//
//! Analog Input Channel 6 Enable
//
#define ADC_CHER_CHEN6          0x00000040

//
//! Analog Input Channel 5 Enable
//
#define ADC_CHER_CHEN5          0x00000020

//
//! Analog Input Channel 4 Enable
//
#define ADC_CHER_CHEN4          0x00000010

//
//! Analog Input Channel 3 Enable
//
#define ADC_CHER_CHEN3          0x00000008

//
//! Analog Input Channel 2 Enable
//
#define ADC_CHER_CHEN2          0x00000004

//
//! Analog Input Channel 1 Enable
//
#define ADC_CHER_CHEN1          0x00000002

//
//! Analog Input Channel 0 Enable
//
#define ADC_CHER_CHEN0          0x00000001

//
//! Analog Input Channel N Enable (mask)
//
#define ADC_CHER_CHEN_M         0x000000FF

//
//! Analog Input Channel N Enable (shift)
//
#define ADC_CHER_CHEN_S         0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_CMPRx A/D Compare Register 0/1 (ADC_CMPRx)
//! \brief Defines for the bit fields in the \ref ADC_CMPR0, \ref ADC_CMPR1 
//! register.
//! @{
//
//*****************************************************************************

//
//! Comparison Data (mask)
//
#define ADC_CMPRX_CMPD_M        0x0FFF0000

//
//! Comparison Data (shift)
//
#define ADC_CMPRX_CMPD_S        16

//
//! Compare Match Count (mask)
//
#define ADC_CMPRX_CMPMATCNT_M   0x00000F00

//
//! Compare Match Count (shift)
//
#define ADC_CMPRX_CMPMATCNT_S   8

//
//! Compare Channel Selection (mask)
//
#define ADC_CMPRX_CMPCH_M       0x00000038

//
//! Compare Channel Selection (shift)
//
#define ADC_CMPRX_CMPCH_S       3

//
//! Compare Condition
//
#define ADC_CMPRX_CMPCOND       0x00000004

//
//! Compare Interrupt Enable
//
#define ADC_CMPRX_CMPIE         0x00000002

//
//! Compare Enable
//
#define ADC_CMPRX_CMPEN         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_SR A/D Status Register (ADC_SR)
//! \brief Defines for the bit fields in the ADC_SR register.
//! @{
//
//*****************************************************************************

//
//! Channel7 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN7         0x00800000

//
//! Channel6 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN6         0x00400000

//
//! Channel5 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN5         0x00200000

//
//! Channel4 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN4         0x00100000

//
//! Channel3 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN3         0x00080000

//
//! Channel2 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN2         0x00040000

//
//! Channel1 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN1         0x00020000

//
//! Channel0 Over Run flag(a mirror to OVERRUN bit in DRx)
//
#define ADC_SR_OVERRUN0         0x00010000

//
//! Channels Over Run flag (mask)
//
#define ADC_SR_OVERRUN_M        0x00FF0000

//
//! Channels Over Run flag (shift)
//
#define ADC_SR_OVERRUN_S        16

//
//! Channel7 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID7           0x00008000

//
//! Channel6 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID6           0x00004000

//
//! Channel5 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID5           0x00002000

//
//! Channel4 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID4           0x00001000

//
//! Channel3 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID3           0x00000800

//
//! Channel2 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID2           0x00000400

//
//! Channel1 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID1           0x00000200

//
//! Channel0 Data Valid flag(a mirror to VALID bit in DRx)
//
#define ADC_SR_VALID0           0x00000100

//
//! Channel Data Valid flags (mask)
//
#define ADC_SR_VALID_M          0x0000FF00

//
//! Channel Data Valid flags (shift)
//
#define ADC_SR_VALID_S          8

//
//! Current Conversion Channel (mask)
//
#define ADC_SR_CHANNEL_M        0x00000070

//
//! Current Conversion Channel (shift)
//
#define ADC_SR_CHANNEL_S        4

//
//! A/D converter is busy or idle.
//
#define ADC_SR_BUSY             0x00000008

//
//! Compare 1 Flag
//
#define ADC_SR_CMPF1            0x00000004

//
//! Compare 0 Flag 
//
#define ADC_SR_CMPF0            0x00000002

//
//!A/D Conversion End Flag
//
#define ADC_SR_ADF              0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_CALR A/D Calibration Register (ADC_CALR)
//! \brief Defines for the bit fields in the ADC_CALR register.
//! @{
//
//*****************************************************************************

//
//! Calibration is Done
//
#define ADC_CALR_CALDONE        0x00000002

//
//! Self Calibration Enable
//
#define ADC_CALR_CALEN          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_PDMA A/D PDMA current transfer data Register (ADC_PDMA)
//! \brief Defines for the bit fields in the ADC_PDMA register.
//! @{
//
//*****************************************************************************

//
//! ADC PDMA current transfer data (mask)
//
#define ADC_PDMA_DATA_M         0x00000FFF

//
//! ADC PDMA current transfer data (shift) 
//
#define ADC_PDMA_DATA_S         0

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

