#ifndef _M051DNDE_COX_BASE_H_
#define _M051DNDE_COX_BASE_H_

#include "lowlayer.h"
#include "acmp.h"
#include "adc.h"
#include "sysctl.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"
#include "i2c.h"
#include "timer.h"
#include "pwm.h"
#include "wdt.h"


#define GPIOA_BASE              GPIO_PORTA_BASE
#define GPIOB_BASE              GPIO_PORTB_BASE
#define GPIOC_BASE              GPIO_PORTC_BASE
#define GPIOD_BASE              GPIO_PORTD_BASE
#define GPIOE_BASE              GPIO_PORTE_BASE
#define GPIOF_BASE              0
#define GPIOG_BASE              0
#define GPIOH_BASE              0
#define GPIOI_BASE              0
#define TIMER4_BASE             0
#define TIMER5_BASE             0
#define TIMER6_BASE             0
#define TIMER7_BASE             0
#define TIMER8_BASE             0
#define TIMER9_BASE             0
#define TIMER10_BASE            0
#define TIMER11_BASE            0
#define TIMER12_BASE            0
#define TIMER13_BASE            0
#define TIMER14_BASE            0
#define PWMC_BASE               0
#define PWMD_BASE               0
#define PWME_BASE               0
#define PWMF_BASE               0
#define PWMG_BASE               0
#define PWMH_BASE               0
#define PWMI_BASE               0
#define PWMJ_BASE               0
#define PWMK_BASE               0
#define PWML_BASE               0
#define DMA0_BASE               0
#define DMA1_BASE               0
#define DMA2_BASE               0
#define DMA3_BASE               0
#define DMA4_BASE               0
#define DMA5_BASE               0
#define DMA6_BASE               0
#define DMA7_BASE               0
#define DMA8_BASE               0
#define RTC_BASE                0

#define UART2_BASE              0
#define UART3_BASE              0
#define UART4_BASE              0
#define UART5_BASE              0
#define I2C2_BASE               0
#define I2C3_BASE               0
#define I2C4_BASE               0
#define SPI2_BASE               0
#define SPI3_BASE               0
#define SPI4_BASE               0
#define I2S0_BASE               0
#define CAN0_BASE               0
#define CAN1_BASE               0
#define CAN2_BASE               0
#define ETH_BASE                0
#define USBH_BASE               0
#define USBD_BASE               0
#define QEI_BASE                0
#define ADC0_BASE               ADC_BASE
#define ADC1_BASE               0
#define DAC0_BASE               0
#define ACMP_BASE               ACMP01_BASE
#define WWDT_BASE               WDT_BASE



#define SYSCTL_PERIPH_ACMP      SYSCTL_PERIPH_ACMP01
#define SYSCTL_PERIPH_ADC0      SYSCTL_PERIPH_ADC
#define SYSCTL_PERIPH_ADC1      0
#define SYSCTL_PERIPH_ADC2      0
#define SYSCTL_PERIPH_DMA0      0
#define SYSCTL_PERIPH_DMA1      0
#define SYSCTL_PERIPH_DMA2      0
#define SYSCTL_PERIPH_IOPA      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPB      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPC      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPD      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPE      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPF      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPG      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPH      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPI      SYSCTL_PERIPH_GPIO

#define SYSCTL_PERIPH_I2C2      0
#define SYSCTL_PERIPH_I2C3      0
#define SYSCTL_PERIPH_I2C4      0

#define SYSCTL_PERIPH_PWMA      SYSCTL_PERIPH_PWM01
#define SYSCTL_PERIPH_PWMB      SYSCTL_PERIPH_PWM23
#define SYSCTL_PERIPH_PWMC      SYSCTL_PERIPH_PWM45
#define SYSCTL_PERIPH_PWMD      SYSCTL_PERIPH_PWM67
#define SYSCTL_PERIPH_PWME      0
#define SYSCTL_PERIPH_PWMF      0
#define SYSCTL_PERIPH_PWMG      0
#define SYSCTL_PERIPH_PWMH      0
#define SYSCTL_PERIPH_PWMI      0
#define SYSCTL_PERIPH_PWMJ      0
#define SYSCTL_PERIPH_PWMK      0
#define SYSCTL_PERIPH_PWML      0
#define SYSCTL_PERIPH_RTC       0

