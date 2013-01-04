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
#include "CAT93Cx6.h"

int main()
{
    unsigned long address;
	unsigned long dat;

	xSysCtlClockSet(80000000, SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
	
	CAT93Cx6_EraseToAll();
	address = 2;
	dat = 0;
	dat = CAT93Cx6_ReadFromAddress(address);
	dat = 0x1234;
	CAT93Cx6_WriteToAddress(address, dat);
	dat = 0;
	dat = CAT93Cx6_ReadFromAddress(address);
	CAT93Cx6_EraseToAddress(address);
	dat = 0;
	dat = CAT93Cx6_ReadFromAddress(address);
	dat = 0x5678;
	CAT93Cx6_WriteToAll(dat);
	address = 8;
	dat = 0;
	dat = CAT93Cx6_ReadFromAddress(address);

	while(1)
	{
	}
}
