//*****************************************************************************
//
//! \file sysctl.h
//! \brief Prototypes for the System Manager Driver.
//! Prototypes for the Clock Controller Driver.
//! \version V2.1.1.0
//! \date 12/26/2011
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

#ifndef __SYSCTL_H__
#define __SYSCTL_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Peripheral_ID M051 SysCtl Peripheral ID
//! \brief Values that can be passed to the SysCtlPeripheralEnable(),
//! SysCtlPeripheralDisable(), and SysCtlPeripheralReset().
//! @{
//
//*****************************************************************************

//
//! ISP No reset
//
#define SYSCTL_PERIPH_ISP       0x00000004  

//
//! WDT No reset
//
#define SYSCTL_PERIPH_WDT       0x00004001 

//
//! GPIO No enable
//
#define SYSCTL_PERIPH_GPIO      0x70020000  

//
//! TMR0
//
#define SYSCTL_PERIPH_TMR0      0x70044004  

//
//! TMR1
//
#define SYSCTL_PERIPH_TMR1      0x70084008  

//
//! TMR2
//
#define SYSCTL_PERIPH_TMR2      0x70104010  

//
//! TMR3
//
#define SYSCTL_PERIPH_TMR3      0x70204020  

//
//! FDIV No reset
//
#define SYSCTL_PERIPH_FDIV      0x00004040 

//
//! I2C0
//
#define SYSCTL_PERIPH_I2C0      0x68014801

//
//! I2C1
//
#define SYSCTL_PERIPH_I2C1      0x68024802

//
//! SPI0
//
#define SYSCTL_PERIPH_SPI0      0x68104810 

//
//! SPI1
//
#define SYSCTL_PERIPH_SPI1      0x68204820  

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x40015001

//
//! UART1
//
#define SYSCTL_PERIPH_UART1     0x40025002

//
//! PWM01
//
#define SYSCTL_PERIPH_PWM01     0x40105010  

//
//! PWM23
//
#define SYSCTL_PERIPH_PWM23     0x40105020  

//
//! PWM45
//
#define SYSCTL_PERIPH_PWM45     0x40205040  

//
//! PWM67
//
#define SYSCTL_PERIPH_PWM67     0x40205080

//
//! ADC
//
#define SYSCTL_PERIPH_ADC       0x48105810

//
//! ACMP01
//
#define SYSCTL_PERIPH_ACMP01    0x40405840

//
//! ACMP23
//
#define SYSCTL_PERIPH_ACMP23    0x40805880

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Peripheral_Src_Clk SysCtl Peripheral Clock Source
//! \brief The following are values that can be passed to the
//! SysCtlPeripheralClockSourceSet()  API as the ulPeripheralsrc parameter.  
//! @{
//
//*****************************************************************************

//
//! Watch dog 00 = Clock source from external crystal clock.(4 ~ 24MHz)
//
#define SYSCTL_PERIPH_WDG_EXTSL 0x00000300 

//
//! Watch dog clock source is HCLK/2048 clock
//
#define SYSCTL_PERIPH_WDG_S_HCLK_2048                                         \
                                0x00000302     
                                
//
//! Watch dog clock source is internal 10 kHz oscillator clock
//
#define SYSCTL_PERIPH_WDG_S_INT10K                                            \
                                0x00000303
                                
//
//! ADC clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_ADC_S_EXT12M                                            \
                                0x00020300  
                                
//
//! ADC clock source is PLL clock
//
#define SYSCTL_PERIPH_ADC_S_PLL                                               \
                                0x00020301

//
//! ADC clock source is HCLK
//
#define SYSCTL_PERIPH_ADC_S_HCLK                                              \
                                0x00020302 
                                
//
//! ADC clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_ADC_S_INT22M                                            \
                                0x00020303  
                                
//
//! Timer0 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR0_S_EXT12M                                           \
                                0x00080700  
//
//! Timer0 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR0_S_HCLK                                             \
                                0x00080702   
                                
//
//! Timer0 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR0_S_INT22M                                           \
                                0x00080707  
                                
//
//! Timer1 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_EXT12M                                           \
                                0x000C0700 
                                
//
//! Timer1 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR1_S_HCLK                                             \
                                0x000C0702    
                                
//
//! Timer1 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR1_S_INT22M                                           \
                                0x000C0707  
                                
//
//! Timer2 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR2_S_EXT12M                                           \
                                0x00100700   
                                
//
//! Timer2 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR2_S_HCLK                                             \
                                0x00100702  
                                
//
//! Timer2 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR2_S_INT22M                                           \
                                0x00100707
                                
//
//! Timer3 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR3_S_EXT12M                                           \
                                0x00140700   
                                
//
//! Timer3 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR3_S_HCLK                                             \
                                0x00140702    
                                
