//*****************************************************************************
//
//! @page xtimer_testcase xtimer register test
//!
//! File: @ref xtimertest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xtimer sub component.<br><br>
//! - \p Board: NUC140VE3CN board <br><br>
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
//! - \subpage test_xtimer_register
//! .
//! \file xtimertest1.c
//! \brief xtimer test source file
//! \brief xtimer test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_timer.h"
#include "xtimer.h"


//*****************************************************************************
//
//!\page test_xtimer_register test_xtimer_register
//!
//!<h2>Description</h2>
//!Test xtimer register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Define The 4 timer base address array, and Peripheral ID array.
//
//*****************************************************************************

//
// Timer base array
//
static unsigned long ulTimerBase[4] = {TIMER0_BASE, TIMER1_BASE,
                                     TIMER2_BASE, TIMER3_BASE};

//
// Timer ID array
//
static unsigned long ulTimerID[4] = {xSYSCTL_PERIPH_TIMER0,
                                     xSYSCTL_PERIPH_TIMER1,
                                     xSYSCTL_PERIPH_TIMER2,
                                     xSYSCTL_PERIPH_TIMER3};

//
// Timer mode
//
static unsigned long ulTimerMode[4] = {xTIMER_MODE_ONESHOT,
                                       xTIMER_MODE_PERIODIC,
                                       xTIMER_MODE_TOGGLE,
                                       xTIMER_MODE_CONTINUOUS};

//
// Capture mode set
//
static unsigned long ulCaptureMode[2] = {xTIMER_CAP_MODE_CAP,
                                         xTIMER_CAP_MODE_RST};

//
// Prescale set
//
static unsigned long ulPrescale[3] = {0, 150, 255};

//
// Match  value set
//
static unsigned long ulCaptureValue[3] = {2, 100, 4095};

//
// Count detecte phase
//
static unsigned long ulCountPhase[2] = {xTIMER_COUNTER_RISING,
                                        xTIMER_COUNTER_FALLING};

//
// Capture edge set
//
static unsigned long ulCaptureEdge[3] = {xTIMER_CAP_RISING,
                                         xTIMER_CAP_FALLING,
                                         xTIMER_CAP_BOTH};

//*****************************************************************************
//
//! \brief Get the Test description of xtimer001 register test.
//!
//! \return the desccription of the xtimer001 test.
//
//*****************************************************************************
static char* xTimer001GetTest(void)
{
    return "xTimer [001]: xtimer register read and write test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Setup(void)
{
    int i;
    //
    //Set the external 12MHZ clock as system clock 
    //
    SysCtlKeyAddrUnlock();
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_6MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Set the timer clock
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_EXT12M);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_EXT12M);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_EXT12M);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_EXT12M);
    
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {   
        
        xSysCtlPeripheralEnable(ulTimerID[i]);  
       
    }
    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001TearDown(void)
{
    int i;
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {
        xSysCtlPeripheralDisable(ulTimerID[i]);  
    }
}

