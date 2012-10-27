//*****************************************************************************
//
//! \file xsysctl.c
//! \brief Driver for the system controller
//! \version V2.2.1.0
//! \date 8/7/2012
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
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xhw_adc.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xcore.h"



static unsigned long s_ulExtClockMHz = 8;

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral number for enable.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_E(a)(((a) >> 14) & 0x3)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral number for 
// enable.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_E(a) (((a) & 0xff) << (((a) & 0x1f00) >> 8))

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the SYSCLK_AHBCLK register that
// controls the run-mode enable for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulAXBCLKRegs[] =
{
    SIM_SCGC4,
    SIM_SCGC5,
    SIM_SCGC6,
    SIM_SCGC7
};

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
}
tPeripheralTable;

//*****************************************************************************
//
// An array that maps the peripheral base and peripheral ID and interrupt number
// together to enablea peripheral or peripheral interrupt by a peripheral base.
//
//*****************************************************************************
static const tPeripheralTable g_pPeripherals[] =
{
    {xGPIO_PORTA_BASE, xSYSCTL_PERIPH_GPIOA, INT_PORTA},
    {xGPIO_PORTD_BASE, xSYSCTL_PERIPH_GPIOD, INT_PORTD},
    {xUART0_BASE,      xSYSCTL_PERIPH_UART0, INT_UART0SE},
    {xUART1_BASE,      xSYSCTL_PERIPH_UART1, INT_UART1SE},
    {xUART2_BASE,      xSYSCTL_PERIPH_UART2, INT_UART2SE},
    {xTIMER0_BASE,     xSYSCTL_PERIPH_TIMER0, INT_FTM0},
    {xTIMER1_BASE,     xSYSCTL_PERIPH_TIMER1, INT_FTM1},
    {xTIMER2_BASE,     xSYSCTL_PERIPH_TIMER2, INT_FTM2},
    {xSPI0_BASE,       xSYSCTL_PERIPH_SPI0, INT_SPI0},
    {xSPI1_BASE,       xSYSCTL_PERIPH_SPI1, INT_SPI1},
    {xI2C0_BASE,       xSYSCTL_PERIPH_I2C0, INT_I2C0},
    {xI2C1_BASE,       xSYSCTL_PERIPH_I2C1, INT_I2C1},
    {xADC0_BASE,       xSYSCTL_PERIPH_ADC0, INT_ADC},
    {xACMP0_BASE,      xSYSCTL_PERIPH_ACMP0, INT_ACMP},
    {xPWMA_BASE,       xSYSCTL_PERIPH_PWMA, xINT_PWMA},
    {xPWMB_BASE,       xSYSCTL_PERIPH_PWMB, xINT_PWMB},
    {xPWMC_BASE,       xSYSCTL_PERIPH_PWMC, xINT_PWMC},
    {0,                0,                   0},
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
SysCtlDelay(unsigned long ulCount)
{
    __asm("    sub     r0, #1\n"
          "    bne     SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(ewarm) || defined(__ICCARM__)
void
SysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__CC_ARM)
__asm void
SysCtlDelay(unsigned long ulCount)
{
    subs    r0, #1;
    bne     SysCtlDelay;
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
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
SysCtlPeripheralValid(unsigned long ulPeripheral)
{
    return((ulPeripheral == SYSCTL_PERIPH_DMA) ||
           (ulPeripheral == SYSCTL_PERIPH_RTC) ||
           (ulPeripheral == SYSCTL_PERIPH_TSI) ||
           (ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_PIT) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR0) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR1) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR2) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI1) ||
           (ulPeripheral == SYSCTL_PERIPH_DAC)  ||
           (ulPeripheral == SYSCTL_PERIPH_PWMA) ||
           (ulPeripheral == SYSCTL_PERIPH_PWMB) ||
           (ulPeripheral == SYSCTL_PERIPH_PWMC) ||
           (ulPeripheral == SYSCTL_PERIPH_USB)  ||
           (ulPeripheral == SYSCTL_PERIPH_ACMP) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_LPTMR) ||
           (ulPeripheral == SYSCTL_PERIPH_DMAMUX));
}
#endif

//*****************************************************************************
//
//! \brief Sets the clock of the device.
//!
//! \param ulSysClk is the clock rate you will set.
//! \param ulConfig is the required configuration of the device clock.
//!
//! This function configures the clock of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \ref xSYSCTL_XTAL_3MHZ, \ref xSYSCTL_XTAL_4MHZ, \ref xSYSCTL_XTAL_5MHZ,
//! \ref xSYSCTL_XTAL_32MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref xSYSCTL_OSC_MAIN, \ref xSYSCTL_OSC_INTSL.
//!
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device will be prevented by the hardware.
//! <br />
//! Details please refer to \ref xSysCtl_Clock_Set_Config.
//!
//! \note The ulSysClk should be between 31250 and 39063 Hz
//! if the ulConfig is xSYSCTL_OSC_INTSL.
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig)
{
    unsigned long ulOscFreq, ulSysDiv, i, ulTemp;
    
    unsigned char ucTempReg = 0;
    xASSERT((ulSysClk > 0 && ulSysClk <= 48000000));
    //
    // Calc oscillator freq
    //
    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);
    ulSysDiv = 0;
    ulOscFreq = s_ulExtClockMHz*1000000;

    switch(ulConfig & SYSCTL_OSCSRC_M)
    {
        case xSYSCTL_OSC_MAIN:
        {
            xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
            xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV4_M;
            xHWREG(SIM_CLKDIV1) |= SIM_CLKDIV1_OUTDIV4_2;

            if(!((((xHWREGB(MCG_S) & MCG_S_CLKST_M) >> MCG_S_CLKST_S) == 0x0) &&
              (xHWREGB(MCG_S) & MCG_S_IREFST) &&
              (!(xHWREGB(MCG_S) & MCG_S_PLLST))))                                
            {
            }
           
            ucTempReg = xHWREGB(MCG_C2);
            ucTempReg &= ~(MCG_C2_RANGE0_M | MCG_C2_HGO0 | MCG_C2_EREFS0);
            ucTempReg |= (MCG_C2_RANGE0_HIGH | MCG_C2_EREFS0); 
            xHWREGB(MCG_C2) = ucTempReg;

            ucTempReg = xHWREGB(MCG_C1);
            ucTempReg &= ~(MCG_C1_SRC_MCGOUTCLK_M | MCG_C1_FRDIV_M | MCG_C1_IREFS);
            ucTempReg |= (MCG_C1_SRC_MCGOUTCLK_EXTERAL | MCG_C1_FRDIV_256); 
            xHWREGB(MCG_C1) = ucTempReg;

            for (i = 0 ; i < 20000 ; i++)
            {
                if(xHWREGB(MCG_S) & MCG_S_OSCINIT0)
                {
                    //
                    // jump out early if OSCINIT sets before loop finishes
                    //
                    break;
                }
            }
            //
            // wait for Reference clock Status bit to clear
            //
            for (i = 0 ; i < 20000 ; i++)
            {
                if(xHWREGB(MCG_S) & MCG_S_IREFST)
                {
                    //
                    // jump out early if OSCINIT sets before loop finishes
                    //
                    break; 
                }
            }

            //
            // Wait for clock status bits to show clock source is ext ref clk
            //
            for (i = 0 ; i < 20000 ; i++)
            {
                if((xHWREGB(MCG_S) & MCG_S_CLKST_M)==MCG_S_CLKST_EXT)
                {
                    //
                    // jump out early if CLKST shows EXT CLK slected before loop finishes
                    //
                    break;
                }
            }

            xHWREGB(MCG_C6) |= MCG_C6_CME0;

            ucTempReg = xHWREGB(MCG_C5);
            ucTempReg &= ~(MCG_C5_PRDIV0_M);
            ulTemp = ulSysClk/1000000;
            ulSysDiv = 192/ulTemp;
            if(ulSysDiv >= 24)
            {
                ulSysDiv = 24;
            }
            ucTempReg |= (ulSysDiv-1); 
            xHWREGB(MCG_C5) = ucTempReg;

            ucTempReg = xHWREGB(MCG_C6);
            ucTempReg &= ~(MCG_C6_VDIV0_M);
            ucTempReg |= (MCG_C6_PLLS | MCG_C6_VDIV0_24); 
            xHWREGB(MCG_C6) = ucTempReg;
            
            //
            // wait for PLLST status bit to set
            //
            for(i = 0 ; i < 2000 ; i++)
            {
                if(xHWREGB(MCG_S) & MCG_S_PLLST)
                {
                    //
                    // jump out early if PLLST sets before loop finishes
                    //
                    break; 
                }
            }
            //
            // Wait for LOCK bit to set
            //
            for (i = 0 ; i < 4000 ; i++)
            {
                if(xHWREGB(MCG_S)&MCG_S_LOCK0)
                {
                    //
                    // jump out early if LOCK sets before loop finishes
                    //
                    break;
                }
            }

            SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);

            //
            // Wait for clock status bits to update
            //
            for (i = 0 ; i < 2000 ; i++)
            {
                if((xHWREGB(MCG_S) & MCG_S_CLKST_PLL) == MCG_S_CLKST_PLL)
                {
                    break; // jump out early if CLKST = 3 before loop finishes            
                }

            }
            //
            // set PLLFLLSEL to select the PLL for this clock source
            //
            xHWREG(SIM_SOPT2) |= SIM_SOPT2_PLLFLLSEL;

            if (ulSysClk < ulOscFreq)
            {
                //
                // Calc the SysDiv
                //    
                xASSERT(ulSysClk <= ulOscFreq);
            
                for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
                {
                    if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
                    {
                        break;
                    }
                }
                xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
                xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV1_S);
            }
            break;
        }
        case xSYSCTL_OSC_INTSL:
        {
            if(!((((xHWREGB(MCG_S) & MCG_S_CLKST_M) >> MCG_S_CLKST_S) == 0x0) &&
              (xHWREGB(MCG_S) & MCG_S_IREFST) &&
              (!(xHWREGB(MCG_S) & MCG_S_PLLST))))                                
            {
            }
            xHWREGB(MCG_C2) &= ~MCG_C2_IRCS;
            //
            // Change the CLKS mux to select the IRC as the MCGOUT
            //
            ucTempReg = xHWREGB(MCG_C1);
            ucTempReg &= ~MCG_C1_SRC_MCGOUTCLK_M;
            //
            // select IRC as the MCG clock sourse
            //
            ucTempReg |= MCG_C1_SRC_MCGOUTCLK_INTERAL;
            xHWREGB(MCG_C1) = ucTempReg;
            //
            // wait until internal reference switches to requested irc.
            //
            for (i = 0 ; i < 2000 ; i++)
            {
                if((xHWREGB(MCG_S) & MCG_S_IRCST) != MCG_S_IRCST)
                {
                    break;
                }

            }
            //
            // Wait for clock status bits to update
            //
            for (i = 0 ; i < 2000 ; i++)
            {
                if((xHWREGB(MCG_S) & MCG_S_CLKST_INT) == MCG_S_CLKST_INT)
                {
                    break;            
                }

            }
            break;
        }
        default:
        {
            xASSERT(0);
            break;
        }       
    }
}
        
