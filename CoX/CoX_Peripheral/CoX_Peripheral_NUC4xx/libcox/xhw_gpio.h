//*****************************************************************************
//
//! \file xhw_gpio.h
//! \brief Macros used when accessing the GPIO control hardware.
//! \version V2.2.1.0
//! \date 11/15/2013
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


#ifndef __XHW_GPIO_H__
#define __XHW_GPIO_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register NUC4xx GPIO Register
//! \brief Here are the detailed info of GPIO registers. 
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
//! \addtogroup NUC4xx_GPIO_Register_Offsets GPIO Register Offset(Map)
//! \brief Here is the GPIO register offset, users can get the register address
//! through <b>GPIO_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! GPIO Port  I/O Mode Control
//
#define GPIO_PMD                0x00000000  

//
//! GPIO Port Pin OFF Digital Enable
//
#define GPIO_OFFD               0x00000004  

//
//! GPIO Port Data Output Value
//
#define GPIO_DOUT               0x00000008  

//
//! GPIO Port Data Output Write Mask
//
#define GPIO_DMASK              0x0000000C   

//
//! GPIO Port Pin Value
//
#define GPIO_PIN                0x00000010  

//
//! GPIO Port De-bounce Enable
//
#define GPIO_DBEN               0x00000014  

//
//! GPIO Port Interrupt Mode Control
//
#define GPIO_IMD                0x00000018  

//
//! GPIO Port Interrupt Enable
//
#define GPIO_IEN                0x0000001C  

//
//! GPIO Port Interrupt Trigger Source Indicator
//
#define GPIO_ISRC               0x00000020  

//
//! GPIO Input Schmitt Trigger Enable
//
#define GPIO_SMTEN              0x00000024

//
//! GPIO High Slew Rate Control
//
#define GPIO_SLEWCTL            0x00000028

//
//! GPIO Port External Interrupt De-bounce Control
//
#define GPIO_DBNCECON           0x00000440

//
//! GPIO PA.0 Bit Output/Input Control
//
#define GPIOA0_DOUT             0x00000800

//
//! GPIO PA.1 Bit Output/Input Control
//
#define GPIOA1_DOUT             0x00000804

//
//! GPIO PA.2 Bit Output/Input Control
//
#define GPIOA2_DOUT             0x00000808

//
//! GPIO PA.3 Bit Output/Input Control
//
#define GPIOA3_DOUT             0x0000080C

//
//! GPIO PA.4 Bit Output/Input Control
//
#define GPIOA4_DOUT             0x00000810

//
//! GPIO PA.5 Bit Output/Input Control
//
#define GPIOA5_DOUT             0x00000814

//
//! GPIO PA.6 Bit Output/Input Control
//
#define GPIOA6_DOUT             0x00000818

//
//! GPIO PA.7 Bit Output/Input Control
//
#define GPIOA7_DOUT             0x0000081C

//
//! GPIO PA.8 Bit Output/Input Control
//
#define GPIOA8_DOUT             0x00000820

//
//! GPIO PA.9 Bit Output/Input Control
//
#define GPIOA9_DOUT             0x00000824

//
//! GPIO PA.10 Bit Output/Input Control
//
#define GPIOA10_DOUT            0x00000828

//
//! GPIO PA.11 Bit Output/Input Control
//
#define GPIOA11_DOUT            0x0000082C

//
//! GPIO PA.12 Bit Output/Input Control
//
#define GPIOA12_DOUT            0x00000830

//
//! GPIO PA.13 Bit Output/Input Control
//
#define GPIOA13_DOUT            0x00000834

//
//! GPIO PA.14 Bit Output/Input Control
//
#define GPIOA14_DOUT            0x00000838

//
//! GPIO PA.15 Bit Output/Input Control
//
#define GPIOA15_DOUT            0x0000083C

//
//! GPIO PB.0 Bit Output/Input Control
//
#define GPIOB0_DOUT             0x00000840

//
//! GPIO PB.1 Bit Output/Input Control
//
#define GPIOB1_DOUT             0x00000844

