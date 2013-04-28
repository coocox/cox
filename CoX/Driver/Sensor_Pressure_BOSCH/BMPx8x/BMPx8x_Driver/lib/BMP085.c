//*****************************************************************************
//
//! \file BMP085.c
//! \brief BMP085/BMP180 driver file.
//! \version 0.0.1
//! \date 4/24/2013
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
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "BMP085.h"
#ifdef BMP085_USE_HARDWARE_I2C
#include "xhw_i2c.h"
#include "xi2c.h"
#endif

//**************************************************************
//
//! \internal
//! \brief software I2C SCL and SDA I/O control define
//
//***************************************************************
#ifndef BMP085_USE_HARDWARE_I2C
#define BMP085_SDA_SET()          xGPIOSPinWrite(BMP085_I2C_PIN_SDA,1)
#define BMP085_SDA_CLR()          xGPIOSPinWrite(BMP085_I2C_PIN_SDA,0)
#define BMP085_SCL_SET()          xGPIOSPinWrite(BMP085_I2C_PIN_SCL,1)
#define BMP085_SCL_CLR()          xGPIOSPinWrite(BMP085_I2C_PIN_SCL,0)
#define BMP085_SDA_DDR_OUT()      xGPIOSDirModeSet(BMP085_I2C_PIN_SDA, xGPIO_DIR_MODE_OD)
#define BMP085_SDA_DDR_IN()       xGPIOSDirModeSet(BMP085_I2C_PIN_SDA, xGPIO_DIR_MODE_IN)
#endif

static BMP085CalibratationStruct BMP085CalibData;

//*****************************************************************************
//
//! \brief Provides an approximately tms delay.
//!
//! \param t is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.
//! It can not ensure the accuracy of delay since different system clock maybe used.
//! Change the delay time as you need.
//!
//! \return None.
//
//*****************************************************************************
static void BMP085DelayMs(unsigned long t)
{
	while(t--)
	{
		xSysCtlDelay(20000);
	}
}

#ifndef BMP085_USE_HARDWARE_I2C
//*****************************************************************************
//
//! \brief Provides an short delay for I2C to slow down the clock rate.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void BMP085I2CDelay()
{
	xSysCtlDelay(100);
}

//*****************************************************************************
//
//! \brief Send start signal on I2C BUS.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void BMP085I2CStart(void)
{
    BMP085_SDA_SET();
    BMP085_SCL_SET();
    BMP085I2CDelay();
    BMP085_SDA_CLR();
    BMP085I2CDelay();
    BMP085_SCL_CLR();
}

//*****************************************************************************
//
//! \brief Send stop signal on I2C BUS.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void BMP085I2CStop(void)
{
    BMP085_SDA_CLR();
    BMP085_SCL_SET();
    BMP085I2CDelay();
    BMP085_SDA_SET();
    BMP085I2CDelay();
}

//*****************************************************************************
//
//! \brief Master Send ACK signal on I2C BUS.
//!
//! \param ack 1 stands for ACK, 0 stands for NACK.
//!
//! \return None.
//
//*****************************************************************************
void BMP085I2CSendACK(unsigned char ack)
{
	BMP085_SCL_CLR();
    if(ack)
    {
    	BMP085_SDA_CLR();
    }
    else
    {
    	BMP085_SDA_SET();
    }
    BMP085I2CDelay();
    BMP085_SCL_SET();
    BMP085I2CDelay();
    BMP085_SCL_CLR();
    BMP085I2CDelay();
    BMP085_SDA_CLR();
}

//*****************************************************************************
//
//! \brief Send ACK signal on I2C BUS.
//!
//! \param ack 1 stands for ACK, 0 stands for NACK.
//!
//! \return None.
//
//*****************************************************************************
unsigned char BMP085_RecvACK(void)
{
	unsigned char res;

	BMP085_SDA_DDR_IN();
	xGPIOSPinWrite(BMP085_I2C_PIN_SDA,1);  //pull up
    BMP085_SCL_SET();
    BMP085I2CDelay();
    res = xGPIOSPinRead(BMP085_I2C_PIN_SDA);
    BMP085_SCL_CLR();
    BMP085_SDA_DDR_OUT();
    //BMP085I2CDelay();

    return res;
}

