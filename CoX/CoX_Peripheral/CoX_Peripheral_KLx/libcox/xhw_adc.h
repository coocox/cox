//*****************************************************************************
//
//! \file xhw_adc.h
//! \brief Macros used when accessing the ADC hardware.
//! \version V2.2.1.0
//! \date 8/15/2012
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
//! \addtogroup KLx_ADC_Register KLx ADC Register
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
//! \addtogroup KLx_ADC_Register_Offset ADC Register Offset(Map)
//! \brief Here is the ADC register offset, users can get the register address
//! through <b>ADC_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! ADC Status and Control Registers 1(ADC0_SC1A)
//
#define ADC0_SC1A               0x00000000

//
//! ADC Status and Control Registers 1(ADC0_SC1A)
//
#define ADC0_SC1B               0x00000004

//
//! ADC Configuration Register 1(ADC0_CFG1)
//
#define ADC0_CFG1               0x00000008

//
//! ADC Configuration Register 2(ADC0_CFG2)
//
#define ADC0_CFG2               0x0000000C

//
//! ADC Data Result Register(ADC0_RA)
//
#define ADC0_RA                 0x00000010

//
//! ADC Data Result Register(ADC0_RB)
//
#define ADC0_RB                 0x00000014

//
//! Compare Value Registers(ADC0_CV1)
//
#define ADC0_CV1                0x00000018

//
//! Compare Value Registers(ADC0_CV2)
//
#define ADC0_CV2                0x0000001C

//
//! ADC Status and Control Registers 2(ADC0_SC2)
//
#define ADC0_SC2                0x00000020

//
//! ADC Status and Control Registers 3(ADC0_SC3)
//
#define ADC0_SC3                0x00000024

//
//! ADC Offset Correction Register(ADC0_OFS)
//
#define ADC0_OFS                0x00000028

//
//! ADC Plus-Side Gain Register(ADC0_PG)
//
#define ADC0_PG                 0x0000002C

//
//! ADC  Minus-Side Gain Register(ADC0_MG)
//
#define ADC0_MG                 0x00000030

//
//! ADC Plus-Side General Calibration Value Register(ADC0_CLPD)
//
#define ADC0_CLPD               0x00000034

//
//! ADC Plus-Side General Calibration Value Register(ADC0_CLPS)
//
#define ADC0_CLPS               0x00000038

//
//! ADC Plus-Side General Calibration Value Register(ADC0_CLP4)
//
#define ADC0_CLP4               0x0000003C

//
//! ADC Plus-Side General Calibration Value Register(ADC0_CLP3)
//
#define ADC0_CLP3               0x00000040

//
//! ADC Plus-Side General Calibration Value Register(ADC0_CLP2)
//
#define ADC0_CLP2               0x00000044

//
//! ADC Plus-Side General Calibration Value Register(ADC0_CLP1)
//
#define ADC0_CLP1               0x00000048

//
//! ADC Plus-Side General Calibration Value Register(ADC0_CLP0)
//
#define ADC0_CLP0               0x0000004C

//
//! ADC Minus-Side General Calibration Value Register(ADC0_CLMD)
//
#define ADC0_CLMD               0x00000054

//
//! ADC Minus-Side General Calibration Value Register(ADC0_CLMS)
//
#define ADC0_CLMS               0x00000058

//
//! ADC Minus-Side General Calibration Value Register(ADC0_CLM4)
//
#define ADC0_CLM4               0x0000005C

//
//! ADC Minus-Side General Calibration Value Register(ADC0_CLM3)
//
#define ADC0_CLM3               0x00000060

//
//! ADC Minus-Side General Calibration Value Register(ADC0_CLM2)
//
#define ADC0_CLM2               0x00000064

//
//! ADC Minus-Side General Calibration Value Register(ADC0_CLM1)
//
#define ADC0_CLM1               0x00000068

