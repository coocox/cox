//*****************************************************************************
//
//! \file      xhw_gpio.h
//! \brief     Macros used when accessing the GPIO control hardware.
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

#ifndef __XHW_GPIO_H__
#define __XHW_GPIO_H__

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
//! \addtogroup GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_GPIO_Register GPIO Register Hardware Layer.
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
//! \addtogroup LPC17xx_GPIO_Register_Offsets GPIO Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>GPIOx_BASE + offset</b>, (x=A/B/C...).
//! @{
//
//*****************************************************************************

//! Pin Function Select register 0
#define PINSEL0                        ((unsigned long)0x00000000)

//! Pin Function Select register 1
#define PINSEL1                        ((unsigned long)0x00000004)

//! Pin Function Select register 2
#define PINSEL2                        ((unsigned long)0x00000008)

//! Pin Function Select register 3
#define PINSEL3                        ((unsigned long)0x0000000C)

//! Pin Function Select register 4
#define PINSEL4                        ((unsigned long)0x00000010)

//! Pin Function Select register 5
#define PINSEL5                        ((unsigned long)0x00000014)

//! Pin Function Select register 6
#define PINSEL6                        ((unsigned long)0x00000018)

//! Pin Function Select register 7
#define PINSEL7                        ((unsigned long)0x0000001C)

//! Pin Function Select register 8
#define PINSEL8                        ((unsigned long)0x00000020)

//! Pin Function Select register 9
#define PINSEL9                        ((unsigned long)0x00000024)

//! Pin Function Select register 10
#define PINSEL10                       ((unsigned long)0x00000028)

//! Pin Mode register 0
#define PINMODE0                       ((unsigned long)0x00000040)

//! Pin Mode register 1
#define PINMODE1                       ((unsigned long)0x00000044)

//! Pin Mode register 2
#define PINMODE2                       ((unsigned long)0x00000048)

//! Pin Mode register 3
#define PINMODE3                       ((unsigned long)0x0000004C)

//! Pin Mode register 4
#define PINMODE4                       ((unsigned long)0x00000050)

//! Pin Mode register 5
#define PINMODE5                       ((unsigned long)0x00000054)

//! Pin Mode register 6
#define PINMODE6                       ((unsigned long)0x00000058)

//! Pin Mode register 7
#define PINMODE7                       ((unsigned long)0x0000005C)

//! Pin Mode register 9
#define PINMODE8                       ((unsigned long)0x00000060)

//! Pin Mode register 9
#define PINMODE9                       ((unsigned long)0x00000064)


//! Pin Open-Drain register 0
#define PINMODE_OD0                    ((unsigned long)0x00000068)

//! Pin Open-Drain register 1
#define PINMODE_OD1                    ((unsigned long)0x0000006C)

//! Pin Open-Drain register 2
#define PINMODE_OD2                    ((unsigned long)0x00000070)

//! Pin Open-Drain register 3
#define PINMODE_OD3                    ((unsigned long)0x00000074)

//! Pin Open-Drain register 4
#define PINMODE_OD4                    ((unsigned long)0x00000078)

//! I2C Pad configure register
#define I2CPADCFG                      ((unsigned long)0x0000007C)

//! \brief GPIO direction register offset.
//! \note  You can use those offset register with GPIO_PORTx_BASE
//!        (x = A/B/C/D/E) to access direction register.
#define FIODIR                         ((unsigned long)0x00000000)

//! Fast IO Direction register 0.
#define FIO0DIR                        ((unsigned long)0x00000000)

//! Fast IO Direction register 1.
#define FIO1DIR                        ((unsigned long)0x00000000)

//! Fast IO Direction register 2.
#define FIO2DIR                        ((unsigned long)0x00000000)

//! Fast IO Direction register 3.
#define FIO3DIR                        ((unsigned long)0x00000000)

//! Fast IO Direction register 4.
#define FIO4DIR                        ((unsigned long)0x00000000)

//! \brief GPIO mask register offset.
//! \note  You can use those offset register with GPIO_PORTx_BASE
//!        (x = A/B/C/D/E) to access direction register.
#define FIOMASK                        ((unsigned long)0x00000010)

