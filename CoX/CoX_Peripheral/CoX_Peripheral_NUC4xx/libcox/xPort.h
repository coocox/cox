#ifndef _NUC4XX_COX_BASE_H_
#define _NUC4XX_COX_BASE_H_

#include "sysctl.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"
#include "i2c.h"
#include "dma.h"
#include "timer.h"
#include "wdt.h"
#include "rtc.h"

//#define WDT_BASE                WWDT_BASE

#define SYSCTL_PERIPH_IOPA      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPB      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPC      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPD      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPE      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPF      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPG      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPH      SYSCTL_PERIPH_GPIO
#define SYSCTL_PERIPH_IOPI      SYSCTL_PERIPH_GPIO

#define SYSCTL_PERIPH_DMA0      SYSCTL_PERIPH_PDMA

#define TIMER_MODE_CAPTURE      0
#define TIMER_MODE_PWM          0

#define TIMER_INT_CAP_EVENT     TIMER_INT_CAP
#define TIMER_INT_CAP_MATCH     0
#define TIMER_INT_OVERFLOW      0
#define TIMER_INT_PWM           0

#define TIMER_EVENT_MATCH       BIT_32_0
#define TIMER_EVENT_CAP_EVENT   BIT_32_1
#define TIMER_EVENT_CAP_MATCH   0
#define TIMER_EVENT_OVERFLOW    0
#define TIMER_EVENT_PWM         0

//#define TIMER_CAP_BOTH          0

#define TIMER_COUNT_UP          0
#define TIMER_COUNT_DOWN        0

#define TIMER_CHANNEL0          0
#define TIMER_CHANNEL1          0
#define TIMER_CHANNEL2          0
#define TIMER_CHANNEL3          0

#define WDT_S_INTSL             BIT_32_0
#define WDT_S_EXTSL             BIT_32_1
#define WDT_S_HCLK_DIV          0


#define RTC_INT_SECOND          RTC_INT_TIME_TICK
#define RTC_INT_OVERFLOW        0

#define RTC_EVENT_SECOND        BIT_32_0
#define RTC_EVENT_ALARM         BIT_32_1
#define RTC_EVENT_OVERFLOW      0

#define PWM_CHANNEL6            0
#define PWM_CHANNEL7            0

#endif