//*****************************************************************************
//
//! \brief Enables a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \return None.
//
//*****************************************************************************
void 
xSysCtlPeripheralEnable2(unsigned long ulPeripheralBase)
{
    unsigned long i;
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralEnable(g_pPeripherals[i].ulPeripheralID);
            break;
        }
    }
}
        
//*****************************************************************************
//
//! \brief Disables a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are disabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
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
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralDisable(g_pPeripherals[i].ulPeripheralID);
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
//! \ref xGPIOSPinToPort function, and then use this function to enable the GPIO
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
xSysCtlPeripheraIntNumGet(unsigned long ulPeripheralBase)
{
    unsigned long i;
    
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralBase == xGPIO_PORTA_BASE)||
            (ulPeripheralBase == xGPIO_PORTD_BASE)||
            (ulPeripheralBase == xUART0_BASE)||   
            (ulPeripheralBase == xUART1_BASE)||   
            (ulPeripheralBase == xUART2_BASE)||   
            (ulPeripheralBase == xTIMER0_BASE)||    
            (ulPeripheralBase == xTIMER1_BASE)||          
            (ulPeripheralBase == xTIMER2_BASE)||    
            (ulPeripheralBase == xSPI0_BASE)||     
            (ulPeripheralBase == xSPI1_BASE)||         
            (ulPeripheralBase == xSPI2_BASE)||           
            (ulPeripheralBase == xSPI3_BASE)||   
            (ulPeripheralBase == xI2C0_BASE)||  
            (ulPeripheralBase == xI2C1_BASE)||
            (ulPeripheralBase == xADC0_BASE)||    
            (ulPeripheralBase == xACMP0_BASE)||       
            (ulPeripheralBase == xPWMA_BASE)||
            (ulPeripheralBase == xPWMB_BASE)||       
            (ulPeripheralBase == xPWMC_BASE)       
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
//! \brief Set a peripheral clock source and peripheral divide.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//! \param ulDivide is the peripheral clock divide to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \ref xSysCtl_Peripheral_Src_Clk.
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc,
                                unsigned long ulDivide)
{
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralSrc==xSYSCTL_WDT0_INTSL)||
            (ulPeripheralSrc==xSYSCTL_ADC0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_WDT0_HCLK_2)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_HCLK)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_INT)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_MAIN)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_HCLK)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_INT)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_MAIN)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_HCLK)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_INT)||
            (ulPeripheralSrc==xSYSCTL_UART0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_UART0_PLL)||
            (ulPeripheralSrc==xSYSCTL_UART0_INT)||
            (ulPeripheralSrc==xSYSCTL_PWMA_MAIN)||
            (ulPeripheralSrc==xSYSCTL_PWMA_HCLK)||
            (ulPeripheralSrc==xSYSCTL_PWMA_INT)||
            (ulPeripheralSrc==xSYSCTL_PWMB_MAIN)||
            (ulPeripheralSrc==xSYSCTL_PWMB_HCLK)||
            (ulPeripheralSrc==xSYSCTL_PWMB_INT)||
            (ulPeripheralSrc==xSYSCTL_PWMC_MAIN)||
            (ulPeripheralSrc==xSYSCTL_PWMC_HCLK)||
            (ulPeripheralSrc==xSYSCTL_PWMC_INT));
    xASSERT((ulDivide <= 256) && (ulDivide >= 1));

    //
    // Set the peripheral clock source
    //
    ulDivide = 0;
    if(ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_OSC32KCLK)
    {
        xHWREG(SIM_SOPT1) &= ~SIM_SOPT1_OSC32KSEL_M;
        xHWREG(SIM_SOPT1) |= SIM_SOPT1_OSC32KSEL_OSC32KCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_RTC_CLKIN)
    {
        xHWREG(SIM_SOPT1) &= ~SIM_SOPT1_OSC32KSEL_M;
        xHWREG(SIM_SOPT1) |= SIM_SOPT1_OSC32KSEL_RTC_CLKIN;
    }
    else if(ulPeripheralSrc == xSYSCTL_ADC0_MAIN)
    {
        xHWREG(ADC_BASE + ADC0_CFG1) &= ~ADC0_CFG1_ADICLK_M;
        xHWREG(ADC_BASE + ADC0_CFG1) &= ~ADC0_CFG1_ADIV_M;
        xHWREG(ADC_BASE + ADC0_CFG1) |= ulDivide;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_LPO)
    {
        xHWREG(SIM_SOPT1) &= ~SIM_SOPT1_OSC32KSEL_M;
        xHWREG(SIM_SOPT1) |= SIM_SOPT1_OSC32KSEL_LPO;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGFLLCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_PLLFLLSEL;
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2)
    {
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_PLLFLLSEL;
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_OSCERCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_OSCERCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGIRCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_MCGIRCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGFLLCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_PLLFLLSEL;    	
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGPLLCLK_2)
    {
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_PLLFLLSEL;
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_OSCERCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_OSCERCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGIRCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_MCGIRCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_USB_S_USB_CLKIN)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_USBSRC;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_USB_S_MCGPLLCLK_2)
    {
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_PLLFLLSEL;    	
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_USBSRC;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_USB_S_MCGFLLCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_PLLFLLSEL;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_USBSRC;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_1K)
    {
        xHWREG(SIM_COPC ) &= ~SIM_COPC_COPCLKS;
    }
    else
    {
        xHWREG(SIM_COPC ) |= SIM_COPC_COPCLKS;
    }
}

//*****************************************************************************
//
//! \brief Enables a peripheral.
//!
//! \param ulPeripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_DMA,  \b SYSCTL_PERIPH_DAC,  \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_TMR2, \b SYSCTL_PERIPH_RTC,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_SPI1, \b SYSCTL_PERIPH_PIT,  \b SYSCTL_PERIPH_DMAMUX,
//! \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_UART1,\b SYSCTL_PERIPH_UART2,
//! \b SYSCTL_PERIPH_PWMA, \b SYSCTL_PERIPH_PWMB, \b SYSCTL_PERIPH_PWMC,
//! \b SYSCTL_PERIPH_USB,  \b SYSCTL_PERIPH_ADC,  \b SYSCTL_PERIPH_FLASH,
//! \b SYSCTL_PERIPH_ACMP, \b SYSCTL_PERIPH_GPIOA,\b SYSCTL_PERIPH_GPIOB,
//! \b SYSCTL_PERIPH_GPIOC,\b SYSCTL_PERIPH_GPIOD,\b SYSCTL_PERIPH_GPIOE.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralEnable(unsigned long ulPeripheral)
{
    unsigned long ulReadValue = 0, ulIndex = 0;
    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));
    ulIndex = SYSCTL_PERIPH_INDEX_E(ulPeripheral);
    ulReadValue = SYSCTL_PERIPH_MASK_E(ulPeripheral);
    //
    // Enable this peripheral.
    //
    xHWREG(g_pulAXBCLKRegs[ulIndex]) |= ulReadValue;
}

