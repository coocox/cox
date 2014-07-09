#ifndef _AU9110_SYSCTL_H_
#define _AU9110_SYSCTL_H_

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Peripheral_ID AU9110 SysCtl Peripheral ID
//! \brief These values but not all that can be passed to the below:
//! SysCtlIPClockSet(),
//! SysCtlIPReset(),
//! SysCtlIPSleepClockSet().
//!
//! @{
//
//*****************************************************************************

//
//! Watchdog, not support SysCtlIPClockSet
//
#define SYSCTL_PERIPH_WDG       0x00000010

//
//! Real-time clock, not support SysCtlIPClockSet
//
#define SYSCTL_PERIPH_RTC       0x00000020

//
//! Timer0
//
#define SYSCTL_PERIPH_TMR0      0x00000040

//
//! Timer1
//
#define SYSCTL_PERIPH_TMR1      0x00000080

//
//! I2C0
//
#define SYSCTL_PERIPH_I2C0      0x00000100

//
//! SPI0
//
#define SYSCTL_PERIPH_SPI0      0x00001000

//
//! DPWM
//
#define SYSCTL_PERIPH_DPWM      0x00002000

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x00010000

//
//! BIQALC
//
#define SYSCTL_PERIPH_BIQALC    0x00040000

//
//! CRC
//
#define SYSCTL_PERIPH_CRC       0x00080000

//
//! PWM01
//
#define SYSCTL_PERIPH_PWM01     0x00100000

//
//! ACMP
//
#define SYSCTL_PERIPH_ACMP      0x00400000

//
//! SBRAM, not support SysCtlIPClockSet
//
#define SYSCTL_PERIPH_SBRAM     0x04000000

//
//! ADC
//
#define SYSCTL_PERIPH_ADC       0x10000000

//
//! I2S
//
#define SYSCTL_PERIPH_I2S       0x20000000

//
//! ANA
//
#define SYSCTL_PERIPH_ANA       0x40000000

//
//! CPU
//
#define SYSCTL_PERIPH_CPU       0x80000001

//
//! PDMA
//
#define SYSCTL_PERIPH_PDMA      0x80000002

//
//! ISP, not support SysCtlIPClockSet
//
#define SYSCTL_PERIPH_ISP       0x80000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Hclk_Src AU9110 SysCtl Hclk Source
//! \brief The following are values that can be passed to the
//! SysCtlHClockSourceSet()\ SysCtlHClockSet API as the ulhclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is internal 48 MHz oscillator clock
//
#define SYSCTL_HLCK_S_INT48M    0x00000000

//
//! Systick Clock source is external 32KHz crystal clock
//
#define SYSCTL_HLCK_S_EXT32K    0x00000001

//
//! Systick Clock source is internal 16 kHz oscillator clock
//
#define SYSCTL_HLCK_S_INT16K    0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Stclk_Src AU9110 SysCtl Stick Source
//! \brief The following are values that can be passed to the
//! SysCtlSysTickSourceSet()  API as the ulstclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is 16 kHz internal clock
//
#define SYSCTL_STCLK_S_EXT12M   0x00000000  

//
//! Systick Clock source is external 32kHz crystal
//
#define SYSCTL_STCLK_S_EXT32K   0x00000001

//
//! Systick Clock source is 16 kHz internal oscillator divided by 2.
//
#define SYSCTL_STCLK_S_EXT16K_2 0x00000002

//
//! Systick Clock source from OSC49M internal oscillator divided by 2.
//
#define SYSCTL_STCLK_S_OSC49M_2 0x00000003

//
//! Systick Clock source is from HCLK/2
//
#define SYSCTL_STCLK_S_INT22M_2 0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Reset_Src AU9110 SysCtl Reset Source
//! \brief The following are values that can be returned in the bit mask by the 
//! SysCtlResetSrcGet() API.   
//! @{
//
//*****************************************************************************

//
//! Core was reset by hardware block
//
#define SYSCTL_RSTSRC_CORE      0x00000001

//
//! Reset from the watch dog module
//
#define SYSCTL_RSTSRC_WDG       0x00000002

//
//! reset from the cortex m0 kernel
//
#define SYSCTL_RSTSRC_SYS       0x00000020

//
//! reset from a power down/standby event
//
#define SYSCTL_RSTSRC_PMU       0x00000040

//
//! reset by software setting
//
#define SYSCTL_RSTSRC_CPU       0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Peripheral_ClkDiv AU9110 SysCtl Peripheral ClkDiv
//! \brief The following are values that can be passed to the
//! SysCtlIPClockDividerSet()  API as the ulConfig parameter. 
//! @{
//
//*****************************************************************************

//
//! ADC clock divide number mask
//
#define SYSCTL_CLK_ADC_D        0x00000003

//
//! UART clock divide number mask
//
#define SYSCTL_CLK_UART_D       0x00000002

//
//! HCLK clock divide number mask
//
#define SYSCTL_CLK_HCLK_D       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Osc_Ctl AU9110 SysCtl Oscillator Control
//! \brief The following are values that can be passed to the
//! SysCtlOscCtrlSet()  API as the ulOSCCTRL parameter.
//! @{
//
//*****************************************************************************

//
//! External 32.768 kHz Crystal Enable bit
//
#define SYSCTL_OSC_XTAL32K_EN   0x00000002

//
//! OSC49M Oscillator enable bit
//
#define SYSCTL_OSC_49M_EN       0x00000004

//
//! OSC16K Oscillator enable bit
//
#define SYSCTL_OSC_16K_EN       0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Exported_APIs AU9110 SysCtl APIs
//! @{
//
//*****************************************************************************

extern void SysCtlIPReset(unsigned long ulPeriphID);
extern void SysCtlCPUReset(void);
extern void SysCtlChipReset(void);
extern void SysCtlRCAdjValueSet(unsigned long ulAdj);
extern unsigned long SysCtlEXTClockGet(void);
extern int SysCtlKeyAddrUnlock(void);
extern int SysCtlKeyAddrLock(void);
extern unsigned long SysCtlResetSrcGet(void);
extern void SysCtlResetSrcClear(unsigned long ulSrc);

extern void SysCtlIPClockSet(unsigned long ulPeriphClkID, unsigned long ulEnable);
extern void SysCtlIPSleepClockSet(unsigned long ulPeriphSlpClkID, unsigned long ulEnable);
extern void SysCtlHCLKSourceSet(unsigned long ulHclkSrcSel);
extern int SysCtlSysTickSourceSet(unsigned long ulStclkSrcSel);
extern void SysCtlIpClockSourceSet(unsigned long ulIPClkSrc, unsigned char ucClkSrcSel);
extern void SysCtlIPClockDividerSet(unsigned long ulIPDiv, unsigned long ulValue);
extern int SysCtlOscCtrlSet(unsigned long ulOSCCTRL, unsigned long ulEnable);

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

#endif
