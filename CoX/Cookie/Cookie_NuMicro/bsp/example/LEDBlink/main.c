#include "cookie.h"
#include "xgpio.h"
#include "xuart.h"
#include "xsysctl.h"

int main()
{
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlDelay(1000);
	
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);	
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD13));   
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);

    while(1)
    {
        xGPIOSPinWrite(sD13, 1);
        xSysCtlDelay(1000000);
        xGPIOSPinWrite(sD13, 0);
        xSysCtlDelay(1000000);
    }
}
