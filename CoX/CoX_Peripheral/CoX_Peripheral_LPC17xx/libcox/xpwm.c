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
#include "xhw_pwm.h"
#include "xpwm.h"

static unsigned long _PWMFrequency = 0;

//*****************************************************************************
//
// An array is PWM callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnPWMHandlerCallbacks = 0;

//*****************************************************************************
//
//! \brief  PWM interrupt handler.
//!         This function is the PWM interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//! \return None.
//!
//
//*****************************************************************************
void PWM1IntHandler(void)
{
    if(g_pfnPWMHandlerCallbacks != 0)
    {
        g_pfnPWMHandlerCallbacks(0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Register user's interrupt callback function for the PWM.
//!
//! \param  [in] ulBase is the base address of PWM module.
//!              this value can be one of the following value:
//!              - \ref xPWM1_BASE
//!
//! \param  [in] xtPortCallback is user callback for the PWM.
//!
//! \return None.
//
//*****************************************************************************
void xPWMIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    // Avoid Compiler warning
    (void)ulBase;

    // Check the parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT(pfnCallback != 0);

    g_pfnPWMHandlerCallbacks = pfnCallback;
}

//*****************************************************************************
//
//! \brief  Set PWM prescale value
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulValue is clock prescale value.
//!              It's a 32-bit value.
//!
//! \return None.
//
//*****************************************************************************
void PWMPrescaleValueSet(unsigned long ulBase, unsigned long ulValue)
{
    // Check the parameters.
    xASSERT(ulBase == PWM1_BASE);

    xHWREG(ulBase + PWM_PR) = ulValue;
}

//*****************************************************************************
//
//! \brief  Clear PWM interrupt status flag.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulIntFlags is the interrupt flag, which can be logical OR of
//!              the following value:
//!              - \ref PWM_INT_CH_0
//!              - \ref PWM_INT_CH_1
//!              - \ref PWM_INT_CH_2
//!              - \ref PWM_INT_CH_3
//!              - \ref PWM_INT_CH_4
//!              - \ref PWM_INT_CH_5
//!              - \ref PWM_INT_CH_6
//!              - \ref PWM_INT_CAP_0
//!              - \ref PWM_INT_CAP_1
//! \return None.
//
//*****************************************************************************
void PWMIntStatusClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT((ulIntFlags & ~ PWM_INT_FLAG_MASK) == 0);

    // Clear Interrupt flag
    xHWREG(PWM1_BASE + PWM_IR) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief  Get PWM interrupt status.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \return  The PWM interrupt status, which consists of the following value:
//!              - \ref PWM_INT_CH_0
//!              - \ref PWM_INT_CH_1
//!              - \ref PWM_INT_CH_2
//!              - \ref PWM_INT_CH_3
//!              - \ref PWM_INT_CH_4
//!              - \ref PWM_INT_CH_5
//!              - \ref PWM_INT_CH_6
//!              - \ref PWM_INT_CAP_0
//!              - \ref PWM_INT_CAP_1
//
//*****************************************************************************
unsigned long PWMIntStatusGet(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);

    return xHWREG(PWM1_BASE + PWM_IR);

}

//*****************************************************************************
//
//! \brief  Check PWM interrupt status.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the
//!              following value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulIntFlags is the interrupt flag, which can be logical OR of
//!              the following value:
//!              - \ref PWM_INT_CH_0
//!              - \ref PWM_INT_CH_1
//!              - \ref PWM_INT_CH_2
//!              - \ref PWM_INT_CH_3
//!              - \ref PWM_INT_CH_4
//!              - \ref PWM_INT_CH_5
//!              - \ref PWM_INT_CH_6
//!              - \ref PWM_INT_CAP_0
//!              - \ref PWM_INT_CAP_1
//!
//! \return The status of check interrupt flag.
//!         - xtrue  The check flag has been set.
//!         - xflase The check flag has not been set.
//
//*****************************************************************************
xtBoolean PWMIntStatusCheck(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT((ulIntFlags & ~ PWM_INT_FLAG_MASK) == 0);

    // Check flag.
    if( xHWREG(PWM1_BASE + PWM_IR) & ulIntFlags )
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
//! \brief  Enable PWM counter.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the
//!              following value:
//!              - \ref PWM1_BASE
//!
//! \return None.
//
//*****************************************************************************
void PWMCounterEnable(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);

    // Enable counter
    xHWREG(PWM1_BASE + PWM_TCR) |= TCR_CNT_EN;
}

//*****************************************************************************
//
//! \brief  Disable PWM counter.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the
//!              following value:
//!              - \ref PWM1_BASE
//!
//! \return None.
//
//*****************************************************************************
void PWMCounterDisable(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);

    // Disable counter
    xHWREG(PWM1_BASE + PWM_TCR) &= ~TCR_CNT_EN;
}

