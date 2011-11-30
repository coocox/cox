//*****************************************************************************
//
//! \file DrvADC.c
//! \brief Driver for the ADC.
//! \version v1.02.003
//! \date 09/05/2011
//! \author Nuvoton
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************


//*****************************************************************************
//
//! Includes of local headers
//
//*****************************************************************************
#include "MINI51.h"
#include "core_cm0.h"
#include "DrvADC.h"
#include "DrvSYS.h"
#include "assert.h"

//*****************************************************************************
//
//! Global file scope (static) variables
//
//*****************************************************************************
static DRVADC_ADC_CALLBACK *g_ptADCCallBack;
static DRVADC_ADCMP0_CALLBACK *g_ptADCMP0CallBack;
static DRVADC_ADCMP1_CALLBACK *g_ptADCMP1CallBack;
static uint32_t g_pu32UserData[3];

//*****************************************************************************
//
//! \brief Enable the ADC function. Configure the corresponding pins of the 
//!  specified channels as analog input pins.    
//!
//! \param u8Channel Specify the input channels.
//! \param ClockSrc Specify the clock source of ADC clock,It could be EXTERNAL_12MHZ / 
//!  INTERNAL_PLL / INTERNAL_RC22MHZ.
//! \param u8AdcDivisor Determine the ADC clock frequency. It could be 0~255.
//!  ADC clock frequency = ADC clock source frequency / ( u8AdcDivisor + 1 )
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_Open(uint8_t u8Channel, E_ADC_CLK_SRC ClockSrc, uint8_t u8AdcDivisor)
{

	if(u8Channel >= ADC_CHANNEL_NUM)
		return;

    /* reset ADC */
    GCR->IPRST_CTL2_BITS.ADC_RST = 1;
    GCR->IPRST_CTL2_BITS.ADC_RST = 0;
    
    /* ADC clock source */
    CLK->CLKSEL1_BITS.ADC_S = ClockSrc;
    
    /* Set ADC divisor */
    CLK->CLKDIV_BITS.ADC_N = u8AdcDivisor;
    /* ADC engine clock enable */
    CLK->APBCLK_BITS.ADC_EN = 1;
    /* ADC enable */
    ADC->CR_BITS.ADEN = 1;
        
    ADC->CHER &= ~0xFF;
	  ADC->CHER |= (1 << u8Channel);
}

//*****************************************************************************
//
//! \brief Disable the ADC function, ADC engine clock, ADC compare 0&1 and 
//!  related interrupts.   
//!
//! \param  None
//! \return None  
//
//*****************************************************************************
void DrvADC_Close(void)
{     
    ADC->CR = 0;                /* ADC disable */
    CLK->APBCLK_BITS.ADC_EN = 0;         /* ADC engine clock disable */

    NVIC_DisableIRQ(ADC_IRQn);
    
    ADC->CMPR0 = 0;          /* Disable ADC compare 0 */    
    ADC->CMPR1 = 0;          /* Disable ADC compare 1 */
}

//*****************************************************************************
//
//! \brief Select ADC input channels.  
//!
//! \param u8Channel:  Specify the analog input channels.
//! \return None  
//
//*****************************************************************************
void DrvADC_SetADCChannel(uint8_t u8Channel)
{     
    assert_param(u8Channel < ADC_CHANNEL_NUM);

    ADC->CHER &= ~0xFF;
    ADC->CHER |= (1 << u8Channel);
}

//*****************************************************************************
//
//! \brief Select the input signal source of ADC channel 7. ADC channel 7 is a                                                    */
//!  multi-function channel.Its input source could come from a external signal,                         
//!  a internal bandgap voltage or a internal temperature sensor.
//!
//! \param Ch7Src Specify the analog input source.     
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_ConfigADCChannel7(E_ADC_CH7_SRC Ch7Src)
{
    ADC->CHER_BITS.PRESEL = Ch7Src;
}

//*****************************************************************************
//
//! \brief Set the ADC clock source.
//!
//! \param ClockSrc :Specify the ADC clock source.  
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_SetADCClkSrc(E_ADC_CLK_SRC ClockSrc)
{
    CLK->CLKSEL1_BITS.ADC_S = ClockSrc; /* ADC clock source */
}

