//*****************************************************************************
//
//! \file xsysctl.c
//! \brief Driver for the system controller
//! \version V2.2.1.0
//! \date 6/15/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
#include "hw_sysctl.h"
#include "CoX.h"
#include "sysctl.h"


static unsigned long s_ulExtClockkHz = 32;

//*****************************************************************************
//
//! Peripheral Base and ID Table structure type
//
//*****************************************************************************
typedef struct 
{
    unsigned long ulPeripheralBase;
    unsigned long ulPeripheralID;
    unsigned long ulPeripheralIntNum;
}tPeripheralTable;

//*****************************************************************************
//
//! An array that maps the peripheral base and peripheral ID and interrupt number
//! together to enablea peripheral or peripheral interrupt by a peripheral base.
//
//*****************************************************************************
static const tPeripheralTable g_pPeripherals[] =
{
    {xADC0_BASE,       xSYSCTL_PERIPH_ADC0,    xINT_ADC0},
    {xACMP_BASE,       xSYSCTL_PERIPH_ACMP,    xINT_ACMP},
    {xDMA0_BASE,       xSYSCTL_PERIPH_DMA0,    xINT_DMA0},
    {xGPIO_PORTA_BASE, xSYSCTL_PERIPH_GPIOA,   xINT_GPIOA},
    {xI2C0_BASE,       xSYSCTL_PERIPH_I2C0,    xINT_I2C0},
    {RTC_BASE,         xSYSCTL_PERIPH_RTC,     xINT_RTC},
    {xSPI0_BASE,       xSYSCTL_PERIPH_SPI0,    xINT_SPI0},
    {xTIMER0_BASE,     xSYSCTL_PERIPH_TIMER0,  xINT_TIMER0},
    {xTIMER1_BASE,     xSYSCTL_PERIPH_TIMER1,  xINT_TIMER1},
    {xUART0_BASE,      xSYSCTL_PERIPH_UART0,   xINT_UART0},
    {xPWMA_BASE,       xSYSCTL_PERIPH_PWMA,    xINT_PWMA},
    {xWDT_BASE,        xSYSCTL_PERIPH_WDOG,    xINT_WDT},
    {0,                0,                      0},
};
                                
//*****************************************************************************
//
//! \brief Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.  It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! The loop takes 3 cycles/loop.
//!
//! \return None.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
void __attribute__((naked))
xSysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne     xSysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(ewarm) || defined(__ICCARM__)
void
xSysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   xSysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__CC_ARM)
__asm void
xSysCtlDelay(unsigned long ulCount)
{
    subs    r0, #1;
    bne     xSysCtlDelay;
    bx      lr;
}
#endif

//*****************************************************************************
//
//! \internal
//! \brief Checks a peripheral identifier.
//!
//! \param ulPeripheral is the peripheral identifier.
//!
//! This function determines if a peripheral identifier is valid.
//!
//! \return Returns \b true if the peripheral identifier is valid and \b false
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Set the clock of the device.
//!
//! \param ulSysClk is the clock rate that you will set.
//! \param ulConfig is the required configuration of the device clock. For AU9110,
//!  there are three clock can be selected:
//! - xSYSCTL_OSC_INT        49M hz
//! - xSYSCTL_OSC_INTSL      16k hz
//! - SYSCTL_OSC_EXTSL       32k hz
//!
//! /note ulSysClk is not used in AU9110 CoX.
//!
//! Details please refer to \ref XSysCtl_Clock_Set_Config_CoX.
//! 
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig)
{

    xASSERT((ulSysClk > 0 && ulSysClk <= 49000000));

    SysCtlHCLKSourceSet(ulConfig);
}

//*****************************************************************************
//
//! \brief The function is used to Get HCLK clock and the UNIT is in Hz
//!
//! \param None.
//!
//! The function is used to Get HCLK clock and the UNIT is in Hz
//!
//! \return HCLK clock frequency in Hz
//
//*****************************************************************************
unsigned long
xSysCtlClockGet(void)
{
	unsigned long ulHCLKSrc;

	ulHCLKSrc = xHWREG(SYSCLK_CLKSEL0) & SYSCLK_CLKSEL0_HCLK_S_M;

	if(ulHCLKSrc == 0)
	{
		return 48000000;
	}
	else if (ulHCLKSrc == 1)
	{
        return 32000;
	}
	else
	{
        return 16000;
	}
}