//*****************************************************************************
//
//! \brief  Start PWM
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the
//!              following value:
//!              - \ref PWM1_BASE
//!
//! \return None.
//
//*****************************************************************************
void PWMStart(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);

    // Enable counter
    // Enable PWM mode
    xHWREG(PWM1_BASE + PWM_TCR) = TCR_PWM_EN | TCR_CNT_EN;
}

//*****************************************************************************
//
//! \brief  Stop PWM
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the
//!              following value:
//!              - \ref PWM1_BASE
//!
//! \return None.
//
//*****************************************************************************
void PWMStop(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);

    // Disable counter
    // Enable PWM mode
    xHWREG(PWM1_BASE + PWM_TCR) = TCR_PWM_EN;
}

//*****************************************************************************
//
//! \brief  Reset PWM counter.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the
//!              following value:
//!              - \ref PWM1_BASE
//!
//! \return None.
//
//*****************************************************************************
void PWMCounterReset(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);

    // Reset pwm counter
    xHWREG(PWM1_BASE + PWM_TCR) |=  TCR_CNT_RST;
    xHWREG(PWM1_BASE + PWM_TCR) &= ~TCR_CNT_RST;
}

//*****************************************************************************
//
//! \brief  Configurate PWM match function.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulCh is PWM channel, which can be one of the following value:
//!              - \ref PWM_CH_0
//!              - \ref PWM_CH_1
//!              - \ref PWM_CH_2
//!              - \ref PWM_CH_3
//!              - \ref PWM_CH_4
//!              - \ref PWM_CH_5
//!              - \ref PWM_CH_6
//!
//! \param  [in] ulCfg is pwm configure parameters, which can be the logical
//!              OR of the following value:
//!              - \ref PWM_MATCH_INT_EN
//!              - \ref PWM_MATCH_INT_DIS
//!              - \ref PWM_MATCH_RESET_EN
//!              - \ref PWM_MATCH_RESET_DIS
//!              - \ref PWM_MATCH_STOP_EN
//!              - \ref PWM_MATCH_STOP_DIS
//!
//! \return None.
//
//*****************************************************************************
void PWMMatchCfg(unsigned long ulBase, unsigned long ulCh, unsigned long ulCfg)
{
    unsigned long i        = 0;
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT( (ulCh & ~( PWM_CH_0 | PWM_CH_1 | PWM_CH_2 | PWM_CH_3 |
                       PWM_CH_4 | PWM_CH_5 | PWM_CH_6 )) == 0);

    for(i = 0; i < 8; i++)
    {
        if((1<<i) & ulCh)
        {
            // Configure pwm match event(interrupt/reset/stop)
            ulTmpReg = xHWREG(PWM1_BASE + PWM_MCR);
            ulTmpReg &= ~((ulCfg >> 8) & 0xFF);
            ulTmpReg |=  ((ulCfg >> 0) & 0xFF);
            xHWREG(PWM1_BASE + PWM_MCR) = ulTmpReg;
        }
    }
}

