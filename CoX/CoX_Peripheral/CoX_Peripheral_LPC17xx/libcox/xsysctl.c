//*****************************************************************************
//
//! \file xsysctl.c
//! \brief Driver for the system controller
//! \version V2.2.1.0
//! \todo Update this time information.
//! \date 11/20/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
//!     - Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     - Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     - Neither the name of the <ORGANIZATION> nor the names of its
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
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"

static unsigned long s_ulExtClockMHz = 12000000;
static unsigned long g_ulSystemClk = 0;           // System Clock frequency
static unsigned long g_ulAHBClk    = 0;           // AHB Clock frequency
//static unsigned long g_ulAPB1Clk   = 0;           // APB1 Clock frequency
//static unsigned long g_ulAPB2Clk   = 0;           // APB2 Clock frequency

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

    { xTIMER0_BASE       , xSYSCTL_PERIPH_TIMER0  , xINT_TIMER0 },
    { xTIMER1_BASE       , xSYSCTL_PERIPH_TIMER1  , xINT_TIMER1 },
    { xUART0_BASE        , xSYSCTL_PERIPH_UART0   , xINT_UART0  },
    { xUART1_BASE        , xSYSCTL_PERIPH_UART1   , xINT_UART1  },
    { xPWM0_BASE         , xSYSCTL_PERIPH_PWM0    , xINT_PWM0   },
    { xPWM1_BASE         , xSYSCTL_PERIPH_PWM1    , xINT_PWM1   },
    { xI2C0_BASE         , xSYSCTL_PERIPH_I2C0    , xINT_I2C0   },
    { xSPI0_BASE         , xSYSCTL_PERIPH_SPI     , xINT_SPI0   },
    { xRTC_BASE          , xSYSCTL_PERIPH_RTC     , xINT_RTC    },
    { xSSP1_BASE         , xSYSCTL_PERIPH_SSP1    , xINT_SSP1   },
    { xADC0_BASE         , xSYSCTL_PERIPH_ADC0    , xINT_ADC    },
    { xCAN1_BASE         , xSYSCTL_PERIPH_CAN1    , xINT_CAN1   },
    { xCAN2_BASE         , xSYSCTL_PERIPH_CAN2    , xINT_CAN2   },
    { xGPIO_PORTA_BASE   , xSYSCTL_PERIPH_GPIOA   , xINT_GPIOA  },
    { xGPIO_PORTB_BASE   , xSYSCTL_PERIPH_GPIOB   , xINT_GPIOB  },
    { xGPIO_PORTC_BASE   , xSYSCTL_PERIPH_GPIOC   , xINT_GPIOC  },
    { xGPIO_PORTD_BASE   , xSYSCTL_PERIPH_GPIOD   , xINT_GPIOD  },
    { xGPIO_PORTE_BASE   , xSYSCTL_PERIPH_GPIOE   , xINT_GPIOE  },
    { xRIT_BASE          , xSYSCTL_PERIPH_RIT     , 0           },
    { xMCPWM_BASE        , xSYSCTL_PERIPH_MCPWM   , 0           },
    { xQEI_BASE          , xSYSCTL_PERIPH_QEI     , 0           },
    { xI2C1_BASE         , xSYSCTL_PERIPH_I2C1    , xINT_I2C1   },
    { xSSP0_BASE         , xSYSCTL_PERIPH_SSP0    , xINT_SSP0   },
    { xTIMER2_BASE       , xSYSCTL_PERIPH_TIMER2  , xINT_TIMER2 },
    { xTIMER3_BASE       , xSYSCTL_PERIPH_TIMER3  , xINT_TIMER3 },
    { xUART2_BASE        , xSYSCTL_PERIPH_UART2   , xINT_UART2  },
    { xUART3_BASE        , xSYSCTL_PERIPH_UART3   , xINT_UART3  },
    { xI2C2_BASE         , xSYSCTL_PERIPH_I2C2    , xINT_I2C2   },
    { xUART4_BASE        , xSYSCTL_PERIPH_UART4   , xINT_UART4  },
    { xI2S_BASE          , xSYSCTL_PERIPH_I2S     , xINT_I2S    },
    { xDMA0_BASE         , xSYSCTL_PERIPH_DMA     , xINT_DMA0   },
    { xETH_BASE          , xSYSCTL_PERIPH_ETH     , xINT_ETH    },
    { xUSB_BASE          , xSYSCTL_PERIPH_USB     , xINT_USB    },
    { 0                  , 0                      , 0           },
};

