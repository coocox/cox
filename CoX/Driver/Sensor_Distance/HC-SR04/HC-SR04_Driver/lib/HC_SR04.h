//*****************************************************************************
//
//! \file HC_SR04.h
//! \brief Prototypes for the ultrasonic distance measure module driver.
//! \version V2.1.1.0
//! \date 1/28/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
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
//*****************************************************************************
#ifndef __HC_SR04_H__
#define __HC_SR04_H__

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
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Distance_Measure
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HC_SR04
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HC_SR04_Configuration  HC_SR04 Configuration
//! \brief Change the IO port and timer define if needed
//! @{
//
//*****************************************************************************

#define HCSR04_TRIG_PIN PD5
#define HCSR04_ECHO_PIN PB7

#define HCSR04_TIMER_BASE    xTIMER4_BASE
#define HCSR04_TIMER_CHANNEL xTIMER_CHANNEL1
#define HCSR04_TIMER_INT     xINT_TIMER4
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HC_SR04_Attribute HC_SR04 Attribute
//! \brief HC_SR04 attribute include the max reload value of the timer and unit
//! \note These macros don't need to be modified in common use.
//! @{
//
//*****************************************************************************

#define MAX_RELOAD_VAL       35000
#define UNIT_CM              0
#define UNIT_INCH            1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

extern void HCSR04Init(void);
extern unsigned long HCSR04GetDistance(unsigned char ucUnit);

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
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  //__HC_SR04_H__
