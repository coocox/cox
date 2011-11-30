//*****************************************************************************
//
//! \file DrvSYS.c
//! \brief Contains all functions support for SYS 
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c) Nuvoton Technology Corp. All rights reserved.
//
//*****************************************************************************
#include <stdio.h>
#include "DrvSYS.h"
#include "Assert.h"


//*****************************************************************************
//
//! Global file scope (static) variables
//
//*****************************************************************************
static BOD_CALLBACK BOD_callbackFn;
static PWRWU_CALLBACK PWRWU_callbackFn;

static void	(*_pfIrcCallback)(uint32_t u32IRCStatus);
static uint32_t _gTrimCtl;

//*****************************************************************************
//
//! Auto-Trim ISR
//
//*****************************************************************************
void HIRC_IRQHandler(void)
{
	__IO uint32_t u32IRCStatus;

	u32IRCStatus = GCR->IRCTRIMISR;
	
	/* Clear interrupt status */
	GCR->IRCTRIMISR = (u32IRCStatus & 0x06);
	
	/* enable auto-trim again */
	GCR->IRCTRIMCTL = _gTrimCtl;

	/* Call	the	callback function of IRC interrupt */
	if ( _pfIrcCallback )
		_pfIrcCallback(u32IRCStatus);
}


//*****************************************************************************
//
//! \brief This function is used to get the DrvSYS version number             
//!                                                                            
//! \param None                                                               
//!                                                                           
//! \return The DrvSYS version number     
//
//*****************************************************************************
uint32_t DrvSYS_GetVersion(void)
{
    return DRVSYS_VERSION_NUM;
}

//*****************************************************************************
//
//! \brief Read Product ID             
//!                                                                            
//! \param None                                                               
//!                                                                           
//! \return Product ID      
//
//*****************************************************************************
uint32_t DrvSYS_ReadProductID(void)
{   
    return GCR->PDID;
}

//*****************************************************************************
//
//! \brief Unlock protected register             
//!                                                                            
//! \param None                                                               
//!                                                                           
//! \return - 0 Success
//!         - <0 Failed
//
//*****************************************************************************
int32_t DrvSYS_UnlockProtectedReg(void)
{
    uint32_t lockbit;
    
    GCR->RegLockAddr = 0x59;
    GCR->RegLockAddr = 0x16;
    GCR->RegLockAddr = 0x88;

    lockbit = GCR->RegLockAddr & 0x01;
    return (lockbit)? 0 : E_DRVSYS_ERR_UNLOCK_FAIL;
} 
 

//*****************************************************************************
//
//! \brief Re-Lock protected registers             
//!                                                                            
//! \param None                                                               
//!                                                                           
//! \return - 0 Success
//!         - <0 Failed
//
//***************************************************************************** 
int32_t DrvSYS_LockProtectedReg(void)
{
    uint32_t lockbit;
    
    GCR->RegLockAddr = 0x00;

    lockbit = GCR->RegLockAddr & 0x01;
    return (lockbit)? E_DRVSYS_ERR_LOCK_FAIL : 0;
}


//*****************************************************************************
//
//! \brief This function is used to check the protected registers are locked or
//!        not             
//!                                                                            
//! \param None                                                               
//!                                                                           
//! \return - 1 The protected Registers are unlocked 
//!         - 0 The protected Registers are locked 
//
//*****************************************************************************
int32_t DrvSYS_IsProtectedRegLocked(void)
{
    return GCR->RegLockAddr & 0x01;
}

//*****************************************************************************
//
//! \brief Get reset source from last operation             
//!                                                                            
//! \param None                                                               
//!                                                                           
//! \return Reset source       
//
//*****************************************************************************
uint32_t DrvSYS_GetResetSource(void)
{
    return GCR->RST_SRC;
}

//*****************************************************************************
//
//! \brief Clear reset source by write 1              
//!                                                                            
//! \param u32Src The corresponding bit of reset source                                                                
//!                                                                           
//! \return 0       
//
//*****************************************************************************
uint32_t DrvSYS_ClearResetSource(uint32_t u32Src)
{
    GCR->RST_SRC = u32Src;
    return 0;
}