//*****************************************************************************
//
//! \brief  Set PWM match value.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulCh is PWM channel, which can be one of the following value:
//!              - \ref PWM_CH_0
//!              - \ref PWM_CH_1
//!              - \ref PWM_CH_2
//!              - \ref PWM_CH_3
//!              - \ref PWM_CH_4
//!              - \ref PWM_CH_5
//!              - \ref PWM_CH_6
//!
//! \param  [in] ulValue is the PWM channel match value.
//!              It's a 32-bit value.
//!
//! \return None.
//
//*****************************************************************************
void PWMMatchUpdate(unsigned long ulBase, unsigned long ulCh, unsigned long ulValue)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT( (ulCh == PWM_CH_0) ||
             (ulCh == PWM_CH_1) ||
             (ulCh == PWM_CH_2) ||
             (ulCh == PWM_CH_3) ||
             (ulCh == PWM_CH_4) ||
             (ulCh == PWM_CH_5) ||
             (ulCh == PWM_CH_6) );

    switch(ulCh)
    {
        case PWM_CH_0:
            {
                xHWREG(PWM1_BASE + PWM_MR0) = ulValue;
                break;
            }
        case PWM_CH_1:
            {
                xHWREG(PWM1_BASE + PWM_MR1) = ulValue;
                break;
            }
        case PWM_CH_2:
            {
                xHWREG(PWM1_BASE + PWM_MR2) = ulValue;
                break;
            }
        case PWM_CH_3:
            {
                xHWREG(PWM1_BASE + PWM_MR3) = ulValue;
                break;
            }
        case PWM_CH_4:
            {
                xHWREG(PWM1_BASE + PWM_MR4) = ulValue;
                break;
            }
        case PWM_CH_5:
            {
                xHWREG(PWM1_BASE + PWM_MR5) = ulValue;
                break;
            }
        case PWM_CH_6:
            {
                xHWREG(PWM1_BASE + PWM_MR6) = ulValue;
                break;
            }

        default:                         // Error
            {
                while(1);
            }
    }

    // Write Latch Register.
    xHWREG(PWM1_BASE + PWM_LER) |= ulCh;
}

//*****************************************************************************
//
//! \brief  Enable PWM channel signal output.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulCh is PWM channel, which can be the logical OR of the
//!              following value:
//!              - \ref PWM_CH_0
//!              - \ref PWM_CH_1
//!              - \ref PWM_CH_2
//!              - \ref PWM_CH_3
//!              - \ref PWM_CH_4
//!              - \ref PWM_CH_5
//!              - \ref PWM_CH_6
//!
//! \return None.
//
//*****************************************************************************
void PWMOutPutEnable(unsigned long ulBase, unsigned long ulChs)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT( (ulChs &~ ( PWM_CH_0 | PWM_CH_1 | PWM_CH_2 | PWM_CH_3 |
                       PWM_CH_4 | PWM_CH_5 | PWM_CH_6 )) == 0);

    xHWREG(PWM1_BASE + PWM_PCR) |= (ulChs<<8);
}

//*****************************************************************************
//
//! \brief  Disable PWM channel signal output.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulCh is PWM channel, which can be the logical OR of the
//!              following value:
//!              - \ref PWM_CH_0
//!              - \ref PWM_CH_1
//!              - \ref PWM_CH_2
//!              - \ref PWM_CH_3
//!              - \ref PWM_CH_4
//!              - \ref PWM_CH_5
//!              - \ref PWM_CH_6
//!
//! \return None.
//
//*****************************************************************************
void PWMOutPutDisable(unsigned long ulBase, unsigned long ulChs)
{
     // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT( (ulChs &~ ( PWM_CH_0 | PWM_CH_1 | PWM_CH_2 | PWM_CH_3 |
                       PWM_CH_4 | PWM_CH_5 | PWM_CH_6 )) == 0);

    xHWREG(PWM1_BASE + PWM_PCR) &= ~(ulChs<<8);
}

