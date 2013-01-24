#include "xhw_types.h"
#include "xhw_memmap.h"
#include "cookie.h"
#include "xgpio.h"
#include "xuart.h"
#include "xsysctl.h"
#include "T00006x.h"
#include "stdio.h"

void DeltaAngleGet()
{
	tLPR5150ALData g_XYAxisCurrentVoltage;
	tLPR5150ALData g_XYAxisNullVoltage;
	tLPR5150ALData g_XYAxisAngle;
	tLPR5150ALData g_XYAxisRate;

    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlDelay(1000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD13));
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);

    sPinTypeUART(sUART_DBG_BASE);
    xUARTConfigSet(sUART_DBG_BASE, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    xUARTEnable(sUART_DBG_BASE, (UART_BLOCK_UART | UART_BLOCK_RX));

    //automatically added by CoIDE
	//ADConvert();


    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);

    LPR5150ALInit();

	while(1)
    {
		g_XYAxisAngle = LPR5150ALXYAxisAngleGet();
		printf("The roll angle is: %f   ", g_XYAxisAngle.fXAxisData);
		printf("The pitch angle is: %f \r\n", g_XYAxisAngle.fYAxisData);
		//DelayMS(500);
    }
}
