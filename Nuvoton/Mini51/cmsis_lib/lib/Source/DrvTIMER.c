//*****************************************************************************
//
//! \file DrvTIMER.c
//! \brief Driver for the TIMER Controller.
//! \version v1.04.005
//! \date 11/28/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//
//*****************************************************************************
  
//*****************************************************************************
//
//! Includes of system headers
//
//*****************************************************************************

//*****************************************************************************
//
//! Includes of local headers
//
//*****************************************************************************
#include "DrvTIMER.h"
#include "DrvSYS.h"
#include "DrvGPIO.h"
#include "Assert.h"

//*****************************************************************************
//
//! Macro, type and constant definitions
//
//*****************************************************************************
#define TIMER_EVENT_COUNT   1
const uint32_t CH_OFFSET[] = {0x0, 0x20};


//*****************************************************************************
//
//! Global file scope (static) variables
//
//*****************************************************************************
static TIMER_EVENT_T tTime0Event[TIMER_EVENT_COUNT],
                     tTime1Event[TIMER_EVENT_COUNT];

int32_t volatile bIsTimer0Initial     = FALSE,
                 bIsTimer1Initial     = FALSE,
                 bIsTimer0Used        = FALSE,
                 bIsTimer1Used        = FALSE,
                 bIsSetTime0Event     = FALSE,
                 bIsSetTime1Event     = FALSE;

static uint32_t volatile uTimer0Tick = 0,
                         uTimer1Tick = 0,
                         uTime0EventCount = 0,
                         uTime1EventCount = 0;

static uint32_t volatile _sys_uTimer0TickPerSecond,
                         _sys_uTimer1TickPerSecond;

uint32_t volatile u32EXTClockFreq = 12000000;

static WDT_CALLBACK fnCallBack_WDT;

//*****************************************************************************
//
//! \brief Get the timer clock from the specified timer channel. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return u32clk                           The timer clock (Hz)
//
//*****************************************************************************
static uint32_t GetTimerClock(E_TIMER_CHANNEL ch)
{
    volatile uint8_t u8ClockcSrc;
    volatile uint32_t u32clk = 0;

	assert_param(CHECK_TMR_PORT(ch));
        
	u8ClockcSrc = ((CLK->CLKSEL1) >> (8+(ch*4))) & 0x7;

	if (u8ClockcSrc == 0)			
	{
        //
        // Option 0: Get External Clock From DrvSYS Setting
        //
		u32clk = DrvSYS_GetExtClockFreq();
	}
	else if(u8ClockcSrc == 1)
	{
        //
        // Option 1: Internal 10KHz
        // 
		u32clk = __IRC10K;
	}
	else if(u8ClockcSrc == 2)
	{
        //
        // Option 2: HCLK
        //
		u32clk = DrvSYS_GetHCLKFreq();
	}
	else if(u8ClockcSrc == 3)
	{
        //
        // Option 3: External Trigger
        //
		u32clk = u32EXTClockFreq;
	}
	else 
	{
        //
        // Option 4: 22MHz
        //
		u32clk = __IRC22M;
	}  

    return u32clk;
}

//*****************************************************************************
//
//! \brief Calculate the Timer Compare Value and pre-scale value for Timer 
//!
//! \param u32ClockValue  Input the clock value of Timer
//! \param u32TicksPerSec  Specify the ticks per second of Timer
//!
//! \return
//!      Return 32 bits unsigned integer where                                  
//!              bits [ 0:23] - The Timer Compare Value(TCMPR) for Timer        
//!              bits [24:31] - The pre-scale value for Timer                  
//!      (uint32_t)-1                            Out of range 
//
//*****************************************************************************
static uint32_t CalTimerInitValue(uint32_t u32ClockValue, uint32_t u32TicksPerSec)
{
    uint32_t u32PreScale;
    uint32_t u32TCMPRValue;

    if ((u32ClockValue < 2) || (u32TicksPerSec == 0))
        return (uint32_t)-1;

    for (u32PreScale=1; u32PreScale<256; u32PreScale++)
    {
        u32TCMPRValue = u32ClockValue / (u32TicksPerSec * u32PreScale);

        //
        // The TCMPR value must > 1
        //
        if ((u32TCMPRValue > 1) && (u32TCMPRValue < 0x1000000))
            return (((u32PreScale-1) << 24) | u32TCMPRValue);
    }
    
    return (uint32_t)-1;
}

