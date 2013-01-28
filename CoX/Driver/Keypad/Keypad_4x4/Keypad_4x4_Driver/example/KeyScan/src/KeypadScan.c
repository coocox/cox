#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xgpio.h"
#include "xuart.h"
#include "xsysctl.h"
#include "keypad_4x4.h"
#include "stdio.h"

void KeypadScan(void)
{
	unsigned char ucKeyScan, ucPin4;

    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlDelay(1000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOE);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PA7));
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);

    xSPinTypeUART(UART0TX, PA2);
    xUARTConfigSet(xUART0_BASE, 115200, (xUART_CONFIG_WLEN_8 | xUART_CONFIG_STOP_1 | xUART_CONFIG_PAR_NONE));
    xUARTEnable(xUART0_BASE, (xUART_BLOCK_UART | xUART_BLOCK_RX));

    Keypad4x4Init();

	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_0));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_4));

    while(1)
    {
    	ucKeyScan = Keypad4x4Scan();
    	printf("The key pressed is: %d \r\n", ucKeyScan);
    	xSysCtlDelay(1000000);
    }
}