//*****************************************************************************
//
//! \brief       Calculate the PLL Multiplier/Diviver
//! \param [in]  Fin is the input clock frequency (1Mhz --> 25Mhz).
//! \param [in]  Fout is the target clock frequency, Maximum value is 120Mhz.
//! \param [out] pM is the Calculate result of multipler.
//! \param [out] pN is the Calculate result of divider.
//! \param [out] pDiv is the system divider.
//! \return      the result of calculate
//!              - 0 Failure
//!              - 1 Success
//! \note
//!              - This function is internal use, user MUST NOT call it.
//!              - pM and pN is the pointer, must be point to a valid variable.
//!              - This function only used for calculate internal RC and
//!                oscillator, NOT supply RTC(32.768KHz).
//
//*****************************************************************************
static unsigned long PLLMNCal(unsigned long Fin,
        unsigned long Fout, unsigned long * pM, unsigned long *pN, unsigned long *pDiv)
{
    unsigned long M    = 0;   // PLL Multiplier Value
    unsigned long N    = 0;   // PLL Divider Value
    unsigned long Fcco = 0;   // PLL Fcco Output frequency
    unsigned long Fclk = 0;   // System Clock frequency
    unsigned long i    = 0;   // Counter

    /************ Check Input parameters ****************/
    // Input Frequency Range: 1 --> 25 Mhz
    if((Fin < 1000000) || (Fin > 25000000))
    {
        return (0);
    }

    // Target Maximum Frequency Range: 10 --> 120Mhz
    if( (Fout == 0) || (Fout >= 120000000) )
    {
        return (0);
    }

    // Check pN/pM Pointer valid
    if((pN == 0) || (pM == 0))
    {
        return (0);
    }

    /************ Calculate Multiplier/Divider **********/
    for(N = 1; N < 32; N++)
    {

        // The value of PLOCK0 may not be stable when the PLL reference frequency
        // (FREF, the frequency of REFCLK, which is equal to the PLL input
        // frequency divided by the pre-divider value) is less than 100 kHz or
        // greater than 20 MHz
        Fcco = Fin/N;
        if((Fcco < 100000) || (Fcco > 20000000))
        {
            continue;
        }

        for(M = 6; M < 512; M++)
        {
            // Fcco Range: 275 --> 550 MHz
            Fcco = Fin/N;
            Fcco = 2*Fcco*M;
            if( (Fcco < 275000000) || (Fcco > 550000000) )
            {
                continue;
            }

            for(i = 1; i < 256; i++)
            {
                Fclk = Fcco/i;
                if(Fclk > 120000000)
                {
                    continue;
                }

                // Fclk and Fout Maximum different is 10K
                if( ((Fclk - Fout) <= 10000) || ((Fout - Fclk) <= 10000) )
                {
                    // Find suitable Multiplier/Divider value.
                    *pM   = M;
                    *pN   = N;
                    *pDiv = i;
                    return (1);
                }
            }

        }
    }

    // Can not find suitable Multiplier/Divider value.
    return (0);
}


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
    __asm("    subs    r0, #1\n"
          "    bne     SysCtlDelay\n"
          "    bx      lr");
}
#elif defined(ewarm) || defined(__ICCARM__)
void
SysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   SysCtlDelay\n"
          "    bx      lr");
}
#elif defined(rvmdk) || defined(__CC_ARM)
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
//! \brief Configure the system clock of the device.
//!
//! This function configures the clock of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! \param [in] ulSysClk is the target system clock frequency.
//! \param [in] ulConfig is the required configuration of the device clock.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//!     - \ref SYSCTL_XTAL_1_MHZ
//!     - \ref SYSCTL_XTAL_2_MHZ
//!     - ...
//!     - \ref SYSCTL_XTAL_25_MHZ
//!
//! The oscillator source is chosen with one of the following values:
//!     - \ref SYSCTL_OSC_MAIN
//!     - \ref SYSCTL_OSC_INT
//!
//! The internal and main oscillators and PLL are disabled with the
//!     - \ref SYSCTL_INT_OSC_DIS
//!     - \ref SYSCTL_MAIN_OSC_DIS
//!     - \ref SYSCTL_PLL_PWRDN
//!
//! \return None.
//!
//! \note
//!      The external oscillator must be enabled in order to use an external clock
//!      source.  Note that attempts to disable the oscillator used to clock the
//!      device will be prevented by the hardware.
//!
//
//*****************************************************************************
void SysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig)
{

    unsigned long ulTmpReg;   // Temporary register
    unsigned long ulRes;      // Store Result value
    unsigned long ulM;        // PLL Multiplier
    unsigned long ulN;        // PLL Divider
    unsigned long ulDiv;      // System clock divider
    unsigned long ulFin;      // Input Clock frequency

    /************** Check input parameters valid ********************/
    // ulSysClk clock range: 0 --> 12MHz
    xASSERT( (ulSysClk > 0) && (ulSysClk <= SYSTEM_CLOCK_MAX) );

    // Check ulConfig valid
    xASSERT((ulConfig & ~BIT_MASK(32, 9, 0)) == 0);

    /************** Configure Flash Accelerator  ********************/
    // use 6 CPU clocks.
    // This "safe" setting will work under any conditions
    ulTmpReg = xHWREG(FLASHCFG);
    ulTmpReg &= ~FLASHCFG_FLASHTIM_M;
    ulTmpReg |=  FLASHCFG_FLASHTIM_ANY;
    xHWREG(FLASHCFG) = ulTmpReg;

    /************** Configure Main Oscillator    ********************/
    // Need Enable Main Oscillator ?
    if(ulConfig & SYSCTL_OSC_MAIN)              // Enable Main Osc
    {
        // Get Input Frequency (unit: Hz)
        ulTmpReg = (ulConfig & SYSCTL_XTAL_nMHZ_MASK) * 1000000;

        // Configure Main Osc Frequency Range
        if(ulTmpReg > 20000000)
        {
            ulTmpReg = xHWREG(SCS);
            if((ulTmpReg & SCS_OSCRS) == 0)    // Wrong Range: 1 --> 20 MHz
            {
                if(ulTmpReg & SCS_OSCEN)       // Main Osc Have Been enabled
                {
                    //Disable Main Osc then Configure Osc Range
                    ulTmpReg &= ~SCS_OSCEN;
                    xHWREG(SCS) = ulTmpReg;

                    // Waiting for Main Osc Disabled
                    do
                    {
                        ulTmpReg = xHWREG(SCS);
                        ulTmpReg &= SCS_OSCEN;
                    }while(ulTmpReg != 0);

                    // Configure Osc Range
                    ulTmpReg = xHWREG(SCS);
                    ulTmpReg |= SCS_OSCRS;
                    xHWREG(SCS) = ulTmpReg;
                }
            }
        }

        ulTmpReg = xHWREG(SCS);
        if((ulTmpReg & SCS_OSCSTAT) != SCS_OSCSTAT_RDY)
        {
            // Enable Main Osc
            ulTmpReg |= SCS_OSCEN;
            xHWREG(SCS) = ulTmpReg;

            // Waitting for Main Osc stable.
            do
            {
                ulTmpReg =  xHWREG(SCS);
                ulTmpReg &= SCS_OSCSTAT;
            }while(ulTmpReg != SCS_OSCSTAT_RDY);
        }

        //Select Main Osc as PLL Input
        ulTmpReg = xHWREG(CLKSRCSEL);
        ulTmpReg &= ~CLKSRCSEL_CLKSRC_M;
        ulTmpReg |= CLKSRCSEL_CLKSRC_OSC;
        xHWREG(CLKSRCSEL) = ulTmpReg;

        // Get Input Frequency (unit: Hz)
        ulFin = (ulConfig & SYSCTL_XTAL_nMHZ_MASK) * 1000000;
    }

    /************** Configure Internal oscillator ********************/
    // For LPC 17xx serial MCU, Internal RC is always enable.
    // so, you need not deal with those parameters
    // 1) SYSCTL_OSC_INT
    // 2) SYSCTL_INT_OSC_DIS
    //
    if(ulConfig & SYSCTL_OSC_INT)             // Enable Internal Osc
    {
        //Need not Enable Internal RC

        //Select Internal RC as PLL Input
        ulTmpReg = xHWREG(CLKSRCSEL);
        ulTmpReg &= ~CLKSRCSEL_CLKSRC_M;
        ulTmpReg |= CLKSRCSEL_CLKSRC_IRC;
        xHWREG(CLKSRCSEL) = ulTmpReg;

        // Get Input Frequency (unit: Hz)
        // For IRC, there is 4MHz
        ulFin = 4 * 1000000;
    }

    //
    // if(ulConfig & SYSCTL_INT_OSC_DIS)        // Disable Internal Osc
    // {
    //     //Do Nothing Here.
    // }

    /************** Configure PLL                 ********************/
    // Need to Turn off PLL ?
    // if(ulConfig & SYSCTL_PLL_PWRDN)
    // {
    //     //Do Nothing Here
    // }

    s_ulExtClockMHz = ulFin;
    ulRes = PLLMNCal(ulFin, ulSysClk, &ulM, &ulN, &ulDiv);
    if(!ulRes)                                  // Configure Failure
    {
        while(1);
    }

    // Check PLL Enable/Connect Status
    // if Enable and Connect, then disconnect it.
    // At last, Reconfigure PLL and connect to system clock.
#if defined(LPC_175x) && defined (LPC_176x)
    // PLL0 Connected ?
    ulTmpReg = xHWREG(PLL0STAT);
    if(ulTmpReg & PLL0STAT_PLLC_STAT)           // Connected to System Clock
    {
        // Disconnect PLL
        ulTmpReg = xHWREG(PLL0CON);
        ulTmpReg &= ~PLL0CON_PLLC;
        xHWREG(PLL0CON) = ulTmpReg;

        // Write key to PLL Feed register
        xHWREG(PLL0FEED) = 0xAA;
        xHWREG(PLL0FEED) = 0x55;

        // waiting for disconnect
        do
        {
            ulTmpReg = xHWREG(PLL0STAT);
            ulTmpReg &= PLL0STAT_PLLC_STAT;
        }while(ulTmpReg);

    }
#endif

    // PLL0 Enable ?
    ulTmpReg = xHWREG(PLL0STAT);
    if(ulTmpReg & PLL0STAT_PLLE_STAT) // PLL Have Been Enabled, we need to Disable it.
    {
        // Disable PLL0
        ulTmpReg =  xHWREG(PLL0CON);
        ulTmpReg &= ~PLL0CON_PLLE;
        xHWREG(PLL0CON) = ulTmpReg;

        // Write key to PLL0 Feed register
        xHWREG(PLL0FEED) = 0xAA;
        xHWREG(PLL0FEED) = 0x55;

        // Waitting for Disable
        do
        {
            ulTmpReg = xHWREG(PLL0STAT);
            ulTmpReg &= PLL0STAT_PLLE_STAT;
        }while(ulTmpReg);
    }
 
    // Configure PLL0 Multiplier/Divider
    ulM -= 1;
    ulN -= 1;
    ulTmpReg = (ulN << PLL0CFG_PSEL_S) | ulM;
    xHWREG(PLL0CFG) = 0x09; //ulTmpReg;

    //ReEnable PLL0 and Wait Locked
    ulTmpReg =  xHWREG(PLL0CON);
    ulTmpReg |= PLL0CON_PLLE;
    xHWREG(PLL0CON) = ulTmpReg;

    // Write key to PLL0 Feed register
    xHWREG(PLL0FEED) = 0xAA;
    xHWREG(PLL0FEED) = 0x55;

    // Waitting for PLL0 Enable and Locked
    do
    {
        ulTmpReg = xHWREG(PLL0STAT);
        ulTmpReg &= (PLL0STAT_PLLE_STAT | PLL0STAT_PLOCK);
    }while(ulTmpReg == 0);

    //
    //! Configure PLL1 Multiplier/Divider for USB Clock
    //
    xHWREG(PLL1CFG)   = 0x23;
    
    //ReEnable PLL1 and Wait Locked
    ulTmpReg =  xHWREG(PLL1CON);
    ulTmpReg |= PLL1CON_PLLE;
    xHWREG(PLL1CON) = ulTmpReg;
    
    // Write key to PLL1 Feed register
    xHWREG(PLL1FEED)  = 0xAA;
    xHWREG(PLL1FEED)  = 0x55;
    
    // Waitting for PLL1 Enable
    do
    {
        ulTmpReg = xHWREG(PLL1STAT);
        ulTmpReg &= PLL1STAT_PLLE_STAT ;
    }while(ulTmpReg == 0);
 
    // Waitting for PLL1 Locked
    do
    {
        ulTmpReg = xHWREG(PLL1STAT);
        ulTmpReg &= PLL1STAT_PLOCK;
    }while(ulTmpReg == 0);
    
#if defined(LPC_175x) || defined (LPC_176x)
    // Connect It
    ulTmpReg =  xHWREG(PLL0CON);
    ulTmpReg |= PLL0CON_PLLC;
    xHWREG(PLL0CON) = ulTmpReg;

    // Write key to PLL Feed register
    xHWREG(PLL0FEED) = 0xAA;
    xHWREG(PLL0FEED) = 0x55;
    
    // Waitting for Enable
    do
    {
        ulTmpReg = xHWREG(PLL0STAT);
        ulTmpReg &= PLL0STAT_PLLC_STAT;
    }while(ulTmpReg == 0);
#endif

    // Setup Clock Divider
    xHWREG(CCLKSEL) = (1<<8)|(ulDiv - 1);
    
    // Select PLL1 for USB clock and Setup USB Clock Divider
    xHWREG(USBCLKSEL) = 0x01|(0x02 << 8);
    
    // EMC Clock Selection
    xHWREG(EMCCLKSEL) = 0x01;
    
    // Peripheral Clock Selection, APB clock is equal to AHB/2
#if defined(LPC_177x) | defined(LPC_178x)
    xHWREG(PCLKSEL)  = 0x02;
#else
    xHWREG(PCLKSEL0) = (unsigned long)0x00;
    xHWREG(PCLKSEL1) = (unsigned long)0x00;
#endif
}

