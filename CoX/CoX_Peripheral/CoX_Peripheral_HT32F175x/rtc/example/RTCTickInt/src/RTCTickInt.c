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
unsigned long ulCount = 0;
unsigned long ulTimeAlarm[2] = {RTC_TIME_CURRENT, RTC_TIME_ALARM};
unsigned long xRTCCallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    ulCount++;
    UARTBufferWrite(UART0_BASE, "RTC tick interrupt test!", sizeof("RTC tick interrupt test!")-1);
    return 0;
}
void RTCTickInt()
{
    
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART0RX, PA8);
    xSPinTypeUART(UART0TX, PA9);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_HCLK);
    xSysCtlPeripheralClockSourceSet(xSYSCTL_RTC_EXTSL, 15);

    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                             UART_CONFIG_STOP_ONE | 
                                             UART_CONFIG_PAR_NONE));

    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    
    tTime1.ulSecond = 40;     
    
    tTime1.ulMinute = 20; 
    
    tTime1.ulHour = 17; 
    
    tTime1.ulMDay = 11;  
    
    tTime1.ulMonth = 8;   
    
    tTime1.ulYear = 2011;    
    
    tTime1.ulWDay = 3;   
    
    //
    // Writes current time to corresponding register.
    //
    RTCTimeWrite(&tTime1, ulTimeAlarm[0]);
   

    RTCIntCallbackInit(xRTCCallback);
    
    //
    // Enables tick interrupt.
    //
    RTCIntEnable(RTC_INT_TIME_TICK);
    
    xIntEnable(INT_RTC);
    xIntMasterEnable();
    while(ulCount < 1);
    xIntMasterDisable();
 }


