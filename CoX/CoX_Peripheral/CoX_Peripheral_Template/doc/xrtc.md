\page xRTC_page xRTC page 

[TOC]




xRTC document
======
本篇文章主要讲解，CoX.RTC的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）
 
xRTC Interrupt Type  {#xRTC_INT_Type_md}
================
这个参数定义中断的类型：对于RTC来说，中断有三种类型，时间中断（CoX将这个中断定义为一秒）、闹钟中断和溢出中断。
参数的形式为固定的宏名称： 
 - \ref xRTC_INT_SECOND  
 - \ref xRTC_INT_ALARM 
 - \ref xRTC_INT_OVERFLOW
 
这个参数是 API \ref xRTCIntEnable() 和 API \ref xRTCIntDisable() 的 ulIntType参数。
有些系列实现了这三个功能，然后有些系列只有前两个功能，下面是各个系列的实现的情况。

|  xRTC Interrupts |LPC17xx|STM32F1xx|NUC1xx/NUC2xx/M051/Mini51|KLx      |HT32F125x|HT32F175x|
|:----------------:|:-----:|:-------:|:-----------------------:|:-------:|:-------:|:-------:|
|  xRTC_INT_SECOND |**Y**  |  **Y**  |          **Y**          |  **Y**  |  **Y**  |  **Y**  |
|  xRTC_INT_ALARM  |**Y**  |  **Y**  |          **Y**          |  **Y**  |  **Y**  |  **Y**  |
|xRTC_INT_OVERFLOW | *N*   |  **Y**  |           *N*           |  **Y**  |  **Y**  |  **Y**  |


xRTC Interrupt Event   {#xRTC_INT_Event_md}
========
这个参数是中断的事件，当RTC发生时 用这个参数来判断 当前的 中断源 是什么。
中断事件和类型，基本保持一致。
参数的形式为固定的宏名称： 
 - \ref xRTC_EVENT_SECOND  
 - \ref xRTC_EVENT_ALARM 
 - \ref xRTC_EVENT_OVERFLOW

这个将在回调函数中使用，以判断已经发生的中断源。

有些系列实现了这三个功能，然后有些系列只有前两个功能，下面是各个系列的实现的情况。

|  xRTC Event        |LPC17xx|STM32F1xx|NUC1xx/NUC2xx/M051/Mini51|KLx      |HT32F125x|HT32F175x|
|:------------------:|:-----:|:-------:|:-----------------------:|:-------:|:-------:|:-------:|
|  xRTC_EVENT_SECOND |**Y**  |  **Y**  |          **Y**          |  **Y**  |  **Y**  |  **Y**  |
|  xRTC_EVENT_ALARM  |**Y**  |  **Y**  |          **Y**          |  **Y**  |  **Y**  |  **Y**  |
|xRTC_EVENT_OVERFLOW | *N*   |  **Y**  |           *N*           |  **Y**  |  **Y**  |  **Y**  |


xRTC Day Week    {#xRTC_Day_Week_md}
========
这组宏用于定义星期，枚举 星期日 到 星期六

参数的形式为固定的宏名称： 
 - \ref xRTC_WEEK_SUNDAY  
 - \ref xRTC_WEEK_MONDAY 
 - \ref xRTC_WEEK_TUESDAY
 - \ref xRTC_WEEK_WEDNESDAY
 - \ref xRTC_WEEK_THURSDAY
 - \ref xRTC_WEEK_FRIDAY
 - \ref xRTC_WEEK_SATURDAY

这组红将作为 xtTime.ulWDay 参数传入 函数 \ref xRTCTimeRead(), \ref xRTCTimeWrite()

|  tTime.ulWDay            |         All Series     |
|--------------------------|------------------------|
|  xRTC_WEEK_SUNDAY        |            Y           |
|  xRTC_WEEK_MONDAY        |            Y           |
|  xRTC_WEEK_TUESDAY       |            Y           |
|  xRTC_WEEK_WEDNESDAY     |            Y           |
|  xRTC_WEEK_THURSDAY      |            Y           |
|  xRTC_WEEK_FRIDAY        |            Y           |
|  xRTC_WEEK_SATURDAY      |            Y           |


xRTC Year Offset     {#xRTC_Year_Offset_md}
=======

由于有些 RTC 实际上就是一个 32 位的计数器，所以为了将这个鬼计数器转化为具体的时间，需要
一个转换过程，而 32 位数据能表示的年份有限（最多能表示136年多），所以为了能表示当前公历（比如2014）
需要定义一个 固定偏移量。比如，偏移量为2000，则当计数值为14年时，表示2014年1月1日0时0分0秒。
这个偏移将影响 32 位的计数器 类型RTC的时间调节范围。

参数的形式为固定的宏名称： 
 - \ref xRTC_YEAR_OFFSET

时间的调节分为   xRTC_YEAR_OFFSET <= time <= xRTC_YEAR_OFFSET+136

CoX 定义了一个默认值为2000

下面是各个系列的实现情况
|  xRTC_Year_Offset        | LPC17xx |STM32F1xx|NUC1xx/NUC2xx/M051/Mini51|KLx      |HT32F125x|HT32F175x|
|--------------------------|---------|:-------:|:-----------------------:|:-------:|:-------:|:-------:|
|  xRTC_YEAR_OFFSET        |    N    |  **Y**  |          **Y**          |  **Y**  |  **Y**  |  **Y**  |


xRTC Time Type     {#xRTC_Time_Type_md}
======
在设置 当前时间 和 设置 闹钟的时候，由于设置方式一样，所以 用了一个参数表示，当前究竟是什么操作（是在设置 时间 还是闹钟）？

参数的形式为固定的宏名称： 
 - \ref xRTC_TIME_CURRENT
 - \ref xRTC_TIME_ALARM

|  ulTimeAlarm             |         All Series     |
|--------------------------|------------------------|
|  xRTC_TIME_CURRENT       |            Y           |
|  xRTC_TIME_ALARM         |            Y           |


xRTC Exported Types    {#xRTC_Exported_Types_md}  
==========
CoX 为RTC定义了一个 xtime 的结构体，该结构体包含了组成 时间的 年月日 时分秒 和星期。


xRTC API   {#xRTC_Exported_APIs_md}
=====

|      xRTC API            |         All Series     |
|--------------------------|------------------------|
| \ref xRTCTimeInit        |            Y           |
| \ref xRTCTimeRead        |            Y           |
| \ref xRTCTimeWrite       |            Y           |
| \ref xRTCIntEnable       |            Y           |
| \ref xRTCIntCallbackInit |            Y           |
| \ref xRTCIntDisable      |            Y           |
| \ref xRTCStart           |            Y           |
| \ref xRTCStop            |            Y           |

\note  xRTCTimeInit 在实现的时候要将RTC 的时间 中断间隔设置为一秒。

\note 有些系列 不需要 xRTCStart 和 xRTCStop，那么 这两个函数空实现即可。



~~~{.c}
xtTime  tTime1;
unsigned long xRTCCallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    if(ulMsgParam & xRTC_EVENT_SECOND)
    {
        xRTCTimeRead(&tTime1, xRTC_TIME_CURRENT);
        printf("RTC interrupt\r\n");
    }
    return 0;
}
void RTCTickInt()
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_RTC);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_RTC);  

    xRTCTimeInit();
    
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
    xRTCTimeWrite(&tTime1, xRTC_TIME_CURRENT);
    
   
    xRTCIntCallbackInit(xRTCCallback);
    
    //
    // Enables tick interrupt.
    //
    xRTCIntEnable(RTC_INT_TIME_TICK);
    
    xIntEnable(INT_RTC);

    while(1);
    
}
~~~

