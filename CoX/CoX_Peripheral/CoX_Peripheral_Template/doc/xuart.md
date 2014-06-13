\page xUART_page xUART page 

[TOC]




xUART document
======
本篇文章主要讲解，CoX.UART的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）



# xUART Interrupts               {#xUARTInterrupt}
======

这一组宏用来表示UART的中断类型，CoX对于UART外设提取了9种类型的中断，其中有4种是通用强制型，有5种是通用非强制型。
通用强制类型的有：
- xUART_INT_ERROR
- xUART_INT_RT
- xUART_INT_TX
- xUART_INT_RX
通用非强制类型的有：
- xUART_INT_DSR
- xUART_INT_DCD
- xUART_INT_CTS
- xUART_INT_RI
- xUART_INT_LMSB
这些UART的中断宏可以传给 \ref xUARTIntEnable 和 \ref xUARTIntDisable的ulIntFlags参数使用。

以下这个表是各个系列的CoX库对于UART interrupt中断类型的实现情况：
xUART Interrupts| LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
----------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xUART_INT_ERROR | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_INT_RT    | **N** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_INT_TX    | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_INT_RX    | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_INT_DSR   | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_INT_DCD   | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_INT_CTS   | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_INT_RI    | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_INT_LMSB  | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N** 


# xUART Events               {#xUARTEvents}
======

这一组宏用来表示UART的事件类型，CoX对于UART外设提取了11种类型的事件，其中有4种是通用强制型，有7种是通用非强制型。
通用强制类型的有：
- \ref xUART_EVENT_TX
- \ref xUART_EVENT_RX
- \ref xUART_EVENT_OE
- \ref xUART_EVENT_FE
通用非强制类型的有：
- \ref xUART_EVENT_RT
- \ref xUART_EVENT_PE
- \ref xUART_EVENT_DSR
- \ref xUART_EVENT_DCD
- \ref xUART_EVENT_CTS
- \ref xUART_EVENT_RI
- \ref xUART_EVENT_LMSB
这些UART的宏可以传递给用户定义的中断回调函数ulMsgParam参数。

以下这个表是各个系列的CoX库对于UART EVENT事件类型的实现情况：

xUART Events   | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
----------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xUART_EVENT_TX  | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_EVENT_RX  | **N** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_EVENT_OE  | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_EVENT_FE  | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_EVENT_RT  | **N** | **N**   |  **N** | **N** | **N** | **Y** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_EVENT_PE  | **N** | **N**   |  **N** | **N** | **N** | **Y** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_EVENT_DSR | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_EVENT_DCD | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_EVENT_CTS | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N** 
xUART_EVENT_RI  | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_EVENT_LMSB| **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N** 


# xUART Error               {#xUARTError}
======

这一组宏用来表示UART的接收错误类型，CoX对于UART外设提取了4种接收错误类型，都定义的为通用强制类型：
- \ref xUART_RXERROR_OVERRUN
- \ref xUART_RXERROR_BREAK
- \ref xUART_RXERROR_PARITY
- \ref xUART_RXERROR_FRAMING

这些接收错误类型可以作为 \ref xUARTRxErrorGet返回值 。

以下这个表是各个系列的CoX库对于UART 接收错误类型的实现情况：

xUART Error         | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
---------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xUART_RXERROR_OVERRUN| **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_RXERROR_BREAK  | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_RXERROR_PARITY | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_RXERROR_FRAMING| **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 


# xUART Frame Config               {#xUARTFrameConfig}
======
UART数据帧格式包括数据位长度，奇偶校验位，停止位长度，CoX对这三种配置分别进行了定义。UART的数据位长度一般从5 bit~8bit，因此CoX对UART的数据位长度定义了以下几个宏：
- \ref xUART_CONFIG_WLEN_8
- \ref xUART_CONFIG_WLEN_7
- \ref xUART_CONFIG_WLEN_6
- \ref xUART_CONFIG_WLEN_5

CoX对于UART数据帧校验位定义了5个类型，其中有3个是通用强制型，2个是通用非强制型。
通用强制型的有：
- \ref xUART_CONFIG_PAR_NONE
- \ref xUART_CONFIG_PAR_EVEN
- \ref xUART_CONFIG_PAR_ODD
通用非强制型的有：
- \ref xUART_CONFIG_PAR_ONE
- \ref xUART_CONFIG_PAR_ZERO

