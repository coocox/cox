//*****************************************************************************
//
//! \file SensorShield.h
//! \brief Prototypes for Character LCD Shield Driver.
//! \version 2.1.1.0
//! \date 10/18/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX
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

#ifndef __SENSORSHIELD_H__
#define __SENSORSHIELD_H__


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
//! \addtogroup CoX_Shield_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor_Shield
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor_Shield_Configs  Sensor Shield Driver config
//! \brief GPIOs of Sensor Shield config.
//! @{
//
//*****************************************************************************
#define SENSOR_SHIELD_OUT_USED  1

#define SENSOR_SHIELD_IN0_USED  0
#define SENSOR_SHIELD_IN1_USED  SENSOR_SHIELD_IN_ANALOG
#define SENSOR_SHIELD_IN2_USED  SENSOR_SHIELD_IN_ANALOG
#define SENSOR_SHIELD_IN3_USED  SENSOR_SHIELD_IN_ANALOG
#define SENSOR_SHIELD_IN4_USED  0
#define SENSOR_SHIELD_IN5_USED  0

#define SENSOR_SHIELD_I2C_USED  0

#define SENSOR_SHIELD_UART_USED 1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor_Shield_Input Mode  Sensor Shield Input Mode
//! \brief GPIOs of Sensor Shield Input Mode.
//! @{
//
//*****************************************************************************
#define SENSOR_SHIELD_IN_ANALOG 2

#define SENSOR_SHIELD_IN_DIGITAL                                              \
                                1


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor_Shield_Exported_IOs  Sensor Shield Driver GPIOs
//! \brief GPIOs of Sensor Shield Driver.
//! @{
//
//*****************************************************************************
#define SENSOR_SHIELD_O0        sD11
#define SENSOR_SHIELD_O1        sD10
#define SENSOR_SHIELD_O2        sD9
#define SENSOR_SHIELD_O3        sD6
#define SENSOR_SHIELD_O4        sD5
#define SENSOR_SHIELD_O5        sD3

#define SENSOR_SHIELD_I0        sA5
#define SENSOR_SHIELD_I1        sA4
#define SENSOR_SHIELD_I2        sA3
#define SENSOR_SHIELD_I3        sA2
#define SENSOR_SHIELD_I4        sA1
#define SENSOR_SHIELD_I5        sA0


#define SENSOR_SHIELD_AI0       0
#define SENSOR_SHIELD_AI1       1
#define SENSOR_SHIELD_AI2       2
#define SENSOR_SHIELD_AI3       3
#define SENSOR_SHIELD_AI4       4
#define SENSOR_SHIELD_AI5       5

#define SENSOR_SHIELD_TWI_SDA   sA4
#define SENSOR_SHIELD_TWI_SCK   sA5

#define SENSOR_SHIELD_TX        sD1
#define SENSOR_SHIELD_RX        sD0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor_Shield_Exported_APIs  Sensor Shield Driver APIs
//! \brief API Refrence of Sensor Shield Driver.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Write the values to the specified pin of Sensor Shield.
//!
//! \param ulChannel Specified port and pin.
//! \param ucVal is the value to write to the pin(s), 0 or 1.
//!
//! The parameter of ulChannel can be:
//! - SENSOR_SHIELD_O0
//! - SENSOR_SHIELD_O1
//! - SENSOR_SHIELD_O2
//! - SENSOR_SHIELD_O3
//! - SENSOR_SHIELD_O4
//! - SENSOR_SHIELD_O5
//!
//! Write the values to the specified pin of Sensor Shield.
//!
//! \return None
//
//*****************************************************************************
#define SensorShieldOutWrite(ulChannel, ucVal)                                \
		xGPIOSPinWrite(ulChannel, ucVal)

//*****************************************************************************
//
//! \brief Write the values to the specified pin of Sensor Shield.
//!
//! \param ulChannel Specified port and pin.
//! \param ucVal is the value to write to the pin(s), 0 or 1.
//!
//! The parameter of ulChannel can be:
//! - SENSOR_SHIELD_AI0
//! - SENSOR_SHIELD_AI1
//! - SENSOR_SHIELD_AI2
//! - SENSOR_SHIELD_AI3
//! - SENSOR_SHIELD_AI4
//! - SENSOR_SHIELD_AI5
//!
//! Write the values to the specified pin of Sensor Shield.
//!
//! \return None
//
//*****************************************************************************
#define SensorShieldAInGet(ulChannel, pulVal)                                  \
		do                                                                     \
		{                                                                      \
			xASSERT(ulChannel == SENSOR_SHIELD_AI0 ||                          \
					ulChannel == SENSOR_SHIELD_AI1 ||                          \
					ulChannel == SENSOR_SHIELD_AI2 ||                          \
					ulChannel == SENSOR_SHIELD_AI3 ||                          \
					ulChannel == SENSOR_SHIELD_AI4 ||                          \
					ulChannel == SENSOR_SHIELD_AI5);                           \
		   ADCValueGet(ulChannel,  pulVal);                                    \
		}                                                                      \
		while(0)

//*****************************************************************************
//
//! \brief Write the values to the specified pin of Sensor Shield.
//!
//! \param ulChannel Specified port and pin.
//! \param ucVal is the value to write to the pin(s), 0 or 1.
//!
//! The parameter of ulChannel can be:
//! - SENSOR_SHIELD_I0
//! - SENSOR_SHIELD_I1
//! - SENSOR_SHIELD_I2
//! - SENSOR_SHIELD_I3
//! - SENSOR_SHIELD_I4
//! - SENSOR_SHIELD_I5
//!
//! Write the values to the specified pin of Sensor Shield.
//!
//! \return None
//
//*****************************************************************************
#define SensorShieldInGet(ulChannel, pulVal)                                   \
		do                                                                     \
		{                                                                      \
		    xASSERT(ulChannel == SENSOR_SHIELD_I0 ||                           \
					ulChannel == SENSOR_SHIELD_I1 ||                           \
					ulChannel == SENSOR_SHIELD_I2 ||                           \
					ulChannel == SENSOR_SHIELD_I3 ||                           \
					ulChannel == SENSOR_SHIELD_I4 ||                           \
					ulChannel == SENSOR_SHIELD_I5);                            \
		   *pulVal = xGPIOSPinRead(ulChannel);                                 \
		}                                                                      \
		while(0)

extern void SensorShieldInit(void);
extern void SensorShieldIOInit(void);

extern unsigned long SensorShieldUARTBufferGet(unsigned long ulBase,
		                                       unsigned char *pucBuf,
		                                       unsigned long  ulLen);
extern void SensorShieldUARTBufferPut(unsigned long ulBase,
		                              unsigned char *pucStr,
		                              unsigned long ulLen);


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
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__SENSORSHIELD_H__
