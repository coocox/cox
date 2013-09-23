#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_timer.h"
#include "xtimer.h"


//*****************************************************************************
//
// Callback Function Array.
//
//****************************************************************************
static xtEventCallback g_pfnTimerHandlerCallbacks[4] = {0};

//*****************************************************************************
//
//! \brief  Timer 0 Interrupt handler.
//!         This function is startup code handler entry.
//!
//! \param  None.
//! \return None.
//
//*****************************************************************************
void TIMER0IntHandler(void)
{
    if( g_pfnTimerHandlerCallbacks[0] != 0 )           // Valid function.
    {
        g_pfnTimerHandlerCallbacks[0](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Timer 1 Interrupt handler.
//!         This function is startup code handler entry.
//!
//! \param  None.
//! \return None.
//
//*****************************************************************************
void TIMER1IntHandler(void)
{
    if( g_pfnTimerHandlerCallbacks[1] != 0 )      // Valid function.
    {
        g_pfnTimerHandlerCallbacks[1](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Timer 2 Interrupt handler.
//!         This function is startup code handler entry.
//!
//! \param  None.
//! \return None.
//
//*****************************************************************************
void TIMER2IntHandler(void)
{
    if( g_pfnTimerHandlerCallbacks[2] != 0 )           // Valid function.
    {
        g_pfnTimerHandlerCallbacks[2](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Timer 3 Interrupt handler.
//!         This function is startup code handler entry.
//!
//! \param  None.
//! \return None.
//
//*****************************************************************************
void TIMER3IntHandler(void)
{
    if( g_pfnTimerHandlerCallbacks[3] != 0 )           // Valid function.
    {
        g_pfnTimerHandlerCallbacks[3](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the timer.
//!
//! \param [in] ulBase is the base address of the Timer port.
//! \param [in] xtPortCallback is user callback for the timer.
//!
//! \return None.
//
//*****************************************************************************
void TimerIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    switch(ulBase)
    {
        case TIMER0_BASE:                            // Register timer 0 user ISR
            {
                g_pfnTimerHandlerCallbacks[0] = pfnCallback;
                break;
            }

        case TIMER1_BASE:                            // Register timer 1 user ISR
            {
                g_pfnTimerHandlerCallbacks[1] = pfnCallback;
                break;
            }

        case TIMER2_BASE:                            // Register timer 2 user ISR
            {
                g_pfnTimerHandlerCallbacks[2] = pfnCallback;
                break;
            }

        case TIMER3_BASE:                            // Register timer 3 user ISR
            {
                g_pfnTimerHandlerCallbacks[3] = pfnCallback;
                break;
            }

        default:
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Configurate The Timer's mode and tick frequency.
//!         This function is to configurate The Timer's mode and tick frequency.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is timer channel.
//!              - \ref xTIMER_CHANNEL1 is capture channel.
//!
//! \param  [in] ulConfig is the mode Configuratation of the Timer port.
//!              Can be one of the following value:
//!              - Timer mode
//!                  - \ref xTIMER_MODE_ONESHOT
//!                  - \ref xTIMER_MODE_PERIODIC
//!                  - \ref xTIMER_MODE_CONTINUOUS
//!                  - \ref xTIMER_MODE_CAPTURE
//!              - Timer counter direction
//!                  - \ref xTIMER_COUNT_UP
//!
//! \param  [in] ulTickFreq is the tick frequency of the Timer port.
//!
//! \return None.
//!
//! \note   For LPC17xx, Only xTIMER_CHANNEL1 can be configure into Capture mode.
//
//*****************************************************************************
void TimerInitConfig(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulConfig, unsigned long ulTickFreq)
{
    unsigned long ulFre    = 0;
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT((ulChannel == xTIMER_CHANNEL0) || (ulChannel == xTIMER_CHANNEL1));
    xASSERT( (ulConfig == xTIMER_MODE_ONESHOT)    || (ulConfig == xTIMER_MODE_PERIODIC) ||
             (ulConfig == xTIMER_MODE_CONTINUOUS) || (ulConfig == xTIMER_MODE_CAPTURE) );

    // Get Timer System Clock Frequency.
    switch(ulBase)
    {
        case TIMER0_BASE:
            {
                ulFre = SysCtlPeripheralClockGet(PCLKSEL_TIMER0);
                break;
            }

        case TIMER1_BASE:
            {
                ulFre = SysCtlPeripheralClockGet(PCLKSEL_TIMER1);
                break;
            }

        case TIMER2_BASE:
            {
                ulFre = SysCtlPeripheralClockGet(PCLKSEL_TIMER2);
                break;
            }

        case TIMER3_BASE:
            {
                ulFre = SysCtlPeripheralClockGet(PCLKSEL_TIMER3);
                break;
            }
        default:
            {
                while(1);                          // Error
            }
    }

    // Configure Timer Clock
    if(ulTickFreq >= ulFre)
    {
        ulFre = 0;
    }
    else
    {
        ulFre = ulFre/ulTickFreq - 1;
    }
    TimerPrescaleSet(ulBase, ulFre);

    // Configure into timer mode
    xHWREG(ulBase + TIMER_CTCR) = 0;

    if(ulChannel == xTIMER_CHANNEL0)               // Timer Mode
    {
        // Error! Only xTIMER_CHANNEL1 can be configur into capture mode.
        if(ulConfig == xTIMER_MODE_CAPTURE)
        {
            while(1);
        }

        ulTmpReg = xHWREG(ulBase + TIMER_MCR);
        ulTmpReg &= ~(MCR_MRxR | MCR_MRxS);

        // Configure Timer mode.
        switch(ulConfig)
        {
            case xTIMER_MODE_ONESHOT:
                {
                    ulTmpReg |= MCR_MRxS;
                    xHWREG(ulBase + TIMER_MCR) = ulTmpReg;
                    break;
                }

            case xTIMER_MODE_PERIODIC:
                {
                    ulTmpReg |= MCR_MRxR;
                    xHWREG(ulBase + TIMER_MCR) = ulTmpReg;
                    break;
                }

            case xTIMER_MODE_CONTINUOUS:
                {
                    xHWREG(ulBase + TIMER_MCR) = ulTmpReg;
                    break;
                }
        }
    }
    else if(ulChannel == xTIMER_CHANNEL1)          // Capture Mode
    {
        // Error! Only xTIMER_CHANNEL1 can be configur into capture mode.
        if(ulConfig != xTIMER_MODE_CAPTURE)
        {
            while(1);
        }

        // Clear all channel match event
        xHWREG(ulBase + TIMER_MCR) = 0;
    }
}

//*****************************************************************************
//
//! \brief  Get Timer Interrupt status.
//!         This function is used to get timer interrupts status.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \return The status of timer module interrupt status.
//!         This value is the OR of the following value:
//!              - \ref TIMER_INT_MAT_CH_0
//!              - \ref TIMER_INT_MAT_CH_1
//!              - \ref TIMER_INT_MAT_CH_2
//!              - \ref TIMER_INT_MAT_CH_3
//!              - \ref TIMER_INT_CAP_CH_0
//!              - \ref TIMER_INT_CAP_CH_1
//!
//
//*****************************************************************************
unsigned long TimerIntStatusGet(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Read Interrupt status register
    return (xHWREG(ulBase + TIMER_IR));
}

//*****************************************************************************
//
//! \brief  Check Timer Interrupt Flag.
//!         This function is used to check whether special flag is set or not.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulIntFlags is the interrupt flag you want to check
//!         This value is the OR of the following value:
//!              - \ref TIMER_INT_MAT_CH_0
//!              - \ref TIMER_INT_MAT_CH_1
//!              - \ref TIMER_INT_MAT_CH_2
//!              - \ref TIMER_INT_MAT_CH_3
//!              - \ref TIMER_INT_CAP_CH_0
//!              - \ref TIMER_INT_CAP_CH_1
//!
//! \return The status of special interrupt flag.
//!         - xtrue The check flag has been set.
//!         - xflase The check flag has not been set.
//!
//
//*****************************************************************************
xtBoolean TimerIntStatusCheck(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Check interrupt status register
    if(xHWREG(ulBase + TIMER_IR) & ulIntFlags)
    {
        return (xtrue);
    }
    else
    {
        return (xfalse);
    }

}

//*****************************************************************************
//
//! \brief  Clear Timer Interrupt Flag.
//!         This function is used to clear special timer interrupt flag.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulIntFlags is the interrupt flag you want to clear.
//!         This value is the OR of the following value:
//!              - \ref TIMER_INT_MAT_CH_0
//!              - \ref TIMER_INT_MAT_CH_1
//!              - \ref TIMER_INT_MAT_CH_2
//!              - \ref TIMER_INT_MAT_CH_3
//!              - \ref TIMER_INT_CAP_CH_0
//!              - \ref TIMER_INT_CAP_CH_1
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerIntStatusClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Clear special interrupt flag by write 1 to correct bit.
    xHWREG(ulBase + TIMER_IR) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief  Start Timer
//!         This function is used to start timer module.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerStart(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Enable Timer Module.
    xHWREG(ulBase + TIMER_TCR) |= TCR_CNT_EN;
}

//*****************************************************************************
//
//! \brief  Stop Timer
//!         This function is used to stop timer module.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerStop(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Disable Timer Module.
    xHWREG(ulBase + TIMER_TCR) &= ~TCR_CNT_EN;
}

//*****************************************************************************
//
//! \brief  Reset Timer Counter.
//!         This function is used to reset timer counter.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerReset(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Reset Timer Counter.
    xHWREG(ulBase + TIMER_TCR) |=  TCR_CNT_RST;
    xHWREG(ulBase + TIMER_TCR) &= ~TCR_CNT_RST;
}

/*
MODE_COUNTER_CH0_RISING
MODE_COUNTER_CH0_FALLING
MODE_COUNTER_CH0_BOTHEDGE
MODE_COUNTER_CH1_RISING
MODE_COUNTER_CH1_FALLING
MODE_COUNTER_CH1_BOTHEDGE
*/


//*****************************************************************************
//
//! \brief  Set timer prescale value.
//!         This function is used to configure timer clock prescale value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulValue is the timer clock precsacle.
//!              0 <= ulValue <= (32-bit long maximum value)
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerPrescaleSet(unsigned long ulBase, unsigned long ulValue)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Write the prescale value
    xHWREG(ulBase + TIMER_PR) = ulValue;
}

//*****************************************************************************
//
//! \brief  Get timer prescale value.
//!         This function is used to get timer clock prescale value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \return      The timer clock precsacle.
//!              0 <= ulValue <= (32-bit long maximum value)
//!
//
//*****************************************************************************
unsigned long TimerPrescaleGet(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Read back the prescale value
    return (xHWREG(ulBase + TIMER_PR));
}

//*****************************************************************************
//
//! \brief  Set timer counter value.
//!         This function is used to set timer clock counter value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulValue is the timer counter value.
//!              0 <= ulValue <= (32-bit long maximum value)
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerLoadSet(unsigned long ulBase, unsigned long ulValue)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Write the Timer Counter value
    xHWREG(ulBase + TIMER_TC) = ulValue;
}

//*****************************************************************************
//
//! \brief  Get timer counter value.
//!         This function is used to get timer clock counter value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \return [in] The timer counter value.
//!              0 <= ulValue <= (32-bit long maximum value)
//!
//!
//
//*****************************************************************************
unsigned long TimerLoadGet(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Read the Timer Counter value
    return (xHWREG(ulBase + TIMER_TC));
}

//*****************************************************************************
//
//! \brief  Set timer channel match value.
//!         This function is used to set timer channel match value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulChs is the timer channel.
//!              This value can be one of the following value:
//!              - \ref TIMER_MAT_CH_0
//!              - \ref TIMER_MAT_CH_1
//!              - \ref TIMER_MAT_CH_2
//!              - \ref TIMER_MAT_CH_3
//!
//! \param  [in] ulValue is the timer match value.
//!              0 <= ulValue <= (32-bit long maximum value)
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerMatchValueSet(unsigned long ulBase, unsigned long ulChs, unsigned long ulValue)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT((ulBase == TIMER_MAT_CH_0) || (ulBase == TIMER_MAT_CH_1) ||
            (ulBase == TIMER_MAT_CH_2) || (ulBase == TIMER_MAT_CH_3) );

    switch(ulChs)
    {
        case TIMER_MAT_CH_0:                          // Match Channel 0
            {
                xHWREG(ulBase + TIMER_MR0) = ulValue;
                break;
            }

        case TIMER_MAT_CH_1:                          // Match Channel 0
            {
                xHWREG(ulBase + TIMER_MR1) = ulValue;
                break;
            }

        case TIMER_MAT_CH_2:                          // Match Channel 0
            {
                xHWREG(ulBase + TIMER_MR2) = ulValue;
                break;
            }

        case TIMER_MAT_CH_3:                          // Match Channel 0
            {
                xHWREG(ulBase + TIMER_MR3) = ulValue;
                break;
            }

        default:                                      // Error
            {
                while(1);
            }
    }

}

//*****************************************************************************
//
//! \brief  Get timer channel match value.
//!         This function is used to get timer channel match value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulChs is the timer channel.
//!              This value can be one of the following value:
//!              - \ref TIMER_MAT_CH_0
//!              - \ref TIMER_MAT_CH_1
//!              - \ref TIMER_MAT_CH_2
//!              - \ref TIMER_MAT_CH_3
//!
//! \return The timer match value.
//!
//
//*****************************************************************************
unsigned long  TimerMatchValueGet(unsigned long ulBase, unsigned long ulChs)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT((ulBase == TIMER_MAT_CH_0) || (ulBase == TIMER_MAT_CH_1) ||
            (ulBase == TIMER_MAT_CH_2) || (ulBase == TIMER_MAT_CH_3) );

    switch(ulChs)
    {
        case TIMER_MAT_CH_0:                          // Match Channel 0
            {
                return xHWREG(ulBase + TIMER_MR0);
                break;
            }

        case TIMER_MAT_CH_1:                          // Match Channel 2
            {
                return xHWREG(ulBase + TIMER_MR1);
                break;
            }

        case TIMER_MAT_CH_2:                          // Match Channel 2
            {
                return xHWREG(ulBase + TIMER_MR2);
                break;
            }

        case TIMER_MAT_CH_3:                          // Match Channel 3
            {
                return xHWREG(ulBase + TIMER_MR3);
                break;
            }

        default:                                      // Error
            {
                while(1);
            }
    }

}

//*****************************************************************************
//
//! \brief  Get timer current counter value.
//!         This function is used to get timer current counter value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \return The timer current counter value.
//!         0 <= ulValue <= (32-bit long maximum value).
//!
//
//*****************************************************************************
unsigned long TimerValueGet(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    // Get current counter value.
    return (xHWREG(ulBase + TIMER_TC));
}

//*****************************************************************************
//
//! \brief  Configure timer match function.
//!         This function is used to configure timer match function.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulChs is the timer channel.
//!              This value can be one of the following value:
//!              - \ref TIMER_MAT_CH_0
//!              - \ref TIMER_MAT_CH_1
//!              - \ref TIMER_MAT_CH_2
//!              - \ref TIMER_MAT_CH_3
//!
//! \param  [in] ulCfgs is the parameters for timer match mode.
//!              This value can be one of the following value:
//!              - \ref TIMER_MAT_INT        Triggle interrupt when match event occurs.
//!              - \ref TIMER_MAT_RESET      Reset counter when match event occurs.
//!              - \ref TIMER_MAT_STOP       Stop counter when match event occurs.
//!              - \ref TIMER_MAT_PIN_NONE   No action when match event occurs.
//!              - \ref TIMER_MAT_PIN_LOW    Set pin low when match event occurs.
//!              - \ref TIMER_MAT_PIN_HIGH   Set pin High when match event occurs.
//!              - \ref TIMER_MAT_PIN_TOGGLE Toggle pin value when match event occurs.
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerMatchCfg(unsigned long ulBase, unsigned long ulChs, unsigned long ulCfgs)
{
    unsigned long i        = 0;
    unsigned long ulTmpReg = 0;
    unsigned long Tmp      = 0;

    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    xASSERT( (ulChs & ~( TIMER_MAT_CH_0 | TIMER_MAT_CH_1 |
                TIMER_MAT_CH_2 | TIMER_MAT_CH_3)) == 0 );

    xASSERT( (ulCfgs & ~(TIMER_MAT_MASK | TIMER_MAT_PIN_MASK)) == 0 );

    for(i = 0; i < 4; i++)
    {
        if( ulChs & (1<<i) )                         // Find Match Channel
        {
            /*********** Configure MCR register ******************/
            if(ulCfgs & TIMER_MAT_MASK)
            {
                Tmp = ulCfgs & BIT_MASK(32, 7, 0);
                ulTmpReg = xHWREG(ulBase + TIMER_MCR);
                ulTmpReg &= ~( (MCR_MRxI | MCR_MRxR | MCR_MRxS) << i*3 );
                ulTmpReg |= (Tmp << i*3);
                xHWREG(ulBase + TIMER_MCR) = ulTmpReg;
            }

            /*********** Configure EMR register ******************/
            if(ulCfgs & TIMER_MAT_PIN_MASK)          // Enable Match Pin output
            {
                if(ulCfgs & TIMER_MAT_PIN_NONE)      // Disable Match Pin output
                {
                    xHWREG(ulBase + TIMER_EMR) &= ~( EMR_EM0 << i );
                    xHWREG(ulBase + TIMER_EMR) &= ~( EMR_EMC0_M << (i*2) );
                }
                else
                {
                    Tmp = (ulCfgs >> 8) & BIT_MASK(32, 7, 0);
                    ulTmpReg = xHWREG(ulBase + TIMER_EMR);
                    ulTmpReg |= ( EMR_EM0 << i );
                    ulTmpReg &= ~( EMR_EMC0_M << (2*i) );
                    ulTmpReg |= (Tmp << (2*i));
                    xHWREG(ulBase + TIMER_EMR) = ulTmpReg;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \brief  Configure timer capture function.
//!         This function is used to configure timer capture function.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulChs is the timer channel.
//!              This value can be one of the following value:
//!              - \ref TIMER_CAP_CH_0
//!              - \ref TIMER_CAP_CH_1
//!
//! \param  [in] ulCfgs is the parameters for timer match mode.
//!              This value can be one of the following value:
//!              - \ref TIMER_CFG_CAP_RISING  Capture rising edge signal.
//!              - \ref TIMER_CFG_CAP_FALLING Capture falling edge signal.
//!              - \ref TIMER_CFG_CAP_INT     Triggle interrupt when capture event occurs.
//!
//! \return None.
//! \note   - \ref TIMER_CFG_CAP_INT can be used with - \ref TIMER_CFG_CAP_RISING
//!         and - \ref TIMER_CFG_CAP_FALLING, i.e:
//!         TimerCaptureCfg(TIMER0_BASE, TIMER_CAP_CH_0, TIMER_CFG_CAP_RISING | TIMER_CFG_CAP_INT);
//!
//
//*****************************************************************************
void TimerCaptureCfg(unsigned long ulBase, unsigned long ulChs, unsigned long ulCfgs)
{
    unsigned long ulTmpReg = 0;
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT( (ulChs & ~( TIMER_CAP_CH_0 | TIMER_CAP_CH_1 )) == 0 );
    xASSERT( (ulCfgs & ~( TIMER_CFG_CAP_RISING | TIMER_CFG_CAP_FALLING | TIMER_CFG_CAP_INT )) == 0 );

    // Configure Capture Channel 0
    if(ulChs & TIMER_CAP_CH_0)
    {
        ulTmpReg = xHWREG(ulBase + TIMER_CCR);
        ulTmpReg &= ~(CCR_CAP0RE | CCR_CAP0FE | CCR_CAP0IE);
        ulTmpReg |= ulCfgs;
        xHWREG(ulBase + TIMER_CCR) = ulTmpReg;
    }

    // Configure Capture Channel 1
    if(ulChs & TIMER_CAP_CH_1)
    {
        ulTmpReg = xHWREG(ulBase + TIMER_CCR);
        ulTmpReg &= ~(CCR_CAP1RE | CCR_CAP1FE | CCR_CAP1IE);
        ulTmpReg |= (ulCfgs << 3);
        xHWREG(ulBase + TIMER_CCR) = ulTmpReg;
    }
}

//*****************************************************************************
//
//! \brief  Get timer capture value.
//!         This function is used to get capture time value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulChs is the timer channel.
//!              This value can be one of the following value:
//!              - \ref TIMER_CAP_CH_0
//!              - \ref TIMER_CAP_CH_1
//!
//! \return The capture value.
//!
//
//*****************************************************************************
unsigned long TimerCapValueGet(unsigned long ulBase, unsigned long ulChs)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );

    xASSERT( (ulChs & ~( TIMER_CAP_CH_0 | TIMER_CAP_CH_1 )) == 0 );

    switch(ulChs)
    {
        case TIMER_CAP_CH_0:
            {
                return xHWREG(ulBase + TIMER_CR0);
            }

        case TIMER_CAP_CH_1:
            {
                return xHWREG(ulBase + TIMER_CR1);
            }
        default:
            {
                while(1);
            }
    }
}



//*****************************************************************************
//
//! \brief  Configure timer capture function.
//!         This function is used to configure timer capture function.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              This value can be one of the following value:
//!              - \ref TIMER0_BASE, - \ref TIMER1_BASE,
//!              - \ref TIMER2_BASE, - \ref TIMER3_BASE.
//!
//! \param  [in] ulChs is the timer channel.
//!              This value can be one of the following value:
//!              - \ref TIMER_CAP_CH_0
//!              - \ref TIMER_CAP_CH_1
//!
//! \param  [in] ulCfg is the parameters for configure timer counter mode.
//!              This value can be one of the following value:
//!              - \ref TIMER_CFG_CNT_CAP0_RISING     Capture 0 rising edge increase counter.
//!              - \ref TIMER_CFG_CNT_CAP0_FALLING    Capture 0 falling edge increase counter.
//!              - \ref TIMER_CFG_CNT_CAP0_BOTH       Capture 0 both edge increase counter.
//!              - \ref TIMER_CFG_CNT_CAP1_RISING     Capture 1 rising edge increase counter.
//!              - \ref TIMER_CFG_CNT_CAP1_FALLING    Capture 1 falling edge increase counter.
//!              - \ref TIMER_CFG_CNT_CAP1_BOTH       Capture 1 both edge increase counter.
//!
//! \return None.
//!
//
//*****************************************************************************
void TimerCounterCfg(unsigned long ulBase, unsigned long ulCfg)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT( (ulCfg & ~BIT_MASK(32, 2, 0)) == 0 );

    // Configure Timer Counter/Timer Register.
    xHWREG(ulBase + TIMER_CTCR) = ulCfg;
    xHWREG(ulBase + TIMER_CCR)  = 0x00;
}

//*****************************************************************************
//
//! \brief Enable The Timer counter interrupt.
//!        This function is to enable The Timer counter interrupt.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE, - \ref xTIMER1_BASE,
//!             - \ref xTIMER2_BASE, - \ref xTIMER3_BASE.
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulIntFlags is the interrupt type of the Timer port.
//!             - \ref xTIMER_INT_MATCH       Match interrupt event.
//!             - \ref xTIMER_INT_CAP_EVENT   Input capture interrupt event.
//!
//! \return None.
//
//*****************************************************************************
void xTimerIntEnable(unsigned long ulBase, unsigned long ulChannel, unsigned long ulIntFlags)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT((ulChannel == xTIMER_CHANNEL0) || (ulChannel == xTIMER_CHANNEL1));
    (void) ulIntFlags;

    if(ulChannel == xTIMER_CHANNEL0)               // Timer Mode
    {
        ulTmpReg = xHWREG(ulBase + TIMER_MCR);
        ulTmpReg |= MCR_MR0I;
        xHWREG(ulBase + TIMER_MCR) = ulTmpReg;
    }
    else if(ulChannel == xTIMER_CHANNEL1)          // Capture Mode
    {
        ulTmpReg = xHWREG(ulBase + TIMER_CCR);
        ulTmpReg |= CCR_CAP0IE;
        xHWREG(ulBase + TIMER_CCR) = ulTmpReg;
    }
}

//*****************************************************************************
//
//! \brief Disable The Timer counter interrupt.
//!        This function is to disable The Timer counter interrupt.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE, - \ref xTIMER1_BASE,
//!             - \ref xTIMER2_BASE, - \ref xTIMER3_BASE.
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulIntFlags is the interrupt type of the Timer port.
//!             - \ref xTIMER_INT_MATCH       Match interrupt event.
//!             - \ref xTIMER_INT_CAP_EVENT   Input capture interrupt event.
//!
//! \return None.
//
//*****************************************************************************
void xTimerIntDisable(unsigned long ulBase, unsigned long ulChannel, unsigned long ulIntFlags)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT((ulChannel == xTIMER_CHANNEL0) || (ulChannel == xTIMER_CHANNEL1));
    (void) ulIntFlags;

    if(ulChannel == xTIMER_CHANNEL0)               // Timer Mode
    {
        ulTmpReg = xHWREG(ulBase + TIMER_MCR);
        ulTmpReg &= ~MCR_MR0I;
        xHWREG(ulBase + TIMER_MCR) = ulTmpReg;
    }
    else if(ulChannel == xTIMER_CHANNEL1)          // Capture Mode
    {
        ulTmpReg = xHWREG(ulBase + TIMER_CCR);
        ulTmpReg &= ~CCR_CAP0IE;
        xHWREG(ulBase + TIMER_CCR) = ulTmpReg;
    }
}

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status.
//!        This function is to get timer interrupt status.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE, - \ref xTIMER1_BASE,
//!             - \ref xTIMER2_BASE, - \ref xTIMER3_BASE.
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulIntFlags is the interrupt type of the Timer port.
//!             - \ref xTIMER_INT_MATCH       Match interrupt event.
//!             - \ref xTIMER_INT_CAP_EVENT   Input capture interrupt event.
//!
//! \return the Status of The Timer counter interrupt.
//
//*****************************************************************************
xtBoolean xTimerStatusGet(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulIntFlags)
{
    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT((ulChannel == xTIMER_CHANNEL0) || (ulChannel == xTIMER_CHANNEL1));
    (void) ulIntFlags;

    if(ulChannel == xTIMER_CHANNEL0)               // Timer Mode
    {
        return TimerIntStatusCheck(ulBase, TIMER_INT_MAT_CH_0);
    }
    else if(ulChannel == xTIMER_CHANNEL1)          // Capture Mode
    {
        return TimerIntStatusCheck(ulBase, TIMER_INT_CAP_CH_0);
    }
    else
    {
        return (xfalse);                           // Error
    }
}

//*****************************************************************************
//
//! \brief Select The Timer counter capture detect edge.
//!        This function is to select The Timer counter capture detect edge.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulEdge is the capture detect mode and detect edge of the
//!             Timer port.
//!             This value can be logic OR of the following value:
//!             - \ref xTIMER_CAP_RISING
//!             - \ref xTIMER_CAP_FALLING
//!             - \ref xTIMER_CAP_BOTH
//!
//! \return None.
//
//*****************************************************************************
void xTimerCaptureEdgeSelect(unsigned long ulBase, unsigned long ulChannel,
                                    unsigned long ulEdge)
{
    // Avoid compiler warning
    (void) ulChannel;

    // Check the parameters.
    xASSERT((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
            (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE) );
    xASSERT(ulChannel == xTIMER_CHANNEL1);

    if (ulEdge != 0)
    {
        // Configure Capture Edge
        TimerCaptureCfg(ulBase, TIMER_CAP_CH_0, ulEdge);
    }

}

//*****************************************************************************
//
//! \brief  Select The Timer counter detect phase.
//!         This function is to select The Timer counter detect phase.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is general timer channel.
//!              - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param  [in] ulPhase is the counter detect phase of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_COUNTER_RISING
//!              - \ref xTIMER_COUNTER_FALLING
//!
//! \return None.
//!
//! \note   This function configure input capture pin 0 for counter clock.
//
//*****************************************************************************
void xTimerCounterDetectPhaseSelect(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulPhase)
{

    // Avoid compiler warning
    (void) ulChannel;

    // Check the parameters.
    xASSERT( (ulBase == xTIMER0_BASE) ||
             (ulBase == xTIMER1_BASE) ||
             (ulBase == xTIMER2_BASE) ||
             (ulBase == xTIMER3_BASE) );

    xASSERT( (ulChannel == xTIMER0_BASE) ||
             (ulChannel == xTIMER1_BASE) );

    xASSERT( (ulPhase == xTIMER_COUNTER_RISING) ||
             (ulPhase == xTIMER_COUNTER_FALLING) );

    if(ulPhase == xTIMER_COUNTER_FALLING) // Falling edge increment timer counter
    {
        xHWREG(ulBase + TIMER_CTCR) = 0x10;
    }
    else                                  // Rising edge increment timer counter
    {
        xHWREG(ulBase + TIMER_CTCR) = 0x01;
    }
}