//
//! Timer3 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR3_S_INT22M                                           \
                                0x00140707  
                                
//
//! UART clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_UART_S_EXT12M                                           \
                                0x00180300  
                                
//
//! UART clock source is PLL clock
//
#define SYSCTL_PERIPH_UART_S_PLL                                              \
                                0x00180301  
                                
//
//! UART clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_UART_S_INT22M                                           \
                                0x00180303  
                                
//
//! PWM0 and PWM1 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM01_S_EXT12M                                          \
                                0x001C0300 
                                
//
//! PWM0 and PWM1 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM01_S_HCLK                                            \
                                0x001C0302   
                                
//
//! PWM0 and PWM1 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM01_S_INT22M                                          \
                                0x001C0303  
                                
//
//! PWM2 and PWM3 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM23_S_EXT12M                                          \
                                0x001E0300  
                                
//
//! PWM2 and PWM3 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM23_S_HCLK                                            \
                                0x001E0302  
                                
//
//! PWM2 and PWM3 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM23_S_INT22M                                          \
                                0x001E0303
                                
//
//! frequency divide source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_FRQDIV_S_EXT12M                                         \
                                0x10020300
                                
//
//! frequency divide source is HCLK
//
#define SYSCTL_PERIPH_FRQDIV_S_HCLK                                           \
                                0x10020302          
                                
//
//! frequency divide source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_FRQDIV_S_INT22M                                         \
                                0x10020303  
                                
//
//! PWM4 and PWM5 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM45_S_EXT12M                                          \
                                0x10040300
                                
//
//! PWM4 and PWM5 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM45_S_HCLK                                            \
                                0x10040302       
                                
//
//! PWM4 and PWM5 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM45_S_INT22M                                          \
                                0x10040303  
                                
//
//! PWM6 and PWM7 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM67_S_EXT12M                                          \
                                0x10060300
                                
//
//! PWM6 and PWM7 clock source is HCLK 
//
#define SYSCTL_PERIPH_PWM67_S_HCLK                                            \
                                0x10060302   
                                
//
//! PWM6 and PWM7 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM67_S_INT22M                                          \
                                0x10060303  
                             
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Hclk_Src M051 SysCtl Hclk Source
//! \brief The following are values that can be passed to the
//! SysCtlHClockSourceSet()\ SysCtlHClockSet API as the ulhclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Hclk source is external 12 MHz crystal clock
//
#define SYSCTL_HLCK_S_EXT12M    0x00000000

//
//! Hclk source is PLL clock
//
#define SYSCTL_HLCK_S_PLL       0x00000002  

//
//! Hclk source is internal 10 kHz oscillator clock
//
#define SYSCTL_HLCK_S_INT10K    0x00000003  

//
//! Hclk source is internal 22 MHz oscillator clock
//
#define SYSCTL_HLCK_S_INT22M    0x00000007  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Stclk_Src M051 SysCtl Stick Source
//! \brief The following are values that can be passed to the
//! SysCtlSysTickSourceSet()  API as the ulstclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is external 12 MHz crystal clock
//
#define SYSCTL_STCLK_S_EXT12M   0x00000000

//
//! Systick Clock source is 12 MHz crystal clock/2
//
#define SYSCTL_STCLK_S_EXT12M_2 0x00000010  

//
//! Systick Clock source is HCLK/2
//
#define SYSCTL_STCLK_S_HCLK_2   0x00000018  

//
//! Systick Clock source is internal 22 MHz oscillator clock/2
//
#define SYSCTL_STCLK_S_INT22M_2 0x00000038  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Reset_Src M051 SysCtl Reset Source
//! \brief The following are values that can be returned in the bit mask by the 
//! SysCtlResetSrcGet() API.   
//! @{
//
//*****************************************************************************

//
//! "reset signal" from Power-On Reset
//
#define SYSCTL_RSTSRC_POR       0x00000001  

//
//! "reset signal" from the /RESET pin
//
#define SYSCTL_RSTSRC_PAD       0x00000002 

//
//! "reset signal" from the Watch-Dog
//
#define SYSCTL_RSTSRC_WDG       0x00000004  

//
//! "reset signal" from Low-Voltage-Reset
//
#define SYSCTL_RSTSRC_LVR       0x00000008  

//
//! "reset signal" from Brown-Out-Detected
//
#define SYSCTL_RSTSRC_BOD       0x00000010  

//
//! "reset signal" from MCU Cortex_M0 kernel
//
#define SYSCTL_RSTSRC_SYS       0x00000020  

//
//! "reset signal" from CPU_RST (IPRSTCR1[1])
//
#define SYSCTL_RSTSRC_CPU       0x00000080  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Bod_level M051 SysCt Bod level
//! \brief The following are values that can be passed to the
//! SysCtlSelectBODVolt()  API as the ulVoltage parameter.  
//! @{
//
//*****************************************************************************

