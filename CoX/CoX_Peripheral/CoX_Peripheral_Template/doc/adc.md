\page xADC_page xADC page 


[TOC]


xADC document
======
本篇文章主要讲解，CoX.ADC的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）


# xADC Resolution               {#xADCResolution}
======

这一个宏用来表示ADC的转换分辨率，这是一种通用强制类型接口，CoX中定义如下：
- \ref xADC_DATA_BIT_SIZE

以下这个表是各个系列的CoX库中ADC转换分辨率：
xADC Resolution | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
----------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xADC_DATA_BIT_SIZE | ** Y ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** | ** Y **  | ** Y ** | ** Y ** |  ** Y **  |** Y ** 


# xADC Ints               {#xADCInts}
======

这一组宏用来表示ADC的中断类型，CoX对于ADC外设提取了2种类型的事件，其中有1种是通用强制型，有1种是通用非强制型。
通用强制类型的是：
- \ref xADC_INT_COMP

通用非强制类型的有：
- \ref xADC_INT_END_CONVERSION

这一组宏可以传递给 \ref xADCIntEnable, \ref xADCIntDisable的 ulIntFlags参数，对相应中断进行使能和除能。

xADC Interrupt          | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
---------------------- --|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xADC_INT_COMP            | ** N ** | ** Y **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** N **  |** N ** 
xADC_INT_END_CONVERSION  | ** Y ** | ** Y **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** Y **  |** Y ** 



# xADC Events               {#xADCEvents}
======

这一组宏用来表示ADC的事件类型， CoX对于ADC外设提取了2种类型的事件，其中有1种是通用强制型，有1种是通用非强制型。
通用强制类型的有：
- \ref xADC_EVENT_COMP0
- \ref xADC_EVENT_COMP1

通用非强制类型的有：
- \ref xADC_EVENT_END_CONVERSION

这些ADC的宏可以传递给用户定义的中断回调函数的ulMsgParam参数，从而回调函数在处理的时候可以知道具体发生了什么类型的中断事件。

以下这个表是各个系列的CoX库对于ADC EVENT事件类型的实现情况：

xADC Events             | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
-------------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xADC_EVENT_COMP0          | ** N ** | ** N **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** N **  |** N ** 
xADC_EVENT_COMP1          | ** N ** | ** N **  |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** N ** |  ** N **  |** N ** 
xADC_EVENT_END_CONVERSION | ** Y ** | ** Y **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** Y **  |** Y ** 


# xADC Operation Mode               {#xADCMode}
======

这一组宏用来表示ADC的操作模式，ADC的工作模式主要是单周期模式和循环模式两种，都属于通用强制类型， CoX对于ADC的这两种工作模式定义如下：
- \ref xADC_MODE_SCAN_SINGLE_CYCLE 
- \ref xADC_MODE_SCAN_CONTINUOUS

这两个宏可以传递给 \ref xADCConfigure函数的ulMode，对ADC的工作模式进行配置。
以下这个表是各个系列的CoX库对于ADC工作模式的实现情况：

xADC Operation Mode      | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
--------------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xADC_MODE_SCAN_SINGLE_CYCLE | ** Y ** | ** Y **  |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** Y **  |** Y ** 
xADC_MODE_SCAN_CONTINUOUS  | ** Y ** | ** Y **  |  ** N ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** N ** |  ** Y **  |** Y ** 


# xADC Trigger Source              {#xADCTriggerSrc}
======
ADC触发开始AD转换一般有两种类型，一种是软件触发，一种是外部信号触发。因此CoX对于ADC触发源定义了两类宏，其中一类是软件触发源，它是通用强制型，定义如下： 
- \ref xADC_TRIGGER_PROCESSOR

另一类是外部信号触发源是通用非强制型，它是通用非强制类型的，它的定义形式为 
- \ref xADC_TRIGGER_EXT_$ShortPin$
实现的时候ShortPin是对应具体的管脚名。比如在LPC17xx中，外部管脚EINT0、CAP01、MAT01、MAT03、MAT10、MAT11，因此LPC17xx的外部信号触发源有下面几个：
- \ref xADC_TRIGGER_EXT_EINT0
- \ref xADC_TRIGGER_EXT_CAP01
- \ref xADC_TRIGGER_EXT_MAT01
- \ref xADC_TRIGGER_EXT_MAT03
- \ref xADC_TRIGGER_EXT_MAT10
- \ref xADC_TRIGGER_EXT_MAT11

ADC的触发源这两个宏可以传递给 \ref xADCConfigure函数的ulTrigger参数，进而对AD触发转换的模式进行配置。

以下这个表是各个系列的CoX库对于ADC触发转换源的实现情况：

xADC Frame Config   | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
----------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xADC_TRIGGER_PROCESSOR | ** Y ** | ** Y **   |  ** Y ** | ** Y ** | ** Y ** | ** Y ** | ** Y **  | ** Y ** | ** Y ** |  ** Y **  |** Y ** 
xADC_TRIGGER_EXT_EINT0 | ** Y ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N ** 
xADC_TRIGGER_EXT_CAP01 | ** Y ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N ** 
xADC_TRIGGER_EXT_MAT01 | ** Y ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N ** 
xADC_TRIGGER_EXT_MAT03 | ** Y ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N ** 
xADC_TRIGGER_EXT_MAT10 | ** Y ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N ** 
xADC_TRIGGER_EXT_MAT11 | ** Y ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N ** 
xADC_TRIGGER_EXT_PB0 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |**Y **
xADC_TRIGGER_EXT_PB1 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **

