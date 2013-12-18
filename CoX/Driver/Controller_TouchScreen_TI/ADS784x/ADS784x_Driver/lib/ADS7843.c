//*****************************************************************************
//
//! \file ADS7843.c
//! \brief Driver source file for ADS7843 touch screen controller
//! \version V0.0.1
//! \date 4/27/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2013, CooCox 
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
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_gpio.h"
#include "xhw_spi.h"
#include "xhw_nvic.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xspi.h"
#include "ADS7843.h"
#include "stdio.h"

TouchInfo tTouchData;

#ifdef ADS7843_ENABLE_TOUCH_INT
unsigned long TouchIntSvr(void *pvCBData,  unsigned long ulEvent,
                      unsigned long ulMsgParam, void *pvMsgData);
#endif

//*****************************************************************************
//
//! \brief Initialize ADS7843
//!
//! \param None.
//!
//! This function initialize ADS7843's SPI interface and .
//!
//! \return None.
//
//*****************************************************************************
void ADS7843Init(void)
{
    xSysCtlPeripheralDisable2(ADS7843_SPI_BASE);
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ADS7843_PIN_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ADS7843_PIN_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ADS7843_PIN_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ADS7843_PIN_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ADS7843_PIN_INT));
    xSysCtlPeripheralEnable2(ADS7843_SPI_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xGPIOSPinDirModeSet(ADS7843_PIN_CS, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(ADS7843_PIN_INT, xGPIO_DIR_MODE_IN);

    xGPIOSPinWrite(ADS7843_PIN_INT, 1); // pull up
    xGPIOSPinWrite(ADS7843_PIN_CS, 1);  // Deselect

#ifdef ADS7843_ENABLE_TOUCH_INT
    //
    // GPIO interrupt call back function initialize
    //
    xGPIOSPinIntCallbackInit(ADS7843_PIN_INT, TouchIntSvr);

    //
    // Enable ADS7843_PIN_INT interrupt input
    //
    xGPIOSPinIntEnable(ADS7843_PIN_INT, xGPIO_FALLING_EDGE);

    //
    // Enable GPIO interrupt
    //
    xIntEnable(xINT_GPIOC);
#endif

#ifdef ADS7843_USE_PIN_BUSY
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ADS7843_PIN_BUSY));
    xGPIOSPinDirModeSet(ADS7843_PIN_BUSY, xGPIO_DIR_MODE_IN);
    xGPIOSPinWrite(ADS7843_PIN_BUSY, 1);  // pull up
#endif

    //
    // PB13 as SPI2.CLK
    //
    xSPinTypeSPI(ADS7843_SPI_CLK, ADS7843_PIN_CLK);

    //
    // PB14 as SPI2.MISO
    //
    xSPinTypeSPI(ADS7843_SPI_MISO, ADS7843_PIN_MISO);
    //
    // PB15 as SPI2.MOSI
    //
    xSPinTypeSPI(ADS7843_SPI_MOSI, ADS7843_PIN_MOSI);

    //xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    //! Set SPI mode.
    //
    xSPIConfigSet(ADS7843_SPI_BASE, 2000000,
            xSPI_MOTO_FORMAT_MODE_0 |
            xSPI_MODE_MASTER |
            xSPI_MSB_FIRST |
            xSPI_DATA_WIDTH8);

    xSPISSSet( ADS7843_SPI_BASE, xSPI_SS_SOFTWARE, xSPI_SS0 );
    xSPIEnable(ADS7843_SPI_BASE);

    // assign default values
    tTouchData.th_ad_left = TOUCH_AD_X_MIN;
    tTouchData.th_ad_right = TOUCH_AD_X_MAX;
    tTouchData.th_ad_up = TOUCH_AD_Y_MAX;
    tTouchData.th_ad_down = TOUCH_AD_Y_MIN;
    tTouchData.touch_status = 0;
}

//*****************************************************************************
//
//! \brief Inquire for pen down ADS7843
//!
//! \param None.
//!
//! This function initialize ADS7843's SPI interface and .
//!
//! \return None.
//
//*****************************************************************************
unsigned long ADS7843PenInq(void)
{
    return(xGPIOSPinRead(ADS7843_PIN_INT));
}

