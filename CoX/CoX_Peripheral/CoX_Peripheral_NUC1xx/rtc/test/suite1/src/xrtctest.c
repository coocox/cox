//*****************************************************************************
//
//! @page xrtc_testcase xrtc register test
//!
//! File: @ref xrtctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xrtc sub component.<br><br>
//! - \p Board: NUC140 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xrtc_register
//! .
//! \file xrtctest.c
//! \brief xrtc test source file
//! \brief xrtc test header file <br>
//
//*****************************************************************************
#include "test.h"
#include "xrtc.h"
#include "xhw_rtc.h"
unsigned long uli = 0, ulj = 0;
unsigned long ulTimeAlarm[2] = {RTC_TIME_CURRENT, RTC_TIME_ALARM};

tTime tTime1, tTime2;

unsigned long xRTCCallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    if(1==(xHWREG(RTC_RIIR)) & 1)
    {
        RTCTimeRead(&tTime1, ulTimeAlarm[0]);
    
    }
    TestEmitToken('a');
    return 0;
}

//*****************************************************************************
//
//! \page test_xrtc test_xrtc
//!
//! <h2>Description</h2>
//! Test xrtc. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of xrtc001  test.
//!
//! \return the desccription of the xrtc001 test.
//
//*****************************************************************************
static char* xrtc001GetTest(void)
{
  return "xrtc[001]: xrtc initalization test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc001Setup(void)
{
  
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc001TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xrtc001 test main body for rtc initialization.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc001Execute_Init()
{
   //
   // RTC initialization.
   //
   TestAssert(1 == RTCTimeInit() ,
		  "xrtc API \"RTCTimeInit\" error!");  
}

//*****************************************************************************
//
//! \brief xrtc001 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc001Init = {
        xrtc001GetTest,
        xrtc001Setup,
        xrtc001TearDown,
        xrtc001Execute_Init 
};

//*****************************************************************************
//
//! \brief Get the Test description of xrtc002 test.
//!
//! \return the desccription of the xrtc002 test.
//
//*****************************************************************************
static char* xrtc002GetTest(void)
{
    return "xrtc[002]: xrtc time frequency compensation test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc002Setup(void)
{

}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc002TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xrtc002 test for rtc frequency compensation .
//!
//! \return None.
//
//*****************************************************************************
static void xrtc002Execute_FCset()
{
    unsigned long ulFrequency[3] = {3276100, 3276550, 3277699};
    unsigned long ulFCR[3] = {0, 0x41E , 0xF3B};
    
    for(uli = 0; uli < 3; uli ++)
    {
        //
        // Sets frequency.
        //
        RTCFrequencyCompensationSet(ulFrequency[uli]);
        
        for(ulj = 0; ulj < 0xffff; ulj ++);
        
        //
        // Tests RTCFrequencyCompensationSet API.
        //
        while(!RTCWriteEnable());
        TestAssert(ulFCR[uli] == (xHWREG(RTC_FCR) & 0x00000F3F),
                   "xrtc API \" RTCFrequencyCompensationSet\" error!");
    }
    
}

//*****************************************************************************
//
//! \brief xrtc002 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc002FCset = {
        xrtc002GetTest,
        xrtc002Setup,
        xrtc002TearDown,
        xrtc002Execute_FCset
};


//*****************************************************************************
//
//! \brief Get the Test description of xrtc003 test.
//!
//! \return the desccription of the xrtc003 test.
//
//*****************************************************************************
static char* xrtc003GetTest(void)
{
    return "xrtc[003]: xrtc tick mode test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc003Setup(void)
{

}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc003TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xrtc003 test for rtc mode set.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc003Execute_ModeTest()
{
    unsigned long ulMode[8] = {RTC_TIME_TICK_1, RTC_TIME_TICK_1_2, RTC_TIME_TICK_1_4,
                       RTC_TIME_TICK_1_8, RTC_TIME_TICK_1_16, RTC_TIME_TICK_1_32,
                       RTC_TIME_TICK_1_64, RTC_TIME_TICK_1_128};     
   
    for(ulj = 0; ulj < 8; ulj ++)
    {
        RTCTickModeSet(ulMode[ulj]);
       
        for(uli = 0; uli < 0xffff; uli ++);
        
        while(!RTCWriteEnable());
        
        TestAssert(ulMode[ulj] == (xHWREG(RTC_TTR) & 0x00000007), 
                     "xrtc API \"RTCTickModeSet\" error!");
    }
}

//*****************************************************************************
//
//! \brief xrtc003 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc003Mode = {
        xrtc003GetTest,
        xrtc003Setup,
        xrtc003TearDown,
        xrtc003Execute_ModeTest
};

//*****************************************************************************
//
//! \brief Get the Test description of xrtc004 test.
//!
//! \return the desccription of the xrtc004 test.
//
//*****************************************************************************
static char* xrtc004GetTest(void)
{
    return "xrtc[004]: xrtc interrupt test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc004Setup(void)
{

}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc004TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xrtc004 test for rtc interrupt.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc004Execute_Int()
{    
    tTime2.ulSecond = 40;     
    
    tTime2.ulMinute = 20; 
    
    tTime2.ulHour = 17; 
    
    tTime2.ulMDay = 11;  
    
    tTime2.ulMonth = 8;   
    
    tTime2.ulYear = 2011;    
    
    tTime2.ulWDay = 3;   

    tTime2.ulFormat = RTC_TIME_24H;
    
    //
    // Writes current time to corresponding register.
    //
    RTCTimeWrite(&tTime2, ulTimeAlarm[0]);
      
    //
    // Alarm interrupt after 10 seconds.
    //
    tTime2.ulSecond +=10;
    
    //
    // Writes current time to corresponding register.
    //
    RTCTimeWrite(&tTime2, ulTimeAlarm[1]);
    
    for(ulj = 0; ulj < 0xffff; ulj ++);
    
    while(!RTCWriteEnable());
    
    RTCTimeRead(&tTime1, ulTimeAlarm[1]);
    
    TestAssert(2011 == tTime1.ulYear && 8 == tTime1.ulMonth
           && 11 ==  tTime1.ulMDay && RTC_TIME_24H == tTime1.ulFormat 
          && 17 == tTime1.ulHour  && 20 == tTime1.ulMinute 
          && 50 == tTime1.ulSecond
                ,"xrtc API \" RTCTimeWrite()\" or \"RTCTimeRead()\" error!");
    
    
    RTCIntCallbackInit(xRTCCallback);
    
    xIntEnable(INT_RTC);
    xIntMasterEnable();
    
    //
    // Enables alarm interrupt.
    //
    RTCIntEnable(RTC_INT_ALARM);
    
    TestAssertQBreak("a","Alarm interrupt failed!", 0xffffffff);
    
    for(ulj = 0; ulj < 0xffff; ulj ++);
       
    TestAssert(2011 == tTime1.ulYear && 8 == tTime1.ulMonth
           && 11 ==  tTime1.ulMDay && RTC_TIME_24H == tTime1.ulFormat 
           && 17 == tTime1.ulHour  && 20 == tTime1.ulMinute 
           && 50 == tTime1.ulSecond
                 ,"xrtc API \" RTCTimeWrite()\" or \"RTCTimeRead()\" error!"); 
    
    //
    // Disables alarm interrupt.
    //
    RTCIntDisable(RTC_INT_ALARM);
   
    xIntMasterEnable();
    //
    // Sets second interrupt.
    //
    RTCTickModeSet(RTC_TIME_TICK_1);
   
    //
    // Enables tick interrupt.
    //
    RTCIntEnable(RTC_INT_TIME_TICK);
    
    TestAssert(RTC_INT_TIME_TICK == ( xHWREG(RTC_RIER) & 0x00000003),
		  "xrtc API \"RTCIntEnable\" error!");
    
    TestAssertQBreak("a","Tick interrupt failed!",0xffffffff);
    
    RTCIntDisable(RTC_INT_TIME_TICK);
    
}

//*****************************************************************************
//
//! \brief xrtc004 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc004Int = {
        xrtc004GetTest,
        xrtc004Setup,
        xrtc004TearDown,
        xrtc004Execute_Int
};

//*****************************************************************************
//
//! \brief Get the Test description of xrtc005test.
//!
//! \return the desccription of the xrtc005 test.
//
//*****************************************************************************
static char* xrtc005GetTest(void)
{
    return "xrtc[005]: xrtc wake up test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc005Setup(void)
{

}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc005TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xrtc005 test for rtc wake up.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc005Execute_WakeUp()
{
    RTCWakeupEnable();
    
    for(uli = 0; uli < 0xffff; uli ++);
    
    while(!RTCWriteEnable());
    
    //
    // Tests RTCWakeupEnable API.
    //
    TestAssert(RTC_TTR_TWKE == ( xHWREG(RTC_TTR) & RTC_TTR_TWKE),
		      "xrtc API \"RTCIntEnable\" error!");
    
    RTCWakeupDisable();
    
    for(uli = 0; uli < 0xffff; uli ++);
   
    while(!RTCWriteEnable());
 
    //
    // Tests RTCWakeupDisable API.
    //
    TestAssert(0 == (xHWREG(RTC_TTR) & RTC_TTR_TWKE),
		       "xrtc API \"RTCIntEnable\" error!");
}
//*****************************************************************************
//
//! \brief xrtc005 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc005WakeUp = {
        xrtc005GetTest,
        xrtc005Setup,
        xrtc005TearDown,
        xrtc005Execute_WakeUp
};

//*****************************************************************************
//
//! \brief Get the Test description of xrtc006test.
//!
//! \return the desccription of the xrtc006 test.
//
//*****************************************************************************
static char* xrtc006GetTest(void)
{
    return "xrtc[006]: xrtc RTCIsLeapYear API test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc006test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc006Setup(void)
{

}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc006TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xrtc006 test for rtc  RTCIsLeapYear API.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc006Execute_IsLeapYear()
{
    unsigned long ulTestYear[4] = {2000, 2004, 2100, 2036};
    xtBoolean xFlag[4] = {1, 1, 0, 1};
  
    tTime time[4];
  
    for(uli = 0; uli < 4; uli ++)
    {
        //
        // Sets the value of time structure that will be test.
        //
        time[uli].ulYear = ulTestYear[uli];
        
        time[uli].ulSecond = 40;     
    
        time[uli].ulMinute = 10; 
    
        time[uli].ulHour = 17; 
    
        time[uli].ulMDay = 11;  
    
        time[uli].ulMonth = 8;      
    
        time[uli].ulWDay = 3;   

        time[uli].ulFormat = RTC_TIME_24H;
        
        RTCTimeWrite(&time[uli], ulTimeAlarm[0]);
        
        while(!RTCWriteEnable());
        
        TestAssert(xFlag[uli] ==  RTCIsLeapYear(),
		       "xrtc API \"RTCIsLeapYear\" error!");
        
    }
}
//*****************************************************************************
//
//! \brief xrtc006 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc006IsLeapYear = {
        xrtc006GetTest,
        xrtc006Setup,
        xrtc006TearDown,
        xrtc006Execute_IsLeapYear 
};

//*****************************************************************************
//
//! \brief Get the Test description of xrtc007test.
//!
//! \return the desccription of the xrtc007 test.
//
//*****************************************************************************
static char* xrtc007GetTest(void)
{
    return "xrtc[007]: xrtc time format test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc007test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc007Setup(void)
{

}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc007 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc007TearDown(void)
{

}

//*****************************************************************************
//
//! \brief xrtc007 test for rtc time format.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc007Execute_TimeFormat()
{
    unsigned long ulTimeFormat[3] = {RTC_TIME_24H, RTC_TIME_12H_AM , 
                                                      RTC_TIME_12H_PM};
    
    for(uli = 0; uli < 3; uli ++)
    {
        //
        // Sets the value of time structure that will be test.
        //
        tTime1.ulYear = 2011;
        
        tTime1.ulSecond = 40;     
    
        tTime1.ulMinute = 10; 
    
        tTime1.ulHour = 11; 
    
        tTime1.ulMDay = 11;  
    
        tTime1.ulMonth = 8;      
    
        tTime1.ulWDay = 3;   

        tTime1.ulFormat = ulTimeFormat[uli];
        
        RTCTimeWrite(&tTime1, ulTimeAlarm[0]);
        
        while(!RTCWriteEnable());
        
        TestAssert(tTime1.ulFormat == ulTimeFormat[uli],
		       "xrtc API \"RTCTimeRead\" error!");
        
    }
}
//*****************************************************************************
//
//! \brief xrtc007 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc007TimeFormat = {
        xrtc007GetTest,
        xrtc007Setup,
        xrtc007TearDown,
        xrtc007Execute_TimeFormat 
};

//
// xrtc test suits.
//
const tTestCase * const psPatternxrtc[] =
{
    &sTestxrtc001Init,
    &sTestxrtc002FCset,
    &sTestxrtc003Mode,
    &sTestxrtc004Int,
    &sTestxrtc005WakeUp,
    &sTestxrtc006IsLeapYear,
    &sTestxrtc007TimeFormat,
    0
};