//
//! GPIO PB.2 Bit Output/Input Control
//
#define GPIOB2_DOUT             0x00000848

//
//! GPIO PB.3 Bit Output/Input Control
//
#define GPIOB3_DOUT             0x0000084C

//
//! GPIO PB.4 Bit Output/Input Control
//
#define GPIOB4_DOUT             0x00000850

//
//! GPIO PB.5 Bit Output/Input Control
//
#define GPIOB5_DOUT             0x00000854

//
//! GPIO PB.6 Bit Output/Input Control
//
#define GPIOB6_DOUT             0x00000858

//
//! GPIO PB.7 Bit Output/Input Control
//
#define GPIOB7_DOUT             0x0000085C

//
//! GPIO PB.8 Bit Output/Input Control
//
#define GPIOB8_DOUT             0x00000860

//
//! GPIO PB.9 Bit Output/Input Control
//
#define GPIOB9_DOUT             0x00000864

//
//! GPIO PB.10 Bit Output/Input Control
//
#define GPIOB10_DOUT            0x00000868

//
//! GPIO PB.11 Bit Output/Input Control
//
#define GPIOB11_DOUT            0x0000086C

//
//! GPIO PB.12 Bit Output/Input Control
//
#define GPIOB12_DOUT            0x00000870

//
//! GPIO PB.13 Bit Output/Input Control
//
#define GPIOB13_DOUT            0x00000874

//
//! GPIO PB.14 Bit Output/Input Control
//
#define GPIOB14_DOUT            0x00000878

//
//! GPIO PB.15 Bit Output/Input Control
//
#define GPIOB15_DOUT            0x0000087C

//
//! GPIO PC.0 Bit Output/Input Control
//
#define GPIOC0_DOUT             0x00000880

//
//! GPIO PC.1 Bit Output/Input Control
//
#define GPIOC1_DOUT             0x00000884

//
//! GPIO PC.2 Bit Output/Input Control
//
#define GPIOC2_DOUT             0x00000888

//
//! GPIO PC.3 Bit Output/Input Control
//
#define GPIOC3_DOUT             0x0000088C

//
//! GPIO PC.4 Bit Output/Input Control
//
#define GPIOC4_DOUT             0x00000890

//
//! GPIO PC.5 Bit Output/Input Control
//
#define GPIOC5_DOUT             0x00000894

//
//! GPIO PC.6 Bit Output/Input Control
//
#define GPIOC6_DOUT             0x00000898

//
//! GPIO PC.7 Bit Output/Input Control
//
#define GPIOC7_DOUT             0x0000089C

//
//! GPIO PC.8 Bit Output/Input Control
//
#define GPIOC8_DOUT             0x000008A0

//
//! GPIO PC.9 Bit Output/Input Control
//
#define GPIOC9_DOUT             0x000008A4

//
//! GPIO PC.10 Bit Output/Input Control
//
#define GPIOC10_DOUT            0x000008A8

//
//! GPIO PC.11 Bit Output/Input Control
//
#define GPIOC11_DOUT            0x000008AC

//
//! GPIO PC.12 Bit Output/Input Control
//
#define GPIOC12_DOUT            0x000008B0

//
//! GPIO PC.13 Bit Output/Input Control
//
#define GPIOC13_DOUT            0x000008B4

//
//! GPIO PC.14 Bit Output/Input Control
//
#define GPIOC14_DOUT            0x000008B8

//
//! GPIO PC.15 Bit Output/Input Control
//
#define GPIOC15_DOUT            0x000008BC


//
//! GPIO PD.0 Bit Output/Input Control
//
#define GPIOD0_DOUT             0x000008C0

//
//! GPIO PD.1 Bit Output/Input Control
//
#define GPIOD1_DOUT             0x000008C4

//
//! GPIO PD.2 Bit Output/Input Control
//
#define GPIOD2_DOUT             0x000008C8

//
//! GPIO PD.3 Bit Output/Input Control
//
#define GPIOD3_DOUT             0x000008CC

//
//! GPIO PD.4 Bit Output/Input Control
//
#define GPIOD4_DOUT             0x000008D0