//*****************************************************************************
//
//! \brief Read the x, y axis ADC convert value once from ADS7843
//!
//! \param x To save the x axis ADC convert value.
//! \param y To save the y axis ADC convert value.
//!
//! \return None.
//
//*****************************************************************************
void ADS7843ReadADXYRaw(unsigned short *x, unsigned short *y)
{
    // Chip select
    xGPIOSPinWrite(ADS7843_PIN_CS, 0);
    xSysCtlDelay(10);

    // Send read x command
    xSPISingleDataReadWrite(ADS7843_SPI_BASE, ADS7843_READ_X); //read x command
#ifdef ADS7843_USE_PIN_BUSY

    // wait for conversion complete
    while(xGPIOSPinRead(ADS7843_PIN_BUSY));
#else

    // The conversion needs 8us to complete
    xSysCtlDelay(240);
#endif

    // Read the high 8bit of the 12bit conversion result
    *x = (unsigned short)xSPISingleDataReadWrite(ADS7843_SPI_BASE, 0x00)&0xFF;
    *x <<= 4;
    // Read the low 4bit of the 12bit conversion result
    *x |= (unsigned short)xSPISingleDataReadWrite(ADS7843_SPI_BASE, 0x00)>>4;

    // Send read y command
    xSPISingleDataReadWrite(ADS7843_SPI_BASE, ADS7843_READ_Y); //read y command
#ifdef ADS7843_USE_PIN_BUSY

    // wait for conversion complete
    while(xGPIOSPinRead(ADS7843_PIN_BUSY));
#else

    // The conversion needs 8us to complete
    xSysCtlDelay(240);
#endif

    // Read the high 8bit of the 12bit conversion result
    *y = (unsigned short)xSPISingleDataReadWrite(ADS7843_SPI_BASE, 0x00)&0xFF;
    *y <<= 4;

    // Read the low 4bit of the 12bit conversion result
    *y |= (unsigned short)xSPISingleDataReadWrite(ADS7843_SPI_BASE, 0x00)>>4;
    xGPIOSPinWrite(ADS7843_PIN_CS, 1);
}

//*****************************************************************************
//
//! \brief read the x, y axis ADC convert value from ADS7843(with software filter)
//!
//! \param x To save the x axis ADC convert value.
//! \param y To save the y axis ADC convert value.
//!
//! This function Reads the x,y axis's ADC value from ADS7843 with software
//! filter. The function first read out TOUCH_SMAPLE_LEN samples. Then discard
//! the first data and the last data and sort the remained data. Then discard
//! the first and the last one of the remained data and compute the average
//! value of the final remained data.
//!
//! \return None.
//
//*****************************************************************************
void ADS7843ReadADXY(unsigned short *x, unsigned short *y)
{
    unsigned short usXYArray[2][TOUCH_SMAPLE_LEN];
    unsigned char i,j;
    unsigned short temp;

    for(i=0; i<TOUCH_SMAPLE_LEN; i++)
    {
        ADS7843ReadADXYRaw(&usXYArray[0][i], &usXYArray[1][i]);
    }

    // Discard the first and the last one of the data and sort remained data
    for(i=1;i<TOUCH_SMAPLE_LEN-2; i++)
    {
        for(j=i+1;j<TOUCH_SMAPLE_LEN-1; j++)
        {
            if(usXYArray[0][i]>usXYArray[0][j])
            {
                temp = usXYArray[0][i];
                usXYArray[0][i] = usXYArray[0][j];
                usXYArray[0][j] = temp;
            }

            if(usXYArray[1][i]>usXYArray[1][j])
            {
                temp = usXYArray[1][i];
                usXYArray[1][i] = usXYArray[1][j];
                usXYArray[1][j] = temp;
            }
        }
    }
    usXYArray[0][0] = 0;
    usXYArray[1][0] = 0;

    //
    // Discard the first and the last one of the sorted data
    // and compute the average value of the remained data.
    //
    for(i=2; i<TOUCH_SMAPLE_LEN-2; i++)
    {
        usXYArray[0][0] += usXYArray[0][i];
        usXYArray[1][0] += usXYArray[1][i];
    }
    *x = usXYArray[0][0]/(TOUCH_SMAPLE_LEN - 4);
    *y = usXYArray[1][0]/(TOUCH_SMAPLE_LEN - 4);
}

