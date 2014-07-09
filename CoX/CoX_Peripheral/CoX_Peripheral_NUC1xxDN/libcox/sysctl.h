#ifndef _NUC1XX_SYSCTL_H_
#define _NUC1XX_SYSCTL_H_

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Peripheral_ID NUC1xx SysCtl Peripheral ID
//! \brief Values that show SysCtl Peripheral ID
//! Values that can be passed to the
//! SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
//! SysCtlPeripheralDisable(), and SysCtlPeripheralReset() APIs as the
//! ulPeripheral parameter.  The peripherals in the fourth group (upper nibble
//! is 3) can only be used with the SysCtlPeripheralPresent() API.
//! @{
//
//*****************************************************************************

//
//! PDMA
//
#define SYSCTL_PERIPH_PDMA      0x30040002

//
//! EBI
//
#define SYSCTL_PERIPH_EBI       0x30080000

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
#define SYSCTL_PERIPH_IOPA      0x70020000
#define SYSCTL_PERIPH_IOPB      0x70020000
#define SYSCTL_PERIPH_IOPC      0x70020000
#define SYSCTL_PERIPH_IOPD      0x70020000
#define SYSCTL_PERIPH_IOPE      0x70020000

//
//! RTC No reset
//
#define SYSCTL_PERIPH_RTC       0x00004002

//
//! TMR0
//
#define SYSCTL_PERIPH_TIMER0    0x70044004

//
//! TMR1
//
#define SYSCTL_PERIPH_TIMER1    0x70084008

//
//! TMR2
//
#define SYSCTL_PERIPH_TIMER2    0x70104010

//
//! TMR3
//
#define SYSCTL_PERIPH_TIMER3    0x70204020

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
//! SPI2
//
#define SYSCTL_PERIPH_SPI2      0x68404840

//
//! SPI3
//
#define SYSCTL_PERIPH_SPI3      0x68804880

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x40015001

//
//! UART1
//
#define SYSCTL_PERIPH_UART1     0x40025002

//
//! UART2
//
#define SYSCTL_PERIPH_UART2     0x40045004

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
//! CAN0
//
#define SYSCTL_PERIPH_CAN0      0x48015801

//
//! USBD
//
#define SYSCTL_PERIPH_USBD      0x48085808

//
//! ADC0
//
#define SYSCTL_PERIPH_ADC0      0x48105810

//
//! I2S
//
#define SYSCTL_PERIPH_I2S       0x48205820

//
//! ACMP
//
#define SYSCTL_PERIPH_ACMP      0x40405840

//
//! PS2
//
#define SYSCTL_PERIPH_PS2       0x40805880

#define SYSCTL_PERIPH_PWMA      (SYSCTL_PERIPH_PWM01|SYSCTL_PERIPH_PWM23)
#define SYSCTL_PERIPH_PWMB      (SYSCTL_PERIPH_PWM45|SYSCTL_PERIPH_PWM67)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Peripheral_Src_Clk SysCtl Peripheral Source Clock
//! \brief Values that show SysCtl Peripheral Source Clock
//! The following are values that can be passed to the
//! SysCtlPeripheralClockSourceSet()  API as the
//! ulPeripheralsrc parameter.
//! @{
//
//*****************************************************************************

//
//! Watch dog clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_WDG_S_EXT32K                                            \
                                0x00000301

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
//! Timer0 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_TMR0_S_EXT32K                                           \
                                0x00080701

//
//! Timer0 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR0_S_HCLK                                             \
                                0x00080702

//
//! Timer0 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR0_S_EXTTRG                                           \
                                0x00080703

//
//! Timer0 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR0_S_INT22M                                           \
                                0x00080704

//
//! Timer1 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_EXT12M                                           \
                                0x000C0700

//
//! Timer1 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_EXT32K                                           \
                                0x000C0701

//
//! Timer1 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR1_S_HCLK                                             \
                                0x000C0702

//
//! Timer1 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR1_S_EXTTRG                                           \
                                0x000C0703

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
//! Timer2 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_TMR2_S_EXT32K                                           \
                                0x00100701

//
//! Timer2 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR2_S_HCLK                                             \
                                0x00100702

//
//! Timer2 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR2_S_EXTTRG                                           \
                                0x00100703

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
//! Timer3 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_TMR3_S_EXT32K                                           \
                                0x00140701

//
//! Timer3 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR3_S_HCLK                                             \
                                0x00140702

//
//! Timer3 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR3_S_EXTTRG                                           \
                                0x00140703

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
//! CAN clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_CAN_S_EXT12M                                            \
                                0x001A0300

//
//! CAN clock source is PLL clock
//
#define SYSCTL_PERIPH_CAN_S_PLL                                               \
                                0x001A0301

//
//! CAN clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_CAN_S_INT22M                                            \
                                0x001A0302

