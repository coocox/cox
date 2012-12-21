#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xgpio.h"
#include "xhw_gpio.h"
#include "xhw_uart.h"
#include "xuart.h"
#include "xrtc.h"
#include "xhw_rtc.h"

tTime  tTime1;
unsigned long ulj = 0;
unsigned long ulTimeAlarm[2] = {RTC_TIME_CURRENT, RTC_TIME_ALARM};

unsigned long xRTCCallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
   //xIntMasterDisable();
    ulj++;
    UARTBufferWrite(xUART1_BASE, "RTC tick interrupt test!", sizeof("RTC tick interrupt test!")-1);
    return 0;
}

void RTCTickInt()
{   
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

		xSysCtlPeripheralEnable(SYSCTL_PERIPH_PWR);

		xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
		
		SysCtlBackupAccessEnable();
	
    SysCtlLSEConfig(SYSCTL_LSE_OSC_EN);
    SysCtlPeripheralClockSourceSet(SYSCTL_RTC_LSE); 
		xSysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
	
    SysCtlDelay(10000);
		
    xSPinTypeUART(UART1RX,PA10);   
    xSPinTypeUART(UART1TX,PA9);
		xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
		xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);	 
    xUARTConfigSet(xUART1_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                          UART_CONFIG_STOP_ONE | 
                                            UART_CONFIG_PAR_NONE));		
		xUARTEnable(xUART1_BASE, UART_BLOCK_UART | UART_BLOCK_RX | UART_BLOCK_TX);

		UARTBufferWrite(xUART1_BASE, "usart init is ok!", sizeof("usart init is ok!")-1);
		
    RTCTimeInit(0X7FFF);
			
    tTime1.ulSecond = 20;     
    
    tTime1.ulMinute = 10; 
    
    tTime1.ulHour = 11; 
    
    tTime1.ulMDay = 13;  
    
    tTime1.ulMonth = 6;   
    
    tTime1.ulYear = 2012;    
    
    tTime1.ulWDay = 3;   
    
    //
    // Writes current time to corresponding register.
    //
    RTCTimeWrite(&tTime1, ulTimeAlarm[0]);
		
		SysCtlDelay(10000);

    RTCIntCallbackInit(xRTCCallback);  
		
    //
    // Enables tick interrupt.
    //
    RTCIntEnable(RTC_INT_TIME_TICK);
		
    xIntEnable(INT_RTC);
    xIntMasterEnable();
    while(ulj < 2);
    xIntMasterDisable(); 
		RTCTimeRead(&tTime1, ulTimeAlarm[0]);
 }