//*****************************************************************************
//
//! \brief Disables a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are disabled with this function.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \return None.
//
//*****************************************************************************
void 
xSysCtlPeripheralDisable2(unsigned long ulPeripheralBase)
{
    unsigned long i;

    xASSERT((ulPeripheralBase == xADC0_BASE) ||
    		(ulPeripheralBase == xACMP_BASE) ||
    		(ulPeripheralBase == xDMA0_BASE) ||
    		(ulPeripheralBase == xGPIO_PORTA_BASE) ||
    		(ulPeripheralBase == xI2C0_BASE) ||
    		(ulPeripheralBase == xRTC_BASE) ||
    		(ulPeripheralBase == xSPI0_BASE) ||
    		(ulPeripheralBase == xTIMER0_BASE) ||
    		(ulPeripheralBase == xTIMER1_BASE) ||
    		(ulPeripheralBase == xUART0_BASE) ||
    		(ulPeripheralBase == xPWMA_BASE) ||
    		(ulPeripheralBase == xPWMB_BASE) ||
    		(ulPeripheralBase == xWDT_BASE)
    		);

    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            xSysCtlPeripheralDisable(g_pPeripherals[i].ulPeripheralID);
            break;
        }
    }
}
        
//*****************************************************************************
//
//! \brief Reset a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! Reset.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \return None.
//
//*****************************************************************************
void 
xSysCtlPeripheralReset2(unsigned long ulPeripheralBase)
{
    unsigned long i;

    xASSERT((ulPeripheralBase == xADC0_BASE) ||
    		(ulPeripheralBase == xACMP_BASE) ||
    		(ulPeripheralBase == xDMA0_BASE) ||
    		(ulPeripheralBase == xGPIO_PORTA_BASE) ||
    		(ulPeripheralBase == xI2C0_BASE) ||
    		(ulPeripheralBase == xRTC_BASE) ||
    		(ulPeripheralBase == xSPI0_BASE) ||
    		(ulPeripheralBase == xTIMER0_BASE) ||
    		(ulPeripheralBase == xTIMER1_BASE) ||
    		(ulPeripheralBase == xUART0_BASE) ||
    		(ulPeripheralBase == xPWMA_BASE) ||
    		(ulPeripheralBase == xPWMB_BASE) ||
    		(ulPeripheralBase == xWDT_BASE)
    		);

    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            xSysCtlPeripheralReset(g_pPeripherals[i].ulPeripheralID);
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief Get the peripheral interrupt number through peripheral base.
//!
//! \param ulPeripheral The peripheral's base  
//!
//! \note It's especially useful to enable the short pin's corresponding 
//! peripheral interrupt: Use the short pin to Get the GPIO base through 
//! \ref xGPIOSPinToPort() function, and then use this function to enable the 
//! GPIO interrupt.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
xSysCtlPeripheralIntNumGet(unsigned long ulPeripheralBase)
{
    unsigned long i;
    
    xASSERT((ulPeripheralBase == xADC0_BASE) ||
    		(ulPeripheralBase == xACMP_BASE) ||
    		(ulPeripheralBase == xDMA0_BASE) ||
    		(ulPeripheralBase == xGPIO_PORTA_BASE) ||
    		(ulPeripheralBase == xI2C0_BASE) ||
    		(ulPeripheralBase == xRTC_BASE) ||
    		(ulPeripheralBase == xSPI0_BASE) ||
    		(ulPeripheralBase == xTIMER0_BASE) ||
    		(ulPeripheralBase == xTIMER1_BASE) ||
    		(ulPeripheralBase == xUART0_BASE) ||
    		(ulPeripheralBase == xPWMA_BASE) ||
    		(ulPeripheralBase == xPWMB_BASE) ||
    		(ulPeripheralBase == xWDT_BASE)
    		);
            
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            break;
        }
    }
    return g_pPeripherals[i].ulPeripheralIntNum;
}

//*****************************************************************************
//
//! \brief Performs a software reset of a peripheral.
//!
//! \param ulPeripheral is the peripheral to reset.
//!
//! This function performs a software reset of the specified peripheral.  An
//! individual peripheral reset signal is asserted for a brief period and then
//! deasserted, returning the internal state of the peripheral to its reset
//! condition.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b xSYSCTL_PERIPH_RTC, \b xSYSCTL_PERIPH_SPI0,\b xSYSCTL_PERIPH_TIMER0,
//! \b xSYSCTL_PERIPH_TIMER1,\b xSYSCTL_PERIPH_UART0,\b xSYSCTL_PERIPH_WDOG,
//! \b xSYSCTL_PERIPH_I2S0,\b SYSCTL_PERIPH_PWM01, \b xSYSCTL_PERIPH_DMA0,
//! \b xSYSCTL_PERIPH_I2C0
//!  
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralReset(unsigned long ulPeripheral)
{

    //
    // Check the arguments.
    //
    xASSERT((ulPeriphClkID == xSYSCTL_PERIPH_RTC) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_SPI0) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_TIMER0) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_TIMER1) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_UART0) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_WDOG) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_I2S0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_PWM01) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_DMA0) ||
            (ulPeriphClkID == xSYSCTL_PERIPH_I2C0)
            );

    SysCtlIPReset(ulPeripheral);
}

