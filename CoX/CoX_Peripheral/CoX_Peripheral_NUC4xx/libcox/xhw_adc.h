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
//! A/D Data Register 8
//
#define ADC_DR8                 0x00000020

//
//! A/D Data Register 9
//
#define ADC_DR9                 0x00000024

//
//! A/D Data Register 10
//
#define ADC_DR10                0x00000028

//
//! A/D Data Register 11
//
#define ADC_DR11                0x0000002C

//
//! A/D Data Register 12 (for Band-gap Voltage)
//
#define ADC_DR12                0x00000030

//
//! A/D Data Register 13 (for Temperature Sensor)
//
#define ADC_DR13                0x00000034

//
//! A/D Control Register
//
#define ADC_CR                  0x00000040

//
//! A/D Channel Enable Control Register
//
#define ADC_CHEN                0x00000044

//
//! A/D Compare Register 0
//
#define ADC_CMPR0               0x00000048

//
//! A/D Compare Register 1 
//
#define ADC_CMPR1               0x0000004C

//
//! A/D Status Register
//
#define ADC_STATUS0              0x00000050

//
//! A/D Calibration Register
//
#define ADC_STATUS1             0x00000054

//
//! ADC PDMA current transfer data
//
#define ADC_PDMA                0x00000060

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
#define ADC_CR_DMOF             BIT_32_31

//
//! PWM Trigger Delay Time
//
#define ADC_CR_PWMTRGDLY_M     0x00F00000
#define ADC_CR_PWMTRGDLY_S     16
//
//! A/D Conversion Start
//
#define ADC_CR_SWTRG            BIT_32_11
    
//
//! Differential Input Mode Enable
//
#define ADC_CR_DIFFEN           BIT_32_10

//
//! PDMA Transfer Enable
//
#define ADC_CR_PDMAEN           BIT_32_9

//
//! External Trigger Enable
//
#define ADC_CR_TRGEN            BIT_32_8

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
#define ADC_CR_TRGSEL_M         0x00000030

//
//! Hardware Trigger Source (shift)
//
#define ADC_CR_TRGSEL_S         4

//
//! A/D Converter Operation Mode (mask)
//
#define ADC_CR_OPMODE_M         0x0000000C

//
//! A/D Converter Operation Mode (shift)
//
#define ADC_CR_OPMODE_S         2

//
//! Single conversion Mode
//
#define ADC_CR_OPMODE_SINGLE    0x00000000

//
//! Single-cycle scan conversion Mode
//
#define ADC_CR_OPMODE_SINGLE_CYCLE                                            \
                                0x00000008

//
//! Continuous scan Mode
//
#define ADC_CR_OPMODE_CONTINUOUS 0x0000000C


//
//! A/D Interrupt Enable
//
#define ADC_CR_ADCIEN           BIT_32_1

//
//! A/D Converter Enable
//
#define ADC_CR_ADCEN            BIT_32_0

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
//! Internal Temperature Sensor Selection
//
#define ADC_CHEN_ADTSEN         BIT_32_17

//
//! Internal Band-Gap Selection
//
#define ADC_CHEN_ADBGEN         BIT_32_16

//
//! Analog Input Channel Enable Control Mask
//
#define ADC_CHEN_CHEN_M         0x00000FFF

//
//! Analog Input Channel Enable Control (shift)
//
#define ADC_CHEN_CHEN_S         0

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
#define ADC_CMPRX_CMPCH_M       0x00000078

//
//! Compare Channel Selection (shift)
//
#define ADC_CMPRX_CMPCH_S       3

//
//! Compare Condition
//
#define ADC_CMPRX_CMPCOND       BIT_32_2

//
//! Compare Interrupt Enable
//
#define ADC_CMPRX_CMPIE         BIT_32_1

//
//! Compare Enable
//
#define ADC_CMPRX_CMPEN         BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Register_STATUS0 A/D Status 0 Register (ADC_STATUS0)
//! \brief Defines for the bit fields in the ADC_STATUS0 register.
//! @{
//
//*****************************************************************************

//
//! Current Conversion Channel (mask)
//
#define ADC_STATUS0_CHANNEL_M   0x000000F0

//
//! Current Conversion Channel (shift)
//
#define ADC_STATUS0_CHANNEL_S        4

//
//! A/D converter is busy or idle.
//
#define ADC_STATUS0_BUSY        BIT_32_3

//
//! Compare 1 Flag
//
#define ADC_STATUS0_CMPF1       BIT_32_2

//
//! Compare 0 Flag 
//
#define ADC_STATUS0_CMPF0       BIT_32_1

//
//! ADC Interrupt Flag
//
#define ADC_STATUS0_ADIF        BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ADC_Register_STATUS1 A/D Status 1 Register (ADC_STATUS1)
//! \brief Defines for the bit fields in the ADC_STATUS1 register.
//! @{
//
//*****************************************************************************

//
//! ADC Overrun Flag (Read Only) Mask
//
#define ADC_STATUS1_OV_M        0x3FFF0000

//
//! Overrun Flag (Read Only) shift
//
#define ADC_STATUS1_OV_S        16                           

//
//! Data Valid Flag (Read Only) Mask
//
#define ADC_STATUS1_VALID_M     0x00003FFF

//
//! Data Valid Flag (Read Only) shift
//
#define ADC_STATUS1_VALID_S     0

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
