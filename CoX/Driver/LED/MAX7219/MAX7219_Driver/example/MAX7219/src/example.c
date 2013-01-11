#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xspi.h"
#include "MAX7219.h"

int test(void)
{
	unsigned short data[] = {0x0108, 0x0207, 0x0306, 0x0405,
                       0x0504, 0x0603, 0x0702, 0x0801};
	int i,j;
	int intensity=0x0f;

    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(36000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);

	MAX7219_Init();

	for(i=0;i<8;i++)
	{
		MAX7219_Write(data[i]>>8,data[i]);
	}

	while(1)
	{
		if(intensity>0x0f)
			intensity = 0;
		for(i=0;i<300000;i++);
		MAX7219_Write(MAX7219_INTENSITY_ADDR, intensity);
		intensity++;
	}
}