//*****************************************************************************
//
//! \brief Enables a peripheral.
//!
//! \param ulPeripheral is the peripheral base address to be enabled.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b xSYSCTL_PERIPH_WDOG, \b xSYSCTL_PERIPH_RTC, \b xSYSCTL_PERIPH_TIMER0,
//! \b xSYSCTL_PERIPH_TIMER1,\b xSYSCTL_PERIPH_I2C0, \b xSYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0, \b xSYSCTL_PERIPH_UART0,
//! \b xSYSCTL_PERIPH_PWMA,\b xSYSCTL_PERIPH_PWMB, \b xSYSCTL_PERIPH_ACMP,
//! \b xSYSCTL_PERIPH_ADC0,\b xSYSCTL_PERIPH_I2S0, \b xSYSCTL_PERIPH_DMA0
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralEnable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
	xASSERT((ulPeriphClkID == SYSCTL_PERIPH_WDG) ||
			(ulPeriphClkID == SYSCTL_PERIPH_RTC) ||
			(ulPeriphClkID == xSYSCTL_PERIPH_TIMER0) ||
			(ulPeriphClkID == xSYSCTL_PERIPH_TIMER1) ||
			(ulPeriphClkID == SYSCTL_PERIPH_I2C0) ||
			(ulPeriphClkID == SYSCTL_PERIPH_SPI0) ||
			(ulPeriphClkID == SYSCTL_PERIPH_DPWM) ||
			(ulPeriphClkID == SYSCTL_PERIPH_UART0) ||
			(ulPeriphClkID == SYSCTL_PERIPH_BIQALC) ||
			(ulPeriphClkID == SYSCTL_PERIPH_CRC) ||
			(ulPeriphClkID == SYSCTL_PERIPH_PWM01) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ACMP) ||
			(ulPeriphClkID == SYSCTL_PERIPH_SBRAM) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ADC) ||
			(ulPeriphClkID == SYSCTL_PERIPH_I2S) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ANA) ||
			(ulPeriphClkID == SYSCTL_PERIPH_PDMA) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ISP)
			);

	SysCtlIPClockSet(ulPeripheral, 1);
}

//*****************************************************************************
//
//! \brief Disable a peripheral.
//!
//! \param ulPeripheral is the peripheral base address to be Disabled.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b xSYSCTL_PERIPH_WDOG, \b xSYSCTL_PERIPH_RTC, \b xSYSCTL_PERIPH_TIMER0,
//! \b xSYSCTL_PERIPH_TIMER1,\b xSYSCTL_PERIPH_I2C0, \b xSYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0, \b xSYSCTL_PERIPH_UART0,
//! \b xSYSCTL_PERIPH_PWMA,\b xSYSCTL_PERIPH_PWMB, \b xSYSCTL_PERIPH_ACMP,
//! \b xSYSCTL_PERIPH_ADC0,\b xSYSCTL_PERIPH_I2S0, \b xSYSCTL_PERIPH_DMA0
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralDisable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
	xASSERT((ulPeriphClkID == SYSCTL_PERIPH_WDG) ||
			(ulPeriphClkID == SYSCTL_PERIPH_RTC) ||
			(ulPeriphClkID == xSYSCTL_PERIPH_TIMER0) ||
			(ulPeriphClkID == xSYSCTL_PERIPH_TIMER1) ||
			(ulPeriphClkID == SYSCTL_PERIPH_I2C0) ||
			(ulPeriphClkID == SYSCTL_PERIPH_SPI0) ||
			(ulPeriphClkID == SYSCTL_PERIPH_DPWM) ||
			(ulPeriphClkID == SYSCTL_PERIPH_UART0) ||
			(ulPeriphClkID == SYSCTL_PERIPH_BIQALC) ||
			(ulPeriphClkID == SYSCTL_PERIPH_CRC) ||
			(ulPeriphClkID == SYSCTL_PERIPH_PWM01) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ACMP) ||
			(ulPeriphClkID == SYSCTL_PERIPH_SBRAM) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ADC) ||
			(ulPeriphClkID == SYSCTL_PERIPH_I2S) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ANA) ||
			(ulPeriphClkID == SYSCTL_PERIPH_PDMA) ||
			(ulPeriphClkID == SYSCTL_PERIPH_ISP)
			);

	SysCtlIPClockSet(ulPeripheral, 0);
}

