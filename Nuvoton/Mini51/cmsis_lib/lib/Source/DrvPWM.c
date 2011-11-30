//*****************************************************************************
//
//! \file DrvPWM.c
//! \brief Driver for the PWM Controller.
//! \version v1.01.002
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
//! Includes of local headers
//
//*****************************************************************************
#include "DrvPWM.h"
#include "DrvSYS.h"
#include "Assert.h"

///*****************************************************************************
//
//! Macro, type and constant definitions
//
//*****************************************************************************
#define PWM_CNR0        PWM_BASE + 0x0C
#define PWM_CMR0        PWM_BASE + 0x24

//*****************************************************************************
//
//! Global file scope (static) variables
//
//*****************************************************************************
static PFN_DRVPWM_CALLBACK g_pfnPWMDutyCallback[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
static uint32_t	dutyCallbackParam[6] = {0, 0, 0, 0, 0, 0};
static PFN_DRVPWM_CALLBACK g_pfnPWMPeriodCallback[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
static uint32_t	periodCallbackParam[6] = {0, 0, 0, 0, 0, 0};
static PFN_DRVPWM_CALLBACK g_pfnFBCallback[2] = {NULL, NULL};
static uint32_t fbCallbackParam[2] = {0, 0};


//*****************************************************************************
//
//! \brief This function is used to get the DrvPWM version number 
//!
//! \param None 
//!
//! \return The DrvPWM version number  
//
//*****************************************************************************
uint32_t DrvPWM_GetVersion(void)
{
    return DRVPWM_VERSION_NUM;
}

//*****************************************************************************
//
//! \brief ISR to handle PWM interrupt event 
//!
//! \param None 
//!
//! \return None  
//
//*****************************************************************************
void PWM_IRQHandler(void)
{    
	uint32_t reg = PWM->PIIR & 0x3f3f;
	uint8_t i;

	for(i = 0; i < 6; i++) {
		if((reg & (0x1 << i)) && (g_pfnPWMPeriodCallback[i] != NULL))
			g_pfnPWMPeriodCallback[i](periodCallbackParam[i]);
	}

	for(i = 0; i < 6; i++) {
		if((reg & (0x100 << i)) && (g_pfnPWMDutyCallback[i] != NULL))
			g_pfnPWMDutyCallback[i](dutyCallbackParam[i]);
	}

    //
    // clear
    //
	PWM->PIIR = reg; 

	return;
}

//*****************************************************************************
//
//! \brief ISR to handle fault break interrupt event
//!
//! \param None 
//!
//! \return None  
//
//*****************************************************************************
void FB_IRQHandler(void)
{    
	uint32_t reg = PWM->PIIR & 0x30000;

	if((reg & 0x10000) && (g_pfnFBCallback[0] != NULL)) {
		g_pfnFBCallback[0](fbCallbackParam[0]);
	}
	
	if((reg & 0x20000) && (g_pfnFBCallback[1] != NULL)) {
		g_pfnFBCallback[1](fbCallbackParam[1]);
	}

	PWM->PIIR = reg;

	return;
}

//*****************************************************************************
//
//! \brief This function is used to get PWM  channel enable/disable state 
//!
//! \param u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5 
//!
//! \return 0      disable 
//!         1      enable 
//
//*****************************************************************************
int32_t DrvPWM_IsTimerEnabled(uint8_t u8Timer)
{
    int32_t status = 0;

	assert_param((u8Timer < DRVPWM_CHANNEL_NUM)); 

	status = ( inp32(&PWM->PCR) & (1 << (u8Timer * 4) ) )? 1 : 0;
    
    return status;
}


//*****************************************************************************
//
//! \brief This function is used to set the PWM0~5 specified timer counter 
//!
//! \param u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5
//! \param u16Counter Timer counter : 0~65535
//!
//! \return None 
//!
//! \Note  If the counter is set to 0, the timer will stop. 
//
//*****************************************************************************
void DrvPWM_SetTimerCounter(uint8_t u8Timer, uint16_t u16Counter)
{   
	assert_param((u8Timer < DRVPWM_CHANNEL_NUM)); 
    
	*((__IO uint32_t *) (PWM_CNR0 + (u8Timer) * 4)) = u16Counter;

}


//*****************************************************************************
//
//! \brief This function is used to set the PWM0~5 specified timer comperator
//!
//! \param u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5
//! \param u16Comparator Timer counter : 0~65535
//!
//! \return None 
//
//*****************************************************************************
void DrvPWM_SetTimerComparator(uint8_t u8Timer, uint16_t u16Comparator)
{   
	assert_param((u8Timer < DRVPWM_CHANNEL_NUM)); 

    *((__IO uint32_t *) (PWM_CMR0 + (u8Timer) * 4)) = u16Comparator;

}


//*****************************************************************************
//
//! \brief This function is used to enable the PWM0~5 timer/capture interrupt 
//!
//! \param u8Source  DRVPWM_TIMER0 / DRVPWM_TIMER1/DRVPWM_TIMER2 /DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5 / DRVPWM_FB0 / DRVPWM_FB1  
//! \param  eType        Interrupt type. Not used if source is fault break 
//! \param  pfncallback  The call back function for specified timer  
//! \param  u32Param     Parameter send to  callback function  
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_EnableInt(uint8_t u8Source, E_DRVPWM_INTERRUPT_TYPE eType, PFN_DRVPWM_CALLBACK pfncallback, uint32_t u32Param)
{
	
	if(u8Source < DRVPWM_CHANNEL_NUM) {
		g_pfnPWMDutyCallback[u8Source] = pfncallback;
		dutyCallbackParam[u8Source] = u32Param;
		PWM->PIER |= (eType << u8Source);
	    NVIC_EnableIRQ(PWM_IRQn);
	} else if(u8Source == DRVPWM_FB0 || u8Source == DRVPWM_FB1) {
		g_pfnFBCallback[u8Source - 0x10] = pfncallback;
		fbCallbackParam[u8Source - 0x10] = u32Param;		
		PWM->PIER |= 0x1000; 
		NVIC_EnableIRQ(FB_IRQn);
	}
	
	return;         
}

//*****************************************************************************
//
//! \brief This function is used to disable the PWM0~5 timer/capture interrupt 
//!
//! \param u8Source  DRVPWM_TIMER0 / DRVPWM_TIMER1/DRVPWM_TIMER2 /DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5 / DRVPWM_FB0 / DRVPWM_FB1  
//! \param  eType        Interrupt type. Not used if source is fault break  
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_DisableInt(uint8_t u8Source, E_DRVPWM_INTERRUPT_TYPE eType)
{
	if(u8Source < DRVPWM_CHANNEL_NUM) {
		PWM->PIER &= ~(eType << u8Source);    
	} else if(u8Source == DRVPWM_FB0 || u8Source == DRVPWM_FB1) {
		PWM->PIER &= ~0x10000;
		NVIC_DisableIRQ(FB_IRQn); 
	} 

	if((PWM->PIER & 0x3F3F) == 0)
		NVIC_DisableIRQ(PWM_IRQn);		

	return;
}

//*****************************************************************************
//
//! \brief This function is used to clear the PWM0~5 timer/fault break 
//! interrupt flag
//!
//! \param u8Source  DRVPWM_TIMER0 / DRVPWM_TIMER1/DRVPWM_TIMER2 /DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5 / DRVPWM_FB0 / DRVPWM_FB1   
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_ClearInt(uint8_t u8Source, E_DRVPWM_INTERRUPT_TYPE eType)
{
	if(u8Source < DRVPWM_CHANNEL_NUM) {
		PWM->PIIR = (eType << u8Source);    
	} else if(u8Source == DRVPWM_FB0) {
		PWM->PIIR = 0x10000; 
	} else if(u8Source == DRVPWM_FB1) {
		PWM->PIIR = 0x20000; 
	}

	return;
}

//*****************************************************************************
//
//! \brief This function is used to get the PWM0~5 timer/fault break 
//! interrupt flag
//!
//! \param u8Source  DRVPWM_TIMER0 / DRVPWM_TIMER1/DRVPWM_TIMER2 /DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5 / DRVPWM_FB0 / DRVPWM_FB1   
//!
//! \return  0   FALSE 
//!          1   TRUE
//
//*****************************************************************************
int32_t DrvPWM_GetIntFlag(uint8_t u8Source, E_DRVPWM_INTERRUPT_TYPE eType)
{
    int32_t status = -1;

	if(u8Source < DRVPWM_CHANNEL_NUM) {
		status = (PWM->PIIR & (eType << u8Source)) ? 1 : 0; 			     
	} else if(u8Source == DRVPWM_FB0) {
		status = (PWM->PIIR & 0x10000) ? 1 : 0; 
	} else if(u8Source == DRVPWM_FB1) {
		status = (PWM->PIIR & 0x20000) ? 1 : 0;
	}

    return status;      
}



//*****************************************************************************
//
//! \brief Enable PWM engine clock and reset PWM 
//!
//! \param  None
//!                 
//! \return None  
//
//*****************************************************************************
void DrvPWM_Open(void)
{ 
    outp32(&CLK->APBCLK, inp32(&CLK->APBCLK) | 0x00700000);
	GCR->IPRST_CTL2_BITS.PWM_RST = 1;
	GCR->IPRST_CTL2_BITS.PWM_RST = 0;
}

//*****************************************************************************
//
//! \brief Disnable PWM engine clock and reset PWM 
//!
//! \param  None
//!                 
//! \return None  
//
//*****************************************************************************
void DrvPWM_Close(void)
{
    PWM->POE = 0;

    NVIC_DisableIRQ(PWM_IRQn);
    NVIC_DisableIRQ(FB_IRQn);
    
	GCR->IPRST_CTL2_BITS.PWM_RST = 1;
	GCR->IPRST_CTL2_BITS.PWM_RST = 0;
    outp32(&CLK->APBCLK, inp32(&CLK->APBCLK) & ~0x00700000);
}

//*****************************************************************************
//
//! \brief This function is used to set the dead zone length and enable Dead 
//! Zone function 
//!
//! \param  u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3 
//!                 DRVPWM_TIMER4 / DRVPWM_TIMER5 
//! \param  u8Length  Dead Zone Length : 0~255
//!                 
//! \return None  
//
//*****************************************************************************
void DrvPWM_EnableDeadZone(uint8_t u8Timer, uint8_t u8Length)
{

    switch (u8Timer)
    {
        case DRVPWM_TIMER0:
        case DRVPWM_TIMER1:
            PWM->PDZIR_BITS.DZI01 = u8Length;
            PWM->PCR_BITS.DZEN01 = 1;
            break;
        case DRVPWM_TIMER2:
        case DRVPWM_TIMER3:
            PWM->PDZIR_BITS.DZI23 = u8Length;
            PWM->PCR_BITS.DZEN23 = 1;
            break;
        case DRVPWM_TIMER4:
        case DRVPWM_TIMER5:
            PWM->PDZIR_BITS.DZI45 = u8Length;
            PWM->PCR_BITS.DZEN45 = 1;
            break;
    }   
	return;
}

//*****************************************************************************
//
//! \brief This function is used to disable Dead Zone function 
//!
//! \param  u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3 
//!                 DRVPWM_TIMER4 / DRVPWM_TIMER5 
//!                 
//! \return None  
//
//*****************************************************************************
void DrvPWM_DisableDeadZone(uint8_t u8Timer)
{

    switch (u8Timer)
    {
        case DRVPWM_TIMER0:
        case DRVPWM_TIMER1:
            PWM->PCR_BITS.DZEN01 = 0;
            break;
        case DRVPWM_TIMER2:
        case DRVPWM_TIMER3:
            PWM->PCR_BITS.DZEN23 = 0;
            break;
        case DRVPWM_TIMER4:
        case DRVPWM_TIMER5:
            PWM->PCR_BITS.DZEN45 = 0;
            break;
    }   
	return;
}

//*****************************************************************************
//
//! \brief This function is used to enable PWM0~5 timer function   
//!
//! \param  u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3 
//!                 DRVPWM_TIMER4 / DRVPWM_TIMER5 
//!                 
//! \return None  
//
//*****************************************************************************
void DrvPWM_Enable(uint8_t u8Timer)
{

	if(u8Timer < DRVPWM_CHANNEL_NUM)
		PWM->PCR |= (1 << (u8Timer * 4));
	
	return;
}

//*****************************************************************************
//
//! \brief This function is used to disable PWM0~5 timer function   
//!
//! \param  u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3 
//!                 DRVPWM_TIMER4 / DRVPWM_TIMER5 
//!                 
//! \return None  
//
//*****************************************************************************
void DrvPWM_Disable(uint8_t u8Timer)
{

	if(u8Timer < DRVPWM_CHANNEL_NUM)
		PWM->PCR &= ~(1 << (u8Timer * 4));
	
	return;
}

//*****************************************************************************
//
//! \brief This function is used to configure the frequency/pulse/mode/inverter
//!  function 
//!
//! \param  u8Timer             DRVPWM_TIMER0/DRVPWM_TIMER1/DRVPWM_TIMER2/DRVPWM_TIMER3
//!                             DRVPWM_TIMER4/DRVPWM_TIMER5             
//! \param  S_DRVPWM_TIME_DATA_T *sPt                                                                 
//! \param  u32Frequency        Frequency (Hz)                                             
//! \param  u8HighPulseRatio    High Pulse Ratio                                           
//! \param  u8Mode              DRVPWM_ONE_SHOT_MODE / DRVPWM_AUTO_RELOAD_MODE             
//! \param  bInverter           Inverter Enable  (TRUE) / Inverter Disable  (FALSE)        
//! \param  u8ClockSelector     Clock Selector                                             
//!                             DRVPWM_CLOCK_DIV_1/DRVPWM_CLOCK_DIV_2/DRVPWM_CLOCK_DIV_4   
//!                             DRVPWM_CLOCK_DIV_8/DRVPWM_CLOCK_DIV_16                     
//!                             (The parameter takes effect when u8Frequency = 0)          
//! \param  u8PreScale          Prescale (1 ~ 255).                                        
//!                             The PWM input clock = PWM source clock / (u8PreScale + 1)  
//!                             Note: If the value is set to 0, the timer will stop.       
//!                             (The parameter takes effect when u8Frequency = 0)          
//! \param  u32Duty             Pulse duty                                                 
//!                             (The parameter takes effect when u8Frequency = 0)        
//!
//! \return The actual frequency (Hz)  
//
//*****************************************************************************
uint32_t DrvPWM_SetTimerClk(uint8_t u8Timer, S_DRVPWM_TIME_DATA_T *sPt)
{
    uint32_t    u32Frequency;
    uint32_t    u32Freqout;
    uint16_t    u16Duty, u16cnrData, u16cmrData;
    uint8_t     u8EngineClk = 0;
        
    switch (u8Timer)
    {
        case DRVPWM_TIMER0:
        case DRVPWM_TIMER1:
            u8EngineClk = CLK->CLKSEL1_BITS.PWM01_S;              
            break;
        case DRVPWM_TIMER2:
        case DRVPWM_TIMER3:
            u8EngineClk = CLK->CLKSEL1_BITS.PWM23_S;
            break;      
        case DRVPWM_TIMER4:
        case DRVPWM_TIMER5:
            u8EngineClk = CLK->CLKSEL2_BITS.PWM45_S;              
            break;
    }


    if (u8EngineClk == 0)        /* external 12MHz crystal clock    */
    {
        u32Freqout = __XTAL;    
    }
    else if(u8EngineClk == 2)    /* HCLK clock */
    {
        u32Freqout = DrvSYS_GetHCLKFreq();//SystemCoreClock;
    }
    else                         /* internal 22MHz oscillator clock */
    {
        u32Freqout = __IRC22M;  
    }

	if(sPt->i32Inverter)
		PWM->PCR |= (0x4 << (u8Timer * 4));
	else
		PWM->PCR &= ~(0x4 << (u8Timer * 4));

	if(sPt->u8Mode)
		PWM->PCR |= (0x8 << (u8Timer * 4));
	else
		PWM->PCR |= (0x8 << (u8Timer * 4));	           
    
    if (sPt->u32Frequency == 0)
    {   
        uint8_t u8Divider = 1;
        uint32_t u32duty;
        
        switch (u8Timer)
        {
            case DRVPWM_TIMER0:
            case DRVPWM_TIMER1:
                PWM->PPR_BITS.CP01 = sPt->u8PreScale;
                break;
            case DRVPWM_TIMER2:
            case DRVPWM_TIMER3:
                PWM->PPR_BITS.CP23 = sPt->u8PreScale;
                break;
            case DRVPWM_TIMER4:
            case DRVPWM_TIMER5:
                PWM->PPR_BITS.CP45 = sPt->u8PreScale;
                break;
        } 
        
        u32duty = sPt->u32Duty * sPt->u8HighPulseRatio / 100 - 1;
        
		PWM->CSR = (PWM->CSR & ~(0x7 << (u8Timer * 4))) | (sPt->u8ClockSelector << (u8Timer * 4));
        outp32(PWM_CNR0 + u8Timer * 4, (sPt->u32Duty - 1));
        outp32(PWM_CMR0 + u8Timer * 4, u32duty);
                
        switch (sPt->u8ClockSelector)
        {
            case DRVPWM_CLOCK_DIV_1:
                u8Divider = 1;
                break;
            case DRVPWM_CLOCK_DIV_2:
                u8Divider = 2;          
                break;          
            case DRVPWM_CLOCK_DIV_4:
                u8Divider = 4;          
                break;          
            case DRVPWM_CLOCK_DIV_8:
                u8Divider = 8;          
                break;          
            case DRVPWM_CLOCK_DIV_16: 
                u8Divider = 16;         
                break;      
        }       
        
        u32Frequency = u32Freqout / (sPt->u8PreScale + 1) / u8Divider / sPt->u32Duty;
    }
    else
    {
        uint8_t  u8Divider;
        uint16_t u16PreScale;
        
        u32Frequency =  u32Freqout / sPt->u32Frequency;     
        
        if (u32Frequency > 0x10000000)
            return 0;
            
        u8Divider = 1;          
            
        if (u32Frequency < 0x20000)
            u16PreScale = 2;    
        else
        {
            u16PreScale = u32Frequency / 65536; 
                            
            if (u32Frequency / u16PreScale > 65536)
                u16PreScale++;
            
            if (u16PreScale > 256)
            {
                uint8_t u8i = 0;
                
                u16PreScale = 256;
                u32Frequency = u32Frequency / u16PreScale;
                
                u8Divider = u32Frequency / 65536;               
                
                if(u32Frequency / u8Divider > 65536)
                    u8Divider++;                
                
                while(1)    
                {
                    if((1 << u8i++) > u8Divider)
                        break;
                }
                
                u8Divider = 1 << (u8i - 1);
                
                if (u8Divider > 16)
                    return 0;   
                    
                u32Frequency = u32Frequency * u16PreScale;                      
            }       
                    
        }
        u16Duty = (uint16_t )(u32Frequency/u16PreScale/u8Divider);
        
        u32Frequency = (u32Freqout / u16PreScale / u8Divider) / u16Duty;    
                
        switch (u8Timer)
        {
            case DRVPWM_TIMER0:
            case DRVPWM_TIMER1:
                PWM->PPR_BITS.CP01 = u16PreScale - 1;
                break;
            case DRVPWM_TIMER2:
            case DRVPWM_TIMER3:
                PWM->PPR_BITS.CP23 = u16PreScale - 1;
                break;
            case DRVPWM_TIMER4:
            case DRVPWM_TIMER5:
                PWM->PPR_BITS.CP45 = u16PreScale - 1;
                break;
        }
        
        switch(u8Divider)
        {
            case 1:
                u8Divider = DRVPWM_CLOCK_DIV_1;
                break;
            case 2:
                u8Divider = DRVPWM_CLOCK_DIV_2;         
                break;          
            case 4:
                u8Divider = DRVPWM_CLOCK_DIV_4;         
                break;          
            case 8:
                u8Divider = DRVPWM_CLOCK_DIV_8;         
                break;          
            case 16:
                u8Divider = DRVPWM_CLOCK_DIV_16;            
                break;      
        }               
                    
        
        u16cnrData = u16Duty - 1;
        u16cmrData = u16Duty * sPt->u8HighPulseRatio / 100 - 1;
        

		PWM->CSR = (PWM->CSR & ~(0x7 << (u8Timer * 4))) | (u8Divider << (u8Timer * 4));

        outp32(PWM_CNR0 + u8Timer * 4, u16cnrData);
        outp32(PWM_CMR0 + u8Timer * 4, u16cmrData);		       
    }
    
    return u32Frequency;
}

//*****************************************************************************
//
//! \brief This function is used to enable/disable PWM0~5 timer/capture I/O
//!  function 
//!
//! \param u8Timer DRVPWM_TIMER0 / DRVPWM_TIMER1 / DRVPWM_TIMER2 / DRVPWM_TIMER3
//!                DRVPWM_TIMER4 / DRVPWM_TIMER5 
//! \param i32Enable Enable  (1) / Diasble  (0) 
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_SetTimerIO(uint8_t u8Timer, int32_t i32Enable)
{

	assert_param((u8Timer < DRVPWM_CHANNEL_NUM)); 

    if (i32Enable)
    {
		PWM->POE |= (1 << u8Timer);
    }
    else
    {
		PWM->POE &= !(1 << u8Timer);
    }

	return;
}


//*****************************************************************************
//
//! \brief Set the attribute of all channels
//!
//! \param eMode PWM op mode
//! \param  eType PWM align type
//! \param  u8Group Enable/disable group mode
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_SetAttribute(E_DRVPWM_OP_MODE eMode, E_DRVPWM_ALIGN_TYPE eType, uint8_t u8Group)
{
    uint32_t reg;

    reg = PWM->PCR & ~0xF0000000;

    reg = reg | (eType << 31) | (u8Group << 30) | (eMode << 28);   			

	PWM->PCR = reg;
}

//*****************************************************************************
//
//! \brief Clear counter on all channels
//!
//! \param None
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_ClearCounter(void)
{
	PWM->PCR |= 0x8000000;
}

//*****************************************************************************
//
//! \brief Configure PWM period interrupt type
//!
//! \param type Interrupt type
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_SetPeriodInterruptType(E_DRVPWM_PERIOD_INT_TYPE eType)  
{
	if(eType == PWM_CNTR_UNDERFLOW)
		PWM->PIER &= ~0x20000;
	else
		PWM->PIER |= 0x20000;
}

//*****************************************************************************
//
//! \brief Specified fault break output level
//!
//! \param u8Level Output level of all PWM channels. From bit0~bit5, each bit 
//!  represents one channel
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_SetFaultBreakOutputLevel(uint8_t u8Level)
{
    uint32_t reg;
    
    reg = PWM->PFBCON;
    reg = (reg & ~0x3F000080) | (u8Level << 24);
    PWM->PFBCON = reg;
}

//*****************************************************************************
//
//! \brief Enable specified fault break source
//!
//! \param eSrc  Specify the fault break source
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_EnableFaultBreak(E_DRVPWM_FB_SRC eSrc)
{

    uint32_t reg;
    reg = PWM->PFBCON;
	switch(eSrc) {
		case PWM_FB_EINT0:
            reg |= 1;
			break;
		case PWM_FB_CPO0:
            reg |= 6;                        
            break;		
		case PWM_FB_EINT1:	
            reg = (reg & ~4) | 2;
            break;
		default:
			break;
	}
    PWM->PFBCON = reg;

}

//*****************************************************************************
//
//! \brief Disable specified fault break source
//!
//! \param eSrc  Specify the fault break source
//!
//! \return None  
//
//*****************************************************************************
void DrvPWM_DisableFaultBreak(E_DRVPWM_FB_SRC eSrc)
{
	switch(eSrc) {
		case PWM_FB_EINT0:
			PWM->PFBCON &= ~0x1;
			break;
		case PWM_FB_EINT1:
		case PWM_FB_CPO0:
			PWM->PFBCON &= ~0x2;
			break;
		default:
			break;
	}

}

//*****************************************************************************
//
//! \brief Disable specified fault break source
//!
//! \param  None
//!
//! \return None 
//!
//! \note  PWM must clear this bit to restart after FB occurred
//
//*****************************************************************************
void DrvPWM_ClearFaultBreak(void)
{
    PWM->PFBCON |= 0x80;
    return;

}


