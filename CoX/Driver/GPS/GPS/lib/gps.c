//*****************************************************************************
//
//! \file gps.c
//! \brief Driver for gps EB-365.
//! \version 2.1.1.0
//! \date 10/18/2011
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

#include <string.h>
#include <stdlib.h>
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"
#include "cookie_cfg.h"
#include "cookie.h"
#include "gps.h"

//*****************************************************************************
//
//! \brief Get the character number.
//!
//! \param ulNum is the first of several comma.
//! \param *str is string.
//!
//! \return Returns the index value of string after the comma character.
//
//*****************************************************************************
static unsigned char GetComma(unsigned char ulNum, char *str)
{
    unsigned char i, j = 0;
    int len = strlen(str);

    for(i = 0; i < len; i ++)
    {
        if(str[i] == ',')
            j++;
        if(j == ulNum)
            return (i + 1);
    }
    return 0;	
}

static double Str_To_Double(char *buf)
{
    double rev = 0;
    double dat;
    unsigned char integer = 1;
    unsigned int i;

    char *str = buf;
    while(*str != '\0')
    {
        dat = *str;
        if((dat >= '0')&&(dat <= '9'))
        {
        	dat = dat - 0x30;
        }
        if(dat == '.')
        {
            integer = 0;
            i = 1;
            str ++;
            continue;
        }
        if( integer == 1 )
        {
            rev = rev * 10 + dat;
        }
        else
        {
            i = i * 10 ;
            rev = rev + dat / i;          
        }
        str ++;
    }
    return rev;
}

static double Get_Double_Number(char *s)
{
    char buf[10];
    unsigned char i;
    double rev;
    i = GetComma(1, s);
    i = i - 1;
    strncpy(buf, s, i);
    buf[i] = '\0';
    rev=Str_To_Double(buf);
    return rev;	
}

//*****************************************************************************
//
//! \brief Analyze GPGGA information.
//!
//! \param str is the pointer to the string.
//! \param GPS is the GPS_INFO struct.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char
GPS_GPGGA(char *str, GPS_INFO *GPS)
{
    unsigned char ch, status;
    char *buf = str;
    ch = buf[4];
    status = buf[GetComma(2, buf)];

    if (ch == 'G')
    {
        if (status != ',')
        {
            GPS->height_sea = (float)Get_Double_Number(&buf[GetComma(9, buf)]);
            GPS->height_ground = (float)Get_Double_Number(&buf[GetComma(11, buf)]);
            return 1;
        }
    }
    return 0;    
}

//*****************************************************************************
//
//! \brief Analyze GPGLL information.
//!
//! \param str is the pointer to the string.
//! \param GPS is the GPS_INFO struct.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char
GPS_GPGLL(char *str, GPS_INFO *GPS)
{
    unsigned char ch, status, ucTemp;
    char *buf = str;
    double LatitudeTemp, LongitudeTemp;
    ch = buf[5];
    status = buf[GetComma(6, buf)];
    if(ch == 'L')
    {
        if(status == 'A')
        {
            GPS -> NS = buf[GetComma(2, buf)];
            GPS -> EW = buf[GetComma(4, buf)];

            GPS->latitude   = Get_Double_Number(&buf[GetComma(1, buf)]);
            GPS->longitude  = Get_Double_Number(&buf[GetComma(3, buf)]);

            GPS->latitude_Degree  = (unsigned char)(GPS->latitude / 100);
            LatitudeTemp    = GPS->latitude - GPS->latitude_Degree * 100;
            GPS->latitude_Cent = (unsigned char)LatitudeTemp;
            GPS->latitude_Second  = (unsigned char)((LatitudeTemp - GPS->latitude_Cent) * 60);

            GPS->longitude_Degree  = (unsigned char)(GPS->longitude / 100);
            LongitudeTemp    = GPS->longitude - GPS->longitude_Degree * 100;
            GPS->longitude_Cent = (unsigned char)LongitudeTemp;
            GPS->longitude_Second  = (unsigned char)((LongitudeTemp - GPS->longitude_Cent) * 60);

            ucTemp = GetComma(5, buf);
            GPS->D.hour    = (buf[ucTemp] - '0') * 10 + (buf[ucTemp + 1] - '0');
            GPS->D.minute  = (buf[ucTemp + 2] - '0') * 10 + (buf[ucTemp + 3] - '0');
            GPS->D.second  = (buf[ucTemp + 4] - '0') * 10 + (buf[ucTemp + 5] - '0');
			
            return 1;
        }
    }
    return 0;
}