//*****************************************************************************
//
//! \brief Resets the device.
//!
//! This function will perform a software reset of the entire device. Processor
//! and all peripherals will be reset and all device registers will return to
//! their default values (with the exception of the reset cause register, which
//! will maintain its current value but have the software reset bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
xSysCtlReset(void)
{
    //
    // Perform a software reset request.  This will cause the device to reset,
    // no further code will be executed.
    //
    xHWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Puts the processor into sleep mode.
//!
//! This function places the processor into sleep mode; it will not return
//! until the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlSleep(void)
{
    //
    // Wait for an interrupt to wake up.
    //
    SysCtlPowerDownEnable(1);
    SysCtlPowerDownWaitCPUSet(1);
    xCPUwfi();
    SysCtlPowerDownEnable(0);
    SysCtlPowerDownWaitCPUSet(0);
}

//*****************************************************************************
//
//! \brief Puts the processor into deep-sleep mode.
//!
//! This function places the processor into deep-sleep mode; it will not return
//! until the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDeepSleep(void)
{
    //
    // Enable deep-sleep.
    //
    xHWREG(NVIC_SYS_CTRL) |= NVIC_SYS_CTRL_SLEEPDEEP;
    SysCtlPowerDownEnable(1);
    SysCtlPowerDownWaitCPUSet(1);

    //
    // Wait for an interrupt.
    //
    xCPUwfi();

    //
    // Disable deep-sleep so that a future sleep will work correctly.
    //
    xHWREG(NVIC_SYS_CTRL) &= ~(NVIC_SYS_CTRL_SLEEPDEEP);
    SysCtlPowerDownEnable(0);
    SysCtlPowerDownWaitCPUSet(0);
}

//*****************************************************************************
//
//! \brief The function is used to Unlock protected registers
//!
//! \param None.
//!
//! The function is used to Unlock protected registers
//!
//! \return Returns \b true if the protected registers is unlocked and \b false
//! if it is not.
//
//*****************************************************************************
xtBoolean
SysCtlKeyAddrUnlock(void)
{
    //
    // Unlock the protected registers.
    //
    xHWREG(GCR_REGLOCK) = 0x59;
    xHWREG(GCR_REGLOCK) = 0x16;
    xHWREG(GCR_REGLOCK) = 0x88;

    return xHWREG(GCR_REGLOCK)&0x01;
}

//*****************************************************************************
//
//! \brief The function is used to lock protected registers
//!
//! \param None.
//!
//! The function is used to lock protected registers
//!
//! \return Returns \b true if the protected registers is unlocked and \b false
//! if it is not.
//
//*****************************************************************************
xtBoolean
SysCtlKeyAddrLock(void)
{
    //
    // Lock the protected registers.
    //
    xHWREG(GCR_REGLOCK) = 0x00;

    return xHWREG(GCR_REGLOCK)&0x01;
}

//*****************************************************************************
//
//! \brief The function is used to reset the peripheral.
//!
//! \param ulPeriphID is the peripheral to be reset.
//! \b SYSCTL_PERIPH_WDG, \b SYSCTL_PERIPH_RTC, \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_DPWM, \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_BIQALC,
//! \b SYSCTL_PERIPH_CRC, \b SYSCTL_PERIPH_PWM01,\b SYSCTL_PERIPH_ACMP,
//! \b SYSCTL_PERIPH_SBRAM, \b SYSCTL_PERIPH_ADC,\b SYSCTL_PERIPH_I2S,
//! \b SYSCTL_PERIPH_ANA, \b SYSCTL_PERIPH_PDMA,\b SYSCTL_PERIPH_ISP
//!
//! \return None.
//
//*****************************************************************************
void SysCtlIPReset(unsigned long ulPeriphID)
{

    xASSERT((ulPeriphClkID == SYSCTL_PERIPH_TMR0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_TMR1) ||
            (ulPeriphClkID == SYSCTL_PERIPH_I2C0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_SPI0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_DPWM) ||
            (ulPeriphClkID == SYSCTL_PERIPH_UART0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_CRC) ||
            (ulPeriphClkID == SYSCTL_PERIPH_PWM01) ||
            (ulPeriphClkID == SYSCTL_PERIPH_ACMP) ||
            (ulPeriphClkID == SYSCTL_PERIPH_ADC) ||
            (ulPeriphClkID == SYSCTL_PERIPH_I2S) ||
            (ulPeriphClkID == SYSCTL_PERIPH_ANA) ||
            (ulPeriphClkID == SYSCTL_PERIPH_PDMA));

    if(ulPeriphID == SYSCTL_PERIPH_PDMA)
    {
        //
        // Set the reset bit
        //
        xHWREG(GCR_IPRSTC1) |= GCR_IPRSTC1_PDMA;

        xSysCtlDelay(100);

        //
        // Clear the reset bit
        //
        xHWREG(GCR_IPRSTC1) &= ~GCR_IPRSTC1_PDMA;
    }
    else
    {
        //
        // Set the reset bit
        //
    	xHWREG(GCR_IPRSTC2) |= ulPeriphID;

        xSysCtlDelay(100);

    	//
    	// Clear the reset bit
    	//
        xHWREG(GCR_IPRSTC2) &= ~ulPeriphID;
    }
}

//*****************************************************************************
//
//! \brief The function is used to Reset CPU
//!
//! \param None.
//!
//! The function is used to Reset CPU
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlCPUReset(void)
{
    SysCtlKeyAddrUnlock();
    xHWREG(GCR_IPRSTC1) |= GCR_IPRSTC1_CPU;
    SysCtlKeyAddrLock();
}


//*****************************************************************************
//
//! \brief The function is used to Reset chip
//!
//! \param None.
//!
//! The function is used to Reset chip
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlChipReset(void)
{
    SysCtlKeyAddrUnlock();
    xHWREG(GCR_IPRSTC1) |= GCR_IPRSTC1_CHIP;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to adjust the AU9110 master oscillator frequency.
//!
//! \param ulAdj is RC adjustment value
//!
//! \return None.
//
//*****************************************************************************
void SysCtlRCAdjValueSet(unsigned long ulAdj)
{
	unsigned long ulRegData;

	if((xHWREG(SYSCLK_CLKSEL0) & 0X01) == 0) // OSCTRIM[0] is active
	{
		ulRegData = xHWREG(GCR_OSCTRIM);
		ulRegData &= ~GCR_OSCTRIM_OSCTRIM0TRIM_M;
		ulRegData |= (ulAdj & 0x000000FF);
		xHWREG(GCR_OSCTRIM) = ulRegData;
	}
	else // OSCTRIM[1] is active
	{
		ulRegData = xHWREG(GCR_OSCTRIM);
		ulRegData &= ~GCR_OSCTRIM_OSCTRIM1TRIM_M;
		ulRegData |= (ulAdj & 0x00FF0000);
		xHWREG(GCR_OSCTRIM) = ulRegData;
	}

}

//*****************************************************************************
//
//! \brief The function is used to get external clock frequency.
//!
//! \return The external clock frequency. The unit is KHz.
//
//*****************************************************************************
unsigned long SysCtlEXTClockGet(void)
{
    return s_ulExtClockkHz;

}

//*****************************************************************************
//
//! \brief The function is used to Get reset source from last operation
//!
//! \param None.
//!
//! The function is used to Get reset source from last operation
//!
//! \return Reset source enumerated as a bit field of
//! \b SYSCTL_RSTSRC_CORE, \b SYSCTL_RSTSRC_WDG, \b SYSCTL_RSTSRC_SYS,
//! \b SYSCTL_RSTSRC_PMU, \b SYSCTL_RSTSRC_CPU.
//
//*****************************************************************************
unsigned long
SysCtlResetSrcGet(void)
{
    //
    // Get reset source from last operation.
    //
    return xHWREG(GCR_RSTSRC);
}

//*****************************************************************************
//
//! \brief The function is used to Clear reset source by write 1
//!
//! \param ulSrc The corresponding bit of reset source.
//!
//! The function is used to Get reset source from last operation
//!
//! The \e ulSrc parameter must be only one of the following values:
//! \b SYSCTL_RSTSRC_CORE, \b SYSCTL_RSTSRC_WDG, \b SYSCTL_RSTSRC_SYS,
//! \b SYSCTL_RSTSRC_PMU, \b SYSCTL_RSTSRC_CPU.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlResetSrcClear(unsigned long ulSrc)
{
    //
    // Check the arguments.
    //
    xASSERT((ulSrc == SYSCTL_RSTSRC_POR) ||
            (ulSrc == SYSCTL_RSTSRC_PAD) ||
            (ulSrc == SYSCTL_RSTSRC_WDG) ||
            (ulSrc == SYSCTL_RSTSRC_LVR) ||
            (ulSrc == SYSCTL_RSTSRC_BOD) ||
            (ulSrc == SYSCTL_RSTSRC_SYS) ||
            (ulSrc == SYSCTL_RSTSRC_CPU));
    //
    // Clear reset source from last operation.
    //

    xHWREG(GCR_RSTSRC) |= ulSrc;
}


//*****************************************************************************
//
//! \brief The function is used to set the peripheral clock.
//!
//! \param[in] ulPeriphClkID is the peripheral clock to be set.
//! \b SYSCTL_PERIPH_WDG, \b SYSCTL_PERIPH_RTC, \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_DPWM, \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_BIQALC,
//! \b SYSCTL_PERIPH_CRC, \b SYSCTL_PERIPH_PWM01,\b SYSCTL_PERIPH_ACMP,
//! \b SYSCTL_PERIPH_SBRAM, \b SYSCTL_PERIPH_ADC,\b SYSCTL_PERIPH_I2S,
//! \b SYSCTL_PERIPH_ANA, \b SYSCTL_PERIPH_PDMA,\b SYSCTL_PERIPH_ISP
//!
//! \param[in] ulEnable, 1: Enable,  0:Disable.
//!
//! \return None.
//
//*****************************************************************************
void SysCtlIPClockSet(unsigned long ulPeriphClkID, unsigned long ulEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulPeriphClkID == SYSCTL_PERIPH_WDG) ||
            (ulPeriphClkID == SYSCTL_PERIPH_RTC) ||
            (ulPeriphClkID == SYSCTL_PERIPH_TMR0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_TMR1) ||
            (ulPeriphClkID == SYSCTL_PERIPH_I2C0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_SPI0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_DPWM) ||
            (ulPeriphClkID == SYSCTL_PERIPH_UART0) ||
            (ulPeriphClkID == SYSCTL_PERIPH_BIQALC) ||
            (ulPeriphClkID == SYSCTL_PERIPH_CRC) ||
            (ulPeriphClkID == SYSCTL_PERIPH_PWM01) ||
            (ulPeriphClkID == SYSCTL_PERIPH_ACMP) ||
            (ulPeriphClkID == SYSCTL_PERIPH_SBRAM) ||
            (ulPeriphClkID == SYSCTL_PERIPH_ADC) ||
            (ulPeriphClkID == SYSCTL_PERIPH_I2S) ||
            (ulPeriphClkID == SYSCTL_PERIPH_ANA) ||
            (ulPeriphClkID == SYSCTL_PERIPH_PDMA) ||
            (ulPeriphClkID == SYSCTL_PERIPH_ISP));

    xASSERT((ulEnable == 0) ||
    		(ulEnable == 1));

    if (ulPeriphClkID == SYSCTL_PERIPH_ISP)
    {
        if (ulEnable == 1)
        {
            xHWREG(SYSCLK_AHBCLK) |= SYSCLK_AHBCLK_ISP_EN;
		}
        else
        {
        	xHWREG(SYSCLK_AHBCLK) &= ~SYSCLK_AHBCLK_ISP_EN;
		}
	}
    else if(ulPeriphClkID == SYSCTL_PERIPH_PDMA)
    {
        if (ulEnable == 1)
        {
            xHWREG(SYSCLK_AHBCLK) |= SYSCLK_AHBCLK_PDMA_EN;
		}
        else
        {
        	xHWREG(SYSCLK_AHBCLK) &= ~SYSCLK_AHBCLK_PDMA_EN;
		}
    }
    else
    {
        if (ulEnable == 1)
        {
            xHWREG(SYSCLK_APBCLK) |= ulPeriphClkID;
		}
        else
        {
        	xHWREG(SYSCLK_APBCLK) &= ~ulPeriphClkID;
		}
    }
}