//
//! ADC Minus-Side General Calibration Value Register(ADC0_CLM0)
//
#define ADC0_CLM0               0x0000006C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_SC1A A/D  Status and Control Registers (ADC0_SC1A)
//! \brief Defines for the bit fields in the \ref ADC0_SC1A register.
//! @{
//
//*****************************************************************************

//
//! Conversion Complete Flag 
//
#define ADC0_SC1A_COCO_FLAG     0x00000080

//
//! Interrupt Enable 
//
#define ADC0_SC1A_AIEN          0x00000040

//
//! Differential Mode Enable 
//
#define ADC0_SC1A_DIFF          0x00000020

//
//! Input channel select (mask)
//
#define ADC0_SC1A_ADCH_M        0x0000001F

//
//! Input channel select (Shift)
//
#define ADC0_SC1A_ADCH_S        0

//
//! Select Temperature Sensor as input
//
#define ADC0_SC1A_ADCH_TEMP_SENSOR                                            \
                                0x0000001A

//
//! Select Bandgap as input
//
#define ADC0_SC1A_ADCH_BANDGAP  0x0000001B
                                
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CFG1 A/D Configuration Register(ADC0_CFG1)
//! \brief Defines for the bit fields in the \ref ADC0_CFG1 register.
//! @{
//
//*****************************************************************************

//
//! Low-Power Configuration
//
#define ADC0_CFG1_ADLPC         0x00000080

//
//! Clock Divide Select(mask)
//
#define ADC0_CFG1_ADIV_M        0x00000060

//
//! Clock Divide Select(shift)
//
#define ADC0_CFG1_ADIV_S        5

//
//! Sample time configuration
//
#define ADC0_CFG1_ADLSMP        0x00000010

//
//! ADC Conversion resolution mode(mask)
//
#define ADC0_CFG1_MODE_M        0x0000000C

//
//! ADC Conversion resolution mode(shift)
//
#define ADC0_CFG1_MODE_S        2

//
//! Input Clock Select(mask)
//
#define ADC0_CFG1_ADICLK_M      0x00000003

//
//! Input Clock Select(shift)
//
#define ADC0_CFG1_ADICLK_S      0

//
//! Input Clock is Bus Clock
//
#define ADC0_CFG1_ADICLK_BUSCLK 0x00000000

//
//! Input Clock is (Bus Clock)/2
//
#define ADC0_CFG1_ADICLK_BUSCLK_2                                             \
                                0x00000001

//
//! Input Clock is Alternate clock(ALTCLK)
//
#define ADC0_CFG1_ADICLK_ALTCLK                                               \
                                0x00000002

//
//! Input Clock is Asynchronous clock(ADACK)
//
#define ADC0_CFG1_ADICLK_ADACK  0x00000003


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CFG2 A/D Configuration Register(ADC0_CFG2)
//! \brief Defines for the bit fields in the \ref ADC0_CFG2 register.
//! @{
//
//*****************************************************************************

//
//! ADC Mux Select
//
#define ADC0_CFG2_MUXSEL        0x00000010

//
//! Asynchronous Clock Output Enable
//
#define ADC0_CFG2_ADACKEN       0x00000008

//
//! High-Speed Configuration
//
#define ADC0_CFG2_ADHSC         0x00000004

//
//! Long Sample Time Select(mask)
//
#define ADC0_CFG2_ADLSTS_M      0x00000003

//
//! Long Sample Time Select(shift)
//
#define ADC0_CFG2_ADLSTS_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_RA A/D Data Result Register(ADC0_RA)
//! \brief Defines for the bit fields in the \ref ADC0_RA register.
//! @{
//
//*****************************************************************************

//
//! Data result A Mask
//
#define ADC0_RA_D_M             0x0000FFFF

//
//! Data result A Shift
//
#define ADC0_RA_D_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_RB A/D Data Result Register(ADC0_RB)
//! \brief Defines for the bit fields in the \ref ADC0_RB register.
//! @{
//
//*****************************************************************************

