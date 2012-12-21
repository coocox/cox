//*****************************************************************************
//
//! \file hw_STMPE811.h
//! \brief header file of Driver for M24Cxx
//! \version V2.1.1.0
//! \date 7/5/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
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



#ifndef __HW_STMPE811_H__
#define __HW_STMPE811_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib 
//! @{
//! \addtogroup Sensor
//! @{
//! \addtogroup I2C_TouchSensor
//! @{
//! \addtogroup STMPE811
//! @{
//! \addtogroup STMPE811_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register STMPE811 Register
//! \brief Here are the detailed info of STMPE811 registers. 
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_Offsets STMPE811 address(Map)
//! \brief Here is the STMPE811 register address.
//! @{
//
//*****************************************************************************

//
//! STMPE811 Device identification.
// 
#define STMPE811_CHIP_ID        0x00

//
//! STMPE811 Revision.
// 
#define STMPE811_ID_VER         0x02

//
//! STMPE811 reset control
// 
#define STMPE811_SYS_CTRL1      0x03

//
//! STMPE811 clock control.
// 
#define STMPE811_SYS_CTRL2      0x04

//
//! STMPE811 SPI interface configuration.
// 
#define STMPE811_SPI_CFG        0x08

//
//! STMPE811 interrupt control register.
// 
#define STMPE811_INT_CTRL       0x09

//
//! STMPE811 interrupt enable register.
// 
#define STMPE811_INT_EN         0x0A

//
//! STMPE811 interrupt status register.
// 
#define STMPE811_INT_STA        0x0B

//
//! STMPE811 GPIO interrupt enable register.
// 
#define STMPE811_GPIO_EN        0x0C

//
//! STMPE811 GPIO interrupt status register.
// 
#define STMPE811_GPIO_INT_STA   0x0D

//
//! STMPE811 ADC interrupt enable register.
// 
#define STMPE811_ADC_INT_EN     0x0E

//
//! STMPE811 ADC interface status register.
// 
#define STMPE811_ADC_INT_STA    0x0F

//
//! STMPE811 GPIO set pin register.
// 
#define STMPE811_GPIO_SET_PIN   0x10

//
//! STMPE811 GPIO clear pin register.
// 
#define STMPE811_GPIO_CLR_PIN   0x11

//
//! STMPE811 GPIO monitor pin state register.
// 
#define STMPE811_MP_STA         0x12

//
//! STMPE811 GPIO direction register.
// 
#define STMPE811_GPIO_DIR       0x13

//
//! STMPE811 GPIO edge detect register.
// 
#define STMPE811_GPIO_ED        0x14

//
//! STMPE811 GPIO rising edge register.
// 
#define STMPE811_GPIO_RE        0x15

//
//! STMPE811 GPIO falling edge register.
// 
#define STMPE811_GPIO_FE        0x16

//
//! STMPE811 alternate function register.
// 
#define STMPE811_GPIO_AF        0x17

//
//! STMPE811 ADC control.
// 
#define STMPE811_ADC_CTRL1      0x20

//
//! STMPE811 ADC control.
// 
#define STMPE811_ADC_CTRL2      0x21

//
//! STMPE811 to initiate ADC data acquisition.
// 
#define STMPE811_ADC_CAPT       0x22

//
//! STMPE811 ADC channel 0.
// 
#define STMPE811_ADC_DATA_CHO   0x30

//
//! STMPE811 ADC channel 1.
// 
#define STMPE811_ADC_DATA_CH1   0x32

//
//! STMPE811 ADC channel 2.
// 
#define STMPE811_ADC_DATA_CH2   0x34

//
//! STMPE811 ADC channel 3.
// 
#define STMPE811_ADC_DATA_CH3   0x36

//
//! STMPE811 ADC channel 4.
// 
#define STMPE811_ADC_DATA_CH4   0x38

//
//! STMPE811 ADC channel 5.
// 
#define STMPE811_ADC_DATA_CH5   0x3A