//*****************************************************************************
//
//! \brief The function is used to set the peripheral in sleep mode.
//!
//! \param[in] ulPeriphClkID is the peripheral clock to be set.
//! \b SYSCTL_PERIPH_WDG, \b SYSCTL_PERIPH_RTC, \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_DPWM, \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_BIQALC,
//! \b SYSCTL_PERIPH_CRC, \b SYSCTL_PERIPH_PWM01,\b SYSCTL_PERIPH_ACMP,
//! \b SYSCTL_PERIPH_SBRAM, \b SYSCTL_PERIPH_ADC,\b SYSCTL_PERIPH_I2S,
//! \b SYSCTL_PERIPH_ANA, \b SYSCTL_PERIPH_PDMA, \b SYSCTL_PERIPH_PDMA,
//! \b SYSCTL_PERIPH_ISP
//!
//! \param[in] ulEnable, 1: Enable,  0:Disable.
//! \return None.
//
//*****************************************************************************
void SysCtlIPSleepClockSet(unsigned long ulPeriphSlpClkID, unsigned long ulEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulPeriphSlpClkID == SYSCTL_PERIPH_WDG) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_RTC) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_TMR0) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_TMR1) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_I2C0) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_SPI0) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_DPWM) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_UART0) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_BIQALC) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_CRC) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_PWM01) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_ACMP) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_SBRAM) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_ADC) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_I2S) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_ANA) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_CPU) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_PDMA) ||
            (ulPeriphSlpClkID == SYSCTL_PERIPH_ISP));

    xASSERT((ulEnable == 0) ||
    		(ulEnable == 1));

    if(ulEnable == 1)
    {
        if (ulPeriphSlpClkID & 0x80000000)
        {
            xHWREG(SYSCLK_CLKSLEEP) |= (ulPeriphSlpClkID & 0x7FFFFFFF);
		}
        else
        {
           xHWREG(SYSCLK_CLKSLEEP) |= ulPeriphSlpClkID;
		}
    }
    else
    {
        if (ulPeriphSlpClkID & 0x80000000)
        {
            xHWREG(SYSCLK_CLKSLEEP) &= ~(ulPeriphSlpClkID & 0x7FFFFFFF);
		}
        else
        {
           xHWREG(SYSCLK_CLKSLEEP) &= ~ulPeriphSlpClkID;
		}
	}
}