#define SYSCTL_PERIPH_SPI2      0
#define SYSCTL_PERIPH_SPI3      0
#define SYSCTL_PERIPH_TIMER0    SYSCTL_PERIPH_TMR0
#define SYSCTL_PERIPH_TIMER1    SYSCTL_PERIPH_TMR1
#define SYSCTL_PERIPH_TIMER2    SYSCTL_PERIPH_TMR2
#define SYSCTL_PERIPH_TIMER3    SYSCTL_PERIPH_TMR3
#define SYSCTL_PERIPH_TIMER4    0
#define SYSCTL_PERIPH_TIMER5    0
#define SYSCTL_PERIPH_TIMER6    0
#define SYSCTL_PERIPH_TIMER7    0
#define SYSCTL_PERIPH_TIMER8    0
#define SYSCTL_PERIPH_TIMER9    0
#define SYSCTL_PERIPH_TIMER10   0
#define SYSCTL_PERIPH_TIMER11   0
#define SYSCTL_PERIPH_TIMER12   0
#define SYSCTL_PERIPH_TIMER13   0
#define SYSCTL_PERIPH_TIMER14   0

#define SYSCTL_PERIPH_UART2     0
#define SYSCTL_PERIPH_UART3     0
#define SYSCTL_PERIPH_UART4     0
#define SYSCTL_PERIPH_UART5     0
#define SYSCTL_PERIPH_CAN0      0
#define SYSCTL_PERIPH_CAN1      0
#define SYSCTL_PERIPH_CAN2      0
#define SYSCTL_PERIPH_I2S0      0
#define SYSCTL_PERIPH_I2S1      0
#define SYSCTL_PERIPH_USB       0
#define SYSCTL_PERIPH_WDOG      SYSCTL_PERIPH_WDT

//
//! Ethernet MAC Controller
//
#define SYSCTL_PERIPH_ETH       0

//
//! Repetitive Interrupt Timer
//
#define SYSCTL_PERIPH_RIT       0

//
//! Motor Control PWM power/clock
//
#define SYSCTL_PERIPH_MCPWM     0

//
//! Quadrature Encoder Interface 0
//
#define SYSCTL_PERIPH_QEI0      0

//
//! Quadrature Encoder Interface 0
//
#define SYSCTL_PERIPH_QEI1      0

#define SYSCTL_XTAL_25MHZ       0x00001800

#define SYSCTL_XTAL_1MHZ        0x00000400
#define SYSCTL_XTAL_2MHZ        0x00000400
#define SYSCTL_XTAL_3MHZ        0x00000400


#define ACMP_ASRCP_PIN          0
#define ACMP_ASRCP_REF          0
#define ACMP_REF_1_2V           0

#define ADC_INT_COMP            ADC_INT_COMP0 | ADC_INT_COMP1

#define ADC_EVENT_COMP0         ADC_INT_COMP0
#define ADC_EVENT_COMP1         ADC_INT_COMP1
#define ADC_EVENT_END_CONVERSION                                              \
                                xADC_INT_END_CONVERSION

#define ADC_MODE_SCAN_SINGLE_CYCLE ADC_OP_SINGLE_CYCLE
#define ADC_MODE_SCAN_CONTINUOUS   ADC_OP_CONTINUOUS

#define ADC_START_MODE_NOW      ADC_TRIGGER_PROCESSOR
#define ADC_TRIGGER_EXT_BOTH_EDGE 0



#define ADC_CTL_TS              0x80000000
#define ADC_CTL_END             0x40000000
#define ADC_CTL_D               0x20000000
#define ADC_CTL_CH0             0x00000000

#define ADC_CTL_CH1             0x00000001

#define ADC_CTL_CH2             0x00000002
#define ADC_CTL_CH3             0x00000003
#define ADC_CTL_CH4             0x00000004
#define ADC_CTL_CH5             0x00000005
#define ADC_CTL_CH6             0x00000006
#define ADC_CTL_CH7             0x00000007
#define ADC_CTL_CMP0            0x00000800
#define ADC_CTL_CMP1            0x00000900

#define ADC_COMP_INT_LOW        ADC_COMP_LESS_THAN
#define ADC_COMP_INT_MID        0
#define ADC_COMP_INT_HIGH       ADC_COMP_GREATER_EQUAL

#define I2C_MASTER_INT_DATA     I2C_INT_FUNCTION
#define I2C_MASTER_EVENT_TX     BIT_32_0
#define I2C_MASTER_EVENT_RX     BIT_32_1

#define I2C_SLAVE_INT_DATA      I2C_INT_FUNCTION

#define I2C_SLAVE_INT_START     0

#define I2C_SLAVE_INT_STOP      I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX

#define I2C_SLAVE_EVENT_START   0
#define I2C_SLAVE_EVENT_STOP    BIT_32_0
#define I2C_SLAVE_EVENT_TREQ    BIT_32_1
#define I2C_SLAVE_EVENT_RREQ    BIT_32_2