//
//! STMPE811 ADC channel 6.
// 
#define STMPE811_ADC_DATA_CH6   0x3C

//
//! STMPE811 ADC channel 7.
// 
#define STMPE811_ADC_DATA_CH7   0x3E

//
//! STMPE811 4-wire touchscreen controller setup.
// 
#define STMPE811_TSC_CTRL       0x40

//
//! STMPE811 touchscreen controller configuration.
// 
#define STMPE811_TSC_CFG        0x41

//
//! STMPE811 window setup for top right X.
// 
#define STMPE811_WDW_TR_X       0x42

//
//! STMPE811 window setup for top right Y.
// 
#define STMPE811_WDW_TR_Y       0x44

//
//! STMPE811 window setup for bottom left X.
// 
#define STMPE811_WDW_BL_X       0x46

//
//! STMPE811 window setup for bottom left Y.
// 
#define STMPE811_WDW_BL_Y       0x48

//
//! STMPE811 FIFO level to generate interrupt.
// 
#define STMPE811_FIFO_TH        0x4A

//
//! STMPE811 current status of FIFO.
// 
#define STMPE811_FIFO_STA       0x4B

//
//! STMPE811 current filled level of FIFO.
// 
#define STMPE811_FIFO_SIZE      0x4C

//
//! STMPE811 data port for touchscreen controller data access.
// 
#define STMPE811_TSC_DATA_X     0x4D

//
//! STMPE811 data port for touchscreen controller data access.
// 
#define STMPE811_TSC_DATA_Y     0x4F

//
//! STMPE811 data port for touchscreen controller data access.
// 
#define STMPE811_TSC_DATA_Z     0x51

//
//! STMPE811 data port fir touchscreen controller data access.
// 
#define STMPE811_TSC_DATA_XYZ   0x52

//
//! STMPE811 touchscreen controller FRACTION_Z.
// 
#define STMPE811_TSC_FRACTION_Z 0x56


//
//! STMPE811 data port for touchscreen controller data access
// 
#define STMPE811_TSC_DATA       0x57

//
//! STMPE811 touchscreen controller drivel.
// 
#define STMPE811_TSC_I_DRIVE    0x58

//
//! STMPE811 touchscreen controller shield.
// 
#define STMPE811_TSC_SHIELD     0x59

//
//! STMPE811 temperature sensor setup.
// 
#define STMPE811_TEMP_CTRL      0x60

//
//! STMPE811 temperature data access port.
// 
#define STMPE811_TEMP_DATA      0x61

//
//! STMPE811 threshold for temperature controlled interrupt.
// 
#define STMPE811_TEMP_TH        0x62

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_SYS_CTRL1 System control register1
//! \brief Defines for the bit fields in the STMPE811_SYS_CTRL1 register.
//! @{
//
//*****************************************************************************
//
//! Reset the STMPE811 using the serial communication interface.
//
#define STMPE811_SYS_CTRL1_SOFTRESET                                          \
                                0x02

//
//! Force the device into hibernation mode.
//
#define STMPE811_SYS_CTRL1_HIBERNATE                                          \
                                0x01
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_SYS_CTRL2 System control register 2
//! \brief Defines for the bit fields in the STMPE811_SYS_CTRL2 register.
//! @{
//
//*****************************************************************************
//
//! Switch off the clock supply to the temperature sensor.
//
#define STMPE811_CTRL2_TS_OFF   0x08

//
//! Switch off the clock the supply to the GPIO.
//
#define STMPE811_CTRL2_GPIO_OFF 0x04

//
//! Switch off the clock supply to the touchscreen controller.
//
#define STMPE811_CTRL2_TSC_OFF  0x02

//
//! Switch off the clock supply to the ADC.
//
#define STMPE811_CTRL2_ADC_OFF  0x01
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_INT_EN interrupt enable register 
//! \brief Defines for the bit fields in the STMPE811_INT_EN register.
//! @{
//
//*****************************************************************************
//
//! Any enabled GPIO interrupts.
//
#define STMPE811_INT_EN_GPIO    0x80