//*****************************************************************************
//
//! \brief The function is used to set HCLK clock source.
//!
//! \param[in] ulPeriphClkID it can be selceted from those values:
//! \b SYSCTL_HLCK_S_INT48M, \b SYSCTL_HLCK_S_EXT32K, \b SYSCTL_HLCK_S_INT16K
//!
//! \return None.
//
//*****************************************************************************
void SysCtlHCLKSourceSet(unsigned long ulHclkSrcSel)
{
    unsigned long ulRegValue;

	xASSERT((ulEnable == SYSCTL_HLCK_S_INT48M) ||
    		(ulEnable == SYSCTL_HLCK_S_EXT32K) ||
    		(ulEnable == SYSCTL_HLCK_S_INT16K));

    SysCtlKeyAddrUnlock();

    ulRegValue = xHWREG(SYSCLK_CLKSEL0);
    ulRegValue &= ~SYSCLK_CLKSEL0_HCLK_S_M;
    ulRegValue |= ulHclkSrcSel;
    xHWREG(SYSCLK_CLKSEL0) = ulRegValue;

    SysCtlKeyAddrLock();

}

//*****************************************************************************
//
//! \brief Set a SysTick clock source.
//!
//! \param ulHclkSrcSel is the SysTick clock source to set.
//!
//! The function is used to select SysTick clock source
//!
//! The \e ulHclkSrcSel parameter must be only one of the following values:
//! \b SYSCTL_STCLK_S_EXT12M, \b SYSCTL_STCLK_S_EXT32K, \b SYSCTL_STCLK_S_EXT16K_2,
//! \b SYSCTL_STCLK_S_OSC49M_2, \b SYSCTL_STCLK_S_INT22M_2.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlSysTickSourceSet(unsigned long ulHclkSrcSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulHclkSrcSel==SYSCTL_STCLK_S_EXT12M)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_EXT32K)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_EXT16K_2)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_OSC49M_2)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_INT22M_2)
           );

    //
    // Enable SysTickclock source.
    //
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_CLKSEL0) &=~SYSCLK_CLKSEL0_STCLK_S_M;
    xHWREG(SYSCLK_CLKSEL0) |=ulHclkSrcSel;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Peripheral clock source select.
