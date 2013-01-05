#include "coshining.h"
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
	
    sPinTypeUART(sUART_DBG_BASE); 
    //xSPinTypeUART(UART0RX,PD0);
    //xSPinTypeUART(UART0TX,PD1);
    xUARTConfigSet(sUART_DBG_BASE, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    xUARTEnable(sUART_DBG_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
	
    xUARTCharPut(xUART0_BASE, 'H');
    xUARTCharPut(xUART0_BASE, 'e');	
    xUARTCharPut(xUART0_BASE, 'l');
    xUARTCharPut(xUART0_BASE, 'l');	
    xUARTCharPut(xUART0_BASE, 'o');
    xUARTCharPut(xUART0_BASE, ',');	
    xUARTCharPut(xUART0_BASE, ' ');
    xUARTCharPut(xUART0_BASE, 'C');	
    xUARTCharPut(xUART0_BASE, 'o');
    xUARTCharPut(xUART0_BASE, 'S');	
    xUARTCharPut(xUART0_BASE, 'H');
    xUARTCharPut(xUART0_BASE, 'i');		
    xUARTCharPut(xUART0_BASE, 'n');	
    xUARTCharPut(xUART0_BASE, 'i');
    xUARTCharPut(xUART0_BASE, 'n');	
    xUARTCharPut(xUART0_BASE, 'g');
    xUARTCharPut(xUART0_BASE, '\n');	

    while(1)
    {
        xGPIOSPinWrite(sD13, 1);
        xSysCtlDelay(1000000);
        xGPIOSPinWrite(sD13, 0);
        xSysCtlDelay(1000000);
    }
}