//*****************************************************************************
//
//! \brief Analyze GPGSA information.
//!
//! \param str is the pointer to the string.
//! \param GPS is the GPS_INFO struct.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char
GPS_GPGSA(char *str, GPS_INFO *GPS)
{
    char *buf = str;
    if((buf[4] == 'S')&&(buf[5] == 'A'))
    {
        //
        //add your code
        //
        return 1;
    }
    return 0;
}

static void UTC2BTC(DATE_TIME *GPS_TIME)
{
    GPS_TIME->second ++;
    if(GPS_TIME->second > 59)
    {
        GPS_TIME->second = 0;
        GPS_TIME->minute ++;
        if(GPS_TIME->minute > 59)
        {
            GPS_TIME->minute = 0;
            GPS_TIME->hour ++;
        }
    }

    GPS_TIME->hour = GPS_TIME->hour + 8;  //Beijing time
    if(GPS_TIME->hour > 23)
    {
        GPS_TIME->hour -= 24;
        GPS_TIME->day += 1;
        if( GPS_TIME->month == 2 ||
            GPS_TIME->month == 4 ||
            GPS_TIME->month == 6 ||
            GPS_TIME->month == 9 ||
            GPS_TIME->month == 11 )
        {
            if(GPS_TIME->day > 30)
            {
                GPS_TIME->day = 1;
                GPS_TIME->month++;
            }
        }
        else
        {
            if(GPS_TIME->day > 31)
            {
                GPS_TIME->day = 1;
                GPS_TIME->month ++;
            }
        }
        if(GPS_TIME->year % 4 == 0 )
        {
            if((GPS_TIME->day > 29) && (GPS_TIME->month == 2))
            {
                GPS_TIME->day = 1;
                GPS_TIME->month ++;
            }
        }
        else
        {
            if((GPS_TIME->day > 28) && (GPS_TIME->month == 2))
            {
                GPS_TIME->day = 1;
                GPS_TIME->month ++;
            }
        }
        if(GPS_TIME->month > 12)
        {
            GPS_TIME->month -= 12;
            GPS_TIME->year ++;
        }
    }
}

//*****************************************************************************
//
//! \brief Analyze GPRMC information.
//!
//! \param str is the pointer to the string.
//! \param GPS is the GPS_INFO struct.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char
GPS_GPRMC(char *str, GPS_INFO *GPS)
{
    unsigned char ch, status, ucTemp;
    char *buf = str;
    double LatitudeTemp, LongitudeTemp;
    ch = buf[5];
    status = buf[GetComma(2, buf)];

    if(ch == 'C')
    {
        if(status == 'A')
        {
            GPS -> NS = buf[GetComma(4, buf)];
            GPS -> EW = buf[GetComma(6, buf)];

            GPS->latitude   = Get_Double_Number(&buf[GetComma(3, buf)]);
            GPS->longitude  = Get_Double_Number(&buf[GetComma(5, buf)]);

            GPS->latitude_Degree  = (unsigned char)(GPS->latitude / 100);
            LatitudeTemp    = GPS->latitude - GPS->latitude_Degree * 100;
            GPS->latitude_Cent = (unsigned char)LatitudeTemp;
            GPS->latitude_Second  = (unsigned char)((LatitudeTemp - GPS->latitude_Cent) * 60);

            GPS->longitude_Degree  = (unsigned char)(GPS->longitude / 100);
            LongitudeTemp    = GPS->longitude - GPS->longitude_Degree * 100;
            GPS->longitude_Cent = (unsigned char)LongitudeTemp;
            GPS->longitude_Second  = (unsigned char)((LongitudeTemp - GPS->longitude_Cent) * 60);

            GPS->speed     = (float)Get_Double_Number(&buf[GetComma(7, buf)]) * 1.85;
            GPS->direction = (float)Get_Double_Number(&buf[GetComma(8, buf)]);
			
            ucTemp = GetComma(1, buf);
            GPS->D.hour    = (buf[ucTemp + 0] - '0') * 10 + (buf[ucTemp + 1] - '0');
            GPS->D.minute  = (buf[ucTemp + 2] - '0') * 10 + (buf[ucTemp + 3] - '0');
            GPS->D.second  = (buf[ucTemp + 4] - '0') * 10 + (buf[ucTemp + 5] - '0');
			
            ucTemp = GetComma(9, buf);
            GPS->D.day     = (buf[ucTemp + 0] - '0') * 10 + (buf[ucTemp + 1] - '0');
            GPS->D.month   = (buf[ucTemp + 2] - '0') * 10 + (buf[ucTemp + 3] - '0');
            GPS->D.year    = (buf[ucTemp + 4] - '0') * 10 + (buf[ucTemp + 5] - '0') + 2000;
            UTC2BTC(&GPS->D);
						
            return 1;
        }
    }
    return 0;
}