//
//! Data result B Mask
//
#define ADC0_RB_D_M             0x0000FFFF

//
//! Data result B Shift
//
#define ADC0_RB_D_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CV1 A/D Compare Value Register(ADC0_CV1)
//! \brief Defines for the bit fields in the \ref ADC0_CV1 register.
//! @{
//
//*****************************************************************************

//
//! Compare Value Mask
//
#define ADC0_CV1_CV_M           0x0000FFFF

//
//! Compare Value Shift
//
#define ADC0_CV1_CV_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_RB A/D Compare Value Register(ADC0_CV2)
//! \brief Defines for the bit fields in the \ref ADC0_CV2 register.
//! @{
//
//*****************************************************************************

//
//! Compare Value Mask
//
#define ADC0_CV2_CV_M           0x0000FFFF

//
//! Compare Value Shift
//
#define ADC0_CV2_CV_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_SC2 A/D Status and Control Register 2(ADC0_SC2)
//! \brief Defines for the bit fields in the \ref ADC0_SC2 register.
//! @{
//
//*****************************************************************************

//
//! Conversion Active
//
#define ADC0_SC2_ADACT          0x00000080

//
//! Conversion Trigger Select(Hardware)
//
#define ADC0_SC2_ADTRG_HARD     0x00000040

//
//! Compare Function Enable
//
#define ADC0_SC2_ACFE           0x00000020

//
//! Compare Function Greater Than Enable
//
#define ADC0_SC2_ACFGT          0x00000010

//
//! Compare Function Range Enable
//
#define ADC0_SC2_ACREN          0x00000008

//
//! DMA Enable
//
#define ADC0_SC2_DMAEN          0x00000004

//
//! Voltage Reference Selection(mask)
//
#define ADC_SC2_REFSEL_M        0x00000003

//
//! Voltage Reference Selection(shift)
//
#define ADC_SC2_REFSEL_S        0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_SC3 A/D Status and Control Register 3(ADC0_SC3)
//! \brief Defines for the bit fields in the \ref ADC0_SC3 register.
//! @{
//
//*****************************************************************************

//
//! Calibration
//
#define ADC0_SC3_CAL            0x00000080

//
//! Calibration Failed Flag
//
#define ADC0_SC3_CALF           0x00000040

//
//! Continuous Conversion Enable
//
#define ADC0_SC3_ADCO           0x00000008

//
//! Hardware Average Enable
//
#define ADC0_SC3_AVGE           0x00000004

//
//! Hardware Average Select(mask)
//
#define ADC0_SC3_AVGS_M         0x00000003

//
//! Hardware Average Select(shift)
//
#define ADC0_SC3_AVGS_S         0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_OFS A/D Offset Correction Register(ADC0_OFS)
//! \brief Defines for the bit fields in the \ref ADC0_OFS register.
//! @{
//
//*****************************************************************************

//
//! Offset Error Correction Value(mask)
//
#define ADC0_OFS_M              0x0000FFFF

//
//! Offset Error Correction Value(shift)
//
#define ADC0_OFS_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_PG A/D Plus-Side Gain Register(ADC0_PG)
//! \brief Defines for the bit fields in the \ref ADC0_PG register.
//! @{
//
//*****************************************************************************

//
//! Plus-Side Gain(mask)
//
#define ADC0_PG_M               0x0000FFFF

//
//! Plus-Side Gain(shift)
//
#define ADC0_PG_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_MG A/D Minus-Side Gain Register(ADC0_MG)
//! \brief Defines for the bit fields in the \ref ADC0_MG register.
//! @{
//
//*****************************************************************************

//
//! Minus-Side Gain(mask)
//
#define ADC0_MG_M               0x0000FFFF

//
//! Minus-Side Gain(shift)
//
#define ADC0_MG_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLPD A/D Plus-Side General Calibration Value Register(ADC0_CLPD)
//! \brief Defines for the bit fields in the \ref ADC0_CLPD register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLPD_M               0x0000003F

