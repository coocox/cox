#include "cookie.h"
#include "xgpio.h"
#include "xuart.h"
#include "xsysctl.h"

#define MAX_TICK 0xFFFFF
static void PrintStr(const char * pStr)
{
	while(*pStr != '\0')
	{
		xUARTCharPut(USART3_BASE, *pStr++);
	}
}

int main()
{
    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(1000);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
	
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOB);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOC);
    xSPinTypeUART(UART3TX, PC10);
    xSPinTypeUART(UART3RX, PC11);

	
    //
    // Configure UART1 115200 8-N-1
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART3);
    xUARTConfigSet(USART3_BASE, 115200, xUART_CONFIG_WLEN_8 |
    		                            xUART_CONFIG_STOP_1 |
    		                            xUART_CONFIG_PAR_NONE);
    xUARTEnable(USART3_BASE, xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX);
	
    PrintStr("Embedded Pi Board UART Test Begin\r\n");

    while(1)
    {
    	xUARTCharPut(USART3_BASE, 0x05);
//    	xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 1 );
//        PrintStr(".");
//        xSysCtlDelay(10*MAX_TICK);
//
//        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 0 );
//        PrintStr(".");
//        xSysCtlDelay(10*MAX_TICK);
//
//        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 1 );
//        PrintStr(".");
//        xSysCtlDelay(10*MAX_TICK);
//
//        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 0 );
//        PrintStr(".");
//        xSysCtlDelay(10*MAX_TICK);

    }
}
