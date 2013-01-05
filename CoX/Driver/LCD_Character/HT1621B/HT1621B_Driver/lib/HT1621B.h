//*****************************************************************************
//
//! \file HT1621B.h
//! \brief header file of Driver for HT1621B
//! \version 1.0.0.0
//! \date 12/20/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox All rights reserved.
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
#ifndef  __HT1621B_H__
#define  __HT1621B_H__

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "hw_HT1621B.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup LCD
//! @{
//! \addtogroup LCD_Character 
//! @{
//! \addtogroup HT1621B_LCD_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT1621B_IO_Config  HT1621B IO Configuration
//! configure the DATA, WR, CS, RD, BL line of HT1621B, user can modify this
//! as needed.
//! @{
//
//*****************************************************************************
#define LCDPORT      xGPIO_PORTA_BASE
#define DATA         xGPIO_PIN_9
#define CS    		 xGPIO_PIN_10
#define RD           xGPIO_PIN_10
#define WR           xGPIO_PIN_11
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT1621B_Commons HT1621B Commons
//! HT1621B Common Operation
//! @{
//
//*****************************************************************************

void ht1621b_delay(int iDelayTime);

#define CS_LOW     {xGPIOPinWrite(LCDPORT, CS, 0);ht1621b_delay(2);}
#define CS_HIGH    {xGPIOPinWrite(LCDPORT, CS, 1);ht1621b_delay(2);}
#define WR_LOW     {xGPIOPinWrite(LCDPORT, WR, 0);ht1621b_delay(2);}
#define WR_HIGH    {xGPIOPinWrite(LCDPORT, WR, 1);ht1621b_delay(2);}
#define DATA_LOW   {xGPIOPinWrite(LCDPORT, DATA, 0);ht1621b_delay(2);}
#define DATA_HIGH  {xGPIOPinWrite(LCDPORT, DATA, 1);ht1621b_delay(2);}

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT1621B_APIs  HT1621B APIs
//! HT1621B APIs
//! @{
//
//*****************************************************************************
extern unsigned int lcd_buffer[8];
extern void send_lcd_command(unsigned char command);
extern void send_lcd_data(unsigned short int address,unsigned short int data);
extern void flood_lcd_data(void);
extern void lcd_init(void);
extern void lcd_char(unsigned short int name,unsigned short int display);
extern void lcd_clr();
extern void lcd_number(unsigned short int number,unsigned short int position,unsigned short int );
extern int DisplayEFSNum( int iEFSIndex );
extern int Display5Power(int IntPower, int FracPower );
extern int DisplaydORs( char cdORs );
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