//
//! GPIO PD.5 Bit Output/Input Control
//
#define GPIOD5_DOUT             0x000008D4

//
//! GPIO PD.6 Bit Output/Input Control
//
#define GPIOD6_DOUT             0x000008D8

//
//! GPIO PD.7 Bit Output/Input Control
//
#define GPIOD7_DOUT             0x000008DC

//
//! GPIO PD.8 Bit Output/Input Control
//
#define GPIOD8_DOUT             0x000008E0

//
//! GPIO PD.9 Bit Output/Input Control
//
#define GPIOD9_DOUT             0x000008E4

//
//! GPIO PD.10 Bit Output/Input Control
//
#define GPIOD10_DOUT            0x000008E8

//
//! GPIO PD.11 Bit Output/Input Control
//
#define GPIOD11_DOUT            0x000008EC

//
//! GPIO PD.12 Bit Output/Input Control
//
#define GPIOD12_DOUT            0x000008F0

//
//! GPIO PD.13 Bit Output/Input Control
//
#define GPIOD13_DOUT            0x000008F4

//
//! GPIO PD.14 Bit Output/Input Control
//
#define GPIOD14_DOUT            0x000008F8

//
//! GPIO PD.15 Bit Output/Input Control
//
#define GPIOD15_DOUT            0x000008FC


//
//! GPIO PE.0 Bit Output/Input Control
//
#define GPIOE0_DOUT             0x00000900

//
//! GPIO PE.1 Bit Output/Input Control
//
#define GPIOE1_DOUT             0x00000904

//
//! GPIO PE.2 Bit Output/Input Control
//
#define GPIOE2_DOUT             0x00000908

//
//! GPIO PE.3 Bit Output/Input Control
//
#define GPIOE3_DOUT             0x0000090C

//
//! GPIO PE.4 Bit Output/Input Control
//
#define GPIOE4_DOUT             0x00000910

//
//! GPIO PE.5 Bit Output/Input Control
//
#define GPIOE5_DOUT             0x00000914

//
//! GPIO PE.6 Bit Output/Input Control
//
#define GPIOE6_DOUT             0x00000918

//
//! GPIO PE.7 Bit Output/Input Control
//
#define GPIOE7_DOUT             0x0000091C

//
//! GPIO PE.8 Bit Output/Input Control
//
#define GPIOE8_DOUT             0x00000920

//
//! GPIO PE.9 Bit Output/Input Control
//
#define GPIOE9_DOUT             0x00000924

//
//! GPIO PE.10 Bit Output/Input Control
//
#define GPIOE10_DOUT            0x00000928

//
//! GPIO PE.11 Bit Output/Input Control
//
#define GPIOE11_DOUT            0x0000092C

//
//! GPIO PE.12 Bit Output/Input Control
//
#define GPIOE12_DOUT            0x00000930

//
//! GPIO PE.13 Bit Output/Input Control
//
#define GPIOE13_DOUT            0x00000934

//
//! GPIO PE.14 Bit Output/Input Control
//
#define GPIOE14_DOUT            0x00000938

//
//! GPIO PE.15 Bit Output/Input Control
//
#define GPIOE15_DOUT            0x0000093C

//
//! GPIO PF.0 Bit Output/Input Control
//
#define GPIOF0_DOUT             0x00000940

//
//! GPIO PF.1 Bit Output/Input Control
//
#define GPIOF1_DOUT             0x00000944

//
//! GPIO PF.2 Bit Output/Input Control
//
#define GPIOF2_DOUT             0x00000948

//
//! GPIO PF.3 Bit Output/Input Control
//
#define GPIOF3_DOUT             0x0000094C

//
//! GPIO PF.4 Bit Output/Input Control
//
#define GPIOF4_DOUT             0x00000950

//
//! GPIO PF.5 Bit Output/Input Control
//
#define GPIOF5_DOUT             0x00000954

//
//! GPIO PF.6 Bit Output/Input Control
//
#define GPIOF6_DOUT             0x00000958

//
//! GPIO PF.7 Bit Output/Input Control
//
#define GPIOF7_DOUT             0x0000095C

