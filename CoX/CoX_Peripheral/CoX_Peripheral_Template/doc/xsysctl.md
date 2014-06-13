\page xSysctl_page xSysctl page 

[TOC]





CoX Sysctl mandatory peripheral ID               {#PerID}
==================================
CoX ACMP Base Tab
-----------------

Peripheral ID\Series |         LPC17xx      |         STM32F1xx    |         Mini51       |          M051        |       NUC1xx         | NUC122/NUC123/NUC2xx |         KLx          |      HT32F125x       |        HT32F175x     |   
-------------------- | ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------|   
xSYSCTL_PERIPH_ACMPn |            N         |             N        | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 |           N          | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 |


CoX ADC Base Tab
----------------

Peripheral ID\Series|         LPC17xx     |        STM32F1xx    |        Mini51       |         M051        |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         |      HT32F125x      |        HT32F175x    |   
------------------- | --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| --------------------| --------------------|   
xSYSCTL_PERIPH_ADCn | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC1 | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 |            N         | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 |
                  | |                     | xSYSCTL_PERIPH_ADC2 |                     |                     |                     |                      |                     |                     |                     |       

CoX DMA Base Tab
----------------

Peripheral ID\Series|         LPC17xx     |        STM32F1xx    | Mini51 | MO51 |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         | HT32F125x |        HT32F175x    |   
------------------- | --------------------| --------------------| -------| -----| --------------------| ---------------------| ------------------- | ----------| --------------------|   
xSYSCTL_PERIPH_DMAn | xSYSCTL_PERIPH_DMA0 | xSYSCTL_PERIPH_DMA1 |   N    |   N  | xSYSCTL_PERIPH_DMA0 |            N         | xSYSCTL_PERIPH_DMA0 |     N     | xSYSCTL_PERIPH_DMA0 |
                  | |                     | xSYSCTL_PERIPH_DMA2 |        |      |                     |                      |                     |           |                     |

CoX GPIO Base Tab
-----------------

Peripheral ID\Series |         LPC17xx      |         STM32F1xx    |         Mini51       |          M051        |       NUC1xx         |     NUC122/NUC123    |        NUC2xx        |         KLx          |      HT32F125x       |        HT32F175x     |   
-------------------- | ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------|   
xSYSCTL_PERIPH_GPIOn | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA |
                   | |         ...          |         ...          |         ...          |         ...          |         ...          |         ...          |         ...          |         ...          | xSYSCTL_PERIPH_GPIOB |         ...          |
				   | | xSYSCTL_PERIPH_GPIOE | xSYSCTL_PERIPH_GPIOG | xSYSCTL_PERIPH_GPIOF | xSYSCTL_PERIPH_GPIOE | xSYSCTL_PERIPH_GPIOE | xSYSCTL_PERIPH_GPIOD | xSYSCTL_PERIPH_GPIOF | xSYSCTL_PERIPH_GPIOE |                      | xSYSCTL_PERIPH_GPIOE | 

CoX I2C Base Tab
-----------------

Peripheral ID\Series|         LPC17xx     |        STM32F1xx    |        Mini51       |         M051        |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         |      HT32F125x      |       HT32F175x     |   
------------------- | --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| ------------------- | --------------------|   
xSYSCTL_PERIPH_I2Cn | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C1 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0  | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 |
                  | | xSYSCTL_PERIPH_I2C1 | xSYSCTL_PERIPH_I2C2 |                     |                     | xSYSCTL_PERIPH_I2C1 |                      | xSYSCTL_PERIPH_I2C1 |                     | xSYSCTL_PERIPH_I2C1 |
				  | | xSYSCTL_PERIPH_I2C2 |                     |                     |                     |                     |                      |                     |                     |                     | 


CoX SPI Base Tab
-----------------

Peripheral ID\Series|         LPC17xx     |        STM32F1xx    |        Mini51       |         MO51        |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         |      HT32F125x      |       HT32F175x     |   
--------------------| --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| --------------------| --------------------|   
xSYSCTL_PERIPH_SPIn | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI1 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0  | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 |
                  | | xSYSCTL_PERIPH_SPI1 | xSYSCTL_PERIPH_SPI2 |                     | xSYSCTL_PERIPH_SPI1 |         ...         | xSYSCTL_PERIPH_SPI1  | xSYSCTL_PERIPH_SPI1 |                     | xSYSCTL_PERIPH_SPI1 |
                  | | xSYSCTL_PERIPH_SPI2 | xSYSCTL_PERIPH_SPI3 |                     |                     | xSYSCTL_PERIPH_SPI3 |                      |                     |                     |                     | 

				  
CoX UART Base Tab
-----------------

Peripheral ID\Series |         LPC17xx      |         STM32F1xx    |         Mini51       |          M051        |       NUC1xx         | NUC122/NUC123/NUC2xx |         KLx          |      HT32F125x       |       HT32F175x      |   
-------------------- | ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------|   
xSYSCTL_PERIPH_UARTn | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 |
                   | |         ...          |         ...          |                      | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART1 |                      | xSYSCTL_PERIPH_UART1 |
				   | | xSYSCTL_PERIPH_UART3 | xSYSCTL_PERIPH_UART5 |                      |                      | xSYSCTL_PERIPH_UART2 |                      | xSYSCTL_PERIPH_UART2 |                      |                      |       

				   
CoX TIMER Base Tab
-----------------

Peripheral ID\Series  |         LPC17xx       |         STM32F1xx     |         Mini51        |           M051        |        NUC1xx         | NUC122/NUC123/NUC2xx  |          KLx          |       HT32F125x       |         HT32F175x     |   
--------------------- | ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------|   
xSYSCTL_PERIPH_TIMERn | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 |
                    | |         ...           |         ...           | xSYSCTL_PERIPH_TIMER1 |         ...           |         ...           |         ...           | xSYSCTL_PERIPH_TIMER1 | xSYSCTL_PERIPH_TIMER1 | xSYSCTL_PERIPH_TIMER1 |
					| | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER14|                       | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER2 |                       |                       | 


CoX PWM Base Tab
-----------------
					
Peripheral ID\Series|         LPC17xx     |       STM32F1xx     |       Mini51        |         M051        |      NUC1xx         | NUC122/NUC123/NUC2xx |        KLx          |     HT32F125x       |       HT32F175x     |   
------------------- | --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| --------------------| --------------------|
xSYSCTL_PERIPH_PWMn | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA  | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA |
                  | |                     |         ...         |                     | xSYSCTL_PERIPH_PWMB | xSYSCTL_PERIPH_PWMB |                      | xSYSCTL_PERIPH_PWMB | xSYSCTL_PERIPH_PWMB | xSYSCTL_PERIPH_PWMB |
                  | |                     | xSYSCTL_PERIPH_PWML |                     |                     |                     |                      | xSYSCTL_PERIPH_PWMC |                     |                     |


CoX CAN Base Tab
-----------------
				  
Peripheral ID\Series|         LPC17xx     |        STM32F1xx    | Mini51 | M051 | NUC1xx | NUC122/NUC123/NUC2xx | KLx | HT32F125x/HT32F175x |   
------------------- | --------------------| --------------------| -------| -----| -------| ---------------------| ----| --------------------|
xSYSCTL_PERIPH_CANn | xSYSCTL_PERIPH_CAN1 | xSYSCTL_PERIPH_CAN0 |    N   |   N  |    N   |            N         |  N  |          N          |
                  | | xSYSCTL_PERIPH_CAN2 |                     |        |      |        |                      |     |                     | 				  


CoX ACMP Base Tab
-----------------

Peripheral ID\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122/NUC123/NUC2xx | KLx | HT32F125x/HT32F175x |   
-------------------- | --------| ----------| -------| -----| -------| ---------------------| ----| --------------------| 
xSYSCTL_PERIPH_I2S   |    Y    |     N     |    N   |   N  |    N   |           N          |  N  |          N          |
xSYSCTL_PERIPH_RTC   |    Y    |     Y     |    N   |   N  |    Y   |           Y          |  Y  |          N          |
xSYSCTL_PERIPH_DAC   |    N    |     Y     |    N   |   N  |    N   |           N          |  N  |          N          |
xSYSCTL_PERIPH_WDOG  |    N    |     Y     |    N   |   Y  |    Y   |           Y          |  N  |          N          |
xSYSCTL_PERIPH_ETH   |    Y    |     N     |    N   |   N  |    N   |           N          |  N  |          N          |
xSYSCTL_PERIPH_USB   |    Y    |     N     |    N   |   N  |    N   |           N          |  N  |          N          |

	   

CoX Sysctl mandatory System Clock               {#ClockSelect}
=================================
SysCtl Clock \Series  |    NXP   |    ST    | Freescale |   Holtek     |
-------------         | ---------| ---------| ----------| -------------|
xSYSCTL_OSC_MAIN      |    Y     |    Y     |    Y      |      Y       |
xSYSCTL_OSC_INT       |    Y     |    Y     |    Y      |      Y       |
xSYSCTL_OSC_INTSL     |    N     |    Y     |    Y      |      N       |   
xSYSCTL_OSC_EXTSL     |    Y     |    Y     |    Y      |      N       |
xSYSCTL_XTAL_nMHZ     | 17xx:(1~25)| F103(4~16M)| KLx(3~32M) | HT32F1xx(4~16M)|
                |     | 16xx:()  |          |           |              |
xSYSCTL_INT_nMHZ      |    4M    |    8M    |    4M     |      8M      |
xSYSCTL_INTSL_nKHZ/HZ |    N     |    40K   |    32K    |      N       | 
xSYSCTL_XTALSL_nHZ    | 32.768K  | 32.768K  |  32.768K  |   32.768K    |
xSYSCTL_INT_OSC_DIS   |    Y     |    Y     |    N      |      N       |
xSYSCTL_MAIN_OSC_DIS  |    Y     |    Y     |    N      |      N       |
xSYSCTL_PLL_PWRDN     |    Y     |    Y     |    N      |      N       |