//*****************************************************************************
//
//! \brief      Configure External interrupt.
//!
//! \param [in] ulPin is the MCU External interrupt channel, this value can be
//!             logical OR of the following value:
//!             - \ref EXT_INT_0
//!             - \ref EXT_INT_1
//!             - \ref EXT_INT_2
//!             - \ref EXT_INT_3
//!
//! \param [in] ulCfg is used to configure Interrupt Type, this value can be
//!             one of the following value:
//!             - \ref EXT_INT_LV_H         High Level
//!             - \ref EXT_INT_LV_L         Low Level
//!             - \ref EXT_INT_EG_R         Rising Edge
//!             - \ref EXT_INT_EG_F         Falling Edge
//!
//! \return     None.
//!
//
//*****************************************************************************
void SysCtlExtIntCfg(unsigned long ulPin, unsigned long ulCfg)
{
    unsigned long i         = 0;
    unsigned long ulTmpReg1 = 0;
    unsigned long ulTmpReg2 = 0;

    // Check input parameters
    xASSERT( (ulPin & EXT_INT_MASK) != 0 );
    xASSERT( (ulCfg & EXT_INT_MASK) != 0 );

    ulTmpReg1 = xHWREG(EXTMODE);              // External Interrupt Mode register
    ulTmpReg2 = xHWREG(EXTPOLAR);             // External Interrupt Polar register

    for(i = 0; i < 4; i++)
    {
        if(ulPin & (0x01 << i))
        {
            switch(ulCfg)
            {
                case EXT_INT_LV_H:            // High Level Triggle
                    {
                        ulTmpReg1 &= ~(0x01 << i);
                        ulTmpReg2 |=  (0x01 << i);
                        break;
                    }
                case EXT_INT_LV_L:           // Low Level Triggle
                    {
                        ulTmpReg1 &= ~(0x01 << i);
                        ulTmpReg2 &= ~(0x01 << i);
                        break;
                    }
                case EXT_INT_EG_R:           // Rising Triggle
                    {
                        ulTmpReg1 |=  (0x01 << i);
                        ulTmpReg2 |=  (0x01 << i);
                        break;
                    }
                case EXT_INT_EG_F:           // Falling Triggle
                    {
                        ulTmpReg1 |=  (0x01 << i);
                        ulTmpReg2 &= ~(0x01 << i);
                        break;
                    }
            }
        }
    }

    // Write back to mode/polar register
    xHWREG(EXTMODE)  = ulTmpReg1;             // Mode register
    xHWREG(EXTPOLAR) = ulTmpReg2;             // Polar register
}

//*****************************************************************************
//
//! \brief  Get the External Interrupt source flag.
//!
//! \param  None.
//!
//! \return The External Interrupt flag, this value is logical OR of the
//!         following value:
//!             - \ref EXT_INT_0
//!             - \ref EXT_INT_1
//!             - \ref EXT_INT_2
//!             - \ref EXT_INT_3
//!
//! \note   User can use \ref SysCtlExtIntFlagGet or \ref SysCtlExtIntFlagCheck
//!         to check MCU External Int source.
//
//*****************************************************************************
unsigned long SysCtlExtIntFlagGet(void)
{
    return xHWREG(EXTINT);
}