//
//! PWM0 and PWM1 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM01_S_EXT12M                                          \
                                0x001C0300

//
//! PWM0 and PWM1 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_PWM01_S_EXT32K                                          \
                                0x001C0301

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
//! PWM2 and PWM3 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_PWM23_S_EXT32K                                          \
                                0x001E0301

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
//! I2S clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_I2S_S_EXT12M                                            \
                                0x10000300

//
//! I2S clock source is PLL
//
#define SYSCTL_PERIPH_I2S_S_PLL                                               \
                                0x10000301

//
//! I2S clock source is HCLK
//
#define SYSCTL_PERIPH_I2S_S_HCLK                                              \
                                0x10000302

//
//! I2S clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_I2S_S_INT22M                                            \
                                0x10000303

//
//! frequency divide source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_FRQDIV_S_EXT12M                                         \
                                0x10020300

//
//! frequency divide source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_FRQDIV_S_EXT32K                                         \
                                0x10020301

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
//! PWM4 and PWM5 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_PWM45_S_EXT32K                                          \
                                0x10040301

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
//! PWM6 and PWM7 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_PWM67_S_EXT32K                                          \
                                0x10060301

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
//! \addtogroup NUC1xx_SysCtl_Hclk_Src NUC1xx SysCtl Hclk Source
//! brief Values that show NUC1xx SysCtl Hclk Source
//! The following are values that can be passed to the
//! SysCtlHClockSourceSet()\ SysCtlHClockSet API as the
//! ulhclkSrcSel parameter.
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is external 12 MHz crystal clock
//
#define SYSCTL_HLCK_S_EXT12M    0x00000000

//
//! Systick Clock source is external 32 KHz crystal clock
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
//! \addtogroup NUC1xx_SysCtl_Stclk_Src NUC1xx SysCtl Stclk Source
//! \brief Values that show NUC1xx SysCtl Stclk Source
//! The following are values that can be passed to the
//! SysCtlSysTickSourceSet()  API as the
//! ulstclkSrcSel parameter.
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is external 12 MHz crystal clock
//
#define SYSCTL_STCLK_S_EXT12M   0x00000000

//
//! Systick Clock source is external 32 KHz crystal clock
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
//! \addtogroup NUC1xx_SysCtl_Reset_Src NUC1xx SysCtl Reset Source
//! \brief Values that show NUC1xx SysCtl Reset Source
//! The following are values that can be returned in the bit mask
//! by the SysCtlResetSrcGet() API.
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
//! \addtogroup NUC1xx_SysCtl_Bod_level NUC1xx SysCt Bod level
//! \brief Values that show NUC1xx SysCt Bod level
//! The following are values that can be passed to the
//! SysCtlSelectBODVolt()  API as the
//! ulVoltage parameter.
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
//! \addtogroup NUC1xx_SysCtl_Peripheral_ClkDiv NUC1xx SysCtl Peripheral ClkDiv
//! \brief Values that show NUC1xx SysCtl Peripheral ClkDiv
//! The following are values that can be passed to the
//! SysCtlIPClockDividerSet()  API as the
//! ulConfig parameter.
//! @{
//
//*****************************************************************************

//
//! HCLK clock divide number mask
//
#define SYSCTL_PERIPH_HCLK_D    0x00000000

//
//! USB clock divide number mask
//
#define SYSCTL_PERIPH_USB_D     0x00040800

//
//! UART clock divide number mask
//
#define SYSCTL_PERIPH_UART_D    0x00080800

//
//! CAN clock divide number mask
//
#define SYSCTL_PERIPH_CAN_D     0x000C0C00

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
//! \addtogroup NUC1xx_SysCtl_Clock_Config NUC1xx SysCtl Clock Configuration
//! \brief NUC1xx SysCtl Clock Configuration
//! The following are values that can be passed to the SysCtlClockSet() API as
//! the ulConfig parameter.
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
//! \addtogroup NUC1xx_SysCtl_Exported_APIs NUC1xx SysCtl APIs
//! \brief NUC1xx SysCtl API Reference
//! @{
//
//*****************************************************************************
#define SysCtlIPClockSourceSetConvert(ulPeripheral, ulSrc, ulDivide)          \
        xSysCtlPeripheralClockSourceSet(xSYSCTL_##ulPeripheral##_##ulSrc,     \
        ulDivide);

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
extern void SysCtlTempatureSensorEnable(xtBoolean bEnable);

extern xtBoolean SysCtlBODStateGet(void);
extern void SysCtlBODRstEnable(xtBoolean bEnable);
extern void SysCtlRCAdjValueSet(unsigned long ulAdjValue);

extern void SysCtlIPClockDividerSet(unsigned long ulConfig);
extern void SysCtlFreqDividerOutputEnable(xtBoolean bEnable, unsigned char u8Divider);
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