//*****************************************************************************
//
//! \brief Read the ADC convert value of specified input channel
//!
//! \param ucChannel specifies the channel to read
//!
//! This function read the ADC convert value of specified channel. The channel
//! can be: ADS7843_READ_X, ADS7843_READ_Y, ADS7843_READ_IN3, ADS7843_READ_IN4.
//!
//! \return None.
//
//*****************************************************************************
unsigned short ADS7843ReadInputChannel(unsigned char ucChannel)
{
    unsigned short res;

    if((ucChannel != ADS7843_READ_IN4) || (ucChannel != ADS7843_READ_IN3) ||
            (ucChannel != ADS7843_READ_X) || (ucChannel != ADS7843_READ_Y))
    {
        return 0;
    }
    xGPIOSPinWrite(ADS7843_PIN_CS, 0);
    xSysCtlDelay(10);
    xSPISingleDataReadWrite(ADS7843_SPI_BASE, ucChannel);
#ifdef ADS7843_USE_PIN_BUSY

    // Waiting for conversion complete
    while(xGPIOSPinRead(ADS7843_PIN_BUSY));
#else
    xSysCtlDelay(240);
#endif
    res = (unsigned short)xSPISingleDataReadWrite(ADS7843_SPI_BASE, 0x00)&0x00FF;
    res <<= 4;
    res |= (unsigned short)xSPISingleDataReadWrite(ADS7843_SPI_BASE, 0x00)>>4;
    xGPIOSPinWrite(ADS7843_PIN_CS, 1);

    return res;
}

//*****************************************************************************
//
//! \brief Touch screen calibration.
//!
//! \param None.
//!
//! This function is to calibrate the touch screen. If the read out coordinate
//! is not accurate, you can use this function to calibrate it. After this
//! function is called, you must touch the screen in about 10 seconds or the
//! function will return with no effect. After you touch the screen, the counter
//! will be zeroed and restart counting. If the calibration is not over and the
//! touch is always applied on the screen, the counter will not increase, so you
//! don't have to worry about the calibrate time.
//!     All you need to do with the calibration is to use a touch pen or other
//! object which is a little sharp but will not damage the touch screen to touch
//! the screen and slide the pen from top edge of the screen to the bottom edge.
//! Then slide the pen from left edge to right edge. Make sure that the pen should
//! not leave the screen until it slides to the edge or the calibrate may be
//! inaccurate. The direction or sequence is optional. If __DEBUG_PRINT__ is defined
//! you can see the calibration result. The calibration will calibrate both x axis
//! and y axis. Also you can calibration only one axis. the axis which is not
//! calibrated will retain its original value.
//!
//! \return None.
//
//*****************************************************************************
unsigned char ADS7843Calibration(void)
{
    unsigned short adx, ady;
    unsigned short adxmin = TOUCH_AD_X_MAX;
    unsigned short adxmax = TOUCH_AD_X_MIN;
    unsigned short adymin = TOUCH_AD_X_MAX;
    unsigned short adymax = TOUCH_AD_X_MIN;
    unsigned char ucCalibrationFlag = 0;
    unsigned long timeout = 0;

#ifdef ADS7843_ENABLE_TOUCH_INT
    //  disable touch interrupt
    xGPIOSPinIntDisable(ADS7843_PIN_INT);
#endif
    while(1)
    {
        if(!xGPIOSPinRead(ADS7843_PIN_INT))
        {
            //
            // If pen down continuously read the x,y value and record the
            // maximum and minimum value
            //
            while(!xGPIOSPinRead(ADS7843_PIN_INT))
            {
                ADS7843ReadADXY(&adx, &ady);
                if(adx < adxmin)
                {
                    adxmin = adx;
                }
                else if(adx > adxmax)
                {
                    adxmax = adx;
                }

                if(ady < adymin)
                {
                    adymin = ady;
                }
                else if(ady > adymax)
                {
                    adymax = ady;
                }
            }
            // Counter clear.
            timeout = 0;
        }

        // If x axis calibration is not complete
        if(!(ucCalibrationFlag & 1))
        {
            //  If x axis calibrate over
            if((adxmax>(TOUCH_AD_X_MAX - TOUCH_AD_CALIB_ERROR))&&
                (adxmax<(TOUCH_AD_X_MAX + TOUCH_AD_CALIB_ERROR))&&
                (adxmin>(TOUCH_AD_X_MIN - TOUCH_AD_CALIB_ERROR))&&
                (adxmin<(TOUCH_AD_X_MIN + TOUCH_AD_CALIB_ERROR)))
            {
#ifdef __DEBUG_PRINT__
                printf("x coordinate calibrate over\n\r");
#endif
                tTouchData.th_ad_left = adxmin;
                tTouchData.th_ad_right = adxmax;
                ucCalibrationFlag |= 1;
            }
        }

        // If y axis calibration is not complete
        if(!(ucCalibrationFlag & 2))
        {
            //  If y axis calibrate over
            if((adymax>(TOUCH_AD_Y_MAX - TOUCH_AD_CALIB_ERROR))&&
                (adymax<(TOUCH_AD_Y_MAX + TOUCH_AD_CALIB_ERROR))&&
                (adymin>(TOUCH_AD_Y_MIN - TOUCH_AD_CALIB_ERROR))&&
                (adymin<(TOUCH_AD_Y_MIN + TOUCH_AD_CALIB_ERROR)))
            {
#ifdef __DEBUG_PRINT__
                printf("y coordinate calibrate over\n\r");
#endif
                tTouchData.th_ad_up = adymax;
                tTouchData.th_ad_down = adymin;
                ucCalibrationFlag |= 2;
            }
        }

        // If two coordinates calibrate over or timer out
        if((ucCalibrationFlag == 3)||(timeout++ > 100000))
        {
#ifdef ADS7843_ENABLE_TOUCH_INT
            xGPIOSPinIntEnable(ADS7843_PIN_INT, xGPIO_FALLING_EDGE);
#endif
            return ucCalibrationFlag;
        }
        xSysCtlDelay(1000);
    }
}