//!
//! \param ulPeriphClkSrcID is the peripheral.
//! \b SYSCTL_PERIPH_WDG, \b SYSCTL_PERIPH_DPWM, \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_PWM01, \b SYSCTL_PERIPH_I2S
//!
//! \param ucClkSrcSel is the corresponding clock source.
//!
//! \return None.
//
//*****************************************************************************
void SysCtlIpClockSourceSet(unsigned long ulPeriphClkSrcID, unsigned char ucClkSrcSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulHclkSrcSel==SYSCTL_PERIPH_WDG)||
            (ulHclkSrcSel==SYSCTL_PERIPH_DPWM)||
            (ulHclkSrcSel==SYSCTL_PERIPH_TMR0)||
            (ulHclkSrcSel==SYSCTL_PERIPH_TMR1)||
            (ulHclkSrcSel==SYSCTL_PERIPH_PWM01)||
            (ulHclkSrcSel==SYSCTL_PERIPH_I2S)
           );

    switch (ulPeriphClkSrcID)
    {
        case valSYSCTL_PERIPH_WDG:
            xHWREG(SYSCLK_CLKSEL1) &= ~SYSCLK_CLKSEL1_WDG_S_M;
            xHWREG(SYSCLK_CLKSEL1) |= (ucClkSrcSel << SYSCLK_CLKSEL1_WDG_S_S);
			break;

        case SYSCTL_PERIPH_DPWM:
            xHWREG(SYSCLK_CLKSEL1) &= ~SYSCLK_CLKSEL1_DPWM_S_2OSC48M;
            xHWREG(SYSCLK_CLKSEL1) |= (4 << SYSCLK_CLKSEL1_WDG_S_S);
            break;

        case SYSCTL_PERIPH_TMR0:
            xHWREG(SYSCLK_CLKSEL1) &= ~SYSCLK_CLKSEL1_TMR0_S_M;
            xHWREG(SYSCLK_CLKSEL1) |= (ucClkSrcSel << SYSCLK_CLKSEL1_TMR0_S_S);
			break;

        case SYSCTL_PERIPH_TMR1:
            xHWREG(SYSCLK_CLKSEL1) &= ~SYSCLK_CLKSEL1_TMR1_S_M;
            xHWREG(SYSCLK_CLKSEL1) |= (ucClkSrcSel << SYSCLK_CLKSEL1_TMR1_S_S);
            break;

        case SYSCTL_PERIPH_PWM01:
            xHWREG(SYSCLK_CLKSEL1) &= ~SYSCLK_CLKSEL1_PWM01_S_M;
            xHWREG(SYSCLK_CLKSEL1) |= (ucClkSrcSel << SYSCLK_CLKSEL1_PWM01_S_S);

			break;
        case SYSCTL_PERIPH_I2S:
            xHWREG(SYSCLK_CLKSEL2) &= ~SYSCLK_CLKSEL2_I2S_S_M;
            xHWREG(SYSCLK_CLKSEL2) |= (ucClkSrcSel << SYSCLK_CLKSEL2_I2S_S_S);

            break;

		default:
			break;
	}

}