//*****************************************************************************
//
//! \brief      Check the External Interrupt source flag.
//!
//! \param [in] ulFlag is the External Interrupt Channel, This parameter can be
//!             one of the following value:
//!             - \ref EXT_INT_0
//!             - \ref EXT_INT_1
//!             - \ref EXT_INT_2
//!             - \ref EXT_INT_3
//!
//! \return     The status of the External Int flag.
//!             - xtrue The Checked Flag has been set.
//!             - xfalse The Checked Flag has not been set.
//!
//! \note   User can use \ref SysCtlExtIntFlagGet or \ref SysCtlExtIntFlagCheck
//!         to check MCU External Int source.
//
//*****************************************************************************
xtBoolean SysCtlExtIntFlagCheck(unsigned long ulFlag)
{
    unsigned long ulTmpReg = 0;

    xASSERT( (ulFlag & EXT_INT_MASK) != 0 );

    ulTmpReg = xHWREG(EXTINT);

    if(ulTmpReg & ulFlag)
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
//! \brief      Check the External Interrupt source flag.
//!
//! \param [in] ulFlag is the External Interrupt Channel, This parameter can be
//!             one of the following value:
//!             - \ref EXT_INT_0
//!             - \ref EXT_INT_1
//!             - \ref EXT_INT_2
//!             - \ref EXT_INT_3
//!
//! \return     The status of the External Int flag.
//!             - xtrue The Checked Flag has been set.
//!             - xfalse The Checked Flag has not been set.
//!
//! \note   User can use \ref SysCtlExtIntFlagGet or \ref SysCtlExtIntFlagCheck
//!         to check MCU External Int source.
//
//*****************************************************************************
void SysCtlExtIntFlagClear(unsigned long ulFlag)
{

    xASSERT( (ulFlag & EXT_INT_MASK) != 0 );

    xHWREG(EXTINT) |= ulFlag;
}

//*****************************************************************************
//
//! \brief  Get the reset source flag.
//!
//! \param  None.
//!
//! \return The reset flag, this value is logical OR of the following value:
//!         - \ref RESET_FLAG_POR          Power On reset
//!         - \ref RESET_FLAG_EXTR         External reset
//!         - \ref RESET_FLAG_WDTR         Watchdog reset
//!         - \ref RESET_FLAG_BODR         Brown-out reset
//!         - \ref RESET_FLAG_SYSRESET     System Request reset
//!         - \ref RESET_FLAG_LOCKUP       Lock up reset
//!
//! \note   User can use \ref SysCtlResetFlagGet or \ref SysCtlResetFlagCheck
//!         to check MCU reset source.
//
//*****************************************************************************
unsigned long SysCtlResetFlagGet(void)
{
   return xHWREG(RSID);
}

//*****************************************************************************
//
//! \brief       Check the reset source flag.
//!
//! \param [in]  ulFlag is the reset flag, this value is logical OR of
//!              the following value:
//!              - \ref RESET_FLAG_POR          Power On reset
//!              - \ref RESET_FLAG_EXTR         External reset
//!              - \ref RESET_FLAG_WDTR         Watchdog reset
//!              - \ref RESET_FLAG_BODR         Brown-out reset
//!              - \ref RESET_FLAG_SYSRESET     System Request reset
//!              - \ref RESET_FLAG_LOCKUP       Lock up reset
//!
//! \return      The status of the reset flag.
//!              - xtrue The Checked Flag has been set.
//!              - xfalse The Checked Flag has not been set.
//
//*****************************************************************************
xtBoolean SysCtlResetFlagCheck(unsigned long ulFlag)
{
    unsigned long ulTmpReg = 0;

    ulTmpReg = xHWREG(RSID);

    if(ulTmpReg & ulFlag)
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
//! \brief       Clear the reset source flag.
//!
//! \param [in]  ulFlag is the reset flag, this value is logical OR of
//!              the following value:
//!              - \ref RESET_FLAG_POR          Power On reset
//!              - \ref RESET_FLAG_EXTR         External reset
//!              - \ref RESET_FLAG_WDTR         Watchdog reset
//!              - \ref RESET_FLAG_BODR         Brown-out reset
//!              - \ref RESET_FLAG_SYSRESET     System Request reset
//!              - \ref RESET_FLAG_LOCKUP       Lock up reset
//!
//! \return      None.
//
//*****************************************************************************
void SysCtlResetFlagClear(unsigned long ulFlag)
{
    //! Check input Parameters
     xASSERT( ulFlag & (RESET_FLAG_POR     | RESET_FLAG_EXTR   |
                       RESET_FLAG_WDTR     | RESET_FLAG_BODR   |
                       RESET_FLAG_SYSRESET | RESET_FLAG_LOCKUP) );

    xHWREG(RSID) |= ulFlag;
}

//*****************************************************************************
//
//! \brief Configure Peripheral Clock.
//!
//! \param [in] ulPeri is the LPC17nx(n=5/6) peripherals, the parameter can be
//!             logical OR of the following value:
//!             - \ref PCLKSEL_WDT
//!             - \ref PCLKSEL_TIMER0
//!             - \ref PCLKSEL_TIMER1
//!             - \ref PCLKSEL_UART0
//!             - \ref PCLKSEL_UART1
//!             - \ref PCLKSEL_PWM1
//!             - \ref PCLKSEL_I2C0
//!             - \ref PCLKSEL_SPI
//!             - \ref PCLKSEL_SSP1
//!             - \ref PCLKSEL_DAC
//!             - \ref PCLKSEL_ADC
//!             - \ref PCLKSEL_CAN1
//!             - \ref PCLKSEL_CAN2
//!             - \ref PCLKSEL_ACF
//!             - \ref PCLKSEL_QEI
//!             - \ref PCLKSEL_GPIOINT
//!             - \ref PCLKSEL_PCB
//!             - \ref PCLKSEL_I2C1
//!             - \ref PCLKSEL_SSP0
//!             - \ref PCLKSEL_TIMER2
//!             - \ref PCLKSEL_TIMER3
//!             - \ref PCLKSEL_UART2
//!             - \ref PCLKSEL_UART3
//!             - \ref PCLKSEL_I2C2
//!             - \ref PCLKSEL_I2S
//!             - \ref PCLKSEL_RIT
//!             - \ref PCLKSEL_SYSCON
//!             - \ref PCLKSEL_MC
//!
//! \param [in] ulCfg is the Divider of Cclk, Pclk = Cclk/Divider.
//!             This value can be one of the following value:
//!             - \ref PCLK_CCLK_DIV_1
//!             - \ref PCLK_CCLK_DIV_2
//!             - \ref PCLK_CCLK_DIV_4
//!             - \ref PCLK_CCLK_DIV_6
//!             - \ref PCLK_CCLK_DIV_8
//!
//! \return     None.
//! \note       PCLK_CCLK_DIV_6 is only suit for CAN1, CAN2.
//!
//
//*****************************************************************************
void SysCtlPeripheralClockSourceSet(unsigned long ulPeri, unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    if(ulPeri < 32)
    {
        ulTmpReg = xHWREG(PCLKSEL0);
        ulTmpReg &= ~(PCLKSEL_PPP_M << ulPeri);
        ulTmpReg |= ulCfg << ulPeri;
        xHWREG(PCLKSEL0) = ulTmpReg;
    }
    else
    {
        ulPeri -= 32;
        ulTmpReg = xHWREG(PCLKSEL1);
        ulTmpReg &= ~(PCLKSEL_PPP_M << ulPeri);
        ulTmpReg |= ulCfg << ulPeri;
        xHWREG(PCLKSEL1) = ulTmpReg;
    }
}

//*****************************************************************************
//
//! \brief Get Peripheral Clock.
//!
//! \param [in] ulPeri is the LPC17nx(n=5/6) peripherals, the parameter can be
//!             logical OR of the following value:
//!             - \ref PCLKSEL_WDT
//!             - \ref PCLKSEL_TIMER0
//!             - \ref PCLKSEL_TIMER1
//!             - \ref PCLKSEL_UART0
//!             - \ref PCLKSEL_UART1
//!             - \ref PCLKSEL_PWM1
//!             - \ref PCLKSEL_I2C0
//!             - \ref PCLKSEL_SPI
//!             - \ref PCLKSEL_SSP1
//!             - \ref PCLKSEL_DAC
//!             - \ref PCLKSEL_ADC
//!             - \ref PCLKSEL_CAN1
//!             - \ref PCLKSEL_CAN2
//!             - \ref PCLKSEL_ACF
//!             - \ref PCLKSEL_QEI
//!             - \ref PCLKSEL_GPIOINT
//!             - \ref PCLKSEL_PCB
//!             - \ref PCLKSEL_I2C1
//!             - \ref PCLKSEL_SSP0
//!             - \ref PCLKSEL_TIMER2
//!             - \ref PCLKSEL_TIMER3
//!             - \ref PCLKSEL_UART2
//!             - \ref PCLKSEL_UART3
//!             - \ref PCLKSEL_I2C2
//!             - \ref PCLKSEL_I2S
//!             - \ref PCLKSEL_RIT
//!             - \ref PCLKSEL_SYSCON
//!             - \ref PCLKSEL_MC
//!
//! \return     None.
//! \note       PCLK_CCLK_DIV_6 is only suit for CAN1, CAN2.
//!
//
//*****************************************************************************
unsigned long SysCtlPeripheralClockGet(unsigned long ulPeri)
{
    unsigned long ulTmpReg = 0;
    unsigned long ulDiv    = 0;

    if(ulPeri < 32)
    {
        ulTmpReg = xHWREG(PCLKSEL0);
        if(ulPeri == 26 || ulPeri == 28) // CAN1 or CAN2
        {
            ulDiv = (ulTmpReg >> ulPeri) & 0x03;
            if(3 == ulDiv)
            {
                return (g_ulSystemClk/6);
            }
        }
    }
    else
    {
        ulPeri -= 32;
        ulTmpReg = xHWREG(PCLKSEL1);
    }

    ulDiv = (ulTmpReg >> ulPeri) & 0x03;

    switch(ulDiv)
    {
        case 0:                  // Div 4
            {
                return (g_ulSystemClk/4);
            }

        case 1:                  // Div 1
            {
                return (g_ulSystemClk/1);
            }

        case 2:                  // Div 2
            {
                return (g_ulSystemClk/2);
            }

        case 3:                  // Div 8
            {
                return (g_ulSystemClk/8);
            }
        default:                // Error
            {
                while(1);
            }
    }
}


//*****************************************************************************
//
//! \brief Reset MCU Periperal.
//!
//! \param [in] ulPeripheral is the LPC17nx(n=7/8) peripherals, the parameter
//!             can be one of the following value:
//!             - \ref SYSCTL_PERIPH_TIMER0
//!             - \ref SYSCTL_PERIPH_TIMER1
//!             - \ref SYSCTL_PERIPH_UART0
//!             - \ref SYSCTL_PERIPH_UART1
//!             - \ref SYSCTL_PERIPH_PWM0
//!             - \ref SYSCTL_PERIPH_PWM1
//!             - \ref SYSCTL_PERIPH_I2C0
//!             - \ref SYSCTL_PERIPH_SPI
//!             - \ref SYSCTL_PERIPH_RTC
//!             - \ref SYSCTL_PERIPH_SSP1
//!             - \ref SYSCTL_PERIPH_ADC
//!             - \ref SYSCTL_PERIPH_CAN1
//!             - \ref SYSCTL_PERIPH_CAN2
//!             - \ref SYSCTL_PERIPH_GPIOA
//!             - \ref SYSCTL_PERIPH_GPIOB
//!             - \ref SYSCTL_PERIPH_GPIOC
//!             - \ref SYSCTL_PERIPH_GPIOD
//!             - \ref SYSCTL_PERIPH_GPIOE
//!             - \ref SYSCTL_PERIPH_RIT
//!             - \ref SYSCTL_PERIPH_MCPWM
//!             - \ref SYSCTL_PERIPH_QEI
//!             - \ref SYSCTL_PERIPH_I2C1
//!             - \ref SYSCTL_PERIPH_SSP0
//!             - \ref SYSCTL_PERIPH_TIMER2
//!             - \ref SYSCTL_PERIPH_TIMER3
//!             - \ref SYSCTL_PERIPH_UART2
//!             - \ref SYSCTL_PERIPH_UART3
//!             - \ref SYSCTL_PERIPH_I2C2
//!             - \ref SYSCTL_PERIPH_UART4
//!             - \ref SYSCTL_PERIPH_I2S
//!             - \ref SYSCTL_PERIPH_GPDMA
//!             - \ref SYSCTL_PERIPH_ETH
//!             - \ref SYSCTL_PERIPH_USB
//!
//! \return     None.
//!
//! \note       This function is only suit for LPC177x or LPC178x.
//
//*****************************************************************************
void SysCtlPeripheralReset(unsigned long ulPeripheral)
{
    // Note: Not for LPC 17nx (n=5/6)

#if defined(LPC_175x) | defined(LPC_176x)
    // Nothing
    (void) ulPeripheral;
#elif defined(LPC_177x) | defined(LPC_178x)

    unsigned long ulTmpReg = 0;
    if(ulPeripheral < 32)    // Reset register 0
    {
        // Reset Peripheral by write 1 to respond bit.
        ulTmpReg = xHWREG(RSTCON0);
        ulTmpReg |= ulPeripheral;
        xHWREG(RSTCON0) = ulTmpReg;

        // Restore reset bit
        ulTmpReg = xHWREG(RSTCON0);
        ulTmpReg &= ~ulPeripheral;
        xHWREG(RSTCON0) = ulTmpReg;
    }
    else                     // Reset register 1
    {
        ulPeripheral -= 1;

        // Reset Peripheral by write 1 to respond bit.
        ulTmpReg = xHWREG(RSTCON1);
        ulTmpReg |= ulPeripheral;
        xHWREG(RSTCON1) = ulTmpReg;

        // Restore reset bit
        ulTmpReg = xHWREG(RSTCON1);
        ulTmpReg &= ~ulPeripheral;
        xHWREG(RSTCON1) = ulTmpReg;
    }
#endif
}

//*****************************************************************************
//
//! \brief Enable MCU Periperal.
//!
//! \param [in] ulPeripheral is the LPC17nx(n=5/6/7/8) peripherals, the parameter
//!             can be one of the following value:
//!             - \ref SYSCTL_PERIPH_TIMER0
//!             - \ref SYSCTL_PERIPH_TIMER1
//!             - \ref SYSCTL_PERIPH_UART0
//!             - \ref SYSCTL_PERIPH_UART1
//!             - \ref SYSCTL_PERIPH_PWM1
//!             - \ref SYSCTL_PERIPH_I2C0
//!             - \ref SYSCTL_PERIPH_SPI
//!             - \ref SYSCTL_PERIPH_RTC
//!             - \ref SYSCTL_PERIPH_SSP1
//!             - \ref SYSCTL_PERIPH_ADC
//!             - \ref SYSCTL_PERIPH_CAN1
//!             - \ref SYSCTL_PERIPH_CAN2
//!             - \ref SYSCTL_PERIPH_GPIOA
//!             - \ref SYSCTL_PERIPH_GPIOB
//!             - \ref SYSCTL_PERIPH_GPIOC
//!             - \ref SYSCTL_PERIPH_GPIOD
//!             - \ref SYSCTL_PERIPH_GPIOE
//!             - \ref SYSCTL_PERIPH_RIT
//!             - \ref SYSCTL_PERIPH_MCPWM
//!             - \ref SYSCTL_PERIPH_QEI
//!             - \ref SYSCTL_PERIPH_I2C1
//!             - \ref SYSCTL_PERIPH_SSP0
//!             - \ref SYSCTL_PERIPH_TIMER2
//!             - \ref SYSCTL_PERIPH_TIMER3
//!             - \ref SYSCTL_PERIPH_UART2
//!             - \ref SYSCTL_PERIPH_UART3
//!             - \ref SYSCTL_PERIPH_I2C2
//!             - \ref SYSCTL_PERIPH_I2S
//!             - \ref SYSCTL_PERIPH_GPDMA
//!             - \ref SYSCTL_PERIPH_ETH
//!             - \ref SYSCTL_PERIPH_USB
//!
//! \return     None.
//!
//
//*****************************************************************************
void SysCtlPeripheralEnable(unsigned long ulPeripheral)
{
    if(ulPeripheral >= 32)           // GPIOx (x=A/B/C/D/E)
    {
        ulPeripheral = 15;
    }
    xHWREG(PCONP) |= ((unsigned long)0x01 << ulPeripheral);
}

//*****************************************************************************
//
//! \brief Disable MCU Periperal.
//!
//! \param [in] ulPeripheral is the LPC17nx(n=5/6/7/8) peripherals, the parameter
//!             can be one of the following value:
//!             - \ref SYSCTL_PERIPH_TIMER0
//!             - \ref SYSCTL_PERIPH_TIMER1
//!             - \ref SYSCTL_PERIPH_UART0
//!             - \ref SYSCTL_PERIPH_UART1
//!             - \ref SYSCTL_PERIPH_PWM1
//!             - \ref SYSCTL_PERIPH_I2C0
//!             - \ref SYSCTL_PERIPH_SPI
//!             - \ref SYSCTL_PERIPH_RTC
//!             - \ref SYSCTL_PERIPH_SSP1
//!             - \ref SYSCTL_PERIPH_ADC
//!             - \ref SYSCTL_PERIPH_CAN1
//!             - \ref SYSCTL_PERIPH_CAN2
//!             - \ref SYSCTL_PERIPH_GPIOA
//!             - \ref SYSCTL_PERIPH_GPIOB
//!             - \ref SYSCTL_PERIPH_GPIOC
//!             - \ref SYSCTL_PERIPH_GPIOD
//!             - \ref SYSCTL_PERIPH_GPIOE
//!             - \ref SYSCTL_PERIPH_RIT
//!             - \ref SYSCTL_PERIPH_MCPWM
//!             - \ref SYSCTL_PERIPH_QEI
//!             - \ref SYSCTL_PERIPH_I2C1
//!             - \ref SYSCTL_PERIPH_SSP0
//!             - \ref SYSCTL_PERIPH_TIMER2
//!             - \ref SYSCTL_PERIPH_TIMER3
//!             - \ref SYSCTL_PERIPH_UART2
//!             - \ref SYSCTL_PERIPH_UART3
//!             - \ref SYSCTL_PERIPH_I2C2
//!             - \ref SYSCTL_PERIPH_I2S
//!             - \ref SYSCTL_PERIPH_GPDMA
//!             - \ref SYSCTL_PERIPH_ETH
//!             - \ref SYSCTL_PERIPH_USB
//!
//! \return     None
//
//*****************************************************************************
void SysCtlPeripheralDisable(unsigned long ulPeripheral)
{

    if(ulPeripheral >= 32)           // GPIOx (x=A/B/C/D/E)
    {
        ulPeripheral = 15;
    }
    xHWREG(PCONP) &= ~((unsigned long)0x01 << ulPeripheral);
}

//*****************************************************************************
//
//! \brief      Reset a peripheral by base address.
//!
//!             Peripherals are Reset with this function.  At power-up, all
//!             peripherals are disabled; they must be enabled in order to operate
//!             or respond to register reads/writes.
//!
//! \param [in] ulPeripheralBase a Peripheral base indicate which peripheral to be
//!             enabled. it must be one of the following value:
//!             - \ref ETH_BASE
//!             - \ref DMA0_BASE
//!             - \ref USB_BASE
//!             - \ref GPIO_PORTA_BASE
//!             ...
//!             More information, please refer to
//!                                     \ref LPC17xx_LowLayer_Peripheral_Memmap.
//!
//! \return     None.
//! \note       This function not suit for LPC17_5x or LPC17_6x
//
//*****************************************************************************
void SysCtlPeripheralReset2(unsigned long ulPeripheralBase)
{
    unsigned long i = 0;
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralReset(g_pPeripherals[i].ulPeripheralID);
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief      Enables a peripheral by base address.
//!
//!             Peripherals are enabled with this function.  At power-up, all
//!             peripherals are disabled; they must be enabled in order to operate
//!             or respond to register reads/writes.
//!
//! \param [in] ulPeripheralBase a Peripheral base indicate which peripheral to be
//!             enabled. it must be one of the following value:
//!             - \ref ETH_BASE
//!             - \ref DMA0_BASE
//!             - \ref USB_BASE
//!             - \ref GPIO_PORTA_BASE
//!             ...
//!             More information, please refer to
//!                                     \ref LPC17xx_LowLayer_Peripheral_Memmap.
//!
//! \return     None.
//
//*****************************************************************************
void SysCtlPeripheralEnable2(unsigned long ulPeripheralBase)
{
    unsigned long i = 0;

    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralEnable(g_pPeripherals[i].ulPeripheralID);
            return ;
        }
    }
}

//*****************************************************************************
//
//! \brief      Disables a peripheral by base address.
//!
//!             Peripherals are Disabled with this function.  At power-up, all
//!             peripherals are disabled; they must be enabled in order to operate
//!             or respond to register reads/writes.
//!
//! \param [in] ulPeripheralBase a Peripheral base indicate which peripheral to be
//!             enabled. it must be one of the following value:
//!             - \ref ETH_BASE
//!             - \ref DMA0_BASE
//!             - \ref USB_BASE
//!             - \ref GPIO_PORTA_BASE
//!             ...
//!             More information, please refer to \ref LPC17xx_LowLayer_Peripheral_Memmap.
//!
//! \return     None.
//
//*****************************************************************************
void SysCtlPeripheralDisable2(unsigned long ulPeripheralBase)
{
    unsigned long i = 0;
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralDisable(g_pPeripherals[i].ulPeripheralID);
            return ;
        }
    }
}