//*****************************************************************************
//
//! \brief Disable a peripheral.
//!
//! \param ulPeripheral is the peripheral to Disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_DMA,  \b SYSCTL_PERIPH_DAC,  \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_TMR2, \b SYSCTL_PERIPH_RTC,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_SPI1, \b SYSCTL_PERIPH_PIT,  \b SYSCTL_PERIPH_DMAMUX,
//! \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_UART1,\b SYSCTL_PERIPH_UART2,
//! \b SYSCTL_PERIPH_PWMA, \b SYSCTL_PERIPH_PWMB, \b SYSCTL_PERIPH_PWMC,
//! \b SYSCTL_PERIPH_USB,  \b SYSCTL_PERIPH_ADC,  \b SYSCTL_PERIPH_FLASH,
//! \b SYSCTL_PERIPH_ACMP, \b SYSCTL_PERIPH_GPIOA,\b SYSCTL_PERIPH_GPIOB,
//! \b SYSCTL_PERIPH_GPIOC,\b SYSCTL_PERIPH_GPIOD,\b SYSCTL_PERIPH_GPIOE.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDisable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Enable this peripheral.
    //
    xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX_E(ulPeripheral)]) &=
        ~(SYSCTL_PERIPH_MASK_E(ulPeripheral));
}

//*****************************************************************************
//
//! \brief Enables and configures the edge detection for the wakeup pin.
//!
//! \param bEnable is a boolean that is \b true if Enable wakeup pin,
//! \b false if not.
//! \param ulPinIndex is the index of the wakeup pin.
//! \param ulEdge is mode of wakeup pin edge.
//!
//! This function is to Enable and configures the edge detection for the wakeup
//! pin or not.
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlWakeupPinConfig(xtBoolean bEnable, unsigned long ulPinIndex, unsigned long ulEdge)
{
    xASSERT((ulPinIndex >= 0 && ulPinIndex <= 15));
    xASSERT((ulEdge == SYSCTL_WAKEUP_PIN_DIS) ||
            (ulEdge == SYSCTL_WAKEUP_PIN_ANY) ||
            (ulEdge == SYSCTL_WAKEUP_PIN_RISING) ||
            (ulEdge == SYSCTL_WAKEUP_PIN_FALLING));
    //
    // Enable the edge detection for the wakeup pin.
    //
    if(bEnable)
    {
        xHWREGB(LLWU_PE1 + ulPinIndex/4) &= ~(LLWU_PE1_WUPE0_M << ((ulPinIndex%4)*2));
        xHWREGB(LLWU_PE1 + ulPinIndex/4) |= ulEdge << ((ulPinIndex%4)*2);
    }
    else
    {
        xHWREGB(LLWU_PE1 + ulPinIndex/4) &= ~(LLWU_PE1_WUPE0_M << ((ulPinIndex%4)*2));
    }
}

//*****************************************************************************
//
//! \brief Enables and configures the edge detection for the wakeup pin.
//!
//! \param bEnable is a boolean that is \b true if Enable wakeup pin,
//! \b false if not.
//! \param ulPinIndex is the index of the wakeup pin.
//! \param ulEdge is mode of wakeup pin edge.
//!
//! This function is to Enable and configures the edge detection for the wakeup
//! pin or not.
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlWakeupFilterConfig(unsigned long ulFilterIndex, unsigned long ulPinIndex,
                         unsigned long ulEdge)
{
    xASSERT((ulFilterIndex >= 1 && ulFilterIndex <= 2));
    xASSERT((ulPinIndex >= 0 && ulPinIndex <= 15));
    xASSERT((ulEdge == SYSCTL_WAKEUP_FILTER_DIS) ||
            (ulEdge == SYSCTL_WAKEUP_FILTER_ANY) ||
            (ulEdge == SYSCTL_WAKEUP_FILTER_RISING) ||
            (ulEdge == SYSCTL_WAKEUP_FILTER_FALLING));

    //
    // Controls the digital filter options for the external pin detect
    //
    xHWREGB(LLWU_FILT1+ulFilterIndex/2) &= ~LLWU_FILT1_FILTE_M;
    xHWREGB(LLWU_FILT1+ulFilterIndex/2) |= ulEdge;
    
    //
    // Selects 1 out of the 16 wakeup pins to be muxed into the filter.
    //
    xHWREGB(LLWU_FILT1+ulFilterIndex/2) &= ~LLWU_FILT1_FILTSEL_M;
    xHWREGB(LLWU_FILT1+ulFilterIndex/2) |= ulPinIndex;
}

//*****************************************************************************
//
//! \brief Get the wakeup pin flag of the specified index.
//!
//! \param ulPinIndex is the index of the wakeup pin.
//!
//! This function is to Get the wakeup pin flag of the specified index.
//!
//! \return This function return the wakeup source Flag,if it is the wakeup
//!  source, it returns xtrue, xfalse if not.
//
//*****************************************************************************
xtBoolean
SysCtlWakeupPinFlagGet(unsigned long ulPinIndex)
{
    xtBoolean xtFlag = 0;
    xASSERT((ulPinIndex >= 0 && ulPinIndex <= 15));

    xtFlag = (xHWREGB(LLWU_F1+ulPinIndex/8) & (LLWU_F1_WUF0 << ulPinIndex));
    if(xtFlag)
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief Get the wakeup pin Filter flag of the specified index.
//!
//! \param ulFilterIndex is the index of the wakeup pin filter.
//!
//! This function is to Get the wakeup pin filter flag of the specified index.
//!
//! \return This function return the wakeup filter source Flag,if it is the wakeup
//!  source, it returns xtrue, xfalse if not.
//
//*****************************************************************************
xtBoolean
SysCtlWakeupPinFilterFlagGet(unsigned long ulFilterIndex)
{
    xtBoolean xtFlag = 0;
    xASSERT((ulFilterIndex >= 1 && ulFilterIndex <= 2));

    xtFlag = (xHWREGB(LLWU_FILT1+ulFilterIndex/2) & LLWU_FILT1_FILTSEL_FILTF);
    if(xtFlag)
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}
//*****************************************************************************
//
//! \brief Get the wakeup Module flag of the specified index.
//!
//! \param ulModuleIndex is the index of the wakeup Module.
//!
//! This function is to Get the wakeup module flag of the specified index.
//!
//! \return This function return the wakeup source Flag,if it is the wakeup
//!  source, it returns xtrue, xfalse if not.
//
//*****************************************************************************
xtBoolean
SysCtlWakeupModuleFlagGet(unsigned long ulModuleIndex)
{
    xtBoolean xtFlag = 0;
    xASSERT((ulModuleIndex >= 0 && ulModuleIndex <= 7));

    xtFlag = (xHWREGB(LLWU_F3) & (LLWU_F3_MWUF0 << ulModuleIndex));
    if(xtFlag)
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief Enables Wakeup Module or not.
//!
//! \param bEnable is a boolean that is \b true if Enable wakeup pin,
//! \b false if not.
//! \param ulModuleIndex is the index of the wakeup pin.
//!
//! This function is to Enable Wakeup Module or not.
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlWakeupModuleEnable(xtBoolean bEnable, unsigned long ulModuleIndex)
{
    xASSERT((ulModuleIndex >= 0 && ulModuleIndex <= 15));

    //
    // Enable wakeup module.
    //
    if(bEnable)
    {
        xHWREGB(LLWU_ME) &= 0x00;
        xHWREGB(LLWU_ME) |= LLWU_ME_WUME0 << ulModuleIndex;
    }
    else
    {
        xHWREGB(LLWU_ME) &= ~(LLWU_ME_WUME0 << ulModuleIndex);
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
SysCtlSleep(void)
{
    //
    // Clear the SLEEPDEEP bit to make sure we go into WAIT(sleep) mode 
    // instead of deep sleep
    //
    xHWREG(SCB_SCR) &= ~SCB_SCR_SLEEPDEEP;
    //
    // WFI instruction will start entry into STOP mode
    //
    xCPUwfi();
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
    // Set the SLEEPDEEP bit to enable deep sleep mode(STOP).
    //
    xHWREG(SCB_SCR) |= SCB_SCR_SLEEPDEEP;
    
    //
    // WFI instruction will start entry into STOP mode
    //
    xCPUwfi();
}

//*****************************************************************************
//
//! \brief Set a peripheral clock source.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_RTC_S_OSC32KCLK,  \b SYSCTL_PERIPH_RTC_S_RTC_CLKIN, 
//! \b SYSCTL_PERIPH_RTC_S_LPO,        \b SYSCTL_PERIPH_LPTMR_S_OSC32KCLK, 
//! \b SYSCTL_PERIPH_LPTMR_S_RTC_CLKIN,\b SYSCTL_PERIPH_LPTMR_S_LPO, 
//! \b SYSCTL_PERIPH_TPM_S_MCGFLLCLK,  \b SYSCTL_PERIPH_TPM_S_MCGPLLCLK_2, 
//! \b SYSCTL_PERIPH_TPM_S_OSCERCLK,   \b SYSCTL_PERIPH_TPM_S_MCGIRCLK, 
//! \b SYSCTL_PERIPH_UART0_S_MCGFLLCLK,\b SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2,
//! \b SYSCTL_PERIPH_UART0_S_OSCERCLK, \b SYSCTL_PERIPH_UART0_S_MCGIRCLK, 
//! \b SYSCTL_PERIPH_USB_S_USB_CLKIN,  \b SYSCTL_PERIPH_USB_S_MCGPLLCLK_2, 
//! \b SYSCTL_PERIPH_USB_S_MCGFLLCLK,  \b SYSCTL_PERIPH_WDG_S_1K,
//! \b SYSCTL_PERIPH_WDG_S_BUS,        \b SYSCTL_PERIPH_ADC_S_BUSCLK,
//! \b SYSCTL_PERIPH_ADC_S_BUSCLK_2,   \b SYSCTL_PERIPH_ADC_S_ATCLK,
//! \b SYSCTL_PERIPH_ADC_S_ADACK.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc)
{
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_OSC32KCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_RTC_CLKIN) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_LPTMR_S_OSC32KCLK)||
            (ulPeripheralSrc == SYSCTL_PERIPH_LPTMR_S_RTC_CLKIN) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_LPTMR_S_LPO) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_LPO) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_1K) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_BUSCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_BUSCLK_2) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_ATCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_ADACK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGFLLCLK)||
            (ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGPLLCLK_2) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_OSCERCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGIRCLK)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGFLLCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_OSCERCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGIRCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_USB_S_USB_CLKIN) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_USB_S_MCGPLLCLK_2) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_USB_S_MCGFLLCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_BUS));

    //
    // Set this peripheral clock source
    //
    if(ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_OSC32KCLK)
    {
        xHWREG(SIM_SOPT1) &= ~SIM_SOPT1_OSC32KSEL_M;
        xHWREG(SIM_SOPT1) |= SIM_SOPT1_OSC32KSEL_OSC32KCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_RTC_CLKIN)
    {
        xHWREG(SIM_SOPT1) &= ~SIM_SOPT1_OSC32KSEL_M;
        xHWREG(SIM_SOPT1) |= SIM_SOPT1_OSC32KSEL_RTC_CLKIN;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_RTC_S_LPO)
    {
        xHWREG(SIM_SOPT1) &= ~SIM_SOPT1_OSC32KSEL_M;
        xHWREG(SIM_SOPT1) |= SIM_SOPT1_OSC32KSEL_LPO;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_BUSCLK)
    {
        xHWREG(ADC_BASE + ADC0_CFG1) &= ~ADC0_CFG1_ADICLK_M;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_BUSCLK_2)
    {
        xHWREG(ADC_BASE + ADC0_CFG1) &= ~ADC0_CFG1_ADICLK_M;
        xHWREG(ADC_BASE + ADC0_CFG1) |= ADC0_CFG1_ADICLK_BUSCLK_2;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_ATCLK)
    {
        xHWREG(ADC_BASE + ADC0_CFG1) &= ~ADC0_CFG1_ADICLK_M;
        xHWREG(ADC_BASE + ADC0_CFG1) |= ADC0_CFG1_ADICLK_ALTCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_ADACK)
    {
        xHWREG(ADC_BASE + ADC0_CFG1) &= ~ADC0_CFG1_ADICLK_M;
        xHWREG(ADC_BASE + ADC0_CFG1) |= ADC0_CFG1_ADICLK_ADACK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGFLLCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_PLLFLLSEL;    
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2)
    {
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_PLLFLLSEL;    
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_OSCERCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_OSCERCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART0_S_MCGIRCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_UART0SRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_UART0SRC_MCGIRCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGFLLCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_PLLFLLSEL;  
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGPLLCLK_2)
    {
        xHWREG(SIM_SOPT2)|= SIM_SOPT2_PLLFLLSEL;  
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_MCGXLL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_OSCERCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_OSCERCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_TPM_S_MCGIRCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_TPMSRC_M;
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_TPMSRC_MCGIRCLK;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_USB_S_USB_CLKIN)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_USBSRC;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_USB_S_MCGFLLCLK)
    {
        xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_PLLFLLSEL; 
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_USBSRC;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_USB_S_MCGPLLCLK_2)
    {
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_PLLFLLSEL; 
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_USBSRC;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_1K)
    {
        xHWREG(SIM_COPC ) &= ~SIM_COPC_COPCLKS;
    }
    else
    {
        xHWREG(SIM_COPC ) |= SIM_COPC_COPCLKS;
    }
}