//*****************************************************************************
//
//! \brief Send data byte on I2C BUS.
//!
//! \param dat The byte to be sent.
//!
//! \return result of the sending operation.
//
//*****************************************************************************
unsigned char BMP085I2CSendByte(unsigned char dat)
{
    unsigned char i;

    BMP085_SCL_CLR();
    for (i=0; i<8; i++)
    {
    	(dat&0x80) ? BMP085_SDA_SET():BMP085_SDA_CLR();
        dat <<= 1;
        BMP085_SCL_SET();
        BMP085I2CDelay();
        BMP085_SCL_CLR();
        BMP085I2CDelay();
    }
    return(BMP085_RecvACK());
}

//*****************************************************************************
//
//! \brief Receive data byte on I2C BUS.
//!
//! \param ack Specifies the ACK type, 0->NACK, 1->ACK.
//!
//! \return result of the reading operation.
//
//*****************************************************************************
unsigned char BMP085I2CRecvByte(unsigned char ack)
{
    unsigned char i;
    unsigned char dat = 0;

    BMP085_SCL_CLR();
    BMP085I2CDelay();
    BMP085_SDA_DDR_IN();
    xGPIOSPinWrite(BMP085_I2C_PIN_SDA,1);  //pull up,
    for (i=0; i<8; i++)
    {
        dat <<= 1;
        BMP085_SCL_SET();
        BMP085I2CDelay();
        if(xGPIOSPinRead(BMP085_I2C_PIN_SDA))
        {
        	dat++;
        }
        BMP085_SCL_CLR();
        BMP085I2CDelay();
    }
    BMP085_SDA_DDR_OUT();
    BMP085I2CSendACK(ack);

    return dat;
}

#endif

//*****************************************************************************
//
//! \brief Read data from EEPROM.
//!
//! \param ucReg Specifies the register address.
//! \param ucDataLen Specifies how many bytes to read(max is 4).
//!
//! \return output value. MSB first, right align.
//
//*****************************************************************************
unsigned long BMP085ReadData(unsigned char ucReg, unsigned char ucDataLen)
{
	unsigned char tmp = 0;
	unsigned long res = 0;

#ifndef BMP085_USE_HARDWARE_I2C

	BMP085I2CStart();
	//  send slave address(write)
	BMP085I2CSendByte(BMP085_ADDR << 1);
	//  send register address
	BMP085I2CSendByte(ucReg);
	//  restart transmission
	BMP085I2CStart();
	//  send slave address(read)
	BMP085I2CSendByte((BMP085_ADDR << 1)+1);
	//  read data
	while(ucDataLen-- >1)
	{
		res <<= 8;
		res += BMP085I2CRecvByte(1);
	}
	res <<= 8;
	res += BMP085I2CRecvByte(0);
	BMP085I2CStop();
#else

	//  send slave address(write) and register address and not end transmission
	xI2CMasterWriteRequestS1(BMP085_I2C_PORT, BMP085_ADDR, ucReg, xfalse);

	//  restart transmission, send slave address(read) and read a byte
	if(ucDataLen > 1)
	{
		xI2CMasterReadS1(BMP085_I2C_PORT, BMP085_ADDR, &tmp, xfalse);
		res = tmp;
		//  continue reading
		while((ucDataLen-1)&&(ucDataLen<5))
		{
			if(ucDataLen-1 != 1)
			{
				xI2CMasterReadS2(BMP085_I2C_PORT, &tmp, xfalse);
			}
			else
			{
				//  read over, end transmission
				xI2CMasterReadS2(BMP085_I2C_PORT, &tmp, xtrue);
			}
			res <<= 8;
			res += tmp;
			ucDataLen--;
		}
	}
	else
	{
		xI2CMasterReadS1(BMP085_I2C_PORT, BMP085_ADDR, &tmp, xtrue);
		res = tmp;
	}
#endif
	return res;
}

