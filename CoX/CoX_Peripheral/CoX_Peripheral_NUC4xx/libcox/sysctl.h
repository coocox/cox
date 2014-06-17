#ifndef _NUC4XX_SYSCTL_H_
#define _NUC4XX_SYSCTL_H_

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Peripheral_ID NUC4xx SysCtl Peripheral ID
//! \brief Values that can be passed to the
//! SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
//! SysCtlPeripheralDisable(), and SysCtlPeripheralReset().
//! @{
//
//*****************************************************************************

//
//! GPIO No enable
//
#define SYSCTL_PERIPH_GPIO      0x70020000

//
//! PDMA
//
#define SYSCTL_PERIPH_PDMA      0x00000001

//
//! ISP
//
#define SYSCTL_PERIPH_ISP       0x00000002

//
//! EBI
//
#define SYSCTL_PERIPH_EBI       0x00000003

//
//! USBD
//
#define SYSCTL_PERIPH_USBD      0x02803C84

//
//! EMAC
//
#define SYSCTL_PERIPH_ETH       0x02AFFE05

//
//! CRC
//
#define SYSCTL_PERIPH_CRC       0x00000007

//
//! CAP
//
#define SYSCTL_PERIPH_CAP       0x070FFC08

//
//! SENCLK
//
#define SYSCTL_PERIPH_SENCLK    0x000FFD09

//
//! UDC20
//
#define SYSCTL_PERIPH_UDC20     0x0000000A

//
//! WDT
//
#define SYSCTL_PERIPH_WDT       0x70000000

//
//! WWDT
//
#define SYSCTL_PERIPH_WWDT      0x57E00000

//
//! RTC
//
#define SYSCTL_PERIPH_RTC       0x40000001

//
//! TIMER0
//
#define SYSCTL_PERIPH_TIMER0    0x5E800002

//
//! TIMER1
//
#define SYSCTL_PERIPH_TIMER1    0x5EC00003

//
//! TIMER2
//
#define SYSCTL_PERIPH_TIMER2    0x5F100004

//
//! TIMER3
//
#define SYSCTL_PERIPH_TIMER3    0x5F400005

//
//! FDIV
//
#define SYSCTL_PERIPH_FDIV      0x57C00006

//
//! ACMP
//
#define SYSCTL_PERIPH_ACMP      0x40000007

//
//! I2C0
//
#define SYSCTL_PERIPH_I2C0      0x40000008

//
//! I2C1
//
#define SYSCTL_PERIPH_I2C1      0x40000009

//
//! I2C2
//
#define SYSCTL_PERIPH_I2C2      0x4000000A

//
//! I2C3
//
#define SYSCTL_PERIPH_I2C3      0x4000000B

//
//! I2C4
//
#define SYSCTL_PERIPH_I2C4      0x80000008

//
//! SPI0
//
#define SYSCTL_PERIPH_SPI0      0x5240000C

//
//! SPI1
//
#define SYSCTL_PERIPH_SPI1      0x5250000D

//
//! SPI2
//
#define SYSCTL_PERIPH_SPI2      0x5260000E

//
//! SPI3
//
#define SYSCTL_PERIPH_SPI3      0x5270000F

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x57803D10

//
//! UART1
//
#define SYSCTL_PERIPH_UART1     0x57803D11

//
//! UART2
//
#define SYSCTL_PERIPH_UART2     0x57803D12

//
//! UART3
//
#define SYSCTL_PERIPH_UART3     0x57803D13

//
//! UART4
//
#define SYSCTL_PERIPH_UART4     0x57803D14

//
//! UART5
//
#define SYSCTL_PERIPH_UART5     0x57803D15

//
//! CAN0
//
#define SYSCTL_PERIPH_CAN0      0x40000018

//
//! CAN1
//
#define SYSCTL_PERIPH_CAN1      0x40000019

//
//! USBOTG
//
#define SYSCTL_PERIPH_USBOTG    0x4000001A

//
//! ADC
//
#define SYSCTL_PERIPH_ADC0      0x5623FE1C

//
//! I2S0
//
#define SYSCTL_PERIPH_I2S0      0x7700001D

//
//! I2S0
//
#define SYSCTL_PERIPH_I2S1      0x7720001E

//
//! PS2
//
#define SYSCTL_PERIPH_PS2       0x4000001F

//
//! Smart Card 0
//
#define SYSCTL_PERIPH_SC0       0xB607FC00

//
//! Smart Card 1
//
#define SYSCTL_PERIPH_SC1       0xB627FD01

//
//! Smart Card 2
//
#define SYSCTL_PERIPH_SC2       0xB647FE02

//
//! Smart Card 3
//
#define SYSCTL_PERIPH_SC3       0xB667FF03

//
//! Smart Card 4
//
#define SYSCTL_PERIPH_SC4       0xB68BFC04

//
//! Smart Card 5
//
#define SYSCTL_PERIPH_SC5       0xB6ABFD05

//
//! PWMA01
//
#define SYSCTL_PERIPH_PWMA01    0xAE000010

//
//! PWMA23
//
#define SYSCTL_PERIPH_PWMA23    0xAE400011

//
//! PWMA45
//
#define SYSCTL_PERIPH_PWMA45    0xAE800012
          
