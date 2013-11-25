//*****************************************************************************
//
//! \file Dot_Matrix.c
//! \brief Driver for the Dot Matrix controller
//! \version V2.1.1.0
//! \date 12/5/2012
//! \author CooCox
//! \copy
//!
//
//*****************************************************************************

#include "xhw_types.h"
#include "xcore.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xhw_timer.h"
#include "xtimer.h"
#include "Cookie.h"
#include "Cookie_cfg.h"
#include "Dot_Matrix.h"

//*****************************************************************************
//
//! Define the data zone
//
//*****************************************************************************

//
//! Gamma correctly value, every LED plane is different.value range is 0~63
//! [3]:RGB data, 0 for Red; 1 for green, 2 for Blue
//
static unsigned char g_ucGammaValue[3] = {10,63,63};

//
//! the index of buffer
//
static unsigned char g_ucPageIndex = 0;
static unsigned char g_ucLine = 0;

//
//! Test dots
//!dots matrix
//![2]:Page:one for display, one for receive data
//![8]:Row:8 row in LED plane
//![8]:Column:8 column in one row
//![3]:Color:RGB data: 0 for Red; 1 for green, 2 for Blue
//
static unsigned char dots[2][8][8][3] = {0};


#define open_line0	{xGPIOSPinWrite(sD8,1);}
#define open_line1	{xGPIOSPinWrite(sD9,1);}
#define open_line2	{xGPIOSPinWrite(sD10,1);}
#define open_line3	{xGPIOSPinWrite(sD11,1);}
#define open_line4	{xGPIOSPinWrite(sD12,1);}
#define open_line5	{xGPIOSPinWrite(sD13,1);}
#define open_line6	{xGPIOSPinWrite(sD3,1);}
#define open_line7	{xGPIOSPinWrite(sD4,1);}
#define close_all_line	{xGPIOSPinWrite(sD8,0);xGPIOSPinWrite(sD9,0);   \
                         xGPIOSPinWrite(sD10,0);xGPIOSPinWrite(sD11,0); \
                         xGPIOSPinWrite(sD12,0);xGPIOSPinWrite(sD13,0); \
                         xGPIOSPinWrite(sD3,0);xGPIOSPinWrite(sD4,0);}

//*****************************************************************************
//
//! \brief Init the DM163 Control connected pin
//!
//! \note The data will parral out.
//! 
//! \return None.
//
//*****************************************************************************
void 
DM163PinInit(void)
{
    xSysCtlPeripheralReset(xGPIOSPinToPeripheralId(sD6));
    xSysCtlPeripheralReset(xGPIOSPinToPeripheralId(sD7));
    xSysCtlPeripheralReset(xGPIOSPinToPeripheralId(sA1));
    xSysCtlPeripheralReset(xGPIOSPinToPeripheralId(sA0));
    xSysCtlPeripheralReset(xGPIOSPinToPeripheralId(sA2));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD6));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD7));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD8));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD10));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sA0));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sA1));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sA2));

    //
    // Set PD4(DIR_SDA), PD5(DIR_SCL), and PB0(DIR_SB) PB1(DIR_LATCH) PB2(DIR_RST) as output
    //
    xGPIOSPinTypeGPIOOutput(sD6);   // SCK
    xGPIOSPinTypeGPIOOutput(sD7);   // SDA
    xGPIOSPinTypeGPIOOutput(sA0);   // SB
    xGPIOSPinTypeGPIOOutput(sA1);   // LATCH
    xGPIOSPinTypeGPIOOutput(sA2);   // RST

    sD8PinTypeOUT();
    xGPIOSPinTypeGPIOOutput(sD9);
    xGPIOSPinTypeGPIOOutput(sD10);
    xGPIOSPinTypeGPIOOutput(sD11);
    xGPIOSPinTypeGPIOOutput(sD12);
    xGPIOSPinTypeGPIOOutput(sD13);
    xGPIOSPinTypeGPIOOutput(sD14);
    xGPIOSPinTypeGPIOOutput(sD3);
    xGPIOSPinTypeGPIOOutput(sD4);

    //
    // Disable the output, data serial in and latch register.
    //
    xGPIOSPinWrite(sA2, 1);
    xSysCtlDelay(100);
    xGPIOSPinWrite(sA2, 0);
    xSysCtlDelay(100);
    xGPIOSPinWrite(sA2, 1);

    xGPIOSPinWrite(sA0, 1);
    xGPIOSPinWrite(sA1, 0);
}