//*****************************************************************************
//
//! \brief Set the divisor value of ADC clock.
//!
//! \param u8AdcDivisor  Specify the divisor value. It could be 0~255. 
//!  ADC clock frequency = ADC clock source frequency / ( u8AdcDivisor + 1 )    
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_SetADCDivisor(uint8_t u8AdcDivisor)
{
    CLK->CLKDIV_BITS.ADC_N = u8AdcDivisor;
}

//*****************************************************************************
//
//! \brief Enable the ADC interrupt and setup callback function.
//!
//! \param Callback :The callback function of ADC interrupt.
//! \param u32UserData This user's data will be passed to the callback function.    
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_EnableADCInt(DRVADC_ADC_CALLBACK Callback, uint32_t u32UserData)
{
    g_ptADCCallBack = Callback;
    g_pu32UserData[0] = u32UserData;
    _DRVADC_CLEAR_ADC_INT_FLAG();     /* clear the A/D interrupt flag for safe */
    ADC->CR_BITS.ADIE = 1;
    NVIC_SetPriority(ADC_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(ADC_IRQn);
}

//*****************************************************************************
//
//! \brief Disable the ADC interrupt.
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_DisableADCInt(void)
{
    ADC->CR_BITS.ADIE = 0;
}

//*****************************************************************************
//
//! \brief Enable the ADC compare 0 interrupt and setup callback function.
//!
//! \param Callback The callback function of ADC result monitor 0 (compare 0) 
//!  interrupt.
//! \param u32UserData This user's data will be passed to the callback function.    
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_EnableADCCmp0Int(DRVADC_ADCMP0_CALLBACK Callback, uint32_t u32UserData)
{
    g_ptADCMP0CallBack = Callback;
    g_pu32UserData[1] = u32UserData;
    _DRVADC_CLEAR_CMP0_INT_FLAG();        /* clear the ADC comparator 0 interrupt flag for safe */
    ADC->CMPR0_BITS.CMPIE = 1;
    NVIC_SetPriority(ADC_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(ADC_IRQn);
}

//*****************************************************************************
//
//! \brief Disable the ADC compare 0 interrupt..
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_DisableADCCmp0Int(void)
{
    ADC->CMPR0_BITS.CMPIE = 0;
}

//*****************************************************************************
//
//! \brief Enable the ADC compare 1 interrupt and setup callback function.
//!
//! \param Callback The callback function of ADC result monito r1 (compare1) 
//!  interrupt.
//! \param u32UserData This user's data will be passed to the callback function.    
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_EnableADCCmp1Int(DRVADC_ADCMP1_CALLBACK Callback, uint32_t u32UserData)
{
    g_ptADCMP1CallBack = Callback;
    g_pu32UserData[2] = u32UserData;
    _DRVADC_CLEAR_CMP1_INT_FLAG();        /* clear the ADC comparator 1 interrupt flag for safe */
    ADC->CMPR1_BITS.CMPIE = 1;
    NVIC_SetPriority(ADC_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(ADC_IRQn);
}

//*****************************************************************************
//
//! \brief Disable the ADC compare 1 interrupt..
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_DisableADCCmp1Int(void)
{
    ADC->CMPR1_BITS.CMPIE = 0;
}

//*****************************************************************************
//
//! \brief ADC Interrupt Service Routine.According to the interrupt flags to call
//!  the corresponding callback function.
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void ADC_IRQHandler(void)
{
    if(ADC->SR_BITS.ADF==1)
    {
        if(g_ptADCCallBack)
            g_ptADCCallBack(g_pu32UserData[0]);
        
        /* clear the A/D conversion flag */
        /* "ADC->ADSR.ADF = 1;" is not recommended. It may clear CMPF0 and CMPF1. */
        outpw(ADC_ADSR, (inpw(ADC_ADSR)&(~0x7))|0x1);
    }
    
    if(ADC->SR_BITS.CMPF0==1)
    {
        if(g_ptADCMP0CallBack)
            g_ptADCMP0CallBack(g_pu32UserData[1]);
        
        /* clear the A/D compare flag 0 */
        /* "ADC->ADSR.CMPF0 = 1;" is not recommended. It may clear ADF and CMPF1. */
        outpw(ADC_ADSR, (inpw(ADC_ADSR)&(~0x7))|0x2);
    }
    
    if(ADC->SR_BITS.CMPF1==1)
    {
        if(g_ptADCMP1CallBack)
            g_ptADCMP1CallBack(g_pu32UserData[2]);
        
        /* clear the A/D compare flag 1 */
        /* "ADC->ADSR.CMPF1 = 1;" is not recommended. It may clear ADF and CMPF0. */
        outpw(ADC_ADSR, (inpw(ADC_ADSR)&(~0x7))|0x4);
    }
}

//*****************************************************************************
//
//! \brief Return the A/D conversion rate (sample/second.)The conversion rate 
//!  depends on the clock source of ADC clock.It needs about 38 ADC clocks to 
//!  complete an A/D conversion.
//!
//! \param  None   
//!
//! \return Conversion rate.  
//
//*****************************************************************************
uint32_t DrvADC_GetConversionRate(void)
{
    if( CLK->CLKSEL1_BITS.ADC_S == 0 )           /* external 12MHz crystal clock */
    {
        return (__XTAL/(CLK->CLKDIV_BITS.ADC_N + 1)/38);
    }
	  if( CLK->CLKSEL1_BITS.ADC_S == 2 )				   /* HCLK */
	  {
		    return (DrvSYS_GetHCLKFreq()/(CLK->CLKDIV_BITS.ADC_N + 1)/38);
	  }
    else                                       /* internal 22MHz RC oscillator clock */
    {
        return (__IRC22M/(CLK->CLKDIV_BITS.ADC_N + 1)/38);
    }
}
//*****************************************************************************
//
//! \brief Allow the external trigger pin ADCST (P3.2) to be the trigger 
//!  source of ADC. The trigger condition could be low-level/high-level/
//!  falling-edge/positive-edge. TRGE bit and ADST bit should be clear to 0 
//!  before changing TRGS bit.                     
//!
//! \param  TriggerCondition Specify the trigger condition.
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_EnableExtTrigger(E_ADC_EXT_TRI_COND TriggerCondition)
{
    GPIO3->PMD_BITS.PMD2 = 0;                    /* Configure P3.2 as an input pin */
    ADC->CR = 0;        				         /* Stop A/D conversion */
	  ADC->CR = (0x100 | TriggerCondition);		 /* Enable ext trigger and set trigger condition */

}

//*****************************************************************************
//
//! \brief Prohibit the external ADC trigger.                 
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_DisableExtTrigger(void)
{
    ADC->CR_BITS.TRGEN = 0;
}

//*****************************************************************************
//
//! \brief Set the ADST bit of ADCR to start the A/D conversion action.
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void DrvADC_StartConvert(void)
{
    /* clear the A/D conversion interrupt flag (ADF) */
    /* "ADC->ADSR.ADF = 1;" is not recommended. It may clear CMPF0 and CMPF1 */
    outpw(ADC_ADSR, (inpw(ADC_ADSR)&(~0x7))|0x1);
    ADC->CR_BITS.ADST = 1;
}


//*****************************************************************************
//
//! \brief Check whether the conversion action is finished or not.
//!
//! \param  None   
//!
//! \return TRUE:  the conversion action is finished.
//!         FALSE: the conversion action is in progress.  
//
//*****************************************************************************
uint32_t DrvADC_IsConversionDone(void)
{
    if(ADC->SR_BITS.ADF==0)
        return FALSE;
    else
        return TRUE;
}

//*****************************************************************************
//
//! \brief Get the conversion result of the specified ADC channel.
//!
//! \param  None    
//!
//! \return Conversion result.  
//
//*****************************************************************************
int32_t DrvADC_GetConversionData(void)
{
    return (ADC->DR_BITS.RESULT);
}

//*****************************************************************************
//
//! \brief Check whether the conversion data is valid or not.
//!
//! \param  None
//!
//! \return TRUE: valid.                                                                          
//!         FALSE: invalid. 
//
//*****************************************************************************
uint32_t DrvADC_IsDataValid(void)
{   
    if( ADC->SR_BITS.VALID)
        return TRUE;
    else
        return FALSE;
}

//*****************************************************************************
//
//! \brief Check whether the conversion data is overrun or not.
//!
//! \param  None  
//!
//! \return TRUE: valid.                                                                          
//!         FALSE: inon-nvalid. 
//
//*****************************************************************************
uint32_t DrvADC_IsDataOverrun(void)
{

    if( ADC->SR_BITS.OVERRUN)
        return TRUE;
    else
        return FALSE;
}

//*****************************************************************************
//
//! \brief Enable the ADC result monitor 0 and configure the necessary settings.
//!
//! \param  u8CmpChannelNum :  Specify the channel number that want to compare.
//! \param  CmpCondition   Specify the compare condition.
//!                  LESS_THAN for the condition of "less than the compare data";       
//!                  GREATER_OR_EQUAL for the condition of "greater or equal to 
//!                     the compare data."
//! \param   u16CmpData   Specify the compare data.    
//! \param   u8CmpMatchCount Specify the compare match count.   
//!
//! \return E_DRVADC_ARGUMENT: one of the input arguments is out of the range.  
//!         E_SUCCESS: the compare function is enabled.  
//
//*****************************************************************************
int32_t DrvADC_EnableADCCmp0(uint8_t u8CmpChannelNum, 
                             E_ADC_CMP_CONDITION CmpCondition, 
                             uint16_t u16CmpData, 
                             uint8_t u8CmpMatchCount)
{
    assert_param((u8CmpChannelNum <= 7 || u16CmpData <= 0x0FFF || u8CmpMatchCount <= 0x0F));

    ADC->CMPR0 = ((u16CmpData << 16) | (u8CmpMatchCount << 8) | (u8CmpChannelNum << 3) | CmpCondition | 1);
    
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Disable the ADC result monitor 0.
//!
//! \param None   
//!
//! \return None
//
//*****************************************************************************
void DrvADC_DisableADCCmp0(void)
{
    ADC->CMPR0_BITS.CMPEN = 0;
}

//*****************************************************************************
//
//! \brief Enable the ADC result monitor 1 and configure the necessary settings.
//!
//! \param  u8CmpChannelNum Specify the channel number that want to compare.
//! \param  CmpCondition  Specify the compare condition.
//!                  LESS_THAN for the condition of "less than the compare data";       
//!                  GREATER_OR_EQUAL for the condition of "greater or equal to 
//!                     the compare data."
//! \param   u16CmpData   Specify the compare data.    
//! \param   u8CmpMatchCount Specify the compare match count.  
//!
//! \return E_DRVADC_ARGUMENT: one of the input arguments is out of the range.  
//!         E_SUCCESS: the compare function is enabled.  
//
//*****************************************************************************
int32_t DrvADC_EnableADCCmp1(uint8_t u8CmpChannelNum, 
                             E_ADC_CMP_CONDITION CmpCondition, 
                             uint16_t u16CmpData, 
                             uint8_t u8CmpMatchCount)
{
    assert_param((u8CmpChannelNum <= 7 || u16CmpData <= 0x0FFF || u8CmpMatchCount <= 0x0F));
    
	  ADC->CMPR1 = ((u16CmpData << 16) | (u8CmpMatchCount << 8) | (u8CmpChannelNum << 3) | CmpCondition | 1);
    
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Disable the ADC result monitor 1.
//!
//! \param None   
//!
//! \return None
//
//*****************************************************************************
void DrvADC_DisableADCCmp1(void)
{
    ADC->CMPR1_BITS.CMPEN = 0;
}


//*****************************************************************************
//
//! \brief Get the version number of M05xx ADC driver.
//!
//! \param None   
//!
//! \return Version number.  
//
//*****************************************************************************
uint32_t DrvADC_GetVersion (void)
{
    return DRVADC_VERSION_NUM;
}