//
//! Any enabled ADC interrupts
//
#define STMPE811_INT_EN_ADC     0x40

//
//! Temperature threshold triggering.
//
#define STMPE811_INT_EN_TEMP_SENS                                             \
                                0x20

//
//! FIFO is empty.
//
#define STMPE811_INT_EN_FIFOEMPTY                                             \
                                0x10

//
//! FIFO is full.
//
#define STMPE811_INT_EN_FIFOFULL                                             \
                                0x08

//
//! FIFO is overflowed.
//
#define STMPE811_INT_EN_FIFOOFLOW                                            \
                                0x04
//
//! FIFO is equal or above threshold value.
//
#define STMPE811_INT_EN_TH      0x02

//
//! Touch is detected.
//
#define STMPE811_INT_EN_TOUCHDET                                              \
                                0x01
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_ADC_CTRL1 ADC control register 1
//! \brief Defines for the bit fields in the STMPE811_ADC_CTRL1 register.
//! @{
//
//*****************************************************************************
//
//! ADC conversion time (in number of clock) mask.
//
#define STMPE811_ADC_CTRL1_SAMPLE_M                                          \
                                0x7

//
//! ADC conversion time (in number of clock) shift.
//
#define STMPE811_ADC_CTRL1_SAMPLE_S                                          \
                                4

//
//! Selects 10 or 12-bit ADC operation.
//
#define STMPE811_ADC_CTRL1_MOD  0x8

//
//! Select between internal or external reference for the ADC.
//
#define STMPE811_ADC_CTRL1_SEL  0x2
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_ADC_CTRL2 ADC control register 2
//! \brief Defines for the bit fields in the STMPE811_ADC_CTRL1 register.
//! @{
//
//*****************************************************************************

//
//! Selects the clock speed of ADC is 1.625 MHz typ
//
#define STMPE811_ADC_CTRL2_CLK1 0x0

//
//! Selects the clock speed of ADC is 3.25 MHz typ
//
#define STMPE811_ADC_CTRL2_CLK2 0x1

//
//! Selects the clock speed of ADC is 6.5 MHz typ
//
#define STMPE811_ADC_CTRL2_CLK13                                               \
                                0x2

//
//! Selects the clock speed of ADC is 6.5 MHz typ
//
#define STMPE811_ADC_CTRL2_CLK4                                                \
                                0x3
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_TSC_CFG Touchscreen controller 
//! configuration register.
//! \brief Defines for the bit fields in the STMPE811_TSC_CFG register.
//! @{
//
//*****************************************************************************
//
//! 1 sample.
//
#define STMPE811_TSC_CFG_AVE_1  0x00

//
//! 2 sample.
//
#define STMPE811_TSC_CFG_AVE_2  0x40

//
//! 4 sample.
//
#define STMPE811_TSC_CFG_AVE_4  0x80

//
//! 8 sample.
//
#define STMPE811_TSC_CFG_AVE_8  0xC0

//
//! Touch detect delay mask.
//
#define STMPE811_TSC_CFG_DELAY_M                                              \
                                0x7

//
//! Touch detect delay shift.
//
#define STMPE811_TSC_CFG_DELAY_S                                              \
                                3
//
//! Panel driver setting time mask.
//
#define STMPE811_TSC_CFG_SETTING_M                                            \
                                0x7

//
//! Panel driver setting time shift.
//
#define STMPE811_TSC_CFG_SETTING_S                                           \
                                0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_FIFO_STA FIFO status register.
//! \brief Defines for the bit fields in the STMPE811_FIFO_STA register.
//! @{
//
//*****************************************************************************
//
//! Reads 1 if FIFO is overflow.
//
#define STMPE811_FIFO_STA_OFLOW 0x80

//
//! Reads 1 if FIFO is full.
//
#define STMPE811_FIFO_STA_FULL  0x40