//
//! GPIO PF.8 Bit Output/Input Control
//
#define GPIOF8_DOUT             0x00000960

//
//! GPIO PF.9 Bit Output/Input Control
//
#define GPIOF9_DOUT             0x00000964

//
//! GPIO PF.10 Bit Output/Input Control
//
#define GPIOF10_DOUT            0x00000968

//
//! GPIO PF.11 Bit Output/Input Control
//
#define GPIOF11_DOUT            0x0000096C

//
//! GPIO PF.12 Bit Output/Input Control
//
#define GPIOF12_DOUT            0x00000970

//
//! GPIO PF.13 Bit Output/Input Control
//
#define GPIOF13_DOUT            0x00000974

//
//! GPIO PF.14 Bit Output/Input Control
//
#define GPIOF14_DOUT            0x00000978

//
//! GPIO PF.15 Bit Output/Input Control
//
#define GPIOF15_DOUT            0x0000097C

//
//! GPIO PG.0 Bit Output/Input Control
//
#define GPIOG0_DOUT             0x00000980

//
//! GPIO PG.1 Bit Output/Input Control
//
#define GPIOG1_DOUT             0x00000984

//
//! GPIO PG.2 Bit Output/Input Control
//
#define GPIOG2_DOUT             0x00000988

//
//! GPIO PG.3 Bit Output/Input Control
//
#define GPIOG3_DOUT             0x0000098C

//
//! GPIO PG.4 Bit Output/Input Control
//
#define GPIOG4_DOUT             0x00000990

//
//! GPIO PG.5 Bit Output/Input Control
//
#define GPIOG5_DOUT             0x00000994

//
//! GPIO PG.6 Bit Output/Input Control
//
#define GPIOG6_DOUT             0x00000998

//
//! GPIO PG.7 Bit Output/Input Control
//
#define GPIOG7_DOUT             0x0000099C

//
//! GPIO PG.8 Bit Output/Input Control
//
#define GPIOG8_DOUT             0x000009A0

//
//! GPIO PG.9 Bit Output/Input Control
//
#define GPIOG9_DOUT             0x000009A4

//
//! GPIO PG.10 Bit Output/Input Control
//
#define GPIOG10_DOUT            0x000009A8

//
//! GPIO PG.11 Bit Output/Input Control
//
#define GPIOG11_DOUT            0x000009AC

//
//! GPIO PG.12 Bit Output/Input Control
//
#define GPIOG12_DOUT            0x000009B0

//
//! GPIO PG.13 Bit Output/Input Control
//
#define GPIOG13_DOUT            0x000009B4

//
//! GPIO PG.14 Bit Output/Input Control
//
#define GPIOG14_DOUT            0x000009B8

//
//! GPIO PG.15 Bit Output/Input Control
//
#define GPIOG15_DOUT            0x000009BC


//
//! GPIO PH.0 Bit Output/Input Control
//
#define GPIOH0_DOUT             0x000009C0

//
//! GPIO PH.1 Bit Output/Input Control
//
#define GPIOH1_DOUT             0x000009C4

//
//! GPIO PH.2 Bit Output/Input Control
//
#define GPIOH2_DOUT             0x000009C8

//
//! GPIO PH.3 Bit Output/Input Control
//
#define GPIOH3_DOUT             0x000009CC

//
//! GPIO PH.4 Bit Output/Input Control
//
#define GPIOH4_DOUT             0x000009D0

//
//! GPIO PH.5 Bit Output/Input Control
//
#define GPIOH5_DOUT             0x000009D4

//
//! GPIO PH.6 Bit Output/Input Control
//
#define GPIOH6_DOUT             0x000009D8

//
//! GPIO PH.7 Bit Output/Input Control
//
#define GPIOH7_DOUT             0x000009DC

//
//! GPIO PH.8 Bit Output/Input Control
//
#define GPIOH8_DOUT             0x000009E0

//
//! GPIO PH.9 Bit Output/Input Control
//
#define GPIOH9_DOUT             0x000009E4

