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
unsigned long ulMode[8] = {RTC_TIME_TICK_1, RTC_TIME_TICK_1_2, RTC_TIME_TICK_1_4,
                           RTC_TIME_TICK_1_8, RTC_TIME_TICK_1_16, RTC_TIME_TICK_1_32,
                           RTC_TIME_TICK_1_64, RTC_TIME_TICK_1_128};
unsigned long xRTCCallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
   //xIntMasterDisable();
    ulj++;
    UARTBufferWrite(UART0_BASE, "RTC tick interrupt test!", sizeof("RTC tick interrupt test!")-1);
    return 0;
}
void RTCTickInt()
{
    
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;

    SysCtlDelay(10000);

    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
                                             UART_CONFIG_STOP_ONE | 
                                               UART_CONFIG_PAR_NONE));
    
   

    RTCTimeInit();
    
    tTime1.ulSecond = 40;     
    
    tTime1.ulMinute = 20; 
    
    tTime1.ulHour = 17; 
    
    tTime1.ulMDay = 11;  
    
    tTime1.ulMonth = 8;   
    
    tTime1.ulYear = 2011;    
    
    tTime1.ulWDay = 3;   

    tTime1.ulFormat = RTC_TIME_24H;
    
    //
    // Writes current time to corresponding register.
    //
    RTCTimeWrite(&tTime1, ulTimeAlarm[0]);
    
    //
    // Sets Tick interrupt.
    //
    RTCTickModeSet(ulMode[0]);
   

    RTCIntCallbackInit(xRTCCallback);
    
        //
    // Enables tick interrupt.
    //
    RTCIntEnable(RTC_INT_TIME_TICK);
    
    xIntEnable(INT_RTC);
    xIntMasterEnable();
    while(ulj < 1);
    xIntMasterDisable();
    
 }