//*****************************************************************************
//
//! \brief Set a HCLK clock source.
//!
//! \param ucHclkSrcSel is the HCLK clock source to set.
//!
//! The function is used to select HCLK clock source
//!
//! The \e ucHclkSrcSel parameter must be only one of the following values:
//! \b SYSCTL_HLCK_S_PLL, \b SYSCTL_HLCK_S_INT, \b SYSCTL_HLCK_S_MAIN.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlHClockSourceSet(unsigned char ucHclkSrcSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ucHclkSrcSel==SYSCTL_HLCK_S_MAIN) ||
            (ucHclkSrcSel==SYSCTL_HLCK_S_PLL) ||
            (ucHclkSrcSel==SYSCTL_HLCK_S_INT));

    xHWREGB(MCG_C1) &= ~MCG_C1_SRC_MCGOUTCLK_M;
    xHWREGB(MCG_C1) |= ucHclkSrcSel;
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
//! \b SYSCTL_RSTSRC_POR, \b SYSCTL_RSTSRC_PAD, \b SYSCTL_RSTSRC_WDG,
//! \b SYSCTL_RSTSRC_LOL, \b SYSCTL_RSTSRC_LOC, \b SYSCTL_RSTSRC_LVD, 
//! \b SYSCTL_RSTSRC_WAKEUP, \b SYSCTL_RSTSRC_SACKERR, \b SYSCTL_RSTSRC_MDM_AP
//! \b SYSCTL_RSTSRC_SW, and \b SYSCTL_RSTSRC_LOCKUP.
//
//*****************************************************************************
unsigned long 
SysCtlResetSrcGet(void)
{
    
    unsigned long ulResetSrc = 0;
    //
    // Get reset source from last operation.
    //
    if((xHWREGB(RCM_SRS0)&SYSCTL_RSTSRC_PAD))
    {
        return SYSCTL_RSTSRC_PAD;
    }
    if((xHWREGB(RCM_SRS0)&SYSCTL_RSTSRC_LOC))
    {
        return SYSCTL_RSTSRC_LOC;
    }
    if((xHWREGB(RCM_SRS0)&SYSCTL_RSTSRC_LOL))
    {
        return SYSCTL_RSTSRC_LOL;
    }
    if((xHWREGB(RCM_SRS0)&SYSCTL_RSTSRC_WDG))
    {
        return SYSCTL_RSTSRC_WDG;
    }
    else
    {
        ulResetSrc = xHWREGB(RCM_SRS0);
        ulResetSrc = ulResetSrc | xHWREGB(RCM_SRS1);
        return ulResetSrc;
    }
}

//*****************************************************************************
//
//! \brief The function is used to Get The Current Power Mode
//!
//! \param None.
//!
//! The function is used to The Current Power Mode
//!
//! \return Reset source enumerated as a bit field of
//! \b SYSCTL_POWER_MODE_RUN,  \b SYSCTL_POWER_MODE_STOP, 
//! \b SYSCTL_POWER_MODE_VLPR, \b SYSCTL_POWER_MODE_VLPW,
//! \b SYSCTL_POWER_MODE_VLPS, \b SYSCTL_POWER_MODE_LLS, SYSCTL_POWER_MODE_VLLS
//
//*****************************************************************************
unsigned long 
SysCtlPowerModeGet(void)
{
    //
    // Get The Current Power Mode.
    //
    return (xHWREGB(SMC_PMSTAT)&SMC_PMSTAT_PMSTAT_M);
}
//*****************************************************************************
//
//! \brief The function is to Enable or Disbale Reset Pin Filter Select in Stop Mode 
//!
//! \param bEnable is a boolean that is \b true if Enable Reset Pin Filter Select
//! in Stop Mode, \b false if not.
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlResetPinFilterStopModeEnable(xtBoolean bEnable)
{
    //
    // Enable Reset Pin Filter Select in Stop Mode or not.
    //
    if(bEnable)
    {
        xHWREGB(RCM_RPFC) |= RCM_RPFC_RSTFLTSRW_LPO;
    }
    else
    {
        xHWREGB(RCM_RPFC) &= ~RCM_RPFC_RSTFLTSRW_LPO;
    }
}

//*****************************************************************************
//
//! \brief The function is used to Selects the reset pin bus clock filter width
//!
//! \param ulBusClkWidth the volt will be Select.
//!
//! The function is used to Select Reset Pin Filter in Run and Wait Modes
//!
//! The \e ulFilter parameter must be only one of the following values:1~32. 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlResetPinFilterBusClkWidthSet(unsigned char ulBusClkWidth)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBusClkWidth > 0 && ulBusClkWidth <= 32));

    //
    // Reset Pin Filter Bus Clock Select.
    //
    xHWREGB(RCM_RPFW) &= ~RCM_RPFW_RSTFLTSEL_M;
    xHWREGB(RCM_RPFW) |= ulBusClkWidth;
}