//*****************************************************************************
//
//! \brief xtimer 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Execute(void)
{
    unsigned long ulTemp;
    unsigned long ulBase;
    int i,j ;
    
 //   TestEmitToken('A');
 //   TestAssertQ('A', "Interrupt ont error!");
    //
    // Test the register write and read.
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
        // 
        // Mode set test
        //
        for(j = 0; j < 4; j++)
        {
            xTimerInitConfig(ulBase, i, ulTimerMode[j], 1000);
            ulTemp = xHWREG(ulBase + TIMER_O_TCSR) & TIMER_TCSR_MODE_M;
            TestAssert(ulTimerMode[j] == ulTemp,
                       "xtiemr API \"TimerInitConfig\" error!");
        }
                
        //
        // Tiemr start test
        //
        xTimerStart(ulBase, i);
        ulTemp = xHWREG(ulBase + TIMER_O_TCSR) & TIMER_TCSR_CEN;
        TestAssert(TIMER_TCSR_CEN == ulTemp,
                   "xtiemr API \"TimerStart\" error!");    
  
        //
        // Counter enable test
        // 
        xTimerCounterEnable(ulBase, i);
        ulTemp = xHWREG(ulBase + TIMER_O_TCSR) & TIMER_TCSR_CTB;
        TestAssert(TIMER_TCSR_CTB == ulTemp,
                   "xtiemr API \"TimerCounterEnable\" error!");
        
        
        //
        // Captuer mode enable test
        //
        for(j = 0; j < 2; j++)
        {
            xTimerCaptureModeSet(ulBase, i, ulCaptureMode[j]);
            ulTemp = xHWREG(ulBase + TIMER_O_TEXCON) & TIMER_CAP_MODE_RST;
            TestAssert(ulCaptureMode[j] == ulTemp,
                       "xtiemr API \"TimerCaptureModeSet\" error!");  
        }
       
        //
        // Timer prescale set test
        //
        for(j = 0; j < 3; j++)
        {
            xTimerPrescaleSet(ulBase, i,  ulPrescale[j]);
            ulTemp = xHWREG(ulBase + TIMER_O_TCSR) & TIMER_TCSR_PRESCALE_M;
            TestAssert(ulPrescale[j] == ulTemp,
                       "xtiemr API \"TimerPrescaleSet\" error!");   
        }
         
        //
        // Timer match set test
        //
        for(j = 0; j < 3; j++)
        {
            xTimerMatchSet(ulBase, i, ulCaptureValue[j]);
            ulTemp = TimerMatchGet(ulBase);
            TestAssert(ulCaptureValue[j] == ulTemp,
                       "xtiemr API \"TimerMatchSet\" error!");     
        }
         
        //
        // Timer Int enable test
        // 
        
        xTimerIntEnable(ulBase, i,  TIMER_INT_MATCH | TIMER_INT_CAP);
        ulTemp = xHWREG(ulBase + TIMER_O_TCSR) & TIMER_INT_MATCH;
        TestAssert(TIMER_INT_MATCH == ulTemp,
                   "xtiemr API \"TimerIntEnable\" error!");   
        ulTemp = xHWREG(ulBase + TIMER_O_TEXCON) & TIMER_INT_CAP;
        TestAssert(TIMER_INT_CAP == ulTemp,
                   "xtiemr API \"TimerIntEnable\" error!");    
        
        //
        // Timer Int disable test
        //
        TimerIntDisable(ulBase, TIMER_INT_MATCH | TIMER_INT_CAP);
        ulTemp =  xHWREG(ulBase + TIMER_O_TCSR) & TIMER_INT_MATCH;
        TestAssert(0x00000000 == ulTemp,
                   "xtiemr API \"TimerIntDisable\" error!");  
        ulTemp = xHWREG(ulBase + TIMER_O_TEXCON) & TIMER_INT_CAP;
        TestAssert(0x00000000 == ulTemp,
                   "xtiemr API \"TimerIntDisable\" error!");
        
        //
        // Int status clear test
        //
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        ulTemp = xHWREG(ulBase + TIMER_O_TISR) & TIMER_TISR_TIF;
        TestAssert(0x00000000 == ulTemp,
                   "xtiemr API \"TimerIntClear\" error!");        
        
        //
        // Counter detect phase set
        //
        for(j = 0; j < 2; j++)
        {
            xTimerCounterDetectPhaseSelect(ulBase, i, ulCountPhase[j]);
            ulTemp = xHWREG(ulBase + TIMER_O_TEXCON) & TIMER_COUNTER_RISING;
            TestAssert(ulCountPhase[j] == ulTemp,
                       "xtiemr API \"TimerCounterDetectPhaseSelect\" error!");
        }
        
        //
        // Capture edge set
        //
        for(j = 0; j < 2; j++)
        {
            xTimerCaptureEdgeSelect(ulBase, i,  ulCaptureEdge[j]);
            ulTemp = xHWREG(ulBase + TIMER_O_TEXCON) & TIMER_TEXCON_TEX_EDGE_M;
            TestAssert(ulCaptureEdge[j] == ulTemp,
                       "xtiemr API \"TimerCaptureEdgeSelect\" error!");     
        }
        
        //
        // Counter de-bounce set test
        //
        TimerCounterDebounceEnable(ulBase);
        ulTemp = xHWREG(ulBase + TIMER_O_TEXCON) & TIMER_TEXCON_TCDB;
        TestAssert(TIMER_TEXCON_TCDB == ulTemp,
                   "xtiemr API \"TimerCounterDebounceEnable\" error!");  
        
        //
        // Capture de-bounce set test
        //
        TimerCaptureDebounceEnable(ulBase);
        ulTemp = xHWREG(ulBase + TIMER_O_TEXCON) & TIMER_TEXCON_TEXDB;
        TestAssert(TIMER_TEXCON_TEXDB == ulTemp,
                   "xtiemr API \"TimerCaptureDebounceEnable\" error!"); 
        
         
        //
        // Timer stop test
        //
        xTimerStop(ulBase, i);
        ulTemp = xHWREG(ulBase + TIMER_O_TCSR) & TIMER_TCSR_CEN;
        TestAssert(0x00000000 == ulTemp,
                   "xtiemr API \"TimerStop\" error!");  
        
    }   
  
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer001Register = {
		xTimer001GetTest,
		xTimer001Setup,
		xTimer001TearDown,
		xTimer001Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer001[] =
{
    &sTestxTimer001Register,
    0
};