//*****************************************************************************
//
//! \brief This function is used to set IP divider number from the corresponding
//! clock source.
//!
//! \param ulConfig is the required configuration of the IP divider.
//! \b SYSCTL_CLK_ADC_D, \b SYSCTL_CLK_UART_D, \b SYSCTL_CLK_HCLK_D
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIPClockDividerSet(unsigned long ulIPDiv, unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT((ulHclkSrcSel==SYSCTL_PERIPH_ADC_D)||
            (ulHclkSrcSel==SYSCTL_PERIPH_UART_D)||
            (ulHclkSrcSel==SYSCTL_PERIPH_HCLK_D));

    //
    // Set  this peripheral clock source
    //
    switch (ulIPDiv)
    {
		case SYSCTL_CLK_ADC_D:
		    xHWREG(SYSCLK_CLKDIV) &= ~SYSCLK_CLKDIV_ADC_N_M;
		    xHWREG(SYSCLK_CLKDIV) |= (ulValue << SYSCLK_CLKDIV_ADC_N_S);

			break;
		case SYSCTL_CLK_UART_D:
		    xHWREG(SYSCLK_CLKDIV) &= ~SYSCLK_CLKDIV_UART_N_M;
		    xHWREG(SYSCLK_CLKDIV) |= (ulValue << SYSCLK_CLKDIV_UART_N_S);

			break;
		case SYSCTL_CLK_HCLK_D:
		    xHWREG(SYSCLK_CLKDIV) &= ~SYSCLK_CLKDIV_HCLK_N_M;
		    xHWREG(SYSCLK_CLKDIV) |= (ulValue << SYSCLK_CLKDIV_HCLK_N_S);

			break;

		default:
			break;
	}
}

//*****************************************************************************
//
//! \brief OSC/Crystal enable set.
//!
//! \param ulOSCCTRL can be select from these value:
//! \b SYSCTL_OSC_XTAL32K_EN, \b SYSCTL_OSC_49M_EN, \b SYSCTL_OSC_16K_EN
//!
//! \param ulEnable  1:Enable, 0:Disable
//!
//! \return None.
//
//*****************************************************************************
void SysCtlOscCtrlSet(unsigned long ulOSCCTRL, unsigned long ulEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulOSCCTRL == SYSCTL_OSC_XTAL32K_EN)||
            (ulOSCCTRL == SYSCTL_OSC_49M_EN)||
            (ulOSCCTRL == SYSCTL_OSC_16K_D));
    xASSERT((ulEnable == 1)||
            (ulEnable == 0));

    SysCtlKeyAddrUnlock();
    if (1 == ulEnable)
    {
        xHWREG(SYSCLK_PWRCON) |= ulOSCCTRL;
	}
    else
    {
        xHWREG(SYSCLK_PWRCON) &= ~ulOSCCTRL;
	}
    SysCtlKeyAddrLock();

}