//*****************************************************************************
//
//! \brief The function is used to Select Reset Pin Filter in Run and Wait Modes.
//!
//! \param ulFilter the volt will be Select.
//!
//! The function is used to Select Reset Pin Filter in Run and Wait Modes
//!
//! The \e ulFilter parameter must be only one of the following values:
//! \b SYSCTL_RESET_PIN_FILTER_RUN_DIS, \b SYSCTL_RESET_PIN_FILTER_RUN_BUS, 
//! \b SYSCTL_RESET_PIN_FILTER_RUN_LPO. 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlResetPinFilterRunModeSelect(unsigned long ulFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulFilter == SYSCTL_RESET_PIN_FILTER_RUN_DIS) ||
            (ulFilter == SYSCTL_RESET_PIN_FILTER_RUN_BUS) ||
            (ulFilter == SYSCTL_RESET_PIN_FILTER_RUN_LPO));
    //
    // Reset Pin Filter in Run and Wait Modes.
    //
    xHWREGB(RCM_RPFC) &= ~RCM_RPFC_RSTFLTSRW_M;
    xHWREGB(RCM_RPFC) |= ulFilter;
}

//*****************************************************************************
//
//! \brief The function is used to Select Low-Voltage Detect Voltage.
//!
//! \param ulVoltage the volt will be Select.
//!
//! The function is used to Select Low-Voltage Detect Voltage.
//!
//! The \e ulVoltage parameter must be only one of the following values:
//! \b SYSCTL_LVD_DET_LOW, \b SYSCTL_LVD_DET_HIGH. 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDVolSet(unsigned long ulVoltage)
{
    //
    // Check the arguments.
    //
    xASSERT((ulVoltage == SYSCTL_LVD_DET_LOW) ||
            (ulVoltage == SYSCTL_LVD_DET_HIGH));
    //
    // Select Low-Voltage Detect Voltage.
    //
    xHWREGB(PMC_LVDSC1) &= ~PMC_LVDSC1_LVDV_M;
    xHWREGB(PMC_LVDSC1) |= ulVoltage;
}

//*****************************************************************************
//
//! \brief The function is used to Select Low-Voltage Warning Voltage.
//!
//! \param ulVoltage the volt will be Select.
//!
//! The function is used to Select Low-Voltage Warning Voltage.
//!
//! The \e ulVoltage parameter must be only one of the following values:
//! \b SYSCTL_LVD_WARNING_LOW, \b SYSCTL_LVD_WARNING_MID1,
//! \b SYSCTL_LVD_WARNING_MID2, \b SYSCTL_LVD_WARNING_HIGH.
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDWarningVolSet(unsigned long ulVoltage)
{
    //
    // Check the arguments.
    //
    xASSERT((ulVoltage == SYSCTL_LVD_WARNING_LOW) ||
            (ulVoltage == SYSCTL_LVD_WARNING_MID1) ||
            (ulVoltage == SYSCTL_LVD_WARNING_MID2) ||
            (ulVoltage == SYSCTL_LVD_WARNING_HIGH));
    //
    // Select Low-Voltage Warning Voltage.
    //
    xHWREGB(PMC_LVDSC2) &= ~PMC_LVDSC2_LVWV_M;
    xHWREGB(PMC_LVDSC2) |= ulVoltage;
}