//
//! Reads 1 if FIFO is empty.
//
#define STMPE811_FIFO_STA_EMPTY 0x20

//
//! FIFO size is at or beyond the threshold value.
//
#define STMPE811_FIFO_STA_TRIG  0x10

//
//! Resets FIFO, all data in FIFO are cleared.
//
#define STMPE811_FIFO_STA_RESET 0x01

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_TSC_FRACTION_Z Touchscreen controll 
//! FRACTION_Z register.
//! \brief Defines for the bit fields in the STMPE811_TSC_FRACTION_Z register.
//! @{
//
//*****************************************************************************
//
//! Pressure measurement accuracy value mask.
//
#define STMPE811_FRACTION_Z_M   0x7

//
//! Pressure measurement accuracy value mask.
//
#define STMPE811_FRACTION_Z_S   0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_TSC_I_DRIVE TSC driver 1 register.
//! \brief Defines for the bit fields in the STMPE811_TSC_I_DRIVE register.
//! @{
//
//*****************************************************************************
//
//! Set maximum current on the TSC driving channel is 20 mA, 35 mA max.
//
#define STMPE811_TSC_I_DRIVE_20 0x00

//
//! Set maximum current on the TSC driving channel is 50 mA, 80 mA max.
//
#define STMPE811_TSC_I_DRIVE_50 0x01

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_TSC_CTRL TSC control register.
//! \brief Defines for the bit fields in the STMPE811_TSC_CTRL register.
//! @{
//
//*****************************************************************************
//
//! TSC status
//
#define STMPE811_TSC_CTRL_STA   0x80

//
//! Tracking index mask.
//
#define STMPE811_TSC_CTRL_TRACK_M                                             \
                                0x7

//
//! Tracking index mask.
//
#define STMPE811_TSC_CTRL_TRACK_S                                             \
                                4

//
//! TSC operating mode: X, Y, Z acquisition.
//
#define STMPE811_TSC_CTRL_XYZ   0x00

//
//! TSC operating mode: only X, Y.
//
#define STMPE811_TSC_CTRL_XY    0x02

//
//! TSC operating mode: only X.
//
#define STMPE811_TSC_CTRL_X     0x04

//
//! TSC operating mode: only Y.
//
#define STMPE811_TSC_CTRL_Y     0x06

//
//! TSC operating mode: only Z.
//
#define STMPE811_TSC_CTRL_Z     0x08

//
//! Enable TSC.
//
#define STMPE811_TSC_CTRL_EN    0x01
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_INT_STA interrupt status register. 
//! \brief Defines for the bit fields in the STMPE811_INT_STA register.
//! @{
//
//*****************************************************************************
//
//! Any enable GPIO interrupts.
//
#define STMPE811_INT_STA_GPIO   0x80

//
//! Any enable ADC interrupts.
//
#define STMPE811_INT_STA_ADC    0x40

//
//! Temperature threshold triggering.
//
#define STMPE811_INT_STA_SENS   0x20

//
//! FIFO is empty.
//
#define STMPE811_INT_STA_EMPTY  0x10

//
//! FIFO is full.
//
#define STMPE811_INT_STA_FULL   0x08

//
//! FIFO is overflowed.
//
#define STMPE811_INT_STA_OFLOW  0x04

//
//! FIFO is equal or above threshold value.
//
#define STMPE811_INT_STA_TH     0x02

//
//! Touch is detected.
//
#define STMPE811_INT_STA_DET    0x01
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811_Register_STMPE811_INT_CTRL interrupt control register.
//! \brief Defines for the bit fields in the STMPE811_INT_CTRL register.
//! @{
//
//*****************************************************************************
//
//! sets the INT pin polarity.
//
#define STMPE811_INT_POLARITY   0x04

//
//! sets the type of interrupt signal required by the host.
//
#define STMPE811_INT_TYPE       0x02

//
//! Master enable for the interrupt system.
//
#define STMPE811_INT_GLOBAL     0x01

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
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************      



#endif // __HW_M24Cxx_H__