//
//! PWMB01
//
#define SYSCTL_PERIPH_PWMB01    0xAEC00013

//
//! PWMB23
//
#define SYSCTL_PERIPH_PWMB23    0xAF000014

//
//! PWMB45
//
#define SYSCTL_PERIPH_PWMB45    0xAF400015
          
//
//! QEI0
//
#define SYSCTL_PERIPH_QEI0      0x80000016

//
//! QEI1
//
#define SYSCTL_PERIPH_QEI1      0x80000017

//
//! TAMPER
//
#define SYSCTL_PERIPH_TAMPER    0x80000018

//
//! ECAP0
//
#define SYSCTL_PERIPH_ECAP0     0x8000001A

//
//! ECAP1
//
#define SYSCTL_PERIPH_ECAP1     0x8000001B

//
//! EPWMA
//
#define SYSCTL_PERIPH_EPWMA     0x8000001C

//
//! EPWMB
//
#define SYSCTL_PERIPH_EPWMB     0x8000001D

//
//! OPA
//
#define SYSCTL_PERIPH_OPA       0x8000001E

//
//! EADC
//
#define SYSCTL_PERIPH_ADC1      0x8000001F

#define SYSCTL_PERIPH_PWMA      (SYSCTL_PERIPH_PWMA01|SYSCTL_PERIPH_PWMA23|SYSCTL_PERIPH_PWMA45)
#define SYSCTL_PERIPH_PWMB      (SYSCTL_PERIPH_PWMB01|SYSCTL_PERIPH_PWMB23|SYSCTL_PERIPH_PWMB45)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Hclk_Src NUC4xx SysCtl Hclk Source
//! \brief The following are values that can be passed to the
//! SysCtlHClockSourceSet()\ SysCtlHClockSet API as the ulhclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is external 12 MHz crystal clock
//
#define SYSCTL_HLCK_S_EXT12M    0x00000000 

//
//! Systick Clock source is external 32.768KHz crystal clock
//
#define SYSCTL_HLCK_S_EXT32K    0x00000001

//
//! Systick Clock source is PLL clock
//
#define SYSCTL_HLCK_S_PLL       0x00000002  

//
//! Systick Clock source is internal 10 kHz oscillator clock
//
#define SYSCTL_HLCK_S_INT10K    0x00000003  

//
//! Systick Clock source is PLL clock/2
//
#define SYSCTL_HLCK_S_PLL_2     0x00000004

//
//! Systick Clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_HLCK_S_INT22M    0x00000007  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Stclk_Src NUC4xx SysCtl Stick Source
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
//! Systick Clock source is 32.768KHz crystal
//
#define SYSCTL_STCLK_S_EXT32K   0x00000008

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
//! \addtogroup NUC4xx_SysCtl_Reset_Src NUC4xx SysCtl Reset Source
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
//! \addtogroup NUC4xx_SysCtl_Bod_level NUC4xx SysCt Bod level
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
//! Threshold Voltage 2.6V
//
#define SYSCTL_BOD_2_6          0x00000002  

//
//! Threshold Voltage 3.8V
//
#define SYSCTL_BOD_3_8          0x00000004  

//
//! Threshold Voltage 4.5V
//
#define SYSCTL_BOD_4_5          0x00000006  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Peripheral_ClkDiv NUC4xx SysCtl Peripheral ClkDiv
//! \brief The following are values that can be passed to the
//! SysCtlIPClockDividerSet()  API as the ulConfig parameter. 
//! @{
//
//*****************************************************************************

//
//! HCLK clock divide number mask
// 
#define SYSCTL_PERIPH_HCLK_D    0x00000F00

//
//! USB clock divide number mask
//
#define SYSCTL_PERIPH_USB_D     0x00040F00

//
//! UART clock divide number mask
//
#define SYSCTL_PERIPH_UART_D    0x00080F00

#define SYSCTL_PERIPH_ADC_D     0x0010FF00

#define SYSCTL_PERIPH_SDHOST_D  0x0018FF00

#define SYSCTL_PERIPH_SC0_D     0x1000FF00
#define SYSCTL_PERIPH_SC1_D     0x1008FF00
#define SYSCTL_PERIPH_SC2_D     0x1010FF00
#define SYSCTL_PERIPH_SC3_D     0x1018FF00

#define SYSCTL_PERIPH_SC4_D     0x2000FF00
#define SYSCTL_PERIPH_SC5_D     0x2008FF00
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Clock_Config NUC4xx SysCtl Clock Configuration
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
//! HCLK source is ext.32.768k
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
//! \addtogroup NUC4xx_SysCtl_Exported_APIs NUC2xx SysCtl APIs
//! @{
//
//*****************************************************************************

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
extern void SysCtlTempatureSensorEnable(xtBoolean bEnable);

extern xtBoolean SysCtlBODStateGet(void);
extern void SysCtlBODRstEnable(xtBoolean bEnable);

extern void SysCtlIPClockDividerSet(unsigned long ulConfig);
extern void SysCtlPWRWUIntEnable(xtBoolean bEnable, xtBoolean bDelay);
extern void SysCtlPowerDownEnable(xtBoolean bEnable);
extern void SysCtlPowerDownWaitCPUSet(xtBoolean bEnable);
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

#endif
