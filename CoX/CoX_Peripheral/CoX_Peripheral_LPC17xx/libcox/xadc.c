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
#include "xhw_adc.h"
#include "xadc.h"

//! ADC channel ID array
static unsigned long ChID[8] =
{
    ADC_CH_0,
    ADC_CH_1,
    ADC_CH_2,
    ADC_CH_3,
    ADC_CH_4,
    ADC_CH_5,
    ADC_CH_6,
    ADC_CH_7,
};

// internal variable.
static unsigned long _ADC_Mode     = 0;
static unsigned long _ADC_Status   = 0;
static unsigned long _ADC_Triggler = 0;
static unsigned long _ADC_Channels = 0;

//*****************************************************************************
//
// An array is ADC callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnADCHandlerCallbacks = 0;

//*****************************************************************************
//
//! \brief  ADC interrupt handler.
//!         This function is the ADC interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void ADCIntHandler(void)
{
    if(g_pfnADCHandlerCallbacks != 0)
    {
        g_pfnADCHandlerCallbacks(0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Register user interrupts callback function  for the ADC.
//!
//! \param  [in] xtPortCallback is user callback for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void xADCIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    // Avoid compiler warning
    (void) ulBase;

    // Check the parameters.
    xASSERT(pfnCallback != 0);

    g_pfnADCHandlerCallbacks = pfnCallback;
}

//*****************************************************************************
//
//! \brief  Init ADC module
//!         This function can be used to configure ADC peripherals clock frequecy.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be - \ref xADC0_BASE.
//!
//! \param  [in] ulRate is the ADC convert frequecy, it must be lower than 200KHz.
//!
//! \return None.
//
//*****************************************************************************
void ADCInit(unsigned long ulBase, unsigned long ulRate)
{

    unsigned long temp    = 0;
    unsigned long ulClk   = 0;

    // Note: ADC Module Maximum frequecy is 13MHz
    // ulRate <= 200KHz
    // ulClk = SysCtlPeripheralClockGet(SYSCTL_PERIPH_ADC);
    // ulClk /= 13000000;

    //xHWREG(ulBase + AD_CR) = (ulClk<<CR_CLKDIV_S) | BIT_32_0;
    xHWREG(ulBase + AD_CR) = 0;

    // Set clock frequency
    ulClk = SysCtlPeripheralClockGet(SYSCTL_PERIPH_ADC);

    // The APB clock (PCLK_ADC0) is divided by (CLKDIV+1) to produce the clock for
    // A/D converter, which should be less than or equal to 13MHz.
    // A fully conversion requires 65 of these clocks.
    // ADC clock = PCLK_ADC0 / (CLKDIV + 1);
    // ADC rate = ADC clock / 65;
    temp = ulRate * 65;

    // Get the round value by fomular: (2*A + B)/(2*B)
    temp = (ulClk * 2 + temp)/(2 * temp) - 1;

    xHWREG(ulBase + AD_CR) = (temp<<CR_CLKDIV_S) | BIT_32_0;
}

//*****************************************************************************
//
//! \brief  Start special ADC channel.
//!         This function configure ADC convert mode, triggle mode.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be - \ref xADC0_BASE.
//!
//! \param  [in] ulChs is ADC channel.
//!              This value can be OR of the following value:
//!              - \ref ADC_CH_0
//!              - \ref ADC_CH_1
//!              - \ref ADC_CH_2
//!              - \ref ADC_CH_3
//!              - \ref ADC_CH_4
//!              - \ref ADC_CH_5
//!              - \ref ADC_CH_6
//!
//! \param  [in] ulMode is adc convert mode, consist of burst and external
//!              triggle mode. this value can be one of the following value:
//!              - \ref ADC_START_MODE_BURST
//!              - \ref ADC_START_MODE_NOW
//!              - \ref ADC_START_MODE_EINT0
//!              - \ref ADC_START_MODE_CAP01
//!              - \ref ADC_START_MODE_MAT01
//!              - \ref ADC_START_MODE_MAT03
//!              - \ref ADC_START_MODE_MAT10
//!              - \ref ADC_START_MODE_MAT11
//!
//! \return None.
//
//*****************************************************************************
void ADCStart(unsigned long ulBase, unsigned long ulChs, unsigned long ulMode)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT(ulBase == ADC_BASE);
    xASSERT( (ulMode == ADC_START_MODE_BURST)  ||
             (ulMode == ADC_START_MODE_NOW  )  ||
             (ulMode == ADC_START_MODE_EINT0)  ||
             (ulMode == ADC_START_MODE_CAP01)  ||
             (ulMode == ADC_START_MODE_MAT01)  ||
             (ulMode == ADC_START_MODE_MAT03)  ||
             (ulMode == ADC_START_MODE_MAT10)  ||
             (ulMode == ADC_START_MODE_MAT11)  );

    if(ulMode != ADC_START_MODE_BURST)        // Normal Mode
    {
        // Configure ADC Channel
        ulTmpReg =  xHWREG(ulBase + AD_CR);
        ulTmpReg &= ~(CR_START_M | CR_BURST);
        ulTmpReg |= (CR_PDN | ulMode);
        xHWREG(ulBase + AD_CR) = ulTmpReg;

        // Configure ADC into normal mode, and select
        ulTmpReg =  xHWREG(ulBase + AD_CR);
        ulTmpReg &= ~(CR_START_M | CR_BURST | CR_SEL_M);
        ulTmpReg |= (CR_PDN | ulMode | ulChs);
        xHWREG(ulBase + AD_CR) = ulTmpReg;
    }
    else                                      // Burst Mode
    {
        ulTmpReg =  xHWREG(ulBase + AD_CR);
        ulTmpReg &= ~(CR_START_M | CR_SEL_M);
        ulTmpReg |= (CR_PDN | CR_BURST | ulChs);
        xHWREG(ulBase + AD_CR) = ulTmpReg;
    }
}

//*****************************************************************************
//
//! \brief  Stop ADC convert procedure.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be - \ref xADC0_BASE.
//!
//! \return None.
//
//*****************************************************************************
void ADCStop(unsigned long ulBase)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT(ulBase == ADC_BASE);

    // Stop ADC by set ADC into power dowm mode then configure stop bit
    ulTmpReg = xHWREG(ulBase + AD_CR);
    ulTmpReg &= ~(CR_PDN | CR_START_M);
    xHWREG(ulBase + AD_CR) = ulTmpReg;
}