//
//! GPIO PH.10 Bit Output/Input Control
//
#define GPIOH10_DOUT            0x000009E8

//
//! GPIO PH.11 Bit Output/Input Control
//
#define GPIOH11_DOUT            0x000009EC

//
//! GPIO PH.12 Bit Output/Input Control
//
#define GPIOH12_DOUT            0x000009F0

//
//! GPIO PH.13 Bit Output/Input Control
//
#define GPIOH13_DOUT            0x000009F4

//
//! GPIO PH.14 Bit Output/Input Control
//
#define GPIOH14_DOUT            0x000009F8

//
//! GPIO PH.15 Bit Output/Input Control
//
#define GPIOH15_DOUT            0x000009FC

//
//! GPIO PI.0 Bit Output/Input Control
//
#define GPIOI0_DOUT             0x00000A00

//
//! GPIO PI.1 Bit Output/Input Control
//
#define GPIOI1_DOUT             0x00000A04

//
//! GPIO PI.2 Bit Output/Input Control
//
#define GPIOI2_DOUT             0x00000A08

//
//! GPIO PI.3 Bit Output/Input Control
//
#define GPIOI3_DOUT             0x00000A0C

//
//! GPIO PI.4 Bit Output/Input Control
//
#define GPIOI4_DOUT             0x00000A10

//
//! GPIO PI.5 Bit Output/Input Control
//
#define GPIOI5_DOUT             0x00000A14

//
//! GPIO PI.6 Bit Output/Input Control
//
#define GPIOI6_DOUT             0x00000A18

//
//! GPIO PI.7 Bit Output/Input Control
//
#define GPIOI7_DOUT             0x00000A1C

//
//! GPIO PI.8 Bit Output/Input Control
//
#define GPIOI8_DOUT             0x00000A20

//
//! GPIO PI.9 Bit Output/Input Control
//
#define GPIOI9_DOUT             0x00000A24

//
//! GPIO PI.10 Bit Output/Input Control
//
#define GPIOI10_DOUT            0x00000A28

//
//! GPIO PI.11 Bit Output/Input Control
//
#define GPIOI11_DOUT            0x00000A2C

//
//! GPIO PI.12 Bit Output/Input Control
//
#define GPIOI12_DOUT            0x00000A30

//
//! GPIO PI.13 Bit Output/Input Control
//
#define GPIOI13_DOUT            0x00000A34

//
//! GPIO PI.14 Bit Output/Input Control
//
#define GPIOI14_DOUT            0x00000A38

//
//! GPIO PI.15 Bit Output/Input Control
//
#define GPIOI15_DOUT            0x00000A3C


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_PMD GPIO Mode Control(GPIO_PMD)
//! \brief Defines for the bit fields in the GPIO_PMD register.
//! @{
//
//*****************************************************************************
//
//! Pin[0] Mode Control
//
#define GPIO_PMD_PMD0_M         0x00000003  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD0_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD0_OUT       0x00000001

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD0_OD        0x00000002

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD0_QB        0x00000003

//
//! Pin[1] Mode Control
//
#define GPIO_PMD_PMD1_M         0x0000000C  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD1_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD1_OUT       0x00000004

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD1_OD        0x00000008

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD1_QB        0x0000000C

//
//! Pin[2] Mode Control
//
#define GPIO_PMD_PMD2_M         0x00000030  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD2_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD2_OUT       0x00000010

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD2_OD        0x00000020

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD2_QB        0x00000030

//
//! Pin[3] Mode Control
//
#define GPIO_PMD_PMD3_M         0x000000C0  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD3_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD3_OUT       0x00000040

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD3_OD        0x00000080

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD3_QB        0x000000C0

//
//! Pin[4] Mode Control
//
#define GPIO_PMD_PMD4_M         0x00000300  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD4_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD4_OUT       0x00000100

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD4_OD        0x00000200

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD4_QB        0x00000300

//
//! Pin[5] Mode Control
//
#define GPIO_PMD_PMD5_M         0x00000C00  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD5_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD5_OUT       0x00000400

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD5_OD        0x00000800

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD5_QB        0x00000C00