xADC_TRIGGER_EXT_PB2 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB3 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB4 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB5 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB6 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB6 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB7 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB8 | ** N ** | ** N **   |  ** N ** | ** N ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB9 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB10 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB11 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB12 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB13 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB14 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PB15 | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** Y **  |** Y **
xADC_TRIGGER_EXT_PD2 | ** N ** | ** N **   |  ** Y ** | ** Y ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N **
xADC_TRIGGER_EXT_INT11 | ** N ** | ** Y **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N **


# xADC External Tigger Source Mode               {#xADCExtTriggerMode}
======

在ADC的触发设置为外部触发模式的情况下，外部触发的方式也是不同的，一般可以设置为管脚的高电平触发，低电平触发， 上升沿触发，下降沿触发，上下沿触发这五种模式，它们都是通用非强制型的，在CoX中定义如下：
- \ref xADC_TRIGGER_EXT_LOW_LEVEL
- \ref xADC_TRIGGER_EXT_HIGH_LEVEL
- \ref xADC_TRIGGER_EXT_RISING_EDGE
- \ref xADC_TRIGGER_EXT_FALLING_EDGE
- \ref xADC_TRIGGER_EXT_BOTH_EDGE

这组宏需要先和外部信号触发宏进行或操作之后再传递给 \ref xADCIrDAConfig 函数的ulTrigger参数使用， 例如
（xADC_TRIGGER_EXT_PB8 |xADC_TRIGGER_EXT_LOW_LEVEL）。

以下这个表是各个系列的CoX库对于ADC 外部触发模式的实现情况：

xADC External Tigger Mode| LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
------------------------- |--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xADC_TRIGGER_EXT_LOW_LEVEL| ** N ** | ** N **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** | ** N **  |** N ** 
xADC_TRIGGER_EXT_HIGH_LEVEL| ** N ** | ** N **   | ** N ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** | ** N **  |** N ** 
xADC_TRIGGER_EXT_RISING_EDGE| ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** Y ** | ** Y **  | ** Y ** | ** Y ** | ** Y **  |** Y ** 
xADC_TRIGGER_EXT_FALLING_EDGE| ** Y ** | ** N **   | ** N ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** | ** N **  |** N ** 
xADC_TRIGGER_EXT_BOTH_EDGE| ** N ** | ** N **   | ** Y ** | ** Y ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** | ** N **  |** N ** 


# xADC Step Config               {#xADCStepConfig}
======
这一组宏包含ADC转换系列中每一个单步转换的配置。包括采集通道，比较器选择， 单端/差分采集，是否结束。
采集通道分为一般的采集通道和芯片内置的温度传感器采集通道两类，一般的采集通道在CoX中是通用强制类型，定义如下：
- \ref xADC_CTL_CH$x$ 
其中$x$从0到n， 不同MCU的ADC通道数目不同，例如LPC17xx的通道从xADC_CTL_CH0到xADC_CTL_CH7
温度传感器通道在CoX中是通用非强制类型，定义如下：
- \ref xADC_CTL_TS

ADC的比较器用于监测ADC某个通道转换的值，它是通用非强制类型，定义如下：
- \ref xADC_CTL_CMP$x$
其中$x$从0到n， 不同MCU的ADC比较器数目不同，例如LPC17xx的比较器从xADC_CTL_CMP0到xADC_CTL_CMP1

ADC有单端输入和差分输入，一般默认情况下是单端输入。在CoX中它是通用非强制型，定义如下：
- \ref xADC_CTL_D

如果要将ADC的某一步设置为转换序列的最后一步，CoX中用一个通用非强制类型的宏，定义如下：
- \ref xADC_CTL_END

以上配置中，ADC通道选择是必须的，其余的是否需要对转换值进行比较，是否为差分输入，是否是转换序列最后一步是根据具体情况进行选择的，对他们进行或操作之后传递给 \ref xADCStepConfigure函数的ulConfig参数，进而对ADC每一个单步转换的配置。

以下这个表是各个系列的CoX库对于ADC单步转换配置的实现情况：

xADC Step Config | LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX  | HT32F125x | HT32F175x              
-------------------|-------|----------|--------|-------|--------|--------|--------|--------|------|----------|----------
xADC_CTL_CH0       | ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** |** Y ** 
xADC_CTL_CH0       | ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** |** Y ** 
xADC_CTL_CH0       | ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** |** Y ** 
xADC_CTL_CH0       | ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** |** Y ** 
xADC_CTL_CH0       | ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** |** Y ** 
xADC_CTL_CH0       | ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** |** Y ** 
xADC_CTL_CH0       | ** Y ** | ** Y **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** Y ** |** Y **  
xADC_CTL_TS        | ** N ** | ** N **   | ** N ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** N ** |** N **
xADC_CTL_CMP0      | ** N ** | ** N **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** N ** |** N ** 
xADC_CTL_CMP1      | ** N ** | ** N **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** N ** |** N ** 
xADC_CTL_D         | ** N ** | ** N **   | ** N ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** N ** |** N **
xADC_CTL_END       | ** N ** | ** N **   | ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y ** | ** Y ** | ** Y ** | ** N ** |** N **


