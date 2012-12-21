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

unsigned long xRTCSCallback(void *pvCBData, unsigned long ulEvent,
                            unsigned long ulMsgParam, void *pvMsgData)                                                        
{
    ulj++;
    return 0;
}

void RTCTickInt()
{  
    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(1000000);
    
    //
    // Enable GPIO/UART Clock
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOC);

    //
    // Remap UART pin to GPIO Port
    //
    xSPinTypeUART(UART1RX,PC3);
    xSPinTypeUART(UART1TX,PC4);
   
    //
    // Sets the configuration of UART Receive/Transmit 
    //
    xUARTConfigSet(xUART1_BASE, 9600, UART_CONFIG_WLEN_8   | 
                                      UART_CONFIG_PAR_NONE |
                                      UART_CONFIG_STOP_1);
    
    //
    // Enable UART Receive/Transmit
    //
    xUARTEnable(xUART1_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));

    RTCTimeInit();
    
    tTime1.ulSecond = 40;     
    
    tTime1.ulMinute = 20; 
    
    tTime1.ulHour = 17; 
    
    tTime1.ulMDay = 11;  
    
    tTime1.ulMonth = 8;   
    
    tTime1.ulYear = 2011;    
    
    tTime1.ulWDay = 4;   

    tTime1.ulFormat = RTC_TIME_24H;
    
    //
    // Writes current time to corresponding register.
    //
    RTCTimeWrite(&tTime1, ulTimeAlarm[0]); 

    RTCIntCallbackInit(RTC_INT_TIME_TICK, xRTCSCallback);
    
    //
    // Enables tick interrupt.
    //
    RTCIntEnable(RTC_INT_TIME_TICK);
    
    xIntEnable(INT_RTCS);
    xIntMasterEnable();
	RTCStart();
	
    while(ulj < 1);
    xIntMasterDisable();  
 }