CoX对于UART数据帧停止位定义了4个类型，其中有2个是通用强制型，2个是通用非强制型。
通用强制型的有：
- \ref xUART_CONFIG_STOP_1
- \ref xUART_CONFIG_STOP_2
通用非强制性的有：
- \ref xUART_CONFIG_STOP_0_5
- \ref xUART_CONFIG_STOP_1_5

UART的数据帧的这3中配置是用或操作之后传递给 \ref xUARTConfigSet 函数的的ulConfig参数进而对UART的数据帧格式进行配置。

以下这个表是各个系列的CoX库对于UART数据帧格式实现情况：

xUART Frame Config   | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
----------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xUART_CONFIG_WLEN_10  | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **Y** |  **N**  | **N** 
xUART_CONFIG_WLEN_9   | **N** | **Y**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **Y** |  **N**  | **N** 
xUART_CONFIG_WLEN_8   | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_CONFIG_WLEN_7   | **Y** | **N**  |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_CONFIG_WLEN_6   | **Y** | **N**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **N**  | **N** 
xUART_CONFIG_WLEN_5   | **Y** | **N**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **N**  | **N** 
xUART_CONFIG_PAR_NONE | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_CONFIG_PAR_EVEN | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_CONFIG_PAR_ODD  | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_CONFIG_PAR_ONE  | **Y** | **N**   |  **Y** | **Y** | **N** | **Y** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_CONFIG_PAR_ZERO | **Y** | **N**   |  **Y** | **Y** | **N** | **Y** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_CONFIG_STOP_1   | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_CONFIG_STOP_2   | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **Y**  | **Y** 
xUART_CONFIG_STOP_0_5 | **N** | **Y**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N** 
xUART_CONFIG_STOP_1_5 | **N** | **Y**   |  **Y** | **Y** | **N** | **Y** | **N**  | **N** | **N** |  **N**  | **N** 

# xUART IrDA Mode               {#xUARTIrDAMode}
======

这一组宏用来表示UART IrDA模式的工作模式，CoX对于UART IrDA定义了2种工作模式，
一种是标准模式，它是通用强制型的
- \ref xUART_IRDA_MODE_NORMAL
另一种是低功耗模式，它是通用非强制型的
- \ref xUART_IRDA_MODE_LOW_POWER

这组宏可以传递给 \ref xUARTIrDAConfig 函数的ulMode参数使用。

以下这个表是各个系列的CoX库对于UART IrDA工作模式实现情况：

xUART IrDA Mode          | LPC17xx| STM32F1xx | Mini51 | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
------------------------- |--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xUART_IRDA_MODE_NORMAL    | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_IRDA_MODE_LOW_POWER | **N** | **Y**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 


# xUART Enable Block               {#xUARTEnableBlock}
======

这一组宏用来表示UART外设功能的是能，CoX对于UART外设的使能定义了3个部分，分别为使能UART整体，
单独使能UART的接收，单独使能UART的发送。它们都是通用强制型的，具体宏定义如下：
- \ref xUART_BLOCK_UART
- \ref xUART_BLOCK_RX
- \ref xUART_BLOCK_TX

这组宏可以传递给 \ref xUARTEnable 及 \ref xUARTDisable 函数的ulBlock参数使用。

以下这个表是各个系列的CoX库对于UART 模块使能宏的实现情况：

xUART Enable Block| LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
-------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xUART_BLOCK_UART   | **Y** | **Y**   |  **N** | **N** | **Y** | **Y** | **Y**  | **Y** | **N** |  **N**  | **Y** 
xUART_BLOCK_RX     | **Y** | **Y**   |  **N** | **N** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **N**  | **Y** 
xUART_BLOCK_TX     | **Y** | **Y**   |  **N** | **N** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **N**  | **Y** 



# xUART FIFO RX               {#xUARTFIFORx}
======

这一组宏用来表示UART接收FIFO大小，CoX对UART的接收FIFO定义形式为xUART_FIFO_RX_n，其中n为FIFO的大小，以字节为单位。

这组宏可以传递给 \ref xUARTFIFORxLevelSet 函数的ulRxLevel参数使用。

以下这个表是各个系列的CoX库对于UART接收FIFO的实现情况：

