//*****************************************************************************
//
//! \file TCN75.h
//! \brief header file of Driver for TCN75
//! \version 1.0
//! \date 9/5/2011
//! \author CooCox
//! \copy
//
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

#ifndef __TCN75_H__
#define __TCN75_H__

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
//! \addtogroup COX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup COX_TempSensor_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TCN75
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TCN75_Address
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The address of  TCN75-5.0MOA.
//
//*****************************************************************************

#define  TCN75Address   0x48;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TCN75_I2C_Set
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

#define  XSYSCTL_PERIPH_I2C      xSYSCTL_PERIPH_I2C0
#define  I2C_BASE      I2C0_BASE
#define  I2CSCL_PIN    PA9
#define  I2CDATA_PIN   PA8
#define  EventPORT     GPIO_PORTB_BASE
#define  EventPIN	   0x1000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup TCN75_Shutdown_Mode
//! Values that can be passed to TCN75ModeSet().
//! @{
//
//*****************************************************************************

//
//! Select TCN75 shutdown mode
//
#define TCN75_SHUTDOWM_ON  0x01

//
//! Don't select TCN75 shutdown mode
//
#define TCN75_SHUTDOWN_OFF 0x00

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TCN75_Alert_Pol  TCN75 Alert Polarity
//! Values that can be passed to TCN75IntConfig().
//! @{
//
//*****************************************************************************

//
//! Set Alert Polarity as Low(power-up default)
//
#define  ALERTPOL_LOW      0

//
//! Set Alert Polarity as High
//
#define  ALERTPOL_HIGH      1


//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup TCN75_Mode_Set
//! Values that can be passed to TCN75IntConfig().
//! @{
//
//*****************************************************************************

//
//! Select TCN75  compare mode
//
#define TCN75_MODE_CMP  0x00

//
//! Select TCN75 interrupt mode
// 
#define TCN75_MODE_INT  0x02 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  

//*****************************************************************************
//
//! \addtogroup TCN75_Polarity_Set
//! Set TCN75 polarity active.
//! @{
//
//*****************************************************************************
//
//! Select low polarity active
//
#define TCN75_POLARITY_LOW   0x00

//
//!	Select high polarity active
//
#define TCN75_POLARITY_HIGH  0x04 

//*****************************************************************************
//
//! \addtogroup TCN75_Queue_Set
//! @{
//
//*****************************************************************************
//
//! Set the Queue num
//
#define TCN75_FAULTQUE_1  0x00
#define TCN75_FAULTQUE_2  0x08
#define TCN75_FAULTQUE_4  0x10
#define TCN75_FAULTQUE_6  0x18  

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
//! \addtogroup TCN75_Exported_APIs
//! @{
//
//*****************************************************************************

extern void TCN75Init(unsigned long ulRate);
extern void TCN75DeInit(void);
extern long TCN75RegRead(unsigned char ucReg);
extern void TCN75RegWrite(unsigned char ucReg, void* vpValue);
extern void TCN75ModeSet(unsigned char ucMode);
extern unsigned char TCN75ModeGet(void);
extern void TCN75FaultQueSet(unsigned char ucFq);
extern unsigned char TCN75FaultQueGet(void);
extern void TCN75IntConfig(xtEventCallback xtIntCallback, 
                 unsigned long ulTrigMode, unsigned long ulEventMode);
extern long TCN75TempGet(unsigned char ucReg);
extern float TCN75TempReadFDC(unsigned char ucReg);
       
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

#ifdef __cplusplus
}
#endif

#endif 