//
//! Calibration Value(shift)
//
#define ADC0_CLPD_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLPD A/D Plus-Side General Calibration Value Register(ADC0_CLPS)
//! \brief Defines for the bit fields in the \ref ADC0_CLPS register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLPS_M               0x0000003F

//
//! Calibration Value(shift)
//
#define ADC0_CLPS_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLP4 A/D Plus-Side General Calibration Value Register(ADC0_CLP4)
//! \brief Defines for the bit fields in the \ref ADC0_CLP4 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLP4_M               0x000003FF

//
//! Calibration Value(shift)
//
#define ADC0_CLP4_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLP3 A/D Plus-Side General Calibration Value Register(ADC0_CLP3)
//! \brief Defines for the bit fields in the \ref ADC0_CLP3 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLP3_M               0x000001FF

//
//! Calibration Value(shift)
//
#define ADC0_CLP3_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLP2 A/D Plus-Side General Calibration Value Register(ADC0_CLP2)
//! \brief Defines for the bit fields in the \ref ADC0_CLP2 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLP2_M               0x000000FF

//
//! Calibration Value(shift)
//
#define ADC0_CLP2_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLP1 A/D Plus-Side General Calibration Value Register(ADC0_CLP1)
//! \brief Defines for the bit fields in the \ref ADC0_CLP1 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLP1_M               0x0000007F

//
//! Calibration Value(shift)
//
#define ADC0_CLP1_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLP0 A/D Plus-Side General Calibration Value Register(ADC0_CLP0)
//! \brief Defines for the bit fields in the \ref ADC0_CLP0 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLP0_M               0x0000003F

//
//! Calibration Value(shift)
//
#define ADC0_CLP0_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLMD A/D Minus-Side General Calibration Value Register(ADC0_CLMD)
//! \brief Defines for the bit fields in the \ref ADC0_CLMD register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLMD_M               0x0000003F

//
//! Calibration Value(shift)
//
#define ADC0_CLPM_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLMS A/D Minus-Side General Calibration Value Register(ADC0_CLMS)
//! \brief Defines for the bit fields in the \ref ADC0_CLMS register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLMS_M               0x0000003F

//
//! Calibration Value(shift)
//
#define ADC0_CLMS_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLM4 A/D Minus-Side General Calibration Value Register(ADC0_CLM4)
//! \brief Defines for the bit fields in the \ref ADC0_CLM4 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLP4_M               0x000003FF

//
//! Calibration Value(shift)
//
#define ADC0_CLP4_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLM3 A/D Minus-Side General Calibration Value Register(ADC0_CLM3)
//! \brief Defines for the bit fields in the \ref ADC0_CLM3 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLM3_M               0x000001FF

//
//! Calibration Value(shift)
//
#define ADC0_CLM3_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLM2 A/D Minus-Side General Calibration Value Register(ADC0_CLM2)
//! \brief Defines for the bit fields in the \ref ADC0_CLM2 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLM2_M               0x000000FF

//
//! Calibration Value(shift)
//
#define ADC0_CLM2_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLM1 A/D Minus-Side General Calibration Value Register(ADC0_CLM1)
//! \brief Defines for the bit fields in the \ref ADC0_CLM1 register.
//! @{
//
//*****************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLM1_M               0x0000007F

//
//! Calibration Value(shift)
//
#define ADC0_CLM1_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Register_CLM0 A/D Minus-Side General Calibration Value Register(ADC0_CLM0)
//! \brief Defines for the bit fields in the \ref ADC0_CLM0 register.
//! @{
//!
//*******************************************************************************

//
//! Calibration Value(mask)
//
#define ADC0_CLM0_M               0x0000003F

//
//! Calibration Value(shift)
//
#define ADC0_CLM0_S               0

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

#endif  // __XHW_ADC_H__ 