//*****************************************************************************
//
//! \brief Analyze GPVTG information.
//!
//! \param str is the pointer to the string.
//! \param GPS is the GPS_INFO struct.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char
GPS_GPVTG(char *str, GPS_INFO *GPS)
{
    unsigned char ch;
    char *buf = str;
    ch = buf[4];
    if(ch == 'T')
    {
        //
        //add your code
        //
        return 1;
    }
    return 0;
}

//*****************************************************************************
//
//! \brief Analyze GPGSV information.
//!
//! \param str is the pointer to the string.
//! \param GPS is the GPS_INFO struct.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char
GPS_GPGSV(char *str, GPS_INFO *GPS)
{
    unsigned char ch;
    char *buf = str;
    ch = buf[5];
    if(ch == 'V')
    {
        //
        //add your code
        //
        return 1;
    }
    return 0;
}

//*****************************************************************************
//
//! \brief UART1 Interrupt Receive Service.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
unsigned char num = 0;
//
//! You need to define these variables in the main.c and initialize to 0.
//
extern char rev_buf[80];        //Receive Buffer
extern unsigned char rev_start, //Receiving start flag
                     rev_stop,  //Receiving end flag
                     gps_flag;  //GPS Processed flag
unsigned long 
uart1CallbackFunc(void *pvCBData, unsigned long ulEvent,  
                   unsigned long ulMsgParam, void *pvMsgData)				   
{
    unsigned char ch;  
    ch = UARTCharGet(sUART_BASE);
    if ((ch == '$') && (gps_flag == 0))
    {
        rev_start = 1;
        rev_stop  = 0;		  
    }
    if (rev_start == 1)
    {
        rev_buf[num++] = ch;  
        if (ch == '\n')       
        {
            rev_buf[num] = '\0';
            rev_start = 0;
            rev_stop  = 1;	  
            gps_flag = 1;
            num = 0;
        }
    }
    return 0;
}

//*****************************************************************************
//
//! \brief UART1 Initialize.
//!
//! \param ulBaudrate is the baud rate of UART1.
//!
//! \return None.
//
//*****************************************************************************
void
UART1_Init(unsigned long ulBaudrate)
{
    xSysCtlPeripheralEnable2(sUART_BASE);
    //xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD0));

    sPinTypeUART(sUART_BASE);
	
    xUARTConfigSet(sUART_BASE, ulBaudrate, (UART_CONFIG_WLEN_8   |
                                            UART_CONFIG_STOP_ONE |
                                            UART_CONFIG_PAR_NONE));
    xUARTIntEnable(sUART_BASE, xUART_INT_RX);
    UARTIntCallbackInit(sUART_BASE, uart1CallbackFunc);
    xUARTEnable(sUART_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    xIntEnable(xSysCtlPeripheraIntNumGet(sUART_BASE));
}

//*****************************************************************************
//
//! \brief GPS Initialize.
//!
//! \param ulBaudrate is the baud rate of GPS.
//!
//! \return None.
//
//*****************************************************************************
void
GPS_Init(unsigned long ulBaudrate)
{
    UART1_Init(ulBaudrate);
}
