//*****************************************************************************
//
//! @page xrtc_testcase xrtc register test
//!
//! File: @ref xrtctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xrtc sub component.<br><br>
//! - \p Board: KL25Z128 <br><br>
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
#include "xhw_rtc.h"
#include "xrtc.h"

unsigned long uli = 0, ulj = 0;
unsigned long ulTimeAlarm[2] = {RTC_TIME_CURRENT, RTC_TIME_ALARM};

tTime tTime1, tTime2;

unsigned long xRTCACallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    xRTCTimeRead(&tTime1, ulTimeAlarm[0]);
    TestEmitToken('a');
    return 0;
}

unsigned long xRTCSCallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    TestEmitToken('b');
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
   TestAssert(1 == RTCTimeInit(), "xrtc API \"RTCTimeInit\" error!"); 		   
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
    unsigned long ulFrequency[3] = {3264100, 3276700, 3289600};
    unsigned long ulFCR[3] = {0x7f, 0x01, 0x80};
    
    for(uli = 0; uli < 3; uli ++)
    {
        //
        // Sets frequency.
        //
        RTCFrequencyCompensationSet(ulFrequency[uli], 10);
        
        for(ulj = 0; ulj < 0xffff; ulj ++);
        
        //
        // Tests RTCFrequencyCompensationSet API.
        //
        TestAssert(ulFCR[uli] == (xHWREG(RTC_TCR) & RTC_TCR_TCR_M),
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
    return "xrtc[003]: xrtc interrupt register test";
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
    unsigned long ulIntSrc[] = {RTC_INT_TIME_TICK, RTC_INT_ALARM, RTC_INT_OVERFLOW};
    for(uli = 0; uli < 3; uli++)
    {
        RTCIntEnable(ulIntSrc[uli]);
        TestAssert((xHWREG(RTC_IER) & ulIntSrc[uli]) == ulIntSrc[uli],
                     "xrtc API \"RTCIntEnable\" error!");
    } 
  
    for(uli = 0; uli < 3; uli++)
    {
        RTCIntDisable(ulIntSrc[uli]);
        TestAssert((xHWREG(RTC_IER) & ulIntSrc[uli]) == 0,
                     "xrtc API \"RTCIntDisable\" error!");
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
    RTCTimeInit();  
    
    tTime2.ulSecond = 40;     
    
    tTime2.ulMinute = 20; 
    
    tTime2.ulHour = 17; 
    
    tTime2.ulMDay = 11;  
    
    tTime2.ulMonth = 8;   
    
    tTime2.ulYear = 2011;    
    
    tTime2.ulWDay = 4;   

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
      
    xRTCTimeRead(&tTime1, ulTimeAlarm[1]);
    
    TestAssert(2011 == tTime1.ulYear && 8 == tTime1.ulMonth
          && 11 ==  tTime1.ulMDay && RTC_TIME_24H == tTime1.ulFormat 
          && 17 == tTime1.ulHour  && 20 == tTime1.ulMinute 
          && 50 == tTime1.ulSecond,
             "xrtc API \" RTCTimeWrite()\" or \"xRTCTimeRead()\" error!");

    //
    // Enables alarm interrupt.
    //
    RTCIntCallbackInit(RTC_INT_ALARM, xRTCACallback);
    RTCIntEnable(RTC_INT_ALARM);
    xIntEnable(INT_RTCA);
    xIntMasterEnable();
    
    RTCStart();
    
    TestAssertQBreak("a","Alarm interrupt failed!", 0xffffffff);
    
    for(ulj = 0; ulj < 0xffff; ulj ++);
       
    TestAssert(2011 == tTime1.ulYear && 8 == tTime1.ulMonth
           && 11 ==  tTime1.ulMDay && RTC_TIME_24H == tTime1.ulFormat 
           && 17 == tTime1.ulHour && 20 == tTime1.ulMinute 
           && 50 == tTime1.ulSecond ,
            "xrtc API \" RTCTimeWrite()\" or \"xRTCTimeRead()\" error!"); 
    
    //
    // Disables alarm interrupt.
    //
    RTCIntDisable(RTC_INT_ALARM);
   
    //
    // Enables seconds interrupt.
    //
    RTCIntCallbackInit(RTC_INT_TIME_TICK, xRTCSCallback);
    RTCIntEnable(RTC_INT_TIME_TICK);
    xIntEnable(INT_RTCS);
    
    RTCStart();
    
    TestAssertQBreak("b","Tick interrupt failed!",0xffffffff);
    
    //
    // Disables seconds interrupt.
    //
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
    
    //
    // Tests RTCWakeupEnable API.
    //
    TestAssert(RTC_CR_WPE == (xHWREG(RTC_CR) & RTC_CR_WPE),
		      "xrtc API \"RTCWakeupEnable\" error!");
    TestAssert(RTC_IER_WPON == (xHWREG(RTC_IER) & RTC_IER_WPON),
		      "xrtc API \"RTCWakeupEnable\" error!");
    
    RTCWakeupDisable();
 
    //
    // Tests RTCWakeupDisable API.
    //
    TestAssert(0 == (xHWREG(RTC_CR) & RTC_CR_WPE),
		       "xrtc API \"RTCWakeupDisable\" error!");
    TestAssert(0 == (xHWREG(RTC_IER) & RTC_IER_WPON),
		      "xrtc API \"RTCWakeupDisable\" error!");    
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
    TestAssert(RTCIsLeapYear(2000) == 1, "xrtc API \"RTCIsLeapYear\" error!");
    TestAssert(RTCIsLeapYear(2015) == 0, "xrtc API \"RTCIsLeapYear\" error!");
    TestAssert(RTCIsLeapYear(2084) == 1, "xrtc API \"RTCIsLeapYear\" error!");
    TestAssert(RTCIsLeapYear(2095) == 0, "xrtc API \"RTCIsLeapYear\" error!");
   
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
    
        tTime1.ulWDay = 4;   

        tTime1.ulFormat = ulTimeFormat[uli];
        
        RTCTimeWrite(&tTime1, ulTimeAlarm[0]);
        
        RTCTimeRead(&tTime2, ulTimeAlarm[0], ulTimeFormat[uli]);
        
        TestAssert(tTime1.ulFormat == tTime2.ulFormat,
		       "xrtc API \"xRTCTimeRead\" error!");   
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

//*****************************************************************************
//
//! \brief Get the Test description of xrtc008test.
//!
//! \return the desccription of the xrtc008 test.
//
//*****************************************************************************
static char* xrtc008GetTest(void)
{
    return "xrtc[008]: xrtc time Lock Register test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xrtc008test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc008Setup(void)
{
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xrtc008 test.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc008TearDown(void)
{
}

//*****************************************************************************
//
//! \brief xrtc008 test for rtc time format.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc008Execute_LockRegister()
{
    unsigned long ulLockType[] = {RTC_LOCK_SR, RTC_LOCK_CR, RTC_LOCK_TR, RTC_LOCK_LR};
    for(uli = 0; uli < 4; uli++)
    {
        RTCRegisterWriteLock(ulLockType[uli]);
        TestAssert((xHWREG(RTC_LR) & ulLockType[uli]) == 0,
                     "xrtc API \"RTCRegisterWriteLock\" error!");
    } 
}
//*****************************************************************************
//
//! \brief xrtc008 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc008LockRegister = {
        xrtc008GetTest,
        xrtc008Setup,
        xrtc008TearDown,
        xrtc008Execute_LockRegister 
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
    &sTestxrtc008LockRegister,
    0
};