//
//! Threshold Voltage 2.2V
//
#define SYSCTL_BOD_2_2          0x00000000  

//
//! Threshold Voltage 2.7V
//
#define SYSCTL_BOD_2_7          0x00000002  

//
//! Threshold Voltage 3.7V
//
#define SYSCTL_BOD_3_7          0x00000004  

//
//! Threshold Voltage 4.3V
//
#define SYSCTL_BOD_4_3          0x00000006  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Peripheral_ClkDiv M051 SysCtl Peripheral ClkDiv
//! \brief The following are values that can be passed to the
//! SysCtlIPClockDividerSet()  API as the ulConfig parameter. 
//! @{
//
//*****************************************************************************

//
//! HCLK clock divide number mask
// 
#define SYSCTL_PERIPH_HCLK_D    0x00000000

//
//! UART clock divide number mask
//
#define SYSCTL_PERIPH_UART_D    0x00080800

//
//! ADC clock divide number mask
//
#define SYSCTL_PERIPH_ADC_D     0x00101000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Clock_Config M051 SysCtl Clock Configuration
//! \brief The following are values that can be passed to the SysCtlClockSet() 
//! API as the ulConfig parameter.
//! @{
//
//*****************************************************************************

//
//! Processor clock is osc/pll /1
//
#define SYSCTL_SYSDIV_1         0x00000000  

//
//! Processor clock is osc/pll /2
//
#define SYSCTL_SYSDIV_2         0x01000000  

//
//! Processor clock is osc/pll /3
//
#define SYSCTL_SYSDIV_3         0x02000000  

//
//! Processor clock is osc/pll /4
//
#define SYSCTL_SYSDIV_4         0x03000000  

//
//! Processor clock is osc/pll /5
//
#define SYSCTL_SYSDIV_5         0x04000000  

//
//! Processor clock is osc/pll /6
//
#define SYSCTL_SYSDIV_6         0x05000000  

//
//! Processor clock is osc/pll /7
//
#define SYSCTL_SYSDIV_7         0x06000000  

//
//! Processor clock is osc/pll /8
//
#define SYSCTL_SYSDIV_8         0x07000000  

//
//! Processor clock is osc/pll /9
//
#define SYSCTL_SYSDIV_9         0x08000000  

//
//! Processor clock is osc/pll /10
//
#define SYSCTL_SYSDIV_10        0x09000000  

//
//! Processor clock is osc/pll /11
//
#define SYSCTL_SYSDIV_11        0x0A000000  

//
//! Processor clock is osc/pll /12
//
#define SYSCTL_SYSDIV_12        0x0B000000  

//
//! Processor clock is osc/pll /13
//
#define SYSCTL_SYSDIV_13        0x0C000000  

//
//! Processor clock is osc/pll /14
//
#define SYSCTL_SYSDIV_14        0x0D000000  

//
//! Processor clock is osc/pll /15
//
#define SYSCTL_SYSDIV_15        0x0E000000  

//
//! Processor clock is osc/pll /16
//
#define SYSCTL_SYSDIV_16        0x0F000000  

//
//! Disable internal oscillator
//
#define SYSCTL_INT_OSC_DIS      0x00000004  

//
//! Disable main oscillator
//
#define SYSCTL_MAIN_OSC_DIS     0x00000001  

//
//! Disable PLL
//
#define SYSCTL_PLL_PWRDN        0x00010000  

//
//! HCLK source is main osc
//
#define SYSCTL_OSC_MAIN         0x00000000  

//
//! HCLK source is ext. 32 KHz
//
#define SYSCTL_OSC_EXTSL        0x00000010  

//
//! HCLK source is PLL
//
#define SYSCTL_OSC_PLL          0x00000020  

//
//! HCLK source is int. osc
//
#define SYSCTL_OSC_INT          0x00000040  

//
//! HCLK source is int. 10 KHz
//
#define SYSCTL_OSC_INTSL        0x00000030  

//
//! Oscillator Source
//
#define SYSCTL_OSCSRC_M         0x00080070 

//
//! PLL source is int. 12 MHz
//
#define SYSCTL_PLL_MAIN         0x00000000  

//
//! PLL source is int. 22 MHz
//
#define SYSCTL_PLL_INT          0x00080000  

//
//! External main clock crystal mask.
//
#define SYSCTL_XTAL_MASK        0x0000FF00  

//
//! External main clock crystal is 4MHz.
//
#define SYSCTL_XTAL_4MHZ        0x00000400  

//
//! External main clock crystal is 5MHz.
//
#define SYSCTL_XTAL_5MHZ        0x00000500  

