#ifndef _AU9110_COX_BASE_H_
#define _AU9110_COX_BASE_H_

#include "lowlayer.h"
#include "sysctl.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"
#include "i2c.h"
#include "rtc.h"
#include "timer.h"
#include "pwm.h"
#include "dma.h"
#include "adc.h"
#include "acmp.h"
#include "wdt.h"

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_xPort
//! \brief Define the macro which the xPeriph_Driver need but not existence in
//!        the Inc files
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowlayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowlayer_Memmap_Port Memory port
//! @{
//
//*****************************************************************************

//
//! GPIO memory map port
//
/*
#define GPIOC_BASE              GPIOC_BASE
#define GPIOD_BASE              GPIOD_BASE
#define GPIOE_BASE              GPIOE_BASE
#define GPIOF_BASE              GPIOF_BASE
#define GPIOG_BASE              GPIOG_BASE
#define GPIOH_BASE              GPIOH_BASE
#define GPIOI_BASE              GPIOI_BASE
*/

//
//! Timer memory map port
//
/*
#define TIMER2_BASE             TIMER2_BASE
#define TIMER3_BASE             TIMER3_BASE
#define TIMER4_BASE             TIMER4_BASE
#define TIMER5_BASE             TIMER5_BASE
#define TIMER6_BASE             TIMER6_BASE
#define TIMER7_BASE             TIMER7_BASE
#define TIMER8_BASE             TIMER8_BASE
#define TIMER9_BASE             TIMER9_BASE
#define TIMER10_BASE            TIMER10_BASE
#define TIMER11_BASE            TIMER11_BASE
#define TIMER12_BASE            TIMER12_BASE
#define TIMER13_BASE            TIMER13_BASE
#define TIMER14_BASE            TIMER14_BASE
*/

//
//! PWM memory map port
//
/*
#define PWMB_BASE               PWMB_BASE
#define PWMC_BASE               PWMC_BASE
#define PWMD_BASE               PWMD_BASE
#define PWME_BASE               PWME_BASE
#define PWMF_BASE               PWMF_BASE
#define PWMG_BASE               PWMG_BASE
#define PWMH_BASE               PWMH_BASE
#define PWMI_BASE               PWMI_BASE
#define PWMJ_BASE               PWMJ_BASE
#define PWMK_BASE               PWMK_BASE
#define PWML_BASE               PWML_BASE
*/

//
//! DMA memory map port
//
#define DMA0_BASE               PDMA0_BASE
#define DMA1_BASE               PDMA1_BASE
#define DMA2_BASE               PDMA2_BASE
#define DMA3_BASE               PDMA3_BASE

//
//! I2C memory map port
//
#define I2S0_BASE               I2S_BASE

//
//! ADC memeory map port
//
#define ADC0_BASE               ADC_BASE

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowlayer_Int_Assignment_Port Int assignment port
//! @{
//
//*****************************************************************************

//
//! GPIO interrupt ID port
//
#define INT_GPIOA               INT_GPIOAB
#define INT_GPIOB               INT_GPIOAB

//
//! DMA interrupt ID port
//
#define INT_DMA0                INT_PDMA
#define INT_DMA1                INT_PDMA
#define INT_DMA2                INT_PDMA

//
//! I2S interrupt ID port
//
#define INT_I2S0                INT_I2S

//
//! ADC interrupt ID port
//
#define INT_ADC0                INT_ADC

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
//! \addtogroup xSysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_ID_Port Peripheral ID port
//! @{
//
//*****************************************************************************

//
//! ADC peripheral ID port
//
#define SYSCTL_PERIPH_ADC0      SYSCTL_PERIPH_ADC

//
//! DMA peripheral ID port
//
#define SYSCTL_PERIPH_DMA0      SYSCTL_PERIPH_PDMA

//
//! PWM peripheral ID port
//
#define SYSCTL_PERIPH_PWMA      SYSCTL_PERIPH_PWM01

//
//! Timer0 peripheral ID port
//
#define SYSCTL_PERIPH_TIMER0    SYSCTL_PERIPH_TMR0

//
//! Timer1 peripheral ID port
//
#define SYSCTL_PERIPH_TIMER1    SYSCTL_PERIPH_TMR1

//
//! I2S0 peripheral ID port
//
#define SYSCTL_PERIPH_I2S0      SYSCTL_PERIPH_I2S

//
//! WDOG peripheral ID port
//
#define SYSCTL_PERIPH_WDT      SYSCTL_PERIPH_WDG

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_HCLK_set_Port HCLK set Port
//! @{
//
//*****************************************************************************

//
//! Internal RC
//
#define SYSCTL_OSC_INT          SYSCTL_OSC_49M_EN

//
//! SYSCTL_PLL_INT
//
#define SYSCTL_PLL_INT          0


//
//! Internal 10K RC
//
#define SYSCTL_OSC_INTSL        SYSCTL_OSC_16K_EN

//
//! External Oscillator 32.768K
//
#define SYSCTL_OSC_EXTSL        SYSCTL_OSC_XTAL32K_EN


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
//! \addtogroup xGPIO_Port GPIO Port
//! @{
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


#endif
