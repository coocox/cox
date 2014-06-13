\page xGPIO_page xGPIO page 

[TOC]




xGPIO document
======
本篇文章主要讲解，CoX.GPIO的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）
 

xGPIO interrupt number config   {#xGPIO_Config_md}
================

- 这个宏是提供给用户的，用户根据自己使用的GPIO中断情况来配置这个宏，默认值是8，表示可以用8个GPIO可以使用中断，具体会对应8个回调函数。
- 这个宏不是API的参数
- 在CoX规范中，它是强制的，其形式 就是一个固定的宏名称：\ref xGPIO_INT_NUMBER
- 所有的系列都需要提供这个配置宏。

|xGPIO General Pin ID    |       CoX      |     all series         |
|:----------------------:|:--------------:|:----------------------:|
|xGPIO_INT_NUMBER        |    Mandatory   |  xGPIO_INT_NUMBER      |



xGPIO General Pin ID           {#xGPIO_General_Pin_IDs_md}
===========================

- 这个参数一个GPIO port对应的pin的位域编码，使用位域编码的好处：
    - 与寄存器实际的位域一一对应
    - 可以使用 | 操作 一次性操作 多个位域。
- 这组宏定义在CoX中是强制的，在每个系列中都必须实现这样一组宏。其强制的形式为xGPIO_PIN_n。
- 使用了这个宏的API
    -  \ref xGPIODirModeSet <br>
    -  \ref xGPIODirModeGet <br>
    -  \ref xGPIOPinIntCallbackInit <br>
    -  \ref xGPIOPinIntEnable <br>
    -  \ref xGPIOPinIntDisable <br>
    -  \ref xGPIOPinIntClear <br>
    -  \ref xGPIOPinRead <br>
    -  \ref xGPIOPinWrite <br>
    -  \ref xGPIOPadConfigSet <br>
    -  \ref xGPIOPadConfigGet <br>
- 对于每个系列这个n的大小可以不同。一般n可以是8，16，32.

CoX 支持了以下的系列，这个参数在各个系列的实现情况如下表所示：

表格一
----------

|  xGPIO General Pin ID    | LPC17xx          |STM32F1xx         |NUC1xx/NUC2xx/NUC122/NUC123|Mini51/M051|Freescale       |Holtek            |
|:------------------------:|:-------------:   |:----------:      |:----------:      |:----------:      |:-----------     :|:-----------:     |
|  xGPIO_PIN_0             | xGPIO_PIN_0      |xGPIO_PIN_0       |xGPIO_PIN_0       |xGPIO_PIN_0       |xGPIO_PIN_0       |xGPIO_PIN_0       |
|  xGPIO_PIN_1             | xGPIO_PIN_1      |xGPIO_PIN_1       |xGPIO_PIN_1       |xGPIO_PIN_1       |xGPIO_PIN_1       |xGPIO_PIN_1       |
|    ...                   |   ...            |...               |...               |...               |...               |...               |
|                          | xGPIO_PIN_30     |xGPIO_PIN_14      |xGPIO_PIN_14      |xGPIO_PIN_6       |xGPIO_PIN_30      |xGPIO_PIN_14      |
|  xGPIO_PIN_n             | **xGPIO_PIN_31** | **xGPIO_PIN_15** | **xGPIO_PIN_15** | **xGPIO_PIN_7**  | **xGPIO_PIN_31** | **xGPIO_PIN_15** |


xGPIO Dir Mode  {#xGPIO_Dir_Mode_md}
========

- 这组宏用来表示 GPIO方向的模式，CoX抽出了以下5种：输入、输出、准双端、开漏输出、作为外设管脚
- 这组宏作为 xGPIODirModeSet() 的ulPinIO参数传入，或者是 xGPIODirModeGet()的返回值。
- 其形式为固定的名称 :
    - \ref xGPIO_DIR_MODE_IN
    - \ref xGPIO_DIR_MODE_OUT
    - \ref xGPIO_DIR_MODE_HW
    - \ref xGPIO_DIR_MODE_QB
    - \ref xGPIO_DIR_MODE_OD
- 不一定所有的芯片都具备这5种功能，以下表格列举了五种模式在各个系列的实现情况：

|  xGPIO Dir Mode       | LPC17xx|STM32F1xx|M051 |Mini51 |NUC1xx |NUC122 |NUC123 |NUC2xx |KLx    |HT32F125x| HT32F175x| 
|:---------------------:|:------:|:-------:|:---:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-------:|:--------:|
|  xGPIO_DIR_MODE_IN    |    **Y**   |    **Y**    | **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**     |   **Y**     |
|  xGPIO_DIR_MODE_OUT   |    **Y**   |    **Y**    | **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**     |   **Y**     |
|  xGPIO_DIR_MODE_HW    |    *N*     |    **Y**    | *N*   |   *N*   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   *N*   |   **Y**     |   **Y**     |
|  xGPIO_DIR_MODE_QB    |    *N*   |    **Y**    | **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   *N*   |   *N*     |   *N*     |
|  xGPIO_DIR_MODE_OD    |    **Y**   |    **Y**    | **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   **Y**   |   *N*   |   **Y**     |   **Y**     |

>\note 对于强制参数，有的系列是No，也就是没有这个功能时，我们一般空实现一个。

xGPIO Int Type  {#xGPIO_Int_Type_md}
===========
- 这里定义的是GPIO支持的一些中断类型，包括:
    - 上升沿 \ref xGPIO_RISING_EDGE
    - 下降沿 \ref xGPIO_FALLING_EDGE
    - 高电平 \ref xGPIO_HIGH_LEVEL
    - 低电平 \ref xGPIO_LOW_LEVEL
    - 双边沿 \ref xGPIO_BOTH_EDGES
    - 双电平 \ref xGPIO_BOTH_LEVEL
- 这组宏作为 xGPIOPinIntEnable() 的ulIntType参数传入。
- MCU都会有 上升沿和下降沿。一些MCU还支持电平触发。

|  xGPIO Int Type       | LPC17xx |STM32F1xx| M051 |Mini51 |NUC1xx |NUC122 |NUC123 |NUC2xx |KLx    |HT32F125x| HT32F175x| LM3S     |
|-----------------------|---------|:-------:|: ---:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-------:|:--------:|:--------:|
|  xGPIO_FALLING_EDGE   |  **Y**  |  **Y**  | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  xGPIO_RISING_EDGE    |  **Y**  |  **Y**  | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  xGPIO_LOW_LEVEL      |   *N*   |   *N*   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  xGPIO_HIGH_LEVEL     |   *N*   |   *N*   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  xGPIO_BOTH_LEVEL     |   *N*   |   *N*   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|   *N* |   *N*   |   *N*    |   *N*    |
|  xGPIO_BOTH_EDGES     |  **Y**  |  **Y**  | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |




xGPIO Pad Config Strength {#xGPIO_Pad_Config_Strength_md}
=============
- 这组宏定义是定义 管脚的驱动能力，是个非强制性的参数（其对应的函数也是非强制性的） 
- 这组宏作为 xxx() 的 xx 参数传入。
- 其宏的形式 是 xGPIO_STRENGTH_nMA，其中nMA表示 具体的驱动能力，芯片不同 n 也会不同，比如：TI 的LM3S系列 n = 2，4，8。
- 当然很多芯片没有这个功能，比如ST NXP的芯片。
详见下表：
|  xGPIO Pad Strength   | LPC17xx|STM32F1xx|M051/Mini51/NUC1xx/NUC122/NUC123/NUC2xx|KLx   |HT32F125x/HT32F175x|LM3S  |
|-----------------------|:------:|:------:|:--------------------------------------:|:----:|:-----------------:|:----:|
|  xGPIO_STRENGTH_2MA   |  *N*   |  *N*   |  *N*                                   |  *N* |  *N*              | **Y**|
|  xGPIO_STRENGTH_4MA   |  *N*   |  *N*   |  *N*                                   |  *N* | **Y**             | **Y**|
|  xGPIO_STRENGTH_8MA   |  *N*   |  *N*   |  *N*                                   |  *N* | **Y**             | **Y**|


xGPIO Short Pin ID           {#xGPIO_Short_Pin_md} 
======
Short Pin 是为了让用户更加方便的使用GPIO而引入的，比如 PA5表示GPIO portA的5号管脚，或者是 port0
（有些厂商用0，1，2...表示port） 的5号管脚。Short Pin 适合单个管脚的应用场合。对于需要多个引脚并行操作的，
不适合使用Short Pin 

我们提供了一系列的Short Pin 的API"函数"(其实是一些函数宏)，这些宏分三类：
- 一类是作为GPIO的功能
    - xGPIOSPinDirModeSet()
    - xGPIOSPinIntCallbackInit()
    - xGPIOSPinIntEnable()
    - xGPIOSPinIntDisable()
    - xGPIOSPinIntClear()
    - xGPIOSPinRead()
    - xGPIOSPinWrite()
    - xGPIOSPinTypeGPIOInput()
    - xGPIOSPinTypeGPIOOutput()
    - xGPIOSPinTypeGPIOOutputOD()
- 另一类是设置引脚的外设功能
    - xSPinTypeADC()
    - xSPinTypeCAN()
    - xSPinTypeI2C()
    - xSPinTypePWM()
    - xSPinTypeSPI()
    - xSPinTypeTimer()
    - xSPinTypeUART()
    - xSPinTypeDAC()
    - xSPinTypeACMP()
    - xSPinTypeI2S()
- 最后一类是将Spin转化成API函数的参数
    - xGPIOSPinToPeripheralId()
    - xGPIOSPinToPort()
    - xGPIOSPinToPortPin()
    - xGPIOSPinToPin()
 
将PA0设置为输出，直接 xGPIOSPinTypeGPIOOutput(PA0)就行了,将PA0置1，xGPIOSPinWrite(PA0,1),清零则是 xGPIOSPinWrite(PA0,0)。
Short Pin的好处是可以直接传入 PA0这个字符串，而毋庸关心。PA0的寄存器地址或者port A的结构体变量等。

> API 部分我会给出具体的例子来说明。


|xGPIO Short Pin ID| LPC17xx    |STM32F1xx   |M051       |Mini51     |NUC1xx      |NUC122      |NUC123      |NUC2xx      |KLx         |HT32F125x   |HT32F175x   |LM3S       |
|:-----------------|:----------:|:----------:|:---------:|:---------:|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:---------:|
|PXn               |PA0 ... PA31|PA0 ... PA15|PA0 ... PA7|PA0 ... PA7|PA0 ... PA15|PA10... PA15|PA10... PA15|PA0 ... PA15|PA0 ... PA31|PA0 ... PA15|PA0 ... PA15|PA0 ... PA7|
|(X = A/B/...)     |PB0 ... PB31|PB0 ... PB15|PB0 ... PB7|PB0 ... PB7|PB0 ... PB15|PB0 ... PB15|PB0 ... PB15|PB0 ... PB15|PB0 ... PB31|PB0 ... PB15|PB0 ... PB15|PB0 ... PB7|
|(n = 0/1/...)     |PC0 ... PC31|PC0 ... PC15|PC0 ... PC7|PC0 ... PC7|PC0 ... PC15|PC0 ... PC13|PC0 ... PC13|PC0 ... PC15|PC0 ... PC31|  ---       |PC0 ... PC15|PC0 ... PC7|
|                  |PD0 ... PD31|PD0 ... PD15|PD0 ... PD7|PD0 ... PD7|PD0 ... PD15|PD0 ... PD11|PD0 ... PD11|PD0 ... PD15|PD0 ... PD31|  ---       |PD0 ... PD15|PD0 ... PD7|
|                  |PE0 ... PE31|PE0 ... PE15|PE0 ... PE7|PE0 ... PE7|PE0 ... PE15|  ---       |  ---       |PE0 ... PE15|PE0 ... PE31|  ---       |PE0 ... PE15|PE0 ... PE7|
|                  |PF0 ... PF31|PF0 ... PF15|  ---      |  ---      |  ---       |  ---       |PF0 ... PF3 |PF0 ... PF3 |  ---       |  ---       |  ---       |PF0 ... PF7|
|                  |PG0 ... PG31|PG0 ... PG15|  ---      |  ---      |  ---       |  ---       |  ---       |  ---       |  ---       |  ---       |  ---       |PG0 ... PG7|
|                  |  ---       |  ---       |  ---      |  ---      |  ---       |  ---       |  ---       |  ---       |  ---       |  ---       |  ---       |PH0 ... PH7|
|                  |  ---       |  ---       |  ---      |  ---      |  ---       |  ---       |  ---       |  ---       |  ---       |  ---       |  ---       |PJ0 ... PJ7|


General Peripheral Pin            {#xGPIO_Peripheral_Pin_md} 
======
- CoX 为了让用户更加方便的使用 GPIO的外设功能，特定义了一组SPin to Peripheral的功能。比如：
    - xSPinTypeADC()
    - xSPinTypeCAN()
    - xSPinTypeI2C()
    - xSPinTypePWM()
    - xSPinTypeSPI()
    - xSPinTypeTimer()
    - xSPinTypeUART()
    - xSPinTypeDAC()
    - xSPinTypeACMP()
    - xSPinTypeI2S()
    
这些函数的特点是一次值配置一个管脚，其中一个参数就是 上面的Short Pin，另外一个参数就是
这里要介绍的 外设管脚名称（General Peripheral Pin），比如：ADC0 I2C0SCK SPI0CS等。
比如 xSPinTypeADC(ADC0,PA0) 就是将PA0设置为 ADC 通道 0 的输入引脚。

- 这些外设引脚名称的形式是：外设名引脚名+编号
    - ADC0 ADC1 ... ADC7
    - I2C0SCK I2C1SCK I2C2SCK
    - UART0RX UART1RX UART2RX UART3RX
    - ...
    
- 下面 我们列举 CoX定义的一些外设管脚名称。

| General Peripheral Pin  |          LPC17xx                |
|-------------------------|---------------------------------|
| ADCn                    | ADC0 ADC1 ... ADC7              |
| I2CnSCK                 | I2C0SCK I2C1SCK I2C2SCK         |
| I2CnSDA                 | I2C0SDA I2C1SDA I2C2SDA         |
| SPInCLK                 | SPI0CLK                         |
| SPInMOSI                | SPI0MOSI                        |
| SPInMISO                | SPI0MISO                        |
| SPInCS                  | SPI0CS                          |
| UARTnRX                 | UART0RX UART1RX UART2RX UART3RX |
| UARTnTX                 | UART0TX UART1TX UART2TX UART3TX |
| UARTnCTS                | UART1CTS                        |
| UARTnDCD                | UART1DCD                        |
| UARTnDSR                | UART1DSR                        |
| UARTnDTR                | UART1DTR                        |
| PWMn                    | PWM0 ... PWM6                   |
| TIMCCPn                 | TIMCCP0 ... TIMCCP7             |
| DACOUTn                 | DACOUT0                         |
| CANnRX                  | CAN0RX  CAN1RX                  |
| CANnTX                  | CAN0TX  CAN1TX                  |
|I2SnRXSCK                | I2S0RXSCK                       |
|I2SnRXMCLK               | I2S0RXMCLK                      |
|I2SnRXSD                 | I2S0RXSD                        |
|I2SnRXWS                 | I2S0RXWS                        |
|I2SnTXSCK                | I2S0TXSCK                       |
|I2SnTXMCLK               | I2S0TXMCLK                      |
|I2SnTXSD                 | I2S0TXSD                        |
|I2SnTXWS                 | I2S0TXWS                        |

\note 关于 timer的引脚，由于不同系列的timer相差太大：有的有输入而有的没有，有的有几组输出，有的输入输出公用一个引脚，
有的是单独分开的。所以，我们只定义了timer的输出引脚标准。


xGPIO API              {#xGPIO_Exported_APIs_md}
==========


|       xGPIO API                 |LPC17xx  |STM32F1xx| M051 |Mini51 |NUC1xx |NUC122 |NUC123 |NUC2xx |KLx    |HT32F125x| HT32F175x| LM3S     |
|:--------------------------------|:-------:|:-------:|: ---:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-------:|:--------:|:--------:|
|  \ref xGPIODirModeSet           | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinToPeripheralId   | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinToPort           | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinToPin            | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinDirModeSet       | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIODirModeGet           | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinIntCallbackInit   | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinIntEnable         | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinIntEnable        | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinIntDisable        | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinIntDisable       | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinIntStatus         | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinIntClear          | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinIntClear         | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinRead              | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinRead             | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinWrite             | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinWrite            | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOPinConfigure         | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinTypeGPIOInput    | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinTypeGPIOOutput   | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinTypeGPIOOutputOD | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xGPIOSPinTypeGPIOOutputQB | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeADC              | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeDAC              | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeCAN              | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeI2C              | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypePWM              | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeSPI              | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeTimer            | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeUART             | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeACMP             |  *N*    | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |
|  \ref xSPinTypeI2S              |  *N*    | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   |


API 分组
----------
占位

API 组合使用例子
------
占位