xUART FIFO RX     | LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
-------------------|--------|----------|--------|-------|--------|--------|--------|---------|-------|----------|----------
xUART_FIFO_RX_n    | **Y** | **Y**   |  **N** | **N** | **Y** | **Y** | **Y**  | **Y** | **N** |  **N**  | **Y** 
     | **Y** | **Y**   |  **N** | **N** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **N**  | **Y** 
     | **Y** | **Y**   |  **N** | **N** | **Y** | **Y** | **Y**  | **Y** | **Y** |  **N**  | **Y** 


# xUART Modem Output            {#xUARTModemOutput}
======

这一组宏用来表示UART Modem模式的输出控制类型，CoX对UART的Modem模式的输出控制定义了两个类型，
一个是数据终端就绪，即DTR（Data Terminal Ready）；另一个是请求发送，即RTS（Request To Send)。
它们都是通用非强制型的：
- \ref xUART_OUTPUT_RTS
- \ref xUART_OUTPUT_DTR

这组宏可以传递给 \ref xUARTModemControlSet, \ref xUARTModemControlClear, \ref xUARTModemControlGet 函数的ulControl参数使用。

以下这个表是各个系列的CoX库对于UART Modem模式的输出控制类型实现情况：

xUART Modem Output| LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
-------------------|--------|----------|---------|-------|--------|--------|--------|---------|------|----------|----------
xUART_OUTPUT_RTS   | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_OUTPUT_DTR   | **Y** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 


# xUART Modem Input            {#xUARTModemInput}
======

这一组宏用来表示UART Modem模式的输入类型，CoX对UART的Modem模式的输入定义了4个类型，分别为：
清除发送  CTS（Clear To Send), 振铃提示  RI（Ring Indicator),  载波检测  DCD（Data Carrier Detect）,数据准备好  DSR（Data Set Ready）。它们都是通用非强制类型，定义如下：
- \ref xUART_INPUT_CTS
- \ref xUART_INPUT_RI
- \ref xUART_INPUT_DCD
- \ref xUART_INPUT_DSR

这组宏可以作为 \ref xURTModemStatusGet函数的返回参数。

以下这个表是各个系列的CoX库对于UART Modem模式的输入类型实现情况：

xUART Modem Output| LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
-------------------|--------|----------|---------|-------|--------|--------|--------|---------|------|----------|----------
xUART_INPUT_CTS    | **Y** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_INPUT_RI     | **Y** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_INPUT_DCD    | **Y** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 
xUART_INPUT_DSR    | **Y** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **Y**  | **Y** 


# xUART Flow Control            {#xUARTFlowControl}
======

这一组宏用来表示UART流控制， CoX对UART的流控制定义了3个类型，分别为：
- \ref xUART_FLOWCONTROL_TX
- \ref xUART_FLOWCONTROL_RX
- \ref xUART_FLOWCONTROL_NONE

这组宏可以作为 \ref xUARTFlowControlSet函数的ulMode参数使用，也可作为 \ref xUARTFlowControlGet返回值。

以下这个表是各个系列的CoX库对于UART Modem模式的输入类型实现情况：

xUART Flow Control   | LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
----------------------|--------|----------|---------|-------|--------|--------|--------|---------|------|----------|----------
xUART_FLOWCONTROL_TX  | **N** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_FLOWCONTROL_RX  | **N** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 
xUART_FLOWCONTROL_NONE| **N** | **Y**   |  **Y** | **Y** | **Y** | **Y** | **Y**  | **Y** | **N** |  **Y**  | **Y** 


# xUART LIN Config            {#xUARTLINConfig}
======

这一组宏用来表示UART LIN配置， CoX对UART的LIN配置定义了以下几个宏，它们都是通用非强制类型：
- \ref xUART_LIN_MODE_MASTER
- \ref xUART_LIN_MODE_SLAVE
- \ref xUART_LIN_SYNC_BREAK_LEN_13
- \ref xUART_LIN_SYNC_BREAK_LEN_14
- \ref xUART_LIN_SYNC_BREAK_LEN_15
- \ref xUART_LIN_SYNC_BREAK_LEN_16
可以从LIN_MODE和LIN_SYNC_BREAK_LEN中分别取一个宏进行逻辑或操作之后传递给 \ref xUARTLINConfig,
ulConfig参数。

以下这个表是各个系列的CoX库对于UART LIN模式的实现情况：