#define I2C_MASTER_ERR_NONE     0
#define I2C_MASTER_ERR_ADDR_ACK 1
#define I2C_MASTER_ERR_DATA_ACK 2
#define I2C_MASTER_ERR_ARB_LOST 3

#define SPI_INT_TXE             SPI_INT_EOT
#define SPI_INT_TXBE            0
#define SPI_INT_RXBNE           0
#define SPI_INT_ERROR           0

#define SPI_EVENT_TXE           SPI_INT_EOT
#define SPI_EVENT_TXBE          0
#define SPI_EVENT_RXBNE         0
#define SPI_EVENT_ERROR         0
#define SPI_TI_FORMAT_MODE      0
#define SPI_NMW_FORMAT_MODE     0

#define SPI_DMA_TX              0
#define SPI_DMA_RX              0
#define SPI_DMA_BOTH            0

#define SPI_SS1                 0
#define SPI_SS01                0

#define TIMER_MODE_CAPTURE      0
#define TIMER_MODE_PWM          0
#define TIMER_INT_CAP_EVENT     TIMER_INT_CAP
#define TIMER_INT_CAP_MATCH     0
#define TIMER_INT_OVERFLOW      0
#define TIMER_INT_PWM           0

#define TIMER_EVENT_MATCH       TIMER_INT_MATCH
#define TIMER_EVENT_CAP_EVENT   TIMER_INT_CAP
#define TIMER_EVENT_CAP_MATCH   0
#define TIMER_EVENT_OVERFLOW    0
#define TIMER_EVENT_PWM         0

#define TIMER_COUNT_UP          0
#define TIMER_COUNT_DOWN        0

#define TIMER_CHANNEL0          0
#define TIMER_CHANNEL1          0
#define TIMER_CHANNEL2          0
#define TIMER_CHANNEL3          0

#define UART_INT_ERROR          UART_INT_RLS
#define UART_INT_RT             UART_INT_RTO
#define UART_INT_TX             UART_INT_THRE
#define UART_INT_RX             UART_INT_RDA
#define UART_INT_DSR            0
#define UART_INT_DCD            0
#define UART_INT_CTS            0
#define UART_INT_RI             0
#define UART_INT_LMSB           0

#define UART_EVENT_TX           UART_INT_THRE
#define UART_EVENT_RX           UART_INT_RDA
#define UART_EVENT_OE           UART_INT_RLS
#define UART_EVENT_PE           UART_INT_RLS
#define UART_EVENT_FE           UART_INT_RLS
#define UART_EVENT_RT           UART_INT_RTO
#define UART_EVENT_DSR          0
#define UART_EVENT_DCD          0
#define UART_EVENT_CTS          0
#define UART_EVENT_RI           0
#define UART_EVENT_LMSB         0

#define UART_CONFIG_STOP_1      UART_CONFIG_STOP_ONE

#define UART_CONFIG_STOP_2      UART_CONFIG_STOP_TWO
#define UART_CONFIG_STOP_0_5    0
#define UART_CONFIG_STOP_1_5    0

#define UART_IRDA_MODE_NORMAL   0
#define UART_IRDA_MODE_LOW_POWER 0

#define UART_FIFO_RX_1          UART_FIFO_1BYTES
#define UART_FIFO_RX_4          UART_FIFO_4BYTES
#define UART_FIFO_RX_8          UART_FIFO_8BYTES
#define UART_FIFO_RX_14         UART_FIFO_14BYTES
#define UART_FIFO_RX_30         0
#define UART_FIFO_RX_46         0
#define UART_FIFO_RX_62         0

#define UART_OUTPUT_RTS         UART_OUTPUT_RTS_SET
#define UART_OUTPUT_DTR         0
#define UART_INPUT_CTS          UART_INPUT_CTS_L
#define UART_INPUT_RI           0
#define UART_INPUT_DCD          0
#define UART_INPUT_DSR          0


#define UART_LIN_MODE_MASTER    0
#define UART_LIN_MODE_SLAVE     0
#define UART_LIN_SYNC_BREAK_LEN_13                                           \
                                13
#define UART_LIN_SYNC_BREAK_LEN_14                                           \
                                14
#define UART_LIN_SYNC_BREAK_LEN_15                                           \
                                15
#define UART_LIN_SYNC_BREAK_LEN_16                                           \
                                16

#define WDT_S_INTSL             SYSCTL_PERIPH_WDG_S_INT10K
#define WDT_S_EXTSL             SYSCTL_PERIPH_WDG_EXTSL
#define WDT_S_HCLK_DIV          SYSCTL_PERIPH_WDG_S_HCLK_2048


#endif