//*****************************************************************************
//
//! \brief  Configure PWM channel output edge.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulCh is PWM channel, which can be the logical OR of the
//!              following value:
//!              - \ref PWM_CH_0
//!              - \ref PWM_CH_1
//!              - \ref PWM_CH_2
//!              - \ref PWM_CH_3
//!              - \ref PWM_CH_4
//!              - \ref PWM_CH_5
//!              - \ref PWM_CH_6
//!
//! \param  [in] ulCfg is PWM Configure parameter, which can be one of the
//!              following value:
//!              - \ref PWM_EDGE_DOUBLE
//!              - \ref PWM_EDGE_SINGLE
//!
//! \return None.
//
//*****************************************************************************
void PWMEdgeCfg(unsigned long ulBase, unsigned long ulChs, unsigned long ulCfg)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT( (ulChs &~ ( PWM_CH_0 | PWM_CH_1 | PWM_CH_2 | PWM_CH_3 |
                       PWM_CH_4 | PWM_CH_5 | PWM_CH_6 )) == 0);

    switch(ulCfg)
    {
        case PWM_EDGE_DOUBLE:
            {
                xHWREG(PWM1_BASE + PWM_PCR) |= ulChs;
                break;
            }

        case PWM_EDGE_SINGLE:
            {
                xHWREG(PWM1_BASE + PWM_PCR) &= ~ulChs;
                break;
            }
        default:                         // Error
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Configure PWM capture channel mode.
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulCfg is PWM capture configure parameter, which can be logical OR
//!              of the following value:
//!              - \ref CH0_FALLING_SAMPLE_EN
//!              - \ref CH0_FALLING_SAMPLE_DIS
//!              - \ref CH0_RISING_SAMPLE_EN
//!              - \ref CH0_RISING_SAMPLE_DIS
//!              - \ref CH0_EDGE_EVENT_INT_EN
//!              - \ref CH0_EDGE_EVENT_INT_DIS
//!              - \ref CH1_FALLING_SAMPLE_EN
//!              - \ref CH1_FALLING_SAMPLE_DIS
//!              - \ref CH1_RISING_SAMPLE_EN
//!              - \ref CH1_RISING_SAMPLE_DIS
//!              - \ref CH1_EDGE_EVENT_INT_EN
//!              - \ref CH1_EDGE_EVENT_INT_DIS
//!
//! \return None.
//
//*****************************************************************************
void PWMCapCfg(unsigned long ulBase, unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT( (ulCfg & ~(CH0_FALLING_SAMPLE_EN   | CH0_FALLING_SAMPLE_DIS  |
                        CH0_RISING_SAMPLE_EN    | CH0_RISING_SAMPLE_DIS   |
                        CH0_EDGE_EVENT_INT_EN   | CH0_EDGE_EVENT_INT_DIS  |
                        CH1_FALLING_SAMPLE_EN   | CH1_FALLING_SAMPLE_DIS  |
                        CH1_RISING_SAMPLE_EN    | CH1_RISING_SAMPLE_DIS   |
                        CH1_EDGE_EVENT_INT_EN   | CH1_EDGE_EVENT_INT_DIS  )) == 0 );

    // Configure capture channel 0/1 toggle mode (falling/rising/both edge).
    ulTmpReg = xHWREG(ulBase + PWM_CCR);
    ulTmpReg &= ~((ulCfg >> 8) & 0xFF);
    ulTmpReg |=  ((ulCfg >> 0) & 0xFF);
    xHWREG(ulBase + PWM_CCR) = ulTmpReg;

}

//*****************************************************************************
//
//! \brief  Get PWM capture value
//!
//! \param  [in] ulBase is the PWM base address, which can be one of the following
//!              value:
//!              - \ref PWM1_BASE
//!
//! \param  [in] ulCh is PWM capture channel ID, which can be one of the 
//!              following value:
//!              - \ref PWM_CAP_0
//!              - \ref PWM_CAP_1
//!
//! \return The capture event time stamp.
//
//*****************************************************************************
unsigned long PWMCapValueGet(unsigned long ulBase, unsigned long ulCh)
{
    // Check input parameters.
    xASSERT(ulBase == PWM1_BASE);
    xASSERT( (ulCh == PWM_CAP_0) || (ulCh == PWM_CAP_1) );

    switch(ulCh)
    {
        case PWM_CAP_0:
            {
                return xHWREG(ulBase + PWM_CR0);
            }
        case PWM_CAP_1:
            {
                return xHWREG(ulBase + PWM_CR1);
            }
        default:
            {
                while(1); // Error
            }
    }
}

//*****************************************************************************
//
//! \brief  Enable the PWM interrupt of the PWM module.
//!         This function is to enable the PWM interrupt of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulIntType is the PWM channel interrupt type.
//!              This value can be:
//!              - \ref xPWM_INT_PWM
//!
//! \return None.
//
//*****************************************************************************
void xPWMIntEnable(unsigned long ulBase, unsigned long ulChannel, unsigned long ulIntType)
{

    // Avoid Compiler warning
    (void) ulIntType;

    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT(ulIntType == xPWM_INT_PWM);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );

    switch(ulChannel)
    {
        case xPWM_CHANNEL0:
            {
                xHWREG(PWM1_BASE + PWM_MCR) |= MCR_PWMMR0I;
                break;
            }
        case xPWM_CHANNEL1:
            {
                xHWREG(PWM1_BASE + PWM_MCR) |= MCR_PWMMR1I;
                break;
            }
        case xPWM_CHANNEL2:
            {
                xHWREG(PWM1_BASE + PWM_MCR) |= MCR_PWMMR2I;
                break;
            }
        case xPWM_CHANNEL3:
            {
                xHWREG(PWM1_BASE + PWM_MCR) |= MCR_PWMMR3I;
                break;
            }
        case xPWM_CHANNEL4:
            {
                xHWREG(PWM1_BASE + PWM_MCR) |= MCR_PWMMR4I;
                break;
            }
        case xPWM_CHANNEL5:
            {
                xHWREG(PWM1_BASE + PWM_MCR) |= MCR_PWMMR5I;
                break;
            }
        case xPWM_CHANNEL6:
            {
                xHWREG(PWM1_BASE + PWM_MCR) |= MCR_PWMMR6I;
                break;
            }
    }
}

