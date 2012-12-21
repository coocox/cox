//*****************************************************************************
//
//! \file STMPE811.c
//! \brief the STMPE811 Driver.
//! \version V2.1.1.0
//! \date 7/5/2012
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xi2c.h"
#include "xhw_i2c.h"
#include "xgpio.h"
#include "STMPE811.h"
#include "hw_STMPE811.h"

#define I2C_Speed               400000

unsigned long ulX, ulY, ulZ;
xtBoolean TouchDetect = xfalse;
                                       
//*****************************************************************************
//
//! \brief Initialize STMPE811 and I2C  
//!
//! \param None
//!
//! This function initialize the mcu I2C as master and specified I2C port.the 
//! master block will be set up to transfer data at 400 kbps.
//! 
//! \return None.
//
//*****************************************************************************
void STMPE811Init(void)
{
    //
    // Enable GPIO Periph clock and Alternate Fuction I/O clock.
    //  
    xSysCtlPeripheralEnable(STMPE811_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    // Enable the I2C which is connected with STMPE811
    //
    xSysCtlPeripheralEnable2(STMPE811_PIN_I2C_PORT);   
    //
    // Set STMPE811_PIN_I2C_SCK as IICx.SCK
    //
    xSPinTypeI2C(STMPE811_I2C_SCK, STMPE811_PIN_I2C_SCK);   
    //
    // Set STMPE811_PIN_I2C_SDA as I2Cx.SDA
    //
    xSPinTypeI2C(STMPE811_I2C_SDA, STMPE811_PIN_I2C_SDA);  
    //
    // I2C enable
    //
    xI2CMasterEnable(STMPE811_PIN_I2C_PORT);
    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(STMPE811_PIN_I2C_PORT, I2C_Speed);
    //
    // Set INT pin.
    //
    xGPIODirModeSet(STMPE811_INT_PORT, STMPE811_INT_GPIO, xGPIO_DIR_MODE_IN);
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(STMPE811_INT_PORT, STMPE811_INT_GPIO, STMPE811IntCallback);
    //  Enable GPIO pin interrupt.
    xGPIOPinIntEnable(STMPE811_INT_PORT, STMPE811_INT_GPIO, xGPIO_FALLING_EDGE);
    xIntEnable(INT_GPIO);
    // STNPE811 initializtion.
    STMPE811InitConfig();     
}

//*****************************************************************************
//
//! \brief Initializes the STMPE811 device.
//!
//! \param none.
//!
//! This function initialize the STMPE811 operating as touchscreen controller.
//! 
//! \return None.
//
//*****************************************************************************
void STMPE811InitConfig(void)
{
    //
    // Enable TSC,and set TSC operating mode is X, Y only.
    //
    STMPE811SetOperatingMode(STMPE811_TSC_CTRL_EN| STMPE811_TSC_CTRL_XY);
    //
    // Reset STMPE811.
    //
    STMPE811Write (STMPE811_SYS_CTRL1, 1, STMPE811_SYS_CTRL1_SOFTRESET);
    //
    // Wait minumum of 10ms.
    //
    xSysCtlDelay(180000);
    //
    // Enable TSC and ADC
    //
    STMPE811Write (STMPE811_SYS_CTRL2, 1, STMPE811_CTRL2_TS_OFF |
                   STMPE811_CTRL2_GPIO_OFF);
    //
    // Enable Touch detect, FIFO interrupt. 
    //
    STMPE811Write (STMPE811_INT_EN, 1, STMPE811_INT_EN_TOUCHDET |
                                       STMPE811_INT_EN_TH |
                                       STMPE811_INT_EN_FIFOOFLOW);
    //
    // To select sample time, bit number and ADC reference.
    //
    STMPE811Write (STMPE811_ADC_CTRL1, 1, ((0x6 & STMPE811_ADC_CTRL1_SAMPLE_M)
                                          << STMPE811_ADC_CTRL1_SAMPLE_S )|
                                          STMPE811_ADC_CTRL1_MOD);
    //
    // Wait minumum of 2ms.
    //
    xSysCtlDelay(36000);
    //
    // To select the ADC clock speed is 3.25 MHz.
    //
    STMPE811Write (STMPE811_ADC_CTRL2, 1, STMPE811_ADC_CTRL2_CLK1);
    //
    // To set Average, Touch Detect Delay and Setting Time setting.
    //
    STMPE811Write (STMPE811_TSC_CFG, 1, 
                   STMPE811_TSC_CFG_AVE_8 |
                 ((0x6 & STMPE811_TSC_CFG_DELAY_M) << STMPE811_TSC_CFG_DELAY_S)|
                 ((0x5 & STMPE811_TSC_CFG_SETTING_M) 
                  << STMPE811_TSC_CFG_SETTING_S));
    //
    // Set FIFO threshold level.
    //
    STMPE811Write (STMPE811_FIFO_TH, 1, 0x01);
    //
    // Reset FIFO.
    //
    STMPE811Write (STMPE811_FIFO_STA, 1, STMPE811_FIFO_STA_RESET);
    //
    // Write 0x00 to put the FIFO back into operation mode.
    //
    STMPE811Write (STMPE811_FIFO_STA, 1, 0x00);
    //
    // Set the data format for Z value.
    //
    STMPE811Write (STMPE811_TSC_FRACTION_Z, 1, 
                   (0x07 * STMPE811_FRACTION_Z_M) << STMPE811_FRACTION_Z_S);
    //
    // Set the driving capability of the device for touchscreen controller pins.
    //
    STMPE811Write (STMPE811_TSC_I_DRIVE, 1, STMPE811_TSC_I_DRIVE_50);
    //
    // Set tracking index, set touchscreen controller operation mode and enable 
    // the TSC.
    //
    STMPE811SetOperatingMode(STMPE811_TSC_CTRL_EN |STMPE811_TSC_CTRL_XYZ);
    //
    // Clear all the interrupt status.
    //
    STMPE811Write (STMPE811_INT_STA, 1, 0xFF);
    //
    // Set interrupt mode and enable interrupt.
    //
    STMPE811Write (STMPE811_INT_CTRL, 1, STMPE811_INT_TYPE| 
                   STMPE811_INT_GLOBAL);
}

//*****************************************************************************
//
//! \brief Write the register of the STMPE811 device.
//!
//! \param ucReg Register selected.
//! \param ucNum the number of bytes want to be write.
//! \param ulVal value to write to register.
//!
//! This function is to write a data to touchscreen controller.
//!
//! \return None.
//
//*****************************************************************************
void
STMPE811Write(unsigned char ucReg, unsigned char ucNum, unsigned long ulVal)
{

    xI2CMasterWriteS1(STMPE811_PIN_I2C_PORT, (STMPE811_ADDRESS >> 1), 
                     ucReg, 
                     xfalse);
    while(ucNum--)  
    {     
      if(ucNum == 0)
      {
        xI2CMasterWriteS2(STMPE811_PIN_I2C_PORT, 
                         (unsigned char)(ulVal & 0xFF), xtrue);
      }	
      else
      {        
    	xI2CMasterWriteS2(STMPE811_PIN_I2C_PORT, 
                         (unsigned char)(ulVal & 0xFF), xfalse);
        ulVal >>= 8;
      } 
    }
}

//*****************************************************************************
//
//! \brief read data from touchscreen controller.
//!
//! \param ucReg Register to be read.
//! \param ucNum number of bytes to read.
//! \param pucBuffer specifies the location data which will be store.
//!
//! This function is to read data from touchscreen register.
//!
//! \return None.
//
//*****************************************************************************
void
STMPE811Read(unsigned char ucReg, unsigned char ucNum, unsigned char* pucBuffer)
{
    xI2CMasterWriteS1(STMPE811_PIN_I2C_PORT, (STMPE811_ADDRESS >> 1), 
                     ucReg, 
                     xfalse);
    if(ucNum == 1)
    {
      xI2CMasterReadS1(STMPE811_PIN_I2C_PORT, (STMPE811_ADDRESS >> 1), 
                       pucBuffer, xtrue);     
    } 
    else
    {
      xI2CMasterReadS1(STMPE811_PIN_I2C_PORT, (STMPE811_ADDRESS >> 1),
                       pucBuffer, xfalse);
    } 
    ucNum--;
    while(ucNum)
    {
    	if(ucNum == 1)
    	{
          pucBuffer++;
      	  xI2CMasterReadS2(STMPE811_PIN_I2C_PORT, pucBuffer, xtrue);
    	}	
    	else
        {
          pucBuffer++;
    	  xI2CMasterReadS2(STMPE811_PIN_I2C_PORT, pucBuffer, xfalse);       
        }  
        ucNum--;        
    }
}

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long STMPE811IntCallback(void *pvCBData, unsigned long ulEvent,
                        unsigned long ulMsgParam,void *pvMsgData)
{
   unsigned char ucInt = 0;
   unsigned char ucXYZ[4];
   unsigned long ulXYZ;
   
   ucInt = STMPE811GetINTStatus();
   
   if(ucInt & 0x02)
   {
     STMPE811Read(0xD7, 4, ucXYZ);
     ulXYZ = (ucXYZ[0] << 24)|(ucXYZ[1] << 16)|(ucXYZ[2] << 8)|(ucXYZ[3] << 0);
     ulX = (ulXYZ >> 20) & 0x00000FFF;
     ulY = (ulXYZ >>  8) & 0x00000FFF;
     ulZ = (ulXYZ >>  0) & 0x0000000F;
     STMPE811INTClear(ucInt);
     TouchDetect = xtrue;
   }    
   return 0;
}
//*****************************************************************************
//
//! \brief Set tracking index, TSC operation mode or enable the TSC. 
//!
//! \param ulMode TSC mode config.
//!
//! This function is to set TSC operation mode.
//!
//! \return None.
//
//*****************************************************************************
void STMPE811SetOperatingMode(unsigned long ulMode)
{
    STMPE811Write (STMPE811_TSC_CTRL, 1, ulMode);
}

//*****************************************************************************
//
//! \brief Get interrupt status. 
//!
//! \param none.
//!
//! This function is to get STMPE811 interrupt status.
//!
//! \return interrupt status.
//
//*****************************************************************************
unsigned STMPE811GetINTStatus(void)
{   
    unsigned char ucIntStatus = 0;
    STMPE811Read(STMPE811_INT_STA, 1, &ucIntStatus);
    return ucIntStatus;
}

//*****************************************************************************
//
//! \brief clear interrupt status. 
//!
//! \param ucVal the bit want to clear.
//!
//! This function is to clear STMPE811 interrupt status.
//!
//! \return none.
//
//*****************************************************************************
void STMPE811INTClear(unsigned char ucVal)
{
    STMPE811Write(STMPE811_INT_STA, 1, (unsigned long)ucVal);
}