//*****************************************************************************
//
//! \brief Reset coresponding IP              
//!                                                                            
//! \param eIpRst The coresponding IP
//!
//! The \e eIpRst can be one of the following values:
//! \b E_SYS_GPIO_RST, \b E_SYS_TMR0_RST, \b E_SYS_TMR1_RST, \b E_SYS_I2C_RST, 
//! \b E_SYS_SPI_RST, \b E_SYS_UART_RST, \b E_SYS_PWM_RST, \b E_SYS_ADC_RST, 
//! \b E_SYS_ACMP_RST
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_ResetIP(E_SYS_IP_RST eIpRst)
{   
    uint32_t u32Reg;

    u32Reg = GCR->IPRST_CTL2;
    GCR->IPRST_CTL2 = u32Reg | (1<<eIpRst);
    GCR->IPRST_CTL2 = u32Reg & ~(1<<eIpRst);
 }

//*****************************************************************************
//
//! \brief Reset CPU              
//!                                                                            
//! \param None
//!    
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_ResetCPU(void)
{
    UNLOCKREG();
    GCR->IPRST_CTL1_BITS.CPU_RST = 1;
    LOCKREG();
}

//*****************************************************************************
//
//! \brief Reset whole chip              
//!                                                                            
//! \param None 
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_ResetChip(void)
{
	UNLOCKREG();
	GCR->IPRST_CTL1_BITS.CHIP_RST = 1;
	LOCKREG();
}

//*****************************************************************************
//
//! \brief Select Brown-Out Detector threshold voltage              
//!                                                                            
//! \param u8Volt BOD voltage value, it can be selected form one of the
//!               following value: 3-Disable BOD
//!                                - 2:3.8V
//!                                - 1:2.7V
//!    
//! \note Please make sure that Register Write-Protection Function has been 
//!       disabled before using this function to select BOD threshold voltage.  
//!       User can check the status of Register Write-Protection Function
//!       with DrvSYS_IsProtectedRegLocked().   
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_SelectBODVolt(uint8_t u8Volt)
{
	UNLOCKREG();
	GCR->BODCTL_BITS.VL = u8Volt;
	LOCKREG();
}