//
//! Pin[6] Mode Control
//
#define GPIO_PMD_PMD6_M         0x00003000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD6_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD6_OUT       0x00001000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD6_OD        0x00002000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD6_QB        0x00003000

//
//! Pin[7] Mode Control
//
#define GPIO_PMD_PMD7_M         0x0000C000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD7_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD7_OUT       0x00004000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD7_OD        0x00008000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD7_QB        0x0000C000

//
//! Pin[8] Mode Control
//
#define GPIO_PMD_PMD8_M         0x00030000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD8_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD8_OUT       0x00010000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD8_OD        0x00020000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD8_QB        0x00030000

//
//! Pin[9] Mode Control
//
#define GPIO_PMD_PMD9_M         0x000C0000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD9_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD9_OUT       0x00040000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD9_OD        0x00080000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD9_QB        0x000C0000

//
//! Pin[10] Mode Control
//
#define GPIO_PMD_PMD10_M        0x00300000 

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD10_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD10_OUT      0x00100000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD10_OD       0x00200000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD10_QB       0x00300000

//
//! Pin[11] Mode Control
//
#define GPIO_PMD_PMD11_M        0x00C00000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD11_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD11_OUT      0x00400000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD11_OD       0x00800000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD11_QB       0x00C00000

//
//! Pin[12] Mode Control
//
#define GPIO_PMD_PMD12_M        0x03000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD12_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD12_OUT      0x01000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD12_OD       0x02000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD12_QB       0x03000000

//
//! Pin[13] Mode Control
//
#define GPIO_PMD_PMD13_M        0x0C000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD13_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD13_OUT      0x04000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD13_OD       0x08000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD13_QB       0x0C000000

//
//! Pin[14] Mode Control
//
#define GPIO_PMD_PMD14_M        0x30000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD14_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD14_OUT      0x10000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD14_OD       0x20000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD14_QB       0x30000000

//
//! Pin[15] Mode Control
//
#define GPIO_PMD_PMD15_M        0xC0000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD15_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD15_OUT      0x40000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD15_OD       0x80000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD15_QB       0xC0000000


#define GPIO_PMD_PMD0_S         0
#define GPIO_PMD_PMD1_S         2
#define GPIO_PMD_PMD2_S         4
#define GPIO_PMD_PMD3_S         6
#define GPIO_PMD_PMD4_S         8
#define GPIO_PMD_PMD5_S         10
#define GPIO_PMD_PMD6_S         12
#define GPIO_PMD_PMD7_S         14
#define GPIO_PMD_PMD8_S         16
#define GPIO_PMD_PMD9_S         18
#define GPIO_PMD_PMD10_S        20
#define GPIO_PMD_PMD11_S        22
#define GPIO_PMD_PMD12_S        24
#define GPIO_PMD_PMD13_S        26
#define GPIO_PMD_PMD14_S        28
#define GPIO_PMD_PMD15_S        30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_OFFD GPIO OFF Digital Enable Register(GPIO_OFFD)
//! \brief Defines for the bit fields in the GPIO_OFFD register.
//! @{
//
//*****************************************************************************

//
//! Pin[n] OFF digital input path Enable mask
//
#define GPIO_OFFD_OFFD_M        0xFFFF0000  

//
//! Pin[n] OFF digital input path Enable shift
//
#define GPIO_OFFD_OFFD_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_DOUT GPIO Data Output Value Register(GPIO_DOUT)
//! \brief Defines for the bit fields in the GPIO_DOUT register.
//! @{
//
//*****************************************************************************

//
//! Pin[n] Output Value mask
//
#define GPIO_DOUT_DOUT_M        0x0000FFFF  

//
//! Pin[n] Output Value shift
//
#define GPIO_DOUT_DOUT_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_DMASK GPIO Data Output Write Mask Register(GPIO_DMASK)
//! \brief Defines for the bit fields in the GPIO_DMASK register.
//! @{
//
//*****************************************************************************

//
//! Data Output Write Mask
//
#define GPIO_DMASK_DMASK_M      0x0000FFFF  