//*****************************************************************************
//
//! \brief Get Low-Voltage Detect Flag.
//!
//! \param None.
//!
//! This function is to Get Low-Voltage Detect Flag
//!
//! \return This function return the LVD Detect Flag,if a low-voltage detect
//! event happens, it returns xtrue, xfalse if not.
//
//*****************************************************************************
xtBoolean
SysCtlLVDEventFlagGet(void)
{
    xtBoolean xtFlag = 0;

    xtFlag = xHWREGB(PMC_LVDSC1) & PMC_LVDSC1_LVDF;
    if(xtFlag)
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief Clear Low-Voltage Detect Flag.
//!
//! \param None.
//!
//! This function is to Clear Low-Voltage Detect Flag
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlLVDEventFlagClear(void)
{
    xHWREGB(PMC_LVDSC1) |= PMC_LVDSC1_LVDACK;
}

//*****************************************************************************
//
//! \brief Get Low-Voltage Warning Flag.
//!
//! \param None.
//!
//! This function is to Get Low-Voltage Warning Flag
//!
//! \return This function return LVD Warning Flag,if a low-voltage Warning
//! event happens, it returns xtrue, xfalse if not.
//
//*****************************************************************************
xtBoolean
SysCtlLVDWaringFlagGet(void)
{
    xtBoolean xtFlag = 0;

    xtFlag = xHWREGB(PMC_LVDSC2) & PMC_LVDSC2_LVWF;
    if(xtFlag)
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief Clear Low-Voltage Warning Flag.
//!
//! \param None.
//!
//! This function is to Clear Low-Voltage Warning Flag
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlLVDWarningFlagClear(void)
{
    xHWREGB(PMC_LVDSC2) |= PMC_LVDSC2_LVWACK;
}

//*****************************************************************************
//
//! \brief The function is to Enter very low power run mode or not
//!
//! \param bEnable is a boolean that is \b true if Enter very low power run mode
//! and \b false if exit very low power run mode to run mode.
//!
//! The function is used to Enter very low power run mode or not
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlVeryLowPowerRunModeEnable(xtBoolean bEnable)
{
    //
    // Enter very low power run mode.
    //
    if(bEnable)
    {
        xHWREGB(SMC_PMPROT) |= SMC_PMPROT_AVLP;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_RUNM_M;
        xHWREGB(SMC_PMCTRL) |= SMC_PMCTRL_RUNM_VLPR;
    }
    //
    // Exit very low power run mode.
    //
    else
    {
        xHWREGB(SMC_PMPROT) &= ~SMC_PMPROT_AVLP;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_RUNM_M;
    }
}

//*****************************************************************************
//
//! \brief The function is to Enable Low-Voltage Detect Interrupt or not
//!
//! \param bEnable is a boolean that is \b true if Enable Low-Voltage Detect 
//!  Interrupt and \b false if not.
//!
//! The function is used to Enable Low-Voltage Detect Interrupt or not
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDIntEnable(xtBoolean bEnable)
{
    //
    // Enable Low-Voltage Detect Interrupt.
    //
    if(bEnable)
    {
        xHWREGB(PMC_LVDSC1) |= PMC_LVDSC1_LVDIE;
    }
    //
    // Disable Low-Voltage Detect Interrupt.
    //
    else
    {
        xHWREGB(PMC_LVDSC1) &= ~PMC_LVDSC1_LVDIE;
    }
}

//*****************************************************************************
//
//! \brief The function is to Enable Low-Voltage Detect Warning Interrupt or not
//!
//! \param bEnable is a boolean that is \b true if Enable Low-Voltage Warning 
//!  Interrupt and \b false if not.
//!
//! The function is used to Enable Low-Voltage Detect Warning Interrupt or not
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDWarningIntEnable(xtBoolean bEnable)
{
    //
    // Enable Low-Voltage Detect Warning Interrupt.
    //
    if(bEnable)
    {
        xHWREGB(PMC_LVDSC2) |= PMC_LVDSC2_LVDRE;
    }
    //
    // Disable Low-Voltage Detect Warning Interrupt.
    //
    else
    {
        xHWREGB(PMC_LVDSC2) &= ~PMC_LVDSC2_LVDRE;
    }
}
//*****************************************************************************
//
//! \brief The function is to Enable Low-Voltage Detect Reset or not
//!
//! \param bEnable is a boolean that is \b true if Enable Low-Voltage Detect 
//!  Reset and \b false if not.
//!
//! The function is used to Enable Low-Voltage Detect Reset or not
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDResetEnable(xtBoolean bEnable)
{
    //
    // Enable Low-Voltage Detect Reset.
    //
    if(bEnable)
    {
        xHWREGB(PMC_LVDSC1) |= PMC_LVDSC1_LVDRE;
    }
    //
    // Disable Low-Voltage Detect Reset.
    //
    else
    {
        xHWREGB(PMC_LVDSC1) &= ~PMC_LVDSC1_LVDRE;
    }
}
//*****************************************************************************
//
//! \brief The function is to Enter the various Stop mode.
//!
//! \param ulStopMode is the Stop mode which will enter.
//!
//! The function is used to Enter the various Stop mode
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlStopModeSet(unsigned long ulStopMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulStopMode == SYSCTL_STOP_MODE_VLPS) ||
            (ulStopMode == SYSCTL_STOP_MODE_LLS)  ||
            (ulStopMode == SYSCTL_STOP_MODE_VLLS0)||
            (ulStopMode == SYSCTL_STOP_MODE_VLLS1)||
            (ulStopMode == SYSCTL_STOP_MODE_VLLS2)||
            (ulStopMode == SYSCTL_STOP_MODE_VLLS3)||
            (ulStopMode == SYSCTL_STOP_MODE_NORMAL));

    //
    // Set the SLEEPDEEP bit to enable deep sleep mode(STOP).
    //
    xHWREG(SCB_SCR) |= SCB_SCR_SLEEPDEEP;
    //
    // Enter the various Stop mode.
    //
    if(ulStopMode == SYSCTL_STOP_MODE_VLPS)
    {
        xHWREGB(SMC_PMPROT) |= SMC_PMPROT_AVLP;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_STOPM_M;
        xHWREGB(SMC_PMCTRL) |= SMC_PMCTRL_STOPM_VLPS;
    }
    else if(ulStopMode == SYSCTL_STOP_MODE_NORMAL)
    {
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_RUNM_M;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_STOPM_M;
    }
    else if(ulStopMode == SYSCTL_STOP_MODE_LLS)
    {
        xHWREGB(SMC_PMPROT) |= SMC_PMPROT_ALLS;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_STOPM_M;
        xHWREGB(SMC_PMCTRL) |= SMC_PMCTRL_STOPM_LLS;
    }
    else if(ulStopMode == SYSCTL_STOP_MODE_VLLS0)
    {
        xHWREGB(SMC_PMPROT) |= SMC_PMPROT_AVLLS;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_STOPM_M;
        xHWREGB(SMC_PMCTRL) |= SMC_PMCTRL_STOPM_VLLS;
        xHWREGB(SMC_STOPCTRL) &= ~SMC_STOPCTRL_VLLSM_M;
        xHWREGB(SMC_STOPCTRL) |= SMC_STOPCTRL_VLLSM_VLLS0;
    }
    else if(ulStopMode == SYSCTL_STOP_MODE_VLLS1)
    {
        xHWREGB(SMC_PMPROT) |= SMC_PMPROT_AVLLS;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_STOPM_M;
        xHWREGB(SMC_PMCTRL) |= SMC_PMCTRL_STOPM_VLLS;
        xHWREGB(SMC_STOPCTRL) &= ~SMC_STOPCTRL_VLLSM_M;
        xHWREGB(SMC_STOPCTRL) |= SMC_STOPCTRL_VLLSM_VLLS1;
    }
    else if(ulStopMode == SYSCTL_STOP_MODE_VLLS2)
    {
        xHWREGB(SMC_PMPROT) |= SMC_PMPROT_AVLLS;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_STOPM_M;
        xHWREGB(SMC_PMCTRL) |= SMC_PMCTRL_STOPM_VLLS;
        xHWREGB(SMC_STOPCTRL) &= ~SMC_STOPCTRL_VLLSM_M;
        xHWREGB(SMC_STOPCTRL) |= SMC_STOPCTRL_VLLSM_VLLS2;
    }
    else
    {
        xHWREGB(SMC_PMPROT) |= SMC_PMPROT_AVLLS;
        xHWREGB(SMC_PMCTRL) &= ~SMC_PMCTRL_STOPM_M;
        xHWREGB(SMC_PMCTRL) |= SMC_PMCTRL_STOPM_VLLS;
        xHWREGB(SMC_STOPCTRL) &= ~SMC_STOPCTRL_VLLSM_M;
        xHWREGB(SMC_STOPCTRL) |= SMC_STOPCTRL_VLLSM_VLLS3;
    }
    //
    // WFI instruction will start entry into STOP mode
    //
    xCPUwfi();
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
SysCtlHClockGet(void)
{
    unsigned long  ulFreqout = 0, ulDivider = 0, ulDividerPll = 0;

    //
    // external 12MHz crystal clock.
    //
    if((xHWREG(MCG_C1)&SYSCTL_HLCK_S_MAIN) == SYSCTL_HLCK_S_MAIN)
    {
        ulFreqout = s_ulExtClockMHz*1000000;
        ulDivider = (xHWREG(SIM_CLKDIV1) & SIM_CLKDIV1_OUTDIV1_M) >> SIM_CLKDIV1_OUTDIV1_S;
        ulFreqout = ulFreqout/(ulDivider+1);  
    }
    //
    // internal 32KHz crystal clock.
    //
    else if((xHWREG(MCG_C1)&SYSCTL_HLCK_S_INT) == SYSCTL_HLCK_S_INT)     
    {
        if((xHWREGB(MCG_C2)&MCG_C2_IRCS) == MCG_C2_IRCS)
        {
            ulFreqout = 32768;
        }
        else
        {
            ulDivider = (xHWREG(SIM_CLKDIV1) & SIM_CLKDIV1_OUTDIV1_M) >> SIM_CLKDIV1_OUTDIV1_S;
            ulFreqout = 4000000/(ulDivider+1);
        }
    }
    //
    // PLL or FLL clock.
    //
    else    
    {
        //
        // PLL
        //
        if((xHWREGB(MCG_C6) & MCG_C6_PLLS) == MCG_C6_PLLS)
        {
            ulFreqout = s_ulExtClockMHz* ((xHWREGB(MCG_C6)&MCG_C6_VDIV0_M)+24)*1000000;
            ulDivider = (xHWREG(SIM_CLKDIV1) & SIM_CLKDIV1_OUTDIV1_M) >> SIM_CLKDIV1_OUTDIV1_S;
            ulDividerPll = (xHWREGB(MCG_C5)&MCG_C5_PRDIV0_M);
            ulFreqout = ulFreqout/((ulDivider+1)*(ulDividerPll+1));
        }
        //
        // FLL
        //
        else
        {
            //
            // The slow internal reference clock is FLL Source
            //
            if((xHWREG(MCG_C1)&MCG_C1_IREFS) == MCG_C1_IREFS)
            {
                ulFreqout = 96000000;
                ulDivider = (xHWREG(SIM_CLKDIV1) & SIM_CLKDIV1_OUTDIV1_M) >> SIM_CLKDIV1_OUTDIV1_S;
                ulFreqout = ulFreqout/(ulDivider+1);            
            }
            //
            // The external reference clock is FLL Source
            //
            else
            {
                ulFreqout = s_ulExtClockMHz * 1000000;
                ulDivider = (xHWREG(SIM_CLKDIV1) & SIM_CLKDIV1_OUTDIV1_M) >> SIM_CLKDIV1_OUTDIV1_S;
                ulFreqout = ulFreqout/(ulDivider+1);            
            }
        }
    }

    return ulFreqout;
}

//*****************************************************************************
//
//! \brief This function is used to set HCLK for the system
//!
//! \param ulSysClk is the clock rate you will set.
//! \param ulConfig is the required configuration of the device clock.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//! 
//! The external crystal frequency is chosen with one of the following values:
//! \b SYSCTL_XTAL_3MHZ, \b SYSCTL_XTAL_4MHZ, 
//! \b SYSCTL_XTAL_5MHZ, \b SYSCTL_XTAL_6MHZ, ...
//! \b SYSCTL_XTAL_32MHZ, 
//!
//! The HCLK source is chosen with one of the following values:
//! \b SYSCTL_OSC_MAIN, \b SYSCTL_OSC_PLL, \b SYSCTL_OSC_INT_FAST,
//! \b SYSCTL_OSC_FLL_INT, \b SYSCTL_OSC_FLL_MAIN, \b SYSCTL_OSC_INT. 
//! 
//! \note The ulSysClk should be External Reference Clock Rate if you Set the 
//! parameter ulConfig is SYSCTL_OSC_FLL_MAIN.
//! \return None.
//
//*****************************************************************************
void
SysCtlHClockSet(unsigned long ulSysClk, unsigned long ulConfig)
{

    unsigned long ulOscFreq=0, ulSysDiv, ulCount, i, ucTempReg, ulTemp;
    xASSERT((ulSysClk > 0 && ulSysClk <= 48000000));

    ulSysDiv = 0;
    //
    // Calc oscillator freq
    //
    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);

    //
    // HLCK clock source is SYSCTL_OSC_FLL_INT
    //
    if((ulConfig & 0x0F) == SYSCTL_OSC_FLL_INT)
    {
        ulOscFreq = 96000000;
        xHWREG(MCG_C1) &= 0x3F;
        xHWREG(MCG_C1) |= MCG_C1_IREFS;
        xHWREG(MCG_C6) &= ~MCG_C6_PLLS;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT);
        SysCtlDelay(100);
        if((ulConfig & OSC0_CR_ERCLKEN)!=0)
        {
            xHWREG(OSC0_CR) &= ~OSC0_CR_ERCLKEN;
        }
        xHWREG(MCG_C5) &= ~MCG_C5_PLLCLKEN0;
        xHWREG(MCG_C4) |= MCG_C4_DMX32;
        xHWREG(MCG_C4) |= MCG_C4_DRST_DRS_MID_HIGH;
        if(ulSysClk <= ulOscFreq)
        {
            //
            // Calc the SysDiv
            //    
            xASSERT(ulSysClk <= ulOscFreq);
            
            for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
            {
                if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
                {
                    break;
                }
            }
        }
        xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
        xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV1_S);
    }
    //
    // HLCK clock source is SYSCTL_OSC_FLL_MAIN
    //
    else if((ulConfig & 0x0F) == SYSCTL_OSC_FLL_MAIN)
    {
        if(!((((xHWREGB(MCG_S) & MCG_S_CLKST_M) >> MCG_S_CLKST_S) == 0x0) &&
          (xHWREGB(MCG_S) & MCG_S_IREFST) &&
          (!(xHWREGB(MCG_S) & MCG_S_PLLST))))                                
        {
        }
           
        ucTempReg = xHWREGB(MCG_C2);
        ucTempReg &= ~(MCG_C2_RANGE0_M | MCG_C2_HGO0 | MCG_C2_EREFS0);
        ucTempReg |= (MCG_C2_RANGE0_HIGH | MCG_C2_EREFS0); 
        xHWREGB(MCG_C2) = ucTempReg;

        ucTempReg = xHWREGB(MCG_C1);
        ucTempReg &= ~(MCG_C1_SRC_MCGOUTCLK_M | MCG_C1_FRDIV_M | MCG_C1_IREFS);
        ucTempReg |= (MCG_C1_SRC_MCGOUTCLK_EXTERAL | MCG_C1_FRDIV_256); 
        xHWREGB(MCG_C1) = ucTempReg;

        for (i = 0 ; i < 20000 ; i++)
        {
            if(xHWREGB(MCG_S) & MCG_S_OSCINIT0)
            {
                //
                // jump out early if OSCINIT sets before loop finishes
                //
                break;
            }
        }
        //
        // wait for Reference clock Status bit to clear
        //
        for (i = 0 ; i < 20000 ; i++)
        {
            if(xHWREGB(MCG_S) & MCG_S_IREFST)
            {
                //
                // jump out early if OSCINIT sets before loop finishes
                //
                break; 
            }
        }
        //
        // Wait for clock status bits to show clock source is ext ref clk
        //
        for (i = 0 ; i < 20000 ; i++)
        {
            if((xHWREGB(MCG_S) & MCG_S_CLKST_M)==MCG_S_CLKST_EXT)
            {
                //
                // jump out early if CLKST shows EXT CLK slected before loop finishes
                //
                break;
            }
        }
        xHWREGB(MCG_C6) |= MCG_C6_CME0;
        ulOscFreq = s_ulExtClockMHz * 1000000;
        if(ulSysClk <= ulOscFreq)
        {
            //
            // Calc the SysDiv
            //    
            xASSERT(ulSysClk <= ulOscFreq);
            
            for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
            {
                if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
                {
                    break;
                }
            }
            xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
            xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV1_S);
        }
    }
    //
    // HLCK clock source is SYSCTL_OSC_INT_FAST
    //
    else if((ulConfig & 0x0F) == SYSCTL_OSC_INT_FAST)
    {
        ulOscFreq = 4000000;
        xHWREG(OSC0_CR) &= ~OSC0_CR_ERCLKEN;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT);
        xHWREG(MCG_C6) &= ~MCG_C6_PLLS;
        xHWREG(MCG_C2) &= ~MCG_C2_LP;
        xHWREG(MCG_C2) |= MCG_C2_IRCS;
        SysCtlDelay(100);
        if((ulConfig & OSC0_CR_ERCLKEN)!=0)
        {
            xHWREG(OSC0_CR) &= ~OSC0_CR_ERCLKEN;
        }
        while(!(xHWREG(MCG_S)&MCG_S_CLKST_INT));
        if(ulSysClk <= ulOscFreq)
        {
            //
            // Calc the SysDiv
            //    
            xASSERT(ulSysClk <= ulOscFreq);
            
            for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
            {
                if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
                {
                    break;
                }
            }
        }
        xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
        xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV1_S);
    }
    //
    // HLCK clock source is SYSCTL_OSC_INT
    //
    else if((ulConfig & 0x0F) == SYSCTL_OSC_INT)
    {
        if(!((((xHWREGB(MCG_S) & MCG_S_CLKST_M) >> MCG_S_CLKST_S) == 0x0) &&
          (xHWREGB(MCG_S) & MCG_S_IREFST) &&
          (!(xHWREGB(MCG_S) & MCG_S_PLLST))))                                
        {
        }
        xHWREG(MCG_C2) &= ~MCG_C2_IRCS;
        //
        // Change the CLKS mux to select the IRC as the MCGOUT
        //
        ucTempReg = xHWREGB(MCG_C1);
        ucTempReg &= ~MCG_C1_SRC_MCGOUTCLK_M;
        //
        // select IRC as the MCG clock sourse
        //
        ucTempReg |= MCG_C1_SRC_MCGOUTCLK_INTERAL;
        xHWREGB(MCG_C1) = ucTempReg;
        //
        // wait until internal reference switches to requested irc.
        //
        for (i = 0 ; i < 2000 ; i++)
        {
            if((xHWREGB(MCG_S) & MCG_S_IRCST) != MCG_S_IRCST)
            {
                break;
            }

        }
        //
        // Wait for clock status bits to update
        //
        for (i = 0 ; i < 2000 ; i++)
        {
            if((xHWREGB(MCG_S) & MCG_S_CLKST_INT) == MCG_S_CLKST_INT)
            {
                break;            
            }

        }
    }
    //
    // HLCK clock source is SYSCTL_OSC_PLL
    //
    else if((ulConfig & 0xF0) == SYSCTL_OSC_PLL)
    {
        ulCount = 4096;
        xHWREG(OSC0_CR) |= OSC0_CR_ERCLKEN;
        while(ulCount--);
        xHWREG(MCG_C2) |= MCG_C2_RANGE0_HIGH;
        xHWREG(MCG_C2) |= MCG_C2_HGO0;
        xHWREG(MCG_C2) &= ~MCG_C2_EREFS0;
        xHWREG(MCG_C1) |= MCG_C1_SRC_MCGOUTCLK_EXTERAL;
        xHWREG(MCG_C1) |= MCG_C1_FRDIV_128;
        xHWREG(MCG_C1) &= ~MCG_C1_IREFS;
        while(!(xHWREG(MCG_S)&MCG_S_OSCINIT0));
        while((xHWREG(MCG_S)&MCG_S_IREFST));
        while(!(xHWREG(MCG_S)&MCG_S_CLKST_EXT));
        xHWREG(MCG_C5) &= ~MCG_C5_PRDIV0_M;
            
        ulOscFreq = s_ulExtClockMHz*1000000;
        if (ulSysClk <= ulOscFreq)
        {
            //
            // Calc the SysDiv
            //    
            xASSERT(ulSysClk <= ulOscFreq);
            
            for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
            {
                if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
                {
                    break;
                }
            }
            xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
            xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV1_S);
        }
        else
        {
            xHWREG(MCG_C6) |= MCG_C6_PLLS;
            while(!(xHWREG(MCG_S)&MCG_S_PLLST));
            while(!(xHWREG(MCG_S)&MCG_S_LOCK0));
            SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);
            while(!((xHWREG(MCG_S)&MCG_S_CLKST_PLL)==MCG_S_CLKST_PLL));
            xHWREG(MCG_C6) |= MCG_C6_VDIV0_48;
            ulOscFreq = 48*ulOscFreq;
            for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
            {
                if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
                {
                    break;
                }
            }
            xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
            xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV1_S);
        }
    }
    //
    // HLCK clock source is SYSCTL_OSC_MAIN
    //
    else 
    {
        xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
        xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV4_M;
        xHWREG(SIM_CLKDIV1) |= SIM_CLKDIV1_OUTDIV4_2;

        if(!((((xHWREGB(MCG_S) & MCG_S_CLKST_M) >> MCG_S_CLKST_S) == 0x0) &&
          (xHWREGB(MCG_S) & MCG_S_IREFST) &&
          (!(xHWREGB(MCG_S) & MCG_S_PLLST))))                                
        {
        }
           
        ucTempReg = xHWREGB(MCG_C2);
        ucTempReg &= ~(MCG_C2_RANGE0_M | MCG_C2_HGO0 | MCG_C2_EREFS0);
        ucTempReg |= (MCG_C2_RANGE0_HIGH | MCG_C2_EREFS0); 
        xHWREGB(MCG_C2) = ucTempReg;

        ucTempReg = xHWREGB(MCG_C1);
        ucTempReg &= ~(MCG_C1_SRC_MCGOUTCLK_M | MCG_C1_FRDIV_M | MCG_C1_IREFS);
        ucTempReg |= (MCG_C1_SRC_MCGOUTCLK_EXTERAL | MCG_C1_FRDIV_256); 
        xHWREGB(MCG_C1) = ucTempReg;

        for (i = 0 ; i < 20000 ; i++)
        {
            if(xHWREGB(MCG_S) & MCG_S_OSCINIT0)
            {
                //
                // jump out early if OSCINIT sets before loop finishes
                //
                break;
            }
        }
        //
        // wait for Reference clock Status bit to clear
        //
        for (i = 0 ; i < 20000 ; i++)
        {
            if(xHWREGB(MCG_S) & MCG_S_IREFST)
            {
                //
                // jump out early if OSCINIT sets before loop finishes
                //
                break; 
            }
        }
        //
        // Wait for clock status bits to show clock source is ext ref clk
        //
        for (i = 0 ; i < 20000 ; i++)
        {
            if((xHWREGB(MCG_S) & MCG_S_CLKST_M)==MCG_S_CLKST_EXT)
            {
                //
                // jump out early if CLKST shows EXT CLK slected before loop finishes
                //
                break;
            }
        }
        xHWREGB(MCG_C6) |= MCG_C6_CME0;

        ucTempReg = xHWREGB(MCG_C5);
        ucTempReg &= ~(MCG_C5_PRDIV0_M);
        ulTemp = ulSysClk/1000000;
        ulSysDiv = 192/ulTemp;
        if(ulSysDiv >= 24)
        {
            ulSysDiv = 24;
        }
        ucTempReg |= (ulSysDiv-1); 
        xHWREGB(MCG_C5) = ucTempReg;

        ucTempReg = xHWREGB(MCG_C6);
        ucTempReg &= ~(MCG_C6_VDIV0_M);
        ucTempReg |= (MCG_C6_PLLS | MCG_C6_VDIV0_24); 
        xHWREGB(MCG_C6) = ucTempReg;
            
        //
        // wait for PLLST status bit to set
        //
        for(i = 0 ; i < 2000 ; i++)
        {
            if(xHWREGB(MCG_S) & MCG_S_PLLST)
            {
                //
                // jump out early if PLLST sets before loop finishes
                //
                break; 
            }
        }
        //
        // Wait for LOCK bit to set
        //
        for(i = 0 ; i < 4000 ; i++)
        {
            if(xHWREGB(MCG_S)&MCG_S_LOCK0)
            {
                //
                // jump out early if LOCK sets before loop finishes
                //
                break;
            }
        }

        SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);

        //
        // Wait for clock status bits to update
        //
        for (i = 0 ; i < 2000 ; i++)
        {
            if((xHWREGB(MCG_S) & MCG_S_CLKST_PLL) == MCG_S_CLKST_PLL)
            {
                break; // jump out early if CLKST = 3 before loop finishes            
            }

        }
        //
        // set PLLFLLSEL to select the PLL for this clock source
        //
        xHWREG(SIM_SOPT2) |= SIM_SOPT2_PLLFLLSEL;

        if (ulSysClk <= ulOscFreq)
        {
            //
            // Calc the SysDiv
            //    
            xASSERT(ulSysClk <= ulOscFreq);
            
            for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
            {
                if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
                {
                    break;
                }
            }
            xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV1_M;
            xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV1_S);
        }
    }
}