xUART Flow Control        | LPC17xx| STM32F1xx| Mini51  | M051  | NUC1xx | NUC122 | NUC123 | NUC2xx | KLX   | HT32F125x | HT32F175x              
---------------------------|--------|----------|---------|-------|--------|--------|--------|---------|------|----------|----------
xUART_LIN_MODE_MASTER      | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N** 
xUART_LIN_MODE_SLAVE       | **N** | **N**   |  **N** | **N** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N** 
xUART_LIN_SYNC_BREAK_LEN_10| **N** | **Y**   |  **N** | **Y** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N** 
xUART_LIN_SYNC_BREAK_LEN_11| **N** | **Y**   |  **N** | **Y** | **N** | **N** | **N**  | **N** | **N** |  **N**  | **N**
xUART_LIN_SYNC_BREAK_LEN_13| **N** | **N**   |  **N** | **N** | **Y** | **N** | **Y**  | **Y** | **Y** |  **N**  | **N** 
xUART_LIN_SYNC_BREAK_LEN_14| **N** | **N**   |  **N** | **N** | **Y** | **N** | **Y**  | **Y** | **Y** |  **N**  | **N**
xUART_LIN_SYNC_BREAK_LEN_15| **N** | **N**   |  **N** | **N** | **Y** | **N** | **Y**  | **Y** | **Y** |  **N**  | **N**
xUART_LIN_SYNC_BREAK_LEN_16| **N** | **N**   |  **N** | **N** | **Y** | **N** | **Y**  | **Y** | **Y** |  **N**  | **N**


xUART API              {#xUART_Exported_APIs_md}
==========


|       xUART API       |LPC17xx  |STM32F1xx| M051 |Mini51 |NUC1xx |NUC122 |NUC123 |NUC2xx |KLx    |HT32F125x| HT32F175x| LM3S  |
|:-----------------------|:-------:|:-------:|:----:|:-----:|:-----:|:-----:|:-------:|:-----:|:-----:|:-------:|:--------:|:-----:|
|  \ref xUARTConfigSet   | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y** |  **Y**| **Y** |  **Y**  |  **Y**  |  **Y** 
|  \ref xUARTEnable      | **Y**   | **Y**   | **Y**|  **Y**|  **N**|  **Y**|  **N** |  **N**| **Y** |  **Y**  |  **Y**  |  **Y** 
|  \ref xUARTDisable     | **Y**   | **Y**   | **Y**|  **Y**|  **N**|  **Y**|  **N**|  **N**|  **Y**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTFIFOEnable  | **N**   | **N**   | **N**|  **Y**|  **N**|  **N**|  **N**|  **N**|  **N**|  **N**  |  **N**   |  **Y**   
|  \ref xUARTFIFODisable  | **N**   | **N**   | **N**|  **Y**|  **N**|  **N**|  **N**|  **N**|  **N**|  **N**  |  **N**   |  **Y**  
|  \ref xUARTFIFORxLevelSet | **Y**  | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y** 
|  \ref xUARTCharsAvail   | **N**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**  
|  \ref xUARTSpaceAvail   | **N**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**  
|  \ref xUARTCharGetNonBlocking | **Y** | **Y** | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y** |  **Y** |  **Y**   
|  \ref xUARTCharGet     | **Y**   | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTCharPutNonBlocking  | **Y** | **Y** | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y** |  **Y** 
|  \ref xUARTCharPut     | **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTBusy        | **N** | **N**   | **N**|  **N**|  **N**|  **N**|  **N**|  **N**|  **Y**|  **N**  |  **N**   |  **Y**   
|  \ref xUARTIntEnable   | **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTIntCallbackInit | **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**
|  \ref xUARTIntDisable  | **Y** | **Y** | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTRxErrorGet  | **N** | **Y** | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTRxErrorClear  | **N** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTModemControlSet | **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**
|  \ref xUARTModemControlClear | **N** | **Y** | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**
|  \ref xUARTModemControlGet   | **N** | **Y** | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**
|  \ref xUARTModemStatusGet | **N** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**
|  \ref xUARTFlowControlSet | **N** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**
|  \ref xUARTFlowControlGet | **N**  | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**
|  \ref xUARTIrDAConfig  | **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**   
|  \ref xUARTIrDAEnable  | **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**  
|  \ref xUARTIrDADisable | **Y** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **N**|  **Y**  |  **Y**   |  **Y**  
|  \ref xUARTLINConfig   | **N** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**  
|  \ref xUARTLINEnable   | **N** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**  
|  \ref xUARTLINEnable   | **N** | **Y**   | **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**|  **Y**  |  **Y**   |  **Y**  


API 分组
----------
占位

API 组合使用例子
------
占位