//*****************************************************************************
//
//! \brief Write data to DM163.
//!
//! \param ucData is the serial in data. 
//!
//! \note The data will parral out.
//! 
//! \return None.
//
//*****************************************************************************
void 
DotMatrixSetGamma(void)
{
    unsigned char ucData, i, j, k;

    //
    // 6 bit image data
    //
    xGPIOSPinWrite(sA0, 0);

    xGPIOSPinWrite(sA1, 0);

    //
    // Serial data in
    //
    for(i = 0; i < 8; i++)
    {
        for(j = 3; j > 0; j--)
        {
            ucData = g_ucGammaValue[j-1]<<2;
            for(k = 0; k < 6; k++)
            {
                if(ucData & 0x80)
                {
                    xGPIOSPinWrite(sD7, 1);
                }
                else
                {
                    xGPIOSPinWrite(sD7, 0);
                }
          
                ucData = ucData << 1;
                xGPIOSPinWrite(sD6, 0);
                xGPIOSPinWrite(sD6, 1);
            }
        }
    }
}

//*****************************************************************************
//
//! \brief Write data in the corresponding row and select it.
//!
//! \param ucRow is the row number in LED plane, range 0 to 7.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void
DotMatrixRunRow(unsigned char ucRow)
{
    unsigned char i, j, p, ucData;

    //
    // 8 bit image data
    //
    xGPIOSPinWrite(sA0, 1);
    xGPIOSPinWrite(sA1, 0);

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 3; j++)
        {
            ucData = dots[g_ucPageIndex][ucRow][i][2-j];
            for(p = 0; p < 8; p++)
            {
    	        if(ucData & 0x80)
                {
                    xGPIOSPinWrite(sD7, 1);
                }
                else
                {
                    xGPIOSPinWrite(sD7, 0);
                }

    	        ucData = ucData << 1;
                xGPIOSPinWrite(sD6, 0);
                xGPIOSPinWrite(sD6, 1);
            }
        }
    }
    xGPIOSPinWrite(sA1, 1);
    xGPIOSPinWrite(sA1, 0);
}

//*****************************************************************************
//
//! \brief Select the corresponding row.
//!
//! \param ucLine is line num range 0 to 7.
//!
//! \return None.
//
//*****************************************************************************
void
DotMatrixOpenLine(unsigned char ucLine)
{
    switch (ucLine)
    {
      case 0 :open_line0;
            break;
      case 1 :open_line1;
            break;
      case 2 :open_line2;
            break;
      case 3 :open_line3;
            break;
      case 4 :open_line4;
            break;
      case 5 :open_line5;
            break;
      case 6 :open_line6;
            break;
      case 7 :open_line7;
            break;
      default: close_all_line;
            break;
  }
}

#include "font.h"
unsigned char
pgm_read_byte(unsigned char *s)
{
    return *s;
}

//*****************************************************************************
//
//! \brief Show the four-dimensional arrays in LED matrix.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void
DotMatrixRunArray(void)
{
    if(g_ucLine > 7) g_ucLine = 0;
    close_all_line;
    DotMatrixRunRow(g_ucLine);
    DotMatrixOpenLine(g_ucLine);
    g_ucLine++;
}

