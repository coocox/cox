//*****************************************************************************
//
//! @page GPS_testcase GPS function test
//!
//! File: @ref GPS_Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the GPS sub component.<br><br>
//! - \p Board: Cookie M0516 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_DM163_Function
//! .
//! \file GPS_Test.c
//! \brief GPS test source file
//! \brief GPS test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "GPS.h"

char rev_buf[80];                //Receive Buffer
unsigned char rev_start = 0;     //Receiving start flag
unsigned char rev_stop  = 0;     //Receiving end flag
unsigned char gps_flag = 0;      //GPS Processed flag

//*****************************************************************************
//
//! \brief Get the Test description of GPS Function test.
//!
//! \return the description of the GPS test.
//
//*****************************************************************************
static char* GPSGetTest(void)
{
    return "GPS Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of GPS test.
//!
//! \return None.
//
//*****************************************************************************
static void GPSSetup(void)
{
    GPS_Init(9600);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of GPS test.
//!
//! \return None.
//
//*****************************************************************************
static void GPSTearDown(void)
{
}

void
PrintStr(char* pcMsg)
{
	while (*pcMsg != '\0')
    {
        TestIOPut(*pcMsg++);
    }
}

void
PrintNum(unsigned long n)
{
	char buf[16], *p;

    if (n == 0)
    {
	        TestIOPut('0');
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > buf)
            TestIOPut(*--p);
    }
}
void UART_Put_Inf(char *inf, unsigned long dat)
{
	PrintStr(inf);
    PrintNum(dat);
    TestIOPut('\n');
}
//*****************************************************************************
//
//! \brief GPS test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void GPSExecute(void)
{
    unsigned char error_num = 0;
    GPS_INFO GPS;
	
    rev_stop=0;
    while(1)
    {
        if(rev_stop)
        {
        	PrintStr(rev_buf);

            if(GPS_GPRMC(rev_buf, &GPS))
            {
                UART_Put_Inf("Latitude: ", GPS.latitude);
                UART_Put_Inf("Longitude: ", GPS.longitude);
                UART_Put_Inf("Year: ", GPS.D.year);
                UART_Put_Inf("Month: ", GPS.D.month);
                UART_Put_Inf("Day: ", GPS.D.day);
                UART_Put_Inf("Hour: ", GPS.D.hour);
                UART_Put_Inf("minute: ", GPS.D.minute);
                UART_Put_Inf("South or North: ", GPS.NS);
                UART_Put_Inf("East or West: ", GPS.EW);
                rev_stop = 0;
                gps_flag = 0;
                error_num = 0;
            }
            else
            {
            	PrintStr("Analysis is invalid and reinitialize\n");
                error_num++;
                if (error_num >= 20)
                {
                    error_num = 20;
                    GPS_Init(9600);
                }
                rev_stop = 0;
                gps_flag = 0;
            }
        }
    }			
}

//
// GPS Function test case struct.
//
const tTestCase sTestGPSFunction = {
    GPSGetTest,	
    GPSSetup,
    GPSTearDown,
    GPSExecute
};

//
// GPS test suits.
//
const tTestCase * const psPatternGPSTest[] =
{
    &sTestGPSFunction,
    0
};

