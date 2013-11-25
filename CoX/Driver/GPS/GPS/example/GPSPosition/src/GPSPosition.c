//*****************************************************************************
//
//! \file GPSPosition.c
//! \brief Get GPS location information, and then print it out through UART.
//! \version 1.0
//! \date 01/11/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2013 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"
#include "gps.h"

char rev_buf[80];                //Receive Buffer
unsigned char rev_start = 0;     //Receiving start flag
unsigned char rev_stop  = 0;     //Receiving end flag
unsigned char gps_flag = 0;      //GPS Processed flag
void u32tostr(unsigned long dat, char *str);
void UART_Send_Str(char *str);
void UART_Put_Inf(char *inf, int dat);

void GPSPosition(void)
{
    unsigned char error_num = 0;
    GPS_INFO GPS;

    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(100000);
	
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PA9));

    xSPinTypeUART(UART1TX, PA9);

    xUARTConfigSet(xUART1_BASE, 115200, (UART_CONFIG_WLEN_8   |
                                         UART_CONFIG_STOP_ONE |
                                         UART_CONFIG_PAR_NONE));
    xUARTEnable(xUART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
	
    GPS_Init(9600);

    while (1) {
        if(rev_stop) {
            if(GPS_GPRMC(rev_buf, &GPS)){
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
            } else {
                UART_Send_Str("Analysis is invalid and reinitialize\n");
                error_num++;
                if (error_num >= 20){
                    error_num = 20;
                    GPS_Init(9600);
                }
                rev_stop = 0;
                gps_flag = 0;
            }
        }
    }
}

void u32tostr(unsigned long dat, char *str)
{
    char temp[20];
    unsigned char i, j;

    i = 0;
    while(dat){
        temp[i] = dat % 10 + 0x30;
        i++;
        dat /= 10;
    }
    j = i;
    for(i = 0; i < j; i++){
        str[i] = temp[j - i- 1];
    }
    if(!i){
        str[i++] = '0';
    }
    str[i] = 0;
}

void UART_Send_Str(char *str)
{
    int len = strlen(str) - 1;
    int i;

    for(i = 0; i < len; i++)
        xUARTCharPut(xUART1_BASE, str[i]);
    if(str[i] == '\n'){
        xUARTCharPut(xUART1_BASE, 0x0d);
        xUARTCharPut(xUART1_BASE, 0x0a);
    } else {
        xUARTCharPut(xUART1_BASE, str[i]);
    }
}

void UART_Put_Inf(char *inf, int dat)
{
    char temp[20];
    UART_Send_Str(inf);
    u32tostr(dat, temp);
    UART_Send_Str(temp);
    UART_Send_Str("\n");
}