//*****************************************************************************
//
//! \brief  Disable the PWM interrupt of the PWM module.
//!         This function is to disable the PWM interrupt of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulIntType is the PWM channel interrupt type.
//!              This value can be:
//!              - \ref xPWM_INT_PWM
//!
//! \return None.
//
//*****************************************************************************
void xPWMIntDisable(unsigned long ulBase, unsigned long ulChannel, unsigned long ulIntType)
{
    // Avoid Compiler warning
    (void) ulIntType;

    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT(ulIntType == xPWM_INT_PWM);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );

    switch(ulChannel)
    {
        case xPWM_CHANNEL0:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~MCR_PWMMR0I;
                break;
            }
        case xPWM_CHANNEL1:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~MCR_PWMMR1I;
                break;
            }
        case xPWM_CHANNEL2:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~MCR_PWMMR2I;
                break;
            }
        case xPWM_CHANNEL3:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~MCR_PWMMR3I;
                break;
            }
        case xPWM_CHANNEL4:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~MCR_PWMMR4I;
                break;
            }
        case xPWM_CHANNEL5:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~MCR_PWMMR5I;
                break;
            }
        case xPWM_CHANNEL6:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~MCR_PWMMR6I;
                break;
            }
    }
}

//*****************************************************************************
//
//! \brief  Initialize and configure the PWM module.
//!         This function is to initialize and configure channel of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulConfig is the configuration of PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_ONE_SHOT_MODE     
//!              - \ref xPWM_TOGGLE_MODE        
//!              More information, please reference macro define section.
//!
//! \return None.
//
//*****************************************************************************
void xPWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulConfig)
{
    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );
    xASSERT((ulConfig == xPWM_ONE_SHOT_MODE) || (ulConfig == xPWM_TOGGLE_MODE));

    switch(ulChannel)
    {
        case xPWM_CHANNEL0:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~(MCR_PWMMR0R | MCR_PWMMR0S);
                xHWREG(PWM1_BASE + PWM_MCR) |= ulConfig;
                break;
            }
        case xPWM_CHANNEL1:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~(MCR_PWMMR1R | MCR_PWMMR1S);
                xHWREG(PWM1_BASE + PWM_MCR) |= ulConfig;
                break;
            }
        case xPWM_CHANNEL2:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~(MCR_PWMMR2R | MCR_PWMMR2S);
                xHWREG(PWM1_BASE + PWM_MCR) |= ulConfig;
                break;
            }
        case xPWM_CHANNEL3:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~(MCR_PWMMR3R | MCR_PWMMR3S);
                xHWREG(PWM1_BASE + PWM_MCR) |= ulConfig;
                break;
            }
        case xPWM_CHANNEL4:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~(MCR_PWMMR4R | MCR_PWMMR4S);
                xHWREG(PWM1_BASE + PWM_MCR) |= ulConfig;
                break;
            }
        case xPWM_CHANNEL5:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~(MCR_PWMMR5R | MCR_PWMMR5S);
                xHWREG(PWM1_BASE + PWM_MCR) |= ulConfig;
                break;
            }
        case xPWM_CHANNEL6:
            {
                xHWREG(PWM1_BASE + PWM_MCR) &= ~(MCR_PWMMR6R | MCR_PWMMR6S);
                xHWREG(PWM1_BASE + PWM_MCR) |= ulConfig;
                break;
            }
    }
}

