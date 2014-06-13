\page xSysctl_page xSysctl page 

[TOC]

xSysctl document
======
本篇文章主要讲解，CoX.SYSCTL的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）
	
<br>
CoX Sysctl mandatory peripheral ID
=========================
<br>

xACMP Peripheral Base Tab             {#xSystcl_ACMP_md}
====================
- 这组宏定义是ACMP设备的时钟开启状态, 是非强制类型，N表示该芯片不包含ACMP模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_ACMPn(n = 0, 1 ...) as the ulPeripheral parameter.

Peripheral ID\Series |         LPC17xx      |         STM32F1xx    |         Mini51       |          M051        |       NUC1xx         | NUC122/NUC123/NUC2xx |         KLx          |      HT32F125x       |        HT32F175x     |   
-------------------- | ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------|   
xSYSCTL_PERIPH_ACMPn |          **N**       |           **N**      | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 |         **N**        | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 | xSYSCTL_PERIPH_ACMP0 |


xADC Peripheral Base Tab             {#xSystcl_ADC_md}
====================
- 这组宏定义是ADC设备的时钟开启状态, N表示该芯片不包含ADC模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_ADCn(n = 0, 1 ...) as the ulPeripheral parameter.

Peripheral ID\Series|         LPC17xx     |        STM32F1xx    |        Mini51       |         M051        |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         |      HT32F125x      |        HT32F175x    |   
------------------- | --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| --------------------| --------------------|   
xSYSCTL_PERIPH_ADCn | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC1 | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 |          **N**       | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 | xSYSCTL_PERIPH_ADC0 |
                  | |                     | xSYSCTL_PERIPH_ADC2 |                     |                     |                     |                      |                     |                     |                     |       

xDMA Peripheral Base Tab            {#xSystcl_DMA_md}
===================
- 这组宏定义是DMA设备的时钟开启状态, 是非强制类型，N表示该芯片不包含DMA模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_DMAn(n = 0, 1 ...) as the ulPeripheral parameter.
Peripheral ID\Series|         LPC17xx     |        STM32F1xx    | Mini51 | MO51 |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         | HT32F125x |        HT32F175x    |   
------------------- | --------------------| --------------------| -------| -----| --------------------| ---------------------| ------------------- | ----------| --------------------|   
xSYSCTL_PERIPH_DMAn | xSYSCTL_PERIPH_DMA0 | xSYSCTL_PERIPH_DMA1 | **N**  | **N**| xSYSCTL_PERIPH_DMA0 |          **N**       | xSYSCTL_PERIPH_DMA0 |   **N**   | xSYSCTL_PERIPH_DMA0 |
                  | |                     | xSYSCTL_PERIPH_DMA2 |        |      |                     |                      |                     |           |                     |

xGPIO Peripheral Base Tab            {#xSystcl_GPIO_md}
===================
- 这组宏定义是GPIO设备的时钟开启状态, N表示该芯片不包含GPIO模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_GPIOn(n = A, B ...) as the ulPeripheral parameter.

Peripheral ID\Series |         LPC17xx      |         STM32F1xx    |         Mini51       |          M051        |       NUC1xx         |     NUC122/NUC123    |        NUC2xx        |         KLx          |      HT32F125x       |        HT32F175x     |   
-------------------- | ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------|   
xSYSCTL_PERIPH_GPIOn | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA | xSYSCTL_PERIPH_GPIOA |
                   | |         ...          |         ...          |         ...          |         ...          |         ...          |         ...          |         ...          |         ...          | xSYSCTL_PERIPH_GPIOB |         ...          |
				   | | xSYSCTL_PERIPH_GPIOE | xSYSCTL_PERIPH_GPIOG | xSYSCTL_PERIPH_GPIOF | xSYSCTL_PERIPH_GPIOE | xSYSCTL_PERIPH_GPIOE | xSYSCTL_PERIPH_GPIOD | xSYSCTL_PERIPH_GPIOF | xSYSCTL_PERIPH_GPIOE |                      | xSYSCTL_PERIPH_GPIOE | 

xI2C Peripheral Base Tab            {#xSystcl_I2C_md}
===================
- 这组宏定义是I2C设备的时钟开启状态, 是非强制类型，N表示该芯片不包含I2C模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_I2Cn(n = 0, 1 ...) as the ulPeripheral parameter.

Peripheral ID\Series|         LPC17xx     |        STM32F1xx    |        Mini51       |         M051        |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         |      HT32F125x      |       HT32F175x     |   
------------------- | --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| ------------------- | --------------------|   
xSYSCTL_PERIPH_I2Cn | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C1 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0  | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 | xSYSCTL_PERIPH_I2C0 |
                  | | xSYSCTL_PERIPH_I2C1 | xSYSCTL_PERIPH_I2C2 |                     |                     | xSYSCTL_PERIPH_I2C1 |                      | xSYSCTL_PERIPH_I2C1 |                     | xSYSCTL_PERIPH_I2C1 |
				  | | xSYSCTL_PERIPH_I2C2 |                     |                     |                     |                     |                      |                     |                     |                     | 


xSPI Peripheral Base Tab            {#xSystcl_SPI_md}
===================
- 这组宏定义是SPI设备的时钟开启状态, N表示该芯片不包含SPI模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_SPIn(n = 0, 1 ...) as the ulPeripheral parameter.

Peripheral ID\Series|         LPC17xx     |        STM32F1xx    |        Mini51       |         MO51        |       NUC1xx        | NUC122/NUC123/NUC2xx |         KLx         |      HT32F125x      |       HT32F175x     |   
--------------------| --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| --------------------| --------------------|   
xSYSCTL_PERIPH_SPIn | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI1 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0  | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 | xSYSCTL_PERIPH_SPI0 |
                  | | xSYSCTL_PERIPH_SPI1 | xSYSCTL_PERIPH_SPI2 |                     | xSYSCTL_PERIPH_SPI1 |         ...         | xSYSCTL_PERIPH_SPI1  | xSYSCTL_PERIPH_SPI1 |                     | xSYSCTL_PERIPH_SPI1 |
                  | | xSYSCTL_PERIPH_SPI2 | xSYSCTL_PERIPH_SPI3 |                     |                     | xSYSCTL_PERIPH_SPI3 |                      |                     |                     |                     | 

				  
xUART Peripheral Base Tab            {#xSystcl_UART_md}
===================
- 这组宏定义是UART设备的时钟开启状态, N表示该芯片不包含UART模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_UARTn(n = 0, 1 ...) as the ulPeripheral parameter.

Peripheral ID\Series |         LPC17xx      |         STM32F1xx    |         Mini51       |          M051        |       NUC1xx         | NUC122/NUC123/NUC2xx |         KLx          |      HT32F125x       |       HT32F175x      |   
-------------------- | ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------| ---------------------|   
xSYSCTL_PERIPH_UARTn | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 | xSYSCTL_PERIPH_UART0 |
                   | |         ...          |         ...          |                      | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART1 | xSYSCTL_PERIPH_UART1 |                      | xSYSCTL_PERIPH_UART1 |
				   | | xSYSCTL_PERIPH_UART3 | xSYSCTL_PERIPH_UART5 |                      |                      | xSYSCTL_PERIPH_UART2 |                      | xSYSCTL_PERIPH_UART2 |                      |                      |       

				   
xTIMER Peripheral Base Tab            {#xSystcl_TIMER_md}
===================
- 这组宏定义是TIMER设备的时钟开启状态, N表示该芯片不包含TIMER模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_TIMERn(n = 0, 1 ...) as the ulPeripheral parameter.

Peripheral ID\Series  |         LPC17xx       |         STM32F1xx     |         Mini51        |           M051        |        NUC1xx         | NUC122/NUC123/NUC2xx  |          KLx          |       HT32F125x       |         HT32F175x     |   
--------------------- | ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------| ----------------------|   
xSYSCTL_PERIPH_TIMERn | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 | xSYSCTL_PERIPH_TIMER0 |
                    | |         ...           |         ...           | xSYSCTL_PERIPH_TIMER1 |         ...           |         ...           |         ...           | xSYSCTL_PERIPH_TIMER1 | xSYSCTL_PERIPH_TIMER1 | xSYSCTL_PERIPH_TIMER1 |
					| | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER14|                       | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER3 | xSYSCTL_PERIPH_TIMER2 |                       |                       | 


xPWM Peripheral Base Tab            {#xSystcl_PWM_md}
===================	
- 这组宏定义是PWM设备的时钟开启状态, 是非强制类型，N表示该芯片不包含PWM模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_PWMn(n = A, B ...) as the ulPeripheral parameter.	
		
Peripheral ID\Series|         LPC17xx     |       STM32F1xx     |       Mini51        |         M051        |      NUC1xx         | NUC122/NUC123/NUC2xx |        KLx          |     HT32F125x       |       HT32F175x     |   
------------------- | --------------------| --------------------| --------------------| --------------------| --------------------| ---------------------| --------------------| --------------------| --------------------|
xSYSCTL_PERIPH_PWMn | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA  | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA | xSYSCTL_PERIPH_PWMA |
                  | |                     |         ...         |                     | xSYSCTL_PERIPH_PWMB | xSYSCTL_PERIPH_PWMB |                      | xSYSCTL_PERIPH_PWMB | xSYSCTL_PERIPH_PWMB | xSYSCTL_PERIPH_PWMB |
                  | |                     | xSYSCTL_PERIPH_PWML |                     |                     |                     |                      | xSYSCTL_PERIPH_PWMC |                     |                     |


xCAN Peripheral Base Tab            {#xSystcl_CAN_md}
===================		
- 这组宏定义是CAN设备的时钟开启状态, 是非强制类型，N表示该芯片不包含CAN模块，不支持该功能。
- 使用了这个宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- xSYSCTL_PERIPH_CANn(n = 0, 1 ...) as the ulPeripheral parameter.
	  
Peripheral ID\Series|         LPC17xx     |        STM32F1xx    | Mini51 | M051 | NUC1xx | NUC122/NUC123/NUC2xx | KLx | HT32F125x/HT32F175x |   
------------------- | --------------------| --------------------| -------| -----| -------| ---------------------| ----| --------------------|
xSYSCTL_PERIPH_CANn | xSYSCTL_PERIPH_CAN1 | xSYSCTL_PERIPH_CAN0 |  **N** | **N**|  **N** |          **N**       |**N**|        **N**        |
                  | | xSYSCTL_PERIPH_CAN2 |                     |        |      |        |                      |     |                     | 				  


CoX Other Peripheral Base Tab            {#xSystcl_other_md}
===================
- 下面这些宏定义是其他一些常见设备的时钟开启状态, N表示芯片不包含该模块。
- 使用了这些宏的API
    -  \ref xSysCtlPeripheralEnable <br>
    -  \ref xSysCtlPeripheralDisable <br>
	-  \ref xSysCtlPeripheralReset <br>
- 其中xSYSCTL_PERIPH_I2S、xSYSCTL_PERIPH_DAC、xSYSCTL_PERIPH_ETH、xSYSCTL_PERIPH_USB是非强制类型。

Peripheral ID\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122/NUC123/NUC2xx | KLx | HT32F125x/HT32F175x |   
-------------------- | --------| ----------| -------| -----| -------| ---------------------| ----| --------------------| 
xSYSCTL_PERIPH_I2S   |  **Y**  |   **N**   |  **N** | **N**|  **N** |         **N**        |**N**|        **N**        |
xSYSCTL_PERIPH_RTC   |  **Y**  |   **Y**   |  **N** | **N**|  **Y** |         **Y**        |**Y**|        **N**        |
xSYSCTL_PERIPH_DAC   |  **N**  |   **Y**   |  **N** | **N**|  **N** |         **N**        |**N**|        **N**        |
xSYSCTL_PERIPH_WDOG  |  **N**  |   **Y**   |  **N** | **Y**|  **Y** |         **Y**        |**N**|        **N**        |
xSYSCTL_PERIPH_ETH   |  **Y**  |   **N**   |  **N** | **N**|  **N** |         **N**        |**N**|        **N**        |
xSYSCTL_PERIPH_USB   |  **Y**  |   **N**   |  **N** | **N**|  **N** |         **N**        |**N**|        **N**        |

	   

CoX Sysctl mandatory System Clock               {#xSystcl_ClockSelect}
=================================
- 下面定义的是芯片的输入时钟：PLL、XTAL、XTALSL、INT、INTSL.
- 适当组合下面的时钟源形式，调用函数xSysCtlClockSet()，可以为芯片设置任意符合要求的运行频率。

SysCtl Clock \Series  |    NXP   |    ST    | Freescale |   Holtek     |
-------------         | ---------| ---------| ----------| -------------|
xSYSCTL_OSC_MAIN      |  **Y**   |  **Y**   |  **Y**    |    **Y**     |
xSYSCTL_OSC_INT       |  **Y**   |  **Y**   |  **Y**    |    **Y**     |
xSYSCTL_OSC_INTSL     |  **N**   |  **Y**   |  **Y**    |    **N**     |   
xSYSCTL_OSC_EXTSL     |  **Y**   |  **Y**   |  **Y**    |    **N**     |
xSYSCTL_XTAL_nMHZ     | 17xx:(1~25)| F103(4~16M)| KLx(3~32M) | HT32F1xx(4~16M)|
                |     | 16xx:()  |          |           |              |
xSYSCTL_INT_nMHZ      |    4M    |    8M    |    4M     |      8M      |
xSYSCTL_INTSL_nKHZ/HZ |  **N**   |    40K   |    32K    |    **N**     | 
xSYSCTL_XTALSL_nHZ    | 32.768K  | 32.768K  |  32.768K  |   32.768K    |
xSYSCTL_INT_OSC_DIS   |  **Y**   |  **Y**   |  **N**    |    **N**     |
xSYSCTL_MAIN_OSC_DIS  |  **Y**   |  **Y**   |  **N**    |    **N**     |
xSYSCTL_PLL_PWRDN     |  **Y**   |  **Y**   |  **N**    |    **N**     |