//*****************************************************************************
//
//! \brief  Enable speical ADC interrupt.
//!         This function can be used to enable ADC convert done interrupt.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be - \ref xADC0_BASE.
//!
//! \param  [in] ulChs is ADC channel.
//!              This value can be OR of the following value:
//!              - \ref ADC_CH_0
//!              - \ref ADC_CH_1
//!              - \ref ADC_CH_2
//!              - \ref ADC_CH_3
//!              - \ref ADC_CH_4
//!              - \ref ADC_CH_5
//!              - \ref ADC_CH_6
//!
//! \return None.
//
//*****************************************************************************
void ADCIntEnable(unsigned long ulBase, unsigned long ulChs)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT(ulBase == ADC_BASE);
    xASSERT( (ulChs & ~ADC_CH_M) == 0 );

    // Enable Selected ADC Channel
    ulTmpReg = xHWREG(ulBase + AD_INTEN);
    ulTmpReg &= ~INTEN_GEN;
    ulTmpReg |= ulChs;
    xHWREG(ulBase + AD_INTEN) = ulTmpReg;
}

//*****************************************************************************
//
//! \brief  Disable speical ADC interrupt.
//!         This function can be used to disable ADC convert done interrupt.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be - \ref xADC0_BASE.
//!
//! \param  [in] ulChs is ADC channel.
//!              This value can be OR of the following value:
//!              - \ref ADC_CH_0
//!              - \ref ADC_CH_1
//!              - \ref ADC_CH_2
//!              - \ref ADC_CH_3
//!              - \ref ADC_CH_4
//!              - \ref ADC_CH_5
//!              - \ref ADC_CH_6
//!
//! \return None.
//
//*****************************************************************************
void ADCIntDisable(unsigned long ulBase, unsigned long ulChs)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT(ulBase == ADC_BASE);
    xASSERT( (ulChs & ~ADC_CH_M) == 0 );

    // Disable Selected ADC Channel
    ulTmpReg = xHWREG(ulBase + AD_INTEN);
    ulTmpReg &= ~INTEN_GEN;
    ulTmpReg &= ~ulChs;
    xHWREG(ulBase + AD_INTEN) = ulTmpReg;
}