//*****************************************************************************
//
//! \brief Read the XY coordinate of touch point.
//!
//! \param x To save the x coordinate
//! \param y To save the y coordinate
//!
//! This function is to read current touch point. The x,y coordinates will be
//! read out from the input parameters. If the screen is not touched, it will
//! return last value, after the last value is read out, additional read will
//! return fail information and nothing will be read out.
//!
//! \return None.
//
//*****************************************************************************
unsigned char ADS7843ReadPiontXY(unsigned short *x, unsigned short *y)
{
    unsigned short usADX;
    unsigned short usADY;
    unsigned long temp = 0;

    if(!xGPIOSPinRead(ADS7843_PIN_INT))
    {
        //  If pen down
        ADS7843ReadADXY(&usADX, &usADY);

        //  calculate the difference
        temp = usADX - tTouchData.th_ad_left;

        //  limit the left edge
        if(temp>tTouchData.th_ad_right) temp=0;

        //  calculate the x coordinate
        *x=temp*TOUCH_SCREEN_WIDTH/(tTouchData.th_ad_right - tTouchData.th_ad_left);
        tTouchData.last_x = tTouchData.cur_x;
        tTouchData.cur_x = *x;

        temp = tTouchData.th_ad_up - usADY;

        //  limit the top edge
        if(temp>tTouchData.th_ad_up) temp=0;

        //  calculate the y coordinate
        *y=temp*TOUCH_SCREEN_HEIGHT/(tTouchData.th_ad_up - tTouchData.th_ad_down);
        tTouchData.last_y = tTouchData.cur_y;
        tTouchData.cur_y = *y;
        return 0;
    }
    else
    {
        //  if pen up
        if(tTouchData.touch_status&TOUCH_STATUS_PENUP)
        {
            tTouchData.last_x = tTouchData.cur_x;
            *x = tTouchData.cur_x;
            tTouchData.last_y = tTouchData.cur_y;
            *y = tTouchData.cur_y;
            tTouchData.touch_status = 0;
            return 0;
        }
        return 1;
    }
}

//
// If pen interrupt is enabled
//
#ifdef ADS7843_ENABLE_TOUCH_INT
//*****************************************************************************
//
//! \brief ADS7843 touch interrupt callback function.
//!
//! \param pvCBData Not used.
//! \param ulEvent Not used.
//! \param ulMsgParam Not used.
//! \param pvMsgData Not used.
//!
//! This function is called when the screen is touched. The program capture both
//! the falling edge when pen down and the rising edge when pen up. When pen down
//! the program will read the coordinate of x,y and update touch status.
//!
//! \return 0.
//
//*****************************************************************************
unsigned long TouchIntSvr(void *pvCBData,  unsigned long ulEvent,
                      unsigned long ulMsgParam, void *pvMsgData)
{
    unsigned short x, y;
    xGPIOSPinIntDisable(ADS7843_PIN_INT);
    if(xGPIOSPinRead(ADS7843_PIN_INT))
    {
        // Change to falling trigger edge when pen up
        xGPIOSPinIntEnable(ADS7843_PIN_INT, xGPIO_FALLING_EDGE);
        tTouchData.touch_status |= TOUCH_STATUS_PENUP;
        tTouchData.touch_status &= ~TOUCH_STATUS_PENDOWN;
    }
    else
    {
        // Modify status
        tTouchData.touch_status |= TOUCH_STATUS_PENDOWN;
        tTouchData.touch_status &= ~TOUCH_STATUS_PENUP;
        // Read x,y coordinate
        ADS7843ReadPiontXY(&x, &y);
        // Change
        xGPIOSPinIntEnable(ADS7843_PIN_INT, xGPIO_RISING_EDGE);
    }
    return 0;
}
#endif
