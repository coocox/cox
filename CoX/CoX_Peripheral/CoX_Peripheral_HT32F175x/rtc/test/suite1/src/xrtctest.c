//*****************************************************************************
//
//! @page xrtc_testcase xrtc register test
//!
//! File: @ref xrtctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xrtc sub component.<br><br>
//! - \p Board: HT32F125x <br><br>
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
unsigned long i = 0, j = 0;
unsigned long ulTimeAlarm[2] = {RTC_TIME_CURRENT, RTC_TIME_ALARM};

tTime tTime1, tTime2;

unsigned long xRTCCallback(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    if(1==(xHWREG(RTC_SR)) & RTC_SR_CSECFLAG)
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
  SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
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
    unsigned long ulTemp;

    //
    // RTC initialization.
    //
    RTCTimeInit(RTC_CLOCK_SRC_LSE | RTC_CR_LSEEN);

    ulTemp = xHWREG(RTC_CR);

    TestAssert((RTC_CLOCK_SRC_LSE | RTC_CR_LSEEN) == ulTemp, "xrtc API error!");

    RTCTimeInit(RTC_CLOCK_SRC_LSI | RTC_CR_LSIEN);

    ulTemp = xHWREG(RTC_CR);

    TestAssert((RTC_CLOCK_SRC_LSI | RTC_CR_LSIEN) == ulTemp, "xrtc API error!"); 
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
    return "xrtc[002]: xrtc enable test";
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
//! \brief xrtc002 test for rtc enable.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc002Execute_ENset()
{
    unsigned long ulTemp;

	//
	// Stop and Start Enable
	//
    RTCStart();
	ulTemp = xHWREG(RTC_CR) & RTC_CR_RTCEN;
    TestAssert(ulTemp == RTC_CR_RTCEN, "xrtc API error!");

    RTCStop();
	ulTemp = xHWREG(RTC_CR) & RTC_CR_RTCEN;
    TestAssert(0 == ulTemp, "xrtc API error!");

	//
	// Interrupt enable test
	//
	RTCIntEnable(RTC_INT_TIME_TICK);
	ulTemp = xHWREG(RTC_IWEN) & RTC_INT_TIME_TICK;
    TestAssert(ulTemp == RTC_INT_TIME_TICK, "xrtc API error!");

	RTCIntDisable(RTC_INT_TIME_TICK);
	ulTemp = xHWREG(RTC_IWEN) & RTC_INT_TIME_TICK;
    TestAssert(ulTemp == 0, "xrtc API error!");
	
	RTCIntEnable(RTC_INT_ALARM);
	ulTemp = xHWREG(RTC_IWEN) & RTC_INT_ALARM;
    TestAssert(ulTemp == RTC_INT_ALARM, "xrtc API error!");

	RTCIntDisable(RTC_INT_ALARM);
	ulTemp = xHWREG(RTC_IWEN) & RTC_INT_ALARM;
    TestAssert(ulTemp == 0, "xrtc API error!");
	
	RTCIntEnable(RTC_INT_OVERFLOW);
	ulTemp = xHWREG(RTC_IWEN) & RTC_INT_OVERFLOW;
    TestAssert(ulTemp == RTC_INT_OVERFLOW, "xrtc API error!");

	RTCIntDisable(RTC_INT_OVERFLOW);
	ulTemp = xHWREG(RTC_IWEN) & RTC_INT_OVERFLOW;
    TestAssert(ulTemp == 0, "xrtc API error!");

    //
	// Wakeup enbale test
	// 
	RTCWakeupEnable(RTC_WAKEUP_TIME_TICK);
	ulTemp = xHWREG(RTC_IWEN) & RTC_WAKEUP_TIME_TICK;
    TestAssert(ulTemp == RTC_WAKEUP_TIME_TICK, "xrtc API error!");

	RTCWakeupDisable(RTC_WAKEUP_TIME_TICK);
	ulTemp = xHWREG(RTC_IWEN) & RTC_WAKEUP_TIME_TICK;
    TestAssert(ulTemp == 0, "xrtc API error!");
	
	RTCWakeupEnable(RTC_WAKEUP_ALARM);
	ulTemp = xHWREG(RTC_IWEN) & RTC_WAKEUP_ALARM;
    TestAssert(ulTemp == RTC_WAKEUP_ALARM, "xrtc API error!");

	RTCWakeupDisable(RTC_WAKEUP_ALARM);
	ulTemp = xHWREG(RTC_IWEN) & RTC_WAKEUP_ALARM;
    TestAssert(ulTemp == 0, "xrtc API error!");
	
	RTCWakeupEnable(RTC_WAKEUP_OVERFLOW);
	ulTemp = xHWREG(RTC_IWEN) & RTC_WAKEUP_OVERFLOW;
    TestAssert(ulTemp == RTC_WAKEUP_OVERFLOW, "xrtc API error!");

	RTCWakeupDisable(RTC_WAKEUP_OVERFLOW);
	ulTemp = xHWREG(RTC_IWEN) & RTC_WAKEUP_OVERFLOW;
    TestAssert(ulTemp == 0, "xrtc API error!");

	//
	// Output enable
	//
    RTCOutputEnable();
	ulTemp = xHWREG(RTC_CR) & RTC_CR_ROEN;
    TestAssert(ulTemp == RTC_CR_ROEN, "xrtc API error!");

	RTCOutputDisable();
	ulTemp = xHWREG(RTC_CR) & RTC_CR_ROEN;
    TestAssert(ulTemp == 0, "xrtc API error!"); 
}

//*****************************************************************************
//
//! \brief xrtc002 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc002ENset = {
        xrtc002GetTest,
        xrtc002Setup,
        xrtc002TearDown,
        xrtc002Execute_ENset
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
    return "xrtc[003]: xrtc output configure test";
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
//! \brief xrtc003 test for rtc output configure set.
//!
//! \return None.
//
//*****************************************************************************
static void xrtc003Execute_OutputConfigTest()
{    
   	unsigned long ulTemp;

	RTCOutputConfig(RTC_CR_ROAP | RTC_CR_ROWM | RTC_CR_ROES);
	ulTemp = xHWREG(RTC_CR) & (RTC_CR_ROAP | RTC_CR_ROWM | RTC_CR_ROES);
    TestAssert(ulTemp == (RTC_CR_ROAP | RTC_CR_ROWM | RTC_CR_ROES), "xrtc API error!");

	RTCOutputConfig(~(RTC_CR_ROAP | RTC_CR_ROWM | RTC_CR_ROES));
	ulTemp = xHWREG(RTC_CR) & (RTC_CR_ROAP | RTC_CR_ROWM | RTC_CR_ROES);
    TestAssert(ulTemp == 0, "xrtc API error!");
}

//*****************************************************************************
//
//! \brief xrtc003 test case struct.
//!
//! \return None.
//
//*****************************************************************************
const tTestCase sTestxrtc003Outut = {
        xrtc003GetTest,
        xrtc003Setup,
        xrtc003TearDown,
        xrtc003Execute_OutputConfigTest
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
    
    //
    // Writes current time to corresponding register.
    //
    RTCTimeWrite(&tTime2, ulTimeAlarm[0]);
      
    //
    // Alarm interrupt after 10 seconds.
    //
    tTime2.ulSecond +=10;
    
    //
    // Writes alarm time to corresponding register.
    //
    RTCTimeWrite(&tTime2, ulTimeAlarm[1]);
    
    for(j = 0; j < 0xffff; j ++);
    
    RTCTimeRead(&tTime1, ulTimeAlarm[1]);
    
    TestAssert(2011 == tTime1.ulYear && 8 == tTime1.ulMonth
              && 11 ==  tTime1.ulMDay && 50 == tTime1.ulSecond
              && 17 == tTime1.ulHour  && 20 == tTime1.ulMinute
                ,"xrtc API \" RTCTimeWrite()\" or \"RTCTimeRead()\" error!");
    
   
    RTCIntCallbackInit(xRTCCallback);
    
    xIntEnable(INT_RTC);
    xIntMasterEnable();
    
    //
    // Enables alarm interrupt.
    //

    RTCIntEnable(RTC_INT_ALARM);
    
//    TestAssertQBreak("a","Alarm interrupt failed!", 0xffffffff);
    
    for(j = 0; j < 0xffff; j ++);
       
    TestAssert(2011 == tTime1.ulYear && 8 == tTime1.ulMonth
           && 11 ==  tTime1.ulMDay && 50 == tTime1.ulSecond
           && 17 == tTime1.ulHour  && 20 == tTime1.ulMinute
                 ,"xrtc API \" RTCTimeWrite()\" or \"RTCTimeRead()\" error!"); 
    
    //
    // Disables alarm interrupt.
    //
    RTCIntDisable(RTC_INT_ALARM); 
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

//
// xrtc test suits.
//
const tTestCase * const psPatternxrtc[] =
{
    &sTestxrtc001Init,
    &sTestxrtc002ENset,
    &sTestxrtc003Outut,
    &sTestxrtc004Int,
    0
};