//
//! External main clock crystal is 6MHz.
//
#define SYSCTL_XTAL_6MHZ        0x00000600  

//
//! External main clock crystal is 7MHz.
//
#define SYSCTL_XTAL_7MHZ        0x00000700  

//
//! External main clock crystal is 8MHz.
//
#define SYSCTL_XTAL_8MHZ        0x00000800  

//
//! External main clock crystal is 9MHz.
//
#define SYSCTL_XTAL_9MHZ        0x00000900  

//
//! External main clock crystal is 10MHz.
//
#define SYSCTL_XTAL_10MHZ       0x00000A00  

//
//! External main clock crystal is 11MHz.
//
#define SYSCTL_XTAL_11MHZ       0x00000B00  

//
//! External main clock crystal is 12MHz.
//
#define SYSCTL_XTAL_12MHZ       0x00000C00 

//
//! External main clock crystal is 13MHz.
//
#define SYSCTL_XTAL_13MHZ       0x00000D00  

//
//! External main clock crystal is 14MHz.
//
#define SYSCTL_XTAL_14MHZ       0x00000E00  

//
//! External main clock crystal is 15MHz.
//
#define SYSCTL_XTAL_15MHZ       0x00000F00  

//
//! External main clock crystal is 16MHz.
//
#define SYSCTL_XTAL_16MHZ       0x00001000  

//
//! External main clock crystal is 17MHz.
//
#define SYSCTL_XTAL_17MHZ       0x00001100  

//
//! External main clock crystal is 18MHz.
//
#define SYSCTL_XTAL_18MHZ       0x00001200  

//
//! External main clock crystal is 19MHz.
//
#define SYSCTL_XTAL_19MHZ       0x00001300  

//
//! External main clock crystal is 20MHz.
//
#define SYSCTL_XTAL_20MHZ       0x00001400  

//
//! External main clock crystal is 21MHz.
//
#define SYSCTL_XTAL_21MHZ       0x00001500 

//
//! External main clock crystal is 22MHz.
//
#define SYSCTL_XTAL_22MHZ       0x00001600  

//
//! External main clock crystal is 23MHz.
//
#define SYSCTL_XTAL_23MHZ       0x00001700  

//
//! External main clock crystal is 24MHz.
//
#define SYSCTL_XTAL_24MHZ       0x00001800  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_SysCtl_Exported_APIs M051 SysCtl APIs
//! @{
//
//*****************************************************************************
#define SysCtlIPClockSourceSetConvert(ulPeripheral, ulSrc, ulDivide)          \
        xSysCtlPeripheralClockSourceSet(xSYSCTL_##ulPeripheral##_##ulSrc,     \
        ulDivide);
        
extern void SysCtlDelay(unsigned long ulCount);

extern void SysCtlPeripheralReset(unsigned long ulPeripheral);
extern void SysCtlPeripheralEnable(unsigned long ulPeripheral);
extern void SysCtlPeripheralDisable(unsigned long ulPeripheral);
extern void SysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc);
extern void SysCtlHClockSourceSet(unsigned long ulHclkSrcSel);
extern void SysCtlSysTickSourceSet(unsigned long ulStclkSrcSel);

extern void SysCtlCPUReset(void);
extern void SysCtlChipReset(void);
extern void SysCtlSleep(void);
extern void SysCtlReset(void);
extern void SysCtlDeepSleep(void);

extern xtBoolean  SysCtlKeyAddrUnlock(void);
extern xtBoolean  SysCtlKeyAddrLock(void);

extern unsigned long SysCtlResetSrcGet(void);
extern void SysCtlResetSrcClear(unsigned long ulSrc);

extern void SysCtlBODEnable(xtBoolean bEnable);
extern void SysCtlBODVoltSelect(unsigned char ulVoltage);
extern void SysCtlBODLowPowerModeEnable(xtBoolean bEnable);
extern void SysCtlLowVoltRstEnable(xtBoolean bEnable);
extern xtBoolean SysCtlBODStateGet(void);
extern void SysCtlBODRstEnable(xtBoolean bEnable);
extern void SysCtlTempatureSensorEnable(xtBoolean bEnable);

extern void SysCtlIPClockDividerSet(unsigned long ulConfig);
extern void SysCtlFreqDividerOutputEnable(xtBoolean bEnable, unsigned char u8Divider);
extern void SysCtlPWRWUIntEnable(xtBoolean bEnable, xtBoolean bDelay);
extern void SysCtlPowerDownEnable(xtBoolean bEnable);
extern void SysCtlPowerDownWaitCPUSet(xtBoolean bEnable);
extern unsigned long SysCtlHClockGet(void);
extern void SysCtlHClockSet(unsigned long ulConfig);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __xSYSCTL_H__