//*****************************************************************************
//
//! \brief Write data to control register.
//!
//! \param ucReg Specifies the register address.
//! \param ucData The data to be written.
//!
//! \return None.
//
//*****************************************************************************
void BMP085WriteData(unsigned char ucReg, unsigned char ucData)
{
#ifndef BMP085_USE_HARDWARE_I2C
	BMP085I2CStart();
	BMP085I2CSendByte(BMP085_ADDR << 1);
	BMP085I2CSendByte(ucReg);
	BMP085I2CSendByte(ucData);
	BMP085I2CStop();
#else
	xI2CMasterWriteRequestS1(BMP085_I2C_PORT, BMP085_ADDR, ucReg, xfalse);
	xI2CMasterWriteRequestS2(BMP085_I2C_PORT, ucData, xtrue);
#endif
}

//*****************************************************************************
//
//! \brief I2C and port initialization.
//!
//! \param ulBitRate Specifies the clock frequency
//!
//! \return None.
//
//*****************************************************************************
static void BMP085I2CInit(unsigned long ulBitRate)
{
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(BMP085_I2C_PIN_SCL));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(BMP085_I2C_PIN_SDA));
#ifdef BMP085_USE_HARDWARE_I2C
    xI2CMasterDisable(BMP085_I2C_PORT);
    xSPinTypeI2C(BMP085_I2C_SCL, BMP085_I2C_PIN_SCL);
    xSPinTypeI2C(BMP085_I2C_SDA, BMP085_I2C_PIN_SDA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSysCtlPeripheralEnable2(BMP085_I2C_PORT);
    xI2CMasterInit(BMP085_I2C_PORT, ulBitRate);
    I2CMasterInit(BMP085_I2C_PORT, xSysCtlClockGet()/2, xfalse, xtrue);
    xI2CMasterEnable(BMP085_I2C_PORT);
#else
    xGPIOSDirModeSet(BMP085_I2C_PIN_SCL, xGPIO_DIR_MODE_OD);
    xGPIOSDirModeSet(BMP085_I2C_PIN_SDA, xGPIO_DIR_MODE_OD);
    xGPIOSPinWrite(BMP085_I2C_PIN_SDA,1);
    xGPIOSPinWrite(BMP085_I2C_PIN_SCL,1);
#endif
}

//*****************************************************************************
//
//! \brief BMP085 initialization.
//!
//! \param ulBitRate Specifies the clock frequency
//!
//! \return Initial result. 0 stands for success, 1 stands for fail.
//
//*****************************************************************************
unsigned long BMP085Init(unsigned long ulBitRate)
{
	unsigned long ulBmpId;
	BMP085I2CInit(ulBitRate);
	ulBmpId = BMP085ReadData(BMP085_REG_ID, 1);
	if(ulBmpId != BMP085_ID)
	{
		return 1;
	}
	BMP085CalibData.ac1 = BMP085ReadData(BMP085_REG_AC1, 2);
	BMP085CalibData.ac2 = BMP085ReadData(BMP085_REG_AC2, 2);
	BMP085CalibData.ac3 = BMP085ReadData(BMP085_REG_AC3, 2);
	BMP085CalibData.ac4 = BMP085ReadData(BMP085_REG_AC4, 2);
	BMP085CalibData.ac5 = BMP085ReadData(BMP085_REG_AC5, 2);
	BMP085CalibData.ac6 = BMP085ReadData(BMP085_REG_AC6, 2);
	BMP085CalibData.b1  = BMP085ReadData(BMP085_REG_B1 , 2);
	BMP085CalibData.b2  = BMP085ReadData(BMP085_REG_B2 , 2);
	BMP085CalibData.mb  = BMP085ReadData(BMP085_REG_MB , 2);
	BMP085CalibData.mc  = BMP085ReadData(BMP085_REG_MC , 2);
	BMP085CalibData.md  = BMP085ReadData(BMP085_REG_MD , 2);
	return 0;
}