//*****************************************************************************
//
//! \brief  Check ADC status flag.
//!         This function can be use to check ADC special channel DONE and
//!         OVERRUN flag.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be - \ref xADC0_BASE.
//!
//! \param  [in] ulChs is ADC channel.
//!              This value can be OR of the following value:
//!              - \ref ADC_CH_0
//!              - \ref ADC_CH_1
//!              - \ref ADC_CH_2
//!              - \ref ADC_CH_3
//!              - \ref ADC_CH_4
//!              - \ref ADC_CH_5
//!              - \ref ADC_CH_6
//!
//! \param  [in] ulFlags is used to check done or overrun status bit.
//!              This flag is OR of the following value:
//!              - \ref ADC_DONE
//!              - \ref ADC_OVERRUN
//!
//! \return The ADC channel status flag.
//!              - \ref xtrue when flag has been set.
//!              - \ref xflase when flag has not been set.
//
//*****************************************************************************
xtBoolean ADCStatusCheck(unsigned long ulBase, unsigned long ulChs, unsigned long ulFlags)
{

    switch(ulFlags)
    {
        case ADC_DONE:                 // Check ADC convert done flag.
            {
                ulChs = ulChs;
                break;
            }

        case ADC_OVERRUN:              // Check ADC overrun flag.
            {
                ulChs <<= 8;
                break;
            }

        case ADC_DONE | ADC_OVERRUN:   // Check ADC convert done and overrun flag.
            {
                ulChs |= (ulChs << 8);
                break;
            }
        default:
            {
                while(1);
            }
    }

    if( xHWREG(ulBase + AD_STAT) &  ulChs )
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
//! \brief  Read ADC channel converted data.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be - \ref xADC0_BASE.
//!
//! \param  [in] ulChs is ADC channel.
//!              This value can be OR of the following value:
//!              - \ref ADC_CH_0
//!              - \ref ADC_CH_1
//!              - \ref ADC_CH_2
//!              - \ref ADC_CH_3
//!              - \ref ADC_CH_4
//!              - \ref ADC_CH_5
//!              - \ref ADC_CH_6
//!
//! \return The ADC channel data.
//!
//! \note   The ADC convert data is 12-bit length.
//
//*****************************************************************************
unsigned long ADCDataRead(unsigned long ulBase, unsigned long ulCh)
{
    unsigned long ulTmpReg = 0;

    switch(ulCh)
    {
        case ADC_CH_0:
            {
                ulTmpReg =  xHWREG(ulBase + AD_DR0);
                break;
            }

        case ADC_CH_1:
            {
                ulTmpReg =  xHWREG(ulBase + AD_DR1);
                break;
            }

        case ADC_CH_2:
            {
                ulTmpReg =  xHWREG(ulBase + AD_DR2);
                break;
            }

        case ADC_CH_3:
            {
                ulTmpReg =  xHWREG(ulBase + AD_DR3);
                break;
            }

        case ADC_CH_4:
            {
                ulTmpReg =  xHWREG(ulBase + AD_DR4);
                break;
            }

        case ADC_CH_5:
            {
                ulTmpReg =  xHWREG(ulBase + AD_DR5);
                break;
            }

        case ADC_CH_6:
            {
                ulTmpReg =  xHWREG(ulBase + AD_DR6);
                break;
            }

        default:
            {
                while(1);              // Error.
            }
    }

    // Return ADC channel value.
    ulTmpReg = (ulTmpReg & BIT_MASK(32, 15, 4)) >> 4;
    return (ulTmpReg);
}

//*****************************************************************************
//
//! \brief  Get the captured data from a sample sequence.
//!         This function copies data from the specified sample sequence
//!         FIFO to a memory resident buffer.  The number of samples
//!         available in the FIFO are copied into the buffer, which is
//!         assumed to be large enough to hold that many samples.
//!         This will only return the samples that are presently available,
//!         which may not be the entire sample sequence if it is in the
//!         process of being executed.
//!
//! \param  [in] ulBase is the base address of the ADC module.  This value must be
//!              - \ref xADC0_BASE.
//!
//! \param  [in] pulBuffer is the address where the data is stored.
//!
//! \return The number of sample channel, if return 0, indicate that some channel
//!         is converting.
//!
//
//*****************************************************************************
unsigned long xADCDataGet(unsigned long ulBase, unsigned long * pulBuffer)
{
    unsigned long i        = 0;
    unsigned long cnt      = 0;
    unsigned long ulTmpReg = 0;

    // Check input parameters valid
    xASSERT(ulBase == xADC0_BASE);
    xASSERT(pulBuffer != NULL);

    // Check channel 0-->6 status, then read converted channel data.
    ulTmpReg = xHWREG(ulBase + AD_STAT);
    for(i = 0; i < 7; i++)
    {
        if( ulTmpReg & (1<<i) )  // Check
        {
            cnt++;
            *pulBuffer++ = ADCDataRead(ulBase, ChID[i]);
        }
    }
    
    // return the number of convert channel
    return (cnt);
}

//*****************************************************************************
//
//! \brief  Configure ADC Module.
//!         This function configures ADC convert mode(single/continue scan mode)
//!         and triggle mode(soft/hardware triggler).
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be
//!              - \ref xADC0_BASE.
//!
//! \param  [in] ulMode is ADC scan mode, can be one of the following value:
//!              - \ref xADC_MODE_SCAN_SINGLE_CYCLE
//!              - \ref xADC_MODE_SCAN_CONTINUOUS
//!
//! \param  [in] ulTrigger is ADC triggle source select. For LPC17xx, it can be
//!              one of the following value:
//!              - \ref xADC_TRIGGER_PROCESSOR
//!              - \ref xADC_TRIGGER_EXT_EINT0
//!              - \ref xADC_TRIGGER_EXT_CAP01
//!              - \ref xADC_TRIGGER_EXT_MAT01
//!              - \ref xADC_TRIGGER_EXT_MAT03
//!              - \ref xADC_TRIGGER_EXT_MAT10
//!              - \ref xADC_TRIGGER_EXT_MAT11
//!
//! \return None.
//!
//! \note   This function must be called first!
//
//*****************************************************************************
void xADCConfigure(unsigned long ulBase, unsigned long ulMode,
        unsigned long ulTrigger)
{
    // Check input parameters valid
    xASSERT(ulBase == xADC0_BASE);

    // Record the configure parameters
    _ADC_Mode     = ulMode;
    _ADC_Triggler = ulTrigger;

    // ADC has been configured, mark it!
    _ADC_Status   = 1;
}

//*****************************************************************************
//
//! \brief  Configure ADC convert array.
//!         This function is used to fill ADC convert array, so you can use it
//!         to support ADC burst mode.
//!
//! \param  [in] ulBase is the base address of the ADC module.
//!              This value must be
//!              - \ref xADC0_BASE.
//!
//! \param  [in] ulStep is the ID of ADC converter channel array, which can be
//!              used in continue convert mode.
//!              0 <= ulStep <=7.
//!
//! \param  [in] ulConfig is ADC channerl source, which can be one of the
//!              following value:
//!              - \ref xADC_CTL_CH0
//!              - \ref xADC_CTL_CH1
//!              - \ref xADC_CTL_CH2
//!              - \ref xADC_CTL_CH3
//!              - \ref xADC_CTL_CH4
//!              - \ref xADC_CTL_CH5
//!              - \ref xADC_CTL_CH6
//!              - \ref xADC_CTL_CH7
//!
//! \return None.
//!
//! \note   For LPC17xx, The relationship between ADC Convert array is fixed.
//!         must follow the below law.
//! \note
//!         Array ID  |  ADC Channel
//!         ----------|--------------
//!         Array[0]  |  xADC_CTL_CH0
//!         Array[1]  |  xADC_CTL_CH1
//!         ...       |  ...
//!         Array[7]  |  xADC_CTL_CH7
//! \note
//!         so, you can use this function to configure ADC continue scan mode
//!         or single sample mode.
//!         for example:
//!         Status   |  Configure Function
//!         ---------|-----------------------------------------------
//!         Right    |  xADCStepConfigure(xADC0_BASE, 0, xADC_CTL_CH0)
//!         Wrong    |  xADCStepConfigure(xADC0_BASE, 1, xADC_CTL_CH0)
//
//*****************************************************************************
void xADCStepConfigure(unsigned long ulBase, unsigned long ulStep,
       unsigned long ulConfig)
{

    // Check input parameters valid
    xASSERT(ulBase == xADC0_BASE);
    xASSERT(ulStep <= 6);
    xASSERT( (ulConfig == xADC_CTL_CH0) ||
             (ulConfig == xADC_CTL_CH1) ||
             (ulConfig == xADC_CTL_CH2) ||
             (ulConfig == xADC_CTL_CH3) ||
             (ulConfig == xADC_CTL_CH4) ||
             (ulConfig == xADC_CTL_CH5) ||
             (ulConfig == xADC_CTL_CH6) );

    _ADC_Channels |= ulConfig;

    // Configure ADC array.
    xHWREG(ulBase + AD_CR) |= ulConfig;
}

//*****************************************************************************
//
//! \brief  Enable ADC sample sequence.
//!         Allows the specified sample sequence to be captured when its trigger
//!         is detected. A sample sequence must be configured before it is enabled.
//!
//! \param  [in] ulBase is the base address of the ADC module. This value must be
//!              - \ref xADC0_BASE.
//!
//! \return None.
//!
//! \note   User must call xADCConfigure first.
//
//*****************************************************************************
void xADCEnable(unsigned long ulBase)
{
    // Check input parameters valid
    xASSERT(ulBase == xADC0_BASE);

    // Has been call xADCConfigure ?
    if(0 == _ADC_Status)
    {
        // Error! user must call xADCConfigure first.
        while(1);
    }

    // Record the configure parameters
    //_ADC_Mode     = ulMode;
    //_ADC_Triggler = ulTrigger;

    // Configure ADC Clock
    ADCInit(ulBase, 200000);

    if(_ADC_Mode == xADC_MODE_SCAN_CONTINUOUS)  //brust mode
    {
        ADCStart(ulBase, _ADC_Channels, ADC_START_MODE_BURST);
    }
    else
    {
        ADCStart(ulBase, _ADC_Channels, _ADC_Triggler);
    }

}