//*****************************************************************************
//
//! \brief  Set the PWM frequency of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulConfig is the configuration of PWM channel's frequency.
//!              - \ref xPWM_FREQ_CONFIG(a,b,c) 
//!              \b a is The Divider value, \b b is The PreScale value
//!              \b c is PWM Counter value
//!
//! \return the Actual Frequency of PWM.
//! 
//
//*****************************************************************************
unsigned long xPWMFrequencyConfig(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulConfig)
{
    // Avoid compiler warning
    (void) ulChannel;

    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );

    // Configure PWM prescale register
    xHWREG(ulBase + PWM_PR) = ulConfig;

    // Get PWM counter frequency.
    //ulPwmFre = SysCtlPeripheralClockGet(PCLKSEL_PWM1);

    return (SysCtlPeripheralClockGet(PCLKSEL_PWM1)/ulConfig);
}

//*****************************************************************************
//
//! \brief  Set the PWM frequency of the PWM module.
//!         This function is to set the PWM frequency of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulFrequency is the PWM frequency of PWM channel.
//!              The ulFrequency parameter can be values: Any values,
//!              ulFrequency > 0 && ulFrequency < PWM module input clock.
//!
//! \return The Actual Frequency of PWM Module.
//
//*****************************************************************************
unsigned long xPWMFrequencySet(unsigned long ulBase,unsigned long ulChannel,
        unsigned long ulFrequency)
{
    unsigned long ulPwmFre = 0;

    // Avoid compiler warning
    (void) ulChannel;

    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );

    // Get PWM input clock frequency.
    ulPwmFre = SysCtlPeripheralClockGet(PCLKSEL_PWM1);
    if(ulPwmFre < ulFrequency)
    {
        while(1); // Error
    }
    
    // Record the target frequency
    _PWMFrequency = ulFrequency;

    // Configure PWM prescale register
    xHWREG(ulBase + PWM_PR) = ((ulPwmFre/ulFrequency) - 1);

    return (ulFrequency);
}

//*****************************************************************************
//
//! \brief  Get the PWM frequency of the PWM module.
//!         This function is to get the PWM frequency of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return The Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long xPWMFrequencyGet(unsigned long ulBase, unsigned long ulChannel)
{
    // Avoid compiler warning
    (void) ulBase;
    (void) ulChannel;

    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );

    return (_PWMFrequency);
}

//*****************************************************************************
//
//! \brief  Start the PWM of the PWM module.
//!         This function is to start the PWM of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return None.
//
//*****************************************************************************
void xPWMStart(unsigned long ulBase, unsigned long ulChannel)
{
    // Avoid compiler warning
    (void) ulChannel;

    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );

    // 1: Enable Counter
    // 2: Enable PWM mode
    xHWREG(ulBase + PWM_TCR) = TCR_CNT_EN | TCR_PWM_EN;
}

//*****************************************************************************
//
//! \brief  Stop the PWM of the PWM module.
//!         This function is to stop the PWM of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return None.
//
//*****************************************************************************
void xPWMStop(unsigned long ulBase, unsigned long ulChannel)
{
    // Avoid compiler warning
    (void) ulChannel;

    // Check input parameters.
    xASSERT(ulBase == xPWM1_BASE);
    xASSERT( (ulChannel == xPWM_CHANNEL0) ||
             (ulChannel == xPWM_CHANNEL1) ||
             (ulChannel == xPWM_CHANNEL2) ||
             (ulChannel == xPWM_CHANNEL3) ||
             (ulChannel == xPWM_CHANNEL4) ||
             (ulChannel == xPWM_CHANNEL5) ||
             (ulChannel == xPWM_CHANNEL6) );

    // 1: Disable Counter
    // 2: Enable PWM mode
    xHWREG(ulBase + PWM_TCR) = TCR_PWM_EN;
}