//*****************************************************************************
//
//! \brief Get temperature.
//!
//! \param None
//!
//! The function will directly get the temperature which has been calibrated.
//! The returned temperature is in unit of 0.1 Celsius degree for example
//! if the result is 213, then the temperature is 21.3 Celsius degree
//!
//! \return temperature.
//
//*****************************************************************************
long BMP085GetTemperature(void)
{
	long temp;
	long x1,x2,b5;

	BMP085WriteData(BMP085_REG_PRES_OS3, BMP085_REG_TEMP);

	//  At least 4.5ms delay is needed
	BMP085DelayMs(5);
	temp = BMP085ReadData(BMP085_REG_READ, 2);
	x1 = (((long)temp - (long)BMP085CalibData.ac6)*(long)BMP085CalibData.ac5) >> 15;
	x2 = ((long)BMP085CalibData.mc << 11) / (x1 + BMP085CalibData.md);
	b5 = x1 + x2;
	temp = ((b5 + 8) >> 4);
	return temp;
}

//*****************************************************************************
//
//! \brief Get barometric pressure.
//!
//! \param oss Specifies the over-sample rate(BMP085_OSS_0 ~ BMP085_OSS_3).
//!
//! The function will directly get the pressure which has been calibrated.
//! The returned pressure is in unit of Pa.
//! \note oss can be BMP085_OSS_0 ~ BMP085_OSS_3 which equal to 0~3. The bigger
//! oss is, the more precise and the longer time consumption for conversion.
//!
//! \return pressure.
//
//*****************************************************************************
long BMP085GetPressure(unsigned char oss)
{
	long temp;
	long x1,x2,x3,b3,b5,b6,p;
	unsigned long b4,b7;

	oss = oss>3 ? 3:oss;

	//
	// Read uncompensated temperature value
	//
	BMP085WriteData(BMP085_REG_PRES_OS3, BMP085_REG_TEMP);

	//  At least 4.5ms delay is needed
	BMP085DelayMs(5);
	temp = BMP085ReadData(BMP085_REG_READ, 2);
	x1 = (((long)temp - (long)BMP085CalibData.ac6)*(long)BMP085CalibData.ac5) >> 15;
	x2 = ((long)BMP085CalibData.mc << 11) / (x1 + BMP085CalibData.md);
	b5 = x1 + x2;

	//
	// Read uncompensated pressure value
	//
	BMP085WriteData(BMP085_REG_PRES_OS3, BMP085_REG_PRES_OS0+(oss<<6));

	//  This delay is important, the bigger oss is, the longer delay need.
	//  If delay is not enough, the read out data maybe error.
	BMP085DelayMs(2+((unsigned long)3<<oss));
	if(oss==0)
	{
		temp = BMP085ReadData(BMP085_REG_READ, 2);
	}
	else
	{
		temp = BMP085ReadData(BMP085_REG_READ, 3);
		temp >>= (8-oss);
	}

	b6 = b5 - 4000;
	// Calculate B3
	x1 = (BMP085CalibData.b2 * (b6 * b6)>>12)>>11;
	x2 = (BMP085CalibData.ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)BMP085CalibData.ac1)*4 + x3)<<oss) + 2)>>2;

	// Calculate B4
	x1 = (BMP085CalibData.ac3 * b6)>>13;
	x2 = (BMP085CalibData.b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (BMP085CalibData.ac4 * (unsigned long)(x3 + 32768))>>15;

	b7 = ((unsigned long)(temp - b3) * (50000>>oss));
	if (b7 < 0x80000000)
	{
		p = (b7<<1)/b4;
	}
	else
	{
		p = (b7/b4)<<1;
	}

	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	temp = p+((x1 + x2 + 3791)>>4);
	return temp;
}

//*****************************************************************************
//
//! \brief Get altitude.
//!
//! \param None.
//!
//! The function will return the altitude according to the barometric pressure.
//! The result is not accurate enough, it can only be used as a reference.
//!
//! \return temperature.
//
//*****************************************************************************
long BMP085GetAltitude(void)
{
	//P0  sea level barometric pressure as the zero height pressure
	long P0 = 101325;
	long P = BMP085GetPressure(BMP085_OSS_0);
	long Altitude;

	Altitude = (P0-P)*83/1000;

	return Altitude;
}



