#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xi2c.h"
#include "PCF8591.h"

int test(void)
{
        unsigned char SendBuf[] = {0x40, 0x00, 0x0f, 0x80, 0xf0, 0xff};
	    unsigned char ucdata[11] = {0x00, 0x0f, 0x80, 0xf0, 0xff,
	    0x00, 0x0f, 0x80, 0xf0, 0xff,0x78};

	    char data[11] = {0x00, 0x0f, 0x80, 0xf0, 0xff,
	        0x00, 0x0f, 0x80, 0xf0, 0xff,0x78};

	    float vol[11] = {0.0};
	    unsigned long SendLength = 11;

	    unsigned char suc = 0;
	    int i,j;

	    PCF8591_Init(50000);

	    for(i=0; i<SendLength; i++)
	    {
	       SendBuf[1] = ucdata[i];
	       suc = PCF8591_DA_OUT(SendBuf,2);
	       for(j=0;j<1000000;j++);
	    }


	    PCF8591_AD_Trans(data, 11 ,PCF8591_INPUT_FOUR_SINGLE |
	                    PCF8591__INPUT_INC_ENABLE |
	                    PCF8591_CHANNEL_0);

	    PCF8591_AD_Vol(vol, data, 11);
}