//*****************************************************************************
//
//! \brief Show a English latter in LED matrix.
//!
//! \param ch is the latter want to show.
//! \param R is the value of RED,   Range:RED 0~255.
//! \param G is the value of GREEN, Range:RED 0~255.
//! \param B is the value of BLUE,  Range:RED 0~255.
//! \param Bias is the bias of a letter in LED Matrix, Range -7~7.
//!
//! \return None.
//
//*****************************************************************************
void
DotMatrixShowChar(char ch, unsigned char R, unsigned char G, unsigned char B, long lBias)
{
    unsigned char i, j, Page_Write, ucData;
    unsigned char chrtemp[24] = {0};

    xASSERT((lBias > -8) && (lBias < 8));

    if ((lBias > 8) || (lBias < -8))
        return;

    if(g_ucPageIndex == 0)
    {
        Page_Write = 1;
    }
    if(g_ucPageIndex == 1)
    {
        Page_Write = 0;
    }

    j = 8 - lBias;
    for(i = 0; i< 8; i++)
    {
        chrtemp[j] = pgm_read_byte(&(font8_8[ch - 32][i]));
        j++;
    }

    for(i = 0; i < 8; i++)
    {
	    ucData = chrtemp[i+8];
        for(j = 0; j < 8; j++)
        {
            if(ucData & 0x80)
            {
                dots[Page_Write][j][i][0] = B;
                dots[Page_Write][j][i][1] = G;
                dots[Page_Write][j][i][2] = R;
            }
            else
            {
                dots[Page_Write][j][i][0] = 0;
                dots[Page_Write][j][i][1] = 0;
                dots[Page_Write][j][i][2] = 0;
            }
            ucData = ucData << 1;
        }
    }
    g_ucPageIndex = Page_Write;
}

//*****************************************************************************
//
//! \brief Fill a picture in LED matrix from FLASH.
//!
//! \param Index is the index of picture in Flash.
//! 
//! \return None.
//
//*****************************************************************************
void
DotMatrixShowPic(unsigned char ucIndex)
{
    unsigned char Page_Write,i,j;

    if(g_ucPageIndex == 0)
        Page_Write = 1;
    if(g_ucPageIndex == 1)
        Page_Write = 0;

    for (i = 0; i<8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            dots[Page_Write][i][j][0] = pgm_read_byte(&(pic[ucIndex][i][j][2]));
            dots[Page_Write][i][j][1] = pgm_read_byte(&(pic[ucIndex][i][j][1]));
            dots[Page_Write][i][j][2] = pgm_read_byte(&(pic[ucIndex][i][j][0]));
        }
    }
    g_ucPageIndex = Page_Write;
}

//*****************************************************************************
//
//! !brief callback function of TIMER interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long
DotMatrixScan(void *pvCBData,  unsigned long ulEvent,
               unsigned long ulMsgParam,
               void *pvMsgData)
{
	TimerIntClear(DM_SCAN_TIMER, xTIMER_INT_CAP_EVENT);
	DotMatrixRunArray();
	return 0;
}

//*****************************************************************************
//
//! \brief Configure scanning duty cycle.
//!
//! \param ulSrcFreq is the timer clock source.
//! \param ulScanFerq(ms) is the scanning duty cycle.
//!
//! \return None.
//
//*****************************************************************************
void 
DotMatrixScanTimerInit(unsigned long ulSrcFreq, unsigned long ulScanFerq)
{
    unsigned long ulMatchVal = (ulSrcFreq * DM_SCAN_FREQ) / (DM_SCANDIV_VALUE * (DM_SCANPSR_VALUE + 1) * 1000);

    //
    // Set the timer clock
    //
//    xSysCtlPeripheralClockSourceSet(DM_SCAN_CLKSRC, DM_SCANDIV_VALUE);

    xSysCtlPeripheralEnable2(DM_SCAN_TIMER);

    //
    // Clear the status first
    //
    TimerIntClear(DM_SCAN_TIMER, xTIMER_INT_CAP_EVENT);
    while(xTimerStatusGet(DM_SCAN_TIMER, DM_SCAN_CHANNEL, xTIMER_INT_CAP_EVENT));

    // 
    // Config as periodic mode
    //        
    xTimerInitConfig(DM_SCAN_TIMER, DM_SCAN_CHANNEL, xTIMER_MODE_PERIODIC, ulScanFerq);
    xTimerPrescaleSet(DM_SCAN_TIMER, DM_SCAN_CHANNEL, DM_SCANPSR_VALUE);
    xTimerMatchSet(DM_SCAN_TIMER, DM_SCAN_CHANNEL, ulMatchVal);
    xTimerIntEnable(DM_SCAN_TIMER, DM_SCAN_CHANNEL, xTIMER_INT_CAP_EVENT);
    xTimerIntCallbackInit(DM_SCAN_TIMER, DotMatrixScan);
//    xIntEnable(xSysCtlPeripheralIntNumGet(DM_SCAN_TIMER));
    xIntEnable(xINT_TIMER1);

    //
    // Start the timer
    //
    xTimerStart(DM_SCAN_TIMER, DM_SCAN_CHANNEL);
}