//*****************************************************************************
//
//! \brief The function is used to Set Clock Output source. 
//!
//! \param ulClkOutSrc is the clock source of Clock Output.
//!
//! The function is used to Set Clock Output source.
//!
//! \return None.
//
//*****************************************************************************
void SysCtlClkOututSrcSet(unsigned long ulClkOutSrc)
{
    //
    // Check the arguments.
    //
    xASSERT((ulClkOutSrc == SYSCTL_OUTPUT_CLKSRC_BUS)||
            (ulClkOutSrc == SYSCTL_OUTPUT_CLKSRC_LPO)||
            (ulClkOutSrc == SYSCTL_OUTPUT_CLKSRC_MCGIRCLK)||
            (ulClkOutSrc == SYSCTL_OUTPUT_CLKSRC_OSCERCLK));
    //
    // Select Output Clock Source.
    //
    xHWREG(SIM_SOPT2) &= ~SIM_SOPT2_CLKOUTSEL_M;
    xHWREG(SIM_SOPT2) |= ulClkOutSrc;
}

//*****************************************************************************
//
//! \brief The function is used to Set Bus Clock. 
//!
//! \param ulBusClk is the bus clock you will set.
//!
//! The function is used to Set Bus Clock.
//!
//! \return None.
//
//*****************************************************************************
void SysCtlBusClkSet(unsigned long ulBusClk)
{
    unsigned long ulHclk = 0, ulSysDiv;

    //
    // Check the arguments.
    //
    xASSERT((ulBusClk > 0 && ulBusClk <= 24000000));

    //
    // Get the Hclk.
    //
    ulHclk = SysCtlHClockGet();
    
    if (ulBusClk <= ulHclk)
    {
        //
        // Calc the SysDiv
        //    
        xASSERT(ulBusClk <= ulHclk);
        
        for(ulSysDiv = 1; ulSysDiv < 8; ulSysDiv++)
        {
            if((ulHclk / (ulSysDiv + 1)) <= ulBusClk)
            {
                break;
            }
        }
        xHWREG(SIM_CLKDIV1) &= ~SIM_CLKDIV1_OUTDIV4_M;
        xHWREG(SIM_CLKDIV1) |= (ulSysDiv << SIM_CLKDIV1_OUTDIV4_S);
    }
}
//*****************************************************************************
//
//! \brief The function is used to Get Bus Clock. 
//!
//! \param None.
//!
//! The function is used to Get Bus Clock.
//!
//! \return the Bus clock.
//
//*****************************************************************************
unsigned long SysCtlBusClkGet(void)
{
    unsigned long ulHclk = 0, ulBusClk = 0, ulSysDiv;

    //
    // Get the Hclk.
    //
    ulHclk = SysCtlHClockGet();
    
    //
    // Calc the SysDiv
    //    
    ulSysDiv = (xHWREG(SIM_CLKDIV1) & SIM_CLKDIV1_OUTDIV4_M) >> SIM_CLKDIV1_OUTDIV4_S;
    
    ulBusClk = ulHclk/(ulSysDiv+1);
    
    return ulBusClk;
}