//*****************************************************************************
//
//! \brief      Get the peripheral interrupt number through peripheral base.
//!
//! \param [in] ulPeripheral The peripheral's base
//!
//! \return     None.
//! \note       It's especially useful to enable the short pin's corresponding
//!             peripheral interrupt: Use the short pin to Get the GPIO base
//!             through \ref xGPIOSPinToPort function, and then use this function
//!             to enable the GPIO interrupt.
//!
//
//*****************************************************************************
unsigned long SysCtlPeripheraIntNumGet(unsigned long ulPeripheralBase)
{
    unsigned long i = 0;

    //
    // Check the arguments.
    //

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
//! \brief  Get System Clock frequency.
//!
//! \param  None.
//!
//! \return Return the System clock frequency.
//!
//
//*****************************************************************************
unsigned long SysCtlClockGet(void)
{
    //return (g_ulSystemClk);
    unsigned long ulM, ulP, ulDiv;
    unsigned long ulTmpReg = xHWREG(PLL0CFG);
    ulM = (ulTmpReg & 0x1F) + 1;
    ulP = ((ulTmpReg & PLL0CFG_PSEL_M) >> PLL0CFG_PSEL_S) + 1;
    ulDiv = xHWREG(CCLKSEL) & 0x1F;
    return ((s_ulExtClockMHz * ulM) / (ulP * ulDiv));
  //return (s_ulExtClockMHz * ((ulTmpReg & 0x1F) + 1) / ((((ulTmpReg&PLL0CFG_PSEL_M)>>PLL0CFG_PSEL_S)+1) * (xHWREG(CCLKSEL) & 0x1F)));
}

//*****************************************************************************
//
//! \brief  Get AHB Clock frequency.
//!
//! \param  None.
//!
//! \return Return the AHB clock frequency.
//!
//
//*****************************************************************************
unsigned long SysCtlHClockGet(void)
{
    return (g_ulAHBClk);
}

//*****************************************************************************
//
//! \brief  Get APB1 Clock frequency.
//!
//! \param  None.
//!
//! \return Return the APB1 clock frequency.
//!
//! \note   This APB1 Clock is set by Systen Initialize function.
//!         Default: APB1 = APB2 = AHB/4.
//
//*****************************************************************************
//unsigned long SysCtlAPB1ClockGet(void)
//{
//    return (g_ulAPB1Clk);
//}

//*****************************************************************************
//
//! \brief  Get APB2 Clock frequency.
//!
//! \param  None.
//!
//! \return Return the APB2 clock frequency.
//!
//! \note   This APB2 Clock is set by Systen Initialize function.
//!         Default: APB1 = APB2 = AHB/4.
//
//*****************************************************************************
//unsigned long SysCtlAPB2ClockGet(void)
//{
//    return (g_ulAPB2Clk);
//}

//*****************************************************************************
//
//! \brief Configure MCU Power Mode.
//!
//! \param [in] ulMode is the power mode of LPC17xx, this value can be one of
//!             the following value:
//!             - \ref PWR_MODE_SLEEP     Set Mcu into Sleep mode.
//!             - \ref PWR_MODE_SLEEP_D   Set Mcu into Deep Sleep mode.
//!             - \ref PWR_MODE_PWRDOWN   Set Mcu into Powerdown mode.
//!             - \ref PWR_MODE_PWRDOWN_D Set Mcu into Deep Powerdown mode.
//!
//! \return     the result of operation, can be one of the following value:
//!             - 0 success
//!             - 1 failure cause by incorrect input parameter.
//! \note
//!             -# Any enabled interrupt can wake up the CPU from Sleep mode.
//!             Certain interrupts can wake up the processor if it is in either
//!             Deep Sleep mode or Power-down mode.
//!
//!             -# Interrupts that can occur during Deep Sleep or Power-down mode will
//!             wake up the CPU if the interrupt is enabled. After wake-up, execution
//!             will continue to the appropriate interrupt service routine.
//!             These interrupts are NMI, External Interrupts EINT0 through EINT3,
//!             GPIO interrupts, Ethernet Wake-on-LAN interrupt, Brownout Detect,
//!             RTC Alarm, CAN Activity Interrupt, and USB Activity Interrupt.
//!             In addition, the watchdog timer can wake up the part from Deep Sleep
//!             mode if the watchdog timer is being clocked by the IRC oscillator.
//!             For the wake-up process to take place the corresponding interrupt must
//!             be enabled in the NVIC. For pin-related peripheral functions,
//!             the related functions must also be mapped to pins.
//!
//!             -# In Deep Power-down mode, internal power to most of the device is
//!             removed, which limits the possibilities for waking up from this mode.
//!             Wake-up from Deep Power-down mode will occur when an external reset
//!             signal is applied, or the RTC interrupt is enabled and an RTC interrupt
//!             is generated.
//!
//! \bug        -# Once you put mcu input DeepSleep or DeepPowerDown mode, mcu clock
//!             is reset to default, that to say, PLL is disconnect and disable,
//!             IRC is used as the main clock source.
//!             However, you can't use SysCtlClockSet to reconfigure PLL.
//!             This problem will be solved in the later.
//!
//*****************************************************************************
unsigned long SysCtlPwrCfg(unsigned long ulMode)
{

    // Check input parameters valid.
    xASSERT((ulMode == PWR_MODE_SLEEP    ) ||
            (ulMode == PWR_MODE_SLEEP_D  ) ||
            (ulMode == PWR_MODE_PWRDOWN  ) ||
            (ulMode == PWR_MODE_PWRDOWN_D) );

    switch(ulMode)
    {
        case PWR_MODE_SLEEP:           // Sleep Mode
            {
                xHWREG(PCON)          = (unsigned long)0x00;
                xHWREG(NVIC_SYS_CTRL) = (unsigned long)0x00;
                xCPUwfi();
                return (0);
            }
        case PWR_MODE_SLEEP_D:        // Deep Sleep Mode
            {
                xHWREG(PCON)          = (unsigned long)0x00;
                xHWREG(NVIC_SYS_CTRL) = (unsigned long)0x04;
                xCPUwfi();
                return (0);
            }
        case PWR_MODE_PWRDOWN:        // Power Down Mode
            {
                xHWREG(PCON)          = (unsigned long)0x01;
                xHWREG(NVIC_SYS_CTRL) = (unsigned long)0x04;
                xCPUwfi();
                return (0);
            }
        case PWR_MODE_PWRDOWN_D:      // Deep Power Down Mode
            {
                xHWREG(PCON)          = (unsigned long)0x03;
                xHWREG(NVIC_SYS_CTRL) = (unsigned long)0x04;
                xCPUwfi();
                return (0);
            }
        default:
            {
                return (1);           // Error
            }
    }
}

//*****************************************************************************
//
//! \brief Check Power-Manager Status.
//!
//! \param [in] ulCfg is Power-Manager Configure input parameter, this parameter is
//!             the logical OR of several different values:
//!             - \ref PWR_MODE_SLEEP       Sleep Flag
//!             - \ref PWR_MODE_SLEEP_D     Deep Sleep Flag
//!             - \ref PWR_MODE_PWRDOWN     Power Down Flag
//!             - \ref PWR_MODE_PWRDOWN_D   Deep Power Down Flag
//!
//! \return     Return the status of Special Flag.
//!             - xtrue  Flag that check has been set.
//!             - xfalse Flag that check has NOT been set.
//!
//*****************************************************************************
xtBoolean SysCtlPwrFlagCheck(unsigned long ulFlag)
{
    // Check input parameters valid.
    xASSERT( ulFlag & (PWR_MODE_SLEEP   | PWR_MODE_SLEEP_D   |
                      PWR_MODE_PWRDOWN | PWR_MODE_PWRDOWN_D ));

    ulFlag = (ulFlag >> 8 ) & BIT_MASK(32, 3, 0);
    if(xHWREG(PCON) & ulFlag)
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
//! \brief Clear Power-Manager status Flag.
//!
//! \param [in] ulCfg is Brown-out Configure input parameter, this parameter is
//!             the logical OR of several different values:
//!             - \ref PWR_MODE_SLEEP       Sleep Flag
//!             - \ref PWR_MODE_SLEEP_D     Deep Sleep Flag
//!             - \ref PWR_MODE_PWRDOWN     Power Down Flag
//!             - \ref PWR_MODE_PWRDOWN_D   Deep Power Down Flag
//!
//! \return     None.
//!
//
//*****************************************************************************
void SysCtlPwrFlagClear(unsigned long ulFlag)
{
    // Check input parameters valid.
    xASSERT( ulFlag & (PWR_MODE_SLEEP   | PWR_MODE_SLEEP_D   |
                      PWR_MODE_PWRDOWN | PWR_MODE_PWRDOWN_D ));

    ulFlag = (ulFlag >> 8 ) & BIT_MASK(32, 3, 0);
    xHWREG(PCON) |= ulFlag;
}

//*****************************************************************************
//
//! \brief Configure Brown-out module.
//!
//! \param [in] ulCfg is Brown-out Configure input parameter, this parameter is
//!             the logical OR of several different values:
//!             - \ref BOD_REDUCE_PWR_EN   The Brown-Out Detect function remains active
//!                                   during Power-down and Deep Sleep modes.
//!
//!             - \ref BOD_REDUCE_PWR_DIS  The Brown-Out Detect circuitry will be turned
//!                                   off when chip Power-down mode or Deep Sleep mode
//!                                   is entered, resulting in a further reduction
//!                                   in power usage. However, the possibility of
//!                                   using Brown-Out Detect as a wake-up source
//!                                   from the reduced power mode will be lost.
//!
//!             - \ref BOD_GLOBAL_EN       The Brown-Out Detect circuitry is enabled.
//!
//!             - \ref BOD_GLOBAL_DIS      The Brown-Out Detect circuitry is fully
//!                                   disabled at all times, and does not consume
//!                                   power.
//!
//!             - \ref BOD_RESET_EN        Enable Brown-out reset function.
//!             - \ref BOD_RESET_DIS       Disable Brown-out reset function.
//!
//! \return     None.
//! \note       When you call this function with one group parameter, e.g.
//!             SysCtlBODCfg(BOD_GLOBAL_EN | BOD_GLOBAL_DIS)
//!             it equals to
//!             SysCtlBODCfg(BOD_GLOBAL_DIS).
//!
//*****************************************************************************
void SysCtlBODCfg(unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;
    unsigned long ulTmp    = 0;

    xASSERT( ulCfg & (BOD_REDUCE_PWR_EN   | BOD_REDUCE_PWR_DIS |
                       BOD_GLOBAL_EN      | BOD_GLOBAL_DIS     |
                       BOD_RESET_EN       | BOD_RESET_DIS      ));

    ulTmpReg = xHWREG(PCON);
    ulTmp    = ( ulCfg & BIT_MASK(32, 31, 16) ) >> 16;
    ulTmpReg &= ~(ulTmp);
    ulTmpReg |= ulCfg & BIT_MASK(32, 15, 0);
    xHWREG(PCON) = ulTmpReg;
}

//*****************************************************************************
//
//! \brief  Resets the device.
//!
//!         This function will perform a software reset of the entire device.
//!         The processor and all peripherals will be reset and all device
//!         registers will return to their default values (with the exception of
//!         the reset cause register, which will maintain its current value but
//!         have the software reset bit set as well).
//!
//! \return None.
//
//*****************************************************************************
void SysCtlReset(void)
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
//! \brief  Configure MCO function.
//!
//! \param [in] ulCfg can be used to configure MCO Clock source and Clock divider.
//!             The value can be divided into two groups:
//!             -# Clock Source Select
//!                This value can be one of the following value:
//!                - \ref MCO_CLKSRC_CPU
//!                - \ref MCO_CLKSRC_MAIN_OSC
//!                - \ref MCO_CLKSRC_IRC
//!                - \ref MCO_CLKSRC_USB
//!                - \ref MCO_CLKSRC_RTC
//!
//!             -# Clock Source Divider
//!                This value can be one of the following value:
//!                - \ref MCO_CLKDIV_1
//!                - \ref MCO_CLKDIV_2
//!                  ...
//!                - \ref MCO_CLKDIV_16
//!
//! \return None.
//!
//! \note   \ref MCO_CLKSRC_CPU and \ref MCO_CLKDIV_1 is default parameter.
//!         That's to say, when you call this function with only one parameter,
//!         then default parameter is used as another input parameter.
//!
//!         e.g. 1
//!               SysCtlMCOCfg(MCO_CLKSRC_IRC)
//!         is equal to
//!             SysCtlMCOCfg(MCO_CLKSRC_IRC, MCO_CLKDIV_1)
//!
//!         e.g. 2
//!               SysCtlMCOCfg(MCO_CLKDIV_4)
//!         is equal to
//!             SysCtlMCOCfg(MCO_CLKSRC_CPU, MCO_CLKDIV_4)
//
//*****************************************************************************
void SysCtlMCOCfg(unsigned long ulCfg)
{
    // Check input parameter
    xASSERT((ulCfg & BIT_MASK(32, 31, 8)) == 0);

    xHWREG(CLKOUTCFG) = ulCfg;
}

//*****************************************************************************
//
//! \brief  Enable MCO Clock Output.
//!
//! \return None.
//!
//! \note   Before you call \ref SysCtlMCOEnable or \ref SysCtlMCODisable, you
//!         MUST call \ref SysCtlMCOCfg to configure MCO clock source and clock
//!         divider.
//
//*****************************************************************************
void SysCtlMCOEnable(void)
{
    xHWREG(CLKOUTCFG) |= CLKOUTCFG_CLKOUT_EN;
}

//*****************************************************************************
//
//! \brief  Disable MCO Clock Output.
//!
//! \return None.
//!
//! \note   Before you call \ref SysCtlMCOEnable or \ref SysCtlMCODisable, you
//!         MUST call \ref SysCtlMCOCfg to configure MCO clock source and clock
//!         divider.
//
//*****************************************************************************
void SysCtlMCODisable(void)
{
    xHWREG(CLKOUTCFG) &= ~CLKOUTCFG_CLKOUT_EN;
}

//*****************************************************************************
//
//! \brief  Disable MCO Clock Output.
//!
//! \return the MCO activity indication.
//!         - xtrue  when CLKOUT is enabled.
//!         - xfalse when CLKOUT has been disabled via the CLKOUT_EN bit and
//!                  the clock has completed being stopped.
//!
//! \note   Before you call \ref SysCtlMCOStatusGet, you MUST call
//!         \ref SysCtlMCOCfg to configure MCO clock source and clock divider.
//
//*****************************************************************************
xtBoolean SysCtlMCOStatusGet(void)
{
    if (xHWREG(CLKOUTCFG) & CLKOUTCFG_CLKOUT_ACT)
    {
        return (xtrue);
    }
    else
    {
        return (xfalse);
    }

}

