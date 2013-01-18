#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xcore.h"

#include "LCD4884.h"
#include "bmp.h"

char const ucCharacterSet[96] = " !\"#$%&'()*+,-./0123456789:;<=>?@"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_\\abcdefghijklmnopqrstuvwxyz{|}~";
//*****************************************************************************
//
//! \brief This function is to test LCD4884.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void LCD4884_example(void)
{
	unsigned char ucI;
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    LCD4884Init();
    while(1)
    {
    	if(ucI++ % 2 == 1)
    	{
           //LCD4884VideoInverse();
    	}
    	LCD4884BmpPixelDraw(0,0,bmp,84,48);
    	LCD4884ScreenClear();
        LCD4884XYSet(0,0);

        LCD4884StringWrite(0,0,"Following disp as normal!");
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();

        LCD4884StringWrite(0,0,"Coocox");
        LCD4884StringWrite(1,0,"Cookie");
        LCD4884GB1616Write(0,36,"点");
        LCD4884GB1616Write(0,52,"然");
        LCD4884GB1616Write(0,68,"嵌");
        LCD4884GB1616Write(2,0,"入");
        LCD4884GB1616Write(2,16,"式");
        LCD4884GB1616Write(2,32,"开");
        LCD4884GB1616Write(2,48,"源");
        LCD4884GB1616Write(2,64,"之");
        LCD4884GB1616Write(4,0,"火");
        LCD4884GB1616Write(4,16,"一");
        LCD4884GB1616Write(4,32,"起");
        LCD4884GB1616Write(4,48,"加");
        LCD4884GB1616Write(4,64,"油");
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();
        LCD4884BigStringWrite(0,0,(char *)ucCharacterSet);
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();
        LCD4884StringWrite(0,0,(char *)ucCharacterSet);
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();

        LCD4884IStringWrite(0,0,"Following disp as invert,which function with I!");
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();

        LCD4884IStringWrite(0,0,"Coocox");
        LCD4884IStringWrite(1,0,"Cookie");
        LCD4884IGB1616Write(0,36,"点");
        LCD4884IGB1616Write(0,52,"然");
        LCD4884IGB1616Write(0,68,"嵌");
        LCD4884IGB1616Write(2,0,"入");
        LCD4884IGB1616Write(2,16,"式");
        LCD4884IGB1616Write(2,32,"开");
        LCD4884IGB1616Write(2,48,"源");
        LCD4884IGB1616Write(2,64,"之");
        LCD4884IGB1616Write(4,0,"火");
        LCD4884IGB1616Write(4,16,"一");
        LCD4884IGB1616Write(4,32,"起");
        LCD4884IGB1616Write(4,48,"加");
        LCD4884IGB1616Write(4,64,"油");
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();
        LCD4884IBigStringWrite(0,0,(char *)ucCharacterSet);
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();
        LCD4884IStringWrite(0,0,(char *)ucCharacterSet);
        xSysCtlDelay(10000000);
        LCD4884ScreenClear();
    }
}