//! GPIO mask register offset 0.
#define FIO0MASK                       ((unsigned long)0x00000010)

//! GPIO mask register offset 1.
#define FIO1MASK                       ((unsigned long)0x00000010)

//! GPIO mask register offset 2.
#define FIO2MASK                       ((unsigned long)0x00000010)

//! GPIO mask register offset 3.
#define FIO3MASK                       ((unsigned long)0x00000010)

//! GPIO mask register offset 4.
#define FIO4MASK                       ((unsigned long)0x00000010)

//! \brief GPIO Pin value register offset.
//! \note  You can use those offset register with GPIO_PORTx_BASE
//!        (x = A/B/C/D/E) to access direction register.
#define FIOPIN                         ((unsigned long)0x00000014)

//! Fast IO Value register 0.
#define FIO0PIN                        ((unsigned long)0x00000014)

//! Fast IO Value register 1.
#define FIO1PIN                        ((unsigned long)0x00000014)

//! Fast IO Value register 2.
#define FIO2PIN                        ((unsigned long)0x00000014)

//! Fast IO Value register 3.
#define FIO3PIN                        ((unsigned long)0x00000014)

//! Fast IO Value register 4.
#define FIO4PIN                        ((unsigned long)0x00000014)

//! \brief GPIO Pin Set register offset.
//! \note  You can use those offset register with GPIO_PORTx_BASE
//!        (x = A/B/C/D/E) to access direction register.
#define FIOSET                         ((unsigned long)0x00000018)

//! Fast IO Set register 0.
#define FIO0SET                        ((unsigned long)0x00000018)

//! Fast IO Set register 1.
#define FIO1SET                        ((unsigned long)0x00000018)

//! Fast IO Set register 2.
#define FIO2SET                        ((unsigned long)0x00000018)

//! Fast IO Set register 3.
#define FIO3SET                        ((unsigned long)0x00000018)

//! Fast IO Set register 4.
#define FIO4SET                        ((unsigned long)0x00000018)

//! \brief GPIO Pin Clear register offset.
//! \note  You can use those offset register with GPIO_PORTx_BASE
//!        (x = A/B/C/D/E) to access direction register.
#define FIOCLR                         ((unsigned long)0x0000001C)

//! Fast IO Clear register 0.
#define FIO0CLR                        ((unsigned long)0x0000001C)

//! Fast IO Clear register 1.
#define FIO1CLR                        ((unsigned long)0x0000001C)

//! Fast IO Clear register 2.
#define FIO2CLR                        ((unsigned long)0x0000001C)

//! Fast IO Clear register 3.
#define FIO3CLR                        ((unsigned long)0x0000001C)

//! Fast IO Clear register 4.
#define FIO4CLR                        ((unsigned long)0x0000001C)

//! \brief GPIO Port 0 Interrupt Rising Control register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO0IntEnR                      ((unsigned long)0x00000090)

//! \brief GPIO Port 2 Interrupt Rising Control register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO2IntEnR                      ((unsigned long)0x000000B0)

//! \brief GPIO Port 0 Interrupt Falling Control register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO0IntEnF                      ((unsigned long)0x00000094)

//! \brief GPIO Port 2 Interrupt Falling Control register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO2IntEnF                      ((unsigned long)0x000000B4)

//! \brief GPIO Port 0 Interrupt Rising status register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO0IntStatR                    ((unsigned long)0x00000084)

//! \brief GPIO Port 2 Interrupt Rising status register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO2IntStatR                    ((unsigned long)0x000000A4)

//! \brief GPIO Port 0 Interrupt Falling status register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO0IntStatF                    ((unsigned long)0x00000088)

//! \brief GPIO Port 2 Interrupt Falling status register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO2IntStatF                    ((unsigned long)0x000000A8)

//! \brief GPIO Port 0 Interrupt Clear Control register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO0IntClr                      ((unsigned long)0x0000008C)

//! \brief GPIO Port 2 Interrupt Clear Control register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IO2IntClr                      ((unsigned long)0x000000AC)

//! \brief GPIO Interrupt status register.
//! \note  You can use those offset register with GPIO_INT_BASE
#define IOIntStatus                    ((unsigned long)0x00000080)

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