//*****************************************************************************
//
//! \brief The TIMER0 default IRQ, declared in startup_MINI51.s  
//!
//! \param None 
//!
//! \return None 
//
//*****************************************************************************
void TMR0_IRQHandler(void)
{
    int32_t i;

	if((TIMER0->CSR_BITS.IE==1) && (TIMER0->ISR_BITS.TIF==1))
	    TIMER0->ISR_BITS.TIF = 1;
	if((TIMER0->EXCON_BITS.TEXEN==1) && (TIMER0->EXCON_BITS.TEX_INT==1) && (TIMER0->EXISR_BITS.TEXIF==1))
	    TIMER0->EXISR_BITS.TEXIF = 1;
	if((TIMER0->CSR_BITS.WAKE_EN==1) && (TIMER0->ISR_BITS.TWF==1))
	    TIMER0->ISR_BITS.TWF = 1;

    uTimer0Tick++;
    //
    // Timer Event Handle
    //
    if (bIsSetTime0Event)
    {
        for (i=0; i<TIMER_EVENT_COUNT; i++)
        {
            if (tTime0Event[i].active)
            {
                tTime0Event[i].curTick--;
                if (tTime0Event[i].curTick == 0)
                {
                    (*tTime0Event[i].funPtr)(tTime0Event[i].transParam);
                    tTime0Event[i].curTick = tTime0Event[i].initTick;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \brief The TIMER1 default IRQ, declared in startup_MINI51.s  
//!
//! \param None 
//!
//! \return None 
//
//*****************************************************************************
void TMR1_IRQHandler(void)
{
    int32_t i;
    
    if((TIMER1->CSR_BITS.IE==1) && (TIMER1->ISR_BITS.TIF==1))
	    TIMER1->ISR_BITS.TIF = 1;
	if((TIMER1->EXCON_BITS.TEXEN==1) && (TIMER1->EXCON_BITS.TEX_INT==1) && (TIMER1->EXISR_BITS.TEXIF==1))
	    TIMER1->EXISR_BITS.TEXIF = 1;
	if((TIMER1->CSR_BITS.WAKE_EN==1) && (TIMER1->ISR_BITS.TWF==1))
	    TIMER1->ISR_BITS.TWF = 1;

    uTimer1Tick++;
    //
    // Timer Event Handle
    //
    if (bIsSetTime1Event)
    {
        for (i=0; i<TIMER_EVENT_COUNT; i++)
        {
            if (tTime1Event[i].active)
            {
                tTime1Event[i].curTick--;
                if (tTime1Event[i].curTick == 0)
                {
                    (*tTime1Event[i].funPtr)(tTime1Event[i].transParam);
                    tTime1Event[i].curTick = tTime1Event[i].initTick;
                }
            }
        }
    }
}



//*****************************************************************************
//
//! \brief User must to call this function before any timer operations after
//!  system boot up. 
//!
//! \param None 
//!
//! \return None 
//
//*****************************************************************************
void DrvTIMER_Init(void)
{
    bIsTimer0Initial    = TRUE;
    bIsTimer1Initial    = TRUE;
}

//*****************************************************************************
//
//! \brief Open the specified timer channel with specified operation mode. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param uTicksPerSecond  This value means how many timer interrupt ticks in
//!  one second
//! \param op_mode  E_TIMER_OPMODE,
//!  E_ONESHOT_MODE/E_PERIODIC_MODE/E_TOGGLE_MODE/E_CONTINUOUS_MODE
//!
//! \return E_SUCCESS                        Operation successful
//!         E_DRVTIMER_CLOCK_RATE            Calculate initial value fail 
//
//*****************************************************************************
int32_t DrvTIMER_Open(E_TIMER_CHANNEL ch, uint32_t uTicksPerSecond, E_TIMER_OPMODE op_mode)
{
    uint32_t i;
    uint32_t uRegTcmpr, uRegTcr = 0x0;

	assert_param(CHECK_TMR_PORT(ch));

    switch (ch)
    {
        case E_TMR0:
        {
            if ((bIsTimer0Initial != TRUE) || (bIsTimer0Used != FALSE))
                return E_DRVTIMER_EIO;
            
            bIsTimer0Used = TRUE;
           
            CLK->APBCLK_BITS.TMR0_EN = 1;
            
            //
            // disable timer
            //
            TIMER0->CSR = 0; 
           
            //
            // write 1 to clear for safty
            //
            TIMER0->ISR_BITS.TIF = 1; 
			      uTime0EventCount = 0;
            for (i=0; i<TIMER_EVENT_COUNT; i++)
            {
                tTime0Event[i].active = FALSE;
            }

            uTimer0Tick = 0;            
            _sys_uTimer0TickPerSecond = uTicksPerSecond;
                    
            uRegTcmpr = CalTimerInitValue(GetTimerClock(E_TMR0), uTicksPerSecond); 
            if (uRegTcmpr == (uint32_t)-1)      
            {
                return E_DRVTIMER_CLOCK_RATE;           
            }

			      if(op_mode == E_TOGGLE_MODE)
                    //
                    // Open toggle pin
                    //
				    DrvGPIO_InitFunction(FUNC_TMR0);

            TIMER0->CMPR = (uRegTcmpr << 8) >> 8;
            TIMER0->CSR = (uRegTcr|(uRegTcmpr>>24))|(op_mode<<27);
            break;
        }

        case E_TMR1:
        {
            if ((bIsTimer1Initial != TRUE) || (bIsTimer1Used != FALSE))
                return E_DRVTIMER_EIO;

            bIsTimer1Used = TRUE;

            CLK->APBCLK_BITS.TMR1_EN = 1;
            
            //
            // disable timer
            //
            TIMER1->CSR = 0; 
            
            //
            // write 1 to clear for safty
            //
            TIMER1->ISR_BITS.TIF = 1;
			      uTime1EventCount = 0;
            for (i=0; i<TIMER_EVENT_COUNT; i++)
            {
                tTime1Event[i].active = FALSE;
            }

            uTimer1Tick = 0;
            _sys_uTimer1TickPerSecond = uTicksPerSecond;

            uRegTcmpr = CalTimerInitValue(GetTimerClock(E_TMR1), uTicksPerSecond); 
            if(uRegTcmpr == (uint32_t)-1)       
            {
                return E_DRVTIMER_CLOCK_RATE;           
            }

		        if(op_mode == E_TOGGLE_MODE)
                    //
                    // Open toggle pin
                    //
				    DrvGPIO_InitFunction(FUNC_TMR1);

            TIMER1->CMPR = (uRegTcmpr << 8) >> 8;
            TIMER1->CSR = (uRegTcr|(uRegTcmpr>>24))|(op_mode<<27);
            break;
        }     

    }

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief The function is used to close the timer channel. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1/E_TMR2/E_TMR3
//!
//! \return
//!      E_SUCCESS                               Operation successful          
//
//*****************************************************************************
int32_t DrvTIMER_Close(E_TIMER_CHANNEL ch)
{
	assert_param(CHECK_TMR_PORT(ch));
	
    switch (ch)
    {
        case E_TMR0:
        {
            DrvTIMER_DisableInt(E_TMR0);
            TIMER0->CSR_BITS.CRST   = 1;
            bIsTimer0Used       = FALSE;
            bIsSetTime0Event    = FALSE;
            break;
        }

        case E_TMR1:
        {
            DrvTIMER_DisableInt(E_TMR1);
            TIMER1->CSR_BITS.CRST   = 1;
            bIsTimer1Used       = FALSE;
            bIsSetTime1Event    = FALSE;
            break;
        }

    }

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Install the interrupt callback function of the specified timer
//!  channel. And trigger timer callback functuion when interrupt occur
//!  specified times. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param uInterruptTicks  Number of timer interrupt occurred
//! \param pTimerCallback  The function pointer of the interrupt callback
//!  function
//! \param  parameter A parameter of the callback function 
//!
//! \return uTimerEventNo                    The timer event number
//!         E_DRVTIMER_EVENT_FULL            The timer event is full 
//
//*****************************************************************************
int32_t DrvTIMER_SetTimerEvent(E_TIMER_CHANNEL ch, uint32_t uInterruptTicks, TIMER_CALLBACK pTimerCallback, uint32_t parameter)
{
    volatile int32_t i;
    int32_t uTimerEventNo = 0;

	assert_param(CHECK_TMR_PORT(ch));
	
    switch (ch)
    {
        case E_TMR0:
        {
            if (uTime0EventCount >= TIMER_EVENT_COUNT)
                return E_DRVTIMER_EVENT_FULL;

            bIsSetTime0Event = TRUE;
            uTime0EventCount++;
            for (i=0; i<TIMER_EVENT_COUNT; i++)
            {
                if (tTime0Event[i].active  == FALSE)
                {
                    tTime0Event[i].active       = TRUE;
                    tTime0Event[i].initTick     = uInterruptTicks;
                    tTime0Event[i].curTick      = uInterruptTicks;
                    tTime0Event[i].funPtr       = (TIMER_CALLBACK)pTimerCallback;
                    tTime0Event[i].transParam   = parameter;
                    uTimerEventNo = i;
                    break;
                }
            }
            break;
        }

        case E_TMR1:
        {
            if (uTime1EventCount >= TIMER_EVENT_COUNT)
                return E_DRVTIMER_EVENT_FULL;

            bIsSetTime1Event = TRUE;
            uTime1EventCount++;
            for (i=0; i<TIMER_EVENT_COUNT; i++)
            {
                if (tTime1Event[i].active   == FALSE)
                {
                    tTime1Event[i].active       = TRUE;
                    tTime1Event[i].initTick     = uInterruptTicks;
                    tTime1Event[i].curTick      = uInterruptTicks;
                    tTime1Event[i].funPtr       = (TIMER_CALLBACK)pTimerCallback;
                    tTime1Event[i].transParam   = parameter;
                    uTimerEventNo = i;
                    break;
                }
            }
            break;
        }

    }

    return uTimerEventNo;
}

//*****************************************************************************
//
//! \brief Clear the timer event of the specified timer channel. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param uTimerEventNo  The timer event number
//!
//! \return None 
//
//*****************************************************************************
void DrvTIMER_ClearTimerEvent(E_TIMER_CHANNEL ch, uint32_t uTimerEventNo)
{
	assert_param(CHECK_TMR_PORT(ch));
	
    switch (ch)
    {
        case E_TMR0:
        {
            tTime0Event[uTimerEventNo].active = FALSE;
            uTime0EventCount--;
            if (uTime0EventCount == 0)
            {
                bIsSetTime0Event = FALSE;
            }
            break;
        }

        case E_TMR1:
        {
            tTime1Event[uTimerEventNo].active = FALSE;
            uTime1EventCount--;
            if (uTime1EventCount == 0)
            {
                bIsSetTime1Event = FALSE;
            }
            break;
        }

    }
}

//*****************************************************************************
//
//! \brief This function is used to enable the specified timer interrupt. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                        Operation successful
//
//*****************************************************************************
int32_t DrvTIMER_EnableInt(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->CSR_BITS.IE = 1;
    NVIC_EnableIRQ((IRQn_Type)((uint32_t)TMR0_IRQn + (uint32_t)ch)); 
    return E_SUCCESS ;

}

//*****************************************************************************
//
//! \brief This function is used to disable the specified timer interrupt 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                               Operation successful
//
//*****************************************************************************
int32_t DrvTIMER_DisableInt(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	  assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->CSR_BITS.IE = 0;
    NVIC_DisableIRQ((IRQn_Type)((uint32_t)TMR0_IRQn + (uint32_t)ch)); 
    return E_SUCCESS ;

}

//*****************************************************************************
//
//! \brief Get the interrupt flag status from the specified timer channel. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return iIntStatus               0:No interrupt / 1:Interrupt occurred
//!         E_DRVTIMER_CHANNEL       Invalid Timer channel 
//
//*****************************************************************************
int32_t DrvTIMER_GetIntFlag(E_TIMER_CHANNEL ch)
{
    if (ch == E_TMR0 )
        return TIMER0->ISR_BITS.TIF;
    else if(ch == E_TMR1 )                                   
        return TIMER1->ISR_BITS.TIF;
    else 
        return E_DRVTIMER_CHANNEL;
}

//*****************************************************************************
//
//! \brief Clear the interrupt flag of the specified timer channel. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                               Operation successful
//!         E_DRVTIMER_CHANNEL                      Invalid Timer channel 
//
//*****************************************************************************
int32_t DrvTIMER_ClearIntFlag(E_TIMER_CHANNEL ch)
{
    if (ch == E_TMR0 )
        TIMER0->ISR_BITS.TIF = 1;
    else if(ch == E_TMR1 )                                   
        TIMER1->ISR_BITS.TIF = 1;
    else 
        return E_DRVTIMER_CHANNEL;

    return E_SUCCESS;
}


//*****************************************************************************
//
//! \brief Start to count the specified timer channel. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                        Operation successful 
//
//*****************************************************************************
int32_t DrvTIMER_Start(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->CSR_BITS.CEN = 1;
    return E_SUCCESS ;

}

//*****************************************************************************
//
//! \brief This function is used to get the number of interrupt occurred after
//!  the timer interrupt function is enabled. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return uTimerTick                       Returns the interrupt ticks 
//
//*****************************************************************************
uint32_t DrvTIMER_GetIntTicks(E_TIMER_CHANNEL ch)
{
	uint32_t tick=0;
	
	assert_param(CHECK_TMR_PORT(ch));

	if(ch == E_TMR0)
		tick = uTimer0Tick;
	else if(ch == E_TMR1)
		tick = uTimer1Tick;

	return tick;
}

//*****************************************************************************
//
//! \brief This function is used to clear interrupt ticks to 0. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                        Operation successful
//
//*****************************************************************************
int32_t DrvTIMER_ResetIntTicks(E_TIMER_CHANNEL ch)
{

	assert_param(CHECK_TMR_PORT(ch));
	
    switch (ch)
    {
        case E_TMR0:
        {
            uTimer0Tick = 0;
            break;
        }

        case E_TMR1:
        {
            uTimer1Tick = 0;
            break;
        }

    }

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief This function is used to add a delay loop by specified interrupt
//!  ticks of the timer channel. 
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param uIntTicks  The delay ticks
//!
//! \return None 
//
//*****************************************************************************
void DrvTIMER_Delay(E_TIMER_CHANNEL ch, uint32_t uIntTicks)
{
    uint32_t volatile btime;

    btime = DrvTIMER_GetIntTicks(ch);
    
    while (1)
    {
        if ((DrvTIMER_GetIntTicks(ch) - btime) > uIntTicks)
        {
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief Set the external clock frequence, it's used for timer clock source.
//!  User can change the timer clock source from the external clock source by 
//!  calling DrvSYS_SelectIPClockSource (...)
//!
//! \param u32ClockFreq Set the clock frequence (Hz) for external clock source 
//!
//! \return None 
//
//*****************************************************************************
void DrvTIMER_SetEXTClockFreq(uint32_t u32ClockFreq)
{
    u32EXTClockFreq = u32ClockFreq;
}

//*****************************************************************************
//
//! \brief This function is used to open the timer channel with the specified
//!  operation mode. And the counting source of timer is from the external
//!  event/counter. The TIMER clock source should be set as HCLK. Only NuMicro
//!  NUC1x0xxxBx and NUC1x0xxxCx series support this function,ex:NUC140RD2BN,
//!  NUC140VE3CN.
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param uCounterBoundary  The parameter is used to determine how many counts
//!  occurred will toggle once timer interrupt.
//! \param op_mode  E_TIMER_OPMODE,
//!  E_ONESHOT_MODE/E_PERIODIC_MODE/E_CONTINUOUS_MODE
//!
//! \return E_SUCCESS                        Operation successful
//!         E_DRVTIMER_MODE                  Invalid Timer mode 
//!         E_DRVTIMER_EIO                   Timer has not been initialized 
//
//*****************************************************************************
int32_t DrvTIMER_OpenCounter(E_TIMER_CHANNEL ch, uint32_t uCounterBoundary, E_TIMER_OPMODE op_mode)
{
    uint32_t i;
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));

    if ((bIsTimer0Initial == FALSE) || (bIsTimer1Initial == FALSE))
    {
        return E_DRVTIMER_EIO;
    }

    if (op_mode == E_TOGGLE_MODE)
        return E_DRVTIMER_MODE;
                        
    switch (ch)
    {
        case E_TMR0:
        {
            if (bIsTimer0Used != FALSE)
                return E_DRVTIMER_EIO;
            
            bIsTimer0Used = TRUE;
           
            CLK->APBCLK_BITS.TMR0_EN = 1;

            //
            // Disable timer
            //
            TIMER0->CSR = 0;

			uTime0EventCount = 0;
            for (i=0; i<TIMER_EVENT_COUNT; i++)
            {
                tTime0Event[i].active = FALSE;
            }
            uTimer0Tick = 0;
            break;
        }

        case E_TMR1:
        {
            if (bIsTimer1Used != FALSE)
                return E_DRVTIMER_EIO;
                                       
            bIsTimer1Used = TRUE;
           
            CLK->APBCLK_BITS.TMR1_EN = 1;

            //
            // Disable timer
            //
            TIMER1->CSR = 0; 

			uTime1EventCount = 0;
            for (i=0; i<TIMER_EVENT_COUNT; i++)
            {
                tTime1Event[i].active = FALSE;
            }
            uTimer1Tick = 0;
            break;
        }

    }

	if (ch ==  E_TMR0)
        //
        // Open external Timer Counter source
        //
    	DrvGPIO_InitFunction(FUNC_TMR0);
	else
        //
        // Open external Timer Counter source
        //
		DrvGPIO_InitFunction(FUNC_TMR1);

    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);   
    //
    // Write 1 to clear for safty
    //
    tTMR->ISR_BITS.TIF      = 1;         
    tTMR->CMPR         = uCounterBoundary;
    //
    // Set operation mode & enable TDR & enable CTB
    //
	tTMR->CSR = (op_mode<<27) | (1<<16) | (1<<24);

    return E_SUCCESS;
}


//*****************************************************************************
//
//! \brief Start counting of the specified timer channel.
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                          Operation successful
//
//*****************************************************************************
int32_t DrvTIMER_StartCounter(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);   
    if (tTMR->CSR_BITS.IE == 0)
        //
        // If use Polling Mode, do not configure Timer Compare Register.
        //
        tTMR->CMPR = 0;
    tTMR->CSR_BITS.CRST     = 1;                    
    tTMR->CSR_BITS.CEN      = 1;                    
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to get the current counters of the specified
//!  timer channel.
//!
//! \param ch  E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return u32Counters                        Returns current counters 
//
//*****************************************************************************
uint32_t DrvTIMER_GetCounters(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    return tTMR->DR;

}

//*****************************************************************************
//
//! \brief This function is used to initial the external timer capture source 
//!  and set to start catpure or reset specified timer counter.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param mode: E_TIMER_RSTCAP_MODE
//!              E_CAPTURE : Run capture function
//!              E_RESET   : Reset counter value of specified timer channel
//!
//! \return E_SUCCESS          Operation successful  
//! 
//
//*****************************************************************************
int32_t DrvTIMER_OpenCapture(E_TIMER_CHANNEL ch, E_TIMER_RSTCAP_MODE mode)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
	if (ch == E_TMR0)
    	DrvGPIO_InitFunction(FUNC_T0EX);
	else
		DrvGPIO_InitFunction(FUNC_T1EX);

    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.RSTCAP = mode;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to close the external timer capture source.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS           Operation successful 
//! 
//
//*****************************************************************************
int32_t DrvTIMER_CloseCapture(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON = 0; 
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to select to run capture function or reset 
//!  the timer counter.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param mode: E_TIMER_RSTCAP_MODE,
//!              E_CAP_FREE_COUNTING    : Select free-counting mode 
//!              E_CAP_COUNTER_RESET    : Select counter-reset mode 
//!              E_CAP_TRIGGER_COUNTING : Select trigger-counting mode 
//!
//! \return E_SUCCESS                         Operation successful
//!         E_DRVTIMER_MODE                   Invalid Timer mode 
//! 
//
//*****************************************************************************
int32_t DrvTIMER_SelectExternalMode(E_TIMER_CHANNEL ch, E_TIMER_CAP_MODE mode)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	

    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    if(mode == E_CAP_FREE_COUNTING)
    {
		tTMR->EXCON_BITS.CAP_MODE = 0;
		tTMR->EXCON_BITS.RSTCAP = 0;
	}
	else if(mode == E_CAP_COUNTER_RESET)
    {
		tTMR->EXCON_BITS.CAP_MODE = 0;
		tTMR->EXCON_BITS.RSTCAP = 1;
	}
	else if(mode == E_CAP_TRIGGER_COUNTING)
    {
		tTMR->EXCON_BITS.CAP_MODE = 1;
		tTMR->EXCON_BITS.RSTCAP = 0;
	}
	else return E_DRVTIMER_MODE;
	
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to select to configure the detect edge of 
//!  specified counter-reset & free-counting capture mode.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param edge: E_TIMER_TEX_EDGE,
//!              E_EDGE_FALLING : 1 to 0 transition on TEX will be detected.
//!              E_EDGE_RISING  : 0 to 1 transition on TEX will be detected.
//!              E_EDGE_BOTH    : either 0 to 1 or 1 to 0 transition on TEX will 
//!                               be detected.
//!
//! \return E_SUCCESS               Operation successful 
//! 
//
//*****************************************************************************
int32_t DrvTIMER_SelectCaptureEdge(E_TIMER_CHANNEL ch, E_TIMER_TEX_EDGE edge)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEX_EDGE = edge;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to select to configure the detect edge of 
//!  specified trigger capture mode.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param edge: E_TIMER_TEX_TRIGGER_EDGE,
//!              E_FALLING_EDGE : First 1 to 0 transition to start,
//!                               second 1 to 0 transition to stop counting 
//!              E_RISING_EDGE  : First 0 to 1 transition to start,
//!                               second 0 to 1 transition to stop counting  
//!              E_FALLING_RISING_EDGE : First 1 to 0 transition to start,
//!                                  second 0 to 1 transition to stop counting 
//!              E_RISING_FALLING_EDGE : First 0 to 1 transition to start,
//!                                  second 1 to 0 transition to stop counting 
//!
//!
//! \return E_SUCCESS               Operation successful 
//! 
//
//*****************************************************************************
int32_t DrvTIMER_SelectTriggerCaptureEdge(E_TIMER_CHANNEL ch, E_TIMER_TEX_TRIGGER_EDGE edge)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEX_EDGE = edge;
    return E_SUCCESS;
	
}

//*****************************************************************************
//
//! \brief This function is used to select to enable the timer external 
//! interrupt function.And when detect transition on TEX pin, system will cause 
//! the external interrupt flag(TEXIF) to 1. 
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                 Operation successful
//! 
//
//*****************************************************************************
int32_t DrvTIMER_EnableCaptureInt(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEX_INT = 1;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to select to disable the timer external interrupt
//! function.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS            Operation successful  
//! 
//
//*****************************************************************************
int32_t DrvTIMER_DisableCaptureInt(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEX_INT = 0;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to enable the specified capture pin.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS             Operation successful 
//! 
//
//*****************************************************************************
int32_t DrvTIMER_EnableCapture(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEXEN = 1;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to disable the specified capture pin.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return E_SUCCESS                       Operation successful
//! 
//
//*****************************************************************************
int32_t DrvTIMER_DisableCapture(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEXEN = 0;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief This function is used to get the capture value of the specified timer
//!  channel.
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return Capture value                 Return capture value
//
//*****************************************************************************
uint32_t DrvTIMER_GetCaptureData(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    return tTMR->CAP;

}

//*****************************************************************************
//
//! \brief Get the external interrupt flag status from the specified timer
//!  channel. 
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return External interrupt flag       0:No interrupt / 1:Interrupt occurred 
//
//*****************************************************************************
int32_t DrvTIMER_GetCaptureIntFlag(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    return tTMR->EXISR_BITS.TEXIF;

}

//*****************************************************************************
//
//! \brief Get the external interrupt flag of the specified timer
//!  channel. 
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//!
//! \return  E_SUCCESS         Operation successful
//
//*****************************************************************************
int32_t DrvTIMER_ClearCaptureIntFlag(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
	tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
	tTMR->EXISR_BITS.TEXIF = 1;
	return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief  Enable the debounce function of specified external capture input 
//! source. 
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! 
//! \return E_SUCCESS                Operation successful
//
//*****************************************************************************
int32_t DrvTIMER_EnableCaptureDebounce(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEX_DBNCE = 1;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief   Disable the debounce function of specified external capture input 
//! source. 
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! 
//! \return E_SUCCESS                Operation successful
//
//*****************************************************************************
int32_t DrvTIMER_DisableCaptureDebounce(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

    assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TEX_DBNCE = 0;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief   Enable the debounce function of specified external counter input 
//! source. 
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! 
//! \return E_SUCCESS                Operation successful
//
//***************************************************************************** 
int32_t DrvTIMER_EnableCounterDebounce(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.COUNTER_DBNCE = 1;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief   Disable the debounce function of specified external counter input 
//! source. 
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! 
//! \return E_SUCCESS                Operation successful
//
//***************************************************************************** 
int32_t DrvTIMER_DisableCounterDebounce(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

    assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.COUNTER_DBNCE = 0;
    return E_SUCCESS;
   
}

//*****************************************************************************
//
//! \brief This function is used to configure the detect edge of specified 
//!  timer counter mode
//!
//! \param ch:   E_TIMER_CHANNEL, it could be E_TMR0/E_TMR1
//! \param phase: E_TIMER_TX_PHASE
//!   E_PHASE_FALLING : A falling edge of external counter pin will be counted.
//!   E_PHASE_RISING  : A rising edge of external counter pin will be counted. 
//!
//! \return E_SUCCESS                 Operation successful 
//! 
//
//*****************************************************************************
int32_t DrvTIMER_SelectCounterDetectPhase(E_TIMER_CHANNEL ch, E_TIMER_TX_PHASE phase)
{
    TIMER_TypeDef * tTMR;

    assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->EXCON_BITS.TX_PHASE = phase;
    return E_SUCCESS;
    
}

//*****************************************************************************
//
//! \brief   Enable specified timer channel to wake up the system
//!
//! \param  ch  Timer channel enabled to wake up system
//! 
//! \return  0                   Success
//!          E_DRVTIMER_CHANNEL  Unknown support timer channel
//
//*****************************************************************************
int32_t DrvTIMER_EnableWakeUp(E_TIMER_CHANNEL ch)
{
    TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->CSR_BITS.WAKE_EN = 1;
    return E_SUCCESS;

}

//*****************************************************************************
//
//! \brief   Disable specified timer channel to wake up the system
//!
//! \param  ch  Timer channel enabled to wake up system
//! 
//! \return  0                   Success
//!          E_DRVTIMER_CHANNEL  Unknown support timer channel
//
//*****************************************************************************
int32_t DrvTIMER_DisableWakeUp(E_TIMER_CHANNEL ch)
{
	TIMER_TypeDef * tTMR;

	assert_param(CHECK_TMR_PORT(ch));
	
    tTMR = (TIMER_TypeDef *)((uint32_t)TIMER0 + CH_OFFSET[ch]);         
    tTMR->CSR_BITS.WAKE_EN = 0;
    return E_SUCCESS;

}



//*****************************************************************************
//
//! \brief This function is used to Get the version number of Timer/WDT driver.
//!
//! \param None
//!
//! \return DRVTIMER_VERSION_NUM Version number of Timer/WDT driver
//! 
//
//*****************************************************************************
uint32_t DrvTIMER_GetVersion(void)
{
    return DRVTIMER_VERSION_NUM;
}


//*****************************************************************************
//
//! \brief The WatchDog Timer(WDT) default IRQ, declared in startup_MINI51.s 
//!
//! \param None
//!
//! \return None
//! 
//
//*****************************************************************************
void WDT_IRQHandler(void)
{
    //
    // Clear the WDT INT Flag
    //
    WDT->WTCR_BITS.WTIF = 1;

    if (fnCallBack_WDT)        
    {
        fnCallBack_WDT(NULL);
    }
}

//*****************************************************************************
//
//! \brief  Enable WDT engine clock and set WDT time-out interval. 
//!
//! \param in:   E_WDT_INTERVAL, enumerate the WDT time-out interval.Refer to
//!              WDT_INTERVAL enumeration for detail time-out value.
//!
//! \return None      
//! 
//
//*****************************************************************************
void DrvWDT_Open(E_WDT_INTERVAL WDTlevel)
{
    //
    // Stop WDT first
    //
    DrvWDT_Ioctl(E_WDT_IOC_STOP_TIMER, 0);

    //
    // Enable WatchDog Timer Clock
    //
    CLK->APBCLK_BITS.WDT_EN = 1;

    //
    // Select WatchDog Timer Interval
    //
    WDT->WTCR_BITS.WTIS = WDTlevel;
}

//*****************************************************************************
//
//! \brief This function is used to stop/disable WDT relative functions.
//!
//! \param None
//!
//! \return None
//! 
//
//*****************************************************************************
void DrvWDT_Close(void)
{
    //
    // Stop WDT 
    //
    DrvWDT_Ioctl(E_WDT_IOC_STOP_TIMER, 0);
    
    //
    // Disable WDT Interrupt
    //
    DrvWDT_Ioctl(E_WDT_IOC_DISABLE_INT, 0);

    CLK->APBCLK_BITS.WDT_EN = 0;
}

//*****************************************************************************
//
//! \brief This function is used to install WDT interrupt service routine.
//!
//! \param pvWDTISR: The function pointer of the interrupt service routine
//!
//! \return None
//! 
//
//*****************************************************************************
void DrvWDT_InstallISR(WDT_CALLBACK pvWDTISR)
{
    WDT->WTCR_BITS.WTIE = 1 ;
    fnCallBack_WDT = (WDT_CALLBACK)pvWDTISR;    
}

//*****************************************************************************
//
//! \brief This function is used to operate more WDT applications, it could be 
//! the start/stop the WDT, enable/disable WDT interrupt function, enable/disable
//! WDT time-out wake up function, enable/disable system reset when WDT time-out 
//! and set the WDT time-out interval.                               
//!
//! \param uWDTCmd:   E_WDT_CMD commands,it could be the one of the follow commands 
//!                   E_WDT_IOC_START_TIMER,            
//!                   E_WDT_IOC_STOP_TIMER,    
//!                   E_WDT_IOC_ENABLE_INT,       
//!                   E_WDT_IOC_DISABLE_INT,
//!                   E_WDT_IOC_ENABLE_WAKEUP,
//!                   E_WDT_IOC_DISABLE_WAKEUP,
//!                   E_WDT_IOC_RESET_TIMER,
//!                   E_WDT_IOC_ENABLE_RESET_FUNC,
//!                   E_WDT_IOC_DISABLE_RESET_FUNC,
//!                   E_WDT_IOC_SET_INTERVAL      
//! \param uArgument: Set the argument for the specified WDT command
//!
//! \return E_SUCCESS                     Operation successful 
//!         E_DRVTIMER_CHANNEL            Invalid WDT command 
//! 
//
//*****************************************************************************
int32_t DrvWDT_Ioctl(E_WDT_CMD uWDTCmd, uint32_t uArgument)
{
    switch (uWDTCmd)
    {
        case E_WDT_IOC_START_TIMER  :
        {
            WDT->WTCR_BITS.WTE = 1;
            break ;
        }

        case E_WDT_IOC_STOP_TIMER :
        {
            WDT->WTCR_BITS.WTE = 0;
            break ;
        }

        case E_WDT_IOC_ENABLE_INT :
        {
            WDT->WTCR_BITS.WTIE = 1;
            NVIC_EnableIRQ(WDT_IRQn); 
            break ;
        }

        case E_WDT_IOC_DISABLE_INT :
        {
            WDT->WTCR_BITS.WTIE = 0;
            NVIC_DisableIRQ(WDT_IRQn); 
            break ;
        }

        case E_WDT_IOC_ENABLE_WAKEUP :
        {
            WDT->WTCR_BITS.WTWKE = 1;            
            break ;
        }

        case E_WDT_IOC_DISABLE_WAKEUP :
        {
            WDT->WTCR_BITS.WTWKE = 0;            
            break ;
        }

        case E_WDT_IOC_RESET_TIMER:
        {
            WDT->WTCR_BITS.WTR = 1;
            break ;
        }

        case E_WDT_IOC_ENABLE_RESET_FUNC :
        {
            WDT->WTCR_BITS.WTRE = 1;
            break ;
        }

        case E_WDT_IOC_DISABLE_RESET_FUNC:
        {
            WDT->WTCR_BITS.WTRE = 0;
            break ;
        }

        case E_WDT_IOC_SET_INTERVAL:
        {
            WDT->WTCR_BITS.WTIS = (E_WDT_INTERVAL)uArgument;

            break ;
        }
       
        default :
        {
            return E_DRVWDT_CMD;
        }
    }

    return E_SUCCESS;
}
