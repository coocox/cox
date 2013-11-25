
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"

extern int test0,test1;

#define SSSSSSSS "a\0b\0"
int main()
{
    xSysCtlClockSet(12000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_USBD);
    test0++;
    test1++;

 	while(1);
}