# xADC Comparator ID               {#xADCComparatorID}
======

这一组宏用来表示ADC的比较器ID，CoX提取了两个比较器，它们是通用非强制型的，定义如下:
- \ref xADC_COMP_0
- \ref xADC_COMP_1

这组宏可以传递给 \ref xADCCompConditionConfig，\ref xADCCompRegionSet函数去配置比较器。
也可以传递给\ref xADCCompEnable，\ref xADCCompDisable去使能和除能比较器。

以下这个表是各个系列的CoX库对于ADC比较器ID的实现情况： 




xADC Comparator ID| LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
-------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xADC_COMP_0        | ** N ** | ** N **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** N **  |** N ** 
xADC_COMP_1        | ** N ** | ** N **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** N **  |** N ** 



# xADC Comp Interrupt Condition            {#xADCompIntCondition}
======

这一组用来表示ADC 比较器中断发生的条件，CoX提取了三种条件，分别为ADC转换值比比较器最低阀值低，转换值介于比较器最低阀值和最高阀值之间，转换值高于最高阀值。定义如下：
- \ref xADC_COMP_INT_LOW
- \ref xADC_COMP_INT_MID
- \ref xADC_COMP_INT_HIGH

这组宏可以传递给 \ref xADCCompConditionConfig 函数的ulConfig参数，对比较值中断条件进行配置。

以下这个表是各个系列的CoX库对于ADC Modem模式的输出控制类型实现情况：

xADCompIntCondition | LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
-------------------|--------|----------|---------|-------|--------|--------|--------|---------|------|----------|----------
xADC_COMP_INT_LOW  | ** N ** | ** N **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** N **  |** N ** 
xADC_COMP_INT_MID  | ** N ** | ** N **   |  ** N ** | ** N ** | ** N ** | ** N ** | ** N **  | ** N ** | ** N ** |  ** N **  |** N** 
xADC_COMP_INT_HIGH | ** N ** | ** N **   |  ** Y ** | ** Y ** | ** Y ** | ** N ** | ** Y **  | ** Y ** | ** Y ** |  ** N **  |** N ** 


xADC API              {#xADC_Exported_APIs_md}
==========


|xADC API              |LPC17xx|STM32F1xx| M051 |Mini51 |NUC1xx |NUC122 |NUC123 |NUC2xx |KLx|HT32F125x| HT32F175x| |:-----------------------|:-------:|:-------:|:----:|:-----:|:-----:|:-----:|:-------:|:-----:|:-----:|:-------:|:--------:|
| \ref xADCConfigure     | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **N**|  **Y** |  **Y**| **Y** |  **Y**  |  **Y**  |
| \ref xADCStepConfigure | **Y**   | **Y**   | **Y**|  **Y**|  **N**|  **N**|  **N** |  **Y**| **Y** |  **Y**  |  **Y**  |
| \ref xADCIntCallbackInit| **Y**   | **Y**   | **Y**|  **Y**|  **N**|  **N**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |
| \ref xADCIntEnable     | **Y**   | **N**   | **N**|  **Y**|  **N**|  **N**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |
| \ref xADCIntDisable    | **Y**   | **N**   | **N**|  **Y**|  **N**|  **N**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |
| \ref xADCDMAEnable     | **N**   | **N**   | **N**|  **N**|  **Y**|  **N**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |
| \ref xADCDMADisable    | **N**   | **N**   | **N**|  **N**|  **Y**|  **N**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |
| \ref xADCEnable        | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **N**|  **Y**|  **N**  |  **N**   |
| \ref xADCDisable       | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **N**|  **Y**|  **N** |  **N** | 
| \ref xADCProcessorTrigger| **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |
| \ref xADCDataGet       | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y** |
| \ref xADCOverflow      | **Y**   | **N**   | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **N**|  **N**|  **Y**  |  **Y**   |
| \ref xADCOverflowClear | **Y**   | **N**   | **N**|  **N**|  **N**|  **N**|  **Y**|  **N**|  **N**|  **Y**  |  **Y**   |
| \ref xADCCompConditionConfig | **N** | **N** | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **Y**|  **Y**|  **N**  |  **N**  |
| \ref xADCCompRegionSet   | **N** | **N**   | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **Y**|  **Y**|  **N**  |  **N**   |
| \ref xADCCompEnable      | **N** | **N**   | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **Y**|  **Y**|  **N**  |  **N**   |
| \ref xADCCompDisable    | **N** | **N**    | **Y**|  **Y**|  **Y**|  **N**|  **Y**|  **Y**|  **Y**|  **N**  |  **N**   |

API 分组
----------
占位

API 组合使用例子
------
占位