//*****************************************************************************
//
//! \brief Enable Brown-Out Detector, and select BOD reset function or interrupt
//!        function. And, install call backfunction if interrupt function is 
//!        selected.              
//!                                                                            
//! \param ignored
//!
//! \param i32Flag if \b 1 Enable BOD reset function, \b 0 Enable BOD interrupt 
//!        function
//!    
//! \param bodcallbackFn BOD Call back function
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_SetBODFunction(int32_t i32Enable, int32_t i32Mode, BOD_CALLBACK bodcallbackFn)
{
    UNLOCKREG();	
    GCR->BODCTL_BITS.RSTEN = i32Mode;
    LOCKREG();
    
    if (i32Mode)
    {       
         NVIC_DisableIRQ(BOD_IRQn);
    }
    else
    { 
        BOD_callbackFn = bodcallbackFn;
        NVIC_SetPriority(BOD_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
        NVIC_EnableIRQ(BOD_IRQn);
     }   
}

//*****************************************************************************
//
//! \brief Get Brown-Out Detector state            
//!                                                                            
//! \param None 
//! 
//! \return BOD output status - 1: the detected voltage is lower than BOD 
//!                                threshold voltage    
//!                           - 0: the detected voltage is higher than BOD
//!                                threshold voltage
//
//*****************************************************************************
uint32_t DrvSYS_GetBODState(void)
{
    return GCR->BODCTL_BITS.OUT;
}

//*****************************************************************************
//
//! \brief Enable power on reset (POR) control          
//!                                                                            
//! \param None   
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_EnablePOR(void)
{
    UNLOCKREG();
    GCR->PORCTL = 0;
    LOCKREG();
}


//*****************************************************************************
//
//! \brief Disable power on reset (POR) control          
//!                                                                            
//! \param None   
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_DisablePOR(void)
{
    UNLOCKREG();
    GCR->PORCTL = 0x5AA5;
    LOCKREG();
}

//*****************************************************************************
//
//! \brief ISR to handle BOD interrupt event         
//!                                                                            
//! \param None 
//! 
//! \return None       
//
//*****************************************************************************
void BOD_IRQHandler(void)
{
    GCR->BODCTL_BITS.INTF = 1;
    if (BOD_callbackFn != NULL)
        BOD_callbackFn();

}

//*****************************************************************************
//
//! \brief Enable/Disable coresponding IP clock              
//!                                                                            
//! \param eIpClk The coresponding IP
//!
//! \param i32Enable When \b 1 Enable the corresponding IP, while \b 0 Disable
//!
//! The \e eIpClk can be one of the following values:
//! \b E_SYS_WDT_CLK, \b E_SYS_TMR0_CLK, \b E_SYS_TMR1_CLK, \b E_SYS_I2C_CLK, 
//! \b E_SYS_SPI_CLK, \b E_SYS_UART_CLK, \b E_SYS_PWM01_CLK, \b E_SYS_ACMP_CLK,
//! \b E_SYS_PWM23_CLK, \b E_SYS_PWM45_CLK, \b E_SYS_ADC_CLK, \b E_SYS_ISP_CLK,
//! 
//! \return None       
//
//*****************************************************************************
void DrvSYS_SetIPClock(E_SYS_IP_CLK eIpClk, int32_t i32Enable)
{   
    uint32_t u32Reg;

    if (eIpClk == E_SYS_ISP_CLK)
    {
        CLK->AHBCLK_BITS.ISP_EN = i32Enable;
    }
    else
    {
        u32Reg = CLK->APBCLK;
        
        if (i32Enable)
        {
            CLK->APBCLK = u32Reg | (1<<eIpClk);
        }
        else
        {
            CLK->APBCLK = u32Reg & ~(1<<eIpClk);
        }
    }
}

//*****************************************************************************
//
//! \brief This function is used to select HCLK clock source              
//!                                                                            
//! \param u8ClkSrcSel The clock source can be slected form one of the following
//!                    value:
//!                    - 0:External 12M clock
//!                    - 3:Internal 10K clock 
//!                    - 7:Internal 22M clock
//! 
//! \return - 0:Success 
//!         - E_DRVSYS_ERR_CLKSWITCH_FAIL:Clock switch failed 
//
//*****************************************************************************
int32_t DrvSYS_SelectHCLKSource(uint8_t u8ClkSrcSel)
{
    assert_param(CHECK_HCLK_SOURCE(u8ClkSrcSel));

    UNLOCKREG();
    CLK->CLKSEL0_BITS.HCLK_S = u8ClkSrcSel;
    LOCKREG();

    if (CLK->CLKSTATUS_BITS.CLK_SW_FAIL)
    {
          /* Clear Clock Switch Fail Flag */
          CLK->CLKSTATUS_BITS.CLK_SW_FAIL = 1;
          return E_DRVSYS_ERR_CLKSWITCH_FAIL;
    }
    
    SystemCoreClockUpdate();

    return 0;
}

//*****************************************************************************
//
//! \brief This function is used to select system tick clock source             
//!                                                                            
//! \param u8ClkSrcSel The clock source can be slected form one of the following
//!                    value:
//!                    - 0:External 12M or 32KHz clock
//!                    - 2:External 12M or 32KHz clock / 2
//!                    - 3:HCLK / 2 
//!                    - 4~7:Internal 22M clock / 2
//! 
//! \return - 0:Success 
//
//*****************************************************************************
int32_t DrvSYS_SelectSysTickSource(uint8_t u8ClkSrcSel)
{
    assert_param(CHECK_SYSTICK_SOURCE(u8ClkSrcSel));
    
    UNLOCKREG();
    CLK->CLKSEL0_BITS.STCLK_S = u8ClkSrcSel;
    LOCKREG();

    return 0;
}

//*****************************************************************************
//
//! \brief This function is used to select IP clock source             
//!                                                                            
//! \param eIpClkSrc The coresponding IP
//!
//! \param u8ClkSrcSel It can be one of the following value:
//!                    \b 0x00, \b 0x01, \b 0x02, \b 0x03, \b 0x07
//!
//! The \e eIpClkSrc can be one of the following values:
//! \b E_SYS_WDT_CLKSRC, \b E_SYS_ADC_CLKSRC, \b E_SYS_TMR0_CLKSRC, 
//! \b E_SYS_TMR1_CLKSRC, \b E_SYS_UART_CLKSRC, \b E_SYS_PWM01_CLKSRC,
//! \b E_SYS_PWM23_CLKSRC, \b E_SYS_PWM45_CLKSRC,\b E_SYS_FRQDIV_CLKSRC
//!
//!  --------------------------------------------------------------------------------------------
//!  |  u8ClkSrcSel  |     0x00     |     0x01     |     0x02     |     0x03     |     0x07     |
//!  --------------------------------------------------------------------------------------------
//!  |      WDT      |   Reserved   |   Reserved   |   HCLK/2048  | Internal 10K |      X       |
//!  --------------------------------------------------------------------------------------------
//!  |      ADC      | External 12M |     PLL      |   Reserved   | Internal 22M |      X       |
//!  --------------------------------------------------------------------------------------------
//!  |    TMR 0~1    | External 12M |   Reserved   |     HCLK     |   Reserved   | Internal 22M |
//!  --------------------------------------------------------------------------------------------
//!  |      UART     | External 12M |     PLL      |   Reserved   | Internal 22M |      X       |
//!  --------------------------------------------------------------------------------------------
//!  |      PWM      | External 12M |   Reserved   |     HCLK     | Internal 22M |      X       |
//!  --------------------------------------------------------------------------------------------
//!  |   Frequency   | External 12M |   Reserved   |     HCLK     | Internal 22M |      X       |
//!  | Divider Output|              |              |              |              |              |
//!  -------------------------------------------------------------------------------------------- 
//!     
//! 
//! \return - 0:Success 
//
//*****************************************************************************
int32_t DrvSYS_SelectIPClockSource(uint32_t u32IpClkSrc, uint8_t u8ClkSrcSel)
{
     uint32_t u32Mask, u32BitPos, u32RegNum;
	 
     assert_param(CHECK_IP_CLKSRC(u32IpClkSrc));

     u32BitPos = (u32IpClkSrc & 0x0000FF00) >> 8;
     u32Mask  = (u32IpClkSrc & 0x000000FF)  << u32BitPos;
     u32RegNum = (u32IpClkSrc & 0x00FF0000) >> 16;

     if (u32RegNum == 1)
	 	CLK->CLKSEL1 = (CLK->CLKSEL1 & (~u32Mask)) | (u8ClkSrcSel << u32BitPos);
     else
	 	CLK->CLKSEL2 = (CLK->CLKSEL1 & (~u32Mask)) | (u8ClkSrcSel << u32BitPos);
   
    return E_SUCCESS;
}


//*****************************************************************************
//
//! \brief This function is used to set IP divider number from the corresponding
//!        clock source The actual clock divide number is (i32value + 1).             
//!                                                                            
//! \param eIpDiv The IP can be slected form one of the following value:
//!               \b E_SYS_ADC_DIV, \b E_SYS_UART_DIV, \b E_SYS_HCLK_DIV
//!        i32value The Values can be 0 ~ 255 for ADC, 0 ~ 15 for UART or HCLK
//!    
//! \note None
//! 
//! \return - 0:Success 
//!         - <0:Incorrect value
//
//*****************************************************************************
int32_t DrvSYS_SetClockDivider(uint32_t u32IpDiv , int32_t i32value)
{
     uint32_t u32Mask, u32BitPos;
	 
     assert_param(CHECK_IP_CLKDIV(u32IpDiv));

     u32BitPos = (u32IpDiv & 0x0000FF00) >> 8;
     u32Mask  = (u32IpDiv & 0x000000FF)  << u32BitPos;

     CLK->CLKDIV = (CLK->CLKDIV & (~u32Mask)) | (i32value << u32BitPos);

     if (u32IpDiv == HCLK_CLK_DIV)
	 	SystemCoreClockUpdate();

    return E_SUCCESS;   
}

//*****************************************************************************
//
//! \brief This function is used to enable/disable internal oscillator or 
//!        external crystal           
//!                                                                            
//! \param eClkSrc The clock source can be slected form one of the following value:
//!               \b E_SYS_XTL12M, \b E_SYS_OSC22M, \b E_SYS_OSC10K
//!
//! \param i32Enable - 1: Enable
//!                  - 0: Disable
//!
//! \return - 0:Success 
//
//*****************************************************************************
int32_t DrvSYS_SetOscCtrl(uint32_t u32ClkSrc, int32_t i32Enable)
{   
    uint32_t u32ClkEn, u32ClkEnMask;

    assert_param(CHECK_CLK_ALL(u32ClkSrc));
	
    u32ClkEn     =  u32ClkSrc & 0x000000FF;
    u32ClkEnMask = (u32ClkSrc & 0x0000FF00) >> 8;	
	
    UNLOCKREG();

    CLK->PWRCON &= (~u32ClkEnMask);
    if (i32Enable == 1)
		CLK->PWRCON |= u32ClkEn;

    LOCKREG();
	
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief ISR to handle Power Down Wake up interrupt event          
//!                                                                            
//! \param None
//!    
//! \note None
//! 
//! \return None
//
//*****************************************************************************
void PWRWU_IRQHandler(void)
{
    CLK->PWRCON_BITS.PD_WK_STS = 1;
    if (PWRWU_callbackFn != NULL)
        PWRWU_callbackFn(); 
}

//*****************************************************************************
//
//! \brief Enable or disable Power dowm Wake up interrupt function, and install
//! call back function. And, enable or disable clock cycles delay to wait oscillator
//! clock stable.The delayed clock cycle is 4096 clock cycles when chip work at 
//! external 4~24 MHz crystal,or 256 clock cycles when chip work at internal 22.1184
//! MHz oscillator.
//!                                                                                          
//! \param i32Enable - 1:Enable Power dowm Wake up interrup 
//!                  - 0:Disable Power dowm Wake up interrup
//!
//! \param pdwucallbackFn Power Down Wake Up Call back function 
//!
//! \param i32enWUDelay - 1:Enable clock cycles delay
//!                     - 0:Disable clock cycles delay
//! 
//! \return None 
//
//*****************************************************************************
void DrvSYS_SetPowerDownWakeUpInt(int32_t i32Enable, PWRWU_CALLBACK pdwucallbackFn, int32_t i32enWUDelay)
{
    UNLOCKREG();
    CLK->PWRCON_BITS.PD_WK_IE = i32Enable;
        
    if (i32Enable)
    {       
        CLK->PWRCON_BITS.WK_DLY = i32enWUDelay;
        PWRWU_callbackFn = pdwucallbackFn;
        NVIC_SetPriority(PDWU_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
        NVIC_EnableIRQ(PDWU_IRQn);
    }
    else
    { 
        CLK->PWRCON_BITS.WK_DLY = 0;
        PWRWU_callbackFn = NULL;
        NVIC_DisableIRQ(PDWU_IRQn);
    }   
    LOCKREG();
}

//*****************************************************************************
//
//! \brief Enter power down function         
//!                                                                            
//! \param ePDType The power down type can be selected foem one of the following
//!                values:\b 1 : If  LXT 32K is enabled, it will still be avtice 
//!                in power down mode.\b 0 : No effect in power down mode
//! 
//! \return None
//
//*****************************************************************************
void DrvSYS_EnterPowerDown(int32_t i32Active32K)
{   
     UNLOCKREG();
     CLK->PWRCON_BITS.PD_32K_EN = i32Active32K;
     CLK->PWRCON_BITS.PD_EN = 1;
     LOCKREG();	 
}


//*****************************************************************************
//
//! \brief Get external clock frequency. The clock UNIT is in Hz.          
//!                                                                            
//! \param None
//!    
//! \note None
//! 
//! \return The external clock frequency. The default clock is 12MHz. 
//
//*****************************************************************************
uint32_t DrvSYS_GetExtClockFreq(void)
{   
	if (CLK->PWRCON_BITS.XTLCLK_EN == 1)
		return __XTAL12M;
	else
		return __XTAL32K;
}

//*****************************************************************************
//
//! \brief Get HCLK clock and the UNIT is in Hz.        
//!                                                                            
//! \param None
//!    
//! \note None
//! 
//! \return HCLK clock frequency in Hz.   
//
//*****************************************************************************
uint32_t DrvSYS_GetHCLKFreq(void)
{   
    uint32_t u32Freqout = 0, u32AHBDivider;

    if (CLK->CLKSEL0_BITS.HCLK_S == 0)        /* external 12MHz crystal clock */
    {
        u32Freqout = (CLK->PWRCON_BITS.XTLCLK_EN == 1) ? __XTAL12M : __XTAL32K ;    
    }
    else if(CLK->CLKSEL0_BITS.HCLK_S == 3)    /* internal 10KHz oscillator clock */
    {
        u32Freqout = __IRC10K;
    }
    else                                    /* internal 22MHz oscillator clock */
    {
        u32Freqout = __IRC22M;
    
    }
    u32AHBDivider = CLK->CLKDIV_BITS.HCLK_N + 1 ;
    
    return (u32Freqout/u32AHBDivider);  
}

//*****************************************************************************
//
//! \brief This function enable the selected clock as the source of HCLK. The 
//! staus of unselected clock  keep unchanged.
//!                                                                            
//! \param u32HclkSrc The selected clock source for HCLK. The value cound be  
//!                   XTL_CLK, XTL32K_CLK,OSC22M_CLK or OSC10K_CLK                                       
//!    
//! 
//!
//! \return - E_SUCCESS:Success 
//!         - E_DRVSYS_ERR_CLKSSRC_UNSTABLE:The selected clock source is unstable.
//
//*****************************************************************************
int32_t DrvSYS_Open(uint32_t u32HclkSrc)
{
    uint32_t u32ClkEn, u32ClkEnMask, u32ClkSts, u32HclkSel;
	
    assert_param(CHECK_CLK_ALL(u32HclkSrc));

    u32ClkEn     =  u32HclkSrc & 0x000000FF;
    u32ClkEnMask = (u32HclkSrc & 0x0000FF00) >> 8;	
    u32ClkSts    = (u32HclkSrc & 0x00FF0000) >> 16;
    u32HclkSel   = (u32HclkSrc & 0xFF000000) >> 24;

    if (u32ClkEn & 0x03)
		GCR->P5_MFP = (GCR->P5_MFP & 0x00FFFCFC) | 0x03; /* P5.1 -> XTAL2, P5.0 -> XTAL1 */
	
    UNLOCKREG();
    CLK->PWRCON = (CLK->PWRCON & (~u32ClkEnMask)) | u32ClkEn; /* enable selected clock source */
    DrvSYS_Delay(1200);

    if ((CLK->CLKSTATUS & u32ClkSts) == 0)
	   return E_DRVSYS_ERR_CLKSSRC_UNSTABLE;
				
    CLK->CLKDIV_BITS.HCLK_N = 0;
    CLK->CLKSEL0_BITS.HCLK_S = u32HclkSel;
    LOCKREG();
			
    SystemCoreClockUpdate();
	
    return E_SUCCESS;
}


//*****************************************************************************
//
//! \brief Enable frequency clock output and set its divider value. The output 
//!        frequency = Fin/2^(N+1), Fin is the input clock frequency, N is 4-bit
//!        value       
//!                                                                            
//! \param i32Flag - 1:Enable
//!                - 0:Disable
//!   
//! \param u8Divider The divider of output frequency (0~15)   
//! 
//! \return - 0:Success 
//
//*****************************************************************************
int32_t DrvSYS_SetFreqDividerOutput(int32_t i32Flag, uint8_t u8Divider)
{
   assert_param(CHECK_FREQ_DIVIDER(u8Divider));

    if (i32Flag)
    {
        CLK->FRQDIV_BITS.FSEL = u8Divider;
    }
    CLK->FRQDIV_BITS.FDIV_EN = i32Flag;       
    DrvSYS_SetIPClock(E_SYS_FDIV_CLK, i32Flag);

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Use the SysTick to generate the delay time and the UNIT is in us 
//!        The SysTick clock source is from HCLK.      
//!                                                                            
//! \param us Delay time. The Max value is 335000
//! 
//! \return  None 
//
//*****************************************************************************
void DrvSYS_Delay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  =  (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
//
// Waiting for down-count to zero
//
    while((SysTick->CTRL & (1 << 16)) == 0);
}

//*****************************************************************************
//
//! \brief This function is used to monitor if the chip clock source is stable
//!        or not      
//!                                                                            
//! \param uClkSrc The chip clock source can be selected form the following value:
//!         \b XTL_CLK, \b XTL_CLK, \b OSC22M_CLK, \b XTL32K_CLK, \b OSC10K_CLK
//! 
//! \return - 0:Clock source is not stable or not enabled 
//!         - 1:Clock source is stable 
//
//*****************************************************************************
int32_t DrvSYS_GetChipClockSourceStatus(uint32_t u32ClkSrc)
{
    uint32_t u32ClkSts;
    int32_t   i32Status;
	
    assert_param(CHECK_CLK_ALL(u32ClkSrc));

    u32ClkSts = (u32ClkSrc & 0x00FF0000) >> 16;

    if (CLK->CLKSTATUS & u32ClkSts)
		i32Status = 1 ;
    else
	       i32Status = 0;
	
    return i32Status;      
}


//*****************************************************************************
//
//! \brief This function is used to get if switch target clock is successful or
//!        not when software switches system clock source.     
//!                                                                            
//! \param None
//! 
//! \return - 1:Clock switch fail
//!         - 0:Clock switch success 
//
//*****************************************************************************
uint32_t DrvSYS_GetClockSwitchStatus(void)
{   
    return CLK->CLKSTATUS_BITS.CLK_SW_FAIL;
}

//*****************************************************************************
//
//! \brief This function is used to clear the Clock Switch Fail Flag 
//!                                                                            
//! \param None
//! 
//! \return None
//
//*****************************************************************************
void DrvSYS_ClearClockSwitchStatus(void)
{
     CLK->CLKSTATUS_BITS.CLK_SW_FAIL = 1;
}

//*****************************************************************************
//
//! \brief This function is used to enable auto-trim fucntion.
//!                                                                                          
//! \param sParam - the struct parameter to configure IRC-Trim include of                                                                             */
//! u8cRetryCnt - E_SYS_RETRY_64/E_SYS_RETRY_128/E_SYS_RETRY_256/E_SYS_RETRY_512								        
//! u8cLoop - E_SYS_LOOP_4 / E_SYS_LOOP_8 / E_SYS_LOOP_16 / E_SYS_LOOP_32
//!
//! \param pfncallback A function pointer for callback function. 
//!
//! 
//! \return   -     0:  success																			 
//!               < 0:  32K clock not enable	
//
//*****************************************************************************
int32_t DrvSYS_EnableAutoTrim(STR_IRC_T *sParam, DRVSYS_IRC_CALLBACK pfncallback)
{
	if (CLK->PWRCON_BITS.XTLCLK_EN != 0x2)	/* Not enable the 32K */
		return E_DRVSYS_ERR_32K_CLK_FAIL;

	_gTrimCtl = ((sParam->u8cRetryCnt << 6) | (sParam->u8cLoop << 4) | 0x01);
	_pfIrcCallback = (void (*)(uint32_t))pfncallback;
//
// enable trim-fail and 32K-error interrupt
//
	GCR->IRCTRIMIER = 0x06;
	NVIC_EnableIRQ(HIRC_IRQn);

	GCR->IRCTRIMCTL = _gTrimCtl;

	return E_SUCCESS;
}


//*****************************************************************************
//
//! \brief This function is used to disable auto-trim function. 
//!                                                                            
//! \param None
//! 
//! \return None
//
//*****************************************************************************
void DrvSYS_DisableAutoTrim(void)
{
	GCR->IRCTRIMCTL_BITS.TRIM_SEL = 0;
//
// disable trim-fail and 32K-error interrupt
//
	GCR->IRCTRIMIER = 0;
	_gTrimCtl = 0;
	_pfIrcCallback = NULL;
	NVIC_DisableIRQ(HIRC_IRQn);
}