//*****************************************************************************
//
//! \brief The function is to Enable Bandgap In VLPx Operation or not
//!
//! \param bEnable is a boolean that is \b true if Enable Bandgap In VLPx 
//! Operation and \b false if Disable it.
//!
//! The function is used to Enable Bandgap In VLPx Operation or not
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBandgapEnable(xtBoolean bEnable)
{
    //
    // Enable Bandgap In VLPx Operation.
    //
    if(bEnable)
    {
        xHWREGB(PMC_REGSC) |= PMC_REGSC_BGEN;
    }
    //
    // Disable Bandgap In VLPx Operation.
    //
    else
    {
        xHWREGB(PMC_REGSC) &= ~PMC_REGSC_BGEN;
    }
}

//*****************************************************************************
//
//! \brief The function is to Enable Bandgap Buffer or not
//!
//! \param bEnable is a boolean that is \b true if Enable Bandgap Buffer 
//! and \b false if Disable it.
//!
//! The function is used to Enable Bandgap Buffer or not
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBandgapBufferEnable(xtBoolean bEnable)
{
    //
    // Enable Bandgap Buffer.
    //
    if(bEnable)
    {
        xHWREGB(PMC_REGSC) |= PMC_REGSC_BGBE;
    }
    //
    // Disable Bandgap Buffer.
    //
    else
    {
        xHWREGB(PMC_REGSC) &= ~PMC_REGSC_BGBE;
    }
}

//*****************************************************************************
//
//! \brief Get Status of Regulator In Run Regulation.
//!
//! \param None.
//!
//! This function is to Get Status of Regulator In Run Regulation.
//!
//! \return This function return Status of Regulator In Run Regulation,if Regulator
//! is in run regulation, it returns xtrue, xfalse if not.
//
//*****************************************************************************
xtBoolean
SysCtlRegulatorStatusGet(void)
{
    xtBoolean xtFlag = 0;

    xtFlag = xHWREGB(PMC_REGSC) & PMC_REGSC_REGONS;
    if(xtFlag)
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief The function is used to Get PWM and UART0 Clock Rate. 
//!
//! \param None.
//!
//! The function is used to Get PWM and UART0 Clock Rate.
//!
//! \return the PWM and UART0 Clock Rate clock.
//
//*****************************************************************************
unsigned long SysCtlPWMAndUART0ClkGet(void)
{
    unsigned long ulHclk = 0, ulPWMClk = 0;

    //
    // Check the PWM Clock Source.
    //
    if((xHWREG(SIM_SOPT2) & SIM_SOPT2_TPMSRC_MCGXLL)
                         == SIM_SOPT2_TPMSRC_MCGXLL)
    {
        ulHclk = SysCtlHClockGet();
        ulPWMClk = ulHclk/2;
        return ulPWMClk;
    }
    else if((xHWREG(SIM_SOPT2) & SIM_SOPT2_TPMSRC_OSCERCLK)
                         == SIM_SOPT2_TPMSRC_OSCERCLK)
    {
        xHWREGB(OSC0_CR) |= OSC0_CR_ERCLKEN;
        xHWREGB(MCG_C2) |= MCG_C2_EREFS0;
        ulPWMClk = s_ulExtClockMHz*1000000;
        return ulPWMClk;    
    }
    else
    {
        xHWREGB(MCG_C1) |= MCG_C1_IRCLKEN;
        xHWREGB(MCG_C2) |= MCG_C2_IRCS;
        ulPWMClk = 4000000;
        return ulPWMClk;    
    }
}