//
//! Data Output Write shift
//
#define GPIO_DMASK_DMASK_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_PIN GPIO Pin Value Register(GPIO_PIN)
//! \brief Defines for the bit fields in the GPIO_PIN register.
//! @{
//
//*****************************************************************************

//
//! Port in Values mask
//
#define GPIO_PIN_PIN_M          0x0000FFFF 

//
//! Port in Values shift
//
#define GPIO_PIN_PIN_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_DBEN GPIO De-bounce Enable Register(De-bounce Enable)
//! \brief Defines for the bit fields in the GPIO_DBEN register.
//! @{
//
//*****************************************************************************

//
//! Input Signal De-bounce Enable mask
//
#define GPIO_DBEN_DBEN_M        0x0000FFFF  // Input Signal De-bounce Enable

//
//! Input Signal De-bounce Enable shift
//
#define GPIO_DBEN_DBEN_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_IMD GPIO Interrupt Mode Control(GPIO_IMD)
//! \brief Defines for the bit fields in the GPIO_IMD register.
//! @{
//
//*****************************************************************************

//
//! Port [A/B/C/D/E] Edge or Level Detection Interrupt Control mask
//
#define GPIO_IMD_IMD_M          0x0000FFFF  

//
//! Port [A/B/C/D/E] Edge or Level Detection Interrupt Control shift
//
#define GPIO_IMD_IMD_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_IEN GPIO Interrupt Enable Register(GPIO_IEN)
//! \brief Defines for the bit fields in the GPIO_IEN register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask
//
#define GPIO_IEN_IR_EN_M        0xFFFF0000  

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask shift
//                                            
#define GPIO_IEN_IR_EN_S        16

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask
//
#define GPIO_IEN_IF_EN_M        0x0000FFFF  

//
//! Interrupt Enable by Input Rising Edge or Input Level High shift
//                                          
#define GPIO_IEN_IF_EN_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_ISRC GPIO Interrupt Source Flag Register(GPIO_ISRC)
//! \brief Defines for the bit fields in the GPIO_ISRC register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Trigger Source Indicator mask
//
#define GPIO_ISRC_ISRC_M        0x0000FFFF  

//
//! Interrupt Trigger Source Indicator shift
//
#define GPIO_ISRC_ISRC_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_SMTEN GPIO Schmitt Trigger Enable(GPIO_SMTEN)
//! \brief Defines for the bit fields in the GPIO_SMTEN register.
//! @{
//
//*****************************************************************************

//
//! Port N Bit M Input Schmitt Trigger Enable Bit mask
//
#define GPIO_SMTEN_SMTEN_M      0x0000FFFF

//
//! Port N Bit M Input Schmitt Trigger Enable Bit shift
//
#define GPIO_SMTEN_SMTEN_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_GPIO_SLEWCTL GPIO High Slew Rate Control(GPIO_SLEWCTL)
//! \brief Defines for the bit fields in the GPIO_SLEWCTL register.
//! @{
//
//*****************************************************************************

//
//! Port N Bit M High Slew Rate Control mask
//
#define GPIO_SLEWCTL_HSREN_M    0x0000FFFF

//
//! Port N Bit M High Slew Rate Control shift
//
#define GPIO_SLEWCTL_HSREN_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Register_DBNCECON GPIO De-bounce Cycle Control Register(GPIO_DBNCECON)
//! \brief Defines for the bit fields in the GPIO_DBNCECON register.
//! @{
//
//*****************************************************************************

//
//! Interrupt clock On mode
//
#define GPIO_DBNCECON_ICLK_ON   0x00000020  

//
//! De-bounce counter clock source select
//
#define GPIO_DBNCECON_DBCLKSRC  0x00000010  

//
//! De-bounce sampling cycle selection mask
//
#define GPIO_DBNCECON_DBCLKSEL_M                                               \
                                0x0000000F  
                                
//
//! De-bounce sampling cycle selection shift
//
#define GPIO_DBNCECON_DBCLKSEL_S                                               \
                                0
                                
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
#endif // __XHW_GPIO_H__
